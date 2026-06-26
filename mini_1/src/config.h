#ifndef _CONFIG_H
#define _CONFIG_H

#include <Arduino.h>

#include <SPI.h>    //SPI
#include <Ticker.h> //定时器
#include "my_gpio.h"
#include "task.h"
#include "device.h" //设备状态
#include "LED.h"
#include "task_size.h"
#include "key.h"
#include "ble.h"
#include "my_queue.h"
#include "my_adc.h"
#include "my_motor.h"
#include "my_paper.h"
#include "my_time.h"
#include "my_printer.h"
#include "my_spi.h"




// 蓝牙名称
#define BLE_NAME "Mini-Printer"
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// 按键引脚
#define PIN_KEY       5     

// LED引脚
#define PIN_LED         18

//纸张检测引脚
#define PIN_PAPER 35

// 电池引脚
#define PIN_BATTERY 34

//热敏电阻
#define PIN_TEMPERATRUE 36

//打印加热时间
#define PRINT_TIME 4600   

//冷却时间
#define PRINT_END_TIME 300      

//打印头加热通道
#define PIN_STB1 14  
#define PIN_STB2 27  
#define PIN_STB3 26  
#define PIN_STB4 25  
#define PIN_STB5 33  
#define PIN_STB6 32 


//打印头数据引脚
#define PIN_LAT    12    //片选
#define PIN_SCK    15    // SPI时钟线
#define PIN_MISO   16    // 主入从出
#define PIN_MOSI   13    // 主出从入

#define LAT_TIME 5             //数据锁存时间(us)


//每行总点数
#define TPH_DOTS_PER_LINE 384
//每行字节长度 384/8
#define TPH_DI_LEN 48
//所有通道打印
#define ALL_STB_NUM 0xFF

// 电机引脚
#define PIN_MOTOR_AP 23
#define PIN_MOTOR_AM 22
#define PIN_MOTOR_BP 21
#define PIN_MOTOR_BM 19

//打印头电源升压控制引脚
#define PIN_VHEN 17

#define my_delay_nb_ms(ms) vTaskDelay(pdMS_TO_TICKS(ms))
#define my_delay_us(us) delayMicroseconds(us);
#define my_delay_ms(ms) delay(ms)

// 函数简介     绝对值函数 数据范围是 [-32767,32767]
// 参数说明     dat             需要求绝对值的数
// 返回参数     int             返回绝对值
// 使用示例     dat = func_abs(dat);                            // 将dat变成正数
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define     func_abs(x)             ((x) >= 0 ? (x): -(x))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     限幅 数据范围是 [-32768,32767]
// 参数说明     x               被限幅的数据
// 参数说明     y               限幅范围(数据会被限制在-y至+y之间)
// 返回参数     int             限幅之后的数据
// 使用示例     int dat = func_limit(500, 300);                 // 数据被限制在-300至+300之间  因此返回的结果是300
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define     func_limit(x, y)        ((x) > (y) ? (y) : ((x) < -(y) ? -(y) : (x)))

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     双边限幅 数据范围是 [-32768,32767]
// 参数说明     x               被限幅的数据
// 参数说明     a               限幅范围左边界
// 参数说明     b               限幅范围右边界
// 返回参数     int             限幅之后的数据
// 使用示例     int dat = func_limit_ab(500, -300, 400);        //数据被限制在-300至+400之间  因此返回的结果是400
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
#define     func_limit_ab(x, a, b)  ((x) < (a) ? (a) : ((x) > (b) ? (b) : (x)))

#endif 