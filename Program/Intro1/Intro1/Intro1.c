/*
 * Intro1.c
 *
 * Created: 27/11/2015 3:31:02 PM
 *  Author: TechClass
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
    DDRB=255; 
	while(1)
    {
       /* for (int i=0;i<255;i++)
        {
			PORTB=i;
			_delay_ms(100);
		}
	   PORTB=128;*/
	   for(char i = 0; i < 8; i++)
	   {
		   PORTB = 1 << i;
		   _delay_ms(100);
	   }
    }
	return (0);
}