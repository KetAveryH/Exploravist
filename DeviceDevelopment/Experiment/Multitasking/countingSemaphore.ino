//================================================================================//
/*
  ESP32 Counting Semaphore Example
  Read more at https://circuitstate.com/tutorials/how-to-write-parallel-multitasking-applications-for-esp32-with-freertos-arduino
*/
//================================================================================//

SemaphoreHandle_t countingSem = NULL;  // counting semaphore
SemaphoreHandle_t semFull = NULL;  // semaphore indicating that the counting semaphore is full

//================================================================================//

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode (LED_BUILTIN, OUTPUT);

  Serial.begin (115200);

  semFull = xSemaphoreCreateBinary();  // Create a binary semaphore
  countingSem = xSemaphoreCreateCounting (3, 3);  // create a semaphore object

  if (countingSem != NULL) {
    Serial.println ("Semaphore created successfully");
  }

  xTaskCreatePinnedToCore (
    task1,     // Function to implement the task
    "task1",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    10,        // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );

  xTaskCreatePinnedToCore (
    task2,     // Function to implement the task
    "task2",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    10,        // Priority of the task
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

// this will acquire two counting semaphores and wait for a signal from task2
void task1 (void *pvParameters) {
  while(1) {
    if (uxSemaphoreGetCount (countingSem) == 3) { // check if the counting semaphore is free
      if (xSemaphoreTake (countingSem, portMAX_DELAY) && xSemaphoreTake (countingSem, portMAX_DELAY)) { // acquire two semaphores
        Serial.print ("Task 1: 2 semaphores acquired at ");
        Serial.println (xTaskGetTickCount());
        Serial.print ("Task 1: Semaphores left = ");
        Serial.println (uxSemaphoreGetCount (countingSem)); // print the number of semaphores left
        delay (1000);
      }
    }

    if (xSemaphoreTake (semFull, portMAX_DELAY)) {  // wait for signal from task 2
      Serial.println ("Task 1: Semaphore is full. Releasing 2 semaphores..");
      xSemaphoreGive (countingSem); // release the two semaphores
      xSemaphoreGive (countingSem);
      delay (1000);
    }
  }
}

//================================================================================//

// this task will acquire only semaphore
void task2 (void *pvParameters) {
  while (1) {
    if (uxSemaphoreGetCount (countingSem) == 1) {  // check when only 1 semaphore is left
      if (xSemaphoreTake (countingSem, portMAX_DELAY)) {  //try to acquire the semaphore
        Serial.println ("Task 2: Acquiring last semaphore..");
        Serial.print ("Task 2: Semaphore acquired at ");
        Serial.println (xTaskGetTickCount());
        Serial.print ("Task 2: Semaphores left = ");
        Serial.println (uxSemaphoreGetCount (countingSem));
        delay (1000);
        xSemaphoreGive (semFull); // signal that the counting semaphore is full
        delay (1000);
        Serial.print ("Task 2: Releasing 1 semaphore at ");
        Serial.println (xTaskGetTickCount());
        xSemaphoreGive (countingSem); // release the semaphore
      }
    }
  }
}

//================================================================================//
