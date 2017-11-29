#include "aduc812.h"
#include "uart.h"
#include "interrupt.h"


void delay ( unsigned long ms );

void main( void ) {
	initialize_uart(S9600);
	initialize_handler();
	
	EA=1;
	
	handler_loop();
}