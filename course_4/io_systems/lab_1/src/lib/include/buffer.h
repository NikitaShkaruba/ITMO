#pragma once

#include "common.h"

class Buffer;

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

    // Write to bus
    sc_out<u32> data_to_bus;
    sc_in<bool> read_signal_from_bus;
    sc_out<bool> write_signal_to_bus;

    SC_HAS_PROCESS(Buffer);

    Buffer(sc_module_name name);
    ~Buffer();

    void tick();
    void read_timers();
    void buffer_empty();
    void buffer_full();
    void write_to_bus();

private:
    bool is_full();
    bool is_empty();
    void push(u32 data);
    u32 pop();

    u32 mem[32];
    u32 head;
    u32 tail;
};