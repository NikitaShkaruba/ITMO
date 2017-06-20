#include "lib/core/headers/init.lib.h"

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

  int initial_balances[processes_amount];
  initial_balances[0] = 0;
  for (int i = 1; i < processes_amount; i++) {
    initial_balances[i] = atoi(argv[i + 2]);
  }

  init_root(processes_amount, initial_balances, is_mutex_mode);

  return 0;
}
