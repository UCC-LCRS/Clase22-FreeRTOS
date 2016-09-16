/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "bsp.h"

/* Standard includes */
#include <stdio.h>                          // prototype declarations for I/O functions
#include <string.h>

/* Scheduler includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

TaskHandle_t tareaB;
SemaphoreHandle_t xSemaphore;

void prvTaskA(void* pvParameters) {
	(void) pvParameters;                    // Just to stop compiler warnings.
	char msg[] = "Hola desde la Tarea A\n";
	for (;;) {
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
		for (int i = 0; i < strlen(msg); i++) {
			TransmitData(&msg[i], 1);
			vTaskDelay(1);

		}
		xSemaphoreGive(xSemaphore);
		vTaskDelay(1);
	}
}

void prvTaskB(void* pvParameters) {
	(void) pvParameters;                    // Just to stop compiler warnings.
	char msg[] = "Hola desde la Tarea B\n";
	for (;;) {
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
		for (int i = 0; i < strlen(msg); i++) {
			TransmitData(&msg[i], 1);
			vTaskDelay(1);
		}
		xSemaphoreGive(xSemaphore);
		vTaskDelay(1);
	}
}

int main(void) {
// Init BSP
	BSP_Init();

	xTaskCreate(prvTaskA, (signed char * ) "TaskA", configMINIMAL_STACK_SIZE,
			NULL, tskIDLE_PRIORITY, ( xTaskHandle * ) NULL);
	xTaskCreate(prvTaskB, (signed char * ) "TaskB", configMINIMAL_STACK_SIZE,
			NULL, tskIDLE_PRIORITY, &tareaB);

	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphore);

	vTaskStartScheduler();

	//should never get here
	printf("ERORR: vTaskStartScheduler returned!");
	for (;;)
		;
}

void APP_1ms() {

}

