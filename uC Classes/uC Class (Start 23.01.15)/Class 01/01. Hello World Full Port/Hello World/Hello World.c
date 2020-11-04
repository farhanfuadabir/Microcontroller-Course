/*
 * Hello_World.c
 *
 * Created: 11/5/2014 7:44:51 PM
 *  Author: SAIYEB
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA = 0xFF; //0b11111111
	
    while(1)
    {
		PORTA = 0xFF;
		_delay_ms(1000);
		PORTA = 0x00;
		_delay_ms(1000);
    }
}