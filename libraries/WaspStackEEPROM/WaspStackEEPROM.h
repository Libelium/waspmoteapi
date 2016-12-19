/*
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:	3.0
 *  Author:   	Gustavo Maratuech, Alejandro Gállego
 */

#ifndef WaspstackEEPROM_h
#define WaspstackEEPROM_h


#include <inttypes.h>

/************define************************/
/*start of the stack*/
#define START_STACK	1100
/*end of the stack*/
#define END_STACK	4000
/*block size within the stack*/
#define BLOCK_SIZE	100

enum stack_modes_enum
{
	FIFO_MODE,
	LIFO_MODE,
};


//! starting address of the first block of the stack 
//! it is calculated as START_STACK adding an offset of 3 bytes: counter, 
//! front_pointer and back_pointer
const uint16_t START_ADDRESS = START_STACK + 3;


//! WaspStackEEPROM Class
/*!
	WaspStackEEPROM Class defines all the variables and functions used to store data in EEPROM
 */
class WaspStackEEPROM
{

private:
		
	//! Size of the block, BLOCK_SIZE by default
	uint8_t block_size;
		
	//! Stores the maximum number of blocks that fits inside the stack 
	//! after giving a specific 'block_size'
	uint8_t _max_blocks;
	
	//! Stores the STACK mode: FIFO or LIFO
	uint8_t _mode;
	
	
	//! It writes the new pointer in the first address of the stack
	/*!
	\param uint8_t new_pointer: number of the new pointer(0,1,2,3..).
	\return '1' on success, '0' error writing
	*/
	bool setStackPointer(uint8_t new_pointer);  
	bool setFrontPointer(uint8_t new_pointer);  
	bool setBackPointer(uint8_t new_pointer);    
	
	//!It gets the pointer indicating the position of the last written block.
	/*!
	\return returns last pointer used.
	*/
	uint8_t getStackPointer();	
	uint8_t getFrontPointer();	
	uint8_t getBackPointer();	
	

public:

	//! class constructor
  	/*!
	\param void
	\return void
	 */
    WaspStackEEPROM();

	//!It initializes the block size for the stack
	/*!
	\param uint8_t blocksize: Block size
	\return void
	*/
	void initBlockSize(uint8_t blocksize);
	
	//!It initializes the stack
	/*!
	\return '1' on succes, '0' error 
	*/
	bool initStack();
	bool initStack( uint8_t mode );

	//!It pushes a new block of data into the stack
	/*!
	\param uint8_t* data: vector with the data to store
	\param uint8_t data_length: length of data to store
	\return '1' on success
		'0' error writing
		'2'is full
		'3' block size small.
	*/
	uint8_t push(uint8_t* data, uint8_t data_length);
	uint8_t push_front(uint8_t* data, uint8_t data_length);
	uint8_t push_back(uint8_t* data, uint8_t data_length);

	//!It gets a block from the stack
	/*!
	\param uint8_t* data: position of the data that is going to take.
	\return '0' if empty,
		'1' error reading,
		'2' if error updating the new pointer
		value positive value means the number of bytes read.
	*/
	uint16_t pop(uint8_t* data);	
	uint16_t pop_front(uint8_t* data);	
	uint16_t pop_back(uint8_t* data);	
	
	//!It checks if the stack is full. If full then stop writing.
	/*!
	\return returns 1 if the stack is full or 0 if not.
	*/
	bool isFull();

	//!It checks if the stack is empty. 
	/*!
	\return returns 1 if the stack is empty or 0 if not.
	*/
	bool isEmpty();

	//!It gets the number of stored frames inside Stack
	/*!
	\return number of stored frames
	*/
	int getStoredFrames();
	
	//!It returnsthe maximum number of frames that fit inside the Stack
	/*!
	\return number of maximum possible frames
	*/
	uint8_t getMaxFrames();


};

extern WaspStackEEPROM stack;

#endif
