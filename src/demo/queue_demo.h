// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef DEMO_QUEUE_DEMO_H_
#define DEMO_QUEUE_DEMO_H_

#include "common/class_helper.h"

namespace aoaa_board {
class Console;
}

namespace demo {
class QueueReceiver;
class QueueSender;
}

namespace freertos {
class QueueWrapper;
}

using aoaa_board::Console;
using freertos::QueueWrapper;

namespace demo {

///
/// @brief         Demonstrates the usage of FreeRTOS queues with the help of two tasks transferring a counter.
///
class QueueDemo {
 public:
  ///
  /// @brief         Constructor.
  ///
  explicit QueueDemo();
  ///
  /// @brief         Creates and initializes the queue, sender and receiver task.
  /// @param[in]     Console
  /// @return        None
  ///
  bool Init(Console *console);
  ///
  /// @brief         Deinitializes and deletes the queue, sender and receiver task.
  /// @return        None
  ///
  void Deinit();

 private:
  /// Queue to communicate between a sender and receiver task
  QueueWrapper *queue_;
  /// Receiver task which receives periodically a value
  QueueReceiver *receiver_;
  /// Sender task which sends periodically a value
  QueueSender *sender_;
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(QueueDemo);
};

}  // namespace demo

#endif  // DEMO_QUEUE_DEMO_H_
