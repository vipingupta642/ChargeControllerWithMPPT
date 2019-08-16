/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        SystemAndClock.h                                                 *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        30.07.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Work with clock's system and core functions                      *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#pragma once 

#include "stm32f3xx.h"

/********************************************************************************
 * Local function declaration
 ********************************************************************************/

void InitSystemClockMCU (void);
void EnableOutputMCO (void);

/********************************* END OF FILE **********************************/