#pragma once

#include "common.h"
#include "../include/addresses.h"

class Timer;

SC_MODULE(Timer) {
    // Clock
    sc_in<bool> clock_in;

    // Read from bus
    sc_in<u32> data_from_bus;
    sc_in<bool> write_signal_from_bus;
    sc_in<u32> address_from_bus;

    // Write to bus
    sc_out<u32> data_to_bus;
    sc_in<bool> read_signal_from_bus;
    sc_out<bool> write_signal_to_bus;

    // Write to buffer
    sc_out<u32> data_to_buffer;
    sc_in<bool> read_signal_from_buffer;
    sc_out<bool> data_signal_to_buffer;

    SC_HAS_PROCESS(Timer);

    Timer(sc_module_name name);
    ~Timer();

    void write_from_bus();
    void write_to_bus();
    void write_to_buffer();
    void tick();

    bool decremental();
    bool working();
private:
    u32 tmr;
    u32 tconf;
    u32 tval;
};
