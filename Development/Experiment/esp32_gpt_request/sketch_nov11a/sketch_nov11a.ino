/*
 * The simplest demo of XIAO ESP32C3 calling OpenAI
*/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "esp_camera.h"
#include "base64.h"

const int buttonPin = 2;  // the number of the pushbutton pin
const char* ssid = "Claremont-ETC";
const char* password = "Cl@remontI0T";
const char* chatgpt_token = "";
const char* chatgpt_Q = "\"Who are you\"";
camera_fb_t *fb = NULL;
esp_err_t res = ESP_OK;

int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);

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
}

void loop() {
    HTTPClient https;
    buttonState = digitalRead(buttonPin);
    
    // if (buttonState == HIGH) {

    fb = esp_camera_fb_get();
    Serial.println("1");
    if (!fb) {
    ESP_LOGE(TAG, "Camera capture failed");
    Serial.println("2");
    // Handle the error, possibly with a return or goto to clean up
    } else if (!fb->buf) {
      Serial.println("3");
        ESP_LOGE(TAG, "Camera buffer is invalid");
        esp_camera_fb_return(fb);  // Make sure to return the frame buffer to avoid a memory leak
        // Handle the error
    } else if (fb->len == 0) {
        Serial.println("4");
        ESP_LOGE(TAG, "Camera buffer length is zero");
        esp_camera_fb_return(fb);  // Make sure to return the frame buffer to avoid a memory leak
        // Handle the error
    } else {
        Serial.println("5");
        // If fb and fb->buf are valid, and fb->len is greater than zero, it should be safe to proceed
        String base64Image = base64::encode(fb->buf, fb->len);
        ESP_LOGE(TAG, "base64 Encoding Success!");
        Serial.print("success");
        // Make sure you do not use base64Image if the encode function failed
        if (base64Image.length() == 0) {
            Serial.println("6");
            ESP_LOGE(TAG, "Base64 encoding failed");
            Serial.print("Base64 encoding failed");
            // Handle the error
        } else {
            Serial.println("7");
            // Proceed with using base64Image
            Serial.println(base64Image);
        }
        Serial.println("8");
        // After you're done using the camera buffer
        esp_camera_fb_return(fb);
    }

    Serial.print("[HTTPS] begin...\n");
    if (https.begin("https://api.openai.com/v1/completions")) {  // HTTPS
      
      https.addHeader("Content-Type", "application/json"); 
      String token_key = String("Bearer ") + chatgpt_token;
      https.addHeader("Authorization", token_key);
      
      // String payload = String("{\"model\": \"gpt-4-vision-preview\", \"prompt\": ") + chatgpt+Q + 
      
      String payload = String("{\"model\": \"text-davinci-003\", \"prompt\": ") + chatgpt_Q + String(", \"temperature\": 0, \"max_tokens\": 7}"); //Instead of TEXT as Payload, can be JSON as Paylaod
      
      Serial.print("[HTTPS] GET...\n");
      
      // start connection and send HTTP header
      int httpCode = https.POST(payload);

      // httpCode will be negative on error      
      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload);
      }
      else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    }
    else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
    
    Serial.println("Wait 60s before next round...");
    delay(60000);
    // }

    

  
}