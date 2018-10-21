/** \file sniffPort.h
 * \brief sniffPort header file.
 * \details Holds the defines, which have to be implemented by the user. See the implementatin guide for more information.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFPORT_H_
#define SNIFFPORT_H_

#include <sniffPayload.h>

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_uart.h"
#include <selfFIFO.h>
#include <sniffFIFO.h>

//! @cond Doxygen_Suppress
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;
//! @endcond



#define sendByteOverInterface(sendByte) /**<the function to send over the preferred Interface has to be implemented here, an interrupt should be used*/

#define enableReceiveInterrupt() /**<the code for enabling the receive Interrupt should be added here*/
#define sendReceivedByteToSniffTask(receivedByte) /**<this definition should be placed in the receiving interrupt*/

#define readOutSysTimerHigh() 	 /**<the function to read the SysTimer-HighByte should be implemented here*/
#define readOutSysTimerLow()	/**<the function to read the SysTimer-LowByte should be implemented here*/



#endif /* SNIFFPORT_H_ */




