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


/**
 * @brief Enumerates all priorities
 */
typedef enum{
	prioERROR,
	prioSTREAM,
	prioRECEIVE
}Priority;

/**
 * @brief Defines the StreamFIFO struct, where payloads to be send by the sniffTask get buffered
 */
typedef struct{
	size_t wptr;/**<The current write pointer of the FIFO*/
	size_t rptr;/**<The current read pointer of the FIFO*/
	size_t size;/**<The size of the FIFO @sa SIZE_OF_STREAM_FIFO*/
	Payload3 Buffer[SIZE_OF_STREAM_FIFO];/**< Buffer where the data gets saved into*/
	size_t DataType[SIZE_OF_STREAM_FIFO];/**< DataType @sa Payload0 Payload1 Payload2 Payload3*/
}StreamFIFO;

/**
 * @brief Defines the ReceiveFIFO struct, where payloads to be received in the sniffTask get buffered
 */
typedef struct{
	size_t wptr;/**<The current write pointer of the FIFO*/
	size_t rptr;/**<The current read pointer of the FIFO*/
	size_t size;/**<The size of the FIFO @sa SIZE_OF_RECEIVE_FIFO*/
	uint8_t Buffer[SIZE_OF_RECEIVE_FIFO]; /**< Buffer where the data gets saved into*/
	size_t DataType[SIZE_OF_RECEIVE_FIFO];/**< DataType, not needed anymore TODO: update receive fifo data type */
}ReceiveFIFO;

/**
 * @brief Defines the ErrorFIFO struct, where errors to be send by the sniffTask get buffered
 */
typedef struct{
	size_t wptr;/**<The current write pointer of the FIFO*/
	size_t rptr;/**<The current read pointer of the FIFO*/
	size_t size;/**<The size of the FIFO @sa SIZE_OF_ERROR_FIFO*/
	Payload3 Buffer[SIZE_OF_ERROR_FIFO];/**< Buffer where the data gets saved into*/
	size_t DataType[SIZE_OF_ERROR_FIFO];/**< DataType, not needed anymore TODO: update error fifo data type */
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
