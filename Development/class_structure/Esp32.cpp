// Esp32.cpp
#include "Esp32.h"
#include "Camera.h"
#include "WifiAccess.h"
#include "gptAccess.h"



Esp32::Esp32() {
    ssid = "";
    password = "";
    systemVolume = 0.015;
}

