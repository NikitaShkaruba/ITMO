#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include "lib/vendor/ipc.h"
#include "lib/vendor/common.h"
#include "lib/vendor/pa1.h"
#include "lib/structs.h"

void init(Lab* lab) {
  lab->n_process_pid = getpid(); // open
  lab->n_parent_pid = 0; // parent has no parent

  lab->main_log = fopen(events_log, "a");
  lab->pipes_log = fopen(pipes_log, "w");

  // allocate pipes array
  lab->channels = calloc((size_t) lab->n_processes_count, sizeof(Channel*));
  for (int i = 0; i < lab->n_processes_count; ++i) {
    lab->channels[i] = calloc((size_t) lab->n_processes_count, sizeof(Channel));
  }

  // init pipes
  for (int i = 0; i < lab->n_processes_count; ++i) {
    for (int j = 0; j < lab->n_processes_count; ++j) {
      if (i == j) continue; // I -> I communication refused

      if (pipe((int*) &lab->channels[i][j]) != -1) {
        fcntl(lab->channels[i][j].rf, F_SETFL, O_NONBLOCK);
        fcntl(lab->channels[i][j].wf, F_SETFL, O_NONBLOCK);
        printf("Pipe set %d -> %d\n", i, j);
        fprintf(lab->pipes_log, "Pipe set %d -> %d\n", i, j);
      } else {
        printf("Error creating pipes\n");
        exit(-1);
      }
    }
  }

  fclose(lab->pipes_log);

  // create child processes
  pid_t ParentPID = getpid();
  for (int i = 0; i < lab->n_processes_count - 1; ++i) {
    if (fork() == 0) { // CHILD code execution starts here
      lab->n_process_id = i + 1;
      lab->n_process_pid = getpid();
      lab->n_parent_pid = ParentPID;
      break;
    }
  }

  // configure pipes
  close(lab->channels[lab->n_process_id][lab->n_process_id].rf);
  close(lab->channels[lab->n_process_id][lab->n_process_id].wf);

  for (int i = 0; i < lab->n_processes_count; ++i) {
    for (int j = 0; j < lab->n_processes_count; ++j) {
      if (i != lab->n_process_id && j != lab->n_process_id) {
        close(lab->channels[i][j].rf);
        close(lab->channels[i][j].wf);
      }
      if (i == lab->n_process_id && j != lab->n_process_id) {
        close(lab->channels[i][j].rf);
      }
      if (j == lab->n_process_id && i != lab->n_process_id) {
        close(lab->channels[i][j].wf);
      }
    }
  }
}

void run(Lab* lab) {
  int processes_statuses[lab->n_processes_count];
  memset(processes_statuses, -1, (lab->n_processes_count) * sizeof(int));
  int msg_len = 0;
  char msg_buf[4096];

  if (lab->n_process_id == 0) { // parent code
    // log 'started'
    msg_len = sprintf(msg_buf, log_started_fmt, lab->n_process_id, lab->n_process_pid, lab->n_parent_pid);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

    int starts_receiving = 1;
    while (starts_receiving) {
      for (int i = 1; i < lab->n_processes_count; ++i) {
        if (processes_statuses[i] == STARTED) {
          continue;
        }

        Message msg;
        if (receive(lab, i, &msg) == 0) {
          if (msg.s_header.s_type == STARTED) {
            processes_statuses[i] = STARTED;
            printf("%s", msg.s_payload);
            fwrite(msg.s_payload, 1, msg.s_header.s_payload_len, lab->main_log);
          } else {
            printf("Error occured in parent\n");
          }
        }
      }

      starts_receiving = 0;
      for (int i = 1; i < lab->n_processes_count; ++i) {
        if (processes_statuses[i] != STARTED) {
          starts_receiving = 1;
        }
      }
    }

    // log 'received all started'
    msg_len = sprintf(msg_buf, log_received_all_started_fmt, lab->n_process_id); fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

    // work goes here
    // ...
    // work ends here

    // work done msg
    msg_len = sprintf(msg_buf, log_done_fmt, lab->n_process_id); fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

    int ends_receiving = 1;
    while (ends_receiving) {
      for (int i = 1; i < lab->n_processes_count; ++i) {
        if (processes_statuses[i] == DONE) {
          continue;
        }

        Message msg;
        if (receive(lab, i, &msg) == 0) {
          if (msg.s_header.s_type == DONE) {
            processes_statuses[i] = DONE;
            printf("%s", msg.s_payload);
            fwrite(msg.s_payload, 1, msg.s_header.s_payload_len, lab->main_log);
          } else {
            printf("Error occured in parent\n");
          }
        }
      }

      ends_receiving = 0;
      for (int i = 1; i < lab->n_processes_count; ++i) {
        if (processes_statuses[i] != DONE) {
          ends_receiving = 1;
        }
      }
    }

    // all done
    msg_len = sprintf(msg_buf, log_received_all_done_fmt, lab->n_process_id);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

    int waiting_processes = lab->n_processes_count - 1;
    while (waiting_processes) {
      wait(NULL);
      --waiting_processes;
    }

    // close everything
    fclose(lab->main_log);
    for (int i = 0; i < lab->n_processes_count; ++i) {
      for (int j = 0; j < lab->n_processes_count; ++j) {
        close(lab->channels[i][j].rf);
        close(lab->channels[i][j].wf);
      }
      free(lab->channels[i]);
    }
    free(lab->channels);

    exit(0); // everything worked fine!
  } else { // child code
    // firstly - send STARTED to everyone
    Message msg;
    msg.s_header.s_type = STARTED;
    msg.s_header.s_magic = MESSAGE_MAGIC;
    msg.s_header.s_local_time = (timestamp_t) time(NULL);
    msg_len = sprintf(msg_buf, log_started_fmt, lab->n_process_id, lab->n_process_pid, lab->n_parent_pid);

    // Mark process itself as started
    processes_statuses[lab->n_process_id] = STARTED;

    // send to other processes
    msg.s_header.s_payload_len = (uint16_t) msg_len;
    memcpy(msg.s_payload, msg_buf, (size_t) msg_len);
    send_multicast(lab, &msg);

    int starts_receiving = 1;
    while (starts_receiving) {
      for (int i = 1; i < lab->n_processes_count; ++i) {
        if (processes_statuses[i] == STARTED)
          continue;

        Message received_message;
        if (receive(lab, i, &received_message) == 0) {
          if (received_message.s_header.s_type == STARTED) {
            processes_statuses[i] = STARTED;
          } else {
            printf("1: Error occured in child %d, received %d\n", lab->n_process_id, received_message.s_header.s_type);
          }
        }
      }

      starts_receiving = 0;
      for (int i = 1; i < lab->n_processes_count; ++i) {
        if (processes_statuses[i] != STARTED) {
          starts_receiving = 1;
        }
      }
    }

    // all started
    msg_len = sprintf(msg_buf, log_received_all_started_fmt, lab->n_process_id);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

    // work goes here
    // ...
    // work ends here

    // work done msg
    msg_len = sprintf(msg_buf, log_done_fmt, lab->n_process_id);

    // Mark process itself as done
    processes_statuses[lab->n_process_id] = DONE;

    // send to other processes
    msg.s_header.s_type = DONE;
    msg.s_header.s_payload_len = (uint16_t) msg_len;
    msg.s_header.s_local_time = (timestamp_t) time(NULL);
    memcpy(msg.s_payload, msg_buf, (size_t) msg_len);
    send_multicast(lab, &msg);

    int ends_receiveing = 1;
    while (ends_receiveing) {
      for (int i = 1; i < lab->n_processes_count; ++i) {
        if (processes_statuses[i] == DONE) {
          continue;
        }

        Message received_message;
        if (receive(lab, i, &received_message) == 0) {
          if (received_message.s_header.s_type == DONE) {
            processes_statuses[i] = DONE;
          } else {
            printf("2: Error occured in child %d, received %d\n", lab->n_process_id, received_message.s_header.s_type);
          }
        }
      }

      ends_receiveing = 0;
      for (int i = 1; i < lab->n_processes_count; ++i) {
        if (processes_statuses[i] != DONE) {
          ends_receiveing = 1;
        }
      }
    }

    // all done
    msg_len = sprintf(msg_buf, log_received_all_done_fmt, lab->n_process_id);
    printf("%s", msg_buf);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);

    // close everything
    fclose(lab->main_log);
    for (int i = 0; i < lab->n_processes_count; ++i) {
      for (int j = 0; j < lab->n_processes_count; ++j) {
        close(lab->channels[i][j].rf);
        close(lab->channels[i][j].wf);
      }
      free(lab->channels[i]);
    }
    free(lab->channels);
    exit(0);
  }
}

int main(int argc, const char* argv[]) {
  if (argc < 3 || strcmp(argv[1], "-p") != 0) {
    return 1;
  }

  Lab lab;
  lab.n_processes_count = atoi(argv[2]) + 1;
  lab.n_process_id = 0; // everything starts from parent

  init(&lab);
  run(&lab);
  return 0;
}
