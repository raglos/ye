
#include "stm32f4xx.h"

void LED_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED_On(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
}

void LED_Off(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
}

void flip() {
	static int i;
	if (i&1)
		LED_On();
	else
		LED_Off();
	i++;
}

int main(void)
{
	int i;
	LED_Init ();
A:
	for (i=0; i < 2000000; i++) {
		asm ("\t nop");
	}
	flip ();
	goto A;
}
