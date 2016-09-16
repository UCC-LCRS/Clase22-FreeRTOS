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


/* Scheduler includes */
#include "FreeRTOS.h"
#include "task.h"

void prvTaskA (void* pvParameters)
{
    (void) pvParameters;                    // Just to stop compiler warnings.

    for (;;) {
    	led_setBright(LED_ROJO,0);
        vTaskDelay(500);
    	led_setBright(LED_ROJO,100);
        vTaskDelay(500);
    }
}

void prvTaskB (void* pvParameters)
{
    (void) pvParameters;                    // Just to stop compiler warnings.

    for (;;) {
    	led_setBright(LED_VERDE,0);
        vTaskDelay(1000);
    	led_setBright(LED_VERDE,100);
        vTaskDelay(1000);
    }
}

int main (void)
{
// Init BSP
BSP_Init();

    xTaskCreate( prvTaskA, ( signed char * ) "TaskA", configMINIMAL_STACK_SIZE, NULL,
        tskIDLE_PRIORITY, ( xTaskHandle * ) NULL );
    xTaskCreate( prvTaskB, ( signed char * ) "TaskB", configMINIMAL_STACK_SIZE, NULL,
        tskIDLE_PRIORITY, ( xTaskHandle * ) NULL );

    vTaskStartScheduler();

   //should never get here
   printf("ERORR: vTaskStartScheduler returned!");
   for (;;);
}

void APP_1ms(){


}
