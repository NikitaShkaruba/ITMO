#include "mips32.h"
#include "mem.h"

int sc_main(int argc, char* argv[]) {
  sc_clock clk("clk", sc_time(1000, SC_NS));
  sc_signal<int> addr;
  sc_signal<int> data_mips32_bo;
  sc_signal<int> data_mips32_bi;
  sc_signal<bool> wr;
  sc_signal<bool> rd;

  // Create core
  MIPS32 mips32_core("mips32");
  mips32_core.clk_i(clk);
  mips32_core.addr_bo(addr);
  mips32_core.data_bi(data_mips32_bi);
  mips32_core.data_bo(data_mips32_bo);
  mips32_core.wr_o(wr);
  mips32_core.rd_o(rd);

  // Create memory
  Mem memory("memory");
  memory.clk_i(clk);
  memory.addr_bi(addr);
  memory.data_bi(data_mips32_bo);
  memory.data_bo(data_mips32_bi);
  memory.rd_i(rd);
  memory.wr_i(wr);

  sc_start();
  return (0);
}
