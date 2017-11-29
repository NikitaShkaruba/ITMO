#ifndef __UART__H
#define __UART__H

#include "common.h"

//Константы скорости
#define S9600   0xFD
#define S4800   0xFA
#define S2400   0xF4
#define S1200   0xE8

void initialize_uart(char speed);
void send_byte(char data);
bool read_byte(char* data);
void send_string(char * str);

#endif