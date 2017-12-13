#include "handler.h"
#include "system_timer.h"
#include "max.h"
#include "uart.h"
#include "led.h"
#include "keyboard.h"

const u8 DIP_POLL_MODE=0x01;
const u8 NUMBER_LIMIT=0xFF;

//ибо константа это не константа ќ_о
#define STATE_NUMBER 0
#define STATE_ERROR 1

u8 mode;
u8 number;
u8 state;

u8 v;

u8 read_dip(){
	u8 dip;
	
	dip=read_max(EXT_LO);
	
	return dip;
}

void reset() {
	number=0;
	state=STATE_NUMBER;
}

void initialize_handler() {
	mode = MODE_TEST;
	reset();
}

void test_loop() {
	u8 byte_in;
	
	while( read_dip()!=DIP_POLL_MODE ){
		if( keyboard_read_byte(&byte_in) ){
			send_byte(byte_in);
			send_string("\r\n");
		}
		delay_ms(1);
	}
	
	mode=MODE_INT;
}

void int_loop() {
	u8 byte_in;
	
	while( read_dip()==DIP_POLL_MODE ){
		if( keyboard_read_byte(&byte_in) ){
			handler_int(byte_in);
			//send_string("\r\n");
		}
		delay_ms(1);
	}
	
	mode=MODE_TEST;
}

void handler_loop() {
	while(1) {
		if( mode==MODE_TEST ) {
			send_string("\r\ntest mode\r\n");
			test_loop();
		}else{
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
	int array[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int i;
	int count=0;
	
	switch (state) {
		case STATE_ERROR://очищаем после ошибки
			reset();
			leds(0x00);
			break;
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
			}else if( sym=='*' ) {
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
				
			}else{
				error();
			}
			break;
	}
}