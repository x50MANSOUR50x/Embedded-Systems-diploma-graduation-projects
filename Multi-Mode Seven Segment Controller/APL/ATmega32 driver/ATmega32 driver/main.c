/*
 * ATmega32_driver.c
 *
 * Created: 2/11/2024 17:02:25
 * Author : Mohammed Ahmed Mansour
 */ 

#include <avr/interrupt.h>

#include "ADC_interface.h"
#include "EXTI_interface.h"

#include "7SEGMENT_interface.h"

float reading;

int counter = 0;

int initial_pot_value = 0;

int main(void)
{
	ADC_Init(A0);
	
	EXTI_vEnable(EXTI0);
	EXTI_vActiveMode(EXTI0, RISING);
	
	EXTI_vEnable(EXTI1);
	EXTI_vActiveMode(EXTI1, RISING);
	
	EXTI_vEnable(EXTI2);
	EXTI_vActiveMode(EXTI2, RISING);
	
	BCD_to_SEVEN_SEG_Init(portc, 0);
	BCD_to_SEVEN_SEG_Init(portc, 1);
	
	while(1)
	{
		reading = ADC_Read(A0);
		
		if(initial_pot_value != ADC_Read(A0))
		{
			counter = (reading / 1023) * 99;
		}

		
		initial_pot_value = reading;

		
		BCD_to_SEVEN_SEG_Write(portc, 0, counter%10);
		BCD_to_SEVEN_SEG_Write(portc, 1, counter/10);
	}
}

ISR(INT0_vect)
{
	counter ++;
}

ISR(INT1_vect)
{
	counter --;
}

ISR(INT2_vect)
{
	counter = 0;
}