/*
    FreeRTOS V8.2.1 - Copyright (C) 2015 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

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

/* ************************************************************************ */
/* PSoC Extensions for FreeRTOS                                             */
/* Author: Chuck Erhardt (chuck@e2forlife.com)                              */
/* these extensions are to wrap the FreeRTOS M3 implementation with the     */
/* standard PSoC Creator API, auto-assign the ISRs required, and start      */
/* the scheduler without having to write that code every time. Also the     */
/* creator component allows for OS configuration from the block diagram     */
/* editor like other PSoC Creator components                                */
/* ************************************************************************ */


/* Include FreeRTOS APIs and defines */
#include <FreeRTOS.h>
#include <FreeRTOS_task.h>
#include <FreeRTOS_queue.h>
#include <FreeRTOS_event_groups.h>

/* Declaration of NVIC base vector for FreeRTOS exception handling */
#define CORTEX_INTERRUPT_BASE          (16)

/* Declarations of the exception handlers for FreeRTOS */
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vPortSVCHandler(void);

#include <cytypes.h>
#include <cylib.h>

#if (CY_PSOC5)
	#include "core_cm3_psoc5.h"
#elif (CY_PSOC4)
	#include "core_cm0_psoc4.h"
#endif

uint8 `$INSTANCE_NAME`_initVar = 0;

/* ------------------------------------------------------------------------ */
void `$INSTANCE_NAME`_Init( void )
{
    /* Handler for Cortex Supervisor Call (SVC, formerly SWI) - address 11 */
    CyIntSetSysVector( CORTEX_INTERRUPT_BASE + SVCall_IRQn,
        (cyisraddress)vPortSVCHandler );
    
    /* Handler for Cortex PendSV Call - address 14 */
	CyIntSetSysVector( CORTEX_INTERRUPT_BASE + PendSV_IRQn,
        (cyisraddress)xPortPendSVHandler );    
    
    /* Handler for Cortex SYSTICK - address 15 */
	CyIntSetSysVector( CORTEX_INTERRUPT_BASE + SysTick_IRQn,
        (cyisraddress)xPortSysTickHandler );
	
	`$INSTANCE_NAME`_initVar = 1;
}
/* ------------------------------------------------------------------------ */
void `$INSTANCE_NAME`_Enable( void )
{
	/* start the scheduler so the tasks will start executing */
	vTaskStartScheduler();	
}
/* ------------------------------------------------------------------------ */
void `$INSTANCE_NAME`_Start( void )
{
	if (`$INSTANCE_NAME`_initVar == 0) {
		`$INSTANCE_NAME`_Init();
	}
	`$INSTANCE_NAME`_Enable();
	
	/*
	 * After the scheduler starts in Enable(), the code should never get to
	 * this location.
	 */
	for (;;);
}

/* ========================================================================= */

/*
 * Function:	vApplicationStackOverflowHook
 *
 * Called if a task exceeds its alloted stack.
 *
 * Requires configCHECK_FOR_STACK_OVERFLOW to be set in FreeRTOSConfig.h.
 *
 * Globals:		None
 *
 * Parameters:	Task handle and name
 *
 * Return:		Never returns - this is a fatal error condition
 */
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	/* The stack space has been execeeded for a task */
	taskDISABLE_INTERRUPTS();
	while( 1 )
    {
        /* Do nothing - this is a placeholder for a breakpoint */
    }
}


#if (`$USE_MALLOC_FAILED_HOOK` == 1)
/*
 * Function:	vApplicationMallocFailedHook
 *
 * Called if a malloc from the FreeRTOS heap fails. This may require more
 * heap (configTOTAL_HEAP_SIZE in FreeRTOSVConfig.h) or a different heap
 * algorithm (heap_?.c in Source\portable\MemMang).
 *
 * Requires configUSE_MALLOC_FAILED_HOOK to be set in FreeRTOSConfig.h.
 *
 * Globals:		None
 *
 * Parameters:	Task handle and name
 *
 * Return:		Never returns - this is a fatal error condition
 */
void vApplicationMallocFailedHook( void )
{
	/* The heap space has been execeeded. */
	taskDISABLE_INTERRUPTS();
	while( 1 )
    {
        /* Do nothing - this is a placeholder for a breakpoint */
    }
}
#endif

/* [] END OF FILE */
