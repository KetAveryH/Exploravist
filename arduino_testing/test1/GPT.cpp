// GPT.cpp

#include <ArduinoJson.h>
#include <HTTPClient.h>

class GPT {


    public:
    String get_response(String gpt_prompt, String base64_image) {
        // TODO:
        // call Json_payload, feed out paylaod into gpt_request
        // parse output and return
        String payload;
        payload = JSON_Payload(gpt_prompt, base64_image);
        payload = gpt_request(payload, chatgpt_token)
    }

    private:
    const char* chatgpt_token = "";

    // HELPER FUNCTION
    String JSON_Payload(String gpt_prompt, String base64_image) {
    DynamicJsonDocument doc(50000); // Adjust the size to suit your needs

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
    
    return payload
    }

    void gpt_request(String payload, const char* chatgpt_token) { // 
        // Does the API Communication 
        HTTPClient http;
        http.begin("https://api.openai.com/v1/chat/completions"); // Your API endpoint
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer " + String(chatgpt_token)); // Your API key

        int httpResponseCode = http.POST(payload);

        if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("API Response:");
        Serial.println(response);
        } else {
        Serial.print("Error on sending POST: ");
        Serial.println(http.errorToString(httpResponseCode));
        }

        http.end();
    }

    

    // JSON Processing
    // API Request (return text)
    // Text Parser
    // Audio to Text
    // Text to Audio

}
