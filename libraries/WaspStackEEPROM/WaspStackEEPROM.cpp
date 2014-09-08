/*
 *  Copyright (C) 2014 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		0.1
 *  Design:			David Gascón
 *  Implementation:	Gustavo Maratuech, Alejandro Gallago
 */

#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "WaspStackEEPROM.h"


// Constructor //

WaspStackEEPROM::WaspStackEEPROM()
{
	block_size = BLOCK_SIZE;	
}


// Private Methods //
/*
Function: Write the new pointer in the first address of the stack
Returns:'1' on success, '0' error writing
Parameters:
	new_pointer:pointer value:1,2,3....(number of data written to the stack)
Values:
*/
bool WaspStackEEPROM::setStackPointer( uint8_t new_pointer )
{	
	//write the value of the pointer in the first address of the stack
	Utils.writeEEPROM(START_STACK, new_pointer);
	
	//check that value is written well
	if ( getStackPointer() == new_pointer )
	{	
		return true;
	}	
	else
	{
		return false;
	}
}

/*
Function: Get the pointer indicating the position of the last written block.
Returns:Return the pointer value(1,2,3...)
Parameters:
	
Values:
*/
uint8_t WaspStackEEPROM::getStackPointer()
{
	uint8_t pointer;

	pointer = Utils.readEEPROM( START_STACK );

	return pointer;
}

/*
Function: Check if the stack is full
Returns:'1' if is full, '0' if not
Parameters:
	
Values:
*/
bool WaspStackEEPROM::isFull()
{
	uint8_t max_pointer;
	
	//obtain the maximum value that can take pointer
	max_pointer = (END_STACK - (START_STACK + 1)) / block_size;
	
	//check if the current pointer is equal to the maximum pointer
	if( getStackPointer() >= max_pointer )
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
Function: Check if the stack is empty
Returns:'1' if is empty, '0' if not
Parameters:
	
Values:
*/
bool WaspStackEEPROM::isEmpty()
{
	//check if the current pointer is diferent to 0
	if( getStackPointer() != 0 )
	{
		return false;
	}
	else
	{
		return true;
	}
}


// Public Methods //
/*
Function: Initialize the block size for the stack
Returns:
Parameters:
	block_size: Value of the block in the stack
Values:
*/
void WaspStackEEPROM::initBlockSize( uint8_t blocksize )
{
	block_size = blocksize;	
}

/*
Function: Initialize the stack
Returns:'1' on success, '0' error writing
Parameters:
	
Values:
*/	
bool WaspStackEEPROM::initStack()
{	
	// Wwrite 0 in the first address position of the stack(pointer value)	
	if( setStackPointer(0x00) == false )
	{
		return 0;
	}

	//write ones in the entire stack	
	for( uint16_t i = (START_STACK + 1) ; i < (END_STACK + 1) ; i++ )
	{
		eeprom_write_byte ((unsigned char*) i, 0xFF);
	}

	//check if it was written well
	for( uint16_t i = (START_STACK + 1); i < (END_STACK + 1) ; i++)
	{
		if( eeprom_read_byte((unsigned char*) i) != 0xFF )
		{
			return 0;
		}		
	}		

	return 1;
}

/*
Function: Push a new block of data into the stack
Returns:'1' on success
		'0' error writing
		'2'is full
		'3' block size small
Parameters:
	data: vector with the data to store
	data_length: length of data to store
Values:
*/
uint8_t WaspStackEEPROM::push(uint8_t* data, uint8_t data_length)
{
	uint8_t new_pointer;
	uint16_t address;

	if( block_size > data_length )
	{
	
		//check if the stack is full
		if( isFull() == true )
		{
			return 2;	
		}	
	
		// get the new pointer	
		new_pointer = getStackPointer() + 1;
	
		// obtain the next valid address to write in the stack
		address = ( START_STACK + 1 ) + (( new_pointer - 1 ) * block_size );


		// write the data length
		Utils.writeEEPROM(address, data_length);
	
		//check if length was written well
		if( data_length != Utils.readEEPROM(address) )
		{
			return 0;
		}	

		// write the data	
		for( uint16_t i = 0; i < data_length; i++)
		{
			Utils.writeEEPROM(address + 1 + i, data[i]);
		}
	
		//check if it was written well
		for( uint16_t i = 0; i < data_length; i++)
		{
			if(data[i] != Utils.readEEPROM(address + 1 + i))
			{
				return 0;
			}
		}
	
		//update the pointer value
		if( setStackPointer(new_pointer) == true )
		{
			return 1;
		}
	
		return 0;
	}
	else
	{
		return 3;
	}
}

/*
Function: Gets a block from the stack
Returns:'0' if empty,
		'1' error reading,
		'2' if error updating the new pointer
		value positive value means the number of bytes read.
Parameters:
	data:Position where it will store the data out the stack.
	
Values:
*/
uint16_t WaspStackEEPROM::pop(uint8_t* data)
{
	uint8_t pointer;
	uint16_t address;
	uint16_t length;	

	//Check if the stack is empty 	
	if( isEmpty() == true )
	{	
		return 0;
	}

	//get the pointer	
	pointer = getStackPointer();

	//obtain the next address to get the data
	address = ( START_STACK + 1 ) + (( pointer - 1 ) * block_size );

	//Get the data length	
	length = Utils.readEEPROM(address);

	//copy the data in a variable	
	for( uint16_t i = 0; i < length; i++ )
	{
		data[i] = Utils.readEEPROM(address + 1 + i);
	}

	//check if it was written well
	for( uint16_t i = 0; i < length; i++ )
	{
		if( data[i] != Utils.readEEPROM(address + 1 + i) )
		{
			return 1;
		}
	}
	
	//update the pointer	
	pointer = pointer - 1;
	
	//update the pointer value
	if( setStackPointer(pointer) == true )
	{
		return length;
	}

	return 2;
}


WaspStackEEPROM stack = WaspStackEEPROM();



