#ifndef AI_INTERFACE_H
#define AI_INTERFACE_H

#include <Arduino.h>
#include "SD_MMC.h"
#include <HTTPClient.h>
#include <SPIFFS.h>
#include <FS.h>
#include <ArduinoJson.h>

class AIInterface
{
public:
    AIInterface(const char *gpt_token, const char *anthropic_key);    // Constructor
    void beginGPT(); // Initialize the GPT HTTP client          
    void beginANTHROPIC(); // Initialize the Anthropic HTTP client    
    String gptImgResponse(const String &gpt_prompt, const String &base64_image); // Method to get response from GPT
    String anthropicImgResponse(const String &gpt_prompt, const String &base64_image);
    void GPT_Text_Speech_To_File(const String &gpt_response);
    // void GoogleTTS(String text, String lang);
    // void playTextSegments(String text, String lang);
    void setMaxToken(int max_token);
    ~AIInterface(); // Destructor to clean up
    int model_select = 0;

private:
    // TODO: not sure how to securely set chatgpt_token
    HTTPClient http;
    
    const char *_gpt_token; // Private member variable for storing the GPT token
    const char *_anthropic_key;
    int _max_token;

    // Private helper methods

    String JSON_Text_Speech(const String &gpt_prompt); // TTS helper

    String extractTextResponse(DynamicJsonDocument &doc); // GPT image + prompt helpers
    String JSON_Img_Payload(const String &gpt_prompt, const String &base64_image, int img_len);
    String GPT_img_request(const String &payload, const char *gpt_token);
    String Anthropic_img_request(const String &payload, const char *anthropic_key);
    String extractAnthropicResponse(DynamicJsonDocument &doc);
};

#endif // AI_INTERFACE_H