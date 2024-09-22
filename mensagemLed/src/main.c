/*
******************************************************************************
Mensagem no led.
O led de status de um equipamento é utilizado para sinalizar sua condição de
operação, através de uma mensagem visual codificada como piscadas. O
período da mensagem é de 1s e o tempo de cada piscada é de 100 ms,
seguido por 100ms com o led apagado.
As mensagens seguem a codificação dada pela tabela abaixo:

0 - sempre aceso
1 - 1 piscada (15999)
2 - 2 piscadas (3999)
3 - 3 piscadas (2666)
4 - 4 piscadas (1999)
5 - 5 piscadas (1599)

O led é ativo em HIGH, conectado ao PA8.
Utilize os pinos PB3, PB4 e PB5 para entrada do código. Podem ser
utilizados botões, chaves ou mesmo jumpers.

LED = PA8
Botao0 = PB3
Botao1 = PB4
Botao2 = PB5


******************************************************************************
*/
#include "stm32f4xx.h"

void delay_ms(int delay) {
    TIM10->CNT = 0;
    while (TIM10->CNT < delay);  // Espera até atingir o valor desejado
}

int main(void)
{

  int botao0, botao1, botao2, botaoAux;
  int cont;


  RCC->AHB1ENR = 0x87;
  RCC->APB2ENR |= 1 << 17;

  GPIOA->MODER |= 0x28000000;
  GPIOA->MODER |= 0b010000000000000000;
  GPIOA->MODER |= 0x400;
  GPIOB->PUPDR |= 0b010101000000;

  TIM10->CR1 = 0x1;
  TIM10->ARR = 999;
  TIM10->PSC = 1599;

	while (1)
  {

	botao0 = GPIOB->IDR & 0b1000;
	botao1 = GPIOB->IDR & 0b10000;
	botao2 = GPIOB->IDR & 0b100000;
	botaoAux = GPIOC->IDR & 0x2000;

	if(TIM10->SR & 0x1){
		GPIOA->ODR ^= 0x20;

		if((!botao2 || !botaoAux) && botao1 && !botao0){ //5
			if(cont < 11){
				GPIOA->ODR ^= 0b100000000;
				cont++;
			}
			else{
				GPIOA->ODR |= 0b100000000;
			}
		}
		else if((!botao2 || !botaoAux) && botao1 && botao0){ //4
			if(cont < 9){
				GPIOA->ODR ^= 0b100000000;
				cont++;
			}
			else{
				GPIOA->ODR |= 0b100000000;
			}
		}
		else if((botao2 || botaoAux) && !botao1 && !botao0){ //3
			if(cont < 7){
				GPIOA->ODR ^= 0b100000000;
				cont++;
			}
			else{
				GPIOA->ODR |= 0b100000000;
			}
		}
		else if((botao2 || botaoAux) && !botao1 && botao0){ //2
			if(cont < 5){
				GPIOA->ODR ^= 0b100000000;
				cont++;
			}
			else{
				GPIOA->ODR |= 0b100000000;
			}
		}
		else if((botao2 || botaoAux) && botao1 && !botao0){ //1
			if(cont < 3){
				GPIOA->ODR ^= 0b100000000;
				cont++;
			}
			else{
				GPIOA->ODR |= 0b100000000;
			}
		}
		else{
			GPIOA->ODR |= 0b100000000;
			cont = 0;
		}

		TIM10->SR = 0x0;
	}

  }
}
