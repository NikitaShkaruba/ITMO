#include "lib/include/core.h"
#include "lib/include/bus.h"
#include "lib/include/icconf.h"


int sc_main(int argc, char* argv[]) {
    CORE core("core");
    Bus bus("bus");
    ICCONF icconf("icconf");

    //region Bind Bus and Core
    sc_signal<u32> address_core_bus;
    core.address_to_bus(address_core_bus);
    bus.address_from_core(address_core_bus);

    sc_signal<u32> data_core_bus;
    core.data_to_bus(data_core_bus);
    bus.data_from_core(data_core_bus);

    sc_signal<bool> write_signal_core_bus;
    core.write_signal_to_bus(write_signal_core_bus);
    bus.write_signal_from_core(write_signal_core_bus);

    sc_signal<u32> data_bus_core;
    core.data_from_bus(data_bus_core);
    bus.data_to_core(data_bus_core);

    sc_signal<bool> read_signal_core_bus;
    core.read_signal_to_bus(read_signal_core_bus);
    bus.read_signal_from_core(read_signal_core_bus);
    //endregion

    // region Bind Bus and ICCONF
    sc_signal<u32> data_bus_icconf;
    bus.data_to_icconf(data_bus_icconf);
    icconf.data_from_bus(data_bus_icconf);

    sc_signal<bool> write_signal_bus_icconf;
    bus.write_signal_to_icconf(write_signal_bus_icconf);
    icconf.write_signal_from_bus(write_signal_bus_icconf);

    sc_signal<u32> data_icconf_bus;
    bus.data_from_icconf(data_icconf_bus);
    icconf.data_to_bus(data_icconf_bus);

    sc_signal<bool> read_signal_bus_icconf;
    bus.read_signal_to_icconf(read_signal_bus_icconf);
    icconf.read_signal_from_bus(read_signal_bus_icconf);

    sc_signal<bool> write_signal_icconf_bus;
    bus.write_signal_from_icconf(write_signal_icconf_bus);
    icconf.write_signal_to_bus(write_signal_icconf_bus);
    // endregion

    // region Bind Clock
    sc_clock clock("clock", sc_time(10, SC_NS));
    core.clock_in(clock);
    bus.clock_in(clock);
    icconf.clock_in(clock);
    // endregion

    printf("c");

    sc_start();
    return (0);
}