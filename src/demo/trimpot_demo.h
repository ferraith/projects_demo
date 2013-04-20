// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef DEMO_TRIMPOT_DEMO_H_
#define DEMO_TRIMPOT_DEMO_H_

#include <stdint.h>

#include "aoaa_board/console.h"
#include "common/class_helper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/port/task_wrapper.h"
#include "lpc17xx/lpc17xx_uart.h"

using ::aoaa_board::Console;
using ::freertos::TaskWrapper;

namespace demo {

///
/// @brief         A task demonstrates the usage of the trim-pot placed on the AOAA board by reading sampled values.
///
class TrimpotDemo : public TaskWrapper {
 public:
  ///
  /// @brief         Constructor
  ///
  TrimpotDemo();
  ///
  /// @brief         Destructor
  ///
  ~TrimpotDemo() {}

  ///
  /// @brief         Removes the trim-pot demo task from the list of tasks that are ready to run.
  /// @return        None
  ///
  void Deinit();
  ///
  /// @brief         Creates the trim-pot demo task and add it to the list of tasks that are ready to run.
  /// @param[in]     execution_cycle  Cycle time in milliseconds in which the task will be executed periodically
  /// @param[in]     priority  Priority at which the task should run
  /// @param[in]     console  Console
  /// @return        True if the task was successfully created and added to a ready list
  ///
  bool Init(uint16_t execution_cycle, uint8_t priority, Console *console);
  ///
  /// @brief         Will be executed in task context and reads cyclic the current trim-pot value. The value will be
  ///                printed on the console.
  /// @return        None
  ///
  void Run();

 private:
  /// Sample rate in which trim-pot will be read
  const uint32_t kSampleRate;
  /// Size of the task stack specified as the number of variables the stack can hold
  const uint16_t kStackDepth;
  /// Descriptive name for the task
  const char *kTaskName;
  /// Reference to the console which is used for printing debug messages
  Console *console_;
  /// Current value of trim-pot
  uint16_t current_value_;
  /// Cycle time in milliseconds in which the task will be executed periodically
  uint16_t execution_cycle_;
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(TrimpotDemo);
};

}  // namespace demo

#endif  // DEMO_TRIMPOT_DEMO_H_
