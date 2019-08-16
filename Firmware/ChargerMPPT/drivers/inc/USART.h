/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        USART.h                                                          *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        31.07.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Work with transceiver for USART1                                 *
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

void InitGpioForUSART1 (void);
void InitUSARTforDebug (void);
void SendSymbolForUSART (char chr);
void SendByteForUSART (uint8_t data);
void SendStringForUSART (char* str);

/********************************* END OF FILE **********************************/