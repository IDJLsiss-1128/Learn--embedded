#include "clock.h"
#include "tuble.h"

bit sym_data_time = 0, sym_data_date = 0;
int16 year = 2020;
int8 month = 1, day = 1, hour = 0, minute = 0, second = 0;

uint8 day_of_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

uint8 is_leap() {
	if(year%4 == 0) {
		if(year%100 == 0 && year%400 != 0) {
			return 0;
		}
		return 1;
	}
	return 0;
}


void updata_total_time() {
	second++;
	sym_data_time = 1;
	if(second > 59) {
		second = 0;
		minute++;
		if(minute > 59) {
			minute = 0;
			hour++;
			if(hour > 23) {
				hour = 0;
				sym_data_date = 1;
				day++;
				if(day > day_of_month[(month-1)%12]+is_leap()) {
					day = 1;
					month++;
					if(month > 12) {
						month = 1;
						year++;
					}
				}
			}
		}
	}

}


void updata_time() {
	/*更新时*/
	updata_value_site_tuble(7, hour/10%10);
	updata_value_site_tuble(6, hour/1%10);
	
	updata_value_site_tuble(5, 16);
	/*更新分*/
	updata_value_site_tuble(4, minute/10%10);
	updata_value_site_tuble(3, minute/1%10);

	updata_value_site_tuble(2, 16);
	/*更新秒*/
	updata_value_site_tuble(1, second/10%10);
	updata_value_site_tuble(0, second/1%10);
}

void updata_date() {
	/*更新年*/
	updata_value_site_tuble(7, year/1000%10);
	updata_value_site_tuble(6, year/100%10);
	updata_value_site_tuble(5, year/10%10);
	updata_value_site_tuble(4, year/1%10);

	/*更新月*/
	updata_value_site_tuble(3, month/10%10);
	updata_value_site_tuble(2, month/1%10);

	/*更新日*/
	updata_value_site_tuble(1, day/10%10);
	updata_value_site_tuble(0, day/1%10);
}

/**
 * @brief 闪烁小时
 * @param par_glint 闪烁状态
 */
void glint_hour(bit par_glint) {
	glint_site_tuble(7, par_glint);
	glint_site_tuble(6, par_glint);
	glint_site_tuble(5, 0x01);
	glint_site_tuble(4, 0x01);
	glint_site_tuble(3, 0x01);
	glint_site_tuble(2, 0x01);
	glint_site_tuble(1, 0x01);
	glint_site_tuble(0, 0x01);
}

/**
 * @brief 闪烁分钟
 * @param par_glint 闪烁状态
 */
void glint_minute(bit par_glint) {
	glint_site_tuble(7, 0x01);
	glint_site_tuble(6, 0x01);
	glint_site_tuble(5, 0x01);
	glint_site_tuble(4, par_glint);
	glint_site_tuble(3, par_glint);
	glint_site_tuble(2, 0x01);
	glint_site_tuble(1, 0x01);
	glint_site_tuble(0, 0x01);
}

/**
 * @brief 闪烁年
 * @param par_glint 
 */
void glint_year(bit par_glint) {
	glint_site_tuble(7, par_glint);
	glint_site_tuble(6, par_glint);
	glint_site_tuble(5, par_glint);
	glint_site_tuble(4, par_glint);
	glint_site_tuble(3, 0x01);
	glint_site_tuble(2, 0x01);
	glint_site_tuble(1, 0x01);
	glint_site_tuble(0, 0x01);
}

/**
 * @brief 闪烁月
 * @param par_glint 
 */
void glint_month(bit par_glint) {
	glint_site_tuble(7, 0x01);
	glint_site_tuble(6, 0x01);
	glint_site_tuble(5, 0x01);
	glint_site_tuble(4, 0x01);
	glint_site_tuble(3, par_glint);
	glint_site_tuble(2, par_glint);
	glint_site_tuble(1, 0x01);
	glint_site_tuble(0, 0x01);
}

/**
 * @brief 闪烁日
 * @param par_glint 
 */
void glint_day(bit par_glint) {
	glint_site_tuble(7, 0x01);
	glint_site_tuble(6, 0x01);
	glint_site_tuble(5, 0x01);
	glint_site_tuble(4, 0x01);
	glint_site_tuble(3, 0x01);
	glint_site_tuble(2, 0x01);
	glint_site_tuble(1, par_glint);
	glint_site_tuble(0, par_glint);
}

/**
 * @brief 修改小时的值
 * @param par_hour 小时值
 */
void updata_hour(int8 par_hour) {
	hour += par_hour;
	if(hour > 23) {
		hour = 0;
	}
	else if(hour < 0) {
		hour = 23;
	}
	second = 0;
	updata_time();
}

/**
 * @brief 修改小时的值
 * @param par_minute 小时值
 */
void updata_minute(int8 par_minute) {
	minute += par_minute;
	if(minute > 59) {
		minute = 0;
		hour++;
		if(hour > 23) {
			hour = 0;
		}
	}
	else if(minute < 0) {
		minute = 59;
		hour--;
	}
	second = 0;
	updata_time();
}

/**
 * @brief 修改年
 * @param par_year 年值
 */
void updata_year(int8 par_year) {
	year += par_year;
	if(year > 9999) {
		year = 0;
	}
	else if(month < 0) {
		year = 9999;
	}
	month = 1;
	day = 1;
	updata_date();
}

/**
 * @brief 修改月
 * @param par_month 月
 */
void updata_month(int8 par_month) {
	month += par_month;
	if(month > 12) {
		month = 1;
	}
	else if(month < 1) {
		month = 12;
	}
	day = 1;
	updata_date();
}

/**
 * @brief 修改日
 * @param par_day 日
 */
void updata_day(int8 par_day) {
	day += par_day;
	if(month == 2) {
		if(day > day_of_month[month-1]+is_leap()) {
			day = 1;
		}
		else if(day < 1) {
			day = day_of_month[month-1]+is_leap();
		}
	}
	else {
		if(day > day_of_month[month-1]) {
			day = 1;
		}
		else if(day < 1) {
			day = day_of_month[month-1];
		}
	}
	
	updata_date();
}

