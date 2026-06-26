#include "my_time.h"

Ticker cycle_timer;
Ticker one_timer;


// 【定义】两个信号量句柄
SemaphoreHandle_t g_cycle_semaphore = NULL;
SemaphoreHandle_t g_one_semaphore = NULL;

// ==========================================
// 循环定时器回调 (5s 读电池)
// ==========================================
void cycle_timer_callbackfun(){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (g_cycle_semaphore != NULL) {
        xSemaphoreGiveFromISR(g_cycle_semaphore, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// ==========================================
// 一次性定时器回调
// ==========================================
void one_timer_callbackfun(){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // 【新增】释放一次性定时器的信号量
    if (g_one_semaphore != NULL) {
        xSemaphoreGiveFromISR(g_one_semaphore, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// ==========================================
// 关闭循环定时器
// ==========================================
void close_cycle_timer(){   
    cycle_timer.detach();  
    
    if (g_cycle_semaphore != NULL) {
        vSemaphoreDelete(g_cycle_semaphore);  
        g_cycle_semaphore = NULL;              
    }
}

// ==========================================
// 关闭一次性定时器
// ==========================================
void close_one_timer(){
    one_timer.detach();

    // 【新增】删除一次性定时器的信号量
    if (g_one_semaphore != NULL) {
        vSemaphoreDelete(g_one_semaphore);
        g_one_semaphore = NULL;
    }
}

// ==========================================
// 初始化循环定时器
// ==========================================
void cycle_timer_init(uint32_t cycle_time){
    if (g_cycle_semaphore == NULL) {
        g_cycle_semaphore = xSemaphoreCreateBinary();
    }
    cycle_timer.attach_ms(cycle_time, cycle_timer_callbackfun);
}

// ==========================================
// 初始化一次性定时器
// ==========================================
void one_timer_init(uint32_t one_time){
    // 【新增】创建一次性定时器的信号量
    if (g_one_semaphore == NULL) {
        g_one_semaphore = xSemaphoreCreateBinary();
    }
    one_timer.once_ms(one_time, one_timer_callbackfun);
}