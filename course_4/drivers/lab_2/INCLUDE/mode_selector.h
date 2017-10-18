#ifndef __MODE_SELECTOR__H
#define __MODE_SELECTOR__H

#include "common.h"

extern u8 mode;

const u8 MODE_ANIMATION=1;
const u8 MODE_COUNTER=2;

void initialize_mode_selector();

#endif