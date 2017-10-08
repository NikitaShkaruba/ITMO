#pragma once

const unsigned int CONFIG_EDGE_ANY = 0;
const unsigned int CONFIG_EDGE_RISING = 1;
const unsigned int CONFIG_EDGE_FALLING = 2;

class Config {
public:
  bool is_enabled = 0;

  unsigned int scale = 0;
  unsigned int edge = 0;
};
