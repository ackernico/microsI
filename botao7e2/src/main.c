/*
******************************************************************************
Altere o exercício 1 para que a frequência da piscada seja
função de uma entrada E. Quando E estiver em nivel alto, o led pisca a 2 Hz,
caso contrário pisca a 7 Hz. O led é ativo em HIGH e conectado ao PB0. A
entrada E será feita através do pino PC1. Utilize o TIM10.

******************************************************************************
Led = PB0
Botao = PC1
*/
#include "stm32f4xx.h"

int main(void)
{
	int psc;
	int botao;

	RCC->AHB1ENR = 0x87;
	RCC->APB2ENR = 1 << 17;

	GPIOA->MODER = 28000000;
	GPIOB->MODER |= 0x1; // Definir Led como saida
	GPIOC->PUPDR |= 0b0100; //Pull-Up no botao


	TIM10->CR1 = 0x1;
	TIM10->ARR = 999;

	while (1)
  {
		psc = 7999;
		TIM10->PSC = psc;

		botao = GPIOC->IDR & 0b10;

		if(botao == 0){
				psc = 2284;
		}

		if(TIM10->SR & 0x1){
			GPIOB->ODR ^= 0x1;
			TIM10->SR &= 0x0;
		}
  }
}
