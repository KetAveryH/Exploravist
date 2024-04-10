# Exploravist
Our goal is to empower the visually impaired with tools that improve their independence at a reasonable cost. Our current solution is a wearable device that with a simple tap provides a text description of their environment. Being able to read out text is a very important feature of the device that improves user independence.

We are providing this device as a low-cost alternative to devices like Orcam and Envision which are typically priced between $2500 to $3000+. Our current manufacturing cost lies at around $20-$30 which we are able to achieve due to our use of widely available consumer hardware in our electronics. We plan to provide similar functionality at a fraction of the cost!

![Image of Device Version 2](/images/device.png "Exploravist Version 2")

## Team Organization:
Currently we have a few sub-teams with some general goals:

#### Embedded Software Team:
The Embedded Software Team works on writing code that is flashed onto the ESP32 S3 board. They are responsible for ensuring the reliability and responsiveness of device software. How the device will connect to Wi-Fi, and how it will respond to a user's tap is all determined by this team. The Embedded Software team is also responsible for integrating i2c and i2s communication with a variety of components with device software. This team is the heart of the device's functionality!

#### Device Hardware Design:
The Device Hardware Design Team works on the physical appearance and physical interface of the device. How do we design a light weight, easily attachable, and versatile device that is physically intuitive to use for the visually impaired.

#### Electrical PCB Design:
The Electrical PCB Team is responsible for getting all of how hardware onto a PCB. This minimizes weight, size, and simplifies the construction process of putting together new devices! 

#### App Development:
The App Development Team is currently working on a mobile app that pairs with our device. This will enable users to configure device settings from their mobile phone, and provides the opportunity of running local ML models when WiFi access is limited.

#### ML Dev Team:
The ML Dev Team is responsible for the research and development of future models that can fill in for our API Vision models when WiFi connection is lost. These models will be lower-resolution, but we hope to read text from an image or provide general scene recognition with mobile models. It also is possible that with models like DeblurGAN-v2 we can reduce the blurriness of pictures taken which we hope will improve image descriptions.

#### Server Dev Team:
In the future we plan to hand out these devices to many potential customers for testing. We want to be able to provide API access to each of these devices and would need some server to perform this management between all devices. Research in this area is required for the future progression of the project.

## The Github:
Currently the DeviceDevelopment holds all device code for the ESP32. The code that is flashed onto the ESP32 is held within the mainController folder and we currently use the Arduino IDE for development. Look into the README in the mainController folder for details on how to flash our code onto an ESP32.

There will also be an AppDevelopment folder along with a MLDevelopment folder in the near future, currently they are being developed in other branches.