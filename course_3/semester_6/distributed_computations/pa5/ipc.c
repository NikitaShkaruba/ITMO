#include "include.h"

int receive(void* self, local_id from, Message* msg) {
  Context* context = (Context*) self;

  while (1) {
    ssize_t bytes_read = 0;
    if ((bytes_read = read(context->pipes[from][context->current_id].from_id, &msg->s_header, sizeof(MessageHeader))) > 0) {
      bytes_read += read(context->pipes[from][context->current_id].from_id, msg->s_payload, msg->s_header.s_payload_len);
      msg->s_payload[msg->s_header.s_payload_len] = 0;
    }

    if (bytes_read == (sizeof(MessageHeader) + msg->s_header.s_payload_len)) {
      set_max_lamport_time(get_lamport_time(), msg->s_header.s_local_time);
      return from;
    } else if (errno == EAGAIN) {
      for (int i = 0; i < 1000000; ++i) {}
    } else {
      printf("Error receiving!\n");
      return -1;
    }
  }
}

int receive_any(void* self, Message* msg) {
  Context* context = (Context*) self;
  ssize_t bytes_read = 0;

  for (int i = 0; i < context->processes_amount; ++i) {
    if ((bytes_read = read(context->pipes[i][context->current_id].from_id, &msg->s_header, sizeof(MessageHeader))) > 0) {
      bytes_read += read(context->pipes[i][context->current_id].from_id, msg->s_payload, msg->s_header.s_payload_len);
      msg->s_payload[msg->s_header.s_payload_len] = 0;

      if (bytes_read == (sizeof(MessageHeader) + msg->s_header.s_payload_len)) {
        set_max_lamport_time(get_lamport_time(), msg->s_header.s_local_time);
        return i;
      } else {
        printf("Error in receive_any\n");
        return -1;
      }
    }
  }

  return -1;
}

int send(void* self, local_id dst, const Message* msg) {
  Context* context = (Context*) self;

  if (write(context->pipes[context->current_id][dst].to_id, msg, msg->s_header.s_payload_len + sizeof(MessageHeader)) != (msg->s_header.s_payload_len + sizeof(MessageHeader))) {
    printf("Error in send\n");
    return -1;
  }

  return 0;
}

int send_multicast(void* self, const Message* msg) {
  Context* context = (Context*) self;

  for (int i = 0; i < context->processes_amount; ++i) {
    if (i != context->current_id) {
      if (write(context->pipes[context->current_id][i].to_id, msg, msg->s_header.s_payload_len + sizeof(MessageHeader)) != (msg->s_header.s_payload_len + sizeof(MessageHeader))) {
        printf("Error in sendmulticast\n");
      }
    }
  }

  return 0;
}

void send_request(Context* context, timestamp_t request_time) {
  Message lock_message;
  lock_message.s_header.s_type = CS_REQUEST;
  lock_message.s_header.s_local_time = request_time;
  lock_message.s_header.s_payload_len = 0;
  lock_message.s_header.s_magic = MESSAGE_MAGIC;

  send_multicast(context, &lock_message);
}

void handle_request_message(Context* context, Message request_message, int sender_id, int request_time) {
  if ((request_time > request_message.s_header.s_local_time) || ((request_time == request_message.s_header.s_local_time) && (context->current_id > sender_id))) {
    inc_lamport_time();

    Message rep_msg;
    rep_msg.s_header.s_type = CS_REPLY;
    rep_msg.s_header.s_local_time = get_lamport_time();
    rep_msg.s_header.s_magic = MESSAGE_MAGIC;
    rep_msg.s_header.s_payload_len = 0;
    send(context, (local_id) sender_id, &rep_msg);
  } else {
    context->process_locks[sender_id] = 1;
  }
}

int request_cs(const void* self) {
  Context* context = (Context*) self;

  inc_lamport_time();
  timestamp_t request_time = get_lamport_time();

  send_request(context, request_time);

  char responses[context->processes_amount];
  memset(responses, 0, context->processes_amount);
  responses[context->current_id] = 1;

  for (int i = 1; i < context->processes_amount; ++i) {
    if (context->process_statuses[i] == DONE) {
      responses[i] = 1;
    }
  }

  char need_managing_replies = 0;
  for (int i = 1; i < context->processes_amount; ++i) {
    if (responses[i] == 0) {
      need_managing_replies = 1;
    }
  }

  while (need_managing_replies) {
    Message request_message;

    int sender_id = receive_any(context, &request_message);
    if (sender_id == -1) {
      for (int i = 0; i < 1000000; ++i) {}
      continue;
    }

    char* type = "SHIasdfasd";
    if (request_message.s_header.s_type == CS_REQUEST) {
      handle_request_message(context, request_message, sender_id, request_time);
      type = "REQUEST";
    } else if (request_message.s_header.s_type == CS_REPLY) {
      responses[sender_id] = 1;
      type = "REPLY";
    } else if (request_message.s_header.s_type == DONE) {
      context->process_statuses[sender_id] = DONE;
      responses[sender_id] = 1;
      type = "DONE";
    }

    need_managing_replies = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (responses[i] != DONE) {
        need_managing_replies = 1;
      }
    }
    printf("%d Received from %d %s [ %d, %d, %d, %d, %d, %d, %d, %d, %d ]\n", context->current_id, sender_id,  type, responses[0], responses[1], responses[2], responses[3], responses[4], responses[5], responses[6], responses[7], responses[8]);
  }

  return 0;
}

void send_release_lock(Context* context, int process_id) {
  Message rep_msg;
  rep_msg.s_header.s_type = CS_REPLY;
  rep_msg.s_header.s_local_time = get_lamport_time();
  rep_msg.s_header.s_magic = MESSAGE_MAGIC;
  rep_msg.s_header.s_payload_len = 0;
  send(context, (local_id) process_id, &rep_msg);

  context->process_locks[process_id] = 0;
}

int release_cs(const void* self) {
  Context* context = (Context*) self;

  inc_lamport_time();
  for (int i = 1; i < context->processes_amount; ++i) {
    if (context->process_locks[i] == 1) {
      send_release_lock(context, i);
    }
  }

  return 0;
}
