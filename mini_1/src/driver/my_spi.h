#ifndef _MY_SPI_H
#define _MY_SPI_H

#include "config.h"

//发送指定长度的SPI数据
void my_spi_send(uint8_t *data_buffer, uint8_t data_len);

//SPI初始化(时钟，输入，输出，片选)
void my_spi_init(int8_t sck,int8_t miso,int8_t mosi,int8_t ss);

#endif 