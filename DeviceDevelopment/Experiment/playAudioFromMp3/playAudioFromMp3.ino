/**
 * @file streams-url_mp3-i2s.ino
 * @author Phil Schatzmann
 * @brief decode MP3 stream from url and output it on I2S
 * @version 0.1
 * @date 2021-96-25
 * 
 * @copyright Copyright (c) 2021
 */

// install https://github.com/pschatzmann/arduino-libhelix.git

#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"
#include "gptInterface.h"
#include "WifiAccess.h"

#include <Stream.h>
#include <Arduino.h>

class StringStream : public Stream {
    private:
        String data;
        size_t position;

    public:
        StringStream(const String& s) : data(s), position(0) {}

        int available() {
            return data.length() - position;
        }

        int read() {
            if (position >= data.length()) return -1;
            return data[position++];
        }

        int peek() {
            if (position >= data.length()) return -1;
            return data[position];
        }

        void flush() {
            // Not needed for reading
        }

        size_t write(uint8_t) {
            // Read-only stream
            return 0;
        }
};



URLStream url("Linksys3000","jass loves lynxlee"); // Not needed for now
I2SStream i2s; // final output of decoded stream
EncodedAudioStream dec(&i2s, new MP3DecoderHelix()); // Decoding stream



const char* ssid = "Linksys3000";
const char* password = "jass loves lynxlee";
const char* gpt_token = "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";

WifiAccess wifiAccess(ssid, password); // Initialize WifiAccess object named "wifi"

AIInterface aiInterface(gpt_token);

String gpt_audio = aiInterface.getTextSpeech("hello, I am ready to assist you!");
String mp3Data = gpt_audio;
StringStream mp3Stream(mp3Data);

StreamCopy copier(dec, mp3Stream); // copy mp3Stream to decoder
    

void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);  
  wifiAccess.connect();

  // setup i2s
  auto config = i2s.defaultConfig(TX_MODE);
  // you could define e.g your pins and change other settings
  config.pin_ws = 45;
  config.pin_bck = 47;
  config.pin_data = 21;
  //config.mode = I2S_STD_FORMAT;
  i2s.begin(config);


  // setup I2S based on sampling rate provided by decoder
  dec.setNotifyAudioChange(i2s);
  dec.begin();
  Serial.println("dec begun");

// // mp3 Stream  
//   mp3Stream.begin();

  // url.begin("http://stream.srg-ssr.ch/m/rsj/mp3_128","audio/mp3");

}

void loop(){
  wifiAccess.isConnected();
  copier.copy();
}
