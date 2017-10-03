#pragma once

#include "systemc.h"
#include "addresses.h"

SC_MODULE(Bus) {
  sc_in<bool>  clock_in;
  sc_in<int>   address_in;
  sc_in<int>   data_in;
  sc_out<int>  data_out;
  sc_in<bool>  write_in;
  sc_in<bool>  read_in;

  SC_HAS_PROCESS(Bus);

  Bus(sc_module_name name);
  ~Bus();

  void write();
  void read();

private:
  int memory[256];
};
