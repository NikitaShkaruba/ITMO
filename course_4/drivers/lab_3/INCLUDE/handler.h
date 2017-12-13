#ifndef __HANDLERI__H
#define __HANDLERI__H

#include "common.h"

extern u8 mode;

static const u8 MODE_POLL=0x00;
static u8 MODE_INT=0xFF;

void initialize_handler();
void poll_loop();
void int_loop();
void handler_int(u8);
void handler_loop();

#endif