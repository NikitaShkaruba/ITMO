#ifndef LAB_5_PRIORITY_QUEUE_H
#define LAB_5_PRIORITY_QUEUE_H

#include "include.h"
#include "structs.h"

pqueue* create_pqueue(int size);

void pq_push(pqueue* pq, int priority, int data);

int pq_pop(pqueue* pq);

int pq_peek(pqueue* pq);

#endif
