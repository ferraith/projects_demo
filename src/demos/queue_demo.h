// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef QUEUE_DEMO_H_
#define QUEUE_DEMO_H_

#include <cstddef>

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "types.h"

extern xQueueHandle queue_handle;

///
/// @brief         Demonstrates the usage of FreeRTOS queues with the help of two tasks transferring a counter
///
class QueueDemo {
 public:
  ///
  /// @brief         Constructor
  ///
  QueueDemo(xQueueHandle queue_handle);
  QueueDemo();
  ///
  /// @brief         Destructor
  ///
  virtual ~QueueDemo() {};
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
  /// Task handle referencing Task A
  xTaskHandle task_a_handle_;
  /// Task handle referencing Task B
  xTaskHandle task_b_handle_;

  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(QueueDemo);
};

#endif  // QUEUE_DEMO_H_
