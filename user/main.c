/*
 * main.c
 *
 *  Created on: 13 мар. 2024 г.
 *      Author: user
 */

#include "stm32f1xx.h"

//----------------------------------------------------------
#define LED_ON() SET_BIT(GPIOB->ODR,GPIO_ODR_ODR2)
#define LED_OFF() CLEAR_BIT(GPIOB->ODR,GPIO_ODR_ODR2)
//----------------------------------------------------------
__IO uint32_t tmpreg;
uint8_t time2_count = 0;
//----------------------------------------------------------

void delay(__IO uint32_t tck) {
	while (tck) {
		tck--;
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
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);
	//Delay after an RCC peripheral clock enabling
	tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);
	//Delay after an RCC peripheral clock enabling
	tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);

	MODIFY_REG(GPIOB->CRL, GPIO_CRL_CNF2, GPIO_CRL_MODE2_0);
	LED_ON();

	while (1) {
		//LED_ON();
		//LED_OFF();
		//delay(500);

	}
}
