#include "include.h"

void transfer(void* parent_data, local_id src, local_id dst, balance_t amount) {
  Context* app = (Context*) parent_data;

  inc_lamport_time();

  // create message and send it to src
  Message msg;
  msg.s_header.s_local_time = get_lamport_time();
  msg.s_header.s_magic = MESSAGE_MAGIC;
  msg.s_header.s_type = TRANSFER;
  msg.s_header.s_payload_len = sizeof(TransferOrder);

  TransferOrder transfer;
  transfer.s_dst = dst;
  transfer.s_src = src;
  transfer.s_amount = amount;
  memcpy(msg.s_payload, &transfer, sizeof(transfer));

  send(app, src, &msg);
  if (receive(app, dst, &msg) == 0 && msg.s_header.s_type != ACK) {
    printf("%d: ERROR parent received garbage from %d\n", get_lamport_time(), dst);
  }

  set_max_lamport_time(get_lamport_time(), msg.s_header.s_local_time);
}

int main(int argc, const char* argv[]) {
  if (argc < 3 || strcmp(argv[1], "-p") != 0) {
    return 1;
  }

  int processes_amount = atoi(argv[2]) + 1;

  int is_mutex_mode = 0;
  for (int i = 0; i < argc; i++) {
    if (!strcmp(argv[i], "--mutexl")) {
      is_mutex_mode = 1;
    }
  }

  setbuf(stdout, NULL);
  init_root(processes_amount, is_mutex_mode);

  return 0;
}
