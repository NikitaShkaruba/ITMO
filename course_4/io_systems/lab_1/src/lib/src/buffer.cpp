#include "../include/buffer.h"

const u32 BUFFER_LEN=32;

Buffer::Buffer(sc_module_name nm) : sc_module(nm),
    clock_in("clock_in"),
    mode_from_icconf("mode_from_icconf"),
    edge_signal_from_prescaler("edge_signal_from_prescaler"),
    read_signal_to_timer1("read_signal_to_timer1"),
    data_from_timer1("data_from_timer1"),
    data_signal_from_timer1("data_signal_from_timer1"),
    read_signal_to_timer2("read_signal_to_timer2"),
    data_from_timer2("data_from_timer2"),
    data_signal_from_timer2("data_signal_from_timer2,"),
    buffer_empty_signal_to_icconf("buffer_empty_signal_to_icconf"),
    buffer_full_signal_to_icconf("buffer_full_signal_to_icconf")
{
    read_signal_to_timer1.initialize(0);
    read_signal_to_timer2.initialize(0);
    buffer_empty_signal_to_icconf.initialize(0);
    buffer_full_signal_to_icconf.initialize(0);

    SC_METHOD(tick);
    sensitive << clock_in.pos();

    SC_METHOD(read_timers);
    sensitive << clock_in.pos();

    SC_METHOD(buffer_empty);
    sensitive << clock_in.pos();

    SC_METHOD(buffer_full);
    sensitive << clock_in.pos();

    head=0;
    tail=0;
}

Buffer::~Buffer() = default;

void Buffer::tick() {
    if( edge_signal_from_prescaler.read() ){
        printf("EDGE\n");
        u32 mode=mode_from_icconf.read();

        if( mode==1 ) {
            read_signal_to_timer1.write(1);
        }else if( mode==3) {
            read_signal_to_timer1.write(1);
        }else{
            read_signal_to_timer1.write(0);
        }

        if( mode==2 ) {
            read_signal_to_timer2.write(1);
        }else if( mode==3) {
            read_signal_to_timer2.write(1);
        }else{
            read_signal_to_timer2.write(0);
        }
    }else{
        read_signal_to_timer1.write(0);
        read_signal_to_timer2.write(0);
    }
}

void Buffer::read_timers() {
    u32 mode=mode_from_icconf.read();

    if( mode==1 ){
        if( data_signal_from_timer1.read() ){
            u32 data=data_from_timer1.read();

            printf("data1 %d\n",data);
        }
    }else if( mode==2 ){
        if( data_signal_from_timer2.read() ){
            u32 data=data_from_timer2.read();

            printf("data2 %d\n",data);
        }
    }else if( mode==3 ){
        if( data_signal_from_timer1.read() && data_signal_from_timer2.read() ){
            u32 data1=data_from_timer1.read();
            u32 data2=data_from_timer2.read();

            u32 data=data1<<16 | (data2&0xFFFF);

            printf("data3 %d\n",data);
        }
    }
}

void Buffer::buffer_empty() {
    if( tail==head ) {
        buffer_empty_signal_to_icconf.write(1);
    }else{
        buffer_empty_signal_to_icconf.write(0);
    }
}

void Buffer::buffer_full() {
    if( head==0 && tail==(BUFFER_LEN-1) ){
        buffer_full_signal_to_icconf.write(1);
    }else if( tail<head ) {
        buffer_full_signal_to_icconf.write(1);
    }else{
        buffer_full_signal_to_icconf.write(0);
    }
}