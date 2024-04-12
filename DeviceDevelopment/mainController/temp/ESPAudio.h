#ifndef AUDIOPLAYERESP_H
#define AUDIOPLAYERESP_H

#include "AudioTools.h"
#include "AudioCodecs/CodecMP3Helix.h"
#include <Stream.h>
#include <Arduino.h> // Not sure if this is considered a double inclusion

class StringStream : public Stream {
private:
    String data;
    size_t position;

public:
    StringStream(const String& s);

    int available() override;
    int read() override;
    int peek() override;
    void flush() override;
    size_t write(uint8_t) override;
};

class ESPAudio {
public:
    ESPAudio();
    void playAudioMp3(const String& mp3_file);

private:
    void playBlocking(StringStream& stream);
};

#endif