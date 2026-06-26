#include "task.h"

SemaphoreHandle_t xKeySemaphore = NULL;

bool warn = 0;

void set_warn(){
    warn=1;
}

void read_all(){

    device_state_t *pdevice = get_device_state();

    // 1. 缺纸告警判断
    if(pdevice->paper_state == PAPER_STATUS_LACK){
        Serial.println("缺纸");
        set_LED_state(LED_WARN);
        return;
    }

    // 2. 低电量告警判断
    if(pdevice->battery < 20){
        Serial.println("电量低");
        Serial.printf("电量过低（当前电量：%d%）\n", pdevice->battery);
        set_LED_state(LED_LOW_POWER);
        return;
    }

    // 3. 温度过高告警判断（温度>60℃触发警告快闪，阈值可调整）
    if(pdevice->temperature > 60){
        set_stb_idle();
        Serial.printf("温度过高（当前温度：%d℃）\n", pdevice->temperature);
        set_LED_state(LED_WARN);
        return;
    }

}


void deviceTask(void *pvParameters) {   
    for(;;) {
        if (xSemaphoreTake(g_cycle_semaphore, portMAX_DELAY) == pdTRUE) { 
            if(get_device_state()->printer_state!=PRINTER_STATUS_WORKING)                    
                update_battery();
            update_temperatrue();           
            read_all();   
            ble_report();    
        }
    }
}

void print_test(){
    clean_printbuffer();
    testSTB();
}

void print_run(){
    device_state_t *pdevice = get_device_state();
    
    if (pdevice->read_ble_finish == true)
    {
        if (pdevice->printer_state == PRINTER_STATUS_FINISH ||
            pdevice->printer_state == PRINTER_STATUS_INIT)
        {
            pdevice->read_ble_finish = false;
            pdevice->printer_state = PRINTER_STATUS_START;
            ble_report();
            Serial.printf("开始打印：%d\n",get_ble_rx_leftline());           
            set_LED_state(LED_PRINTER_START);
        }
    }

    // 开始打印
    if (pdevice->printer_state == PRINTER_STATUS_START)
    {
        pdevice->printer_state = PRINTER_STATUS_WORKING;
        start_printing();       
        set_LED_state(LED_NORMAL);
        pdevice->printer_state = PRINTER_STATUS_FINISH;
    }

}

void init_task()
{
    // 初始化硬件
    init_printer();
    initLED();
    initKey();
    adc_init();
    init_paper();       
    

    // 初始化 BLE 服务器
    init_queue();
    init_ble();

    //初始化设备状态
    init_device_state();

    cycle_timer_init(1000);
    xTaskCreate(
        deviceTask,          // 任务函数
        "deviceTask",      // 任务名称
        1024*5,           // 任务栈大小
        NULL,             // 任务参数
        1,                // 任务优先级
        NULL              // 任务句柄
    );

    

}





