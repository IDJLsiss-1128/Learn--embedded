#ifndef __BEEP_H__
#define __BEEP_H__

#include "type.h"

/**
 * @brief 启动蜂呜器
 */
void on_beep();

/**
 * @brief 关闭蜂呜器
 */
void off_beep();

/**
 * @brief 播放音符
 * @param par_note 对应音符
 * @return uint8* 音符缓冲区
 */
uint8 *display_player(uint8 par_note);

#endif