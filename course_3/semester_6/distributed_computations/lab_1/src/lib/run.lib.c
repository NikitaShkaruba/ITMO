#include "run.lib.h"

void run(Context* context) {
  int process_statuses[context->processes_amount];
  memset(process_statuses, -1, (context->processes_amount) * sizeof(int));

  if (context->current_id == 0) { // parent code
    runParent(context, process_statuses);
  } else {
    runChild(context, process_statuses);
  }
}

void runParent(Context* context, int process_statuses[]) {
  int msg_len = 0;
  char msg_buf[4096];

  msg_len = sprintf(msg_buf, log_started_fmt, context->current_id, context->current_pid, context->parent_pid);
  fwrite(msg_buf, 1, (size_t) msg_len, context->events_log);
  printf("%s", msg_buf);

  int starts_receiving = 1;
  while (starts_receiving) {
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] == STARTED) {
        continue;
      }

      Message msg;
      if (receive(context, i, &msg) == 0) {
        if (msg.s_header.s_type == STARTED) {
          process_statuses[i] = STARTED;
          printf("%s", msg.s_payload);
          fwrite(msg.s_payload, 1, msg.s_header.s_payload_len, context->events_log);
        } else {
          printf("Error occured in parent\n");
        }
      }
    }

    starts_receiving = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] != STARTED) {
        starts_receiving = 1;
      }
    }
  }

  // log 'received all started'
  msg_len = sprintf(msg_buf, log_received_all_started_fmt, context->current_id); fwrite(msg_buf, 1, (size_t) msg_len, context->events_log);
  printf("%s", msg_buf);

  // work goes here
  // ...
  // work ends here

  // work done msg
  msg_len = sprintf(msg_buf, log_done_fmt, context->current_id); fwrite(msg_buf, 1, (size_t) msg_len, context->events_log);
  printf("%s", msg_buf);

  int ends_receiving = 1;
  while (ends_receiving) {
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] == DONE) {
        continue;
      }

      Message msg;
      if (receive(context, i, &msg) == 0) {
        if (msg.s_header.s_type == DONE) {
          process_statuses[i] = DONE;
          printf("%s", msg.s_payload);
          fwrite(msg.s_payload, 1, msg.s_header.s_payload_len, context->events_log);
        } else {
          printf("Error occured in parent\n");
        }
      }
    }

    ends_receiving = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] != DONE) {
        ends_receiving = 1;
      }
    }
  }

  // all done
  msg_len = sprintf(msg_buf, log_received_all_done_fmt, context->current_id);
  fwrite(msg_buf, 1, (size_t) msg_len, context->events_log);
  printf("%s", msg_buf);

  int waiting_processes = context->processes_amount - 1;
  while (waiting_processes) {
    wait(NULL);
    --waiting_processes;
  }

  // close everything
  fclose(context->events_log);
  for (int i = 0; i < context->processes_amount; ++i) {
    for (int j = 0; j < context->processes_amount; ++j) {
      close(context->pipes[i][j].from_id);
      close(context->pipes[i][j].to_id);
    }
    free(context->pipes[i]);
  }
  free(context->pipes);

  exit(0); // everything worked fine!
}

void runChild(Context* context, int process_statuses[]) {
  int msg_len = 0;
  char msg_buf[4096];

  // firstly - send STARTED to everyone
  Message msg;
  msg.s_header.s_type = STARTED;
  msg.s_header.s_magic = MESSAGE_MAGIC;
  msg.s_header.s_local_time = (timestamp_t) time(NULL);
  msg_len = sprintf(msg_buf, log_started_fmt, context->current_id, context->current_pid, context->parent_pid);

  // Mark process itself as started
  process_statuses[context->current_id] = STARTED;

  // send to other processes
  msg.s_header.s_payload_len = (uint16_t) msg_len;
  memcpy(msg.s_payload, msg_buf, (size_t) msg_len);
  send_multicast(context, &msg);

  int starts_receiving = 1;
  while (starts_receiving) {
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] == STARTED)
        continue;

      Message received_message;
      if (receive(context, i, &received_message) == 0) {
        if (received_message.s_header.s_type == STARTED) {
          process_statuses[i] = STARTED;
        } else {
          printf("1: Error occured in child %d, received %d\n", context->current_id, received_message.s_header.s_type);
        }
      }
    }

    starts_receiving = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] != STARTED) {
        starts_receiving = 1;
      }
    }
  }

  // all started
  msg_len = sprintf(msg_buf, log_received_all_started_fmt, context->current_id);
  fwrite(msg_buf, 1, (size_t) msg_len, context->events_log);
  printf("%s", msg_buf);

  // work goes here
  // ...
  // work ends here

  // work done msg
  msg_len = sprintf(msg_buf, log_done_fmt, context->current_id);

  // Mark process itself as done
  process_statuses[context->current_id] = DONE;

  // send to other processes
  msg.s_header.s_type = DONE;
  msg.s_header.s_payload_len = (uint16_t) msg_len;
  msg.s_header.s_local_time = (timestamp_t) time(NULL);
  memcpy(msg.s_payload, msg_buf, (size_t) msg_len);
  send_multicast(context, &msg);

  int ends_receiveing = 1;
  while (ends_receiveing) {
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] == DONE) {
        continue;
      }

      Message received_message;
      if (receive(context, i, &received_message) == 0) {
        if (received_message.s_header.s_type == DONE) {
          process_statuses[i] = DONE;
        } else {
          printf("2: Error occured in child %d, received %d\n", context->current_id, received_message.s_header.s_type);
        }
      }
    }

    ends_receiveing = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] != DONE) {
        ends_receiveing = 1;
      }
    }
  }

  // all done
  msg_len = sprintf(msg_buf, log_received_all_done_fmt, context->current_id);
  printf("%s", msg_buf);
  fwrite(msg_buf, 1, (size_t) msg_len, context->events_log);

  // close everything
  fclose(context->events_log);
  for (int i = 0; i < context->processes_amount; ++i) {
    for (int j = 0; j < context->processes_amount; ++j) {
      close(context->pipes[i][j].from_id);
      close(context->pipes[i][j].to_id);
    }
    free(context->pipes[i]);
  }
  free(context->pipes);
  exit(0);
}
