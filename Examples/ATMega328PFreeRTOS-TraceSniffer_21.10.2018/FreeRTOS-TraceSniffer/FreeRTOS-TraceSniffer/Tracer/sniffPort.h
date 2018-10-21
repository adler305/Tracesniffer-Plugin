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
#include <avr/io.h>
//This file collects all functions, which have to be user-defined.

// Maximal number of objects for the object lists, maximum is 255 due to the counter type unsigned int

#define enableReceiveInterrupt() 



#define sendByteOverInterface(sendByte) uart_putc(sendByte);// Wie genau?
#define sendReceivedByteToSniffTask(receivedByte) {writeFIFO(&receivedByte,1,prioRECEIVE);}
#define readOutSysTimerHigh() 	TCNT1H
#define readOutSysTimerLow()	TCNT1L



#endif /* SNIFFPORT_H_ */




