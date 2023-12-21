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
#include <FS.h>
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

void sendAudioToWhisperAPI(const String& audioFilePath) {
    // Ensure the file exists
    if (!SPIFFS.exists(audioFilePath)) {
        Serial.println("Audio file not found: " + audioFilePath);
        return;
    }

    File audioFile = SPIFFS.open(audioFilePath, "r");
    if (!audioFile) {
        Serial.println("Failed to open audio file");
        return;
    }

    // Initialize HTTPClient
    HTTPClient http;
    http.begin("https://api.openai.com/v1/audio/transcriptions"); // Whisper API endpoint
    http.addHeader("Content-Type", "multipart/form-data");
    http.addHeader("Authorization", "Bearer " + String(chatgpt_token)); // Your API key

    // Start constructing the multipart/form-data request
    String httpRequestData = "--boundary\r\n";
    httpRequestData += "Content-Disposition: form-data; name=\"model\"\r\n\r\n";
    httpRequestData += "whisper-1\r\n"; // Model name
    httpRequestData += "--boundary\r\n";
    httpRequestData += "Content-Disposition: form-data; name=\"file\"; filename=\"audio.wav\"\r\n"; // Adjust the filename and content type
    httpRequestData += "Content-Type: audio/wav\r\n\r\n"; // Content type of the file

    http.POST(httpRequestData);

    // Send the file in chunks
    const size_t bufferSize = 512;
    uint8_t buffer[bufferSize];
    while (audioFile.available()) {
        size_t bytesRead = audioFile.read(buffer, bufferSize);
        if (http.sendRequestData(buffer, bytesRead) != bytesRead) {
            Serial.println("Failed to send audio data");
            break;
        }
    }

    // End of the multipart request
    http.sendRequestData("\r\n--boundary--\r\n", 17);

    // End the request and get the response
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Whisper API Response:");
        Serial.println(response);
    } else {
        Serial.print("Error on sending POST: ");
        Serial.println(http.errorToString(httpResponseCode));
    }

    // Cleanup
    audioFile.close();
    http.end();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SPIFFSInit();
  i2sInit();
  xTaskCreate(i2s_adc, "i2s_adc", 1024 * 4, NULL, 1, NULL);
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
    Serial.println("WiFi reconnected!");
  }

  // File path to the audio file
  String audioFilePath = "/path/audio.wav"; // Update this path

  // Send the audio file to the Whisper API
  sendAudioToWhisperAPI(audioFilePath);

  // Wait some time before next operation
  delay(60000);
}
