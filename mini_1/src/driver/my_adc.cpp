#include "my_adc.h"

void adc_init() {
  //配置 ADC的读取分辨率
  analogReadResolution(12);
}

/**
 * @brief 获取ADC引脚电压值，可根据需要加入滤波算法
 * 
 * @return int 
 */
int get_adc_volts(int adc_pin){    
    int analogVolts = analogReadMilliVolts(adc_pin);   
    return analogVolts;
}

// 滑动滤波函数，返回平滑后的电压值（mV）
int get_smooth_voltage(int data)
{
    static uint16_t buffer[5] = {0}; // 静态数组，保存历史数据
    static uint8_t index = 0;                    // 当前写入位置的索引
    static uint32_t sum = 0;                     // 累加和（避免每次重新计算）
    
    // 1. 减去最旧的那个值（窗口滑动：移除旧数据）
    sum -= buffer[index];
    
    // 2. 采集新值，存入当前索引位置（窗口滑动：加入新数据）
    buffer[index] = data;
    
    // 3. 累加新值
    sum += buffer[index];
    
    // 4. 更新索引（循环移动，到末尾后回到开头）
    index++;
    if(index >=5)
    {
        index = 0;
    }
    
    // 5. 返回平均值
    return (int)(sum / 5);
}


