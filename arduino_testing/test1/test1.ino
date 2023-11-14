/*
 * Simple image reading from ESP23
*/

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

boolean takeNewPhoto = true;
const char* ssid = "Claremont-ETC";
const char* password = "Cl@remontI0T";
const char* chatgpt_token = "";
const char* chatgpt_Q = "\"Can you read this text please?\"";

// Photo File Name to save in SPIFFS
#define FILE_PHOTO "/photo.jpg"


// OV2640 camera module pins (CAMERA_MODEL_WROVER_KIT)
#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 21
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 19
#define Y4_GPIO_NUM 18
#define Y3_GPIO_NUM 5
#define Y2_GPIO_NUM 4
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22








void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200); 

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  while(!Serial);

  // wait for WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    ESP.restart();
  }

  // Turn-off the 'brownout detector'
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  // OV2640 camera module
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_HVGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    ESP.restart();
  }

}

void loop() {
  // Ensure WiFi is connected
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Attempting to reconnect...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nWiFi reconnected!");
  }

  // Take a new photo if needed
  if (takeNewPhoto) {
    String base64_image = capturePhotoSaveSpiffs();
    if(base64_image.length() == 0) {
      Serial.println("Failed to capture or encode photo.");
      takeNewPhoto = false;
      return;
    }
    takeNewPhoto = false;

    // Prepare JSON payload
    DynamicJsonDocument doc(50000); // Adjust the size to suit your needs
    JsonArray messagesArray = doc.createNestedArray("messages");
    JsonObject messageObject = messagesArray.createNestedObject();
    messageObject["role"] = "user";

    JsonArray contentArray = messageObject.createNestedArray("content");

    JsonObject textObject = contentArray.createNestedObject();
    textObject["type"] = "text";
    textObject["text"] = "What’s in this image?";

    JsonObject imageObject = contentArray.createNestedObject();
    imageObject["type"] = "image_url";
    JsonObject imageUrlObject = imageObject.createNestedObject("image_url");
    imageUrlObject["url"] = "data:image/jpeg;base64," + base64_image;

    doc["model"] = "gpt-4-vision-preview";
    doc["max_tokens"] = 300;
    
    String payload;
    serializeJson(doc, payload);
    // Debug: Print the payload
    Serial.println("Payload being sent:");
    Serial.println(payload);

    HTTPClient http;
    http.begin("https://api.openai.com/v1/chat/completions"); // Your API endpoint
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(chatgpt_token)); // Your API key

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("API Response:");
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(http.errorToString(httpResponseCode));
    }

    http.end();
  }
  Serial.println("Wait 60s before next round...");
  delay(60000);
}

// Check if photo capture was successful
bool checkPhoto( fs::FS &fs ) {
  File f_pic = fs.open( FILE_PHOTO );
  unsigned int pic_sz = f_pic.size();
  return ( pic_sz > 100 );
}

/// Capture Photo and return it as a Base64-encoded String
String capturePhotoSaveSpiffs() {
  camera_fb_t *fb = esp_camera_fb_get(); // Take a photo with the camera
  if (!fb) {
    Serial.println("Camera capture failed");
    return ""; // Return an empty string to indicate failure
  }

  // Encode the image in base64
  String base64Image = base64::encode(fb->buf, fb->len);
  if (base64Image.length() == 0) {
    Serial.println("Base64 encoding failed");
    esp_camera_fb_return(fb);
    return ""; // Return an empty string to indicate failure
  }

  Serial.print("Base64 Image Success! Length: ");
  Serial.println(base64Image.length());

  // Return the frame buffer back to the driver for reuse
  esp_camera_fb_return(fb);

  return base64Image; // Return the encoded image as a string
}

