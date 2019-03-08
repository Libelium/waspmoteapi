/*
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.0
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
	_max_blocks = (END_STACK - START_ADDRESS)/block_size;
	_mode = LIFO_MODE;
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
Function: Write the new pointer in the first address of the stack
Returns:'1' on success, '0' error writing
Parameters:
	new_pointer:pointer value:1,2,3....(number of data written to the stack)
Values:
*/

bool WaspStackEEPROM::setFrontPointer( uint8_t new_pointer )
{	
	//write the value of the pointer in the first address of the stack
	Utils.writeEEPROM(START_STACK+1, new_pointer);
	
	//check that value is written well
	if ( getFrontPointer() == new_pointer )
	{	
		return true;
	}	
	else
	{
		return false;
	}
}

/*
Function: Write the new pointer in the first address of the stack
Returns:'1' on success, '0' error writing
Parameters:
	new_pointer:pointer value:1,2,3....(number of data written to the stack)
Values:
*/
bool WaspStackEEPROM::setBackPointer( uint8_t new_pointer )
{	
	//write the value of the pointer in the first address of the stack
	Utils.writeEEPROM(START_STACK+2, new_pointer);
	
	//check that value is written well
	if ( getBackPointer() == new_pointer )
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
Function: Get the pointer indicating the position of the last written block.
Returns:Return the front pointer value: from '0' to 'max_blocks-1'
Parameters:
	
Values:
*/
uint8_t WaspStackEEPROM::getFrontPointer()
{
	uint8_t pointer;

	pointer = Utils.readEEPROM( START_STACK+1 );

	return pointer;
}

/*
Function: Get the pointer indicating the position of the last written block.
Returns:Return the pointer value(1,2,3...)
Parameters:
	
Values:
*/
uint8_t WaspStackEEPROM::getBackPointer()
{
	uint8_t pointer;

	pointer = Utils.readEEPROM( START_STACK+2 );

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
	//check if the current pointer is equal to the maximum pointer
	if( getStackPointer() >= _max_blocks )
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
	// update block size
	block_size = blocksize;	
	
	// update maximum number of blocks that fit in Stack
	_max_blocks = (END_STACK - START_ADDRESS)/block_size;
}

/*
Function: Initialize the stack
Returns:'1' on success, '0' error writing
Parameters:
	
Values:
*/	
bool WaspStackEEPROM::initStack()
{	
	return initStack( LIFO_MODE );
}


/*
Function: Initialize the stack
Returns:'1' on success, '0' error writing
Parameters:
	
Values:
*/	
bool WaspStackEEPROM::initStack( uint8_t mode )
{	
	// update mode: LIFO_MODE or FIFO_MODE
	_mode = mode;
	
	// Write 0 in the first address position of the stack(pointer value)	
	if( setStackPointer(0x00) == false )
	{
		return 0;
	}
	
	// Write '_max_blocks-1' in the front pointer 
	// address position of the stack(pointer value)	
	if( setFrontPointer( (uint8_t)(_max_blocks-1) ) == false )
	{
		return 0;
	}
	// Write '0' in the back address position of the stack(pointer value)	
	if( setBackPointer(0x00) == false )
	{
		return 0;
	}

	//write ones in the entire stack	
	for( uint16_t i = START_ADDRESS ; i < (END_STACK + 1) ; i++ )
	{
		eeprom_write_byte ((unsigned char*) i, 0xFF);
	}

	//check if it was written well
	for( uint16_t i = START_ADDRESS; i < (END_STACK + 1) ; i++)
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
	if( _mode == LIFO_MODE )
	{
		return push_back( data, data_length );
	}
	else
	{
		// FIFO_MODE (it is the same)
		return push_back( data, data_length );		
	}
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
uint8_t WaspStackEEPROM::push_front(uint8_t* data, uint8_t data_length)
{	 
	uint8_t counter;
	uint8_t new_pointer;
	uint16_t address;

	if( block_size > data_length )
	{	
		//check if the stack is full
		if( isFull() == true )
		{
			return 2;	
		}	
	
		// get the front pointer	
		new_pointer = getFrontPointer();
	
		// obtain the next valid address to write in the stack
		address = START_ADDRESS + ( new_pointer * block_size );

		// write the data length (first byte of block)
		Utils.writeEEPROM(address, data_length);
	
		// check if length was written well
		if( data_length != Utils.readEEPROM(address) )
		{
			return 0;
		}	

		// write the data into the rest of the block
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
		if( new_pointer != 0 )
		{
			//decrease one position
			new_pointer = new_pointer-1;
		}
		else
		{
			new_pointer = _max_blocks - 1;
		}
		new_pointer = new_pointer%_max_blocks; // modulo _max_blocks
		
		if( setFrontPointer( new_pointer ) == true )
		{			
			counter = getStackPointer();
			counter++;		
			if( setStackPointer(counter) == true )
			{
				return 1;
			}
		}
	
		return 0;
	}
	else
	{
		return 3;
	}
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
uint8_t WaspStackEEPROM::push_back(uint8_t* data, uint8_t data_length)
{	 
	uint8_t counter;
	uint8_t new_pointer;
	uint16_t address;

	if( block_size > data_length )
	{	
		//check if the stack is full
		if( isFull() == true )
		{
			return 2;	
		}	
	
		// get the back pointer	
		new_pointer = getBackPointer();
	
		// obtain the next valid address to write in the stack
		address = START_ADDRESS + ( new_pointer * block_size );

		// write the data length (first byte of block)
		Utils.writeEEPROM(address, data_length);
	
		// check if length was written well
		if( data_length != Utils.readEEPROM(address) )
		{
			return 0;
		}	

		// write the data into the rest of the block
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
		new_pointer = new_pointer+1; //increase one position
		new_pointer = new_pointer%_max_blocks; // modulo _max_blocks
		
		if( setBackPointer( new_pointer ) == true )
		{			
			counter = getStackPointer();
			counter++;		
			if( setStackPointer(counter) == true )
			{
				return 1;
			}
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
	if( _mode == LIFO_MODE )
	{
		return pop_back( data );
	}
	else
	{
		// FIFO_MODE
		return pop_front( data );		
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
uint16_t WaspStackEEPROM::pop_front(uint8_t* data)
{
	uint8_t counter;
	uint8_t pointer;
	uint16_t address;
	uint16_t length;	

	//Check if the stack is empty 	
	if( isEmpty() == true )
	{	
		return 0;
	}

	//get the Front pointer	
	pointer = getFrontPointer();
	pointer++;
	pointer = pointer%_max_blocks;

	//obtain the next address to get the data
	address = START_ADDRESS + ( pointer * block_size );

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
	
	//update the pointer value
	if( setFrontPointer(pointer) == true )
	{
		counter = getStackPointer();
		counter--;		
		if( setStackPointer(counter) == true )
		{
			return length;
		}
	}

	return 2;
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
uint16_t WaspStackEEPROM::pop_back(uint8_t* data)
{
	uint8_t counter;
	uint8_t pointer;
	uint16_t address;
	uint16_t length;	

	//Check if the stack is empty 	
	if( isEmpty() == true )
	{	
		return 0;
	}

	//get the Back pointer	
	pointer = getBackPointer();
	if( pointer != 0 )
	{
		pointer--;
	}
	else
	{
		pointer = _max_blocks-1;
	}
	pointer = pointer%_max_blocks;

	//obtain the next address to get the data
	address = START_ADDRESS + ( pointer * block_size );

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
	
	//update the pointer value
	if( setBackPointer(pointer) == true )
	{
		counter = getStackPointer();
		counter--;		
		if( setStackPointer(counter) == true )
		{
			return length;
		}
	}

	return 2;
}



/*
Function: Gets number of Stored Frames
Returns: number of Stored Frames	
*/
int WaspStackEEPROM::getStoredFrames()
{
	int storedFrames = 0;
	
	storedFrames = (int)getStackPointer();
	
	return storedFrames;
}


/*
Function: Gets the maximum number of possible Stored Frames
*/
uint8_t WaspStackEEPROM::getMaxFrames()
{
	return _max_blocks;
}

WaspStackEEPROM stack = WaspStackEEPROM();



