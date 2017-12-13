#ifndef __HANDLERI__H
#define __HANDLERI__H

#include "common.h"

extern u8 mode;

static const u8 MODE_TEST=0x00;
static u8 MODE_INT=0xFF;

void initialize_handler();
void test_loop();
void int_loop();
void handler_int(u8 sym);
void handler_loop();

#endif