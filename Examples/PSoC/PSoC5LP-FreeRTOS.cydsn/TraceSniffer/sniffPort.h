/** \file sniffPort.h
 * \brief sniffPort header file.
 * \details Holds the defines, which have to be implemented by the user. See the implementatin guide for more information.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFPORT_H_
#define SNIFFPORT_H_

#include <sniffPayload.h>

#include <selfFIFO.h>
#include <sniffFIFO.h>
#include <TRACE_UART.h>
    
#define portNVIC_SYSTICK_CURRENT_VALUE_REG  ( * ( ( volatile uint32_t * ) 0xe000e018 ) )
    
#define sendByteOverInterface(sendByte)  TRACE_UART_PutChar(sendByte);/**<the function to send over the preferred Interface has to be implemented here, an interrupt should be used*/

#define enableReceiveInterrupt() TRACE_UART_Start();/**<the code for enabling the receive Interrupt should be added here*/
#define sendReceivedByteToSniffTask(receivedByte) {writeFIFO(&receivedByte,1,prioRECEIVE);}/**<this definition should be placed in the receiving interrupt*/

#define readOutTickCount() xTaskGetTickCount()   /**<the function to read out the tick Count, in FreeRTOS: xTaskGetTickCount() */
#define readOutSysTimerHigh() (portNVIC_SYSTICK_CURRENT_VALUE_REG>>16)&0xff /**<the function to read the SysTimer-HighByte should be implemented here*/
#define readOutSysTimerLow() (portNVIC_SYSTICK_CURRENT_VALUE_REG>>8)&0xff /**<the function to read the SysTimer-LowByte should be implemented here*/



#endif /* SNIFFPORT_H_ */




