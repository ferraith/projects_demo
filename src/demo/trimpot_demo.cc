// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "demo/trimpot_demo.h"

#include <stdio.h>
#include <cstdlib>

#include "aoaa_board/console.h"
#include "aoaa_board/trimpot.h"

using ::std::abs;
using ::aoaa_board::Trimpot;

namespace demo {

TrimpotDemo::TrimpotDemo()
    : kSampleRate(200000),  // 200 kHz sample rate
      kStackDepth(90),  // 360 Bytes
      kTaskName("TrimpotDemo"),
      console_(nullptr),
      current_value_(0),
      execution_cycle_(0) {}

void TrimpotDemo::Deinit() {
  Delete();
}

bool TrimpotDemo::Init(uint16_t execution_cycle, uint8_t priority, Console *console) {
  execution_cycle_ = execution_cycle;
  console_ = console;
  return Create(kTaskName, kStackDepth, priority);
}

void TrimpotDemo::Run() {
  uint16_t value = 0;
  char console_string[30];
  Trimpot trimpot;

  // Initialize trimpot to be able to read trimpot value
  trimpot.Init(kSampleRate);

  // Endless task loop
  for (;;) {
    // Read trimpot value
    bool value_is_valid = trimpot.Get(&value);
    // Check if value is valid and different from value which was read in last iteration
    if (value_is_valid && (abs(current_value_ - value) > 1)) {
      // Print read value on console
      snprintf(console_string, sizeof(console_string), "TrimpotDemo: Read %d\r\n", value);
      console_->SendString(console_string);
      current_value_ = value;
    // Read value is invalid
    } else if (!value_is_valid) {
      // Print error message
      snprintf(console_string, sizeof(console_string), "TrimpotDemo: Read error\r\n", value);
      console_->SendString(console_string);
    }
    // Delay task some time
    Delay(execution_cycle_);
  }
  // Should never be reached
  trimpot.Deinit();
}

}  // namespace demo
