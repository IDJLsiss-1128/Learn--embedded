#include <stdio.h>
#include "reg52.h"
#include "key.h"
#include "beep.h"
#include "interrupts.h"

bit sym_beep = 0;
uint8 count = 0;
uint16 time_count = 0;

uint8 music[] = {1+7,2+7,3+7,4+7,5+7,6+7,7+7,1+7,2+7,3+7,4+7,5+7,6+7,7+7,1+7,2+7,3+7,4+7,5+7,6+7,7+7,1+7,2+7,3+7,4+7,5+7,6+7,7+7};
uint8 length[] = {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};

int main() {
	init_t0_1_interrupt(display_player(music[count])[0], display_player(music[count])[1]);
	init_t1_1_interrupt(0xF7, 0x00);
    while(1) {
		
    }
    return 0;
}

void change_interrupt() interrupt 1 {
	TR0 = 0;
	TH0 = display_player(music[count])[0];
	TL0 = display_player(music[count])[1];
	TR0 = 1;
	if(sym_beep) on_beep();
	else off_beep();
	sym_beep = !sym_beep;
} // 音符切换

void tystem_interrupt() interrupt 3 {
	TR1 = 0;
	TH1 = 0xF7;
	TL1 = 0x00;
	TR1 = 1;
	if(time_count%50 == 1) {
		if(length[count]>0) length[count] -= 1;
		else count++;
		if(count == sizeof(length)/sizeof(uint8)) {
			count = 0;
		}
	}
	time_count++;
} // 音符播放长度