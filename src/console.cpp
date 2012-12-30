// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#include "Console.h"

#include <cstring>

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"

namespace aoaa_board {

Console::Console()
    : kTimeout(5 * portTICK_RATE_MS),                  // Timeout is reached after 5 ms
      kConsoleDevice((LPC_UART_TypeDef *) LPC_UART0),  // USB-to-UART bridge is connected to UART0
      receive_lock_(NULL),
      send_lock_(NULL) {}

Console::~Console() {
  // Delete semaphores
  vSemaphoreDelete(send_lock_);
  vSemaphoreDelete(receive_lock_);
}

void Console::Deinit() {
  // Disable UART0
  UART_TxCmd(const_cast<LPC_UART_TypeDef *>(kConsoleDevice), DISABLE);

  // Reset UART0 pin selection to default
  PINSEL_CFG_Type default_pin2_config;
  default_pin2_config.Portnum = PINSEL_PORT_0;
  default_pin2_config.Pinnum = PINSEL_PIN_2;
  default_pin2_config.Funcnum = PINSEL_FUNC_0;
  default_pin2_config.Pinmode = PINSEL_PINMODE_PULLUP;
  default_pin2_config.OpenDrain = PINSEL_PINMODE_NORMAL;
  PINSEL_ConfigPin(&default_pin2_config);

  PINSEL_CFG_Type default_pin3_config;
  default_pin3_config.Portnum = PINSEL_PORT_0;
  default_pin3_config.Pinnum = PINSEL_PIN_3;
  default_pin3_config.Funcnum = PINSEL_FUNC_0;
  default_pin3_config.Pinmode = PINSEL_PINMODE_PULLUP;
  default_pin3_config.OpenDrain = PINSEL_PINMODE_NORMAL;
  PINSEL_ConfigPin(&default_pin3_config);
}

bool Console::Init(uint32_t baud_rate, UART_DATABIT_Type num_data_bits, UART_PARITY_Type parity,
                   UART_STOPBIT_Type num_stop_bits) {
  // Initialize semaphores
  vSemaphoreCreateBinary(send_lock_);
  vSemaphoreCreateBinary(receive_lock_);

  if((send_lock_ != NULL) && (receive_lock_ != NULL)) {
    // Configure UART0 pin selection for serial output
    PINSEL_CFG_Type tx_pin_config;
    tx_pin_config.Portnum = PINSEL_PORT_0;
    tx_pin_config.Pinnum = PINSEL_PIN_2;
    tx_pin_config.Funcnum = PINSEL_FUNC_1;
    tx_pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
    tx_pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&tx_pin_config);

    // Configure UART0 pin selection for serial input
    PINSEL_CFG_Type rx_pin_config;
    rx_pin_config.Portnum = PINSEL_PORT_0;
    rx_pin_config.Pinnum = PINSEL_PIN_3;
    rx_pin_config.Funcnum = PINSEL_FUNC_1;
    rx_pin_config.Pinmode = PINSEL_PINMODE_PULLUP;
    rx_pin_config.OpenDrain = PINSEL_PINMODE_NORMAL;
    PINSEL_ConfigPin(&rx_pin_config);

    // Configure UART0
    UART_CFG_Type uart0_config;
    uart0_config.Baud_rate = baud_rate;
    uart0_config.Databits = num_data_bits;
    uart0_config.Parity = parity;
    uart0_config.Stopbits = num_stop_bits;
    UART_Init(const_cast<LPC_UART_TypeDef *>(kConsoleDevice), &uart0_config);

    // Enable UART0
    UART_TxCmd(const_cast<LPC_UART_TypeDef *>(kConsoleDevice), ENABLE);

    return true;
  } else {
    return false;
  }
}

uint32_t Console::SendData(uint8_t *tx_buffer, uint32_t buffer_length) const {
  uint32_t num_sent_bytes = 0;
  // Wait until no other task is sending data
  if(xSemaphoreTake(send_lock_, kTimeout) == pdTRUE) {
    // Send data
    num_sent_bytes = UART_Send(const_cast<LPC_UART_TypeDef *>(kConsoleDevice), tx_buffer, buffer_length, BLOCKING);
    xSemaphoreGive(send_lock_);
  }
  return num_sent_bytes;
}

uint32_t Console::SendString(const char *string) const {
  uint32_t num_sent_bytes = 0;
  // Wait until no other task is sending a string
  if(xSemaphoreTake(send_lock_, kTimeout) == pdTRUE) {
    // Send string
    num_sent_bytes = UART_Send(const_cast<LPC_UART_TypeDef *>(kConsoleDevice), (uint8_t *) string, strlen(string),
                               BLOCKING);
    xSemaphoreGive(send_lock_);
  }
  return num_sent_bytes;
}

uint32_t Console::Receive(uint8_t *rx_buffer, uint32_t buffer_length) const {
  uint32_t num_received_bytes = 0;
  // Wait until no other task is receiving data
  if( xSemaphoreTake(receive_lock_, kTimeout) == pdTRUE) {
    // Receive data
    num_received_bytes = UART_Receive(const_cast<LPC_UART_TypeDef *>(kConsoleDevice), rx_buffer, buffer_length,
                                      BLOCKING);
    xSemaphoreGive(receive_lock_);
  }
  return num_received_bytes;
}

}  // namespace aoaa_board
