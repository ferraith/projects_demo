// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef DEMOS_QUEUE_DEMO_H_
#define DEMOS_QUEUE_DEMO_H_

#include <stdint.h>
#include <cstddef>

#include "FreeRTOS.h"
#include "class_helper.h"
#include "console.h"
#include "queue.h"
#include "task.h"

using ::aoaa_board::Console;

namespace demo {

///
/// @brief         Demonstrates the usage of FreeRTOS queues with the help of two tasks transferring a counter
///
class QueueDemo {
 public:
  ///
  /// @brief         Constructor
  ///
  QueueDemo(xQueueHandle queue_handle, Console *console);
  ///
  /// @brief         Implementation of a FreeRTOS task receiving and sending a counter. This task starts sending the
  ///                counter
  /// @return        None
  ///
  void TaskA();
  ///
  /// @brief         Implementation of a FreeRTOS task receiving and sending a counter
  /// @return        None
  ///
  void TaskB();
  ///
  ///
  ///
  void Run();
  /// Queue handle referencing a queue containing the counter which is transfered between the two tasks
  xQueueHandle queue_handle_;

 private:
  /// Console
  Console *console_;
  /// Task handle referencing Task A
  xTaskHandle task_a_handle_;
  /// Task handle referencing Task B
  xTaskHandle task_b_handle_;
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(QueueDemo);
};

}  // namespace demo

#endif  // DEMOS_QUEUE_DEMO_H_
