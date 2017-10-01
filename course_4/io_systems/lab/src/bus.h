#ifndef _Bus_H
#define _Bus_H

#include "common.h"
#include "systemc.h"

SC_MODULE(Bus)
{
    //mips32
    sc_in<bool>  clk_i;
    sc_in<u32>   addr_bi;
    //sc_in<u32>   data_bi;
    sc_out<u32>  data_bo;
    sc_in<bool>  wr_i;
    sc_in<bool>  rd_i;

    //icconf
    sc_out<bool>  icconf_wr_o;
    sc_out<bool>  icconf_rd_o;
    //sc_in<u32>  icconf_data_bi;

    SC_HAS_PROCESS(Bus);

    Bus(sc_module_name nm);
    ~Bus();

    void bus_write();
    void bus_read();

private:

};


#endif
