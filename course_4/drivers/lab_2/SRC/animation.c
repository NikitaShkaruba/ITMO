#include "animation.h"
#include "led.h"
#include "system_timer.h"

//»спользует таймер T1 дл€ Ў»ћ

//€ркость светодиодов
u8 power=0;
//LEVEL_ON
u8 power_l1=0;
u8 power_h1=0;
//LEVEL_OFF
u8 power_l2=0;
u8 power_h2=0;

u8 level;
//величивать или уменьшать €ркость
u8 direction;
//врем€ следующего кадра
time next_frame;

const u8 LEVEL_ON=0xF0;
const u8 LEVEL_OFF=0x0F;

const u8 UP=0xFF;
const u8 DOWN=0x00;
const time FRAME_DELAY=1000;

void T1_ISR( void ) __interrupt ( 1 );

void initialize_animation() {
	TMOD|=0b00010000; //Timer1, внутренний генератор частоты, 16- бит счетчик
	SetVector( 0x201B, (void *)T1_ISR );
}

void enable_animation(){
	direction=UP;
	next_frame=get_ms()+FRAME_DELAY;
	set_power(0);
	
	level=LEVEL_ON;
	leds( level );
	
	TH1=power_h1;
	TL1=power_l1;
	
	ET1=1;       //включаем прерывание от таймера 1
	TR1=1;      //разрешаем счет таймера 1
}

void disable_animation(){
	ET1=0;
	TR1=0;
}

void set_power(u8 new_power){
	u16 power1,power2;
	
	TR1=0;//дабы не сработал T1_ISR и не записал неправильные данные
	
	power=new_power;
	power1=-(100*power+1);
	power2=-(100*(100-power)+1);
	
	power_l1=power1&0xFF;
	power_h1=power1>>8;
	
	power_l2=power2&0xFF;
	power_h2=power2>>8;
	
	TR1=1;
}

u8 get_power() {
	return power;
}

void T1_ISR( void ) __interrupt ( 1 ){
	if( level==LEVEL_ON ){
		level=LEVEL_OFF;
		leds( level );
		
		TH1=power_h2;
		TL1=power_l2;
	}else{
		level=LEVEL_ON;
		leds( level );
		
		TH1=power_h1;
		TL1=power_l1;
	}
	
	if(get_ms()>=next_frame) {//пора сменить кадр анимации
		next_frame=get_ms()+FRAME_DELAY;
		
		if( direction==UP ){
			set_power(get_power()+10);
			
			if( get_power()==100 ){
				direction=DOWN;
			}
		}else{
			set_power(get_power()-10);
					
			if( get_power()==0 ){
				direction=UP;
			}
		}
	}
}