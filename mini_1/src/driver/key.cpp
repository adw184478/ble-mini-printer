#include "key.h"

KeyEvent  currentEvent = KEY_EVENT_NONE;
uint32_t  pressStartMs = 0;
bool      isPressed = false;
bool      longPressTriggered = false;

void initKey() {
    my_gpio_init(PIN_KEY, my_input, my_high_level);   
    xTaskCreate(
        keyTask,          // 任务函数
        "KeyTask",        // 任务名称
        1024*5,           // 任务栈大小
        NULL,             // 任务参数
        0,                // 任务优先级
        NULL              // 任务句柄
    );
    
}

void keyTask(void *pvParameters) {   
    while (true) {
        uint8_t keyLevel = my_get_gpio(PIN_KEY);

        // ===== 按键按下 =====
        if (keyLevel == LOW) {
            if (!isPressed) {
                // 刚按下：记录起始时间
                pressStartMs = millis();
                isPressed = true;
                longPressTriggered = false;
                currentEvent = KEY_EVENT_NONE;
            } else {
                // 已按下：检测是否达到长按阈值
                uint32_t duration = millis() - pressStartMs;
                if (duration >= LONG_PRESS_MS && !longPressTriggered) {
                    currentEvent = KEY_EVENT_LONG_PRESS;
                    longPressTriggered = true;
                }
            }
        }
        // ===== 按键释放 =====
        else {
            if (isPressed) {
                // 刚释放：判断事件类型
                uint32_t duration = millis() - pressStartMs;
                if (longPressTriggered) {
                    currentEvent = KEY_EVENT_LONG_RELEASE;
                } else if (duration < LONG_PRESS_MS) {
                    currentEvent = KEY_EVENT_SHORT_PRESS;
                }
                isPressed = false;
            }
        }

        // 任务延时       
        my_delay_nb_ms(10);
    }
}

KeyEvent getKeyEvent() {
    // 读取后清空事件，避免重复处理
    KeyEvent evt = currentEvent;
    currentEvent = KEY_EVENT_NONE;
    return evt;
}