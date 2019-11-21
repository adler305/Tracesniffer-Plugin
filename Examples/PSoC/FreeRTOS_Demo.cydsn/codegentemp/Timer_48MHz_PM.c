/*******************************************************************************
* File Name: Timer_48MHz_PM.c
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

#include "Timer_48MHz.h"

static Timer_48MHz_backupStruct Timer_48MHz_backup;


/*******************************************************************************
* Function Name: Timer_48MHz_SaveConfig
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
*  Timer_48MHz_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_48MHz_SaveConfig(void) 
{
    #if (!Timer_48MHz_UsingFixedFunction)
        Timer_48MHz_backup.TimerUdb = Timer_48MHz_ReadCounter();
        Timer_48MHz_backup.InterruptMaskValue = Timer_48MHz_STATUS_MASK;
        #if (Timer_48MHz_UsingHWCaptureCounter)
            Timer_48MHz_backup.TimerCaptureCounter = Timer_48MHz_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_48MHz_UDB_CONTROL_REG_REMOVED)
            Timer_48MHz_backup.TimerControlRegister = Timer_48MHz_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_48MHz_RestoreConfig
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
*  Timer_48MHz_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_48MHz_RestoreConfig(void) 
{   
    #if (!Timer_48MHz_UsingFixedFunction)

        Timer_48MHz_WriteCounter(Timer_48MHz_backup.TimerUdb);
        Timer_48MHz_STATUS_MASK =Timer_48MHz_backup.InterruptMaskValue;
        #if (Timer_48MHz_UsingHWCaptureCounter)
            Timer_48MHz_SetCaptureCount(Timer_48MHz_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_48MHz_UDB_CONTROL_REG_REMOVED)
            Timer_48MHz_WriteControlRegister(Timer_48MHz_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_48MHz_Sleep
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
*  Timer_48MHz_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_48MHz_Sleep(void) 
{
    #if(!Timer_48MHz_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_48MHz_CTRL_ENABLE == (Timer_48MHz_CONTROL & Timer_48MHz_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_48MHz_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_48MHz_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_48MHz_Stop();
    Timer_48MHz_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_48MHz_Wakeup
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
*  Timer_48MHz_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_48MHz_Wakeup(void) 
{
    Timer_48MHz_RestoreConfig();
    #if(!Timer_48MHz_UDB_CONTROL_REG_REMOVED)
        if(Timer_48MHz_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_48MHz_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
