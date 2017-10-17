#pragma once

#include "common.h"

class CORE;

SC_MODULE(CORE) {
    sc_in<bool> clock_in;

    //Write to bus
    sc_out<u32> data_to_bus;
    sc_out<u32> address_to_bus;
    sc_out<bool> write_signal_to_bus;

    //Read from bus
    sc_in<u32> data_from_bus;
    sc_out<bool> read_signal_to_bus;

    sc_out<bool> signal_to_edge_detector;


    SC_HAS_PROCESS(CORE);

    CORE(sc_module_name nm);
    ~CORE();

    void main_thread();

  // Probably needs to be defined in other module
  //void configure_input_capture(unsigned int input_capture_mode, unsigned int timers_config);
  //void changeInputCaptureSignal(bool signal);

private:
  void write_to_bus(u32 address, u32 data);
  u32 read_from_bus(u32 address);
  void write_to_ins(bool signal);

  void test_bus();
  void test_timer();
  void test_timers();
  void test_system();

  void check_if_signal_periodic();
};
