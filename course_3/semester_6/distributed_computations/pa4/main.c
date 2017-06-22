#include "init.lib.h"

int main(int argc, const char* argv[]) {
  if (argc < 3 || strcmp(argv[1], "-p") != 0) {
    return 1;
  }

  int is_mutex_mode = 0;
  for (int i = 1; i < argc; ++i) {
    if (!strcmp("--mutexl", argv[i])) {
      is_mutex_mode = 1;
    }
  }

  int processes_amount = atoi(argv[2]) + 1;
  init_root(processes_amount, is_mutex_mode);

  return 0;
}
