#ifndef _MIPS32_H
#define _MIPS32_H

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

private:
  void write_to_bus(int address, int data);
  int read_from_bus(int address);
};


#endif
