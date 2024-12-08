/*
 * ATmega32_driver.c
 *
 * Created: 2/11/2024 17:02:25
 * Author : Mohammed Ahmed Mansour
 */ 

#include <avr/interrupt.h>

#include "ADC_interface.h"
#include "EXTI_interface.h"

#include "LCD_interface.h"
#include "LED_interface.h"

const unsigned char  vref = 5;

unsigned char toggle_degree = 0;
unsigned char degree = 'C';

float temp;

int main(void)
{
	ADC_Init(A0);
	
	LCD_Init();
	
	LED_Init(portb, pin7);
	
	EXTI_vEnable(EXTI2);
	EXTI_vActiveMode(EXTI2, RISING);
	
	while(1)
	{
		temp = ADC_Read(A0);
		temp = (temp * vref) / (1024 * 0.01);
		
		if(temp >= 25)
		{
			LED_On(portb, pin7);
		}
		else
		{
			LED_Off(portb, pin7);
			temp++;
		}
		
		if(toggle_degree % 2 != 0)
		{
			temp = (temp * 9/5) + 32;
			degree = 'F';
		}
		else
		{
			degree = 'C';
		}
		
		LCD_SendCommand(RETURN_HOME);
		LCD_SendString("Temp: ");
		LCD_SendNumber(temp);
		LCD_SendChar(degree);
	}
}

ISR(INT2_vect)
{
	toggle_degree++;
}