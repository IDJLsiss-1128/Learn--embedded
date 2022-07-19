#ifndef __LATTICE_H__
#define __LATTICE_H__

#include "type.h"

/**
 * @brief 74HC595写入一个字节
 * @param par_bit 输入字节内容
 */
void write_bit_lattice(uint8 par_bit);

/**
 * @brief 更新LED点阵字形
 * @param par_data 字形
 */
void updata_lattice(uint8 par_data);

/**
 * @brief 获取LED点阵模块缓冲区
 * @param par_site 位序
 * @return uint8 内容
 */
uint8 get_buff_lattice(uint8 par_site);

/**
 * @brief 点亮LED点阵模块列内容
 * @param par_col 列序
 * @param par_data 内容
 */
void display_row_lattice(uint8 par_col, uint8 par_data);

/**
 * @brief LED点阵显示缓冲区内容
 * @param par_data 字形
 */
void display_lattice(uint8 par_data);

#endif