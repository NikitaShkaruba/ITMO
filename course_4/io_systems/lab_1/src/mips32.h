#ifndef _MIPS32_H
#define _MIPS32_H

#include "systemc.h"

SC_MODULE(MIPS32)
{
    sc_in<bool>  clk_i;
    sc_out<int>  addr_bo;
    sc_in<int>   data_bi;
    sc_out<int>  data_bo;
    sc_out<bool> wr_o;
    sc_out<bool> rd_o;
    
    SC_HAS_PROCESS(MIPS32);
    
    MIPS32(sc_module_name nm);
    ~MIPS32();
    
    void mainThread();
private:

    void bus_write(int addr, int data);
    int  bus_read(int addr);

};


#endif
