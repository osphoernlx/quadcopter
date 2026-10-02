#ifndef INT_KEY_H
#define INT_KEY_H

#include "main.h"
#include "freeRTOS.h"
#include "task.h"


//枚举按键的值
typedef enum
{
	KEY_NONE,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_LEFT_X,
	KEY_RIGHT_X,
	KEY_RIGHT_X_LONG,
}KEY_type;


/**
 * @brief  获取当前按键是否被按下
 * 
 * @return KEY_type 当前按键的值
 */
KEY_type Int_key_get(void);

#endif
