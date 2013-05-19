// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "demo/queue_sender.h"

#include <stdio.h>

#include "aoaa_board/console.h"
#include "freertos/port/queue_wrapper.h"

#define CONSOLE_STRING_SIZE 30

namespace demo {

QueueSender::QueueSender(QueueWrapper *queue)
    : kStackDepth(90),  // 360 Bytes
      kTaskName("QueueSender"),
      console_(nullptr),
      execution_cycle_(0),
      queue_(queue) {}

void QueueSender::Deinit() {
  Delete();
}

bool QueueSender::Init(uint16_t execution_cycle, uint8_t priority, Console *console) {
  execution_cycle_ = execution_cycle;
  console_ = console;
  return Create(kTaskName, kStackDepth, priority);
}

void QueueSender::Run() {
  uint16_t counter = 0;
  char console_string[CONSOLE_STRING_SIZE];

  for (;;) {
    queue_->SendToBack(&counter, static_cast<uint16_t>(portMAX_DELAY));
    snprintf(console_string, CONSOLE_STRING_SIZE, "QueueSender: Sent %d\r\n", counter);
    console_->SendString(console_string);
    counter++;
    Delay(execution_cycle_);
  }
}

}  // namespace demo
