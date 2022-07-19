#ifndef __KEY_H__
#define __KEY_H__

#include <reg52.h>

/*独立按键状态标志*/
extern bit KEY1_DOWN, KEY2_DOWN, KEY3_DOWN, KEY4_DOWN; // 独立按键按下状态
extern bit KEY1_UP, KEY2_UP, KEY3_UP, KEY4_UP; // 独立按键释放状态

/**
 * @brief 检测独立按键模块
 */
void detect_key();

#endif