/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        HighResolutionPWM.h                                              *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        31.07.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Work with high resolution PWM for buck converter                 *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "HighResolutionPWM.h"

/********************************************************************************
 * User variables
 ********************************************************************************/

const uint16_t PeriodTimerB = 45000;
const uint16_t PeriodTimerMaster = 45000;

/********************************************************************************
 * Initialization GPIO for HRPWM channel B
 * Channel B1 - PA10
 * Channel B2 - PA11
 ********************************************************************************/

void InitGpioForHRPWM (void) {

    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;             // Enable clock for GPIO port A

	GPIOA->MODER   |= GPIO_MODER_MODER10_1;         // Output alternative push-pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10;      // Select very high speed for gpio

	GPIOA->MODER   |= GPIO_MODER_MODER11_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11;

	GPIOA->AFR[1] |= (AF13 << GPIO_AFRH_AFRH2_Pos) | (AF13 << GPIO_AFRH_AFRH3_Pos);     // Select alternative function for PA10 and PA11
}

/********************************************************************************
 * Initialization HRPWM channel B
 * Frequency - 100 kHz
 * Dead time - 104 ns
 * Complementary output
 ********************************************************************************/

void InitHRPWMforConverter (void) {

    InitGpioForHRPWM();

    RCC->CFGR3   |= RCC_CFGR3_HRTIM1SW_PLL;                             // Enable multiplier x2 for PLL frequency
    RCC->APB2ENR |= RCC_APB2ENR_HRTIM1EN;                               // Enable clock for HRPWM

    HRTIM1->sCommonRegs.DLLCR |= HRTIM_DLLCR_CAL | HRTIM_DLLCR_CALEN;   // Start timer's calibration 
    while ((HRTIM1->sCommonRegs.ISR & HRTIM_ISR_DLLRDY) == RESET);      // Waiting for the end fo calibration          

    HRTIM1->sTimerxRegs[1].PERxR = PeriodTimerB;                        // Set period for timer B
    HRTIM1->sTimerxRegs[1].CMP1xR = 0;                                  // Set starting duty for timer B
    
    HRTIM1->sTimerxRegs[1].OUTxR |= HRTIM_OUTR_DTEN;                                        // Enable dead-time
    HRTIM1->sTimerxRegs[1].DTxR  |= (3 << HRTIM_DTR_DTPRSC_Pos);                            // Set Tdtg = (2^3) * 868 ps = 6.94 ns
    HRTIM1->sTimerxRegs[1].DTxR  |= (15 << HRTIM_DTR_DTR_Pos) | (15 << HRTIM_DTR_DTF_Pos);  // Set dead-time rising and falling = 15 * Ttg = 104 ns 	
    HRTIM1->sTimerxRegs[1].DTxR  |= HRTIM_DTR_DTFSLK | HRTIM_DTR_DTRSLK;                    // Lock value dead-time

    SelectEventForExternalGeneration();                                 // Enable generation event for ADC

    HRTIM1->sTimerxRegs[1].SETx1R |= HRTIM_SET1R_PER;	                // Event forces the output to active state for TB1
    HRTIM1->sTimerxRegs[1].RSTx1R |= HRTIM_RST1R_CMP1;                  // Event forces the output to inactive state for TB1

    HRTIM1->sCommonRegs.OENR |= HRTIM_OENR_TB1OEN | HRTIM_OENR_TB2OEN;  // Enable output PWM for TB1 and TB2
    HRTIM1->sTimerxRegs[1].TIMxCR |= HRTIM_TIMCR_CONT;                  // Continuous mode

    HRTIM1->sMasterRegs.MPER = PeriodTimerMaster;                       // Period for master timer
    HRTIM1->sMasterRegs.MCR |= HRTIM_MCR_MCEN | HRTIM_MCR_TBCEN;        // Enable counter for Master and timer B
}

/********************************************************************************
 * Select and enable generation event for ADC
 ********************************************************************************/

void SelectEventForExternalGeneration (void) {
   
    HRTIM1->sTimerxRegs[1].CMP2xR = PeriodTimerB / 10;  // Samples in 10% of ON time 
    HRTIM1->sCommonRegs.CR1 |= HRTIM_CR1_ADC2USRC_1;    // ADC trigger 2 update: Timer B 
    HRTIM1->sCommonRegs.ADC2R |= HRTIM_ADC2R_AD2TBC2;   // ADC trigger 2 event: Timer B compare 2  
}

/********************************************************************************
 * Set value duty for HRPWM channel B
 ********************************************************************************/

void SetDutyTimerB (uint16_t duty) { 
    
    HRTIM1->sTimerxRegs[1].CMP1xR = PeriodTimerB - duty; 
}

/********************************* END OF FILE **********************************/