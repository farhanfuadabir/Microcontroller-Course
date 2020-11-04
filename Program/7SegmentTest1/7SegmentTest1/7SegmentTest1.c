/*
 * _7SegmentTest1.c
 *
 * Created: 12/12/2015 10:18:54 AM
 *  Author: TechClass
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


// #define zero		0x3F
// #define one		0x06
// #define two		0x5B
// #define three		0x4F
// #define four		0x66
// #define five		0x6D
// #define six		0x7D
// #define seven	0x07
// #define eight		0x7F
// #define nine		0x6F
	
uint8_t digit[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

int main(void)
{
    DDRB=0xFF;
	while(1)
    {
        //TODO:: Please write your application code 
		for (int i=0;i<10;i++)
		{
 			PORTB=digit[i];
 			_delay_ms(500);
 		}
		/*PORTB=zero;
		_delay_ms(500);
		PORTB=one;
		_delay_ms(500);
		PORTB=two;
		_delay_ms(500);
		PORTB=three;
		_delay_ms(500);
		PORTB=four;
		_delay_ms(500);
		PORTB=five;
		_delay_ms(500);
		PORTB=six;
		_delay_ms(500);
		PORTB=seven;
		_delay_ms(500);
		PORTB=eight;
		_delay_ms(500);
		PORTB=nine;
		_delay_ms(500);*/
    }
}