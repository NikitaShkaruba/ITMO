#ifndef LAB_4_PRIORITY_QUEUE_H
#define LAB_4_PRIORITY_QUEUE_H

#include "../core/headers/include.h"

PriorityQueue* priority_queue_create(int size);

void priority_queue_push(PriorityQueue* priority_queue, int priority, int data);

int priority_queue_pop(PriorityQueue* priority_queue);

int priority_queue_peek(PriorityQueue* priority_queue);

#endif
