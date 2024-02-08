#include "Esp32.h"
#include "Camera.h"
#include "WifiAccess.h"
#include "gptInterface.h"

#include "sd_read_write.h"
#include "PlayerSpiffsI2S.h"
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM
#define FORMAT_SPIFFS_IF_FAILED true

// variables defined on heap that must eventually be de-allocated
// int that determines whether or not the loop responsible for taking / sending an image / playing audio continues
// By manipulating this variable we can early terminate/ cancel

void setup() {
    // Serial port for debugging purposes
    Serial.begin(115200); 
    int* takePic = new int(0);
    int* cancelPic = new int(0);

    wifiAccess.connect();
    camera.initializeCamera();

    // SPIFFS Initialization
    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }

     // Turn-off the 'brownout detector'
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Might help overcome early shutoff due to power fluctuations
}

// We want to always check if we are connected to wifi, if not we want to try to re-connect

// We want to always check for inputs. We could have an "input checker". 
    // We want to be able to eventually be able to cancel the reading of any 

void inputCheck() {
    while (1) {
        if (touchRead(T14)>70000) {
            *takePic = 1;
        }
    }
}

void takePicture() {
    while(*takePic) {  // I am going to not use takePic, instead I am going to create a class that manages these states for me, a devicemanager class in ESP32.
        String image_base64 = camera.capture_base64();

        if(image_base64.length() == 0) {
            Serial.println("Failed to capture or encode photo.");
            return;
        }

        String gpt_response = gptInterface.getImgResponse(gpt_prompt, image_base64);

        Serial.println(gpt_response);

        gptInterface.GPT_Text_Speech_To_File(gpt_response);

        playerOut.setup();
        unsigned long startTime = millis();
        unsigned long duration = 30000; // plays audio for about 30 seconds

        while (millis() - startTime < duration) {
            playerOut.loop();  
        }

        *takePic = 0;
    }
}

// Function that removes elements from cache


void audioPlay() {
    while (1) {

    }
}

