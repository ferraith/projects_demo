// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#include "Console.h"

#include "LPC17xx.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"

Console::Console() {
	// TODO Auto-generated constructor stub

}

Console::~Console() {
	// TODO Auto-generated destructor stub
}

bool Console::Init() {
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

  UART_Init(((LPC_UART_TypeDef *)LPC_UART0), &uartCfg);
  UART_TxCmd(((LPC_UART_TypeDef *)LPC_UART0), ENABLE);

  return true;
}
