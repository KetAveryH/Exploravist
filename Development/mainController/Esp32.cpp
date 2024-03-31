// Esp32.cpp
#include "Esp32.h"
// #include <Arduino.h>
#include "AudioESP.h"
#include "SD.h"
#include "SD_MMC.h"
#include "FS.h"
#include <SPI.h>
#include <Wire.h>
#include <time.h>
#include <iostream>
#include <chrono>
#include <thread>


#define LED1 2

// MAX17048 Fuel Gauge Definitions
#define MAX17048_ADDRESS        0x36
#define MAX17048_VCELL          0x02 // voltage
#define MAX17048_SOC            0x04 // percentage
#define MAX17048_MODE           0x06
#define MAX17048_VERSION        0x08
#define MAX17048_CONFIG         0x0c
#define MAX17048_COMMAND        0xfe

#define I2S_LRC       45 // LR Clock (LRC)
#define I2S_BCLK      47 // Bit Clock (BCLK)
#define I2S_DOUT      21 // Data Out (DIN)

#define SD_MMC_CMD 38 //Please do not modify it.
#define SD_MMC_CLK 39 //Please do not modify it. 
#define SD_MMC_D0  40 //Please do not modify it.


Esp32::Esp32() {
    
    ssid = "";
    password = "";
    systemVolume = 0.015;
    beep = 0;
    Wire.begin(2,48); // Initialize I2C
};

float Esp32::readPercentage() {
    uint16_t soc = read16(MAX17048_SOC);
    Serial.println(soc);
    // Wire.endTransmission();
    return static_cast<float>(soc) / 256; // Convert to percentage
}

void Esp32::playWAVFile(const String &filename) {
    AudioESP audio;
    

    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(12); // 0...21

    audio.connecttoFS(SD_MMC, filename.c_str());
    delay(25);

    while (audio.isRunning()) {
        // Serial.println("is playing");
        audio.loop();

        if(Serial.available()){ // put streamURL in serial monitor
            audio.stopSong();
            String r=Serial.readString(); r.trim();
            if(r.length()>5) audio.connecttohost(r.c_str());
            log_i("free heap=%i", ESP.getFreeHeap());
        }

        if(touchRead(T3) > TOUCHTHRESHOLD) {
            break;
        }
    }
    
    // Your actual code to play the .wav file should go here
    
}

// Function to find the nearest multiple of 5
int Esp32::nearestMultipleOfFive(int percentage) {
    return ((percentage + 2) / 5) * 5;
}

uint16_t Esp32::read16(uint8_t reg) {
    Wire.beginTransmission(MAX17048_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission(false); // Send repeated start condition, not a stop condition
    Wire.requestFrom((int)MAX17048_ADDRESS, 2); // Request 2 bytes from the MAX17048_ADDRESS
    
    if (Wire.available() == 2) {
        uint16_t value = Wire.read() << 8 | Wire.read();
        return value;
    }
    return 0; // Return 0 if no data is available, indicating an error
}

// Function to play the WAV file based on the battery percentage
void Esp32::playBatterySound(int percentage) {
  int roundedPercentage = nearestMultipleOfFive(percentage);
  String filename = "Battery " + String(roundedPercentage) + " .wav";
//   filename = "Volume.wav"; // for testing
  playWAVFile(filename);
}

// Reads out the menus
int Esp32::menuAudioManager(int menuIndex){
    String filename = "";
    if (menuIndex == 1) {
        filename = "ShortDescription.wav";
        playWAVFile(filename);  // Just testing if the type is an issue
      } else if (menuIndex == 2) {
        playWAVFile("LongDescription.wav");
      } else if (menuIndex == 3) {
        playWAVFile("Volume.wav");
      } else if (menuIndex == 4) {
        playWAVFile("BatteryLevel.wav");
      } else {
        Serial.println("Outside of menu range Error");
      }

}

// Outputs current position in the selection menu
// 1: short description 2: Long Description 3: Volume
int Esp32::menuManager(int* menuIndex){
    while (true) {

        // Front Button Pressed
        if (touchRead(T14)>TOUCHTHRESHOLD) {  
            return *menuIndex;
        }

        // Back Button Pressed
        if (touchRead(T3)>TOUCHTHRESHOLD) {
            Serial.println("We are here");
            if (*menuIndex >= 3) {
                *menuIndex = 1;
            }
            
            (*menuIndex)++;
            delay(10);
            menuAudioManager(*menuIndex);
        }
        delay(10);
    }
    
}

int Esp32::inputHandler() {
    int prev_value = touchRead(T14);
    // continuously poll the difference
    while (true) {
        // sleep for some time 
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // current_value
        int curr_value = touchRead(T14);
        int difference = curr_value - prev_value;
        std::cout << "Difference" << difference << endl;

        prev_value = curr_value;


    }

    return 0;
    // // when difference is above a certain threshold, then change state (go into while loop)
    // // if tap, call menuManger
    // while (capacitanceHold > x secs) { 
    //     // track to another state change 
    //     //x threshold is number of seconds
    //     //count secs

    //     time_t start = time(0);
    //     double seconds_since_start = difftime( time(0), start);
    // }
    // // if hold,
}


int Esp32::getBeep() {
    return beep;
}

void Esp32::setBeep(int beeps) {
    beep = beeps;
}

void blinkNtimes(int numTimes, int spacing) {
    pinMode(LED1,OUTPUT);
    if (numTimes < 0 || spacing < 0) return;
    
    for (int i=0; i<numTimes; i++) {

        if (i != 0) {       // Don't delay first blink
            delay(spacing);
        }

        digitalWrite(LED1, HIGH);
        delay(spacing);
        digitalWrite(LED1, LOW);
    }
}
