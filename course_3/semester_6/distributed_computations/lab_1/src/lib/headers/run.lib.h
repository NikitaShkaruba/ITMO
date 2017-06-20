#ifndef __IFMO_DISTRIBUTED_CLASS_RUN__H
#define __IFMO_DISTRIBUTED_CLASS_RUN__H

#include "include.h"
#include "structs.h"
#include "init.lib.h"

void run(Context* context);
void run_parent(Context *context, int *process_statuses);
void run_child(Context *context, int *process_statuses);

void wait_until_everyone_starts(Context *context, int *process_statuses);
void wait_until_everyone_finishes(Context *context, int* process_statuses);
void wait_for_children(Context* context);

void do_work(Context* context);

void send_started_to_everyone(Context* context);
void send_finished_to_everyone(Context* context);

void start_child(Context *context, int *process_statuses);
void finish_child(Context *context, int *process_statuses);
void start_parent(Context *context, int *process_statuses);
void finish_parent(Context *context, int *process_statuses);

void log_parent_started(Context *context);
void log_parent_finished(Context *context);
void log_all_started(Context *context);
void log_all_finished(Context* context);
void log_message(Context* context, Message message);

#endif


