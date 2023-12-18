// Esp32.cpp
#include "Esp32.h"
#include "Camera.h"
#include "WifiAccess.h"
#include "gptAccess.h"


public:
    Esp32() {}

private:

    const char* ssid = "";
    const char* password = "";
    float systemVolume = 0.015;