#include "key.h"
#include "type.h"

/*独立按键模块引脚*/
sbit KEY1 = P3^1; // K1
sbit KEY2 = P3^0; // K2
sbit KEY3 = P3^2; // K3
sbit KEY4 = P3^3; // K4

/*独立按键状态标志*/
bit KEY1_DOWN = 0, KEY2_DOWN = 0, KEY3_DOWN = 0, KEY4_DOWN = 0; // 独立按键按下状态
bit KEY1_UP = 0, KEY2_UP = 0, KEY3_UP = 0, KEY4_UP = 0; // 独立按键释放状态

/**
 * @brief 检测独立按键模块
 */
void detect_key() {
	static uint8 KEY1_FILTER =0xFF,KEY2_FILTER=0xFF, KEY3_FILTER=0xFF,KEY4_FILTER=0xFF;
	KEY1_FILTER <<= 1;
	KEY2_FILTER <<= 1;
	KEY3_FILTER <<= 1;
	KEY4_FILTER <<= 1;
	if(KEY1) KEY1_FILTER |= 0x01;
	if(KEY2) KEY2_FILTER |= 0x01;
	if(KEY3) KEY3_FILTER |= 0x01;
	if(KEY4) KEY4_FILTER |= 0x01;
	if((KEY1_FILTER&0x0F) == 0x0D) KEY1_FILTER |= 0x02;
	if((KEY2_FILTER&0x0F) == 0x0D) KEY2_FILTER |= 0x02;
	if((KEY3_FILTER&0x0F) == 0x0D) KEY3_FILTER |= 0x02;
	if((KEY4_FILTER&0x0F) == 0x0D) KEY4_FILTER |= 0x02;
	if((KEY1_FILTER&0x0F) == 0x02) KEY1_FILTER &= 0x0D;
	if((KEY2_FILTER&0x0F) == 0x02) KEY2_FILTER &= 0x0D;
	if((KEY3_FILTER&0x0F) == 0x02) KEY3_FILTER &= 0x0D;
	if((KEY4_FILTER&0x0F) == 0x02) KEY4_FILTER &= 0x0D;
	if(KEY1_FILTER == 0xF0) KEY1_DOWN = 1;
	if(KEY2_FILTER == 0xF0) KEY2_DOWN = 1;
	if(KEY3_FILTER == 0xF0) KEY3_DOWN = 1;
	if(KEY4_FILTER == 0xF0) KEY4_DOWN = 1;
	if(KEY1_FILTER == 0x0F) KEY1_UP = 1;
	if(KEY2_FILTER == 0x0F) KEY2_UP = 1;
	if(KEY3_FILTER == 0x0F) KEY3_UP = 1;
	if(KEY4_FILTER == 0x0F) KEY4_UP = 1;
}






