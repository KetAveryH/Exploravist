//================================================================================//
/*
  ESP32 Critical Section Example
  Read more at https://circuitstate.com/tutorials/how-to-write-parallel-multitasking-applications-for-esp32-with-freertos-arduino
*/
//================================================================================//

portMUX_TYPE taskMux = portMUX_INITIALIZER_UNLOCKED;  // critical section mutex

int counter = 0;  // A shared variable

//================================================================================//

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode (LED_BUILTIN, OUTPUT);

  Serial.begin (115200);

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

// this task will periodically lock the mutex, increment the counter by 1 and unlock the mutex
void task1 (void *pvParameters) {
  while(1) {
    Serial.print ("Task 1: Trying to increment the counter at ");
    Serial.println (xTaskGetTickCount());

    portENTER_CRITICAL (&taskMux);  // lock the mutex (busy waiting)
      counter = counter + 1;  // increment the counter
      Serial.print ("Task 1: Counter = ");
      Serial.println (counter);
    portEXIT_CRITICAL (&taskMux); // unlock the mutex
    
    delay (1000);
  }
}

//================================================================================//

// this task will periodically lock the mutex, increment the counter by 1000 and unlock the mutex
void task2 (void *pvParameters) {
  while (1) {
    Serial.print ("Task 2: Trying to increment the counter at ");
    Serial.println (xTaskGetTickCount());

    portENTER_CRITICAL (&taskMux);  // lock the mutex (busy waiting)
      counter = counter + 1000;
      Serial.print ("Task 2: Counter = ");
      Serial.println (counter);
    portEXIT_CRITICAL (&taskMux); // unlock the mutex

    delay (500);
  }
}

//================================================================================//
