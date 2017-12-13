#ifndef __KEYBOARD__H
#define __KEYBOARD__H

#include "common.h"

void initialize_keyboard();
void scan_keyboard_int();
bool keyboard_read_byte(u8* dat);

#endif