// mic_to_wav.h
#ifndef MIC_TO_WAV_H
#define MIC_TO_WAV_H

#include <Arduino.h>
#include <SPIFFS.h>

#define I2S_WS 42
#define I2S_SD 41
#define I2S_SCK 1
#define I2S_PORT I2S_NUM_0
#define I2S_SAMPLE_RATE   (16000)
#define I2S_SAMPLE_BITS   (16)
#define I2S_READ_LEN      (16 * 1024)
#define RECORD_TIME       (20) //Seconds
#define I2S_CHANNEL_NUM   (1)
#define FLASH_RECORD_SIZE (I2S_CHANNEL_NUM * I2S_SAMPLE_RATE * I2S_SAMPLE_BITS / 8 * RECORD_TIME)

void SPIFFSInit();

void i2sInit();

void i2s_adc_data_scale(uint8_t * d_buff, uint8_t* s_buff, uint32_t len);

void i2s_adc(void *arg);

void example_disp_buf(uint8_t* buf, int length);

void wavHeader(byte* header, int wavSize);

void listSPIFFS(void);

#endif // MIC_TO_WAV_H