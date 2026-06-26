#ifndef _KEY_H
#define _KEY_H

#include "config.h"

// 按键引脚
// #define PIN_KEY         0     
#define LONG_PRESS_MS   1000     // 长按阈值（超过1s判定为长按）

// 按键事件枚举
typedef enum {
    KEY_EVENT_NONE,        // 无事件
    KEY_EVENT_SHORT_PRESS, // 短按（按下<1s后释放）
    KEY_EVENT_LONG_PRESS,  // 长按（按下≥1s时触发）
    KEY_EVENT_LONG_RELEASE // 长按释放（长按后松开）
} KeyEvent;

// 初始化按键
void initKey();

// FreeRTOS 按键扫描任务函数
void keyTask(void *pvParameters);

// 获取并清空当前按键事件（外部调用）
KeyEvent getKeyEvent();



#endif // KEY_H