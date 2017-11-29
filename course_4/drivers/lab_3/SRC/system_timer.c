#include "system_timer.h"

void delay_ms ( unsigned long ms )
{
volatile unsigned long i, j;
    for( j = 0; j < ms; j++ )
    {
        for( i = 0; i < 50; i++ );
    }
}
