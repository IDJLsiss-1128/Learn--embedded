#include "heartbeat.h"
#include "led.h"

/**
 * @brief LED模拟系统活动(心跳)
 * @param site_led led位置
 */
void start_heartbeat(uint8 site_led) {
    if(site_led < 4) {
		on_site_led(site_led);
		on_site_led(7-site_led);
	}
	else {
		off_site_led(site_led);
		off_site_led(7-site_led);
	}
}