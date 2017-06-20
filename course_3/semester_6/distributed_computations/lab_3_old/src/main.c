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

timestamp_t max_timestamp(timestamp_t a, timestamp_t b) {
  return a > b ? a : b;
}

timestamp_t lamp_local_time = 0;

timestamp_t get_lamport_time() {
  return lamp_local_time;
}

void transfer(void* parent_data, local_id src, local_id dst, balance_t amount) {
  Lab* app = (Lab*) parent_data;

  // create message and send it to src
  Message msg;
  ++lamp_local_time;
  msg.s_header.s_local_time = get_lamport_time();
  msg.s_header.s_magic = MESSAGE_MAGIC;
  msg.s_header.s_type = TRANSFER;
  msg.s_header.s_payload_len = sizeof(TransferOrder);

  TransferOrder transfer;
  transfer.s_dst = dst;
  transfer.s_src = src;
  transfer.s_amount = amount;
  memcpy(msg.s_payload, &transfer, sizeof(transfer));

  send(app, src, &msg);
  if (receive(app, dst, &msg) == 0 && msg.s_header.s_type != ACK) {
    printf("%d: ERROR parent received garbage from %d\n", get_lamport_time(), dst);
  }

  lamp_local_time = max_timestamp(lamp_local_time, msg.s_header.s_local_time);
  ++lamp_local_time;
}

void init(Lab* app, int* initial_balances) {
  // open
  app->pid = getpid();
  app->parent_pid = 0; // parent has no parent

  app->main_log = fopen(events_log, "a");
  app->pipes_log = fopen(pipes_log, "w");

  // allocate pipes array
  app->channels = calloc((size_t) app->processes_amount, sizeof(Channel*));
  for (int i = 0; i < app->processes_amount; i++) {
    app->channels[i] = calloc((size_t) app->processes_amount, sizeof(Channel));
  }

  // init pipes
  for (int i = 0; i < app->processes_amount; i++) {
    for (int j = 0; j < app->processes_amount; j++) {
      if (i == j) {
        continue; // I -> I communication refused
      }

      if (pipe((int*) &app->channels[i][j]) != -1) {
        fcntl(app->channels[i][j].rf, F_SETFL, O_NONBLOCK);
        fcntl(app->channels[i][j].wf, F_SETFL, O_NONBLOCK);
        printf("Pipe set %d -> %d\n", i, j);
        fprintf(app->pipes_log, "Pipe set %d -> %d\n", i, j);
      } else {
        printf("Error creating pipes\n");
        exit(-1);
      }
    }
  }

  fclose(app->pipes_log);

  // create child processes
  pid_t ParentPID = getpid();
  app->balance = initial_balances[0];
  for (int i = 0; i < app->processes_amount - 1; i++) {
    if (fork() == 0) {
      // CHILD code execution starts here
      app->node_id = i + 1;
      app->pid = getpid();
      app->parent_pid = ParentPID;
      app->balance = initial_balances[app->node_id];
      break;
    }
  }

  // configure pipes (personally)
  close(app->channels[app->node_id][app->node_id].rf);
  close(app->channels[app->node_id][app->node_id].wf);

  for (int i = 0; i < app->processes_amount; i++) {
    for (int j = 0; j < app->processes_amount; j++) {
      if (i != app->node_id && j != app->node_id) {
        close(app->channels[i][j].rf);
        close(app->channels[i][j].wf);
      }
      if (i == app->node_id && j != app->node_id) {
        close(app->channels[i][j].rf);
      }
      if (j == app->node_id && i != app->node_id) {
        close(app->channels[i][j].wf);
      }
    }
  }
}

void run(Lab* lab) {
  int processes_statuses[lab->processes_amount];
  int msg_len = 0;
  char msg_buf[4096];

  memset(processes_statuses, -1, (lab->processes_amount) * sizeof(int));

  if (lab->node_id == 0) { // parent code
    AllHistory history;
    history.s_history_len = (uint8_t) (lab->processes_amount - 1);

    // log 'started'
    msg_len = sprintf(msg_buf, log_started_fmt, get_lamport_time(), lab->node_id, lab->pid, lab->parent_pid, lab->balance);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

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

            lamp_local_time = max_timestamp(lamp_local_time, message.s_header.s_local_time);
            ++lamp_local_time;
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
    msg_len = sprintf(msg_buf, log_received_all_started_fmt, get_lamport_time(), lab->node_id);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

    // work goes here
    bank_robbery(lab, lab->processes_amount - 1);
    Message stop_msg;
    stop_msg.s_header.s_type = STOP;
    stop_msg.s_header.s_magic = MESSAGE_MAGIC;
    stop_msg.s_header.s_payload_len = 0;
    ++lamp_local_time;
    stop_msg.s_header.s_local_time = get_lamport_time();

    send_multicast(lab, &stop_msg);
    // work ends here

    // log work done
    msg_len = sprintf(msg_buf, log_done_fmt, get_lamport_time(), lab->node_id, lab->balance);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

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

            lamp_local_time = max_timestamp(lamp_local_time, message.s_header.s_local_time);
            ++lamp_local_time;
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
    msg_len = sprintf(msg_buf, log_received_all_done_fmt, get_lamport_time(), lab->node_id);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

    printf("Parent starts to receive histories\n");
    int histories_remaining = lab->processes_amount - 1;
    while (histories_remaining) {
      Message history_message;
      if (receive_any(lab, &history_message) == 0 && history_message.s_header.s_type == BALANCE_HISTORY) {
        BalanceHistory* balance_history = (BalanceHistory*) history_message.s_payload;
        memcpy(&history.s_history[balance_history->s_id - 1], history_message.s_payload, history_message.s_header.s_payload_len);
        histories_remaining--;

        lamp_local_time = max_timestamp(lamp_local_time, history_message.s_header.s_local_time);
        ++lamp_local_time;
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
  } else { // child code
    // initialize balance history
    BalanceHistory history;
    history.s_id = lab->node_id;

    history.s_history[0].s_balance_pending_in = 0;
    history.s_history[0].s_balance = lab->balance;
    history.s_history[0].s_time = get_lamport_time();

    // Send STARTED to everyone
    Message message;
    message.s_header.s_type = STARTED;
    message.s_header.s_magic = MESSAGE_MAGIC;
    ++lamp_local_time;
    message.s_header.s_local_time = get_lamport_time();
    msg_len = sprintf(msg_buf, log_started_fmt, get_lamport_time(), lab->node_id, lab->pid, lab->parent_pid, lab->balance);

    // Mark process itself as started
    processes_statuses[lab->node_id] = STARTED;

    // send to other processes
    message.s_header.s_payload_len = (uint16_t) msg_len;
    memcpy(message.s_payload, msg_buf, (size_t) msg_len);
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

            lamp_local_time = max_timestamp(lamp_local_time, received_message.s_header.s_local_time);
            ++lamp_local_time;
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

    // all started
    msg_len = sprintf(msg_buf, log_received_all_started_fmt, get_lamport_time(), lab->node_id);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
    printf("%s", msg_buf);

    // initialize balance history

    // work goes here
    Message received_message;
    while (1) {
      if (receive_any(lab, &received_message) == 0) {
        lamp_local_time = max_timestamp(lamp_local_time, received_message.s_header.s_local_time);
        ++lamp_local_time;

        if (received_message.s_header.s_type == TRANSFER) {
          TransferOrder* order = (TransferOrder*) received_message.s_payload;

          if (order->s_src == lab->node_id) {
            lab->balance -= order->s_amount;

            timestamp_t cur_time = get_lamport_time();
            history.s_history[cur_time].s_time = get_lamport_time();
            history.s_history[cur_time].s_balance = lab->balance;
            history.s_history[cur_time].s_balance_pending_in = order->s_amount;

            // next step receiver will acquire money, in afterstep pending will be nulled
            history.s_history[cur_time + 2].s_time = get_lamport_time() + 2;
            history.s_history[cur_time + 2].s_balance = lab->balance;
            history.s_history[cur_time + 2].s_balance_pending_in = 0;

            msg_len = sprintf(msg_buf, log_transfer_out_fmt, get_lamport_time(), lab->node_id, order->s_amount, order->s_dst);
            fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
            printf("%s", msg_buf);

            ++lamp_local_time;
            received_message.s_header.s_local_time = get_lamport_time();
            send(lab, order->s_dst, &received_message);
          } else if (order->s_dst == lab->node_id) {
            lab->balance += order->s_amount;

            timestamp_t cur_time = get_lamport_time();
            history.s_history[cur_time].s_time = get_lamport_time();
            history.s_history[cur_time].s_balance = lab->balance;
            history.s_history[cur_time].s_balance_pending_in = 0;

            msg_len = sprintf(msg_buf, log_transfer_in_fmt, get_lamport_time(), lab->node_id, order->s_amount, order->s_src);
            fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);
            printf("%s", msg_buf);

            Message conf_msg;
            conf_msg.s_header.s_type = ACK;
            ++lamp_local_time;
            conf_msg.s_header.s_local_time = get_lamport_time();
            conf_msg.s_header.s_magic = MESSAGE_MAGIC;
            conf_msg.s_header.s_payload_len = 0;

            send(lab, 0, &conf_msg);
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

    // log work done
    msg_len = sprintf(msg_buf, log_done_fmt, get_lamport_time(), lab->node_id, lab->balance);

    // Mark process itself as done
    processes_statuses[lab->node_id] = DONE;

    // send to other processes
    message.s_header.s_type = DONE;
    message.s_header.s_payload_len = (uint16_t) msg_len;
    ++lamp_local_time;
    message.s_header.s_local_time = get_lamport_time();
    memcpy(message.s_payload, msg_buf, (size_t) msg_len);
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

            lamp_local_time = max_timestamp(lamp_local_time, received_message.s_header.s_local_time);
            ++lamp_local_time;
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
    msg_len = sprintf(msg_buf, log_received_all_done_fmt, get_lamport_time(), lab->node_id);
    printf("%s", msg_buf);
    fwrite(msg_buf, 1, (size_t) msg_len, lab->main_log);

    // prepare history & send it
    timestamp_t cur_time = get_lamport_time();
    timestamp_t last_history_row = cur_time;
    history.s_history[cur_time].s_time = get_lamport_time();
    history.s_history[cur_time].s_balance = lab->balance;
    history.s_history[cur_time].s_balance_pending_in = 0;
    history.s_history_len = (uint8_t) (last_history_row + 1);

    balance_t cur_bal = history.s_history[0].s_balance;
    balance_t cur_bal_pend = history.s_history[0].s_balance_pending_in;
    cur_time = history.s_history[0].s_time;
    for (int i = 1; i < history.s_history_len; i++) {
      ++cur_time;
      if (history.s_history[i].s_balance == 0 &&
          history.s_history[i].s_time == 0) {
        history.s_history[i].s_balance = cur_bal;
        history.s_history[i].s_balance_pending_in = cur_bal_pend;
        history.s_history[i].s_time = cur_time;
      } else {
        cur_bal = history.s_history[i].s_balance;
        cur_bal_pend = history.s_history[i].s_balance_pending_in;
        cur_time = history.s_history[i].s_time;
      }
    }

    // send it
    Message history_msg;
    history_msg.s_header.s_type = BALANCE_HISTORY;
    history_msg.s_header.s_magic = MESSAGE_MAGIC;
    ++lamp_local_time;
    history_msg.s_header.s_local_time = get_lamport_time();
    history_msg.s_header.s_payload_len = sizeof(history.s_id) + sizeof(history.s_history_len) + history.s_history_len * sizeof(BalanceState);

    memcpy(history_msg.s_payload, &history, history_msg.s_header.s_payload_len);
    send(lab, 0, &history_msg);

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
  if (argc < 3 || strcmp(argv[1], "-p") != 0)
    return 1;

  Lab app;
  app.node_id = 0; // everything starts from parent

  app.processes_amount = atoi(argv[2]) + 1;
  if (app.processes_amount != argc - 2) {
    return 1;
  }

  int initial_balances[app.processes_amount];
  initial_balances[0] = 0;
  for (int i = 1; i < app.processes_amount; i++) {
    initial_balances[i] = atoi(argv[i + 2]);
  }

  init(&app, initial_balances);
  run(&app);
  return 0;
}
