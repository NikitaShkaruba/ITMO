#include "../include/bus.h"

Bus::Bus(sc_module_name nm) : sc_module(nm),
    clock_in("clock_in"),
    address_from_core("address_from_core"),
    data_from_core("data_from_core"),
    write_signal_from_core("write_signal_from_core"),
    data_to_core("data_to_core"),
    read_signal_from_core("read_signal_from_core"),
    data_to_icconf("data_to_icconf"),
    write_signal_to_icconf("write_signal_to_icconf"),
    data_from_icconf("data_from_icconf"),
    read_signal_to_icconf("read_signal_to_icconf"),
    write_signal_from_icconf("write_signal_from_icconf")
{
    write_signal_to_icconf.initialize(0);
    read_signal_to_icconf.initialize(0);
    data_to_core.initialize(0);

    SC_METHOD(write_from_core);
    sensitive << clock_in.pos();

    SC_METHOD(write_to_core);
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

                printf("BUS_WRITE%d\n");

                break;
        }
    }else{
        write_signal_to_icconf.write(0);
    }
}

void Bus::read_from_icconf() {
    if( read_signal_from_core.read() && address_from_core.read()==){
        u32 address=address_from_core.read();

        printf("lol\n");

        switch (address) {
            case BUS_ADDRESS_ICCONF:
                read_signal_to_icconf.write(1);
                printf("read_signal_to_icconf\n");

                break;
        }
    }else{
        read_signal_to_icconf.write(0);
    }

    if( write_signal_from_icconf.read() ){
        u32 data=data_from_icconf.read();
        printf("BUS READ FROM ICCONF%d\n",data);
        data_to_core.write(data);
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