#include "include.h"

int receive(void* self, local_id from, Message* msg) {
  Context* app = (Context*) self;

  while (1) {
    ssize_t bytes_read = 0;
    if ((bytes_read = read(app->pipes[from][app->current_id].from_id,
                           &msg->s_header,
                           sizeof(MessageHeader))) > 0) {
      bytes_read += read(app->pipes[from][app->current_id].from_id,
                         msg->s_payload,
                         msg->s_header.s_payload_len);
      msg->s_payload[msg->s_header.s_payload_len] = 0;
    }

    if (bytes_read == (sizeof(MessageHeader) + msg->s_header.s_payload_len)) {
      set_max_lamport_time(get_lamport_time(), msg->s_header.s_local_time);
      return from;
    } else if (errno == EAGAIN) {
      for (int i = 0; i < 1000000; ++i) {} // handmade usleep analog!
    } else {
      printf("Error occured in receive!\n");
      return -1;
    }
  }
}

int receive_any(void* self, Message* msg) {
  Context* context = (Context*) self;
  ssize_t bytes_read = 0;

  // printf("%d GOT REPLY\n", context->current_id);
  for (int i = 0; i < context->processes_amount; ++i) {
    if ((bytes_read = read(context->pipes[i][context->current_id].from_id, &msg->s_header, sizeof(MessageHeader))) > 0) {
      bytes_read += read(context->pipes[i][context->current_id].from_id, msg->s_payload, msg->s_header.s_payload_len);
      msg->s_payload[msg->s_header.s_payload_len] = 0;

      if (bytes_read == (sizeof(MessageHeader) + msg->s_header.s_payload_len)) {
        set_max_lamport_time(get_lamport_time(), msg->s_header.s_local_time);
        return i;
      } else {
        printf("ERROR IN RECEIVE_ANY (NUMBER OF BYTES INEQUALITY)\n");
        return -1;
      }
    }
  }

  return -1;
}

int send(void* self, local_id dst, const Message* msg) {
  Context* app = (Context*) self;

  if (write(app->pipes[app->current_id][dst].to_id,
            msg,
            msg->s_header.s_payload_len + sizeof(MessageHeader)) !=
      (msg->s_header.s_payload_len + sizeof(MessageHeader))) {
    printf("ERROR IN SEND\n");
    return -1;
  }

  return 0;
}

int send_multicast(void* self, const Message* msg) {
  Context* app = (Context*) self;

  for (int i = 0; i < app->processes_amount; ++i) {
    if (i != app->current_id) {
      if (write(app->pipes[app->current_id][i].to_id,
                msg,
                msg->s_header.s_payload_len + sizeof(MessageHeader)) !=
          (msg->s_header.s_payload_len + sizeof(MessageHeader))) {
        printf("Error in sendmulticast\n");
      }
    }
  }

  return 0;
}

int request_cs(const void* self) {
  Context* context = (Context*) self;

  // step 1: send request
  Message req_msg;
  req_msg.s_header.s_type = CS_REQUEST;
  inc_lamport_time();
  req_msg.s_header.s_local_time = get_lamport_time();
  req_msg.s_header.s_payload_len = 0;
  req_msg.s_header.s_magic = MESSAGE_MAGIC;
  send_multicast(context, &req_msg);

  timestamp_t request_time = get_lamport_time();

  char replies_received[context->processes_amount];
  memset(replies_received, 0, context->processes_amount);
  replies_received[context->current_id] = 1;

  for (int i = 1; i < context->processes_amount; ++i) {
    if (context->paProcessesStatuses[i] == DONE)
      replies_received[i] = 1;
  }
  // check that replies receiving is needed
  char replies_receiving = 0;
  for (int i = 1; i < context->processes_amount; ++i) {
    if (replies_received[i] == 0)
      replies_receiving = 1;
  }

  Message rec_msg;
  while (replies_receiving) {
    int sender_id = receive_any(context, &rec_msg);
    if (sender_id == -1) {
      for (int i = 0; i < 1000000; ++i) {} // homemade usleep analog
      continue;
    }

    if (rec_msg.s_header.s_type == CS_REPLY) {
      printf("%d GOT REPLY\n", context->current_id);
      replies_received[sender_id] = 1;
    } else if (rec_msg.s_header.s_type == CS_REQUEST) {
      if ((request_time > rec_msg.s_header.s_local_time) || ((request_time == rec_msg.s_header.s_local_time) && (context->current_id > sender_id))) {
        printf("%d GOT REQUEST\n", context->current_id);
        Message rep_msg;
        rep_msg.s_header.s_type = CS_REPLY;
        inc_lamport_time();
        rep_msg.s_header.s_local_time = get_lamport_time();
        rep_msg.s_header.s_magic = MESSAGE_MAGIC;
        rep_msg.s_header.s_payload_len = 0;

        send(context, sender_id, &rep_msg);
      } else {
        printf("%d GOT REQUEST FALSE\n", context->current_id);
        context->paDRs[sender_id] = 1;
      }
    } else if (rec_msg.s_header.s_type == DONE) {
      printf("%d GOT DONE\n", context->current_id);
      context->paDRs[sender_id] = 1;
      context->paProcessesStatuses[sender_id] = DONE;
      replies_received[sender_id] = 1;
    }

    // check that replies receiving is done
    printf("%d APP PROCESSES: %d, %d, %d, %d\n", context->current_id, context->paProcessesStatuses[0], context->paProcessesStatuses[1], context->paProcessesStatuses[2], context->paProcessesStatuses[3]);
    replies_receiving = 0;
    for (int i = 1; i < context->processes_amount; ++i) {
      if (replies_received[i] == STARTED) {
        replies_receiving = 1;
      }
    }
  }

  printf("%d EXITING\n", context->current_id);
  return 0;
}

int release_cs(const void* self) {
  Context* app = (Context*) self;

  inc_lamport_time();
  for (int i = 1; i < app->processes_amount; ++i) {
    if (app->paDRs[i] == 1) {
      Message rep_msg;
      rep_msg.s_header.s_type = CS_REPLY;
      rep_msg.s_header.s_local_time = get_lamport_time();
      rep_msg.s_header.s_magic = MESSAGE_MAGIC;
      rep_msg.s_header.s_payload_len = 0;

      send(app, i, &rep_msg);

      app->paDRs[i] = 0;
    }
  }

  return 0;
}
