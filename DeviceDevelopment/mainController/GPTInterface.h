#ifndef GPT_INTERFACE_H
#define GPT_INTERFACE_H

#include <Arduino.h>
#include "SD_MMC.h"
#include <HTTPClient.h>
#include <SPIFFS.h>
#include <FS.h>
#include <ArduinoJson.h>

class GPTInterface
{
public:
    GPTInterface(const char *gpt_token, const char *anthropic_key, const char *gemini_key);    // Constructor
    void beginGPT(); // Initialize the GPT HTTP client          
    void beginANTHROPIC(); // Initialize the Anthropic HTTP client    
    void beginGEMINI();
    String getImgResponse(const String &gpt_prompt, const String &base64_image); // Method to get response from GPT
    String anthropicImgResponse(const String &gpt_prompt, const String &base64_image);
    String Gemini_Request(const String &payload, const char *gemini_key);
    void GPT_Text_Speech_To_File(const String &gpt_response);
    String extractGeminiTextResponse(const String &response);

    String JSON_Gemini_Payload(const String &role, const String &text, const String &fileMimeType, const String &fileUri);
    
    // void GoogleTTS(String text, String lang);
    // void playTextSegments(String text, String lang);
    void setMaxToken(int max_token);
    ~GPTInterface(); // Destructor to clean up
    int model_select = 0;

private:
    // TODO: not sure how to securely set chatgpt_token
    HTTPClient http;
    
    const char *_gpt_token; // Private member variable for storing the GPT token
    const char *_anthropic_key;
    const char *_gemini_key;
    int _max_token;

    // Private helper methods

    String JSON_Text_Speech(const String &gpt_prompt); // TTS helper

    String extractTextResponse(DynamicJsonDocument &doc); // GPT image + prompt helpers
    String JSON_Img_Payload(const String &gpt_prompt, const String &base64_image, int img_len);
    String GPT_img_request(const String &payload, const char *gpt_token);
    String Anthropic_img_request(const String &payload, const char *anthropic_key);
    String extractAnthropicResponse(DynamicJsonDocument &doc);
    
};

#endif // GPT_INTERFACE_H
