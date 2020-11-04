/*
 * _10.c
 *
 * Created: 11/25/2012 12:43:05 PM
 *  Author: SusmImu 
 * Using Timer0 and Timer1 interrupts, write a program in which: 
  (a) PORTA counts up every time Timer1 overflows. It overflows once per second. 
  (b) A pulse is fed into Timer0 where Timer0 is used as counter and counts up. 
  Whenever the counter reaches 5, it will toggle the pin PORTB.6. 
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRA = 0xFF;							//Set PORTA output 
	DDRB |= 0x40;							//Set PORTB6 output 
	DDRB &= 0xFE;							//Set PORTB0 input 
	DDRC = 0x00;
	DDRD = 0xFF;
	
	PORTB |= 0x01;							//Activate pull-up 
	
	TCNT0 = -5;								//Load Timer0 with -5 
	TCCR0 = 0x06;							//Normal mode, Falling edge, No prescaler 
	
	TCNT1H = (-31250) >> 8;					//The high byte 
	TCNT1L = (-31250) & 0xFF;				//Overflow after 31250 clocks 
	TCCR1A = 0x00;							//Normal mode 
	TCCR1B = 0x04;							//Internal clock, prescaler 1:256 
	
	TIMSK = (1 << TOIE0) | (1 << TOIE1);	//Enable T0 and T1 interrupt 
	sei();									//Enable interrupts 	
	
	
    while(1)
    {
		PORTD = PINC;        
    }
}

ISR(TIMER0_OVF_vect)						//ISR for Timer0 overflow 
{
	TCNT0 = -5;
	PORTB ^= 0x40;
}

ISR(TIMER1_OVF_vect)						//ISR for Timer1 overflow 
{
	TCNT1H = (-31250) >> 8;
	TCNT1L = (-31250) & 0xFF; 
	
	PORTA ++;
}