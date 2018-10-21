/** \file sniffConfig.h
 * \brief sniffConfig header file.
 * \details In this file all options are collected, which have to be specified for the target system.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFCONFIG_H_
#define SNIFFCONFIG_H_

#define MAX_NUMBER_OF_OBJECTS 5 /**< Defines the maximum amount of different objects per array, for example the amount of tasks or queues*/
#define MAX_LENGTH_OF_OBJECTNAME 8 /**< Defines the maximum length of an objectname, like the task name*/

#define SIZE_OF_STREAM_FIFO 30 /**< Defines the size of the streamFIFO in Payload3-blocks, depending on the timespan in which the Tracer can't send payloads */
#define SIZE_OF_RECEIVE_FIFO 15 /**< Defines the size of the receiveFIFO,in Bytes*/
#define SIZE_OF_ERROR_FIFO 0 /**< Defines the size of the errorFIFO in Payload3-blocks */

#define STACK_SIZE_OF_SNIFF_TASK 85 /**< Defines the stack size of the sniff Task, shouldn't be changed normally*/
#define PRIORITY_OF_SNIFF_TASK  1 /**< Defines the priority of the sniff Task, can be adapted if the priority is not enough to send data*/
#define SIZE_OF_FILTER 13 /**< Defines the size (in bytes) of the sniffFilter*/

#define WAIT_FOR_SNIFFER_START 0
#define SEND_WITHOUT_SNIFF_TASK 1 // Filter funktioniert dann nicht mehr

#define SEND_PREAMBLE sendByteOverInterface(0xfd);sendByteOverInterface(0xfe);sendByteOverInterface(0xff);/**< Defines the preamble which is send at the start of every package*/

#endif /* SNIFFCONFIG_H_ */
