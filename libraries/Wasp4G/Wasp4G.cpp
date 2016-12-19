/*! \file Wasp4G.cpp
 *  \brief Library for managing Telit LE910
 *
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
 *  Version:		3.1
 *  Design:			David Gascón
 *  Implementation:	A. Gállego, Y. Carmona
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

#include "Wasp4G.h"
#include <inttypes.h>



//! class constructor
Wasp4G::Wasp4G()
{
	memset(_apn, '\0', sizeof(_apn));
	memset(_apn_login, '\0', sizeof(_apn_login));
	memset(_apn_password, '\0', sizeof(_apn_password));
	strncpy(_apn, LE910_GPRS_APN, min(sizeof(_apn), strlen(LE910_GPRS_APN)));
	strncpy(_apn_login, LE910_GPRS_LOGIN, min(sizeof(_apn_login), strlen(LE910_GPRS_LOGIN)));
	strncpy(_apn_password, LE910_GPRS_PASSW, min(sizeof(_apn_password), strlen(LE910_GPRS_PASSW)));	
}


// Private Methods ////////////////////////////////////////////////////////////



/* 
 * Function: This function parses the error copde returned by the module. At the
 * point this function is called, the UART is supposed to have received: 
 * "+CME ERROR: <err>\r\n" and the first part of the response has been already 
 * detected: "+CME ERROR:", so this function needs to parse the error code
 * 
 * If error code is parsed succesfully then the attribute _errorCode stores
 * this error information
 * 
 * @return	'0' if ok; '1' if error
 */
uint8_t Wasp4G::getErrorCode()
{	
	uint8_t status;
	char format[20];
		
	// wait for " <err>\r\n"
	status = waitFor((char*)"\r\n", 3000);
	
	if (status == 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("no response\n"));
		#endif
		return 1;
	}
	else
	{
		parseUint32((uint32_t*)&_errorCode, " \r\n");
		
		#if DEBUG_WASP4G > 0
			printErrorCode( _errorCode );	
		#endif	
		return 0;
	}
	
}



/* Function: 	This function checks connection status and connect to data service
 * Parameters:	time: max allowed time in seconds to connect
 * Return:	0 If the module is connected to data service
 * 			1 not registered, ME is not currently searching for a new operator to register to
 * 			2 not registered, but ME is currently searching for a new operator to register to
 * 			3 registration denied
 * 			4 unknown
 * 			6 not registered, ME is not currently searching for a new operator to register to
 * 			8 not registered, but ME is currently searching for a new operator to register to
 * 			9 registration denied
 * 			10 unknown
 * 			12 if error setting APN
 * 			13 if error setting login
 * 			14 if error setting password
 * 			15 if error activating GPRS connection
 */
uint8_t Wasp4G::checkDataConnection(uint8_t time)
{	
	uint8_t answer;
	uint32_t previous, max_time;
	uint8_t status;
	
	char command_buffer[40];
	char answer1[20];
	char answer2[20];
	
	answer = 0;
	max_time = (unsigned long)time * 1000;
	previous = millis();
	
	
	//// 1. Check if the module has the GPRS connection active
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[26]))); // "AT#GPRS?\r"
	strcpy_P(answer1, (char*)pgm_read_word(&(table_4G[27]))); // "GPRS: 1"
	strcpy_P(answer2, (char*)pgm_read_word(&(table_4G[28]))); // "GPRS: 0"
	
	// send command
	answer = sendCommand(command_buffer, answer1, answer2, 2000);
	if (answer == 1)
	{		
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("Connection active, nothing more to check\n"));
		#endif
		return 0;
	}
	
	
	//// 2. Check Network Registration Report
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[0])));	//AT+CREG?\r
	strcpy_P(answer1, (char*)pgm_read_word(&(table_4G[1])));	//+CREG: 0,
	do{	
		// Sends the command and waits for the answer:
		// 	answer "0,1" for "home network" 
		// 	answer "0,5" for "roaming"
		answer = sendCommand(command_buffer, answer1, LE910_ERROR_CODE, 2000);
		
		if (answer == 1)
		{
			status = waitFor("\r\n", LE910_ERROR_CODE, 500);
			
			if (status == 1)
			{
				parseUint8(&answer, "\r\n");
				#if DEBUG_WASP4G > 1
					PRINT_LE910(F("CREG: 0,")); 
					USB.println(answer, DEC);
				#endif
			}			
		}
		delay(1000);
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
	}while (((answer == 2) || (answer == 3) || (answer == 4) || (answer == 0)) && ((millis() - previous) < max_time));
	
	// check bad responses or timeout
	if (((answer != 1) && (answer != 5)) || ((millis() - previous) > max_time))
	{
		if (answer == 0)
		{
			return answer + 1;
		}
		return answer;
	}


	//// 3. Check GPRS Network Registration Status
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[2])));	//AT+CGREG?\r
	strcpy_P(answer1, (char*)pgm_read_word(&(table_4G[3])));	//+CGREG: 0,	
	do{	
		// Sends the command and waits for the answer: 
		// 	answer "0,1" for "home network" 
		// 	answer "0,5" for "roaming"
		answer = sendCommand(command_buffer, answer1, LE910_ERROR_CODE, 2000);		
		if (answer == 1)
		{			
			status = waitFor("\r\n", LE910_ERROR_CODE, 500);
			
			if (status == 1)
			{
				parseUint8(&answer, "\r\n");
				#if DEBUG_WASP4G > 1
					PRINT_LE910(F("CGREG: 0,"));
					USB.println(answer, DEC);
				#endif
			}	
		}
		delay(1000);
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
	}while (((answer == 2) || (answer == 3) || (answer == 4) || (answer == 0)) && ((millis() - previous) < max_time));
	
	// check good responses
	if (((answer != 1) && (answer != 5)) || ((millis() - previous) > max_time))
	{
		return answer + 6;
	}
	
	
	//// 4. Define PDP Context
	// AT+CGDCONT=1,"IP","<APN>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_4G[29])), _apn);
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 12;
	}
	
	
	//// 5. Set Authentication User ID
	// AT#USERID="<login>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_4G[5])), _apn_login);
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 13;
	}
	
	
	//// 6. Set Authentication Password
	// AT#PASSW="<pass>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_4G[6])), _apn_password);
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 14;
	}
	
	
	//// 7. GPRS Context Activation
	// "AT#GPRS=1\r"
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[31])));
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 15000);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 15;
	}
	
	// delimiters <--- "+IP: \"\r\n"
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[32])));
	
	// get IP address in response
	answer = parseString(_ip, sizeof(_ip), command_buffer);
	
	if (answer != 0)
	{
		return 16;
	}
	
	return 0;
}


/* This function configures the remote server and sends the request
 * Parameters;	
 * 		method: selected HTTP method:	GET_METHOD
 * 										HEAD_METHOD
 * 										DELETE_METHOD
 * 										POST_METHOD
 * 										PUT_METHOD
 *		url: host name or IP address of the server
 *		port: server port
 *		resource: parameter indicating the HTTP resource, object of the	request
 *		data: data to send in POST/PUT method	
 * 
 *	Return:	'0' if OK
 * 			'x' if error. See httpRequest()
 */
uint8_t Wasp4G::httpRequest(uint8_t method,
							char* url, 
							uint16_t port,
							char* resource,
							char* data)
{	
	return httpRequest(	method,
						url, 
						port, 
						resource, 
						(uint8_t*)data, 
						strlen(data));

}

/* This function configures the remote server and sends the request
 * Parameters;	
 * 		method: selected HTTP method:	GET_METHOD
 * 										HEAD_METHOD
 * 										DELETE_METHOD
 * 										POST_METHOD
 * 										PUT_METHOD
 *		url: host name or IP address of the server
 *		port: server port
 *		resource: parameter indicating the HTTP resource, object of the	request
 *		data: data to send in POST/PUT method
 *		length: data length to send in POST/PUT method
 * 
 *	Return:	0 if OK
 * 			1 if error setting URL and port
 * 			2 if error sending the request
 * 			3 if error sending POST / PUT data
 * 			4 if wrong method has been selected
 */
uint8_t Wasp4G::httpRequest(uint8_t method,
							char* url, 
							uint16_t port,
							char* resource,
							uint8_t* data,
							uint16_t length)
{	
	uint8_t answer;
	char command_buffer[500];	
	char aux[3];
	memset( aux, 0x00, sizeof(aux) );

	// Step1: Configure HTTP parameters	
	// Generate: AT#HTTPCFG=0,"<url>",<port>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[0])), url, port);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR, LE910_ERROR_CODE, 2000);		

	if (answer == 2)
	{	
		_errorCode = WASP4G_ERROR_MESSAGE;
		return 1;
	}
	else if (answer == 3)
	{
		getErrorCode();
		return 1;
	}
	else if (answer == 0)
	{
		// timeout
		_errorCode = WASP4G_ERROR_TIMEOUT;
		return 1;
	}
	
	
	// Step2: Perform the request depending on the method selected as input 
	// in the function: GET, HEAD, DELETE, POST or PUT
	if ((method == Wasp4G::HTTP_GET) ||
		(method == Wasp4G::HTTP_HEAD) ||
		(method == Wasp4G::HTTP_DELETE))
	{		
		// AT#HTTPQRY=0,<method>,"<resource>"\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[1])), method, resource);
		
		// send command
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR, 5000);
		
		if (answer == 1)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
	else if ((method == Wasp4G::HTTP_POST) ||
			(method == Wasp4G::HTTP_PUT))
	{		
		// 2a. Send HTTP POST or PUT request
		// AT#HTTPSND=0,<method>,"<resource>",<data_length>
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[2])),
				method - 3, 
				resource, 
				length);
				
		// send command
		answer = sendCommand(command_buffer, LE910_DATA_TO_MODULE, LE910_ERROR, 5000);		
		if (answer != 1)
		{
			return 2;
		}
		
		// 2b. Send POST/PUT data
		answer = sendCommand((char*)data, LE910_OK ,LE910_ERROR, 5000);
		if (answer != 1)
		{
			return 3;
		}
		
		return 0;
	}
	else if (method == Wasp4G::HTTP_POST_FRAME)
	{
		char php_file[27];
		
		// 2a. Perform the request
		// "/getpost_frame_parser.php"
		strcpy_P(php_file, (char*)pgm_read_word(&(table_HTTP[5])));	
		
		// AT#HTTPSND=0,0,"<php_file>",<data_length>
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[2])),
				0, 
				php_file, 
				6 + (length * 2));
				
		answer = sendCommand(command_buffer, LE910_DATA_TO_MODULE, LE910_ERROR, 5000);		
		if (answer != 1)
		{
			return 2;
		}
		
		// Add "frame="
		strcpy_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[6])));		
		printString(command_buffer, 1);
		
		// Add frame contents in ASCII representation: 3C3D3E...
		for(uint16_t x = 0; x < length; x++)
		{
			// make conversion from byte to hex representation in ASCII (2Bytes)
			Utils.hex2str((uint8_t*)&data[x], aux, 1);		
			printByte(aux[0], 1);
			printByte(aux[1], 1);
		}
		
		
		// 2b. Send POST/PUT data
		answer = waitFor(LE910_OK ,LE910_ERROR, 5000);
		if (answer != 1)
		{
			return 3;
		}
		
		return 0;
		
	}
	
	// Wrong method
	return 4;
	
}

/* This function waits the URC code and reads the data availble
 * Parameters:	wait_timeout: timeout for URC * 				
 *	Return:	0 if OK
 * 			1 if timeout waiting the URC 
 * 			2 if error reading the URC
 * 			3 if error reading the HTTP status
 * 			4 if error reading the HTTP data length
 * 			5 if error reading the HTTP data
 * 			6 if error code from 4G module
 * 			7 if timeout waiting for data
 * 			8 if data length is zero
 */
uint8_t Wasp4G::httpWaitResponse(uint32_t wait_timeout)
{
	char *pointer;
	uint8_t answer;
	uint16_t data_size;
	char command_buffer[50];
		
	// 1. Wait URC: "#HTTPRING: 0,"
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[3])));
	
	answer = waitFor(command_buffer, wait_timeout);
	if (answer == 0)
	{
		return 1;
	}
	
	// 2. Read the whole response: "#HTTPRING: 0,<http_status_code>,<content_type>,<data_size>\r
	answer = waitFor("\r", 5000);
	if (answer == 0)
	{
		return 2;
	}
	
	// 3. Read <http_status_code>
	pointer = strtok((char*)_buffer, ",");
	
	if (pointer == NULL)
	{
		return 3;
	}
	else
	{
		// Store the HTTP code in attribute
		_httpCode = atoi(pointer);
	}
	
	
	// 4. Skip <content_type>
	strtok(NULL, ",");	
	
	
	// 5. Read <data_size>
	pointer = strtok((char*)_buffer, ",");
		
	if (pointer == NULL)
	{
		return 4;
	}
	else
	{
		// Store the HTTP code in attribute
		data_size = atoi(pointer);
	}	
	
	// 6. Read data received
	if (data_size > 0)
	{
		// AT#HTTPRCV=0,0\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[4])), 0, 0);
		
		// send command
		answer = sendCommand(command_buffer, LE910_DATA_FROM_MODULE, LE910_ERROR, 2000);
		
		// check answer
		if (answer == 1)
		{			
			// Read the data
			answer = waitFor("\r", 5000);
			if (answer == 0)
			{
				return 5;
			}
			
			// Add end of string in _buffer
			_buffer[_length] = '\0';
			
			return 0;
		}
		else if (answer == 2)
		{
			return 6;
		}
		else
		{
			// Timeout
			return 7;
		}		
	}
	
	return 8;
	
}


/* Function: 	This function reads the size of a file in a FTP server
 * Parameters:	ftp_file: file
 * Return:	0 if "ok"
 * 			1 if error
 */
uint8_t Wasp4G::ftpFileSize( char* ftp_file)
{	
	uint8_t answer;
	char *pointer;
	char command_buffer[50];
	
	// init variable
	_filesize = 0;
	
	// AT#FTPFSIZE=<ftp_file>\r
	memset(command_buffer,0x00,sizeof(command_buffer));
	sprintf_P(command_buffer,(char*)pgm_read_word(&(table_FTP[5])),ftp_file);

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 15000);

	#if DEBUG_WASP4G > 0
		PRINT_LE910(F("_buffer:")); 
		USB.println((char*)_buffer);
	#endif

	if (answer != 1)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error getting filesize\n")); 
		#endif
		
		if (answer == 2)
		{
			getErrorCode();
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		return 1;
	}
	
	// parse file size
	char delimiters[50];	
	memset(delimiters, 0x00, sizeof(delimiters));
	strcat(delimiters, "#FTPFSIZE: ");
	strcat(delimiters, "\r\n");	
	
	if (strstr((char*)_buffer, "FTPFSIZE:") == NULL)
	{
		return 2;
	}
	
	
	answer = parseUint32(&_filesize, delimiters);
	
	if (answer == 0)
	{
		return 0;
	}	
	
	return 3;
}


/* Function: 	This function gets the status of a TCP or UDP socket
 * Parameters:	socketId: number of the socket Id
 * Return:		0: ok; 1: error
 */
uint8_t Wasp4G::getSocketStatus(uint8_t socketId)
{
	uint8_t answer;
	char delimiters[20];
	char command_buffer[20];
	char *pointer;
	
	// clear structure
	socketStatus[socketId].id = 0;
	socketStatus[socketId].state = 0;
	socketStatus[socketId].localPort = 0;
	socketStatus[socketId].remotePort = 0;
	memset(socketStatus[socketId].localIp, 0x00, sizeof(socketStatus[socketId].localIp));
	memset(socketStatus[socketId].remoteIp, 0x00, sizeof(socketStatus[socketId].remoteIp));
		
	// AT#SS=<socketId>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[0])),	socketId+1);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer
	if(answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif	
		}
			
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error getting socket status\n"));
		#endif	
		return 1;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("_buffer:"));
		USB.println((char*)_buffer);
	#endif	
	
	
	// delimiters <-- "#SS: "
	strcpy_P(delimiters, (char*)pgm_read_word(&(table_IP[20])));
	
	// seek pattern in module response
	// the response is something similar to this:
	// "#SS: <id>,<status>,<localIp>,<lPort>,<remoteIp>,<rPort>\r\n\r\nOK\r\n"
	pointer = strstr((char*)_buffer, delimiters);
	
	if (pointer == NULL)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error: null pointer1\n"));
		#endif	
		return 1;
	}
	
	// delimiters <-- "#SS: ,\r\n"
	strcpy_P(delimiters, (char*)pgm_read_word(&(table_IP[21])));
	
	// find first value skipping delimiters
	pointer = strtok(pointer, delimiters);
	
	// iterate through response	
	for (int i = 0; i < 6; i++)
	{
		if (pointer == NULL)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error: null pointer2\n"));
			#endif
			return 1;
		}
		
		if (i == 0)
		{
			socketStatus[socketId].id = (uint8_t) strtoul( pointer, NULL, 10);			
		}
		else if (i == 1)
		{			
			socketStatus[socketId].state = (uint8_t) strtoul( pointer, NULL, 10);
			
			// if state is closed then break
			if (socketStatus[socketId].state == 0)
			{
				break;
			}			
		}
		else if (i == 2)
		{
			strncpy(socketStatus[socketId].localIp, pointer, sizeof(socketStatus[socketId].localIp));
		}
		else if (i == 3)
		{
			socketStatus[socketId].localPort = (uint16_t) strtoul( pointer, NULL, 10);	
		}
		else if (i == 4)
		{
			strncpy(socketStatus[socketId].remoteIp, pointer, sizeof(socketStatus[socketId].remoteIp));	
		}
		else if (i == 5)
		{
			socketStatus[socketId].remotePort = (uint16_t) strtoul( pointer, NULL, 10);
			break;
		}
		
		pointer = strtok (NULL, " ,\r\n");
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("socketStatus.id:"));
		USB.println(socketStatus[socketId].id, DEC);
		PRINT_LE910(F("socketStatus.state:"));
		USB.println(socketStatus[socketId].state, DEC);
		if (socketStatus[socketId].state != 0)
		{		
			PRINT_LE910(F("socketStatus.localIp:"));
			USB.println(socketStatus[socketId].localIp);
			PRINT_LE910(F("socketStatus.localPort:"));
			USB.println(socketStatus[socketId].localPort, DEC);
			PRINT_LE910(F("socketStatus.remoteIp:"));
			USB.println(socketStatus[socketId].remoteIp);
			PRINT_LE910(F("socketStatus.remotePort:"));
			USB.println(socketStatus[socketId].remotePort, DEC);			
		}
	#endif
	
	return 0;

}


/* Function: 	This function gets the status of all TCP/UDP socket from 
 * 				SOCKET_1 to SOCKET_6
 * 
 * Return:		0: ok; 1: error
 */
uint8_t Wasp4G::getAllSocketStatus()
{
	uint8_t answer;	
	char command_pattern[20];
	char command_buffer[20];
	char *pointer;
	
	// clear structure
	memset(socketStatus, 0x00, sizeof(socketStatus));
	
	// "AT#SS\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[31])));
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif	
		}
		
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error getting socket status\n"));
		#endif	
		return 1;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("_buffer:"));
		USB.println((char*)_buffer);
	#endif	
	
	// iterate through all profile from 1 to 6
	for (int profile = 0; profile < 6; profile++)
	{
		// "#SS: %u,"
		sprintf_P(command_pattern, (char*)pgm_read_word(&(table_IP[32])), profile+1);
		
		// seek start of correct index
		pointer = strstr((char*)_buffer, command_pattern);		
		
		// delimiters <-- "#SS: ,\r\n"
		strcpy_P(command_pattern, (char*)pgm_read_word(&(table_IP[21])));
	
		// find first value skipping delimiters
		pointer = strtok(pointer, command_pattern);
		
		// iterate through response	
		for (int i = 0; i < 6; i++)
		{
			if (pointer == NULL)
			{
				#if DEBUG_WASP4G > 0
					PRINT_LE910(F("Error: null pointer2\n"));
				#endif
				return 1;
			}
			
			if (i == 0)
			{
				socketStatus[profile].id = (uint8_t) strtoul( pointer, NULL, 10);			
			}
			else if (i == 1)
			{			
				socketStatus[profile].state = (uint8_t) strtoul( pointer, NULL, 10);
				
				// if state is closed then break
				if (socketStatus[profile].state == 0)
				{
					break;
				}			
			}
			else if (i == 2)
			{
				strncpy(socketStatus[profile].localIp, pointer, sizeof(socketStatus[profile].localIp));
			}
			else if (i == 3)
			{
				socketStatus[profile].localPort = (uint16_t) strtoul( pointer, NULL, 10);	
			}
			else if (i == 4)
			{
				strncpy(socketStatus[profile].remoteIp, pointer, sizeof(socketStatus[profile].remoteIp));	
			}
			else if (i == 5)
			{
				socketStatus[profile].remotePort = (uint16_t) strtoul( pointer, NULL, 10);
				break;
			}
			
			pointer = strtok (NULL, " ,\r\n");
		}		
	}
	
	#if DEBUG_WASP4G > 1
		for (int i = 0; i < 6; i++)
		{		
			PRINT_LE910(F("socketStatus.id:"));
			USB.println(socketStatus[i].id, DEC);
			PRINT_LE910(F("socketStatus.state:"));
			USB.println(socketStatus[i].state, DEC);
			if (socketStatus[i].state != 0)
			{		
				PRINT_LE910(F("socketStatus.localIp:"));
				USB.println(socketStatus[i].localIp);
				PRINT_LE910(F("socketStatus.localPort:"));
				USB.println(socketStatus[i].localPort, DEC);
				PRINT_LE910(F("socketStatus.remoteIp:"));
				USB.println(socketStatus[i].remoteIp);
				PRINT_LE910(F("socketStatus.remotePort:"));
				USB.println(socketStatus[i].remotePort, DEC);			
			}
			PRINT_LE910(F("---------------------------\n"));
		}
	#endif
	
	return 0;

}


/* Function: 	This function gets the status of a TCP or UDP socket
 * Parameters:	socketId: number of the socket Id
 * Return:		0: ok; 1: error
 */
uint8_t Wasp4G::getSocketStatusSSL(uint8_t socketId)
{
	uint8_t answer;
	char delimiters[20];
	char command_buffer[20];
	char *pointer;
	
	// clear structure
	socketStatusSSL[socketId].id = 0;
	socketStatusSSL[socketId].state = 0;
		
	// AT#SSLS=<socketId>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[13])), socketId+1);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer
	if(answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif	
		}
			
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error getting socket status\n"));
		#endif	
		return 1;
	}
	
	// delimiters <-- "#SSLS: "
	strcpy_P(delimiters, (char*)pgm_read_word(&(table_IP[22])));
	
	// seek pattern in module response
	// the response is something similar to this:
	// "#SSLS: <id>,<status>\r\n\r\nOK\r\n"
	pointer = strstr((char*)_buffer, delimiters);
	
	if (pointer == NULL)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error: null pointer1\n"));
		#endif	
		return 1;
	}
	
	// delimiters <-- "#SSLS: ,\r\n"
	strcpy_P(delimiters, (char*)pgm_read_word(&(table_IP[23])));
	
	// find first value skipping delimiters
	pointer = strtok(pointer, delimiters);
	
	// iterate through response	
	for (int i = 0; i < 2; i++)
	{
		if (pointer == NULL)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error: null pointer2\n"));
			#endif
			return 1;
		}
		
		if (i == 0)
		{
			socketStatusSSL[socketId].id = (uint8_t) strtoul( pointer, NULL, 10);
		}
		else if (i == 1)
		{			
			socketStatusSSL[socketId].state = (uint8_t) strtoul( pointer, NULL, 10);
			break;
		}
		
		pointer = strtok (NULL, " ,\r\n");
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("socketStatusSSL.id:"));
		USB.println(socketStatusSSL[socketId].id, DEC);
		PRINT_LE910(F("socketStatusSSL.state:"));
		USB.println(socketStatusSSL[socketId].state, DEC);
	#endif
	
	return 0;

}


/* Function: 	This function gets info from a TCP or UDP socket
 * Parameters:	socketId: number of the socket Id
 * 				parameter:	0 for total amount (in bytes) of sent data
 * 							1 for total amount (in bytes) of received data
 * 							2 for total amount (in bytes) of data just 
 * 								arrived through the socket connection and 
 * 								currently buffered, not yet read
 * 							3 for total amount (in bytes) of sent and not yet
 *								 acknowledged data
 * Return:	0 or positive value from the command
 * 			-1 if error reading the info from the socket
 */
uint8_t Wasp4G::getSocketInfo(uint8_t socketId)
{
	uint8_t answer;
	char delimiters[20];
	char command_buffer[20];
	char *pointer;
	
	// clear structure
	socketInfo[socketId].id = 0;
	socketInfo[socketId].sent = 0;
	socketInfo[socketId].received = 0;
	socketInfo[socketId].size = 0;
	socketInfo[socketId].ack = 0;
	
	// AT#SI=<socketId>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[1])),	socketId+1);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);	

	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}		
		return 1;
	}
		
	// delimiters <-- #SI: "
	strcpy_P(delimiters, (char*)pgm_read_word(&(table_IP[24])));
	
	// seek pattern in module response
	// the reponse is something similar to this:
	// "#SI: <v1>,<v2>,<v3>,<v4>,<v5>\r\n\r\nOK\r\n"
	pointer = strstr((char*)_buffer, delimiters);
	
	if (pointer == NULL)
	{
		return 1;
	}	
	
	// delimiters <-- "#SI: ,\r\n"
	strcpy_P(delimiters, (char*)pgm_read_word(&(table_IP[25])));
	
	// find first value skipping delimiters
	pointer = strtok(pointer, delimiters);
	
	// iterate through response	
	for (int i = 0; i < 5; i++)
	{
		if (pointer == NULL)
		{
			return 1;
		}
		
		if (i == 0)
		{
			socketInfo[socketId].id = (uint8_t) strtoul( pointer, NULL, 10);			
		}
		else if (i == 1)
		{			
			socketInfo[socketId].sent = (uint16_t) strtoul( pointer, NULL, 10);	
		}
		else if (i == 2)
		{
			socketInfo[socketId].received = (uint16_t) strtoul( pointer, NULL, 10);
		}
		else if (i == 3)
		{
			socketInfo[socketId].size = (uint16_t) strtoul( pointer, NULL, 10);	
		}
		else if (i == 4)
		{
			socketInfo[socketId].ack = (uint16_t) strtoul( pointer, NULL, 10);
			break;
		}
		
		pointer = strtok (NULL, " ,\r\n");
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("socketInfo.id:"));
		USB.println(socketInfo[socketId].id, DEC);
		PRINT_LE910(F("socketInfo.sent:"));
		USB.println(socketInfo[socketId].sent, DEC);
		PRINT_LE910(F("socketInfo.received:"));
		USB.println(socketInfo[socketId].received, DEC);
		PRINT_LE910(F("socketInfo.size:"));
		USB.println(socketInfo[socketId].size, DEC);
		PRINT_LE910(F("socketInfo.ack:"));
		USB.println(socketInfo[socketId].ack, DEC);
	#endif
	
	return 0;	
}



// Public Methods /////////////////////////////////////////////////////////////

/* Function: 	This function inits the LE910 module
 * Return:	0 if OK
 * 			1 for no comunication
 * 			2 if error switching CME errors to numeric response
 * 			3 if error disabling the echo from the module
 * 			4 if error enabling RTC update with network time
 */
uint8_t Wasp4G::ON()
{	
	uint8_t counter;
	uint8_t answer;
	char command_buffer[50];
	
	// set UART1 multiplexer to Socket1
	Utils.setMuxSocket1();
	
	// Set UART
	_uart = UART1;
	_baudrate = LE910_RATE;
	beginUART();
		
	// Power on the module
	digitalWrite(GPRS_PW, LOW);
	delay(500);
	digitalWrite(GPRS_PW, HIGH);
	delay(10000);
	
	
	// Check communication with the module sending a basic AT command
	counter = 15;
	answer = 0;
	while ((counter > 0) && (answer == 0))
	{
		answer = sendCommand("AT\r", LE910_OK, 1000);
		counter--;		
	}
	
	if (answer == 0)
	{
		// No comunication with the module
		// Power off and return an error
		digitalWrite(GPRS_PW, LOW);
		
		// Error code for no communication
		return 1; 
	}
	
	
	// Set Report Mobile Equipment Error (CMEE)
	counter = 3;
	answer = 0;
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[19])));	//AT+CMEE=1\r
	while ((counter > 0) && (answer == 0))
	{
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR, 500);
		counter--;
	}	
	if (answer != 1)
	{
		// Error switching CME errors to numeric response 
		// Power off and return an error
		digitalWrite(GPRS_PW, LOW);
		
		// Error code for error switching CME errors to numeric response
		return 2; 
	}
	
	
	// Disable command echo
	counter = 3;
	answer = 0;
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[20])));	//ATE0\r
	while ((counter > 0) && (answer == 0))
	{
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR, 500);
		counter--;
	}	
	if (answer != 1)
	{
		// Error disabling the echo from the module
		// Power off and return an error
		digitalWrite(GPRS_PW, LOW);
		
		// Error code disabling the echo from the module
		return 3; 
	}
	
	
	// setup NETWORK_UTRAN
	answer = setWirelessNetwork(Wasp4G::NETWORK_3GPP);
		
	return 0;	
}

/* Function: 	This function powers off the LE910 module
 * Return:	 nothing
 */
void Wasp4G::OFF()
{
	// close UART0
	closeUART();
			
	// power down
	pinMode(GPRS_PW,OUTPUT);	
	digitalWrite(GPRS_PW, LOW);
	
}

/* Function: 	This function sets a PIN / PUK code
 * Parameters: code: string with the requested code
 * Return:	0 if OK
 * 			1 if error
 */
uint8_t Wasp4G::enterPIN(char* code)
{	
	return enterPIN(code, NULL);
}

/* Function: 	This function sets a PIN / PUK code
 * Parameters: 
 * 		code: string with the requested code
 * 		new_code: string with the new code (only for SIM PUK or SIM PUK2)
 * Return:	0 if OK, 1 if error
 */
uint8_t Wasp4G::enterPIN(char* code, char* new_code)
{	
	uint8_t answer;
	char command_buffer[50];
	
	// generate command depending on selection
	if (new_code == NULL)
	{
		// AT+CPIN="<code>"\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_PIN[18])), code);
	}
	else
	{
		// AT+CPIN="<code>","<new_code>"\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_PIN[19])), code, new_code);
	}
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check response
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}		
		return 1;
	}
	
	return 0;
}

/* Function: This function returns the result code for a PIN request
 * Return:	
 * 		0 for PIN ready
 * 		1 LE910 is awaiting SIM PIN
 * 		2 LE910 is awaiting SIM PUK
 * 		3 LE910 is awaiting phone-to-SIM card password.
 * 		4 LE910 is awaiting phone-to-very-first-SIM card password.
 * 		5 LE910 is awaiting phone-to-very-first-SIM card unblocking password.
 * 		6 LE910 is awaiting SIM PIN2
 * 		7 LE910 is awaiting SIM PUK2
 * 		8 LE910 is awaiting network personalization password
 * 		9 LE910 is awaiting network personalization unblocking password
 * 		10 LE910 is awaiting network subset personalization password
 * 		11 LE910 is awaiting network subset personalization unblocking password
 * 		12 LE910 is awaiting service provider personalization password
 * 		13 LE910 is awaiting service provider personalization unblocking password
 * 		14 LE910 is awaiting corporate personalization password
 * 		15 LE910 is awaiting corporate personalization unblocking password
 * 		254 if not expected code returned
 * 		255 if command error
 */
uint8_t Wasp4G::checkPIN()
{
	char command_buffer[20];
	char command_answer[20];
	uint8_t answer;
	
	// command: AT+CPIN?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_PIN[0])));
	
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}		
		return 255;
	}
	
	// Seeks a code
	for (int x = 0; x < 17; x++ )
	{
		strcpy_P(command_answer, (char*)pgm_read_word(&(table_PIN[x+1])));
		answer = find( _buffer, _length, command_answer);
		if (answer == 1)
		{
			return x;
		}
	}
	
	return 254;
}



/* Function: 	This function checks connection status
 * Parameters:	time: max allowed time in seconds to connect
 * Return:	0 If the module is connected to the network
 * 			1 not registered, ME is not currently searching for a new operator to register to
 * 			2 not registered, but ME is currently searching for a new operator to register to
 * 			3 registration denied
 * 			4 unknown
 */
uint8_t Wasp4G::checkConnection(uint8_t time)
{	
	uint8_t answer;
	uint8_t status;
	uint8_t value;
	uint32_t previous;
	
	char command_buffer[40];
	char command_answer[20];
	
	answer = 0;
	previous = millis();
	
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[0])));		//AT+CREG?\r
	strcpy_P(command_answer, (char*)pgm_read_word(&(table_4G[1])));		//+CREG: 0,
	
	while ((millis()-previous) < (uint32_t)time*1000)
	{	
		// Sends the command and waits for the answer. The status options in 
		// "+CREG: 0,<status>" response are:
		//	0: not registered, ME is not currently searching a new operator to register to
		//	1: registered, home network
		// 	2: not registered, but ME is currently searching a new operator to register to
		// 	3: registration denied
		//  4: unknown
		// 	5: registered, roaming
		answer = sendCommand(command_buffer, command_answer, 2000);
		
		if (answer == 1)
		{
			status = waitFor("OK",500);
			
			if (status == 1)
			{
				parseUint8(&answer, "\r\n OK");
			}
		}		
		
		if ((answer == 1) || (answer == 5))
		{
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Break condition\n"));
				PRINT_LE910(F("answer:"));
				USB.println(answer,DEC);
			#endif
			break;
		}
		else
		{
			// continue waiting for correct response
			delay(1000);
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();		
	}
	
	if (((answer != 1) && (answer != 5)) || ((millis() - previous) > (unsigned long)(time * 1000)))
	{
		if (answer == 0)
		{
			return answer + 1;
		}
		return answer;
	}
	
	return 0;
	
}


/* Function: 	This function checks EPS Network Registratio Status
 * Parameters:	time: max allowed time in seconds to connect
 * Return:	0 if OK

 */
uint8_t Wasp4G::checkConnectionEPS(uint8_t time)
{	
	uint8_t answer;
	uint8_t status;
	uint32_t previous;	
	char command_buffer[40];
	char command_answer[20];
	
	// init variables
	status = 0;
	answer = 0;
	previous = millis();
	
	//// 1. Generate command
	// "AT+CEREG?\r"
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[41])));
	
	//// 2. Generate answer
	// "+CEREG: 0,"
	strcpy_P(command_answer, (char*)pgm_read_word(&(table_4G[42])));
	
	//// 3. Iterate until status is correct
	while ((status != 1) && (status != 5))
	{	
		// Sends the command and waits for the answer. The status options in 
		// "+CEREG: 0,<status>" response are:
		//	0 - not registered, MT is not currently searching an operator to register to.
		//	1 - registered, home network.
		//	2 - not registered, but MT is currently trying to attach or searching an operator to register to.
		//	3 - registration denied.
		//	4 - unknown (e.g. out of E-UTRAN coverage).
		//	5 - registered, roaming.
		//	6 - registered for "SMS only", home network (not applicable)
		//	7 - registered for "SMS only", roaming (not applicable).
		//	8 - attached for emergency bearer services only (See NOTE 2).
		//	9 - registered for "CSFB not preferred", home network (not applicable).
		//	10 - registered for "CSFB not preferred", roaming (not applicable).

		answer = sendCommand(command_buffer, command_answer, LE910_ERROR_CODE, 2000);
		
		if (answer == 1)
		{
			// get whole response
			status = waitFor(LE910_OK, 500);
			
			if (status == 1)
			{
				parseUint8(&status, "\r\n OK");
				#if DEBUG_WASP4G > 1
					PRINT_LE910(F("----> status:"));
					USB.println(status,DEC);
				#endif
			}
		}		
		
		// check status from response
		if ((status == 1) || (status == 5))
		{
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Break condition\n"));
				PRINT_LE910(F("status:"));
				USB.println(status,DEC);
			#endif
			break;
		}
		else if (status == 2) 
		{
			// continue waiting for correct response
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Continue waiting for correct response\n"));
			#endif			
		}
		
		delay(1000);
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < previous) previous = millis();
			
		// check timeout error
		if ((millis() - previous) > (uint32_t)(time * 1000))
		{
			return status;
		}		
	}
	
	// check bad responses
	if ((status != 1) && 
		(status != 5) && 
		(status != 6) && 
		(status != 7) && 
		(status != 8) && 
		(status != 9) && 
		(status != 10))
	{
		if (status == 0)
		{
			return status + 1;
		}
		
		return status;
	}
	
	return 0;	
}



/* This function manages incoming data from the module
 * Parameters:	wait_time: maximum waiting time in milliseconds
 * Return:	0 if 'OK', 'x' if error
*/
uint8_t	Wasp4G::manageIncomingData(unsigned long wait_time)
{

	uint8_t answer;
	char command_buffer[50];
	char sms_incoming[15];
	char IP_incoming[15];
	
	// set _incomingType to no data received
	_incomingType = 0;
	
	// "+CMTI"
	strcpy_P(sms_incoming, (char*)pgm_read_word(&(table_4G[22])));
	
	// "SRING: "
	strcpy_P(IP_incoming, (char*)pgm_read_word(&(table_4G[23])));

	// Wait for data
	answer = waitFor(sms_incoming, IP_incoming, wait_time);
	
	if (answer == 1)
	{
		// Received data: "+CMTI: <memr>,<index>\r"
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Incoming SMS\n"));
		#endif
		
		// wait for first ','
		waitFor(",", 1000);
		
		// wait for end of response
		answer = waitFor("\r", 2000);
		
		if (answer == 1)
		{	
			// store index
			_smsIndex = atoi((char*) _buffer);
			
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("SMS index:"));
				USB.println(_smsIndex, DEC);
			#endif
			
			// set attribute to SMS data
			_incomingType = LE910_INCOMING_SMS;
			
			return 0;
		}
		else
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error reading SMS index\n"));
			#endif
		}
			
		return 1;
		
	}
	else if (answer == 2)
	{
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("Incoming IP data\n"));
		#endif
		
		answer = waitFor("\r", 2000);		
		if (answer == 1)
		{	
			_socketIndex = atoi((char*) _buffer);
			_socketIndex--;
			
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Socket Index:"));
				USB.println(_socketIndex, DEC);
			#endif
			
			// set attribute to IP data
			_incomingType = LE910_INCOMING_IP;
			
			// wait for get socket status:
			answer = getSocketStatus(_socketIndex);
			
			if (answer == 0)
			{
				#if DEBUG_WASP4G > 1
					PRINT_LE910(F("getSocketStatus OK: "));
					USB.println(socketStatus[_socketIndex].state, DEC);
				#endif
			}
			else
			{		
				#if DEBUG_WASP4G > 0	
					PRINT_LE910(F("getSocketStatus ERROR.\n"));
				#endif
				return 1;
			}

			// check if socket state is a Socket with an incoming connection, 
			// in that case module accepts the connection with the client
			if (socketStatus[_socketIndex].state == 5)
			{			
				// accept connection in command mode
				// AT#SA=<socketId>,1\r
				sprintf_P(command_buffer, (char*)pgm_read_word(&(table_4G[37])), _socketIndex+1);
		
				// send command
				answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
				
				// check answer
				if (answer != 1)
				{
					if (answer == 2)
					{
						getErrorCode();
					}
					return 1;
				}
				
				// get new socket status
				answer = getSocketStatus(_socketIndex);
				
				if (answer == 0)
				{
					#if DEBUG_WASP4G > 1
						PRINT_LE910(F("getSocketStatus OK: "));
						USB.println(socketStatus[_socketIndex].state, DEC);
					#endif
				}
				else
				{		
					#if DEBUG_WASP4G > 0	
						PRINT_LE910(F("getSocketStatus ERROR.\n"));
					#endif
					return 1;
				}
			}
			else
			{
				return 1;
			}			
			
			// return OK
			return 0;
		}
		else
		{			
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error reading SocketId\n"));
			#endif
		}		
	}
	
	// timeout error
	return 3;
}




/* This function manages incoming data from sockets
 * Return:	0 if 'OK', 'x' if error
*/
uint8_t	Wasp4G::manageSockets()
{
	return manageSockets(0);
}


/* This function manages incoming data from sockets
 * Parameters:	wait_time: maximum waiting time in milliseconds
 * Return:	0 if 'OK', 'x' if error
*/
uint8_t	Wasp4G::manageSockets(uint32_t wait_time)
{
	uint8_t answer;
	char command_buffer[50];
	uint32_t previous = millis();
	bool pending_accept = false;
	bool new_accepted = false;

	//// 1. Get socket status and wait until there is 
	//	at least one pending connection to be accepted
	do
	{
		answer = getAllSocketStatus();
		
		if (answer != 0)
		{
			return 1;
		}
		
		for (int profile = 0; profile < 6; profile++)
		{
			if (socketStatus[profile].state == 5)
			{
				pending_accept = true;
			}
		}
		
		// check if there is any pending connection
		if (pending_accept == true)
		{
			break;
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
		delay(500);
		
	} while (((millis() - previous) < wait_time));
	
	
	//// 2. Accept connections if needed
	for (int profile = 0; profile < 6; profile++)
	{
		// check if socket state is a Socket with an incoming connection, 
		// in that case module accepts the connection with the client
		if (socketStatus[profile].state == 5)
		{
			// accept connection in command mode
			// AT#SA=<socketId>,1\r
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_4G[37])), profile+1);
	
			// send command
			answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
			
			// check answer
			if (answer == 1)
			{
				new_accepted = true;
			}
			else
			{
				if (answer == 2)
				{
					getErrorCode();
				}
				return 1;
			}
		}
	}
	
	
	//// 3. Get new socket status
	answer = getAllSocketStatus();
	
	if (answer == 0)
	{
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("getSocketStatus OK\n"));
		#endif
	}
	else
	{		
		#if DEBUG_WASP4G > 0	
			PRINT_LE910(F("getSocketStatus ERROR.\n"));
		#endif
		return 1;
	}
	
	// return OK if new incoming connections have been accepted
	if (new_accepted == true)
	{		
		return 0;
	}
	
	return 1;
}




/* This function sets the parameters to use SMS
 * Return:	0 if OK
 * 			1 if error setting the SMS format
 * 			2 if error selecting the storage
 * 			3 if error setting the incoming SMS indication
*/
uint8_t Wasp4G::configureSMS()
{
	uint8_t answer;
	char command_buffer[50];
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Setting SMS parameters\n"));
	#endif		
		
	// 1. Configure format, storage and indication parameters
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SMS[0])));	//AT+CMGF=1
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR,500);
	if (answer != 1)
	{
		return 1;
	}
	
	/*
	memset(command_buffer,0x00,sizeof(command_buffer));
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SMS[1])));	//AT+CPMS="SM","SM","SM"
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR,500);

	if (answer != 1)
	{
		USB.println("Error CPMS");
		return 2;
	}

	memset(command_buffer,0x00,sizeof(command_buffer));
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SMS[2])));	//AT+CNMI=2,1,0,0,0
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR,500);
	if (answer != 1)
	{
		USB.println("Error CNMI");
		return 3;
	}
	*/
	return 0;
	
}

/* This function sends a SMS
 * Parameters:	phone_number: number to send the SMS
 * 				sms_string: body of the SMS
 * Return:	0 if OK
 * 			1 not registered, ME is not currently searching for a new operator to register to
 * 			2 not registered, but ME is currently searching for a new operator to register to
 * 			3 registration denied
 * 			4 unknown connection error
 * 			5 if error setting the phone number
 * 			6 if error sending the body
*/
uint8_t Wasp4G::sendSMS(char* phone_number, char* sms_string)
{
	char command_buffer[50];
	uint8_t answer;
	
		
	//// 1. Check connection
	answer = checkConnection(60);
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error checking connection\n"));
		#endif
		return answer;
	}	
	
	
	//// 2. Send SMS
	// AT+CMGS="<phone_number>"	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SMS[4])), phone_number);
	
	// send command
	answer = sendCommand(command_buffer, ">");
	
	// check answer
	if (answer != 1)
	{
		printByte(0x1B, 1); //ESC ASCII
		return 5;
	}
	
	printString(sms_string, 1);
	command_buffer[0] = 0x1A;
	command_buffer[1] = '\0';
	answer = sendCommand(command_buffer, LE910_OK);
	if (answer != 1)
	{
		printByte(0x1B, 1); //ESC ASCII
		return 6;
	}
	
	return 0;
	
}



/* Function: 	This function reads the last unread received message
 * Parameters:	none
 * Return:	0 if ok
 * 			1 if error
 */
uint8_t Wasp4G::readNewSMS()
{	
	return readNewSMS(0);
}


/* Function: 	This function reads the last unread received message
 * Parameters:	none
 * Return:	0 if ok
 * 			1 if error
 */
uint8_t Wasp4G::readNewSMS(uint32_t timeout)
{	
	uint8_t answer;
	char command_buffer[50];
	char command_answer[10];
	char *pointer;
	uint32_t previous;
	
	//// 1. Check connection
	answer = checkConnection(60);
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error checking connection\n"));
		#endif
		return answer;
	}
	
	
	//// 3. Read unread message
	// AT+CMGL="REC UNREAD"\r
	memset(command_buffer, 0x00, sizeof(command_buffer));
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[36])));
	
	// "+CMGL: "
	memset(command_answer, 0x00, sizeof(command_answer));
	sprintf_P(command_answer, (char*)pgm_read_word(&(table_4G[39])));
	
	
	// get current time
	previous = millis();
	
	do
	{
		// send command
		answer = sendCommand(command_buffer, command_answer, LE910_ERROR_CODE, LE910_ERROR, LE910_OK, 2000);

		// check answer
		if (answer == 1)
		{
			// read first line
			answer = waitFor("\r\n", 1000);

			// _buffer stores a response like:
			// 	19,"REC UNREAD","+345901000118833","","16/06/20,12:20:20+08"	
			pointer = strtok((char*)_buffer,"\",");
			
			for (int i = 0; i < 5; i++)	
			{	
				// Get SMS index
				if (i == 0)
				{
					_smsIndex = atoi((char*)pointer);
				}
				
				// Get SMS status
				if (i == 1)
				{
					strncpy(_smsStatus, pointer, sizeof(_smsStatus));			
				}
					
				// Get phone number
				if (i == 2)
				{
					strncpy(_smsNumber, pointer, sizeof(_smsNumber));			
				}
				
				// Get date
				if (i == 3)
				{
					strncpy(_smsDate, pointer, sizeof(_smsDate));			
				}
				
				// Get time
				if (i == 4)
				{
					strncpy(_smsTime, pointer, sizeof(_smsTime));		
				}
				
				pointer = strtok(NULL, "\",");	
			}
			
			// Get body
			waitFor("\r\n\r\nOK", 1000);
			
			// update buffer length
			_length -= strlen("\r\n\r\nOK");
			_buffer[_length] = 0x00;
			
			return 0;
		}
		else if (answer == 4)
		{
			// LE910_OK
			// do nothing because no incoming SMS was received
		}		
		else
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting response\n")); 
			#endif
			if (answer == 2)
			{
				getErrorCode();
				#if DEBUG_WASP4G > 0
					printErrorCode();
				#endif
			}
			return 1;
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
	} while (millis()-previous < timeout);
	
	return 1;
}


/* This function reads a SMS
 * Parameters:	sms_index: index of the SMS into the memory
 * 				sms_buffer: buffer to store the SMS
 * Return:	0 if OK
 * 			1 if error getting the SMS
*/
uint8_t Wasp4G::readSMS(uint8_t sms_index)
{	
	char command_buffer[40];
	char command_answer[15];
	uint8_t answer;
	char* pointer;
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Reading SMS from index "));
		USB.println(sms_index, DEC);
	#endif		
		
	//// 1. Generate command request
	// AT+CMGR=<sms_index>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SMS[3])), sms_index);
	
	//// 2. Generate expected answer
	// +CMGR: 
	memset(command_answer, 0x00, sizeof(command_answer));
	sprintf_P(command_answer,(char*)pgm_read_word(&(table_4G[40])));

	// send command
	answer = sendCommand(command_buffer, command_answer, LE910_ERROR_CODE, LE910_ERROR, LE910_OK, 5000);

	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}		
		return 1;
	}

	// read first line
	answer = waitFor("\r\n", 1000);

	// _buffer stores a response like:
	// 	"REC READ","+34666666666","","16/06/20,10:12:34+08"
	
	pointer = strtok((char*)_buffer,"\",");
	
	for (int i = 0; i < 4; i++)	
	{	
		// Get SMS status
		if (i == 0)
		{
			strncpy(_smsStatus, pointer, sizeof(_smsStatus));			
		}		
		// Get phone number
		if (i == 1)
		{
			strncpy(_smsNumber, pointer, sizeof(_smsNumber));			
		}
		
		// Get date
		if (i == 2)
		{
			strncpy(_smsDate, pointer, sizeof(_smsDate));			
		}
		
		// Get time
		if (i == 3)
		{
			strncpy(_smsTime, pointer, sizeof(_smsTime));		
		}
		
		pointer = strtok(NULL, "\",");	
	}
	
	// Get body
	waitFor("\r\n\r\nOK", 1000);
	
	// update buffer length
	_length -= strlen("\r\n\r\nOK");
	_buffer[_length] = 0x00;	

	return 0;	
}


/* This function deletes a SMS
 * Parameters:	sms_index: index of the SMS into the memory
 * Return:	0 if OK
 * 			1 if error deleting the SMS
*/
uint8_t Wasp4G::deleteSMS(uint8_t sms_index)
{
	return deleteSMS(sms_index, SMS_DELETE_MESSAGE);	
}



/* This function deletes a SMS
 * Parameters:	
 * 	sms_index: 	index of the SMS into the memory
 * 	del_flag: 	
 * 		0: 	Delete message specified in <index>
 * 		1: 	Delete all read messages from <memr> storage, leaving unread messages 
 * 			and stored mobile originated messages (whether sent or not) untouched
 * 		2: 	Delete all read messages from <memr> storage and sent mobile originated
 * 			messages, leaving unread messages and unsent mobile originated messages untouched
 *  	3: 	Delete all read messages from <memr> storage, sent and unsent mobile
 * 			originated messages, leaving unread messages untouched
 * 		4: 	Delete all messages from <memr> storage
 * Return:	0 if OK
 * 			1 if error deleting the SMS
*/
uint8_t Wasp4G::deleteSMS(uint8_t sms_index, uint8_t del_flag)
{	
	char command_buffer[20];
	uint8_t answer;
	
	#if DEBUG_WASP4G > 0
		PRINT_LE910(F("Deleting SMS from index: "));
		USB.println(sms_index, DEC);
	#endif		
	
	// AT+CMGD=<sms_index>,<del_flag>\r
	sprintf_P(command_buffer,(char*)pgm_read_word(&(table_SMS[6])), sms_index, del_flag);

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}		
		return 1;
	}
	
	return 0;	
}




/* Function: 	This function performs a HTTP request
 * Parameters:	
 * 		method: selected HTTP method:	Wasp4G::HTTP_GET
 * 										Wasp4G::HTTP_HEAD
 * 										Wasp4G::HTTP_DELETE
 *		url: host name or IP address of the server
 *		port: server port
 *		resource: parameter indicating the HTTP resource, object of the	request				
 * Return:	'0' if OK
 * 			'x' if error. See http()
 */
uint8_t Wasp4G::http(uint8_t method, 
						char* url,
						uint16_t port,
						char* resource)
{
	return http(method,
				url,
				port,
				resource,
				NULL);
}


/* Function: 	This function performs a HTTP request
 * Parameters:	
 * 		method: selected HTTP method:	Wasp4G::HTTP_GET
 * 										Wasp4G::HTTP_HEAD
 * 										Wasp4G::HTTP_DELETE
 * 										Wasp4G::HTTP_POST
 * 										Wasp4G::HTTP_PUT
 * 										Wasp4G::HTTP_POST_FRAME
 *		url: host name or IP address of the server
 *		port: server port
 *		resource: parameter indicating the HTTP resource, object of the	request
 *		data: data to send in HTTP method
 * 
 * Return:	0 if OK
 * 			1 not registered, ME is not currently searching for a new operator to register to
 * 			2 not registered, but ME is currently searching for a new operator to register to
 * 			3 registration denied
 * 			4 unknown
 * 			6 not registered, ME is not currently searching for a new operator to register to
 * 			8 not registered, but ME is currently searching for a new operator to register to
 * 			9 registration denied
 * 			10 unknown
 * 			12 if error setting APN
 * 			13 if error setting login
 * 			14 if error setting password
 * 			15 if error activating GPRS connection
 * 			16 if error setting URL and port
 * 			17 if error sending the request
 * 			18 if error sending POST / PUT data
 * 			19 if wrong method has been selected
 * 			20 if timeout waiting the URC 
 * 			21 if error reading the URC
 * 			22 if error reading the HTTP status
 * 			23 if error reading the HTTP data length
 * 			24 if error reading the HTTP data
 * 			25 if error code from 4G module while waiting for HTTP response
 * 			26 if timeout waiting for HTTP response
 * 			27 if HTTP response data length is zero
 */
uint8_t Wasp4G::http(	uint8_t method, 
						char* url,
						uint16_t port,
						char* resource,
						char* data)
{
	uint8_t answer;
	int16_t http_data;
	
	// 1. Check data connection
	answer = checkDataConnection(60);	
	if (answer != 0)
	{
		return answer;	// 1 to 15 error codes
	}
	
	// 2. Configure parameters	and send the request
	answer = httpRequest(method, url, port, resource, data);
	if (answer != 0)
	{
		return answer+15;	// 16 to 19 error codes
	}
	
	// 3. Wait for the response
	answer = httpWaitResponse(LE910_HTTP_TIMEOUT);	
	if (answer != 0)
	{
		return answer+19;	// 20 to 27 error codes
	}
	
	return 0;	
}






/* Function: 	This function performs a HTTP GET request to the Meshlium device
 * 				connected in port and host specified as input
 * Parameters:	 											
 *				url: host name or IP address of the server
 *				port: server port
 *				resource: parameter indicating the HTTP resource, object of the
 * 					request
 *				POST_PUT_data: data to send in POST/PUT method
 *				POST_PUT_length: data length to send in POST/PUT method
 * Return:	0 if OK
 * 			1 not registered, ME is not currently searching for a new operator to register to
 * 			2 not registered, but ME is currently searching for a new operator to register to
 * 			3 registration denied
 * 			4 unknown
 * 			6 not registered, ME is not currently searching for a new operator to register to
 * 			8 not registered, but ME is currently searching for a new operator to register to
 * 			9 registration denied
 * 			10 unknown
 * 			12 if error setting APN
 * 			13 if error setting login
 * 			14 if error setting password
 * 			15 if error activating GPRS connection
 * 			16 if error setting URL and port
 * 			17 if error sending the request
 * 			18 if error sending POST / PUT data
 * 			19 if wrong method has been selected
 * 			20 if timeout waiting the URC 
 * 			21 if error reading the URC
 * 			22 if error reading the HTTP status
 * 			23 if error reading the HTTP data length
 * 			24 if error reading the HTTP data
 * 			25 if error code from 4G module while waiting for HTTP response
 * 			26 if timeout waiting for HTTP response
 * 			27 if HTTP response data length is zero
 */
uint8_t Wasp4G::sendFrameToMeshlium(char* url,
									uint16_t port,
									uint8_t* data,
									uint16_t length)
{
	uint8_t answer;
	int16_t http_data;
	
	// 1. Check data connection
	answer = checkDataConnection(60);	
	if (answer != 0)
	{
		return answer;	// 1 to 15 error codes
	}
	
	// 2. Configure parameters	and send the request
	answer = httpRequest(Wasp4G::HTTP_POST_FRAME, url, port, NULL, data, length);
	if (answer != 0)
	{
		return answer+15;	// 16 to 19 error codes
	}
	
	// 3. Wait for the response
	answer = httpWaitResponse(LE910_HTTP_TIMEOUT);	
	if (answer != 0)
	{
		return answer+19;	// 20 to 27 error codes
	}
	
	return 0;		
}




/* Function: 	This function configures FTP parameters and opens the connection
 * Parameters:	server: address of FTP server
 *				port: port of FTP server
 *				username: authentication user identification string for FTP
 *				password: authentication password for FTP
 * Return:	0 if OK
 * 			1 not registered, ME is not currently searching for a new operator to register to
 * 			2 not registered, but ME is currently searching for a new operator to register to
 * 			3 registration denied
 * 			4 unknown
 * 			6 not registered, ME is not currently searching for a new operator to register to
 * 			8 not registered, but ME is currently searching for a new operator to register to
 * 			9 registration denied
 * 			10 unknown
 * 			12 if error setting APN
 * 			13 if error setting login
 * 			14 if error setting password
 * 			15 if error activating GPRS connection
 * 			16 if error opening the FTP connection
 * 			17 if error setting the transfer type
 */
uint8_t Wasp4G::ftpOpenSession(	char* server,
								uint16_t port,
								char* username,
								char* password)
{	
	uint8_t answer;
	char command_buffer[100];

	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Checking connection\n"));
	#endif
	
	// 1. Check data connection
	answer = checkDataConnection(60);
	if (answer != 0)
	{
		return answer;	// 1 to 15 error codes
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Opening FTP session\n"));
	#endif
		
	// 2. Configure FTP parameters and open the connection
	// AT#FTPOPEN="<server>:<port>","<username>","<password>",1\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FTP[0])),
			server,
			port,
			username,
			password);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, LE910_FTP_CONF_TIMEOUT);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif	
		}
		return 16;
	}
	
	
	// 3. Set binary transfer. Once connected we can call the AT#FTPTYPE command
	// AT#FTPTYPE=0\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_FTP[4])));
	
	// mandatory delay
	delay(2000);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif	
		}
		
		return 17;
	}	

	
	return 0;
}



/* Function: 	This function closes the FTP connection
 * Return:	0 if OK
 * 			1 if error
 */
uint8_t Wasp4G::ftpCloseSession()
{	
	char command_buffer[50];
	uint8_t answer;

	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Closing FTP session\n"));
	#endif
	
	delay(1000);
	
	//AT#FTPCLOSE\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_FTP[1])));

	// First attempt
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 10000);
	
	if (answer == 1)
	{
		// ok
		return 0;
	}
	else if (answer == 2)
	{
		// error code
		getErrorCode();
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error code:"));
			USB.println((char*)_buffer);
		#endif
		return 1;
	}
		
	// Second attempt
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 1000);
	
	if (answer == 1)
	{
		// ok
		return 0;
	}
	else if (answer == 2)
	{
		// error code
		getErrorCode();
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error code:"));
			USB.println((char*)_buffer);
		#endif
		return 1;
	}
	else
	{
		return 2;
	}	
}



/* Function: 	This function requests the current working directory in FTP server
 * 
 * Return:	'0' if OK
 * 			'x' otherwise
 */
uint8_t Wasp4G::ftpGetWorkingDirectory()
{		
	uint8_t answer;
	char command_buffer[100];
	char* pointer;
	
	// AT#FTPPWD\r
	memset(command_buffer, 0x00, sizeof(command_buffer));
	strcpy_P(command_buffer,(char*)pgm_read_word(&(table_FTP[15])));

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 15000);

	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("_buffer:")); 
		USB.println((char*)_buffer);
	#endif

	if (answer != 1)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error showing Working Directory\n")); 
		#endif
		
		if (answer == 2)
		{
			getErrorCode();
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		return 1;
	}	
	
	// parse response similar to: "\r\n#FTPPWD: 257 "/""\r\n
	// so the working directory is in the second token:
	answer = parseString(_ftpWorkingDirectory, sizeof(_ftpWorkingDirectory), "\"", 2);
	
	if (answer != 0)
	{
		return 2;
	}	

	return 0;	
}




/* Function: 	This function changes the working directory of the FTP session
 * Parameters:	dirname: destiny directory in FTP server
 * Return:	'0' if OK
 * 			'x' otherwise
 */
uint8_t Wasp4G::ftpChangeWorkingDirectory(char* dirname)
{		
	uint8_t answer;
	char command_buffer[100];	
	
	// AT#FTPCWD="dirname"\r
	memset(command_buffer, 0x00, sizeof(command_buffer));
	sprintf_P(command_buffer,(char*)pgm_read_word(&(table_FTP[17])), dirname);

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 15000);

	#if DEBUG_WASP4G > 0
		PRINT_LE910(F("_buffer:")); 
		USB.println((char*)_buffer);
	#endif

	if (answer != 1)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error changing Working Directory\n")); 
		#endif
		
		if (answer == 2)
		{
			getErrorCode();
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		return 1;
	}
	
	// update attribute if OK
	memset(_ftpWorkingDirectory, 0x00, sizeof(_ftpWorkingDirectory));
	strncpy(_ftpWorkingDirectory, "/", 1);
	strncat(_ftpWorkingDirectory, dirname, sizeof(_ftpWorkingDirectory)-2);

	return 0;	
}


/* Function: 	This function uses DELETE to delete a file to in the current 
 * 				working directory of the FTP server
 * Parameters:	ftp_file: file to delete in FTP session
 * Return:	'0' if OK
 * 			'x' otherwise
 */
uint8_t Wasp4G::ftpDelete(char* ftp_file)
{		
	uint8_t answer;
	char command_buffer[100];	
	
	// AT#FTPDELE="<ftp_file>"\r
	memset(command_buffer, 0x00, sizeof(command_buffer));
	sprintf_P(command_buffer,(char*)pgm_read_word(&(table_FTP[14])),ftp_file);

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 15000);

	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("_buffer:")); 
		USB.println((char*)_buffer);
	#endif

	if (answer != 1)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error deleting file\n")); 
		#endif
		
		if (answer == 2)
		{
			getErrorCode();
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		return 1;
	}

	return 0;	
}


/* Function: 	This function uses PUT to send a file to a FTP server
 * Parameters:	ftp_file: destiny file
 *				sd_file: origin file
 * Return:	0 if OK
 * 			1 if no SD present
 * 			2 if file does not exist
 * 			3 if error opening the file
 * 			4 if error setting the pointer of the file
 * 			5 if error getting the file size
 * 			6 if error opening the PUT connection
 * 			7 if error exiting from the data mode
 * 			8 if error sending data
 */
uint8_t Wasp4G::ftpUpload( char* ftp_file, char* sd_file)
{
	
	uint8_t answer;
	char command_answer[20];
	char command_buffer[512];
	int32_t file_size = 0;
	int nBytes = 0;
	uint8_t error_counter = 5;
	
	//// 1. Delete file in FTP server if exists
	ftpDelete(ftp_file);
	
	// define file variable
	SdFile file;	
	
	// get current state of SD card power supply
	bool sd_state = SPI.isSD;
	
	// switch SD card ON
	SD.ON();
	
	// go to Root directory
	SD.goRoot();
	
	// check if the card is there or not
	if (!SD.isSD())
	{	
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error: SD not present\n"));
		#endif 
		if (sd_state == false)
		{
			SD.OFF();			
		}
		return 1;
	}
	
	// Delete file in the case it exists
	if (!SD.isFile(sd_file))
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error: file does not exist\n"));
		#endif
		if (sd_state == false)
		{
			SD.OFF();			
		}
		return 2;		
	}
	
	// search file in current working directory and open it 
	// exit if error and modify the general flag with FILE_OPEN_ERROR
	if (!SD.openFile((char*)sd_file, &file, O_RDONLY))
	{
		// SD error		
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error: opening file\n"));
		#endif	
		if (sd_state == false)
		{
			SD.OFF();			
		}
		return 3;
	}

	// set pointer to the beginning of the file
	if (!file.seekSet(0))	
	{
		// SD error		
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error: setting initial offset in file\n"));
		#endif	
		if (sd_state == false)
		{
			SD.OFF();			
		}	
		return 4;
	}
		
	// get file size	
	file_size = SD.getFileSize(sd_file);
	if (file_size < 0)
	{	
		// Return the SD to the original state
		if (sd_state == 0)
		{
			SD.OFF();
		}
		
		return 5;		
	}
		
	// mandatory delay so the module works ok
	delay(1000);
	
	// 5. Open the PUT connection
	// AT#FTPPUT=<ftp_file>,0\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FTP[2])), ftp_file);
	
	// send command	
	answer = sendCommand(command_buffer, "CONNECT", "NO CARRIER", 15000);
	if (answer != 1)
	{			
		// Close file
		file.close();
		
		// Return the SD to the original state
		if (sd_state == 0)
		{
			SD.OFF();
		}
		
		return 6;
	}
	
	#if DEBUG_WASP4G > 0
		PRINT_LE910(F("File size: "));
		USB.println(file_size, DEC);	
		PRINT_LE910(F("error_counter: "));
		USB.println(error_counter, DEC);
	#endif
	
	// 6. Send data to the server
	while ((file_size > 0) && (error_counter > 0))
	{
		// 6a. Read data from SD
		nBytes = file.read(command_buffer, 500);
		
		// 6b. Send the data if no errors
		if (nBytes == -1)
		{
			// SD error		
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error reading the file\n")); 
			#endif
			error_counter--;
		}
		else
		{
			for (int i = 0; i < nBytes; i++)
			{
				printByte(command_buffer[i], 1);
			}
			
			file_size -= nBytes; 
		}
		
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Remains: "));
			USB.print(file_size);
			USB.println(F("Bytes"));
		#endif
	}
		
	// 7. Close file
	file.close();
	
	// 8. Return the SD to the original state
	if (sd_state == 0)
	{
		SD.OFF();
	}
	
	// 9. Exit from data mode
	delay(1000);
	
	// "+++"
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_FTP[11])));
	// "NO CARRIER"
	strcpy_P(command_answer, (char*)pgm_read_word(&(table_FTP[12])));
	
	answer = sendCommand(command_buffer, command_answer, LE910_ERROR_CODE, 15000);
	if (answer != 1)
	{
		return 7;
	}
	
	if (error_counter == 0)
	{ 
		return 8;
	}
		
	return 0;
}



/* Function: 	This function uses GET to read a file from a FTP server
 * Parameters:	sd_file: destiny file
 *				ftp_file: origin file
 * Return:	'0' if OK
 * 			'x' if error
 */
uint8_t Wasp4G::ftpDownload( char* sd_file, char* ftp_file)
{	
	uint8_t error;
	uint8_t answer;
	char command_buffer[50];
	char command_answer[50];
	bool sd_state;
	uint32_t server_filesize = 0;
	uint32_t sd_filesize = 0;
	int32_t packet_size = LE910_MAX_DL_PAYLOAD;
	int nBytes = 0;
	uint8_t error_counter = 5;
	int data_available;
	uint32_t prev;
	
	// init error code variable
	_errorCode = 0;
	
	delay(2000);
	
	/// 1. Get filesize in FTP server
	error = ftpFileSize(ftp_file);
    
	if (error == 0)
	{
		server_filesize = _filesize;	
		
		if (server_filesize == 0)
		{
			USB.println();
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Server file size is zero\n")); 
			#endif
			return 1;
		}
		
		
		if (server_filesize < LE910_MAX_DL_PAYLOAD)
		{
			packet_size = server_filesize;
		}
	}
	else
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error retrieving file size\n")); 
		#endif
		return 2;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("File size in FTP: "));
		USB.println(server_filesize, DEC);
	#endif
	
	
	
	/// 2. Prepare SD card for downloading
	
	// define file variable
	SdFile file;
	
	// get current state of SD card power supply
	sd_state = SPI.isSD;
	
	// switch SD card ON
	SD.ON();
	
	// go to Root directory
	SD.goRoot();
	
	// check if the card is there or not
	if (!SD.isSD())
	{	
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("SD not present\n"));  
		#endif 
		if (sd_state == false)
		{
			SD.OFF();			
		}		
		return 3;
	}
	
	// Delete file in the case it exists
	if (SD.isFile(sd_file) == 1)
	{
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("delete file\n")); 
		#endif
		SD.del(sd_file);
	}
	
	// Creates a file in that folder
	if (!SD.create(sd_file))
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("file not created\n"));  
		#endif 
		if (sd_state == false)
		{
			SD.OFF();			
		}
		
		return 4;
	}

	// search file in current directory and open it in write mode
	if (!SD.openFile(sd_file, &file, O_READ | O_WRITE | O_SYNC))
	{	
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("error opening file\n")); 
		#endif
		if (sd_state == false)
		{
			SD.OFF();			
		}
		
		return 5;
	}
        
    // select correct SPI slave for the rest of the function
	SPI.setSPISlave(SD_SELECT);

	// jump over zero 'offset'
	if (!file.seekSet(0))
	{	
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("setting file offset\n"));  
		#endif
		file.close();
		if (sd_state == false)
		{
			SD.OFF();			
		}		
	
		return 6;
	}
	
	/// 3. Open the GET connection
	
	// AT#FTPGETPKT="<ftp_file>"\r
	memset(command_buffer,0x00,sizeof(command_buffer));
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FTP[3])),ftp_file);

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, LE910_FTP_TIMEOUT);

	if (answer != 1)
	{	
		if (answer == 2)
		{
			getErrorCode();
		}		

		// Close file
		file.close();
		
		// Return the SD to the original state
		if (sd_state == 0)
		{
			SD.OFF();
		}
		
		return 7;
	}

	// calculate delay for retrieving packets depending on file size
	uint32_t delay_ms;
	
	if (_filesize > 50000)
	{
		delay_ms = 700;
	}
	else if (_filesize > 25000)
	{
		delay_ms = _filesize/100;
	}
	else
	{
		delay_ms = _filesize/160;
	}
	
	#if DEBUG_WASP4G > 0
		PRINT_LE910(F("Set delay_ms = "));
		USB.println(delay_ms);
	#endif

	setDelay(delay_ms);
	
	// Note: Please commnent this line if your SIM card does not 
	// permit good data transmission
	setDelay(0);

	delay(500);
	
	// "#FTPRECV: "
	sprintf_P(command_answer, (char*)pgm_read_word(&(table_FTP[13])));

	/// 4. Read data from the module
	while ((server_filesize > 0) && (error_counter > 0))
	{
		if (server_filesize > LE910_MAX_DL_PAYLOAD)
		{
			packet_size = LE910_MAX_DL_PAYLOAD;
		}
		else
		{
			packet_size = server_filesize;
		}
		
		//// 6b Request data
		// AT#FTPRECV=<packet_size>\r
		memset(command_buffer, 0x00, sizeof(command_buffer));
		sprintf_P(command_buffer,(char*)pgm_read_word(&(table_FTP[6])),packet_size);
		
		// send command
		answer = sendCommand(command_buffer, command_answer, LE910_ERROR_CODE, LE910_ERROR, 2000);

		if (answer == 2)
		{
			getErrorCode();
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif		
			setDelay(DEF_COMMAND_DELAY);
			return 8;
		}
		else if (answer != 1)
		{	
			error_counter--;
			// Error could be that no data in the buffer, wait one second
			delay(1000);
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting data\n"));
			#endif
		}
		else
		{
			//// 6c Read the number of bytes of the packet
			waitFor("\r\n", 100);
			error = parseInt32(&packet_size,"\r\n");

			if (error == 1)
			{				
				#if DEBUG_WASP4G > 0
					PRINT_LE910(F("Error getting packet size\n"));
				#endif
				file.close();
				
				if (sd_state == false)
				{
					SD.OFF();
				}
				setDelay(DEF_COMMAND_DELAY);
				return 9;
			}
			
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Packet size: "));
				USB.println(packet_size);
			#endif
			
			// Read the data from the UART and stores in _buffer		
			nBytes = readBuffer(packet_size);

			if (nBytes != packet_size)
			{
				#if DEBUG_WASP4G > 0
					PRINT_LE910(F("Error in packet size mismatch\n"));
				#endif
				file.close();
				
				if (sd_state == false)
				{
					SD.OFF();
				}
				setDelay(DEF_COMMAND_DELAY);
				return 10;
			}
		
			// Write the data into the SD			
			if (file.write(_buffer, nBytes) != (int)nBytes)
			{				
				#if DEBUG_WASP4G > 0
					PRINT_LE910(F("Writing SD error"));
				#endif
				file.close();
				
				if (sd_state == false)
				{
					SD.OFF();
				}
				setDelay(DEF_COMMAND_DELAY);
				return 11;    
			}

			// decrement filesize
			server_filesize -= nBytes;
			
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Remaining server_filesize: "));
				USB.println(server_filesize);
			#endif		
		}
	}
	
	// Close file
	file.close();
	
	// check error counter
	if (error_counter == 0)
	{ 
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error counter=0\n"));
		#endif
		return 12;
	}	
	
	// save the actual server file size
	server_filesize = _filesize;
	
	// update file size in SD card
	sd_filesize = SD.getFileSize(sd_file);
	
	// check size mismatch
	if (sd_filesize != server_filesize)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("File size mismatch\n"));
			PRINT_LE910(F("sd_filesize:"));
			USB.println(sd_filesize);
			PRINT_LE910(F("server_filesize:"));
			USB.println(server_filesize);
		#endif
		setDelay(DEF_COMMAND_DELAY);
		return 13;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("DOWNLOAD OK\n"));
		PRINT_LE910(F("sd_filesize:"));
		USB.println(sd_filesize,DEC);
		PRINT_LE910(F("server_filesize:"));
		USB.println(server_filesize,DEC);
	#endif
	
	
	// 8. Return the SD to the original state
	if (sd_state == false)
	{
		SD.OFF();
	}
	
	setDelay(DEF_COMMAND_DELAY);
	
	return 0;
}




/* Function: 	This function configures and open a socket
 * Parameters:	socketId: number of the socket Id
 * 				protocol: 0 for TCP and 1 for UDP
 * 				remote_IP: address of the remote host (IPv6 allowed)
 * 				remote_port: remote host port to contact
 * Return:		0 if OK; 'x' if error (see below)
 */
uint8_t Wasp4G::openSocketClient(uint8_t socketId,
								bool protocol,
								char* remote_IP,
								uint16_t remote_port)
{
	return openSocketClient(socketId,
							protocol,
							remote_IP,
							remote_port,
							0, 
							0);
}

/* Function: 	This function configures and opens a socket
 * Parameters:	socketId: number of the socket Id
 * 				protocol: 0 for TCP and 1 for UDP
 * 				remote_IP: address of the remote host (IPv6 allowed)
 * 				remote_port: remote host port to contact
 * 				local_port: UDP connections local port
 * Return:		0 if OK; 'x' if error (see below)
 */
uint8_t Wasp4G::openSocketClient(uint8_t socketId,
								bool protocol,
								char* remote_IP,
								uint16_t remote_port,
								uint16_t local_port)
{
	return openSocketClient(socketId,
							protocol,
							remote_IP,
							remote_port,
							local_port,
							0);
}


/* Function: 	This function configures and opens a socket
 * Parameters:	socketId: number of the socket Id (from 1 to 6)
 * 				protocol: 0 for TCP and 1 for UDP
 * 				remote_IP: address of the remote host (IPv6 allowed)
 * 				remote_port: remote host port to contact
 * 				local_port: UDP connections local port
 * 				keep_alive: From 0 (disabled) to 240 minutes
 * Return:	
 * 		0 if OK
 * 		1 not registered, ME is not currently searching for a new operator to register to
 * 		2 not registered, but ME is currently searching for a new operator to register to
 * 		3 registration denied
 * 		4 unknown
 * 		6 not registered, ME is not currently searching for a new operator to register to
 * 		8 not registered, but ME is currently searching for a new operator to register to
 * 		9 registration denied
 * 		10 unknown
 * 		12 if error setting APN
 * 		13 if error setting login
 * 		14 if error setting password
 * 		15 if error activating GPRS connection
 * 		16 error getting socket status
 * 		17 Socket with an active data transfer connection
 * 		18 Socket suspended
 * 		19 Socket suspended with pending data
 * 		20 Socket listening
 * 		21 Socket with an incoming connection. Waiting for the user accept or shutdown command
 * 		22 Socket in opening process. The socket is not in Closed state but 
 * 			still not in Active or Suspended or Suspended with pending data state
 * 		23 if error in Socket Configuration
 * 		24 if error in Socket Configuration Extended 3
 * 		25 if error sending the open command
 * 		26 if timeout opening the socket
 */
uint8_t Wasp4G::openSocketClient(uint8_t socketId,
								bool protocol,
								char* remote_IP,
								uint16_t remote_port,
								uint16_t local_port,
								uint8_t keep_alive)
{
	uint8_t error;
	uint8_t answer;
	char command_buffer[100];
	
	
	//// 1. Check data connection
	answer = checkDataConnection(60);
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error checking data connection\n"));
		#endif
		return answer;	// 1 to 15 error codes
	}
	
	
	//// 2. Check socket status	
	answer = getSocketStatus(socketId);
	
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error checking socket status\n"));
		#endif
		return 16;
	}
	
	// check if socket is not closed before opening it and return error code
	if (socketStatus[socketId].state != 0)
	{
		return socketStatus[socketId].state+16;	// 17 to 22 error codes
	}
	
	
	//// 3. Socket Configuration Extended
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Configuring connection\n"));
	#endif
	

	// AT#SCFGEXT=<socketId>,0,0,<keep_alive>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[3])), 
				socketId+1, 
				0, 
				0, 
				keep_alive);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		
		return 23;
	}
	
	
	//// 4. Socket Configuration Extended 3
	// AT#SCFGEXT3=<socketId>,1\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[5])), socketId+1);
	
	// send command	
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		return 24;
	}
	
	
	//// 5. Socket Dial
	#if DEBUG_WASP4G > 0
		PRINT_LE910(F("Opening the socket\n"));
	#endif
	
	if (local_port == 0)
	{
		local_port = remote_port;
	}
	
	// AT#SD=<socketId>,<protocol>,<remote_port>,"<remote_IP>",0,<local_port>,1\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[6])), 
			socketId+1,
			protocol,
			remote_port,
			remote_IP,
			local_port);
	
	// send command	
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer 
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		return 25;
	}
	
	
	//// 6. Wait for opening the socket	
	uint32_t previous = millis();	

	do
	{
		// get socket status
		answer = getSocketStatus(socketId);
		
		if (answer == 0)
		{
			if (socketStatus[socketId].state == 2)
			{
				// Socket suspended
				return 0;
			}
			else if (socketStatus[socketId].state == 3)
			{
				// Socket suspended with pending data
				return 0;
			}
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
		delay(1000);
		
	} while (((millis() - previous) < LE910_IP_TIMEOUT));
	
	
	return 26;
}





/* Function: 	This function opens a socket listening for an incoming 
 * 				connection on a specified port
 * Parameters:	socketId: number of the socket Id (from 1 to 6)
 * 				protocol: 0 for TCP_SERVER and 1 for UDP_SERVER
 * 				local_port: TCP/UDP local port
 * Return:		'0' if OK; 'x' if error
 */
uint8_t Wasp4G::openSocketServer(uint8_t socketId,
								bool protocol,
								uint16_t local_port)
{
	return openSocketServer(socketId, protocol, local_port, 0);
}


/* Function: 	This function opens a socket listening for an incoming 
 * 				connection on a specified port
 * Parameters:	socketId: number of the socket Id (from 1 to 6)
 * 				protocol: 0 for TCP_SERVER and 1 for UDP_SERVER
 * 				local_port: TCP/UDP local port
 * 				keep_alive: From 0 (disabled) to 240 minutes
 * Return:		'0' if OK; 'x' if error
 */
uint8_t Wasp4G::openSocketServer(uint8_t socketId,
								bool protocol,
								uint16_t local_port,
								uint8_t keep_alive)
{
	uint8_t error;
	uint8_t answer;
	char command_buffer[100];
	
	
	//// 1. Check data connection
	answer = checkDataConnection(60);
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error checking data connection\n"));
		#endif
		return answer;	// 1 to 15 error codes
	}
	
	
	//// 2. Check socket status	
	answer = getSocketStatus(socketId);
	
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error checking socket status\n"));
		#endif
		return 16;
	}
	
	//// 3. Socket Configuration Extended
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Configuring connection\n"));
	#endif
	
	// AT#SCFGEXT=<socketId>,0,0,<keep_alive>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[3])), 
				socketId+1, 
				0,
				0,
				keep_alive);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		
		return 17;
	}
	
	
	//// 4. Socket Listen TCP / Socket Listen UDP
	#if DEBUG_WASP4G > 0
		PRINT_LE910(F("Opening the socket listen\n"));
	#endif
	
	if (protocol == Wasp4G::TCP)
	{
		// AT#SL=<socketId>,1,<local_port>,255\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[29])), 
				socketId+1,
				1,
				local_port,
				255);
	}
	else if (protocol == Wasp4G::UDP)
	{
		// AT#SLUDP=<socketId>,1,<local_port>\r		
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[30])), 
				socketId+1,
				1,
				local_port);
	}
	else
	{
		return 18;
	}
	
	// send command	
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer 
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		return 19;
	}
		
	return 0;	
}





/* Function: 	This function configures and opens a socket SSL
 * Parameters:	
 * 		socketId: Secure Socket Identifier (must be 1 because until now SSL block manage only 1 socket)
 * 		remote_IP: address of the remote host (IPv6 allowed)
 * 		remote_port: remote host port to contact
 * Return:	
 * 		0 if OK
 * 		1 not registered, ME is not currently searching for a new operator to register to
 * 		2 not registered, but ME is currently searching for a new operator to register to
 * 		3 registration denied
 * 		4 unknown
 * 		6 not registered, ME is not currently searching for a new operator to register to
 * 		8 not registered, but ME is currently searching for a new operator to register to
 * 		9 registration denied
 * 		10 unknown
 * 		12 if error setting APN
 * 		13 if error setting login
 * 		14 if error setting password
 * 		15 if error activating GPRS connection
 * 		16 Socket with an active data transfer connection
 * 		17 Socket suspended
 * 		18 Socket suspended with pending data
 * 		19 Socket listening
 * 		20 Socket with an incoming connection. Waiting for the user accept or shutdown command
 * 		21 Socket in opening process. The socket is not in Closed state but 
 * 			still not in Active or Suspended or Suspended with pending data state
 * 		22 if error reading the status of the socket
 * 		23 if error configuring of the socket
 * 		24 if error configuring of the socket
 * 		25 if error sending the open command
 * 		26 if timeout opening the socket
 * 		27 if timeout opening the socket
 */
uint8_t Wasp4G::openSocketSSL(	uint8_t socketId,
								char* remote_IP,
								uint16_t remote_port)
{
	uint8_t answer;
	char command_buffer[100];
		
		
	//// 1. Enable a SSL socket
	// "AT#SSLEN=<socketId>,1\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[33])), socketId+1, 1);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
		
	// check response
	// If the socket has already been enabled for SSL, 
	// the module returns error, so we continue if error
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
	}
	
	
	//// 2. Check data connection
	answer = checkDataConnection(60);
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error in checkDataConnection()\n"));
		#endif
		return answer;	// 1 to 15 error codes
	}
	

	//// 3. Check socket status	
	answer = getSocketStatusSSL(socketId);
	
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error in getSocketStatusSSL()\n"));
		#endif
		return 16;
	}
	
	// check if socket is not closed before opening it and return error code
	// <state> available values are:
	// 	 0: Socket Disabled
	//	 1: Connection closed
	//	 2: Connection open
	if (socketStatusSSL[socketId].state != 1)
	{
		return socketStatusSSL[socketId].state+17; // 17 to 19 error codes
	}
	
	
	//// 4. Socket Dial
	// AT#SSLD=1,<remote_port>,"<remote_IP>",0,1\r
	sprintf_P(command_buffer, 
			(char*)pgm_read_word(&(table_IP[12])),
			remote_port,
			remote_IP);
	
	// send command	
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 15000);
	
	// check answer 
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		return 20;
	}
	
	
	//// 5. Wait for opening the socket	
	// <state> available values are:
	// 	 0: Socket Disabled
	//	 1: Connection closed
	//	 2: Connection open
	uint32_t previous = millis();
	
	do
	{
		// get socket status
		answer = getSocketStatusSSL(socketId);
		
		if (answer == 0)
		{
			if (socketStatusSSL[socketId].state == 2)
			{
				// Socket suspended
				return 0;
			}
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
		delay(1000);
		
	} while (((millis() - previous) < LE910_IP_TIMEOUT));
	
	
	return 21;

}


/* Function: 	This function closes a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * Return:	0 Socket Closed
 * 			1 if error sending the command
 * 			2 if timeout shutting down the socket
 */
uint8_t Wasp4G::closeSocketClient(uint8_t socketId)
{
	uint8_t answer;
	char command_buffer[10];
				
	//// 1. Check socket status	
	answer = getSocketStatus(socketId);
	
	if ((answer == 0) && (socketStatus[socketId].state == 0))
	{
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("Socket status: closed\n"));
		#endif
		return 0;
	}
	
	
	//// 2. Configure connection	
	// AT#SH=<socketId>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[7])), socketId+1);

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer
	if(answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error closing connection\n"));
		#endif
		return 1;
	}

	
	//// 3. Wait the shutdown of the socket	
	uint32_t previous = millis();
	
	do
	{
		// get socket status
		answer = getSocketStatus(socketId);
		if (answer != 0)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting socket status\n"));
			#endif
			return 2;
		}
		
		if (socketStatus[socketId].state == 0)
		{
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Socket closed\n"));
			#endif
			return 0;
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
		delay(1000);
		
	} while ((millis() - previous) < LE910_IP_TIMEOUT);
	
	
	return 3;
}



/* Function: 	This function closes a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * Return:	0 Socket Closed
 * 			1 if error sending the command
 * 			2 if timeout shutting down the socket
 */
uint8_t Wasp4G::closeSocketServer(uint8_t socketId, uint8_t protocol)
{
	uint8_t answer;
	char command_buffer[10];
				
	//// 1. Check socket status	
	answer = getSocketStatus(socketId);
	
	if ((answer == 0) && (socketStatus[socketId].state == 0))
	{
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("Socket status: closed\n"));
		#endif
		return 0;
	}
	
	
	//// 2. Close socket listening
	if (protocol == Wasp4G::TCP)
	{
		// AT#SL=<socketId>,0,<local_port>,255\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[29])), 
				socketId+1,
				0,
				socketStatus[socketId].localPort,
				255);
	}
	else if (protocol == Wasp4G::UDP)
	{
		// AT#SLUDP=<socketId>,0,<local_port>\r		
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[30])), 
				socketId+1,
				0,
				socketStatus[socketId].localPort);
	}
	else
	{
		return 1;
	}	
	
	// send command	
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer 
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
			
			#if DEBUG_WASP4G > 0
				printErrorCode();
			#endif
		}
		return 1;
	}
	
	
	//// 3. Configure connection	
	// AT#SH=<socketId>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[7])), socketId+1);

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer
	if(answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error closing connection\n"));
		#endif
		return 1;
	}

	
	//// 3. Wait the shutdown of the socket	
	uint32_t previous = millis();
	
	do
	{
		// get socket status
		answer = getSocketStatus(socketId);
		if (answer != 0)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting socket status\n"));
			#endif
			return 2;
		}
		
		if (socketStatus[socketId].state == 0)
		{
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Socket closed\n"));
			#endif
			return 0;
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
		delay(1000);
		
	} while ((millis() - previous) < LE910_IP_TIMEOUT);
	
	
	return 1;
}




/* Function: 	This function closes a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * Return:	0 Socket Closed
 * 			1 if error sending the command
 * 			2 if timeout shutting down the socket
 */
uint8_t Wasp4G::closeSocketSSL(uint8_t socketId)
{
	uint8_t answer;
	char command_buffer[10];
				
	//// 1. Check socket status	
	answer = getSocketStatusSSL(socketId);
	
	if ((answer == 0) && (socketStatusSSL[socketId].state == 1))
	{
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("Socket status: closed\n"));
		#endif
		return 0;
	}
	
	
	//// 2. Configure connection	
	// AT#SSLH=<socketId>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[19])), socketId+1);

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer
	if(answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error closing connection\n"));
		#endif
		return 1;
	}

	
	//// 3. Wait the shutdown of the socket	
	uint32_t previous = millis();
	
	do
	{
		// get socket status
		answer = getSocketStatusSSL(socketId);
		if (answer != 0)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting socket status\n"));
			#endif
			return 2;
		}
		
		if (socketStatusSSL[socketId].state == 1)
		{
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Socket closed\n"));
			#endif
			return 0;
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
		delay(1000);
		
	} while ((millis() - previous) < LE910_IP_TIMEOUT);
	
	
	return 3;
}



/* Function: 	This function sends data through a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * 				data: string with the data
 * Return:		'0' if OK; 'x' if error
 */
uint8_t Wasp4G::send(uint8_t socketId, char* data)
{
	return send(socketId, (uint8_t*)data, strlen(data));
}


/* Function: 	This function sends data through a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * 				data: buffer with the data
 * 				data_length: length of the data buffer
 * Return:		0 if OK, 'x' error
 */
uint8_t Wasp4G::send(uint8_t socketId,
					uint8_t* data,
					uint16_t data_length)
{
	uint8_t answer;
	char command_buffer[25];	
	
	//// 1. Check socket status
	answer = getSocketStatus(socketId);
	
	// check answer error
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error checking socket status\n"));
		#endif
		return 1;
	}
	
	// check correct socket status
	if ((socketStatus[socketId].state != 1) &&
		(socketStatus[socketId].state != 2) &&
		(socketStatus[socketId].state != 3))
	{	
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Incorrect socket status\n"));
		#endif
		return 2;
	}
	
	
	//// 2. Send data	
	// AT#SSENDEXT=<socketId>,<data_length>\r
	sprintf_P(command_buffer, 
			(char*)pgm_read_word(&(table_IP[8])),	
			socketId+1, 
			data_length);
	
	// send command
	answer = sendCommand(command_buffer, ">", LE910_ERROR_CODE, LE910_ERROR);

	// check answer
	if(answer != 1)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error sending data\n"));
		#endif
		return 3;
	}

	// send array of data
	for (int i = 0; i < data_length; i++)
	{
		printByte(data[i], 1);
	}
	
	// wait for "OK"
	answer = waitFor(LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer
	if (answer != 1)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error waiting OK\n"));
		#endif
		return 4;
	}
	
	
	//// 3. Wait that all data have been sent
	uint32_t previous = millis();
	
	do
	{
		// get socket status
		answer = getSocketStatus(socketId);
		if (answer != 0)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting socket status\n"));
			#endif
			return 5;
		}
		
		if (socketStatus[socketId].state == 2)
		{
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Data sent\n"));
			#endif
			return 0;
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
		delay(1000);
		
	} while ((millis() - previous) < LE910_IP_TIMEOUT);
	
	
	return 6;
}






/* Function: 	This function sends data through a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * 				data: string with the data
 * Return:	0 if OK
 * 			1 if error with the socket
 * 			2 if error sending the command
 * 			3 if error sending the command
 * 			4 if timeout shutting down the socket
 */
uint8_t Wasp4G::sendSSL(uint8_t socketId, char* data)
{
	return sendSSL(socketId, (uint8_t*)data, strlen(data));
}

/* Function: 	This function sends data through a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * 				data: buffer with the data
 * 				data_length: length of the data buffer
 * Return:		0 if OK, 'x' error
 */
uint8_t Wasp4G::sendSSL(uint8_t socketId,
						uint8_t* data,
						uint16_t data_length)
{
	uint8_t answer;
	char command_buffer[25];
	
	//// 1. Check socket status
	answer = getSocketStatusSSL(socketId);
	
	// check answer error
	if (answer != 0)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error checking socket status\n"));
		#endif
		return 1;
	}
	
	// check correct socket status
	if (socketStatusSSL[socketId].state != 2)
	{	
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Socket status incorrect\n"));
		#endif
		return 2;
	}
	
	
	//// 2. Send data	
	// AT#SSLSEND=<socketId>\r
	sprintf_P(command_buffer, 
			(char*)pgm_read_word(&(table_IP[14])),	
			socketId+1, 
			data_length);
	
	// send command
	answer = sendCommand(command_buffer, ">", LE910_ERROR_CODE, LE910_ERROR);

	// check answer
	if (answer != 1)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error sending data\n"));
		#endif	
		
		if (answer == 2)
		{
			getErrorCode();
		}	
		return 3;
	}

	// send array of data
	for (int i = 0; i < data_length; i++)
	{
		printByte(data[i], 1);
	}
	// send 0x1A to complete the operation
	printByte(0x1A, 1);
	
	// wait for "OK"
	answer = waitFor(LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
	
	// check answer
	if (answer != 1)
	{		
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error waiting OK\n"));
		#endif
		
		if (answer == 2)
		{
			getErrorCode();
		}		
		return 4;
	}
	
	
	//// 3. Wait that all data have been sent
	uint32_t previous = millis();
	
	do
	{
		// get socket status
		answer = getSocketStatusSSL(socketId);
		if (answer != 0)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting socket status\n"));
			#endif
			return 5;
		}
		
		if (socketStatusSSL[socketId].state == 2)
		{
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("Data sent\n"));
			#endif
			
			return 0;
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
		
		delay(1000);
		
	} while ((millis() - previous) < LE910_IP_TIMEOUT);
	
	
	return 6;
}


/* Function: 	This function read data received in the module
 * Parameters:	socketId: number of the socket Id
 * Return: 		'0' if OK; 'x' if error
 * 			
 */
uint8_t Wasp4G::receive(uint8_t socketId)
{
	return receive(socketId, 0);
}

/* Function: 	This function read data received in the module
 * Parameters:	socketId: number of the socket Id
 * 				timeout: number of ms to wait for incoming bytes
 * Return: 		'0' if OK; 'x' if error
 */
uint8_t Wasp4G::receive(uint8_t socketId, uint32_t timeout)
{
	uint8_t answer;
	int incoming_bytes;
	char command_buffer[25];
	char command_answer[25];
	uint32_t nBytes = 0;
	uint32_t readBufferBytes = 0;
	uint32_t previous;
	
	previous = millis();

	//// 1. Get socket pending bytes to be read for specified 'timeout' in the
	// case the timeout is zero, do it once
	do
	{
		// get socket info
		answer = getSocketInfo(socketId);
	
		if (answer != 0)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting socket info\n"));
			#endif
			return 2;
		}
		
		if (socketInfo[socketId].size > 0)
		{
			break;
		}
		
		if (timeout == NULL)
		{
			return 1;
		}

		delay(500);
	}
	while (millis()-previous < timeout);
	
	if (socketInfo[socketId].size == 0)
	{
		return 3;
	}

	// get number of pending bytes to be read in socket
	incoming_bytes = socketInfo[socketId].size;
	
	
	//// 2. Send command to read received data and save it
	// generate the expected response
	// AT#SRECV: <socketId>,	
	sprintf_P(command_answer,(char*)pgm_read_word(&(table_IP[9])), socketId+1);

	// generate command
	// AT#SRECV=<socketId>,<LE910_MAX_DL_PAYLOAD>\r
	sprintf_P(command_buffer,(char*)pgm_read_word(&(table_IP[26])), 
			socketId+1, 
			LE910_MAX_DL_PAYLOAD);
	
	// send command		
	answer = sendCommand(command_buffer, command_answer, 2000);			
	
	// check answer
	if (answer == 1)
	{
		// wait for end of response "<nBytes>\r\n"
		answer = waitFor("\r\n", 1000);
		
		if (answer != 1)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error waiting EOL\n"));
			#endif
			return 4;
		}
		
		// parse <nBytes>
		answer = parseUint32(&nBytes, " \r\n");	
		
		if (answer != 0)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error parsing nBytes\n"));
			#endif
			return 5;
		}
		
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("nBytes:"));
			USB.println(nBytes, DEC);
		#endif
		
		// wait for number of bytes in data received
		readBufferBytes = readBuffer(nBytes);
		
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("readBufferBytes:"));
			USB.println(readBufferBytes, DEC);
		#endif
		
		if (readBufferBytes != nBytes)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting received bytes\n"));
			#endif
			return 6;
		}
	}
	
	// update attribute length
	_length = nBytes;
	
	return 0;
}




/* Function: 	This function read data received in the module
 * Parameters:	socketId: number of the socket Id
 * Return:		'0' if ok; 'x' if error
 */
uint8_t Wasp4G::receiveSSL(uint8_t socketId)
{
	return receiveSSL(socketId, 0);
}

/* Function: 	This function read data received in the module
 * Parameters:	socketId: number of the socket Id
 * 				timeout: number of ms to wait for incoming bytes
 * Return:		'0' if ok; 'x' if error
 */
uint8_t Wasp4G::receiveSSL(uint8_t socketId, uint32_t timeout)
{
	uint8_t answer;
	char command_buffer[50];
	char answer1[25];
	char answer2[25];
	char answer3[25];
	uint32_t nBytes = 0;
	uint32_t readBufferBytes = 0;
	uint32_t previous;
	
	// get current execution time	
	previous = millis();
	
	// generate command
	// AT#SSLRECV=<socketId>,<MaxNumBytes>\r
	sprintf_P(command_buffer, 
			(char*)pgm_read_word(&(table_IP[15])),			
			socketId+1,
			LE910_MAX_DL_PAYLOAD);
			
	// Generate answers
	strcpy_P(answer1, (char*)pgm_read_word(&(table_IP[16])));	//"#SSLRECV: "
	strcpy_P(answer2, (char*)pgm_read_word(&(table_IP[17])));	//"TIMEOUT\r\n"
	strcpy_P(answer3, (char*)pgm_read_word(&(table_IP[18])));	//"DISCONNECTED\r\n"


	//// 1. Send command to read received data and save it
	do
	{
		// send command to read data from SSL socket
		answer = sendCommand(command_buffer, answer1, answer2, answer3, LE910_ERROR_CODE, 5000);		
	
		// check timeout with no answer
		if (answer == 0)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("No answer from module\n"));
			#endif
			return 1;
		}
		
		// check OK response with incoming data, then break
		if (answer == 1)
		{
			break;
		}
		
		// check OK response with incoming data, then break
		if (answer == 3)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("SSL Socket DISCONNECTED\n"));
			#endif
			return 2;
		}
		
		// check error code
		if (answer == 4)
		{
			getErrorCode();
			return 3;
		}
		
		delay(500);
	}
	while ((millis()-previous < timeout));


	//// 2. If bytes have been received, then proceed to read them
	if (answer == 1)
	{
		// wait for end of response "<nBytes>\r\n"
		answer = waitFor("\r\n", 1000);
		
		if (answer != 1)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error waiting EOL\n"));
			#endif
			return 4;
		}
		
		// parse <nBytes>
		answer = parseUint32(&nBytes, " \r\n");	
		
		if (answer != 0)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error parsing nBytes\n"));
			#endif
			return 5;
		}
		
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("nBytes:"));
			USB.println(nBytes, DEC);
		#endif
		
		// wait for number of bytes in data received
		readBufferBytes = readBuffer(nBytes);
		
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("readBufferBytes:"));
			USB.println(readBufferBytes, DEC);
		#endif
		
		if (readBufferBytes != nBytes)
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Error getting received bytes\n"));
			#endif
			return 6;
		}
	}
	else
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error waiting LE910_OK\n"));
		#endif
		return 7;		
	}
	
	// update attribute length
	_length = nBytes;
	
	return 0;
}



/* Function: 	This function allows to store, delete and read security data 
 * 				(Certificate, CAcertificate, private key) into the non-volatile 
 * 				memory of the module
 * 
 * Parameters:	socketId: Secure Socket Identifier (must be 1)
 * 				action: Action to do:
 * 					0 – Delete data from NVM
 * 					1 – Store data into NVM
 * 					2 – Read data from NVM
 * 				dataType:
 * 					0 – Certificate
 * 					1 – CA certificate
 * 					2 – RSA Private key
 * 				data: string with the security data
 * 
 * Return:		0 if OK; 'x' if error
 */
uint8_t Wasp4G::manageSSL(	uint8_t socketId, 
							uint8_t action, 
							uint8_t dataType)
{
	return manageSSL(socketId, action, dataType, NULL);
}


/* Function: 	This function allows to store, delete and read security data 
 * 				(Certificate, CAcertificate, private key) into the non-volatile 
 * 				memory of the module
 * 
 * Parameters:	socketId: Secure Socket Identifier (must be 1)
 * 				action: Action to do:
 * 					0 – Delete data from NVM
 * 					1 – Store data into NVM
 * 					2 – Read data from NVM
 * 				dataType:
 * 					0 – Certificate
 * 					1 – CA certificate
 * 					2 – RSA Private key
 * 				data: string with the security data
 * 
 * Return:		0 if OK; 'x' if error
 */
uint8_t Wasp4G::manageSSL(	uint8_t socketId, 
							uint8_t action, 
							uint8_t dataType,
							char *data)
{
	uint8_t answer;
	char command_buffer[50];
	char command_answer[50];
	
	// clear buffers
	memset(command_buffer,0x00,sizeof(command_buffer));
	memset(command_answer,0x00,sizeof(command_answer));
	
	
	//// 1. Enable a SSL socket
	// "AT#SSLEN=<socketId>,1\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[33])), socketId+1, 1);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
		
	// check response
	// If the socket has already been enabled for SSL, 
	// the module returns error, so we continue if error
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
	}
		
	
	//// 2. Set SSL settings
	if ((action == Wasp4G::SSL_ACTION_STORE) && (data != NULL))
	{
		// AT#SSLSECDATA=<socketId>,<action>,<dataType>,<data_length>\r
		sprintf_P(	command_buffer, 
					(char*)pgm_read_word(&(table_IP[10])),
					socketId+1,
					action, 
					dataType,
					strlen(data));
					
		// send command
		answer = sendCommand(command_buffer, ">", LE910_ERROR_CODE, LE910_ERROR);
		
		// check response
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}		
			return 1;
		}
		
		// send certificate data	
		printString(data, 1);
		printByte(0x1A, 1);
		
		waitFor(LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
		
		// check response
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}		
			return 2;
		}	
		
		return 0;
	}
	else if (action == Wasp4G::SSL_ACTION_READ)
	{
		// command_buffer <-- AT#SSLSECDATA=<socketId>,<action>,<dataType>\r
		sprintf_P(	command_buffer, 
					(char*)pgm_read_word(&(table_IP[11])),
					socketId+1,
					action, 
					dataType);
		
		// command_answer <-- "#SSLSECDATA: "
		strcpy_P( command_answer, (char*)pgm_read_word(&(table_IP[27])));

		// send command
		answer = sendCommand(command_buffer, command_answer, LE910_ERROR_CODE, LE910_ERROR);
		
		// check response
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}		
			return 3;
		}
		
		waitFor("\r\n");		
		waitFor(LE910_OK);
		
		return 0;
		
	}
	else if (action == Wasp4G::SSL_ACTION_DELETE)
	{
		// AT#SSLSECDATA=<socketId>,<action>,<dataType>\r
		sprintf_P(	command_buffer, 
					(char*)pgm_read_word(&(table_IP[11])),
					socketId+1,
					action, 
					dataType);
					
		// send command
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
		
		// check response
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}		
			return 4;
		}		
		
		return 0;
	}
	
	return 5;
}



/* Function: 	Starts the GPS engine with hot start and stand alone mode
 * Parameters:	
 * 	reset_mode:	
 * 		1 Coldstart
 * 		2 Warmstart
 * 		3 Hotstart
 *	gps_mode:	
 * 		0: Pure MS Assisted - Location estimate from the network (MS Assisted mode).
 *		1: MS Based - Assistance Data from the network (MS Based mode).
 * 		2: MS Assisted Based - Combination of MS-A and MS-B modes, location 
 * 		estimate computed both at UE and Network.
 * 		3: Autonomous – Autonomous GPS mode of operation.
 * 
 * Return:	0 if OK
 * 			1 if GPS is powered yet
 * 			2 if error setting the reset mode
 * 			3 if error starting the GPS engine
 */
uint8_t Wasp4G::gpsStart()
{
	return gpsStart(Wasp4G::GPS_AUTONOMOUS, 3);
}


/* Function: 	Starts the GPS engine with the reset and location mode desired
 * Parameters:	
 * 	reset_mode:	
 * 		1 Coldstart
 * 		2 Warmstart
 * 		3 Hotstart
 *	gps_mode:	
 * 		0: Pure MS Assisted - Location estimate from the network (MS Assisted mode).
 *		1: MS Based - Assistance Data from the network (MS Based mode).
 * 		2: MS Assisted Based - Combination of MS-A and MS-B modes, location 
 * 		estimate computed both at UE and Network.
 * 		3: Autonomous – Autonomous GPS mode of operation.
 * 
 * Return:	0 if OK
 * 			1 if GPS is powered yet
 * 			2 if error setting the reset mode
 * 			3 if error starting the GPS engine
 */
uint8_t Wasp4G::gpsStart(uint8_t gps_mode)
{
	return gpsStart(gps_mode,3);
}


/* Function: 	Starts the GPS engine with the reset and location mode desired
 * Parameters:	
 * 	reset_mode:	
 * 		1 Coldstart
 * 		2 Warmstart
 * 		3 Hotstart
 *	gps_mode:	
 * 		0: Pure MS Assisted - Location estimate from the network (MS Assisted mode).
 *		1: MS Based - Assistance Data from the network (MS Based mode).
 * 		2: MS Assisted Based - Combination of MS-A and MS-B modes, location 
 * 		estimate computed both at UE and Network.
 * 		3: Autonomous – Autonomous GPS mode of operation.
 * 
 * Return:	0 if OK; 'x' if error
 */
uint8_t Wasp4G::gpsStart(uint8_t gps_mode, uint8_t reset_mode)
{
	uint8_t answer;	
	char command_buffer[50];
	char command_answer[10];
	
	//// 1. Set reset mode
	// AT$GPSR=<reset_mode>\r	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[2])), reset_mode);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);		
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	
	//// 2. Check if the GPS engine is powered on
	//// In that case, we return OK; if not we start the gps power
	// AT$GPSP?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_GPS[13])));
		
	// Generate answer to be parsed	
	// "GPSP: 1"
	strcpy_P(command_answer, (char*)pgm_read_word(&(table_GPS[14])));

	// send command
	answer = sendCommand(command_buffer, command_answer, LE910_ERROR_CODE, LE910_ERROR, 1000);		
	
	// check answer
	if (answer == 1)
	{	
		return 0;
	}
	else if ((answer == 2) || (answer == 3))
	{	
		if (answer == 2)
		{
			getErrorCode();
		}		
		return 2;
	}
	
	
	//// 3. Switch GPS to on
	// Send corresponding command depending on gps mode
	if (gps_mode == Wasp4G::GPS_AUTONOMOUS)
	{
		//// GPS Power Management: GPS controller is powered up
		// "AT$GPSP=1\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[0])), 1);
		
		// send command
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 1000);
		
		// check answer
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return 3;
		}
		
		// return OK
		return 0;
	}
	else if ((gps_mode == Wasp4G::GPS_MS_ASSISTED) || (gps_mode == Wasp4G::GPS_MS_BASED))
	{		
		//// 4. setup NETWORK_UTRAN
		answer = setWirelessNetwork(Wasp4G::NETWORK_UTRAN);
		if (answer != 0)
		{
			return 4;
		}
		
		//// 5. Define PDP Context
		// AT+CGDCONT=1,"IP","<APN>"\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_4G[29])), _apn);
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
		if (answer != 1)
		{
			return 5;
		}		
		
		//// 6. Set Authentication User ID
		// AT#USERID="<login>"\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_4G[5])), _apn_login);
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
		if (answer != 1)
		{
			return 6;
		}		
		
		//// 7. Set Authentication Password
		// AT#PASSW="<pass>"\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_4G[6])), _apn_password);
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 5000);
		if (answer != 1)
		{
			return 7;
		}
		
		//// 8. 
		// AT#SCFG=1,1,300,90,600,50\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[2])), 1, 1, 300, 90, 600, 50);
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
		if (answer != 1)
		{
			return 8;
		}
		
		//// 9. Set QoS for GPS:
		// 	horiz_accuracy  = 5
		// 	vertic_accuracy = 5
		// 	rsp_time = 100
		// 	age_of_location_info = 0 
		// 	location_type = 0 (current location)
		// 	nav_profile = 0 Car navigation profile (default)
		// 	velocity_request = TRUE
		answer = gpsSetQualityOfService(5, 5, 100, 0, 0, 0, 1);
		
		if (answer != 0)
		{
			return 9;
		}
		
		//// 10. Set SLP server
		// AT$SLP=1,"supl.nokia.com:7275"\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[21])));
		
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
		if (answer != 1)
		{
			return 10;
		}
		
		//// 11. Set the version of supported SUPL
		// AT$SUPLV=%u\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[20])), 1);
		
		// send command
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 1000);		
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return 11;
		}
		
		//// 12. Update terminal information
		// AT$LCSTER=1,,,1\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[22])));
		
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
		if (answer != 1)
		{
			return 12;
		}
		
		//// 13. Enable unsolicited response 
		// AT$LICLS=1\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[23])));
		
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
		if (answer != 1)
		{
			return 13;
		}
		
		//// 14. Lock context for LCS use
		// AT$LCSLK=1,1\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[24])));
		
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
		if (answer != 1)
		{
			return 14;
		}
		
		//// 15. Enable GNSS (or GLONASS)
		// AT$GPSGLO=1\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[25])));
		
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR);
		if (answer != 1)
		{
			return 15;
		}
		
		//// 16. GPS Start Location Service Request:
		// AT$GPSSLSR=<transport_protocol>,<gps_mode>,,,,,1\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[1])),
					1, 
					gps_mode,
					1);

		// send command
		answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 1000);		
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return 16;
		}	
		
		// check connection
		answer = checkDataConnection(60);
		if (answer != 0)
		{
			return 17;
		}
		
		// return OK
		return 0;
	}
	else
	{
		return 18;
	}
	
	return 0;	
}


/* Function: Stops the GPS engine
 * Return:	'0' if OK; '1' error
 */
uint8_t Wasp4G::gpsStop()
{
	uint8_t answer;
	char command_buffer[20];
	
	// AT$GPSP=0\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[0])), 0);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 1000);		
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}		
		return 1;
	}	
	
	return 0;
	
}

/* Function: 	Checks the GPS and parses GPS data if the sats are fixed
 * Return:	'0' if OK; 'x' error
 */
int8_t Wasp4G::checkGPS()
{
	char *pointer;
	uint8_t answer;
	char command_buffer[20];
	char command_pattern[20];
	
	//// 1. Check if the GPS position is fixed
	// AT$GPSACP\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_GPS[4])));
	
	// pattern <--- "$GPSACP: ,"
	strcpy_P(command_pattern, (char*)pgm_read_word(&(table_GPS[15])));
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	// check if there is not any available data in _buffer
	// If so, _buffer has the following string within it:
	// "$GPSACP: ,,,...."
	if (find(_buffer, _length, command_pattern) == true)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("pattern not found\n"));
		#endif
		return 2;
	}
	
	
	//// 2. Parses the data
	// Example below:
	/* $GPSACP: <hhmmss.sss>,		// field 1: UTC time
	 * 			<ddmm.mmmm><N/S>,	// field 2: latitude
	 * 			<dddmm.mmmm><E/W>,	// field 3: longitude
	 * 			<x.x>,				// field 4: HDOP
	 * 			<xxxx.x>,			// field 5: altitude
	 * 			<fix>,				// field 6: fix mode
	 * 			<ddd.mm>,			// field 7: Course over ground
	 * 			<xxxx.x>,			// field 8: Speed over ground (Km/hr)
	 * 			<xxxx.x>,			// field 9: Speed over ground (knots)
	 * 			<ddmmyy>,			// field 10: Date
	 * 			<nsat>				// field 11: Number of satellites
	 */
	// $GPSACP: 073041.000,4139.7780N,00051.3417W,500.0,-394.4,2,0.0,0.0,0.0,050515,00
	
	// pattern <--- "\r\n$GPSACP: .,"
	strcpy_P(command_pattern, (char*)pgm_read_word(&(table_GPS[16])));
		
	// skip first characters
	pointer = strtok((char*)_buffer, command_pattern);
	if (pointer == NULL)
	{
		return 3;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("UTC:"));
		USB.println(pointer);
	#endif
		
	/// field 1: Get UTC time
	memset(_time, 0x00, sizeof(_time));
	strncpy(_time, pointer, 6);
	
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 4;
	}
		
	// skip '.000' after time field
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 5;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Latitude:"));
		USB.println(pointer);
	#endif
	
	/// field 2: Get latitude
	memset(_latitude, '\0', sizeof(_latitude));
	strcpy(_latitude, pointer);
	
	/// Get NS_indicator
	_latitudeNS = _latitude[strlen(_latitude)-1];
	_latitude[strlen(_latitude)-1] = '\0';
	
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 6;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Longitude:"));
		USB.println(pointer);
	#endif
	
	/// field 3: Get longitude
	memset(_longitude, 0x00, sizeof(_longitude));
	strcpy(_longitude, pointer);
	
	/// Get EW_indicator
	_longitudeEW = _longitude[strlen(_longitude)-1];
	_longitude[strlen(_longitude)-1] = '\0';
	
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 7;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("HDOP:"));
		USB.println(pointer);
	#endif
	
	/// field 4: Get HDOP
	_hdop = atof(pointer);
	
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 8;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Altitude:"));
		USB.println(pointer);
	#endif
	
	/// field 5: Get altitude
	_altitude = atof(pointer);
	
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 9;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Fix mode:"));
		USB.println(pointer);
	#endif	

	/// field 6: Get fix mode
	_fixMode = atoi(pointer);
	
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 10;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Course over ground:"));
		USB.println(pointer);
	#endif
	
	/// field 7: Get course over ground
	memset(_courseOG, 0x00, sizeof(_courseOG));
	strcpy(_courseOG, pointer);	
	
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 11;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Speed over ground (kmh):"));
		USB.println(pointer);
	#endif
	
	/// field 8: Get Speed over ground (Km/hr)
	_speedOG = atof(pointer);
		
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 12;
	}
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Speed over ground (knots):"));
		USB.println(pointer);
	#endif	
	
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 13;
	}									
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Get date:"));
		USB.println(pointer);
	#endif
	
	/// field 10: Get date 			
	memset(_date, 0x00, sizeof(_date));
	strncpy(_date, pointer, 6);
	
	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 14;
	}	
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Num Satellites:"));
		USB.println(pointer);
	#endif
	
	/// field 11: Get satellites in use
	_numSatellites = (uint8_t)atoi(pointer);
	
	return 0;	
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
float Wasp4G::convert2Degrees(char* input, char indicator)
{
	// final latitude expresed in degrees
	float degrees;
	float minutes;
	
	// auxiliar variable
	char aux[10] = "";
	
	// check if 'indicator' is a valid input
	if ((indicator != 'N') && 
		(indicator != 'S') && 
		(indicator != 'E') && 
		(indicator != 'W'))
	{
		// invalid indicator
		return 0;
	}	
	
	// get 'degrees' from input parameter
	if ((indicator == 'N') || (indicator == 'S'))
	{
		// latitude format: DDmm.mmmm'
		aux[0] = input[0];
		aux[1] = input[1];
		aux[2] = '\0';
	}
	else if ((indicator == 'E') || (indicator == 'W'))
	{
		// longitude format: DDDmm.mmmm'
		aux[0]=input[0];
		aux[1]=input[1];
		aux[2]=input[2];
		aux[3]='\0';
	}
	
	// convert string to integer and add it to final float variable
	degrees = atoi(aux);
	
	// get 'minutes' from input parameter
	if ((indicator == 'N') || (indicator == 'S'))
	{
		// latitude format: DDmm.mmmm'
		for ( int i=0; i<7; i++ )
		{
			aux[i] = input[i+2];
		}
		aux[7] = '\0';
	}
	else if ((indicator == 'E') || (indicator == 'W'))
	{
		// longitude format: DDDmm.mmmm'
		for ( int i = 0; i < 7; i++ )
		{
			aux[i] = input[i+3];
		}
		aux[7] = '\0';
	}
	
	// convert string to integer and add it to final float variable
	minutes = atof(aux);
	
	// add minutes to degrees
	degrees = degrees + minutes/60;
	
	// add sign: '+' for North/East; '-' for South/West
	if ((indicator == 'S') || (indicator == 'W'))
	{
		degrees *= -1.0;
	}
	
	return degrees;
}



/* Function:	It waits for satellites signal
 * Return:		'0' if OK; '1' if error
 */
uint8_t Wasp4G::waitForSignal()
{
	return waitForSignal(60000, -1.0);
}


/* Function:	It waits for satellites signal
 * Parameters:	timeout: milliseconds to wait for signal
 * Return:		'0' if OK; '1' if error
 */
uint8_t Wasp4G::waitForSignal(uint32_t timeout)
{
	return waitForSignal(timeout, -1.0);
}


/* Function:	It waits for satellites signal
 * Parameters:	timeout: milliseconds to wait for signal
 * Return:		'0' if OK; '1' if error
 */
uint8_t Wasp4G::waitForSignal(uint32_t timeout, float desired_HDOP)
{
	int8_t answer = 0;
	uint32_t previous;
	
	// get current time
	previous = millis();
	
	// update variable status
	_fixMode = 0;
	
	//// 1. get current gps status
	while((_fixMode != 2) && (_fixMode != 3))
	{
		answer = checkGPS();
	
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("checkGPS answer: "));
			USB.println(answer);
		#endif
		
		if (answer == 0)
		{
			if ((_fixMode == 2) || (_fixMode == 3))
			{
				// Good options:
				// 	2 - 2D fix
				// 	3 - 3D fix
				#if DEBUG_WASP4G > 1
					PRINT_LE910(F("_fixMode ok\n"));
				#endif
				break;
			}
			else
			{
				#if DEBUG_WASP4G > 1
					PRINT_LE910(F("_fixMode is not correct yet. _fixmode = "));
					USB.println(_fixMode, DEC);
				#endif
			}			
		}
		else
		{
		
			#if DEBUG_WASP4G > 1
			PRINT_LE910(F("checkGPS error\n"));
			#endif
		}
		
		delay(500);
		
		if (millis()-previous > timeout)
		{
			// timeout error
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("_fixMode error timeout ==> Exit function\n"));
			#endif
			return 1;
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();		
	}
	
	
	//// 2. Check if desired HDOP is correct
	if (desired_HDOP != -1.0)
	{
		while(((millis() - previous) < timeout) && (_hdop > desired_HDOP))
		{
			answer = checkGPS();
			
			if (answer == 0)
			{
				if ((_fixMode == 2) || (_fixMode == 3))
				{
					// Good options:
					// 	2 - 2D fix
					// 	3 - 3D fix
					break;
				}			
			}
			
			delay(1000);
		}
		
		// if down the threshold then return ok
		if (_hdop <= desired_HDOP)
		{
			return 0;
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();	
	}
	
	if (_hdop < desired_HDOP)
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("_hdop not valid\n"));
		#endif
		return 1;
	}
	
	return 0;
}


/*
 * Function: It sets the quality of service of GPS 
 * 
 */
uint8_t Wasp4G::gpsSetQualityOfService(	uint32_t horiz_accuracy, 
										uint16_t vertic_accuracy,
										uint16_t rsp_time,
										uint32_t age_of_location_info,
										uint8_t location_type,
										uint8_t nav_profile,
										uint8_t velocity_request)
{	
	uint8_t answer;
	char command_buffer[80];
	
	// "AT$GPSQOS=%lu,%u,%u,%lu,%u,%u,%u\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[19])),
				horiz_accuracy, 
				vertic_accuracy,
				rsp_time,
				age_of_location_info,
				location_type,
				nav_profile,
				velocity_request);
	
	// send command
	answer = (int)sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		
		// error
		return 1;
	}
	
	return 0;	
}




/*
 * Function: It gets the NMEA string
 * 
 */
bool Wasp4G::getNMEAString(uint8_t NMEA)
{
	char command_answer[20];
	char command_buffer[30];
	char NMEA_string[100];
	uint16_t NMEA_length;
	uint8_t answer;
	
	switch(NMEA)
	{
		case LE910_GGA:
			// AT$GPSNMUN=3,1,0,0,0,0,0\r
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), 1, 0, 0, 0, 0, 0);
			strcpy_P(command_answer, (char*)pgm_read_word(&(table_GPS[10])));	//$GPGGA
			break;
		case LE910_GSA:
			// AT$GPSNMUN=3,0,0,1,0,0,0\r			
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), 0, 0, 1, 0, 0, 0);
			strcpy_P(command_answer, (char*)pgm_read_word(&(table_GPS[9])));	//$GPGSA
			break;
		case LE910_GLL:
			// AT$GPSNMUN=3,0,1,0,0,0,0\r		
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), 0, 1, 0, 0, 0, 0);
			strcpy_P(command_answer, (char*)pgm_read_word(&(table_GPS[7])));	//$GPGLL
			break;
		case LE910_VTG:
			// AT$GPSNMUN=3,0,0,0,0,1,0\r
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), 0, 0, 0, 0, 1, 0);
			strcpy_P(command_answer, (char*)pgm_read_word(&(table_GPS[11])));	//$GPRMC
			break;
		case LE910_RMC:
			// AT$GPSNMUN=3,0,0,0,0,0,1\r
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), 0, 0, 0, 0, 0, 1);
			strcpy_P(command_answer, (char*)pgm_read_word(&(table_GPS[8])));	//$GPVTG
			break;	
		case LE910_GSV:
			// AT$GPSNMUN=3,0,0,0,1,0,0\r
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), 0, 0, 0, 1, 0, 0);
			strcpy_P(command_answer, (char*)pgm_read_word(&(table_GPS[12])));	//$GPGSV
			break;	
	}
	
	//command_answer <-- "CONNECT\r\n"
	strcpy_P(command_answer, (char*)pgm_read_word(&(table_GPS[6])));
	answer = sendCommand(command_buffer, command_answer, 5000);
	if (answer != 1)
	{
		return 1;
	}
	
	// "+++"
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_GPS[18])));
	
	answer = waitFor("\r\n", 5000);
	if (answer != 1)
	{
		// Exit from data mode
		sendCommand(command_buffer, LE910_OK, 2000);
		return 1;
	}
	
	memset(NMEA_string, '\0', sizeof(NMEA_string));
	NMEA_length = (strchr((char*)_buffer, '*') - (char*)_buffer);
	memcpy(NMEA_string, _buffer, NMEA_length);
	
	// Exit from data mode
	sendCommand(command_buffer, LE910_OK, 2000);
	
	USB.println(NMEA_string);
	
	return 0;
}



/* Function: This function gets the temperature interval or the temperature value
 * Parameters:	mode:	 0 for read the temperature interval
 * 						 1 for read the temperature value
 * Return:	If interval mode selected
 * 			-2 Extreme temperature lower bound.
 * 			-1 Operating temperature lower bound.
 * 			0 normal temperature.
 *			1 Operating temperature upper bound.
 *		 	2 Extreme temperature upper bound.
 * 			-1000 if error
 * 
 * 			If temperature value selected return temperature in Celsius
 * 			-1000 if error
*/
uint8_t Wasp4G::getTemp()
{
	int answer;	
	char *ptr;
	char command_answer[20];
	char command_buffer[20];
	
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[8])));	//AT#TEMPMON=1
	strcpy_P(command_answer, (char*)pgm_read_word(&(table_4G[9])));	//#TEMPMEAS: 
	
	// send command
	answer = (int)sendCommand(command_buffer, command_answer, LE910_ERROR, 2000);
	if (answer != 1)
	{
		return 1;
	}
	
	answer = waitFor(LE910_OK, 2000);
	if (answer != 1)
	{
		return 1;
	}	

	// Get temperature interval 
	ptr = strtok((char*)_buffer, ",");
	
	if (ptr == NULL)
	{
		return 1;
	}
	
	_tempInterval = atoi(ptr);
	
	
	// Get temperature in Celsius degrees
	ptr = strtok(NULL, "\r");
	
	if (ptr == NULL)
	{
		return 1;
	}
	_temp = atoi(ptr);
	
	
	return 0;	
	
}

/* Function:	This function gets the RSSI level
 * Return:	0 if OK; 1 if error
*/
uint8_t Wasp4G::getRSSI()
{
	uint8_t answer;
	uint8_t error;
	char command_buffer[30];	
	char delimiters[30];
	
	// AT+CSQ\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[10])));
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR, 2000);		
	
	// check answer
	if (answer == 1)
	{		
		// delimiters <-- "AT+CSQ\r\n: ,"
		strcpy_P(delimiters, (char*)pgm_read_word(&(table_4G[33])));
		
		error = parseInt(&_rssi, delimiters);
		
		if (error != 0)
		{
			return 1;
		}
		
		#if DEBUG_WASP4G > 0
			USB.print(F("Raw RSSI: "));
			USB.println(_rssi, DEC);
		#endif
		
		// converts the RSSI from the command to dBm
		switch(_rssi)
		{
			case 0:
			case 99:
				_rssi = -113;
				break;
			case 1:
				_rssi = -111;
				break;
			case 33:
				_rssi = 0;
				break;
			default:
				_rssi = (_rssi * 2) - 113;
		}
		
		return 0;
	}
	
	return 1;
		
}

/* Function:	This function gets the packet service network type
 * Return:	'0' if OK; '1' if error
 * 
 * The _networkType attribute stores the corresponding answer:
 * 		0 for GPRS network
 * 		1 for EGPRS network
 * 		2 for WCDMA network
 * 		3 for HSDPA network
 * 		4 for LTE network
 * 		5 for unknown or not registered
*/
uint8_t Wasp4G::getNetworkType()
{
	uint8_t answer;
	uint8_t error;
	char command_buffer[50];
	char delimiters[30];
	
	// AT#PSNT?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[11])));
	
	// send command
	answer =  sendCommand(command_buffer, LE910_OK, LE910_ERROR, 2000);
	
	if (answer == 1)
	{
		// delimiters <-- "AT#PSNT?: ,\r\n"
		strcpy_P(delimiters, (char*)pgm_read_word(&(table_4G[34])));
		
		// parse second response from: "#PSNT: <mode>,<nt>"
		error = parseUint8(&_networkType, delimiters, 2);

		if (error != 0)
		{	
			return 1;
		}
		
		return 0;
	}
	
	return 1;		
}


/* Function: This function gets the operator name
 * Return:	'0' if OK; 'x' if error
*/
uint8_t Wasp4G::getOperator(char* answer_storage)
{
	uint8_t answer;
	char command_buffer[50];
	char* pointer;
	
	// AT+COPS?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[24])));
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	// parse response: "+COPS: 0,0,"<answer>",7"\r\n
	pointer = strtok((char*)_buffer, "\"");
	
	if (pointer == NULL)
	{
		return 2;
	}
	
	strcpy(answer_storage, (char*) strtok(NULL, "\""));

	return 0;
}


/* Function: 	This function gets info from the module
 * Parameters:	info_req:	
 * 					Wasp4G::INFO_HW
 * 					Wasp4G::INFO_MANUFACTURER_ID
 * 					Wasp4G::INFO_MODEL_ID
 * 					Wasp4G::INFO_REV_ID
 * 					Wasp4G::INFO_IMEI 	
 * 					Wasp4G::INFO_IMSI 	
 * 					Wasp4G::INFO_ICCID 
 * Return:	0 if OK; 1 if error
*/
int8_t Wasp4G::getInfo(uint8_t info_req)
{
	uint8_t answer;
	char command_buffer[50];
	
	switch (info_req)
	{
		case 0: 
			// Hardware revision
			// "AT#HWREV\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[12])));
			break;
		case 1: 
			// Manufacturer identification
			// "AT#CGMI\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[13])));
			break;
		case 2: 
			// Model identification
			// "AT#CGMM\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[14])));
			break;
		case 3: 
			// Revision identification
			// "AT#CGMR\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[15])));
			break;
		case 4: 
			// IMEI
			// "AT#CGSN\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[16])));
			break;
		case 5: 
			// IMSI
			// "AT#CIMI\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[17])));
			break;
		case 6: 
			// ICCID
			// "AT#CCID\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[18])));
			break;
		
	}
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR, 2000);
	
	// check answer
	if (answer == 1)
	{
		char aux[30];
		char* pointer;
		pointer = strchr((char*)_buffer, ':');
		
		// skip command name within response buffer
		if (pointer != NULL)
		{
			pointer++;
			_length = strlen(pointer);
			memmove((char*)_buffer, pointer, strlen(pointer));
		}		
		
		// success response format: "\r\n<info>\r\n"
		answer = parseString(aux, sizeof(aux), " \r\n");
		
		if (answer == 0)
		{		
			memset(_buffer, 0x00 ,sizeof(_buffer));
			_length = strlen(aux);
			strncpy((char*)_buffer, aux, strlen(aux));
			return 0;
		}		
		return 1;
	}	
	return 1;		
}




/*
 * This function selects the cellular network (Wireless Data Service, WDS) to 
 * operate with the TA (WDS-Side Stack Selection).
 * 
 * 		NETWORK_GSM	
 * 		NETWORK_UTRAN 
 * 		NETWORK_3GPP
 * 		NETWORK_EUTRAN_ONLY
 * 		NETWORK_GERAN_UTRAN
 * 		NETWORK_GERAN_EUTRAN
 * 		NETWORK_UTRAN_EUTRAN
 * 
 * @return '0' if OK; '1' if error
 * 
 */
uint8_t Wasp4G::setWirelessNetwork(uint8_t n)
{
	uint8_t answer;
	char command_buffer[20];
	
	// "AT+WS46=<n>\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_4G[38])), n);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	return 0;
}



/*
 * This function sets the RTC time and date from the Network's response
 * 
 * @return '0' if OK; '1' if error
 * 
 */
uint8_t Wasp4G::setTimeFrom4G()
{
	int8_t answer, networkType;
	char format[60];
	char command_buffer[50];
	uint8_t year, month, day;
	uint8_t hour, minute, second, timezone;	
	bool RTC_status;
	
	// AT+CCLK?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_4G[25])));
	
	// send command
	answer =  sendCommand(command_buffer, "\"", LE910_ERROR, 2000);
	
	if (answer == 1)
	{	
		waitFor("\"", 2000);
		
		// format <-- "%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%hhd\""
		strcpy_P(format, (char*)pgm_read_word(&(table_4G[35])));
	
		sscanf(	(char*)_buffer, 
				format,
				&year, 
				&month, 
				&day, 
				&hour, 
				&minute, 
				&second, 
				&timezone);
		
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Network time:"));
			USB.print(F("year: "));
			USB.print(year, DEC);
			USB.print(F(" | month: "));
			USB.print(month, DEC);
			USB.print(F(" | day: "));
			USB.println(day, DEC);
			USB.print(F("hour: "));
			USB.print(hour, DEC);
			USB.print(F(" | minute: "));
			USB.print(minute, DEC);
			USB.print(F(" | second: "));
			USB.print(second, DEC);
			USB.print(F(" | timezone: "));
			USB.println(timezone, DEC);
		#endif
		
		// Get current state of RTC power mode
		if (RTC.isON == 0 )
		{
			RTC_status = false;
			RTC.ON();
		}
		else
		{
			RTC_status = true;
		}
		
		#if DEBUG_WASP4G > 0
			USB.print(F("RTC time before: "));
			USB.println(RTC.getTime());
		#endif
		
		// set Time & Date
		RTC.setTime( year, month, day, (uint8_t)RTC.dow((int)year, (int)month, (int)day), hour, minute, second);
		
		#if DEBUG_WASP4G > 0
			USB.print(F("RTC time after: "));
			USB.println(RTC.getTime());
		#endif
		
		if (RTC_status == false )
		{
			RTC.OFF();
		}
		
		return 0;
	}
	
	return 1;
	
}

/* This function sets the apn from operator
 * Parameters:	apn: operator APN
 * Return: nothing
*/
void Wasp4G::set_APN( char* apn)
{
	
	set_APN( apn, NULL, NULL);
}

/* This function sets the apn, login and password from operator
 * Parameters:	apn: operator APN
 * 				login: login or user
 * 				password: password
 * Return: nothing
*/
void Wasp4G::set_APN( char* apn, char* login, char* password)
{
	
	memset(_apn, '\0', sizeof(_apn));
	memset(_apn_login, '\0', sizeof(_apn_login));
	memset(_apn_password, '\0', sizeof(_apn_password));
	
	strncpy(_apn, apn, min(sizeof(_apn), strlen(apn)));
	strncpy(_apn_login, login, min(sizeof(_apn_login), strlen(login)));
	strncpy(_apn_password, password, min(sizeof(_apn_password), strlen(password)));
	
}

/* This function shows the apn, login and password constants
 *
 * Return: nothing
*/
void Wasp4G::show_APN()
{
	// APN parameters depends on SIM
	USB.println(F("*****************************"));
	USB.print(F("APN: "));
	USB.println(_apn);
	USB.print(F("LOGIN: "));
	USB.println(_apn_login);
	USB.print(F("PASSWORD: "));
	USB.println(_apn_password);	
	USB.println(F("*****************************"));
}




/* Function: This function sets the SMTP server address, used for E-mail sending.
 * 
 * Parameter: SMTP server address, string type. This parameter can be either:
 * 	- any valid IP address in the format: xxx.xxx.xxx.xxx
 * 	- any host name to be solved with a DNS query in the format: <host name> 
 * 	(factory default is the empty string “”)
 * 
 * Note: the max length for <smtp> is the output of Test command.
 * Return:	'0' if OK; 'x' if error
*/
uint8_t Wasp4G::emailSetServerSMTP(char* serverSMTP)
{
	uint8_t answer;
	char command_buffer[80];
	
	// AT#ESMTP="<SMTP server>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_EMAIL_LE910[0])),serverSMTP);

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	return 0;
}




/* Function: This function sets the SMTP security and port
 * Return:	'0' if OK; 'x' if error
*/
uint8_t Wasp4G::emailConfigureSMTP(uint8_t security, uint16_t port)
{
	uint8_t error;
	char command_buffer[50];
	char answer[20];
	
	// AT#SMTPCFG=<ssl_encryption>,<port>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_EMAIL_LE910[7])),security,port);
	
	// send command
	error = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (error != 1)
	{
		if (error == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	return 0;
}


/* Function: This function sets the email sender parameters
 * Return:	'0' if OK; 'x' if error
*/
uint8_t Wasp4G::emailSetSender(char* address, char* user, char* password)
{
	uint8_t answer;
	char command_buffer[100];
	
	//// 1. Set sender address
	// AT#EADDR="<address>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_EMAIL_LE910[1])),address);


	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	
	//// 2. Set sender user
	// AT#EUSER="<user>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_EMAIL_LE910[2])),user);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 2;
	}
		
	//// 3. Set sender password
	// AT#EPASSW="<passsword>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_EMAIL_LE910[3])),password);
	
	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 3;
	}	
	
	return 0;	
}



/* Function: This function activates context
 * Return:	'0' if OK; 'x' if error
*/
uint8_t Wasp4G::emailActivateContext(char* user, char* password)
{
	uint8_t error;
	char command_buffer[50];
	char answer[20];
	
	// AT#SGACT=1,1,"<APN user>","<APN pass>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_EMAIL_LE910[5])),user,password);

	// "#SGACT: "
	sprintf_P(answer, (char*)pgm_read_word(&(table_EMAIL_LE910[6])));
	
	// send command
	error = sendCommand(command_buffer, answer, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (error != 1)
	{
		if (error == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	return 0;
}


/* Function: This function sends the email
 * Return:	'0' if OK; 'x' if error
*/

uint8_t Wasp4G::emailSend(char* address,char* subject,char* body)
{
	uint8_t error;
	char command_buffer[50];
	char answer[20];
	
	//// 1. Check data connection
	error = checkDataConnection(60);	
	if (error != 0)
	{
		return error;	// 1 to 15 error codes
	}
	
	
	//// 2. Send email
	// AT#EMAILD=<address>,<subject>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_EMAIL_LE910[8])),address,subject);

	// send command
	error = sendCommand(command_buffer, ">", LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (error != 1)
	{
		if (error == 2)
		{
			getErrorCode();
		}
		return 1;
	}
		
	// send e-mail body to the module
	printString(body,1);
	printByte(0x1A,1);
	
	error = waitFor(LE910_OK,LE910_ERROR_CODE,LE910_ERROR,10000);
	
	// check answer
	if (error != 1)
	{
		if (error == 2)
		{
			getErrorCode();
		}
		return 2;
	}
	return 0;
}


/* Function: This function resets the actual e-mail parameters in the NVM of 
 * the module to the default ones. The values reset are:
 * 		E-mail User Name
 * 		E-mail Password
 * 		E-mail Sender Address
 * 		E-mail SMTP server
 * 
 * Return:	'0' if OK; 'x' if error
*/
uint8_t Wasp4G::emailReset()
{
	uint8_t answer;
	char command_buffer[15];
	
	// AT#ERST\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_EMAIL_LE910[9])));

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	return 0;
}


/* Function: This function saves the actual e-mail parameters in the NVM of the 
 * device. The values reset are:
 * 		E-mail User Name
 * 		E-mail Password
 * 		E-mail Sender Address
 * 		E-mail SMTP server
 * 
 * Return:	'0' if OK; 'x' if error
*/
uint8_t Wasp4G::emailSave()
{
	uint8_t answer;
	char command_buffer[15];
	
	// AT#ESAV\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_EMAIL_LE910[10])));

	// send command
	answer = sendCommand(command_buffer, LE910_OK, LE910_ERROR_CODE, LE910_ERROR, 2000);
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	return 0;
}




/* 
 * requestOTA 
 *
 * This function downloads a new OTA file if OTA is necessary
 *
 * Returns 'x' if error
 */
uint8_t Wasp4G::requestOTA(	char* ftp_server,
							uint16_t ftp_port, 
							char* ftp_user, 
							char* ftp_pass)
{

	uint8_t error;
	char format_no_file[10];
	char format_file[10];
	char format_path[10];
	char format_size[10];
	char format_version[10];
	int length;
	uint8_t error_flag;
	
	char* str_pointer;
	char aux_name[8];
	char path[100];
	char aux_str[10];
	long int aux_size;
	uint8_t aux_version;
	
	
	////////////////////////////////////////////////////////////////////////////
	// 1. SD init
	////////////////////////////////////////////////////////////////////////////
	
	// switch SD card ON
	SD.ON();
	
	// go to Root directory
	SD.goRoot();
	
	// check if the card is there or not
	if (!SD.isSD())
	{	
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error: SD not present\n"));  
		#endif 
		SD.OFF();
		return 1;
	}
	
	// Delete file in the case it exists
	if (SD.isFile(LE910_OTA_FILE) == 1)
	{
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("delete file\n")); 
		#endif
		SD.del(LE910_OTA_FILE);
	}
	
	// switch off the SD card
	SD.OFF();
	
	
	////////////////////////////////////////////////////////////////////////////
	// 2. Open FTP session and download config file
	////////////////////////////////////////////////////////////////////////////
	error = ftpOpenSession(ftp_server, ftp_port, ftp_user, ftp_pass);
		
	if (error == 0)
	{
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("Downloading OTA config file...\n"));
		#endif
		
		// download "UPGRADE.TXT"
		error = ftpDownload(LE910_OTA_FILE, LE910_OTA_FILE);
		
		if (error == 0)
		{
			#if DEBUG_WASP4G > 1
				PRINT_LE910(F("LE910_OTA_FILE download OK\n")); 
			#endif
		}
		else
		{
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("LE910_OTA_FILE download ERROR\n")); 
			#endif
			return 2;
		}
	}
	else
	{
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Open FTP session ERROR\n")); 
		#endif
		return 3;
	}
	
	
	////////////////////////////////////////////////////////////////////////////
	// 3. Analyze LE910_OTA_FILE 
	////////////////////////////////////////////////////////////////////////////

	// "NO_FILE"
	strcpy_P( format_no_file, (char*)pgm_read_word(&(table_OTA_LE910[1])));
	// "FILE:"
	strcpy_P( format_file, (char*)pgm_read_word(&(table_OTA_LE910[2])));
	// "PATH:"
	strcpy_P( format_path, (char*)pgm_read_word(&(table_OTA_LE910[3])));
	// "SIZE:"
	strcpy_P( format_size, (char*)pgm_read_word(&(table_OTA_LE910[4])));
	// "VERSION:"
	strcpy_P( format_version, (char*)pgm_read_word(&(table_OTA_LE910[5])));
	
	// init SD	
	SD.ON();
	SD.goRoot();
		
	// clear buffer
	memset(_buffer, 0x00, sizeof(_buffer));
		
	// Reads the config file and copy to '_buffer'
	SD.cat(LE910_OTA_FILE, 0, sizeof(_buffer));
	strcpy((char*)_buffer, SD.buffer);
	
	
	/// 1. Search the file name
	str_pointer = strstr((char*) _buffer, format_file);
	if (str_pointer != NULL)
	{	
		// Copy the FILE contents:
		// get string length and check it is equal to 7
		length = strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		if (length != 7)
		{			
			ftpCloseSession();
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("length:"));
				USB.println(length);
			#endif	
			return 4;
		}
		// copy string
		strncpy(aux_name, strchr(str_pointer, ':')+1, 7);
		aux_name[7] = '\0';
				
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("FILE:"));
			USB.println(aux_name);	
		#endif
	}
	else
	{
		SD.OFF();
		ftpCloseSession();
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("No FILE label\n"));
		#endif
		return 5;
	}	
	
	/// 2. Check if NO_FILE is the filename
	if (strcmp(aux_name, format_no_file) == 0)
	{	
		ftpCloseSession();
		#if DEBUG_WASP4G > 0
			PRINT_LE910(format_no_file);	
			USB.println(format_no_file);	
		#endif	
		return 6;
	}
	
	/// 3. Search the path 
	str_pointer = strstr((char*) _buffer, format_path);
	if (str_pointer != NULL)
	{
		// copy the PATH contents
		length = strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		strncpy(path, strchr(str_pointer, ':') + 1, length );
		path[length] = '\0';
					
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("PATH:"));
			USB.println(path);
		#endif		
				
		// delete actual program	
		SD.del(aux_name);	
	}
	else
	{	
		SD.OFF();
		ftpCloseSession();	
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("No PATH label\n"));
		#endif
		return 7;
	}
	
	/// 4. Search file size 
	str_pointer = strstr((char*) _buffer, format_size);
	if (str_pointer != NULL)
	{
		// copy the SIZE contents
		length = strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		// check length does not overflow
		if (length >= (int)sizeof(aux_str))
		{
			length = sizeof(aux_str)-1;
		}
		strncpy(aux_str, strchr(str_pointer, ':')+1, length);
		aux_str[length] = '\0';
		
		// converto from string to int
		aux_size = atol(aux_str);
		
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("SIZE:"));
			USB.println(aux_size);
		#endif			
	}
	else
	{
		SD.OFF();
		ftpCloseSession();	
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("No SIZE label\n"));
		#endif
		return 8;
	}
	
	/// 5. Search Version
	str_pointer = strstr((char*) _buffer, format_version);
	if (str_pointer != NULL)
	{
		// copy the SIZE contents
		length = strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		// check length does not overflow
		if (length >= (int)sizeof(aux_str))
		{
			length = sizeof(aux_str)-1;
		}
		strncpy(aux_str, strchr(str_pointer, ':')+1, length);
		aux_str[length] = '\0';	
		
		// convert from string to uint8_t
		aux_version=(uint8_t)atoi(aux_str);
					
		#if DEBUG_WASP4G > 1
			PRINT_LE910(F("VERSION:"));
			USB.println(aux_version,DEC);
		#endif			
	}
	else
	{	
		SD.OFF();
		ftpCloseSession();
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("No VERSION label\n"));
		#endif
		return 9;
	}	
	


	// get actual program version
	uint8_t prog_version = Utils.getProgramVersion();
	// get actual program name (PID)
	char prog_name[8];
	Utils.getProgramID(prog_name);
	
	// check if version number 
	#ifdef LE910_CHECK_VERSION
	if (strcmp(prog_name,aux_name) == 0)
	{
		if ((prog_version >= aux_version) && (prog_version != 255))
		{
			ftpCloseSession();
			
			// if we have specified the same program id and lower/same version 
			// number, then do not proceed with OTA
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Invalid version: actual="));
				USB.print(prog_version,DEC);
				USB.print(F("; new="));
				USB.println(aux_version,DEC);
			#endif	
			return 10;
		}
	}
	#endif


	////////////////////////////////////////////////////////////////////////////
	// 4. Download binary file 
	////////////////////////////////////////////////////////////////////////////
	
	#if DEBUG_WASP4G > 1
		PRINT_LE910(F("Downloading OTA FILE\n"));
	#endif	

	// get binary file
	error = ftpDownload((char*)aux_name, aux_name);
		
	if (error == 0)
	{
		// check if size matches
		SD.ON();
		
		// get file size
		int32_t sd_file_size = SD.getFileSize(aux_name);
		if (sd_file_size != aux_size)
		{
			SD.OFF();
			ftpCloseSession();
			#if DEBUG_WASP4G > 0
				PRINT_LE910(F("Size does not match\n"));
				PRINT_LE910(F("sd_file_size:"));
				USB.println(sd_file_size);
				PRINT_LE910(F("UPGRADE.TXT size field:"));
				USB.println(aux_size);
			#endif	
			return 11;
		}
		#if DEBUG_WASP4G > 1
			SD.ls();
		#endif
		ftpCloseSession();
		
		// call OTA function 
		Utils.loadOTA(aux_name,aux_version);
		return 0;
	}
	else
	{
		error_flag = error;
		SD.OFF();
		ftpCloseSession();
		#if DEBUG_WASP4G > 0
			PRINT_LE910(F("Error getting binary\n"));
		#endif		
		return error_flag + 11; // error codes: 12 to 24
	}	

}




/* This function shows the error code number stored in the related attribute
 *
 * @return: nothing
 */
void Wasp4G::printErrorCode()
{	
	printErrorCode(_errorCode);
}



#if DEBUG_WASP4G > 0
/* This function shows the error code indicated as input
 *
 * @return: nothing
 */
void Wasp4G::printErrorCode( uint16_t error )
{	
	PRINT_LE910(F("==> ERROR CODE: "));
	switch (error)
	{	
		case WASP4G_CME_ERROR_0000: USB.println(F("phone failure")); break;
		case WASP4G_CME_ERROR_0001: USB.println(F("No connection to phone")); break;
		case WASP4G_CME_ERROR_0002: USB.println(F("phone-adaptor link reserved")); break;
		case WASP4G_CME_ERROR_0003: USB.println(F("operation not allowed")); break;
		case WASP4G_CME_ERROR_0004: USB.println(F("operation not supported")); break;
		case WASP4G_CME_ERROR_0005: USB.println(F("PH-SIM PIN required")); break;
		case WASP4G_CME_ERROR_0010: USB.println(F("SIM not inserted")); break;
		case WASP4G_CME_ERROR_0011: USB.println(F("SIM PIN required")); break;
		case WASP4G_CME_ERROR_0012: USB.println(F("SIM PUK required")); break;
		case WASP4G_CME_ERROR_0013: USB.println(F("SIM failure")); break;
		case WASP4G_CME_ERROR_0014: USB.println(F("SIM busy")); break;
		case WASP4G_CME_ERROR_0015: USB.println(F("SIM wrong")); break;
		case WASP4G_CME_ERROR_0016: USB.println(F("incorrect password")); break;
		case WASP4G_CME_ERROR_0017: USB.println(F("SIM PIN2 required")); break;
		case WASP4G_CME_ERROR_0018: USB.println(F("SIM PUK2 required")); break;
		case WASP4G_CME_ERROR_0020: USB.println(F("memory full")); break;
		case WASP4G_CME_ERROR_0021: USB.println(F("invalid index")); break;
		case WASP4G_CME_ERROR_0022: USB.println(F("not found")); break;
		case WASP4G_CME_ERROR_0023: USB.println(F("memory failure")); break;
		case WASP4G_CME_ERROR_0024: USB.println(F("text string too long")); break;
		case WASP4G_CME_ERROR_0025: USB.println(F("invalid characters in text string")); break;
		case WASP4G_CME_ERROR_0026: USB.println(F("dial string too long")); break;
		case WASP4G_CME_ERROR_0027: USB.println(F("invalid characters in dial string")); break;
		case WASP4G_CME_ERROR_0030: USB.println(F("no network service")); break;
		case WASP4G_CME_ERROR_0031: USB.println(F("network time-out")); break;
		case WASP4G_CME_ERROR_0032: USB.println(F("network not allowed - emergency calls only")); break;
		case WASP4G_CME_ERROR_0040: USB.println(F("network personalization PIN required")); break;
		case WASP4G_CME_ERROR_0041: USB.println(F("network personalization PUK required")); break;
		case WASP4G_CME_ERROR_0042: USB.println(F("network subset personalization PIN required")); break;
		case WASP4G_CME_ERROR_0043: USB.println(F("network subset personalization PUK required")); break;
		case WASP4G_CME_ERROR_0044: USB.println(F("service provider personalization PIN required")); break;
		case WASP4G_CME_ERROR_0045: USB.println(F("Service provider personalization PUK required")); break;
		case WASP4G_CME_ERROR_0046: USB.println(F("corporate personalization PIN required")); break;
		case WASP4G_CME_ERROR_0047: USB.println(F("corporate personalization PUK required")); break;
		case WASP4G_CME_ERROR_0100: USB.println(F("unknown")); break;
		case WASP4G_CME_ERROR_0770: USB.println(F("SIM invalid")); break;
		case WASP4G_CME_ERROR_0103: USB.println(F("Illegal MS (#3)*")); break;
		case WASP4G_CME_ERROR_0106: USB.println(F("Illegal ME (#6)*")); break;
		case WASP4G_CME_ERROR_0107: USB.println(F("GPRS service not allowed (#7)*")); break;
		case WASP4G_CME_ERROR_0111: USB.println(F("PLMN not allowed (#11)*")); break;
		case WASP4G_CME_ERROR_0112: USB.println(F("Location area not allowed (#12)*")); break;
		case WASP4G_CME_ERROR_0113: USB.println(F("Roaming not allowed in this location area (#13)*")); break;
		case WASP4G_CME_ERROR_0132: USB.println(F("service option not supported (#32)*")); break;
		case WASP4G_CME_ERROR_0133: USB.println(F("requested service option not subscribed (#33)*")); break;
		case WASP4G_CME_ERROR_0134: USB.println(F("service option temporarily out of order (#34)*")); break;
		case WASP4G_CME_ERROR_0148: USB.println(F("unspecified GPRS error")); break;
		case WASP4G_CME_ERROR_0149: USB.println(F("PDP authentication failure")); break;
		case WASP4G_CME_ERROR_0150: USB.println(F("invalid mobile class")); break;
		case WASP4G_CME_ERROR_0550: USB.println(F("generic undocumented error")); break;
		case WASP4G_CME_ERROR_0551: USB.println(F("wrong state")); break;
		case WASP4G_CME_ERROR_0552: USB.println(F("wrong mode")); break;
		case WASP4G_CME_ERROR_0553: USB.println(F("context already activated")); break;
		case WASP4G_CME_ERROR_0554: USB.println(F("stack already active")); break;
		case WASP4G_CME_ERROR_0555: USB.println(F("activation failed")); break;
		case WASP4G_CME_ERROR_0556: USB.println(F("context not opened")); break;
		case WASP4G_CME_ERROR_0557: USB.println(F("cannot setup socket")); break;
		case WASP4G_CME_ERROR_0558: USB.println(F("cannot resolve DN")); break;
		case WASP4G_CME_ERROR_0559: USB.println(F("time-out in opening socket")); break;
		case WASP4G_CME_ERROR_0560: USB.println(F("cannot open socket")); break;
		case WASP4G_CME_ERROR_0561: USB.println(F("remote disconnected or time-out")); break;
		case WASP4G_CME_ERROR_0562: USB.println(F("connection failed")); break;
		case WASP4G_CME_ERROR_0563: USB.println(F("tx error")); break;
		case WASP4G_CME_ERROR_0564: USB.println(F("already listening")); break;
		case WASP4G_CME_ERROR_0568: USB.println(F("wrong PDP")); break;		
		case WASP4G_CME_ERROR_0615: USB.println(F("FTP not connected")); break;
		case WASP4G_CME_ERROR_0623: USB.println(F("FTP write data closed")); break;
		case WASP4G_CME_ERROR_0643: USB.println(F("FTP communication timeout")); break;
		case WASP4G_CME_ERROR_0657: USB.println(F("Network survey error (No Carrier)*")); break;
		case WASP4G_CME_ERROR_0658: USB.println(F("Network survey error (Busy)*")); break;
		case WASP4G_CME_ERROR_0659: USB.println(F("Network survey error (Wrong request)*")); break;
		case WASP4G_CME_ERROR_0660: USB.println(F("Network survey error (Aborted)*")); break;
		case WASP4G_CME_ERROR_0257: USB.println(F("network rejected request")); break;
		case WASP4G_CME_ERROR_0258: USB.println(F("retry operation")); break;
		case WASP4G_CME_ERROR_0259: USB.println(F("invalid deflected to number")); break;
		case WASP4G_CME_ERROR_0260: USB.println(F("deflected to own number")); break;
		case WASP4G_CME_ERROR_0261: USB.println(F("unknown subscriber")); break;
		case WASP4G_CME_ERROR_0262: USB.println(F("service not available")); break;
		case WASP4G_CME_ERROR_0263: USB.println(F("unknown class specified")); break;
		case WASP4G_CME_ERROR_0264: USB.println(F("unknown network message")); break;
		case WASP4G_CME_ERROR_0680: USB.println(F("LU processing")); break;
		case WASP4G_CME_ERROR_0681: USB.println(F("Network search aborted")); break;
		case WASP4G_CME_ERROR_0682: USB.println(F("PTM mode")); break;
		case WASP4G_CME_ERROR_0683: USB.println(F("Active call state")); break;
		case WASP4G_CME_ERROR_0684: USB.println(F("SSL already activated")); break;
		case WASP4G_CMS_ERROR_0300: USB.println(F("ME failure")); break;
		case WASP4G_CMS_ERROR_0301: USB.println(F("SMS service of ME reserved")); break;
		case WASP4G_CMS_ERROR_0302: USB.println(F("operation not allowed")); break;
		case WASP4G_CMS_ERROR_0303: USB.println(F("operation not supported")); break;
		case WASP4G_CMS_ERROR_0304: USB.println(F("invalid PDU mode parameter")); break;
		case WASP4G_CMS_ERROR_0305: USB.println(F("invalid text mode parameter")); break;
		case WASP4G_CMS_ERROR_0310: USB.println(F("SIM not inserted")); break;
		case WASP4G_CMS_ERROR_0311: USB.println(F("SIM PIN required")); break;
		case WASP4G_CMS_ERROR_0312: USB.println(F("PH-SIM PIN required")); break;
		case WASP4G_CMS_ERROR_0313: USB.println(F("SIM failure")); break;
		case WASP4G_CMS_ERROR_0314: USB.println(F("SIM busy")); break;
		case WASP4G_CMS_ERROR_0315: USB.println(F("SIM wrong ")); break;
		case WASP4G_CMS_ERROR_0316: USB.println(F("SIM PUK required")); break;
		case WASP4G_CMS_ERROR_0317: USB.println(F("SIM PIN2 required")); break;
		case WASP4G_CMS_ERROR_0318: USB.println(F("SIM PUK2 required")); break;
		case WASP4G_CMS_ERROR_0320: USB.println(F("memory failure")); break;
		case WASP4G_CMS_ERROR_0321: USB.println(F("invalid memory index")); break;
		case WASP4G_CMS_ERROR_0322: USB.println(F("memory full")); break;
		case WASP4G_CMS_ERROR_0330: USB.println(F("SMSC address unknown")); break;
		case WASP4G_CMS_ERROR_0331: USB.println(F("no network service")); break;
		case WASP4G_CMS_ERROR_0332: USB.println(F("network time-out")); break;
		case WASP4G_CMS_ERROR_0340: USB.println(F("no +CNMA acknowledgement expected")); break;
		case WASP4G_CMS_ERROR_0500: USB.println(F("unknown error")); break;
		case WASP4G_CME_ERROR_1000: USB.println(F("SSL not activated")); break;
		case WASP4G_CME_ERROR_1001: USB.println(F("SSL certs and keys wrong or not stored")); break;
		case WASP4G_CME_ERROR_1003: USB.println(F("SSL already activated")); break;
		case WASP4G_CME_ERROR_1008: USB.println(F("SSL not connected")); break;		
		default: USB.println(F("UNKNOWN"));	break;
	}
}
#else
void Wasp4G::printErrorCode( uint16_t error )
{	
	USB.print(F("==> ERROR CODE: "));
	USB.println( error, DEC);
}
#endif


// Preinstantiate Objects /////////////////////////////////////////////////////

Wasp4G _4G = Wasp4G();

///////////////////////////////////////////////////////////////////////////////
