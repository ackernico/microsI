#include "stm32f4xx.h"

void verificaBin(int in, int out){
	if((GPIOB->IDR & in) == 0){
			  GPIOC->ODR |= out;
		  }
		  else{
			  GPIOC->ODR &= ~out;
		  }
}
int main(void)
{
	RCC->AHB1ENR |= 0x87; // Ligar todos os clocks

	GPIOB->PUPDR |= 0x15;   //Definir pull up nas chaves
	GPIOC->MODER |= 0b01010101010101; // Definir pinos de saída (LED)
	GPIOA->MODER |= 0x28000000; //Definir PA13 e PA14 como função alternativa


  while (1)
  {
	 verificaBin(0b001, 0b1); // 001
	 verificaBin(0b010, 0b11); //010
	 verificaBin(0b011, 0b111); //011
	 verificaBin(0b100, 0b1111); //100
	 verificaBin(0b101, 0b11111); //101
	 verificaBin(0b110, 0b111111); //110
	 verificaBin(0b111, 0b1111111); // 110
  }
}
