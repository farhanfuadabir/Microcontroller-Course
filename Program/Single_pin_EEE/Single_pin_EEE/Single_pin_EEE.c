/*
 * Single_pin_EEE.c
 *
 * Created: 10/12/2015 3:42:27 PM
 *  Author: TechClass
 */ 


#define F_CPU 8000000UL
#define Desire_pin	7
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |=(1<<Desire_pin);
	while(1)
	{
		//TODO:: Please write your application code
		PORTD |=(1<<Desire_pin);
		_delay_ms(500);
		PORTD &= ~(1<<Desire_pin);
		_delay_ms(500);
	}
}