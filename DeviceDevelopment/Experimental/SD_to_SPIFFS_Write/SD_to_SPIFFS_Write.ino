#include <FS.h>
#include "SPIFFS.h"
#include "SD_MMC.h"
// #include <SD.h> Seems like SD_MMC works on ESP32

#define SD_MMC_CMD 38 //Please do not modify it.
#define SD_MMC_CLK 39 //Please do not modify it. 
#define SD_MMC_D0  40 //Please do not modify it.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // SPIFFS Initialization
  if(!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }
  
  // SD_MMC Initialization
  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
  if (!SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5)) {
      Serial.println("Card Mount Failed");
      return;
    }

  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
      Serial.println("No SD_MMC card attached");
      return;
  }

  Serial.print("SD_MMC Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

  uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
  Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);


  ////
  // File Manipulation Below vvvv
  ////

  // Open file on SD card
  File fileOnSD = SD_MMC.open("/audio.mp3", FILE_READ);
  if (!fileOnSD) {
      Serial.println("Failed to open file for reading");
      return;
  }

  // Create a file on SPIFFS
  File fileOnSPIFFS = SPIFFS.open("/audio1.mp3", FILE_WRITE);
  if (!fileOnSPIFFS) {
      Serial.println("Failed to open file for writing");
      fileOnSD.close();
      return;
  }

  // Read from SD and write to SPIFFS
  byte buf[512];
  while (fileOnSD.available()) {
      size_t bytesRead = fileOnSD.read(buf, sizeof(buf));
      fileOnSPIFFS.write(buf, bytesRead);
  }

  // Close both files
  fileOnSD.close();
  fileOnSPIFFS.close();

  Serial.println("File transfer complete.");
}

void loop() {
  // put your main code here, to run repeatedly:

}
