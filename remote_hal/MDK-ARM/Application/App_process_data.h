#ifndef APP_PROCESS_DATA_H
#define APP_PROCESS_DATA_H

#include "Int_joystick.h"
#include "Int_key.h"
#include "Com_debug.h"

typedef struct
{
    int16_t thr; //油门
    int16_t yaw; //偏航
    int16_t pit; //俯仰
    int16_t rol; //横滚
    uint8_t shutdown; //关机标志位
    uint8_t fix_height; //定高标志位
}Remote_Data;

/**
 * @brief  处理按键数据 如果有按键按下 做相应的记录
 * @param  None
 */
void App_process_key_data(void);


/**
 * @brief  处理摇杆数据 修正极性相位和标准值
 * @param  None
 */
void App_process_joystick_data(void);


#endif
