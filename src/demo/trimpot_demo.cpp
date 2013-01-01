// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "demo/trimpot_demo.h"

#include <stdio.h>
#include <cstdlib>

#include "aoaa_board/trimpot.h"

using ::std::abs;
using ::aoaa_board::Trimpot;

namespace demo {

TrimpotDemo::TrimpotDemo(Console *console) : console_(console), task_handle_(NULL), current_value_(0) {}


extern "C" void TrimpotTaskWrapper(void* parm) {
  (static_cast<TrimpotDemo *>(parm))->Task();
}


void TrimpotDemo::Task() {
  portTickType last_wake_time;
  uint16_t value = 0;
  char console_string[50];
  Trimpot trimpot;

  last_wake_time = xTaskGetTickCount();
  trimpot.Init(200000);

  for (;;) {
    bool value_is_valid = trimpot.Get(&value);
    if (value_is_valid && (abs(current_value_ - value) > 1)) {
      sprintf(console_string, "TrimpotDemo: Read trimpot value %d\r\n", value);
      console_->SendString(console_string);
      current_value_ = value;
    } else if (!value_is_valid) {
      sprintf(console_string, "TrimpotDemo: Read error\r\n", value);
      console_->SendString(console_string);
    }
    vTaskDelayUntil(&last_wake_time, 100 * portTICK_RATE_MS);
  }
  vTaskDelete(NULL);
}


void TrimpotDemo::Run() {
  xTaskCreate(TrimpotTaskWrapper, (const signed char *) "TrimpotDemo", ((unsigned short) 90), (void *) this,
              (tskIDLE_PRIORITY + 1), &task_handle_);
}

}  // namespace demo
