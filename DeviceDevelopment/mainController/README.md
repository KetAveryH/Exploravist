# Running This Code on Your ESP32 S3!
### Step 1: Create a Config.h file that holds your WiFi SSID/PASS along with your API Key

// Copy the following below in to a Config.h fileand fill in the blanks.

const char* ssid = ";
const char* password = "";
char* gpt_token = "";
char* anthropic_key = "";

### Step 2: Arduino IDE Library Downloads
To download make sure to download the respective repositories as ZIP files and import it into the Arduino IDE under ``` Sketch > Include Library > Add .ZIP Library... ```

- Phil Pschatzmann's 
    - [Audio-Tools](https://github.com/pschatzmann/arduino-audio-tools)
    - [Decoder-Helix](https://github.com/pschatzmann/arduino-libhelix)
- ArduinoJson library (Use Arduino IDE Library Search Bar)
- [Audio.h by schreibfaul1](https://github.com/schreibfaul1/ESP32-audioI2S/tree/master)

### Step 3: Open maincontroller.ino in the Arduino IDE with the following settings
- Board: ESP32s3 Dev...
- COM: Make sure to select the proper USB Port.
- PSRAM: TOOLS>PSRAM set to "OPI"
- Boot: Tools>Boot> "Huge APP"

### Step 4: Press Upload button to compile and flash your ESP32 code!
