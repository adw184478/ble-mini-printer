#include "task_size.h"
/**
 * @brief 打印任意 FreeRTOS 任务的栈使用信息
 * @param task_handle 要查看的任务句柄（传NULL则查看当前运行的任务）
 * @param allocated_stack_size 该任务分配的栈大小（字节，创建任务时的第三个参数）
 * @param task_name 任务名称（仅用于打印标识，可选）
 */
void printTaskStackInfo(TaskHandle_t task_handle, 
                        uint32_t allocated_stack_size, 
                        const char* task_name) {
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 5000) {
    lastPrint = millis();
    // 1. 处理空句柄（默认查看当前运行的任务）
    if (task_handle == NULL) {
        Serial.print("[");
        Serial.print(task_name);
        Serial.println("] 任务句柄为空，查看当前任务栈信息：");
    } else {
        Serial.print("[");
        Serial.print(task_name);
        Serial.println("] 栈信息：");
    }

    // 2. 获取剩余最小栈空间（ESP32 Arduino中直接返回字节数）
    UBaseType_t stack_high_water_mark = uxTaskGetStackHighWaterMark(task_handle);
    uint32_t free_stack = stack_high_water_mark;

    // 3. 校验栈大小（避免传入错误的分配值）
    if (free_stack > allocated_stack_size) {
        Serial.println("⚠️ 警告：传入的分配栈大小可能错误！");
        Serial.print("   剩余栈空间(");
        Serial.print(free_stack);
        Serial.print("字节) > 分配栈大小(");
        Serial.print(allocated_stack_size);
        Serial.println("字节)");
        return;
    }

    // 4. 计算实际使用的栈大小和使用率
    uint32_t used_stack = allocated_stack_size - free_stack;
    float usage_rate = (float)used_stack / allocated_stack_size * 100;

    // 5. 打印详细信息
    Serial.println("---------------------");
    Serial.print("分配的栈大小：");
    Serial.print(allocated_stack_size);
    Serial.println(" 字节");
    Serial.print("剩余最小栈空间：");
    Serial.print(free_stack);
    Serial.println(" 字节");
    Serial.print("实际使用的最大栈：");
    Serial.print(used_stack);
    Serial.println(" 字节");
    Serial.print("栈使用率：");
    Serial.print(usage_rate, 2); // 保留2位小数
    Serial.println("%");
    Serial.println("---------------------");
    Serial.println(); // 空行分隔，更易读
    }
}
