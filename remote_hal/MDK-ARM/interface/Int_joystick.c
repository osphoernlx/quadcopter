#include "Int_joystick.h"



uint16_t adc_buff[4] = {0};  //ADC采集的值


/**
 * @brief  初始化ADC遥控 开启ADC采集
 * @param  无
 */
void Int_joystick_init(void)
{   
    //直接使用HAL中的函数 开启ADC
    //16位数据的地址值 其实是32位 32位数据的地址值也是32位
    //32单片机 使用的ADC转换是12位精度 范围 0~4095
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buff, 4);
}


/**
 * @brief  获取当前摇杆的值
 * @param  joystick 摇杆结构体指针
 */
void Int_joystick_get(Joystick_Struct *joystick)
{
    //DMA不依赖CPU计算的，所以可以直接读取adc_buff的值
    //顺序自定义 一定对齐
    joystick->thr=adc_buff[0];
    joystick->yaw=adc_buff[1];
    joystick->pit=adc_buff[2];
    joystick->rol=adc_buff[3];
}


