#define F_CPU 8000000UL									//Set clock speed to 8.0 MHz

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "ADC_routines.h"
#include "lcd_lib.h"
#include "USART_Routines.h"

float ADC0Volt = 0;
float temperature = 0;
char temperatureText[10];

int main(void)
{
	Init_ADC();
	USART_Init();
	
		
	while(1)
	{
		ADC0Volt = Read_ADC_Voltage(0);			//Read Volt from ADC channel0 		
		
		temperature = ADC0Volt / 10;
		
		
		
		itoa((int)temperature, temperatureText, 10);
		
		transmitString(temperatureText);
		
		TX_NEWLINE;
		
		
		
		_delay_ms(1000);
	}

	return 0;
}