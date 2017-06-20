#include "headers/run.lib.h"
#include "headers/include.h"

typedef struct {
  int balance;
  int pending;
} Pair;

void print_history(const AllHistory * history) {
  if (history == NULL) {
    fprintf(stderr, "print_history: history is NULL!\n");
    exit(1);
  }

  int max_time = 0;
  int has_pending = 0;
  int nrows = history->s_history_len + 2; // 0 row (parent) is not used + Total row
  Pair table[nrows][MAX_T];
  memset(table, 0, sizeof(table));

  for (int i = 0; i < history->s_history_len; ++i) {
    for (int j = 0; j < history->s_history[i].s_history_len; ++j) {
      const BalanceState * change = &history->s_history[i].s_history[j];
      int id = history->s_history[i].s_id;
      table[id][change->s_time].balance = change->s_balance;
      table[id][change->s_time].pending = change->s_balance_pending_in;
      if (max_time < change->s_time) {
        max_time = change->s_time;
      }
      if (change->s_balance_pending_in > 0) {
        has_pending = 1;
      }
    }
  }

  if (max_time > MAX_T) {
    fprintf(stderr, "print_history: max value of s_time: %d, expected s_time < %d!\n",
            max_time, MAX_T);
    return;
  }

  // Calculate total sum
  for (int j = 0; j <= max_time; ++j) {
    int sum = 0;
    for (int i = 1; i <= history->s_history_len; ++i) {
      sum += table[i][j].balance + table[i][j].pending;
    }
    table[nrows-1][j].balance = sum;
    table[nrows-1][j].pending = 0;
  }

  // pretty print
  fflush(stderr);
  fflush(stdout);

  const char * cell_format_pending = " %d (%d) ";
  const char * cell_format = " %d ";

  char buf[128];
  int max_cell_width = 0;
  for (int i = 1; i <= history->s_history_len; ++i) {
    for (int j = 0; j <= max_time; ++j) {
      if (has_pending) {
        sprintf(buf, cell_format_pending, table[i][j].balance, table[i][j].pending);
      } else {
        sprintf(buf, cell_format, table[i][j].balance);
      }
      int width = strlen(buf);
      if (max_cell_width < width) {
        max_cell_width = width;
      }
    }
  }

  const char * const first_column_header = "Proc \\ time |";
  const int first_column_width = strlen(first_column_header);
  const int underscrores = (first_column_width + 1) + (max_cell_width + 1) * (max_time + 1);

  char hline[underscrores + 2];
  for (int i = 0; i < underscrores; ++i) {
    hline[i] = '-';
  }
  hline[underscrores] = '\n';
  hline[underscrores + 1] = '\0';

  if (has_pending) {
    printf("\nFull balance history for time range [0;%d], $balance ($pending):\n", max_time);
  } else {
    printf("\nFull balance history for time range [0;%d], $balance:\n", max_time);
  }
  printf("%s", hline);

  printf("%s ", first_column_header);
  for (int j = 0; j <= max_time; ++j) {
    printf("%*d |", max_cell_width - 1, j);
  }
  printf("\n");
  printf("%s", hline);

  for (int i = 1; i <= history->s_history_len; ++i) {
    printf("%11d | ", i);
    for (int j = 0; j <= max_time; ++j) {
      if (has_pending) {
        sprintf(buf, cell_format_pending, table[i][j].balance, table[i][j].pending);
      } else {
        sprintf(buf, cell_format, table[i][j].balance);
      }
      printf("%*s|", max_cell_width, buf);
    }
    printf("\n");
    printf("%s", hline);
  }

  printf("      Total | ");
  for (int j = 0; j <= max_time; ++j) {
    printf("%*d |", max_cell_width - 1, table[nrows-1][j].balance);
  }
  printf("\n");
  printf("%s", hline);
}
void print(const char * s) {
  printf("%s", s);
}

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
  start_root(context, process_statuses);
  root_do_work(context);
  finish_root(context, process_statuses);

  close_pipes(context);
  exit(0);
}
void run_child(Context *context, int *process_statuses) {
  start_child(context, process_statuses);
  child_do_work(context);
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
          set_max_lamport_time(get_lamport_time(), message.s_header.s_local_time);
          inc_lamport_time();
        } else {
          printf("Error occured in wait until everyone starts\n");
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

      Message message;
      if (receive(context, (local_id) i, &message) == 0) {
        if (message.s_header.s_type == DONE) {
          process_statuses[i] = DONE;

          if (context->current_id == 0) {
            log_message(context, message);
          }

          set_max_lamport_time(get_lamport_time(), message.s_header.s_local_time);
          inc_lamport_time();
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
    printf("Root waits for children, %d left\n", waiting_processes);
  }
}

void root_do_work(Context* context) {
  // Rot have no work here
}
void child_do_work(Context *context) {
  char message_buffer[4096];

  int iter_num = 1;
  int iter_count = context->current_id * 5;
  while (iter_num <= iter_count) {
    if (context->is_mutex_mode) {
      request_cs(context);
    }

    sprintf(message_buffer, log_loop_operation_fmt, context->current_id, iter_num, iter_count);
    print(message_buffer);

    if (context->is_mutex_mode) {
      release_cs(context);
    }

    ++iter_num;
  }
}
void child_send_transfer(Context* context, TransferOrder* transfer_order, Message received_message) {
  timestamp_t cur_time = get_lamport_time();

  context->balance -= transfer_order->s_amount;

  // Set current
  context->balance_history.s_history[cur_time].s_time = get_lamport_time();
  context->balance_history.s_history[cur_time].s_balance = context->balance;
  context->balance_history.s_history[cur_time].s_balance_pending_in = transfer_order->s_amount;

  // Null pending
  context->balance_history.s_history[cur_time + 2].s_time = (timestamp_t) (get_lamport_time() + 2);
  context->balance_history.s_history[cur_time + 2].s_balance = context->balance;
  context->balance_history.s_history[cur_time + 2].s_balance_pending_in = 0;

  log_transfer_sended(context, transfer_order);
  inc_lamport_time();

  received_message.s_header.s_local_time = get_lamport_time();
  send(context, transfer_order->s_dst, &received_message);
}
void child_receive_transfer(Context* context, TransferOrder* transfer_order) {
  timestamp_t cur_time = get_lamport_time();

  context->balance += transfer_order->s_amount;

  context->balance_history.s_history[cur_time].s_time = get_lamport_time();
  context->balance_history.s_history[cur_time].s_balance = context->balance;
  context->balance_history.s_history[cur_time].s_balance_pending_in = 0;

  log_transfer_received(context, transfer_order);
  inc_lamport_time();

  Message confirm_message;
  confirm_message.s_header.s_type = ACK;
  confirm_message.s_header.s_local_time = get_lamport_time();
  confirm_message.s_header.s_magic = MESSAGE_MAGIC;
  confirm_message.s_header.s_payload_len = 0;

  send(context, 0, &confirm_message);
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

void init_balance_history(Context* context) {
  memset(context->balance_history.s_history, 0, sizeof(context->balance_history));
  context->balance_history.s_id = (local_id) context->current_id;

  context->balance_history.s_history[0].s_balance_pending_in = 0;
  context->balance_history.s_history[0].s_balance = context->balance;
  context->balance_history.s_history[0].s_time = get_lamport_time();
}

void start_child(Context *context, int *process_statuses) {
  process_statuses[context->current_id] = STARTED;

  init_balance_history(context);
  send_started_to_everyone(context);
  wait_until_everyone_starts(context, process_statuses);
}
void finish_child(Context *context, int *process_statuses) {
  process_statuses[context->current_id] = DONE;

  send_finished_to_everyone(context);
  // child_send_history_to_root(context);
  wait_until_everyone_finishes(context, process_statuses);
}
void start_root(Context *context, int *process_statuses) {
  log_root_started(context);
  wait_until_everyone_starts(context, process_statuses);
}
void finish_root(Context *context, int *process_statuses) {
  log_root_finished(context);

  wait_until_everyone_finishes(context, process_statuses);
  // root_start_receive_histories(context);
  wait_for_children(context);
}

void root_start_receive_histories(Context* context) {
  AllHistory history;
  history.s_history_len = (uint8_t) (context->processes_amount - 1);

  printf("Root listens for histories\n");

  int histories_remaining = context->processes_amount - 1;
  while (histories_remaining) {
    Message history_message;
    if (receive_any(context, &history_message) == 0 && history_message.s_header.s_type == BALANCE_HISTORY) {
      BalanceHistory* balance_history = (BalanceHistory*) history_message.s_payload;
      memcpy(&history.s_history[balance_history->s_id - 1], history_message.s_payload, history_message.s_header.s_payload_len);
      histories_remaining--;

      set_max_lamport_time(get_lamport_time(), history_message.s_header.s_local_time);
      inc_lamport_time();
      printf("Root got history, %d remaining\n", histories_remaining);
    } else {
      printf("Root received garbage in root_start_receive_histories\n");
    }
  }

  // nsh: Uncomment if needed with a piece on top
  // print_history(&history);
}
void child_send_history_to_root(Context* context) {
  // Add last row
  timestamp_t current_time = get_lamport_time();
  timestamp_t last_history_row = current_time;
  context->balance_history.s_history[current_time].s_time = get_lamport_time();
  context->balance_history.s_history[current_time].s_balance = context->balance;
  context->balance_history.s_history[current_time].s_balance_pending_in = 0;
  context->balance_history.s_history_len = (uint8_t) (last_history_row + 1);

  balance_t current_balance = context->balance_history.s_history[0].s_balance;
  balance_t current_pending_balance = 0;
  current_time = 0;
  for (int i = 1; i < context->balance_history.s_history_len; i++) {
    ++current_time;
    if (context->balance_history.s_history[i].s_balance == 0 && context->balance_history.s_history[i].s_time == 0) {
      context->balance_history.s_history[i].s_balance = current_balance;
      context->balance_history.s_history[i].s_balance_pending_in = current_pending_balance;
      context->balance_history.s_history[i].s_time = current_time;
    } else {
      current_balance = context->balance_history.s_history[i].s_balance;
      current_pending_balance = context->balance_history.s_history[i].s_balance_pending_in;
    }
  }

  inc_lamport_time();

  Message history_msg;
  history_msg.s_header.s_type = BALANCE_HISTORY;
  history_msg.s_header.s_magic = MESSAGE_MAGIC;
  history_msg.s_header.s_local_time = get_lamport_time();
  history_msg.s_header.s_payload_len = sizeof(context->balance_history.s_id) + sizeof(context->balance_history.s_history_len) + context->balance_history.s_history_len * sizeof(BalanceState);

  memcpy(history_msg.s_payload, &context->balance_history, history_msg.s_header.s_payload_len);
  send(context, 0, &history_msg);
}

void log_root_started(Context *context) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_started_fmt, get_lamport_time(), context->current_id, context->current_pid, context->parent_pid, context->balance);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  printf("%s", message_buffer);
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
void log_transfer_sended(Context *context, TransferOrder *transferOrder) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_transfer_out_fmt, get_lamport_time(), context->current_id, transferOrder->s_amount, transferOrder->s_dst);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  printf("%s", message_buffer);
}
void log_transfer_received(Context *context, TransferOrder *transferOrder) {
  char message_buffer[4096];
  int message_size = sprintf(message_buffer, log_transfer_in_fmt, get_lamport_time(), context->current_id, transferOrder->s_amount, transferOrder->s_src);

  fwrite(message_buffer, 1, (size_t) message_size, context->events_log);
  printf("%s", message_buffer);
}

void log_message(Context* context, Message message) {
  printf("%s", message.s_payload);
  fwrite(message.s_payload, 1, message.s_header.s_payload_len, context->events_log);
}
