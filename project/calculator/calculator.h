#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include <reg52.h>
#include "type.h"

/*操作数*/
extern uint32 operator_a, operator_b;

/*操作符*/
extern uint8 operator_cn, operator_co;

/*系统状态*/
extern bit sym_display_ab, sym_is_operate;

/**
 * @brief 运算
 */
uint8 operate_calculator();

/**
 * @brief 键盘尾部加入
 * @param par_header 前端值
 * @param par_tail 尾部值
 * @return uint32 结果
 */
uint32 push_calculator(uint32 par_header, uint32 par_tail);

/**
 * @brief 键盘尾部移除
 * @param par_header 移出的值
 * @param par_bite 移出的位数
 * @return uint32 结果
 */
uint32 pop_calculator(uint32 par_header, uint8 par_bite);

/**
 * @brief 键盘检测效应
 */
void keyboard_calculator();

#endif