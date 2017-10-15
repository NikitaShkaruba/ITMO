#include "lib/include/core.h"
#include "lib/include/bus.h"
#include "lib/include/input_capture/input_capture.h"

int sc_main(int argc, char* argv[]) {
  CORE core("core");
  Bus bus("bus");
  InputCapture input_capture("input_capture");

  //region Bind Bus and Core
  sc_signal<int> core_bus_address;
  core.bus_address_out(core_bus_address);
  bus.core_address_in(core_bus_address);

  sc_signal<int> core_bus_i;
  core.bus_data_in(core_bus_i);
  bus.core_data_out(core_bus_i);

  sc_signal<int> core_bus_o;
  core.bus_data_out(core_bus_o);
  bus.core_data_in(core_bus_o);

  sc_signal<bool> core_bus_write;
  core.bus_write_out(core_bus_write);
  bus.core_write_in(core_bus_write);

  sc_signal<bool> core_bus_read;
  core.bus_read_out(core_bus_read);
  bus.core_read_in(core_bus_read);
  //endregion

  // region Bind Bus and InputCapture
  sc_signal<int> ic_bus_address;
  input_capture.address_out(ic_bus_address);
  bus.ic_address_in(ic_bus_address);

  sc_signal<int> ic_bus_input;
  input_capture.data_in(ic_bus_input);
  bus.ic_data_out(ic_bus_input);

  sc_signal<bool> ic_bus_read;
  input_capture.read_out(ic_bus_read);
  bus.ic_read_in(ic_bus_read);
  // endregion

  // region Bind Core and InputCapture
  sc_signal<bool> core_ic_signal;
  core.ic_signal_out(core_ic_signal);
  input_capture.input_signal(core_ic_signal);
  // endregion

  // region Bind Clock
  sc_clock clock("clock", sc_time(10, SC_NS));
  core.clock_in(clock);
  bus.clock_in(clock);
  input_capture.clock_in(clock);
  // endregion

  sc_start();
  return (0);
}
