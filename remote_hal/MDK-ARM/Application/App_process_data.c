#include "App_process_data.h"


Joystick_Struct joystick={0};  //摇杆数据结构体
Remote_Data remote_data={0};   //遥控器数据结构体

//区分摇杆的控制值和按键的微调值
int16_t key_pit_offset=0;       //往前飞是正值，往后飞是负值
int16_t key_rol_offset=0;       //往左飞是负值，往右飞是正值

//记录摇杆的偏移量
int16_t thr_offset=0;       //油门偏移量
int16_t yaw_offset=0;       //偏航偏移量
int16_t pit_offset=0;       //俯仰偏移量
int16_t rol_offset=0;       //横滚偏移量



//校准摇杆函数
void App_calibrate_joystick(void)
{
    //零偏校准的逻辑就是减去零偏的值
    //首先清空掉按键的微调值
    key_pit_offset=0;
    key_rol_offset=0;
    //多次读取求平均值
    int16_t thr_sum=0,yaw_sum=0,pit_sum=0,rol_sum=0;
    for(int i=0;i<10;i++)
    {
        App_process_joystick_data();
        thr_sum+=joystick.thr-0;
        yaw_sum+=joystick.yaw-500;
        pit_sum+=joystick.pit-500;
        rol_sum+=joystick.rol-500;
        vTaskDelay(10);
    }
    //零偏校准的偏移值没有累加的效果 会造成两次校准退回的情况
    thr_offset+=thr_sum/10;
    yaw_offset+=yaw_sum/10;
    pit_offset+=pit_sum/10;
    rol_offset+=rol_sum/10;
}

/**
 * @brief  如果freeRTOS的两个任务优先级相等 两个任务会交替运行
 * 
 */





/**
 * @brief  处理按键数据 如果有按键按下 做相应的记录
 * @param  None
 */
void App_process_key_data(void)
{
        KEY_type key = Int_key_get();
        //根据按键的值进行记录 如果进行摇杆的校准 将按键的值清零
        if(key == KEY_UP)
        {
            //向前飞微调 俯仰角+
            key_pit_offset+=10;
        }
        else if(key == KEY_DOWN)
        {
            //向后飞微调 俯仰角-
            key_pit_offset-=10;
        }
        else if(key == KEY_LEFT)
        {
            //向左飞微调 横滚角-
            key_rol_offset-=10;
        }
        else if(key == KEY_RIGHT)
        {
            //向右飞微调 横滚角+
            key_rol_offset+=10;
        }
        else if(key == KEY_LEFT_X)
        {
            //关机
            remote_data.shutdown=1;
        }
        else if(key == KEY_RIGHT_X)
        {
            //定高
            remote_data.fix_height=1;
        }
        else if(key == KEY_RIGHT_X_LONG)
        {
            //校准摇杆
            //触发校准之后 摇杆的值THR为0 YAW PITCH ROLL为500
            App_calibrate_joystick();
        }
} 



/**
 * @brief  处理摇杆数据 修正极性相位和标准值
 * @param  None
 */
void App_process_joystick_data(void)
{
    //如何解决freeRTOS的任务切换问题
    //使用临界区解决
    taskENTER_CRITICAL();  //进入临界区

    //1.获取摇杆监控的ADC值
    Int_joystick_get(&joystick);

    //理论上 摇杆的任务运行到这一行 有可能跳转到按键任务的运行 会出现按键任务使用的摇杆数据没有经过处理

    //2.处理范围和极性 想要使用的范围0~1000 =>ADC的范围0~4095
    joystick.thr=1000-(joystick.thr*1000/4095);  //油门
    joystick.yaw=1000-(joystick.yaw*1000/4095);  //偏航
    joystick.pit=1000-(joystick.pit*1000/4095);  //俯仰
    joystick.rol=1000-(joystick.rol*1000/4095);  //横滚

 
    //3.处理零偏校准
    joystick.thr-=thr_offset;
    joystick.yaw-=yaw_offset;
    joystick.pit-=pit_offset;
    joystick.rol-=rol_offset;

    //4.考虑按键的微调值
    joystick.pit+=key_pit_offset;
    joystick.rol+=key_rol_offset;

    //5.计算上偏移值可能超出范围 需要限制在0~1000之间
    joystick.thr=Com_limit(joystick.thr,0,1000);
    joystick.yaw=Com_limit(joystick.yaw,0,1000);
    joystick.pit=Com_limit(joystick.pit,0,1000);
    joystick.rol=Com_limit(joystick.rol,0,1000);
    

    //退出临界区
    taskEXIT_CRITICAL();

    debug_printf(":%d,%d,%d,%d\n",joystick.thr,joystick.yaw,joystick.pit,joystick.rol);
}



