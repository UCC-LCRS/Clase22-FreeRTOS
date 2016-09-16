/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
			
/* Standard includes */
#include <stdio.h>                          // prototype declarations for I/O functions


/* Scheduler includes */
#include "FreeRTOS.h"
#include "task.h"

void prvTaskA (void* pvParameters)
{
    (void) pvParameters;                    // Just to stop compiler warnings.

    for (;;) {
        vTaskDelay(5000);
        printf("Task A\n");
        vTaskDelay(5000);
    }
}

void prvTaskB (void* pvParameters)
{
    (void) pvParameters;                    // Just to stop compiler warnings.

    for (;;) {
        printf("Task B\n");
        vTaskDelay(10000);
    }
}

int main (void)
{
// Init BSP


    xTaskCreate( prvTaskA, ( signed char * ) "TaskA", configMINIMAL_STACK_SIZE, NULL,
        tskIDLE_PRIORITY, ( xTaskHandle * ) NULL );
    xTaskCreate( prvTaskB, ( signed char * ) "TaskB", configMINIMAL_STACK_SIZE, NULL,
        tskIDLE_PRIORITY, ( xTaskHandle * ) NULL );

    vTaskStartScheduler();

   //should never get here
   printf("ERORR: vTaskStartScheduler returned!");
   for (;;);
}
