#ifndef APP_FREERTOS_TASK_H
#define APP_FREERTOS_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "Com_debug.h"
#include "Com_config.h"
#include "Int_IP5305T.h"
#include "Int_motor.h"
#include "Int_LED.h"
#include "Int_SI24R1.h"

/**
 * @brief  ??freeRTOS????
 * @param  None
 * @retval None
 */

void App_FreeRTOS_Task_start(void);


#endif
