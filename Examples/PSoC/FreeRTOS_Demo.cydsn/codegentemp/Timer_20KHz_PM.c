/*******************************************************************************
* File Name: Timer_20KHz_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_20KHz.h"

static Timer_20KHz_backupStruct Timer_20KHz_backup;


/*******************************************************************************
* Function Name: Timer_20KHz_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_20KHz_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_20KHz_SaveConfig(void) 
{
    #if (!Timer_20KHz_UsingFixedFunction)
        Timer_20KHz_backup.TimerUdb = Timer_20KHz_ReadCounter();
        Timer_20KHz_backup.InterruptMaskValue = Timer_20KHz_STATUS_MASK;
        #if (Timer_20KHz_UsingHWCaptureCounter)
            Timer_20KHz_backup.TimerCaptureCounter = Timer_20KHz_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_20KHz_UDB_CONTROL_REG_REMOVED)
            Timer_20KHz_backup.TimerControlRegister = Timer_20KHz_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_20KHz_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_20KHz_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_20KHz_RestoreConfig(void) 
{   
    #if (!Timer_20KHz_UsingFixedFunction)

        Timer_20KHz_WriteCounter(Timer_20KHz_backup.TimerUdb);
        Timer_20KHz_STATUS_MASK =Timer_20KHz_backup.InterruptMaskValue;
        #if (Timer_20KHz_UsingHWCaptureCounter)
            Timer_20KHz_SetCaptureCount(Timer_20KHz_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_20KHz_UDB_CONTROL_REG_REMOVED)
            Timer_20KHz_WriteControlRegister(Timer_20KHz_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_20KHz_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_20KHz_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_20KHz_Sleep(void) 
{
    #if(!Timer_20KHz_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_20KHz_CTRL_ENABLE == (Timer_20KHz_CONTROL & Timer_20KHz_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_20KHz_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_20KHz_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_20KHz_Stop();
    Timer_20KHz_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_20KHz_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_20KHz_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_20KHz_Wakeup(void) 
{
    Timer_20KHz_RestoreConfig();
    #if(!Timer_20KHz_UDB_CONTROL_REG_REMOVED)
        if(Timer_20KHz_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_20KHz_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
