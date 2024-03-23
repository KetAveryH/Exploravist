### Step 1: Create a Config.h file that holds your WiFi SSID/PASS along with your API Key

// Copy the following below in to a Config.h fileand fill in the blank.

const char* ssid = ";
const char* password = "";
char* gpt_token = "";

### Step 2: Arduino IDE Library Downloads
- Phil Pschatzmann's 
    - [Audio-Tools](https://github.com/pschatzmann/arduino-audio-tools)
    - [Decoder-Helix](https://github.com/pschatzmann/arduino-audio-tools)
- ArduinoJson 

### Step 3: Open maincontroller.ino in the Arduino IDE with the following settings
- Board: ESP32s3 Dev...
- COM: Make sure to select the proper USB Port.
- PSRAM: TOOLS>PSRAM set to "OPI"
- Boot: Tools>Boot> "Huge APP"

### Step 4: Press Upload button to compile and flash your ESP32 code!
