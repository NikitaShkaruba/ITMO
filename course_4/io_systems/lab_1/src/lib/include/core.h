#pragma once

#include "systemc.h"

SC_MODULE(CORE) {
  sc_in<bool> clock_in;
  sc_in<int> data_in;

  sc_out<int> address_out;
  sc_out<int> data_out;
  sc_out<bool> write_out;
  sc_out<bool> read_out;

  SC_HAS_PROCESS(CORE);

  CORE(sc_module_name nm);
  ~CORE();

  void mainThread();

  // Probably needs to be defined in other module
  void configure_input_capture(unsigned int input_capture_mode, unsigned int timers_config);

private:
  void write_to_bus(int address, int data);
  int readFromBus(int address);
};
