/** \file sniffPayload.h
 * \brief sniffPayload header file.
 * \details Defines all the structs for sending payloads and the used
 * functions for initialising these structs.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFPAYLOAD_H_INCLUDED
#define SNIFFPAYLOAD_H_INCLUDED



#include <sniffConfig.h>
#include <stdint.h>

/**
 * @brief Enumerates all Object Types
 *
 * See the TSP for more detail.
 */
typedef enum {QUEUE,MUTEX,COUNTING_SEMAPHORE,BINARY_SEMAPHORE,RECURSIVE_MUTEX,TASK,NUMBER_OF_OBJECTTYPES}ObjectType;

extern uint8_t sniffIDFilter[SIZE_OF_FILTER];

//Information IDs ranging from 0-77 with 23 Reserved IDs (101 total)
/**
 * @brief Enumerates all InformationIDs
 *
 * See the TSP for more detail.
 */
typedef enum {
	ID_START,
	ID_END,
	ID_TASK_SWITCHED_IN,
	ID_INCREASE_TICK_COUNT,
	ID_LOW_POWER_IDLE_BEGIN,
	ID_LOW_POWER_IDLE_END,
	ID_TASK_SWITCHED_OUT,
	ID_TASK_PRIORITY_INHERIT,
	ID_TASK_PRIORITY_DISINHERIT,
	ID_BLOCKING_ON_QUEUE_RECEIVE,
	ID_BLOCKING_ON_QUEUE_SEND,
	ID_MOVED_TASK_TO_READY_STATE,
	ID_POST_MOVED_TASK_TO_READY_STATE,
	ID_QUEUE_CREATE,
	ID_QUEUE_CREATE_FAILED,
	ID_CREATE_MUTEX,
	ID_CREATE_MUTEX_FAILED,
	ID_GIVE_MUTEX_RECURSIVE,
	ID_GIVE_MUTEX_RECURSIVE_FAILED,
	ID_TAKE_MUTEX_RECURSIVE,
	ID_TAKE_MUTEX_RECURSIVE_FAILED,
	ID_CREATE_COUNTING_SEMAPHORE,
	ID_CREATE_COUNTING_SEMAPHORE_FAILED,
	ID_QUEUE_SEND,
	ID_QUEUE_SEND_FAILED,
	ID_QUEUE_RECEIVE,
	ID_QUEUE_PEEK,
	ID_QUEUE_PEEK_FROM_ISR,
	ID_QUEUE_RECEIVE_FAILED,
	ID_QUEUE_SEND_FROM_ISR,
	ID_QUEUE_SEND_FROM_ISR_FAILED,
	ID_QUEUE_RECEIVE_FROM_ISR,
	ID_QUEUE_RECEIVE_FROM_ISR_FAILED,
	ID_QUEUE_PEEK_FROM_ISR_FAILED,
	ID_QUEUE_DELETE,
	ID_TASK_CREATE,
	ID_TASK_CREATE_FAILED,
	ID_TASK_DELETE,
	ID_TASK_DELAY_UNTIL,
	ID_TASK_DELAY,
	ID_TASK_PRIORITY_SET,
	ID_TASK_SUSPEND,
	ID_TASK_RESUME,
	ID_TASK_RESUME_FROM_ISR,
	ID_TASK_INCREMENT_TICK,
	ID_TIMER_CREATE,
	ID_TIMER_CREATE_FAILED,
	ID_TIMER_COMMAND_SEND,
	ID_TIMER_EXPIRED,
	ID_TIMER_COMMAND_RECEIVED,
	ID_MALLOC,
	ID_FREE,
	ID_EVENT_GROUP_CREATE,
	ID_EVENT_GROUP_CREATE_FAILED,
	ID_EVENT_GROUP_SYNC_BLOCK,
	ID_EVENT_GROUP_SYNC_END,
	ID_EVENT_GROUP_WAIT_BITS_BLOCK,
	ID_EVENT_GROUP_WAIT_BITS_END,
	ID_EVENT_GROUP_CLEAR_BITS,
	ID_EVENT_GROUP_CLEAR_BITS_FROM_ISR,
	ID_EVENT_GROUP_SET_BITS,
	ID_EVENT_GROUP_SET_BITS_FROM_ISR,
	ID_EVENT_GROUP_DELETE,
	ID_PEND_FUNC_CALL,
	ID_PEND_FUNC_CALL_FROM_ISR,
	ID_QUEUE_REGISTRY_ADD,
	ID_TASK_NOTIFY_TAKE_BLOCK,
	ID_TASK_NOTIFY_TAKE,
	ID_TASK_NOTIFY_WAIT_BLOCK,
	ID_TASK_NOTIFY_WAIT,
	ID_TASK_NOTIFY,
	ID_TASK_NOTIFY_FROM_ISR,
	ID_TASK_NOTIFY_GIVE_FROM_ISR,
	ID_CUSTOM_MARKER_1,
	ID_CUSTOM_MARKER_2,
	ID_CUSTOM_MARKER_3,
	ID_CUSTOM_MARKER_4,
	ID_CUSTOM_MARKER_5,

}InformationID;

//Error IDs ranging from 101 to 111 (10 total)
/**
 * @brief Enumerates all Error IDs
 * Error IDs ranging from 101 to 111 (10 total)
 * See the TSP for more detail.
 */
typedef enum{
	ID_ERROR_STREAM_FIFO_FULL=101,
	ID_ERROR_RECEIVE_FIFO_FULL
}ErrorID;

//ObjectList IDs ranging from 151 to 151 (1 total)
/**
 * @brief Enumerates the ObjectListID
 * ObjectList IDs Ranging from 151 to 151 (1 total)
 * See the TSP for more detail.
 */
typedef enum{
	ID_OBJECT_LIST = 151
}ObjectListID;

//SniffFilterID ranging from 152 to 152 (1 total)
/**
 * @brief Enumerates the SniffFilterID
 * SniffFilterID ranging from 152 to 152 (1 total)
 * See the TSP for more detail.
 */
typedef enum{
	ID_SNIFF_FILTER = 152
}SniffFilterID;





/**
 * @brief Defines the header for the ObjectList
 *
 * Defines the header for the ObjectList, so it can be send and detected on the GUI-side
 * @see ObjectList
 * @see Object
 */
typedef struct{
	uint8_t packetID; /**< packetID for detecting missing packets*/
	uint8_t informationID; /**<ID to specify the send information*/
	ObjectType objectType;/**<Type of the object which will be send afterwards*/
	uint8_t length;/**<Amount of objects of the given type*/
}ObjectListHeader;


/**
 * @brief Maps the object number to a name
 *
 * Every object holds a number, for example uxTaskNumber in the TCB of every task.
 * This struct maps this special object number to a name, so its easier to oversee at the GUI-side,
 * which can request these objects anytime (Optimally just once at the begin of the Sniff).
 */
typedef struct{
	uint8_t objectNumber;/**<Specific object ID for one objectType*/
	uint8_t lenObjectName;/**<length of the objectName*/
	char objectName[MAX_LENGTH_OF_OBJECTNAME];/**<objectName*/
}Object;


/**
 * @brief Defines the ObjectList
 *
 * Combines header and an array of Objects, which size can be defined in sniffConfig.h
 * @see ObjectList
 * @see Object
 */
typedef struct{
	ObjectListHeader objectHeader; /**<The header defined before*/
	Object objectArray[MAX_NUMBER_OF_OBJECTS];/**<An array of Objects defined before*/
}ObjectList;


/**
 * @brief Defines the BasicPayload, part of every other payload.
 *
 * Holds all the information needed to identify the package and to detect
 * the chronological order and values.
 */
typedef struct {
	uint8_t packetID;/**< packetCounter which counts up for every Payload send out */
	uint8_t informationID;/**< ID to determine which info is held by the payload */
	uint8_t tickCountHigh;/**<SysTick Count in ms, Byte 15-8*/
	uint8_t tickCountLow;/**<SysTick Count in ms, Byte 7-0*/
	uint8_t timerByteHigh;/**<Timer for SysTick Count, Byte 15-8, can be used with the factor TICKS TO MS in the GUI to get a higher resolution, for example if 1000 ticks are 1 ms you use 1000 as the factor*/
	uint8_t timerByteLow;/**<Timer for SysTick Count, Byte 7-0*/
} BasicPayload;


/**
 * @brief Defines the smallest payload with zero data
 *
 * The smallest Payload holds no data and therefore only includes the BasicPayload
 * @see BasicPayload
 */
typedef struct {
	BasicPayload payloadHead;/**<payloadHead of type BasicPayload which is defined before*/
} Payload0;


/**
 * @brief Defines the payload with one data byte
 *
 * It includes one byte of data.
 * @see BasicPayload
 */
typedef struct {
	BasicPayload payloadHead;/**<payloadHead of type BasicPayload which is defined before*/
	uint8_t data1;/**<First data byte*/
} Payload1;


/**
 * @brief Defines the payload with two data bytes
 *
 * It includes two bytes of data.
 * @see BasicPayload
 */
typedef struct {
	BasicPayload payloadHead;/**<payloadHead of type BasicPayload which is defined before*/
	uint8_t data1;/**<First data byte*/
	uint8_t data2;/**<Second data byte*/
} Payload2;


/**
 * @brief Defines the payload with three data bytes
 *
 * It includes three bytes of data.
 * @see BasicPayload
 */
typedef struct {
	BasicPayload payloadHead;/**<payloadHead of type BasicPayload which is defined before*/
	uint8_t data1;/**<First data byte*/
	uint8_t data2;/**<Second data byte*/
	uint8_t data3;/**<Third data byte*/
} Payload3;


/**
 * @brief Defines an error payload
 *
 * Error payloads are used to notify the GUI-side if an error occured,
 * it needs no data, that the payload was send is enough information.
 * Error payloads wont increase the packet counter and therefore wont
 * disrupt the chronological order of the "normal" payloads
 * @see BasicPayload
 */
typedef struct {
	BasicPayload payloadHead;/**<payloadHead of type BasicPayload which is defined before*/
} PayloadError;


// Holds the type and the size
/**
 * @brief Saves the size of the different objects
 *
 * See the TSP for more detail.
 */
typedef enum {PAYLOAD_0=sizeof(Payload0),PAYLOAD_1=sizeof(Payload1),PAYLOAD_2=sizeof(Payload2),PAYLOAD_3=sizeof(Payload3)/* TODO: Wann genutzt? ,OBJECT_LIST=sizeof(ObjectList)*/,PAYLOAD_ERROR=sizeof(PayloadError)}payloadType;




//Function definitions
void packPayload0(InformationID informationID);
void packPayload1(InformationID informationID, uint8_t data1);
void packPayload2(InformationID informationID, uint8_t data1, uint8_t data2);
void packPayload3(InformationID informationID, uint8_t data1, uint8_t data2,
		uint8_t data3);
void packPayloadError(ErrorID errorID);


void initialiseObjectList();
unsigned int increaseObjectCounter(ObjectType objectType);
unsigned int updateObjectList(ObjectType objectType,char* objectNameExtern);
void sendObjectList(uint8_t *packetCounter);

uint8_t applyInformationIDFilter(uint8_t informationID);

#endif // SNIFFPAYLOAD_H_INCLUDED
