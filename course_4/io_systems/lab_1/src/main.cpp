#include "lib/include/mips32.h"
#include "lib/include/bus.h"
#include "lib/include/icconf.h"

int sc_main(int argc, char* argv[]) {
  MIPS32 mips32_core("mips32");
  Bus bus("bus");
  ICCONF icconf("icconf");

  // bus
  sc_clock clk("clk", sc_time(10, SC_NS));
  sc_signal<u32> address;
  sc_signal<u32> data_mips32_b_out;
  sc_signal<u32> data_mips32_b_input;
  sc_signal<bool> write_signal;
  sc_signal<bool> read_signal;

  // icconf
  sc_signal<bool> icconf_wr;
  sc_signal<bool> icconf_rd;

  mips32_core.clk_i(clk);
  mips32_core.addr_bo(address);
  mips32_core.data_bi(data_mips32_b_input);
  mips32_core.data_bo(data_mips32_b_out);
  mips32_core.wr_o(write_signal);
  mips32_core.rd_o(read_signal);

  bus.clk_i(clk);
  bus.addr_bi(address);
  //bus.data_bi(data_mips32_b_out);
  //bus.data_bo(data_mips32_b_input);
  bus.wr_i(write_signal);
  bus.rd_i(read_signal);
  bus.icconf_rd_o(icconf_rd);
  bus.icconf_wr_o(icconf_wr);
  //bus.icconf_data_bi(data_icconf_bo);

  icconf.clk_i(clk);
  icconf.data_bi(data_mips32_b_out);
  icconf.icconf_rd_i(icconf_rd);
  icconf.icconf_wr_i(icconf_wr);
  icconf.data_bo(data_mips32_b_input);

  sc_trace_file* wf = sc_create_vcd_trace_file("wave");
  sc_trace(wf, clk, "clk");
  sc_trace(wf, address, "addr_bo");
  sc_trace(wf, data_mips32_b_input, "data_bi");
  sc_trace(wf, data_mips32_b_out, "data_bo");
  sc_trace(wf, write_signal, "write_signal");
  sc_trace(wf, read_signal, "read_signal");
  sc_trace(wf, icconf_wr, "icconf_wr");
  sc_trace(wf, icconf_rd, "icconf_rd");

  sc_start();


  sc_close_vcd_trace_file(wf);

  return (0);

}
