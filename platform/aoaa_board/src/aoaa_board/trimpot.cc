// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#include "aoaa_board/trimpot.h"

#include "cmsis_core_lpc17xx/LPC17xx.h"
#include "lpc17xx/lpc17xx_adc.h"
#include "lpc17xx/lpc17xx_pinsel.h"

namespace aoaa_board {

Trimpot::Trimpot() : kConversionTimeout(5) {}  // Timeout is reached after 5 cycles

void Trimpot::Deinit() {
  // Disable ADC
  ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_5, DISABLE);
  // Reset ADC configuration
  ADC_DeInit(LPC_ADC);

  // Reset ADC pin selection to default
  PINSEL_CFG_Type default_pin_config = {
    .Portnum = PINSEL_PORT_1,
    .Pinnum = PINSEL_PIN_31,
    .Funcnum = PINSEL_FUNC_0,
    .Pinmode = PINSEL_PINMODE_PULLUP,
    .OpenDrain = PINSEL_PINMODE_NORMAL
  };
  PINSEL_ConfigPin(&default_pin_config);
}

void Trimpot::Init(uint32_t sample_rate) {
  // Configure ADC pin selection for analog input AD0.5
  PINSEL_CFG_Type ad05_pin_config = {
    .Portnum = PINSEL_PORT_1,
    .Pinnum = PINSEL_PIN_31,
    .Funcnum = PINSEL_FUNC_3,
    .Pinmode = PINSEL_PINMODE_PULLUP,
    .OpenDrain = PINSEL_PINMODE_NORMAL
  };
  PINSEL_ConfigPin(&ad05_pin_config);

  // Configure ADC to measure channel 5
  ADC_Init(LPC_ADC, sample_rate);
  // Disable raising interrupt
  ADC_IntConfig(LPC_ADC, ADC_ADINTEN5, DISABLE);
  // Enable ADC
  ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_5, ENABLE);
}

bool Trimpot::Get(uint16_t *value) {
  uint8_t counter = 0;

  // Start conversion now
  ADC_StartCmd(LPC_ADC, ADC_START_NOW);
  // Wait until conversion is completed or timeout is reached
  while ((ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_5, ADC_DATA_DONE) == SET) && (counter < kConversionTimeout)) {
    counter++;
  }
  // If conversion is finished, read converted value
  if (counter < kConversionTimeout) {
    *value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_5);
    return true;
  } else {
    return false;
  }
}

}  // namespace aoaa_board
