#include "aduc812.h"
#include "led.h"
#include "system_timer.h"
#include "uart.h"
#include "handler.h"


void delay ( unsigned long ms );

void main( void ) {
	initialize_system_timer();
	initialize_uart(S9600);
	initialize_handler();
	
	EA=1;
	
	handler_loop();
}