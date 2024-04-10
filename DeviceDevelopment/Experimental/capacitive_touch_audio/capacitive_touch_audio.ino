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
    // Initialize I2S
    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_PORT, &pin_config);

    // Start a task to generate and play the tone
    xTaskCreatePinnedToCore(playTone, "PlayTone", 8192, NULL, 1, NULL, 0);
}

void loop() {
    // Empty loop
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