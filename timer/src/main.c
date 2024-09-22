//Timer = 3s (TIM11)
//PSC = 48000 -1 = 47999
//ARR = 1000 -1 = 999

//T = (PSC * ARR) / 160000000
//Tirar 1 de PSC e ARR depois


#include "stm32f4xx.h"

int main(void)
{
	RCC->AHB1ENR |= 0x87;
	RCC->APB2ENR |= 1 << 18; //Ligar o TIM11

	GPIOA->MODER |= 0x28000000; //Habilitar os pinos A14 e A13 como função alternativa
	GPIOA->MODER |= 0x400; //Definir pino do led (A5) como saida digital

	TIM11->PSC = 47999;
	TIM11->ARR = 999;
	TIM11->CR1 |= 0x1; //Habilitando a contagem



  while (1)
  {
	 if(TIM11->SR & 0x1){ //Se o contador acabou,
		 GPIOA->ODR ^= 0x20; //Liga o led
		 TIM11->SR &= 0x0; //Registra o contador como 0
	 }
	 }
}
