// Copyright (C) ferraith. All rights reserved.

///
/// @brief  FreeRTOS queue demo
/// @author ferraith
///

#include "queue_demo.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "board.h"
#include "queue.h"
#include "task.h"

#define TASK_STACK_SIZE 160

/// FreeRTOS queue containing the counter which is transfered between the two tasks.
static xQueueHandle queue = NULL;

///
/// @brief      Implementation of a FreeRTOS task receiving and sending a counter. This task starts sending the counter.
/// @param[in]  Parameters of this task
/// @return     None
///
void TaskA(void *pvParameters) {
	portTickType last_wake_time;
	uint32_t counter = 0;
	int init = 1;
	char console_string[50];

	last_wake_time = xTaskGetTickCount();

	for(;;) {
		if(init == 1) {
			// Initial send
			xQueueSend(queue, &counter, 0);
			init = 0;
		} else {
			uint32_t temp;
			xQueueReceive(queue, &counter, portMAX_DELAY);
			temp = counter;
			counter++;
			sprintf(console_string, "Task A: Received %d\t Will Send %d\r\n", temp, counter);
			xQueueSend(queue, &counter, 0);
			console_sendString((uint8_t*)console_string);
		}
		vTaskDelayUntil(&last_wake_time, 100 * configTICK_RATE_HZ / 1000);
	}
	vTaskDelete(NULL);
}

///
/// @brief      Implementation of a FreeRTOS task receiving and sending a counter.
/// @param[in]  Parameters of this task
/// @return     None
///
void TaskB(void *pvParameters) {
	portTickType last_wake_time;
	vTaskDelay(50 * configTICK_RATE_HZ / 1000);
	last_wake_time = xTaskGetTickCount();
	uint32_t counter = 0;
	char console_string[50];

	for(;;) {
		uint32_t temp;
		xQueueReceive(queue, &counter, portMAX_DELAY);
		temp = counter;
		counter++;
		sprintf(console_string, "Task B: Received %d\t Will Send %d\r\n", temp, counter);
		xQueueSend(queue, &counter, 0);
		console_sendString((uint8_t*)console_string);

		vTaskDelayUntil(&last_wake_time, 100 * configTICK_RATE_HZ / 1000);
	}
	vTaskDelete(NULL);
}


void run_queue_demo(void) {
	queue = xQueueCreate(1, sizeof(uint32_t));

	if(queue != NULL) {
		xTaskCreate(TaskA, (const signed char *) "Task A", TASK_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1), NULL);
		xTaskCreate(TaskB, (const signed char *) "Task B", TASK_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1), NULL);
	}
}
