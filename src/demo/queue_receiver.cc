// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "demo/queue_receiver.h"

#include <stdio.h>

#include "aoaa_board/console.h"
#include "freertos/port/queue_wrapper.h"

#define CONSOLE_STRING_SIZE 35
#define STACK_DEPTH 90  // 360 Bytes

namespace demo {

QueueReceiver::QueueReceiver(QueueWrapper *queue)
    : TaskWrapper("QueueReceiver"),
      console_(nullptr),
      execution_cycle_(0),
      queue_(queue) {}

void QueueReceiver::Deinit() {
  Delete();
}

bool QueueReceiver::Init(uint16_t execution_cycle, uint8_t priority, Console *console) {
  execution_cycle_ = execution_cycle;
  console_ = console;
  return Create(priority, STACK_DEPTH);
}

void QueueReceiver::Run() {
  uint16_t counter;
  char console_string[CONSOLE_STRING_SIZE];

  for (;;) {
    queue_->Receive(&counter, static_cast<uint16_t>(portMAX_DELAY));
    snprintf(console_string, CONSOLE_STRING_SIZE, "%s: Received %d\r\n", task_name(), counter);
    console_->SendString(console_string);
    counter++;
    Delay(execution_cycle_);
  }
}

}  // namespace demo
