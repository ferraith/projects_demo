// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "aoaa_board/console.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/port/task_wrapper.h"
#include "demo/queue_demo.h"
#include "demo/trimpot_demo.h"

using ::demo::QueueDemo;
using ::demo::TrimpotDemo;
using ::aoaa_board::Console;

///
/// @brief         Initialize peripherals of microcontroller and board.
/// @param[in]     console  Console to send and receive data to external devices
/// @return        True if peripherals were successfully initialized
///
bool InitEcu(Console *console) {
  // Initialize UART console
  return console->Init(921600, UART_DATABIT_8, UART_PARITY_NONE, UART_STOPBIT_1);
}

///
/// @brief         Deinitialize peripherals of microcontroller and board.
/// @param[in]     console  Console to send and receive data to external devices
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

  // Create queue demo
  xQueueHandle queue_handle = xQueueCreate(1, sizeof(uint32_t));
  QueueDemo *queue_demo = new QueueDemo(queue_handle, console);
  queue_demo->Run();

  // Create trimpot demo
  TrimpotDemo *trimpot_demo = new TrimpotDemo();
  trimpot_demo->Init(100, tskIDLE_PRIORITY + 1, console);

  // Start task scheduling
  vTaskStartScheduler();

  // Deinitialize ECU
  DeinitEcu(console);

  // Delete demos and their dependencies
  delete queue_demo;
  trimpot_demo->Deinit();
  delete trimpot_demo;

  delete console;
  vQueueDelete(queue_handle);

  return 0;
}
