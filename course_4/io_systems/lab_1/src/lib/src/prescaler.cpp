#include "../include/prescaler.h"

Prescaler::Prescaler(sc_module_name nm) : sc_module(nm),
    clock_in("clock_in"),
    mode_from_icconf("mode_from_icconf"),
    edge_signal_from_edge_detector("edge_signal_from_edge_detector"),
    edge_signal_to_buffer("edge_signal_to_buffer")
{
    edge_signal_to_buffer.initialize(0);

    SC_METHOD(tick);
    sensitive << clock_in.pos();

    counter=0;
}

Prescaler::~Prescaler() = default;

void Prescaler::tick() {
    if( edge_signal_from_edge_detector.read() ){
        u32 mode=mode_from_icconf.read();

        counter+=1;

        if( mode<=0x3 ){
            counter=0;
            edge_signal_to_buffer.write(1);
            return;
        }else if((mode==0x4 || mode==0x6) && counter==4 ){
            counter=0;
            edge_signal_to_buffer.write(1);
            return;
        }else if((mode==0x5 || mode==0x7) && counter==16){
            counter=0;
            edge_signal_to_buffer.write(1);
            return;
        }
    }

    edge_signal_to_buffer.write(0);
}