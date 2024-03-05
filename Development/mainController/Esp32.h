// esp32.h
#ifndef ESP32_H
#define ESP32_H

// MACROS FOR PIN LAYOUT:
#define CAMERA_MODEL_ESP32S3_EYE // ESP32-s3 WROOM | Has PSRAM
//#define CAMERA_MODEL_WROVER_KIT // ESP32 WROVER  | Has PSRAM
// #define CAMERA_MODEL_AI_THINKER // ESP32-CAM    | Has PSRAM


class  Esp32 {
    public:
        Esp32();
        int getBeep();
        void setBeep(int);

        // Implement getter and setter methods for the private variables below/
    private:
        const char* ssid;
        const char* password;
        float systemVolume;
        int beep;
    };

#endif // ESP32_H