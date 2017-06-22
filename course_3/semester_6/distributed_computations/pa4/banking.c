#include "include.h"

timestamp_t lamport_local_time = 0;

timestamp_t get_lamport_time() {
  return lamport_local_time;
}

void set_max_lamport_time(timestamp_t timestamp1, timestamp_t timestamp2) {
  timestamp_t max_timextamp = max_timestamp(timestamp1, timestamp2);
  set_lamport_time(max_timextamp);
}
void set_lamport_time(timestamp_t timestamp) {
  lamport_local_time = timestamp;
}

void inc_lamport_time() {
  lamport_local_time++;
}

void transfer(void* parent_data, local_id src, local_id dst, balance_t amount) {
  Context* context = (Context*) parent_data;

  inc_lamport_time();

  Message message;
  message.s_header.s_local_time = get_lamport_time();
  message.s_header.s_magic = MESSAGE_MAGIC;
  message.s_header.s_type = TRANSFER;
  message.s_header.s_payload_len = sizeof(TransferOrder);

  TransferOrder transfer_order;
  transfer_order.s_dst = dst;
  transfer_order.s_src = src;
  transfer_order.s_amount = amount;
  memcpy(message.s_payload, &transfer_order, sizeof(transfer_order));

  send(context, src, &message);
  if (receive(context, dst, &message) == 0 && message.s_header.s_type != ACK) {
    printf("%d: error: received garbage in transfer_order from %d\n", get_lamport_time(), dst);
  }

  set_max_lamport_time(get_lamport_time(), message.s_header.s_local_time);
  inc_lamport_time();
}

