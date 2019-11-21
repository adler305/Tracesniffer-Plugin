/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdlib.h>

xTaskHandle TempReadTaskHandle;
xTaskHandle HumidityReadTaskHandle;
xTaskHandle dataCaptureTaskHandle;

xQueueHandle infoQueueHandle;
xSemaphoreHandle triggerSemaphore;//
xSemaphoreHandle lcdMutex;

void TempReadTask(); // The temperature will be read every 2secs and displayed/written in a Queue towards the data Capture Task
void HumidityReadTask(); // The humidity will be read every 2secs and displayed/written in a Queue towards the data Capture Task
void dataCaptureTask();// The data will be saved in this task

int readTemp();    //Reads the temp // Displayed with flashing of LED3
int readHumidity(); //Reads the temp // Displayed with flashing of LED3
void writeToLCD(); // The LCD is a shared resource// It takes 500ms to write to the LCD // Displayed with LED1
void saveData(); //Data is saved // Displayed by LED2

xTaskHandle blinkTask;

void vBlinkTask( void* pvParameters);


CY_ISR(TRACE_UART_RX_Handler) {
   uint8_t a = TRACE_UART_GetByte();
   sendReceivedByteToSniffTask(a);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	initialiseTraceSniffer();
    
    infoQueueHandle = xQueueCreate(10,sizeof(int)); 
    lcdMutex=xSemaphoreCreateMutex();
    triggerSemaphore=xSemaphoreCreateCounting(5,0);

    xTaskCreate(TempReadTask,"temp",configMINIMAL_STACK_SIZE,NULL,1,&TempReadTaskHandle);

    xTaskCreate(HumidityReadTask,"humid",configMINIMAL_STACK_SIZE,NULL,2,&HumidityReadTaskHandle);

    xTaskCreate(dataCaptureTask,"data",configMINIMAL_STACK_SIZE,NULL,3,&dataCaptureTaskHandle);
    
	xTaskCreate(vBlinkTask,"blink",configMINIMAL_STACK_SIZE,NULL,0,&blinkTask);
    
    Test_LED_Write(1);
    TRACE_UART_RX_ISR_StartEx(TRACE_UART_RX_Handler);
	FreeRTOS_Start();
	
    for(;;);
}

void vBlinkTask( void* pvParameters)
{
	for(;;) {
		vTaskDelay( 125/portTICK_RATE_MS );
		Test_LED_Write( ~Test_LED_Read() );
	}
}


int readTemp()    //Reads the temp // Displayed with flashing of LED3
{

	CyDelay(50);

	return rand();
}
int readHumidity() //Reads the humidity // Displayed with flashing of LED3
{

	CyDelay(50);

	return rand();
}

void writeToLCD() // The LCD is a shared resource// It takes 500ms to write to the LCD // Displayed with LED1
{
	
	CyDelay(40);
	
	CyDelay(50);
}

void saveData() //Data is saved // Displayed by LED2
{

	CyDelay(100);

}


void TempReadTask()
{
	TickType_t lastwoken;
	lastwoken = xTaskGetTickCount();
	int temp;
//	traceCUSTOM_MARKER_1();
	while(1)
	{
		vTaskDelayUntil(&lastwoken,2000);
		temp=readTemp();
		xQueueSend(infoQueueHandle,&temp,portMAX_DELAY);
		if(xSemaphoreTake(lcdMutex,portMAX_DELAY)){
			writeToLCD();
			xSemaphoreGive(lcdMutex);
		}

	}
}
void HumidityReadTask()
{
	TickType_t lastwoken;
	lastwoken = xTaskGetTickCount();
	int humidity;
//	traceCUSTOM_MARKER_2();
	while(1)
	{
		vTaskDelayUntil(&lastwoken,2000);

		//writeFIFO(sniffFifo,&humidity,4,prioRECEIVE);
		//sendObjectList();


		humidity=readHumidity();
		xQueueSend(infoQueueHandle,&humidity,portMAX_DELAY);
		if(xSemaphoreTake(lcdMutex,portMAX_DELAY)){
			writeToLCD();
			xSemaphoreGive(lcdMutex);
		}
	}
}
void dataCaptureTask()
{
	int info;
//	traceCUSTOM_MARKER_3();
	while(1)
	{
		xQueueReceive(infoQueueHandle,&info,portMAX_DELAY);
		saveData();
	}
}
/* [] END OF FILE */
