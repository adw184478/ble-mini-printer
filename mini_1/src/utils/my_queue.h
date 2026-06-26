#ifndef _MY_QUEUE_H_
#define _MY_QUEUE_H_

#include "config.h"

//一行最大byte
#define MAX_ONELINE_BYTE 48

//最大行数
#define MAX_LINE 1500

typedef struct{
    uint8_t buffer[MAX_ONELINE_BYTE];// 单行打印数据存储缓冲区（48字节）
}ble_rx_buffer_t;

typedef struct{
    ble_rx_buffer_t printer_buffer[MAX_LINE]; // 队列存储缓冲区（MAX_LINE行，每行48字节）
    uint32_t r_index;                         // 队列读索引：标记下一次读取数据的位置
    uint32_t w_index;                         // 队列写索引：标记下一次写入数据的位置
    uint32_t left_line;                       // 队列待打印行数：记录当前队列中缓存的有效打印行数
}ble_rx_t;

/**
 * 函数功能：往打印缓冲区写入数据
 * 输入参数：pdata - 待写入的打印数据指针
 *           length - 要写入的数据长度（字节数）
 */
void write_to_printbuffer(uint8_t *pdata,size_t length);

/**
 * 函数功能：获取蓝牙接收的剩余打印行数
 * 返回值：剩余打印行数（无数据时返回0）
 */
uint32_t get_ble_rx_leftline();

/**
 * 函数功能：清空打印缓冲区（重置缓冲区指针/长度）
 */
void clean_printbuffer();

/**
 * 函数功能：从打印缓冲区读取一行打印数据
 * 返回值：指向该行数据的指针（NULL表示缓冲区无数据）
 */
uint8_t * read_to_printer();

/**
 * 函数功能：初始化打印/蓝牙数据的互斥保护
 * 注意：实际创建互斥量，保护全局数据避免多任务并发错乱
 */
void init_queue();

#endif