#include "mips32.h"

using namespace std;

MIPS32::MIPS32(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),
    addr_bo("addr_bo"),
    data_bi("data_bi"),
    data_bo("data_bo"),
    wr_o("wr_o"),
    rd_o("rd_o")
{
    addr_bo.initialize(0);
    data_bo.initialize(0);
    wr_o.initialize(0);
    rd_o.initialize(0);

    SC_CTHREAD(mainThread, clk_i.pos());

}

MIPS32::~MIPS32()
{

}

void MIPS32::mainThread()
{
    //bus_write(0,323);
    bus_write(ICCONF_ADDRESS,94);

    bus_read(ICCONF_ADDRESS);

    sc_stop();
}

int MIPS32::bus_read(u32 addr)
{
    cout << "MIPS32: READ " << endl;
    cout << "  -> addr: " << hex << addr << endl;

    int data;

    wait();
    addr_bo.write(addr);
    rd_o.write(1);

    wait();
    rd_o.write(0);

    wait();
    data = data_bi.read();

    cout << "  -> data: " << data << endl;

    return data;

}

void MIPS32::bus_write(u32 addr, u32 data)
{
    cout << "MIPS32: WRITE " << endl;
    cout << "  -> addr: " << hex << addr << endl;
    cout << "  -> data: " << data << endl;

    wait();
    addr_bo.write(addr);
    wr_o.write(1);
    data_bo.write(data);

    wait();
    wr_o.write(0);
}
