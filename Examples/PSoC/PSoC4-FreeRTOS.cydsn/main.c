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
//xSemaphoreHandle triggerSemaphore;//
xSemaphoreHandle lcdMutex;
xSemaphoreHandle buttonSemaphore;

void TempReadTask(); // The temperature will be read every 2secs and displayed/written in a Queue towards the data Capture Task
void HumidityReadTask(); // The humidity will be read every 2secs and displayed/written in a Queue towards the data Capture Task
void dataCaptureTask();// The data will be saved in this task

int readTemp();    //Reads the temp // Displayed with flashing of LED3
int readHumidity(); //Reads the temp // Displayed with flashing of LED3
void writeToLCD(); // The LCD is a shared resource// It takes 500ms to write to the LCD // Displayed with LED1
void saveData(); //Data is saved // Displayed by LED2

xTaskHandle blinkTask;

void vBlinkTask( void* pvParameters);
void newTraceRxHandler(void);

CY_ISR_PROTO(Button_ISR_Handler);
CY_ISR(Button_ISR_Handler) {
    TRACE_UART_UartPutChar('a');
    xSemaphoreGiveFromISR(buttonSemaphore, 0);
    Button_ISR_ClearPending();
}

int main()
{
    /* Connect ISR Handler */
    Button_ISR_StartEx(Button_ISR_Handler);
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	initialiseTraceSniffer();
    
    /* Start EZI2C Component */
    EZI2C_Start();
    /* Set up communication and initialize data buffer to CapSense data structure*  to use Tuner application */
    EZI2C_EzI2CSetBuffer1(sizeof(CapSense_Trace_dsRam), sizeof(CapSense_Trace_dsRam), (uint8_t*)&(CapSense_Trace_dsRam));
    
    /* CapSense */
    CapSense_Trace_Start();
    CapSense_Trace_InitializeAllBaselines();
    
    infoQueueHandle = xQueueCreate(10,sizeof(int)); 

    lcdMutex=xSemaphoreCreateMutex();
    buttonSemaphore=xSemaphoreCreateMutex();
    //triggerSemaphore=xSemaphoreCreateCounting(5,0);

    xTaskCreate(TempReadTask,"temp",configMINIMAL_STACK_SIZE,NULL,2,&TempReadTaskHandle);

    xTaskCreate(HumidityReadTask,"humid",configMINIMAL_STACK_SIZE,NULL,3,&HumidityReadTaskHandle);

    xTaskCreate(dataCaptureTask,"data",configMINIMAL_STACK_SIZE,NULL,4,&dataCaptureTaskHandle);
    
	xTaskCreate(vBlinkTask,"blink",configMINIMAL_STACK_SIZE,NULL,0,&blinkTask);
    TRACE_UART_SetCustomInterruptHandler(&newTraceRxHandler);
    Test_LED_Write(1);
	FreeRTOS_Start();
	
    for(;;);
}

void newTraceRxHandler(void) {
    if(TRACE_UART_CHECK_INTR_RX_MASKED(TRACE_UART_INTR_RX_NOT_EMPTY)) {
        uint8_t a = TRACE_UART_UartGetByte();
        sendReceivedByteToSniffTask(a);
        TRACE_UART_ClearRxInterruptSource(TRACE_UART_INTR_RX_NOT_EMPTY);
    }
}

void vBlinkTask( void* pvParameters)
{
	for(;;) {
        
		vTaskDelay( 125/portTICK_RATE_MS );
        
        /*
        if(xSemaphoreTake(buttonSemaphore, portMAX_DELAY)) {
            Test_LED_Write( ~Test_LED_Read() );
        }
        */
        Test_LED_Write( ~Test_LED_Read() );
        /*
        if(CapSense_Trace_NOT_BUSY == CapSense_Trace_IsBusy()) {
            if(CapSense_Trace_IsAnyWidgetActive()) {
                CAP_LED_Write(1);
            }
            else {
                CAP_LED_Write(0);
            }
            CapSense_Trace_ScanAllWidgets();
        }
        */
    }
}


int readTemp()    //Reads the temp // Displayed with flashing of LED3
{
    Temp_LED_Write(0);
	CyDelay(40);
    Temp_LED_Write(1);
	return 0;
}
int readHumidity() //Reads the humidity // Displayed with flashing of LED3
{
    Humid_LED_Write(0);
	CyDelay(30);
    Humid_LED_Write(1);
	return 0;
}

void writeToLCD() // The LCD is a shared resource// It takes 500ms to write to the LCD // Displayed with LED1
{
    LCD_LED_Write(0);
	CyDelay(45);
    LCD_LED_Write(1);
}

void saveData() //Data is saved // Displayed by LED2
{
    Data_LED_Write(0);
	CyDelay(60);
    Data_LED_Write(1);
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
