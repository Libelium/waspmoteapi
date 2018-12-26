/*! \file Wasp232.h
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

#ifndef Wasp232_h
#define Wasp232_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#ifndef inttypes_h
	#include <inttypes.h>
#endif
#include <WaspUART.h>

#define DEBUG_RS232	0
#define PRINT_RS232(str)	USB.print(F("[RS232] ")); USB.print(str);
#define PRINTLN_RS232(str)	USB.print(F("[RS232] ")); USB.println(str);

#define _delay 2


//! Parity Modes
enum ParityModes
{
	NONE 		= 0,
	EVEN 		= 2,
	ODD 		= 3,
};

#define ONE_STOP_BIT 1
#define TWO_STOP_BITS 2

/******************************************************************************
 * Class
 ******************************************************************************/

class Wasp232 : public WaspUART
{
	#define RADIO_RS232_UART_SIZE 100
	uint8_t class_buffer[RADIO_RS232_UART_SIZE];

	public:

		//! Class Constructor
		Wasp232()
		{
			// assign class pointer to UART buffer
			_buffer = class_buffer;
			_bufferSize = RADIO_RS232_UART_SIZE;			
		};

		//! Powers the 232 module and opens the UART.
		void ON(char socket);

		//! Switches off the module and closes the UART.
		void OFF(void);

		//!Baud-Rate configuration. It sets the speed of asynchronous communication.
		void baudRateConfig(unsigned long speed);

		//! Receives data through the UART.
		char read(void);

		//! Receive data
		uint16_t receive(void);

		//!Sends data through the UART. It sends a char n.
		void send (uint8_t n);

		//!Sends data through the UART. It sends a string s.
		void send (const char *s);

		//!Sends data through the UART. It sends an int n.
		void send (int n);

		//!Sends data through the UART. It sends an unsigned int n.
		void send (unsigned int n);

		//!Sends data through the UART. It sends a long n.
		void send (long n);

		//!Sends data through the UART. It sends an unsigned long n.
		void send (unsigned long n);

		//!Sends data through the UART. It prints a long number in the specified base.
		void send (long n, int base);

		//!Sends data through the UART. It sends an array of bytes given the length as input
		void send(uint8_t *s, uint16_t length);

		//!Get the number of bytes (characters) available for reading from the serial port.
		int available(void);

		//!It flushes the buffer of incoming serial data.
		void flush(void);

		//! Enables or disables the parity bit.
		void parityBit(uint8_t state);

		//! Selects the number of stop bits to be inserted by the Transmitter. The Receiver ignores this setting.
		void stopBitConfig(uint8_t numStopBits);


		//! Detects a transmission error.
		uint8_t error(void);

//**********************************************************************
// Private functions
//**********************************************************************

	private:
		void print 	(char c, uint8_t uart);
		void printNumber (unsigned long	n, uint8_t	base, uint8_t uart);
};


extern Wasp232 W232;

#endif
