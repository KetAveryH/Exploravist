// esp32.h
#ifndef ESP32_H
#define ESP32_H

// MACROS FOR PIN LAYOUT:
#define CAMERA_MODEL_ESP32S3_EYE // ESP32-s3 WROOM | Has 
#define TOUCHTHRESHOLD 35000 

#include <cstdint>
#include <Arduino.h>

//#define CAMERA_MODEL_WROVER_KIT // ESP32 WROVER  | Has PSRAM
// #define CAMERA_MODEL_AI_THINKER // ESP32-CAM    | Has PSRAM


class  Esp32 {
    public:
        Esp32();
        int getBeep();
        void setBeep(int);
        float readPercentage();
        void playBatterySound(int percentage);
        int menuManager(int* menuIndex);
        int inputHandler();

        // Implement getter and setter methods for the private variables below/
    private:
        int menuAudioManager(int menuIndex);
        void playWAVFile(const String &filename);
        uint16_t read16(uint8_t reg);
        int nearestMultipleOfFive(int percentage);
        const char* ssid;
        const char* password;
        float systemVolume;
        int beep;
    };


void blinkNtimes(int numTimes, int spacing);

#endif // ESP32_H