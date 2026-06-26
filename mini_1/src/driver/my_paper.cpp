#include "my_paper.h"


/**
 * @brief 初始化纸张检测引脚和外部中断
 */
void init_paper(){
    my_gpio_interrupt_init(PIN_PAPER,my_interrupt_rising,paper_isr);

}

/**
 * @brief 纸张检测中断服务函数（ISR）
 */
void ARDUINO_ISR_ATTR paper_isr()
{   
    set_device_paper_status(PAPER_STATUS_LACK);
    my_gpio_interrupt_deinit(PIN_PAPER);
}



//更新电压电量
void update_battery()
{
    int volts =get_adc_volts(PIN_BATTERY);
    volts = get_smooth_voltage(volts);

    static uint8_t num=0;
    if(num<5) {
        num++;
        return;
    }
    
    uint8_t battery = map(func_limit_ab(volts*2,3300, 4200), 3300, 4200, 0, 100);
    get_device_state()->battery = battery;
    //Serial.printf("电池电量：%d%%\n" ,battery);
}



/*
 公式法：
NTC 热敏电阻温度计算公式：Rt = Rp *EXP(B*(1/T1-1/T2))
可以得到温度T1与电阻Rt的关系T1=1/（log（Rt/Rp）/B+1/T2）

T1和T2指的是K度，即开尔文温度,K度=273.15(绝对温度)+摄氏度。
T2=(273.15+25)
Rt 是热敏电阻在T1温度下的阻值。
Rp 是热敏电阻在T2常温下的标称阻值。100K的热敏电阻25℃的值为100K（即R=100K）。T2=(273.15+25)
B值是热敏电阻的重要参数  B25/50= 3950K ±1%
最终对应的摄氏温度t=T1-273.15,同时+0.5的误差矫正。

查表法：
ADC采样率8位 串联电阻R1=10K R2=热敏电阻 电压3.3V
已知
Rt = R*(3.3-VR)/VR
VR = 3.3*ADC_Value/1024
得出
ADC_Value = VR*4096/3.3 =3.3*R/(Rt+R)*4096/3.3 = R/(Rt+R)*1024
ADC_Value=3.3/(C5+10)*10/3.3*1023
如果需要用到小数点后面的温度，正确的方法是使用公式RT＝R0*exp(B (1/T-1/T0))在excel中计算得到步进值为0.1℃的温度表
Rt=100*exp(3950*(1/(273.15+T1)-1/(273.15+25)))
Rt=100*EXP(3990*(1/(273.15+T1)-1/(273.15+25)))
*/

/**
 * @brief 阻值转换温度
 *
 * @param Rt 热敏电阻阻值
 * @return float 返回摄氏度温度
 */
float em_temp_calculate(float Rt)
{
    float Rp = 30000; // 30k
    float T2 = 273.15 + 25;
    float Bx = 3950; // B值
    float Ka = 273.15;
    float temp = 0.0f;

    temp = 1 / (log(Rt / Rp) / Bx + 1 / T2) - Ka + 0.5;
    return temp;
}

int get_smooth_voltage1(int data)
{
    static uint16_t buffer[5] = {0}; // 静态数组，保存历史数据
    static uint8_t index = 0;                    // 当前写入位置的索引
    static uint32_t sum = 0;                     // 累加和（避免每次重新计算）
    
    // 1. 减去最旧的那个值（窗口滑动：移除旧数据）
    sum -= buffer[index];
    
    // 2. 采集新值，存入当前索引位置（窗口滑动：加入新数据）
    buffer[index] = data;
    
    // 3. 累加新值
    sum += buffer[index];
    
    // 4. 更新索引（循环移动，到末尾后回到开头）
    index++;
    if(index >=5)
    {
        index = 0;
    }
    
    // 5. 返回平均值
    return (int)(sum / 5);
}

//更新打印机温度
void update_temperatrue(){
  float Rt=0;
  float vol=0;
  vol = analogReadMilliVolts(PIN_TEMPERATRUE);
  vol = get_smooth_voltage1(vol)/1000.0;

  static uint8_t num = 0;
  if(num<5) {
    num++;
    return;
  }

  Rt=(vol*10000)/(3.3-vol);
  uint8_t temp = func_limit_ab(em_temp_calculate(Rt), 0, 100);
  get_device_state()->temperature = temp;
  //Serial.printf("打印机温度：%d℃\n" ,temp);
}





