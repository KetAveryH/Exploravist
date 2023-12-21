#ifndef GPT_INTERFACE_H
#define GPT_INTERFACE_H

#include <Arduino.h>

class GPTInterface {
public:
    GPTInterface(const char* gpt_token); // Constructor
    String getImgResponse(const String& gpt_prompt, const String& base64_image); // Method to get response from GPT
    String parseResponse(String& response); // Method to parse the response
    String getParsedResponse(const String& gpt_prompt, const String& base64_image);

    
    
    String getSpeechText(const String& gpt_response);


private:
    // TODO: not sure how to securely set chatgpt_token without 

    const char* _gpt_token; // Private member variable for storing the GPT token

    // Private helper methods
    String JSON_Text_Speech(const String& gpt_prompt);
    String gptTextSpeech(const String& payload, const char* gpt_token);
    
    String JSON_PayloadImg(const String& gpt_prompt, const String& base64_image);
    String gptImgRequest(const String& payload, const char* gpt_token);
};

#endif // GPT_INTERFACE_H
