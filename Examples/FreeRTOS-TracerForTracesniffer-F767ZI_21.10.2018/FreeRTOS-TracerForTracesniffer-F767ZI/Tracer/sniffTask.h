/** \file sniffTask.h
 * \brief sniffTask header file.
 * \details Includes everything needed for running the SniffTask.
 * \author Jonas Mair
 * \date 2018
 */
#ifndef SNIFFTASK_H_
#define SNIFFTASK_H_

#include <sniffPayload.h>
#include <sniffFIFO.h>

ObjectList objectList[NUMBER_OF_OBJECTTYPES]; /**< Array of ObjectLists, one Array Element per Objecttype */
extern StreamFIFO streamFIFO;
extern ReceiveFIFO receiveFIFO;
extern ErrorFIFO errorFIFO;

//TODO: Wenn keine sniffTask genutzt dann soll nur noch receive in der sniff fifo sein
void sniffTask();
uint8_t applyInformationIDFilter(uint8_t informationID);

/**
 * \brief State Machine for the sniffTask
*/
typedef enum{NORMAL,RECEIVE_FILTER}ReceiverState;
#endif /* SNIFFTASK_H_ */

