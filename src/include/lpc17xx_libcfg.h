// Copyright (C) ferraith. All rights reserved.

///
/// @brief LPC17xx library configuration file
/// @author ferraith
///

#ifndef LPC17XX_LIBCFG_H_
#define LPC17XX_LIBCFG_H_

#include "lpc_types.h"

// Comment the line below to disable the specific peripheral inclusion
#define _DBGFWK  ///< DEBUG_FRAMWORK
#define _GPIO    ///< GPIO
#define _EXTI    ///< EXTI
#define _UART    ///< UART
#define _UART0   ///< UART0
#define _UART1   ///< UART1
#define _UART2   ///< UART2
#define _UART3   ///< UART3
#define _SPI     ///< SPI
#define _SYSTICK ///< SYSTICK
#define _SSP     ///< SSP
#define _SSP0    ///< SSP0
#define _SSP1    ///< SSP1
#define _I2C     ///< I2C
#define _I2C0    ///< I2C0
#define _I2C1    ///< I2C1
#define _I2C2    ///< I2C2
#define _TIM     ///< TIMER
#define _WDT     ///< WDT
#define _GPDMA   ///< GPDMA
#define _DAC     ///< DAC
#define _ADC     ///< ADC
#define _PWM     ///< PWM
#define _PWM1    ///< PWM1
#define _RTC     ///< RTC
#define _I2S     ///< I2S
#define _USBDEV  ///< USB device
#define _USB_DMA ///< USB DMA
#define _QEI     ///< QEI
#define _MCPWM   ///< MCPWM
#define _CAN     ///< CAN
#define _RIT     ///< RIT
#define _EMAC    ///< EMAC


///
/// @brief      The CHECK_PARAM macro is used for function's parameters check.
///             It is used only if the library is compiled in DEBUG mode.
/// @param[in]  expr - If expr is false, it calls check_failed() function
///                    which reports the name of the source file and the source
///                    line number of the call that failed.
///                  - If expr is true, it returns no value.
/// @return     None
///
#ifdef  DEBUG
#define CHECK_PARAM(expr) ((expr) ? (void)0 : check_failed((uint8_t *)__FILE__, __LINE__))
#else
#define CHECK_PARAM(expr)
#endif  // DEBUG

///
/// @brief       Reports the name of the source file and the source line number
///              where the CHECK_PARAM error has occurred.
/// @param[in]   file Pointer to the source file name
/// @param[in]   line assert_param error line source number
/// @return      None
///
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line);
#endif  // DEBUG

#endif  // LPC17XX_LIBCFG_H_
