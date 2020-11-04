/*
 * Digital_Clock_V0.2.c
 *
 * Created: 10/6/2015 4:16:06 PM
 * Author : Shakran
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "I2C_lib.h"
#include "DS3232M_lib.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define DISP_SELECT_PORT				PORTD

#define STB_LOW()						(PORTB &= ~(1<<PB1))
#define STB_HIGH()						(PORTB |= (1<<PB1))


#define MENU_BUTTON						(PORTC & 0x01)
#define PLUS_BUTTON						(PORTC & 0x02)
#define MINUS_BUTTON					(PORTC & 0x04)
#define EXIT_BUTTON						(PORTC & 0x80)


/************************************************************************/
/*                                                                      */
/************************************************************************/
///////Seven Segment Font: 0,	1,	 2,   3,   4,   5,   6,   7,   8,   9,   -,  BLANK, A,	,P
volatile uint8_t font[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40,0x00,0x77,0x73};
	
//volatile uint8_t digit_selection_val[] = {0b11111110,0b11111101,0b11111011,0b11110111,0b11101111,0b11011111,0b10111111,0b01111111};
//const uint8_t digit_selection_val[] = {0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};

unsigned char second=47, minute=59, hour=12;

/************************************************************************/
/*                                                                      */
/************************************************************************/
 struct Display
 {
	 uint8_t select;
	 uint8_t buffer[8];
	 
 }volatile display;

volatile uint8_t display_buffer[8];
/************************************************************************/
/*                                                                      */
/************************************************************************/
void Timer1_Init()
{
	TCCR1B|=(1<<CS10)|(1<<CS11)|(1<<WGM12);
	OCR1A = 0xF9; // 1 ms
	TIMSK|=(1<<OCIE1A);
}
void SPI_Init()
{
	DDRB |= (1<<5)|(1<<3);
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_send(uint8_t data)
{
	SPDR = data;                       //Load data into the buffer
	while(!(SPSR & (1<<SPIF) ));
}

void Set_Display(uint8_t hour_t, uint8_t minute_t, uint8_t second_t)
{
	display_buffer[0] = hour_t/10;
	display_buffer[1] = hour_t%10;
	
	display_buffer[2] = minute_t/10;
	display_buffer[3] = minute_t%10;
	
	display_buffer[4] = second_t/10;
	display_buffer[5] = second_t%10;
	
	display_buffer[6] = 0;
	display_buffer[7] = 0;
}

void Refresh_Display()
{	
	display.select++;
	if(display.select >= 8) display.select = 0;

	//DISP_SELECT_PORT = ~(1<<display.select);
	
	STB_LOW();
	SPI_send(~(1<<display.select));
	SPI_send(font[display_buffer[display.select]]);
	STB_HIGH();
}

ISR(TIMER1_COMPA_vect)
{
	Refresh_Display();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(void)
{
	DDRB = 0xFF;
	DDRC = 0xF0;
	DDRD = 0xFF;
	
	Timer1_Init();
	SPI_Init();
	sei();
	
	Set_Display(12,34,55);
	
	uint8_t sec=0, min=0, hour=0;
	
    while (1) 
    {	
		sec++;
		
		if(sec > 59)
		{
			min++;
			sec = 0;
		}
		
		if(min > 59)
		{
			hour++;
			min = 0;
		}
		
		Set_Display(hour,min,sec);
		_delay_ms(100);
    }
}

