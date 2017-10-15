#pragma once

#include "common.h"

SC_MODULE(ICCONF) {
    // Clock
    sc_in<bool> clock_in;

    // Read from bus
    sc_in<u32> data_from_bus;
    sc_in<bool> write_signal_from_bus;

    // Write to bus
    sc_out<u32> data_to_bus;
    sc_in<bool> read_signal_from_bus;
    sc_out<bool> write_signal_to_bus;

    SC_HAS_PROCESS(ICCONF);

    ICCONF(sc_module_name name);
    ~ICCONF();

    void write_from_bus();
    void write_to_bus();

private:
    u32 icconf;
};