#include "my_gpio.h"

// 核心初始化函数
void my_gpio_init(uint8_t pin, GPIO_Mode mode, GPIO_State state) {
    switch (mode) {
        case my_input:
            if (state == my_low_level) {
                pinMode(pin, INPUT_PULLDOWN);            
            } else {
                pinMode(pin, INPUT_PULLUP);                
            }
            break;
        
        case my_output:
            pinMode(pin, OUTPUT); // 推挽输出
            if (state == my_low_level) {
                digitalWrite(pin, LOW);              
            } else {
                digitalWrite(pin, HIGH);
               
            }
            break;
    }
}

// 设置输出电平函数
void my_gpio_set(uint8_t pin, GPIO_State state) {
    digitalWrite(pin, (state == my_low_level) ? LOW : HIGH);
}

// 读取输入电平函数
uint8_t my_get_gpio(uint8_t pin) {
    return digitalRead(pin);
}

//中断初始化函数实现
void my_gpio_interrupt_init(uint8_t pin, GPIO_InterruptMode mode, GPIO_Callback callback) {
    
    my_gpio_init(pin, my_input, my_high_level);

    int arduino_int_mode;
    switch (mode) {
        case my_interrupt_low:    arduino_int_mode = LOW;      break;
        case my_interrupt_high:   arduino_int_mode = HIGH;     break;
        case my_interrupt_change: arduino_int_mode = CHANGE;   break;
        case my_interrupt_falling:arduino_int_mode = FALLING;  break;
        case my_interrupt_rising: arduino_int_mode = RISING;   break;
        default: return; 
    }
  
    attachInterrupt(pin, callback, arduino_int_mode);
}

// 中断关闭函数实现
void my_gpio_interrupt_deinit(uint8_t pin) {  
        detachInterrupt(pin); 
}