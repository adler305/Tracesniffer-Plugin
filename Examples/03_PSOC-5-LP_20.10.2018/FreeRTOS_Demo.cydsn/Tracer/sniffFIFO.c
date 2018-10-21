/** \file sniffFIFO.c
 * \brief sniffFIFO source file.
 * \details Implements the priority FIFO which can be configured in sniffConfig.h.
 * \author Marco Seiller
 * \date 2018
 */



#include <sys/types.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sniffPayload.h>
#include <sniffFIFO.h>


//TODO: Any possibility to get the different data structures more variable? (Byte vs Payload3)
#if SEND_WITHOUT_SNIFF_TASK == 0
StreamFIFO streamFIFO;
#endif
ReceiveFIFO receiveFIFO;
ErrorFIFO errorFIFO;

/*
Push data to FIFO
Params:
	fifo: DUAL_PORT_FIFO instance
	data: pointer to data object
	len: length of data object (currently ignored)
	prio: priority, 1=HP, 0=LP
return codes:
0 -> OK
1 -> FULL
*/


#if SEND_WITHOUT_SNIFF_TASK == 0
inline uint8_t writeStreamFIFO(void* inData,payloadType pType){

	size_t nextWptr = (streamFIFO.wptr+1)%streamFIFO.size;

	if ((streamFIFO.rptr)==nextWptr){
		return 1;
	}

	memcpy(&(streamFIFO.Buffer[streamFIFO.wptr]),inData,pType);

	streamFIFO.DataType[streamFIFO.wptr] = pType;
	streamFIFO.wptr = nextWptr;

	return 0;
}
#endif
inline uint8_t writeReceiveFIFO(void* inData,payloadType pType){

	size_t nextWptr = (receiveFIFO.wptr+1)%receiveFIFO.size;

	if ((receiveFIFO.rptr)==nextWptr){
		return 1;
	}
	//receiveFIFO.Buffer[receiveFIFO.wptr]=*inData;
	memcpy(&(receiveFIFO.Buffer[receiveFIFO.wptr]),inData,pType);

	receiveFIFO.DataType[receiveFIFO.wptr] = pType; //TODO: Kein Typ gebraucht nur Bytes
	receiveFIFO.wptr = nextWptr;

	return 0;
}

inline uint8_t writeErrorFIFO(void* inData,payloadType pType){

	size_t nextWptr = (errorFIFO.wptr+1)%errorFIFO.size;

	if ((errorFIFO.rptr)==nextWptr){
		return 1;
	}

	memcpy(&(errorFIFO.Buffer[errorFIFO.wptr]),inData,pType);

	errorFIFO.DataType[errorFIFO.wptr] = pType;
	errorFIFO.wptr = nextWptr;

	return 0;
}

inline uint8_t writeFIFO(void* inData,payloadType pType,Priority prio){
	switch (prio) {
		case prioRECEIVE:
			return writeReceiveFIFO(inData,pType);
			break;
#if SEND_WITHOUT_SNIFF_TASK == 0
		case prioSTREAM:
			return writeStreamFIFO(inData,pType);
			break;
#endif
		case prioERROR:
			return writeErrorFIFO(inData,pType);
			break;
		default:
			return 1;
			break;
	}
}

/*
Behavior:
Reads data from fifo, highest priority first
It's up to the user to free the buffer after use

Params:
	fifo: DUAL_PORT_FIFO instance
	pData: target buffer for data
	pDType: buffer to put read lenght into
	pPrio: buffer to put read priority
return:
0: read OK
1: read FAIL
*/

#if SEND_WITHOUT_SNIFF_TASK == 0
inline uint8_t readStreamFIFO(void* pData, payloadType* pType){

        if (streamFIFO.wptr!=streamFIFO.rptr){
            *pType= streamFIFO.DataType[streamFIFO.rptr];

			memcpy(pData,&(streamFIFO.Buffer[streamFIFO.rptr]),*pType);

           // free(fifo[prio].Buffer[fifo[prio].rptr]);
            //fifo[prio].Buffer[fifo[prio].rptr]=0;
			streamFIFO.rptr=(streamFIFO.rptr+1)%streamFIFO.size;
            return 0;
        }
    //EMPTY
	return 1;
}
#endif

inline uint8_t readReceiveFIFO(void* pData, payloadType* pType){

        if (receiveFIFO.wptr!=receiveFIFO.rptr){
            *pType= receiveFIFO.DataType[receiveFIFO.rptr];

			memcpy(pData,&(receiveFIFO.Buffer[receiveFIFO.rptr]),*pType);

           // free(fifo[prio].Buffer[fifo[prio].rptr]);
            //fifo[prio].Buffer[fifo[prio].rptr]=0;
			receiveFIFO.rptr=(receiveFIFO.rptr+1)%receiveFIFO.size;
            return 0;
        }

    //EMPTY
	return 1;
}

inline uint8_t readErrorFIFO(void* pData, payloadType* pType){

        if (errorFIFO.wptr!=errorFIFO.rptr){
            *pType= errorFIFO.DataType[errorFIFO.rptr];

			memcpy(pData,&(errorFIFO.Buffer[errorFIFO.rptr]),*pType);

           // free(fifo[prio].Buffer[fifo[prio].rptr]);
            //fifo[prio].Buffer[fifo[prio].rptr]=0;
			errorFIFO.rptr=(errorFIFO.rptr+1)%errorFIFO.size;
            return 0;
        }

    //EMPTY
	return 1;
}

inline uint8_t readFIFO(void* pData, payloadType* pType,Priority* prio){
	if(readReceiveFIFO(pData,pType)==0){
		*prio = prioRECEIVE;
		return 0;
	}
#if SEND_WITHOUT_SNIFF_TASK == 0
	else if(readStreamFIFO(pData,pType)==0){
		*prio = prioSTREAM;
		return 0;
	}
#endif
	else if(readErrorFIFO(pData,pType)==0){
		*prio = prioERROR;
		return 0;
	}
	return 1;
}

#if SEND_WITHOUT_SNIFF_TASK == 0
void initialiseStreamFIFO(){
	streamFIFO.wptr=0;
	streamFIFO.rptr=0;
	streamFIFO.size=SIZE_OF_STREAM_FIFO;
}
#endif

void initialiseReceiveFIFO(){
	receiveFIFO.wptr=0;
	receiveFIFO.rptr=0;
	receiveFIFO.size=SIZE_OF_RECEIVE_FIFO;
}

void initialiseErrorFIFO(){
	errorFIFO.wptr=0;
	errorFIFO.rptr=0;
	errorFIFO.size=SIZE_OF_ERROR_FIFO;
}

void initialiseFIFO(){
#if SEND_WITHOUT_SNIFF_TASK == 0
initialiseStreamFIFO();
#endif
initialiseReceiveFIFO();
initialiseErrorFIFO();
}
