#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "config.h"

/**
 * @brief 打印机工作状态枚举
 * @details 标识打印机在生命周期中的不同工作阶段
 */
typedef enum{
    PRINTER_STATUS_INIT = 0,    // 初始化状态（设备启动后初始状态）
    PRINTER_STATUS_START,       // 启动状态（准备开始打印）
    PRINTER_STATUS_WORKING,     // 工作状态（正在打印）
    PRINTER_STATUS_FINISH,      // 完成状态（打印任务结束）
}printer_state_e;

/**
 * @brief 纸张状态枚举
 * @details 标识打印机纸张的有无状态
 */
typedef enum{   
    
    PAPER_STATUS_NORMAL = 0,   // 纸张正常（有纸）
    PAPER_STATUS_LACK          //纸张缺失（缺纸）
}paper_state_e;

/**
 * @brief 设备核心状态结构体
 * @details 集中存储设备的电量、温度、纸张状态、打印机工作状态、蓝牙读取完成标志等核心参数
 */
typedef struct
{
    uint8_t battery;            // 设备电池剩余电量（0-100，100为满电）
    uint8_t temperature;        // 设备核心模块温度（单位：℃）
    paper_state_e paper_state;  // 纸张状态
    printer_state_e printer_state; // 打印机工作状态（枚举值：初始化/启动/工作/完成）
    bool read_ble_finish;       // 蓝牙数据读取完成标志（false=未完成，true=已完成）
}device_state_t;

//初始化设备状态
void init_device_state();

//得到设备状态
device_state_t  *get_device_state();

//设置蓝牙数据读取完成状态
void set_read_ble_finish(bool finish);

//设置纸张缺纸状态
void set_device_paper_status(paper_state_e status);

#endif