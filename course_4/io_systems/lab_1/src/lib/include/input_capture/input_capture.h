#pragma once

#include "systemc.h"
#include "config.h"

SC_MODULE(InputCapture) {
  // Input to capture
  sc_in<bool> input_signal;

  // Read from bus
  sc_in<int> data_in;
  sc_out<bool> read_out;
  sc_out<int> address_out;

  // Clock
  sc_in<bool> clock_in;

  SC_HAS_PROCESS(InputCapture);

  InputCapture(sc_module_name name);
  ~InputCapture();

  void setConfig();
  void tick();

private:
  bool isPassesEdgeDetector(bool input_signal);
  bool isPassesPrescaler();

  Config config;
  unsigned int scale_iteration = 0;
  bool remembered_signal = 0;
};
