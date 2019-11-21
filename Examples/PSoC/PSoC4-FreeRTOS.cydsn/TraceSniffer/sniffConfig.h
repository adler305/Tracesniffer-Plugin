/** \file sniffConfig.h
 * \brief sniffConfig header file.
 * \details In this file all options are collected, which have to be specified for the target system.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFCONFIG_H_
#define SNIFFCONFIG_H_

#define MAX_NUMBER_OF_OBJECTS 16 /**< Defines the maximum amount of different objects per objecttype, for example the amount of tasks or queues*/
#define MAX_LENGTH_OF_OBJECTNAME 16 /**< Defines the maximum length of an objectname, like the task name*/

#define SIZE_OF_STREAM_FIFO 330  /**< Defines the size of the streamFIFO in Payload3-blocks (9 Byte), depending on the timespan in which the Tracer can't send payloads */
#define SIZE_OF_RECEIVE_FIFO 10 /**< Defines the size of the receiveFIFO,in Bytes*/
#define SIZE_OF_ERROR_FIFO 10 /**< Defines the size of the errorFIFO in Payload3-blocks */

#define STACK_SIZE_OF_SNIFF_TASK 128 /**< Defines the stack size of the sniff Task, shouldn't be changed normally*/
#define PRIORITY_OF_SNIFF_TASK  1 /**< Defines the priority of the sniff Task, can be adapted if the priority is not enough to send data*/
#define SIZE_OF_FILTER 13 /**< Defines the size (in bytes) of the sniffFilter*/

#define WAIT_FOR_SNIFFER_START 0 /**< If enabled, the device waits for a random byte send over the defined interface*/
#define SEND_WITHOUT_SNIFF_TASK 0 /**< If enabled, the data gets send directly and isn't buffered and send over the sniffTask, which costs less memory but is also less realtime-save*/

#define SEND_PREAMBLE sendByteOverInterface(0xfd);sendByteOverInterface(0xfe);sendByteOverInterface(0xff);/**< Defines the preamble which is send at the start of every package*/

#endif /* SNIFFCONFIG_H_ */




//How to document different things in Doxygen
//Functions
/**
 * \brief Push data to ReceiveFIFO
 * \param inData a pointer to the data block
 * \param pType the type of data, could be any length
 * \return 0 if OK, 1 if full
 * \sa writeStreamFIFO() and writeErrorFIFO()
 */


//Variables
/**< Defines the size (in bytes) of the sniffFilter*/

//Structs/Enums
/**
 * @brief Enumerates all InformationIDs
 *
 * See the TSP for more detail.
 */
