#ifndef WIFI_ACCESS_H
#define WIFI_ACCESS_H

#include <WiFi.h>
#include <WiFiMulti.h>


class WifiAccess {
public:
    WifiAccess(const char* ssid, const char* password); // Constructor
    void connect(); // Method to initialize WiFi
    bool isConnected(); // Method to check if WiFi is connected

private:
    WiFiMulti wifiMulti;
    const char** _ssid_list;
    const char** _Password_list;
    const char*  _ssid; // Private member variable for storing the SSID
    const char*  _password; // Private member variable for storing the WiFi password
};

#endif // WIFI_ACCESS_H
