#include "../include/edge_detector.h"

EdgeDetector::EdgeDetector(sc_module_name nm) : sc_module(nm),
    clock_in("clock_in"),
    mode_from_icconf("mode_from_icconf"),
    input_signal("input_signal"),
    edge_signal_to_prescaler("edge_signal_to_prescaler")
{
    edge_signal_to_prescaler.initialize(0);

    SC_METHOD(tick);
    sensitive << clock_in.pos();

    prev=false;
}

EdgeDetector::~EdgeDetector() = default;

void EdgeDetector::tick() {
    bool sig=input_signal.read();
    u32 mode=mode_from_icconf.read();

    if( mode!=0x0 && prev!=sig ){
        if( mode==0x1 ) {
            edge_signal_to_prescaler.write(1);
        }else if( prev==true && sig==false && (mode==0x2 || mode==0x6 || mode==0x7)){
            edge_signal_to_prescaler.write(1);
        }else if( prev==false && sig==true && (mode==0x3 || mode==0x4 || mode==0x5)){
            edge_signal_to_prescaler.write(1);
        }else{
            edge_signal_to_prescaler.write(0);
        }
    }else{
        edge_signal_to_prescaler.write(0);
    }

    prev=sig;
}