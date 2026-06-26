#include "my_spi.h"

static const int spiClk = 1000000; // 1 MHz

SPIClass hspi  = SPIClass(HSPI);

// SPISettings(时钟频率, 数据位顺序, SPI模式)
SPISettings printerSPISettings = SPISettings(spiClk, SPI_MSBFIRST, SPI_MODE0);

/**
 * 函数功能：发送指定长度的SPI数据
 * 输入参数：data_buffer - 待发送数据指针
 *           data_len    - 数据长度
 * 注意事项：调用前必须先执行init_spi()初始化SPI
 */
void my_spi_send(uint8_t *data_buffer, uint8_t data_len)
{
    
    // 1. 启动SPI事务：锁定总线+加载通信规则，是传输稳定的核心保障
    hspi.beginTransaction(printerSPISettings);
    
    // 2. 核心操作：批量传输指定长度的打印数据到打印头
    hspi.transfer(data_buffer, data_len);
    
    // 3. 结束SPI事务：释放总线，允许其他任务使用SPI
    hspi.endTransaction();
}

//时钟，输入，输出，片选,通信频率
void my_spi_init(int8_t sck,int8_t miso,int8_t mosi,int8_t ss)
{
    // 绑定SPI引脚(时钟，输入，输出，片选)
    hspi.begin(sck, miso, mosi, ss); 
}

