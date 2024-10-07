// WifiAccess.cpp
#include "WifiAccess.h"
#include "sd_read_write.h"
#include "FS.h"
#include "SPIFFS.h"

// @TODO 
// Use WifiManager library for everything WIFI related.
// Incorporate Flash Encryption: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/security/flash-encryption.html

String _ssid;
String _password;

// @TODO
// Use WifiMulti
// Inputs: a list of ssid password pairs in preferential order to addAP
//
// Required helper functions:
// read list of pairs from SPIFFS
// Update SPIFFS passwords.txt 

// Stored In SPIFFS:
const char* WiFiList[] = {"SSID1", "Pass1", "SSID2", "PASS2"} 

WiFiMulti::WiFiMulti() {
    File file = SPIFFS.open("/WiFiList");
    if (!file || file.isDirectory()) {
        Serial.println("- failed to find WiFi Network List, starting AP");
        // TODO: Implement WifiManager AP Setup to configure WiFi
        return;
    }
    
    std::vector<String> lines; // Use vector to store lines temporarily
    while (file.available()) {
        String line = file.readStringUntil('\n'); // Read each line as a string
        line.trim(); // Trim any whitespace/newlines
        if (line.length() > 0) {
            lines.push_back(line); // Store in vector
        }
    }
    
    file.close(); // Close file when done
    
    // Ensure the number of lines is even (SSID + Password pairs)
    if (lines.size() % 2 != 0) {
        Serial.println("Error: Mismatched SSID and Password pairs");
        return;
    }

    // Create array of SSID/Password pairs
    const char** wifiList = new const char*[lines.size()];
    for (size_t i = 0; i < lines.size(); i++) {
        wifiList[i] = strdup(lines[i].c_str()); // Allocate and copy each string
    }

    // Connect to WiFi networks using pairs
    for (size_t i = 0; i < lines.size(); i += 2) {
        const char* ssid = wifiList[i];
        const char* password = wifiList[i + 1];
        Serial.printf("Connecting to SSID: %s with Password: %s\n", ssid, password);
        // TODO: Use ssid and password to connect with WiFiMulti
    }
    
    // Clean up memory when done
    for (size_t i = 0; i < lines.size(); i++) {
        free((void*)wifiList[i]);
    }
    delete[] wifiList;
}


/**
 * This is a wrapper object for the ESP32's wifi packages
 * 
 * @param Inputs Provide an ssid + password to initialize WifiAccess object
 * 
*/
WifiAccess::WifiAccess(const char* ssid, const char* password)
    : _ssid(ssid), _password(password) {}



void WifiAccess::connect() {

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    while(!Serial); 

    // wait for WiFi connection
    WiFi.begin(_ssid, _password);
    Serial.print("Connecting to ");
    Serial.println(_ssid);
    while (WiFi.status() != WL_CONNECTED) {  
        delay(1000);
        Serial.print(".");
    }
    Serial.println("connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

bool WifiAccess::isConnected() {
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected.");
        return false;
    } else {
        Serial.println("WiFi connected!");
        return true;
    }
}




