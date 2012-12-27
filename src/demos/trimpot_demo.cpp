// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "trimpot_demo.h"

#include <cstdlib>
#include <stdio.h>

#include "console.h"
#include "trimpot.h"

using ::std::abs;
using ::aoaa_board::Console;
using ::aoaa_board::Trimpot;

namespace demo {

TrimpotDemo::TrimpotDemo() : task_handle_(NULL), current_value_(0) {}


extern "C" void TrimpotTaskWrapper(void* parm) {
  (static_cast<TrimpotDemo *>(parm))->Task();
}


void TrimpotDemo::Task() {
  portTickType last_wake_time;
  uint16_t value = 0;
  char console_string[50];
  Console console;
  Trimpot trimpot;

  last_wake_time = xTaskGetTickCount();
  console.Init();
  trimpot.Init();

  for(;;) {
    value = trimpot.Get();
    if(abs(current_value_ - value) > 1) {
      sprintf(console_string, "TrimpotDemo: Read trimpot value %d\r\n", value);
      console.SendString(console_string);
      current_value_ = value;
    }
    vTaskDelayUntil(&last_wake_time, 100 * configTICK_RATE_HZ / 1000);
  }
  vTaskDelete(NULL);
}


void TrimpotDemo::Run() {
  xTaskCreate(TrimpotTaskWrapper, (const signed char *) "TrimpotDemo", ( ( unsigned short ) 100 ), (void *) this,
              (tskIDLE_PRIORITY + 1), &task_handle_);
}

}  // namespace demo
