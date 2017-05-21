#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "lib/vendor/ipc.h"
#include "lib/vendor/common.h"
#include "lib/vendor/pa2345.h"
#include "lib/structs.h"

void transfer(void* parent_data, local_id src, local_id dst, balance_t amount) {
  Lab* lab = (Lab*) parent_data;

  // create message and send it to src
  Message message;
  message.s_header.s_local_time = get_physical_time();
  message.s_header.s_magic = MESSAGE_MAGIC;
  message.s_header.s_type = TRANSFER;
  message.s_header.s_payload_len = sizeof(TransferOrder);

  TransferOrder transfer;
  transfer.s_dst = dst;
  transfer.s_src = src;
  transfer.s_amount = amount;
  memcpy(message.s_payload, &transfer, sizeof(transfer));

  send(lab, src, &message);
  if (receive(lab, dst, &message) == 0 && message.s_header.s_type != ACK) {
    printf("%d: ERROR parent received garbage from %d\n", get_physical_time(), dst);
  }
}

void init(Lab* lab, int* initial_balances) {
  // open
  lab->pid = getpid();
  lab->parent_pid = 0; // parent has no parent

  lab->main_log = fopen(events_log, "a");
  lab->pipes_log = fopen(pipes_log, "w");

  // allocate pipes array
  lab->channels = calloc((size_t) lab->processes_amount, sizeof(Channel*));
  for (int i = 0; i < lab->processes_amount; i++) {
    lab->channels[i] = calloc((size_t) lab->processes_amount, sizeof(Channel));
  }

  // init pipes
  for (int i = 0; i < lab->processes_amount; i++) {
    for (int j = 0; j < lab->processes_amount; j++) {
      if (i == j) {
        continue; // I -> I communication refused
      }

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
  lab->balance = initial_balances[0];
  for (int i = 0; i < lab->processes_amount - 1; i++) {
    if (fork() == 0) {
      // CHILD code execution starts here
      lab->node_id = i + 1;
      lab->pid = getpid();
      lab->parent_pid = ParentPID;
      lab->balance = initial_balances[lab->node_id];
      break;
    }
  }

  // configure pipes (personally)
  close(lab->channels[lab->node_id][lab->node_id].rf);
  close(lab->channels[lab->node_id][lab->node_id].wf);

  for (int i = 0; i < lab->processes_amount; i++) {
    for (int j = 0; j < lab->processes_amount; j++) {
      if (i != lab->node_id && j != lab->node_id) {
        close(lab->channels[i][j].rf);
        close(lab->channels[i][j].wf);
      }
      if (i == lab->node_id && j != lab->node_id) {
        close(lab->channels[i][j].rf);
      }
      if (j == lab->node_id && i != lab->node_id) {
        close(lab->channels[i][j].wf);
      }
    }
  }
}

void run(Lab* lab) {
  int message_length = 0;
  char message_buffer[4096];
  int processes_statuses[lab->processes_amount];

  memset(processes_statuses, -1, (lab->processes_amount) * sizeof(int));

  if (lab->node_id == 0) { // Parent code goes here
    AllHistory history;
    history.s_history_len = (uint8_t) (lab->processes_amount - 1);

    // log 'started'
    message_length = sprintf(message_buffer, log_started_fmt, get_physical_time(), lab->node_id, lab->pid, lab->parent_pid, lab->balance);
    fwrite(message_buffer, 1, (size_t) message_length, lab->main_log);
    printf("%s", message_buffer);

    int starts_receiving = 1;
    while (starts_receiving) {
      for (int i = 1; i < lab->processes_amount; i++) {
        if (processes_statuses[i] == STARTED) {
          continue;
        }

        Message message;
        if (receive(lab, i, &message) == 0) {
          if (message.s_header.s_type == STARTED) {
            processes_statuses[i] = STARTED;
            printf("%s", message.s_payload);
            fwrite(message.s_payload, 1, message.s_header.s_payload_len, lab->main_log);
          } else {
            printf("Error occured in parent\n");
          }
        }
      }

      starts_receiving = 0;
      for (int i = 1; i < lab->processes_amount; i++) {
        if (processes_statuses[i] != STARTED) {
          starts_receiving = 1;
        }
      }
    }

    // log 'received all started'
    message_length = sprintf(message_buffer, log_received_all_started_fmt, get_physical_time(), lab->node_id); fwrite(message_buffer, 1, (size_t) message_length, lab->main_log);
    printf("%s", message_buffer);

    // work goes here
    bank_robbery(lab, lab->processes_amount - 1);
    Message stop_message;
    stop_message.s_header.s_type = STOP;
    stop_message.s_header.s_magic = MESSAGE_MAGIC;
    stop_message.s_header.s_payload_len = 0;
    stop_message.s_header.s_local_time = get_physical_time();

    send_multicast(lab, &stop_message);
    // work ends here

    // work done message
    message_length = sprintf(message_buffer, log_done_fmt, get_physical_time(), lab->node_id, lab->balance);
    fwrite(message_buffer, 1, (size_t) message_length, lab->main_log);
    printf("%s", message_buffer);

    int ends_receiving = 1;
    while (ends_receiving) {
      for (int i = 1; i < lab->processes_amount; i++) {
        if (processes_statuses[i] == DONE) {
          continue;
        }

        Message message;
        if (receive(lab, i, &message) == 0) {
          if (message.s_header.s_type == DONE) {
            processes_statuses[i] = DONE;
            printf("%s", message.s_payload);
            fwrite(message.s_payload, 1, message.s_header.s_payload_len, lab->main_log);
          } else {
            printf("Error occured in parent\n");
          }
        }
      }

      ends_receiving = 0;
      for (int i = 1; i < lab->processes_amount; i++) {
        if (processes_statuses[i] != DONE) {
          ends_receiving = 1;
        }
      }
    }

    // log all done
    message_length = sprintf(message_buffer, log_received_all_done_fmt, get_physical_time(), lab->node_id);
    fwrite(message_buffer, 1, (size_t) message_length, lab->main_log);
    printf("%s", message_buffer);

    printf("Parent starts to receive histories\n");
    int histories_remaining = lab->processes_amount - 1;
    while (histories_remaining) {
      Message history_msg;
      if (receive_any(lab, &history_msg) == 0 && history_msg.s_header.s_type == BALANCE_HISTORY) {
        BalanceHistory* pBH = (BalanceHistory*) history_msg.s_payload;
        memcpy(&history.s_history[pBH->s_id - 1], history_msg.s_payload, history_msg.s_header.s_payload_len);
        histories_remaining--;
      } else {
        print("parent received garbage in historyloop\n");
      }
    }

    printf("Parent received all histories\n");
    print_history(&history);

    int waiting_processes = lab->processes_amount - 1;
    while (waiting_processes) {
      wait(NULL);
      --waiting_processes;
    }

    // close everything
    fclose(lab->main_log);
    for (int i = 0; i < lab->processes_amount; i++) {
      for (int j = 0; j < lab->processes_amount; j++) {
        close(lab->channels[i][j].rf);
        close(lab->channels[i][j].wf);
      }
      free(lab->channels[i]);
    }
    free(lab->channels);

    exit(0);
  } else {    // Child code goes here
    // initialize balance history
    BalanceHistory history;
    history.s_id = lab->node_id;

    // timestamp_t last_history_row = get_physical_time();
    history.s_history[0].s_balance_pending_in = 0;
    history.s_history[0].s_balance = lab->balance;
    history.s_history[0].s_time = get_physical_time();

    // firstly - send STARTED to everyone
    Message message;
    message.s_header.s_type = STARTED;
    message.s_header.s_magic = MESSAGE_MAGIC;
    message.s_header.s_local_time = get_physical_time();
    message_length = sprintf(message_buffer, log_started_fmt, get_physical_time(), lab->node_id, lab->pid, lab->parent_pid, lab->balance);

    // Mark process itself as started
    processes_statuses[lab->node_id] = STARTED;

    // send to other processes
    message.s_header.s_payload_len = (uint16_t) message_length;
    memcpy(message.s_payload, message_buffer, (size_t) message_length);
    send_multicast(lab, &message);

    int starts_receiving = 1;
    while (starts_receiving) {
      for (int i = 1; i < lab->processes_amount; i++) {
        if (processes_statuses[i] == STARTED) {
          continue;
        }

        Message received_message;
        if (receive(lab, i, &received_message) == 0) {
          if (received_message.s_header.s_type == STARTED) {
            processes_statuses[i] = STARTED;
          } else {
            printf("1: Error occured in child %d, received %d\n", lab->node_id, received_message.s_header.s_type);
          }
        }
      }

      starts_receiving = 0;
      for (int i = 1; i < lab->processes_amount; i++) {
        if (processes_statuses[i] != STARTED) {
          starts_receiving = 1;
        }
      }
    }

    // log all started
    message_length = sprintf(message_buffer, log_received_all_started_fmt, get_physical_time(), lab->node_id);
    fwrite(message_buffer, 1, (size_t) message_length, lab->main_log);
    printf("%s", message_buffer);

    // initialize balance history

    // work goes here
    Message received_message;
    while (1) {
      if (receive_any(lab, &received_message) == 0) {
        if (received_message.s_header.s_type == TRANSFER) {
          TransferOrder* order = (TransferOrder*) received_message.s_payload;

          if (order->s_src == lab->node_id) {
            lab->balance -= order->s_amount;

            timestamp_t cur_time = get_physical_time();
            history.s_history[cur_time].s_time = cur_time;
            history.s_history[cur_time].s_balance = lab->balance;
            history.s_history[cur_time].s_balance_pending_in = 0;

            message_length = sprintf(message_buffer, log_transfer_out_fmt, cur_time, lab->node_id, order->s_amount, order->s_dst);
            fwrite(message_buffer, 1, (size_t) message_length, lab->main_log);
            printf("%s", message_buffer);

            send(lab, order->s_dst, &received_message);
          } else if (order->s_dst == lab->node_id) {
            lab->balance += order->s_amount;

            timestamp_t cur_time = get_physical_time();
            history.s_history[cur_time].s_time = cur_time;
            history.s_history[cur_time].s_balance = lab->balance;
            history.s_history[cur_time].s_balance_pending_in = 0;

            message_length = sprintf(message_buffer, log_transfer_in_fmt, cur_time, lab->node_id, order->s_amount, order->s_src);
            fwrite(message_buffer, 1, (size_t) message_length, lab->main_log);
            printf("%s", message_buffer);

            Message conf_message;
            conf_message.s_header.s_type = ACK;
            conf_message.s_header.s_local_time = cur_time;
            conf_message.s_header.s_magic = MESSAGE_MAGIC;
            conf_message.s_header.s_payload_len = 0;

            send(lab, 0, &conf_message);
          } else {
            printf("VERY BAD ERROR\n");
          }
        } else if (received_message.s_header.s_type == STOP) {
          break;
        } else {
          printf("VERY BAD ERROR!\n");
        }
      }
    }
    // work ends here

    // work done message
    message_length = sprintf(message_buffer, log_done_fmt, get_physical_time(), lab->node_id, lab->balance);

    // Mark process itself as done
    processes_statuses[lab->node_id] = DONE;

    // send to other processes
    message.s_header.s_type = DONE;
    message.s_header.s_payload_len = (uint16_t) message_length;
    message.s_header.s_local_time = get_physical_time();
    memcpy(message.s_payload, message_buffer, (size_t) message_length);
    send_multicast(lab, &message);

    int ends_receiving = 1;
    while (ends_receiving) {
      for (int i = 1; i < lab->processes_amount; i++) {
        if (processes_statuses[i] == DONE) {
          continue;
        }

        if (receive(lab, i, &received_message) == 0) {
          if (received_message.s_header.s_type == DONE) {
            processes_statuses[i] = DONE;
          } else {
            printf("2: Error occured in child %d, received %d\n", lab->node_id, received_message.s_header.s_type);
          }
        }
      }

      ends_receiving = 0;
      for (int i = 1; i < lab->processes_amount; i++) {
        if (processes_statuses[i] != DONE) {
          ends_receiving = 1;
        }
      }
    }

    // log all done
    message_length = sprintf(message_buffer, log_received_all_done_fmt, get_physical_time(), lab->node_id);
    printf("%s", message_buffer);
    fwrite(message_buffer, 1, (size_t) message_length, lab->main_log);

    // prepare history & send it
    timestamp_t cur_time = get_physical_time();
    timestamp_t last_history_row = cur_time;
    history.s_history[cur_time].s_time = cur_time;
    history.s_history[cur_time].s_balance = lab->balance;
    history.s_history[cur_time].s_balance_pending_in = 0;

    history.s_history_len = (uint8_t) (last_history_row + 1);
    balance_t cur_bal = history.s_history[0].s_balance;
    cur_time = history.s_history[0].s_time;
    for (int i = 1; i < history.s_history_len; i++) {
      cur_time++;
      if (history.s_history[i].s_balance == 0 && history.s_history[i].s_time == 0) {
        history.s_history[i].s_balance = cur_bal;
        history.s_history[i].s_time = cur_time;
      } else {
        cur_bal = history.s_history[i].s_balance;
        cur_time = history.s_history[i].s_time;
      }
    }

    Message history_message;
    history_message.s_header.s_type = BALANCE_HISTORY;
    history_message.s_header.s_magic = MESSAGE_MAGIC;
    history_message.s_header.s_local_time = get_physical_time();
    history_message.s_header.s_payload_len = sizeof(history.s_id) + sizeof(history.s_history_len) + history.s_history_len * sizeof(BalanceState);

    memcpy(history_message.s_payload, &history, history_message.s_header.s_payload_len);
    send(lab, 0, &history_message);

    // close everything
    fclose(lab->main_log);
    for (int i = 0; i < lab->processes_amount; i++) {
      for (int j = 0; j < lab->processes_amount; j++) {
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
  lab.node_id = 0; // everything starts from parent

  lab.processes_amount = atoi(argv[2]) + 1;
  if (argc != lab.processes_amount + 2) {
    return 1;
  }

  int initial_balances[lab.processes_amount];
  initial_balances[0] = 0;
  for (int i = 1; i < lab.processes_amount; i++) {
    initial_balances[i] = atoi(argv[i + 2]);
  }

  init(&lab, initial_balances);
  run(&lab);
  return 0;
}
