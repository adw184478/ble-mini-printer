#ifndef _LED_H
#define _LED_H

#include "config.h"

// LED引脚
//#define LED_PIN         2
#define  slow_blink_ms 500
#define fast_blink_ms  100


// LED状态枚举
typedef enum {
    LED_NORMAL = 0,          // 正常状态：灭
    LED_PRINTER_START,        // 打印启动：慢闪2次后常亮
    LED_LOW_POWER,           // 没电状态：慢闪（亮500ms/灭500ms）
    LED_WARN,                // 警告状态：快闪（亮100ms/灭100ms）    
} LEDState;

/*外部调用*/

// 初始化LED
void initLED();

//设置LED灯状态
void set_LED_state(LEDState newState);

#endif 