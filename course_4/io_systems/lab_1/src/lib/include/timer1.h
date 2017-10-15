#pragma once

#include "common.h"

SC_MODULE(Timer1) {
  // Input to capture
    sc_in<bool> input_signal;

    // Read from bus
    sc_in<u32> data_in;
    //sc_out<bool> read_out;
    //sc_out<u32> address_out;

    // Clock
    sc_in<bool> clock_in;

    SC_HAS_PROCESS(Timer1);

    Timer1(sc_module_name name);
    ~Timer1();

    void tick();
    bool decremental();
    bool working();

private:
    u32 tmr;
    u32 tconf;
    u32 tval;
};
