// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "FreeRTOS.h"
#include "console.h"
#include "queue_demo.h"
#include "trimpot_demo.h"
#include "task.h"

xQueueHandle queue_handle;
QueueDemo *queue_demo;

///
///
///
void InitEcu(void) {
	// Initialize UART console
  Console console;
  console.Init();

	// Initialize ...
}

///
///
///
int main(void) {
	// Initialize ECU
	InitEcu();

	// Run queue demo
	queue_handle = xQueueCreate(10, sizeof(uint32_t));
	QueueDemo *queue_demo2 = new QueueDemo(); //(queue_handle);
	queue_demo = new QueueDemo[1050]; //(queue_handle);
	queue_demo->Run();

	// Run trimpot demo
	TrimpotDemo trimpot_demo;
	trimpot_demo.Run();

	// Start the tasks running
	vTaskStartScheduler();

	// If all is well this point will never be reached
	for(;;);
	return 0;
}
