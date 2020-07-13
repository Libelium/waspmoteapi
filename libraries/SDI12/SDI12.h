/*! \file SDI12.h
	\brief Library for the SDI-12 protocol for Waspmote boards

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

	Version:		3.1
	Design:			David Gascón
	Implementation: Javier Siscart, Victor Boria

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
/*  Debug mode. Possible values are:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
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


/******************************************************************************
* Class
******************************************************************************/

/*!
	WaspSDI12 Class defines all the variables and functions used for
	managing the SDI12 sensors
*/
class WaspSDI12
{
	public:
		// class constructor
		WaspSDI12(uint8_t _dataPin);

		uint8_t readMeasures(char *sensorSearchedName, uint8_t sensorSearchedNameLength,
							char *sensorSerialNumber,
							float &parameter1,
							float &parameter2,
							float &parameter3,
							float &parameter4);

    	uint8_t readMeasuresFast(char *sensorSearchedName, uint8_t sensorSearchedNameLength,
    					char *sensorSerialNumber,
    					float &parameter1,
    					float &parameter2,
    					float &parameter3,
    					float &parameter4,
						bool readSensorBodyTemp);
		
		uint8_t readSACMeasures(char *sensorSearchedName, uint8_t sensorSearchedNameLength,
								char *sensorSerialNumber,
								float &parameter1,
								float &parameter2,
								float &parameter3,
								float &parameter4,
								float &parameter5);

		char address;
		uint8_t timeToNextMeasure;

		void sendCommand(char* cmd, uint8_t length);
		int available();
		int read();
		void readCommandAnswer(uint8_t length, unsigned long timeout);
		void setState(uint8_t status);
		uint8_t isSensor(char *sensorSearchedName, uint8_t sensorSearchedNameLength,
						char *sensorSerialNumber);

	private:
		uint8_t dataPin;				// digital pin for SDI12
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

		uint8_t startSensor();
	 	uint8_t startSensor(bool readSensorBodyTemp);

};
#endif
