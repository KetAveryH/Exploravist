#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include <Arduino.h>

int counter = 0;

//-----------------------------------------------------------------------------------------------------

void myTask(void *pvParam) 
{
    while(1)
    {
        counter += 1;
        printf("Hello Ket! In the Task!\n");
        char str[20]; // Ensure the array is large enough to hold the number and the null terminator.
        snprintf(str, sizeof(str), "%d", counter);
        printf("%s\n", str);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

//-----------------------------------------------------------------------------------------------------

void taskManager(void *pvParameters) {
    TaskHandle_t newTaskHandle = NULL;

    while (1) {
        // Check some conditions or wait for a signal
        // to create or delete tasks.

        if (touchRead(T14)>70000) {
            xTaskCreate(myTask, "myTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &newTaskHandle);
            // Optionally store the handle for later reference
        }

        if (counter == 10) {
            // Ensure the task is not NULL and then delete it
            if (newTaskHandle != NULL) {
                
                vTaskDelete(newTaskHandle);
                newTaskHandle = NULL; // Avoid dangling pointer
                printf("myTask deleted");
            }
        }

        // Delay to prevent this task from consuming all CPU time
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

//-----------------------------------------------------------------------------------------------------

void app_main(void)
{
    TaskHandle_t managerHandle = NULL;
    xTaskCreate(taskManager, "taskManager", 8192, NULL, 1, &managerHandle);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
