#ifndef GPT_INTERFACE_H
#define GPT_INTERFACE_H

#include <Arduino.h>
#include "SD_MMC.h"
#include <SPIFFS.h>
#include <FS.h>
#include <ArduinoJson.h>


class GPTInterface {
public:
    GPTInterface(const char* gpt_token); // Constructor
    String getImgResponse(const String& gpt_prompt, const String& base64_image); // Method to get response from GPT
    void GPT_Text_Speech_To_File(const String& gpt_response);
    void GoogleTTS(String text, String lang);
    void playTextSegments(String text, String lang);
    void setMaxToken(int max_token);
    

private:
    // TODO: not sure how to securely set chatgpt_token

    const char* _gpt_token; // Private member variable for storing the GPT token
    int _max_token;

    // Private helper methods

    String JSON_Text_Speech(const String& gpt_prompt); // TTS helper

    String extractTextResponse(DynamicJsonDocument& doc); // GPT image + prompt helpers
    String JSON_Img_Payload(const String& gpt_prompt, const String& base64_image, int img_len);
    String GPT_img_request(const String& payload, const char* gpt_token);
};

#endif // GPT_INTERFACE_H
