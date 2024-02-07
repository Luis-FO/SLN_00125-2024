#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

float temperatura = 25.0;  
SemaphoreHandle_t mutex;    


float celsiousTofahrenheit(float celsius) {
    return (celsius * 9/5) + 32;
}


void task1(void *pvParameters) {
    while (1) {

        xSemaphoreTake(mutex, portMAX_DELAY);

        temperatura += 1.5;

        printf("Tarefa 1: Temperatura em Celsius: %.2f\n", temperatura);

        xSemaphoreGive(mutex);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void task2(void *pvParameters) {
    while (1) {

        xSemaphoreTake(mutex, portMAX_DELAY);

        float temperatura_fahrenheit = celsiousTofahrenheit(temperatura);

        printf("Tarefa 2: Temperatura em Fahrenheit: %.2f\n", temperatura_fahrenheit);

        xSemaphoreGive(mutex);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main() {

    mutex = xSemaphoreCreateMutex();

    if (mutex == NULL) {
        printf("Erro ao criar o mutex\n");
        return 1;
    }


    xTaskCreate(task1, "task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(task2, "task2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);


    vTaskStartScheduler();

    return 0;
}
