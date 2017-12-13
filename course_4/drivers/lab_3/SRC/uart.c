#include "uart.h"
#include "buffer.h"
#include "led.h"
#include "handler.h"

Buffer buffer_in;
Buffer buffer_out;

bool sending_byte;

void UART_ISR( void ) __interrupt ( 4 );

void initialize_uart(u8 speed) {
	initialize_buffer(&buffer_in);
	initialize_buffer(&buffer_out);
	SetVector( 0x2023, (void *)UART_ISR );
	
	TH1       =  speed;
    TMOD     |=  0x20;
    TCON     |=  0x40;
    SCON      =  0x50;
	
	ES=0;
}

void send_byte(u8 dat) {
	ES=0;
	
	if( !sending_byte ){
		sending_byte=true;
		SBUF=dat;
	}else if( !is_buffer_full(&buffer_out) ){
		push_byte_to_buffer(&buffer_out,dat);
	}
	
	ES=1;
}

void send_string(char * str){
	ES=0;
	
	if( !sending_byte ){
		sending_byte=true;
		SBUF=*str;
		str++;
	}
	
	while( *str ) {
		if( !is_buffer_full(&buffer_out) ){
			push_byte_to_buffer(&buffer_out,*str);
			str++;
		}
	}
	
	ES=1;
}

bool read_byte(u8* dat) {
	bool is_data;

	ES=0;
	
	is_data=!is_buffer_empty(&buffer_in);
	
	if( is_data ){
		*dat=pop_byte_from_buffer(&buffer_in);
	}
	
	ES=1;
	return is_data;
}

void UART_ISR( void ) __interrupt ( 4 ) {
	u8 dat;
	
	if( TI ){
		if( is_buffer_empty(&buffer_out) ){
			sending_byte=false;
		}else{
			dat=pop_byte_from_buffer(&buffer_out);
			SBUF=dat;
		}
		
		TI=0;
	}
	
	if( RI ){
		RI=0;
		dat=SBUF;
		
		if( !is_buffer_full(&buffer_in) ){
			push_byte_to_buffer(&buffer_in,dat);
		}
	}
}

u8 poll_is_byte()  {
    return RI;
}

u8 poll_read_byte() {
    while( !RI );
    RI = 0;
    return SBUF;
}

void poll_write_byte(u8 byte_out){
	SBUF = byte_out;
    TI   = 0;
    while( !TI );
}

void poll_send_string(char * str){
    while( *str ) poll_write_byte( *str++ );
}
	