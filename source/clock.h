#ifndef __CLOCK_H_
#define __CLOCK_H_

#include <reg52.h>
#include "type.h"

extern bit sym_data_time, 
	sym_data_date, 
	sym_updata_state,
	sym_state_glint,
	sym_glint
	;
extern uint8 state_time,
	glint_count_10s,
	time_glint_state
	;

/**
 * @brief 更新整体时间
 * 运行一次则秒变量加一
 */
void updata_total_time();

/**
 * @brief 更新时间
 * 刷新数码管内容
 */
void updata_time();

/**
 * @brief 更新日期
 * 刷新数码管内容
 */
void updata_date();
/**
 * @brief 闪烁小时
 * @param par_glint 闪烁状态
 */
void glint_hour(bit par_glint);

/**
 * @brief 闪烁分钟
 * @param par_glint 闪烁状态
 */
void glint_minute(bit par_glint);

/**
 * @brief 修改小时的值
 * @param par_hour 小时值
 */
void updata_hour(int8 par_hour);

/**
 * @brief 修改小时的值
 * @param par_minute 小时值
 */
void updata_minute(int8 par_minute);

/**
 * @brief 闪烁年
 * @param par_glint 
 */
void glint_year(bit par_glint);

/**
 * @brief 闪烁月
 * @param par_glint 
 */
void glint_month(bit par_glint);

/**
 * @brief 闪烁日
 * @param par_glint 
 */
void glint_day(bit par_glint);

/**
 * @brief 修改年
 * @param par_year 年值
 */
void updata_year(int8 par_year);

/**
 * @brief 修改月
 * @param par_month 月
 */
void updata_month(int8 par_month);

/**
 * @brief 修改日
 * @param par_day 日
 */
void updata_day(int8 par_day);

/**
 * @brief 键盘检测效应
 */
void keyboard_clock();
#endif