#include "aduc812.h"
#include "led.h"
#include "system_timer.h"
#include "uart.h"
#include "handler.h"
#include "keyboard.h"
#include "speaker.h"


void delay ( unsigned long ms );

void main( void ) {
	initialize_system_timer();
	initialize_keyboard();
	initialize_uart(S9600);
	initialize_handler();
	initialize_speaker();
	
	EA=1;
	
	handler_loop();
}