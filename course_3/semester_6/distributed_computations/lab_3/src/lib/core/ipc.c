#include "../vendor/ipc.h"
#include "headers/include.h"

int receive(void* self, local_id from, Message* msg) {
  Context* context = (Context*) self;

  while (1) {
    ssize_t bytes_read = read(context->pipes[from][context->current_id].from_id, &msg->s_header, sizeof(MessageHeader));
    if (bytes_read > 0) {
      bytes_read += read(context->pipes[from][context->current_id].from_id, msg->s_payload, msg->s_header.s_payload_len);
      msg->s_payload[msg->s_header.s_payload_len] = 0;
    }

    if (bytes_read == (sizeof(MessageHeader) + msg->s_header.s_payload_len)) {
      return 0;
    } else if (errno == EAGAIN) {
      for (int i = 0; i < 100000; ++i) {}
    } else {
      printf("Error occurred in receive!\n");
      return -1;
    }
  }
}

int receive_any(void* self, Message* message) {
  Context* context = (Context*) self;
  ssize_t bytes_read = 0;

  int current_node = 0;
  while (1) {
    if (current_node == context->current_id) {
      ++current_node;
      if (current_node == context->processes_amount) {
        current_node = 0;
      }
      continue;
    }

    if ((bytes_read = read(context->pipes[current_node][context->current_id].from_id, &message->s_header, sizeof(MessageHeader))) > 0) {
      bytes_read += read(context->pipes[current_node][context->current_id].from_id, message->s_payload, message->s_header.s_payload_len);
      message->s_payload[message->s_header.s_payload_len] = 0;
    }
    if (bytes_read == (sizeof(MessageHeader) + message->s_header.s_payload_len)) {
      return 0;
    } else if (errno == EAGAIN) {
      ++current_node;
      if (current_node == context->processes_amount) {
        current_node = 0;
      }

      for (int i = 0; i < 100000; ++i) {}
    } else {
      printf("undefined error in receive any\n");
    }
  } 
}

int send(void* self, local_id dst, const Message* msg) {
  Context* context = (Context*) self;

  write(context->pipes[context->current_id][dst].to_id, msg, msg->s_header.s_payload_len + sizeof(MessageHeader));
  return 0;
}

int send_multicast(void* self, const Message* msg) {
  Context* context = (Context*) self;

  for (int i = 0; i < context->processes_amount; ++i) {
    if (i != context->current_id) {
      if (write(context->pipes[context->current_id][i].to_id, msg, msg->s_header.s_payload_len + sizeof(MessageHeader)) != msg->s_header.s_payload_len + sizeof(MessageHeader)) {
        printf("Error in sendmulticast\n");
      }
    }
  }

  return 0;
}
