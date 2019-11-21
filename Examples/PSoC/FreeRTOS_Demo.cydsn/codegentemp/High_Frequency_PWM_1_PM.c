/*******************************************************************************
* File Name: High_Frequency_PWM_1_PM.c
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

#include "High_Frequency_PWM_1.h"

static High_Frequency_PWM_1_backupStruct High_Frequency_PWM_1_backup;


/*******************************************************************************
* Function Name: High_Frequency_PWM_1_SaveConfig
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
*  High_Frequency_PWM_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void High_Frequency_PWM_1_SaveConfig(void) 
{

    #if(!High_Frequency_PWM_1_UsingFixedFunction)
        #if(!High_Frequency_PWM_1_PWMModeIsCenterAligned)
            High_Frequency_PWM_1_backup.PWMPeriod = High_Frequency_PWM_1_ReadPeriod();
        #endif /* (!High_Frequency_PWM_1_PWMModeIsCenterAligned) */
        High_Frequency_PWM_1_backup.PWMUdb = High_Frequency_PWM_1_ReadCounter();
        #if (High_Frequency_PWM_1_UseStatus)
            High_Frequency_PWM_1_backup.InterruptMaskValue = High_Frequency_PWM_1_STATUS_MASK;
        #endif /* (High_Frequency_PWM_1_UseStatus) */

        #if(High_Frequency_PWM_1_DeadBandMode == High_Frequency_PWM_1__B_PWM__DBM_256_CLOCKS || \
            High_Frequency_PWM_1_DeadBandMode == High_Frequency_PWM_1__B_PWM__DBM_2_4_CLOCKS)
            High_Frequency_PWM_1_backup.PWMdeadBandValue = High_Frequency_PWM_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(High_Frequency_PWM_1_KillModeMinTime)
             High_Frequency_PWM_1_backup.PWMKillCounterPeriod = High_Frequency_PWM_1_ReadKillTime();
        #endif /* (High_Frequency_PWM_1_KillModeMinTime) */

        #if(High_Frequency_PWM_1_UseControl)
            High_Frequency_PWM_1_backup.PWMControlRegister = High_Frequency_PWM_1_ReadControlRegister();
        #endif /* (High_Frequency_PWM_1_UseControl) */
    #endif  /* (!High_Frequency_PWM_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: High_Frequency_PWM_1_RestoreConfig
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
*  High_Frequency_PWM_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void High_Frequency_PWM_1_RestoreConfig(void) 
{
        #if(!High_Frequency_PWM_1_UsingFixedFunction)
            #if(!High_Frequency_PWM_1_PWMModeIsCenterAligned)
                High_Frequency_PWM_1_WritePeriod(High_Frequency_PWM_1_backup.PWMPeriod);
            #endif /* (!High_Frequency_PWM_1_PWMModeIsCenterAligned) */

            High_Frequency_PWM_1_WriteCounter(High_Frequency_PWM_1_backup.PWMUdb);

            #if (High_Frequency_PWM_1_UseStatus)
                High_Frequency_PWM_1_STATUS_MASK = High_Frequency_PWM_1_backup.InterruptMaskValue;
            #endif /* (High_Frequency_PWM_1_UseStatus) */

            #if(High_Frequency_PWM_1_DeadBandMode == High_Frequency_PWM_1__B_PWM__DBM_256_CLOCKS || \
                High_Frequency_PWM_1_DeadBandMode == High_Frequency_PWM_1__B_PWM__DBM_2_4_CLOCKS)
                High_Frequency_PWM_1_WriteDeadTime(High_Frequency_PWM_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(High_Frequency_PWM_1_KillModeMinTime)
                High_Frequency_PWM_1_WriteKillTime(High_Frequency_PWM_1_backup.PWMKillCounterPeriod);
            #endif /* (High_Frequency_PWM_1_KillModeMinTime) */

            #if(High_Frequency_PWM_1_UseControl)
                High_Frequency_PWM_1_WriteControlRegister(High_Frequency_PWM_1_backup.PWMControlRegister);
            #endif /* (High_Frequency_PWM_1_UseControl) */
        #endif  /* (!High_Frequency_PWM_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: High_Frequency_PWM_1_Sleep
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
*  High_Frequency_PWM_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void High_Frequency_PWM_1_Sleep(void) 
{
    #if(High_Frequency_PWM_1_UseControl)
        if(High_Frequency_PWM_1_CTRL_ENABLE == (High_Frequency_PWM_1_CONTROL & High_Frequency_PWM_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            High_Frequency_PWM_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            High_Frequency_PWM_1_backup.PWMEnableState = 0u;
        }
    #endif /* (High_Frequency_PWM_1_UseControl) */

    /* Stop component */
    High_Frequency_PWM_1_Stop();

    /* Save registers configuration */
    High_Frequency_PWM_1_SaveConfig();
}


/*******************************************************************************
* Function Name: High_Frequency_PWM_1_Wakeup
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
*  High_Frequency_PWM_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void High_Frequency_PWM_1_Wakeup(void) 
{
     /* Restore registers values */
    High_Frequency_PWM_1_RestoreConfig();

    if(High_Frequency_PWM_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        High_Frequency_PWM_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
