#include "include/core.h"
#include "include/addresses.h"

using namespace std;

CORE::CORE(sc_module_name nm) : sc_module(nm), clock_in("clock_in"), address_out("address_out"), data_in("data_in"), data_out("data_out"), write_out("write_out"), read_out("read_out") {
  address_out.initialize(0);
  data_out.initialize(0);
  write_out.initialize(0);
  read_out.initialize(0);

  SC_CTHREAD(mainThread, clock_in.pos());
}

CORE::~CORE() = default;

void CORE::mainThread() {
  write_to_bus(BUS_ADDRESS_INPUT_CAPTURE_CONFIG, 0x3);
  read_from_bus(BUS_ADDRESS_INPUT_CAPTURE_CONFIG);

  sc_stop();
}

int CORE::read_from_bus(int address) {
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
