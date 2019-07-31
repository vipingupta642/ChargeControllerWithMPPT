/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        main.c                                                           *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        15.07.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Main program body                                                *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "main.h"

/********************************************************************************
 * Main program body
 ********************************************************************************/

int main (void) {

    InitLEDonBoard();
    InitExtiButtonOnBoard();

    InitSystemClockMCU();
    EnableOutputMCO();

    InitUSART1();

    while(1) {}

}

/********************************* END OF FILE **********************************/