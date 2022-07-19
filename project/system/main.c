#include <reg52.h>
#include "chronograph.h"
#include "interrupts.h"
#include "calculator.h"
#include "heartbeat.h"
#include "keyboard.h"
#include "clock.h"
#include "tuble.h"
#include "type.h"
#include "key.h"

#define BOOL_TRUE 1
#define BOOL_FALSE 0

/*系统全局变量*/
uint16 sys_count = 0,
	sys_sign = 0
	;

uint8 sys_site = 0
	;

bit sym_unit = 0,
	sym_5ms = 0, // 5ms只能用作按键扫描
	sym_50ms = 0,
	sym_100ms = 0,
	sym_250ms = 0,
	sym_500ms = 0,
	sym_1s = 0
	;


/*计算器模块*/


int main() {
	init_t0_1_interrupt(0xF7, 0x00);
	updata_time();
	while(BOOL_TRUE) {
		/*周期性任务*/
		if(sym_unit) {
			sym_unit = 0;
			display_site_tuble(sys_site);
			switch(sys_sign) {
				case 0:
					if(sym_updata_state) {
						clear_point_site_tuble(4);
						clear_point_site_tuble(2);
						clear_point_site_tuble(1);
					} // 显示时间不显示点
					else {
						display_point_site_tuble(4);
						display_point_site_tuble(2);
					} // 显示年显示点
					break;
				case 1:

					break;
			}
			sys_site++;
			if(sys_site >= 8) sys_site = 0;
		}
		
		if(sym_5ms) {
			sym_5ms = 0;
			detect_key();
			detect_col_keyboard();
		}

		if(sym_50ms) {
			sym_50ms = 0;
			start_heartbeat();
			heartbeat_site++;
			switch(sys_sign) {
				case 0:

					break;
				case 1:
					
					break;
			}
			if(heartbeat_site > 8) heartbeat_site = 0;
		}

		if(sym_250ms) {
			sym_250ms = 0;
			switch(sys_sign) {
				case 0:
					break;
				case 1:
					if(sym_display_ab)
						updata_value_all_tuble(operator_b,10);
					else
						updata_value_all_tuble(operator_a,10);
					break;
			}
		}
		
		if(sym_100ms) {
			sym_100ms = 0;
			switch(sys_sign) {
				case 0:
					break;
				case 1:
					break;
				case 2:
					updata_chronograph();
					break;
			}
		}

		if(sym_500ms) {
			sym_500ms = 0;
			switch(sys_sign) {
				case 0:
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
					break;
				case 1:
					break;
			}
		}

		if(sym_1s) {
			sym_1s = 0;
			switch(sys_sign) {
				case 0:
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
					if(sym_data_time||sym_data_date) {
						sym_data_time = 0;
						if(sym_updata_state) {
							updata_time();
						}
						else {
							updata_date();
						}
					}
					break;
				case 1:
					break;
			}
			updata_total_time(); // 读秒操作
		}
		
		/*非周期性任务*/
		switch(sys_sign) {
			case 0:
				keyboard_clock();
				break;
			case 1:
				keyboard_calculator();
				break;
			case 2:
				keyboard_chronograph();
				break;
		}
		
		if(KEY1_UP && (!KEY2_UP) && (!KEY3_UP) && (!KEY4_UP)) {
			KEY1_UP = 0;
			sys_sign = 0;
			if(sym_updata_state) {
				updata_time();
			}
			else {
				updata_date();
			}
		}
		
		if((!KEY1_UP) && KEY2_UP && (!KEY3_UP) && (!KEY4_UP)) {
			KEY2_UP = 0;
			sys_sign = 1;
		}
		
		if((!KEY1_UP) && (!KEY2_UP) && KEY3_UP && (!KEY4_UP)) {
			KEY3_UP = 0;
			sys_sign = 2;
		}
	}
}

void interrupt_func() interrupt 1 {
	TR0 = 0;
	TH0 = 0xF7;
	TL0 = 0x00;
	TR0 = 1;
	sym_unit = 1;
	if(sys_count%2 == 1) {
		sym_5ms = 1;
	}
	if(sys_count%20 == 13) {
		sym_50ms =1;
	}
	if(sys_count%40 == 37) {
		sym_100ms = 1;
	}
	if(sys_count%100 == 83) {
		sym_250ms = 1;
	}
	if(sys_count%200 == 171) {
		sym_500ms = 1;
	}
	if(sys_count >= 400) {
		sym_1s = 1;
		sys_count = 0;
	}
	sys_count++;
} // T0 用作系统时间(心跳)