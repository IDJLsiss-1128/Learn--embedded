#include "heartbeat.h"
#include "led.h"

uint8 heartbeat_site = 0;

/**
 * @brief LED模拟系统活动(心跳)
 * @param site_led led位置
 */
void start_heartbeat() {
    if(heartbeat_site < 4) {
		on_site_led(heartbeat_site);
		on_site_led(7-heartbeat_site);
	}
	else {
		off_site_led(heartbeat_site);
		off_site_led(7-heartbeat_site);
	}
}