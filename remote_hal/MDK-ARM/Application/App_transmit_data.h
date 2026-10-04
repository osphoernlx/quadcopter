#ifndef APP_TRANSMIT_DATA_H
#define APP_TRANSMIT_DATA_H

#include "Int_SI24R1.h"
#include "App_process_data.h"


/**
 * @brief  自动切换SI24R1的模式 将采集完成的遥控数据打包发送到飞机
 * 
 */
void App_transmit_data(void);

#endif /* APP_TRANSMIT_DATA_H */

