/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        LedAndButton.c                                                   *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        15.07.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Work with LED and button on board                                *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "LedAndButton.h"

/********************************************************************************
 * Initialization output GPIO for LEDs:
 * Red - PC13
 * Blue -  PC14
 ********************************************************************************/

void InitLEDonBoard (void) {
    
    RCC->AHBENR  |= RCC_AHBENR_GPIOCEN;     // Clock enable for GPIO port C

	GPIOC->MODER &= ~GPIO_MODER_MODER13;    // Output push-pull
	GPIOC->MODER |= GPIO_MODER_MODER13_0;	

	GPIOC->MODER &= ~GPIO_MODER_MODER14;
	GPIOC->MODER |= GPIO_MODER_MODER14_0;	
}

/********************************************************************************
 * Control LED
 ********************************************************************************/

void ControlLedOnBoard (LedColor color, LedStatus status) {

    if ((color == Red) && (status == LedOff))  {GPIOC->BSRR |= GPIO_BSRR_BR_13;}
    if ((color == Red) && (status == LedOn))   {GPIOC->BSRR |= GPIO_BSRR_BS_13;}

    if ((color == Blue) && (status == LedOff)) {GPIOC->BSRR |= GPIO_BSRR_BR_14;}
    if ((color == Blue) && (status == LedOn))  {GPIOC->BSRR |= GPIO_BSRR_BS_14;}
}

/********************************************************************************
 * Initialization input GPIO and EXTI for button:
 * Button - PC15
 ********************************************************************************/

void InitExtiButtonOnBoard (void) {

    RCC->AHBENR  |= RCC_AHBENR_GPIOCEN;             // Clock enable for GPIO port C
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI15_PC;  // Connect PC15 with EXTI
    EXTI->FTSR |= EXTI_FTSR_TR15;                   // Generation interrupt for falling
    EXTI->IMR  |= EXTI_IMR_MR15;                    // Enable interrupt line

    NVIC_EnableIRQ(EXTI15_10_IRQn);                 // Enable interrupt  
}

/********************************************************************************
 * Interrupt handler for button
 ********************************************************************************/

void EXTI15_10_IRQHandler (void) {

    if (EXTI->PR & EXTI_PR_PR15) {

        EXTI->PR |= EXTI_PR_PR15;                   // Reset flag interrupt

        ControlLedOnBoard (Blue, LedOn);
    }                                      
}

/********************************* END OF FILE **********************************/