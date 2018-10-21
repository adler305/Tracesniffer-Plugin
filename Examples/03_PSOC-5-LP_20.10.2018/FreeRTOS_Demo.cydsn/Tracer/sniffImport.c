/** \file sniffImport.c
 * \brief sniffImport source file.
 * \details Implements the functions used for initialising the Tracer.
 * \author Jonas Mair
 * \date 2018
 */

#include <string.h>
#include <sniffImport.h>

typedef void* TaskHandle_t;
static TaskHandle_t sniffTaskHandle = NULL;
extern long xTaskCreate();
extern void vTaskSuspend(TaskHandle_t xTaskToSuspend);

uint8_t initialiseTraceSniffer() {
	initialiseFIFO();
	initialiseObjectList();
	enableReceiveInterrupt();
	memset(sniffIDFilter, 0xff, sizeof(uint8_t) * SIZE_OF_FILTER);
	//memset(sniffIDFilter, 0xffffffff, sizeof(uint32_t) * 4);
	//memset(&sniffIDFilter[5],0xff,1);
	//memset(&sniffIDFilter[5],~(1<<4),1);

#if WAIT_FOR_SNIFFER_START
	uint8_t* data;
	payloadType* type;
	while(readReceiveFIFO(data,type)!=0);
#endif
	xTaskCreate(sniffTask, "sniffTask", STACK_SIZE_OF_SNIFF_TASK, NULL,
	PRIORITY_OF_SNIFF_TASK, &sniffTaskHandle);
	//Create Task
	return 0;
}
void stopTraceSniffer() {
	vTaskSuspend(sniffTaskHandle);
	//memset(sniffIDFilter, 0x00, sizeof(uint8_t) * SIZE_OF_FILTER);
}

