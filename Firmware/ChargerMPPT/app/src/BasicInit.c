/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        BasicInit.c                                                      *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        14.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Basic initialization for peripheral                              *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "BasicInit.h"

/********************************************************************************
 * Initialization for basic peripheral
 ********************************************************************************/

void BasicInitPeripheral (void) {

    InitLEDonBoard();
    InitExtiButtonOnBoard();

    InitSystemClockMCU();
    EnableOutputMCO();   
}

/********************************* END OF FILE **********************************/