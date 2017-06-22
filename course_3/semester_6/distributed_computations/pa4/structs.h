#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "include.h"

/**
 * Priority queue
 */
typedef struct {
  int priority;
  int data;
} PriorityQueueNode;

/**
 * Priority queue helper
 */
typedef struct {
  PriorityQueueNode* nodes;

  int length;
  int size;
} PriorityQueue;

/**
 * Stores information about channel socket points
 */
typedef struct {
  int from_id;
  int to_id;
} Pipe;

/**
 * Stores current context
 */
typedef struct {
  // Node descriptions
  pid_t       parent_pid;
  pid_t       current_pid;
  int         parent_id;
  int         current_id;

  // File descriptors for logging
  FILE*       events_log;
  FILE*       pipes_log;

  // Main
  Pipe**      pipes;
  int         processes_amount;

  // Banking
  balance_t       balance;
  BalanceHistory  balance_history;

  // Locking and Mutexes
  int               is_mutex_mode;
  PriorityQueue*    priority_queue;
  char*             process_statuses;
} Context;

#endif
