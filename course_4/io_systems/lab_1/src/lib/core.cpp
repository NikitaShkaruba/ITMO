#include "include/core.h"
#include "include/bus/addresses.h"

using namespace std;

CORE::CORE(sc_module_name nm) : sc_module(nm), clock_in("clock_in"), address_out("address_out"), data_in("core_data_in"), data_out("core_data_out"), write_out("write_out"), read_out("read_out") {
  address_out.initialize(0);
  data_out.initialize(0);
  write_out.initialize(0);
  read_out.initialize(0);

  SC_CTHREAD(mainThread, clock_in.pos());
}

CORE::~CORE() = default;

void CORE::mainThread() {
  configure_input_capture(0x5, 0x3);

  for (int i = 0; i < 1000; i++) {
    cout << "tick" << endl;
    wait();
  }

  sc_stop();
}

int CORE::readFromBus(int address) {
  int data;

  wait();
  address_out.write(address);
  read_out.write(1);

  wait();
  read_out.write(1);

  wait();
  data = data_in.read();

  cout << "CORE: READ " << endl;
  cout << "  -> address: " << hex << address << endl;
  cout << "  -> data: " << hex << data << endl;

  return data;
}

void CORE::write_to_bus(int address, int data) {
  wait();
  address_out.write(address);
  data_out.write(data);
  write_out.write(1);

  wait();
  write_out.write(0);

  cout << "CORE: WRITE " << endl;
  cout << "  -> address: " << hex << address << endl;
  cout << "  -> data: " << hex << data << endl;
}

void CORE::configure_input_capture(unsigned int input_capture_mode, unsigned int timers_config) {
  int config_bits = 0 | input_capture_mode | timers_config << 5;

  write_to_bus(BUS_ADDRESS_INPUT_CAPTURE_CONFIG, config_bits);
}
