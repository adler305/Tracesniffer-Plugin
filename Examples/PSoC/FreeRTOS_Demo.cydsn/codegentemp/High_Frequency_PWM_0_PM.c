/*******************************************************************************
* File Name: High_Frequency_PWM_0_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "High_Frequency_PWM_0.h"

static High_Frequency_PWM_0_backupStruct High_Frequency_PWM_0_backup;


/*******************************************************************************
* Function Name: High_Frequency_PWM_0_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  High_Frequency_PWM_0_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void High_Frequency_PWM_0_SaveConfig(void) 
{

    #if(!High_Frequency_PWM_0_UsingFixedFunction)
        #if(!High_Frequency_PWM_0_PWMModeIsCenterAligned)
            High_Frequency_PWM_0_backup.PWMPeriod = High_Frequency_PWM_0_ReadPeriod();
        #endif /* (!High_Frequency_PWM_0_PWMModeIsCenterAligned) */
        High_Frequency_PWM_0_backup.PWMUdb = High_Frequency_PWM_0_ReadCounter();
        #if (High_Frequency_PWM_0_UseStatus)
            High_Frequency_PWM_0_backup.InterruptMaskValue = High_Frequency_PWM_0_STATUS_MASK;
        #endif /* (High_Frequency_PWM_0_UseStatus) */

        #if(High_Frequency_PWM_0_DeadBandMode == High_Frequency_PWM_0__B_PWM__DBM_256_CLOCKS || \
            High_Frequency_PWM_0_DeadBandMode == High_Frequency_PWM_0__B_PWM__DBM_2_4_CLOCKS)
            High_Frequency_PWM_0_backup.PWMdeadBandValue = High_Frequency_PWM_0_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(High_Frequency_PWM_0_KillModeMinTime)
             High_Frequency_PWM_0_backup.PWMKillCounterPeriod = High_Frequency_PWM_0_ReadKillTime();
        #endif /* (High_Frequency_PWM_0_KillModeMinTime) */

        #if(High_Frequency_PWM_0_UseControl)
            High_Frequency_PWM_0_backup.PWMControlRegister = High_Frequency_PWM_0_ReadControlRegister();
        #endif /* (High_Frequency_PWM_0_UseControl) */
    #endif  /* (!High_Frequency_PWM_0_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: High_Frequency_PWM_0_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  High_Frequency_PWM_0_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void High_Frequency_PWM_0_RestoreConfig(void) 
{
        #if(!High_Frequency_PWM_0_UsingFixedFunction)
            #if(!High_Frequency_PWM_0_PWMModeIsCenterAligned)
                High_Frequency_PWM_0_WritePeriod(High_Frequency_PWM_0_backup.PWMPeriod);
            #endif /* (!High_Frequency_PWM_0_PWMModeIsCenterAligned) */

            High_Frequency_PWM_0_WriteCounter(High_Frequency_PWM_0_backup.PWMUdb);

            #if (High_Frequency_PWM_0_UseStatus)
                High_Frequency_PWM_0_STATUS_MASK = High_Frequency_PWM_0_backup.InterruptMaskValue;
            #endif /* (High_Frequency_PWM_0_UseStatus) */

            #if(High_Frequency_PWM_0_DeadBandMode == High_Frequency_PWM_0__B_PWM__DBM_256_CLOCKS || \
                High_Frequency_PWM_0_DeadBandMode == High_Frequency_PWM_0__B_PWM__DBM_2_4_CLOCKS)
                High_Frequency_PWM_0_WriteDeadTime(High_Frequency_PWM_0_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(High_Frequency_PWM_0_KillModeMinTime)
                High_Frequency_PWM_0_WriteKillTime(High_Frequency_PWM_0_backup.PWMKillCounterPeriod);
            #endif /* (High_Frequency_PWM_0_KillModeMinTime) */

            #if(High_Frequency_PWM_0_UseControl)
                High_Frequency_PWM_0_WriteControlRegister(High_Frequency_PWM_0_backup.PWMControlRegister);
            #endif /* (High_Frequency_PWM_0_UseControl) */
        #endif  /* (!High_Frequency_PWM_0_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: High_Frequency_PWM_0_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  High_Frequency_PWM_0_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void High_Frequency_PWM_0_Sleep(void) 
{
    #if(High_Frequency_PWM_0_UseControl)
        if(High_Frequency_PWM_0_CTRL_ENABLE == (High_Frequency_PWM_0_CONTROL & High_Frequency_PWM_0_CTRL_ENABLE))
        {
            /*Component is enabled */
            High_Frequency_PWM_0_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            High_Frequency_PWM_0_backup.PWMEnableState = 0u;
        }
    #endif /* (High_Frequency_PWM_0_UseControl) */

    /* Stop component */
    High_Frequency_PWM_0_Stop();

    /* Save registers configuration */
    High_Frequency_PWM_0_SaveConfig();
}


/*******************************************************************************
* Function Name: High_Frequency_PWM_0_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  High_Frequency_PWM_0_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void High_Frequency_PWM_0_Wakeup(void) 
{
     /* Restore registers values */
    High_Frequency_PWM_0_RestoreConfig();

    if(High_Frequency_PWM_0_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        High_Frequency_PWM_0_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
