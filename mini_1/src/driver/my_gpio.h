#ifndef _MY_GPIO_H_
#define _MY_GPIO_H_

#include "config.h"

// 引脚
/*
    // 通用IO
    IO0,  IO1,  IO2,  IO3,  IO4,  IO5,  IO12, IO13, IO14, IO15, IO16, IO17, IO18, IO19, IO21,
    IO22, IO23, IO25, IO26, IO27, IO32, IO33,

    // 仅输入引脚（IO34-IO39）：设计初衷是 **“高精度模拟输入通道”**（用于 ADC 采集、传感器信号输入），因此硬件上：
    //去掉了输出驱动电路（无法配置为输出）；
    //也去掉了内部上拉 / 下拉电阻（避免电阻影响模拟信号的精度）。
    IO34, IO35, IO36, IO39,
*/


// 模式枚举
typedef enum {
    my_input,
    my_output,
} GPIO_Mode;

// 状态枚举
typedef enum {
    my_low_level,
    my_high_level,
} GPIO_State;

// 中断触发模式枚举
typedef enum {
    my_interrupt_low,      // 低电平触发 (注意：部分平台可能不支持)
    my_interrupt_high,     // 高电平触发 (注意：部分平台可能不支持)
    my_interrupt_change,   // 电平变化触发 (上升/下降沿都触发)
    my_interrupt_falling,  // 下降沿触发
    my_interrupt_rising,   // 上升沿触发
} GPIO_InterruptMode;

//中断回调函数类型 
typedef void (*GPIO_Callback)(void);

//gpio初始化
void my_gpio_init(uint8_t pin, GPIO_Mode mode, GPIO_State state);
//设置gpio状态
void my_gpio_set(uint8_t pin, GPIO_State state);
//得到gpio状态
uint8_t my_get_gpio(uint8_t pin);
//中断初始化函数
void my_gpio_interrupt_init(uint8_t pin, GPIO_InterruptMode mode, GPIO_Callback callback);
// 中断关闭函数
void my_gpio_interrupt_deinit(uint8_t pin);

//示例：my_gpio_interrupt_init(1, my_interrupt_falling, isr_handler);
// void ARDUINO_ISR_ATTR isr_handler() {
//     这里的代码会在按键触发中断时快速执行
// }


#endif