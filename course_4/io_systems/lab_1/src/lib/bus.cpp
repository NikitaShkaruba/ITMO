#include "include/bus/bus.h"

Bus::Bus(sc_module_name nm) : sc_module(nm) {
  core_data_out.initialize(0);

  SC_METHOD(writeFromCore);
  sensitive << clock_in.pos();

  SC_METHOD(readFromCore);
  sensitive << clock_in.pos();

  SC_METHOD(readFromIC);
  sensitive << clock_in.pos();
}

Bus::~Bus() = default;

void Bus::readFromCore() {
  if (!core_read_in.read()) {
    return;
  }

  unsigned int address = (unsigned int) core_address_in.read();
  core_data_out.write(memory[address]);
}

void Bus::writeFromCore() {
  if (!core_write_in.read()) {
    return;
  }

  unsigned int address = (unsigned int) core_address_in.read();
  unsigned int data = (unsigned int) core_data_in.read();
  memory[address] = data;
}

void Bus::readFromIC() {
  if (!ic_read_in.read()) {
    return;
  }

  unsigned int address = (unsigned int) ic_address_in.read();
  ic_data_out.write(memory[address]);
}
