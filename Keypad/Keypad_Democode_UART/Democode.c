/*
 * Democode.c
 * Created: 29/12/2015 9:44:52 PM
 *  Author: Shakran
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "USART_Routines.h"

#define WAIT 20


int main(void)
{
	DDRB  = 0b00001111; //Bit 0-3 is OUTPUT, Bit 4-7 is INPUT
	PORTB = 0b11111111; //Bit 0-3 is SET, Bit 4-7 is PULLED UP
	
	USART_Init();
	
	while(1)
	{
		for(unsigned char i = 0; i < 4; i++)
		{
			_delay_ms(WAIT);
			PORTB = ~(1 << i);
			_delay_ms(WAIT);
			
			//------------------------------------------------------
			if(((PINB & 0b00000001) == 0) && ((PINB & 0b10000000) == 0))
			{
				transmitByte('1');
				while(((PINB & 0b00000001) == 0) && ((PINB & 0b10000000) == 0))
					_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x01)) && (!(PINB & 0x40)))
			{
				transmitByte('2');
				while((!(PINB & 0x01)) && (!(PINB & 0x40)))
				_delay_ms(WAIT);				
			}
			//------------------------------------------------------
			if((!(PINB & 0x01)) && (!(PINB & 0x20)))
			{
				transmitByte('3');
				while((!(PINB & 0x01)) && (!(PINB & 0x20)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x01)) && (!(PINB & 0x10)))
			{
				transmitByte('A');
				while((!(PINB & 0x01)) && (!(PINB & 0x10)))
				_delay_ms(WAIT);
			}
			//======================================================
			if((!(PINB & 0x02)) && (!(PINB & 0x80)))
			{
				transmitByte('4');
				while((!(PINB & 0x02)) && (!(PINB & 0x80)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x02)) && (!(PINB & 0x40)))
			{
				transmitByte('5');
				while((!(PINB & 0x02)) && (!(PINB & 0x40)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x02)) && (!(PINB & 0x20)))
			{
				transmitByte('6');
				while((!(PINB & 0x02)) && (!(PINB & 0x20)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x02)) && (!(PINB & 0x10)))
			{
				transmitByte('B');
				while((!(PINB & 0x02)) && (!(PINB & 0x10)))
				_delay_ms(WAIT);
			}
			//======================================================
			if((!(PINB & 0x04)) && (!(PINB & 0x80)))
			{
				transmitByte('7');
				while((!(PINB & 0x04)) && (!(PINB & 0x80)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x04)) && (!(PINB & 0x40)))
			{
				transmitByte('8');
				while((!(PINB & 0x04)) && (!(PINB & 0x40)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x04)) && (!(PINB & 0x20)))
			{
				transmitByte('9');
				while((!(PINB & 0x04)) && (!(PINB & 0x20)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x04)) && (!(PINB & 0x10)))
			{
				transmitByte('C');
				while((!(PINB & 0x04)) && (!(PINB & 0x10)))
				_delay_ms(WAIT);
			}
			//======================================================
			if((!(PINB & 0x08)) && (!(PINB & 0x80)))
			{
				transmitByte('*');
				while((!(PINB & 0x08)) && (!(PINB & 0x80)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x08)) && (!(PINB & 0x40)))
			{
				transmitByte('0');
				while((!(PINB & 0x08)) && (!(PINB & 0x40)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x08)) && (!(PINB & 0x20)))
			{
				transmitByte('#');
				while((!(PINB & 0x08)) && (!(PINB & 0x20)))
				_delay_ms(WAIT);
			}
			//------------------------------------------------------
			if((!(PINB & 0x08)) && (!(PINB & 0x10)))
			{
				transmitByte('D');
				while((!(PINB & 0x08)) && (!(PINB & 0x10)))
				_delay_ms(WAIT);
			}			
			//=======================END============================
		}
	}
}