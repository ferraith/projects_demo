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
/// @return        True if peripherals were successfully initialized
///
bool InitEcu(Console *console) {
  // Initialize UART console
  return console->Init(921600, UART_DATABIT_8, UART_PARITY_NONE, UART_STOPBIT_1);
}

///
/// @brief         Deinitialize peripherals of microcontroller and board.
/// @return        None
///
void DeinitEcu(Console *console) {
  // Deinitialize UART console
  console->Deinit();
}

///
/// @brief         Entry point of program execution.
/// @return        Exit status
///
int main() {
  Console *console = new Console();

  // Initialize ECU
  InitEcu(console);

  // Run queue demo
  xQueueHandle queue_handle = xQueueCreate(1, sizeof(uint32_t));
  QueueDemo *queue_demo = new QueueDemo(queue_handle, console);
  queue_demo->Run();

  // Run trimpot demo
  TrimpotDemo *trimpot_demo = new TrimpotDemo(console);
  trimpot_demo->Run();

  // Start task scheduling
  vTaskStartScheduler();

  // Deinitialize ECU
  DeinitEcu(console);

  // Delete demos
  delete queue_demo;
  vQueueDelete(queue_handle);
  delete trimpot_demo;
  delete console;

  // If all is well this point will never be reached
  for(;;);

  return 0;
}
