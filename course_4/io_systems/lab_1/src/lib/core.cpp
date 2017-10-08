#include "include/core.h"
#include "include/bus/addresses.h"

using namespace std;

CORE::CORE(sc_module_name nm) : sc_module(nm), clock_in("clock_in"), bus_address_out("bus_address_out"), bus_data_in("core_data_in"), bus_data_out("core_data_out"), bus_write_out("bus_write_out"), bus_read_out("bus_read_out") {
  bus_address_out.initialize(0);
  bus_data_out.initialize(0);
  bus_write_out.initialize(0);
  bus_read_out.initialize(0);

  SC_CTHREAD(mainThread, clock_in.pos());
}

CORE::~CORE() = default;

void CORE::mainThread() {
  configure_input_capture(0x4, 0x0);

  for (int i = 0; i < 1000; i++) {
    cout << "tick" << endl;
    changeInputCaptureSignal(i % 3 == 0);
    wait();
  }

  sc_stop();
}

int CORE::readFromBus(int address) {
  int data;

  wait();
  bus_address_out.write(address);
  bus_read_out.write(1);

  wait();
  bus_read_out.write(1);

  wait();
  data = bus_data_in.read();

  cout << "CORE: READ " << endl;
  cout << "  -> address: " << hex << address << endl;
  cout << "  -> data: " << hex << data << endl;

  return data;
}

void CORE::write_to_bus(int address, int data) {
  wait();
  bus_address_out.write(address);
  bus_data_out.write(data);
  bus_write_out.write(1);

  wait();
  bus_write_out.write(0);

  cout << "CORE: WRITE " << endl;
  cout << "  -> address: " << hex << address << endl;
  cout << "  -> data: " << hex << data << endl;
}

void CORE::configure_input_capture(unsigned int input_capture_mode, unsigned int timers_config) {
  int config_bits = 0 | input_capture_mode | timers_config << 5;

  write_to_bus(BUS_ADDRESS_INPUT_CAPTURE_CONFIG, config_bits);
}

void CORE::changeInputCaptureSignal(bool signal) {
  wait();
  ic_signal_out.write(signal);

  cout << "CORE: changed input capture signal " << endl;
  cout << "  -> signal: " << hex << signal << endl;
}
