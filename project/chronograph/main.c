#include <reg52.h>
#include "chronograph.h"
#include "interrupts.h"
#include "tuble.h"
#include "keyboard.h"

bit sym_100ms = 0, sym_5ms = 0, sym_25ms = 0;
uint8 chronograph_site = 0;
uint16 system_chronograph_count = 0;

int main() {
    init_t0_1_interrupt(0xF7, 0x00);
    init_chronograph();
    while(1) {
		if(sym_5ms) {
			sym_5ms = 0;
			display_site_tuble(chronograph_site);
			chronograph_site++;
			if(chronograph_site >= 8) chronograph_site = 0;
		} // 扫描数码管
		if(sym_25ms) {
			detect_col_keyboard();
			keyboard_chronograph();
		} // 扫描键盘
		if(sym_100ms) {
			sym_100ms = 0;
			updata_chronograph();
		} // 更新计时
    }
    return 0;
}

void chronograph_interrupt() interrupt 1 {
    TR0 = 0;
	TH0 = 0xF7;
	TL0 = 0x00;
	TR0 = 1;
	if(system_chronograph_count%2 == 1) {
		sym_5ms = 1;
	}
	if(system_chronograph_count%10 == 7) {
		sym_25ms = 1;
	}
	if(system_chronograph_count%40 == 37) {
		sym_100ms = 1;
	}
	if(system_chronograph_count >= 400) {
		system_chronograph_count = 0;
	}
	system_chronograph_count++;
}
