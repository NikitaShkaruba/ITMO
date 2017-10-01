#ifndef _INPUT_CAPTURE_H
#define _INPUT_CAPTURE_H

#include "common.h"
#include "systemc.h"

SC_MODULE(InputCapture)
{

    sc_in<bool>  clk_i;
    sc_in<u32>   addr_bi;
    sc_in<u32>   data_bi;
    sc_out<u32>  data_bo;
    sc_in<bool>  wr_i;
    sc_in<bool>  rd_i;

    SC_HAS_PROCESS(InputCapture);

    InputCapture(sc_module_name nm);
    ~InputCapture();

    void bus_write();
    void bus_read();

private:
    u32 mem[256];

};


#endif
