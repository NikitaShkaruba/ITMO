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

void root_do_work(Context *context);
void child_do_work(Context *context);
void child_send_transfer(Context* context, TransferOrder* transfer_order, Message received_message);
void child_receive_transfer(Context* context, TransferOrder* transfer_order);

void send_started_to_everyone(Context* context);
void send_finished_to_everyone(Context* context);

void root_start_receive_histories(Context* context);
void child_send_history_to_root(Context* context);

void start_child(Context *context, int *process_statuses);
void finish_child(Context *context, int *process_statuses);
void start_root(Context *context, int *process_statuses);
void finish_root(Context *context, int *process_statuses);

void log_root_started(Context *context);
void log_root_finished(Context *context);
void log_all_started(Context *context);
void log_all_finished(Context* context);
void log_transfer_sended(Context *context, TransferOrder *transferOrder);
void log_transfer_received(Context *context, TransferOrder *transferOrder);
void log_message(Context* context, Message message);

#endif


