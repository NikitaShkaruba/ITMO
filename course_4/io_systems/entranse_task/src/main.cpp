#include "mips32.h"
#include "mem.h"

int sc_main(int argc, char* argv[])
{
    
    MIPS32 mips32_core("mips32");
    Mem memory("memory");
    
    sc_clock clk("clk", sc_time(10, SC_NS));
    sc_signal<int> addr;
    sc_signal<int> data_mips32_bo;
    sc_signal<int> data_mips32_bi;
    sc_signal<bool> wr;
    sc_signal<bool> rd;
    
    mips32_core.clk_i(clk);
    mips32_core.addr_bo(addr);
    mips32_core.data_bi(data_mips32_bi);
    mips32_core.data_bo(data_mips32_bo);
    mips32_core.wr_o(wr);
    mips32_core.rd_o(rd);
    
    memory.clk_i(clk);
    memory.addr_bi(addr);
    memory.data_bi(data_mips32_bo);
    memory.data_bo(data_mips32_bi);
    memory.wr_i(wr);
    memory.rd_i(rd);
    
    sc_trace_file *wf = sc_create_vcd_trace_file("wave");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, addr, "addr_bo");
    sc_trace(wf, data_mips32_bi, "data_bi");
    sc_trace(wf, data_mips32_bo, "data_bo");
    sc_trace(wf, wr, "wr");
    sc_trace(wf, rd, "rd");

    sc_start();

 
    sc_close_vcd_trace_file(wf);
    
    return(0);
    
}
