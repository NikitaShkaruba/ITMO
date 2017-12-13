#ifndef __COMMON__H
#define __COMMON__H

#include "aduc812.h"

typedef unsigned char bool;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long time;

const bool true=0xFF;
const bool false=0x00;

void SetVector(unsigned char __xdata * Address, void * Vector);

#endif