#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "type.h"

/**
 * IE – 中断允许控制寄存器
 * IP – 中断优先级控制寄存器
 * TMOD – 定时器工作方式寄存器
 * TCON – 定时器控制寄存器
 * SCON – 串口控制寄存器
 * THx/TLx – 定时器初值寄存器
 * EA 全局中断允许位,当此位是1时中断可用。（重要）
 * ET2 定时器/计数器2中断允许位
 * ES 串口中断允许位
 * ET1 定时器/计数器1中断允许位
 * EX1 外部中断1允许位
 * ET0 定时器/计数器0中断允许位 （重要）
 * EX0 外部中断0允许位
 */

/**
 * @brief TMOD
 * GATE 定时器/计数器的开关控制选项：定时器/计数器的开关控制仅由TCON寄存器中的TRx(x = 0,1)控制
 * C/T 定时器模式和计数器模式选择位,将该位置0则为定时器模式
 * M1M0 设置定时器/计数器工作方式：
 * 模式0,13位计数(00) 模式1,16位计数,常用此模式(00) 
 * 模式2,8位初值自动重装(00) 模式3,仅适用于T0,分为两个8位计数器,T1停止计数(00)
 * 
 */

/**
 * @brief TCON
 * TF1 定时器1溢出标志位
 * TR1 定时器1运行控制位,将该位置1时启动定时器1
 * TF0 定时器0溢出标志位
 * TR0 定时器0运行控制位,将该位置1时启动定时器0 （重要）
 * IE1 外部中断1请求标志
 * IT1 外部中断1触发方式选择位
 * IE0 外部中断0请求标志
 * IT0 外部中断0触发方式选择位
 */

/**
 * @brief THx/TLx
 * TH0与TL0组成了一个16位的计数器
 * 执行一条指令的时间是12×(1/12M) s,即计数器每1us加一
 * 
 */

/**
 * @brief INT0中断：如果产生中断则IE = 1
 * @param par_moder 中断方式：0低电平 1下降延
 */
void init_int0_interrupt(uint8 par_moder);

/**
 * @brief INT1中断：如果产生中断则IE = 1
 * @param par_moder 中断方式：0低电平 1下降延
 */
void init_int1_interrupt(uint8 par_moder);

/**
 * @brief T0中断：0方式 0xB8, 0x00 2.5ms
 * @param par_h 中断时间高位
 * @param par_l 中断时间低位
 */
void init_t0_0_interrupt(uint8 par_h, uint8 par_l);

/**
 * @brief T0中断：1方式 0xE0, 0x00 1ms
 * @param par_h 中断时间高位
 * @param par_l 中断时间低位
 */
void init_t0_1_interrupt(uint8 par_h, uint8 par_l);

/**
 * @brief T0中断：2方式 0xB8, 0xB8 2.5/32ms
 * @param par_h 中断时间高位
 * @param par_l 中断时间低位
 */
void init_t0_2_interrupt(uint8 par_h, uint8 par_l);

/**
 * @brief T0中断：3方式 0xB8, 0xB8 2.5/32ms 此时T1只能做串行通信的波特率,且工作模式为0,1,2,3
 * 重置 T0 TL0 T1 TH0
 * @param par_h 中断时间高位
 * @param par_l 中断时间低位
 */
void init_t0_3_interrupt(uint8 par_h, uint8 par_l);

/**
 * @brief T0中断：0方式 0xB8, 0x00 2.5ms
 * @param par_h 中断时间高位
 * @param par_l 中断时间低位
 */
void init_t1_0_interrupt(uint8 par_h, uint8 par_l);

/**
 * @brief T1中断：1方式 0xF7, 0x00 2.5ms
 * @param par_h 中断时间高位
 * @param par_l 中断时间低位
 */
void init_t1_1_interrupt(uint8 par_h, uint8 par_l);

/**
 * @brief T1中断：2方式 0xB8, 0xB8 2.5/32ms
 * @param par_h 中断时间高位
 * @param par_l 中断时间低位
 */
void init_t1_2_interrupt(uint8 par_h, uint8 par_l);

#endif