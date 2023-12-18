/**********************************************************************
  Filename    : GPT Audio to Text
  Description : Takes in audio from INMP441 and sends to GPT Whisper Model for Speech to Text
  Author      : Ket Hollingsworth
  Modification: 2022/10/31
**********************************************************************/
#include "mic_to_wav.h"
#include "Arduino.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include <SPIFFS.h>
#include "base64.h"
#include <string.h>


const char* ssid = "Claremont-ETC";
const char* password = "Cl@remontI0T";
const char* chatgpt_token = "";

// We need to figure out INMP441 pins

#define I2S_SD 41
#define I2S_WS 42
#define I2S_SCK 1
#define I2S_PORT I2S_NUM_0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SPIFFSInit();
  i2sInit();
  xTaskCreate(i2s_adc, "i2s_adc", 1024 * 4, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
