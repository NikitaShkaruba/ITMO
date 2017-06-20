#include "vendor/ipc.h"

#include "structs.h"
#include <errno.h>
#include <unistd.h>

int receive(void* self, local_id from, Message* msg) {
  Lab* lab = (Lab*) self;

  while (1) {
    ssize_t bytes_read = 0;
    if ((bytes_read = read(lab->channels[from][lab->node_id].rf, &msg->s_header, sizeof(MessageHeader))) > 0) {
      bytes_read += read(lab->channels[from][lab->node_id].rf, msg->s_payload, msg->s_header.s_payload_len);
      msg->s_payload[msg->s_header.s_payload_len] = 0;
    }

    if (bytes_read == (sizeof(MessageHeader) + msg->s_header.s_payload_len)) {
      return 0;
    } else if (errno == EAGAIN) {
      for (int i = 0; i < 1000000; ++i) {} // handmade usleep analog!
    } else {
      printf("Error occurred in receive!\n");
      return -1;
    }
  }
}

int receive_any(void* self, Message* msg) {
  Lab* lab = (Lab*) self;
  ssize_t bytes_read = 0;

  int current_node = 0;
  while (1) {
    if (current_node == lab->node_id) {
      ++current_node;
      if (current_node == lab->processes_amount) {
        current_node = 0;
      }
      continue;
    }

    if ((bytes_read = read(lab->channels[current_node][lab->node_id].rf, &msg->s_header, sizeof(MessageHeader))) > 0) {
      bytes_read += read(lab->channels[current_node][lab->node_id].rf, msg->s_payload, msg->s_header.s_payload_len);
      msg->s_payload[msg->s_header.s_payload_len] = 0;
    }
    if (bytes_read == (sizeof(MessageHeader) + msg->s_header.s_payload_len)) {
      return 0;
    } else if (errno == EAGAIN) {
      ++current_node;
      if (current_node == lab->processes_amount) {
        current_node = 0;
      }

      for (int i = 0; i < 100000; ++i) {}
    } else {
      printf("undefined error in receive_any\n");
    }
  }
}

int send(void* self, local_id dst, const Message* msg) {
  Lab* lab = (Lab*) self;

  write(lab->channels[lab->node_id][dst].wf, msg, msg->s_header.s_payload_len + sizeof(MessageHeader));
  return 0;
}

int send_multicast(void* self, const Message* msg) {
  Lab* lab = (Lab*) self;

  for (int i = 0; i < lab->processes_amount; ++i) {
    if (i != lab->node_id) {
      if (write(lab->channels[lab->node_id][i].wf, msg, msg->s_header.s_payload_len + sizeof(MessageHeader)) != msg->s_header.s_payload_len + sizeof(MessageHeader)) {
        printf("Error in sendmulticast\n");
      }
    }
  }

  return 0;
}

