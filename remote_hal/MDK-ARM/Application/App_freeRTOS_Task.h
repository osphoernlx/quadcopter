#ifndef APP_FREERTOS_TASK_H
#define APP_FREERTOS_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "Com_debug.h"
#include "Int_IP5305T.h"
#include "Int_SI24R1.h"
#include "App_process_data.h"

/**
 * @brief  初始化freeRTOS任务
 * @param  None
 * @retval None
 */

void App_FreeRTOS_Task_start(void);


#endif
