// Esp32.cpp
#include "Esp32.h"
#include <Arduino.h>
#define LED1 2



Esp32::Esp32() {
    ssid = "";
    password = "";
    systemVolume = 0.015;
    beep = 0;
};


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