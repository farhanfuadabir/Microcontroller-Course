/************************************************************
Library functions to access the popular DS1307 RTC IC with AVR
Micro controller. 
The library has just two functions. One reads the register whose
address is provided. Other writes to the given register with
given data. Please see DS1307 Data sheet for more info on
the registers. 
Requires eXtreme Electronics Low Level I2C Library. 
************************************************************/
#include <avr/io.h>
#include "i2c_lib.h"
#include "ds1307_lib.h"

/***************************************************
Function To Read Internal Registers of DS1307
---------------------------------------------
address: Address of the register 
data: value of register is copied to this. 

Returns:
0 = Failure
1 = Success
***************************************************/

uint8_t DS1307Read(uint8_t address, uint8_t *data)
{
	uint8_t res;	//result
	
	//Start
	I2CStart();
	
	//SLA + W (for dummy write to set register pointer)
	res = I2CWriteByte(0b11010000);	//DS1307 address + W
	
	//Error
	if(!res)	return FALSE;
	
	//Now send the address of required register
	res = I2CWriteByte(address);
	
	//Error
	if(!res)	return FALSE;
	
	//Repeat Start
	I2CStart();
	
	//SLA + R
	res = I2CWriteByte(0b11010001);	//DS1307 Address + R
	
	//Error
	if(!res)	return FALSE;
	
	//Now read the value with NACK
	res = I2CReadByte(data,0);
	
	//Error
	if(!res)	return FALSE;
	
	//STOP
	I2CStop();
	
	return TRUE;
}

/***************************************************
Function To Write Internal Registers of DS1307
---------------------------------------------
address: Address of the register
data: value to write.

Returns:
0= Failure
1= Success
***************************************************/

uint8_t DS1307Write(uint8_t address, uint8_t data)
{
	uint8_t res;	//result
	
	//Start
	I2CStart();
	
	//SLA+W
	res = I2CWriteByte(0b11010000);	//DS1307 address + W
	
	//Error
	if(!res)	return FALSE;
	
	//Now send the address of required register
	res = I2CWriteByte(address);
	
	//Error
	if(!res)	return FALSE;
	
	//Now write the value
	res = I2CWriteByte(data);
	
	//Error
	if(!res)	return FALSE;
	
	//STOP
	I2CStop();
	
	return TRUE;
}