// LPC17xx Library
// Copyright (C) ferraith. All rights reserved.

#include "lpc17xx_libcfg.h"

#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line)
{
  // User can add his own implementation to report the file name and line number.
  // Example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)

    while (1);
}
#endif  // DEBUG
