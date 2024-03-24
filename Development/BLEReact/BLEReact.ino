#include <Wire.h>
#include <EEPROM.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define BUTTON_PIN 2
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define STEP_DATA_CHAR_UUID "beefcafe-36e1-4688-b7f5-00000000000b"

BLECharacteristic *pStepDataCharacteristic;

int count = 0;
int app_count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Create BLE device, server, and service
  BLEDevice::init("Step-Sense");
  
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create step data characteristic
  pStepDataCharacteristic = pService->createCharacteristic(
      STEP_DATA_CHAR_UUID,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pStepDataCharacteristic->addDescriptor(new BLE2902());

  // Start BLE server and advertising
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("BLE device is ready to be connected");

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  EEPROM.begin(sizeof(int));
  EEPROM.get(0, count);

}

void saveStepCount() {
  EEPROM.put(0, count); // At address 0, save stepCount
  EEPROM.commit();
}


void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(touchRead(T14));
  if (touchRead(T14)>70000) {
    count++;
    saveStepCount();
    Serial.println(count);
    Serial.print("App Count:");
    Serial.println(app_count);
    delay(1000);
  } 
  delay(5);
}
