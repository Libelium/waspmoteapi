/*
 *  Library for managing the GPS v2.0 JN3 receiver
 *
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.4
 *  Design:			David Gascón
 *  Implementation:	Javier Siscart
 */


/******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspGPS.h"


/******************************************************************************
 * FLASH DEFINITIONS
 ******************************************************************************/

/// table_GPS /////////////////////////////////////////////////////////////////
const char	gps_string_00[]	PROGMEM = "$PSRF100,0,115200,8,1,0*00";			// 0
const char	gps_string_01[]	PROGMEM = "$PSRF104,%s,%s,%s,%s,%s,%s,%s,%s*00";// 1
const char	gps_string_02[]	PROGMEM = "$GPRMC";   							// 2
const char	gps_string_03[]	PROGMEM = "$GPGGA";   							// 3
const char	gps_string_04[]	PROGMEM = "$GPGSA";   							// 4
const char	gps_string_05[]	PROGMEM = "$GPGSV";   							// 5
const char	gps_string_06[]	PROGMEM = "$GPGLL";   							// 6
const char	gps_string_07[]	PROGMEM = "$GPVTG";   							// 7
const char	gps_string_08[]	PROGMEM = "%s\r\n";   							// 8
const char	gps_string_09[]	PROGMEM = "$PSRF125*00";   						// 9
const char	gps_string_10[]	PROGMEM = "$PSRF195";   						// 10


const char* const table_GPS[] PROGMEM =
{
	gps_string_00,		// 0
	gps_string_01,		// 1
	gps_string_02,		// 2
	gps_string_03,		// 3
	gps_string_04,		// 4
	gps_string_05,		// 5
	gps_string_06,		// 6
	gps_string_07,		// 7
	gps_string_08,		// 8
	gps_string_09,		// 9
	gps_string_10,		// 10

};


/******************************************************************************
 * User API
 ******************************************************************************/


/******************************************************************************
 * PRIVATE FUNCTIONS                                                          *
 ******************************************************************************/

/*
 * begin (void) - set UART1's multiplexer to GPS and open the serial port
 *
 * opens the serial port at 4800.
 *
 *
 * On Wasp, calling GPS.begin() means initializing the internal UART drivers
 * inside the ATMEGA1281 processor. In order to push the power consumption to
 * the minimum you should remember calling GPS.close() after working with the
 * GPS
 */
void WaspGPS::begin(void)
{
 	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();

	// open UART
	beginSerial(_baudRate,_uart);
}

/*
 * close (void) - close the serial port
 *
 * closes the serial port and unset the UART1's multiplexer
 *
 * An example on the use of this on the code is:
 *
 *   GPS.close();
 *
 * On Wasp, calling GPS.close() means disconnecting the internal UART drivers
 * inside the ATMEGA1281 processor. This will push the power consumption to
 * the minimum, since the UART is making a massive use of resources
 */
void WaspGPS::close()
{
	// close UART
	closeSerial(_uart);

	// Disable UART1's multiplexer
	Utils.setMux(LOW,LOW);
}


 /*
 * setCommMode (uint8_t mode) - switches between communication modes
 *
 * Switches between NMEA and binary (OSP) communication modes
 *
 * return 0 if already in that mode, 1 otherwise.
 *
 */
//
uint8_t WaspGPS::setCommMode(uint8_t mode)
{
	if (mode == _commMode) return 0;

	switch(mode)
  {
  case OSP_MODE:

	// By default OSP at 115200.
    _commMode = OSP_MODE;

	// copy "$PSRF100,0,115200,8,1,0*00" from flash memory
	char aux[40];
    strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[0])));

 	sendCommand(aux);
	delay(100);

    // Now change UART baudrate
	closeSerial(_uart);
	delay(10);
	_baudRate = 115200;
	beginSerial(_baudRate,_uart);
    break;

  case NMEA_MODE:

	// By default NMEA at 4800, enabling all NMEA sentences
    _commMode = NMEA_MODE;

    // Command to switch from OSP to NMEA 4800, with all NMEA sentences.
    //A0 A2 00 18 81 02 01 01 01 01  01 01 05 01 01 01 01 01 00 01  00
	//00 00 01 00 00 12 C0 01 67 B0 B3
    uint8_t outBuff[32] =
     {0xA0,0xA2,0x00,0x18,0x81,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x05,
	0x01,0x01,0x01,0x01,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,
	0x12,0xC0,0x01,0x67,0xB0,0xB3};

    sendCommand(outBuff,32);
    delay(100);

    //NMEA mode by default at 4800.
    // Now change UART baudrate
    closeSerial(_uart);
	delay(10);
	 _baudRate = 4800;
	beginSerial(_baudRate,_uart);
	break;
  }

  return 1;
}

/*
 * init (void) - initialize the GPS using grouped parameters
 *
 */
uint8_t WaspGPS::init()
{
	return init(	coordinateLat,
			coordinateLon,
			coordinateAl,
			clkOffset,
			timeOfWeek,
			weekNo,
			channel,
			resetCfg);
}

/*
 * init () - initialize the GPS using grouped parameters
 *
 */
uint8_t WaspGPS::init(const char* _coordinateLat,
					const char* _coordinateLon,
					const char* _coordinateAl,
					const char* _clkOffset,
					const char* _timeOfWeek,
					const char* _weekNo,
					const char* _channel,
					const char* _resetCfg	)
{
	char dummyBuffer[4] ="";
	unsigned long previous = millis();
	uint8_t valid = 0;

	// Ensure that module is in NMEA mode by default
	setCommMode(OSP_MODE);
	delay(100);
	setCommMode(NMEA_MODE);
	delay(100);

	// Look for starting sentence
	while( (!valid) && (millis()-previous)<2000)
	{
		//read three bytes
		if(serialAvailable(_uart)>3)
		{
			dummyBuffer[0] = serialRead(_uart);
			if (dummyBuffer[0] == '$')
			{
				dummyBuffer[1] = serialRead(_uart);
				dummyBuffer[2] = serialRead(_uart);
				dummyBuffer[3] = '\0';

				#ifdef GPS_DEBUG
				PRINT_GPS(F("dummyBuffer:"));
				USB.println(dummyBuffer);
				#endif

				//check if NMEA sentence ($GP...) or init msg found
				//strcmp returns '0' if both equal
				if((!strcmp(dummyBuffer,"$GP")) || (!strcmp(dummyBuffer,"$PS")))
				{
					#ifdef GPS_DEBUG
					PRINT_GPS(F("INIT OK\n"));
					#endif
					valid=1;
				}
			}
		}
		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	// clear variable
	memset(_dataBuffer, 0x00, sizeof(_dataBuffer) );

	//add here coordinates setting.

	// copy "$PSRF104,%s,%s,%s,%s,%s,%s,%s,%s*00" from flash memory
	char aux[40] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[1])));
	// create LLANavigationInitialization command
	snprintf(_dataBuffer, sizeof(_dataBuffer), aux, _coordinateLat, _coordinateLon,
															_coordinateAl,
															_clkOffset,
															_timeOfWeek,
															_weekNo,
															_channel,
															_resetCfg);
	// sencoCommand() not used here.
	setChecksum(_dataBuffer);
	snprintf(_dataBuffer, sizeof(_dataBuffer), "%s\r\n", _dataBuffer);
	serialFlush(_uart);
	printString(_dataBuffer,_uart);

	// Ensure that module is in NMEA mode by default
	if(!valid)
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("init command not found.\n"));
		#endif
		OFF();
	}

	return valid;
}

/*
 * checkSum (gpsString) - checks the NMEA checkSum of a NMEA sentence
 *
 * returns 1 if the checksum is right, 0 if error
 *
 */
uint8_t WaspGPS::checkNMEAMsg(const char* gpsString)
{

  // return error if there is no asterisk at the end of the string
  if (gpsString[strlen(gpsString)-3] != '*') return 0;

  char check = 0;
  // iterate over the string, XOR each byte with the total sum:
  for (uint16_t c = 1; c < strlen(gpsString) - 3; c++)
  {
    check = char(check ^ gpsString[c]);
  }

  // get the checksum character for the string itself
  char stringCheckSum = (gpsString[strlen(gpsString)-2] - '0') << 4 |
						(gpsString[strlen(gpsString)-1] - '0');

  uint8_t result = (check == stringCheckSum);

  // return the result
  return result;
}

/* getChecksum (gpsString) - calculate the NMEA checkSum, leave out $, *, and
 * the checkSum bytes
 *
 * returns 1 if the checksum is right, 0 if error
 *
 * credit: Tom Igoe
 */
uint8_t WaspGPS::getChecksum(const char* gpsString)
{
  char check = 0;
  // iterate over the string, XOR each byte with the total sum:
  for (uint16_t c = 1; c < strlen(gpsString) - 3; c++)
  {
    check = char(check ^ gpsString[c]);
  }
  return check;
}

/* getChecksum(buffer) - calculate checksum for a secuence given as a parameter
 *
 * It calculates the corresponding checksum for a secuence given as a parameter
 *
 * It stores in 'checkSUM' variable the result
 */
void WaspGPS::getChecksum(uint8_t* buffer)
{
	int a = 4;
	int check = 0;
	uint8_t aux = 0, aux2 = 0;
	while( (buffer[aux] != 0xB0) || (buffer[aux+1] != 0xB3) )
	{
		aux++;
	}
	buffer[aux-1] = 0x00;
	buffer[aux-2] = 0x00;
	aux = 0;
	while( (buffer[a] != 0xB0) || (buffer[a+1] != 0xB3) )
	{
		check += buffer[a];
		check &= 0x7FFF;
		a++;
	}
	if(check > 255)
	{
		aux = check / 256;
		aux2 = check - (aux*256);
		_checkSUM[0] = aux;
		_checkSUM[1] = aux2;
	}
	else
	{
		_checkSUM[0] = 0x00;
		_checkSUM[1] = check;
	}
}


/* returns the introduced command with checksum added.
 * the command lenght must include checksum bytes.
 */
char* WaspGPS::setChecksum(char * command)
{
	uint8_t length = 0;
	uint8_t aux_1 = 0;
    uint8_t aux_2 = 0;
	char checksumStr[3] ="";

	_checksum = getChecksum(command);

	aux_1 = _checksum/16;
    aux_2 = _checksum%16;
    if (aux_1 < 10)
    {
      checksumStr[0] = aux_1+'0';
    }
    else{
      checksumStr[0] = aux_1+('A'-10);
    }
    if (aux_2 < 10){
      checksumStr[1] = aux_2+'0';
    }
    else{
      checksumStr[1] = aux_2+('A'-10);
    }

	checksumStr[2] = '\0';

	//append checksum to the command
	length = strlen(command);
	command[length-2] = checksumStr[0];
	command[length-1] = checksumStr[1];

	return command;
}


/* parseRMC() - listen to serial port and parse the NMEA RMC sentence,
 * updating necessary global variables.
 *
 * return '0' if not connected yet, '-1' if no RMC sentence parsed,
 * '-2' if no gps data, '1' if connected.
 */
int8_t WaspGPS::parseRMC()
{  
	#ifdef GPS_DEBUG
	PRINT_GPS(F("parseRMC\n"));
	#endif

	char* argument;
	char dummyBuffer[7] ="";
	uint8_t i = 0;
	bool valid = 0;
	bool end = 0;

	// Look for starting NMEA RMC characters '$GPRMC'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<2000)
	{
		if(serialAvailable(_uart) > 0)
		{
			dummyBuffer[0] = serialRead(_uart);
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5) && (millis()-previous)<2000);
				for (i=1; i<6;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';

				// check if RMC sentence
				// copy "$GPRMC" from flash memory
				char aux[10] ="";
				strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[2])));

				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer, aux) )
				{
					valid = 1;
				}
			}
		}

		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("no GPS data\n"));
		#endif
		return -2;
	}

	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i=0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				_dataBuffer[i] = serialRead(_uart);
				if (_dataBuffer[i] == '*' || _dataBuffer[i] == '$')
				{
					// end of NMEA or new one.
					end = 1;
					_dataBuffer[i+1] = '\0';
				}
				i++;
			}
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		// Now parse the read NMEA sentence
		// separate all the subarrays from 'dataBuffer' to 'argument' pointer
		// Example: $GPRMC,161229.487,A,3723.2475,N,12158.3416,W,0.13,309.62,120598, ,*10
		// Define buffer to parse received data
		char _dataBuffer2[GPS_BUFFER_SIZE];
		memset(_dataBuffer2, 0x00, sizeof(_dataBuffer2));
		strncpy(_dataBuffer2, _dataBuffer, strlen(_dataBuffer));
		_dataBuffer2[strlen(_dataBuffer)]='\0';

		#ifdef GPS_DEBUG
		PRINT_GPS(F("inbuffer2:"));
		USB.println(_dataBuffer2);
		#endif

		//first of all, look if connected
		argument = strtok (_dataBuffer2, ",");
		//strcmp returns '0' if both equal
		if(!strcmp(argument, "V") )
		{
			strncpy(state,argument,strlen(argument));
			state[strlen(argument)]='\0';
		}
		else
		{
			// time is set before getting possition
			strncpy(timeGPS, argument, strlen(argument));
			timeGPS[strlen(argument)]='\0';

			#ifdef GPS_DEBUG
			PRINT_GPS(F("timeGPS:"));
			USB.println(timeGPS);
			#endif

			// status
			argument = strtok(NULL,",");
			strncpy(state, argument, strlen(argument));
			state[strlen(argument)]='\0';

			#ifdef GPS_DEBUG
			PRINT_GPS(F("state:"));
			USB.println(state);
			#endif
		}

		if (state[0] == 'A')
		{
			#ifdef GPS_DEBUG
			PRINT_GPS(F("connected\n"));
			#endif
			 //connected. keep extracting tokens.
			 // latitude
			argument = strtok(NULL,",");
			strncpy(latitude, argument, strlen(argument));
			latitude[strlen(argument)]='\0';

			// North/South
			argument = strtok(NULL,",");
			NS_indicator = argument[0];

			 // Longitude
			argument = strtok(NULL,",");
			strncpy(longitude, argument, strlen(argument));
			longitude[strlen(argument)]='\0';

			// East / West
			argument = strtok(NULL,",");
			EW_indicator = argument[0];

			// Speed
			argument = strtok(NULL,",");
			strncpy(speed, argument, strlen(argument));
			speed[strlen(argument)] = '\0';

			// convert speed from knots to Km/h
			//1 Knot = 1,852 Km/h
			float speedKM = atof(speed);
			speedKM = speedKM * 1.852;
			Utils.float2String(speedKM, speed, 2);
			i = strlen(speed);
			speed[i] = '\0';

			// Course deegrees
			argument = strtok(NULL,",");
			strncpy(course, argument, strlen(argument));
			course[strlen(argument)] = '\0';

			// date
			argument = strtok(NULL,",");
			strncpy(dateGPS, argument, strlen(argument));
			dateGPS[strlen(argument)] = '\0';

			// mode
			argument = strtok(NULL,",");
			strncpy(RMCMode, argument, strlen(argument));
			RMCMode[strlen(argument)] = '\0';

			#ifdef GPS_DEBUG
			PRINT_GPS(F("latitude:"));
			USB.println(latitude);
			PRINT_GPS(F("NS_indicator:"));
			USB.println(NS_indicator);
			PRINT_GPS(F("longitude:"));
			USB.println(longitude);
			PRINT_GPS(F("EW_indicator:"));
			USB.println(EW_indicator);
			PRINT_GPS(F("speed:"));
			USB.println(speed);
			PRINT_GPS(F("course:"));
			USB.println(course);
			PRINT_GPS(F("date:"));
			USB.println(dateGPS);
			#endif

			return 1;
		}
		else
		{
			if (state[0] == 'V')
			{
				#ifdef GPS_DEBUG
				PRINT_GPS(F("not connected\n"));
				#endif
				// Not connected
				return 0;
			}

			// If state is not V and it is not connected, must be an error parsing
			return -1;
		}
	}
	else
		{
			#ifdef GPS_DEBUG
			PRINT_GPS(F("not RMC NEMEA\n"));
			#endif
			// Not RMC NMEA sentence
			valid = 0;
			return -1;
		}
}

/* parseGGA() - listen to serial port and parse the NMEA GGA sentence,
 * updating necessary global variables.
 *
 * return '0' if not connected yet, '-1' if no GGA sentence parsed,
 * '-2' if no gps data, '1' if connected.
 */
int8_t WaspGPS::parseGGA()
{
	#ifdef GPS_DEBUG
	PRINT_GPS(F("parseGGA\n"));
	#endif

	char* argument;
	char dummyBuffer[7] ="";
	uint8_t i = 0;
	bool valid = 0;
	bool end = 0;

	// Look for starting NMEA GGA characters '$GPGGA'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<2000)
	{
		if(serialAvailable(_uart) > 0)
		{
			dummyBuffer[0] = serialRead(_uart);
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5)&& (millis()-previous)<2000);
				for (i = 1; i < 6; i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';

				// check if GGA sentence
				// copy "$GPGGA" from flash memory
				char aux[10] ="";
				strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[3])));
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer, aux) )
				{
					#ifdef GPS_DEBUG
					PRINT_GPS(F("dummyBuffer: "));
					USB.print(dummyBuffer);
					USB.println(F(" , valid: "));
					#endif
					valid = 1;
				}
			}
		}

		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("no GPS data\n"));
		#endif
		return -2;
	}

	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i=0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				_dataBuffer[i] = serialRead(_uart);
				if (_dataBuffer[i] == '*' || _dataBuffer[i] == '$')
				{
					// end of NMEA or new one.
					end = 1;
					_dataBuffer[i+1] = '\0';
				}
				i++;
			}
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		// Now parse the read NMEA sentence
		// separate all the subarrays from '_dataBuffer' to 'argument' pointer
		// Define buffer to parse received data
		char _dataBuffer2[GPS_BUFFER_SIZE];
		memset(_dataBuffer2, 0x00, sizeof(_dataBuffer2));
		strncpy(_dataBuffer2, _dataBuffer, strlen(_dataBuffer));
		_dataBuffer2[strlen(_dataBuffer)] = '\0';

		#ifdef GPS_DEBUG
		PRINT_GPS(F("inbuffer2: "));
		USB.println(_dataBuffer2);
		#endif

		//first of all, look if connected
		argument = strtok (_dataBuffer2,",");
		//strcmp returns '0' if both equal
		if(!strcmp(argument,"0") )
		{
			strncpy(state, argument, strlen(argument));
			state[strlen(argument)] = '\0';
		}
		else
		{
			// time is set before getting possition
			strncpy(timeGPS, argument, strlen(argument));
			timeGPS[strlen(argument)] = '\0';

			#ifdef GPS_DEBUG
			PRINT_GPS(F("timeGPS: "));
			USB.println(timeGPS);
			#endif

			// status or LAT?
			argument = strtok(NULL, ",");
			if(!strcmp(argument, "0") )
			{
				strncpy(state, argument, strlen(argument));
				state[strlen(argument)] = '\0';

				#ifdef GPS_DEBUG
				PRINT_GPS(F("state: "));
				USB.println(state);
				#endif
			}
			else
			{
				#ifdef GPS_DEBUG
				PRINT_GPS(F("connected:\n"));
				#endif
				 //connected. keep extracting tokens.
				 // latitude
				strncpy(latitude, argument, strlen(argument));
				latitude[strlen(argument)] = '\0';

				// North/South
				argument = strtok(NULL, ",");
				NS_indicator = argument[0];

				 // Longitude
				argument = strtok(NULL, ",");
				strncpy(longitude, argument, strlen(argument));
				longitude[strlen(argument)] = '\0';

				// East / West
				argument = strtok(NULL, ",");
				EW_indicator = argument[0];

				//position FIX
				argument = strtok(NULL, ",");
				strncpy(state, argument, strlen(argument));
				state[strlen(argument)] = '\0';

				// satellites used
				argument = strtok(NULL, ",");
				strncpy(satellites, argument, strlen(argument));
				satellites[strlen(argument)] = '\0';

				// Precision
				argument = strtok(NULL, ",");
				strncpy(accuracy, argument, strlen(argument));
				accuracy[strlen(argument)] = '\0';

				// Altitude
				argument = strtok(NULL, ",");
				strncpy(altitude, argument, strlen(argument));
				altitude[strlen(argument)] = '\0';

				// units of altitude, geoid separation and units, not parsed

				#ifdef GPS_DEBUG
				PRINT_GPS(F("latitude:"));
				USB.println(latitude);
				PRINT_GPS(F("NS_indicator:"));
				USB.println(NS_indicator);
				PRINT_GPS(F("longitude:"));
				USB.println(longitude);
				PRINT_GPS(F("EW_indicator:"));
				USB.println(EW_indicator);
				PRINT_GPS(F("state:"));
				USB.println(state);
				PRINT_GPS(F("satellites:"));
				USB.println(satellites);
				PRINT_GPS(F("precision:"));
				USB.println(accuracy);
				PRINT_GPS(F("Altitude:"));
				USB.println(altitude);
				#endif

				return 1;
			}
		}

		#ifdef GPS_DEBUG
		PRINT_GPS(F("not connected\n"));
		#endif
		// Not connected
		return 0;
	}
	else
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("not GGA NEMEA\n"));
		#endif
		// Not RMC NMEA sentence
		valid = 0;
		return -1;
	}
}

/* parseGSA() - listen to serial port and parse the NMEA GSA sentence,
 * updating necessary global variables.
 *
 * return '0' if possition not fixed, '-1' if not NMEA sentence, '1' otherwise
 */
int8_t WaspGPS::parseGSA()
{
	#ifdef GPS_DEBUG
	PRINT_GPS(F("parseGSA\n"));
	#endif

	char* argument;
	char dummyBuffer[7] ="";
	uint8_t i = 0;
	bool valid = 0;
	bool end = 0;

	// Look for starting NMEA GSA characters '$GPGSA'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<2000)
	{
		if(serialAvailable(_uart) > 0)
		{
			dummyBuffer[0] = serialRead(_uart);
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5) && (millis()-previous)<2000);
				for (i=1; i<6;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';

				// check if GSA sentence
				// copy "$GPGSA" from flash memory
				char aux[10] ="";
				strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[4])));
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer, aux) )
				{
					#ifdef GPS_DEBUG
					PRINT_GPS(F("dummyBuffer: "));
					USB.print(dummyBuffer);
					USB.println(F(" , valid:"));
					#endif
					valid = 1;
				}
			}
		}

		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("no GPS data\n"));
		#endif
		return -2;
	}

	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i = 0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				_dataBuffer[i] = serialRead(_uart);
				if (_dataBuffer[i] == '*' || _dataBuffer[i] == '$')
				{
					// end of NMEA or new one.
					end = 1;
					_dataBuffer[i+1] = '\0';
				}
				i++;
			}
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		// Now parse the read NMEA sentence
		// separate all the subarrays from '_dataBuffer' to 'argument' pointer
		// Define buffer to parse received data
		char _dataBuffer2[GPS_BUFFER_SIZE];
		memset(_dataBuffer2, 0x00, sizeof(_dataBuffer2));
		strncpy(_dataBuffer2, _dataBuffer, strlen(_dataBuffer));
		_dataBuffer2[strlen(_dataBuffer)] = '\0';

		#ifdef GPS_DEBUG
		PRINT_GPS(F("inbuffer2: "));
		USB.println(_dataBuffer2);
		#endif

		// Mode 1
		argument = strtok (_dataBuffer2,",");
		strncpy(GSAMode1, argument, strlen(argument));
		GSAMode1[strlen(argument)] = '\0';

		// Mode 2
		argument = strtok(NULL,",");
		strncpy(GSAMode2, argument, strlen(argument));
		GSAMode2[strlen(argument)] = '\0';

		if (GSAMode2[0] == '1')
		{
			// position not fixed, exit.
			#ifdef GPS_DEBUG
			PRINT_GPS(F("Position not fixed yet\n"));
			#endif
			return 0;
		}
		else
		{
			// Precision Posicion
			argument = strtok(NULL,",");
			strncpy(dummyBuffer, argument, strlen(argument));

			previous = millis();
			while (((strlen(argument) == 2) || (dummyBuffer[0] == '*')) && ((millis()-previous)<1000))
			{
				argument = strtok(NULL,",");
				strncpy(dummyBuffer, argument, strlen(argument));
				//avoid millis overflow problem
				if( millis() < previous ) previous = millis();
			}

			strncpy(PDOPAccuracy, argument, strlen(argument));
			PDOPAccuracy[strlen(argument)] = '\0';

			// Precision horizontal
			argument = strtok(NULL,",");
			strncpy(HDOPAccuracy, argument, strlen(argument));
			HDOPAccuracy[strlen(argument)] = '\0';

			// Precision vertical
			argument = strtok(NULL,"*");
			strncpy(VDOPAccuracy, argument, strlen(argument));
			VDOPAccuracy[strlen(argument)] = '\0';

			#ifdef GPS_DEBUG
			PRINT_GPS(F("mode1: "));
			USB.println(GSAMode1);
			PRINT_GPS(F("mode2: "));
			USB.println(GSAMode2);
			PRINT_GPS(F("PDOP: "));
			USB.println(PDOPAccuracy);
			PRINT_GPS(F("HDOP: "));
			USB.println(HDOPAccuracy);
			PRINT_GPS(F("VDOP: "));
			USB.println(VDOPAccuracy);
			#endif

			return 1;
		}
	}
	else
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("not GSA NEMEA\n"));
		#endif
		// Not RMC NMEA sentence
		valid = 0;
		return -1;
	}
}

/* parseGSV() - listen to serial port and parse the NMEA GSV sentence,
 * updating necessary global variables.
 *
 * return '-1' if not GSV NMEA sentence, '1' if 0k, '-2' if no gps data.
 */
//
int8_t WaspGPS::parseGSV()
{
	#ifdef GPS_DEBUG
	PRINT_GPS(F("parseGSV\n"));
	#endif

	char* argument;
	char dummyBuffer[7] ="";
	uint8_t i = 0;
	bool valid = 0;
	bool end = 0;

	// Look for starting NMEA GSA characters '$GPGSA'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<8000)
	{
		if(serialAvailable(_uart) > 0)
		{
			dummyBuffer[0] = serialRead(_uart);
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5) && (millis()-previous)<2000);
				for (i=1; i<6;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';

				//check if GSV sentence
				// copy "$GPGSV" from flash memory
				char aux[10] ="";
				strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[5])));
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer, aux))
				{
					#ifdef GPS_DEBUG
					PRINT_GPS(F("dummyBuffer: "));
					USB.print(dummyBuffer);
					USB.println(F(" , valid:"));
					#endif
					valid = 1;
				}
			}
		}

		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("no GPS data\n"));
		#endif
		return -2;
	}

	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i = 0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				_dataBuffer[i] = serialRead(_uart);
				if (_dataBuffer[i] == '*' || _dataBuffer[i] == '$')
				{
					// end of NMEA or new one.
					end = 1;
					_dataBuffer[i+1] = '\0';
				}
				i++;
			}
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		// Now parse the read NMEA sentence
		// separate all the subarrays from '_dataBuffer' to 'argument' pointer
		// Define buffer to parse received data
		char _dataBuffer2[GPS_BUFFER_SIZE];
		memset(_dataBuffer2, 0x00, sizeof(_dataBuffer2));
		strncpy(_dataBuffer2, _dataBuffer, strlen(_dataBuffer));
		_dataBuffer2[strlen(_dataBuffer)] = '\0';

		#ifdef GPS_DEBUG
		PRINT_GPS(F("inbuffer2: "));
		USB.println(_dataBuffer2);
		#endif

		// Number of messages not saved
		argument = strtok (_dataBuffer2, ",");

		// Message number not saved
		argument = strtok(NULL, ",");

		// Satellites in view
		argument = strtok(NULL, ",");
		strncpy(satellitesInView, argument, strlen(argument));
		satellitesInView[strlen(argument)] = '\0';

		// Rest of satellite data not saved

		#ifdef GPS_DEBUG
		PRINT_GPS(F("satellites in View: "));
		USB.println(satellitesInView);
		#endif

		return 1;
	}
	else
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("not GSV NEMEA\n"));
		#endif
		// Not GSV NMEA sentence
		valid=0;
		return -1;
	}
}


/* parseGLL() - listen to serial port and parse the NMEA GLL sentence,
 * updating necessary global variables.
 * Example: $GPGLL,3723.2475,N,12158.3416,W,161229.487,A,A*41<CR><LF>
 *
 * note: NMEA sentence not enabled by default
 * return '0' if not connected yet, '-1' if no GLL sentence parsed,
 * '-2' if no gps data, '1' if connected.
 */
int8_t WaspGPS::parseGLL()
{
	#ifdef GPS_DEBUG
	PRINT_GPS(F("parseGLL\n"));
	#endif

	char* argument;
	char dummyBuffer[7] ="";
	uint8_t i = 0;
	bool valid = 0;
	bool end = 0;

	// Look for starting NMEA GLL characters '$GPGLL'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<8000)
	{
		if(serialAvailable(_uart) > 0)
		{
			dummyBuffer[0] = serialRead(_uart);
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5) && (millis()-previous)<2000);
				for (i=1; i<6;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';

				//check if GLL sentence
				// copy "$GPGLL" from flash memory
				char aux[10] ="";
				strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[6])));
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer, aux))
				{
					#ifdef GPS_DEBUG
					PRINT_GPS(F("dummyBuffer: "));
					USB.print(dummyBuffer);
					USB.println(F(" , valid:"));
					#endif
					valid = 1;
				}
			}
		}

		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("no GPS data\n"));
		#endif
		return -2;
	}

	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i = 0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				_dataBuffer[i] = serialRead(_uart);
				if (_dataBuffer[i] == '*' || _dataBuffer[i] == '$')
				{
					// end of NMEA or new one.
					end = 1;
					_dataBuffer[i+1] = '\0';
				}
				i++;
			}
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		// Now parse the read NMEA sentence
		// separate all the subarrays from '_dataBuffer' to 'argument' pointer
		// Example: $GPGLL,3723.2475,N,12158.3416,W,161229.487,A,A*41
		// Define buffer to parse received data
		char _dataBuffer2[GPS_BUFFER_SIZE];
		memset(_dataBuffer2, 0x00, sizeof(_dataBuffer2));
		strncpy(_dataBuffer2, _dataBuffer, strlen(_dataBuffer));
		_dataBuffer2[strlen(_dataBuffer)] = '\0';

		#ifdef GPS_DEBUG
		PRINT_GPS(F("inbuffer2: "));
		USB.println(_dataBuffer2);
		#endif

		// latitude
		argument = strtok(_dataBuffer2, ",");
		strncpy(latitude, argument, strlen(argument));
		latitude[strlen(argument)] = '\0';

		// North/South
		argument = strtok(NULL, ",");
		NS_indicator = argument[0];

		// Longitude
		argument = strtok(NULL, ",");
		strncpy(longitude, argument, strlen(argument));
		longitude[strlen(argument)] = '\0';

		// East / West
		argument = strtok(NULL, ",");
		EW_indicator = argument[0];

		// UTC Time: hhmmss.sss
		argument = strtok(NULL, ",");
		strncpy(timeGPS, argument, strlen(argument));
		timeGPS[strlen(argument)]='\0';

		// Status: A= valid; V= not valid
		argument = strtok(NULL, ",");
		strncpy(state,argument,strlen(argument));
		state[strlen(argument)]='\0';

		// Mode; A= autonomous, D=DGPS, E=DR, N=Data not valid, S=simulator
		argument = strtok(NULL, ",");
		strncpy(RMCMode, argument, strlen(argument));
		RMCMode[1] = '\0';

		#ifdef GPS_DEBUG
			PRINT_GPS(F("latitude: "));
			USB.println(latitude);
			PRINT_GPS(F("NS_indicator: "));
			USB.println(NS_indicator);
			PRINT_GPS(F("longitude: "));
			USB.println(longitude);
			PRINT_GPS(F("EW_indicator: "));
			USB.println(EW_indicator);
			PRINT_GPS(F("time: "));
			USB.println(timeGPS);
			PRINT_GPS(F("status: "));
			USB.println(state);
			PRINT_GPS(F("mode: "));
			USB.println(RMCMode);
		#endif


		return 1;
	}
	else
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("not GLL NEMEA\n"));
		#endif
		// Not GLL NMEA sentence
		valid=0;
		return -1;
	}
}



/* parseVTG() - listen to serial port and parse the NMEA VTG sentence,
 * updating necessary global variables.
 * Example: $GPVTG,309.62,T, ,M,0.13,N,0.2,K,A*23
 * note: NMEA sentence not enabled by default
 * return '0' if not connected yet, '-1' if no VTG sentence parsed,
 * '-2' if no gps data, '1' if connected.
 */
int8_t WaspGPS::parseVTG()
{
	#ifdef GPS_DEBUG
	PRINT_GPS(F("parseVTG\n"));
	#endif

	char* argument;
	char dummyBuffer[7] ="";
	uint8_t i = 0;
	bool valid = 0;
	bool end = 0;

	// Look for starting NMEA VTG characters '$GPVTG'
	unsigned long previous = millis();
	while( (!valid) && (millis()-previous)<8000)
	{
		if(serialAvailable(_uart) > 0)
		{
			dummyBuffer[0] = serialRead(_uart);
			if (dummyBuffer[0] == '$')
			{
				//read five bytes
				while((serialAvailable(_uart)<5) && (millis()-previous)<2000);
				for (i=1; i<6;i++)
				{
					dummyBuffer[i] = serialRead(_uart);
				}
				dummyBuffer[6] = '\0';

				//check if VTG sentence
				// copy "$GPVTG" from flash memory
				char aux[10] ="";
				strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[7])));
				//strcmp returns '0' if both equal
				if(!strcmp(dummyBuffer, aux))
				{
					#ifdef GPS_DEBUG
					PRINT_GPS(F("dummyBuffer: "));
					USB.print(dummyBuffer);
					USB.println(F(" , valid:"));
					#endif
					valid = 1;
				}
			}
		}

		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	//if timeout, no data. break.
	if(dummyBuffer[0] != '$')
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("no GPS data\n"));
		#endif
		return -2;
	}

	//read remaining NMEA data
	if (valid)
	{
		previous = millis();
		i = 0;
		while((!end) && (i < 82) &&  (millis()-previous)<2000)
		{
			// read the GPS sentence
			if(serialAvailable(_uart) > 0)
			{
				_dataBuffer[i] = serialRead(_uart);
				if (_dataBuffer[i] == '*' || _dataBuffer[i] == '$')
				{
					// end of NMEA or new one.
					end = 1;
					_dataBuffer[i+1] = '\0';
				}
				i++;
			}
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		// Now parse the read NMEA sentence
		// separate all the subarrays from '_dataBuffer' to 'argument' pointer
		// Example: $GPVTG,309.62,T, ,M,0.13,N,0.2,K,A*23
		// Define buffer to parse received data
		char _dataBuffer2[GPS_BUFFER_SIZE];
		memset(_dataBuffer2, 0x00, sizeof(_dataBuffer2));
		strncpy(_dataBuffer2, _dataBuffer, strlen(_dataBuffer));
		_dataBuffer2[strlen(_dataBuffer)] = '\0';

		#ifdef GPS_DEBUG
		PRINT_GPS(F("inbuffer2: "));
		USB.println(_dataBuffer2);
		#endif

		// Course deegrees
		argument = strtok(_dataBuffer2,",");
		strncpy(course, argument, strlen(argument));
		course[strlen(argument)] = '\0';

		// Reference, T=true. not saved
		argument = strtok(NULL, ",");

		// Reference. M= magnetic, not supported
		argument = strtok(NULL, ",");

		// Speed, in Knots, not saved.
		argument = strtok(NULL,",");

		// Units: N= Knots, not saved
		argument = strtok(NULL, ",");

		// Speed, in Km/h
		argument = strtok(NULL,",");
		strncpy(speed, argument, strlen(argument));
		speed[strlen(argument)] = '\0';

		// Units: K= Km per hour, not saved
		argument = strtok(NULL, ",");

		// Mode; A= autonomous, D=DGPS, E=DR, N=Data not valid, S=simulator
		argument = strtok(NULL, ",");
		strncpy(RMCMode, argument, strlen(argument));
		RMCMode[1] = '\0';

		#ifdef GPS_DEBUG
			PRINT_GPS(F("Course: "));
			USB.println(course);
			PRINT_GPS(F("Speed: "));
			USB.println(speed);
			PRINT_GPS(F("mode: "));
			USB.println(RMCMode);
		#endif

		return 1;
	}
	else
	{
		#ifdef GPS_DEBUG
		PRINT_GPS(F("not VTG NEMEA\n"));
		#endif
		// Not GLL NMEA sentence
		valid=0;
		return -1;
	}


}




/* Show OSP messages of GPS module during specified time
 * Time must be specified in seconds
 */
void WaspGPS::showOSPRawData(unsigned long time)
{
	uint8_t binMsg[300];
	bool end = false ;
	uint16_t i = 0;
	uint16_t payloadLength = 0;
	uint16_t TempCommMode = 0;

	// clear variable
	memset(binMsg, 0x00, sizeof(binMsg) );

	if (_commMode == NMEA_MODE)
	{
		// Save previous mode
		TempCommMode = NMEA_MODE	;
		// Set OSP mode at 115200
		setCommMode(OSP_MODE);
	}

	//Use microseconds for millis
	time = time * 1000;

	// Now parse response from module.
	unsigned long previous = millis();
	while(  (millis()-previous)<time)
	{
		i = 0;
		if(serialAvailable(_uart) > 0)
		{
			// look for start sequence A0A2
			binMsg[0] = serialRead(1);
			if (binMsg[0] == 0xA0 )
			{
				binMsg[1] = serialRead(1);
				if (binMsg[1] == 0xA2)
				{
					// beginning found, keep reading till the end of frame.
					unsigned long previous2 = millis();
					i = 2;
					while((!end) && (i < 300) && (i<(payloadLength+8)) && (millis()-previous2)<time)
					{
						if(serialAvailable(_uart) > 0)
						{
							binMsg[i] = serialRead(1);

							// look for payload length inside [2] and [3]
							if (i == 2)
							{
								i++;
								binMsg[i] = serialRead(1);

								// FIXME : use both bytes for length. Now only one used.
								payloadLength = binMsg[i];
							}

							// look Mesage ID
							if (i == 4)
							{
								// MID in HEX
								USB.print(F("MID:"));
								USB.printHex(binMsg[4]);
								USB.print(F("\t"));
								// MID in DEC
								USB.print(binMsg[4],DEC);
								USB.print(F("\t"));
								// Length
								USB.print(binMsg[3],DEC);
								USB.print(F("\t"));
							}

							// look for end of message
							if (binMsg[i] == 0xB0 )
							{
								i++;
								binMsg[i] = serialRead(1);
								if (binMsg[i] == 0xB3 )
								{
									end = true;
								}
							}
						i++;
						}
						//avoid millis overflow problem
						if( millis()-previous2 < 0 ) previous2=millis();
					}

					// save MSG or print it.
					 for(uint16_t b = 0; b < i; b++)
					{
						USB.printHex(binMsg[b]);
					}

					// clear variable
					memset(binMsg, 0x00, sizeof(binMsg) );
					end = false;
					USB.println();
				}
			}
		}
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous = millis();
	}

	// Set Comm Mode as previous
	if (TempCommMode == NMEA_MODE)
	{
		setCommMode(NMEA_MODE);
	}
}


/* Show NMEA messages of GPS module during specified time
 *
 */
void WaspGPS::showNMEARawData(unsigned long time)
{
	uint16_t tempCommMode = 0;
	uint16_t i = 0;
	bool end = 0;

	// clear variable
	memset(_dataBuffer, 0x00, sizeof(_dataBuffer) );

	if (_commMode == OSP_MODE)
	{
		// Save previous mode
		tempCommMode = OSP_MODE	;
		// Set NMEA mode at 4800
		setCommMode(NMEA_MODE);
	}

	//Use microseconds for millis
	time = time * 1000;

	// Look for starting NMEA characters
	unsigned long previous = millis();
	while( (!end) && (millis()-previous)<time)
	{
		if(serialAvailable(_uart) > 0)
		{
			_dataBuffer[0] = serialRead(_uart);
			if (_dataBuffer[0] == '$')
			{
				// read remaining sentence
				unsigned long previous2 = millis();
				i = 1;
				while((!end) && (i<GPS_BUFFER_SIZE) &&(millis()-previous2)<time)
				{
					// read the GPS sentence
					if(serialAvailable(_uart) > 0)
					{
						_dataBuffer[i] = serialRead(_uart);
						if (_dataBuffer[i] == '*' || _dataBuffer[i] == '$')
						{
							// end of NMEA or new one.
							end = 1;
						}
						i++;
					}
					//avoid millis overflow problem
					if( millis() < previous2 ) previous2=millis();
				}

				//print data
				// save MSG or print it.
				USB.println(_dataBuffer);

				// clear variable
				memset(_dataBuffer, 0x00, sizeof(_dataBuffer) );
				end = false;
			}
		}

		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	// Set Comm Mode as previous
	if (tempCommMode == OSP_MODE)
	{
		setCommMode(OSP_MODE);
	}
}

/* Set OSP data rate to 0 using MID166 message
 *
 *
 */
void WaspGPS::disableOSPMsg()
{
	/* defines the sequence which controls the output rate of
	 * binary messages. In this frame, "enable/disable all messages" mode is
	 * selected.
	 * The sequence consists of:
	 * 	A0A20008 - Start Sequence and Payload Length
	 * 	A602020000000000 - Payload
	 * 	00AAB0B3 - Message Checksum and End Sequence
	 */
	uint8_t outBuff[16] =
	{0xA0,0xA2,0x00,0x08,0xA6,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0xAA,0xB0,
	0xB3};

	sendCommand(outBuff,16);
}

/* send command
 * Introduce the whole command to send. the checksum will be calculated inside
 * Example: sendCommand("$PSRF100,0,115200,8,1,0*00");
 * Sends:            	 $PSRF100,0,115200,8,1,0*04\r\n
 */
void WaspGPS::sendCommand(char * NMEAcommand)
{
	// clear global variable
	memset(_dataBuffer, 0x00, sizeof(_dataBuffer) );

	// copy "%s\r\n" from flash memory
	char aux[10] ="";
    strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[8])));
	//Set checksum on command and ads CR+LF
	snprintf(_dataBuffer, sizeof(_dataBuffer), aux, setChecksum(NMEAcommand));

	#ifdef GPS_DEBUG
	PRINT_GPS(F("Command:\t"));
	USB.print(_dataBuffer);
	#endif

	// Send it
	serialFlush(_uart);
    printString(_dataBuffer,_uart);
    delay(100);
}


/* Introduce the whole command to send. the checksum will be calculated inside
 * Binary message structure.
 *   Start Sequence  |  Payload Length  |       PAYLOAD                   |  Checksum  |  End Sequence
 *     0xA0, 0xA2    |      2 Bytes     | (15 bits) Up to (211 – 1) Bytes |  0xXX 0xXX |   0xB0, 0xB3
 * Example: introducing A0 A2 00 03 93 00 00 00 00 B0 B3
 * Will send:           A0 A2 00 03 93 00 00 00 93 B0 B3
*/
void WaspGPS::sendCommand(uint8_t * command, uint16_t commandLength)
{
	// saves the checksum in global checkSUM.
	getChecksum(command);

	// Add checksum to the command
	command[commandLength-4] = _checkSUM[0];
	command[commandLength-3] = _checkSUM[1];

	#ifdef GPS_DEBUG
	PRINT_GPS(F("Command:"));
	USB.print(F("\t"));
	for(uint16_t a = 0; a < commandLength; a++)
	{
		USB.printHex(command[a]);
	}
	USB.println(F(""));
	#endif

	serialFlush(1);
    for(uint16_t b = 0; b < commandLength; b++)
    {
      printByte(command[b], 1);
    }
}


/******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

/******************************************************************************
 * Constructors
 ******************************************************************************/

WaspGPS::WaspGPS()
{
	// by default we choose NMEA's speed for the port
	_baudRate = 4800;

	// UART1 is the microcontrolelr used for the GPS
	_uart=1;

	// basic GPS configuration
	flag = 0;
	_commMode = NMEA_MODE;
	_pwrMode = GPS_ON;
	_checksum=0;

	////////////////////////////////////////////////////////////////////////
	// Initialization parameters for Zaragoza. Change location when needed.
	// Edit when necessary with your location data.
	////////////////////////////////////////////////////////////////////////
	clkOffset = (char*) "96000";
	timeOfWeek = (char*) "470000";
	weekNo = (char*) "1711";
	channel = (char*) "12";
	resetCfg = (char*) "1";
	coordinateLat = (char*) "41.680617";
	coordinateLon = (char*) "-0.886233";
	coordinateAl = (char*) "222";

}


/* ON(void) - opens UART1 and powers the GPS module
 *
 * It opens UART1 and powers the GPS module
 *
 * Returns 0 if not init OK, 1 if init OK
*/
uint8_t WaspGPS::ON()
{
	// power the GPS module
	setMode(GPS_ON);

	// set UART's MUX and open UART
	begin();

	// initialize the GPS on default parameters
	return init();

}

/* OFF(void) - closes UART1 and powers off the GPRS module
 *
 * This function closes UART1 and powers off the GPRS module
 *
 * Returns nothing
*/
void WaspGPS::OFF()
{
	// close uart and disable UART1 multiplexer output
	close();

	// switch GPS off
	setMode(GPS_OFF);
}


/*
 * setMode (void) - sets the current internal Power Mode on the GPS
 *
 * GPS has two different power modes: ON, OFF.
 *
 */
void WaspGPS::setMode(uint8_t mode)
{
	_pwrMode = mode;
	pinMode(GPS_PW,OUTPUT);

	// set the GPS in the defined power mode
	switch (_pwrMode)
	{
		case GPS_ON:	digitalWrite(GPS_PW,HIGH);
						break;

		case GPS_OFF:	digitalWrite(GPS_PW,LOW);
						break;
	}
}

/*
 * getMode (void) - answers the current internal Power Mode on the GPS
 *
 */
uint8_t WaspGPS::getMode(void)
{
	return _pwrMode;
}


/* getCommMode() - get the communication mode
 *
 * It gets the communication mode in use.
 */
uint8_t WaspGPS::getCommMode(void)
{
  return _commMode;
}


/* check() - get if receiver is connected to some satellite
 *
 * It gets if receiver is connected to some satellite
 *
 * It returns '1' if connected, '0' if not
 */
uint8_t WaspGPS::check()
{
	// set UART1's multiplexer to GPS socket
	Utils.setMuxGPS();
	serialFlush(_uart);
	signalStatus=0;

	#ifdef GPS_DEBUG
	PRINT_GPS(F("check\n"));
	#endif

	unsigned long previous = millis();
	// Wait here till timeout or status=connected
	while((!signalStatus) && (millis()-previous)<5000)
	{
		// Updates global status
		signalStatus = parseRMC();

		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	if (signalStatus == 1) return 1;
	else return 0;
}


/* waitForSignal() - check if receiver is connected to some satellite until time out
 *
 * It checks continuously if receiver is connected to some satellite until time out.
 * The time out is 1 minute and is defined in GPS_SIGNAL_TIMEOUT
 *
 * It returns '1' if connected, '0' if not
 */
bool WaspGPS::waitForSignal()
{
	// call function with default timeout
	return waitForSignal(GPS_SIGNAL_TIMEOUT);
}

/* waitForSignal(timeout) - check if receiver is connected to some satellite
 * until time out
 *
 * It checks continuously if receiver is connected to some satellite until time out.
 * The timeout is set as an input parameter defined in seconds
 *
 * It returns '1' if connected, '0' if not
 */
bool WaspGPS::waitForSignal(unsigned long timeout)
{
	unsigned long initTime = millis();
	unsigned long time = 0;
	bool status = 0;

	while(!status && (time < timeout*1000))
	{
		status = check();
		delay(100);
		time = millis() - initTime;

		//avoid millis overflow problem
		if( millis() < initTime ) initTime=millis();
	}

	#ifdef GPS_DEBUG
	PRINT_GPS(F("status_waitforsignal = "));
	USB.println(status);
	#endif

	return status;
}

/*
 * getTime (void) - answers the current time on the GPS
 *
 * gets the time from the GPS and returns it in the format
 * "175600.0000" - hhmmss.mmmm
 *
 * return time if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getTime(void)
{
	unsigned long previous = millis();
	flag = 0;

	// check if GPS signal
	if (signalStatus == 1)
	{
		//update time variable
		while((flag != 1) && (millis()-previous)<5000)
		{
			flag = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return timeGPS;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}

/*
 * getDate (void) - answers the current date on the GPS
 *
 * gets the date from the GPS and returns it in the format "180509" - ddmmyy
 *
 * return date if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getDate(void)
{
	unsigned long previous = millis();
	flag = 0;

	// check if GPS signal
	if (signalStatus == 1)
	{
		//update date variable
		while((flag != 1) && (millis()-previous)<5000)
		{

			flag = parseRMC();
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return dateGPS;
		}
	}
	else
	{
		return 0;
	}
}

/*
 * getLatitude (void) - gets the latitude from the GPS
 *
 * forces getLocation and responds the current value of the latitude
 * variable as a string
 *
 * return latitude if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getLatitude(void)
{
	unsigned long previous = millis();
	flag = 0;

	// check if GPS signal
	if (signalStatus == 1)
	{
		//update latitude variable
		while((flag != 1) && (millis()-previous)<5000)
		{

			flag = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return latitude;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}

/*
 * convert2Degrees ( input , indicator ) - performs the conversion from input
 * parameters in  DD°MM.mmm’ notation to DD.dddddd° notation.
 *
 * Sign '+' is set for positive latitudes/longitudes (North, East)
 * Sign '-' is set for negative latitudes/longitudes (South, West)
 *
 * parameter: 'input' is a string indicating the latitude/longitude in
 * DDDmm.mmmm' notation for latitude and DDDmm.mmmm' notation for longitude
 * parameter: 'indicator' is a char indicating 'N' for North, 'S' for South, 'E'
 * for East and 'W' for West
 * Returns: a float indicating the latitude in DD.dddddd° notation
 *
 */
float WaspGPS::convert2Degrees(char* input, char indicator)
{
	// final latitude expresed in degrees
	float degrees;
	float minutes;

	//auxiliar variable
	char aux[10] ="";

	// check if 'indicator' is a valid input
	if ( indicator != 'N' && indicator != 'S' && indicator != 'E' && indicator != 'W' )
	{
		// invalid indicator
		return 0;
	}

	// get 'degrees' from input parameter
	if ( indicator=='N' || indicator=='S' )
	{
		//latitude format: DDmm.mmmm'
		aux[0] = input[0];
		aux[1] = input[1];
		aux[2] = '\0';
	}
	else if( indicator == 'E' || indicator == 'W')
	{
		//longitude format: DDDmm.mmmm'
		aux[0]=input[0];
		aux[1]=input[1];
		aux[2]=input[2];
		aux[3]='\0';
	}

	// convert string to integer and add it to final float variable
	degrees = atoi(aux);

	// get 'minutes' from input parameter
	if ( indicator == 'N' || indicator == 'S' )
	{
		//latitude format: DDmm.mmmm'
		for ( int i=0; i<7; i++ )
		{
			aux[i] = input[i+2];
		}
		aux[7] = '\0';
	}
	else if( indicator == 'E' || indicator == 'W')
	{
		//latitude format: DDmm.mmmm'
		for ( int i = 0; i < 7; i++ )
		{
			aux[i] = input[i+3];
		}
		aux[7] = '\0';
	}

	// convert string to integer and add it to final float variable
	minutes = atof(aux);

	// add minutes to degrees
	degrees = degrees+minutes/60;

	// add sign: '+' for North/East; '-' for South/West
	if( indicator == 'S' || indicator == 'W')
	{
		degrees *= -1.0;
	}

	return degrees;
}

/*
 * getLongitude (void) - gets the longitude the GPS
 *
 * forces getLocation and responds the current value of the longitude
 * variable as a string
 *
 * return longitude if ok, 0 if timeout or no gps signal.
 */
  //
char* WaspGPS::getLongitude(void)
{
	unsigned long previous = millis();
	flag = 0;

	// check if GPS signal
	if (signalStatus == 1)
	{
		//update longitude variable
		while((flag != 1) && (millis()-previous)<5000)
		{

			flag = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return longitude;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}

/*
 * getSpeed (void) - gets the speed from the GPS
 *
 *
 * Stores the final value in the variable speed as string.
 *
 * Returns the speed in Km/h if ok, 0 if timeout or no gps signal.
 *
 */
char* WaspGPS::getSpeed(void)
{
	unsigned long previous = millis();
	flag = 0;

	// check if GPS signal
	if (signalStatus == 1)
	{
		//update speed variable
		while((flag != 1) && (millis()-previous)<5000)
		{
			flag = parseRMC();
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return speed;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}

/*
 * getAltitude (void) - gets the altitude from the GPS
 *
 * forces getLocation and responds the current value of the altitude
 * variable (in meters) as a string
 *
 * return altitude if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getAltitude(void)
{
	unsigned long previous = millis();
	flag = 0;

	// check if GPS signal
	if (signalStatus == 1)
	{
		//update altitude variable
		while((flag != 1) && (millis()-previous)<5000)
		{
			flag = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return altitude;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}

/*
 * getCourse (void) - gets the course from the GPS
 *
 * makes a call to the GPRMC sentence type to extract the data from the GPS, it
 * separates the data using the '_dataBuffer' and 'strtok' function
 *
 * Stores the final value in the variable course as string.
 *
 * return course if ok, 0 if timeout or no gps signal.
 */
char* WaspGPS::getCourse(void)
{
	unsigned long previous = millis();
	flag = 0;

	// check if GPS signal
	if (signalStatus == 1)
	{
		//update course variable
		while((flag != 1) && (millis()-previous)<5000)
		{
			flag = parseRMC();
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		//if timeout, date not updated.
		if (flag != 1)
		{
			return 0;
		}
		else
		{
			return course;
		}
	}
	else
	{
		// No gps signal
		return 0;
	}
}

/* getPosition() - gets the latitude, longitude, altitude, speed, course, time
 * and date
 *
 * It gets the latitude, longitude, altitude, speed, course, time and date
 *
 * It returns '1' on success and '0' on error.
 */
int8_t WaspGPS::getPosition()
{
	unsigned long previous = millis();
	flag = 0;
	int8_t flag2 = 0;

	// check if GPS signal
	if (signalStatus == 1)
	{
		// update date, time, speed, latitude, longitude and course variables
		while((flag != 1) && (millis()-previous)<5000)
		{
			flag = parseRMC();
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		// update altitude variable
		previous = millis();
		while((flag2 != 1) && (millis()-previous)<5000)
		{

			flag2 = parseGGA();
			//avoid millis overflow problem
			if( millis() < previous ) previous = millis();
		}

		//if timeout, date not updated.
		if ((flag != 1) || (flag2 != 1))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		// No gps signal
		return -1;
	}
}




/* setTimeFromGPS() - sets time and date from the GPS to the RTC.
 * GPS has to be initialized first and got the time/date
 *
 * It sets time and date from the GPS to the RTC.
 * GPS has to be initialized first and got the time/date
 *
 * It returns nothing
 */
void WaspGPS::setTimeFromGPS()
{
	RTC.ON();
	getDate();
	getTime();
	int day, month, year, hour, minute, second = 0;
  	day		= (dateGPS[0]-'0')*10 + (dateGPS[1]-'0');
  	month 	= (dateGPS[2]-'0')*10 + (dateGPS[3]-'0');
  	year 	= (dateGPS[4]-'0')*10 + (dateGPS[5]-'0');
  	hour 	= (timeGPS[0]-'0')*10 + (timeGPS[1]-'0');
  	minute	= (timeGPS[2]-'0')*10 + (timeGPS[3]-'0');
  	second	= (timeGPS[4]-'0')*10 + (timeGPS[5]-'0');
  	RTC.setTime(year, month, day, RTC.dow(year, month, day), hour, minute, second);
}



/* saveEphems() - save ephemeris into SD
 *
 * It saves ephemeris into SD. It creates a file named 'FILE_EPHEMERIS' and
 * stores ephemeris into it.
 *
 * It returns
 * 	'1' on succesful.
 * 	'0' when error on writing
 *  '-1' when there is no SD card
 * 	'-2' when error creating file
 *  '-3' when no ephemerides are returned by GPS receiver,
 */
int8_t WaspGPS::saveEphems()
{
	return saveEphems(FILE_EPHEMERIS);
}

/* saveEphems(filename) - save ephemeris into SD
 *
 * It saves ephemeris into SD. It creates a file named 'filename' and stores
 * ephemeris into it.
 *
  returns
  * -3 no ephem data from module
  * -2 error creating file
  * -1 no SD
  * 0 error writting into file
  * 1 sucess
 */
int8_t WaspGPS::saveEphems(const char* filename)
{
	uint8_t end = 0;
	int8_t error = -3;
	uint16_t i = 0;
	uint16_t payloadLength = 0;
	uint8_t inBuff[GPS_BUFFER_SIZE];
	memset(inBuff, 0x00, sizeof(inBuff));

	// tempBuffer creates the 'Poll Ephemeris' message, ID147
	// By default polls all available ephems (of the 32 possible satellites)
	uint8_t outBuff[11] ={0xA0,0xA2,0x00,0x03,0x93,0x00,0x00,0x00,0x93,0xB0,0xB3};

	// end of file sequence
	uint8_t endFile[7] ={0xAA,0xBB,0xCC,0xCC,0xBB,0xAA,0xAA};

	// First of all, prepare SD card.
	SD.ON();

	// check if the card is there or not
	if (!SD.isSD())
	{
		#ifdef DEBUG_MODE
		PRINT_GPS(F("no SD\n"));
		#endif
		return -1;
	}

	// if file exists -> delete it
	if (SD.isFile(filename)) SD.del(filename);

	// create ephemeris file
	if(!SD.create(filename))
	{
		#ifdef DEBUG_MODE
		PRINT_GPS(F("err SD1\n"));
		#endif
		return -2;
	}

	// Now change to Binary OSP mode
	setCommMode(OSP_MODE);

	// Stop other OSP messages
	delay(100);

	// Send the Poll ephems message.
	sendCommand(outBuff, 11);

	// Now parse response from module.
	// Look for MID 15 messages containing satellite ephems

	// Now parse response from module.
	unsigned long previous = millis();
	while(  (millis()-previous)<3000)
	{
		i = 0;
		if(serialAvailable(_uart) > 1)
		{
			// look for start sequence A0A2
			inBuff[0] = serialRead(1);
			if (inBuff[0] == 0xA0 )
			{
				inBuff[1] = serialRead(1);
				if (inBuff[1] == 0xA2)
				{
					// beginning found, keep reading till the end of frame.
					unsigned long previous2 = millis();
					i= 2;
					while((end == 0) && (i < 300) && (i < (payloadLength + 8)) && (millis() - previous2) < 2000)
					{
						if(serialAvailable(_uart) > 0)
						{
							inBuff[i] = serialRead(1);

							// look for payload length inside [2] and [3]
							if (i == 2)
							{
								i++;
								inBuff[i] = serialRead(1);

								// FIXME : use both bytes for length. Now only one used.
								payloadLength = inBuff[i];
							}

							// look Mesage ID
							if ((i == 4) && (inBuff[i] != 0x0F))
							{
								// not a poll ephem Msg, discard.
								end = 2;
							}

							// look for end of message
							if (inBuff[i] == 0xB0 )
							{
								i++;
								inBuff[i] = serialRead(1);
								if (inBuff[i] == 0xB3 )
								{
									end = 1;
								}
							}
						i++;
						}
						//avoid millis overflow problem
						if( millis()-previous2 < 0 ) previous2=millis();
					}

					// only save MID15 complete (100 bytes) msg
					if ((end == 1) && (i > 98))
					{
						// save it on SD
						if(SD.append(filename,inBuff,i))
						{
							error=1;
							#ifdef DEBUG_MODE
							PRINT_GPS(F("writte ok\n"));
							#endif
							//SD.appendln(filename,"");
						}
						else
						{
							error=0;
							#ifdef DEBUG_MODE
							PRINT_GPS(F("writte error\n"));
							#endif
						}

						// clear variable
						memset(inBuff, 0x00, sizeof(inBuff) );
						end = false;
						USB.println();
					}
					else
					{
						end = false;
					}
				}
			}
		}
		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous = millis();
	}

	//add end sequence to file once ephems data is saved.
	SD.append(filename, endFile, 7);

	// Turn OFF SD card
	SD.OFF();

	// Now change to NMEA mode
	setCommMode(NMEA_MODE);

	return error;
}

/* Load Ephemerids data stored in the default file on SD card.
 * return 0 if error reading file, -1 if no SD, -2 if no file.
 */
int8_t WaspGPS::loadEphems()
{
	return loadEphems(FILE_EPHEMERIS);
}

/* Load Ephemerids data stored in the SD card.
 * return 0 if error reading file, -1 if no SD, -2 if no file.
 */
int8_t WaspGPS::loadEphems(const char* filename)
{
	uint16_t offset = 0;
	uint8_t outBuff[99];
	uint8_t end = 0;

	// Clear variable
	memset(outBuff, 0x00, sizeof(outBuff));

	// Start sequence
	outBuff[0] = 0xA0;
	outBuff[1] = 0xA2;
	// length
	outBuff[2] = 0x00;
	outBuff[3] = 0x5B;
	// MID
	outBuff[4] = 0x95;
	outBuff[5] = 0x00;

	// Now change to Binary OSP mode
	setCommMode(OSP_MODE);


	bool sd_on = (WaspRegister & REG_SD);
	if (!sd_on)
	{
		SD.ON();
	}

	// check if the card is there or not
	if (!SD.isSD())
	{
		if (!sd_on)
		{
			SD.OFF();
		}
		return -1;
	}

	// check if file exists
	if (SD.isFile(filename) != 1)
	{
		if (!sd_on)
		{
			SD.OFF();
		}
		// file does not exist
		return -2;
	}

	// Look on SD file for Ephemerids data and send it to the module
	unsigned long previous = millis();
	while ((!end) && (millis() - previous < 10000) )
	{
		SD.catBin(filename,offset,1);

		// check if there is SD error
		if (SD.flag != 0)
		{
			if (!sd_on)
			{
				SD.OFF();
			}
			return 0;
		}
		if (SD.bufferBin[0] == 0xA0)
		{
			offset++;
			SD.catBin(filename, offset, 1);

			// check if there is SD error
			if (SD.flag != 0)
			{
				if (!sd_on)
				{
					SD.OFF();
				}
				return 0;
			}
			if (SD.bufferBin[0] == 0xA2)
			{
				offset++;
				// read remaining frame 98 bytes
				SD.catBin(filename,offset,98);

				// check if there is SD error
				if(SD.flag != 0)
				{
					if (!sd_on)
					{
						SD.OFF();
					}
					return 0;
				}

				offset = offset + 98;

				// only interested in 89 bytes, leave out length, MIDs, checksum and end.
				for(uint16_t a = 0; a < 89; a++)
				{
					// prepare set ephems command
					outBuff[a+6] = SD.bufferBin[a+5];
				}

				// add end sequence
				outBuff[97] = 0xB0;
				outBuff[98] = 0xB3;

				// send it (checksum calculated inside)
				sendCommand(outBuff, 99);

				// try this delay.
				delay(300);

				//response?
				//look for ACK?
			}
		}
		else
		{
			offset++;
		}

		// look for End of archive characters "AABBCCCCBBAAAA"
		SD.catBin(filename,offset,5);

		// check if there is SD error
		if(SD.flag != 0)
		{
			if (!sd_on)
			{
				SD.OFF();
			}
			return 0;
		}

		// if end of file exit while loop
		if( (SD.bufferBin[0] == 0xAA) &&
			(SD.bufferBin[1] == 0xBB) &&
			(SD.bufferBin[2] == 0xCC) &&
			(SD.bufferBin[3] == 0xCC) &&
			(SD.bufferBin[4] == 0xBB) 	)
		{
			#ifdef GPS_DEBUG
				PRINT_GPS(F("endfile\n"));
			#endif

			end = 1;
		}

		//avoid millis overflow problem
		if( millis()-previous < 0 ) previous = millis();
	}

	// turn OFF SD card
	if (!sd_on)
	{
		SD.OFF();
	}

	// Now change to NMEA mode
	setCommMode(NMEA_MODE);

	return 1;
}

/* showRawFata(mode, time) shows the data directly send by the GPS module,
 * during the specified time in seconds.
 * NMEA sentences are shown in NMEA mode
 * OSP messages are shown in OSP mode.
 *
 */
void WaspGPS::showRawData(uint8_t mode, unsigned long time)
{
	if (mode == OSP_MODE)
	{
		showOSPRawData(time);
	}
	else
	{
		showNMEARawData(time);
	}
}

/* Gets firmware version of the GPS modlue.
 */
char * WaspGPS::getFirmwareVersion()
{
	bool responseFound = 0;
	uint16_t i = 0;
	char dummyBuffer[10] ="";

	memset(_dataBuffer, 0x00, sizeof(_dataBuffer) );

	//go to NMEA mode
	setCommMode(NMEA_MODE);

	// copy $PSRF125*00 from flash memory
	char aux[20] ="";
	strcpy_P(aux, (char*)pgm_read_word(&(table_GPS[9])));

	// Look for firmware version
	unsigned long previous = millis();
	while(!responseFound  && (millis() - previous < 5000))
	{

		// Command to get firmware version $PSRF125*21
		sendCommand(aux);

		// Response $PSRF195,GSD4e_4.1.2-P5 F+ 01/08/2013
		// or $PSRF195,GSD4e_4.1.2-P1 R+ 11/15/2011
		unsigned long previous2 = millis();
		while((!responseFound) && (millis() - previous2 < 1000))
		{
			// Wait till response arrives
			if(serialAvailable(_uart) > 40)
			{
				_dataBuffer[0] = serialRead(_uart);
				if (_dataBuffer[0] == '$')
				{
					//read the sentente
					i = 1;
					while ((_dataBuffer[i] != '*') && (i<39))
					{
						_dataBuffer[i] = serialRead(_uart);
						i++;
					}

					// copy "$PSRF195" from flash memory
					char aux2[20] ="";
					strcpy_P(aux2, (char*)pgm_read_word(&(table_GPS[10])));

					// search PSRF195
					for(int b = 0; b < 8; b++) dummyBuffer[b] = _dataBuffer[b];
					if(strcmp(dummyBuffer,aux2) == 0)
					{
						responseFound = true;
					}
				}
			}
			//avoid millis overflow problem
			if( millis() < previous2 ) previous2 = millis();
		}

		//avoid millis overflow problem
		if( millis() < previous ) previous = millis();
	}

	if (responseFound)
	{
		return _dataBuffer;
	}
	else
	{
		return 0;
	}
}

// Binary message structure.
//   Start Sequence  |  Payload Length  |       PAYLOAD                   |  Checksum  |  End Sequence
//     0xA0, 0xA2    |      2 Bytes     | (15 bits) Up to (211 – 1) Bytes |   2 Bytes  |   0xB0, 0xB3

/// Preinstantiate Objects /////////////////////////////////////////////////////
WaspGPS GPS = WaspGPS();
