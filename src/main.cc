// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "aoaa_board/console.h"
#include "demo/queue_demo.h"
#include "demo/trimpot_demo.h"

using ::aoaa_board::Console;
using ::demo::QueueDemo;
using ::demo::TrimpotDemo;

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
  QueueDemo queue_demo;
  queue_demo.Init(console);

  // Create trim-pot demo
  TrimpotDemo *trimpot_demo = new TrimpotDemo();
  trimpot_demo->Init(100, tskIDLE_PRIORITY + 1, console);

  // Start task scheduling
  vTaskStartScheduler();

  // Deinitialize ECU
  DeinitEcu(console);

  // Deinitialize and delete demos and their dependencies
  queue_demo.Deinit();
  trimpot_demo->Deinit();
  delete trimpot_demo;

  delete console;

  return 0;
}
