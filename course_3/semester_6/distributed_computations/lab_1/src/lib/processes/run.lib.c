#include "../headers/run.lib.h"

void run(Context* context) {
  int process_statuses[context->processes_amount];
  memset(process_statuses, -1, (context->processes_amount) * sizeof(int));

  if (context->current_id == 0) {
    run_parent(context, process_statuses);
  } else {
    run_child(context, process_statuses);
  }
}
void run_parent(Context *context, int *process_statuses) {
  start_parent(context, process_statuses);
  do_work(context);
  finish_parent(context, process_statuses);

  close_pipes(context);
  exit(0);
}
void run_child(Context *context, int *process_statuses) {
  start_child(context, process_statuses);
  do_work(context);
  finish_child(context, process_statuses);

  close_pipes(context);
  exit(0);
}

void wait_until_everyone_starts(Context *context, int *process_statuses) {
  int isListening = 1;
  while (isListening) {
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] == STARTED) {
        continue;
      }

      Message message;
      if (receive(context, (local_id) i, &message) == 0) {
        if (message.s_header.s_type == STARTED) {
          process_statuses[i] = STARTED;
          if (context->current_id == 0) {
            log_message(context, message);
          }
        } else {
          printf("Error occured in wait_until_everyone_starts\n");
        }
      }
    }

    isListening = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] != STARTED) {
        isListening = 1;
      }
    }
  }

  log_all_started(context);
}
void wait_until_everyone_finishes(Context *context, int* process_statuses) {
  int isListening = 1;
  while (isListening) {
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] == DONE) {
        continue;
      }

      Message msg;
      if (receive(context, i, &msg) == 0) {
        if (msg.s_header.s_type == DONE) {
          process_statuses[i] = DONE;
          if (context->current_id == 0) {
            printf("%s", msg.s_payload);
          }
          fwrite(msg.s_payload, 1, msg.s_header.s_payload_len, context->events_log);
        } else {
          printf("Error occured in wait_until_everyone_finishes\n");
        }
      }
    }

    isListening = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (process_statuses[i] != DONE) {
        isListening = 1;
      }
    }
  }

  log_all_finished(context);
}
void wait_for_children(Context* context) {
  int waiting_processes = context->processes_amount - 1;

  while (waiting_processes) {
    wait(NULL);
    --waiting_processes;
  }
}

void do_work(Context* context) {

}

void send_started_to_everyone(Context* context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_started_fmt, context->current_id, context->current_pid, context->parent_pid);

  Message message;
  message.s_header.s_type = STARTED;
  message.s_header.s_magic = MESSAGE_MAGIC;
  message.s_header.s_local_time = (timestamp_t) time(NULL);
  message.s_header.s_payload_len = (uint16_t) message_size;

  memcpy(message.s_payload, message_buffer, (size_t) message_size);
  send_multicast(context, &message);
}
void send_finished_to_everyone(Context* context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_done_fmt, context->current_id);

  Message message;
  message.s_header.s_type = DONE;
  message.s_header.s_magic = MESSAGE_MAGIC;
  message.s_header.s_payload_len = (uint16_t) message_size;
  message.s_header.s_local_time = (timestamp_t) time(NULL);
  memcpy(message.s_payload, message_buffer, (size_t) message_size);
  send_multicast(context, &message);
}

void start_child(Context *context, int *process_statuses) {
  process_statuses[context->current_id] = STARTED;

  send_started_to_everyone(context);
  wait_until_everyone_starts(context, process_statuses);
}
void finish_child(Context *context, int *process_statuses) {
  process_statuses[context->current_id] = DONE;

  send_finished_to_everyone(context);
  wait_until_everyone_finishes(context, process_statuses);
}
void start_parent(Context *context, int *process_statuses) {
  log_parent_started(context);
  wait_until_everyone_starts(context, process_statuses);
}
void finish_parent(Context *context, int *process_statuses) {
  log_parent_finished(context);

  wait_until_everyone_finishes(context, process_statuses);
  wait_for_children(context);
}

void log_parent_started(Context *context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_started_fmt, context->current_id, context->current_pid, context->parent_pid);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  printf("%s", message_buffer);
}
void log_parent_finished(Context *context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_done_fmt, context->current_id); fwrite(message_buffer, 1, (size_t) message_size, context->events_log);

  printf("%s", message_buffer);
}
void log_all_started(Context *context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_received_all_started_fmt, context->current_id);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  printf("%s", message_buffer);
}
void log_all_finished(Context* context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_received_all_done_fmt, context->current_id);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  printf("%s", message_buffer);
}
void log_message(Context* context, Message message) {
  printf("%s", message.s_payload);
  fwrite(message.s_payload, 1, message.s_header.s_payload_len, context->events_log);
}
