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
	DDRA = DDRA | (1 << PA4);	
	
    while(1)
    {
		PORTA = PORTA | (1 << PA4);
		_delay_ms(1000);
		PORTA = 0x00;
		_delay_ms(1000);
    }
}