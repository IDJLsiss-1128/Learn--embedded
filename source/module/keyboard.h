#ifndef __KEYKEYBOARD_H__
#define __KEYKEYBOARD_H__

#include <reg52.h>

/*矩阵键盘模块按键状态*/
extern bit KEYBOARD1_DOWN, KEYBOARD2_DOWN, KEYBOARD3_DOWN, KEYBOARD4_DOWN,
		KEYBOARD5_DOWN, KEYBOARD6_DOWN, KEYBOARD7_DOWN, KEYBOARD8_DOWN, 
		KEYBOARD9_DOWN, KEYBOARD10_DOWN, KEYBOARD11_DOWN, KEYBOARD12_DOWN, 
		KEYBOARD13_DOWN, KEYBOARD14_DOWN, KEYBOARD15_DOWN, KEYBOARD16_DOWN;

/**
 * @brief 列方式进行矩阵键盘检测
 */
void detect_row_keyboard();

/**
 * @brief 行方式进行矩阵键盘检测
 */
void detect_col_keyboard();
#endif