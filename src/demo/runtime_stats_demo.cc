// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "demo/runtime_stats_demo.h"

#include "aoaa_board/console.h"

#define RUNTIME_STATS_SIZE 120

namespace demo {

RuntimeStatsDemo::RuntimeStatsDemo()
    : kStackDepth(110),  // 440 Bytes
      kTaskName("RuntimeStatsDemo"),
      console_(nullptr),
      execution_cycle_(0) {}

void RuntimeStatsDemo::Deinit() {
  Delete();
}

bool RuntimeStatsDemo::Init(uint16_t execution_cycle, uint8_t priority, Console *console) {
  execution_cycle_ = execution_cycle;
  console_ = console;
  return Create(kTaskName, kStackDepth, priority);
}

void RuntimeStatsDemo::Run() {
  char runtime_stats[RUNTIME_STATS_SIZE];

  for (;;) {
    // Read out run time stats
    vTaskGetRunTimeStats((signed char *) runtime_stats);
    // Remove carriage return and line feed and send string to console
    console_->SendString(runtime_stats + 2);
    // Delay task some time
    Delay(execution_cycle_);
  }
}

}  // namespace demo
