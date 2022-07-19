#include "calculator.h"
#include "keyboard.h"

/*操作数*/
uint32 operator_a = 0, operator_b = 0; // 运算结果 输入数值

/*操作符*/
uint8 operator_cn = '\0', operator_co = '+' ; // 记录当前的运算符状态

/*系统状态*/
uint8 system_state = 0;
bit sym_display_ab = 0; // a(0) b(1)
bit sym_is_operate = 1; // 判断是否生效上一次计算
bit sym_equal = 0;

/**
 * @brief 运算
 * @return uint8 返回计算状态
 */
uint8 operate_calculator() {
	switch(operator_co) {
		case '+':
			operator_a = operator_a+operator_b;
			break;
		case '-':
			operator_a = operator_a-operator_b;
			break;
		case '*':
			operator_a = operator_a*operator_b;
			break;
		case '/':
			if(!operator_b) return 0; // 分母为0则要做异常处理
			operator_a = operator_a/operator_b;
			break;
	}
	operator_b = 0;
	return 1;
}

/**
 * @brief 键盘尾部加入
 * @param par_header 前端值
 * @param par_tail 尾部值
 * @return uint32 结果
 */
uint32 push_calculator(uint32 par_header, uint32 par_tail) {
	uint32 tmp_tail = par_tail;
	do {
        par_header *= 10;
        tmp_tail /= 10;
    }while(tmp_tail > 0);
    return (par_header+par_tail)%100000000;
}

/**
 * @brief 键盘尾部移除
 * @param par_header 移出的值
 * @param par_bite 移出的位数
 * @return uint32 结果
 */
uint32 pop_calculator(uint32 par_header, uint8 par_bite) {
	while(par_bite > 0) {
		par_bite--;
		par_header /= 10;
	}
	return par_header;
}

/**
 * @brief 键盘检测效应
 */
void keyboard_calculator() {

	/*数字键*/
	if(KEYBOARD9_DOWN) {
		KEYBOARD9_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 1);
	}
	if(KEYBOARD10_DOWN) {
		KEYBOARD10_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 2);
	}
	if(KEYBOARD11_DOWN) {
		KEYBOARD11_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 3);
	}
	if(KEYBOARD5_DOWN) {
		KEYBOARD5_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 4);
	}
	if(KEYBOARD6_DOWN) {
		KEYBOARD6_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 5);
	}
	if(KEYBOARD7_DOWN) {
		KEYBOARD7_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 6);
	}
	if(KEYBOARD1_DOWN) {
		KEYBOARD1_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 7);
	}
	if(KEYBOARD2_DOWN) {
		KEYBOARD2_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 8);
	}
	if(KEYBOARD3_DOWN) {
		KEYBOARD3_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 9);
	}
	if(KEYBOARD14_DOWN) {
		KEYBOARD14_DOWN = 0;
		if(sym_equal) {
			operator_a = 0;
		}
		sym_display_ab = 1;
		sym_is_operate = 1;
		sym_equal = 0;
		operator_b = push_calculator(operator_b, 0);
	}

	/*运算键*/
	if(KEYBOARD4_DOWN) {
		KEYBOARD4_DOWN = 0;
		operator_cn = '+';
		if(sym_is_operate) {
			operate_calculator();
			sym_is_operate = 0;
			sym_display_ab = 0;
		}
		sym_equal = 0;
		operator_co = operator_cn;
	}
	if(KEYBOARD8_DOWN) {
		KEYBOARD8_DOWN = 0;
		operator_cn = '-';
		if(sym_is_operate) {
			operate_calculator();
			sym_is_operate = 0;
			sym_display_ab = 0;
		}
		sym_equal = 0;
		operator_co = operator_cn;
	}
	if(KEYBOARD12_DOWN) {
		KEYBOARD12_DOWN = 0;
		operator_cn = '*';
		if(sym_is_operate) {
			operate_calculator();
			sym_is_operate = 0;
			sym_display_ab = 0;
		}
		sym_equal = 0;
		operator_co = operator_cn;
	}
	if(KEYBOARD16_DOWN) {
		KEYBOARD16_DOWN = 0;
		operator_cn = '/';
		if(sym_is_operate) {
			operate_calculator();
			sym_is_operate = 0;
			sym_display_ab = 0;
		}
		sym_equal = 0;
		operator_co = operator_cn;
	}

	/*等于键*/
	if(KEYBOARD15_DOWN) {
		KEYBOARD15_DOWN = 0;
		operate_calculator();
		sym_is_operate = 0;
		sym_display_ab = 0;
		sym_equal = 1;
		operator_cn = '\0';
		operator_co = '+' ;
	}

	/*删除键*/
	if(KEYBOARD13_DOWN) {
		KEYBOARD13_DOWN = 0;
		if(sym_is_operate)
			operator_b = pop_calculator(operator_b, 1);
		else {
			operator_a = 0;
			operator_b = 0;
			operator_cn = '\0';
			operator_co = '+' ;
			sym_display_ab = 0;
			sym_is_operate = 1;
			sym_equal = 0;
		}
	}
}