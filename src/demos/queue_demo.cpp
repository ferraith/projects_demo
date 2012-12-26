// Demo Application
// Copyright (C) ferraith. All rights reserved.

#include "queue_demo.h"

#include <stdio.h>

#include "console.h"

using ::aoaa_board::Console;

namespace demo {

QueueDemo::QueueDemo(xQueueHandle queue_handle) : queue_handle_(queue_handle), task_a_handle_(NULL), task_b_handle_(NULL) {}


extern "C" void TaskAWrapper(void* parm) {
  (static_cast<QueueDemo *>(parm))->TaskA();
}


extern "C" void TaskBWrapper(void* parm) {
  (static_cast<QueueDemo *>(parm))->TaskB();
}


void QueueDemo::TaskA() {
  portTickType last_wake_time;
  uint16_t counter = 0;
  int init = 1;
  char console_string[40];
  Console console;

  last_wake_time = xTaskGetTickCount();

  for(;;) {
    if(init == 1) {
      // Initial send
      xQueueSend(queue_handle_, &counter, 0);
      init = 0;
    } else {
      uint16_t temp;
      xQueueReceive(queue_handle_, &counter, portMAX_DELAY);
      temp = counter;
      counter++;
      sprintf(console_string, "QueueDemo: A %d --> %d\r\n", temp, counter);
      xQueueSend(queue_handle_, &counter, 0);
      console.SendString(console_string);
    }
    vTaskDelayUntil(&last_wake_time, 1000 * configTICK_RATE_HZ / 1000);
  }
  vTaskDelete(NULL);
}


void QueueDemo::TaskB() {
  portTickType last_wake_time;
  vTaskDelay(500 * configTICK_RATE_HZ / 1000);
  last_wake_time = xTaskGetTickCount();
  uint16_t counter = 0;
  char console_string[40];
  Console console;

  for(;;) {
    uint16_t temp;
    xQueueReceive(queue_handle_, &counter, portMAX_DELAY);
    temp = counter;
    counter++;
    sprintf(console_string, "QueueDemo: B %d --> %d\r\n", temp, counter);
    xQueueSend(queue_handle_, &counter, 0);
    console.SendString(console_string);

    vTaskDelayUntil(&last_wake_time, 1000 * configTICK_RATE_HZ / 1000);
  }
  vTaskDelete(NULL);
}


void QueueDemo::Run() {
  if(queue_handle_ != NULL) {
    xTaskCreate(TaskAWrapper, (const signed char *) "Task A", ( ( unsigned short ) 83 ), (void *) this,
                (tskIDLE_PRIORITY + 1), &task_a_handle_);
    xTaskCreate(TaskBWrapper, (const signed char *) "Task B", ( ( unsigned short ) 83 ), (void *) this,
                (tskIDLE_PRIORITY + 1), &task_b_handle_);
  }
}

}  // namespace demo
