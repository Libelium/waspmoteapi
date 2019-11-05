/*!
 * @file 	WaspSigfox.cpp
 * @author	Libelium Comunicaciones Distribuidas S.L.
 * @version	3.4
 * @brief 	Library for managing Sigfox modules TD1207 & TD1508
 *
 *  Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

#include "WaspSigfox.h"

// MACROS
#define NARGS_SEQ(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,N,...) N
#define NARGS(...) NARGS_SEQ(__VA_ARGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define GEN_ATCOMMAND_SET(...) generator(1, NARGS(__VA_ARGS__) - 1, __VA_ARGS__)
#define GEN_ATCOMMAND_READ(...) generator(2, NARGS(__VA_ARGS__) - 1, __VA_ARGS__)
#define GEN_ATCOMMAND_DISPLAY(...) generator(3, NARGS(__VA_ARGS__) - 1, __VA_ARGS__)


// PRIVATE METHODS /////////////////////////////////////////////////////////////


/*!
 * @brief	This function generates AT commands for the module
 * @param	uint8_t type: type of command to be created.
 * @param	int n: number of arguments introduced as input
 * @param	const char *cmdCode: AT command name
 * @return	void
 */
void WaspSigfox::generator(uint8_t type, int n, const char *cmdCode, ...)
{
	// define pointer
	char* pointer;

	// clear buffer
	memset( _command, 0x00, sizeof(_command) );


    // if number of arguments is greater than zero
	// then add the corresponding delimiter
	if( n > 0 )
	{
		// Add delimiter type
		switch( type )
		{
			case SIGFOX_CMD_SET:
					// add "AT$"
					strncat(_command, SIGFOX_AT_HEADER, strlen(SIGFOX_AT_HEADER) );

					// add command code
					strncat(_command, cmdCode, strlen(cmdCode) );

					strncat(_command, "=",  1 );
					break;

			case SIGFOX_CMD_DISPLAY:

					// add "AT/"
					strncat(_command, SIGFOX_AT_HEADER_SLASH, strlen(SIGFOX_AT_HEADER_SLASH) );

					// add command code
					strncat(_command, cmdCode, strlen(cmdCode) );

					break;

			default:
					#if DEBUG_SIGFOX > 0
						PRINT_SIGFOX(F("error type\n"));
					#endif
				return (void)0;
		}
	}
	else if( n == 0 )
	{
		// Add delimiter type
		switch( type )
		{
			case SIGFOX_CMD_SET:
							// add "AT$"
							strncat(_command, SIGFOX_AT_HEADER, strlen(SIGFOX_AT_HEADER) );

							// add command code
							strncat(_command, cmdCode, strlen(cmdCode) );

							break;

			case SIGFOX_CMD_READ:
							// add "AT$"
							strncat(_command, SIGFOX_AT_HEADER, strlen(SIGFOX_AT_HEADER) );

							// add command code
							strncat(_command, cmdCode, strlen(cmdCode) );

							// Ask for command
							strncat(_command, "?",  1 );

							break;

			case SIGFOX_CMD_DISPLAY:

							// add "AT/"
							strncat(_command, SIGFOX_AT_HEADER_SLASH, strlen(SIGFOX_AT_HEADER_SLASH) );

							// add command code
							strncat(_command, cmdCode, strlen(cmdCode) );

							break;
			default: 		break;
		}
	}

	// if it is a set command type add argument in list adding ',' in between
    if (type == SIGFOX_CMD_SET)
    {
		// initialize variable argument list
		va_list  args;
		va_start(args, cmdCode);

		// iterate through all arguments to add to the buffer
		for (int i = 0; i < n; i++)
		{
			// get the new argument
			pointer = va_arg( args, char* );

			// continue if the argument is NULL
			if( pointer==NULL )
			{
				continue;
			}

			// add ',' except for the first argument
			if( i!=0 )
			{
				strncat(_command, ",", 1 );
			}

			// calculate size after adding the new argument to check if
			// the new arguments fits inside the buffer or not
			size_t next_size = strlen(pointer) + strlen( _command ) + strlen("\r");

			if( next_size < sizeof( _command)-1 )
			{
				// add the new argument to buffer
				strncat( _command, pointer, strlen(pointer));
			}
			else
			{
				//error
				#if DEBUG_SIGFOX > 0
					PRINT_SIGFOX(F("not enough buffer size\n"));
				#endif
				memset( _command, 0x00, sizeof(_command) );
				return (void)0;
			}
		}

		// end using variable argument list
		va_end(args);
	}
	else
	{

	}

	// add CR at the end of the command
    strncat(_command, "\r", strlen("\r") );

    // show command
    #if DEBUG_SIGFOX > 1
		PRINT_SIGFOX(F("_command: "));
		USB.println( _command );
	#endif
}




/*!
 * @brief	This function parses an hexadecimal value
 * @return	parsed value
 */
uint32_t WaspSigfox::parseHexValue()
{
	char * pch;
	pch = strtok((char*) _buffer,"\r\n");
	pch = strtok(NULL, "\r\n");
	if (pch != NULL)
	{
		return strtoul(pch, NULL, 16);
	}
	return 0;
}





/*!
 * @brief	This function parses a uint8_t value
 * @return	parsed value
 */
uint8_t WaspSigfox::parseUint8Value()
{
	char * pch;
	pch = strtok((char*) _buffer,"\r\nOKERROR");
	if (pch != NULL)
	{
		return strtoul(pch, NULL, 10);
	}
	return 0;
}




/*!
 * @brief	This function parses a uint32_t value
 * @return	parsed value
 */
uint32_t WaspSigfox::parseUint32Value()
{
	char * pch;
	pch = strtok((char*) _buffer,"\r\nOKERROR");
	if (pch != NULL)
	{
		return strtoul(pch, NULL, 10);
	}
	return 0;
}




// PUBLIC METHODS //////////////////////////////////////////////////////////////


/*!
 * @brief	This function powers on the module
 * @param 	uint8_t	socket: socket to be used: SOCKET0 or SOCKET1
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::ON(uint8_t socket)
{
	_baudrate = SIGFOX_RATE;
	_uart = socket;

	// select multiplexer
    if (_uart == SOCKET0) 	Utils.setMuxSocket0();
    if (_uart == SOCKET1) 	Utils.setMuxSocket1();

	// Open UART
	beginUART();

    // power on the socket
    PWR.powerSocket(_uart, HIGH);

	delay(5000);

	// Check communication
	uint8_t answer = check();

	return answer;
}



/*!
 * @brief	This function powers down the module
 * @param 	uint8_t	socket: socket to be used: SOCKET0 or SOCKET1
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::OFF(uint8_t socket)
{
	// close uart
	closeUART();

	// unselect multiplexer
    if (_uart == SOCKET0)	Utils.setMuxUSB();
    if (_uart == SOCKET1)	Utils.muxOFF1();

    // switch module OFF
	PWR.powerSocket(_uart, LOW);

	return SIGFOX_ANSWER_OK;
}



/*!
 * @brief	Checks if TD1207 module is ready
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::check()
{
	uint8_t status;

	// send command
	status = sendCommand("AT\r", SIGFOX_AT_OK, SIGFOX_AT_ERROR, 5000 );

	if( status == 1 )
	{
		// ok -> get module region
		getRegion();
		return SIGFOX_ANSWER_OK;
	}
	else if(status == 2)
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else
	{
		// timeout
		return SIGFOX_NO_ANSWER;
	}
}





/*!
 * @brief	This function is used to read the module's id
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::getID()
{
	uint8_t answer;

	// 1. send command
	answer = sendCommand("ATI7\r", SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	// check possible error answers
	if (answer == 0)
	{
		// timeout
		return SIGFOX_NO_ANSWER;
	}
	else if(answer == 2)
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else if (answer == 1)
	{
		_id = parseHexValue();
		return SIGFOX_ANSWER_OK;
	}
}




/*!
 * @brief	This function is used to configure the Sigfox RF power level in dBm
 * @param	uint8_t power: power level to be set in dBm
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::setPower(uint8_t power)
{
	uint8_t answer;

	snprintf(_command, sizeof(_command), "ATS302=%u\r", power);

	// 1. send command
	answer = sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	// check possible error answers
	if(answer == 2)
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else if (answer == 0)
	{
		// timeout
		return SIGFOX_NO_ANSWER;
	}

	// 2. save config
	answer = saveSettings();

	return answer;
}



/*!
 * @brief	This function is used to read the configuration of the module's RF
 * 			power level in dBm
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::getPower()
{
	uint8_t answer;

	snprintf(_command, sizeof(_command), "ATS302?\r");

	// enter command mode
	if( sendCommand(_command, SIGFOX_AT_EOL, SIGFOX_AT_ERROR, 1000) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	answer = waitFor(SIGFOX_AT_EOL, 1000);

	// enter command mode
	if( answer != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	// get value from received data
	_power = parseUint8Value();


	return SIGFOX_ANSWER_OK;
}


/*!
 * @brief	This function stores the current settings in module's memory
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::saveSettings()
{
	// enter command mode
	if( sendCommand("AT&W\r", SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	return SIGFOX_ANSWER_OK;
}



/*!
 * @brief	set factory configuration
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::factorySettings()
{
	uint8_t status;

	status = sendCommand("AT&F\r", SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);
	if( status == 1 )
	{
		//save config
		status = saveSettings();
		return status;
	}
	else if( status == 2 )
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}
}



/*!
 * @brief	set default configuration previously stored in module's memory
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::defaultConfiguration()
{
	uint8_t answer;

	answer = sendCommand("ATZ\r", SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);
	if (answer == 1)
	{
		delay(2000);

		// Check communication
		answer = check();

		return answer;
	}
	else if (answer == 2)
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}
}



/*!
 *
 * @brief	This function sends a SIGFOX packet
 *
 * @param 	char* data:	data to be sent
 * @remarks	data is a sequence of digit representing the value of byte stream
 * 			expressed in hexadecimal value (i.e.: AT$SF=12A435,0 – the payload
 * 			is composed by the following byte stream: 0x12, 0xA4, 0x35 – 6 digit
 * 			converted in 3 bytes). The maximum length of frame is 24 digit (12Bytes)
 *
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::send(char* data)
{
	uint16_t length = strlen(data);

	if (length>24)
	{
		USB.println(F("ERROR: Sigfox packet too large"));
		return SIGFOX_ANSWER_ERROR;
	}


	// create "AT$SF=<data>" command
	GEN_ATCOMMAND_SET("SF", data);

	// enter command mode
	if( sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 15000) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	return SIGFOX_ANSWER_OK;
}




/*!
 *
 * @brief	This function sends a SIGFOX packet
 *
 * @param 	uint8_t* data:	pointer to the data to be sent
 * @param 	uint16_t length: length of the buffer to send
 *
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::send(uint8_t* data, uint16_t length)
{
	//define buffer
	char ascii_command[30];

	// truncate if greater than 12
	if (length>12)
	{
		length = 12;
	}

	// convert from binary to ASCII
	Utils.hex2str(data, ascii_command, length);

	#if DEBUG_SIGFOX > 1
		PRINT_SIGFOX(F("ascii_command: "));
		USB.println( ascii_command );
	#endif

	return send(ascii_command);
}





/*!
 * @brief	This function sends a SIGFOX packet
 *
 * @param 	char* data:	data to be sent
 * @remarks	data is a sequence of digit representing the value of byte stream
 * 			expressed in hexadecimal value (i.e.: AT$SF=12A435,0 – the payload
 * 			is composed by the following byte stream: 0x12, 0xA4, 0x35 – 6 digit
 * 			converted in 3 bytes). The maximum length of frame is 24 digit (12Bytes)
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::sendACK(char* data)
{
	uint16_t length = strlen(data);
	uint8_t status;

	if (length>24)
	{
		USB.println(F("ERROR: Sigfox packet too large"));
		return SIGFOX_ANSWER_ERROR;
	}


	// create "AT$SF=<data>" command
	GEN_ATCOMMAND_SET("SF", data, "2","1");

	// enter command mode
	if( sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 10000) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	status = waitFor("+RX BEGIN", SIGFOX_AT_ERROR, 20000);

	if (status == 2)
	{
		return SIGFOX_ANSWER_ERROR;
	}
	else if (status == 0)
	{
		return SIGFOX_NO_ANSWER;
	}

	status = waitFor("+RX END", SIGFOX_AT_ERROR, 25000);

	if (status == 1)
	{
		return SIGFOX_ANSWER_OK;
	}
	else if (status == 2)
	{
		return SIGFOX_ANSWER_ERROR;
	}
	else
	{
		return SIGFOX_NO_ANSWER;
	}
}




/*!
 *
 * @brief	This function sends a SIGFOX packet waiting for an ACK
 *
 * @param 	uint8_t* data:	pointer to the data to be sent
 * @param 	uint16_t length: length of the buffer to send
 *
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::sendACK(uint8_t* data, uint16_t length)
{
	//define buffer
	char ascii_command[30];

	// truncate if greater than 12
	if (length>12)
	{
		length = 12;
	}

	// convert from binary to ASCII
	Utils.hex2str(data, ascii_command, length);

	#if DEBUG_SIGFOX > 1
		PRINT_SIGFOX(F("ascii_command: "));
		USB.println( ascii_command );
	#endif

	return sendACK(ascii_command);
}




/*!
 *
 * @brief	This function is used to send a test SIGFOX frame across a
 * 			specific channel
 * @param	uint16_t count = 0..65535: Count of SIGFOX™ test RF messages. Default: 10
 * @param	uint16_t period = 1..255 Period in seconds between Sigfox test RF messages. Default: 10
 * @param	int channel = 0..180 or 220..400 or -1 Use automatic channel selection (default)
 * 			Channel number to use for SIGFOX™ test RF messages. Channels have a
 * 			fixed 100 Hz bandwidth, starting at 868.180 MHz for channel 0,
 * 			ending at 868.198 Mhz for channel 180, restarting at 868.202 MHz for
 * 			channel 220 and ending at 868.220 MHz for channel 400.
 *
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::testTransmit(uint16_t count, uint16_t period, int channel)
{
	char param1[20];
	char param2[20];
	char param3[20];

	// convert to string
	itoa(count, param1, 10);
	utoa(period, param2, 10);
	itoa(channel, param3, 10);

	// create "AT$ST=<count>,<period>,<channel>" command
	GEN_ATCOMMAND_SET("ST", param1, param2, param3);

	// enter command mode
	if( sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 10000*count*period) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	return SIGFOX_ANSWER_OK;
}





/*!
 *
 * @brief	This function displays the library version number as follows:
 * 			SOFTxxxx, where 'xxxx' is the version number
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::showFirmware()
{
	uint8_t status;

	// enter command mode
	if( sendCommand("ATI13\r", "SOFT", SIGFOX_AT_ERROR, 1000) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	// wait for ending pattern
	status = waitFor(SIGFOX_AT_OK,1000);

	if( status != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	// clear buffers
	memset(_firmware, 0x00, sizeof(_firmware));
	memcpy(_firmware, _buffer, _length);

	_firmware[0] = 'S';
	_firmware[1] = 'O';
	_firmware[2] = 'F';
	_firmware[3] = 'T';
	_firmware[4] = _buffer[0];
	_firmware[5] = _buffer[1];
	_firmware[6] = _buffer[2];
	_firmware[7] = _buffer[3];
	_firmware[8] = '\0';

	USB.print(F("Firmware Version:"));
	USB.println(_firmware);

	return SIGFOX_ANSWER_OK;
}




/*!
 *
 * @brief	This function sends a Keep-Alive message
 *
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::sendKeepAlive()
{
	// use the default settings
	sendKeepAlive(24);
}


/*!
 *
 * @brief	This function sends a Keep-Alive message
 *
 * @param 	uint8_t period: Number of hours. 0 Disable SIGFOX keepalive RF messages.
 * 			1..127 Period between 2 SIGFOX keepalive RF messages in hours
 * 			(default value is 24)
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::sendKeepAlive(uint8_t period)
{
	char param1[20];
	uint8_t answer;

	// create "ATS300=<period>" command
	snprintf(_command, sizeof(_command),"ATS300=%u\r", period);

	// set frequency setting
	if( sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 10000) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	return SIGFOX_ANSWER_OK;
}




/*!
 *
 * @brief	This function is used to radiate continuous wave without any modulation
 *
 * @param 	uint32_t freq: center frequency for carrier
 * @param 	bool enable: '1'=enable; '0'=disable
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::continuosWave(uint32_t freq, bool enable)
{
	char param1[20];
	char param2[20];

	// convert to string
	ltoa((uint32_t)freq, param1, 10);
	utoa((uint16_t)enable, param2, 10);

	// create "AT$CW=<enable>" command
	GEN_ATCOMMAND_SET("CW", param1, param2);

	// set CW mode: enabled or disabled
	if( sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 500) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	return SIGFOX_ANSWER_OK;
}




//  RF functions  //////////////////////////////////////////////////////////////





/*!
 * @brief	set LAN address and save settings
 * @param	uint32_t naddress: new address
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::setAddressLAN(uint32_t naddress)
{
	uint8_t status;
	snprintf( _command, sizeof(_command), "ATS400=%lu\r", naddress);

	status = sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);
	if( status == 1 )
	{
		// ok
		status = saveSettings();
		if (status == 0) _address = naddress;
		return status;
	}
	else if( status == 2 )
	{
		// error
		return 1;
	}
	else
	{
		// time out
		return 2;
	}
}





/*!
 * @brief	get LAN address from module in decimal format
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::getAddressLAN()
{
	uint8_t status;

	status = sendCommand("ATS400?\r", SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	if (status == 0)
	{
		return SIGFOX_NO_ANSWER;
	}
	else if (status == 2)
	{
		return SIGFOX_ANSWER_ERROR;
	}
	else if (status == 1)
	{
		// get value from received data
		_address = parseHexValue();
		return SIGFOX_ANSWER_OK;
	}
}




/*!
 * @brief	set Mask and save settings
 * @param	uint32_t nmask: new mask
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::setMask(uint32_t nmask)
{
	uint8_t status;

	snprintf(_command,sizeof(_command),"ATS401=%lu\r",nmask);

	status = sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 500);
	if( status == 1 )
	{
		// ok
		status = saveSettings();
		if (status == 0) _mask = nmask;
		return status;
	}
	else if( status == 2 )
	{
		// error
		return 1;
	}
	else
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}
}



/*!
 * @brief	get Mask from module in decimal format
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::getMask()
{
	uint8_t status;

	status = sendCommand("ATS401?\r", SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	if (status == 0)
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}
	else if (status == 2)
	{
		return SIGFOX_ANSWER_ERROR;
	}
	//status = waitFor(SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);
	else if( status == 1 )
	{
		// get value from received data
		_mask = parseHexValue();
		return SIGFOX_ANSWER_OK;
	}
}



/*!
 * @brief	set frequency and save settings
 * @param	uint32_t freq: new working frequency
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::setFrequency(uint32_t freq)
{
	uint8_t status;
	snprintf(_command, sizeof(_command), "ATS403=%lu\r", freq);

	status = sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);
	if( status == 1 )
	{
		// ok
		status = saveSettings();
		if (status == 0) _frequency = freq;
		return status;
	}
	else if( status == 2 )
	{
		// error
		return 1;
	}
	else
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}
}





/*!
 * @brief	get frequency from module
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::getFrequency()
{
	uint8_t status;

	status = sendCommand("ATS403?\r", "\r\n", SIGFOX_AT_ERROR, 1000);

	if (status != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	status = waitFor(SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	if( status == 1 )
	{
		// get value from received data
		_frequency = parseUint32Value();

		return 0;
	}
	else if( status == 2 )
	{
		// error
		return 1;
	}
	else
	{
		// time out
		return 2;
	}
}



/*!
 * @brief	set powel level for RF transmissions
 * @param	int power: power level to set
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::setPowerLAN(int power)
{
	uint8_t status;
	snprintf(_command, sizeof(_command), "ATS404=%d\r", power);

	status = sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);
	if( status == 1 )
	{
		// ok
		status = saveSettings();
		if (status == 0) _powerLAN = power;
		return status;
	}
	else if( status == 2 )
	{
		// error
		return 1;
	}
	else
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}
}





/*!
 * @brief	get Power level from module in decimal format
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::getPowerLAN()
{
	uint8_t status;

	status = sendCommand("ATS404?\r", "\r\n", SIGFOX_AT_ERROR, 1000);

	if (status != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	status = waitFor(SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	if( status == 1 )
	{
		// get value from received data
		_powerLAN = parseUint8Value();

		return 0;
	}
	else if( status == 2 )
	{
		// error
		return 1;
	}
	else
	{
		// time out
		return 2;
	}
}





/*!
 * @brief	Send a packet from one TD1207 to another TD1207 module
 * @param	uint8_t* data: pointer to data
 * @param	uint16_t length: length of the array of bytes
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::sendLAN(uint8_t* data, uint16_t length)
{
	//conversion to string
	char buffer[35];
	memset(buffer, 0x00, sizeof(buffer));
	Utils.hex2str(data, buffer, length);

	return sendLAN(buffer);
}


/*!
 * @brief	Send a packet from one TD1207 to another TD1207 module
 * @param	char* data: string to be sent
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::sendLAN(char* data)
{
	uint8_t status;
	uint16_t length = strlen(data);

	memset(_command, 0x00, sizeof(_command));
	strcpy(_command,"AT$SL=");
	strcat(_command,data);

	// fill command with zero chars to avoid sending data from previous sending
	for (int i = length; i < SIGFOX_LAN_MAX_PAYLOAD*2; i++)
	{
		strcat(_command, "0");
	}
	strcat(_command,"\r");

	// send packet
	status = sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 5000);

	if( status == 1 )
	{
		// ok
		return 0;
	}
	else if( status == 2 )
	{
		// error
		return 1;
	}
	else
	{
		// time out
		return 2;
	}
}



/*!
 * @brief	Parse the contents of the '_buffer' structure to detect a new
 * 			incoming packet
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::parsePacketLAN()
{
	char* pch;

	pch = strtok((char*) _buffer,"\r\n+RX_LAN=");
	if (pch != NULL)
	{
		memset(_packet, 0x00, sizeof(_packet));
		memcpy(_packet, pch, strlen(pch));

		return SIGFOX_ANSWER_OK;
	}

	return SIGFOX_NO_ANSWER;
}



/*!
 * @brief	Receive packets from another TD1207 module
 * @param	uint32_t wait: time to wait for data
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::receive(uint32_t wait)
{
	uint8_t status;

	snprintf(_command, sizeof(_command), "AT$RL=1,%lu\r", wait);

	status = sendCommand(_command, "\r\n", SIGFOX_AT_ERROR, wait*1001);

	if( status == 2 )
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else if( status == 0 )
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}

	status = waitFor(SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	if( status == 1 )
	{
		// ok
		status = parsePacketLAN();
		return status;
	}
	else if( status == 2 )
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}
}


/*!
 * @brief	Prints data received through USB
 * @return	void
 *
 */
 void WaspSigfox::showPacket()
{
	USB.println(_buffer,_length);
}



/*!
 * @brief	set receiving mode to continuous rx mode
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::setMultiPacket()
{
	uint8_t status;
	status = sendCommand("AT$RL=2\r", SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	if( status == 1 )
	{
		// ok
		return SIGFOX_ANSWER_OK;
	}
	else if( status == 2 )
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}
}



/*!
 * @brief	disable rx mode
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::disableRX()
{
	uint8_t status;
	status = sendCommand("AT$RL=0\r", SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	if( status == 1 )
	{
		// ok
		return SIGFOX_ANSWER_OK;
	}
	else if( status == 2 )
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else
	{
		// time out
		return SIGFOX_NO_ANSWER;
	}
}



/*!
 * @brief	Wait for a new incoming packet. When a packet is received, the
 * 			contents are copied to '_packet' structure. If no packet is received
 * 			after 'time' seconds, the function returns error
 * @param	uint32_t time: time to wait for new incoming packet
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::getMultiPacket(uint32_t time)
{
	uint8_t status;

	status = waitFor("+RX_LAN=",time*1000);

	if (status==1)
	{
		waitFor("\r\n",100);
		status = parsePacketLAN();

		return status;
	}
	else
	{
		return SIGFOX_NO_ANSWER;
	}
}



/*!
 * @brief	get the actual region of the module
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::getRegion()
{
	uint8_t status;

	status = sendCommand("ATS304?\r", "\r\n", SIGFOX_AT_ERROR, 1000);

	if (status != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	status = waitFor(SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	if (status == 1 )
	{
		// get value from received data
		_region = parseUint8Value();

		return 0;
	}
	else if (status == 2 )
	{
		// error
		return 1;
	}
	else
	{
		// time out
		return 2;
	}
}



/*!
 * @brief	This function configures the SIGFOX FCC Macro Channel Bitmask to
 * 			enable/disable the 192KHz macro channels authorized for transmission
 *
 * @remarks	This parameter is used only in FCC region, there is no effect in
 * 			ETSI. To change this parameter, an AT&W command and ATZ command are
 * 			required
 * @param 	char* bitmask: "000000000000000000000000" to "FFFFFFFFFFFFFFFFFFFFFFFF"
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::setMacroChannelBitmask(char* bitmask)
{
	uint8_t answer;

	snprintf(_command, sizeof(_command), "ATS306=%s\r", bitmask);

	// 1. send command
	answer = sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	// check possible error answers
	if (answer == 2)
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else if (answer == 0)
	{
		// timeout
		return SIGFOX_NO_ANSWER;
	}

	// 2. save config
	answer = saveSettings();

	return answer;
}


/*!
 * @brief	This function queries the SIGFOX FCC Macro Channel Bitmask to
 * 			enable/disable the 192KHz macro channels authorized for transmission
 * @remarks	This parameter is used only in FCC region, there is no effect in
 * 			ETSI. To change this parameter, an AT&W command and ATZ command are
 * 			required
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::getMacroChannelBitmask()
{
	uint8_t answer;

	snprintf(_command, sizeof(_command), "ATS306?\r");

	// enter command mode
	if (sendCommand(_command, SIGFOX_AT_EOL, SIGFOX_AT_ERROR, 1000) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	answer = waitFor(SIGFOX_AT_EOL, 1000);

	// enter command mode
	if (answer != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	// get value from received data
	answer = parseString(_macroChannelBitmask, sizeof(_macroChannelBitmask), "\r\n", 1);

	if (answer != 0)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	return SIGFOX_ANSWER_OK;
}





/*!
 * @brief	This function configures the SIGFOX Default FCC Macro Channel.
 *
 * @remarks	This parameter is used only in FCC region, there is no effect in
 * 			ETSI. To change this parameter, an AT&W command and ATZ command are
 * 			required
 * @param 	uint8_t config: range from 1 to 82.
 * 			The default FCC channel value must be between 1 and 82. At least 9
 * 			macro channels must be enabled to ensure the minimum of 50 FCC
 * 			channels. Parameter is 3 x 32bits words, with word 1 first.
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::setMacroChannel(uint8_t config)
{
	uint8_t answer;

	snprintf(_command, sizeof(_command), "ATS307=%u\r", config);

	// 1. send command
	answer = sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	// check possible error answers
	if (answer == 2)
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else if (answer == 0)
	{
		// timeout
		return SIGFOX_NO_ANSWER;
	}

	// 2. save config
	answer = saveSettings();

	return answer;
}


/*!
 * @brief	This function queries the SIGFOX Default FCC Macro Channel.
 * @remarks	This parameter is used only in FCC region, there is no effect in
 * 			ETSI. To change this parameter, an AT&W command and ATZ command are
 * 			required
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::getMacroChannel()
{
	uint8_t answer;

	snprintf(_command, sizeof(_command), "ATS307?\r");

	// enter command mode
	if (sendCommand(_command, SIGFOX_AT_EOL, SIGFOX_AT_ERROR, 1000) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	answer = waitFor(SIGFOX_AT_EOL, 1000);

	// enter command mode
	if (answer != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	// get value from received data
	answer = parseUint8(&_macroChannel, "\r\n", 1);

	if (answer != 0)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	return SIGFOX_ANSWER_OK;
}





/*!
 * @brief	This function configures the SIGFOX Downlink frequency offset.
 *
 * @remarks	This parameter is used only in FCC region, there is no effect in
 * 			ETSI. To change this parameter, an AT&W command and ATZ command are
 * 			required
 * @param 	uint8_t config: range from -30000000  to 30000000 Hz
 * 			The default value in FCC mode is 3000000 Hz
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::setDownFreqOffset(int32_t offset)
{
	uint8_t answer;

	snprintf(_command, sizeof(_command), "ATS308=%li\r", offset);

	// 1. send command
	answer = sendCommand(_command, SIGFOX_AT_OK, SIGFOX_AT_ERROR, 1000);

	// check possible error answers
	if (answer == 2)
	{
		// error
		return SIGFOX_ANSWER_ERROR;
	}
	else if (answer == 0)
	{
		// timeout
		return SIGFOX_NO_ANSWER;
	}

	// 2. save config
	answer = saveSettings();

	return answer;
}


/*!
 * @brief	This function queries the SIGFOX Downlink frequency offset.
 * @remarks	This parameter is used only in FCC region, there is no effect in
 * 			ETSI. To change this parameter, an AT&W command and ATZ command are
 * 			required
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 */
uint8_t WaspSigfox::getDownFreqOffset()
{
	uint8_t answer;

	snprintf(_command, sizeof(_command), "ATS308?\r");

	// enter command mode
	if (sendCommand(_command, SIGFOX_AT_EOL, SIGFOX_AT_ERROR, 1000) != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	answer = waitFor(SIGFOX_AT_EOL, 1000);

	// enter command mode
	if (answer != 1)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	// get value from received data
	answer = parseInt32(&_downFreqOffset, "\r\n");

	if (answer != 0)
	{
		return SIGFOX_ANSWER_ERROR;
	}

	return SIGFOX_ANSWER_OK;
}


/*!
 * @brief	set frequency and save settings
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::setRegionRC4()
{
	uint8_t status;

	status = factorySettings();
	if (status)
	{
		// error
		return status;
	}

	status = defaultConfiguration();
	if (status)
	{
		// error
		return status;
	}

	// set specific Australia channel configuration
	status = setMacroChannelBitmask("00000000C00000000000007F");

	if (status)
	{
		// error
		return status;
	}

	// start channel
	status = setMacroChannel(63);

	if (status)
	{
		// error
		return status;
	}

	// offset definitino for downlink mode
	status = setDownFreqOffset(1500000);

	if (status)
	{
		// error
		return status;
	}

	// save settings in memory
	status = saveSettings();

	if (status)
	{
		// error
		return status;
	}


	status = defaultConfiguration();

	if (status)
	{
		// error
		return status;
	}

}



/*!
 * @brief	set frequency and save settings
 * @return
 * 	@arg	'SIGFOX_ANSWER_OK' if OK
 * 	@arg	'SIGFOX_ANSWER_ERROR' if error
 * 	@arg	'SIGFOX_NO_ANSWER' if no answer
 *
 */
uint8_t WaspSigfox::setRegionRC2()
{
	uint8_t status;

	status = factorySettings();
	if (status)
	{
		// error
		return status;
	}

	status = defaultConfiguration();
	if (status)
	{
		// error
		return status;
	}

}

// Preinstantiate Objects /////////////////////////////////////////////////////

WaspSigfox Sigfox = WaspSigfox();

///////////////////////////////////////////////////////////////////////////////
