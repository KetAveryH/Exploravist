// esp32.cpp
#include "esp32.h"
#include "Camera.h"
#include "esp_camera.h"
#include ""

class esp32 {
private:
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

    // Wifi Credentials
    const char* ssid = "Claremont-ETC";
    const char* password = "Cl@remontI0T";

    // GPT Info
    const char* chatgpt_token = "";

public:
    ESP32() {
        // Initialize ESP32 components
    }


    /// WIFI THINGS VVV

    

    /// MICROPHONE THINGS VVV


    /// SPEAKER THINGS VVV


    //// CAMERA THINGS VVV




    /// GPT API THINGS VVV
    
    // Other ESP32-specific methods...
};
