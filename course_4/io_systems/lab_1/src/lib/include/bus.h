#pragma once

#include "common.h"
#include "addresses.h"

SC_MODULE(Bus) {
  sc_in<bool>  clock_in;

  sc_in<u32>   address_from_core;
  sc_in<u32>   data_from_core;
  sc_in<bool>  write_signal_from_core;

  sc_out<int>  core_data_out;
  sc_in<bool>  core_read_in;

  sc_out<u32>   data_to_icconf;
  //sc_out<int>  ic_data_out;
  sc_out<bool>  write_signal_to_icconf;

  SC_HAS_PROCESS(Bus);

  Bus(sc_module_name name);
  ~Bus();

  void write_from_core();
  //void readFromCore();
  //void readFromIC();

private:
};
