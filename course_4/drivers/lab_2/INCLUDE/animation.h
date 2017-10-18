#ifndef __PWM__H
#define __PWM__H

#include "common.h"

void initialize_animation();
void enable_animation();
void disable_animation();
void set_power(u8);
u8 get_power();

#endif