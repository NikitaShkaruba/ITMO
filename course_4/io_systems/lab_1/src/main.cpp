#include "mips32.h"
#include "bus.h"
#include "icconf.h"

int sc_main(int argc, char* argv[])
{

    MIPS32 mips32_core("mips32");
    Bus bus("bus");
    ICCONF icconf("icconf");

    //bus
    sc_clock clk("clk", sc_time(10, SC_NS));
    sc_signal<u32> addr;
    sc_signal<u32> data_mips32_bo;
    sc_signal<u32>  data_mips32_bi;
    //sc_signal<u32, SC_MANY_WRITERS>  data_mips32_bi;
    sc_signal<bool> wr;
    sc_signal<bool> rd;

    //icconf
    sc_signal<bool> icconf_wr;
    sc_signal<bool> icconf_rd;
    //sc_signal<u32> data_icconf_bo;

    mips32_core.clk_i(clk);
    mips32_core.addr_bo(addr);
    mips32_core.data_bi(data_mips32_bi);
    mips32_core.data_bo(data_mips32_bo);
    mips32_core.wr_o(wr);
    mips32_core.rd_o(rd);

    bus.clk_i(clk);
    bus.addr_bi(addr);
    //bus.data_bi(data_mips32_bo);
    //bus.data_bo(data_mips32_bi);
    bus.wr_i(wr);
    bus.rd_i(rd);
    bus.icconf_rd_o(icconf_rd);
    bus.icconf_wr_o(icconf_wr);
    //bus.icconf_data_bi(data_icconf_bo);

    icconf.clk_i(clk);
    icconf.data_bi(data_mips32_bo);
    icconf.icconf_rd_i(icconf_rd);
    icconf.icconf_wr_i(icconf_wr);
    icconf.data_bo(data_mips32_bi);

    sc_trace_file *wf = sc_create_vcd_trace_file("wave");
    sc_trace(wf, clk, "clk");
    sc_trace(wf, addr, "addr_bo");
    sc_trace(wf, data_mips32_bi, "data_bi");
    sc_trace(wf, data_mips32_bo, "data_bo");
    sc_trace(wf, wr, "wr");
    sc_trace(wf, rd, "rd");
    sc_trace(wf, icconf_wr, "icconf_wr");
    sc_trace(wf, icconf_rd, "icconf_rd");

    sc_start();


    sc_close_vcd_trace_file(wf);

    return(0);

}
