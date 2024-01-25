// ESPAudio.cpp
#include "ESPAudio.h"

// I2SStream i2s; // final output of decoded stream
// EncodedAudioStream dec(&i2s, new MP3DecoderHelix()); // Decoding stream



// Implementation of StringStream methods
StringStream::StringStream(const String& s) : data(s), position(0) {}

int StringStream::available() {
    return data.length() - position;
}

int StringStream::read() {
    if (position >= data.length()) return -1;
    return data[position++];
}

int StringStream::peek() {
    if (position >= data.length()) return -1;
    return data[position];
}

void StringStream::flush() {
    // Not needed for reading
}

size_t StringStream::write(uint8_t) {
    // Read-only stream
    return 0;
}


ESPAudio::ESPAudio() {
}

void ESPAudio::playBlocking(StringStream& mp3Stream) {
    StreamCopy copier(dec, mp3Stream); // Setup the stream copier
    
    // Play as long as there is data available in the MP3 stream
    while(mp3Stream.available() > 0) {
        copier.copy(); // Copy a chunk of data from the stream to the decoder
        
        // Optional: add a short delay to allow the buffer to process
        delay(10); // Adjust the delay based on your specific needs
    }
}



void ESPAudio::playAudioMp3(const String& mp3_file) {
    // Convert the String to a stream
    StringStream mp3Stream(mp3_file);

    // Initialize I2S and decoder here as in your setup function
    // setup i2s
    auto config = i2s.defaultConfig(TX_MODE);
    // you could define e.g your pins and change other settings
    config.pin_ws = 45;
    config.pin_bck = 47;
    config.pin_data = 21;
    //config.mode = I2S_STD_FORMAT;
    i2s.begin(config);

    // Start playing the MP3 data
    playBlocking(mp3Stream);
}




