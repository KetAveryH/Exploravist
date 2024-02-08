#include "Esp32.h"
#include "Camera.h"
#include "WifiAccess.h"
#include "gptInterface.h"
#include "soc/soc.h"           // Disable brownout problems
#include "soc/rtc_cntl_reg.h"  // Disable brownout problems
#include "sd_read_write.h"
#include "PlayerSpiffsI2S.h"



// #include "sd_read_write.h"





// This is a macro, defined in pre-processing
// All included files have access to this macro
#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM

#define FORMAT_SPIFFS_IF_FAILED true


const String gpt_prompt = "Can you please describe what you see in front of you as if you were describing it to a blind individual? Please make your response as concise as possible. Do not describe the lighting of the image. do not mention low image quality. Do not mention color. Focus on objects in the scene.";
const char* ssid = "Claremont-ETC";
const char* password = "Cl@remontI0T";
const char* gpt_token = "";

WifiAccess wifiAccess(ssid, password); // Initialize WifiAccess object named "wifi"
GPTInterface gptInterface(gpt_token);
PlayerSpiffsI2S playerOut;
Camera camera;
  

void setup() {
    // Serial port for debugging purposes
    Serial.begin(115200); 
    
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



void loop() {
    

    // We will need to figure out the control system to determine WHEN we run the following loop
    // 
    // embedded systems
    // interuptions prompted by user inputs
    // 
    // Buffer user inputs
    // Run parallel process that performs entire loop, the process is interruptable
    // main Controller will only check for inputs each clock cycle.
    // 

    

    if (touchRead(T14)>70000) {
        wifiAccess.isConnected();


        String image_base64 = camera.capture_base64();
        if(image_base64.length() == 0) {
        Serial.println("Failed to capture or encode photo.");
        return;
        }
        
        String gpt_response = gptInterface.getImgResponse(gpt_prompt, image_base64);
        Serial.println(gpt_response);
        
        listDir(SPIFFS, "/", 0);
        
        
        

        gptInterface.GPT_Text_Speech_To_File(gpt_response);
        Serial.println("Done Writing Audio File");
        listDir(SPIFFS, "/", 0);

        Serial.println("Waiting to Start Audio");
        playerOut.setup();
        
        unsigned long startTime = millis();
        unsigned long duration = 10000; // plays audio for about 10 seconds

        while (millis() - startTime < duration) {
            playerOut.loop();  
        }
        Serial.println("Audio Done");
        deleteFile(SPIFFS, "/audio.mp3");

        ESP.restart(); // quick fix
    }

    
}
