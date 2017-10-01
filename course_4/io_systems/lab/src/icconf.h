#ifndef _ICCONF_H
#define _ICCONF_H

#include "common.h"
#include "systemc.h"

SC_MODULE(ICCONF)
{

    sc_in<bool>  clk_i;
    sc_in<bool>  icconf_wr_i;
    sc_in<bool>  icconf_rd_i;
    sc_out<u32>  icconf_data_bo;

    sc_in<u32>   data_bi;

    SC_HAS_PROCESS(ICCONF);

    ICCONF(sc_module_name nm);
    ~ICCONF();

    void bus_write();
    void bus_read();

private:
    u32 reg;

};


#endif
