#include <xil_io.h>
#define GPIO_ADDRESS  0x40000000

int main() {
  Xil_Out32(GPIO_ADDRESS, 0xAA0A);
  while(1);
}
