// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef TRIMPOT_DEMO_H_
#define TRIMPOT_DEMO_H_

#include "types.h"
#include "FreeRTOS.h"
#include "task.h"
#include "lpc17xx_uart.h"

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
  /// @brief         Destructor
  ///
  virtual ~TrimpotDemo() {}
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

#endif  // TRIMPOT_DEMO_H_
