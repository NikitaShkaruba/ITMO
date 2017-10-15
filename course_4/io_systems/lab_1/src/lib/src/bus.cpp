#include "../include/bus.h"

Bus::Bus(sc_module_name nm) : sc_module(nm) {
  core_data_out.initialize(0);

  SC_METHOD(write_from_core);
  sensitive << clock_in.pos();

  //SC_METHOD(readFromCore);
  //sensitive << clock_in.pos();

  //SC_METHOD(readFromIC);
  //sensitive << clock_in.pos();
}

Bus::~Bus() = default;

void Bus::write_from_core() {
  if( write_signal_from_core.read() ){
    u32 address=address_from_core.read();
    u32 data=data_from_core.read();

    switch (address) {
      case BUS_ADDRESS_ICCONF:
        write_signal_to_icconf.write(1);
        data_to_icconf.write(data);

        break;
    }
  }
}

/*
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

*/