#ifndef __COMMON__H
#define __COMMON__H

#include "aduc812.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long time;

void SetVector(unsigned char __xdata * Address, void * Vector);

#endif