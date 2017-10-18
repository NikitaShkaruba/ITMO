#ifndef __MAX__H
#define __MAX__H


//Названия регистров
#define KB          0x0
#define DATA_IND    0x1
#define EXT_LO      0x2
#define EXT_HI      0x3
#define ENA         0x4
#define C_IND       0x6
#define SV          0x7


void write_max( unsigned char xdata *regnum, unsigned char val );
unsigned char read_max( unsigned char xdata *regnum );

#endif //__MAX__H
