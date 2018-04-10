/*
* traceSniffing.h
*
* Created: 17.12.2017 03:01:22
*  Author: JonasPC
*/

#ifndef TRACESNIFFING_H_
#define TRACESNIFFING_H_

#define configUSE_TRACE_FACILITY  1
#include "stm32f7xx_hal.h"
#include "selfFIFO.h"

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;

char* msgtoSniffBuffer;
// Enumeration to define the Information ID 
enum{START=14, END, TASK_SWITCHED_IN, INCREASE_TICK_COUNT, LOW_POWER_IDLE_BEGIN, LOW_POWER_IDLE_END, TASK_SWITCHED_OUT, TASK_PRIORITY_INHERIT, TASK_PRIORITY_DISINHERIT, BLOCKING_ON_QUEUE_RECEIVE, BLOCKING_ON_QUEUE_SEND, MOVED_TASK_TO_READY_STATE,
	POST_MOVED_TASK_TO_READY_STATE, QUEUE_CREATE, QUEUE_CREATE_FAILED, CREATE_MUTEX, CREATE_MUTEX_FAILED, GIVE_MUTEX_RECURSIVE, GIVE_MUTEX_RECURSIVE_FAILED, TAKE_MUTEX_RECURSIVE, TAKE_MUTEX_RECURSIVE_FAILED, CREATE_COUNTING_SEMAPHORE, CREATE_COUNTING_SEMAPHORE_FAILED,
	 QUEUE_SEND, QUEUE_SEND_FAILED, QUEUE_RECEIVE, QUEUE_PEEK, QUEUE_PEEK_FROM_ISR, QUEUE_RECEIVE_FAILED, QUEUE_SEND_FROM_ISR, QUEUE_SEND_FROM_ISR_FAILED, QUEUE_RECEIVE_FROM_ISR, QUEUE_RECEIVE_FROM_ISR_FAILED, QUEUE_PEEK_FROM_ISR_FAILED, QUEUE_DELETE,
	 TASK_CREATE, TASK_CREATE_FAILED, TASK_DELETE, TASK_DELAY_UNTIL, TASK_DELAY, TASK_PRIORITY_SET, TASK_SUSPEND, TASK_RESUME, TASK_RESUME_FROM_ISR, TASK_INCREMENT_TICK, TIMER_CREATE, TIMER_CREATE_FAILED, TIMER_COMMAND_SEND, TIMER_EXPIRED, TIMER_COMMAND_RECEIVED,
	 MALLOC, FREE, EVENT_GROUP_CREATE, EVENT_GROUP_CREATE_FAILED, EVENT_GROUP_SYNC_BLOCK, EVENT_GROUP_SYNC_END, EVENT_GROUP_WAIT_BITS_BLOCK, EVENT_GROUP_WAIT_BITS_END, EVENT_GROUP_CLEAR_BITS, EVENT_GROUP_CLEAR_BITS_FROM_ISR, EVENT_GROUP_SET_BITS, EVENT_GROUP_SET_BITS_FROM_ISR, 
	 EVENT_GROUP_DELETE, PEND_FUNC_CALL, PEND_FUNC_CALL_FROM_ISR, QUEUE_REGISTRY_ADD, TASK_NOTIFY_TAKE_BLOCK, TASK_NOTIFY_TAKE, TASK_NOTIFY_WAIT_BLOCK, TASK_NOTIFY_WAIT, TASK_NOTIFY, TASK_NOTIFY_FROM_ISR, TASK_NOTIFY_GIVE_FROM_ISR, CUSTOM_MARKER_1, CUSTOM_MARKER_2, CUSTOM_MARKER_3, CUSTOM_MARKER_4, CUSTOM_MARKER_5
};

/*
#define queueQUEUE_TYPE_BASE				( ( uint8_t ) 0U )
#define queueQUEUE_TYPE_SET					( ( uint8_t ) 0U )
#define queueQUEUE_TYPE_MUTEX 				( ( uint8_t ) 1U )
#define queueQUEUE_TYPE_COUNTING_SEMAPHORE	( ( uint8_t ) 2U )
#define queueQUEUE_TYPE_BINARY_SEMAPHORE	( ( uint8_t ) 3U )
#define queueQUEUE_TYPE_RECURSIVE_MUTEX		( ( uint8_t ) 4U )
*/
//Keine Queue Nummer sondern der QueueType wird mitgeschickt // vllt auch noch die nummer also 2 Bytes noch keine Ahnung


/* Define here the function u want to use to send a byte over USART/serial interface*/
#define sendByteOverInterface(x)  BufferIn(x);SET_BIT(huart2.Instance->CR1, USART_CR1_TXEIE);
#define sendStringOverInterface(x) for(msgtoSniffBuffer = (char*)x;*msgtoSniffBuffer!=0;msgtoSniffBuffer++){BufferIn(*msgtoSniffBuffer);}SET_BIT(huart2.Instance->CR1, USART_CR1_TXEIE);


/*Interface Signals :*/

#define sendInformationStart	sendByteOverInterface(0x0)
// You can decide which time info you want to send. Its mandatory to send the TickCount, for everything else you can decide how many Bytes of TimerValue you want to send (1-4)
#define sendSystemTime			sendByteOverInterface(xTaskGetTickCount()>>8);sendByteOverInterface(xTaskGetTickCount()); sendByteOverInterface((__HAL_TIM_GetCounter(&htim1)&0xFF00)>>8); sendByteOverInterface(__HAL_TIM_GetCounter(&htim1)&0xFF)
#define sendInformationID(x)	sendByteOverInterface(x)
#define sendMessageLength(x)	sendByteOverInterface(x)
//Send Information





#define tenZeros() sendByteOverInterface(0x0);sendByteOverInterface(0x0);sendByteOverInterface(0x0);sendByteOverInterface(0x0);sendByteOverInterface(0x0);sendByteOverInterface(0x0);sendByteOverInterface(0x0);sendByteOverInterface(0x0);sendByteOverInterface(0x0);sendByteOverInterface(0x0); // Sending 10 zeros as signal for a reset

/* Used to perform any necessary initialisation.*/
#define traceSTART() {tenZeros();sendInformationStart;sendSystemTime; sendInformationID(START);sendMessageLength(0);} // Can be used to give all numbers and their tasks to the backend



/* Use to close a trace, for example close a file into which trace has been
written. */
#define traceEND()

#define traceCUSTOM_MARKER_1() {sendInformationStart;sendSystemTime; sendInformationID(CUSTOM_MARKER_1);sendMessageLength(1);sendByteOverInterface('1');}

#define traceCUSTOM_MARKER_2() {sendInformationStart;sendSystemTime; sendInformationID(CUSTOM_MARKER_2);sendMessageLength(1);sendByteOverInterface('2');}

#define traceCUSTOM_MARKER_3() {sendInformationStart;sendSystemTime; sendInformationID(CUSTOM_MARKER_3);sendMessageLength(1);sendByteOverInterface('3');}

#define traceCUSTOM_MARKER_4() {sendInformationStart;sendSystemTime; sendInformationID(CUSTOM_MARKER_4);sendMessageLength(1);sendByteOverInterface('4');}

#define traceCUSTOM_MARKER_5() {sendInformationStart;sendSystemTime; sendInformationID(CUSTOM_MARKER_5);sendMessageLength(1);sendByteOverInterface('5');}

/* Called after a task has been selected to run.  pxCurrentTCB holds a pointer
to the task control block of the selected task. */


#define traceTASK_SWITCHED_IN() {sendInformationStart;sendSystemTime; sendInformationID(TASK_SWITCHED_IN);sendMessageLength(strlen(pxCurrentTCB->pcTaskName)); sendStringOverInterface(pxCurrentTCB->pcTaskName);}

/* Called before stepping the tick count after waking from tickless idle
sleep. */
#define traceINCREASE_TICK_COUNT( x )



/* Called immediately before entering tickless idle. */
#define traceLOW_POWER_IDLE_BEGIN()


/* Called when returning to the Idle task after a tickless idle. */
#define traceLOW_POWER_IDLE_END()



/* Called before a task has been selected to run.  pxCurrentTCB holds a pointer
to the task control block of the task being switched out. */
#define traceTASK_SWITCHED_OUT() {sendInformationStart;sendSystemTime; sendInformationID(TASK_SWITCHED_OUT);sendMessageLength(strlen(pxCurrentTCB->pcTaskName)); sendStringOverInterface(pxCurrentTCB->pcTaskName);}


/* Called when a task attempts to take a mutex that is already held by a
lower priority task.  pxTCBOfMutexHolder is a pointer to the TCB of the task
that holds the mutex.  uxInheritedPriority is the priority the mutex holder
will inherit (the priority of the task that is attempting to obtain the
muted. */
#define traceTASK_PRIORITY_INHERIT( pxTCBOfMutexHolder, uxInheritedPriority )



/* Called when a task releases a mutex, the holding of which had resulted in
the task inheriting the priority of a higher priority task.
pxTCBOfMutexHolder is a pointer to the TCB of the task that is releasing the
mutex.  uxOriginalPriority is the task's configured (base) priority. */
#define traceTASK_PRIORITY_DISINHERIT( pxTCBOfMutexHolder, uxOriginalPriority )


/* Task is about to block because it cannot read from a
queue/mutex/semaphore.  pxQueue is a pointer to the queue/mutex/semaphore
upon which the read was attempted.  pxCurrentTCB points to the TCB of the
task that attempted the read. */
#define traceBLOCKING_ON_QUEUE_RECEIVE( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(BLOCKING_ON_QUEUE_RECEIVE);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}




/* Task is about to block because it cannot write to a
queue/mutex/semaphore.  pxQueue is a pointer to the queue/mutex/semaphore
upon which the write was attempted.  pxCurrentTCB points to the TCB of the
task that attempted the write. */
#define traceBLOCKING_ON_QUEUE_SEND( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(BLOCKING_ON_QUEUE_SEND);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}




#define configCHECK_FOR_STACK_OVERFLOW 0


/* The following event macros are embedded in the kernel API calls. */


#define traceMOVED_TASK_TO_READY_STATE( pxTCB ) {sendInformationStart;sendSystemTime; sendInformationID(MOVED_TASK_TO_READY_STATE);sendMessageLength(strlen(pxTCB->pcTaskName)); sendStringOverInterface(pxTCB->pcTaskName);}


#define tracePOST_MOVED_TASK_TO_READY_STATE( pxTCB )


#define traceQUEUE_CREATE( pxNewQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_CREATE);sendMessageLength(1); sendByteOverInterface(pxNewQueue->uxQueueNumber);}


#define traceQUEUE_CREATE_FAILED( ucQueueType ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_CREATE_FAILED);sendMessageLength(1); sendByteOverInterface((int)ucQueueType);}


#define traceCREATE_MUTEX( pxNewQueue ) {sendInformationStart;sendSystemTime; sendInformationID(CREATE_MUTEX);sendMessageLength(1); sendByteOverInterface(pxNewQueue->uxQueueNumber);}


#define traceCREATE_MUTEX_FAILED() {sendInformationStart;sendSystemTime; sendInformationID(CREATE_MUTEX_FAILED);sendMessageLength(1); sendByteOverInterface(' ');}


#define traceGIVE_MUTEX_RECURSIVE( pxMutex ) {sendInformationStart;sendSystemTime; sendInformationID(GIVE_MUTEX_RECURSIVE);sendMessageLength(1); sendByteOverInterface(pxMutex->uxQueueNumber);}



#define traceGIVE_MUTEX_RECURSIVE_FAILED( pxMutex ) {sendInformationStart;sendSystemTime; sendInformationID(GIVE_MUTEX_RECURSIVE_FAILED);sendMessageLength(1); sendByteOverInterface((int)pxMutex->ucQueueType);}



#define traceTAKE_MUTEX_RECURSIVE( pxMutex ) {sendInformationStart;sendSystemTime; sendInformationID(TAKE_MUTEX_RECURSIVE);sendMessageLength(1); sendByteOverInterface((int)pxMutex->ucQueueType);}



#define traceTAKE_MUTEX_RECURSIVE_FAILED( pxMutex ) {sendInformationStart;sendSystemTime; sendInformationID(TAKE_MUTEX_RECURSIVE_FAILED);sendMessageLength(1); sendByteOverInterface((int)pxMutex->ucQueueType);}



#define traceCREATE_COUNTING_SEMAPHORE() {sendInformationStart;sendSystemTime; sendInformationID(CREATE_COUNTING_SEMAPHORE);sendMessageLength(1); sendByteOverInterface(' ');}



#define traceCREATE_COUNTING_SEMAPHORE_FAILED() {sendInformationStart;sendSystemTime; sendInformationID(CREATE_COUNTING_SEMAPHORE_FAILED);sendMessageLength(1); sendByteOverInterface(' ');}



#define traceQUEUE_SEND( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_SEND);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}


#define traceQUEUE_SEND_FAILED( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_SEND_FAILED);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}


#define traceQUEUE_RECEIVE( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_RECEIVE);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}


#define traceQUEUE_PEEK( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_PEEK);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}



#define traceQUEUE_PEEK_FROM_ISR( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_PEEK_FROM_ISR);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}



#define traceQUEUE_RECEIVE_FAILED( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_RECEIVE_FAILED);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}



#define traceQUEUE_SEND_FROM_ISR( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_SEND_FROM_ISR);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}


#define traceQUEUE_SEND_FROM_ISR_FAILED( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_SEND_FROM_ISR_FAILED);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}



#define traceQUEUE_RECEIVE_FROM_ISR( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_RECEIVE_FROM_ISR);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}


#define traceQUEUE_RECEIVE_FROM_ISR_FAILED( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_RECEIVE_FROM_ISR_FAILED);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}



#define traceQUEUE_PEEK_FROM_ISR_FAILED( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_PEEK_FROM_ISR_FAILED);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}


#define traceQUEUE_DELETE( pxQueue ) {sendInformationStart;sendSystemTime; sendInformationID(QUEUE_DELETE);sendMessageLength(1); sendByteOverInterface((int)pxQueue->ucQueueType);}


#define traceTASK_CREATE( pxNewTCB ) {sendInformationStart;sendSystemTime; sendInformationID(TASK_CREATE);sendMessageLength(strlen(pxNewTCB->pcTaskName)+1); sendByteOverInterface(pxNewTCB->uxTCBNumber+0x30) sendStringOverInterface(pxNewTCB->pcTaskName);}



#define traceTASK_CREATE_FAILED() {sendInformationStart;sendSystemTime; sendInformationID(TASK_CREATE_FAILED);sendMessageLength(1); sendByteOverInterface(' ');}



#define traceTASK_DELETE( pxTaskToDelete ) {sendInformationStart;sendSystemTime; sendInformationID(TASK_DELETE);sendMessageLength(strlen(pxTaskToDelete->pcTaskName)); sendStringOverInterface(pxTaskToDelete->pcTaskName);}



#define traceTASK_DELAY_UNTIL( x ) {sendInformationStart;sendSystemTime; sendInformationID(TASK_DELAY_UNTIL);sendMessageLength(strlen(pxCurrentTCB->pcTaskName)); sendStringOverInterface(pxCurrentTCB->pcTaskName);}



#define traceTASK_DELAY() {sendInformationStart;sendSystemTime; sendInformationID(TASK_DELAY);sendMessageLength(strlen(pxCurrentTCB->pcTaskName)); sendStringOverInterface(pxCurrentTCB->pcTaskName);}



#define traceTASK_PRIORITY_SET( pxTask, uxNewPriority )



#define traceTASK_SUSPEND( pxTaskToSuspend ) {sendInformationStart;sendSystemTime; sendInformationID(TASK_SUSPEND);sendMessageLength(strlen(pxTaskToSuspend->pcTaskName)); sendStringOverInterface(pxTaskToSuspend->pcTaskName);}


#define traceTASK_RESUME( pxTaskToResume ) {sendInformationStart;sendSystemTime; sendInformationID(TASK_RESUME);sendMessageLength(strlen(pxTaskToResume->pcTaskName)); sendStringOverInterface(pxTaskToResume->pcTaskName);}



#define traceTASK_RESUME_FROM_ISR( pxTaskToResume ) {sendInformationStart;sendSystemTime; sendInformationID(TASK_RESUME_FROM_ISR);sendMessageLength(strlen(pxTaskToResume->pcTaskName)); sendStringOverInterface(pxTaskToResume->pcTaskName);}



#define traceTASK_INCREMENT_TICK( xTickCount ) {sendInformationStart;sendSystemTime; sendInformationID(TASK_INCREMENT_TICK);sendMessageLength(strlen("TI")); sendStringOverInterface("TI");}


//NOT IMPLEMENTED ANYMORE
#define traceTIMER_CREATE( pxNewTimer )


#define traceTIMER_CREATE_FAILED()



#define traceTIMER_COMMAND_SEND( xTimer, xMessageID, xMessageValueValue, xReturn )



#define traceTIMER_EXPIRED( pxTimer )



#define traceTIMER_COMMAND_RECEIVED( pxTimer, xMessageID, xMessageValue )



#define traceMALLOC( pvAddress, uiSize )



#define traceFREE( pvAddress, uiSize )



#define traceEVENT_GROUP_CREATE( xEventGroup )



#define traceEVENT_GROUP_CREATE_FAILED()



#define traceEVENT_GROUP_SYNC_BLOCK( xEventGroup, uxBitsToSet, uxBitsToWaitFor )



#define traceEVENT_GROUP_SYNC_END( xEventGroup, uxBitsToSet, uxBitsToWaitFor, xTimeoutOccurred ) ( void ) xTimeoutOccurred


#define traceEVENT_GROUP_WAIT_BITS_BLOCK( xEventGroup, uxBitsToWaitFor )



#define traceEVENT_GROUP_WAIT_BITS_END( xEventGroup, uxBitsToWaitFor, xTimeoutOccurred ) ( void ) xTimeoutOccurred



#define traceEVENT_GROUP_CLEAR_BITS( xEventGroup, uxBitsToClear )


#define traceEVENT_GROUP_CLEAR_BITS_FROM_ISR( xEventGroup, uxBitsToClear )



#define traceEVENT_GROUP_SET_BITS( xEventGroup, uxBitsToSet )


#define traceEVENT_GROUP_SET_BITS_FROM_ISR( xEventGroup, uxBitsToSet )


#define traceEVENT_GROUP_DELETE( xEventGroup )



#define tracePEND_FUNC_CALL(xFunctionToPend, pvParameter1, ulParameter2, ret)


#define tracePEND_FUNC_CALL_FROM_ISR(xFunctionToPend, pvParameter1, ulParameter2, ret)



#define traceQUEUE_REGISTRY_ADD(xQueue, pcQueueName)



#define traceTASK_NOTIFY_TAKE_BLOCK()



#define traceTASK_NOTIFY_TAKE()



#define traceTASK_NOTIFY_WAIT_BLOCK()



#define traceTASK_NOTIFY_WAIT()



#define traceTASK_NOTIFY()



#define traceTASK_NOTIFY_FROM_ISR()



#define traceTASK_NOTIFY_GIVE_FROM_ISR()


#endif


/* TRACESNIFFING_H_ */
