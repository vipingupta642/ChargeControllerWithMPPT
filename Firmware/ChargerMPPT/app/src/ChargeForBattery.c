/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        ChargeForBattery.c                                               *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        14.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Algorithmic for charge battery CC/CV                             *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "ChargeForBattery.h"

/********************************************************************************
 * Initialization and start dc/dc converter for charge battery
 ********************************************************************************/

void StartChargeBattery (void) {

    InitHRPWMforConverter();
    InitAdcForFeedback();
}

/********************************************************************************
 * Control output dc/dc converter
 * PB14 - enable/disable output transistor with pull-up resistor
 * Logic 1 - disable output
 * Logic 0 - enable output
 ********************************************************************************/

void ControlOutputConverter (ConverterStatus status) {

    if (status == Enable)  { GPIOB->BSRR |= GPIO_BSRR_BR_14; }
    if (status == Disable) { GPIOB->BSRR |= GPIO_BSRR_BS_14; }   
}

/********************************* END OF FILE **********************************/