#ifndef GPT_INTERFACE_H
#define GPT_INTERFACE_H

#include <Arduino.h>

class GPTInterface {
public:
    GPTInterface(const char* gpt_token); // Constructor
    String getResponse(const String& gpt_prompt, const String& base64_image); // Method to get response from GPT
    String parseResponse(String& response); // Method to parse the response
    String getParsedResponse(const String& gpt_prompt, const String& base64_image);

private:
    // TODO: not sure how to securely set chatgpt_token without 

    const char* _gpt_token; // Private member variable for storing the GPT token

    // Private helper methods
    String JSON_Payload(const String& gpt_prompt, const String& base64_image);
    String gptRequest(const String& payload, const char* gpt_token);
};

#endif // GPT_INTERFACE_H
