#include <reg52.h>
#include "calculator.h"
#include "tuble.h"
#include "keyboard.h"
#include "interrupts.h"

uint8 count = 0;
uint16 time_count = 0;
bit sym_unit = 0,
	sym_5ms = 0,
    sym_250ms = 0,
    sym_1s = 0
    ;

int main() {
    init_t1_1_interrupt(0xF7, 0x00);
    updata_value_all_tuble(operator_a,10);
    while(1) {
        if(sym_unit) {
            sym_unit = 0;
            display_site_tuble(count++);
            count %= 8;
        }
		if(sym_5ms) {
			detect_col_keyboard();
			keyboard_calculator();
		}
        if(sym_250ms) {
            sym_250ms = 0;
            if(sym_display_ab)
				updata_value_all_tuble(operator_b,10);
			else
				updata_value_all_tuble(operator_a,10);
        }
    }
    return 0;
}

void calculator_interrupt() interrupt 3 {
    TR1 = 0;
    TH1 = 0xF7;
    TL1 = 0x00;
    TR1 = 1;
    sym_unit = 1;
    if(time_count%2 == 1) {
        sym_5ms = 1;
    }
    if(time_count%100 == 99,,) {
        sym_250ms = 1;
    }
    if(time_count >= 400) {
        sym_1s = 1;
        time_count = 0;
    }
    time_count++;
}
