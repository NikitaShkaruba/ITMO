/*

#include "include/input_capture/input_capture.h"
#include "include/addresses.h"

InputCapture::InputCapture(sc_module_name name) : sc_module(name) {
  read_out.initialize(1);
  address_out.initialize(BUS_ADDRESS_INPUT_CAPTURE_CONFIG);

  SC_METHOD(setConfig);
  sensitive << clock_in.pos();

  SC_METHOD(tick);
  sensitive << clock_in.pos();
}

InputCapture::~InputCapture() = default;

// Todo: add input_changed bit maybe (right now it's called every tick)
void InputCapture::setConfig() {
  unsigned int data = (unsigned int) data_in.read();

  unsigned int input_capture_config = data & 0x7;
  switch (input_capture_config) {
    case 0x0:
      config.is_enabled = false;
      break;

    case 0x1:
      config.is_enabled = true;
      config.scale = 1;
      config.edge = CONFIG_EDGE_ANY;
      break;

    case 0x2:
      config.is_enabled = true;
      config.scale = 1;
      config.edge = CONFIG_EDGE_FALLING;
      break;

    case 0x3:
      config.is_enabled = true;
      config.scale = 1;
      config.edge = CONFIG_EDGE_RISING;
      break;

    case 0x4:
      config.is_enabled = true;
      config.scale = 4;
      config.edge = CONFIG_EDGE_RISING;
      break;

    case 0x5:
      config.is_enabled = true;
      config.scale = 16;
      config.edge = CONFIG_EDGE_RISING;
      break;

    case 0x6:
      config.is_enabled = true;
      config.scale = 4;
      config.edge = CONFIG_EDGE_FALLING;
      break;

    case 0x7:
      config.is_enabled = true;
      config.scale = 16;
      config.edge = CONFIG_EDGE_FALLING;
      break;

    default:
      throw std::invalid_argument("Error in ic setConfig");
  }

  unsigned int timer_config = (data >> 5) & 0x5;
  switch (timer_config) {
    case 0x0:
      break;

    case 0x01:
      break;

    case 0x10:
      break;

    case 0x11:
      break;

    default:
      throw std::invalid_argument("Error in timer_config setConfig");
  }

}

void InputCapture::tick() {
  if (!config.is_enabled) {
    return;
  }

  bool input_signal = (bool) this->input_signal.read();

  if (!isPassesEdgeDetector(input_signal)) {
    return;
  }
  if (!isPassesPrescaler()) {
    return;
  }

  return;
}

bool InputCapture::isPassesPrescaler() {
  if (++scale_iteration != config.scale) {
    return false;
  }

  scale_iteration = 0;
  return true;
}

bool InputCapture::isPassesEdgeDetector(bool input_signal) {
  if (remembered_signal == input_signal) {
    return false;
  }

  bool last_signal = remembered_signal;
  remembered_signal = input_signal;

  switch (config.edge) {
    case CONFIG_EDGE_ANY:
      return true;

    case CONFIG_EDGE_RISING:
      return last_signal != true;

    case CONFIG_EDGE_FALLING:
      return last_signal != false;

    default:
      throw std::invalid_argument("Error in edge detector");
  }
}

*/