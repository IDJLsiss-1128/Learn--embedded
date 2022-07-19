#ifndef __LED_H__
#define __LED_H__

#include "type.h"

extern uint8 heartbeat_site;

/* LED模块对应的LED位置 */
enum led_site {D1, D2, D3, D4, D5, D6, D7, D8};

/**
 * @brief 点亮LED模块
 * 通过 par_site指定相应的LED点亮
 * @param par_site 
 */
void on_site_led(uint8 par_site);

/**
 * @brief 熄灭LED模块
 * 通过 par_site指定相应的LED熄灭
 * @param par_site 
 */
void off_site_led(uint8 par_site);

#endif