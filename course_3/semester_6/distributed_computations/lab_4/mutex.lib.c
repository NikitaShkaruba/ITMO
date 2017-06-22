#include "include.h"

void send_mutex_request(Context* context, int request_time) {
  inc_lamport_time();

  Message req_msg;
  req_msg.s_header.s_type = CS_REQUEST;
  req_msg.s_header.s_local_time = (timestamp_t) request_time;
  req_msg.s_header.s_payload_len = 0;
  req_msg.s_header.s_magic = MESSAGE_MAGIC;
  send_multicast(context, &req_msg);
  printf("WEIGHT: %d", request_time);
}
void handle_cs_request(Context* context, int sender_id, int time) {
  priority_queue_push(context->priority_queue, time, sender_id);
  inc_lamport_time();

  Message reply_msg;
  reply_msg.s_header.s_type = CS_REPLY;
  reply_msg.s_header.s_local_time = get_lamport_time();
  reply_msg.s_header.s_magic = MESSAGE_MAGIC;
  reply_msg.s_header.s_payload_len = 0;

  send(context, (local_id) sender_id, &reply_msg);
}
void handle_cs_reply(char* responses, int sender_id, int request_time, int message_time) {
  if (request_time < message_time) {
    responses[sender_id] = 1;
  } else {
    printf("[false]: received YOUNGER MESSAGE\n");
  }
}
void handle_cs_release(Context* context, int sender_id) {
  int next_id = priority_queue_pop(context->priority_queue);
  if (next_id != sender_id) {
    printf("[false]: popped wrong request!\n");
  }
}
void handle_cs_success(Context* context, char* responses, int sender_id) {
  context->process_statuses[sender_id] = DONE;
  responses[sender_id] = 1;
}
char do_need_responses(Context* context, char* replies) {
  char need_responses = 0;

  for (int i = 1; i < context->processes_amount; ++i) {
    if (replies[i] == 0) {
      need_responses = 1;
    }
  }

  return need_responses;
}
int* update_mutex_responses(Context* context, int request_time) {
  char replies[context->processes_amount];
  memset(replies, 0, context->processes_amount);

  replies[context->current_id] = 1;
  for (int i = 1; i < context->processes_amount; ++i) {
    if (context->process_statuses[i] == DONE) {
      replies[i] = 1;
    }
  }

  char need_responses = do_need_responses(context, replies);

  Message request_message;
  while (need_responses || priority_queue_peek(context->priority_queue) != context->current_id) {

    int sender_id = receive_any(context, &request_message);
    if (sender_id == -1) {
      for (int i = 0; i < 100000; ++i) {}
      continue;
    }

    switch (request_message.s_header.s_type) {
      case CS_REQUEST: handle_cs_request(context, sender_id, request_message.s_header.s_local_time); break;
      case CS_REPLY: handle_cs_reply(replies, sender_id, request_time, request_message.s_header.s_local_time); break;
      case CS_RELEASE: handle_cs_release(context, sender_id); break;
      case DONE: handle_cs_success(context, replies, sender_id); break;
      default:break;
    }

    need_responses = do_need_responses(context, replies);
    if (!need_responses) {
      return 0;
    }

    if (priority_queue_peek(context->priority_queue) == -1) {
      printf("[false]: priority_queue is empty\n");
    }
  }

  return 0;
}

int request_cs(const void *self) {
  Context *context = (Context *) self;
  timestamp_t request_time = get_lamport_time();

  printf("process %d sended request (priority: %d)\n", context->current_id, get_lamport_time());
  send_mutex_request(context, request_time);
  priority_queue_push(context->priority_queue, request_time, context->current_id);
  return (int) update_mutex_responses(context, request_time);
}

int release_cs(const void *self) {
  Context *context = (Context *) self;

  printf("process %d received request (priority: %d)\n", context->current_id, get_lamport_time());
  int process_id = priority_queue_pop(context->priority_queue);
  if (process_id == -1) {
    printf("ERROR: popping NULL queue\n");
  }

  inc_lamport_time();

  Message rel_msg;
  rel_msg.s_header.s_type = CS_RELEASE;
  rel_msg.s_header.s_local_time = get_lamport_time();
  rel_msg.s_header.s_magic = MESSAGE_MAGIC;
  rel_msg.s_header.s_payload_len = 0;
  send_multicast(context, &rel_msg);

  return 0;
}
