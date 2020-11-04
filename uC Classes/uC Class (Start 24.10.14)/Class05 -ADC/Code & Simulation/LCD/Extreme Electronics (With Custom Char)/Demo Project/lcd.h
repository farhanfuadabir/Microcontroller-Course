#include <avr/io.h>
#include <util/delay.h>

#ifndef _LCD_H
#define _LCD_H

#define _CONCAT(a,b) a##b
#define PORT(x) _CONCAT(PORT,x)
#define PIN(x) _CONCAT(PIN,x)
#define DDR(x) _CONCAT(DDR,x)

/************************************************
	LCD CONNECTIONS
*************************************************/
#define LCD_DATA D			//Port PD3-PD6 are connected to D4-D7
#define LCD_DATA_POS 3

#define LCD_E D 			//Enable/strobe signal
#define LCD_E_POS	PD7		//Position of enable in above port

#define LCD_RS B			//RS SIGNAL
#define LCD_RS_POS PB2

#define LCD_RW B			//RW SIGNAL
#define LCD_RW_POS PB0

//***********************************************
//LCD Type Selection
//Uncomment Just one of them

//#define LCD_TYPE_202	//For 20 Chars by 2 lines
//#define LCD_TYPE_204	//For 20 Chars by 4 lines
#define LCD_TYPE_162	//For 16 Chars by 2 lines
//#define LCD_TYPE_164	//For 16 Chars by 4 lines
//************************************************

#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010
#define LS_NONE	 0B00000000

void LCDInit(uint8_t style);
void LCDWriteString(const char *msg);
void LCDWriteInt(int val,unsigned int field_length);
void LCDGotoXY(uint8_t x,uint8_t y);

//Low level
void LCDByte(uint8_t,uint8_t);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void LCDBusyLoop();

//MACROS
#define LCDClear() LCDCmd(0b00000001)
#define LCDHome() LCDCmd(0b00000010);

#define LCDWriteStringXY(x, y, msg) {	\
 LCDGotoXY(x, y);						\
 LCDWriteString(msg);					\
}

#define LCDWriteIntXY(x,y,val,fl) {		\
 LCDGotoXY(x,y);						\
 LCDWriteInt(val,fl);					\
}

#endif