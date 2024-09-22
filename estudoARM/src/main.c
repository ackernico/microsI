#include "stm32f4xx.h"

int main(void)
{

  RCC->AHB1ENR = 0x87; //Habilitar o clock de todas as portas GPIO
  GPIOA->MODER |= 0x28000000; //Habilitar os pinos A14 e A13 como fun��o alternativa

  GPIOA->MODER |= 0x400; //Definir pino do led (A5) como saida digital
  //N�o � necess�rio definir o pino do bot�o como entrada digital pois os pinos do ARM s�o definidos por padr�o como sa�da

	while (1)
  {
	if((GPIOC->IDR & 0x2000) == 0){
		GPIOA->ODR |= 0x20;
	}
	else{
		GPIOA->ODR &= ~0x20;
	}
  }
}
