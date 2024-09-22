#include "stm32f4xx.h"

void delay(){
	for(int i=0 ; i<200000 ; i++);
}

int main(void)
{
	int estadobotao;
	int estadoLed;

	RCC->AHB1ENR |= 0x87; // Ligar todos os clocks

	GPIOB->PUPDR = 0b01;
	GPIOC->MODER = 0b01;

	GPIOB->OSPEEDR = 0b00;

	estadoLed=0;

  while (1)
  {
	  estadobotao = ((GPIOB->IDR) & 0b01);

	  if(estadobotao == 0){
		  delay();
		  if(estadoLed == 1){
			  GPIOC->ODR &= 0x0;
			  estadoLed = 0;
		  }
		  else{
			  GPIOC->ODR |= 0x1;
			  estadoLed = 1;
		  }
	  }

	  //delay();
  }
}
