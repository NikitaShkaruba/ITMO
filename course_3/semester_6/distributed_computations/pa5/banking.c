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

