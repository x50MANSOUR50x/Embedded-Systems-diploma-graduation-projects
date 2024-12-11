/*
 * ATmega32_driver.c
 *
 * Created: 2/11/2024 17:02:25
 * Author : Mohammed Ahmed Mansour
 */ 

#include <avr/interrupt.h>

#include "EXTI_interface.h"
#include "LCD_interface.h"
#include "ADC_interface.h"
#include "LED_interface.h"
#include "7SEGMENT_interface.h"

short int map(float x, float in_min, float in_max, float out_min, float out_max);

const unsigned char  vref = 5;

int temp_sensor_reading = 0;
float LDR_reading = 0;

unsigned char temp_button_counter = 0;
unsigned char toggle_button_counter = 0;

unsigned char degree = 'C';

float temp;
float light_intensity;

int value1= 0;
int value2= 0;

int main(void)
{
	ADC_Init(A0);
	ADC_Init(A7);
	
	LED_Init('B', pin0);
	LED_Init('B', pin1);

	LCD_Init();
	
	BCD_to_SEVEN_SEG_Init(portd, 1);
	BCD_to_SEVEN_SEG_Init(portb, 1);
	
	EXTI_vEnable(EXTI0);
	EXTI_vActiveMode(EXTI0, RISING);
	
	EXTI_vEnable(EXTI1);
	EXTI_vActiveMode(EXTI1, RISING);
	
	EXTI_vEnable(EXTI2);
	EXTI_vActiveMode(EXTI2, RISING);
	
	LCD_SendCommand(CURSOR_ON_DISPLAY_OFF);
	while(1)
	{
		degree = 0;
		
		temp_sensor_reading = ADC_Read(A0);
		LDR_reading = ADC_Read(A7);
		
		LDR_reading = map(LDR_reading, 10, 975, 0, 1023);
		light_intensity = ((LDR_reading/1023) * 100);
		// light_intensity = LDR_reading;

		temp = (temp_sensor_reading * vref) / (1024 * 0.01);
		
		if(temp >= 30)
			{
				LED_On('B', pin0);
			}
		else
			{
				LED_Off('B', pin0);
			}
		
		if(light_intensity >= 70)
			{
				LED_On('B', pin1);
			}
		else
			{
				LED_Off('B', pin1);
			}		

		
		if(temp_button_counter %2 != 0)
		{
			temp = (temp * 9/5) + 32;
			degree = 'F';
		}
		else
		{
			degree = 'C';
		}
		
		LCD_ClearScreen();
	
		if(toggle_button_counter %2 == 0)
		{
			LCD_MoveCursor(1, 1);
			LCD_SendString("Temp: ");
			LCD_SendNumber(temp);
			LCD_SendChar(degree);
				
			value2 = light_intensity;
			if(value2 == 100)
			{
				BCD_to_SEVEN_SEG_Write(portd, 1, 9);
				BCD_to_SEVEN_SEG_Write(portb, 1, 9);
			}
			else
			{
				BCD_to_SEVEN_SEG_Write(portd, 1, value2/10);
				BCD_to_SEVEN_SEG_Write(portb, 1, value2%10);
			}
		}
		else
		{
			LCD_MoveCursor(1, 1);
			LCD_SendString("Light: ");
			LCD_SendNumber(light_intensity);
			LCD_SendChar('%');
			
			value1 = temp;
			if(value1 >= 99)
			{
				BCD_to_SEVEN_SEG_Write(portd, 1, 9);
				BCD_to_SEVEN_SEG_Write(portb, 1, 9);
			}
			else
			{
				BCD_to_SEVEN_SEG_Write(portd, 1, temp/10);
				BCD_to_SEVEN_SEG_Write(portb, 1, value1%10);
			}
		}
		_delay_ms(500);
	}
}

ISR(INT0_vect)
{
	temp_button_counter = 0;
	toggle_button_counter = 0;
}

ISR(INT1_vect)
{
	_delay_ms(200);
	temp_button_counter ++;
}

ISR(INT2_vect)
{
	_delay_ms(200);
	toggle_button_counter ++;
}

short int map(float x, float in_min, float in_max, float out_min, float out_max) 
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
