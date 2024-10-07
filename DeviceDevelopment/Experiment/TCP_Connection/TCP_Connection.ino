#include <WiFi.h>
#include "config.h"

// const char* ssid = "myNetWork";
// const char* password = "Mypassword";
const char* ip_address = "";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP:");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client;

  if(!client.connect(IPAddress(ip_address), 3131)){
    Serial.println("Connection to host failed");

    delay(1000);
    return;
  }

  client.print("Hello from ESP32!");

  client.stop();

}