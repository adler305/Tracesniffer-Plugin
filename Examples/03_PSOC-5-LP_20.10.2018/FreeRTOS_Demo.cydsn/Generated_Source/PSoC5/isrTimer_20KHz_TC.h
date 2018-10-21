/*******************************************************************************
* File Name: isrTimer_20KHz_TC.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isrTimer_20KHz_TC_H)
#define CY_ISR_isrTimer_20KHz_TC_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrTimer_20KHz_TC_Start(void);
void isrTimer_20KHz_TC_StartEx(cyisraddress address);
void isrTimer_20KHz_TC_Stop(void);

CY_ISR_PROTO(isrTimer_20KHz_TC_Interrupt);

void isrTimer_20KHz_TC_SetVector(cyisraddress address);
cyisraddress isrTimer_20KHz_TC_GetVector(void);

void isrTimer_20KHz_TC_SetPriority(uint8 priority);
uint8 isrTimer_20KHz_TC_GetPriority(void);

void isrTimer_20KHz_TC_Enable(void);
uint8 isrTimer_20KHz_TC_GetState(void);
void isrTimer_20KHz_TC_Disable(void);

void isrTimer_20KHz_TC_SetPending(void);
void isrTimer_20KHz_TC_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrTimer_20KHz_TC ISR. */
#define isrTimer_20KHz_TC_INTC_VECTOR            ((reg32 *) isrTimer_20KHz_TC__INTC_VECT)

/* Address of the isrTimer_20KHz_TC ISR priority. */
#define isrTimer_20KHz_TC_INTC_PRIOR             ((reg8 *) isrTimer_20KHz_TC__INTC_PRIOR_REG)

/* Priority of the isrTimer_20KHz_TC interrupt. */
#define isrTimer_20KHz_TC_INTC_PRIOR_NUMBER      isrTimer_20KHz_TC__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrTimer_20KHz_TC interrupt. */
#define isrTimer_20KHz_TC_INTC_SET_EN            ((reg32 *) isrTimer_20KHz_TC__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrTimer_20KHz_TC interrupt. */
#define isrTimer_20KHz_TC_INTC_CLR_EN            ((reg32 *) isrTimer_20KHz_TC__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrTimer_20KHz_TC interrupt state to pending. */
#define isrTimer_20KHz_TC_INTC_SET_PD            ((reg32 *) isrTimer_20KHz_TC__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrTimer_20KHz_TC interrupt. */
#define isrTimer_20KHz_TC_INTC_CLR_PD            ((reg32 *) isrTimer_20KHz_TC__INTC_CLR_PD_REG)


#endif /* CY_ISR_isrTimer_20KHz_TC_H */


/* [] END OF FILE */
