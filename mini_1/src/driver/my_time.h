#ifndef _MY_TIME_H
#define _MY_TIME_H

#include "config.h"

// 【修改】声明两个信号量句柄
extern SemaphoreHandle_t g_cycle_semaphore;
extern SemaphoreHandle_t g_one_semaphore;

//示例：if (xSemaphoreTake(g_one_semaphore, 0) == pdTRUE)
    

// 【一次性定时器】
void one_timer_init(uint32_t one_time);
void close_one_timer();

// 【循环定时器】
void cycle_timer_init(uint32_t cycle_time);
void close_cycle_timer();

// 【回调函数声明】
void cycle_timer_callbackfun();
void one_timer_callbackfun();

#endif 