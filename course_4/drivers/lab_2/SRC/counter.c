#include "counter.h"

//Использует таймер T0 как счетчик

void initialize_counter() {
	TMOD|=0b00000100;//режим счетчика для таймера0
	TH0=TL0=0;//обнулим счетчик
	TR0=1;      //разрешаем счет таймера 0
}

u8 get_count() {
	return TL0;
}