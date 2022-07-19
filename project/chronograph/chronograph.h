#ifndef __CHRONOGRAPH_H__
#define __CHRONOGRAPH_H__

#include <reg52.h>
#include "type.h"

extern bit sym_zore, sym_cord;
extern uint16 chronograph_count, chronograph_cord_count;


/**
 * @brief 初始计时器
 */
void init_chronograph();

/**
 * @brief 更新计时时间
 */
void updata_chronograph();

/**
 * @brief 键盘检测效应
 */
void keyboard_chronograph();

/**
 * @brief 查看记录
 */
void look_cord_chronograph();

#endif