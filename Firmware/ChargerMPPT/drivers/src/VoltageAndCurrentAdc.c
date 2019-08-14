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

//uint16_t adcResult = 0;

uint16_t adcResult1 = 0;
uint16_t adcResult2 = 0;
uint16_t adcResult3 = 0;
uint16_t adcResult4 = 0;

/********************************************************************************
 * Initialization GPIO for ADC
 * Current output - ADC2 channel 1 - PA4
 * Voltage output - ADC2 channel 2 - PA5
 * Current input  - ADC2 channel 3 - PA6
 * Voltage input  - ADC2 channel 4 - PA7
 ********************************************************************************/

void InitGpioForFeedbackAdc (void) {

    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;     // Clock enable for GPIO port A
}

/********************************************************************************
 * Callibration for ADC
 ********************************************************************************/

void StartCallibrationForAdc (void) {

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

    RCC->AHBENR |= RCC_AHBENR_ADC12EN;      // Clock enable for ADC1 and ADC2

    InitGpioForFeedbackAdc();
    StartCallibrationForAdc();

    ADC2->JSQR |= 0x10308167;               // Lenght = 4, Trigger = event 9, Type trigger = rising edge, Channel = IN1, IN2, IN3 and IN4

    ADC2->IER |= ADC_IER_JEOSIE;            // Interrupt enable
    NVIC_EnableIRQ(ADC1_2_IRQn);            // Enable interrupt ADC1 and ADC2

    ADC2->CR |= ADC_CR_ADEN;                // Enable ADC2
    while(!(ADC2->ISR & ADC_ISR_ADRDY));    // Wait ready ADC2

    ADC2->CR |= ADC_CR_JADSTART;            // Enable injector conversion
}

/********************************************************************************
 * Handler for ADC
 ********************************************************************************/

void ADC1_2_IRQHandler (void) {

	ADC2->ISR |= ADC_ISR_JEOS;

    adcResult1 = ADC2->JDR1;
    adcResult2 = ADC2->JDR2;
    adcResult3 = ADC2->JDR3;
    adcResult4 = ADC2->JDR4;
}
