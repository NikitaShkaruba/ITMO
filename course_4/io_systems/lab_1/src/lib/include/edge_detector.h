#pragma once

#include "common.h"

class EdgeDetector;

SC_MODULE(EdgeDetector) {
    // Clock
    sc_in<bool> clock_in;

    // Read from icconf
    sc_in<u32> mode_from_icconf;

    // Read input signal
    sc_in<bool> input_signal;

    // Write to prescaler
    sc_out<bool> edge_signal_to_prescaler;

    SC_HAS_PROCESS(EdgeDetector);

    EdgeDetector(sc_module_name name);
    ~EdgeDetector();

    void tick();

private:
    bool prev;
};