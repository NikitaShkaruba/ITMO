#include "mode_selector.h"

//���������� ������ INT1 ��� ������������ ������

u8 mode;

void INT1_ISR( void ) __interrupt ( 5 );

void initialize_mode_selector() {
	IT1=1;//INT1 �������� �� �����
	EX1=1;
	SetVector( 0x2013, (void *)INT1_ISR );
}

void INT1_ISR( void ) __interrupt ( 5 ){
	if( mode==MODE_COUNTER ) {
		mode=MODE_ANIMATION;
	}else{
		mode=MODE_COUNTER;
	}
}