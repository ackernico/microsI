/*
 * Monte dois conjuntos de 3 leds, um verde, um amarelo e um vermelho, nas
posi��es de um sem�foro (se n�o tiveres as cores, n�o importa.).
Desenvolva um programa de controle para este sem�foro de dois tempos. O
tempo de verde/vermelho deve ser de 700 ms e o tempo de amarelo aceso �
200ms. Fa�a a sequ�ncia Vd -> Vd/Am -> Vm
Os exerc�cios a seguir utilizam um conjunto de 8 leds montados em linha.
Pode usar um arranjo de leds ou at� mesmo um display..
 */
#include "stm32f4xx.h"

void delay(int t) {
    for (int i = 0; i < t; i++) {
        while ((TIM10->SR & 0x1) == 0);
        TIM10->SR &= ~0x1;
    }
}

int main(void)
{
	RCC->AHB1ENR = 0x87;
	RCC->APB2ENR = 1 << 17;
	RCC->APB1ENR = 0b1;

	GPIOC->MODER |= 0b010101010101;
	GPIOA->MODER |= 0x400;

	TIM10->CR1 |= 0b1;
	TIM10->ARR = 999;
	TIM10->PSC = 1599;

	TIM2->CR1 |= 0b1;
	TIM2->ARR = 999;
	TIM2->PSC = 3199;

	while (1){
		if(TIM10->SR&0x1){
			GPIOC->ODR |= 0b001; //Liga Vd1
			GPIOC->ODR |= 0b100000;//Liga Vm2
			delay(6);
			GPIOC->ODR |= 0b010; //Liga Am1
			delay(2);
			GPIOC->ODR &= ~0b100011;//Desliga Am1 e Vd1 e Vm2
			GPIOC->ODR |= 0b100; //Liga Vm1
			GPIOC->ODR |= 0b001000; //Liga Vd2
			delay(6);
			GPIOC->ODR |= 0b010000;
			delay(2);
			GPIOC->ODR |= 0b100000;
			GPIOC->ODR &= 0b000;
		}
   }
}
