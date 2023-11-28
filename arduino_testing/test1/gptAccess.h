#ifndef GPT_ACCESS_H
#define GPT_ACCESS_H

#include <Arduino.h>

class gptAccess {
public:
    gptAccess(const char* gpt_token); // Constructor
    String getResponse(const String& gpt_prompt, const String& base64_image); // Method to get response from GPT
    String parseResponse(String& response); // Method to parse the response

private:
    const char* chatgpt_token; // Private member variable for storing the GPT token

    // Private helper methods
    String jsonPayload(const String& gpt_prompt, const String& base64_image);
    String gptRequest(const String& payload, const char* chatgpt_token);
};

#endif // GPT_ACCESS_H
