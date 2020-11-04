#define F_CPU 8000000UL //Set clock speed to 8.0 MHz

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "USART_Routines.h"
#include "ADC_routines.h"

long ADCValues;
char ADCValuesStr[10];


int main(void)
{
	USART_Init();
	
	Init_ADC();
	
	transmitString_P(PSTR("****************************************************"));
	TX_NEWLINE;
	transmitString_P(PSTR("             ADC Testing"));
	TX_NEWLINE;
	transmitString_P(PSTR("****************************************************"));
	TX_NEWLINE;
	TX_NEWLINE;
	
	
	while(1)
	{
		ADCValues = readADCValue(0);		//Read voltage from selected channel and store in ADCValues array
		ADCValues = (ADCValues * 5000)/1023.0;
		ltoa(ADCValues, ADCValuesStr, 10);	//Convert ADC Value to string to print via USART			
		transmitString(ADCValuesStr);					//Print via USART
		TX_NEWLINE;
		
		ADCValues = readADCValue(1);		//Read voltage from selected channel and store in ADCValues array
		ADCValues = (ADCValues*5000)/1023.0;
		itoa(ADCValues, ADCValuesStr, 10);	//Convert ADC Value to string to print via USART
		transmitString(ADCValuesStr);					//Print via USART
		TX_NEWLINE;
		
		transmitString_P(PSTR("--------------------"));
		TX_NEWLINE;
		_delay_ms(3000);
	}		
}