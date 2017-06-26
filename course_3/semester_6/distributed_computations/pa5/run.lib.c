#include "include.h"

void run(Context* context) {
  context->process_statuses = (char*)malloc((size_t) context->processes_amount);
  memset(context->process_statuses, -1, context->processes_amount * sizeof(char));
  context->process_locks = (char*)malloc((size_t) context->processes_amount);
  memset(context->process_locks, 0, context->processes_amount * sizeof(char));

  if (context->current_id == 0) {
    run_root(context);
  } else {
    run_child(context);
  }
}
void run_root(Context* context) {
  start_root(context);
  root_do_work(context);
  finish_root(context);

  close_pipes(context);
  exit(0);
}
void run_child(Context *context) {
  start_child(context);
  child_do_work(context);
  finish_child(context);

  close_pipes(context);
  exit(0);
}

void wait_until_everyone_starts(Context *context) {
  int is_listening = 1;
  while (is_listening) {
    int sender_id = 0;
    Message started_message;

    if ((sender_id = receive_any(context, &started_message)) >= 0) {
      if (started_message.s_header.s_type == STARTED) {
        context->process_statuses[sender_id] = STARTED;
        //printf("%s", started_message.s_payload);
        fwrite(started_message.s_payload, 1, started_message.s_header.s_payload_len, context->events_log);
      }
    } else {
      for (int i = 0; i < 1000000; ++i) {}
    }

    is_listening = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (context->process_statuses[i] != STARTED) {
        is_listening = 1;
      }
    }
  }

  log_all_started(context);
}
void wait_until_everyone_finishes(Context *context) {
  int is_listening = 1;
  while (is_listening) {
    int sender_id = 0;
    Message finished_message;

    if ((sender_id = receive_any(context, &finished_message)) >= 0) {
      if (finished_message.s_header.s_type == DONE) {
        context->process_statuses[sender_id] = DONE;
        printf("%s", finished_message.s_payload);
        fwrite(finished_message.s_payload, 1, finished_message.s_header.s_payload_len, context->events_log);
      }
    } else {
      for (int i = 0; i < 1000000; ++i) {}
    }

    is_listening = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (context->process_statuses[i] != DONE) {
        is_listening = 1;
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
    printf("Root waits for children, %d left\n", waiting_processes);
  }
}

void root_do_work(Context* context) {
  // Root only searches for setup and shutdown in this lab
}
void child_do_work(Context *context) {
  sleep(1);
  int iter_num = 1;
  int iter_count = context->current_id * 5;
  while (iter_num <= iter_count) {
    if (context->is_mutex_mode) {
      request_cs(context);
    }

    printf("DONE FFS");
    char message_buffer[4096];
    sprintf(message_buffer, log_loop_operation_fmt, context->current_id, iter_num, iter_count);

    // Uncomment for debugging
    printf("%s", message_buffer);
    // puts(message_buffer);
    // print(message_buffer);

    if (context->is_mutex_mode) {
      release_cs(context);
    }

    ++iter_num;
  }
}

void send_started_to_everyone(Context* context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_started_fmt, get_lamport_time(), context->current_id, context->current_pid, context->parent_pid, context->balance);

  inc_lamport_time();

  Message message;
  message.s_header.s_type = STARTED;
  message.s_header.s_magic = MESSAGE_MAGIC;
  message.s_header.s_local_time = (timestamp_t) get_lamport_time();
  message.s_header.s_payload_len = (uint16_t) message_size;
  memcpy(message.s_payload, message_buffer, (size_t) message_size);

  send_multicast(context, &message);
}
void send_finished_to_everyone(Context* context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_done_fmt, get_lamport_time(), context->current_id, context->balance);

  inc_lamport_time();

  Message message;
  message.s_header.s_type = DONE;
  message.s_header.s_magic = MESSAGE_MAGIC;
  message.s_header.s_payload_len = (uint16_t) message_size;
  message.s_header.s_local_time = (timestamp_t) get_lamport_time();
  memcpy(message.s_payload, message_buffer, (size_t) message_size);

  send_multicast(context, &message);
}

void start_child(Context *context) {
  context->process_statuses[context->current_id] = STARTED;

  send_started_to_everyone(context);
  wait_until_everyone_starts(context);
}
void finish_child(Context *context) {
  context->process_statuses[context->current_id] = DONE;

  send_finished_to_everyone(context);
  wait_until_everyone_finishes(context);
}
void start_root(Context *context) {
  log_root_started(context);
  wait_until_everyone_starts(context);
}
void finish_root(Context *context) {
  log_root_finished(context);

  wait_until_everyone_finishes(context);
  wait_for_children(context);
}

void log_root_started(Context *context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_started_fmt, get_lamport_time(), context->current_id, context->current_pid, context->parent_pid, context->balance);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  // printf("%s", message_buffer);
}
void log_root_finished(Context *context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_done_fmt, get_lamport_time(), context->current_id, context->balance);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  printf("%s", message_buffer);
}
void log_all_started(Context *context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_received_all_started_fmt, get_lamport_time(), context->current_id);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  printf("%s", message_buffer);
}
void log_all_finished(Context* context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_received_all_done_fmt, get_lamport_time(), context->current_id);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  printf("%s", message_buffer);
}

