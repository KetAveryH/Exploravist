#include <Wire.h>
#include <EEPROM.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define TOUCH_SENSOR_PIN T14
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define STEP_DATA_CHAR_UUID "beefcafe-36e1-4688-b7f5-00000000000b"

BLECharacteristic *pStepDataCharacteristic;

int count = 0;
int previousCount = 0;

void setup() {
  Serial.begin(9600);
  
  BLEDevice::init("Exploravist-Ble");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  pStepDataCharacteristic = pService->createCharacteristic(
      STEP_DATA_CHAR_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pStepDataCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
  pinMode(TOUCH_SENSOR_PIN, INPUT_PULLUP);

  EEPROM.begin(sizeof(int));
  EEPROM.get(0, count);
}

void saveStepCount() {
  EEPROM.put(0, count);
  EEPROM.commit();
}

void loop() {
  int touchValue = touchRead(TOUCH_SENSOR_PIN);
  
  if (touchValue > 70000) {
    count++;
    if (count != previousCount) {
      pStepDataCharacteristic->setValue((uint8_t*)&count, sizeof(count));
      pStepDataCharacteristic->notify();
      previousCount = count;
      Serial.println(count);
      saveStepCount();
    }
    delay(500); // Debounce delay
  } 
  delay(5);
}