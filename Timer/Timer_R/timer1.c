#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int count = 0;


ISR(TIMER1_OVF_vect)
{
	count++;
	if (count == 15)				//F_CPU/65535
	{
		PORTC = ~PORTC;				//toggle PORTC
		count = 0;					//reset count
	}
}

void timer1_init()
{
	TCCR1A = 0x00;				//reset timer register
	TCNT1 = 0x00;				//reset timer0
	TIMSK |= (1<<TOIE1);		//Overflow interrupt enable
	TCCR1B |= (1<<CS10);			//Prescaler = Fcpu/1
}

int main(void)
{
	//disable Jtag on PORTC
	MCUCSR |= 1<<JTD;
	MCUCSR |= 1<<JTD;
	
	//PORTC as Output
	DDRC = 0xFF;
	
	//initialize timer0
	timer1_init();
	
	//enable global interrupt
	sei();
	
	while (1)
	{
		
	
	}
}
