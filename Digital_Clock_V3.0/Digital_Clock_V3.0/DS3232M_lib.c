/*
 * DS3232M_lib.c
 *
 * Created: 9/18/2015 1:31:46 AM
 *  Author: Shakran
 */ 
#include <avr/io.h>
#include "I2C_lib.h"
#include "DS3232M_lib.h"

/***************************************************
Function To Read Internal Registers of DS3232M
---------------------------------------------
address: Address of the register
data: value of register is copied to this.

Returns:
0 = Failure
1 = Success
***************************************************/


uint8_t DS3232M_Read(uint8_t address, uint8_t *data)
{
		uint8_t res;											//result
		
		I2CStart();												//Start		
		res = I2CWriteByte(DS3232M_ADDRESS_WRITE_COMMAND);		//SLA + W (for dummy write to set register pointer)                                	
		
		if(!res)	return FALSE;								//Error Checking!! 
		
		res = I2CWriteByte(address);							//Now send the address of required register
		
		if(!res)	return FALSE;								//Error
				
		I2CStop();												//STOP I2C		
		I2CStart();												//Repeat Start
		
		res = I2CWriteByte(DS3232M_ADDRESS_READ_COMMAND);		//DS3232M Address + R   //SLA + R
		
		if(!res)	return FALSE;								//Error Checking!!
		
		res = I2CReadByte(data,0);								//Now read the value with NACK
			
		if(!res)	return FALSE;								//Error Checking!!
		
		I2CStop();												//STOP I2C
		
		return TRUE;
}

uint8_t DS3232M_Write(uint8_t address, uint8_t data)
{
		uint8_t res;											//result	
		
		I2CStart();												//Start
				
		res = I2CWriteByte(DS3232M_ADDRESS_WRITE_COMMAND);		//DS3232M address + W//SLA+W
				
		if(!res)	return FALSE;								//Error
		
		res = I2CWriteByte(address);							//Now send the address of required register
			
		if(!res)	return FALSE;								//Error	
			
		res = I2CWriteByte(data);								//Now write the value
						
		if(!res)	return FALSE;								//Error
				
		I2CStop();												//STOP
		
		return TRUE;
}
