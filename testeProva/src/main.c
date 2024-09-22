#include "stm32f4xx.h"

//Pino Led = PA5
//Pino entrada = PC13

int main(void)
{
	RCC->AHB1ENR = 0x87;
	GPIOA->MODER |= 0x28000000;

	GPIOC->PUPDR |= 0x4000000;
	GPIOA->MODER |= 0x400;

	int verifica;

  while (1)
  {
	  if(verifica == 0){
		  GPIOA->ODR |= 0x20;
	  }
	  else{
		  GPIOA->ODR &= ~0x20;
	  }

	  if((GPIOC->IDR & 0x2000) == 0){
		  GPIOA->ODR |= 0x20;
		  verifica = 1;
	  }else{
		  GPIOA->ODR &= ~0x20;
	  }

  }
}
