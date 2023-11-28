#ifndef WIFI_ACCESS_H
#define WIFI_ACCESS_H

#include <WiFi.h>

class WifiAccess {
public:
    WifiAccess(const char* ssid, const char* password); // Constructor
    void initializeWifi(); // Method to initialize WiFi
    bool isConnected(); // Method to check if WiFi is connected

private:
    const char* ssid; // Private member variable for storing the SSID
    const char* password; // Private member variable for storing the WiFi password
};

#endif // WIFI_ACCESS_H
