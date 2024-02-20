#include "Esp32.h"
#include "Camera.h"
#include "WifiAccess.h"
#include "gptInterface.h"
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
#include "sd_read_write.h"
#include "PlayerSpiffsI2S.h"

#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM
#define FORMAT_SPIFFS_IF_FAILED true

const String gpt_prompt = "Can you please describe what you see in front of you as if you were describing it to a blind individual? Please make your response as concise as possible. Do not describe the lighting of the image. do not mention low image quality. Do not mention color. Focus on objects in the scene.";
const char* ssid = "Claremont-ETC";
const char* password = "Cl@remontI0T";
const char* gpt_token = "";

WifiAccess wifiAccess(ssid, password);
GPTInterface gptInterface(gpt_token);
PlayerSpiffsI2S playerOut;
Camera camera;

void setup() {
    Serial.begin(115200);
    wifiAccess.connect();
    camera.initializeCamera();

    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
}

void loop() {
    if (touchRead(T14)>70000) {
        unsigned long stepStartTime;
        unsigned long stepDuration;

        // WiFi Connection Check
        stepStartTime = millis();
        wifiAccess.isConnected();
        stepDuration = millis() - stepStartTime;
        Serial.print("WiFi Check Duration: ");
        Serial.println(stepDuration);

        // Image Capture
        stepStartTime = millis();
        String image_base64 = camera.capture_base64();
        if(image_base64.length() == 0) {
            Serial.println("Failed to capture or encode photo.");
            return;
        }
        stepDuration = millis() - stepStartTime;
        Serial.print("Image Capture & Encoding Duration: ");
        Serial.println(stepDuration);

        // GPT Response
        stepStartTime = millis();
        String gpt_response = gptInterface.getImgResponse(gpt_prompt, image_base64);
        Serial.println(gpt_response);
        stepDuration = millis() - stepStartTime;
        Serial.print("GPT Processing Duration: ");
        Serial.println(stepDuration);

        // File Operations
        stepStartTime = millis();
        listDir(SPIFFS, "/", 0);
        gptInterface.GPT_Text_Speech_To_File(gpt_response);
        Serial.println("Done Writing Audio File");
        listDir(SPIFFS, "/", 0);
        stepDuration = millis() - stepStartTime;
        Serial.print("File System Operations Duration: ");
        Serial.println(stepDuration);

        // Audio Playback Setup
        stepStartTime = millis();
        playerOut.setup();
        unsigned long startTime = millis();
        unsigned long duration = 10000; // plays audio for about 10 seconds
        while (millis() - startTime < duration) {
            playerOut.loop();  
        }
        stepDuration = millis() - stepStartTime;
        Serial.print("Audio Playback Duration: ");
        Serial.println(stepDuration);

        deleteFile(SPIFFS, "/audio.mp3");
        ESP.restart(); // quick fix
    }
}