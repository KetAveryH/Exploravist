#include "Esp32.h"
#include "Camera.h"
#include "WifiAccess.h"
#include "gptInterface.h"
#include "sd_read_write.h"
#include "PlayerSpiffsI2S.h"
#include <driver/i2s.h>
#include <Arduino.h>
#include "config.h"

#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

#define LED1 2
/// mainController.ino is the controller for all the functionality within our ESP32 device.


// This is a macro, defined in pre-processing
// All included files have access to this macro
#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM

#define FORMAT_SPIFFS_IF_FAILED true

// #define I2S_SCK 47 // BCLK
// #define I2S_WS  45 // LRC
// #define I2S_SD  21  //DOUT
#define I2S_PORT I2S_NUM_0



// Audio audio;

// I2S configuration
// i2s_config_t i2s_config = {
//     .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
//     .sample_rate = 16000,
//     .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
//     .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
//     .communication_format = I2S_COMM_FORMAT_STAND_MSB,
//     .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
//     .dma_buf_count = 8,
//     .dma_buf_len = 64
// };

// I2S pinout
// i2s_pin_config_t pin_config = {
//     .bck_io_num = I2S_SCK,
//     .ws_io_num = I2S_WS,
//     .data_out_num = I2S_SD,
//     .data_in_num = I2S_PIN_NO_CHANGE
// };


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
  

void setup() {
    // Serial port for debugging purposes
    Serial.begin(115200); 
    
    Serial.println(ssid);
    delay(1000);
    wifiAccess.connect();
    // blinkNtimes(2, 400);
    camera.initializeCamera();


    // SPIFFS Initialization
    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    // Turn-off the 'brownout detector'
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Might help overcome early shutoff due to power fluctuations
    
    // Initialize I2S
    // i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    // i2s_set_pin(I2S_PORT, &pin_config);

    // audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    // audio.setVolume(100);

    // Start a task to generate and play the tone
    // xTaskCreatePinnedToCore(playTone, "PlayTone", 8192, NULL, 1, NULL, 0);
}



void loop() {
    
    // blinkNtimes(4, 200); 
    // delay(500);
    // We will need to figure out the control system to determine WHEN we run the following loop
    // 
    // embedded systems
    // interuptions prompted by user inputs
    // 
    // Buffer user inputs
    // Run parallel process that performs entire loop, the process is interruptable
    // main Controller will only check for inputs each clock cycle.
    // 

    

    // if (touchRead(T14)>20000) {
      if (touchRead(T14)>35000) {
        Serial.println(wifiAccess.isConnected()); 
        if (wifiAccess.isConnected()) {
        //   blinkNtimes(1, 300);

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
        
        // while (request_count < 10 && gpt_response == "Error on response") {
        //     if (request_delay > 1000) {
        //       request_delay = 500;
        //     }
        //     delay(request_delay); // Wait before retrying
        //     gpt_response = gptInterface.getImgResponse(gpt_prompt, image_base64);
            
        //     request_delay *= 2; // Exponential back-off
        //     request_count++;
        // }
        
        request_count = 0;
        // device.setBeep(1);
        
        
        
        
        
        
        listDir(SPIFFS, "/", 0);
        
        
        
        
        // gptInterface.GPT_Text_Speech_To_File(gpt_response);
        gptInterface.GoogleTTS(gpt_response, "en");

        // Serial.println("Done Writing Audio File");
        // listDir(SPIFFS, "/", 0);

        // Serial.println("Waiting to Start Audio");
        // playerOut.setup();
        
        // unsigned long startTime = millis();
        // unsigned long duration = 10000; // plays audio for about 10 seconds

        // while (millis() - startTime < duration) {
        //     // playerOut.loop();  
        //     audio.loop()
        // }
        // Serial.println("Audio Done");
        // deleteFile(SPIFFS, "/audio.mp3");

        // ESP.restart(); // quick fix
    }

    
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




