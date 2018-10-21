/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/**
 * This version of flash .c is for use on systems that have limited stack space
 * and no display facilities.  The complete version can be found in the 
 * Demo/Common/Full directory.
 * 
 * Three tasks are created, each of which flash an LED at a different rate.  The first 
 * LED flashes every 200ms, the second every 400ms, the third every 600ms.
 *
 * The LED flash tasks provide instant visual feedback.  They show that the scheduler 
 * is still operational.
 *
 */


#include <stdlib.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Demo program include files. */
#include "partest.h"
#include "USBSerial.h"

#define USBSerialSTACK_SIZE		configMINIMAL_STACK_SIZE
const TickType_t xDelay = 100 / portTICK_PERIOD_MS;
const TickType_t mDelay = 5000 / portTICK_PERIOD_MS;
    
/* The task that is created three times. */
static portTASK_FUNCTION_PROTO( vUSBSerialTask, pvParameters );

SemaphoreHandle_t USBMutex;

/*-----------------------------------------------------------*/

void usbserial_putString(const char msg[])
{
    if(0 == USBUART_GetConfiguration()) return;
    xSemaphoreTake(USBMutex,portMAX_DELAY);
    while(0 == USBUART_CDCIsReady()) vTaskDelay(xDelay);
    USBUART_PutString(msg);
    xSemaphoreGive(USBMutex);
}

void vStartUSBSerialTasks( UBaseType_t uxPriority )
{
    /*Setup the mutex to control port access*/
    USBMutex = xSemaphoreCreateMutex();
	/* Spawn the task. */
	xTaskCreate( vUSBSerialTask, "USBSerial", USBSerialSTACK_SIZE, NULL, uxPriority, ( TaskHandle_t * ) NULL );

}
/*-----------------------------------------------------------*/

static portTASK_FUNCTION( vUSBSerialTask, pvParameters )
{
   	/* The parameters are not used. */
	( void ) pvParameters;

    /* Start the USB_UART */
    /* Start USBFS operation with 5-V operation. */
    USBUART_Start(0, USBUART_5V_OPERATION);

    
	for(;;)
	{
        /* Host can send double SET_INTERFACE request. */
        if (0u != USBUART_IsConfigurationChanged())
        {
            /* Initialize IN endpoints when device is configured. */
            if (0u != USBUART_GetConfiguration())
            {
                /* Enumeration is done, enable OUT endpoint to receive data 
                 * from host. */
                USBUART_CDC_Init();
            }
        }
        
        if(0 != USBUART_GetConfiguration())
        {
            /* Get and process inputs here */
            vTaskDelay(mDelay);
        }
        vTaskDelay(xDelay);
	}
} /*lint !e715 !e818 !e830 Function definition must be standard for task creation. */

