// WiFI.cpp
#include <WiFi.h>

// TO-DO 
// Use WifiManager library for everything WIFI related.


void initializeWifi() {
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

void isConnected() {
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected. Attempting to reconnect...");
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        }
        Serial.println("\nWiFi reconnected!");
    }
}

