#ifndef __CLOCK_H_
#define __CLOCK_H_

#include <reg52.h>
#include "type.h"

extern bit sym_data_time, sym_data_date;

void updata_total_time();
void updata_time();
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


#endif