#include "include/icconf.h"

ICCONF::ICCONF(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    icconf_wr_i("icconf_wr_i"),
    icconf_rd_i("icconf_rd_i"),

    data_bo("data_bo"),
    data_bi("data_bi")
{
    data_bo.initialize(0x11);

    SC_METHOD(bus_write);
    sensitive << clk_i.pos();

    SC_METHOD(bus_read);
    sensitive << clk_i.pos();

}

ICCONF::~ICCONF(){
    reg=0xff;
    ret_data=false;
}

void ICCONF::bus_write(){
    //cout << "icconf_w" << endl;
    if(icconf_wr_i.read()) {
        reg = data_bi.read();
        cout << "icconf_write " << reg << endl;
    }
}

void ICCONF::bus_read(){
    cout << "icconf_r" << endl;
    if(icconf_rd_i.read()) {
        cout << "icconf_read " << reg << endl;
        data_bo.write(0x22);
        ret_data=true;
    }
/*
    else{
        cout << "icconf no read" << endl;
        if( ret_data ) {
            cout << "ret data" << endl;
            data_bo.write(0x33);
            ret_data=false;
        }else{
            cout << "haha" << endl;
            //data_bo.write(0x44);
        }
        //icconf_data_bo.write(0);
    }
    */
}
