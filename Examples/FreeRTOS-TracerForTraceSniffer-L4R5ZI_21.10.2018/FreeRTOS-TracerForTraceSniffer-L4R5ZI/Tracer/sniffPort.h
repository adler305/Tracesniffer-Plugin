/** \file sniffPort.h
 * \brief sniffPort header file.
 * \details Holds the defines, which have to be implemented by the user.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFPORT_H_
#define SNIFFPORT_H_

#include <sniffPayload.h>

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_uart.h"
#include <selfFIFO.h>
#include <sniffFIFO.h>


extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart2;
//This file collects all functions, which have to be user-defined.

// Maximal number of objects for the object lists, maximum is 255 due to the counter type unsigned int

#define enableReceiveInterrupt() SET_BIT(huart2.Instance->CR1, USART_CR1_RXNEIE_RXFNEIE);



#define sendByteOverInterface(sendByte) {BufferIn(sendByte);SET_BIT(huart2.Instance->CR1, USART_CR1_TXEIE_TXFNFIE);}// Wie genau?
#define sendReceivedByteToSniffTask(receivedByte) {writeReceiveFIFO(&receivedByte,1);}

#define readOutTickCount() xTaskGetTickCount()   /**<the function to read out the tick Count, in FreeRTOS: xTaskGetTickCount()*/
#define readOutSysTimerHigh() 	__HAL_TIM_GetCounter(&htim1)>>8
#define readOutSysTimerLow()	(__HAL_TIM_GetCounter(&htim1)&0xFF)



#endif /* SNIFFPORT_H_ */




