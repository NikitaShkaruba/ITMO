#include "include.h"

void init_new_context(Context *context, int current_id, int parent_pid) {
  context->current_id = current_id;
  context->current_pid = getpid();
  context->parent_pid = parent_pid;
}

void init_root(int processes_amount, int is_mutex_mode) {
  Context context;
  context.processes_amount = processes_amount;
  context.events_log = fopen(events_log, "a");
  context.is_mutex_mode = is_mutex_mode;

  init_new_context(&context, 0, 0);
  init_root_pipes(&context);
  init_children(&context);
  run(&context);
}
void init_root_pipes(Context *context) {
  context->pipes_log = fopen(pipes_log, "w");

  context->pipes = calloc((size_t) context->processes_amount, sizeof(Pipe*));
  for (int i = 0; i < context->processes_amount; ++i) {
    context->pipes[i] = calloc((size_t) context->processes_amount, sizeof(Pipe));
  }

  // Allow writing without blocking for every children
  for (int i = 0; i < context->processes_amount; ++i) {
    for (int j = 0; j < context->processes_amount; ++j) {
      if (i == j) {
        continue;
      }

      if (pipe((int*) &context->pipes[i][j]) != -1) {
        fcntl(context->pipes[i][j].from_id, F_SETFL, O_NONBLOCK);
        fcntl(context->pipes[i][j].to_id, F_SETFL, O_NONBLOCK);
        printf("Pipe paved: %d -> %d\n", i, j);
        fprintf(context->pipes_log, "Pipe paved: %d -> %d\n", i, j);
      } else {
        printf("Error in pipes paving\n");
        exit(-1);
      }
    }
  }

  fclose(context->pipes_log);
}
void close_pipes(Context* context) {
  fclose(context->events_log);

  for (int i = 0; i < context->processes_amount; ++i) {
    for (int j = 0; j < context->processes_amount; ++j) {
      close(context->pipes[i][j].from_id);
      close(context->pipes[i][j].to_id);
    }
    free(context->pipes[i]);
  }

  free(context->pipes);
}

void init_children(Context *context) {
  pid_t parent_pid = getpid();

  for (int i = 0; i < context->processes_amount - 1; ++i) {
    if (fork() == 0) {
      init_new_context(context, i + 1, parent_pid);
      break;
    }
  }

  init_children_pipes(context);
}
void init_children_pipes(Context *context) {
  close(context->pipes[context->current_id][context->current_id].from_id);
  close(context->pipes[context->current_id][context->current_id].to_id);

  for (int i = 0; i < context->processes_amount; ++i) {
    for (int j = 0; j < context->processes_amount; ++j) {
      if (i != context->current_id && j != context->current_id) {
        close(context->pipes[i][j].from_id);
        close(context->pipes[i][j].to_id);
      }
      if (i == context->current_id && j != context->current_id) {
        close(context->pipes[i][j].from_id);
      }
      if (j == context->current_id && i != context->current_id) {
        close(context->pipes[i][j].to_id);
      }
    }
  }
}
