#include <reg52.h>
#include<intrins.h>
#include "lattice.h"

/*LED点阵模块的引脚*/
sbit LARRICE_SCK = P3^6; // 移位寄存器时钟信号 ： 当上升延则将队列中的数据全部输入到LED点阵
sbit LARRICE_RCK = P3^5; // 存储寄存器时钟信号 ：当上升延则队列整体位移一位
sbit LARRICE_SER = P3^4; // 串行输入口 ：在队列尾部插入一位数据

/*LED点阵模块对应列显示的信号*/
code uint8 col_lattice[8] = {
    0x7F, // 第1列
    0xBF, // 第2列
    0xDF, // 第3列
    0xEF, // 第4列
    0xF7, // 第5列
    0xFB, // 第6列
    0xFD, // 第7列
    0xFE  // 第8列
};

/*LED点阵模块对应行缓冲区*/
uint8 col_display_buff_lattice[8] = {
    0x00, // 第1行
    0x00, // 第2行
    0x00, // 第3行
    0x00, // 第4行
    0x00, // 第5行
    0x00, // 第6行
    0x00, // 第7行
    0x00  // 第8行
};

/*LED点阵模块对应行显示的信号*/
code uint8 row_lattice[][8] = {
    /*数字0~9*/
    0x00,0x00,0x3E,0x41,0x41,0x3E,0x00,0x00, // 0
    0x00,0x00,0x21,0x3F,0x7F,0x01,0x00,0x00, // 1
    0x00,0x00,0x23,0x45,0x49,0x31,0x00,0x00, // 2
    0x00,0x00,0x22,0x41,0x49,0x36,0x00,0x00, // 3
    0x00,0x00,0x1C,0x24,0x7F,0x04,0x00,0x00, // 4
    0x00,0x00,0x72,0x51,0x51,0x4E,0x00,0x00, // 5
    0x00,0x00,0x3E,0x49,0x49,0x26,0x00,0x00, // 6
    0x00,0x00,0x40,0x40,0x5F,0x60,0x00,0x00, // 7
    0x00,0x00,0x36,0x49,0x49,0x36,0x00,0x00, // 8
    0x00,0x00,0x32,0x49,0x49,0x3E,0x00,0x00, // 9

    /*字母a~z*/

    /*字母A~Z*/
};

/**
 * @brief 写入一个字节
 * @param par_bit 输入字节内容
 */
void write_bit_lattice(uint8 par_bit) {
    uint8 tmp_site;
    LARRICE_SCK = 0;
    LARRICE_RCK = 0;
    for(tmp_site = 0; tmp_site < 8; ++tmp_site) {
        LARRICE_SER = par_bit>>7; // 插入字节的高位
        par_bit <<= 1; // 将字节向左移动一位
        LARRICE_SCK = 1; // 队列移动一位
        _nop_();
		_nop_();
        LARRICE_SCK = 0;
    } // 串行输入
    LARRICE_RCK = 1; // 并行输出
    _nop_();
	_nop_();
    LARRICE_RCK = 0; // 完成串并转换
}

/**
 * @brief 更新LED点阵字形
 * @param par_data 字形
 */
void updata_lattice(uint8 par_data) {
    uint8 tmp_col = 0, tmp_site;
    if(par_data >= '0' && par_data <= '9')  tmp_col= 0+par_data-'0';
    else if(par_data >= 'a' && par_data <= 'z') tmp_col = 10+par_data-'a';
    else if(par_data >= 'A' && par_data <= 'Z') tmp_col = 35+par_data-'Z';
    for(tmp_site = 0; tmp_site < 8; tmp_site++) {
        col_display_buff_lattice[tmp_site] = row_lattice[tmp_col][tmp_site];
    }
}

/**
 * @brief 获取LED点阵模块缓冲区
 * @param par_site 位序
 * @return uint8 内容
 */
uint8 get_buff_lattice(uint8 par_site) {
    return col_display_buff_lattice[par_site];
}

/**
 * @brief 显示LED点阵模块列内容
 * @param par_col 列序
 * @param par_data 内容
 */
void display_row_lattice(uint8 par_col, uint8 par_data) {
    write_bit_lattice(par_data);
    P0 = col_lattice[par_col];
}

/**
 * @brief LED点阵显示缓冲区内容
 * @param par_data 字形
 */
void display_lattice(uint8 par_data) {
    updata_lattice(par_data);
	display_row_lattice(0,get_buff_lattice(0));
	display_row_lattice(1,get_buff_lattice(1));
	display_row_lattice(2,get_buff_lattice(2));
	display_row_lattice(3,get_buff_lattice(3));
	display_row_lattice(4,get_buff_lattice(4));
	display_row_lattice(5,get_buff_lattice(5));
	display_row_lattice(6,get_buff_lattice(6));
	display_row_lattice(7,get_buff_lattice(7));
    _nop_();
	_nop_();
    P0 = 0xFF;
}
