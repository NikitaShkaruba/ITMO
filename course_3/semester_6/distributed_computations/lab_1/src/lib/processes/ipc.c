#include "../headers/vendor/ipc.h"

#include "../headers/structs.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int receive(void* self, local_id from, Message* msg) {
  Context* lab = (Context*) self;

  while (1) {
    ssize_t bytes_read = read(lab->pipes[from][lab->current_id].from_id, &msg->s_header, sizeof(MessageHeader));
    if (bytes_read > 0) {
      bytes_read += read(lab->pipes[from][lab->current_id].from_id, msg->s_payload, msg->s_header.s_payload_len);
      msg->s_payload[msg->s_header.s_payload_len] = 0;
    }

    if (bytes_read == (sizeof(MessageHeader) + msg->s_header.s_payload_len)) {
      return 0;
    } else if (errno == EAGAIN) {
      for (int i = 0; i < 100000; ++i) {}
    } else {
      printf("Error occured in receive!\n");
      return -1;
    }
  }
}

int receive_any(void* self, Message* msg) {
  Context* lab = (Context*) self;
  ssize_t bytes_read = 0;

  for (int i = 0; i < lab->processes_amount; ++i) {
    if (i == lab->current_id) {
      continue;  // skip current node
    }

    bytes_read = read(lab->pipes[i][lab->current_id].from_id, msg, MAX_MESSAGE_LEN);

    if (bytes_read > 0) {
      return 0;
    } else if (bytes_read == -1 && errno == EAGAIN) {
      if (i == lab->processes_amount - 1) {
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
  Context* lab = (Context*) self;

  write(lab->pipes[lab->current_id][dst].to_id, msg, msg->s_header.s_payload_len + sizeof(MessageHeader));
  return 0;
}

int send_multicast(void* self, const Message* msg) {
  Context* lab = (Context*) self;

  for (int i = 0; i < lab->processes_amount; ++i) {
    if (i != lab->current_id) {
      if (write(lab->pipes[lab->current_id][i].to_id, msg, msg->s_header.s_payload_len + sizeof(MessageHeader)) != msg->s_header.s_payload_len + sizeof(MessageHeader)) {
        printf("Error in sendmulticast\n");
      }
    }
  }

  return 0;
}

