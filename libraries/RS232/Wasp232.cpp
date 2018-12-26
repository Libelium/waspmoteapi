/*! \file Wasp232.cpp
    \brief Library for managing RS-232 module
    
    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		3.3
    Design:			David Gascon
    Implementation:	Ahmad Saad

 */


/***********************************************************************
 * Includes
 ***********************************************************************/

#include "Wasp232.h"

#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif 


 /***********************************************************************
 * Methods of the Class
 ***********************************************************************/
 
 
//!*************************************************************
//!	Name: ON()
//!	Description: Powers the 232 module and opens the UART
//!	Param: socket: the socket to be used (0 or 1)
//!	Returns: void
//!*************************************************************
void Wasp232::ON(char socket)
{
	// set uart
	_uart = socket;
	
	// select multiplexer
    if (_uart == SOCKET0) 	Utils.setMuxSocket0();
    if (_uart == SOCKET1) 	Utils.setMuxSocket1();
	
	// Open UART
	beginUART();
	
    // power on the socket
    PWR.powerSocket(_uart, HIGH);
    
    // wait stabilization time
	delay(100);
	
}


//!*************************************************************
//!	Name:	OFF()
//!	Description: Switches off the module and closes the UART
//!	Param : void
//!	Returns: void
//!*************************************************************
void Wasp232::OFF(void)
{
	// close uart
	closeUART();
	
	// unselect multiplexer 
    if (_uart == SOCKET0)	Utils.setMuxUSB();
    if (_uart == SOCKET1)	Utils.muxOFF1();
    
    // switch module OFF
	PWR.powerSocket(_uart, LOW);
}


//!*************************************************************
//!	Name: baudRateConfig()
//!	Description: It sets the speed of asynchronous communication
//!	Param : unsigmed log, speed to configure
//!	Returns: void
//!*************************************************************
void Wasp232::baudRateConfig(unsigned long speed)
{
	_baudrate = speed;
	beginSerial(speed, _uart);
}


//!*************************************************************
//!	Name: read()
//!	Description: Receives data through the UART
//!	Param : void
//!	Returns: char, data read
//!************************************************************* 
char Wasp232::read(void)
{
	return serialRead(_uart);
}

//!*************************************************************
//!	Name: receive()
//!	Description: Receives data through the UART
//!	Param : void
//!	Returns the number of received bytes	
//!************************************************************* 
uint16_t Wasp232::receive(void)
{
	uint16_t nBytes = 0;
	nBytes = readBuffer(_bufferSize);
	
	return nBytes;
}


//!*************************************************************
//!	Name: send()
//!	Description: It sends an unsigned char(uint_8) n
//!	Param : uint8_t, data to send
//!	Returns: void
//!*************************************************************
void Wasp232::send(uint8_t n) 
{
	printByte(n, _uart);
}



//!*************************************************************
//!	Name: send()
//!	Description: It sends an array of bytes
//!	Param : uint8_t *s: pointer to array
//!	Param : uint16_t length: length of array
//!	Returns: void
//!*************************************************************
void Wasp232::send(uint8_t *s, uint16_t length) 
{
	for (uint16_t i=0; i < length; i++)
	{
		printByte(s[i], _uart);
	}
	delay(_delay);
}



//!*************************************************************
//!	Name: send()
//!	Description: It sends an int n
//!	Param: int, data to send
//!	Returns: void
//!*************************************************************
void Wasp232::send(int n)
{
	if (n < 0) {
		printByte('-', _uart);
		n = -n;
	}
	
	printIntegerInBase(n, 10, _uart);
	delay(_delay);
} 


//!*************************************************************
//!	Name: send()
//!	Description: It sends an unsigned int
//!	Param : unsigned int, data to send
//!	Returns: void
//!*************************************************************
void Wasp232::send(unsigned int n)
{
	printIntegerInBase(n, 10, _uart);
	delay(_delay);
}


//!*************************************************************
//!	Name: send()
//!	Description:  It sends a long
//!	Param: long, data to send
//!	Returns: void
//!*************************************************************
void Wasp232::send(long n)
{
	if (n < 0) {
		printByte('-', _uart);
		n = -n;
	}

	printIntegerInBase(n, 10, _uart);
	delay(_delay);
}


//!*************************************************************
//!	Name: send()
//!	Description: It sends a string
//!	Param : const char s, the string to send
//!	Returns:void
//!*************************************************************
void Wasp232::send(const char *s)
{
	printString(s, _uart);
	delay(_delay);
}


//!*************************************************************
//!	Name: send()
//!	Description: It sends an unsigned long
//!	Param : unsigned long, data to send
//!	Returns: void
//!*************************************************************
void Wasp232::send (unsigned long n)
{
	printIntegerInBase(n, 10, _uart);
	delay(_delay);
}


//!*************************************************************
//!	Name: send()
//!	Description: 
//!	Param: param long n, unsigned long to send.
//!			param int base, the base for printing the number
//!	Returns: void
//!*************************************************************
void Wasp232::send(long n, int base)
{	
	if (base == 0)
		printByte((char) n ,_uart);
	else
		printIntegerInBase(n, base, _uart);
	
}


//!*************************************************************
//!	Name: available()
//!	Description: Get the number of bytes available for reading
//!	Param: void
//!	Returns: the number of bytes available
//!*************************************************************
int Wasp232::available(void)
{
	return serialAvailable(_uart);
}


//!*************************************************************
//!	Name: flush()
//!	Description: Flushes the buffer of incoming serial data
//!	Param: void
//!	Returns: void
//!*************************************************************
void Wasp232::flush(void)
{
	serialFlush(_uart);
}


//!*************************************************************
//!	Name: parityBit()
//!	Description: Enables (EVEN or ODD) or disables the parity bit
//!	Param : bool state: "EVEN", "ODD" or "DISABLED"
//!	Returns: 						
//!*************************************************************
void Wasp232::parityBit(uint8_t state)
{
	if (_uart == SOCKET0) 
	{
		if (state == DISABLED) 	
		{
			cbi(UCSR0C, UPM01);
			cbi(UCSR0C, UPM00);
		}
		if (state == EVEN)				
		{
			sbi(UCSR0C, UPM01);
			cbi(UCSR0C, UPM00);
		}
		if (state == ODD)		
		{
			sbi(UCSR0C, UPM01);
			sbi(UCSR0C, UPM00);
		}
	} 
	else if (_uart == SOCKET1) 
	{
		if (state == DISABLED) 	
		{
			cbi(UCSR1C, UPM11);
			cbi(UCSR1C, UPM10);
		}
		if (state == EVEN)				
		{
			sbi(UCSR1C, UPM11);
			cbi(UCSR1C, UPM10);
		}
		if (state == ODD)		
		{
			sbi(UCSR1C, UPM11);
			sbi(UCSR1C, UPM10);
		}
	}
}



//!*************************************************************
//!	Name:	stopBitConfig()
//!	Description: Selects the number of stop bits to be inserted
//!	Param:  uint8_t numStopBits, the number of stop bits
//!	Returns: void
//!*************************************************************
void Wasp232::stopBitConfig(uint8_t numStopBits)
{
	if (_uart == SOCKET0)
	{
		if (numStopBits == ONE_STOP_BIT)
		{
			cbi(UCSR0C, USBS0);
		}
		if (numStopBits == TWO_STOP_BITS)
		{
			sbi(UCSR0C, USBS0);
		}
	}
	else if (_uart == SOCKET1) 
	{
		if (numStopBits == ONE_STOP_BIT)
		{
			cbi(UCSR1C, USBS1);
		}
		if (numStopBits == TWO_STOP_BITS)
		{
			sbi(UCSR1C, USBS1);
		}
	}
}


//!*************************************************************
//!	Name: error()
//!	Description: Detects a transmission error
//!	Param: void
//!	Returns: 	error = 0 if no error in transmision
//!				error = 1	if frame error
//!				error = 2	if data over run
//!				error = 3	if parity error
//!*************************************************************
uint8_t Wasp232::error(void) 
{ 
	if (_uart == 0) { 
		if ((UCSR0A & 0x1C) ==0) return 0; //!No error
		if (UCSR0A & 0x10) return 1; //!Frame error
		if (UCSR0A & 0x08) return 2; //! Data over run  
		if (UCSR0A & 0x04) return 3; //! Parity error
	} else if (_uart == 1) {
		if ((UCSR1A & 0x1C) ==0) return 0; //!No error
		if (UCSR1A & 0x10) return 1; //!Frame error
		if (UCSR1A & 0x08) return 2; //! Data over run 
		if (UCSR1A & 0x04) return 3; //! Parity error
	}
}


//**********************************************************************
// Private functions
//**********************************************************************

void Wasp232::print(char c, uint8_t uart) 
{
	printByte(c, uart);
}


void Wasp232::printNumber (unsigned long	n, uint8_t	base, uint8_t uart)
{			
	printIntegerInBase(n, base, uart);
}


Wasp232 W232 = Wasp232();
