// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdint.h>

#include "lpc17xx_uart.h"

///
///
///
class Console {
 public:
  ///
  /// @brief      Constructor
  ///
  Console();
  ///
  /// @brief      Destructor
  ///
  virtual ~Console();
  ///
  ///
  ///
  void Init();
  ///
  ///
  ///
  uint32_t SendData(uint8_t *txbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag);
  ///
  ///
  ///
  uint32_t SendString(uint8_t *str);
  ///
  ///
  ///
  uint32_t ReceiveData(uint8_t *rxbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag);
};

#endif  // CONSOLE_H_
