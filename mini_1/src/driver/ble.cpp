#include "ble.h"

bool bleConnected = false;
BLECharacteristic *pCharacteristic = nullptr;
uint32_t packcount = 0;


uint32_t get_blepack_count(){
    return packcount;
}

void clean_blepack_count(){
    packcount = 0;
}

bool get_ble_connect(){
    return bleConnected;
}

// 消息发送核心函数
void ble_report()
{
    if (get_ble_connect()){
        device_state_t *pdevice = get_device_state();
        uint8_t status[4];
        status[0] = pdevice->battery;
        status[1] = pdevice->temperature;
        status[2] = pdevice->paper_state;
        status[3] = pdevice->printer_state;
        pCharacteristic->setValue((uint8_t*)&status,sizeof(status));
        pCharacteristic->notify();
    }
}

// BLE回调类声明
class bleServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer){
        bleConnected = true;
        Serial.println("设备已连接");
    }

    void onDisconnect(BLEServer *pServer){
        bleConnected = false;
        Serial.println("设备断开");
        pServer->startAdvertising();
    }
};

class bleCharacteristicCallbacks : public BLECharacteristicCallbacks
{
    void onRead(BLECharacteristic *pCharacteristic){
         Serial.println("触发读取事件");       
    }

    void onWrite(BLECharacteristic *pCharacteristic){
        size_t length = pCharacteristic->getLength();
        uint8_t *pdata = pCharacteristic->getData();  
        if(packcount>=1001) {
            for (int index = 0; index < length; index++)
            {
                Serial.printf(" %x", pdata[index]);
            }
        }       
        if(length == 5){
            if(pdata[0] == 0xA5 && pdata[1] == 0xA5 && pdata[2] == 0xA5 && pdata[3] == 0xA5){
                if(pdata[4] == 1){
                    set_heat_density(30);
                }else if(pdata[4] == 2){
                    set_heat_density(60); 
                }else{
                    set_heat_density(100);
                }
                return;
            }
            if(pdata[0] == 0xA6 && pdata[1] == 0xA6 && pdata[2] == 0xA6 && pdata[3] == 0xA6){
                set_read_ble_finish(true);
                Serial.printf("接收打印数据完成,总行数=%d\n",packcount);
                return;
            }
        }
        packcount++;
        Serial.println(2);
        write_to_printbuffer(pdata,length);       
        Serial.printf("触发写入事件 length=%d count=%d ", length, packcount);
        for (int index = 0; index < length; index++)
        {
            Serial.printf(" %x", pdata[index]);
        }
        Serial.printf("\n");
        
        
    }

};

void init_ble()
{
    BLEDevice::init(BLE_NAME);
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new bleServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_NOTIFY |
        BLECharacteristic::PROPERTY_WRITE);
    pCharacteristic->setCallbacks(new bleCharacteristicCallbacks());
    pCharacteristic->addDescriptor(new BLE2902()); // 添加描述 

    pService->start();
    BLEDevice::startAdvertising();
    Serial.println("BLE初始化完成,等待连接...");

    
}