#ifndef INT_LED_H
#define INT_LED_H

#include "main.h"

typedef struct
{
 GPIO_TypeDef *port;
 uint16_t pin; 
}LED_Struct;

/**
 * @brief  打开LED灯
 * @param  led: LED结构体指针
 * @retval None
 */
void Int_LED_turn_on(LED_Struct *led);

/**
 * @brief  关闭LED灯
 * @param  led: LED结构体指针
 * @retval None
 */
void Int_LED_turn_off(LED_Struct *led);

/**
 * @brief  翻转LED灯
 * @param  led: LED结构体指针
 * @retval None
 */
void Int_LED_toggle(LED_Struct *led);

#endif /* INT_LED_H */
