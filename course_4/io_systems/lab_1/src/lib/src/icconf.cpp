#include "../include/icconf.h"

ICCONF::ICCONF(sc_module_name nm) : sc_module(nm),
    clock_in("icconf_clock_in"),
    data_from_bus("icconf_data_from_bus"),
    write_signal_from_bus("icconf_write_signal_from_bus"),
    data_to_bus("icconf_data_to_bus"),
    read_signal_from_bus("icconf_read_signal_from_bus"),
    write_signal_to_bus("icconf_write_signal_to_bus"),

    mode_to_edge_detector("mode_to_edge_detector"),
    mode_to_buffer("mode_to_buffer"),
    buffer_empty_signal_from_buffer("buffer_empty_signal_from_buffer"),
    buffer_full_signal_from_buffer("buffer_full_signal_from_buffer")
{
    data_to_bus.initialize(0);
    write_signal_to_bus.initialize(0);

    mode_to_edge_detector.initialize(0);
    mode_to_buffer.initialize(0);

    SC_METHOD(write_from_bus);
    sensitive << clock_in.pos();

    SC_METHOD(write_to_bus);
    sensitive << clock_in.pos();

    SC_METHOD(buffer_empty);
    sensitive << clock_in.pos();

    SC_METHOD(buffer_full);
    sensitive << clock_in.pos();

    icconf=0x24;
}

ICCONF::~ICCONF() = default;

void ICCONF::write_from_bus() {
    if( write_signal_from_bus.read() ) {
        u32 data = data_from_bus.read();

        icconf = data | (icconf & 0x18);//не затрагиваем биты, выставляемые буффером
        printf("icconf %d\n",icconf & 0x08);
        mode_to_edge_detector.write(icconf & 0x7);
        mode_to_buffer.write(icconf >> 5);

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

void ICCONF::buffer_empty() {
    if( buffer_empty_signal_from_buffer.read() ){
        icconf |=0x08;
    }else{
        icconf = icconf & (~0x08);//затрагиваем только бит, выставляемый буффером
    }
}

void ICCONF::buffer_full() {
    if( buffer_full_signal_from_buffer.read() ){
        icconf |=0x10;
    }else{
        icconf = icconf & (~0x10);//затрагиваем только бит, выставляемый буффером
    }
}