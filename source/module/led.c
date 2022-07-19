#include <reg52.h>
#include "led.h"

/* LED模块引脚定义 */
sbit led1 = P2^0; // D1
sbit led2 = P2^1; // D2
sbit led3 = P2^2; // D3
sbit led4 = P2^3; // D4
sbit led5 = P2^4; // D5
sbit led6 = P2^5; // D6
sbit led7 = P2^6; // D7
sbit led8 = P2^7; // D8

/**
 * @brief 点亮LED模块
 * 通过 par_site指定相应的LED点亮
 * @param par_site 
 */
void on_site_led(uint8 par_site){
	switch(par_site%8){
		case D1:led1 = 0;break;
		case D2:led2 = 0;break;
		case D3:led3 = 0;break;
		case D4:led4 = 0;break;
		case D5:led5 = 0;break;
		case D6:led6 = 0;break;
		case D7:led7 = 0;break;
		case D8:led8 = 0;break;
	}
}

/**
 * @brief 熄灭LED模块
 * 通过 par_site指定相应的LED熄灭
 * @param par_site 
 */
void off_site_led(uint8 par_site){
	switch(par_site%8){
		case D1:led1 = 1;break;
		case D2:led2 = 1;break;
		case D3:led3 = 1;break;
		case D4:led4 = 1;break;
		case D5:led5 = 1;break;
		case D6:led6 = 1;break;
		case D7:led7 = 1;break;
		case D8:led8 = 1;break;
	}
}