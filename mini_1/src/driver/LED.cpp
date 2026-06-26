#include "LED.h"

// 初始化LED
void initLED() {
    my_gpio_init(PIN_LED,my_output,my_high_level);   
}

//设置LED灯状态
void set_LED_state(LEDState newState) {       
    switch (newState)
    {
    case LED_NORMAL:        
        my_gpio_set(PIN_LED, my_high_level);       
        break;

    case LED_PRINTER_START:    
        my_gpio_set(PIN_LED, my_low_level);  
        my_delay_nb_ms(pdMS_TO_TICKS(slow_blink_ms));  
        my_gpio_set(PIN_LED, my_high_level);  
        my_delay_nb_ms(pdMS_TO_TICKS(slow_blink_ms));
        my_gpio_set(PIN_LED, my_low_level);  
        my_delay_nb_ms(pdMS_TO_TICKS(slow_blink_ms));  
        my_gpio_set(PIN_LED, my_high_level);  
        my_delay_nb_ms(pdMS_TO_TICKS(slow_blink_ms));
        my_gpio_set(PIN_LED, my_low_level); 
        break;

    case LED_LOW_POWER:        
        my_gpio_set(PIN_LED, my_low_level);  
        my_delay_nb_ms(pdMS_TO_TICKS(slow_blink_ms));  
        my_gpio_set(PIN_LED, my_high_level);  
        my_delay_nb_ms(pdMS_TO_TICKS(slow_blink_ms));
        break;

    case LED_WARN:        
        my_gpio_set(PIN_LED, my_low_level);  
        my_delay_nb_ms(pdMS_TO_TICKS(fast_blink_ms));  
        my_gpio_set(PIN_LED, my_high_level);  
        my_delay_nb_ms(pdMS_TO_TICKS(fast_blink_ms));
        break;

    default:
        // 默认状态：熄灭
        my_gpio_set(PIN_LED, my_high_level);
        break;
    }
    
}