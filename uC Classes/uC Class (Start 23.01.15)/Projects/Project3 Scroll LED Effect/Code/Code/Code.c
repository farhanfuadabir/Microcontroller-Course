/*
 * Code.c
 *
 * Created: 2/17/2015 5:47:42 PM
 *  Author: SusmImu
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRC = 0b11111111;
	
	while(1)
	{
		for(char i = 0; i < 8; i++)
		{
			PORTC = 1 << i;
			_delay_ms(500);
		}
	}
}