/*
******************************************************************
Product:	ADC Routine Source file
Controller:	ATmega8
Clock:		8 MHz (Internal)
FUSE BITS:	LOW C4, HIGH D9
Compiler:	AVR-GCC (ATMEL Studio 6.1)
Author:		SusmImu
Created:	3/13/2013 10:55:10 AM
******************************************************************
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC_routines.h"

void Init_ADC(void)				//Initialize the ADC, Conversion time 52uS
{
	ADCSRA = 0x00;				//Clear ADCSRA Register
	ADMUX |= 1 << REFS0;		//Reference is AVCC with external capacitor at AREF pin.
	ADMUX &= ~(1 << ADLAR);		//Right adjust the result	
	
	ADCSRA &= ~(1 << ADPS0);	//Division factor: 4, single conversion mode 
	ADCSRA |= 1 << ADPS1;
	ADCSRA &= ~(1 << ADPS2);	
	ADCSRA |= (1 << ADEN);		//Enable ADC
}

int readADCValue(unsigned char channel)		//Read ADC value from channel
{
	unsigned int ADCH_temp = 0, ADC_temp = 0, ADCValue = 0;
		
	ADMUX = 0b01000000 | channel;			//Select channel
	
	for(unsigned char i = 0; i < 8; i++)	//Do the ADC conversion 8 times for better accuracy
	{
		ADCSRA |= (1 << ADSC);				//Start conversion
		
		while(!(ADCSRA & (1 << ADIF)));		//wait for conversion done
		ADCSRA |= (1 << ADIF);				//ADIF flag active
		
		ADC_temp = ADCL;					//read out ADCL register
		ADCH_temp = ADCH;					//read out ADCH register
		ADC_temp += (ADCH_temp << 8);		//Merge 10 bit result
		
		ADCValue += ADC_temp;				//Accumulate result (8 samples) for later averaging
	}
	
	ADCValue = ADCValue / 8; //Average the 8 samples
	
	return ADCValue;
}