
#define CAMERA_MODEL_WROVER_KIT // Has PSRAM

#include "esp_camera.h"
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