#include <reg52.h>
#include "tuble.h"

/* 
    数码管模块指定显示引脚
    CBA     数码管位置
    111         7
    110         6
    101         5
    100         4
    011         3
    010         2
    001         1
    000         0
*/
sbit TUBLE_A=P2^2; 
sbit TUBLE_B=P2^3;
sbit TUBLE_C=P2^4;

/*
    数码管显示字形
    注：若想要显示小数点，则令字形码的高位为 1 即可
*/ 
code uint8 font_tuble[] = {
	0x3F, 0x06, 0x5B, 0x4F, // 0 1 2 3
    0x66, 0x6D, 0x7D, 0x07, // 4 5 6 7
    0x7F, 0x6F, 0x77, 0x7C, // 8 9 A B
    0x39, 0x5E, 0x79, 0x71,  // C D E F
	0x40, 0x00
};

/*
    数码管显示字形缓冲区
    调度不同的显示引脚，显示对应的缓冲区内容
*/
uint8 display_buffer[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 扫描数码管时显示内容
uint8 judge_buffer[8] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}; // 扫描数码管时是否显示

/**
 * @brief 显示数码管模块点
 * 通过par_site指定位置显示点
 * @param par_site 数码管的位序
 */
void display_point_site_tuble(uint8 par_site) {
    uint8 tmp_buff_site = display_buffer[par_site]  | 0x80; // 仅修改缓冲区指定位置的高位为1，保留原始数据的显示
    display_buffer[par_site] = tmp_buff_site; 
}

/**
 * @brief 消除除数码管模块点
 * 通过par_site指定位置消除点
 * @param par_site 数码管的位序
 */
void clear_point_site_tuble(uint8 par_site) {
    uint8 tmp_buff_site = display_buffer[par_site]  & 0x7F;
    display_buffer[par_site] = tmp_buff_site & 0x7F; // 仅修改缓冲区指定位置的高位为0，保留原始数据的显示
}

/**
 * @brief 修改数码管模块缓冲区
 * 通过par_site指定位置修改缓冲区的内容
 * @param par_site 数码管的位序
 * @param par_value 数码管缓冲区的内容
 */
void updata_value_site_tuble(uint8 par_site, uint8 par_value) {
    uint8 tmp_buff_site = display_buffer[par_site] & 0x80; // 保留高位，即点的显示状态
    display_buffer[par_site] = tmp_buff_site | font_tuble[par_value];
}

/**
 * @brief 修改数码管模块缓冲区内容
 * 通过par_data与par_advance结合，对缓冲区进行内容更新
 * @param par_data 显示的内容
 * @param par_advance 进制
 */
void updata_value_all_tuble(uint32 par_data, uint8 par_advance) {
    uint8 tmp_digit = 0;
    do {
        display_buffer[tmp_digit] = font_tuble[par_data%par_advance] | (0x80 & display_buffer[tmp_digit]);
		tmp_digit++;
        par_data /= 10;
    }while(par_data > 0);
    while(tmp_digit < 8) display_buffer[tmp_digit++] = 0x00;
}

/**
 * @brief 显示数码管模块内容
 * 显示缓冲区所有的内容
 */
void display_all_tuble() {
    uint8 tmp_cycle;
    for(tmp_cycle = 0; tmp_cycle < 8; ++tmp_cycle) {
        display_site_tuble(tmp_cycle);
    }
}

/**
 * @brief 显示数码管模块缓冲区内容
 * 通过par_site显示缓冲区指定位置的内容
 * @param par_site 缓冲区序列
 */
void display_site_tuble(uint8 par_site) {
    P0 = 0x00;
    TUBLE_A = par_site%2;
    TUBLE_B = par_site/2%2;
    TUBLE_C = par_site/4%2;
    if(judge_buffer[par_site])
        P0 = display_buffer[par_site];
}

/**
 * @brief 显示状态，主要用于闪烁
 * @param par_site 显示状态缓冲区
 * @param par_glint 显示状态缓冲区内容
 */
void glint_site_tuble(uint8 par_site , uint8 par_glint) {
	judge_buffer[par_site] = par_glint;
}
