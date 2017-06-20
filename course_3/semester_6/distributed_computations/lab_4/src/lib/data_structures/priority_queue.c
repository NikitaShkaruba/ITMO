#include "priority_queue.h"

void _priority_queue_set_element(PriorityQueue* priority_queue, int i, int priority, int data) {
  priority_queue->nodes[i].priority = priority;
  priority_queue->nodes[i].data = data;
}

PriorityQueue* priority_queue_create(int size) {
  PriorityQueue* priority_queue = (PriorityQueue*) calloc(1, sizeof(PriorityQueue));
  priority_queue->nodes = (PriorityQueueNode*) calloc((size_t) size, sizeof(PriorityQueueNode));
  priority_queue->size = size;
  priority_queue->length = 0;

  return priority_queue;
}

void priority_queue_push(PriorityQueue* priority_queue, int priority, int data) {
  if (!priority_queue->length) {
    _priority_queue_set_element(priority_queue, 0, priority, data);
    priority_queue->length++;
    return;
  }

  int insert_index = 0;
  while (1) {
    if (insert_index == priority_queue->length) {
      priority_queue->nodes[insert_index].priority = priority;
      priority_queue->nodes[insert_index].data = data;
      priority_queue->length++;
      return;
    }

    if ((priority_queue->nodes[insert_index].priority > priority) || (priority_queue->nodes[insert_index].priority == priority && priority_queue->nodes[insert_index].data > data)) {
      for (int i = priority_queue->length; i > insert_index; --i) {
        _priority_queue_set_element(priority_queue, i, priority_queue->nodes[i - 1].priority, priority_queue->nodes[i - 1].data);
      }

      _priority_queue_set_element(priority_queue, insert_index, priority, data);
      priority_queue->length++;
      return;
    }

    ++insert_index;
  }
}

int priority_queue_pop(PriorityQueue* priority_queue) {
  if (!priority_queue->length) {
    return -1;
  }

  int data = priority_queue->nodes[0].data;
  for (int i = 0; i < priority_queue->length; ++i) {
    _priority_queue_set_element(priority_queue, i, priority_queue->nodes[i - 1].priority, priority_queue->nodes[i - 1].data);
  }
  priority_queue->length--;

  return data;
}

int priority_queue_peek(PriorityQueue* priority_queue) {
  if (!priority_queue->length) {
    return -1;
  }

  return priority_queue->nodes[0].data;
}

