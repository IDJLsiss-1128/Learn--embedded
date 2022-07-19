#include <reg52.h>
#include "heartbeat.h"
#include "interrupts.h"
bit sym_500ms = 0;
uint8 count = 0, site_led = 0;
int main() {
	init_t0_1_interrupt(0xF7, 0x00);
	while(1) {
		if(sym_500ms) {
			sym_500ms = 0;
			start_heartbeat(site_led);
			site_led++;
			if(site_led > 8) site_led = 0;
		}
	}
	return 0;
}

void interrupt_func() interrupt 1 {
	TR0 = 0;
	TH0 = 0xF7;
	TL0 = 0x00;
	TR0 = 1;
	if(++count >= 200) {
		count = 0;
		sym_500ms = 1;
	}
}