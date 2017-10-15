
#include "../include/timer1.h"

Timer1::Timer1(sc_module_name nm) : sc_module(nm) {
    //core_data_out.initialize(0);

    SC_METHOD(tick);
    sensitive << clock_in.pos();

    tmr=0;
    tval=0;
    tconf=0;
}

Timer1::~Timer1() = default;

void Timer1::tick() {
    if( working() ){
        if( decremental() ){
            tval--;

            if( tval==0 ) {
                tval=tmr;
            }
        }else{
            tval++;

            if( tval==tmr ) {
                tval=0;
            }
        }
    }
}

bool Timer1::decremental() {
    return tconf & 0x1 > 0;
}

bool Timer1::working() {
    return tconf & 0x2 > 0;
}
