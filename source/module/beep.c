#include <reg52.h>
#include "beep.h"

/*蜂呜器模块引脚*/
sbit BEEP = P1^5;

/*蜂呜器模块音阶*/
code uint8 scale_H[][7] = {
    0x00, // 解决0位的问题
    0x00, 0x00, 0x00, 0x00, 0xFB, 0xFB, 0xFC, // 低1,2,3,4,5,6,7 == 1,2,3,4,5,6,7
	0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, // 中1,2,3,4,5,6,7 == 1+7,2+7,3+7,4+7,5+7,6+7,7+7
	0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00  // 高1,2,3,4,5,6,7 == 1+14,2+14,3+14,4+14,5+14,6+14,7+14
	// 超高1,2,3,4,5,6,7 == 1+21,2+21,3+21,4+21,5+21,6+21,7+21
}; // 音阶高位

code uint8 scale_L[][7] = {
    0x00, // 解决0位的问题
    0x00, 0x00, 0x00, 0x00, 0x04, 0x90, 0x0C, // 低1,2,3,4,5,6,7 == 1,2,3,4,5,6,7
	0x44, 0xAC, 0x09, 0x34, 0x82, 0xC8, 0x06, // 中1,2,3,4,5,6,7 == 1+7,2+7,3+7,4+7,5+7,6+7,7+7
	0x22, 0x56, 0x85, 0x00, 0x00, 0x00, 0x00  // 高1,2,3,4,5,6,7 == 1+14,2+14,3+14,4+14,5+14,6+14,7+14
	// 超高1,2,3,4,5,6,7 == 1+21,2+21,3+21,4+21,5+21,6+21,7+21
}; // 音阶低位

/*蜂呜器模块音乐缓冲区*/
uint8 music_buff[2] = {0x00, 0x00};

/**
 * @brief 启动蜂呜器
 */
void on_beep() {
    BEEP = 0;
}

/**
 * @brief 关闭蜂呜器
 */
void off_beep() {
    BEEP = 1;
}

/**
 * @brief 播放音符
 * @param par_note 对应音符
 * @return uint8* 音符缓冲区
 */
uint8 *display_player(uint8 par_note) {
    music_buff[0] = scale_H[par_note/7][par_note%7];
    music_buff[1] = scale_L[par_note/7][par_note%7];
    return music_buff;
}