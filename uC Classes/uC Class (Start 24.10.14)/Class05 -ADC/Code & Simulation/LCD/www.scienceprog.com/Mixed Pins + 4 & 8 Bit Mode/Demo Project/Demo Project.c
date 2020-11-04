#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <inttypes.h>
#include "lcd_lib.h"

//Strings stored in AVR Flash memory
const uint8_t LCDwelcomeln1[] PROGMEM = "AVR LCD DEMO";
const uint8_t LCDprogress[] PROGMEM = "Loading...";
const uint8_t LCDanimation[] PROGMEM = "LCD animation";

//Additional custom LCD characters
const uint8_t backslash[8] PROGMEM = {0b00000000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00000000, 0b00000000};	//Back slash 

//Delay 1s
void delay1s(void)
{
	uint8_t i;
	for(i = 0; i < 100; i++)
	{
		_delay_ms(10);
	}
}

//Progress bar
void progress(void)
{
	LCDclr();
	
	CopyStringtoLCD(LCDwelcomeln1, 3, 0);
	delay1s();
	
	LCDclr();
	
	CopyStringtoLCD(LCDprogress, 3, 0);
	
	for(uint8_t i = 0; i < 255; i++)
	{
		_delay_ms(10);
		LCDGotoXY(0, 1);
		LCDprogressBar(i, 255, 16);
	}
}

//Animation
void demoanimation(void)
{
	LCDclr();
	
	LCDdefinechar(backslash, 0);
	
	CopyStringtoLCD(LCDanimation, 0, 0);
	
	for(uint8_t i = 0; i < 3; i++)
	{
		LCDGotoXY(8, 1); LCDsendChar(0); delay1s();
		LCDGotoXY(8, 1); LCDsendChar('-'); delay1s();
		LCDGotoXY(8, 1); LCDsendChar('/'); delay1s();
		LCDGotoXY(8, 1); LCDsendChar('|'); delay1s();
		LCDGotoXY(8, 1); LCDsendChar(8); delay1s();
		LCDGotoXY(8, 1); LCDsendChar('-'); delay1s();
		LCDGotoXY(8, 1); LCDsendChar('/'); delay1s();
		LCDGotoXY(8, 1); LCDsendChar('|'); delay1s();
	}
}


int main(void)
{
	LCDinit();	//Initialize the LCD 	
	LCDclr();	//Clears LCD
	
	while(1) 
	{
		progress();
		delay1s();
		demoanimation();
		delay1s();
	}
	
	return 0;
}