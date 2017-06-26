#include "init.lib.h"

int main(int argc, const char* argv[]) {
  int is_mutex_mode = 0;
  int processes_amount = 0;

  for (int i = 1; i < argc; ++i) {
    if (!strcmp("--mutexl", argv[i])) {
      is_mutex_mode = 1;
    }
    if (!strcmp("-p", argv[i])) {
      processes_amount = atoi(argv[i+1]) + 1;
    }
  }

  init_root(processes_amount, is_mutex_mode);
  return 0;
}
