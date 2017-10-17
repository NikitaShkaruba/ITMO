#include "../include/core.h"
#include "../include/addresses.h"
#include "../include/consts.h"

using namespace std;

CORE::CORE(sc_module_name nm) : sc_module(nm),
    clock_in("clock_in"),
    data_to_bus("data_to_bus"),
    address_to_bus("address_to_bus"),
    write_signal_to_bus("write_signal_to_bus"),
    data_from_bus("data_from_bus"),
    read_signal_to_bus("read_signal_to_bus"),
    signal_to_edge_detector("signal_to_edge_detector")
{
    data_to_bus.initialize(0);
    address_to_bus.initialize(0);
    write_signal_to_bus.initialize(0);

    read_signal_to_bus.initialize(0);
    signal_to_edge_detector.initialize(0);

    SC_CTHREAD(main_thread, clock_in.pos());
}

CORE::~CORE() = default;

void CORE::main_thread() {
  cout << endl << endl << endl << endl << endl << endl << endl;
  cout << "Choose mode:" << endl;
  cout << "  5 - check neither signal is periodic" << endl;
  cout << "  4 - test full system" << endl;
  cout << "  3 - test timers" << endl;
  cout << "  2 - test timer" << endl;
  cout << "  1 - test bus" << endl;
  cout << "  0 - exit" << endl;
  cout << endl << "Your choice: ";

  int mode;
  cin >> mode;

  switch (mode) {
    case 1:
      test_bus();
      break;

    case 2:
      test_timer();
      break;

    case 3:
      test_timers();
      break;

    case 4:
      test_system();
      break;

    case 5:
      check_if_signal_periodic();
      break;

    default:
    case 0:
      break;
  }

  sc_stop();
}

void CORE::write_to_bus(u32 address, u32 data) {
    //wait();
    //printf("==0==\n");
    address_to_bus.write(address);
    data_to_bus.write(data);
    write_signal_to_bus.write(1);
    wait();
    //printf("==1==\n");

    write_signal_to_bus.write(0);
    wait();
    //printf("==2==\n");

//    cout << "CORE: WRITE " << endl;
//    cout << "  -> address: " << hex << address << endl;
//    cout << "  -> data: " << hex << data << endl;
}

u32 CORE::read_from_bus(u32 address) {
    u32 data;

    //printf("==0==\n");
    address_to_bus.write(address);
    read_signal_to_bus.write(1);
    wait();

    //printf("==1==\n");
    read_signal_to_bus.write(0);
    wait();

    //printf("==2==\n");
    wait();

    //printf("==3==\n");
    wait();

    //printf("==4==\n");
    wait();

    //printf("read\n");
    data = data_from_bus.read();
    wait();

    //printf("==3==\n");

//    cout << "CORE: READ " << endl;
//    cout << "  -> address: " << hex << address << endl;
//    cout << "  -> data: " << hex << data << endl;

    return data;
}

// region Tests

void CORE::test_bus() {
    write_to_bus(BUS_ADDRESS_ICCONF,0x43);

    read_from_bus(BUS_ADDRESS_ICCONF);
    write_to_bus(BUS_ADDRESS_TVAL1,0x24);
    read_from_bus(BUS_ADDRESS_TVAL1);
    write_to_bus(BUS_ADDRESS_TMR1,0x12);
    read_from_bus(BUS_ADDRESS_TMR1);
    read_from_bus(BUS_ADDRESS_ICCONF);
}

void CORE::test_timer() {
  write_to_bus(BUS_ADDRESS_TMR1,10);
  write_to_bus(BUS_ADDRESS_TCONF1,0x2);
  read_from_bus(BUS_ADDRESS_TVAL1);
  read_from_bus(BUS_ADDRESS_TVAL1);
  read_from_bus(BUS_ADDRESS_TVAL1);
  read_from_bus(BUS_ADDRESS_TVAL1);
  read_from_bus(BUS_ADDRESS_TVAL1);
};

void CORE::test_timers() {
    write_to_bus(BUS_ADDRESS_TMR1, 10);
    write_to_bus(BUS_ADDRESS_TCONF1, 0x2);
    write_to_bus(BUS_ADDRESS_TMR2, 20);
    write_to_bus(BUS_ADDRESS_TCONF2, 0x2);

    read_from_bus(BUS_ADDRESS_TVAL1);
    read_from_bus(BUS_ADDRESS_TVAL1);
    read_from_bus(BUS_ADDRESS_TVAL1);
    read_from_bus(BUS_ADDRESS_TVAL1);
    read_from_bus(BUS_ADDRESS_TVAL1);

    read_from_bus(BUS_ADDRESS_TVAL2);
    read_from_bus(BUS_ADDRESS_TVAL2);
    read_from_bus(BUS_ADDRESS_TVAL2);
    read_from_bus(BUS_ADDRESS_TVAL2);
    read_from_bus(BUS_ADDRESS_TVAL2);
};

void CORE::test_system() {
    // Настройка таймеров
    write_to_bus(BUS_ADDRESS_TMR1, 10);
    write_to_bus(BUS_ADDRESS_TCONF1, 0x2);
    write_to_bus(BUS_ADDRESS_TMR2, 20);
    write_to_bus(BUS_ADDRESS_TCONF2, 0x2);

    // Настраиваем EdgeDetector, Prescaler и Buffer
    write_to_bus(BUS_ADDRESS_ICCONF, 0x1 | 3 << 5);

    // Генерируем входной сигнал и забиваем буфер до отказа
    bool sig = false;

    for (int i = 0; i < 64; i++) {
        signal_to_edge_detector.write(sig);
        sig = !sig;

        u32 icconf = read_from_bus(BUS_ADDRESS_ICCONF);

        if (icconf & 0x10) {
//            printf("Full\n");
            break;
        }

        //wait(); вместо read_from_bus
        //wait();
        //wait();
    }

    // Читаем буфер пока он не опустеет
    while (1) {
        u32 icconf = read_from_bus(BUS_ADDRESS_ICCONF);

        if (icconf & 0x08) {
//            printf("Empty\n");
            break;
        }

        u32 record = read_from_bus(BUS_ADDRESS_BUFFER);
        printf("Record %d %d\n", record >> 16, record & 0xFFFF);
    }
}

// region Variant task

/*
 * nsh: Test mocks
 *
 * Periodic:
 * string signals = string("1100110011001100110011");
 * string signals = string("10101010101");
 * string signals = string("101010101010");
 * string signals = string("0101010101010");
 *
 * Not periodic:
 * string signals = string("01101100");
 * string signals = string("0110100");
 * string signals = string("111111");
 * string signals = string("00000");
 */
void CORE::check_if_signal_periodic() {
  string signals;
  cout << "Example: 0011101010101010111011010101010" << endl;
  cout << "Input signals for each tick: ";
  cin >> signals;

  // Setup environment
  write_to_bus(BUS_ADDRESS_TMR1, 10);
  write_to_bus(BUS_ADDRESS_TCONF1, 0x2);
  write_to_bus(BUS_ADDRESS_TMR2, 20);
  write_to_bus(BUS_ADDRESS_TCONF2, 0x2);
  write_to_bus(BUS_ADDRESS_ICCONF, 0x1 | 1 << 5);

  // Write to ins
  for (int i = 0; i < std::strlen(signals.c_str()); i++) {
    bool signal = signals[i] == '1';
    write_to_ins(signal);
  }

  // Check periodically
  bool is_periodic;
  int period = 0;

  bool continue_checking;
  int last_time = 0;
  int buffer_size = 10;

  do {
    u32 record = read_from_bus(BUS_ADDRESS_BUFFER);
    int iteration_time = record & 0xFFFF;

    int iteration_period = iteration_time - last_time;
    if (iteration_period < 0) {
      iteration_period += buffer_size;
    }

    is_periodic = !period || period == iteration_period;
    last_time = iteration_time;
    period = iteration_period;

    u32 icconf = read_from_bus(BUS_ADDRESS_ICCONF);
    bool is_buffer_full = static_cast<bool>(icconf & 0x08);

    continue_checking = !is_buffer_full && is_periodic;
  } while(continue_checking);

  if (is_periodic && period) {
    cout << "Is periodic: true" << endl;
    cout << "period: " << period << endl;
    cout << "frequency: " << 1 / static_cast<float>(period) << endl;
  } else {
    cout << "Is periodic: false" << endl;
  }
}

void CORE::write_to_ins(bool signal) {
  signal_to_edge_detector.write(signal);
  wait();
}

// endregion

// endregion
