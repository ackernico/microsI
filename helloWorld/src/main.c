/*Exercício 1 : “Hello word!”
*Este é o clássico dos clássicos. Elabore um programa capaz de piscar o Led
*com um ciclo de trabalho de 50% (metade do tempo ligado, metade
*desligado) e com período de 200ms (5 Hz ou 5 piscadas/segundo). O led é
*ativo em LOW e conectado ao PC0. Utilize o TIM11.
 */
#include "stm32f4xx.h"

int main(void)
{
  RCC->AHB1ENR = 0x87;
  RCC->APB2ENR |= 1 << 18; //Ligar o TIM11

  GPIOA->MODER |= 0x28000000;
  GPIOC->MODER |= 0x01;

  TIM11->CR1 = 0x1;
  TIM11->ARR = 999;
  TIM11->PSC = 3199;


	while (1)
  {
	if(TIM11->SR & 0x1){
		GPIOC->ODR ^= 0x1;
		TIM11->SR &= 0x0;
	}
  }
}
