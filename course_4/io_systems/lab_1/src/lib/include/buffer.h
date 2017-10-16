#pragma once

#include "common.h"

SC_MODULE(Buffer) {
    // Clock
    sc_in<bool> clock_in;

    // Read from icconf
    sc_in<u32> mode_from_icconf;

    // Read edge
    sc_in<bool> edge_signal_from_prescaler;

    // Read timer1
    sc_out<bool> read_signal_to_timer1;
    sc_in<u32> data_from_timer1;
    sc_in<bool> data_signal_from_timer1;

    // Read timer2
    sc_out<bool> read_signal_to_timer2;
    sc_in<u32> data_from_timer2;
    sc_in<bool> data_signal_from_timer2;

    sc_out<bool> buffer_empty_signal_to_icconf;
    sc_out<bool> buffer_full_signal_to_icconf;

    SC_HAS_PROCESS(Buffer);

    Buffer(sc_module_name name);
    ~Buffer();

    void tick();
    void read_timers();
    void buffer_empty();
    void buffer_full();

private:
    u32 mem[32];
    u32 head;
    u32 tail;
};