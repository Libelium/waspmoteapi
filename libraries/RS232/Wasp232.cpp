/*! \file Wasp232.cpp
    \brief Library for managing RS-232 module
    
    Copyright (C) 2014 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.1
    Design:			David Gascón
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
	delay(1);
	
	pinMode(MUX_PW, OUTPUT);
	pinMode(MUX_USB_XBEE, OUTPUT);
	digitalWrite(MUX_PW, HIGH);  
	digitalWrite(MUX_USB_XBEE, HIGH);
	delay(1); 

	if (socket == 1) {
		pinMode(DIGITAL6, OUTPUT);
		digitalWrite(DIGITAL6, HIGH);
		Utils.setMuxSocket1();
		_uart = 1;
	} else {
		pinMode(XBEE_PW,OUTPUT);
		digitalWrite(XBEE_PW,HIGH);
		_uart = 0;
	}
}


//!*************************************************************
//!	Name:	OFF()
//!	Description: Switches off the module and closes the UART
//!	Param : void
//!	Returns: void
//!*************************************************************
void Wasp232::OFF(void)
{
	closeSerial(_uart);

	if (_uart == 1) {
		digitalWrite(DIGITAL6, LOW);
	} else {
		digitalWrite(XBEE_PW,LOW);
	}
}


//!*************************************************************
//!	Name: baudRateConfig()
//!	Description: It sets the speed of asynchronous communication
//!	Param : unsigmed log, speed to configure
//!	Returns: void
//!*************************************************************
void Wasp232::baudRateConfig(unsigned long speed)
{
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
//!	Name: send()
//!	Description: It sends an unsigned char(uint_8) n
//!	Param : uint8_t, data to send
//!	Returns: void
//!*************************************************************
void Wasp232::send(uint8_t n) 
{
	printByte(n, _uart);
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
	
	delay(_delay);
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
//!	Description: Enables or disables the parity bit
//!	Param : bool state, "ENABLED" or "DISABLED"
//!	Returns: 						
//!*************************************************************
void Wasp232::parityBit(bool state)
{
	if (_uart == 0) {
		if (state == DISABLED) {
			UCSR0C = (0<<UPM00)|(3<<UCSZ00);
		} else {
			UCSR0C = (3<<UPM00)|(3<<UCSZ00);
		}
	} else if (_uart ==1) {
		if (state == DISABLED) {
			UCSR1C = (0<<UPM10)|(3<<UCSZ10);
		} else {
			UCSR1C = (3<<UPM10)|(3<<UCSZ10);
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
	if (_uart == 0) {
		if (numStopBits == 1) {
			UCSR0C = (2<<USBS0)|(3<<UCSZ00);
		} else {
			UCSR0C = (1<<USBS0)|(3<<UCSZ00);
		}
	} else if (_uart == 1) {
		if (numStopBits == 1) {
			UCSR1C = (2<<USBS1)|(3<<UCSZ10);
		} else {
			UCSR1C = (1<<USBS1)|(3<<UCSZ10);
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
