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

    InitSysTick();

    InitUSART1();
   
    InitHRPWMforConverter();
    SetDutyTimerB (10000);   
   
    InitAdcForFeedback();

    printf ("End basic initialization\n");

    while(1) {

        ToggleLedOnBoard (Blue);
        Delay (1000);
        printf ("adcResult = %d\n", adcResult);
    }

}

/********************************* END OF FILE **********************************/


