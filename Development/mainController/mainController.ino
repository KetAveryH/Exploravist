#include "Esp32.h"
#include "Camera.h"
#include "WifiAccess.h"
#include "gptInterface.h"
#include <SPIFFS.h>  // Might make a new SPIFFS file management Class

#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems

// This is a macro, defined in pre-processing
// All included files have access to this macro
#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM

const String gpt_prompt = "Can you please describe what you see in front of you as if you were describing it to a blind individual? Please make your response as concise as possible.";
const char* ssid = "";
const char* password = "";
const char* gpt_token = "";

WifiAccess wifiAccess(ssid, password); // Initialize WifiAccess object named "wifi"
GPTInterface gptInterface(gpt_token);

// GPTInterface gpt;
// gpt.gptInterface(gpt_token);
Camera camera;
// I want to define the ESP32 object in order to store password and setting information
// Esp32 esp32();

void setup() {
    // Serial port for debugging purposes
    Serial.begin(115200); 
    
    // wifiAccess.connect();
    wifiAccess.connect();
    camera.initializeCamera();
    
    // initialize Camera Object the #define above will take care of setting pins on initialization

    // "SPIFFS MEMORY" usage, 8 Mb FRAM. 
    // Set up SPIFFS in mainController (idk what to call this class yet)

    if (!SPIFFS.begin(true)) {
      Serial.println("An Error has occurred while mounting SPIFFS");
      ESP.restart();
   }


    // Turn-off the 'brownout detector'
    // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Might help overcome early shutoff due to power fluctuations
}

void loop() {
    // wifiAccess.isConnected();
    wifiAccess.isConnected();

    // We will need to figure out the control system to determine WHEN we run the following loop
    // 
    // embedded systems
    // interuptions prompted by user inputs
    // 
    // Buffer user inputs
    // Run parallel process that performs entire loop, the process is interruptable
    // main Controller will only check for inputs each clock cycle.
    // 

    String image_base64 = camera.capture_base64();

    if(image_base64.length() == 0) {
      Serial.println("Failed to capture or encode photo.");
      return;
    }
    
    // String gpt_response = GPTInterface.getResponse(gpt_prompt, image_base64);  // We want to change this to getParsed response to only return our package
    String gpt_response = gptInterface.getResponse(gpt_prompt, image_base64);
    Serial.println(gpt_response);
    // Not sure yet how to getAudio into a file, must look into SPIFFS reading

    Serial.println("Wait 60s before next round...");
    delay(60000);
}
