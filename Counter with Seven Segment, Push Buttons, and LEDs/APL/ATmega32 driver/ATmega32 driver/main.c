/*
 * ATmega32_driver.c
 *
 * Created: 2/11/2024 17:02:25
 * Author : Mohammed Ahmed Mansour
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>

#include "7SEGMENT_interface.h"
#include "BUTTON_interface.h"
#include "LED_interface.h"

unsigned char counter = 0;

int main(void)
{
	BCD_to_SEVEN_SEG_Init(portc, 0);
	BCD_to_SEVEN_SEG_Init(portc, 1);
	
	LED_Init(portb, pin6); // Green led
	LED_Init(portb, pin7); // Red led
	
	BUTTON_Init(porta, pin0);
	BUTTON_Init(porta, pin6);
	BUTTON_Init(portb, pin3);
	
	while(1)
	{	
		if(BUTTON_Read(porta, pin0) == 1)
		{
			_delay_ms(500);
			counter ++;
		}
		if(BUTTON_Read(porta, pin6) == 1)
		{
			_delay_ms(500);
			counter --;	
		}
		if(BUTTON_Read(portb, pin3) == 1)
		{
			_delay_ms(500);
			counter = 0;
		}
		if(counter % 2 == 0)
		{
			LED_On(portb, pin6);
			LED_Off(portb, pin7);
		}
		else if(counter % 2 != 0)
		{
			LED_Off(portb, pin6);
			LED_On(portb, pin7);
		}
		BCD_to_SEVEN_SEG_Write(portc, 0, counter%10);
		BCD_to_SEVEN_SEG_Write(portc, 1, counter/10);
	}
}
