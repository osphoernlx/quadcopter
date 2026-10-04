#ifndef __COM_TOOL_H__
#define __COM_TOOL_H__

#include "main.h"


/**
 * @brief  限幅函数
 * @param  value: 输入值
 * @param  min: 最小值  
 * @param  max: 最大值
 * @return int16_t: 限幅后的值
 */
int16_t Com_limit(int16_t value,int16_t min,int16_t max);

#endif /* __COM_TOOL_H__ */


