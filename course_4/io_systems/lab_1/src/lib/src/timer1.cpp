
#include "../include/timer1.h"

Timer::Timer(sc_module_name nm) : sc_module(nm),
    clock_in("clock_in"),
    data_from_bus("data_from_bus"),
    write_signal_from_bus("write_signal_from_bus"),
    address_from_bus("address_from_bus"),
    data_to_bus("data_to_bus"),
    read_signal_from_bus("read_signal_from_bus"),
    write_signal_to_bus("write_signal_to_bus"),
    data_to_buffer("data_to_buffer"),
    read_signal_from_buffer("read_signal_from_buffer"),
    data_signal_to_buffer("data_signal_to_buffer")
{
    data_to_bus.initialize(0);
    write_signal_to_bus.initialize(0);

    data_to_buffer.initialize(0);
    data_signal_to_buffer.initialize(0);

    SC_METHOD(write_from_bus);
    sensitive << clock_in.pos();

    SC_METHOD(write_to_bus);
    sensitive << clock_in.pos();

    SC_METHOD(write_to_buffer);
    sensitive << clock_in.pos();

    SC_METHOD(tick);
    sensitive << clock_in.pos();

    tmr=0;
    tval=0;
    tconf=0;
}

Timer::~Timer() = default;

void Timer::write_from_bus() {
    if( write_signal_from_bus.read() ) {
        u32 data = data_from_bus.read();
        u32 address=address_from_bus.read();

        switch (address) {
            case BUS_ADDRESS_TMR1:
                tmr=data; break;
            case BUS_ADDRESS_TVAL1:
                tval=data; break;
            case BUS_ADDRESS_TCONF1:
                tconf=data; break;
        }
    }
}


void Timer::write_to_bus() {
    if( read_signal_from_bus.read() ){
        u32 address=address_from_bus.read();

        switch (address) {
            case BUS_ADDRESS_TMR1:
                data_to_bus.write(tmr); break;
            case BUS_ADDRESS_TVAL1:
                data_to_bus.write(tval); break;
            case BUS_ADDRESS_TCONF1:
                data_to_bus.write(tconf); break;
        }

        write_signal_to_bus.write(1);
    }else{
        write_signal_to_bus.write(0);
    }
}

void Timer::write_to_buffer() {
    if( read_signal_from_buffer.read() ){
        data_to_buffer.write(tval);

        data_signal_to_buffer.write(1);
    }else{
        data_signal_to_buffer.write(0);
    }
}

void Timer::tick() {
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

bool Timer::decremental() {
    return (tconf & 0x1) > 0;
}

bool Timer::working() {
    return (tconf & 0x2) > 0;
}

