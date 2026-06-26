#ifndef _BLE_H
#define _BLE_H

#include <Arduino.h>
#include "config.h"
#include <BLEDevice.h>
#include <BLE2902.h>


uint32_t get_blepack_count();
void clean_blepack_count();
void ble_report();
void init_ble();
bool get_ble_connect();






#endif