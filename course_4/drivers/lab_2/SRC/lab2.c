#include "aduc812.h"
#include "led.h"
#include "animation.h"
#include "mode_selector.h"
#include "counter.h"
#include "system_timer.h"


void delay ( unsigned long ms );

void main( void ) {
	initialize_system_timer();
	initialize_mode_selector();
	initialize_animation();
	initialize_counter();
	
	//enable_animation();
	
	//leds( 0xFF );
	
	//mode=MODE_ANIMATION;
	//enable_animation();
	mode=MODE_COUNTER;
	
	EA=1;
	
	while(1){
		if( mode==MODE_ANIMATION ){
			enable_animation();
			
			while( mode==MODE_ANIMATION ){
				delay_ms(1);
			}
			
			disable_animation();
		}
		
		if( mode==MODE_COUNTER ){
			while( mode==MODE_COUNTER ){
				leds( get_count() );
				delay_ms(1);
			}
		}
	}
}

/*
// Задержка на заданное количество мс
void delay ( unsigned long ms )
{
volatile unsigned long i, j;

    for( j = 0; j < ms; j++ )
    {
        for( i = 0; i < 50; i++ );
    }

    
}

void main( void )
{
int i;

    for( i = 0; i < 3; i++ )
    {

        leds( 0xFF );  delay( 100 );
        leds( 0x00 );  delay( 100 );
    }


    led( 0, 1 ); delay( 300 );
    led( 1, 1 ); delay( 300 );
    led( 2, 1 ); delay( 300 );
    led( 3, 1 ); delay( 300 );
    led( 4, 1 ); delay( 300 );
    led( 5, 1 ); delay( 300 );
    led( 6, 1 ); delay( 300 );
    led( 7, 1 ); delay( 300 );

    delay( 1000 );


    for( i = 0; i < 3; i++ )
    {

        leds( 0xFF );  delay( 100 );
        leds( 0x00 );  delay( 100 );
    }


    while( 1 )
    {
        leds( 0x55 );  delay( 500 );

        leds( 0xAA );  delay( 500 );
    }
}    
*/