//================================================================================//
/*
  ESP32 Mutex Example
  Read more at https://circuitstate.com/tutorials/how-to-write-parallel-multitasking-applications-for-esp32-with-freertos-arduino
*/
//================================================================================//

SemaphoreHandle_t xMutex = NULL;  // Create a mutex object

int counter = 0;  // A shared variable

//================================================================================//

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode (LED_BUILTIN, OUTPUT);

  Serial.begin (115200);

  xMutex = xSemaphoreCreateMutex();  // crete a mutex object

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
    "task2",   // Name of the task
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

// this task will periodically lock the mutex, increment the counter by 1 and unlock the mutex
void task1 (void *pvParameters) {
  while (1) {
    if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex
      Serial.print ("Task 1: Mutex acquired at ");
      Serial.println (xTaskGetTickCount());
      counter = counter + 1;  // increment the counter
      Serial.print ("Task 1: Counter = ");
      Serial.println (counter);
      delay (1000);
      xSemaphoreGive (xMutex);  // release the mutex
      delay (100);
    }
  }
}

//================================================================================//

// this task will periodically lock the mutex, increment the counter by 1000 and unlock the mutex
void task2 (void *pvParameters) {
  while (1) {
    if (xSemaphoreTake (xMutex, (200 * portTICK_PERIOD_MS))) {  // try to acquire the mutex
      Serial.print ("Task 2: Mutex acquired at ");
      Serial.println (xTaskGetTickCount());
      counter = counter + 1000;
      Serial.print ("Task 2: Counter = ");
      Serial.println (counter);
      xSemaphoreGive (xMutex);  // release the mutex
      delay (100);
    }
    else {  // if the mutex was not acquired within 200ms
      Serial.print ("Task 2: Mutex not acquired at ");
      Serial.println (xTaskGetTickCount());
    }
  }
}

//================================================================================//
