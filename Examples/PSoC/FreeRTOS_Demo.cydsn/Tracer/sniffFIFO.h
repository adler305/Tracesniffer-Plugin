/** \file sniffFIFO.h
 * \brief sniffFIFO header file.
 * \details Declares the priority FIFO which can be configured in sniffConfig.h.
 * \author Marco Seiller
 * \date 2018
 */

#ifndef SNIFFFIFO_H_
#define SNIFFFIFO_H_

#include <sys/types.h>
#include <stdint.h>
#include <sniffConfig.h>



#if SEND_WITHOUT_SNIFF_TASK
#undef SIZE_OF_STREAM_FIFO
#define SIZE_OF_STREAM_FIFO 0
#endif

typedef struct{
	size_t wptr;
	size_t rptr;
	size_t size;
	Payload3 Buffer[SIZE_OF_STREAM_FIFO]; //buffer holds pointers
	size_t DataType[SIZE_OF_STREAM_FIFO];
}StreamFIFO;

typedef struct{
	size_t wptr;
	size_t rptr;
	size_t size;
	uint8_t Buffer[SIZE_OF_RECEIVE_FIFO]; //buffer holds pointers
	size_t DataType[SIZE_OF_RECEIVE_FIFO];
}ReceiveFIFO;

typedef struct{
	size_t wptr;
	size_t rptr;
	size_t size;
	Payload0 Buffer[SIZE_OF_ERROR_FIFO]; //buffer holds pointers
	size_t DataType[SIZE_OF_ERROR_FIFO];
}ErrorFIFO;

uint8_t writeStreamFIFO(void* inData,payloadType pType);
uint8_t writeReceiveFIFO(void* inData,payloadType pType);
uint8_t writeErrorFIFO(void* inData,payloadType pType);
uint8_t writeFIFO(void* inData,payloadType pType,Priority prio);

uint8_t readStreamFIFO(void* pData, payloadType* pType);
uint8_t readReceiveFIFO(void* pData, payloadType* pType);
uint8_t readErrorFIFO(void* pData, payloadType* pType);
uint8_t readFIFO(void* pData, payloadType* pType,Priority* prio);

void initialiseStreamFIFO();
void initialiseReceiveFIFO();
void initialiseErrorFIFO();
void initialiseFIFO();



#endif /* SNIFFFIFO_H_ */
