/*! \file SDI12.h
\brief Library for the SDI-12 protocol

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

Based on SDI12 library of Kevin M. Smith (http://ethosengineering.org)

Version:		3.0
Design:			David Gascón
Implementation: Javier Siscart

*/


/*! \def SDI12
\brief The library flag
*/
#ifndef SDI12_h
#define SDI12_h

/******************************************************************************
* Includes
******************************************************************************/
#include <inttypes.h>
#include <avr/parity.h>         // optimized parity bit handling


/******************************************************************************
* Definitions & Declarations
******************************************************************************/
/* Debug mode. Possible values are:
* 0 = no debug messages will be printed
* 1 = some debug messages will be printed
*/
#define SDI12DEBUG	0
#define PRINT_SDI12(str)	USB.print(F("[SDI12] ")); USB.print(str);
#define PRINTLN_SDI12(str)	USB.print(F("[SDI12] ")); USB.println(str);

// SDI12 definitions
#define _BUFFER_SIZE 64
#define DISABLED 0
#define ENABLED 1
#define HOLDING 2
#define TRANSMITTING 3
#define LISTENING 4
#define SPACING 830
#define LISTEN_TIME 500

// Data pin only for Agriculute Xtreme board
#define _dataPin	ANA2


/******************************************************************************
* Class
******************************************************************************/

/*!
WaspSDI12 Class defines all the variables and functions used for
managing the SDI-12 sensors
*/
class WaspSDI12
{

private:

	uint8_t j;						// general counter for received chars
	bool _bufferOverflow;			// buffer overflow status
	char _rxBuffer[_BUFFER_SIZE];	// Buffer variables for incomming data
	uint8_t _rxBufferHead;
	uint8_t _rxBufferTail;

	int peek();
	void flush();
	void wakeSensors();
	void writeChar(uint8_t out);
	void receiveChar();

//protected:

public:

	WaspSDI12();					// class constructor

	void sendCommand(char* cmd, uint8_t length);
	int available();
	int read();
	void readCommandAnswer(uint8_t length, unsigned long timeout);
	void setState(uint8_t status);

};
#endif
