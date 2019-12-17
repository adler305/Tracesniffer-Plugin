/** \file sniffTask.c
 * \brief sniffTask source file.
 * \details Implements everything needed for running the SniffTask.
 * \author Jonas Mair
 * \date 2018
 */
#include <stdlib.h>

#include <sniffTask.h>
#include <sniffHooks.h>
#include <sniffPayload.h>
#include <sniffFIFO.h>
#include <sniffPort.h>

extern void vTaskDelay();/**<extern OsDelay function*/



/**
 * \brief The sniffTask manages the sending and receiving of payloads
 */
void sniffTask() {

	//Important Variables
	Payload3 payload; // payload for read FIFO

	Payload3 *currPayload; //Types to cast to depending on the receive payloadType
	PayloadError *currPayloadError;
	uint8_t* currPayloadReceived;

	payloadType currPayloadType;
	Priority currReadPrio;
	uint8_t packetCounter = 0;
	ReceiverState receiverState = NORMAL;

	//Miscellanous Variables
	unsigned char const* ptr; // ptr for iterating over payload struct
	unsigned char currSniffFilterByte = 0;
	uint8_t* pSniffIDFilter;

	while (1) {

		if (0 == readFIFO((void*) &payload, &currPayloadType, &currReadPrio)) {
			switch (currReadPrio) {
			case prioSTREAM: {
				currPayload = (Payload3*) &payload;
				if (applyInformationIDFilter(
						currPayload->payloadHead.informationID)) {
					currPayload->payloadHead.packetID = packetCounter++;

					SEND_PREAMBLE
					;
					ptr = (unsigned char*) currPayload;
					for (size_t pos = 0; pos < currPayloadType; pos++) {
						sendByteOverInterface(*ptr);
						ptr++;
					}
				}
			}
				break;
			case prioERROR: {
				currPayloadError = (PayloadError*) &payload;
				currPayloadError->payloadHead.packetID = packetCounter++;
				SEND_PREAMBLE
				;
				ptr = (unsigned char*) currPayloadError;
				for (size_t pos = 0; pos < currPayloadType; pos++) {
					sendByteOverInterface(*ptr);
					ptr++;
				}
			}
				break;
			case prioRECEIVE: {

				currPayloadReceived = (uint8_t*) &payload;
				#if SEND_WITHOUT_SNIFF_TASK
				uint8_t copySniffIDFilter[SIZE_OF_FILTER];
				#endif

				switch (receiverState) {
				case NORMAL: {
					switch (*currPayloadReceived) {
					case ID_OBJECT_LIST:
					#if SEND_WITHOUT_SNIFF_TASK // So the Filter Send wont get interrupted (Only by errors)
						for (int i = 0; i < SIZE_OF_FILTER; ++i) {
							copySniffIDFilter[i] = sniffIDFilter[i];
							sniffIDFilter[i] = 0;
						}
					#endif
						sendObjectList(&packetCounter);
					#if SEND_WITHOUT_SNIFF_TASK
						for (int i = 0; i < SIZE_OF_FILTER; ++i) {
							sniffIDFilter[i] = copySniffIDFilter[i];
						}
					#endif
						break;
					case ID_SNIFF_FILTER: {
						receiverState = RECEIVE_FILTER;
						pSniffIDFilter = (uint8_t*) sniffIDFilter;
					}
						break;
					default:
						break;
					}
				}
					break;
				case RECEIVE_FILTER: {

					if (currSniffFilterByte < SIZE_OF_FILTER) {
						*pSniffIDFilter = *currPayloadReceived;
						pSniffIDFilter++;
						currSniffFilterByte++;
						if (currSniffFilterByte >= 13) {
							currSniffFilterByte = 0;
							receiverState = NORMAL;
						}
					}
				}
					break;
				default:
					break;
				}

			}
				break;
			default:

				break;
			}

		} else {
			vTaskDelay(10);
		}
	}
}

