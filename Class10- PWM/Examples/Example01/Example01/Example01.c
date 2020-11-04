/*
 * Example01.c
 *
 * Created: 12/6/2014 9:02:54 PM
 *  Author: Shakran
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA &= ~(1 << PA3); //Input for switch
	DDRD |= 1 << PD5; //Output for Motor
	
    while(1)
    {
		if(!(PINA & (1 << PA3))) //If switch is pressed
		{
			PORTD |= 1 << PD5;
			_delay_ms(80);
			PORTD &= ~(1 << PD5);
			_delay_ms(20);
		}
		else
		{
			PORTD |= 1 << PD5;
			_delay_ms(20);
			PORTD &= ~(1 << PD5);
			_delay_ms(80);
		}
	}
}