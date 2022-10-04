#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include <semphr.h>
#include <stdbool.h>

/* Priorities at which the tasks are created. */
#define TASK_1_PRIORITY			( tskIDLE_PRIORITY + 1 )
#define	TASK_2_PRIORITY			( tskIDLE_PRIORITY + 2 )
#define TASK_3_PRIORITY			( tskIDLE_PRIORITY + 3 )
/* Task stack sizes*/
#define TASK_1_TASK_STACK	( configMINIMAL_STACK_SIZE )
#define	TASK_2_TASK_STACK	( configMINIMAL_STACK_SIZE )
#define TASK_3_TASK_STACK	( configMINIMAL_STACK_SIZE )

/* Task Handles */
TaskHandle_t _taskSecondHandle = NULL;
SemaphoreHandle_t syncSemaphore = NULL;

// --------------------------------------------------------------------------------------
void taskMyTask(void* pvParameters)
{
	// Remove compiler warnings.
	(void)pvParameters;

	
	for (;;)
	{
		if(xSemaphoreTake(syncSemaphore,pdMS_TO_TICKS(5)))
		{
			puts("R");
			vTaskDelay(100);
		}else
		{
			puts("OK1");
			xSemaphoreGive(syncSemaphore);
		}
	}
}

// --------------------------------------------------------------------------------------
void taskMySeccondTask(void* pvParameters)
{
	// Remove compiler warnings.
	(void)pvParameters;

	for (;;)
	{
		if(xSemaphoreTake(syncSemaphore,pdMS_TO_TICKS(5)))
		{
			puts("I");
			vTaskDelay(100);
		}else
		{
			puts("OK2");
			xSemaphoreGive(syncSemaphore);
		}
	}
}

// --------------------------------------------------------------------------------------
void taskMyThirdTask(void* pvParameters)
{
	// Remove compiler warnings.
	(void)pvParameters;

	for (;;)
	{
		
		if(xSemaphoreTake(syncSemaphore,pdMS_TO_TICKS(5)))
		{
			puts("O");
			vTaskDelay(100);
		}else
		{
			puts("OK3");
			xSemaphoreGive(syncSemaphore);
		}
	}
}

// --------------------------------------------------------------------------------------
void main(void)
{
	syncSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(syncSemaphore);
	/* Create the task, not storing the handle. */
	xTaskCreate(
		taskMyTask,       /* Function that implements the task. */
		"MyTask",          /* Text name for the task. */
		TASK_1_TASK_STACK,      /* Stack size in words, not bytes. */
		(void*)1,    /* Parameter passed into the task. */
		TASK_1_PRIORITY,/* Priority at which the task is created. */
		&_taskSecondHandle);      /* Used to pass out the created task's handle. */

		/* Create the task, storing the handle. */
	xTaskCreate(
		taskMySeccondTask,       /* Function that implements the task. */
		"MySecondTask",          /* Text name for the task. */
		TASK_2_TASK_STACK,      /* Stack size in words, not bytes. */
		(void*)2,    /* Parameter passed into the task. */
		TASK_2_PRIORITY,/* Priority at which the task is created. */
		&_taskSecondHandle);      /* Used to pass out the created task's handle. */

	xTaskCreate(
		taskMyThirdTask,       /* Function that implements the task. */
		"MyThirdTask",          /* Text name for the task. */
		TASK_3_TASK_STACK,      /* Stack size in words, not bytes. */
		(void*)2,    /* Parameter passed into the task. */
		TASK_3_PRIORITY,/* Priority at which the task is created. */
		&_taskSecondHandle);      /* Used to pass out the created task's handle. */
	
	// Let the operating system take over :)
	vTaskStartScheduler();
}