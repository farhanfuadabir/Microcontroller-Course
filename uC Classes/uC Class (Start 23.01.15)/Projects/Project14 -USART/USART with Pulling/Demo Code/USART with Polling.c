/*
 * USART_with_Polling.c
 * Created: 1/25/2014 5:39:08 PM
 *  Author: SAIYEB
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "USART_Routines.h"

char data;

int main(void)
{
	USART_Init();
	
	transmitString("===== USART Library with PULLING =====");
	TX_NEWLINE;
	TX_NEWLINE;
	transmitString_P(PSTR("This string is in FLASH area"));
	TX_NEWLINE;
	transmitString("This string is in RAM area");
	TX_NEWLINE;
	
	while(1)
	{
		data = receiveByte();
		transmitByte(data);
		
		_delay_ms(200);
	}
	
	return 0;
}