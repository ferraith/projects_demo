// Demo Application
// Copyright (C) ferraith. All rights reserved.

#ifndef DEMO_RUNTIME_STATS_DEMO_H_
#define DEMO_RUNTIME_STATS_DEMO_H_

#include <stdint.h>

#include "common/class_helper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/port/task_wrapper.h"

namespace aoaa_board {
  class Console;
}

using ::aoaa_board::Console;
using ::freertos::TaskWrapper;

namespace demo {

///
/// @brief         A task demonstrates the usage of the run time stats functionality of FreeRTOS.
///
class RuntimeStatsDemo : public TaskWrapper {
 public:
  ///
  /// @brief         Constructor.
  ///
  RuntimeStatsDemo();
  ///
  /// @brief         Destructor.
  ///
  ~RuntimeStatsDemo() {}

  ///
  /// @brief         Removes the runtime stats demo task from the list of tasks that are ready to run.
  /// @return        None
  ///
  void Deinit();
  ///
  /// @brief         Creates the runtime stats demo task and add it to the list of tasks that are ready to run.
  /// @param[in]     execution_cycle  Cycle time in milliseconds in which the task will be executed periodically
  /// @param[in]     priority  Priority at which the task should run
  /// @param[in]     console  Console
  /// @return        True if the task was successfully created and added to a ready list
  ///
  bool Init(uint16_t execution_cycle, uint8_t priority, Console *console);
  ///
  /// @brief         Will be executed in task context and reads out cyclically the run time stats. The results will be
  ///                printed on the console.
  /// @return        None
  ///
  void Run();

 private:
  /// Reference to the console which is used for printing debug messages
  Console *console_;
  /// Cycle time in milliseconds in which the task will be executed periodically
  uint16_t execution_cycle_;
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(RuntimeStatsDemo);
};

}  // namespace demo

#endif  // DEMO_RUNTIME_STATS_DEMO_H_
