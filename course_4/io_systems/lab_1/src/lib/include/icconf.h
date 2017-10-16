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

    // To EdgeDetector and Prescaler
    sc_out<u32> mode_to_edge_detector;

    // To Buffer
    sc_out<u32> mode_to_buffer;

    // From buffer
    sc_in<bool> buffer_empty_signal_from_buffer;
    sc_in<bool> buffer_full_signal_from_buffer;

    SC_HAS_PROCESS(ICCONF);

    ICCONF(sc_module_name name);
    ~ICCONF();

    void write_from_bus();
    void write_to_bus();
    void buffer_empty();
    void buffer_full();

private:
    u32 icconf;
};