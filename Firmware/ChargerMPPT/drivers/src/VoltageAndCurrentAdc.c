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

float resultCurrentOutput = 0;
float resultVoltageOutput = 0;
float resultCurrentInput = 0;
float resultVoltageInput = 0;

uint8_t stepFilterForAdc = 0;
const uint8_t allStepFilterAdc = 10;

float bufferCurrentOutput = 0;
float bufferVoltageOutput = 0;
float bufferCurrentInput = 0;
float bufferVoltageInput = 0;

const float referenceVoltageForAdc = 0.000807;      // Step = VDDA / 4096

const float offsetForOutputCurrentSensor = 0.516;   // Voltage offset 10% * VCC sensor
const float offsetForInputCurrentSensor = 0.52;    // Voltage offset 10% * VCC sensor
const float SensitivityCurrentSensor = 0.133;       // Sensitivity sensor 133 mV/A

const float dividerResistorCurrentOutput = 1.56;    // Divider = (5.6 kOhm / 10 kOhm) + 1 
const float dividerResistorVoltageOutput = 9.2;     // Divider = (82 kOhm / 10 kOhm) + 1
const float dividerResistorCurrentInput = 1.56;     // Divider = (5.6 kOhm / 10 kOhm) + 1
const float deviderResistorVoltageInput = 18.8571;  // Divider = (100 kOhm / 5.6 kOhm) + 1

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

    bufferCurrentOutput += (dividerResistorCurrentOutput * referenceVoltageForAdc * (ADC2->JDR1) - offsetForOutputCurrentSensor) / SensitivityCurrentSensor;
    bufferVoltageOutput += dividerResistorVoltageOutput * referenceVoltageForAdc * (ADC2->JDR2);
    bufferCurrentInput += (dividerResistorCurrentInput * referenceVoltageForAdc * (ADC2->JDR3) - offsetForInputCurrentSensor) / SensitivityCurrentSensor;
    bufferVoltageInput += deviderResistorVoltageInput * referenceVoltageForAdc * (ADC2->JDR4);

    stepFilterForAdc++;

    if (stepFilterForAdc == allStepFilterAdc) {

        resultCurrentOutput = bufferCurrentOutput / allStepFilterAdc;
        resultVoltageOutput = bufferVoltageOutput / allStepFilterAdc; 
        resultCurrentInput = bufferCurrentInput / allStepFilterAdc;
        resultVoltageInput = bufferVoltageInput / allStepFilterAdc;

        bufferCurrentOutput = 0;
        bufferVoltageOutput = 0;
        bufferCurrentInput = 0;
        bufferVoltageInput = 0;

        stepFilterForAdc = 0;
    }
}

/********************************* END OF FILE **********************************/