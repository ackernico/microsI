#include "stm32f4xx.h"

/*
Pino LED: PC0

Pino ChaveA0: PB0
Pino ChaveA1: PB1
Pino ChaveB0: PB2
Pino ChaveB1: PB3

GPIOC->MODER = 0x1; //Definir LED como saída
GPIOB->PUPDR = 0xAA; //Definir Pull-Down nas chaves
 */

void verifica(int in){
		if((GPIOB->IDR &= in) == 0){
			GPIOC->ODR |= 0b1;
		}
		else{
			GPIOC->ODR &= ~0b1;
		}
}

int main(void)
{

	RCC->AHB1ENR |= 0x87; // Ligar todos os clocks
	GPIOA->MODER |= 0x28000000; //Definir PA13 e PA14 como função alternativa

	GPIOC->MODER = 0x1; //Definir LED como saída
	GPIOB->PUPDR = 0x55; //Definir Pull-Up nas chaves

  while (1)
  {
	verifica(0b1111);
	verifica(0b0101);
	verifica(0b1010);
}
}
