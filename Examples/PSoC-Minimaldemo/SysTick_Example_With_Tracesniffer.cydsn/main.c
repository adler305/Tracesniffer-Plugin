/*******************************************************************************
* File: main.c
*
* Version: 1.0
*
* Description:
*  This example project demonstrates the basic operation of the System Tick
*  Timer: periodic LED triggering - every second and minute.
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>
#include <stdio.h>
#include "sniffImport.h"

#define TIME_MIN_IN_HR      (60u)
#define TIME_SEC_IN_MIN     (60u)
#define TIME_MS_IN_SEC      (1000u)

#if(CY_PSOC4)
    #define LIGHT_OFF                       (1u)
    #define LIGHT_ON                        (0u)
#else
    #define LIGHT_OFF                       (0u)
    #define LIGHT_ON                        (1u)
#endif /* (CY_PSOC4) */

/* Global Variables */
uint32 msCount;
uint32 secCount;
uint32 minCount;
volatile uint32 tickStatus;

/* Function Prototypes */
void SysTickISRCallback(void);


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Starts the SysTick timer and sets the callback function that will be called
*  on SysTick interrupt. Updates timing variables at one millisecond rate and
*  prints the system time to the UART once every second in the main loop.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
int main()
{
    char time[16u];
    uint32 i;

    /* Initialize global variables. */
    tickStatus = 0u;
    msCount = TIME_MS_IN_SEC - 1u;
    secCount = 0u;
    minCount = 0u;
    TraceSnifferUART_Start();
    initialiseTraceSniffer();
    /* Enable global interrupts. */
    CyGlobalIntEnable;

    /* Set initial state (off) for LED */
    LED_Min_Write(LIGHT_OFF);
    LED_Sec_Write(LIGHT_OFF);

    /* Configure the SysTick timer to generate interrupt every 1 ms
    * and start its operation. Call the function before assigning the
    * callbacks as it calls CySysTickInit() during first run that 
    * re-initializes the callback addresses to the NULL pointers.
    */
    CySysTickStart();
    
    //TraceSnifferUART_PutString("Test");
    /* Find unused callback slot and assign the callback. */
    for (i = 0u; i < CY_SYS_SYST_NUM_OF_CALLBACKS; ++i)
    {
        if (CySysTickGetCallback(i) == NULL)
        {
            /* Set callback */
            CySysTickSetCallback(i, SysTickISRCallback);
            break;
        }
    }

    for(;;)
    {
        /* Tick status fires only once every millisecond. */
        if(tickStatus != 0u)
        {
            /* Reset tick status. */
            tickStatus = 0u;

            if(0u == msCount)
            {
                /* Increment seconds. */
                ++secCount;
                traceCUSTOM_MARKER_3(minCount,secCount);
                /* Toggle blue LED. */
                LED_Sec_Write(~LED_Sec_Read());
            }

            if(TIME_SEC_IN_MIN == secCount)
            {
                /* Reset seconds. */
                secCount = 0u;

                /* Increment minutes. */
                ++minCount;

                /* Toggle red LED. */
                LED_Min_Write(~LED_Min_Read());
            }

            if(TIME_MIN_IN_HR == minCount)
            {
                /* Reset minutes. */
                minCount = 0u;
            }

            /* Print system time to UART every second */
            if(0u == msCount)
            {
                sprintf(time, "\r%02lu:%02lu", minCount, secCount);
                UART_PutString(time);
            }
        }
    }
}


/*******************************************************************************
* Function Name: SysTickISRCallback
********************************************************************************
*
* Summary:
*  This API is called from SysTick timer interrupt handler to update the
*  millisecond counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SysTickISRCallback(void)
{
    traceTASK_INCREMENT_TICK();
    traceCUSTOM_MARKER_1();
    tickStatus = 1u;
    CyDelayUs(50);
    //TraceSnifferUART_PutChar(readOutSysTimerHigh());
    //TraceSnifferUART_PutChar(readOutSysTimerLow());
    //TraceSnifferUART_PutChar('\n');
    /* Counts the number of milliseconds in one second */
    traceCUSTOM_MARKER_2();
    if(msCount != 0u)
    {
        --msCount;
    }
    else
    {
        /* Counts from 999 down to 0 */
        msCount = TIME_MS_IN_SEC - 1u;
    }
    
}


/* [] END OF FILE */
