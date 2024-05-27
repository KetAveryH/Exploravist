// esp32.h
#ifndef ESP32_H
#define ESP32_H

// MACROS FOR PIN LAYOUT:
#define CAMERA_MODEL_ESP32S3_EYE // ESP32-s3 WROOM | Has PSRAM
#include <cstdint>
#include <Arduino.h>
#include "Audio.h"

// #define CAMERA_MODEL_WROVER_KIT // ESP32 WROVER  | Has PSRAM
//  #define CAMERA_MODEL_AI_THINKER // ESP32-CAM    | Has PSRAM

class Esp32
{
public:
    Esp32();
    float readPercentage();
    void playBatterySound(int percentage);
    void GoogleTTS(String text, String lang);
    void increaseVolume();
    void decreaseVolume();
    void playWAVFile(const String &filename);
    // int inputHandlerTapHold();
    // int inputHandlerDoubleTap();
    Audio audio;

    // Implement getter and setter methods for the private variables below/
private:
    void playTextSegments(String text, String lang);
    uint16_t read16(uint8_t reg);
    int nearestMultipleOfFive(int percentage);
    const char *ssid;
    const char *password;
    float systemVolume;
};

void blinkNtimes(int numTimes, int spacing);

#endif // ESP32_H


// ESP32 Class:
// InitializeDevice : Will call camera, AI token, and wifi initializations
// Make AI Request : 
//