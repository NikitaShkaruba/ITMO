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

    //Write to icconf
    sc_out<u32>   data_to_icconf;
    sc_out<bool>  write_signal_to_icconf;

    //Read from icconf
    sc_in<u32> data_from_icconf;
    sc_out<bool> read_signal_to_icconf;
    sc_in<bool> write_signal_from_icconf;

    SC_HAS_PROCESS(Bus);

    Bus(sc_module_name name);
    ~Bus();

    void write_from_core();
    void read_from_icconf();

private:
};
