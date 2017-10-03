#include "lib/include/core.h"
#include "lib/include/bus.h"

int sc_main(int argc, char* argv[]) {
  CORE core("core");
  Bus bus("bus");

  //region Bind bus and core
  sc_signal<int> addr;
  core.address_out(addr);
  bus.address_in(addr);

  sc_signal<int> core_bus_i;
  core.data_in(core_bus_i);
  bus.data_out(core_bus_i);

  sc_signal<int> core_but_o;
  core.data_out(core_but_o);
  bus.data_in(core_but_o);

  sc_signal<bool> core_bus_write;
  core.write_out(core_bus_write);
  bus.write_in(core_bus_write);

  sc_signal<bool> core_bus_read;
  core.read_out(core_bus_read);
  bus.read_in(core_bus_read);

  sc_clock clock("clock", sc_time(10, SC_NS));
  core.clock_in(clock);
  bus.clock_in(clock);
  //endregion

  sc_start();

  return (0);
}
