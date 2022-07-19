#ifndef __TUBLE_H_
#define __TUBLE_H_

#include "type.h"

/**
 * @brief 显示数码管模块点
 * 通过par_site指定位置显示点
 * @param par_site 数码管的位序
 */
void display_point_site_tuble(uint8 par_site);

/**
 * @brief 消除除数码管模块点
 * 通过par_site指定位置消除点
 * @param par_site 数码管的位序
 */
void clear_point_site_tuble(uint8 par_site);

/**
 * @brief 修改数码管模块缓冲区
 * 通过par_site指定位置修改缓冲区的内容
 * @param par_site 数码管的位序
 * @param par_value 数码管缓冲区的内容
 */
void updata_value_site_tuble(uint8 par_site, uint8 par_value);

/**
 * @brief 修改数码管模块缓冲区内容
 * 通过par_data与par_advance结合，对缓冲区进行内容更新
 * @param par_data 显示的内容
 * @param par_advance 进制
 */
void updata_value_all_tuble(uint32 par_data, uint8 par_advance);

/**
 * @brief 显示数码管模块内容
 * 显示缓冲区所有的内容
 */
void display_all_tuble();

/**
 * @brief 显示数码管模块缓冲区内容
 * 通过par_site显示缓冲区指定位置的内容
 * @param par_site 缓冲区序列
 */
void display_site_tuble(uint8 par_site);

/**
 * @brief 显示状态，主要用于闪烁
 * @param par_site 显示状态缓冲区
 * @param par_glint 显示状态缓冲区内容
 */
void glint_site_tuble(uint8 par_site , uint8 par_glint);

#endif