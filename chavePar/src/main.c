#include "stm32f4xx.h"

/*
Pino LED: PC0

Pino Chave1: PB0
Pino Chave2: PB1
Pino Chave3: PB2
Pino Chave4: PB3

GPIOC->MODER = 0x1; //Definir LED como saída
GPIOB->PUPDR = 0xAA; //Definir Pull-Down nas chaves
 */

void verificaPar(int in){
		if((GPIOB->IDR &= in) == 0){
			GPIOC->ODR |= 0b1;
		}
		else{
			GPIOC->ODR &= ~0b1;
		}
}

int main(void)
{
	int posicaoPares[] = {
			0b0011,
			0b1100,
			0b1001,
			0b0110,
			0b1010,
			0b0101,
	};

	RCC->AHB1ENR |= 0x87; // Ligar todos os clocks
	GPIOA->MODER |= 0x28000000; //Definir PA13 e PA14 como função alternativa

	GPIOC->MODER = 0x1; //Definir LED como saída
	GPIOB->PUPDR = 0x55; //Definir Pull-Up nas chaves

  while (1)
  {
	verificaPar(posicaoPares[0]);
	verificaPar(posicaoPares[1]);
	verificaPar(posicaoPares[2]);
	verificaPar(posicaoPares[3]);
	verificaPar(posicaoPares[4]);
	verificaPar(posicaoPares[5]);
  }
}
