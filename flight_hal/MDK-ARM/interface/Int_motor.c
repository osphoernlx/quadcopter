#include "Int_motor.h"

/**
 * @brief  传入的参数其实是比较值 最大为1000 默认值为200
 * @param  motor: 电机结构体指针
 * @retval None
 */
void Int_motor_set_speed(Motor_Struct *motor)
{
  if(motor->speed > 1000)
  {
    debug_printf("电机速度设置过大 最大为1000\r\n");
    return;
  }
  __HAL_TIM_SET_COMPARE(motor->htim, motor->channel, motor->speed);
}

/**
 * @brief  启动电机 传入具体电机的指针
 * @param  motor: 电机结构体指针
 * @retval None
 */
void Int_motor_start(Motor_Struct *motor)
{
    HAL_TIM_PWM_Start(motor->htim, motor->channel);
    
}
