#include "include/input_capture/input_capture.h"
#include "include/bus/addresses.h"

InputCapture::InputCapture(sc_module_name name) : sc_module(name) {
  read_out.initialize(1);
  address_out.initialize(BUS_ADDRESS_INPUT_CAPTURE_CONFIG);

  SC_METHOD(setConfig);
  sensitive << clock_in.pos();
}

InputCapture::~InputCapture() = default;

void InputCapture::setConfig() {
  unsigned_int data = (unsigned_int) data_in.read();

  // Fill them by yourself
  config.capture_config = data & 0x7;
  config.timer_config = (data >> 5) & 0x3;

  // Don't used. Fill them by yourself
  config.is_buffer_empty = false;
  config.is_buffer_full = false;
  config.reserve = 0;
}
