// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef DEMOS_TRIMPOT_DEMO_H_
#define DEMOS_TRIMPOT_DEMO_H_

#include "types.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lpc17xx_uart.h"

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
  TrimpotDemo();
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
  xTaskHandle task_handle_;
  ///
  uint16_t current_value_;

  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(TrimpotDemo);
};

}  // namespace demo

#endif  // DEMOS_TRIMPOT_DEMO_H_
