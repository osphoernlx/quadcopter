#ifndef INT_MOTOR_H
#define INT_MOTOR_H

#include "tim.h"
#include "Com_debug.h"
typedef struct
{
    TIM_HandleTypeDef *htim; //定时器句柄
    uint16_t channel;        //定时器通道
    uint16_t speed;          //电机速度
}Motor_Struct;
/**
 * @brief  传入的参数其实是比较值 最大为1000 默认值为200
 * @param  motor: 电机结构体指针
 * @retval None
 */
void Int_motor_set_speed(Motor_Struct *motor);


/**
 * @brief  启动电机 传入具体电机的指针
 * @param  motor: 电机结构体指针
 * @retval None
 */
void Int_motor_start(Motor_Struct *motor);

#endif



