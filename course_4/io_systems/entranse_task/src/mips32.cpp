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
    int data_size = 5;
    
    for(int i = 0; i < data_size; i++)
    {
        bus_write(i, (i+1)*2);
    }
    
    for(int i = 0; i < data_size; i++)
    {
        bus_read(i);
    }
    
    sc_stop();

}

int MIPS32::bus_read(int addr)
{
    int data;

    wait();
    addr_bo.write(addr);
    rd_o.write(1);
    
    wait();
    rd_o.write(0);
    
    wait();
    data = data_bi.read();
    
    cout << "MIPS32: READ " << endl;
    cout << "  -> addr: " << hex << addr << endl;
    cout << "  -> data: " << hex << data << endl;
    
    return data;
    
}

void MIPS32::bus_write(int addr, int data)
{
    wait();
    addr_bo.write(addr);
    data_bo.write(data);
    wr_o.write(1);
    
    wait();
    wr_o.write(0);
    
    cout << "MIPS32: WRITE " << endl;
    cout << "  -> addr: " << hex << addr << endl;
    cout << "  -> data: " << hex << data << endl;

}
