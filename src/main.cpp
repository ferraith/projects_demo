// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "FreeRTOS.h"
#include "console.h"
#include "queue.h"
#include "queue_demo.h"
#include "trimpot_demo.h"
#include "task.h"

using ::demo::QueueDemo;
using ::demo::TrimpotDemo;
using ::aoaa_board::Console;

///
/// @brief         Initialize peripherals of microcontroller and board.
/// @return        None
///
void InitEcu() {
  // Initialize UART console
  Console console;
  console.Init();

  // Initialize ...
}


///
/// @brief         Entry point of program execution.
/// @return        None
///
int main() {

  // Initialize ECU
  InitEcu();

  // Run queue demo
  xQueueHandle queue_handle = xQueueCreate(1, sizeof(uint32_t));
  QueueDemo *queue_demo = new QueueDemo(queue_handle);
  queue_demo->Run();

  // Run trimpot demo
  TrimpotDemo *trimpot_demo = new TrimpotDemo();
  trimpot_demo->Run();

  // Start task scheduling
  vTaskStartScheduler();

  // Delete demos
  delete queue_demo;
  vQueueDelete(queue_handle);
  delete trimpot_demo;

  // If all is well this point will never be reached
  for(;;);

  return 0;
}
