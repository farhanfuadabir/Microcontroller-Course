

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "USART_Routines.h"

char data;

int main(void)
{
	UCSRB = (1 << RXEN) | (1 << TXEN );						//Turn on the transmission and reception circuitry
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0 );	// Use 8- bit character sizes
	
	UBRRH = (BAUD_PRESCALE >> 8);							//Load upper 8- bits of the baud rate value into the high byte of the UBRR register
	UBRRL = BAUD_PRESCALE;	

	//UBRR = 51;
	
	//USART_Init();
	
	transmitString("===== USART Library with PULLING =====");

	TX_NEWLINE;
	
	DDRB = 0xFF;
	
	while(1)
	{
		data = receiveByte();
		
		transmitByte(data);
		
		if (data == 'a')
		{
			PORTB = 0xFF;
		}
		else if (data == 'b')
		{
			PORTB = 0x00;
		}



	}
	
	return 0;
}