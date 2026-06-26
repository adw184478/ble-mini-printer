#include "config.h"

//查看任务栈的初始化
/*
TaskHandle_t led_task_handle;
const uint32_t LED_TASK_STACK_SIZE = 1024;
*/

void setup() {

    Serial.begin(115200);
    delay(1000); // 等待串口初始化
    init_task();


}

void loop() { 
    //printTaskStackInfo(led_task_handle, LED_TASK_STACK_SIZE, "LED任务");//查看任务栈的使用大小
  
    

    // 处理按键事件
    KeyEvent key_state = getKeyEvent();
    switch (key_state) {
        case KEY_EVENT_NONE:
            print_run();
            break;          


        case KEY_EVENT_SHORT_PRESS:{
            Serial.println("✅ 短按");              
                print_test();
            break;
        }
        case KEY_EVENT_LONG_PRESS:
            Serial.println("⏸️ 长按（按下中）");            
           
            break;

        case KEY_EVENT_LONG_RELEASE:
            Serial.println("🔚 长按释放");
            // 示例：长按释放后回到熄灭
            
            break;

        default:
            break;
    }
    
}