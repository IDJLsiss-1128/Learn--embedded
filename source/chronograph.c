#include "chronograph.h"
#include "tuble.h"
#include "keyboard.h"

bit sym_run = 0, // 计时与暂停
	sym_cord = 0; // 计时与记录
uint8 cord_count = 0, cord_count_free = 0; // 记录游标
uint16 chronograph_count = 0,  // 正常计时
	chronograph_cord_count = 0; // 当前记录
uint16 chronograph_cord[10] = {0,0,0,0,0,0,0,0,0,0};

void init_chronograph_cord() {
	uint8 cir_index = 0;
	for(cir_index = 0; cir_index < 10; cir_index++) chronograph_cord[cir_index] = 0;
}

/**
 * @brief 初始计时器
 */
void init_chronograph() {
	display_point_site_tuble(1);
	updata_value_site_tuble(0,0);
	updata_value_site_tuble(1,0);
}

/**
 * @brief 更新计时时间
 */
void updata_chronograph() {
	if(sym_run) {
		chronograph_count++;
		if(chronograph_count >= 10) sym_zore = 0;
	}
	if(sym_cord) {
		updata_value_all_tuble(chronograph_cord_count, 10);
		if(!chronograph_cord_count) updata_value_site_tuble(1,0);
	} // 显示记录
	else {
		updata_value_all_tuble(chronograph_count, 10);
		if(!(chronograph_count/10)) updata_value_site_tuble(1,0);
	} // 显示计时
	display_point_site_tuble(1);
	chronograph_count %= 10000000;
}

/**
 * @brief 键盘检测效应
 */
void keyboard_chronograph() {
	if(KEYBOARD4_DOWN) {
		KEYBOARD4_DOWN = 0;
		cord_count_free++;
		look_cord_chronograph();
		if(cord_count_free >= 10) cord_count_free = 0;
	}
	if(KEYBOARD8_DOWN) {
		KEYBOARD8_DOWN = 0;
		cord_count_free--;
		look_cord_chronograph();
		if(cord_count_free >= 10) cord_count_free = 9;
	}
	if(KEYBOARD12_DOWN) {
		KEYBOARD12_DOWN = 0;
		if((cord_count < 10) && (chronograph_cord[cord_count] == 0)) {
			chronograph_cord[cord_count++] = chronograph_count;
		} // 将当前时间记录到数组
	}
	if(KEYBOARD13_DOWN) {
		KEYBOARD13_DOWN = 0;
		chronograph_count = 0,
		chronograph_cord_count = 0;
		sym_zore = 1;
		sym_run = 0;
		cord_count = 0;
		cord_count_free;
		init_chronograph_cord();
	}
	if(KEYBOARD15_DOWN) {
		KEYBOARD15_DOWN = 0;
		sym_run = !sym_run;
	}
	if(KEYBOARD16_DOWN) {
		KEYBOARD16_DOWN = 0;
		sym_cord = !sym_cord;
		look_cord_chronograph();
	}
	/*防止与其它程序的按键反应冲突*/
	if(KEYBOARD1_DOWN) {
		KEYBOARD1_DOWN = 0;
	}
	if(KEYBOARD2_DOWN) {
		KEYBOARD2_DOWN = 0;
	}
	if(KEYBOARD3_DOWN) {
		KEYBOARD3_DOWN = 0;
	}
	
	if(KEYBOARD5_DOWN) {
		KEYBOARD5_DOWN = 0;
	}
	if(KEYBOARD6_DOWN) {
		KEYBOARD6_DOWN = 0;
	}
	if(KEYBOARD7_DOWN) {
		KEYBOARD7_DOWN = 0;
	}
	
	if(KEYBOARD9_DOWN) {
		KEYBOARD9_DOWN = 0;
	}
	if(KEYBOARD10_DOWN) {
		KEYBOARD10_DOWN = 0;
	}
	if(KEYBOARD11_DOWN) {
		KEYBOARD11_DOWN = 0;
	}
	if(KEYBOARD14_DOWN) {
		KEYBOARD14_DOWN = 0;
	}
	if(KEYBOARD16_DOWN) {
		KEYBOARD16_DOWN = 0;
	}
}

/**
 * @brief 查看记录
 */
void look_cord_chronograph() {
	display_point_site_tuble(1);
	chronograph_cord_count = chronograph_cord[cord_count_free%10];
}