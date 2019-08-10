/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        VoltageAndCurrentAdc.h                                           *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        09.08.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Work with ADC for measuring voltage and current                  *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "VoltageAndCurrentAdc.h"

/********************************************************************************
 * Used variable
 ********************************************************************************/

uint16_t adcResult = 0;

/********************************************************************************
 * Initialization GPIO for ADC
 * Voltage input  - ADC2 channel 4 - PA7
 * Current input  - ADC2 channel 5 - PB0
 * Voltage output - ADC2 channel 2 - PA5
 * Current output - ADC2 channel 1 - PA4
 ********************************************************************************/

void InitGpioForFeedbackAdc (void) {

    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;     // Clock enable for GPIO port A
    RCC->AHBENR  |= RCC_AHBENR_GPIOBEN;     // Clock enable for GPIO port B 
}

/********************************************************************************
 * Callibration for ADC
 ********************************************************************************/

void StartCallibrationForADC (void) {

	ADC2->CR &= ~ADC_CR_ADVREGEN;
	ADC2->CR |= ADC_CR_ADVREGEN_0;		// Enable Vref
	ADC2->CR &= ~ADC_CR_ADCALDIF;

    ADC2->CR |= ADC_CR_ADCAL;           // Start calibration
    while (ADC2->CR & ADC_CR_ADCAL);    // Wait end calibration
}

/********************************************************************************
 * Initiallization ADC2
 ********************************************************************************/

void InitAdcForFeedback (void) {

    RCC->AHBENR |= RCC_AHBENR_ADC12EN;

    InitGpioForFeedbackAdc();
    StartCallibrationForADC();
 
    ADC2->CFGR |= ADC_CFGR_EXTEN_0;                                             // Enable start conversion external trigger
    ADC2->CFGR |= ADC_CFGR_EXTSEL_0 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_2;    // Event 7 - HRTIM		

    ADC2->SQR1 |= ADC_SQR1_SQ1_1;	// Select ADC2 channel IN2								
    ADC2->SQR1 &= ~ADC_SQR1_L;	    // Length regular ADC channel = 1													

    ADC2->IER |= ADC_IER_EOCIE;     // Interrupt enable
    NVIC_EnableIRQ(ADC1_2_IRQn);    // enable interrupt ADC1 and ADC2

    ADC2->CR |= ADC_CR_ADEN;        // Enable ADC2
    ADC2->CR |= ADC_CR_ADSTART;     // Start ADC2
}

/********************************************************************************
 * Handler for ADC
 ********************************************************************************/

void ADC1_2_IRQHandler (void) {

	ADC2->ISR |= ADC_ISR_EOC;

	adcResult = ADC2->DR;
}
