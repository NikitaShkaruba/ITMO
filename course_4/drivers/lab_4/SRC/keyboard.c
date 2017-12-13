#include "keyboard.h"
#include "buffer.h"
#include "max.h"
#include "uart.h"
#include "handler.h"
#include "speaker.h"

#define KEYS_NUMBER 16
const u8 ROWS=4;
const u8 COLS=4;
const u8 PRESS_COUNT=8;//если key_count больше этой константы, клавиша нажата
const u8 RELEASE_COUNT=3;//если key_count меньше этой константы, клавиша отпущена
const u8 KEY_COUNT_LIMIT=20;
const u8 KEY_START_REPEAT_DELAY=60;//те 4мс*100=0.4сек
const u8 KEY_REPEAT_DELAY=100;//те 4мс*250=1сек
const u8 SPEAKER_TIME=100;


//Клавиатура использует SystemTimer, который сканирует колонку каждые 4 мс

__xdata Buffer key_clicks;
u8 key_count[KEYS_NUMBER];
u8 key_pressed_time[KEYS_NUMBER];
u8 key_repeat_time[KEYS_NUMBER];
char key_value[]="147*2580369#ABCD";
u8 col;
u8 prescaler;
u8 speaker;

void initialize_keyboard() {
	initialize_buffer(&key_clicks);
	col=0;
	prescaler=0;
}

bool keyboard_read_byte(u8* dat) {
	bool is_data;

	ET2=0;
	
	is_data=!is_buffer_empty(&key_clicks);
	
	if( is_data ){
		*dat=pop_byte_from_buffer(&key_clicks);
	}
	
	ET2=1;
	return is_data;
}

u8 scan_keyboard() {
	u8 scan_mask;
	u8 row_mask;
	
	scan_mask=~(1 << col);
	write_max(KB, scan_mask);
	row_mask=~(read_max(KB) & 0xF0)>>4;
	
	return row_mask;
}

void key_click(u8 key){
	speaker=1;//включаем спикер
	enable_speaker();
	
	if( !is_buffer_full(&key_clicks) ){
		push_byte_to_buffer(&key_clicks, key_value[key]);
	}
}

void scan_keyboard_int(){
	u8 row;
	u8 row_mask;
	u8 key;
	
	prescaler++;
	if( prescaler==2 ){
	
		prescaler=0;
	
		row_mask=scan_keyboard();
		
		for( row=0;row<ROWS;row++ ){
			key=col*ROWS + row;
			
			if( row_mask>>row & 1 ){//клавиша нажата
				if( key_count[key]<KEY_COUNT_LIMIT ) {
					key_count[key]++;
					
					if( key_count[key]>PRESS_COUNT && key_pressed_time[key]==0 ){//помечаем, как нажатую
						key_click(key);
						key_pressed_time[key]=1;
					}
				}
			}else{//клавиша отпущена
				if( key_count[key]>0 ) {
					key_count[key]--;
					
					if( key_count[key]<RELEASE_COUNT && key_pressed_time[key]>0 ){//помечаем как отпущенную
						key_pressed_time[key]=0;
						key_repeat_time[key]=0;
					}
				}
			}
			
			if( key_pressed_time[key]>0 ){//Клавиша помечена как нажатая
				if( key_pressed_time[key]<KEY_START_REPEAT_DELAY ){
					key_pressed_time[key]++;
				}else{//клавиша нажата уже KEY_START_REPEAT_DELAY
					key_repeat_time[key]++;
					
					if( key_repeat_time[key]==KEY_REPEAT_DELAY ) {//повторяем каждые KEY_REPEAT_DELAY
						key_click(key);
						key_repeat_time[key]=0;
					}
				}
			}
		}
		
		col++;
		
		if( col==COLS ){
			col=0;
		}
	}
	
	if( speaker>0 ){//Спикер работает
		speaker++;
		
		if(speaker==SPEAKER_TIME){
			disable_speaker();
			speaker=0;//выключаем спикер
		}
	}
}