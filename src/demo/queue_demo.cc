// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "demo/queue_demo.h"

namespace demo {

QueueDemo::QueueDemo() : queue_(nullptr) {}

void QueueDemo::Deinit() {
  sender_->Deinit();
  delete sender_;
  receiver_->Deinit();
  delete receiver_;
  queue_->Delete();
  delete queue_;
}

bool QueueDemo::Init(Console *console) {
  // Create queue
  queue_ = new QueueWrapper();
  bool queue_created = queue_->Create(1, sizeof(uint16_t));

  // Create sender and receiver
  receiver_ = new QueueReceiver(queue_);
  bool receiver_created = receiver_->Init(1000, tskIDLE_PRIORITY + 2, console);
  sender_ = new QueueSender(queue_);
  bool sender_created = sender_->Init(1000, tskIDLE_PRIORITY + 2, console);

  // Check if all dependencies were successfully created
  if (queue_created && receiver_created && sender_created) {
    return true;
  } else {
    // Clean dependencies if at least one initialization failed
    Deinit();
    return false;
  }
}

}  // namespace demo
