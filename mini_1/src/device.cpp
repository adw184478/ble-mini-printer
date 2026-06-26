#include "device.h"

device_state_t g_device_state;

device_state_t * get_device_state(){
    return &g_device_state;
}

void set_device_paper_status(paper_state_e status){
    g_device_state.paper_state = status;
}

void set_read_ble_finish(bool finish){
    g_device_state.read_ble_finish = finish;
}



void init_device_state(){
    // 第一步：将整个设备状态结构体的所有字节清零
    // 确保所有成员先有默认的 0 值，避免随机内存值干扰
    memset(&g_device_state,0,sizeof(device_state_t));
    
    // 第二步：为关键状态成员设置具体的初始值
    g_device_state.printer_state = PRINTER_STATUS_INIT;  // 打印机状态初始化为「初始化状态」
    g_device_state.battery = 100;                       // 电池电量初始化为 100%（满电）
    g_device_state.temperature = 30;                    // 设备温度初始化为 30℃（默认值）
    g_device_state.paper_state = PAPER_STATUS_NORMAL;   // 纸张状态初始化为「正常」（非缺纸）
    g_device_state.read_ble_finish = false;             // 蓝牙读取完成标志初始化为「未完成」
}