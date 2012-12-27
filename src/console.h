// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdint.h>

#include "class_helper.h"
#include "lpc17xx_uart.h"

namespace aoaa_board {

///
/// @brief         Provides methods to send and receive data to or from a console connected via UART to a
///                USB-to-UART bridge.
///
class Console {
 public:
  ///
  /// @brief         Constructor
  ///
  Console();
  ///
  /// @brief         Initialize the console.
  /// @return        None
  ///
  void Init() const;
  ///
  /// @brief         Send data to the console.
  /// @param[in]     txbuf   Buffer containing data to send
  /// @param[in]     buflen  Maximum number of bytes to send
  /// @param[in]     flag    Indicates blocking or non-blocking transfer
  /// @return        Number of bytes sent
  ///
  uint32_t SendData(uint8_t *txbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag) const;
  ///
  /// @brief         Send a null-terminates string to the console
  /// @param[in]     str  The string to send
  /// @return        Number of bytes sent
  ///
  uint32_t SendString(char *str) const;
  ///
  /// @brief         Receive a block of data from the console.
  /// @param[in,out] rxbuf   Pointer to receive buffer
  /// @param[in]     buflen  Maximum number of bytes to receive
  /// @param[in]     flag    Indicates blocking or non-blocking transfer
  /// @return        Number of bytes received
  ///
  uint32_t Receive(uint8_t *rxbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag) const;

 private:
  /// UART used to connect USB-to-UART bridge to the microcontroller
  const LPC_UART_TypeDef *kConsoleDev;

  /// Disables the copy constructor and assignment operator
  DISALLOW_COPY_AND_ASSIGN(Console);
};

}  // namespace aoaa_board

#endif  // CONSOLE_H_
