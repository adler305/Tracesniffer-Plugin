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

/*
* Creates all the demo application tasks, then starts the scheduler.  The WEB
* documentation provides more details of the demo application tasks.
*
* Main. c also creates a task called "Check".  This only executes every three
* seconds but has the highest priority so is guaranteed to get processor time.
* Its main function is to check that all the other tasks are still operational.
* Each task that does not flash an LED maintains a unique count that is
* incremented each time the task successfully completes its function.  Should
* any error occur within such a task the count is permanently halted.  The
* check task inspects the count of each task to ensure it has changed since
* the last time the check task executed.  If all the count variables have
* changed all the tasks are still executing error free, and the check task
* toggles an LED.  Should any task contain an error at any time the LED toggle
* will stop.
*
* The LED flash and communications test tasks do not maintain a count.
*/

/*
Changes from V1.2.0

+ Changed the baud rate for the serial test from 19200 to 57600.

Changes from V1.2.3

+ The integer and comtest tasks are now used when the cooperative scheduler
is being used.  Previously they were only used with the preemptive
scheduler.

Changes from V1.2.5

+ Set the baud rate to 38400.  This has a smaller error percentage with an
8MHz clock (according to the manual).

Changes from V2.0.0

+ Delay periods are now specified using variables and constants of
TickType_t rather than unsigned long.

Changes from V2.6.1

+ The IAR and WinAVR AVR ports are now maintained separately.

Changes from V4.0.5

+ Modified to demonstrate the use of co-routines.

*/
#include <stdlib.h>
#include <string.h>
#define F_CPU 16000000
#define BAUDRATE 1000000//9600
#define UBRR_VALUE_NORMAL_SPEED F_CPU/16/BAUDRATE-1 
#define UBRR_VALUE_DOUBLE_SPEED F_CPU/8/BAUDRATE-1 
#ifdef GCC_MEGA_AVR
/* EEPROM routines used only with the WinAVR compiler. */
#include <avr/eeprom.h>
#endif

/* Scheduler include files. */
#include <FreeRTOS.h>
#include <task.h>
#include <croutine.h>
#include <avr/interrupt.h>
#include <queue.h>
#include <semphr.h>
#include <uart.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>



/*Pinbelegung:
PC0 CLK/E
PC1 RS
PC2	D4
PC3 D5
PC4 D6
PC5 D7
PB1 RW*/


/* Priority definitions for most of the tasks in the demo application.  Some
tasks just use the idle priority. */
#define mainLED_TASK_PRIORITY           ( tskIDLE_PRIORITY )
#define basicPriority					( 2 )
#define thirdLED_TASK_PRIORITY           ( tskIDLE_PRIORITY)

//Globale Deklarationen


TaskHandle_t lcd_task_handle;


void blink_task() {
	DDRB =0xff;	
	while (1) {
		
		PORTB ^=0xff;//(1<<PORTB1);
		vTaskDelay(100);
	}
}

void blink2_task() {
	DDRC =0xff;
	
	while (1) {
		
		PORTC ^=0xff;//(1<<PORTB1);
		vTaskDelay(1000);
	}
}

int main( void )
{	

	sei();
	uart_init(UBRR_VALUE_NORMAL_SPEED);
	initialiseTraceSniffer();

	xTaskCreate((pdTASK_CODE)blink_task, "blink", configMINIMAL_STACK_SIZE, 0,
	basicPriority, &lcd_task_handle);
	
	xTaskCreate((pdTASK_CODE)blink2_task, "blink2", configMINIMAL_STACK_SIZE, 0,
	basicPriority, &lcd_task_handle);
 
	vTaskStartScheduler();
	while(1);

}
