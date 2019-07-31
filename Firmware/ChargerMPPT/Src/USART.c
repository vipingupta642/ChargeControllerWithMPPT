/********************************************************************************
 * project     Charge controller for solar panel with MPPT algorithm            *
 *                                                                              *
 * file        USART.с                                                          *
 * author      Ila Galkin (aka Nordic Energy)                                   *
 * date        31.07.2019                                                       *
 * copyright   The MIT License (MIT). Copyright (c) 2019 Ilya Galkin            *
 * brief       Work with transceiver for USART1                                 *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "USART.h"

/********************************************************************************
 * User variables
 ********************************************************************************/

const uint16_t dividerForUSART = (uint16_t)78;

/********************************************************************************
 * Initialization GPIO for USART1
 * TX - PB6
 * RX - PB7
 ********************************************************************************/

void InitGpioForUSART1 (void) {

    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;              // Enable clock for GPIO port B

    GPIOB->MODER |= GPIO_MODER_MODER6_1;            // Output alternative push-pull
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;     // Select medium speed for output TX

    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;     // Select medium speed for input RX

    GPIOB->AFR[0] |= (0x07 << GPIO_AFRL_AFRL7_Pos) | (0x07 << GPIO_AFRL_AFRL6_Pos);   // Select alternative function USART1 for PB6 and PB7   
}

/********************************************************************************
 * Initialization for USART1
 * Speed for USART1 - 115 200 baud
 * Divider: 72 000 000 Hz / 921 600 baud = 78 = 0x4E
 ********************************************************************************/

void InitUSART1 (void) {

    InitGpioForUSART1();

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;                                           // Enable clock for USART1

    USART1->BRR |= dividerForUSART;                                                 // Select divider for USART1
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE | USART_CR1_RXNEIE;   // Enable interrupt for RX, TX and global
    NVIC_EnableIRQ (USART1_IRQn);                                   
}

/********************************************************************************
 * Send symbol for USART
 ********************************************************************************/

void SendSymbolForUSART (char chr) {

    while(!(USART1->ISR & USART_ISR_TC));
    USART1->TDR = chr;
}

/********************************************************************************
 * Send byte for USART
 ********************************************************************************/

void SendByteForUSART (uint8_t data) {

    while(!(USART1->ISR & USART_ISR_TC));
    USART1->TDR = data;
}

/********************************************************************************
 * Send string for USART
 ********************************************************************************/

void SendStringForUSART (char* str) {
	
	uint8_t i = 0;
	
	while(str[i])
	SendSymbolForUSART (str[i++]);	
}

/********************************************************************************
 * Handler for USART interrupt
 ********************************************************************************/

void USART1_IRQHandler (void) {
	
	if (USART1->ISR & USART_ISR_RXNE) {

        USART1->ISR &= ~USART_ISR_RXNE;
    }
    
		
}

/********************************* END OF FILE **********************************/