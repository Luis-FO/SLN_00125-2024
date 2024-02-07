#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "task.h"

float temperatura = 25;
char flag = 0;
SemaphoreHandle_t mutex;    


float celsiousTofahrenheit(float celsius) {
    return (celsius * 9/5) + 32;
}

float fahrenheitTocelsius(float fahrenheit) {
    return (fahrenheit - 32) * 5.0 / 9.0;
}

void task1(void *pvParameters) {
    float temperatura_celsious;
    while (1) {

        xSemaphoreTake(mutex, portMAX_DELAY);

        if(flag == 1){
          temperatura_celsious = fahrenheitTocelsius(temperatura);
          temperatura = temperatura_celsious;
          flag = 0;
        }
        temperatura += 1.5;
        Serial.print("Temperatura em Celsius: ");
        Serial.println(temperatura);

        xSemaphoreGive(mutex);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void task2(void *pvParameters) {
    float temperatura_fahrenheit;
    while (1) {

        xSemaphoreTake(mutex, portMAX_DELAY);
        if(flag == 0){
          temperatura_fahrenheit = celsiousTofahrenheit(temperatura);
          temperatura = temperatura_fahrenheit;
          flag = 1;
        }
        
        Serial.print("Temperatura em Fahrenheit:");
        Serial.println(temperatura);
        xSemaphoreGive(mutex);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


void setup() {

    Serial.begin(115200);
    mutex = xSemaphoreCreateMutex();

    if (mutex == NULL) {
        Serial.print("Erro ao criar o mutex\n");
        return 1;
    }


    xTaskCreate(task1, "task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(task2, "task2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);


    vTaskStartScheduler();

}

void loop(){

}
