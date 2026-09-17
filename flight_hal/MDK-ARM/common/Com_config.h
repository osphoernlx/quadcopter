#ifndef __COM_CONFIG_H__
#define __COM_CONFIG_H__

#include "main.h"

/**
 * @brief  连接状态枚举
 * 
 */
typedef enum
{
    REMOTE_CONNECTED=0,
    REMOTE_DISCONNECTED,
}Remote_State;

/**
 * @brief  飞行状态枚举
 * 
 */
typedef enum
{
    IDLE=0,
    NORMAL,
    FIX_HEIGHT,
    FAIL,
}Flight_State;





#endif
