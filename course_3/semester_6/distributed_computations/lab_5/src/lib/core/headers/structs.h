#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "include.h"

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
  pid_t parent_pid;
  pid_t current_pid;
  int parent_id;
  int current_id;

  // File descriptors for logging
  FILE* events_log;
  FILE* pipes_log;

  // Main
  Pipe** pipes;
  int processes_amount;

  // Banking - Is this still needed ?
  balance_t balance;

  // Priorities
  int is_mutex_mode;
  char* process_statuses;
  char* process_locks;
} Context;

#endif
