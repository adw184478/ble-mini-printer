#ifndef _MY_MOTOR_H_
#define _MY_MOTOR_H_

#include "config.h"

/**
 * 函数功能：电机运行指定步数（阻塞式）
 * 输入参数：steps - 需运行的拍数（步数）
 */
void motor_run_step(uint32_t steps);

/**
 * 函数功能：启动电机（非阻塞式，定时持续转动）
 * 说明：2ms触发一次拍数切换，电机持续运转
 */
void motor_start();

/**
 * 函数功能：停止电机
 * 说明：清零电机引脚电平，关闭电源使能，停止定时器
 */
void motor_stop();

/**
 * 函数功能：初始化电机引脚
 * 说明：设置四相引脚为输出模式，初始电平置0
 */
void init_motor();

/**
 * 函数功能：手动触发电机走一步（单次拍数切换）
 * 说明：仅走1个拍数，需手动重复调用实现多步
 */
void motor_run();

#endif
