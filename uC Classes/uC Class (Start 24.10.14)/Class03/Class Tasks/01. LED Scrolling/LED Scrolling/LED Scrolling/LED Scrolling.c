/*
 * LED_Scrolling.c
 *
 * Created: 11/7/2014 9:51:26 AM
 *  Author: SAIYEB
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//Input or Output declaration 
	DDRC = DDRC | 1 << PC0;
	DDRC = DDRC | 1 << PC1;
	DDRC = DDRC | 1 << PC2;
	DDRC = DDRC | 1 << PC3;
	DDRC = DDRC | 1 << PC4;
	DDRC = DDRC | 1 << PC5;
	DDRC = DDRC | 1 << PC6;
	DDRC = DDRC | 1 << PC7;
	//-------------------------
		
    while(1)
    {
        PORTC = PORTC | 1 << PC0;
		_delay_ms(500);
		PORTC = PORTC &(~(1 << PC0));
		_delay_ms(500);
		
		PORTC = PORTC | 1 << PC1;
		_delay_ms(500);
		PORTC = PORTC &(~(1 << PC1));
		_delay_ms(500);
		
		PORTC = PORTC | 1 << PC2;
		_delay_ms(500);
		PORTC = PORTC &(~(1 << PC2));
		_delay_ms(500);
		
		PORTC = PORTC | 1 << PC3;
		_delay_ms(500);
		PORTC = PORTC &(~(1 << PC3));
		_delay_ms(500);
		
		PORTC = PORTC | 1 << PC4;
		_delay_ms(500);
		PORTC = PORTC &(~(1 << PC4));
		_delay_ms(500);
		
		PORTC = PORTC | 1 << PC5;
		_delay_ms(500);
		PORTC = PORTC &(~(1 << PC5));
		_delay_ms(500);
		
		PORTC = PORTC | 1 << PC6;
		_delay_ms(500);
		PORTC = PORTC &(~(1 << PC6));
		_delay_ms(500);
		
		PORTC = PORTC | 1 << PC7;
		_delay_ms(500);
		PORTC = PORTC &(~(1 << PC7));
		_delay_ms(500);
    }
}