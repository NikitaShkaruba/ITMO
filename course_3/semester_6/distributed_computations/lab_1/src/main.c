#include "lib/init.lib.h"

int main(int argc, const char* argv[]) {
  if (argc < 3 || strcmp(argv[1], "-p") != 0) {
    return 1;
  }

  int processes_amount = atoi(argv[2]) + 1;
  init_root(processes_amount);

  return 0;
}
