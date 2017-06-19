#ifndef __IFMO_DISTRIBUTED_CLASS_INIT__H
#define __IFMO_DISTRIBUTED_CLASS_INIT__H

#include "include.h"
#include "run.lib.h"

void initIds(Context* context, int current_id, int parent_pid);

void initRoot(int processes_amount);
void initRootPipes(Context *context);

void initChildren(Context* context);
void initChildrenPipes(Context *context);

#endif
