#include "../include/core.h"
#include "../include/addresses.h"

using namespace std;

CORE::CORE(sc_module_name nm) : sc_module(nm),
    clock_in("clock_in"),
    data_to_bus("data_to_bus"),
    address_to_bus("address_to_bus"),
    write_signal_to_bus("write_signal_to_bus"),
    data_from_bus("data_from_bus"),
    read_signal_to_bus("read_signal_to_bus")
{
    //bus_address_out.initialize(0);
    //bus_data_out.initialize(0);
    //bus_write_out.initialize(0);
    //bus_read_out.initialize(0);
    data_to_bus.initialize(0);
    address_to_bus.initialize(0);
    write_signal_to_bus.initialize(0);

    read_signal_to_bus.initialize(0);

    SC_CTHREAD(main_thread, clock_in.pos());
}

CORE::~CORE() = default;

void CORE::main_thread() {
  /*
  configure_input_capture(0x4, 0x0);

  for (int i = 0; i < 1000; i++) {
    cout << "tick" << endl;
    changeInputCaptureSignal(i % 3 == 0);
    wait();
  }
  */


    write_to_bus(BUS_ADDRESS_ICCONF,0x43);
    read_from_bus(BUS_ADDRESS_ICCONF);

    sc_stop();
}

void CORE::write_to_bus(u32 address, u32 data) {
    //wait();
    printf("==0==\n");
    address_to_bus.write(address);
    data_to_bus.write(data);
    write_signal_to_bus.write(1);
    wait();
    printf("==1==\n");

    write_signal_to_bus.write(0);
    wait();
    printf("==2==\n");

    cout << "CORE: WRITE " << endl;
    cout << "  -> address: " << hex << address << endl;
    cout << "  -> data: " << hex << data << endl;
}

u32 CORE::read_from_bus(u32 address) {
    u32 data;

    printf("==0==\n");
    address_to_bus.write(address);
    read_signal_to_bus.write(1);
    wait();

    printf("==1==\n");
    read_signal_to_bus.write(0);
    wait();

    printf("==2==\n");
    wait();

    printf("==3==\n");
    wait();

    printf("==4==\n");
    wait();

    printf("read\n");
    data = data_from_bus.read();
    wait();

    printf("==3==\n");

    cout << "CORE: READ " << endl;
    cout << "  -> address: " << hex << address << endl;
    cout << "  -> data: " << hex << data << endl;

    return data;
}

/*

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
*/