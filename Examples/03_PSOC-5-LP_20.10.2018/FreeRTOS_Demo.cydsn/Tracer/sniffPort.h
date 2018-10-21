/** \file sniffPort.h
 * \brief sniffPort header file.
 * \details Holds the defines, which have to be implemented by the user.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFPORT_H_
#define SNIFFPORT_H_

#include <sniffPayload.h>



#include <sniffFIFO.h>
#include <selfFIFO.h>
#include <UART_1.h>
#include <isr_UART1_RX_BYTE_RECEIVED.h>
#include <isr_UART1_TX_BYTE_COMPLETE.h>
//This file collects all functions, which have to be user-defined.

// Maximal number of objects for the object lists, maximum is 255 due to the counter type unsigned int

#define enableReceiveInterrupt() UART_1_Start(); UART_1_SetTxInterruptMode( 0);UART_1_SetRxInterruptMode( UART_1_RX_STS_FIFO_NOTEMPTY );isr_UART1_RX_BYTE_RECEIVED_Start();isr_UART1_TX_BYTE_COMPLETE_Start();

#define portNVIC_SYSTICK_CURRENT_VALUE_REG  ( * ( ( volatile uint32_t * ) 0xe000e018 ) )

#define sendByteOverInterface(sendByte) /*UART_1_PutChar(sendByte);//*/{BufferIn(sendByte);UART_1_SetTxInterruptMode( UART_1_TX_STS_COMPLETE);} // Wie genau?
#define sendReceivedByteToSniffTask(receivedByte) {writeFIFO(&receivedByte,1,prioRECEIVE);}
#define readOutSysTimerHigh() 	(portNVIC_SYSTICK_CURRENT_VALUE_REG>>8)&0xff
#define readOutSysTimerLow()	portNVIC_SYSTICK_CURRENT_VALUE_REG&0xff



#endif /* SNIFFPORT_H_ */




