#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdio.h>
#include <fcntl.h>

typedef struct {
  int rf;
  int wf;
} Channel;

typedef struct {
  pid_t n_process_pid;
  pid_t n_parent_pid;
  int n_process_id; // current Node ID, 0 for parent, > 0 for child
  int n_parent_id;
  int n_processes_count;
  FILE* main_log; // file descriptor for logging
  FILE* pipes_log;
  Channel** channels; // N x N
} Lab;

#endif
