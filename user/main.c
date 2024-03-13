/*
 * main.c
 *
 *  Created on: 13 мар. 2024 г.
 *      Author: user
 */

#include "stm32f1xx.h"

//----------------------------------------------------------
#define LED_ON() GPIOB->BSRR = GPIO_BSRR_BS2
#define LED_OFF() GPIOB->BSRR = GPIO_BSRR_BR2;
//----------------------------------------------------------

__IO uint32_t tmpreg;

void delay(unsigned int Val) {
	for (; Val != 0; Val--) {
		__NOP();
	}
}

//----------------------------------------------------------
void RCC_DeInit(void) {
	SET_BIT(RCC->CR, RCC_CR_HSION);

	while (READ_BIT(RCC->CR, RCC_CR_HSIRDY == RESET)) {
	}
	MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U);
	CLEAR_REG(RCC->CFGR);

	while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET) {
	}
	CLEAR_BIT(RCC->CR, RCC_CR_PLLON);

	while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET) {
	}
	CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);

	while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET) {
	}
	CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
	//Reset all CSR flags
	SET_BIT(RCC->CSR, RCC_CSR_RMVF);
	SET_BIT(RCC->CSR, RCC_CSR_RMVF);
	//Disable all interrupts
	CLEAR_REG(RCC->CIR);
}
//----------------------------------------------------------

int main(void) {
	RCC_DeInit();
	// RCC Alternate Function I/O clock enable
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);
	tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);

	//RCC I/O port B clock enable
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);
	tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);

	//GPIO B settings
	MODIFY_REG(GPIOB->CRL, GPIO_CRL_CNF2, GPIO_CRL_MODE2);
	MODIFY_REG(GPIOB->CRL, GPIO_CRL_CNF2, GPIO_CRL_MODE2_0);

	while (1) {
		LED_ON();
		delay(600000);
		LED_OFF();
		delay(600000);

	}
}
