// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef DEMO_QUEUE_RECEIVER_H_
#define DEMO_QUEUE_RECEIVER_H_

#include <stdint.h>

#include "common/class_helper.h"
#include "freertos/port/task_wrapper.h"

namespace aoaa_board {
  class Console;
}

namespace freertos {
  class QueueWrapper;
}

using ::aoaa_board::Console;
using ::freertos::QueueWrapper;
using ::freertos::TaskWrapper;

namespace demo {

///
/// @brief         A task which receives periodically values from queue.
///
class QueueReceiver : public TaskWrapper {
 public:
  ///
  /// @brief         Constructor.
  /// @param[in]     queue  Queue to communicate between a sender and receiver task.
  ///
  explicit QueueReceiver(QueueWrapper *queue);
  ///
  /// @brief         Destructor.
  ///
  ~QueueReceiver() {}

  ///
  /// @brief         Removes the queue receiver task from the list of tasks that are ready to run.
  /// @return        None
  ///
  void Deinit();
  ///
  /// @brief         Creates the queue receiver task and add it to the list of tasks that are ready to run.
  /// @param[in]     execution_cycle  Cycle time in milliseconds in which the task will be executed periodically.
  /// @param[in]     priority  Priority at which the task should run.
  /// @param[in]     console  The console to display debug information.
  /// @return        True if the task was successfully created and added to a ready list.
  ///
  bool Init(uint16_t execution_cycle, uint8_t priority, Console *console);
  ///
  /// @brief         Will be executed in task context and receives periodically a value. The value will be printed on
  ///                the console.
  /// @return        None
  ///
  void Run();

 private:
  /// Reference to the console which is used for printing debug messages
  Console *console_;
  /// Cycle time in milliseconds in which the task will be executed periodically
  uint16_t execution_cycle_;
  /// Queue to communicate between a sender and receiver task
  QueueWrapper *queue_;
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(QueueReceiver);
};

}  // namespace demo

#endif  // DEMO_QUEUE_RECEIVER_H_
