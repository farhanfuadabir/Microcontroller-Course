/*
 * USART_with_Polling.c
 * Created: 1/25/2014 5:39:08 PM
 *  Author: SAIYEB
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "USART_Routines.h"

char i = 0;

int main(void)
{
	USART_Init();
	sei();
	
	while(1);
	
	return 0;
}

//***************************************
//     USART, Rx Complete vector
//***************************************
ISR(USART_RXC_vect) 
{
	char receivedData;
	
	receivedData = UDR; //Received byte saved in the variable 'receivedData'
	
	UDR = receivedData; //'receivedData' loaded to UDR 
}

//***************************************
//     USART, Tx Complete vector
//***************************************
ISR(USART_TXC_vect)
{
	const char sampleText[] = "This a sample text";
	
	UDR = sampleText[i];
	
	i++;
	
	if(i > 17)
	{
		i = 0;
		TX_NEWLINE;
		_delay_ms(500);
	}
}