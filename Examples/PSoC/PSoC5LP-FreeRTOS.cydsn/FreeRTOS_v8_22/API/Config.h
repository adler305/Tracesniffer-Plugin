/*
    FreeRTOS V8.0.0 - Copyright (C) 2014 Real Time Engineers Ltd. 
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>! NOTE: The modification to the GPL is included to allow you to distribute
    >>! a combined work that includes FreeRTOS without being obliged to provide
    >>! the source code for proprietary components outside of the FreeRTOS
    >>! kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/
#include <cytypes.h>
#include <cyfitter.h>
    
/* This file supports PSoC 4 and PSoC 5LP - some settings need to be different */
    
#if CY_PSOC4
    
    /* Port-dependent settings - not user-editable */
    #define configCPU_CLOCK_HZ          ( ( unsigned long ) CYDEV_BCLK__SYSCLK__HZ )
        
    /* Application settings - user editable */
    #define configMAX_PRIORITIES		( `$MAX_PRIORITIES` )
    #define configTOTAL_HEAP_SIZE		( `$TOTAL_HEAP_SIZE` )
    
#elif CY_PSOC5
    
    /* Device settings - not user-editable */
    #define configCPU_CLOCK_HZ			( ( unsigned long ) BCLK__BUS_CLK__HZ )
        
    /* Application settings - user editable */
    #define configMAX_PRIORITIES        ( `$MAX_PRIORITIES` )
    #define configTOTAL_HEAP_SIZE		( `$TOTAL_HEAP_SIZE` ) 
    
#else
    
    #error "This FreeRTOSConfig.h file is for PSoC 4 and PSoC 5LP devices only"
    
#endif

#define configUSE_PREEMPTION			`$USE_PREEMPTION`
#define configUSE_IDLE_HOOK				`$USE_IDLE_HOOK`
#define configUSE_TICK_HOOK				`$USE_TICK_HOOK`
#define configTICK_RATE_HZ				( ( portTickType ) `$TICK_RATE_HZ` )
#define configMINIMAL_STACK_SIZE		( `$MINIMAL_STACK_SIZE` )
#define configMAX_TASK_NAME_LEN			( `$MAX_TASK_NAME_LEN` )
#define configUSE_TRACE_FACILITY		`$USE_TRACE_FACILITY`
#define configUSE_16_BIT_TICKS			`$USE_16_BIT_TICKS`
#define configIDLE_SHOULD_YIELD			`$IDLE_SHOULD_YIELD`
#define configUSE_MUTEXES				`$USE_MUTEXES`
#define configQUEUE_REGISTRY_SIZE		`$QUEUE_REGISTRY_SIZE`
#define configCHECK_FOR_STACK_OVERFLOW	`$CHECK_FOR_STACK_OVERFLOW`
#define configUSE_RECURSIVE_MUTEXES		`$USE_RECURSIVE_MUTEXES`
#define configUSE_MALLOC_FAILED_HOOK	`$USE_MALLOC_FAILED_HOOK`
#define configUSE_APPLICATION_TASK_TAG	`$USE_APPLICATION_TASK_TAG`
#define configUSE_COUNTING_SEMAPHORES	`$USE_COUNTING_SEMAPHORES`
#define configGENERATE_RUN_TIME_STATS	`$GENERATE_RUN_TIME_STATS`
#define configUSE_TIME_SLICING          `$USE_TIME_SLICING`

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 			`$USE_CO_ROUTINES`
#define configMAX_CO_ROUTINE_PRIORITIES ( `$MAX_CO_ROUTINE_PRIORITIES` )

/* Software timer definitions. */
#define configUSE_TIMERS				`$USE_TIMERS`
#define configTIMER_TASK_PRIORITY		`$TIMER_TASK_PRIORITY`
#define configTIMER_QUEUE_LENGTH		`$TIMER_QUEUE_LENGTH`
#define configTIMER_TASK_STACK_DEPTH	( 2 * configMINIMAL_STACK_SIZE )

/*
Configure interrupt priorities for Cypress PSoC devices.
This is explained here: http://www.freertos.org/a00110.html

Priorities are controlled by two macros:
- configKERNEL_INTERRUPT_PRIORITY determines the priority of the RTOS daemon task
- configMAX_API_CALL_INTERRUPT_PRIORITY dictates the priority of ISRs that make API calls

Notes:
1. Interrupts that do not call API functions should be >= configKERNEL_INTERRUPT_PRIORITY
   and will nest.
2. Interrupts that call API functions must have priority between KERNEL_INTERRUPT_PRIORITY
   and MAX_API_CALL_INTERRUPT_PRIORITY (inclusive).
3. Interrupts running above MAX_API_CALL_INTERRUPT_PRIORITY are never delayed by the OS.
*/
#if CY_PSOC4
    
    /*
    PSoC 4 __NVIC_PRIO_BITS = 2
    0 (high)    
    1
    2           MAX_API_CALL_INTERRUPT_PRIORITY 10xxxxxx (0xBF)
    3 (low)     KERNEL_INTERRUPT_PRIORITY       11xxxxxx (0xFF)
    */
    
    /* Put KERNEL_INTERRUPT_PRIORITY in top __NVIC_PRIO_BITS bits of CM0 register */
    #define configKERNEL_INTERRUPT_PRIORITY         (`$KERNEL_INTERRUPT_PRIORITY`)
    /* Put MAX_SYSCALL_INTERRUPT_PRIORITY in top __NVIC_PRIO_BITS bits of CM0 register */
    #define configMAX_SYSCALL_INTERRUPT_PRIORITY    (`$MAX_SYSCALL_INTERRUPT_PRIORITY`)
    
#elif CY_PSOC5
    
    /*
    PSoC 5LP __NVIC_PRIO_BITS = 3

    0 (high)
    1
    2
    3
    4
    5           MAX_API_CALL_INTERRUPT_PRIORITY 101xxxxx (0xBF)
    6
    7 (low)     KERNEL_INTERRUPT_PRIORITY       111xxxxx (0xFF)
    
    !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
    See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
    */
    
    /* Put KERNEL_INTERRUPT_PRIORITY in top __NVIC_PRIO_BITS bits of CM3 register */
    #define configKERNEL_INTERRUPT_PRIORITY         (`$KERNEL_INTERRUPT_PRIORITY`)
    /* Put MAX_SYSCALL_INTERRUPT_PRIORITY in top __NVIC_PRIO_BITS bits of CM3 register */
    #define configMAX_SYSCALL_INTERRUPT_PRIORITY    (`$MAX_SYSCALL_INTERRUPT_PRIORITY`)

#else
    
    #error "This FreeRTOS_Config.h file is for PSoC 4 and PSoC 5LP devices only"
    
#endif

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		        `$vTaskPrioritySet`
#define INCLUDE_uxTaskPriorityGet		        `$uxTaskPriorityGet`
#define INCLUDE_vTaskDelete				        `$vTaskDelete`
#define INCLUDE_vTaskCleanUpResources	        `$vTaskCleanUpResources`
#define INCLUDE_vTaskSuspend			        `$vTaskSuspend`
#define INCLUDE_vTaskDelayUntil			        `$vTaskDelayUntil`
#define INCLUDE_vTaskDelay				        `$vTaskDelay`
#define INCLUDE_uxTaskGetStackHighWaterMark	    `$uxTaskGetStackHighWaterMark`
#define INCLUDE_xTimerPendFunctionCallFromISR   `$xTimerPendFunctionCallFromISR`
#define INCLUDE_xEventGroupSetBitFromISR        `$xEventGroupSetBitFromISR`
#define INCLUDE_xTimerPendFunctionCall          `$xTimerPendFunctionCall`

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names - or at least those used in the unmodified vector table. */
#define vPortSVCHandler SVCall_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
