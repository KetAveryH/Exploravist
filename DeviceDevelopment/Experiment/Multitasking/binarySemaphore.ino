//================================================================================//
/*
  ESP32 Binary Semaphore Example
  Read more at https://circuitstate.com/tutorials/how-to-write-parallel-multitasking-applications-for-esp32-with-freertos-arduino
*/
//================================================================================//

SemaphoreHandle_t xSemaphore = NULL;  // Create a semaphore object

//================================================================================//

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode (LED_BUILTIN, OUTPUT);

  Serial.begin (115200);

  xSemaphore = xSemaphoreCreateBinary();  // Set the semaphore as binary

  xTaskCreatePinnedToCore (
    task1,     // Function to implement the task
    "task1",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    10,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );

  xTaskCreatePinnedToCore (
    task2,     // Function to implement the task
    "2000",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    10,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );
}

//================================================================================//

// the loop function runs over and over again forever
void loop() {
  digitalWrite (LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay (1000);  // wait for a second
  digitalWrite (LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay (1000);  // wait for a second
}

//================================================================================//

// this task will periodically release the binary semaphore
void task1 (void *pvParameters) {
  while (1) {
    Serial.print ("Binary Semaphore released at ");
    Serial.println (xTaskGetTickCount());
    xSemaphoreGive (xSemaphore);  // Release the semaphore
    delay (1000);
  }
}

//================================================================================//

// this task will wait for the binary semaphore to be released
void task2 (void *pvParameters) {
  while (1) {
    if (xSemaphoreTake (xSemaphore, (200 * portTICK_PERIOD_MS))) {  // try to acquire the semaphore
      Serial.print ("Binary Semaphore acquired at ");
      Serial.println (xTaskGetTickCount());
    }
    else {  // if the semaphore was not acquired within 200ms
      Serial.print ("Binary Semaphore not acquired at ");
      Serial.println (xTaskGetTickCount());
    }
  }
}

//================================================================================//
