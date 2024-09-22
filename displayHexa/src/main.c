/*
Pino Bit 0 = PB0
Pino Bit 1 = PB1
Pino Bit 2 = PB2
Pino bit 3 = PB3

Pino seg A = PC0
Pino seg B = PC1
Pino seg C = PC2
Pino seg D = PC3
Pino seg E = PC4
Pino seg F = PC5
Pino seg G = PC6

0 0000
1 0001
2 0010
3 0011
4 0100
5 0101
6 0110
7 0111
8 1000
9 1001
A 1010
B 1011
C 1100
D 1101
E 1110
F 1111
*/
#include "stm32f4xx.h"

void erase(){
	GPIOC->ODR &= 0b0000000;
}
void num0(){
	erase();
	GPIOC->ODR |= 0b0111111;
}
void num1(){
	erase();
	GPIOC->ODR |= 0b0000110;
}
void num2(){
	erase();
	GPIOC->ODR |= 0b1011011;
}
void num3(){
	erase();
	GPIOC->ODR |= 0b1001111;
}
void num4(){
	erase();
	GPIOC->ODR |= 0b1100110;
}
void num5(){
	erase();
	GPIOC->ODR |= 0b1101101;
}
void num6(){
	erase();
	GPIOC->ODR |= 0b1111101;
}
void num7(){
	erase();
	GPIOC->ODR |= 0b0000111;
}
void num8(){
	erase();
	GPIOC->ODR |= 0b1111111;
}
void num9(){
	erase();
	GPIOC->ODR |= 0b1101111;
}
void chA(){
	erase();
	GPIOC->ODR |= 0b1110111;
}
void chB(){
	erase();
	GPIOC->ODR |= 0b1111100;
}
void chC(){
	erase();
	GPIOC->ODR |= 0b0111001;
}
void chD(){
	erase();
	GPIOC->ODR |= 0b1011110;
}
void chE(){
	erase();
	GPIOC->ODR |= 0b1111001;
}
void chF(){
	erase();
	GPIOC->ODR |= 0b1110001;
}

int main(void)
{
	int chave0;
	int chave1;
	int chave2;
	int chave3;

	RCC->AHB1ENR |= 0x87; // Ligar todos os clocks
	GPIOA->MODER |= 0x28000000; //Definir PA13 e PA14 como função alternativa

	GPIOB->PUPDR = 0x55; // Definir pull up nas entradas
	GPIOC->MODER = 0x1555; //Definir segmentos como saída
  while (1)
  {
	chave0 = ((GPIOB->IDR)&0b0001);
	chave1 = ((GPIOB->IDR)&0b0010);
	chave2 = ((GPIOB->IDR)&0b0100);
	chave3 = ((GPIOB->IDR)&0b1000);

	if(chave3 != 0x0 && chave2 != 0x0 && chave1 != 0x0 && chave0 == 0x0){
		num1();
	}
	else if(chave3 != 0x0 && chave2 != 0x0 && chave1 == 0x0 && chave0 != 0x0){
		num2();
	}
	else if(chave3 != 0x0 && chave2 != 0x0 && chave1 == 0x0 && chave0 == 0x0){
		num3();
	}
	else if(chave3 != 0x0 && chave2 == 0x0 && chave1 != 0x0 && chave0 != 0x0){
		num4();
	}
	else if(chave3 != 0x0 && chave2 == 0x0 && chave1 != 0x0 && chave0 == 0x0){
		num5();
	}
	else if(chave3 != 0x0 && chave2 == 0x0 && chave1 == 0x0 && chave0 != 0x0){
		num6();
	}
	else if(chave3 != 0x0 && chave2 == 0x0 && chave1 == 0x0 && chave0 == 0x0){
		num7();
	}
	else if(chave3 == 0x0 && chave2 != 0x0 && chave1 != 0x0 && chave0 != 0x0){
		num8();
	}
	else if(chave3 == 0x0 && chave2 != 0x0 && chave1 != 0x0 && chave0 == 0x0){
		num9();
	}
	else if(chave3 == 0x0 && chave2 != 0x0 && chave1 == 0x0 && chave0 != 0x0){
		chA();
	}
	else if(chave3 == 0x0 && chave2 != 0x0 && chave1 == 0x0 && chave0 == 0x0){
		chB();
	}
	else if(chave3 == 0x0 && chave2 == 0x0 && chave1 != 0x0 && chave0 != 0x0){
		chC();
	}
	else if(chave3 == 0x0 && chave2 == 0x0 && chave1 != 0x0 && chave0 == 0x0){
		chD();
	}
	else if(chave3 == 0x0 && chave2 == 0x0 && chave1 == 0x0 && chave0 != 0x0){
		chE();
	}
	else if(chave3 == 0x0 && chave2 == 0x0 && chave1 == 0x0 && chave0 == 0x0){
		chF();
	}
	else{
		num0();
	}
  }
}
