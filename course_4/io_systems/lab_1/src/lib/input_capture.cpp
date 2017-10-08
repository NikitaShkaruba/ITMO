#include "include/input_capture/input_capture.h"
#include "include/bus/addresses.h"

InputCapture::InputCapture(sc_module_name name) : sc_module(name) {
  read_out.initialize(1);
  address_out.initialize(BUS_ADDRESS_INPUT_CAPTURE_CONFIG);

  SC_METHOD(setConfig);
  sensitive << clock_in.pos();

  SC_METHOD(tick);
  sensitive << clock_in.pos();
}

InputCapture::~InputCapture() = default;

void InputCapture::setConfig() {
  unsigned int data = (unsigned int) data_in.read();

  unsigned int input_capture_config = data & 0x7;
  switch (input_capture_config) {
    case 0x0:
      config.is_enabled = false;
      break;

    case 0x1:
      config.is_enabled = true;
      config.prescaler_interval = 1;
      config.edge_detector_edge = EDGE_DETECTOR_EDGE_ANY;
      break;

    case 0x2:
      config.is_enabled = true;
      config.prescaler_interval = 1;
      config.edge_detector_edge = EDGE_DETECTOR_EDGE_FALLING;
      break;

    case 0x3:
      config.is_enabled = true;
      config.prescaler_interval = 1;
      config.edge_detector_edge = EDGE_DETECTOR_EDGE_RISING;
      break;

    case 0x4:
      config.is_enabled = true;
      config.prescaler_interval = 4;
      config.edge_detector_edge = EDGE_DETECTOR_EDGE_RISING;
      break;

    case 0x5:
      config.is_enabled = true;
      config.prescaler_interval = 16;
      config.edge_detector_edge = EDGE_DETECTOR_EDGE_RISING;
      break;

    case 0x6:
      config.is_enabled = true;
      config.prescaler_interval = 4;
      config.edge_detector_edge = EDGE_DETECTOR_EDGE_FALLING;
      break;

    case 0x7:
      config.is_enabled = true;
      config.prescaler_interval = 16;
      config.edge_detector_edge = EDGE_DETECTOR_EDGE_FALLING;
      break;

    default:
      throw std::invalid_argument("Default case in InputCapture:setConfig");
  }
}

void InputCapture::tick() {
  if (!config.is_enabled) {
    return;
  }

}
