/** \file sniffHooks.h
 * \brief sniffHook header file.
 * \details Defines all the build-in hooks for a FreeRTOS-System.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFHOOKS_H_
#define SNIFFHOOKS_H_

#include <stdint.h>
#include <sniffPayload.h>

	//	UBaseType_t uxQueueNumber;
	//	uint8_t ucQueueType;

	//	UBaseType_t		uxTCBNumber;		/*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
	//	UBaseType_t		uxTaskNumber;		/*< Stores a number specifically for use by third party trace code. */
//Hooks
#define traceSTART() /**< Use for all necessary initialization.*/

/* Use to close a trace, for example close a file into which trace has been
 written. */
#define traceEND() /**< Use for all necessary deinitialization.*/
//
#define traceCUSTOM_MARKER_1()/**< Custom Marker for use everywhere, for example in an interrupt.*/

#define traceCUSTOM_MARKER_2()/**< Custom Marker for use everywhere, for example in an interrupt.*/

#define traceCUSTOM_MARKER_3()/**< Custom Marker for use everywhere, for example in an interrupt.*/

#define traceCUSTOM_MARKER_4()/**< Custom Marker for use everywhere, for example in an interrupt.*/

#define traceCUSTOM_MARKER_5()/**< Custom Marker for use everywhere, for example in an interrupt.*/

/* Called after a task has been selected to run.  pxCurrentTCB holds a pointer
 to the task control block of the selected task. */

#define traceTASK_SWITCHED_IN() {packPayload1(ID_TASK_SWITCHED_IN,pxCurrentTCB->uxTaskNumber);}/**< Traces if a task gets switched in and sends the task number.*/
/* Called before stepping the tick count after waking from tickless idle
 sleep. */
#define traceINCREASE_TICK_COUNT( x ) {packPayload1(ID_INCREASE_TICK_COUNT,x);} /**< Traces the tick amount increase after a tickless idle sleep.*/

/* Called immediately before entering tickless idle. */
#define traceLOW_POWER_IDLE_BEGIN() {packPayload0(ID_LOW_POWER_IDLE_BEGIN);} /**< Traces the begin of an idle sleep.*/

/* Called when returning to the Idle task after a tickless idle. */
#define traceLOW_POWER_IDLE_END() /**< Traces the end of an idle sleep.*/ {packPayload0(ID_LOW_POWER_IDLE_END);}
//TODO add doxy comments next task switched out
/* Called before a task has been selected to run.  pxCurrentTCB holds a pointer
 to the task control block of the task being switched out. */
#define traceTASK_SWITCHED_OUT() {packPayload1(ID_TASK_SWITCHED_OUT,pxCurrentTCB->uxTaskNumber);}
/* Called when a task attempts to take a mutex that is already held by a
 lower priority task.  pxTCBOfMutexHolder is a pointer to the TCB of the task
 that holds the mutex.  uxInheritedPriority is the priority the mutex holder
 will inherit (the priority of the task that is attempting to obtain the
 muted. */
#define traceTASK_PRIORITY_INHERIT( pxTCBOfMutexHolder, uxInheritedPriority ) {packPayload2(ID_TASK_PRIORITY_INHERIT,pxTCBOfMutexHolder->uxTaskNumber,uxInheritedPriority);}

/* Called when a task releases a mutex, the holding of which had resulted in
 the task inheriting the priority of a higher priority task.
 pxTCBOfMutexHolder is a pointer to the TCB of the task that is releasing the
 mutex.  uxOriginalPriority is the task's configured (base) priority. */
#define traceTASK_PRIORITY_DISINHERIT( pxTCBOfMutexHolder, uxOriginalPriority ) {packPayload2(ID_TASK_PRIORITY_DISINHERIT,pxTCBOfMutexHolder->uxTaskNumber,uxOriginalPriority);}

/* Task is about to block because it cannot read from a
 queue/mutex/semaphore.  pxQueue is a pointer to the queue/mutex/semaphore
 upon which the read was attempted.  pxCurrentTCB points to the TCB of the
 task that attempted the read. */
#define traceBLOCKING_ON_QUEUE_RECEIVE( pxQueue ) {packPayload2(ID_BLOCKING_ON_QUEUE_RECEIVE,(int)pxQueue->ucQueueType,pxQueue->uxQueueNumber);}
/* Task is about to block because it cannot write to a
 queue/mutex/semaphore.  pxQueue is a pointer to the queue/mutex/semaphore
 upon which the write was attempted.  pxCurrentTCB points to the TCB of the
 task that attempted the write. */
#define traceBLOCKING_ON_QUEUE_SEND( pxQueue ) {packPayload2(ID_BLOCKING_ON_QUEUE_SEND,(int)pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

//#define configCHECK_FOR_STACK_OVERFLOW 0

/* The following event macros are embedded in the kernel API calls. */

#define traceMOVED_TASK_TO_READY_STATE( pxTCB ) {packPayload1(ID_MOVED_TASK_TO_READY_STATE,pxTCB->uxTaskNumber);}

#define tracePOST_MOVED_TASK_TO_READY_STATE( pxTCB ) {packPayload1(ID_POST_MOVED_TASK_TO_READY_STATE,pxTCB->uxTaskNumber);}

#define traceQUEUE_CREATE( pxNewQueue ) {pxNewQueue->uxQueueNumber = updateObjectList(pxNewQueue->ucQueueType,"Queue"); packPayload1(ID_QUEUE_CREATE,pxNewQueue->uxQueueNumber);}

#define traceQUEUE_CREATE_FAILED( ucQueueType ) {packPayload1(ID_QUEUE_CREATE_FAILED,ucQueueType);}

#define traceCREATE_MUTEX( pxNewQueue ) {packPayload1(ID_CREATE_MUTEX,pxNewQueue->uxQueueNumber);}//ObjectListUpdate gets called in the nested QUEUE_CREATE

#define traceCREATE_MUTEX_FAILED() {packPayload0(ID_CREATE_MUTEX_FAILED);}

#define traceGIVE_MUTEX_RECURSIVE( pxMutex ) {packPayload2(ID_GIVE_MUTEX_RECURSIVE,(int)pxMutex->ucQueueType,pxMutex->uxQueueNumber);}

#define traceGIVE_MUTEX_RECURSIVE_FAILED( pxMutex ) {packPayload2(ID_GIVE_MUTEX_RECURSIVE_FAILED,(int)pxMutex->ucQueueType,pxMutex->uxQueueNumber);}

#define traceTAKE_MUTEX_RECURSIVE( pxMutex ) {packPayload2(ID_TAKE_MUTEX_RECURSIVE,(int)pxMutex->ucQueueType,pxMutex->uxQueueNumber);}

#define traceTAKE_MUTEX_RECURSIVE_FAILED( pxMutex ) {packPayload2(ID_TAKE_MUTEX_RECURSIVE_FAILED,(int)pxMutex->ucQueueType,pxMutex->uxQueueNumber);}

#define traceCREATE_COUNTING_SEMAPHORE() {packPayload0(ID_CREATE_COUNTING_SEMAPHORE);} //ObjectListUpdate gets called in the nested QUEUE_CREATE

#define traceCREATE_COUNTING_SEMAPHORE_FAILED() {packPayload0(ID_CREATE_COUNTING_SEMAPHORE_FAILED);}

#define traceQUEUE_SEND( pxQueue ) {packPayload2(ID_QUEUE_SEND,(int)pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_SEND_FAILED( pxQueue ) {packPayload2(ID_QUEUE_SEND_FAILED,(int)pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_RECEIVE( pxQueue ) {packPayload2(ID_QUEUE_RECEIVE,pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_PEEK( pxQueue ) {packPayload2(ID_QUEUE_PEEK,(int)pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_PEEK_FROM_ISR( pxQueue ) {packPayload2(ID_QUEUE_PEEK_FROM_ISR,pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_RECEIVE_FAILED( pxQueue ) {packPayload2(ID_QUEUE_RECEIVE_FAILED,pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_SEND_FROM_ISR( pxQueue ) {packPayload2(ID_QUEUE_SEND_FROM_ISR,pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_SEND_FROM_ISR_FAILED( pxQueue ) {packPayload2(ID_QUEUE_SEND_FROM_ISR_FAILED,pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_RECEIVE_FROM_ISR( pxQueue ) {packPayload2(ID_QUEUE_RECEIVE_FROM_ISR,pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_RECEIVE_FROM_ISR_FAILED( pxQueue ) {packPayload2(ID_QUEUE_RECEIVE_FROM_ISR_FAILED,pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_PEEK_FROM_ISR_FAILED( pxQueue ) {packPayload2(ID_QUEUE_PEEK_FROM_ISR_FAILED,pxQueue->ucQueueType,pxQueue->uxQueueNumber);}

#define traceQUEUE_DELETE( pxQueue )  {objectList[pxQueue->ucQueueType].objectArray[pxQueue->uxQueueNumber].objectNumber = 0; packPayload0(ID_QUEUE_DELETE);}

#define traceTASK_CREATE( pxNewTCB ) {pxNewTCB->uxTaskNumber = updateObjectList(TASK,pxNewTCB->pcTaskName); packPayload1(ID_TASK_CREATE,pxNewTCB->uxTaskNumber);}

#define traceTASK_CREATE_FAILED() {packPayload0(ID_TASK_CREATE_FAILED);}

#define traceTASK_DELETE( pxTaskToDelete ) {objectList[TASK].objectArray[pxTaskToDelete->uxTaskNumber].objectNumber = 0;packPayload1(ID_TASK_DELETE,pxTaskToDelete->uxTaskNumber);}

#define traceTASK_DELAY_UNTIL( x ) {packPayload3(ID_TASK_DELAY_UNTIL,pxCurrentTCB->uxTaskNumber,xTimeIncrement>>8,xTimeIncrement);}

#define traceTASK_DELAY() {packPayload3(ID_TASK_DELAY,pxCurrentTCB->uxTaskNumber,xTicksToDelay>>8,xTicksToDelay);}

#define traceTASK_PRIORITY_SET( pxTask, uxNewPriority ) {packPayload2(ID_TASK_PRIORITY_SET,pxTask->uxTaskNumber,uxNewPriority);}

#define traceTASK_SUSPEND( pxTaskToSuspend ) {packPayload1(ID_TASK_SUSPEND,pxTaskToSuspend->uxTaskNumber);}

#define traceTASK_RESUME( pxTaskToResume ) {packPayload1(ID_TASK_RESUME,pxTaskToResume->uxTaskNumber);}

#define traceTASK_RESUME_FROM_ISR( pxTaskToResume ) {packPayload1(ID_TASK_RESUME_FROM_ISR,pxTaskToResume->uxTaskNumber);}

#define traceTASK_INCREMENT_TICK( xTickCount ) {packPayload0(ID_TASK_INCREMENT_TICK);}

#define traceMALLOC( pvAddress, uiSize ) {packPayload2(ID_MALLOC,uiSize>>8,uiSize);}

#define traceFREE( pvAddress, uiSize ) {packPayload2(ID_FREE,uiSize>>8,uiSize);}



/*
//NOT IMPLEMENTED ANYMORE
#define traceTIMER_CREATE( pxNewTimer )

#define traceTIMER_CREATE_FAILED()

#define traceTIMER_COMMAND_SEND( xTimer, xMessageID, xMessageValueValue, xReturn )

#define traceTIMER_EXPIRED( pxTimer )

#define traceTIMER_COMMAND_RECEIVED( pxTimer, xMessageID, xMessageValue )


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
*/



#endif /* SNIFFHOOKS_H_ */
