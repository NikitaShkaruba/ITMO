#include "lib/include/core.h"
#include "lib/include/bus.h"
#include "lib/include/icconf.h"
#include "lib/include/timer1.h"
#include "lib/include/edge_detector.h"
#include "lib/include/prescaler.h"


int sc_main(int argc, char* argv[]) {
    CORE core("core");
    Bus bus("bus");
    ICCONF icconf("icconf");
    Timer1 timer1("timer1");
    EdgeDetector edge_detector("edge_detector");
    Prescaler prescaler("prescaler");

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

    sc_signal<u32, SC_MANY_WRITERS> data_bus_core;
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

    // region Bind Bus and Timer1
    sc_signal<u32> data_bus_timer1;
    bus.data_to_timer1(data_bus_timer1);
    timer1.data_from_bus(data_bus_timer1);

    sc_signal<u32, SC_MANY_WRITERS> address_bus_timer1;
    bus.address_to_timer1(address_bus_timer1);
    timer1.address_from_bus(address_bus_timer1);

    sc_signal<bool> write_signal_bus_timer1;
    bus.write_signal_to_timer1(write_signal_bus_timer1);
    timer1.write_signal_from_bus(write_signal_bus_timer1);

    sc_signal<u32> data_timer1_bus;
    bus.data_from_timer1(data_timer1_bus);
    timer1.data_to_bus(data_timer1_bus);

    sc_signal<bool> read_signal_bus_timer1;
    bus.read_signal_to_timer1(read_signal_bus_timer1);
    timer1.read_signal_from_bus(read_signal_bus_timer1);

    sc_signal<bool> write_signal_timer1_bus;
    bus.write_signal_from_timer1(write_signal_timer1_bus);
    timer1.write_signal_to_bus(write_signal_timer1_bus);
    // endregion

    // region Bind EdgeDetector and Prescaler
    sc_signal<u32> mode_icconf_edge_detector_prescaler;
    edge_detector.mode_from_icconf(mode_icconf_edge_detector_prescaler);
    icconf.mode_to_edge_detector(mode_icconf_edge_detector_prescaler);
    prescaler.mode_from_icconf(mode_icconf_edge_detector_prescaler);

    sc_signal<bool> signal_core_edge_detector;
    edge_detector.input_signal(signal_core_edge_detector);
    core.signal_to_edge_detector(signal_core_edge_detector);

    sc_signal<bool> edge_signal_edge_detector_prescaler;
    edge_detector.edge_signal_to_prescaler(edge_signal_edge_detector_prescaler);
    prescaler.edge_signal_from_edge_detector(edge_signal_edge_detector_prescaler);

    //sc_signal<bool> signal_core_edge_detector;
    //edge_detector.input_signal(signal_core_edge_detector);
    //core.signal_to_edge_detector(signal_core_edge_detector);
    // endregion

    // region Bind Clock
    sc_clock clock("clock", sc_time(10, SC_NS));
    core.clock_in(clock);
    bus.clock_in(clock);
    icconf.clock_in(clock);
    timer1.clock_in(clock);
    edge_detector.clock_in(clock);
    prescaler.clock_in(clock);
    // endregion

    sc_start();
    return (0);
}