#include "system_timer.h"
#include "led.h"

//Использует таймер T2 как системный таймер

u16 cnt=0;
u8 levelo;

const u8 LEVEL_ON=0xF0;
const u8 LEVEL_OFF=0x0F;

time cur_ms;

void T2_ISR( void ) __interrupt ( 2 );

void initialize_system_timer() {
	cur_ms=0;
	cnt=0;
	
	SetVector( 0x202B, (void *)T2_ISR );

	levelo=LEVEL_ON;
	leds( levelo );
	
	//вызывать прерывание каждую миллисекунду
	TH2=(-1000)>>8;0;
	TL2=(-1000)&0xFF;
	RCAP2H=(-1000)>>8;
	RCAP2L=(-1000)&0xFF;
	
	ET2=1;       //включаем прерывание от таймера 2
	TR2=1;      //разрешаем счет таймера 2
}

time get_ms(void){
	return cur_ms;
}

time get_ms_after(time t0){
	return cur_ms-t0;
}

void delay_ms(time t){
	time now=get_ms();
	
	while( get_ms_after(now)<t){}
}

void T2_ISR( void ) __interrupt ( 2 ){
	cur_ms++;
}
