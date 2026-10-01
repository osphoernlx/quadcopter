#ifndef __INT_JOYSTICK_H__
#define __INT_JOYSTICK_H__


#include "adc.h"
#include "FreeRTOS.h"
#include "task.h"

typedef struct
{
    int16_t thr;
    int16_t yaw;
    int16_t pit;
    int16_t rol;

} Joystick_Struct;



/**
 * @brief  初始化ADC遥控 开启ADC采集
 * @param  无
 */
void Int_joystick_init(void);


/**
 * @brief  获取当前摇杆的值
 * @param  joystick 摇杆结构体指针
 */
void Int_joystick_get(Joystick_Struct *joystick);


#endif


