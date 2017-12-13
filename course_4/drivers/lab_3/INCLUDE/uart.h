#ifndef __UART__H
#define __UART__H

#include "common.h"

//Константы скорости
#define S9600   0xFD
#define S4800   0xFA
#define S2400   0xF4
#define S1200   0xE8

void initialize_uart(u8 speed);
void send_byte(u8 data);
bool read_byte(u8* data);
void send_string(char * str);

u8 poll_is_byte();
u8 poll_read_byte();
void poll_write_byte(u8 byte_out);
void poll_send_string(char * str);

#endif