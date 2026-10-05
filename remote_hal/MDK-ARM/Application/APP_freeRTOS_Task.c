#include "APP_freeRTOS_Task.h"

//STM32F109C8T6 => SRAM 20K =>分配12K给操作系统



//电源管理任务
void power_task(void *args);
//最小推荐写128 128*4=512B 
#define POWER_TASK_STACK_SIZE 128
//任务优先级 =>数值越小 优先级越低 => 0~4 =>不推荐使用最小优先级0
#define POWER_TASK_PRIORITY 4
TaskHandle_t Power_Task_Handler;
//任务周期
#define POWER_TASK_PERIOD 10000

//通讯任务
void com_task(void *args);
//最小推荐写128 128*4=512B 
#define COM_TASK_STACK_SIZE 128
//任务优先级 =>数值越小 优先级越低 => 0~4 =>不推荐使用最小优先级0
#define COM_TASK_PRIORITY 3
TaskHandle_t Com_Task_Handler;
//任务周期
#define COM_TASK_PERIOD 6

//按键任务
void key_task(void *args);
//最小推荐写128 128*4=512B 
#define KEY_TASK_STACK_SIZE 128
//任务优先级 =>数值越小 优先级越高=> 0~4 =>不推荐使用最小优先级0
#define KEY_TASK_PRIORITY 2
TaskHandle_t Key_Task_Handler;
//定义任务的周期
#define KEY_TASK_PERIOD 20

//摇杆任务
void joy_task(void *args);
//最小推荐写128 128*4=512B 
#define JOY_TASK_STACK_SIZE 128
//任务优先级 =>数值越小 优先级越高=> 0~4 =>不推荐使用最小优先级0
#define JOY_TASK_PRIORITY 2
TaskHandle_t Joy_Task_Handler;
//定义任务的周期
#define JOY_TASK_PERIOD 20

/**
* @brief  启动freeRTOS操作系统
 * @param  None
 * @retval None
 */

void App_FreeRTOS_Task_start(void)
{
    //1.创建电源管理任务
    xTaskCreate(power_task,"power_task",POWER_TASK_STACK_SIZE,NULL,POWER_TASK_PRIORITY,&Power_Task_Handler);

    //2.创建通讯任务
    xTaskCreate(com_task,"com_task",COM_TASK_STACK_SIZE,NULL,COM_TASK_PRIORITY,&Com_Task_Handler);

    //3.创建按键任务
    xTaskCreate(key_task,"key_task",KEY_TASK_STACK_SIZE,NULL,KEY_TASK_PRIORITY,&Key_Task_Handler);

    //4.创建摇杆任务
    xTaskCreate(joy_task,"joy_task",JOY_TASK_STACK_SIZE,NULL,JOY_TASK_PRIORITY,&Joy_Task_Handler);
    //开启任务调度
    vTaskStartScheduler();

}

void power_task(void *args)
{
    //获取当前的基准时间 
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {

        //每10s执行一次 => 启动电源 避免自动关机
        vTaskDelayUntil(&xLastWakeTime, POWER_TASK_PERIOD);
        //启动电源
        Int_IP5305T_start();
    }
}


/**
 * @brief  通讯任务
 * @param  None
 * @retval None
 */

void com_task(void *args)
{
    //获取当前的基准时间 
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        //将遥控数据打包发送到飞机
        App_transmit_data();

        //每6ms执行一次 
        vTaskDelayUntil(&xLastWakeTime, COM_TASK_PERIOD);
    }
}

/**
 * @brief  按键任务
 * 
 */
void key_task(void *args)
{

    //获取当前的基准时间 
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        //统一的处理方式
        App_process_key_data();
        //每20ms执行一次
        vTaskDelayUntil(&xLastWakeTime, KEY_TASK_PERIOD);
    }
}


/**
 * @brief  摇杆任务
 * 
 */
void joy_task(void *args)
{
    //获取当前的基准时间 
    TickType_t xLastWakeTime = xTaskGetTickCount();
    //1.初始化ADC遥控 开启ADC采集
    Int_joystick_init();
    while(1)
    {
        //统一的处理方式
        App_process_joystick_data();
        //每20ms执行一次
        vTaskDelayUntil(&xLastWakeTime, JOY_TASK_PERIOD);
    }
}

