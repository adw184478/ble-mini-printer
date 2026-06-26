#ifndef _MY_ADC_H_
#define _MY_ADC_H_

#include "config.h"

//adc分辨率初始化
void adc_init();

//得到电压（mv）
int get_adc_volts(int adc_pin);

int get_smooth_voltage(int data);

#endif