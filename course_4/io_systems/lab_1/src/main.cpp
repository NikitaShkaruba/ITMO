#include "lib/include/core.h"
#include "lib/include/bus.h"
#include "lib/include/icconf.h"
#include "lib/include/timer1.h"
#include "lib/include/edge_detector.h"
#include "lib/include/prescaler.h"
#include "lib/include/buffer.h"


int sc_main(int argc, char* argv[]) {
    CORE core("core");
    Bus bus("bus");
    ICCONF icconf("icconf");
    Timer1 timer1("timer1");
    Timer1 timer2("timer2");
    EdgeDetector edge_detector("edge_detector");
    Prescaler prescaler("prescaler");
    Buffer buffer("buffer");

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

    sc_signal<u32> data_timer1_buffer;
    buffer.data_from_timer1(data_timer1_buffer);
    timer1.data_to_buffer(data_timer1_buffer);

    sc_signal<bool> data_signal_timer1_buffer;
    buffer.data_signal_from_timer1(data_signal_timer1_buffer);
    timer1.data_signal_to_buffer(data_signal_timer1_buffer);

    sc_signal<bool> read_signal_buffer_timer1;
    buffer.read_signal_to_timer1(read_signal_buffer_timer1);
    timer1.read_signal_from_buffer(read_signal_buffer_timer1);
    // endregion

    // region Bind Bus and timer2
    sc_signal<u32> data_bus_timer2;
    bus.data_to_timer2(data_bus_timer2);
    timer2.data_from_bus(data_bus_timer2);

    sc_signal<u32, SC_MANY_WRITERS> address_bus_timer2;
    bus.address_to_timer2(address_bus_timer2);
    timer2.address_from_bus(address_bus_timer2);

    sc_signal<bool> write_signal_bus_timer2;
    bus.write_signal_to_timer2(write_signal_bus_timer2);
    timer2.write_signal_from_bus(write_signal_bus_timer2);

    sc_signal<u32> data_timer2_bus;
    bus.data_from_timer2(data_timer2_bus);
    timer2.data_to_bus(data_timer2_bus);

    sc_signal<bool> read_signal_bus_timer2;
    bus.read_signal_to_timer2(read_signal_bus_timer2);
    timer2.read_signal_from_bus(read_signal_bus_timer2);

    sc_signal<bool> write_signal_timer2_bus;
    bus.write_signal_from_timer2(write_signal_timer2_bus);
    timer2.write_signal_to_bus(write_signal_timer2_bus);

    sc_signal<u32> data_timer2_buffer;
    buffer.data_from_timer2(data_timer2_buffer);
    timer2.data_to_buffer(data_timer2_buffer);

    sc_signal<bool> data_signal_timer2_buffer;
    buffer.data_signal_from_timer2(data_signal_timer2_buffer);
    timer2.data_signal_to_buffer(data_signal_timer2_buffer);

    sc_signal<bool> read_signal_buffer_timer2;
    buffer.read_signal_to_timer2(read_signal_buffer_timer2);
    timer2.read_signal_from_buffer(read_signal_buffer_timer2);
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

    sc_signal<bool> edge_signal_prescaler_buffer;
    prescaler.edge_signal_to_buffer(edge_signal_prescaler_buffer);
    buffer.edge_signal_from_prescaler(edge_signal_prescaler_buffer);
    // endregion

    //region Bind ICCONF and Buffer
    sc_signal<bool> buffer_empty_signal_buffer_icconf;
    icconf.buffer_empty_signal_from_buffer(buffer_empty_signal_buffer_icconf);
    buffer.buffer_empty_signal_to_icconf(buffer_empty_signal_buffer_icconf);

    sc_signal<bool> buffer_full_signal_buffer_icconf;
    icconf.buffer_full_signal_from_buffer(buffer_full_signal_buffer_icconf);
    buffer.buffer_full_signal_to_icconf(buffer_full_signal_buffer_icconf);

    sc_signal<u32> mode_icconf_buffer;
    icconf.mode_to_buffer(mode_icconf_buffer);
    buffer.mode_from_icconf(mode_icconf_buffer);
    // endregion

    //region Bind Bus and Buffer
    sc_signal<u32> data_buffer_bus;
    bus.data_from_buffer(data_buffer_bus);
    buffer.data_to_bus(data_buffer_bus);

    sc_signal<bool> read_signal_bus_buffer;
    bus.read_signal_to_buffer(read_signal_bus_buffer);
    buffer.read_signal_from_bus(read_signal_bus_buffer);

    sc_signal<bool> write_signal_buffer_bus;
    bus.write_signal_from_buffer(write_signal_buffer_bus);
    buffer.write_signal_to_bus(write_signal_buffer_bus);
    //endregion

    // region Bind Clock
    sc_clock clock("clock", sc_time(10, SC_NS));
    core.clock_in(clock);
    bus.clock_in(clock);
    icconf.clock_in(clock);
    timer1.clock_in(clock);
    timer2.clock_in(clock);
    edge_detector.clock_in(clock);
    prescaler.clock_in(clock);
    buffer.clock_in(clock);
    // endregion

    sc_start();
    return (0);
}