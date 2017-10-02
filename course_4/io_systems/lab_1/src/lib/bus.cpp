#include "include/bus.h"

Bus::Bus(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    addr_bi("addr_bi"),
    //data_bo("data_bo"),
    wr_i("wr_i"),
    rd_i("rd_i"),

    icconf_wr_o("icconf_wr_o"),
    icconf_rd_o("icconf_rd_o")
{
    //data_bo.initialize(0);

    icconf_wr_o.initialize(0);
    icconf_rd_o.initialize(0);

    SC_METHOD(bus_write);
    sensitive << clk_i.pos();

    SC_METHOD(bus_read);
    sensitive << clk_i.pos();

}

Bus::~Bus(){
}

void Bus::bus_read() {
    cout<<"bus_r\n";
    if(rd_i.read()) {
        switch(addr_bi.read()) {
            case ICCONF_ADDRESS:
                cout<<"bus read\n";
                icconf_rd_o.write(1);

                //u32 d=icconf_data_bi.read();  //Не в этот такт, но как сделать в следующем?
                //cout<<"DATA:"<<d<<endl;
                //data_bo.write( d );
                break;
        }
    }else{
        cout<<"bus not read\n";
        icconf_rd_o.write(0);
    }
}

void Bus::bus_write() {
    if(wr_i.read()) {
        switch(addr_bi.read()) {
            case ICCONF_ADDRESS:
                cout<<"bus write\n";
                icconf_wr_o.write(1);
                break;
        }
    }else{
        //cout<<"bus not write\n";
        icconf_wr_o.write(0);
    }
}
