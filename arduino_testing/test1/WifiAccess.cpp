// WifiAccess.cpp
#include "WifiAccess.h"

// TO-DO 
// Use WifiManager library for everything WIFI related.

public:
    // On the initialization of a WifiAccess object, we will need to have an ssid and password
    
    // Should I be able to construct a WifiAccess object?? I don't know... TODO
    WifiAccess(const char* ssid, const char* password)
        : ssid(ssid), password(password) {}
        

    void connect() {

        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        while(!Serial); 

        // wait for WiFi connection
        WiFi.begin(ssid, password);
        Serial.print("Connecting to ");
        Serial.println(ssid);
        while (WiFi.status() != WL_CONNECTED) {  
            delay(1000);
            Serial.print(".");
        }
        Serial.println("connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());


        if (!SPIFFS.begin(true)) {
            Serial.println("An Error has occurred while mounting SPIFFS");
            ESP.restart();
        }
    }

    bool isConnected() {
        if(WiFi.status() != WL_CONNECTED) {
            Serial.println("WiFi not connected.");
            return true;
        } else {
            Serial.println("WiFi connected!");
            return false;
        }
    }
private:

    const char* ssid;
    const char* password;
    

