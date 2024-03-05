// Esp32.cpp
#include "Esp32.h"




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
