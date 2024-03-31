// GPTInterface.cpp
#include "GPTInterface.h"
#include <HTTPClient.h>
#include "AudioESP.h"
#include "Esp32.h"

#define LED1 2

#define I2S_DOUT      21
#define I2S_BCLK      47
#define I2S_LRC       45

// TODO:
// Consider asynchronous HTTPS requests

const char* _gpt_token = ""; // TODO: 
                                // Need a better way to store gpt_token (be able to cycle through tokens securely)
                                // a configuration file would be good to start

int _max_token = 75;

GPTInterface::GPTInterface(const char* gpt_token) : _gpt_token(gpt_token) {}


void GPTInterface::setMaxToken(int max_token) {
  _max_token = max_token;
}
/**
 * HELPER FUNCTION to getImgResponse()
 * 
 * Takes in Prompt + Image and returns in a JSON payload format for the API call.
 * 
 * @param Inputs a gpt_prompt + base64 image
 * @return returns payload in JSON format.
*/
String GPTInterface::JSON_Img_Payload(const String& gpt_prompt, const String& base64_image, int img_len) {
    DynamicJsonDocument doc(2000 + img_len); // Adjust the size to suit your needs
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
    doc["max_tokens"] = _max_token;

    String payload;
    serializeJson(doc, payload);

    return payload;
}



/**
 * HELPER FUNCTION to getImgResponse()
 * 
 * Makes API call given a JSON payload containing GPT Prompt + base64 Image
 * 
 * @param Inputs a JSON payload with the image and prompt inside
 * @return JSON payload of API response.
*/
String GPTInterface::GPT_img_request(const String& payload, const char* gpt_token) { // 
      // Does the API Communication 
    
      pinMode(LED1,OUTPUT);
      HTTPClient http;
      http.begin("https://api.openai.com/v1/chat/completions"); // Your API endpoint
      http.addHeader("Content-Type", "application/json");
      http.addHeader("Authorization", "Bearer " + String(gpt_token)); // Your API key

      http.setTimeout(20000); // Adjust this value as needed

      int httpResponseCode = http.POST(payload);

      String response = "Error on response";

      if (httpResponseCode > 0) {
      response = http.getString();
      // Serial.println("API Response:");
      // Serial.println(response);
      } else {
      Serial.print("Error on sending POST: ");
      Serial.println(http.errorToString(httpResponseCode));
      // We need to figure out a way to properly repeat HTTP request.
      }

      http.end();


    return response;
}

/**
 * HELPER FUNCTION to getImgResponse()
 * 
 * Is responsible for parsing GPT API response to return only the image description parameter.
 * 
 * @param Inputs A GPT API response as a DynamicJsonDocument document 
 * @return String, extracted GPT API text response
*/
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


/**
 * Makes GPT API call on image + prompt pair, returning an image description.
 * 
 * @param Inputs  a gpt_prompt and a base_64 encoded image 
 * @return String, GPT API image description
*/
String GPTInterface::getImgResponse(const String& gpt_prompt, const String& base64_image) {
    String payload;
    int image_len = base64_image.length();

    payload = JSON_Img_Payload(gpt_prompt, base64_image, image_len); // puts gpt_prompt and base64_image into proper JSON format
    String response = GPT_img_request(payload, _gpt_token);
    
    if (response == "Error on response") {
        return "Sorry, there was an issue getting a text response.";
    } else {
        // Parse the JSON response
        DynamicJsonDocument doc(1000 + response.length()); // Adjust the size according to your needs
        deserializeJson(doc, response); // deserializes JSON

        // Extract the text response
        String textResponse = extractTextResponse(doc);

        return textResponse;
    }
    
}



/**
 * HELPER FUNCTION to GPT_Text_Speech_To_File
 * 
 * Takes GPT text response and properly formats it as a JSON package to prepare for 
 * Whisper Text To Speech API call. 
 * 
 * @param Inputs a GPT text response
 * @return A JSON payload as a string for the Whisper TTS API call 
*/
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



/**
 * Makes TTS API call to Whisper, stores .mp3 file in SPIFFS memory
 * 
 * @param Inputs  a GPT text API response as a const String&.
 * @note Stores all Text-To-Speech outputs to SPIFFS as an .mp3 file
*/
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
            // File file = SD_MMC.open("/audio.mp3", FILE_WRITE); // Uncomment if you want to write to SD_MMC instead, issue reading from SD_MMC
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




void GPTInterface::playTextSegments(String text, String lang) {
    AudioESP audio;
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(100);
    int stop_play = 0; 


    if (text.length() <= 200) {
        // If the text is shorter than 200 characters, play it directly.
        audio.connecttospeech(text.c_str(), lang.c_str());
        Serial.print("Attempting to read full text, no segments");
        while (audio.isRunning()) {
                audio.loop();
                if (touchRead(T14)>35000) {
                  stop_play = 1;
                  break;
                }
            }
    } else {
        // Split and play longer texts in segments.
        size_t start = 0;
        while (start < text.length()) {
            size_t segmentLength = 200;
            if (start + segmentLength > text.length()) segmentLength = text.length() - start;
           
            // Find the nearest space to cut off the segment
            size_t end = start + segmentLength;
            if (end < text.length()) {
                while (end > start && text[end] != ' ') end--;
            }


            // Create a segment
            String segment = text.substring(start, end);


            // Play the segment
            Serial.print("Here is our segment: ");
            Serial.println(segment);
            audio.connecttospeech(segment.c_str(), lang.c_str());
            while (audio.isRunning()) {
                audio.loop();
                if (touchRead(T14)>35000) {
                  stop_play = 1;
                  break;
                }
            }

            if (stop_play == 1) {
              break;
            }


            start = end + 1; // Move to the next segment
        }

      if (stop_play) {
        delay(300);
      }
    }
}


void GPTInterface::GoogleTTS(String text, String lang) {
   


    if (text != NULL) {
        Serial.println("Playing texts");
        playTextSegments(text, lang);
    } else {
        Serial.println("Error TTS, text empty");
    }
   
}





// JSON Processing
// API Request (return text)
// Text Parser
// Audio to Text
// Text to Audio
