#ifndef WIFI_ACCESS_H
#define WIFI_ACCESS_H

#include <WiFi.h>

class WifiAccess {
public:
    WifiAccess(const char* ssid, const char* password); // Constructor
    void connect(); // Method to initialize WiFi
    bool isConnected(); // Method to check if WiFi is connected

private:
    const char* _ssid; // Private member variable for storing the SSID
    const char* _password; // Private member variable for storing the WiFi password
};

#endif // WIFI_ACCESS_H
