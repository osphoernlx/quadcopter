#include "App_process_data.h"




Joystick_Struct joystick={0};  //摇杆数据结构体
Remote_Data remote_data={0};   //遥控器数据结构体

//区分摇杆的控制值和按键的微调值
int16_t key_pit_offset=0;       //往前飞是正值，往后飞是负值
int16_t key_rol_offset=0;       //往左飞是负值，往右飞是正值

/**
 * @brief  处理按键数据 如果有按键按下 做相应的记录
 * @param  None
 */
void App_process_key_data(void)
{
        KEY_type key = Int_key_get();
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
            //校准摇杆 ？
        }
} 



/**
 * @brief  处理摇杆数据 修正极性相位和标准值
 * @param  None
 */
void App_process_joystick_data(void)
{
    //1.获取摇杆监控的ADC值
    Int_joystick_get(&joystick);

    //2.处理范围和极性 想要使用的范围0~1000 =>ADC的范围0~4095
    remote_data.thr=1000-(joystick.thr*1000/4095);  //油门
    remote_data.yaw=1000-(joystick.yaw*1000/4095);  //偏航
    remote_data.pit=1000-(joystick.pit*1000/4095);  //俯仰
    remote_data.rol=1000-(joystick.rol*1000/4095);  //横滚

    debug_printf(":%d,%d,%d,%d\n",remote_data.thr,remote_data.yaw,remote_data.pit,remote_data.rol);
}



