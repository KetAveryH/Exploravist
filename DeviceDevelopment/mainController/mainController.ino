#include "Esp32.h"
#include "Camera.h"
#include "WifiAccess.h"
#include "gptInterface.h"
#include "sd_read_write.h"
#include "SD_MMC.h"   // new

#include "Audio.h" // new
#include "PlayerSpiffsI2S.h"
#include <driver/i2s.h>
#include <Arduino.h>
#include "config.h"

#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

#define LED1 2
/// mainController.ino is the controller for all the functionality within our ESP32 device.

#define I2S_LRC       45 // LR Clock (LRC)
#define I2S_BCLK      47 // Bit Clock (BCLK)
#define I2S_DOUT      21 // Data Out (DIN)

#define SD_MMC_CMD 38 //Please do not modify it.
#define SD_MMC_CLK 39 //Please do not modify it. 
#define SD_MMC_D0  40 //Please do not modify it.

// This is a macro, defined in pre-processing
// All included files have access to this macro
#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM

#define FORMAT_SPIFFS_IF_FAILED true

// #define I2S_SCK 47 // BCLK
// #define I2S_WS  45 // LRC
// #define I2S_SD  21  //DOUT
#define I2S_PORT I2S_NUM_0


// const String gpt_prompt = "Can you please describe what you see in front of you as if you were describing it to a blind individual? Please make your response as concise as possible. Do not describe the lighting of the image. do not mention low image quality. Do not mention color. Focus on objects in the scene.";
const String gpt_prompt = "Please provide a description of this image suitable for a blind or visually impaired individual. The photo is taken from a first-person perspective using a wearable device, intended to capture the wearer's viewpoint. Your description will be relayed through a speaker. Follow these guidelines for your response: Direct Pointing: If a finger points at something, describe what is being pointed at, focusing solely on this aspect. Finger Box: Text Reading: If text is enclosed within a hand-formed box, read it aloud. If the text is unclear, describe the visible part of the object where the text appears. No Text or Blurry: Describe what's inside the box, ignoring the surroundings. Hand Circle: If a circle is formed by the hand, provide a detailed yet concise description of the entire scene, aiming for aesthetic and practical value. General Scene: Absent any hand signals, offer a straightforward description of the scene, prioritizing likely points of interest. Provide a general overview thereafter. Image Quality Disclaimer: Disregard the camera's quality when responding, striving to provide the best possible description under any circumstances. If an aspect (like text) is too blurred to discern, describe its base object and suggest taking another photo if needed";

// Copy the following below in to a Config.h fileand fill in the blank.
// const char* ssid = ";
// const char* password = "";
// const char* gpt_token = "";
//

int request_count = 0;

WifiAccess wifiAccess(ssid, password); // Initialize WifiAccess object named "wifi"
GPTInterface gptInterface(gpt_token);
Esp32 device;
PlayerSpiffsI2S playerOut;
Camera camera;
Audio audio;

void setup() {
    // Serial port for debugging purposes
    Serial.begin(115200); 
    
    Serial.println(ssid);
    delay(1000);
    wifiAccess.connect();
    camera.initializeCamera();

    // SD_MMC Initialization
    SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
    if (!SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5)) {
      Serial.println("Card Mount Failed");
      return;
    }
    uint8_t cardType = SD_MMC.cardType();
    if(cardType == CARD_NONE){
        Serial.println("No SD_MMC card attached");
        return;
    }

    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(12); // 0...21

    // SPIFFS Initialization
    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    // Turn-off the 'brownout detector'
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Might help overcome early shutoff due to power fluctuations
}

int menuIndex = 0;
String menuOptions[] = {"shortDescription.wav", "LongDescription.wav", "Volume.wav", "BatteryLevel.wav"};
bool first = true;

void loop() {
    
    if (touchRead(T3)>35000) {
        menuIndex++;
        if (menuIndex > 3 || first) {
            menuIndex = 0;
            first = false;
        } 

        audio.connecttoFS(SD_MMC, menuOptions[menuIndex].c_str());
        // delay(50); // give user time to take their hand off of the button
        while (audio.isRunning()) {
            audio.loop();
        }
    }


    if (touchRead(T14)>35000) { 
        if (menuIndex == 0) {          // Short Description
          gptInterface.setMaxToken(75);   
        } else if (menuIndex == 1) {   // Long Description
          gptInterface.setMaxToken(150);
        }

    // Description
      if (menuIndex == 0 || menuIndex == 1) {
        // int percentage = device.readPercentage(); 
        // device.playBatterySound(percentage);

        Serial.println(wifiAccess.isConnected()); 
        if (wifiAccess.isConnected()) {
        } else {
        //   blinkNtimes(4, 1000); // If WiFi Not connected blink 4 times, 1 second long beeps.
        }

        // Play sound 
        String image_base64 = camera.capture_base64();
        // Serial.print(image_base64);
        if(image_base64.length() == 0) {
        Serial.println("Failed to capture or encode photo.");
        return;
        }

        Serial.println(image_base64);
        
        
        String gpt_response = gptInterface.getImgResponse(gpt_prompt, image_base64);
        
        request_count = 0;
        // device.setBeep(1);
        
        
        listDir(SPIFFS, "/", 0);

        
        // gptInterface.GPT_Text_Speech_To_File(gpt_response);
        gptInterface.GoogleTTS(gpt_response, "en");
      }

       // Volume
      if(menuIndex == 2) {
        Serial.println("Work in progress");
      }

      // BatteryLevel
      if (menuIndex == 3) {
        int percentage = device.readPercentage(); 
        device.playBatterySound(percentage);
      }
        
    }

   



    //   if (touchRead(T14)>35000) {
    //     int percentage = device.readPercentage(); 
    //     device.playBatterySound(percentage);

    //     Serial.println(wifiAccess.isConnected()); 
    //     if (wifiAccess.isConnected()) {
    //     } else {
    //     //   blinkNtimes(4, 1000); // If WiFi Not connected blink 4 times, 1 second long beeps.
    //     }

    //     // Play sound 
    //     String image_base64 = camera.capture_base64();
    //     // Serial.print(image_base64);
    //     if(image_base64.length() == 0) {
    //     Serial.println("Failed to capture or encode photo.");
    //     return;
    //     }

    //     Serial.println(image_base64);
        
        
    //     String gpt_response = gptInterface.getImgResponse(gpt_prompt, image_base64);
        
    //     request_count = 0;
    //     // device.setBeep(1);
        
        
    //     listDir(SPIFFS, "/", 0);

        
    //     // gptInterface.GPT_Text_Speech_To_File(gpt_response);
    //     gptInterface.GoogleTTS(gpt_response, "en");
    // }

    
}

void playTone(void * parameter) {
    while (1) {
        // play 1 beep
        if (device.getBeep() == 1) {
            const int sample_rate = 16000;
            const int frequency = 440; // Frequency of the tone (A4 note)
            const float volume = 0.1; // Very low volume

            int16_t *sample = (int16_t *)malloc(sample_rate * sizeof(int16_t));

            if (sample == NULL) {
                Serial.println("Failed to allocate memory for tone");
                return;
            }

            for (int i = 0; i < sample_rate; ++i) {
                sample[i] = sin(frequency * 2 * PI * i / sample_rate) * 32767 * volume;
            }
            
            unsigned long startTime = millis();
            unsigned long duration = 250; // plays audio for about 3 seconds
            Serial.println("Started Beep");
            while (millis() - startTime < duration) {
                Serial.println(millis() - startTime);
                size_t bytes_written;
                i2s_write(I2S_PORT, sample, sample_rate * sizeof(int16_t), &bytes_written, portMAX_DELAY);
            }
            Serial.println("finished with beep");
            i2s_stop(I2S_PORT); // Stop I2S driver and transmission
            free(sample);
            device.setBeep(0);
        }
        // play two beeps
        if (device.getBeep() == 2) {
            const int sample_rate = 16000;
            const int frequency = 440; // Frequency of the tone (A4 note)
            const float volume = 0.1; // Very low volume

            int16_t *sample = (int16_t *)malloc(sample_rate * sizeof(int16_t));

            if (sample == NULL) {
                Serial.println("Failed to allocate memory for tone");
                return;
            }

            for (int i = 0; i < sample_rate; ++i) {
                sample[i] = sin(frequency * 2 * PI * i / sample_rate) * 32767 * volume;
            }
            
            unsigned long startTime = millis();
            unsigned long duration = 100; // plays audio for about 3 seconds
            while (millis() - startTime < duration) {
                size_t bytes_written;
                i2s_write(I2S_PORT, sample, sample_rate * sizeof(int16_t), &bytes_written, portMAX_DELAY);
            } 
            i2s_stop(I2S_PORT); // Stop I2S driver and transmission
            delay(250);
            startTime = millis(); // reset start time
            while (millis() - startTime < duration) {
                size_t bytes_written;
                i2s_write(I2S_PORT, sample, sample_rate * sizeof(int16_t), &bytes_written, portMAX_DELAY);
            }
            i2s_stop(I2S_PORT); // Stop I2S driver and transmission
            free(sample);
            device.setBeep(0);
        }
        vTaskDelay(10);
        // vTaskDelete(NULL); This would be used to delete the current thread but we want to continuously check for inputs.
    }
}




