/** \file sniffPort.h
 * \brief sniffPort header file.
 * \details Holds the defines, which have to be implemented by the user. See the implementatin guide for more information.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFPORT_H_
#define SNIFFPORT_H_

#include <project.h>
#include <sniffPayload.h>

//#include <selfFIFO.h>
#include <sniffFIFO.h>

//! @cond Doxygen_Suppress
//! @endcond
extern uint32 msCount;


#define sendByteOverInterface(sendByte) {TraceSnifferUART_PutChar(sendByte);}/**<the function to send over the preferred Interface has to be implemented here, an interrupt should be used*/

#define enableReceiveInterrupt() /**<the code for enabling the receive Interrupt should be added here*/
#define sendReceivedByteToSniffTask(receivedByte) /**<this definition should be placed in the receiving interrupt*/

#define readOutTickCount() (999-msCount)
#define readOutSysTimerHigh() (24000-CY_SYS_SYST_CVR_REG) >> 8	 /**<the function to read the SysTimer-HighByte should be implemented here*/
#define readOutSysTimerLow()    (24000-CY_SYS_SYST_CVR_REG)      /**<the function to read the SysTimer-LowByte should be implemented here*/



#endif /* SNIFFPORT_H_ */




