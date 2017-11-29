#include "handler.h"
#include "system_timer.h"
#include "max.h"
#include "uart.h"
#include "led.h"

const u8 DIP_POLL_MODE=0x01;
const u8 NUMBER_LIMIT=0xFF;

//eai eiinoaioa yoi ia eiinoaioa I_i
#define STATE_NUMBER 0
#define STATE_CR 1
#define STATE_ERROR 2

u8 mode;
u8 number;
u8 state;

u8 read_dip(){
	return read_max(EXT_LO);
}

void reset() {
	number=0;
	state=STATE_NUMBER;
}

void initialize_handler() {
	mode = MODE_POLL;
	reset();
}

void poll_loop() {
	u8 i;
	u8 byte_in;
	leds(0);
	
	while( read_dip()==DIP_POLL_MODE ){
		if( read_byte(&byte_in) ){
			for( i=1;i<=3;i++ ){
				if (byte_in > 96 && byte_in < 123) {
					byte_in = byte_in - 32;
				}
				/*if (byte_in > 191 && byte_in < 224) {
					byte_in = byte_in + 32;
				}*/
				send_byte(byte_in);
			}
			send_string("\r\n");
		}
		
		delay_ms(1);
	}
	
	mode=MODE_INT;
}

void int_loop() {
	while( read_dip()!=DIP_POLL_MODE ){
		delay_ms(1);
	}
	
	mode=MODE_POLL;
}

void handler_loop() {
	while(1) {
		if( mode==MODE_POLL ) {
			send_string("\r\npoll mode\r\n");
			poll_loop();
		}else{
			send_string("\r\ninteruption mode\r\n");
			int_loop();
		}
	}
}

void error() {
	send_string("\r\nerror\r\n");
	state=STATE_ERROR;
}


void handler_int() {
	u8 num;
	u8 sym;
	int array[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int i;
	int count=0;
	
	if( state==STATE_ERROR ){//i?euaai iinea ioeaee
		reset();
	}
	
	if( read_byte(&sym) ){
		switch (state) {
			case STATE_NUMBER:
				if(sym>='0' && sym<='9'){
					send_byte(sym);
					num=sym-'0';
				
					if( num > NUMBER_LIMIT-number*10 ) {//noaiao aieuoa, ?ai NUMBER_LIMIT
						error();
						return;
					}
					
					number*=10;
					number+=num;
				}else if (sym == '\r'){
					send_string("\r\nBin:");
					while (number > 0) {
						array[count] = number % 2;
						number = number / 2;
						count++;
					}
					for (i = 7; i >= 0; i--) {
						send_byte(array[i] + '0');
						led(i, array[i]);
					}
					
					send_string("\r\n");
					reset();
				}
				else{
					error();
				}
				break;
		}
	} else 
		error();
}