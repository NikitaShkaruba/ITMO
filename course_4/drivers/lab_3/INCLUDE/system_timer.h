#ifndef __SYSTEM_TIMER__H
#define __SYSTEM_TIMER__H

#include "common.h"

void initialize_system_timer(void);
time get_ms(void);
time get_ms_after(time t0);
void delay_ms(time t);

#endif