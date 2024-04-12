#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>
#include "base64.h" // For converting img to base64
#include "esp_camera.h"
#include "Esp32.h"
#include "Camera.h"
#include "camera_pins.h" // This defines the Macros that will define our camera pins in initializeCamera();

class Camera
{
public:
    Camera();
    void initializeCamera();
    String capture_base64();

private:
};

#endif // CAMERA_H
