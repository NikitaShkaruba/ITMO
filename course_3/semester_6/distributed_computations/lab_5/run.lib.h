#ifndef __IFMO_DISTRIBUTED_CLASS_RUN__H
#define __IFMO_DISTRIBUTED_CLASS_RUN__H

#include "include.h"

void run(Context* context);
void run_root(Context* context);
void run_child(Context *context);

void wait_until_everyone_starts(Context *context);
void wait_until_everyone_finishes(Context *context);
void wait_for_children(Context* context);

void root_do_work(Context *context);
void child_do_work(Context *context);

void send_started_to_everyone(Context* context);
void send_finished_to_everyone(Context* context);

void start_child(Context *context);
void finish_child(Context *context);
void start_root(Context *context);
void finish_root(Context *context);

void log_root_started(Context *context);
void log_root_finished(Context *context);
void log_all_started(Context *context);
void log_all_finished(Context* context);

#endif


