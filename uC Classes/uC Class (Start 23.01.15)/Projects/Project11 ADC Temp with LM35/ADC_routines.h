/*
******************************************************************
Product:	ADC Routine Header file 
Controller:	ATmega8
Clock:		8 MHz (Internal)
FUSE BITS:	LOW C4, HIGH D9
Compiler:	AVR-GCC (ATMEL Studio 6.1)
Author:		SusmImu
Created:	3/13/2013 10:55:10 AM
******************************************************************
*/

#ifndef _ADC_ROUTINES_H_

	#define _ADC_ROUTINES_H_ 
	
	#define ADC_ENABLE				ADCSRA |= (1 << ADEN)
	#define ADC_DISABLE				ADCSRA &= 0x7F
	#define ADC_START_CONVERSION	ADCSRA |= (1 << ADSC)
	
	unsigned char voltage[7];
	extern volatile unsigned char ADC_flag;
	extern volatile unsigned char cycle_counter;
	
	void Init_ADC(void);	
	float Read_ADC_Voltage(unsigned char channel);
		
#endif