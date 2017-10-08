#pragma once

class Config {
public:
  unsigned int capture_config = 0;
  unsigned int timer_config = 0;

  bool is_buffer_empty = 0;
  bool is_buffer_full = 0;
  unsigned int reserve = 0;
};
