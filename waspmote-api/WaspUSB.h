/*! \file WaspUSB.h
    \brief Library for managing the USB interface
    Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.
   
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
  
    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
    Version:		3.0
    Design:			David Gascón
    Implementation:	David Cuartielles, Alberto Bielsa, Yuri Carmona

 */
 
/*! \def WaspUSB_h
    \brief The library flag
    
 */
#ifndef WaspUSB_h
#define WaspUSB_h


/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>

// Header file in order to allow prints from Flash memory
#include "Printable.h"
#include <stdarg.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
 
/*! \def DEC
    \brief The base to print numbers. Decimal Base in this case
    
 */

/*! \def HEX
    \brief The base to print numbers. Hexadecimal Base in this case
    
 */

/*! \def OCT
    \brief The base to print numbers. Octal Base in this case
    
 */

/*! \def BIN
    \brief The base to print numbers. Binary Base in this case
    
 */

/*! \def BYTE
    \brief The base to print numbers. Byte Base in this case
    
 */
#define DEC 	10
#define HEX 	16
#define OCT 	8
#define BIN 	2
#define BYTE 	0

/*! \def USB_RATE
    \brief USB Baud Rates    
 */
#define USB_RATE	115200




/******************************************************************************
 * Class
 ******************************************************************************/
 
 //! WaspUSB Class
/*!
	WaspUSB Class defines all the variables and functions used for managing the 
	USB interface
 */
class WaspUSB
{

private:
	
	//! Variable : specifies the UART where the USB is connected
  	/*!    
	 */
    uint8_t _uart;
    
    //! backup register attributes
    uint8_t _reg_ubrr0h;
    uint8_t _reg_ubrr0l;
    uint8_t _reg_ucsr0c;
    
    
public:
	  
	//! class constructor
  	/*!
		It initializes some variables
	\param void
	\return void
	*/
    WaspUSB();
	
	//! It opens UART0 to be able to communicate with the FTDI conversor
  	/*!
		It gets the baud rate from 'USB_RATE'
	\param void
	\return void
	 */
    void ON();
	
	//! It closes the previously opened UART0
  	/*!
	\param void
	\return void
	 */
    void OFF();
	
	//! It checks if there is available data waiting to be read
  	/*!
	\param void
	\return '1' if there is available data, '0' otherwise
	 */
	uint8_t available();
	
	//! It reads a byte from the UART
  	/*!
	\param void
	\return the read byte or '-1' if no data is available
	 */
	int read();
	
	//! It clears the UART buffer
  	/*!
	\param void
	\return void
	 */
	void flush();
	
	//! It prints a character
  	/*!
	\param char c : the character to print
	\return void
	 */
	void print(char c);
	
	//! It prints a string
  	/*!
	\param const char[] c : the string to print
	\return void
	 */
	void print(const char[]);
	
	//! It prints an unsigned 8-bit integer
  	/*!
	\param uint8_t b : the number to print
	\return void
	 */
	void print(uint8_t b);
	
	//! It prints an unsigned 16-bit integer
  	/*!
	\param uint16_t n : the number to print
	\return void
	 */
	void print(uint16_t n);
	
	//! It prints an integer
  	/*!
	\param int n : the number to print
	\return void
	 */
	void print(int n);
	
	//! It prints a long integer
  	/*!
	\param long n : the number to print
	\return void
	 */
	void print(long n);
	
	//! It prints an unsigned long integer
  	/*!
	\param unsigned long n : the number to print
	\return void
	 */
	void print(unsigned long n);
	
	//! It prints a long number in the specified base
  	/*!
	\param long n : the number to print
	\param int base : the base for printing the number
	\return void
	 */
	void print(long n, int base);
		
	//! It prints a byte as a hexadecimal (%2X) format 
  	/*!
	\param char n : the byte to print
	\return void
	 */
	void printHex(char n);
	
	//! It prints a double number
  	/*!
	\param double n : the number to print
	\return void
	 */
	void print(double n);
	
	//! It prints a 64-bit number
  	/*!
	\param uint64_t n : the number to print
	\return void
	 */
	void print(uint64_t n);
	
	//! It prints an EOL and a carriage return
  	/*!
	\param void
	\return void
	 */
	void println();
	
	//! It prints a character adding an EOL and a carriage return
  	/*!
	\param char c : the character to print
	\return void
	 */
	void println(char c);
	
	//! It prints a string adding an EOL and a carriage return
  	/*!
	\param const char[] c : the string to print
	\return void
	 */
	void println(const char[]);
	
	//! It prints an unsigned 8-bit integer adding an EOL and a carriage return
  	/*!
	\param uint8_t b : the number to print
	\return void
	 */
	void println(uint8_t b);
	
	//! It prints an unsigned 16-bit integer adding an EOL and a carriage return
  	/*!
	\param uint16_t n : the number to print
	\return void
	 */
	void println(uint16_t n);
	
	//! It prints an integer adding an EOL and a carriage return
  	/*!
	\param int n : the number to print
	\return void
	 */
	void println(int n);
	
	//! It prints a long integer adding an EOL and a carriage return
  	/*!
	\param long n : the number to print
	\return void
	 */
	void println(long n);
	
	//! It prints an unsigned long integer adding an EOL and a carriage return
  	/*!
	\param unsigned long n : the number to print
	\return void
	 */
	void println(unsigned long n);
	
	//! It prints a long number in the specified base adding an EOL and a 
	//! carriage return
  	/*!
	\param long n : the number to print
	\param int base : the base for printing the number
	\return void
	 */
	void println(long n, int base);
	
	//! It prints a double number adding an EOL and a carriage return
  	/*!
	\param double n : the number to print
	\return void
	 */
	void println(double n);
	
	//! It prints a 64-bit number adding an EOL and a carriage return
  	/*!
	\param uint64_t n : the number to print
	\return void
	 */
	void println(uint64_t n);	
	
	//! It prints a string from Flash memory 
  	/*!
	\param const __FlashStringHelper * : pointer to the string in the flash
	\return uint32_t '0'
	 */
	uint32_t print(const __FlashStringHelper *);
	
	//! It prints a string from Flash memory adding an EOL
  	/*!
	\param __FlashStringHelper
	\return uint32_t '0'
	 */
	uint32_t println(const __FlashStringHelper *);
	
	//! It prints a sequence of data formatted as the format argument specifies 
  	/*!
  	This function emulates the stdio.h printf() functionality in C and will send
	the output to the Serial connection using printByte(). The resulting 
	string sent over serial is limited to 128 chars.
	\param char *fmt : is the format string to be printed
	\param ... :  additional arguments as specified in format.
	\return void
	 */
	void  printf(char *fmt, ... );
	
	//! It prints a 'float' number
  	/*!
	\param double number : the number to print
	\param uint8_t digits : the number of non-integer part digits
	\return void
	 */
    void printFloat(double number, uint8_t digits);
    
    //! It prints a buffer specifying the length of the buffer
  	/*!
	\param uint8_t* pointer : pointer to data to be printed
	\param uint16_t length : length of data
	\return void
	 */
    void print(uint8_t* pointer, uint16_t length);
    
    //! It prints a buffer specifying the length of the buffer
  	/*! This function adds an End Of Line after printing the buffer
	\param uint8_t* pointer : pointer to data to be printed
	\param uint16_t length : length of data
	\return void
	 */
    void println(uint8_t* pointer, uint16_t length);
    
    //! It prints a buffer in HEX format specifying the length of the buffer
  	/*! 
	\param uint8_t* pointer : pointer to data to be printed
	\param uint16_t length : length of data
	\return void
	 */
    void printHex(uint8_t* pointer, uint16_t length); 
     
    //! It prints a buffer in HEX format specifying the length of the buffer
  	/*! This function adds an End Of Line after printing the buffer
	\param uint8_t* pointer : pointer to data to be printed
	\param uint16_t length : length of data
	\return void
	 */
    void printHexln(uint8_t* pointer, uint16_t length);
    
    //! It prepares the UART0 for USB port securely
    void secureBegin();
    
    //! It sets the UART0 to the previous settings before using USB port
    void secureEnd();
    
};

extern WaspUSB USB;

#endif

