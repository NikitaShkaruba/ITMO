#include "handler.h"
#include "system_timer.h"
#include "max.h"
#include "uart.h"
#include "led.h"

const u8 DIP_POLL_MODE=0x01;
const u8 NUMBER_LIMIT=0xFF;

//ибо константа это не константа О_о
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
	
	while( read_dip()==DIP_POLL_MODE ){
		if( poll_is_byte() ){// Прием байта
			byte_in=poll_read_byte();
		
			for( i=byte_in;i<='9';i++ ){
				poll_write_byte(i);
			}
			
			poll_write_byte('\r');
			poll_write_byte('\n');
		}
	}
	
	mode=MODE_INT;
}

void int_loop() {
	u8 byte_in;
	
	while( read_dip()!=DIP_POLL_MODE ){
		if( read_byte(&byte_in) ){
			handler_int(byte_in);
		}
		delay_ms(1);
	}
	
	mode=MODE_POLL;
}

void handler_loop() {
	while(1) {
		if( mode==MODE_POLL ) {
			ES=0;
			poll_send_string("\r\npoll mode\r\n");
			poll_loop();
		}else{
			ES=1;
			send_string("\r\ninteruption mode\r\n");
			int_loop();
		}
	}
}

void error() {
	send_string("\r\nerror\r\n");
	leds(0xAA);
	state=STATE_ERROR;
}

u8 to_hex(u8 val) {
	if( val>9 ) {
		return 'A'+val-10;
	}
	
	return '0'+val;
}

void handler_int(u8 sym) {
	u8 num;
	
	if( state==STATE_ERROR ){//очищаем после ошибки
		reset();
		leds(0x00);
	}
	
	switch (state) {
		case STATE_NUMBER:
			if(sym>='0' && sym<='9'){
				send_byte(sym);
				num=sym-'0';
			
				if( num > NUMBER_LIMIT-number*10 ) {//станет больше, чем NUMBER_LIMIT
					error();
					return;
				}
				
				number*=10;
				number+=num;
			}else if( sym=='r' ) {
				state=STATE_CR;
			}else{
				error();
			}
			
			break;
		case STATE_CR:
			if( sym=='n' ) {
				send_string("\r\nHex:");
				send_byte(to_hex(number>>4));
				send_byte(to_hex(number&0x0F));
				send_string("\r\n");
				reset();
			}else{
				error();
			}
			
			break;
	}
}