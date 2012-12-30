// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef DEMOS_TRIMPOT_DEMO_H_
#define DEMOS_TRIMPOT_DEMO_H_

#include <stdint.h>

#include "FreeRTOS.h"
#include "class_helper.h"
#include "console.h"
#include "lpc17xx_uart.h"
#include "task.h"

using ::aoaa_board::Console;

namespace demo {

///
/// @brief         Provides methods to send and receive data to or from a console connected via UART to a
///                USB-to-UART bridge.
///
class TrimpotDemo {
 public:
  ///
  /// @brief         Constructor
  ///
  explicit TrimpotDemo(Console *console);
  ///
  ///
  ///
  void Task();
  ///
  ///
  ///
  void Run();

 private:
  ///
  Console *console_;
  ///
  xTaskHandle task_handle_;
  ///
  uint16_t current_value_;

  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(TrimpotDemo);
};

}  // namespace demo

#endif  // DEMOS_TRIMPOT_DEMO_H_
