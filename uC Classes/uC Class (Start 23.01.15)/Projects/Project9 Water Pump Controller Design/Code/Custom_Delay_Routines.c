#include "Custom_Delay_Routines.h"
#include <util/delay.h>
#include <avr/wdt.h>

//*******************************************************************************
void Delay10xMiliseconds(unsigned int valueOfX)		//Make a 10*x ms delay
{
	for(unsigned int i = 0; i < valueOfX; i++)
	{
		wdt_reset();
		_delay_ms(10);
	}
}
//*******************************************************************************