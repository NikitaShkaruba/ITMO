#pragma once

#include "common.h"
#include "addresses.h"

SC_MODULE(Bus) {
    sc_in<bool>  clock_in;

    //Write from core
    sc_in<u32>   address_from_core;
    sc_in<u32>   data_from_core;
    sc_in<bool>  write_signal_from_core;

    //Write to core
    sc_out<u32>  data_to_core;
    sc_in<bool>  read_signal_from_core;

    //ICCONF
    //Write
    sc_out<u32>   data_to_icconf;
    sc_out<bool>  write_signal_to_icconf;

    //Read
    sc_in<u32> data_from_icconf;
    sc_out<bool> read_signal_to_icconf;
    sc_in<bool> write_signal_from_icconf;

    //TIMER1
    //Write
    sc_out<u32>   data_to_timer1;
    sc_out<bool>  write_signal_to_timer1;

    //Read
    sc_in<u32> data_from_timer1;
    sc_out<bool> read_signal_to_timer1;
    sc_in<bool> write_signal_from_timer1;
    sc_out<u32> address_to_timer1;

    SC_HAS_PROCESS(Bus);

    Bus(sc_module_name name);
    ~Bus();

    void write_to_icconf();
    void read_from_icconf();

    void write_to_timer1();
    void read_from_timer1();

private:
};
