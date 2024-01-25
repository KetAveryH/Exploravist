// PlayerSpiffsI2S.cpp
#include "PlayerSpiffsI2S.h"

// Declare any global variables or objects here

const char *startFilePath="/";
const char* ext="mp3";
AudioSourceSPIFFS source(startFilePath, ext);
I2SStream i2s;
MP3DecoderHelix decoder;
AudioPlayer player(source, i2s, decoder);

void printMetaData(MetaDataType type, const char* str, int len){
  Serial.print("==> ");
  Serial.print(toStr(type));
  Serial.print(": ");
  Serial.println(str);
}


void PlayerSpiffsI2S::setup() {
    // Your setup code from player-spiffs-i2s.ino
    Serial.begin(115200);
    AudioLogger::instance().begin(Serial, AudioLogger::Info);

    // setup output
    auto cfg = i2s.defaultConfig(TX_MODE);
    cfg.pin_ws = 45;
    cfg.pin_bck = 47;
    cfg.pin_data = 21;
    i2s.begin(cfg);

    // setup player
    //source.setFileFilter("*Bob Dylan*");
    player.setMetadataCallback(printMetaData);
    player.begin();
}

void PlayerSpiffsI2S::loop() {
    // Your loop code from player-spiffs-i2s.ino
    player.copy();  // Just reads through data
}
