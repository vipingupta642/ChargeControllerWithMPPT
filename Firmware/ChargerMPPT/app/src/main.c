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

    StopAllConverter();
   
    BasicInitPeripheral();
    StartSystemMonitoring();
    
    StartChargeBattery();  
    SetDutyTimerB (27000);

    ControlOutputConverter (Enable);

    printf ("End initialization MCU\n");

    while(1) {

        ToggleLedOnBoard (Blue);
        Delay (1000);
    }

}

/********************************* END OF FILE **********************************/


