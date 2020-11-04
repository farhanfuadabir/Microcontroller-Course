/*
 * ButtonAndLed.c
 *
 * Created: 08/12/2015 4:33:54 PM
 *  Author: TechClass
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD &= ~(1<<PD0);// input as switch
	DDRD |= (1<<PD7);// as output
	while(1)
    {
        //TODO:: Please write your application code 
		if (!(PIND & (1<<PD0)))
		{
			PORTD |=(1<<PD7);
			_delay_ms(1000);
			PORTD &= ~(1<<PD7);
		}
    }
}