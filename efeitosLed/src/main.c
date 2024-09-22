/*
 * Exerc�cio 5 :
  Acione os leds em sequ�ncia, come�ando de uma ponta da linha e
  percorrendo at� a outra ponta, acionando somente um led. O led aceso deve
  �percorrer� a extens�o da linha, indo de uma extremidade a outra e
  retornando. Seguir com este movimento indefinidamente.

  Exerc�cio 6 :
  Acione os leds em sequ�ncia, come�ando de uma ponta da linha e
  percorrendo at� a outra ponta, acionando o proximo led, mantendo o anterior
  acionado. Ao preencher a linha, retornar apagando os leds.

  Exerc�cio 7 :
  Crie (invente, inove, seja criativo) um efeito visual na linha de leds, a exemplo
  dos exerc�cios anteriores.

  Exerc�cio 8 :
  Utilizando duas chaves conectadas ao kit, junte os codigos 5 a 7,
  selecionando o efeito atrav�s das chaves.
 */

#include "stm32f4xx.h"

void ajudaD(int x, int var[8]){
	GPIOC->ODR &= ~var[x-1];
	GPIOC->ODR |= var[x];
}

void ajudaC(int x, int var[8]){
	GPIOC->ODR |= var[8-x];
	GPIOC->ODR &= ~var[8-x+1];
}

int main(void)
{
  RCC->AHB1ENR = 0x87;
  RCC->APB2ENR = 1 << 17;
  RCC->APB1ENR = 0b1;

  GPIOA->MODER |= 0x28000400;
  GPIOC->MODER |= 0b0101010101010101;
  GPIOB->MODER &= 0x0;

  GPIOB->PUPDR |= 0b0101;

  TIM10->CR1 = 0b1;
  TIM10->PSC = 1599;
  TIM10->ARR = 999;

  TIM3->CR1 = 0b1;
  TIM3->PSC = 3199;
  TIM3->ARR = 999;

  int chave1;
  int chave2;

  int led[] = {  0b00000001, //Led1
  	  	  	  	 0b00000010, //Led2
  	  	  	  	 0b00000100, //Led3
  	  	  	  	 0b00001000, //Led4
  	  	  	  	 0b00010000, //Led5
  	  	  	  	 0b00100000, //Led6
  	  	  	  	 0b01000000, //Led7
  	  	  	  	 0b10000000};//Led8

  int cont=0;

	while (1)
  {
	chave1 = GPIOB->IDR & 0b01;
	chave2 = GPIOB->IDR & 0b10;

		if(TIM10->SR & 0x1){
		cont++;

		GPIOA->ODR ^= 0x20;

		if(!chave1 && chave2){
		switch(cont){
			case 1:
				GPIOC->ODR &= 0b0;
				GPIOC->ODR |= led[0];
				break;
			case 2:
				ajudaD(1, led);
				break;
			case 3:
				ajudaD(2, led);
				break;
			case 4:
				ajudaD(3, led);
				break;
			case 5:
				ajudaD(4, led);
				break;
			case 6:
				ajudaD(5, led);
				break;
			case 7:
				ajudaD(6, led);
				break;
			case 8:
				ajudaD(7, led);
				break;
			case 9:
				ajudaC(1, led);
				break;
			case 10:
				ajudaC(2, led);
				break;
			case 11:
				ajudaC(3, led);
				break;
			case 12:
				ajudaC(4, led);
				break;
			case 13:
				ajudaC(5, led);
				break;
			case 14:
				ajudaC(6, led);
				break;
			case 15:
				ajudaC(7, led);
				break;
			case 16:
				ajudaC(8, led);
				break;
			default:
				cont = 0;
				break;
			}
		}
		else if(chave1 && !chave2){
		switch(cont){
			case 1:
				GPIOC->ODR &= 0b0;
				GPIOC->ODR |= led[0];
				break;
			case 2:
				GPIOC->ODR |= led[1];
				break;
			case 3:
				GPIOC->ODR |= led[2];
				break;
			case 4:
				GPIOC->ODR |= led[3];
				break;
			case 5:
				GPIOC->ODR |= led[4];
				break;
			case 6:
				GPIOC->ODR |= led[5];
				break;
			case 7:
				GPIOC->ODR |= led[6];
				break;
			case 8:
				GPIOC->ODR |= led[7];
				break;
			case 9:
				GPIOC->ODR &= ~led[7];
				break;
			case 10:
				GPIOC->ODR &= ~led[6];
				break;
			case 11:
				GPIOC->ODR &= ~led[5];
				break;
			case 12:
				GPIOC->ODR &= ~led[4];
				break;
			case 13:
				GPIOC->ODR &= ~led[3];
				break;
			case 14:
				GPIOC->ODR &= ~led[2];
				break;
			case 15:
				GPIOC->ODR &= ~led[1];
				break;
			case 16:
				GPIOC->ODR &= ~led[0];
				break;
			default:
				cont = 0;
				break;
			}

		}
		else if(!chave1 && !chave2){
			switch(cont){
			case 1:
				GPIOC->ODR |= 0b00000001;
				break;
			case 2:
				GPIOC->ODR |= 0b00000100;
				break;
			case 3:
				GPIOC->ODR |= 0b00010000;
				break;
			case 4:
				GPIOC->ODR |= 0b01000000;
				break;
			case 5:
				GPIOC->ODR |= 0b10000000;
				break;
			case 6:
				GPIOC->ODR |= 0b00100000;
				break;
			case 7:
				GPIOC->ODR |= 0b00001000;
				break;
			case 8:
				GPIOC->ODR |= 0b00000010;
				break;
			case 9:
				GPIOC->ODR &= ~0b00000001;
				break;
			case 10:
				GPIOC->ODR &= ~0b00000100;
				break;
			case 11:
				GPIOC->ODR &= ~0b00010000;
				break;
			case 12:
				GPIOC->ODR &= ~0b01000000;
				break;
			case 13:
				GPIOC->ODR &= ~0b10000000;
				break;
			case 14:
				GPIOC->ODR &= ~0b00100000;
				break;
			case 15:
				GPIOC->ODR &= ~0b00001000;
				break;
			case 16:
				GPIOC->ODR &= ~0b00000010;
				break;
			default:
				cont = 0;
				break;
			}
		}
		TIM10->SR &= 0b0;
	}
  }
}
