// #include "times.h"

// void delay_1ms() {
// 	uint8 cir_time = 150;
// 	while(--cir_time);
// }

// void delay_nms(uint8 par_times) {
// 	while(--par_times) {
// 		delay_1ms();
// 		delay_1ms();
// 	}
// }

// void delay_1s() {
// 	delay_nms(200);
// 	delay_nms(200);
// 	delay_nms(200);
// 	delay_nms(200);
// 	delay_nms(200);
// }

// void delay_ns(uint8 par_times) {
// 	while(--par_times) {
// 		delay_1s();
// 	}
// }


#include <reg51.h>
sbit BEEP=P1^4; //定义蜂鸣器操作相关的特殊功能位
#define beepOn() BEEP=0 //定义打开蜂鸣器的伪函数
#define beepOff() BEEP=1 //定义关闭蜂鸣器的伪函数
int main(){
int i;
while(1){
beepOn(); //打开蜂鸣器，使其发出声音
for(i=-30000;i<30000;i++); //约 500 毫秒延时
beepOff(); //关闭蜂鸣器，使其停止发声
for(i=-30000;i<30000;i++); //约 500 毫秒延时
}
}