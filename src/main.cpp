// Copyright (C) ferraith. All rights reserved.

///
/// @brief Demo project main module
/// @author ferraith
///

#include "FreeRTOS.h"
#include "console.h"
#include "queue_demo.h"
#include "task.h"

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
	RunQueueDemo();

	// Start the tasks running
	vTaskStartScheduler();

	// If all is well this point will never be reached
	for(;;);
	return 0;
}
