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
#include "queue.h"

TaskHandle_t tareaB;
SemaphoreHandle_t xSemaphore;
QueueHandle_t xQueue1;

void prvTaskA(void* pvParameters) {
	(void) pvParameters;                    // Just to stop compiler warnings.
	char msg = 'A';
	for (;;) {
		xQueueSend(xQueue1, (void * ) &msg, 0);
		xQueueSend(xQueue1, (void * ) &msg, 0);
		xQueueSend(xQueue1, (void * ) &msg, 0);
		vTaskDelay(1000);
	}
}

void prvTaskB(void* pvParameters) {
	(void) pvParameters;                    // Just to stop compiler warnings.
	char msg = 'B';
	for (;;) {
		xQueueSend(xQueue1, (void * ) &msg, 0);
		xQueueSend(xQueue1, (void * ) &msg, 0);
		xQueueSend(xQueue1, (void * ) &msg, 0);
		vTaskDelay(100);
	}
}

void prvTaskC(void* pvParameters) {
	(void) pvParameters;                    // Just to stop compiler warnings.
	char msg;
	char buffer[100];
	int size;
	for (;;) {
		xQueueReceive( xQueue1,(void * ) &( msg ), portMAX_DELAY );
		size = sprintf(buffer, "Recibi mensaje %c\n",msg);
		TransmitData(buffer, size);
	}
}

int main(void) {
// Init BSP
	BSP_Init();

	xTaskCreate(prvTaskA, (signed char * ) "TaskA", configMINIMAL_STACK_SIZE,
			NULL, tskIDLE_PRIORITY, ( xTaskHandle * ) NULL);
	xTaskCreate(prvTaskB, (signed char * ) "TaskB", configMINIMAL_STACK_SIZE,
			NULL, tskIDLE_PRIORITY, &tareaB);
	xTaskCreate(prvTaskC, (signed char * ) "TaskC", configMINIMAL_STACK_SIZE,
			NULL, tskIDLE_PRIORITY, ( xTaskHandle * ) NULL);

	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphore);

	xQueue1 = xQueueCreate(31, sizeof(char));

	vTaskStartScheduler();

	//should never get here
	printf("ERORR: vTaskStartScheduler returned!");
	for (;;)
		;
}

void APP_1ms() {

}

