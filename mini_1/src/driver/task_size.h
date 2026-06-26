#ifndef _TASK_SIZE_H
#define _TASK_SIZE_H

#include <Arduino.h>
#include "config.h"

/*使用示例
TaskHandle_t led_task_handle;
const uint32_t LED_TASK_STACK_SIZE = 1024;

xTaskCreate(
      LEDTask,          // 任务函数
      "LED_Control",    // 任务名称（调试用）
      1024,             // 栈大小（ESP32足够用）
      NULL,             // 任务参数（无）
      1,                // 任务优先级（数字越大优先级越高）
      &led_task_handle              // 任务句柄（无需监听则为NULL）
  );

（要放循环里）5s打印1次
printTaskStackInfo(led_task_handle, LED_TASK_STACK_SIZE, "LED任务");//查看任务栈的使用大小
*/


void printTaskStackInfo(TaskHandle_t task_handle, 
                        uint32_t allocated_stack_size, 
                        const char* task_name = "未知任务");

#endif 