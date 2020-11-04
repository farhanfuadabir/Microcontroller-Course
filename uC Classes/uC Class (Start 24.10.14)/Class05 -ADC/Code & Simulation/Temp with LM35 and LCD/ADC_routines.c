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
	ADMUX  |= 1 << REFS0;		//Reference is AVCC with external capacitor at AREF pin, Right adjust the result.
	ADCSRA |= 1 << ADEN;		//Division factor: 4, single conversion mode
	ADCSRA |= 1 << ADPS1;		//Division factor: 4, single conversion mode
	
	ADCSRA |= (1 << ADEN);
}

float Read_ADC_Voltage(unsigned char channel)		//Read voltage from ADC channels. Parameter: unsigned char ADC channel number. returns: None (modifies the global string 'voltage')
{
	unsigned int ADCH_temp = 0, ADC_temp = 0, ADCValue = 0;
	char i;
	float ADCVolt = 0;
	
	ADMUX = 0x40 | channel;
	/******************** ADC just read for the first time to discard garbage data STA ********************/
	ADC_START_CONVERSION;
	while(!(ADCSRA & 0x10));						//wait for conversion done, ADIF flag active
	ADCSRA |= (1 << ADIF);
	/******************** ADC just read for the first time to discard garbage data END ********************/
	
	for(i = 0; i < 8; i++)							// do the ADC conversion 8 times for better accuracy
	{
		ADC_START_CONVERSION;
		while(!(ADCSRA & 0x10));					//wait for conversion done, ADIF flag active
		ADCSRA |= (1 << ADIF);
		
		ADC_temp = ADCL;							//read out ADCL register
		ADCH_temp = ADCH;							//read out ADCH register
		ADC_temp += (ADCH_temp << 8);				//Merge 10 bit result
		ADCValue += ADC_temp;						// accumulate result (8 samples) for later averaging
	}
	
	ADCValue = ADCValue >> 3;						// average the 8 samples
	
	ADCVolt = ((ADCValue / 1023.00) * 5000.00);
	
	return ADCVolt;
}