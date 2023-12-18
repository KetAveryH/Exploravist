#include <Arduino.h>
#include <driver/i2s.h>

// I2S pin configuration
#define I2S_SCK 47
#define I2S_WS  45
#define I2S_SD  21
#define I2S_PORT I2S_NUM_0

// I2S configuration
i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64
};

// I2S pinout
i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_SD,
    .data_in_num = I2S_PIN_NO_CHANGE
};

void setup() {
  // put your setup code here, to run once:

  // Initialize I2S
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);

  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Touch Test");
}

void playTone(void * parameter) {
    const int sample_rate = 16000;
    const int frequency = 440; // Frequency of the tone (A4 note)
    const float volume = 0.1; // Very low volume

    int16_t *sample = (int16_t *)malloc(sample_rate * sizeof(int16_t));
    if (sample == NULL) {
        Serial.println("Failed to allocate memory for tone");
        return;
    }

    for (int i = 0; i < sample_rate; ++i) {
        sample[i] = sin(frequency * 2 * PI * i / sample_rate) * 32767 * volume;
    }

    while (true) {
        size_t bytes_written;
        i2s_write(I2S_PORT, sample, sample_rate * sizeof(int16_t), &bytes_written, portMAX_DELAY);
    }

    free(sample);
    vTaskDelete(NULL);
}
//variables for counting and array assigning
int count=0;
int arr[2]={};
int apos=0;

void loop() {
  // put your main code here, to run repeatedly:

  //detects if it is currently being touched and counts for how long
  while(touchRead(T14)>70000){
    count++;
    delay(10);
  }

  //decides how long touch must last to be counted as being held
  if(count>50){
    arr[apos]=1;
    apos++;
    Serial.println("held");
    count=0;
    if (arr[0]>0){
    Serial.println(arr[0]);
  }
    }

  //decides how long touch must last to be counted as being tapped
  else if (50>count&&count>=1){
    arr[apos]=-1;
    apos++;
    Serial.println("tapped");
    count=0;
  }
}
