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

/********************************* END OF FILE **********************************/