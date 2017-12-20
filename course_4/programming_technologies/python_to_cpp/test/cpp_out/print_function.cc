#include <cstdio>
#include <string>

using namespace std;

int test_function(string argument_a, string argument_b = "!") {
  printf("%s", "Hello" + argument_a + argument_b);
}
