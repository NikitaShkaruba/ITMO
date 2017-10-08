#pragma once

const unsigned int EDGE_DETECTOR_EDGE_ANY = 0;
const unsigned int EDGE_DETECTOR_EDGE_RISING = 1;
const unsigned int EDGE_DETECTOR_EDGE_FALLING = 2;

class Config {
public:
  bool is_enabled = 0;

  unsigned int prescaler_interval = 0;
  unsigned int edge_detector_edge = 0;
};
