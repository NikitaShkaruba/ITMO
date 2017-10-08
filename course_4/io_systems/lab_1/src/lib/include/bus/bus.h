#pragma once

#include "systemc.h"
#include "addresses.h"

SC_MODULE(Bus) {
  sc_in<bool>  clock_in;

  sc_in<int>   core_address_in;
  sc_in<int>   core_data_in;
  sc_out<int>  core_data_out;
  sc_in<bool>  core_write_in;
  sc_in<bool>  core_read_in;

  sc_in<int>   ic_address_in;
  sc_out<int>  ic_data_out;
  sc_in<bool>  ic_read_in;

  SC_HAS_PROCESS(Bus);

  Bus(sc_module_name name);
  ~Bus();

  void writeFromCore();
  void readFromCore();
  void readFromIC();

private:
  int memory[256];
};
