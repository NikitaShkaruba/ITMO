#ifndef __BUFFER__H
#define __BUFFER__H

#include "common.h"

//ибо константа это не константа О_о
#define BUFFER_LEN 42

typedef struct {
	u8 mem[BUFFER_LEN];
	u8 head;
	u8 tail;
	u8 len;
} Buffer;

void initialize_buffer(Buffer* buffer);
bool is_buffer_empty(Buffer* buffer);
bool is_buffer_full(Buffer* buffer);
void push_byte_to_buffer(Buffer* buffer, u8 data);
u8 pop_byte_from_buffer(Buffer* buffer);

#endif