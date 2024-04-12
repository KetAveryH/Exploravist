// PlayerSpiffsI2S.h
#ifndef PLAYER_SPIFFS_I2S_H
#define PLAYER_SPIFFS_I2S_H

#include "AudioTools.h"
#include "AudioLibs/AudioSourceSPIFFS.h"
#include "AudioCodecs/CodecMP3Helix.h"

class PlayerSpiffsI2S {
public:
    void setup();
    void loop();
};

#endif // PLAYER_SPIFFS_I2S_H
