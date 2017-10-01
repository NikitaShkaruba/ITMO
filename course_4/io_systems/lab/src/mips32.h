#ifndef _MIPS32_H
#define _MIPS32_H

#include "common.h"
#include "systemc.h"

SC_MODULE(MIPS32)
{
    sc_in<bool>  clk_i;
    sc_out<u32>  addr_bo;
    sc_in<u32>   data_bi;
    sc_out<u32>  data_bo;
    sc_out<bool> wr_o;
    sc_out<bool> rd_o;

    SC_HAS_PROCESS(MIPS32);

    MIPS32(sc_module_name nm);
    ~MIPS32();

    void mainThread();
private:

    void bus_write(u32 addr, u32 data);
    int  bus_read(u32 addr);

};


#endif
