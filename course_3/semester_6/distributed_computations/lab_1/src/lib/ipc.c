#include "vendor/ipc.h"

#include "structs.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int receive(void* self, local_id from, Message* msg) {
  Lab* lab = (Lab*) self;

  while (1) {
    ssize_t bytes_read = read(lab->channels[from][lab->n_process_id].rf, &msg->s_header, sizeof(MessageHeader));
    if (bytes_read > 0) {
      bytes_read += read(lab->channels[from][lab->n_process_id].rf, msg->s_payload, msg->s_header.s_payload_len);
      msg->s_payload[msg->s_header.s_payload_len] = 0;
    }

    if (bytes_read == (sizeof(MessageHeader) + msg->s_header.s_payload_len)) {
      return 0;
    } else if (errno == EAGAIN) {
      for (int i = 0; i < 100000; ++i) {} // handmade usleep analog!
    } else {
      printf("Error occured in receive!\n");
      return -1;
    }
  }
}

int receive_any(void* self, Message* msg) {
  Lab* lab = (Lab*) self;
  ssize_t bytes_read = 0;

  for (int i = 0; i < lab->n_processes_count; ++i) {
    if (i == lab->n_process_id) {
      continue;  // skip current node
    }

    bytes_read = read(lab->channels[i][lab->n_process_id].rf, msg, MAX_MESSAGE_LEN);

    if (bytes_read > 0) {
      return 0;
    } else if (bytes_read == -1 && errno == EAGAIN) {
      if (i == lab->n_processes_count - 1) {
        i = 0;
      } else {
        continue;
      }
    } else {
      return -1;
    }
  }

  return -1;
}

int send_one(void* self, local_id dst, const Message* msg) {
  Lab* lab = (Lab*) self;

  write(lab->channels[lab->n_process_id][dst].wf, msg, msg->s_header.s_payload_len + sizeof(MessageHeader));
  return 0;
}

int send_multicast(void* self, const Message* msg) {
  Lab* lab = (Lab*) self;

  for (int i = 0; i < lab->n_processes_count; ++i) {
    if (i != lab->n_process_id) {
      if (write(lab->channels[lab->n_process_id][i].wf, msg, msg->s_header.s_payload_len + sizeof(MessageHeader)) != msg->s_header.s_payload_len + sizeof(MessageHeader)) {
        printf("Error in sendmulticast\n");
      }
    }
  }

  return 0;
}

