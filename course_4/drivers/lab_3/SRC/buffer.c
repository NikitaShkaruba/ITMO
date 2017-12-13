#include "buffer.h"


void initialize_buffer(Buffer* buffer) {
	buffer->head=0;
	buffer->tail=0;
	buffer->len=0;
}

bool is_buffer_empty(Buffer* buffer) {
	return buffer->len == 0;
}
	
bool is_buffer_full(Buffer* buffer) {
	return buffer->len == BUFFER_LEN;
}

void push_byte_to_buffer(Buffer* buffer, u8 dat) {
	buffer->mem[buffer->head] = dat;
    buffer->head++;
	buffer->len++;

    if (buffer->head == BUFFER_LEN) {
		buffer->head = 0;
    }
}

u8 pop_byte_from_buffer(Buffer* buffer) {
	u8 dat;
	dat= buffer->mem[buffer->tail];
	buffer->tail++;
	buffer->len--;

	if (buffer->tail == BUFFER_LEN) {
		buffer->tail = 0;
	}
	
	return dat;
}