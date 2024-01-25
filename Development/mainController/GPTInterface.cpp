// GPTInterface.cpp
#include "GPTInterface.h"
#include <HTTPClient.h>

// TODO:
// Consider asynchronous HTTPS requests

const char* _gpt_token = ""; // TODO: 
                                // Need a better way to store gpt_token (be able to cycle through tokens securely)
                                // a configuration file would be good to start


GPTInterface::GPTInterface(const char* gpt_token) : _gpt_token(gpt_token) {}

String GPTInterface::extractTextResponse(DynamicJsonDocument& doc) {
    String textResponse;

    // Check if 'choices' array exists and has at least one element
    if (doc.containsKey("choices") && doc["choices"].is<JsonArray>() && !doc["choices"].isNull()) {
        JsonArray choices = doc["choices"].as<JsonArray>();

        // Navigate to the first 'message' object, if it exists
        if (!choices[0]["message"].isNull()) {
            JsonObject message = choices[0]["message"].as<JsonObject>();

            // Extract the 'role' and 'content' from the 'message' object
            String role = message["role"].as<String>();
            if (role == "assistant") {
                String content = message["content"].as<String>();
                textResponse = content;
            }
        }
    }

    return textResponse;
}

String GPTInterface::JSON_PayloadImg(const String& gpt_prompt, const String& base64_image) {

    DynamicJsonDocument doc(50000); // Adjust the size to suit your needs
    // TODO: Create a function that dynamically sets doc parameter based on image size.

    // Create properly formatted JSON
    JsonArray messagesArray = doc.createNestedArray("messages");

    JsonObject messageObject = messagesArray.createNestedObject();
    messageObject["role"] = "user";

    JsonArray contentArray = messageObject.createNestedArray("content");

    JsonObject textObject = contentArray.createNestedObject();
    textObject["type"] = "text";
    textObject["text"] = gpt_prompt;

    JsonObject imageObject = contentArray.createNestedObject();
    imageObject["type"] = "image_url";
    JsonObject imageUrlObject = imageObject.createNestedObject("image_url");
    imageUrlObject["url"] = "data:image/jpeg;base64," + base64_image;

    doc["model"] = "gpt-4-vision-preview";
    doc["max_tokens"] = 300;

    String payload;
    serializeJson(doc, payload);

    return payload;
}

String GPTInterface::gptImgRequest(const String& payload, const char* gpt_token) { // 
      // Does the API Communication 
      HTTPClient http;
      http.begin("https://api.openai.com/v1/chat/completions"); // Your API endpoint
      http.addHeader("Content-Type", "application/json");
      http.addHeader("Authorization", "Bearer " + String(gpt_token)); // Your API key

      int httpResponseCode = http.POST(payload);

      String response = "Error on response";

      if (httpResponseCode > 0) {
      response = http.getString();
      // Serial.println("API Response:");
      // Serial.println(response);
      } else {
      Serial.print("Error on sending POST: ");
      Serial.println(http.errorToString(httpResponseCode));
      }

      http.end();
      
    return response;
}

String GPTInterface::getImgResponse(const String& gpt_prompt, const String& base64_image) {
    // TODO:
    // call Json_payload, feed out paylaod into gpt_request
    // parse output and return
    String payload;
    payload = JSON_PayloadImg(gpt_prompt, base64_image);
    String response = gptImgRequest(payload, _gpt_token);

    // Parse the JSON response
    DynamicJsonDocument doc(20000); // Adjust the size according to your needs
    deserializeJson(doc, response);

    // Extract the text response
    String textResponse = extractTextResponse(doc);

    return textResponse;
}





// String GPTInterface::gptTextSpeech(const String& payload, const char* gpt_token) {
//      // Does the API Communication 
//       HTTPClient http;
//       http.begin("https://api.openai.com/v1/audio/speech"); // Your API endpoint
//       http.addHeader("Authorization", "Bearer " + String(_gpt_token)); // Your API key
//       http.addHeader("Content-Type", "application/json");
      

//       int httpResponseCode = http.POST(payload);

//       String response = "Error on response";

//       if (httpResponseCode > 0) {
//         if(httpResponseCode == HTTP_CODE_OK) {
//             // File file = SD_MMC.open("/audio.mp3", FILE_WRITE);
//             File file = SPIFFS.open("/audio.mp3", FILE_WRITE);
//             if(!file){
//                 Serial.println("Failed to open file for writing");
//                 return "";
//             }
//             http.writeToStream(&file);
//             file.close();
//             Serial.println("Audio file saved to SD card.");
//         }
//       } else {
//       Serial.print("Error on sending POST: ");
//       Serial.println(http.errorToString(httpResponseCode));
//       }

//       http.end();
      
//     return response;
// }




// String GPTInterface::getTextSpeech(const String& gpt_response) {
//     // TODO:
//     // call Json_payload, feed out paylaod into gpt_request
//     // parse output and return
//     String payload;
//     payload = JSON_Text_Speech(gpt_response);
//     return gptTextSpeech(payload, _gpt_token);
// }

String GPTInterface::JSON_Text_Speech(const String& gpt_response) {
    DynamicJsonDocument doc(50000); // Adjust the size to suit your needs
    // TODO: Create a function that dynamically sets doc parameter based on image size.

    // Create properly formatted JSON

    doc["input"] = gpt_response;
    doc["voice"] = "alloy";


    doc["model"] = "tts-1";
    doc["max_tokens"] = 300;

    String payload;
    serializeJson(doc, payload);

    return payload;
    
}

void GPTInterface::GPT_Text_Speech_To_File(const String& gpt_response) {
    HTTPClient http;
    http.begin("https://api.openai.com/v1/audio/speech"); // Your API endpoint
    http.addHeader("Authorization", "Bearer " + String(_gpt_token)); // Your API key
    http.addHeader("Content-Type", "application/json");

    String payload = JSON_Text_Speech(gpt_response);
    int httpResponseCode = http.POST(payload);
    
    // Make Http request 
    if (httpResponseCode > 0) {
        if(httpResponseCode == HTTP_CODE_OK) {
            // File file = SD_MMC.open("/audio.mp3", FILE_WRITE); // Uncomment if you want to write to SD_MMC instead
            File file = SPIFFS.open("/audio.mp3", FILE_WRITE);
            if(!file){
                Serial.println("Failed to open file for writing");
                return;
            }
            http.writeToStream(&file); // Writes out file
            file.close();
            Serial.println("Audio file saved.");
        }
      } else {
      Serial.print("Error on sending POST: ");
      Serial.println(http.errorToString(httpResponseCode));
      }

      http.end();
    return;
}   









// JSON Processing
// API Request (return text)
// Text Parser
// Audio to Text
// Text to Audio

