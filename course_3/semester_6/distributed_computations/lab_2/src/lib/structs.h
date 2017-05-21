#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "vendor/banking.h"

#include <stdio.h>
#include <fcntl.h>

typedef struct {
    int rf;
    int wf;
} Channel;

typedef struct {
    pid_t      pid;
    pid_t      parent_pid;
    int        node_id;         // current Node ID (= 0) for parent
    int        parent_node_id;  // current Node ID (> 0) for parent

    Channel**  channels; // N x N
    balance_t  balance;
    int        processes_amount;

    FILE*      main_log; // file descriptor for logging
    FILE*      pipes_log;
} Lab;

#endif
