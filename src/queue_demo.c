/*
 * queue_demo.c
 *
 *  Created on: 13.12.2012
 *      Author: andreas
 */

#include "queue_demo.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "board.h"
#include "queue.h"
#include "task.h"

static xQueueHandle queue = NULL;

void TaskA(void *pvParameters) {
	portTickType last_wake_time;
	uint32_t counter = 0;
	int init = 1;
	char console_string[50];

	last_wake_time = xTaskGetTickCount();

	for(;;) {
		if(init == 1) {
			/* Initial send */
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
		xTaskCreate(TaskA, (const signed char *) "Task A", 100, NULL, (tskIDLE_PRIORITY + 1), NULL);
		xTaskCreate(TaskB, (const signed char *) "Task B", 100, NULL, (tskIDLE_PRIORITY + 1), NULL);
	}
}
