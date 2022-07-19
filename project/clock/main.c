#include <reg52.h>
#include "clock.h"
#include "tuble.h"
#include "interrupts.h"
#include "keyboard.h"
uint16 count = 0;
bit sym_1s = 0, sym_500ms = 0, sym_5ms = 0, sym_1ms = 0;
bit sym_glint = 0,  // 修改状态
	sym_state_glint = 0, // 闪烁状态
	sym_updata_state = 1 // 时间与日期状态
	;
uint8 state_time = 0, glint_count_10s = 10;
int main() {
	uint8 site_ = 0;
    init_t0_1_interrupt(0xF7, 0x00);
	updata_time();
    while(1) {
		
		if(sym_5ms) {
			sym_5ms = 1;
			detect_col_keyboard();
		} // 5ms扫描一次按键
		
        if(sym_1ms) {
			sym_1ms = 0;
			display_site_tuble(site_); // 扫描数码管
			if(sym_updata_state) {
				clear_point_site_tuble(4);
				clear_point_site_tuble(2);
			} // 显示时间不显示点
			else {
				display_point_site_tuble(4);
				display_point_site_tuble(2);
			} // 显示年显示点
			if(++site_ >= 8) site_ = 0;
		}
		
		if(sym_500ms) {
			sym_500ms = 0;
			if(sym_state_glint) {
				if(sym_updata_state) {
					switch (state_time) {
						case 1:
							glint_hour(sym_glint|0x00);
							break;
						case 2:
							glint_minute(sym_glint|0x00);
							break;
					}
				} // 显示时间
				else {
					switch (state_time) {
						case 1:
							glint_year(sym_glint|0x00);
							break;
						case 2:							
							glint_month(sym_glint|0x00);
							break;
						case 3:
							glint_day(sym_glint|0x00);
							break;
					}
				} // 显示日期
			}
			sym_glint = !sym_glint;
		}
		
		if(sym_1s) {
			sym_1s = 0;
			glint_count_10s--;
			if(glint_count_10s <= 0) {
				sym_state_glint = 0;
				if(sym_updata_state) {
					glint_hour(0x01);
					glint_minute(0x01);
				} // 恢复正常时间
				else {
					glint_year(0x01);
					glint_month(0x01);
					glint_day(0x01);
				} // 恢复正常日期
				glint_count_10s = 10;
				state_time = 0;
			} // 10秒钟没有操作则恢复正常
			updata_total_time(); // 读秒操作
			if(sym_data_time||sym_data_date) {
				sym_data_time = 0;
				if(sym_updata_state) {
					updata_time();
				}
				else {
					updata_date();
				}
			}
		} // 更新时间
		
		if(KEYBOARD13_DOWN) {
			KEYBOARD13_DOWN = 0;
			sym_updata_state = !sym_updata_state; // 更替时间与日期
			if(sym_updata_state) {
				glint_hour(0x01);
				glint_minute(0x01);
				updata_time();
			} // 改变时间闪烁状态
			else {
				glint_year(0x01);
				glint_month(0x01);
				glint_day(0x01);
				updata_date();
			} // 改变日期闪烁状态
			state_time = 0; // 修改状态重置状态
		}
		
		if(KEYBOARD15_DOWN) {
			KEYBOARD15_DOWN = 0;
			sym_state_glint = 1;
			glint_count_10s = 10;
			state_time++;
			if(sym_updata_state) {
				if(state_time >= 3) {
					state_time = 0;
					sym_state_glint = 0;
					glint_hour(1);
				}
			} // 改变时间修改状态
			else {
				if(state_time >= 4) {
					state_time = 0;
					sym_state_glint = 0;
					glint_hour(1);
				}
			} // 改变日期修改状态
			
		} // 时间设置触发 1 时/年 2 分/月 3 月
		
		if(KEYBOARD4_DOWN) {
			KEYBOARD4_DOWN = 0;
			if(sym_state_glint) {
				glint_count_10s = 10;
				if(sym_updata_state) {
					switch (state_time) {
						case 1:
							updata_hour(1);
							break;
						case 2:
							updata_minute(1);
							break;
					}
				} // 增加时间状态
				else {
					switch (state_time) {
						case 1:
							updata_year(1);
							break;
						case 2:
							updata_month(1);
							break;
						case 3:
							updata_day(1);
							break;
					}
				} // 增加日期状态
			}
		} // S4下调数值

		if(KEYBOARD8_DOWN) {
			KEYBOARD8_DOWN = 0;
			if(sym_state_glint) {
				glint_count_10s = 10;
				if(sym_updata_state) {
					switch (state_time) {
						case 1:
							updata_hour(-1);
							break;
						case 2:
							updata_minute(-1);
							break;
					}
				} // 减少时间状态
				else {
					switch (state_time) {
						case 1:
							updata_year(-1);
							break;
						case 2:
							updata_month(-1);
							break;
						case 3:
							updata_day(-1);
							break;
					}
				}  // 减少日期状态
			}
		} // S8下调数值
    }
    return 0;
}

void clock_interrupt() interrupt 1 {
	TR0 = 0;
	TH0 = 0xF7;
	TL0 = 0x00;
	TR0 = 1;
	sym_1ms = 1;
	if(count%2 == 1) {
		sym_5ms = 1;
	}
	if(count%200 == 199) {
		sym_500ms = 1;
	}
	if(count >= 400) {
		count = 0;
		sym_1s = 1;
	}
	count++;
}
