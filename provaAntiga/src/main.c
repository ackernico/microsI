/*
 Voc� foi convocado para projetar e testar a parte eletr�nica de um lan�ador de foguetes.
Esse sistema conta com um display de sete segmentos, duas chaves do tipo contato moment�neo (start e stop) e um led.
O sistema lan�ador funciona da seguinte maneira:
- Inicialmente  no display fica aparecendo o n�mero 9 e este n�mero fica piscando com frequ�ncia de 1Hz. (2,0)
Ao acionar a chave start, o sistema come�a uma contagem decrescente com intervalo de 1,5 segundos, e o display indica o tempo para o disparo.  (2,0)
Quando o contador chega a zero � acionado um led que indica o disparo do foguete.      (1,0)
Este � o funcionamento normal do disparador.
- Por�m problemas podem acontecer nos instantes anteriores � decolagem e o disparo deve ser abortado. Para tanto existe um bot�o stop que, ao ser acionado, para  a contagem (1,0) decrescente e faz o display piscar com frequ�ncia de 3Hz indicando que algo de errado aconteceu e o momento em que isso aconteceu. (2,0)
Voc� dever� apresentar o sistema funcionando, o esquem�tico completo, TODOS os c�lculos dos temporizadores e o c�digo implementado
(chame o professor quando tudo estiver completo).   (2,0)
Postar o c�digo (main.c)�no�classroom.

1HZ - 15999
3HZ - 5332
1.5HZ - 10665
 */
#include "stm32f4xx.h"

int chaveStart;
int chaveStop;

int botaoApertado = 0;
int contando = 0;

int cont = 0;
int verif = 0;

int led[] = {0b00000001,
			 0b00000010,
			 0b00000100,
			 0b00001000,
			 0b00010000,
			 0b00100000,
			 0b01000000,
			 0b10000000
	};

int ledP[] = {0b00000001,
		 	  0b00000011,
			  0b00000111,
			  0b00001111,
			  0b00011111,
			  0b00111111,
			  0b01111111,
		 	  0b11111111
};

void ligaLed(int value){
	GPIOC->ODR |= led[value];
}

void para(){
	if(botaoApertado == 1 || !chaveStop){
		botaoApertado = 1;
		TIM11->CR1 = 0;
		while(botaoApertado){
			if(TIM10->SR & 0x1 && cont != 0){
				GPIOC->ODR ^= ledP[cont-1];
				TIM10->SR &= ~0x1;
			}
		}
	}
}

int main(void)
{
	RCC->AHB1ENR = 0x87;
	RCC->APB2ENR |= 1 << 17;
	RCC->APB2ENR |= 1 << 18;

	GPIOA->MODER |= 0x28000000;
	GPIOC->MODER |= 0b0101010101010101;
	GPIOB->MODER &= ~0b1010;
	GPIOA->MODER |= 0x400;

	GPIOB->PUPDR |= 0b0101;

	TIM11->CR1 |= 0b1;
	TIM11->ARR = 999;
	TIM11->PSC = 15999;

	TIM10->CR1 = 0b1;
	TIM10->ARR = 999;
	TIM10->PSC = 5332;

  while (1)
  {
	chaveStart = GPIOB->IDR & 0b10;
	chaveStop  = GPIOB->IDR & 0b01;

		if(!chaveStart || contando == 1){
				contando = 1;

				if(verif == 1){
					GPIOC->ODR &= 0b0;
					verif = 0;
				}

				TIM11->PSC = 10665;
				para();

					if(TIM11->SR & 0x1){
						cont++;
						switch(cont){
						case 1:
							ligaLed(0);
							break;
						case 2:
							ligaLed(1);
							break;
						case 3:
							ligaLed(2);
							break;
						case 4:
							ligaLed(3);
							break;
						case 5:
							ligaLed(4);
							break;
						case 6:
							ligaLed(5);
							break;
						case 7:
							ligaLed(6);
							break;
						case 8:
							ligaLed(7);
							break;
						case 9:
							GPIOA->ODR |= 0x20;
							break;
						}
						TIM11->SR &= ~0b1;
					}
			}
			else if(contando == 0){
				if(TIM11->SR & 0x1){
					GPIOC->ODR ^= 0b11111111;
					verif = 1;
					TIM11->SR &= ~0b1;
				}
			}
  }
}
