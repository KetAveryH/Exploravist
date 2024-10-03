// Camera.cpp
#include "Camera.h"

//#include <SPIFFS.h>  might be necessary


// TODO:
// Create a frame_size() function to change resolution
// There seem to be other knobs you can turn, look into documentation ""
// website socket example, shows images over wifi located at:
// arduino_testing/Freenove_ESP32_WROVER_Board-main/C/Sketches/Sketch_06.1_CameraWebServer

Camera::Camera() {
    
}

/// Initializes camera pins and resolution among other knobs
void Camera::initializeCamera() {
    // OV2640 camera module
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    config.frame_size = FRAMESIZE_HVGA;  // XGA, VGA, CIF, SVGA
    config.jpeg_quality = 10;
    config.fb_count = 1;

    // Camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        ESP.restart();
    }
}


/// Capture Photo and return it as a Base64-encoded String
String Camera::capture_base64() {
  camera_fb_t *fb = esp_camera_fb_get(); // Take a photo with the camera
  // Figure out whether there are failures, how to return that
  // If there is a failure we want to get the most recent 
  if (!fb) {
      Serial.println("Camera capture failed");
      return ""; // Return an empty string to indicate failure
  } 
  esp_camera_fb_return(fb);

  // Take second picture which is now most recent
  fb = esp_camera_fb_get();
  if (!fb) {
      Serial.println("Camera capture failed");
      return ""; // Return an empty string to indicate failure
  } 
  // Serial.println(fb->width);
  // Serial.println(fb->height);
  // Serial.println(fb->format);

  // Encode the second (most recent) image in base64
  String base64Image = base64::encode(fb->buf, fb->len);
  if (base64Image.length() == 0) {
      Serial.println("Base64 encoding failed");
      esp_camera_fb_return(fb);
      return ""; // Return an empty string to indicate failure
  } else {
      Serial.print("Base64 Image Success! Length: ");
      Serial.println(base64Image.length());
      // Return the frame buffer back to the driver for reuse
      esp_camera_fb_return(fb);
      return base64Image; // Return the encoded image as a string
  }
}

  

