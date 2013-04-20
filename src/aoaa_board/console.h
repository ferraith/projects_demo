// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#ifndef AOAA_BOARD_CONSOLE_H_
#define AOAA_BOARD_CONSOLE_H_

#include <stdint.h>

#include "common/class_helper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "lpc17xx/lpc17xx_uart.h"

namespace aoaa_board {

///
/// @brief         Provides methods to send and receive data to or from a console connected via UART0 to a
///                USB-to-UART bridge.
///
class Console {
 public:
  ///
  /// @brief         Constructor
  ///
  Console();
  ///
  /// @brief         Destructor
  ///
  ~Console();

  ///
  /// @brief         Deinitialize the console.
  /// @return        None
  ///
  void Deinit();
  ///
  /// @brief         Initialize the console.
  /// @param[in]     baud_rate      UART baud rate
  /// @param[in]     num_data_bits  Number of data bits
  /// @param[in]     parity         Parity selection
  /// @param[in]     num_stop_bits  Number of stop bits
  /// @return        True if console was successfully initialized
  ///
  bool Init(uint32_t baud_rate, UART_DATABIT_Type num_data_bits, UART_PARITY_Type parity,
            UART_STOPBIT_Type num_stop_bits);
  ///
  /// @brief         Send data to the console.
  /// @param[in]     tx_buffer      Buffer containing data to send
  /// @param[in]     buffer_length  Maximum number of bytes to send
  /// @return        Number of bytes sent
  ///
  uint32_t SendData(uint8_t *tx_buffer, uint32_t buffer_length) const;
  ///
  /// @brief         Send a null-terminates string to the console.
  /// @param[in]     string_buffer  The string to send
  /// @return        Number of bytes sent
  ///
  uint32_t SendString(char *string_buffer) const;
  ///
  /// @brief         Receive a block of data from the console.
  /// @param[out]    rx_buffer      Pointer to receive buffer
  /// @param[in]     buffer_length  Maximum number of bytes to receive
  /// @return        Number of bytes received
  ///
  uint32_t Receive(uint8_t *rx_buffer, uint32_t buffer_length) const;

 private:
  /// Timeout in ticks within sending or receiving data have to be possible
  const portTickType kTimeout;
  /// UART used to connect USB-to-UART bridge to the microcontroller
  const LPC_UART_TypeDef *kConsoleDevice;
  /// Semaphore used to synchronize receiving data from console
  xSemaphoreHandle receive_lock_;
  /// Semaphore used to synchronize sending data to console
  xSemaphoreHandle send_lock_;
  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(Console);
};

}  // namespace aoaa_board

#endif  // AOAA_BOARD_CONSOLE_H_
