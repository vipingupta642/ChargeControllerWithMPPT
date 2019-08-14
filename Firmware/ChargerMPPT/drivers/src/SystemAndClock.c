/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        SystemAndClock.c                                                 *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        30.07.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Work with clock's system and core functions                      *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "SystemAndClock.h"

/********************************************************************************
 * Initialization for the clock's system
 * Source - external crystall
 * Frequency external crystal   - 8 000 000 Hz
 * Frequency for system clock   - 72 000 000 Hz
 * Divider for ADC clock system - 10
 ********************************************************************************/

void InitSystemClockMCU (void) {

    RCC->CR |= RCC_CR_HSEON;                                    // Enable system for external crystall
	while (!(RCC->CR & RCC_CR_HSERDY));                         // Waiting flag about enable

    FLASH->ACR |= FLASH_ACR_LATENCY_1;                          // Latency for internal flash memory

    RCC->CFGR  |= RCC_CFGR_PLLMUL9;                             // Select multiplier frequency for PLL

    RCC->CFGR  |= RCC_CFGR_PLLSRC;                              // Select source external crystall
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV10;                     // Select divider for ADC = AHB/10

    RCC->CR |= RCC_CR_PLLON;                                    // Enable PLL system
	while((RCC->CR & RCC_CR_PLLRDY) == 0){}                     // Waiting flag about enable

    RCC->CFGR |= RCC_CFGR_SW_PLL;                               // Select source SYSCLK = PLL
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {}      // Waiting flag about enable
}

/********************************************************************************
 * Initialization MCO output
 * MCO - PA8
 ********************************************************************************/

void EnableOutputMCO (void) {

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;							// Clock enable for GPIO port A

	GPIOA->MODER   &= ~GPIO_MODER_MODER8;
	GPIOA->MODER   |= GPIO_MODER_MODER8_1;						// Output alternative push-pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8;					// Very high speed for gpio

	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;							// Select source PLL
	RCC->CFGR |= RCC_CFGR_PLLNODIV;								// PLL divider for MCO
}

/********************************* END OF FILE **********************************/