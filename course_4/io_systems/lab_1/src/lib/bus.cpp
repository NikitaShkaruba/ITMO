#include "include/bus.h"

Bus::Bus(sc_module_name nm) : sc_module(nm), clock_in("clock_in"), address_in("address_in"), data_in("data_in"), data_out("data_out"), write_in("write_in"), read_in("read_in") {
  data_out.initialize(0);

  SC_METHOD(write);
  sensitive << clock_in.pos();

  SC_METHOD(read);
  sensitive << clock_in.pos();
}

Bus::~Bus() = default;

void Bus::read() {
  if (!read_in.read()) {
    return;
  }

  u32 address = (u32) address_in.read();
  data_out.write(memory[address]);
}

void Bus::write() {
  if (!write_in.read()) {
    return;
  }

  u32 address = (u32) address_in.read();
  u32 data = (u32) data_in.read();
  memory[address] = data;
}
