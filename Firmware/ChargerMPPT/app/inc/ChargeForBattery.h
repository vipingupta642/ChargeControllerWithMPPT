/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        ChargeForBattery.h                                               *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        14.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Algorithmic for charge battery CC/CV                             *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#pragma once 

#include "HighResolutionPWM.h"
#include "VoltageAndCurrentAdc.h"

/********************************************************************************
 * User typedef
 ********************************************************************************/

typedef enum {
    Enable = 0,
    Disable = 1
} ConverterStatus;

/********************************************************************************
 * Local function declaration
 ********************************************************************************/

void StartChargeBattery (void);
void ControlOutputConverter (ConverterStatus status);

/********************************* END OF FILE **********************************/