// AOAA Board Library
// Copyright (C) ferraith. All rights reserved.

#include "aoaa_board/trimpot.h"

#include "lpc17xx/lpc17xx_adc.h"
#include "lpc17xx/lpc17xx_pinsel.h"

namespace aoaa_board {

Trimpot::Trimpot() {}


void Trimpot::Init() {
  PINSEL_CFG_Type PinCfg;

  // Initialize ADC pin connect
  // AD0.5 on P1.31
  PinCfg.Funcnum = 3;
  PinCfg.OpenDrain = 0;
  PinCfg.Pinmode = 0;
  PinCfg.Portnum = 1;
  PinCfg.Pinnum = 31;

  PINSEL_ConfigPin(&PinCfg);

  // Configuration for ADC:
  // Frequency at 200 kHz, ADC channel 5, no Interrupt
  ADC_Init(LPC_ADC, 200000);
  ADC_IntConfig(LPC_ADC, ADC_ADINTEN5, DISABLE);
  ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_5, ENABLE);
}


uint16_t Trimpot::Get() {
  ADC_StartCmd(LPC_ADC, ADC_START_NOW);
  // Wait conversion complete
  while (!(ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_5, ADC_DATA_DONE)));
  return ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_5);
}

}  // namespace aoaa_board
