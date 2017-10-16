#pragma once

#include "common.h"

SC_MODULE(Prescaler) {
    // Clock
    sc_in<bool> clock_in;

    // Read from icconf
    sc_in<u32> mode_from_icconf;

    // Read from prescaler
    sc_in<bool> edge_signal_from_edge_detector;

    // Write to prescaler
    //sc_out<bool> edge_signal_to_prescaler;

    SC_HAS_PROCESS(Prescaler);

    Prescaler(sc_module_name name);
    ~Prescaler();

    void tick();

private:
    u32 counter;
};