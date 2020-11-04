/*
 * Buzzer_Example.c
 *
 * Created: 12/12/2015 12:07:35 PM
 *  Author: TechClass
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1<<PB3);
    while(1)
    {
        //TODO:: Please write your application code 
		for (int i=0;i<1000;i++)
		{
			PORTB |= (1<<PB3);
			_delay_ms(100);
			PORTB &= ~(1<<PB3);
			_delay_ms(200);
		}
		
    }
}