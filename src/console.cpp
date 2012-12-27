// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#include "Console.h"

#include <cstring>

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"

namespace aoaa_board {

Console::Console() : kConsoleDev((LPC_UART_TypeDef *) LPC_UART0) {}


void Console::Init() const {
  PINSEL_CFG_Type PinCfg;
  UART_CFG_Type uartCfg;

  // Initialize UART0 pin connect
  PinCfg.Funcnum = 1;
  PinCfg.Portnum = 0;
  PinCfg.Pinnum = 2;
  PINSEL_ConfigPin(&PinCfg);
  PinCfg.Pinnum = 3;
  PINSEL_ConfigPin(&PinCfg);

  uartCfg.Baud_rate = 115200;
  uartCfg.Databits = UART_DATABIT_8;
  uartCfg.Parity = UART_PARITY_NONE;
  uartCfg.Stopbits = UART_STOPBIT_1;

  UART_Init(const_cast<LPC_UART_TypeDef *>(kConsoleDev), &uartCfg);
  UART_TxCmd(const_cast<LPC_UART_TypeDef *>(kConsoleDev), ENABLE);
}


uint32_t Console::SendData(uint8_t *txbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag) const {
  return UART_Send(const_cast<LPC_UART_TypeDef *>(kConsoleDev), txbuf, buflen, flag);
}


uint32_t Console::SendString(char *str) const {
  return UART_Send(const_cast<LPC_UART_TypeDef *>(kConsoleDev), (uint8_t *) str, strlen((const char *) str), BLOCKING);
}


uint32_t Console::Receive(uint8_t *rxbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag) const {
  return UART_Receive(const_cast<LPC_UART_TypeDef *>(kConsoleDev), rxbuf, buflen, flag);
}

}  // namespace aoaa_board
