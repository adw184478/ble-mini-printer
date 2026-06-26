#ifndef _MY_PAPER_H_
#define _MY_PAPER_H_

#include "config.h"

/**
 * @brief 初始化纸张检测引脚和中断
 */
void init_paper();

/**
 * @brief 纸张检测中断服务函数（ISR）
 */
void ARDUINO_ISR_ATTR paper_isr();

void update_battery();

void update_temperatrue();

#endif