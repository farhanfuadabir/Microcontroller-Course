/*
 * WPC.c
 *
 * Created: 8/31/2014 11:07:03 PM
 * Author: SAIYEB
 *
 * LOW  = 0xE4 
 * HIGH = 0xD9
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/wdt.h>
#include "Custom_Delay_Routines.h"
#include <util/delay.h>

#define STARTUP_DELAY 500

#define ROOF_TANK_EMPTY  !(PINC & 1 << PC2)
#define RESRV_TANK_NOT_EMPTY  !(PINB & 1 << PB3)
#define UP_MOT_ON  PORTD |=  (1 << PD7)
#define UP_MOT_OFF PORTD &= ~(1 << PD7)

#define RESRV_TANK_FULL       !(PINC & 1 << PC3)
#define RESRV_TANK_EMPTY      !(PINC & 1 << PC4)
#define WASA_WTR_AVAILABLE    !(PINC & 1 << PC5)
#define WASA_WTR_NOT_AVAILABLE (PINC & 1 << PC5)
#define WASA_MOT_ON  PORTB |=  (1 << PB0)
#define WASA_MOT_OFF PORTB &= ~(1 << PB0)

#define HEART_BIT (PORTB |= 1 <<PB1); Delay10xMiliseconds(3); (PORTB &= ~(1 << PB1)); Delay10xMiliseconds(295)

void Init_uC_Ports(void);

unsigned int wasaMotOnCounter    = 0;
unsigned int oneHourDelayCounter = 0;

unsigned char wasaMotOnFlag = 0;

unsigned int dutyCycle = 0;

unsigned char edgeFlag = 0;

#define dutyCycle OCR1A 

int main(void)
{
	Delay10xMiliseconds(STARTUP_DELAY); //5 Seconds	
	Init_uC_Ports();
	wdt_enable(WDTO_2S);
	
	
	while(1)
    {
		//-----------------------------------------
		HEART_BIT;
		//-----------------------------------------
				
		//-----------------------------------------
		if(ROOF_TANK_EMPTY && RESRV_TANK_NOT_EMPTY) 
			UP_MOT_ON;
		else 
			UP_MOT_OFF;
		//-----------------------------------------
		
		//-----------------------------------------
		if(RESRV_TANK_FULL)
		{
			WASA_MOT_OFF;
			wasaMotOnCounter = 0;
		}
		else if(RESRV_TANK_EMPTY && WASA_WTR_AVAILABLE)
		{
			WASA_MOT_ON;
			wasaMotOnCounter = 0;
		}
		else if(RESRV_TANK_EMPTY && WASA_WTR_NOT_AVAILABLE && (wasaMotOnCounter < 5))
		{
			WASA_MOT_ON;
		}
		
		wasaMotOnCounter++; //Increment/3Sec
		
		if(wasaMotOnCounter > 19)
		{
			wasaMotOnCounter = 0;
		}		
		else if(wasaMotOnCounter > 4)
		{
			WASA_MOT_OFF;
		}
		//-----------------------------------------
	}
}

void Init_uC_Ports(void)
{
	//-----------------------------------------
	DDRB |= (1 << PB0) | (1 << PB1);	
	DDRB &= ~(1 << PB3);
	DDRB &= ~(1 << PB4);
	
	PORTB &= ~(1 << PB0);
	PORTB |= (1 << PB3) | (1 << PB4);
	//-----------------------------------------
	DDRC &= ~(1 << PC1);
	DDRC &= ~(1 << PC2);
	DDRC &= ~(1 << PC3);
	DDRC &= ~(1 << PC4);
	DDRC &= ~(1 << PC5);

	PORTC |= (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5);
	//-----------------------------------------
	DDRD &= ~(1 << PD5);
	DDRD &= ~(1 << PD6);	
	DDRD |= (1 << PD7);
	
	PORTD |= (1 << PD5) | (1 << PD6);
	PORTD &= ~(1 << PD7);
	//-----------------------------------------
}