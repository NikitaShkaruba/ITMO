#ifndef __IFMO_DISTRIBUTED_CLASS_RUN__H
#define __IFMO_DISTRIBUTED_CLASS_RUN__H

#include "include.h"
#include "structs.h"
#include "run.lib.h"

void run(Context* lab);
void runParent(Context* context, int process_statuses[]);
void runChild(Context* context, int process_statuses[]);

#endif


