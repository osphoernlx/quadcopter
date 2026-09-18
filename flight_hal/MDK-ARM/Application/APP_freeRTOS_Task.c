#include "APP_freeRTOS_Task.h"

//STM32F109C8T6 => SRAM 20K =>


//内存管理 => C语言中的结构体通常保存在堆�? 不会自动垃圾回收 => 始终使用同一个结构体 不断循环使用

//电机结构�?
Motor_Struct left_top_motor = {.htim = &htim3,.channel = TIM_CHANNEL_1,.speed = 200};
Motor_Struct left_bottom_motor = {.htim = &htim4,.channel = TIM_CHANNEL_4,.speed = 200};
Motor_Struct right_top_motor = {.htim = &htim2,.channel = TIM_CHANNEL_2,.speed = 200};
Motor_Struct right_bottom_motor = {.htim = &htim1,.channel = TIM_CHANNEL_3,.speed = 200};

//LED结构�?
LED_Struct left_top_led = {.port =LED1_GPIO_Port, .pin = LED1_Pin};
LED_Struct right_top_led = {.port =LED2_GPIO_Port, .pin = LED2_Pin};
LED_Struct right_bottom_led = {.port =LED3_GPIO_Port, .pin = LED3_Pin};
LED_Struct left_bottom_led = {.port =LED4_GPIO_Port, .pin = LED4_Pin};



//表示当前连接状�?
Remote_State remote_state = REMOTE_DISCONNECTED;

//表示当前的飞行状�?
Flight_State flight_state = FAIL;


//电源管理任务
void power_task(void *args);
//最小推荐写128 128*4=512B 
#define POWER_TASK_STACK_SIZE 128
//任务优先�? =>数值越�? 优先级越�? => 0~4 =>不推荐使用最小优先级0
#define POWER_TASK_PRIORITY 4
TaskHandle_t Power_Task_Handler;
//定义任务的周�?
#define POWER_TASK_PERIOD 10000


//飞行控制任务
void flight_control_task(void *args);
//最小推荐写128 128*4=512B 
#define FLIGHT_CONTROL_TASK_STACK_SIZE 128
//任务优先�? =>数值越�? 优先级越�? => 0~4 =>不推荐使用最小优先级0
#define FLIGHT_CONTROL_TASK_PRIORITY 3
TaskHandle_t Flight_Control_Task_Handler;
//定义任务的周�?
#define FLIGHT_CONTROL_TASK_PERIOD 6

//LED灯控任务
void led_task(void *args);
//最小推荐写128 128*4=512B 
#define LED_TASK_STACK_SIZE 128
//任务优先�? =>数值越�? 优先级越�? => 0~4 =>不推荐使用最小优先级0
#define LED_TASK_PRIORITY 1
TaskHandle_t Led_Task_Handler;
//定义任务的周�?
#define LED_TASK_PERIOD 100


//通讯任务
void com_task(void *args);
//最小推荐写128 128*4=512B 
#define COM_TASK_STACK_SIZE 128
//任务优先�? =>数值越�? 优先级越�? => 0~4 =>不推荐使用最小优先级0
#define COM_TASK_PRIORITY 2
TaskHandle_t Com_Task_Handler;
//任务周期
#define COM_TASK_PERIOD 6


/**
 * @brief  启动freeRTOS操作系统
 * @param  None
 * @retval None
 */

void App_FreeRTOS_Task_start(void)
{
    //1.创建电源管理任务
    xTaskCreate(power_task,"power_task",POWER_TASK_STACK_SIZE,NULL,POWER_TASK_PRIORITY,&Power_Task_Handler);
    //2.创建飞行控制任务
    xTaskCreate(flight_control_task,"flight_control_task",FLIGHT_CONTROL_TASK_STACK_SIZE,NULL,FLIGHT_CONTROL_TASK_PRIORITY,&Flight_Control_Task_Handler);
    //3.创建LED灯控任务
    xTaskCreate(led_task,"led_task",FLIGHT_CONTROL_TASK_STACK_SIZE,NULL,FLIGHT_CONTROL_TASK_PRIORITY,&Led_Task_Handler);
    //4.创建通讯任务
    xTaskCreate(com_task,"com_task",COM_TASK_STACK_SIZE,NULL,COM_TASK_PRIORITY,&Com_Task_Handler);
    //5.开启任务调�?
    vTaskStartScheduler();
}

/**
 * @brief  电源管理任务
 * 
 */
void power_task(void *args)
{
    //获取当前的基准时�? 
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {

        //�?10s执行一�? => 启动电源 避免自动关机
        vTaskDelayUntil(&xLastWakeTime, POWER_TASK_PERIOD);
        //启动电源
        Int_IP5305T_start();
    }
}
/**
 * @brief  飞行控制任务
 * 
 */
void flight_control_task(void *args)
{
    //获取当前的基准时�? 
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
      //1.设置电机的转�?
      left_top_motor. speed = 400;
      //2.直接启动电机
    //  Int_motor_start(&left_top_motor);
    //  Int_motor_start(&right_bottom_motor);
      //�?6ms执行一�?
      vTaskDelayUntil(&xLastWakeTime, FLIGHT_CONTROL_TASK_PERIOD);

    }
}


/**
 * @brief  LED灯控任务
 * 
 * 
 */
void led_task(void *args)
{
  //获取当前的基准时�?
  TickType_t xLastWakeTime = xTaskGetTickCount();
  uint8_t count = 0;
  while(1)
  {
    count++;
    //前两个灯表示连接状�?
    //1.判断当前连接状�?
    if(remote_state == REMOTE_CONNECTED)
    {
      //点亮前两个灯
      Int_LED_turn_on(&left_top_led);
      Int_LED_turn_on(&right_top_led);
    }
    else
    {
      //关闭前两个灯
      Int_LED_turn_off(&left_top_led);
      Int_LED_turn_off(&right_top_led);
    }

    //后两个灯表示飞行状�?
    //2.判断当前飞行状�?
    if(flight_state == IDLE)
    {
      //灯慢闪烁 => 500ms�? 500ms�?
      if(count%5==0)
      {
        Int_LED_toggle(&left_bottom_led);
        Int_LED_toggle(&right_bottom_led);
      }
    }
    else if(flight_state == NORMAL)
    {
      //灯慢闪烁 => 200ms�? 200ms�?
      if(count%2==0)
      {
        Int_LED_toggle(&left_bottom_led);
        Int_LED_toggle(&right_bottom_led);
      }
    }
    else if(flight_state == FIX_HEIGHT)
    {
      //后两个灯�?
      Int_LED_turn_on(&left_bottom_led);
      Int_LED_turn_on(&right_bottom_led);
    }
    else if(flight_state == FAIL)
    {
      //后两个灯�?
      Int_LED_turn_off(&left_bottom_led);
      Int_LED_turn_off(&right_bottom_led);
    }    
    //�?100ms执行一�?
    vTaskDelayUntil(&xLastWakeTime, LED_TASK_PERIOD);
    
    //将count重置
    if(count == 10 )
    {
      count = 0;
    }
  }
}

/**
 * @brief  通讯任务
 * 
 * 
 */
uint8_t com_data[TX_PLOAD_WIDTH]={0};
void com_task(void *args)
{
  //获取当前的基准时�?
    TickType_t xLastWakeTime = xTaskGetTickCount();

    while (1)
    {
        //接收数据到缓冲区
        uint8_t res = Int_SI24R1_RxPacket(com_data);
        if(res==0)
        {
          debug_printf("RX OK:%s\n", com_data);
        }
        //6ms执行一�? 接收数据的时间间隔应该等于发送数据的时间间隔
        vTaskDelayUntil(&xLastWakeTime, COM_TASK_PERIOD);
    }
}







