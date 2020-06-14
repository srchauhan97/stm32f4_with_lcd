//PC0-7 -> D0-7
/*
PB5 = RS
PB6 = RW
PB7 = EN
*/

#include "stm32f4xx.h"


#define RS  5
#define RW  6
#define EN  7

void GPIO_Init(void);
void LCD_cmd(unsigned char cmd);
void LCD_data(char data);
void delayMs(int delay);
void LCD_Init(void);


int main()
{
	//enabling clocks to the ports
	RCC->AHB1ENR |= (1 << 2) | (1 << 1);
	
	LCD_Init();
	while(1)
	{
		LCD_data('A');
	}

}
void GPIO_Init(void)
{
	//Pin configurations to port c
	GPIOC->MODER |= 0x00005555;
	GPIOC->OSPEEDR |= 0x0000AAAA;	
	//pin configuratuons to port b
	GPIOB->MODER |= 0x5400;
	GPIOB->OSPEEDR |= 0xA800;
	
	
}
void LCD_Init()
{
	GPIO_Init();
	
	delayMs(30);
	LCD_cmd(0x30);
	delayMs(10);
	LCD_cmd(0x30);
	delayMs(5);
	LCD_cmd(0x30);	
	
	LCD_cmd(0x38);
	LCD_cmd(0x06);
	LCD_cmd(0x01);
	LCD_cmd(0x0F);

}
void LCD_cmd(unsigned char cmd)
{
	GPIOB->BSRR |= (1 << (RS + 16));    //RS = 0
	GPIOB->BSRR |= (1 << (RW + 16));    //RW = 0
	
	GPIOC->ODR = cmd;
	GPIOB->BSRR |=( 1 << EN);
	delayMs(1);
	GPIOB->BSRR |= (1 <<(EN+16+1));
}
void LCD_data(char data)
{
	GPIOB->BSRR |= (1 << RS);      //RS = 1
	GPIOB->BSRR |= (1 << (RW + 16));
	
	GPIOC->ODR = data;
	GPIOB->BSRR |=( 1 << EN);
	delayMs(1);
	GPIOB->BSRR |= (1 <<(EN+16+1));

}

void delayMs(int delay)
{
	int i;
	while(delay !=0)
	{
		for(i=0;i<5000;i++);
		delay--;
	}
}
