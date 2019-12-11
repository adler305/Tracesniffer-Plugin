/** \file sniffPayload.c
 * \brief sniffPayload source file.
 * \details Implements all the structs for sending payloads and the used
 * functions for initialising these structs.
 * \author Jonas Mair
 * \date 2018
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sniffPayload.h>
#include <sniffFIFO.h>
#include <sniffPort.h>
//Defines

uint8_t objectCounter[NUMBER_OF_OBJECTTYPES];/**<Counts the number of objects of one specific type*/
uint8_t sniffIDFilter[SIZE_OF_FILTER];/**<Saves the ID-Filter*/
extern ObjectList objectList[NUMBER_OF_OBJECTTYPES];
extern uint32_t readOutTickCount();/**<extern function to read out the SysTick*/

#if SEND_WITHOUT_SNIFF_TASK == 0
extern void stopTraceSniffer();
#endif

#if SEND_WITHOUT_SNIFF_TASK
uint8_t packetCounter;
#endif
//Functions

//Modulo Alternative      i & (m-1)


/**
 * \brief pack a Payload0 payload and make it ready to send
 * \param informationID informationID of the payload
 * \sa InformationID
 */
inline void packPayload0(InformationID informationID) {
#if SEND_WITHOUT_SNIFF_TASK
	if (applyInformationIDFilter(informationID)) {
		SEND_PREAMBLE
		;
		sendByteOverInterface(packetCounter++);
		sendByteOverInterface(informationID);
		sendByteOverInterface(readOutTickCount() >> 8);
		sendByteOverInterface(readOutTickCount());
		sendByteOverInterface(readOutSysTimerHigh());
		sendByteOverInterface(readOutSysTimerLow());
	}
#else
	Payload0 payload;
	payload.payloadHead.informationID = informationID;
	payload.payloadHead.tickCountHigh = readOutTickCount() >> 8;
	payload.payloadHead.tickCountLow = readOutTickCount();
	payload.payloadHead.timerByteHigh = readOutSysTimerHigh();
	payload.payloadHead.timerByteLow = readOutSysTimerLow();
	if(writeFIFO(&payload,PAYLOAD_0,prioSTREAM)!=0) {
		packPayloadError(ID_ERROR_STREAM_FIFO_FULL);
	}
#endif
}


/**
 * \brief pack a Payload1 payload and make it ready to send
 * \param informationID informationID of the payload
 * \param data1 first data byte
 * \sa InformationID
 */
inline void packPayload1(InformationID informationID, uint8_t data1) {
#if SEND_WITHOUT_SNIFF_TASK

	if (applyInformationIDFilter(informationID)) {
		SEND_PREAMBLE
		sendByteOverInterface(packetCounter++);
		sendByteOverInterface(informationID);
		sendByteOverInterface(readOutTickCount() >> 8);
		sendByteOverInterface(readOutTickCount());
		sendByteOverInterface(readOutSysTimerHigh());
		sendByteOverInterface(readOutSysTimerLow());
		sendByteOverInterface(data1);
	}
#else
	Payload1 payload;
	payload.payloadHead.informationID = informationID;
	payload.payloadHead.tickCountHigh = readOutTickCount() >> 8;
	payload.payloadHead.tickCountLow = readOutTickCount();
	payload.payloadHead.timerByteHigh = readOutSysTimerHigh();
	payload.payloadHead.timerByteLow = readOutSysTimerLow();
	payload.data1 = data1;
	if(writeFIFO(&payload,PAYLOAD_1,prioSTREAM)!=0) {
		packPayloadError(ID_ERROR_STREAM_FIFO_FULL);
	}
#endif
}


/**
 * \brief pack a Payload2 payload and make it ready to send
 * \param informationID informationID of the payload
 * \param data1 first data byte
 * \param data2 second data byte
 * \sa InformationID
 */
inline void packPayload2(InformationID informationID, uint8_t data1,
		uint8_t data2) {
#if SEND_WITHOUT_SNIFF_TASK
	if (applyInformationIDFilter(informationID)) {
		SEND_PREAMBLE
		sendByteOverInterface(packetCounter++);
		sendByteOverInterface(informationID);
		sendByteOverInterface(readOutTickCount() >> 8);
		sendByteOverInterface(readOutTickCount());
		sendByteOverInterface(readOutSysTimerHigh());
		sendByteOverInterface(readOutSysTimerLow());
		sendByteOverInterface(data1);
		sendByteOverInterface(data2);
	}

#else
	Payload2 payload;
	payload.payloadHead.informationID = informationID;
	payload.payloadHead.tickCountHigh = readOutTickCount() >> 8;
	payload.payloadHead.tickCountLow = readOutTickCount();
	payload.payloadHead.timerByteHigh = readOutSysTimerHigh();
	payload.payloadHead.timerByteLow = readOutSysTimerLow();
	payload.data1 = data1;
	payload.data2 = data2;
	if(writeFIFO(&payload,PAYLOAD_2,prioSTREAM)!=0) {
		packPayloadError(ID_ERROR_STREAM_FIFO_FULL);
	}
#endif
}


/**
 * \brief pack a Payload2 payload and make it ready to send
 * \param informationID informationID of the payload
 * \param data1 first data byte
 * \param data2 second data byte
 * \param data3 third data byte
 * \sa InformationID
 */
inline void packPayload3(InformationID informationID, uint8_t data1,
		uint8_t data2, uint8_t data3) {
#if SEND_WITHOUT_SNIFF_TASK
	if (applyInformationIDFilter(informationID)) {
		SEND_PREAMBLE
		sendByteOverInterface(packetCounter++);
		sendByteOverInterface(informationID);
		sendByteOverInterface(readOutTickCount() >> 8);
		sendByteOverInterface(readOutTickCount());
		sendByteOverInterface(readOutSysTimerHigh());
		sendByteOverInterface(readOutSysTimerLow());
		sendByteOverInterface(data1);
		sendByteOverInterface(data2);
		sendByteOverInterface(data3);
	}
#else
	Payload3 payload;
	payload.payloadHead.packetID = 0; // packetCounter++;
	payload.payloadHead.informationID = informationID;
	payload.payloadHead.tickCountHigh = readOutTickCount() >> 8;
	payload.payloadHead.tickCountLow = readOutTickCount();
	payload.payloadHead.timerByteHigh = readOutSysTimerHigh();
	payload.payloadHead.timerByteLow = readOutSysTimerLow();
	payload.data1 = data1;
	payload.data2 = data2;
	payload.data3 = data3;

	if(writeFIFO(&payload,PAYLOAD_3,prioSTREAM)!=0) {
		packPayloadError(ID_ERROR_STREAM_FIFO_FULL);
	}
#endif
}

/**
 * \brief pack a Error payload and make it ready to send
 * \param errorID errorID of the payload
 * \sa ErrorID
 */
inline void packPayloadError(ErrorID errorID) {
#if SEND_WITHOUT_SNIFF_TASK
	SEND_PREAMBLE
	sendByteOverInterface(packetCounter);
	sendByteOverInterface(errorID);
	sendByteOverInterface(readOutTickCount() >> 8);
	sendByteOverInterface(readOutTickCount());
	sendByteOverInterface(readOutSysTimerHigh());
	sendByteOverInterface(readOutSysTimerLow());
#else
	PayloadError payload;
	payload.payloadHead.informationID = errorID;
	payload.payloadHead.tickCountHigh = readOutTickCount() >> 8;
	payload.payloadHead.tickCountLow = readOutTickCount();
	payload.payloadHead.timerByteHigh = readOutSysTimerHigh();
	payload.payloadHead.timerByteLow = readOutSysTimerLow();
	if(writeFIFO(&payload,PAYLOAD_ERROR,prioERROR)!=0) {
		stopTraceSniffer();
	}
#endif
}
// To Call before tasks are created

/**
 * \brief Initialises the ObjectList
 * \sa ObjectList
 */
void initialiseObjectList() {

	for (unsigned int i = 0; i < NUMBER_OF_OBJECTTYPES; ++i) {
		objectCounter[i] = 1;
		objectList[i].objectHeader.objectType = i;
		objectList[i].objectHeader.informationID = ID_OBJECT_LIST;
		objectList[i].objectHeader.length = 0;
	}
}

/**
 * \brief Counts up the number of objects of on specific type
 * \sa ObjectList
 */
inline unsigned int increaseObjectCounter(ObjectType objectType) {

	if (0xff == objectCounter[objectType]) {
		//TODO: error -> Counter voll
		return 0x0;
	}
	return objectCounter[objectType]++;
}


/**
 * \brief Adds a new element to the ObjectList
 * \param objectType the type of the added object
 * \param objectNameExtern the name of the added object
 * \return returns the specific id of the added object
 * \sa ObjectList
 */
inline unsigned int updateObjectList(ObjectType objectType,
		char* objectNameExtern) { // count is 1 based while the array place is 0 based -> count-1, the 0 in count is used to determine a deleted object
	size_t len;
	size_t lengthObjectName = strlen(objectNameExtern);
	uint8_t count = increaseObjectCounter(objectType);

	objectList[objectType].objectArray[count - 1].objectNumber = count;

	if ((MAX_LENGTH_OF_OBJECTNAME - 1) < lengthObjectName) {
		len = MAX_LENGTH_OF_OBJECTNAME;
	} else {
		len = lengthObjectName;
	}

	memcpy(objectList[objectType].objectArray[count - 1].objectName,
			objectNameExtern, len);
	objectList[objectType].objectArray[count - 1].objectName[len] = '\0';
	objectList[objectType].objectArray[count - 1].lenObjectName = len;

	objectList[objectType].objectHeader.length++;

	return count;
}


/**
 * \brief Sends the ObjectList over the interface
 * \param packetCounter the reference to the packet counter
 * \sa ObjectList
 */
void sendObjectList(uint8_t *packetCounter) {
	uint8_t lengthList = 0;
	uint8_t lengthObjectName;
	char* currObjectName;

	for (int i = 0; i < NUMBER_OF_OBJECTTYPES; ++i) {

		SEND_PREAMBLE
		;
		objectList[i].objectHeader.packetID = (*packetCounter)++;
		sendByteOverInterface(objectList[i].objectHeader.packetID);
		sendByteOverInterface(objectList[i].objectHeader.informationID);
		sendByteOverInterface(objectList[i].objectHeader.objectType);
		lengthList = objectList[i].objectHeader.length;
		sendByteOverInterface(lengthList);

		for (int j = 0; j < lengthList; ++j) {
			sendByteOverInterface(objectList[i].objectArray[j].objectNumber);
			lengthObjectName = objectList[i].objectArray[j].lenObjectName;
			sendByteOverInterface(lengthObjectName);
			currObjectName = objectList[i].objectArray[j].objectName;
			for (int i = 0; i < lengthObjectName; ++i) {
				sendByteOverInterface(*currObjectName);
				currObjectName++;
			}

		}
		SEND_PREAMBLE
		;
	}
}

//Modulo Alternative      i & (m-1)


/**
 * \brief Filters the payloads, see TSP for more detail
 * \param informationID informationID of the payload
 * \sa sniffIDFilter
 */
uint8_t applyInformationIDFilter(uint8_t informationID) {
	uint8_t arrayPlace;
	arrayPlace = informationID >> 3;
	if (sniffIDFilter[arrayPlace] & (1 << (informationID & (7)))) {
		return 1;
	}
	return 0;
}
