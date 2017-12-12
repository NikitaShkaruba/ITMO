
#include <xil_io.h>
#define GPIO  0x40000000

#define TCSR0 0x41C00000
#define TLR0 0x41C00004
#define TCR0 0x41C00008

#define TCSR1 0x41C00010
#define TLR1 0x41C00014
#define TCR1 0x41C00018

void delay_10ms() {
	for(u32 n = 0; n < 66; n++);
}

int main() {
	u32 timer_config=1<<9 | 1<<7 | 1<<2 | 1<<1;
	//bit 9 - Enable pwm
	//bit 7 - Enable timer
	//bit 2 - Enable external generate signal
	//bit 1 - Down counter

	while(1) {
		for(u32 per = 50; per <= 70; per += 10){
			Xil_Out32(GPIO, per * 10);

			Xil_Out32(TLR0, per-2);   //period of pwm - 2
			Xil_Out32(TLR1, per/2-2); //period of 1 - 2

			Xil_Out32(TCSR0, timer_config);
			Xil_Out32(TCSR1, timer_config);

			delay_10ms();
		}
	}
}
