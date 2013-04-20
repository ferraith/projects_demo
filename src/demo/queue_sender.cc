// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "demo/queue_sender.h"

#include <stdio.h>

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

  portTickType last_wake_time = GetTickCount();

  for (;;) {
    queue_->SendToBack(&counter, 0);
    snprintf(console_string, CONSOLE_STRING_SIZE, "QueueSender: Sent %d\r\n", counter);
    console_->SendString(console_string);
    counter++;
    DelayUntil(&last_wake_time, execution_cycle_);
  }
}

}  // namespace demo
