/*! \file SDI12.cpp
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

    Version:		3.1
    Design:			David Gascón
    Implementation: Javier Siscart, Victor Boria

*/
#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "SDI12.h"

const char string_00[] PROGMEM = "I!";	// SDI-12 info
const char string_01[] PROGMEM = "M!";	// SDI-12 measurement
const char string_02[] PROGMEM = "D0!";	// SDI-12 data
const char string_03[] PROGMEM = "Ab!";	// SDI-12 change address
const char string_04[] PROGMEM = "?!";	// SDI-12 address query
const char string_05[] PROGMEM = "?I!";	// SDI-12 info
const char string_06[] PROGMEM = "sensor not detected";
const char string_07[] PROGMEM = "invalid data";
const char string_08[] PROGMEM = "M1!";	// SDI-12 measurement



const char* const table_sdi12[] PROGMEM =
{
	string_00,
	string_01,
	string_02,
	string_03,
	string_04,
	string_05,
	string_06,
	string_07,
	string_08,
};



 ///////////////////////////////////////// Private methods/////////////

/*	wakeSensors: performs start sequence to begin a transmission
 *	Parameters:void
 *  Return:	void
 */
void WaspSDI12::wakeSensors()
{
	setState(TRANSMITTING);
	//Send the BREAK
	digitalWrite(dataPin, HIGH);
	delayMicroseconds(12500);

	//Send the MARKING
	digitalWrite(dataPin, LOW);
	delayMicroseconds(9000);
}

/*	writeChar: writes a character out on the data line
 *	Parameters: byte to send
 *  Return:void
 */
void WaspSDI12::writeChar(uint8_t out)
{
	// parity bit
	out |= (parity_even_bit(out)<<7);

	digitalWrite(dataPin, HIGH);
	delayMicroseconds(SPACING);

	for (byte mask = 0x01; mask; mask<<=1)
	{
		// send payload
		if(out & mask)
		{
			digitalWrite(dataPin, LOW);
		}
		else
		{
			digitalWrite(dataPin, HIGH);
		}
		delayMicroseconds(SPACING);
	}

	// Stop bit
	digitalWrite(dataPin, LOW);
	delayMicroseconds(SPACING);
}

/*	peek: reveals the next character in the buffer without consuming
 *	Parameters:void
 *  Return:	next byte available on buffer
 */
int WaspSDI12::peek()
{
	// Empty buffer? If yes, -1
	if (_rxBufferHead == _rxBufferTail) return -1;
	// Otherwise, read from "head"
	return _rxBuffer[_rxBufferHead];
}

/*	flush: clears the buffer contents and resets the status of the buffer overflow.
 *	Parameters:void
 *  Return:	void
 */
void WaspSDI12::flush()
{
	_rxBufferHead = _rxBufferTail = 0;
	_bufferOverflow = false;
}


/*	receiveChar: reads a new character and saves itinto the buffer.
 *	Parameters:void
 *  Return:	void
 */
void WaspSDI12::receiveChar()
{
	// Start bit?
	if (digitalRead(dataPin))
	{
		// buffer for new char
		uint8_t newChar = 0;

		delayMicroseconds(SPACING/2);

		// read 7 data bits
		for (uint8_t i=0x1; i<0x80; i <<= 1)
		{
			delayMicroseconds(SPACING);
			uint8_t noti = ~i;
			if (!digitalRead(dataPin))
			{
				newChar |= i;
			}
			else
			{
				newChar &= noti;
			}
		}

		// skip parity adn stop bit
		delayMicroseconds(SPACING);
		delayMicroseconds(SPACING);

		// Overflow? If not, proceed.
		if ((_rxBufferTail + 1) % _BUFFER_SIZE == _rxBufferHead)
		{
			_bufferOverflow = true;
		}
		else
		{
			// Save char, advance tail.
			_rxBuffer[_rxBufferTail] = newChar;
			_rxBufferTail = (_rxBufferTail + 1) % _BUFFER_SIZE;
			j++;
		}
	}
}


 // Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 */
 WaspSDI12::WaspSDI12(uint8_t _dataPin)
{
	dataPin = _dataPin;
	setState(HOLDING);
	_bufferOverflow = false;

}


 // Public Methods //////////////////////////////////////////////////////////////

/*	setState: Manages data pin states
 *	Parameters: uint8_t status: state of the data line
 *  Return:	void
 */
void WaspSDI12::setState(uint8_t status)
{
	switch (status)
	{
		case HOLDING:
			pinMode(dataPin,OUTPUT);
			digitalWrite(dataPin,LOW);
			break;

		case TRANSMITTING:
			pinMode(dataPin,OUTPUT);
			break;

		case LISTENING:
			digitalWrite(dataPin,LOW);
			pinMode(dataPin,INPUT);
			break;

		case DISABLED:
			digitalWrite(dataPin,LOW);
			pinMode(dataPin,INPUT);
			break;

		default:
			break;
	}
}
/*	sendCommand: sends a SDI12 command
 *	Parameters: char* cmd: command to be sent
 * 				uint8_t length: length of the command
 *  Return:	void
 */
void WaspSDI12::sendCommand(char* cmd, uint8_t length)
{
	#if SDI12DEBUG
	PRINT_SDI12(F("[TX]"));
	USB.println(cmd);
	#endif

	flush();
	wakeSensors();

	for (uint8_t i = 0; i < length; i++)
	{
		writeChar(cmd[i]);
	}

	setState(LISTENING);
}

/*	available: number of characters available in the buffer
 *	Parameters:void
 *  Return:	number of bytes available
 */
int WaspSDI12::available()
{
	if(_bufferOverflow) return -1;
	return (_rxBufferTail + _BUFFER_SIZE - _rxBufferHead) % _BUFFER_SIZE;
}

/*	read: reads in the next character from the buffer (and moves the index ahead)
 *	Parameters:void
 *  Return:	next character on the buffer
 */
int WaspSDI12::read()
{
	//reading makes room in the buffer
	_bufferOverflow = false;
	// Empty buffer? If yes, -1
	if (_rxBufferHead == _rxBufferTail) return -1;
	// Otherwise, grab char at head
	uint8_t nextChar = _rxBuffer[_rxBufferHead];
	// increment head
	_rxBufferHead = (_rxBufferHead + 1) % _BUFFER_SIZE;
	// return the char
	return nextChar;
}

/*	readCommandAnswer: waits till sensor answer a command.
 *	Parameters: uint8_t length: legth of expected answer
 * 				unsigned long timeout: time to be waiting for the answer (milliseconds)
 *  Return:	void
 */
void WaspSDI12::readCommandAnswer(uint8_t length, unsigned long timeout)
{
	j = 0;
	unsigned long previous = millis();
	while ((millis() - previous < timeout) && (j < length))
	{
		receiveChar();

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous ) previous=millis();

	}
	#if SDI12DEBUG
	PRINT_SDI12(F("[RX]"));
	for (int i = 0; i < _rxBufferTail; i++)
	{
		USB.print(_rxBuffer[i]);
	}
	USB.println();
	#endif

}


/*!
 * \brief detects if SDI12 sensor is present
 * \param Sensor searched name
 *        Sensor searched length
 *        Sensor Serial Number
 * \return return 0 if not, 1 if present.
 */
uint8_t WaspSDI12::isSensor(char *sensorSearchedName, uint8_t sensorSearchedNameLength, char *sensorSerialNumber)
{
	char sensorParsedName[7];
	char sensorVersion[4];
	char command[6];

	// clear variables
	memset(sensorParsedName, 0x00, sizeof(sensorParsedName));
	memset(sensorVersion, 0x00, sizeof(sensorVersion));

	// check if sensor is present. Copy command from flash memory and send it.
	strcpy_P(command, (char*)pgm_read_word(&(table_sdi12[5])));
	sendCommand(command, strlen(command));

	readCommandAnswer(33, LISTEN_TIME);

	//necessary delay
	delay(30);

	/* readMeasures answer
	* SENSOR ADDRESS | SDI12 SUPPORT | VENDOR | MODEL | VERSION | SERIAL |
	*/
	if (available() >= 20)
	{

		address = read();

		// discard two bytes
		read();
		read();

		// SDI12 SUPPORT model
		for(uint8_t i = 0; i < 8; i++)
		{
			read();
		}

		// sensor model
		for(uint8_t i = 0; i < 6; i++)
		{
			sensorParsedName[i] = read();
		}

		// sensor version
		for(uint8_t i = 0; i < 3; i++)
		{
			sensorVersion[i] = read();
			//read();
		}

		// sensor serial number
		for(uint8_t i = 0; i < 13; i++)
		{
			char byte_buffer = read();
			//13 is carriage return, end of serial number
			if (byte_buffer == 13)
			{
				break;
			}
			else
			{
				sensorSerialNumber[i] = byte_buffer;
			}
			// add end of string
			sensorSerialNumber[i+1] = 0x00;
		}
	}

	#if SDI12DEBUG > 0
	PRINT_SDI12(F("Sensor parsed name:"));
	USB.println(sensorParsedName);
	PRINT_SDI12(F("Sensor searched name:"));
	USB.println(sensorSearchedName);

	PRINT_SDI12(F("Sensor serial number:"));
	USB.println(sensorSerialNumber);

	PRINT_SDI12(F("Sensor version:"));
	USB.println(sensorVersion);
	#endif

	//Compare if the Model field returned by the sensor is equal to sensorSearchedName
	if(strncmp(sensorParsedName, sensorSearchedName, sensorSearchedNameLength) == 0)
	{
		return 1;
	}
	else
	{
		if (sensorParsedName[0] == 0x00)
		{
			#if SDI12DEBUG > 0
				char message[20];
				//"sensor not detected"
				strcpy_P(message, (char*)pgm_read_word(&(table_sdi12[6])));
				PRINTLN_SDI12(message);
			#endif
		}
		else
		{
			#if SDI12DEBUG > 0
				PRINTLN_SDI12(F("Sensor name not matched"));
			#endif
		}

		return 0;
	}
}


/*!
 * \brief send measurement command to the SDI-12 sensor to start measuring
 * \paramvoid
 * \return return 0 if invalid answer. 1 if ok.
 */
uint8_t WaspSDI12::startSensor()
{
    return startSensor(false);
}

/*!
 * \brief send measurement command to the SDI-12 sensor to start measuring
 * \paramvoid
 * \return return 0 if invalid answer. 1 if ok.
 */
uint8_t WaspSDI12::startSensor(bool readSensorBodyTemp)
{
	char aux[4];
	char command[6];
	char numberOfMeasures = 0;
	char timeToNextMeasure_string[4];

	memset(timeToNextMeasure_string, 0x00, sizeof(timeToNextMeasure_string));

	// build command with address
    if (readSensorBodyTemp)
    {
        strncpy_P(aux, (char*)pgm_read_word(&(table_sdi12[8])), sizeof(aux));
    }
    else
    {
        strncpy_P(aux, (char*)pgm_read_word(&(table_sdi12[1])), sizeof(aux));
    }

	//sprintf(command, "%c%s", address, aux);
    snprintf(command, sizeof(command), "%c%s", address, aux);
    sendCommand(command, strlen(command));
	readCommandAnswer(5, LISTEN_TIME);

	//necessary delay
	delay(30);

	// readMeasures answer
	if (available() >= 5)
	{
		// skip sensor address
		read();

		// Measurement data will be available after specified time
		timeToNextMeasure_string[0] = read();
		timeToNextMeasure_string[1] = read();
		timeToNextMeasure_string[2] = read();

		timeToNextMeasure = atoi(timeToNextMeasure_string);
		// Number of values returned
		numberOfMeasures = read();
	}
	else
	{
		//invalid data
		#if SDI12DEBUG > 0
			char message[20];
			//"invalid data"
			strcpy_P(message, (char*)pgm_read_word(&(table_sdi12[7])));
			PRINT_SDI12(message);
		#endif
		return 0;
	}

	#if SDI12DEBUG > 1
		PRINT_SDI12(F("timeToNextMeasure:"));
		USB.println(timeToNextMeasure, DEC);
		PRINT_SDI12(F("numberOfMeasures:"));
		USB.println(numberOfMeasures);
	#endif

	return 1;
}


 /*!
 * \brief Read measures of the SDI12 sensor
 * \param Sensor searched name
 *        Sensor searched length
 *        Sensor Serial Number
 *        parameter1
 *        parameter2
 *        parameter3
 *        parameter4
 * \return 0 if sensor not present or invalid data. 1 Otherwise.
 */
uint8_t WaspSDI12::readMeasures(char *sensorSearchedName, uint8_t sensorSearchedNameLength,
								char *sensorSerialNumber,
								float &parameter1,
								float &parameter2,
								float &parameter3,
								float &parameter4)
{
	char command[6];

	// READING
	char measures[50];
	char aux[6];
	uint8_t i = 0;

	uint8_t numberFields = 4;

	if(parameter4 == -1000)
	{
		numberFields = 3;

		if(parameter3 == -1000)
		{
			numberFields = 2;

			if(parameter2 == -1000)
			{
				numberFields = 1;
			}
		}
	}

	memset(aux, 0x00, sizeof(aux));

	//check if correct SDI12 sensor connected
    if (isSensor(sensorSearchedName, sensorSearchedNameLength, sensorSerialNumber) == 0)
	{
		memset(sensorSerialNumber, 0x00, sizeof(sensorSerialNumber));
		setState(DISABLED);
		return 0;
	}

	if (startSensor() == 0)
	{
		setState(DISABLED);
		return 0;
	}

	// now wait timeToNextMeasure till data is ready + aditional delay
	delay((timeToNextMeasure*1000) + 10);

	// send data command aD0!. Build command with address
	strcpy_P(aux, (char*)pgm_read_word(&(table_sdi12[2])));
	snprintf(command, sizeof(command), "%c%s", address, aux);

	sendCommand(command, strlen(command));
	readCommandAnswer(30, LISTEN_TIME);

	// clear measures array
	memset(measures, 0x00, sizeof(measures));

	// store the reading in measures buffer
	if (available() > 7)
	{
		//skip address because it is not possible to connect more than one SDI-12 sensor at the same time
		read();

		while (available() && (i < 30))
		{
			measures[i] = read();
			if (measures[i] == NULL) break;
			i++;
		}
	}
	setState(DISABLED);

	// PARSING
	i = 0;
	uint8_t counter = 0;

	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;

	uint8_t len = strlen(measures);

	char stringParameter1[20];
	char stringParameter2[20];
	char stringParameter3[20];
	char stringParameter4[20];

	//Empty the arrays
	memset(stringParameter1, 0x00, sizeof(stringParameter1));
	memset(stringParameter2, 0x00, sizeof(stringParameter2));
	memset(stringParameter3, 0x00, sizeof(stringParameter3));
	memset(stringParameter4, 0x00, sizeof(stringParameter4));

	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter <= numberFields) && (i <= len))
	{
		if ((measures[i] == '+') || (measures[i] == '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1:
				stringParameter1[a] = measures[i];
				a++;
				break;

			case 2:
				stringParameter2[b] = measures[i];
				b++;
				break;

			case 3:
				stringParameter3[c] = measures[i];
				c++;
				break;

			case 4:
				stringParameter4[d] = measures[i];
				d++;
				break;

			default:
				break;
		}
		i++;
	}

	//add eof to strings
	stringParameter1[a] = '\0';
	stringParameter2[b] = '\0';
	stringParameter3[c] = '\0';
	stringParameter4[d] = '\0';

	// Convert strings to float values
	parameter1 = atof(stringParameter1);
	parameter2 = atof(stringParameter2);
	parameter3 = atof(stringParameter3);
	parameter4 = atof(stringParameter4);


	#if SDI12DEBUG > 0
		PRINT_SDI12(F("measures:"));
		USB.println(measures);
		PRINT_SDI12(F("Parameter 1:"));
		USB.println(parameter1);
		PRINT_SDI12(F("Parameter 2:"));
		USB.println(parameter2);
		PRINT_SDI12(F("Parameter 3:"));
		USB.println(parameter3);
		PRINT_SDI12(F("Parameter 4:"));
		USB.println(parameter4);
	#endif

	// If every value have been measured, return 1.
	// (counter == numberFields + 1) explication:
	// Some sensors include a '+' simbol at the end of the SDI12 string
	// "+25.582+7.1277-2.2480-8.3837+"
	if ((counter == numberFields) || (counter == numberFields + 1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


 /*!
 * \brief Read measures of the SDI12 sensor
 * \param Sensor searched name
 *        Sensor searched length
 *        Sensor Serial Number
 *        parameter1
 *        parameter2
 *        parameter3
 *        parameter4
 * \return 0 if sensor not present or invalid data. 1 Otherwise.
 */
uint8_t WaspSDI12::readSACMeasures(char *sensorSearchedName, uint8_t sensorSearchedNameLength,
								char *sensorSerialNumber,
								float &parameter1,
								float &parameter2,
								float &parameter3,
								float &parameter4,
								float &parameter5)
{
	char command[6];

	// READING
	char measures[50];
	char aux[6];
	uint8_t i = 0;

	uint8_t numberFields = 5;

	memset(aux, 0x00, sizeof(aux));
	
	//check if correct SDI12 sensor connected
    if (isSensor(sensorSearchedName, sensorSearchedNameLength, sensorSerialNumber) == 0)
	{
		memset(sensorSerialNumber, 0x00, sizeof(sensorSerialNumber));
		setState(DISABLED);
		return 0;
	}

	if (startSensor() == 0)
	{
		setState(DISABLED);
		return 0;
	}

	// now wait timeToNextMeasure till data is ready + aditional delay
	delay((timeToNextMeasure*1000) + 10);

	// send data command aD0!. Build command with address
	strcpy_P(aux, (char*)pgm_read_word(&(table_sdi12[2])));
	snprintf(command, sizeof(command), "%c%s", address, aux);

	sendCommand(command, strlen(command));
	readCommandAnswer(36, 500);

	// clear measures array
	memset(measures, 0x00, sizeof(measures));

	// store the reading in measures buffer
	if (available() > 7)
	{
		//skip address because it is not possible to connect more than one SDI-12 sensor at the same time
		read();

		while (available() && (i < 36))
		{
			measures[i] = read();
			if (measures[i] == NULL) break;
			i++;
		}
	}
	setState(DISABLED);

	// PARSING
	i = 0;
	uint8_t counter = 0;

	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint8_t e = 0;

	uint8_t len = strlen(measures);


	char stringParameter1[20];
	char stringParameter2[20];
	char stringParameter3[20];
	char stringParameter4[20];
	char stringParameter5[20];

	//Empty the arrays
	memset(stringParameter1, 0x00, sizeof(stringParameter1));
	memset(stringParameter2, 0x00, sizeof(stringParameter2));
	memset(stringParameter3, 0x00, sizeof(stringParameter3));
	memset(stringParameter4, 0x00, sizeof(stringParameter4));
	memset(stringParameter4, 0x00, sizeof(stringParameter4));

	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter <= numberFields) && (i <= len))
	{		
		if ((measures[i] == '+') || (measures[i] == '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1:
				stringParameter1[a] = measures[i];
				a++;
				break;

			case 2:
				stringParameter2[b] = measures[i];
				b++;
				break;

			case 3:
				stringParameter3[c] = measures[i];
				c++;
				break;

			case 4:
				stringParameter4[d] = measures[i];
				d++;
				break;
				
			case 5:
				stringParameter5[e] = measures[i];
				e++;
				break;

			default:
				break;
		}
		i++;
	}

	//add eof to strings
	stringParameter1[a] = '\0';
	stringParameter2[b] = '\0';
	stringParameter3[c] = '\0';
	stringParameter4[d] = '\0';
	stringParameter5[e] = '\0';

	// Convert strings to float values
	parameter1 = atof(stringParameter1);
	parameter2 = atof(stringParameter2);
	parameter3 = atof(stringParameter3);
	parameter4 = atof(stringParameter4);
	parameter5 = atof(stringParameter5);


	#if SDI12DEBUG > 0
		PRINT_SDI12(F("measures:"));
		USB.println(measures);
		PRINT_SDI12(F("Parameter 1:"));
		USB.println(parameter1);
		PRINT_SDI12(F("Parameter 2:"));
		USB.println(parameter2);
		PRINT_SDI12(F("Parameter 3:"));
		USB.println(parameter3);
		PRINT_SDI12(F("Parameter 4:"));
		USB.println(parameter4);
		PRINT_SDI12(F("Parameter 5:"));
		USB.println(parameter5);
	#endif

	// If every value have been measured, return 1.
	// (counter == numberFields + 1) explication:
	// Some sensors include a '+' simbol at the end of the SDI12 string
	// "+25.582+7.1277-2.2480-8.3837+"
	if ((counter == numberFields) || (counter == numberFields + 1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*!
* \brief Read measures of the SDI12 sensor
* \param Sensor searched name
*        Sensor searched length
*        Sensor Serial Number
*        parameter1
*        parameter2
*        parameter3
*        parameter4
* \return 0 if sensor not present or invalid data. 1 Otherwise.
*/
uint8_t WaspSDI12::readMeasuresFast(char *sensorSearchedName, uint8_t sensorSearchedNameLength,
               char *sensorSerialNumber,
               float &parameter1,
               float &parameter2,
               float &parameter3,
               float &parameter4,
               bool readSensorBodyTemp)
{
 char command[6];

 // READING
 char measures[50];
 char aux[6];
 uint8_t i = 0;

 uint8_t numberFields = 4;

 if(parameter4 == -1000)
 {
   numberFields = 3;

   if(parameter3 == -1000)
   {
     numberFields = 2;

     if(parameter2 == -1000)
     {
       numberFields = 1;
     }
   }
 }

 memset(aux, 0x00, sizeof(aux));

 //check if correct SDI12 sensor connected
 /*if (isSensor(sensorSearchedName, sensorSearchedNameLength, sensorSerialNumber) == 0)
 {
   memset(sensorSerialNumber, 0x00, sizeof(sensorSerialNumber));
   setState(DISABLED);
   return 0;
 }*/

 if (startSensor(readSensorBodyTemp) == 0)
 {
   setState(DISABLED);
   return 0;
 }

 // now wait timeToNextMeasure till data is ready + aditional delay
 //delay((timeToNextMeasure*1000) + 10);
 // FIX: delay hardcoded to minimum valid tested value
 delay(500);

 // send data command aD0!. Build command with address
 strcpy_P(aux, (char*)pgm_read_word(&(table_sdi12[2])));
 snprintf(command, sizeof(command), "%c%s", address, aux);

 sendCommand(command, strlen(command));
 readCommandAnswer(30, LISTEN_TIME);

 // clear measures array
 memset(measures, 0x00, sizeof(measures));

 // store the reading in measures buffer
 if (available() > 7)
 {
   //skip address because it is not possible to connect more than one SDI-12 sensor at the same time
   read();

   while (available() && (i < 30))
   {
     measures[i] = read();
     if (measures[i] == NULL) break;
     i++;
   }
 }
 setState(DISABLED);

 // PARSING
 i = 0;
 uint8_t counter = 0;

 uint8_t a = 0;
 uint8_t b = 0;
 uint8_t c = 0;
 uint8_t d = 0;

 uint8_t len = strlen(measures);

 char stringParameter1[20];
 char stringParameter2[20];
 char stringParameter3[20];
 char stringParameter4[20];

 //Empty the arrays
 memset(stringParameter1, 0x00, sizeof(stringParameter1));
 memset(stringParameter2, 0x00, sizeof(stringParameter2));
 memset(stringParameter3, 0x00, sizeof(stringParameter3));
 memset(stringParameter4, 0x00, sizeof(stringParameter4));

 //if invalid data, return 0.
 if (len == 0)
 {
   return 0;
 }

 while((counter <= numberFields) && (i <= len))
 {
   if ((measures[i] == '+') || (measures[i] == '-'))
   {
     counter++;
   }
   switch (counter)
   {
     case 1:
       stringParameter1[a] = measures[i];
       a++;
       break;

     case 2:
       stringParameter2[b] = measures[i];
       b++;
       break;

     case 3:
       stringParameter3[c] = measures[i];
       c++;
       break;

     case 4:
       stringParameter4[d] = measures[i];
       d++;
       break;

     default:
       break;
   }
   i++;
 }

 //add eof to strings
 stringParameter1[a] = '\0';
 stringParameter2[b] = '\0';
 stringParameter3[c] = '\0';
 stringParameter4[d] = '\0';

 // Convert strings to float values
 parameter1 = atof(stringParameter1);
 parameter2 = atof(stringParameter2);
 parameter3 = atof(stringParameter3);
 parameter4 = atof(stringParameter4);


 #if SDI12DEBUG > 0
   PRINT_SDI12(F("measures:"));
   USB.println(measures);
   PRINT_SDI12(F("Parameter 1:"));
   USB.println(parameter1);
   PRINT_SDI12(F("Parameter 2:"));
   USB.println(parameter2);
   PRINT_SDI12(F("Parameter 3:"));
   USB.println(parameter3);
   PRINT_SDI12(F("Parameter 4:"));
   USB.println(parameter4);
 #endif

 // If every value have been measured, return 1.
 // (counter == numberFields + 1) explication:
 // Some sensors include a '+' simbol at the end of the SDI12 string
 // "+25.582+7.1277-2.2480-8.3837+"
 if ((counter == numberFields) || (counter == numberFields + 1))
 {
   return 1;
 }
 else
 {
   return 0;
 }
}
