#include "../include/icconf.h"

ICCONF::ICCONF(sc_module_name nm) : sc_module(nm),
    clock_in("clock_in"),
    data_from_bus("data_from_bus"),
    write_signal_from_bus("write_signal_from_bus"),
    data_to_bus("data_to_bus"),
    read_signal_from_bus("read_signal_from_bus"),
    write_signal_to_bus("write_signal_to_bus")
{
    data_to_bus.initialize(0);
    write_signal_to_bus.initialize(0);

    SC_METHOD(write_from_bus);
    sensitive << clock_in.pos();

    SC_METHOD(write_to_bus);
    sensitive << clock_in.pos();

    icconf=0x24;
}

ICCONF::~ICCONF() = default;

void ICCONF::write_from_bus() {
    if( write_signal_from_bus.read() ) {
        u32 data = data_from_bus.read();

        icconf = data;
    }
}


void ICCONF::write_to_bus() {
    if( read_signal_from_bus.read() ){
        data_to_bus.write(icconf);
        write_signal_to_bus.write(1);
    }else{
        write_signal_to_bus.write(0);
    }
}