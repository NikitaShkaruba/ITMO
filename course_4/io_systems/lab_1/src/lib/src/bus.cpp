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
    write_signal_from_icconf("write_signal_from_icconf"),

    data_from_timer1("data_from_timer1"),
    read_signal_to_timer1("read_signal_to_timer1"),
    write_signal_from_timer1("write_signal_from_timer1"),
    address_to_timer1("address_to_timer1"),
    data_to_timer1("data_to_timer1"),
    write_signal_to_timer1("write_signal_to_timer1"),

    data_from_timer2("data_from_timer2"),
    read_signal_to_timer2("read_signal_to_timer2"),
    write_signal_from_timer2("write_signal_from_timer2"),
    address_to_timer2("address_to_timer2"),
    data_to_timer2("data_to_timer2"),
    write_signal_to_timer2("write_signal_to_timer2")
{
    data_to_core.initialize(0);

    //icconf
    write_signal_to_icconf.initialize(0);
    read_signal_to_icconf.initialize(0);

    //timer1
    write_signal_to_timer1.initialize(0);
    read_signal_to_timer1.initialize(0);
    address_to_timer1.initialize(0);

    //timer2
    write_signal_to_timer2.initialize(0);
    read_signal_to_timer2.initialize(0);
    address_to_timer2.initialize(0);

    SC_METHOD(write_to_icconf);
    sensitive << clock_in.pos();

    SC_METHOD(read_from_icconf);
    sensitive << clock_in.pos();

    SC_METHOD(write_to_timer1);
    sensitive << clock_in.pos();

    SC_METHOD(read_from_timer1);
    sensitive << clock_in.pos();

    SC_METHOD(write_to_timer2);
    sensitive << clock_in.pos();

    SC_METHOD(read_from_timer2);
    sensitive << clock_in.pos();
}

Bus::~Bus() = default;

//ICCONF
void Bus::write_to_icconf() {
    if( write_signal_from_core.read() && address_from_core.read()==BUS_ADDRESS_ICCONF ){
        u32 data=data_from_core.read();

        write_signal_to_icconf.write(1);
        data_to_icconf.write(data);
    }else{
        write_signal_to_icconf.write(0);
    }
}

void Bus::read_from_icconf() {
    if( read_signal_from_core.read() && address_from_core.read()==BUS_ADDRESS_ICCONF ){
        read_signal_to_icconf.write(1);
    }else{
        read_signal_to_icconf.write(0);
    }

    if( write_signal_from_icconf.read() ){
        u32 data=data_from_icconf.read();
        data_to_core.write(data);
    }
}

//TIMER1
void Bus::write_to_timer1() {
    if( write_signal_from_core.read() ){
        u32 address=address_from_core.read();

        if( address==BUS_ADDRESS_TVAL1 || address==BUS_ADDRESS_TMR1 || address==BUS_ADDRESS_TCONF1 ){
            u32 data=data_from_core.read();
            write_signal_to_timer1.write(1);
            data_to_timer1.write(data);
            address_to_timer1.write(address);
        }else{
            write_signal_to_timer1.write(0);
        }
    }else{
        write_signal_to_timer1.write(0);
    }
}

void Bus::read_from_timer1() {
    if( read_signal_from_core.read() ){
        u32 address=address_from_core.read();

        if( address==BUS_ADDRESS_TVAL1 || address==BUS_ADDRESS_TMR1 || address==BUS_ADDRESS_TCONF1 ){
            read_signal_to_timer1.write(1);
            address_to_timer1.write(address);
        }else{
            read_signal_to_timer1.write(0);
        }
    }else{
        read_signal_to_timer1.write(0);
    }

    if( write_signal_from_timer1.read() ){
        u32 data=data_from_timer1.read();
        data_to_core.write(data);
    }
}

//timer2
void Bus::write_to_timer2() {
    if( write_signal_from_core.read() ){
        u32 address=address_from_core.read();

        if( address==BUS_ADDRESS_TVAL2 || address==BUS_ADDRESS_TMR2 || address==BUS_ADDRESS_TCONF2 ){
            u32 data=data_from_core.read();
            write_signal_to_timer2.write(1);
            data_to_timer2.write(data);
            address_to_timer2.write(address-BUS_ADDRESS_TMR2);
        }else{
            write_signal_to_timer2.write(0);
        }
    }else{
        write_signal_to_timer2.write(0);
    }
}

void Bus::read_from_timer2() {
    if( read_signal_from_core.read() ){
        u32 address=address_from_core.read();

        if( address==BUS_ADDRESS_TVAL2 || address==BUS_ADDRESS_TMR2 || address==BUS_ADDRESS_TCONF2 ){
            read_signal_to_timer2.write(1);
            address_to_timer2.write(address-BUS_ADDRESS_TMR2);
        }else{
            read_signal_to_timer2.write(0);
        }
    }else{
        read_signal_to_timer2.write(0);
    }

    if( write_signal_from_timer2.read() ){
        u32 data=data_from_timer2.read();
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