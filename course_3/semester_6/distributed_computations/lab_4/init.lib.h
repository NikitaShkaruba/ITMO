#ifndef __IFMO_DISTRIBUTED_CLASS_INIT__H
#define __IFMO_DISTRIBUTED_CLASS_INIT__H

#include "include.h"
#include "run.lib.h"

void init_new_context(Context *context, int current_id, int parent_pid);
void init_root(int processes_amount, int is_mutex_mode);
void init_root_pipes(Context *context);
void init_children(Context *context);
void init_children_pipes(Context *context);

void close_pipes(Context* context);
#endif
