// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#include "Console.h"

#include <string.h>

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"

#define CONSOLE_DEV ((LPC_UART_TypeDef *)LPC_UART0)

Console::Console() {}

Console::~Console() {}

void Console::Init() {
  PINSEL_CFG_Type PinCfg;
  UART_CFG_Type uartCfg;

  /* Initialize UART0 pin connect */
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

  UART_Init(CONSOLE_DEV, &uartCfg);
  UART_TxCmd(CONSOLE_DEV, ENABLE);
}

uint32_t Console::SendData(uint8_t *txbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag) {
  return UART_Send(CONSOLE_DEV, txbuf, buflen, flag);
}

uint32_t Console::SendString(uint8_t *str) {
  return UART_Send(CONSOLE_DEV, str, strlen((const char *) str), BLOCKING);
}

uint32_t ReceiveData(uint8_t *rxbuf, uint32_t buflen, TRANSFER_BLOCK_Type flag) {
  return UART_Receive(CONSOLE_DEV, rxbuf, buflen, flag);
}
