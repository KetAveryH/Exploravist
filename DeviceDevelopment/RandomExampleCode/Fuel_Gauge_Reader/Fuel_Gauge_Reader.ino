#include <Wire.h>

#define MAX17048_ADDRESS        0x36
#define MAX17048_VCELL          0x02 // voltage
#define MAX17048_SOC            0x04 // percentage
#define MAX17048_MODE           0x06
#define MAX17048_VERSION        0x08
#define MAX17048_CONFIG         0x0c
#define MAX17048_COMMAND        0xfe

void setup() {
  Serial.begin(115200);
  Wire.begin(2,48); // Initialize I2C
}

void loop() {
  float voltage = readVoltage();
  float percentage = readPercentage();

  // Output the values to the Serial Monitor
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");
  
  Serial.print("Percentage: ");
  Serial.print(percentage);
  Serial.println(" %");

  delay(1700); // Wait for 10 seconds before updating again
}

float readVoltage() {
  uint16_t vCell = read16(MAX17048_VCELL);
  return (float)(vCell) * 78.125 / 1000000; // Convert to voltage
}

float readPercentage() {
  uint16_t soc = read16(MAX17048_SOC);
  return (float)(soc) / 256; // Convert to percentage
}

uint16_t read16(uint8_t reg) {
  Wire.beginTransmission(MAX17048_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(false); // false to send repeated start condition, not stop condition
  
  // Explicitly cast address to the type expected by the method signature.
  Wire.requestFrom((uint16_t)MAX17048_ADDRESS, (uint8_t)2); 
  
  // Ensure reading is completed before proceeding.
  if (Wire.available() == 2) {
      uint16_t value = Wire.read() << 8 | Wire.read();
      return value;
  }
  return 0; // Return 0 if data is not available to indicate error.
}

