// Esp32.cpp
#include "Esp32.h"
// #include <Arduino.h>

#include "SD.h"
#include "SD_MMC.h"
#include "FS.h"
#include <SPI.h>
#include <Wire.h>

#define LED1 2

// MAX17048 Fuel Gauge Definitions
#define MAX17048_ADDRESS 0x36
#define MAX17048_VCELL 0x02 // voltage
#define MAX17048_SOC 0x04   // percentage
#define MAX17048_MODE 0x06
#define MAX17048_VERSION 0x08
#define MAX17048_CONFIG 0x0c
#define MAX17048_COMMAND 0xfe

#define I2S_LRC 45  // LR Clock (LRC)
#define I2S_BCLK 47 // Bit Clock (BCLK)
#define I2S_DOUT 21 // Data Out (DIN)

#define SD_MMC_CMD 38 // Please do not modify it.
#define SD_MMC_CLK 39 // Please do not modify it.
#define SD_MMC_D0 40  // Please do not modify it.

Audio audio;

Esp32::Esp32()
{
    ssid = "";
    password = "";
    systemVolume = 12;
    beep = 0;

    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(systemVolume); // 0...21

    Wire.begin(2, 48); // Initialize I2C
};

// Audio initializeAudio() {
//   Audio audio;
//   audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
//   audio.setVolume(systemVolume); // 0...21
// }

void Esp32::playWAVFile(const String &filename)
{

    delay(5);
    if (!audio.connecttoFS(SD_MMC, filename.c_str()))
    {
        Serial.println("Failed to connect to file system.");
        return;
    }

    while (audio.isRunning())
    {
        // Serial.println("is playing");
        audio.loop();
        if (Serial.available())
        { // put streamURL in serial monitor
            audio.stopSong();
            String r = Serial.readString();
            r.trim();
            if (r.length() > 5)
                audio.connecttohost(r.c_str());
            log_i("free heap=%i", ESP.getFreeHeap());
        }
    }

    // Your actual code to play the .wav file should go here
    Serial.println("Playing file: " + filename);
}

void Esp32::increaseVolume()
{
    if (systemVolume < 21)
    {
        systemVolume += 1;             // Increase the volume by 1 unit
        audio.setVolume(systemVolume); // Apply the new volume to the Audio object
        Serial.print("Volume increased to: ");
        Serial.println(systemVolume);
    }
    else
    {
        Esp32::playWAVFile("MaximumVolume.wav");
        Serial.println("Maximum Volume.");
    }
}

void Esp32::decreaseVolume()
{
    if (systemVolume > 0)
    {
        systemVolume -= 1;             // Decrease the volume by 1 unit
        audio.setVolume(systemVolume); // Apply the new volume to the Audio object
        Serial.print("Volume decreased to: ");
        Serial.println(systemVolume);
    }
    else
    {
        Serial.println("Volume is already at minimum.");
    }
}

float Esp32::readPercentage()
{
    uint16_t soc = read16(MAX17048_SOC);
    Serial.println(soc);
    // Wire.endTransmission();
    return static_cast<float>(soc) / 256; // Convert to percentage
}

// Function to find the nearest multiple of 5
int Esp32::nearestMultipleOfFive(int percentage)
{
    return ((percentage + 2) / 5) * 5;
}

uint16_t Esp32::read16(uint8_t reg)
{
    Wire.beginTransmission(MAX17048_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission(false);                // Send repeated start condition, not a stop condition
    Wire.requestFrom((int)MAX17048_ADDRESS, 2); // Request 2 bytes from the MAX17048_ADDRESS

    if (Wire.available() == 2)
    {
        uint16_t value = Wire.read() << 8 | Wire.read();
        return value;
    }
    return 0; // Return 0 if no data is available, indicating an error
}

// Function to play the WAV file based on the battery percentage
void Esp32::playBatterySound(int percentage)
{
    int roundedPercentage = nearestMultipleOfFive(percentage);
    String filename = "Battery" + String(roundedPercentage) + ".wav";
    Serial.println(filename);
    playWAVFile(filename);
}

void Esp32::playTextSegments(String text, String lang)
{
    // Audio audio;
    // audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    // audio.setVolume(100);
    int stop_play = 0;

    if (text.length() <= 200)
    {
        // If the text is shorter than 200 characters, play it directly.
        delay(10);
        audio.connecttospeech(text.c_str(), lang.c_str());
        Serial.print("Attempting to read full text, no segments");
        while (audio.isRunning())
        {
            audio.loop();
            if (touchRead(T14) > 35000)
            {
                stop_play = 1;
                break;
            }
        }
    }
    else
    {
        // Split and play longer texts in segments.
        size_t start = 0;
        while (start < text.length())
        {
            size_t segmentLength = 200;
            if (start + segmentLength > text.length())
                segmentLength = text.length() - start;

            // Find the nearest space to cut off the segment
            size_t end = start + segmentLength;
            if (end < text.length())
            {
                while (end > start && text[end] != ' ')
                    end--;
            }

            // Create a segment
            String segment = text.substring(start, end);

            // Play the segment
            Serial.print("Here is our segment: ");
            Serial.println(segment);
            audio.connecttospeech(segment.c_str(), lang.c_str());
            while (audio.isRunning())
            {
                audio.loop();
                if (touchRead(T14) > 35000)
                {
                    stop_play = 1;
                    break;
                }
            }

            if (stop_play == 1)
            {
                break;
            }

            start = end + 1; // Move to the next segment
        }

        if (stop_play)
        {
            delay(300);
        }
    }
}

void Esp32::GoogleTTS(String text, String lang)
{

    if (text != NULL)
    {
        Serial.println("Playing texts");
        playTextSegments(text, lang);
    }
    else
    {
        Serial.println("Error TTS, text empty");
    }
}

int Esp32::getBeep()
{
    return beep;
}

void Esp32::setBeep(int beeps)
{
    beep = beeps;
}

void blinkNtimes(int numTimes, int spacing)
{
    pinMode(LED1, OUTPUT);
    if (numTimes < 0 || spacing < 0)
        return;

    for (int i = 0; i < numTimes; i++)
    {

        if (i != 0)
        { // Don't delay first blink
            delay(spacing);
        }

        digitalWrite(LED1, HIGH);
        delay(spacing);
        digitalWrite(LED1, LOW);
    }
}