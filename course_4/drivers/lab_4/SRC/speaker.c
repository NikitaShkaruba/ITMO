#include "speaker.h"
#include "max.h"

//������ ���������� Timer0, ������� ������ � �������� 4���

bool speaker_on;

void T0_ISR( void ) __interrupt ( 2 );

void initialize_speaker(){
	SetVector( 0x200B, (void *)T0_ISR );
	TMOD|=0b00000010; //Timer0, ���������� ���������, 8 ��� �������
	ET0=1;       //�������� ���������� �� ������� 0
	TH0=-250;
}
	
void enable_speaker(){
	speaker_on=false;
	TL0=-250;
	TR0=1;      //��������� ���� ������� 0
}

void disable_speaker(){
	TR0=0;      //��������� ���� ������� 0
	
	speaker_on=false;
	write_max(ENA, 0b0100000);
}

void T0_ISR( void ) __interrupt ( 2 ){
	if( speaker_on ){
		write_max(ENA, 0b0111100);
	}else{
		write_max(ENA, 0b0100000);
	}
	
	speaker_on=!speaker_on;
}
