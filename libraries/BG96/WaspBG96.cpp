/*! \file BG96.cpp
 *  \brief Library for managing simCom BG96
 *
 *  Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.0
 *  Design:			David Gascón
 *  Implementation:	P.Moreno
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

#include "WaspBG96.h"
#include <inttypes.h>

WaspOneWire oneWireDS(DS2413_ONEWIRE_PIN);

//! class constructor
WaspBG96::WaspBG96()
{
	memset(_apn, '\0', sizeof(_apn));
	memset(_apn_login, '\0', sizeof(_apn_login));
	memset(_apn_password, '\0', sizeof(_apn_password));
	strncpy(_apn, BG96_APN, min(sizeof(_apn), strlen(BG96_APN)));
	strncpy(_apn_login, BG96_LOGIN, min(sizeof(_apn_login), strlen(BG96_LOGIN)));
	strncpy(_apn_password, BG96_PASSW, min(sizeof(_apn_password), strlen(BG96_PASSW)));
	
	memset(_eIDRX_value, '\0', sizeof(_eIDRX_value));	
	strncpy(_eIDRX_value, BG96_eIDRX_value, min(sizeof(_eIDRX_value), strlen(BG96_eIDRX_value)));
	// eIDRX disabled by default
	_eIDRX_status = 0;
	

	// Set "application/x-www-form-urlencoded" as default Content-Type
	//sprintf_P(_contentType, (char*)pgm_read_word(&(table_HTTP[7])));
	
	// assign class pointer to UART buffer
	_buffer = class_buffer;
	_bufferSize = RADIO_BG96_UART_SIZE;
	
}


// Private Methods ////////////////////////////////////////////////////////////



/*
 * Function: This function parses the error code returned by the module. At the
 * point this function is called, the UART is supposed to have received:
 * "+CME ERROR: <err>\r\n" and the first part of the response has been already
 * detected: "+CME ERROR:", so this function needs to parse the error code
 *
 * If error code is parsed succesfully then the attribute _errorCode stores
 * this error information
 *
 * @return	'0' if ok; '1' if error
 */
uint8_t WaspBG96::getErrorCode()
{
	uint8_t status;
	char format[20];

	// wait for " <err>\r\n"
	status = waitFor((char*)"\r\n", 3000);

	if (status == 0)
	{
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("no response\n"));
		#endif
		return 1;
	}
	else
	{
		parseUint32((uint32_t*)&_errorCode, " \r\n");

		#if DEBUG_BG96 > 0
			printErrorCode( _errorCode );
		#endif
		return 0;
	}

}

/*
 * Function: This function parses the error code returned by the module 
 * after executing TCP/IP commands. At the  * point this function is called, 
 * the UART is supposed to have received: "ERROR: <err>\r\n" 
 *
 * @return	'0' if ok; '1' if error
 */
uint8_t WaspBG96::getTCPErrorCode()
{
	uint8_t answer;
	char command_buffer[20];	

	// AT+QIGETERROR\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[5])));
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	PRINT_BG96(F("TCP/IP error code info: "));
	USB.println(_buffer, _length);
	
	if (answer == 1)
		{
			return 99;
		}
	else 
		{
			PRINT_BG96(F("Error getting error code info! "));
			return 100;
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
uint8_t WaspBG96::checkDataConnection(uint8_t time)
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

	//// 2. Check Network Registration Report
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[0])));	//AT+CREG?\r
	strcpy_P(answer1, (char*)pgm_read_word(&(table_AT[1])));	//+CREG: 0,
	do{
		// Sends the command and waits for the answer:
		// 	answer "0,1" for "home network"
		// 	answer "0,5" for "roaming"
		answer = sendCommand(command_buffer, answer1, sBG96_ERROR_CODE, 2000);

		if (answer == 1)
		{
			status = waitFor("\r\n", sBG96_ERROR_CODE, 500);

			if (status == 1)
			{
				parseUint8(&answer, "\r\n");
				#if DEBUG_BG96 > 1
					PRINT_BG96(F("CREG: 0,"));
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
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[2])));	//AT+CGREG?\r
	strcpy_P(answer1, (char*)pgm_read_word(&(table_AT[3])));	//+CGREG: 0,
	do{
		// Sends the command and waits for the answer:
		// 	answer "0,1" for "home network"
		// 	answer "0,5" for "roaming"
		answer = sendCommand(command_buffer, answer1, sBG96_ERROR_CODE, 2000);
		if (answer == 1)
		{
			status = waitFor("\r\n", sBG96_ERROR_CODE, 500);

			if (status == 1)
			{
				parseUint8(&answer, "\r\n");
				#if DEBUG_BG96 > 1
					PRINT_BG96(F("CGREG: 0,"));
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

	//**AQUI HACEMOS UNA CONSULTA A QIACT PARA VER SI TIENE IP. EN CASO DE TENER IP, EL CONTEXT ESTA ACTIVADO Y EL
	//**MODULO ESTA CONECTADO A LA RED.
	//// 4. Check PDP context connection
	// "AT+QIACT?\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[39])));
		#if DEBUGAT > 0
			USB.println(command_buffer);
		#endif
		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
		#if DEBUG_BG96 > 1
			USB.println(_buffer, _length);
		#endif
		
		// check answer
		if (answer == 1)
		{
			//char aux[30];
			char* pointer;
			char* status = "0";
			pointer = strchr((char*)_buffer, ',');

			// skip command name within response buffer
			if (pointer != NULL)
			{
				pointer++;
				_length = strlen(pointer);
				memmove((char*)_buffer, pointer, strlen(pointer));
			}

			// success response format: "\r\n<info>\r\n"			
			answer = parseString(status, sizeof(status), ",");		
			
		 
		#if DEBUG_BG96 > 1
			PRINT_BG96(F("Context status: "));
			USB.println(status);
		#endif
		
		//char aux[30];
			//char* pointer;
			pointer = strchr((char*)_buffer, '"');

			// skip command name within response buffer
			if (pointer != NULL)
			{
				pointer++;
				_length = strlen(pointer);
				memmove((char*)_buffer, pointer, strlen(pointer));
			}

			// success response format: "\r\n<info>\r\n"			
			answer = parseString(_ip, sizeof(_ip), " \"\r\n");		
		}	
		 
		#if DEBUG_BG96 > 1
			PRINT_BG96(F("IP address: "));
			USB.println(_ip);
		#endif


	return 0;
}

/* Function: 	This function checks connection status and connect to data service
 * Parameters:	apn: APN network
 * 				ltem1tband: LTE-M1 network band
 * 				network: Network operator number
 * Return:	0 If the module is connected to data service
 * 			1 Module CFUN OFF error
 * 			2 Setting band parameter error
 * 			3 Setting mode parameter error
 * 			4 Setting PDP context error
 * 			5 Module CFUN ON error 
 */

uint8_t WaspBG96::lteM1Connection(char* apn, char* ltem1tband, char* network, uint8_t operator_type)
{
	uint8_t answer;
	//uint32_t previous, max_time;
	uint8_t status;

	char command_buffer[40];
	char answer1[20];
	char answer2[20];

	answer = 0;
	//max_time = (unsigned long)time * 1000;
	//previous = millis();
	
	//// 1.Modulo desconectado
	// AT+CFUN=0\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[43])), 0);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	//delay(2000);
	
	// 2.Setting band parameter. **SACAR FUERA COMO FUNCION DE CONFIGURACIÓN. 80000.
	answer = setBand("0", ltem1tband, "80000");
	
	#if DEBUG_BG96 > 1
		USB.print(F("nbiotsetband = "));
		USB.println(answer, DEC);
	#endif
	
	if (answer != 0)
	{	
		return 2;
	}
	
	// 3.Setting some AT+QCFG parameters. uint8_t scanMode, char* scanseq, uint8_t iotmode
	answer = setMode(3, "02", 0);
	#if DEBUG_BG96 > 1
		USB.print(F("nbiotsetmode = "));
		USB.println(answer, DEC);
	#endif
	
	if (answer != 0)
	{	
		return 3;
	}	
	
	//// 4.Define PDP Context
	// AT+CGDCONT=1,"IP","<apn>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[29])), apn);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	
	#if DEBUG_BG96 == 2
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
		
		//Checking parameter values.
		sendCommand("AT+CGDCONT?\r", sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);
		//USB.println(answer, DEC);
		USB.println(_buffer, _length);
	#endif
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 4;
	}
	
	//// 5.Modulo conectado
	// AT+CFUN=1\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[43])), 1);
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 5;
	}
	
	//When CFUN=1, waitting a little bit.
	delay(5000);
	
	// 6.Connecting to network. 
	// AT+COPS
	answer = setOperator(network, 8, operator_type);
	if (answer != 0)
	{	
		return 6;
	}
	
	return 0;
}

/* Function: 	This function checks connection status and connect to data service
 * Parameters:	apn: APN network
 * 				nbiotband: NB-IoT network band
 * 				network: Network operator number
 * Return:	0 If the module is connected to data service
 * 			1 Module CFUN OFF error
 * 			2 Setting band parameter error
 * 			3 Setting mode parameter error
 * 			4 Setting PDP context error
 * 			5 Module CFUN ON error
 * 			6 Setting eIDRX parameters error
 * 			7 Network connection error
 */

uint8_t WaspBG96::nbiotConnection(char* apn, char* nbiotband, char* network, uint8_t operator_type)
{
	uint8_t answer;	
	uint8_t status;

	char command_buffer[40];
	char answer1[20];
	char answer2[20];

	answer = 0;
	
	//// 1.Modulo desconectado
	// AT+CFUN=0\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[43])), 0);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	//delay(2000);
	
	// 2.Setting band parameter. 
	answer = setBand("0", "0", nbiotband);
	
	#if DEBUG_BG96 > 1
		USB.print(F("nbiotsetband = "));
		USB.println(answer, DEC);
	#endif
	
	if (answer != 0)
	{	
		return 2;
	}
	
	// 3.Setting some AT+QCFG parameters. uint8_t scanMode, char* scanseq, uint8_t iotmode
	answer = setMode(3, "03", 1);
	#if DEBUG_BG96 > 1
		USB.print(F("nbiotsetmode = "));
		USB.println(answer, DEC);
	#endif
	
	if (answer != 0)
	{	
		return 3;
	}	
	
	//// 4.Define PDP Context
	// AT+CGDCONT=1,"IP","<apn>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[29])), apn);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	
	#if DEBUG_BG96 == 2
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
		
		//Checking parameter values.
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[72])));
		sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);
		//USB.println(answer, DEC);
		USB.println(_buffer, _length);
	#endif
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 4;
	}
	
	//// 5.Modulo conectado
	// AT+CFUN=1\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[43])), 1);
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 5;
	}
	
	//When CFUN=1, waitting a little bit.
	delay(5000);
	
	// eIDRX setup
	answer = settingeIDRX(_eIDRX_status, 5, _eIDRX_value);
	if (answer != 0)
	{
		return 6;
	}
	
	// 6.Connecting to network. 
	// AT+COPS
	answer = setOperator(network, 9, operator_type);
	if (answer != 0)
	{	
		return 7;
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
uint8_t WaspBG96::httpRequest(uint8_t method,
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
//NBIOT
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
 * 			1 if error setting context id
 * 			2 if error sending url
 * 			3 if error sending POST 
 * 			4 if wrong method has been selected
 */
uint8_t WaspBG96::httpRequest(uint8_t method,
							char* url,
							uint16_t port,
							char* resource,
							uint8_t* data,
							uint16_t length)
{
	uint8_t answer;
	char command_buffer[500];
	char aux[3];
	char datapacket[500];
	
	memset( aux, '\0', sizeof(aux) );
	memset( datapacket, '\0', sizeof(datapacket) );
	
	//Construct new url using host:port.
	char urlport[50];
	snprintf(urlport, 50, "%s:%u", url, port);
	
	// Step1: Configure HTTP parameters: contextid
	// Generate: AT+QHTTPCFG=“contextid”, 1
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[6])), 1);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR, sBG96_ERROR_CODE, 1000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif

	if (answer == 2)
	{
		_errorCode = BG96_ERROR_MESSAGE;
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
		_errorCode = BG96_ERROR_TIMEOUT;
		return 1;
	}


	// Step2: Perform the request depending on the method selected as input
	// in the function: GET or POST
	if (method == WaspBG96::HTTP_GET)
	{			
		//Construct the data.
		sprintf_P(datapacket, (char*)pgm_read_word(&(table_HTTP[12])), urlport, resource, data);
		#if DEBUG_BG96 == 2
			USB.print(F("Packet structure: "));
			USB.println(datapacket);
			USB.println(strlen(datapacket));	
		#endif
		
		// Set respondheader
		// "AT+QHTTPCFG=\"responseheader\",%u\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[7])), 1);

		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR, 1000);
		
		
		//send the http request.
		// Set respondheader
		// "AT+QHTTPURL=%u,%u\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[8])), (strlen(datapacket)-1), BG96_HTTP_TIMEOUT);

		// send command
		answer = sendCommand(command_buffer, "CONNECT", sBG96_ERROR, 10000);
		
		answer = sendCommand(datapacket, sBG96_OK, sBG96_ERROR, 10000);
		#if DEBUG_BG96 == 2
			USB.print(F("Answer value: "));
			USB.println(answer, DEC);
			USB.println(_buffer, _length);	
		#endif
		if (answer == 1)
		{
			return 0;
		}
	
	}
	else if (method == WaspBG96::HTTP_POST)			
	{
		
		//Construct the data.
		sprintf_P(datapacket, (char*)pgm_read_word(&(table_HTTP[12])), urlport, resource, NULL);
		#if DEBUG_BG96 == 2
			USB.print(F("Packet structure: "));
			USB.println(datapacket);
			USB.println(strlen(datapacket));	
		#endif
		
		// 2a. Send HTTP POST or PUT request
		// "AT+QHTTPURL=%u,%u\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[8])), (strlen(datapacket)), BG96_HTTP_TIMEOUT);

		// send command
		answer = sendCommand(command_buffer, "CONNECT", sBG96_ERROR, 10000);
		
		answer = sendCommand(datapacket, sBG96_OK, sBG96_ERROR, 10000);
		#if DEBUG_BG96 == 2
			USB.print(F("Answer value: "));
			USB.println(answer, DEC);
			USB.println(_buffer, _length);	
		#endif
		if (answer =! 1)
		{
			return 2;
		}

		// wait a little bit
		delay(100);

		// 3a. Send HTTP POST
		// "AT+QHTTPPOST=%u,%u,60\r" 
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[11])), length, BG96_HTTP_TIMEOUT);

		// send command
		answer = sendCommand(command_buffer, "CONNECT", sBG96_ERROR, 15000);
		
		answer = sendCommand((char*)data, sBG96_OK, sBG96_ERROR, 15000);
		#if DEBUG_BG96 == 2
			USB.print(F("Answer value: "));
			USB.println(answer, DEC);
			USB.println(_buffer, _length);	
		#endif
		if (answer != 1)
		{
			return 3;
		}

		return 0;
	}
	else if (method == WaspBG96::HTTP_POST_FRAME)
	{
		char resource[27];
		//Construct the data.
		sprintf_P(resource, (char*)pgm_read_word(&(table_HTTP[0])));
		sprintf_P(datapacket, (char*)pgm_read_word(&(table_HTTP[12])), urlport, resource, NULL);
		#if DEBUG_BG96 == 2
			USB.print(F("Packet structure: "));
			USB.println(datapacket);
			USB.println(strlen(datapacket));	
		#endif
		
		// 2a. Send HTTP POST or PUT request
		//"AT+QHTTPURL=%u,%u\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[8])), (strlen(datapacket)), BG96_HTTP_TIMEOUT);

		// send command
		answer = sendCommand(command_buffer, "CONNECT", sBG96_ERROR, 15000);
		
		answer = sendCommand(datapacket, sBG96_OK, sBG96_ERROR, 10000);
		#if DEBUG_BG96 == 2
			USB.print(F("Answer value: "));
			USB.println(answer, DEC);
			USB.println(_buffer, _length);	
		#endif
		if (answer != 1)
		{
			return 2;
		}
		#if DEBUG_BG96 == 2
			USB.print(F("data: ")); USB.println(data, length);
			USB.print(F("SIZE: ")); USB.println(length);
		#endif
		
		char  datahex[500];	
		memset( datahex, 0x00, sizeof(datahex) );	
			
		for(uint16_t x = 0; x < length; x++)
		{
		  // make conversion from byte to hex representation in ASCII (2Bytes)
		  Utils.hex2str((uint8_t*)&data[x], aux, 1);    
		  strncat( datahex, aux, 2 );
		}

		// wait a little bit
		//delay(100);
		memset( datapacket, 0x00, sizeof(datapacket) );
		
		sprintf_P(resource, (char*)pgm_read_word(&(table_HTTP[1])));
		sprintf_P(datapacket, (char*)pgm_read_word(&(table_HTTP[12])), resource, datahex, NULL);
		#if DEBUG_BG96 == 2
			USB.print(F("Packet structure: "));
			USB.println(datapacket);
			USB.println(strlen(datapacket));	
		#endif

		// 3a. Send HTTP POST 
		// "AT+QHTTPPOST=%u,%u,60\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[11])), strlen(datapacket), BG96_HTTP_TIMEOUT);

		// send command
		answer = sendCommand(command_buffer, "CONNECT", sBG96_ERROR, 15000);
		
		answer = sendCommand(datapacket, sBG96_OK, sBG96_ERROR, 15000);
		#if DEBUG_BG96 == 2
			USB.print(F("Answer value: "));
			USB.println(answer, DEC);
			USB.println(_buffer, _length);	
		#endif
		if (answer != 1)
		{
			return 3;
		}

		return 0;
	}

}

/* This function waits the URC code and reads the data availble
 * Parameters:	wait_timeout: timeout for URC *
 *	Return:	0 if OK
 * 			1 if timeout waiting HTTP GET response
 * 			2 if timeout waiting HTTP POST response
 * 			3 if error waiting response
 * 			4 if error reading the response
 * 			5,6 if error reading the response
 * 			7 error waiting response function
 * 			
 */
uint8_t WaspBG96::httpWaitResponse(uint8_t method, uint32_t wait_timeout)
{
	char* pointer;
	uint8_t answer;
	uint16_t data_size;
	char command_buffer[50];
		
	
	if (method == WaspBG96::HTTP_GET){
		// "AT+QHTTPGET=%u\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[9])), BG96_HTTP_TIMEOUT);

		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR, 2000);
		
		answer = waitFor("+QHTTPGET: ", (wait_timeout*1000));
		if (answer == 0)
		{
			return 1;
		}
	}
	else if ((method == WaspBG96::HTTP_POST)||(method == WaspBG96::HTTP_POST_FRAME))
	{
		answer = waitFor("+QHTTPPOST: ", (wait_timeout*1000));
		if (answer == 0)
		{
			return 2;
		}		
	}
	// 2. Read the whole response: "+QHTTPGET: <http_status_code>,<content_type>,<data_size>\r
	answer = waitFor("\r", 5000);
	if (answer == 0)
	{
		return 3;
	}

	pointer = strtok((char*)_buffer, ",");
	
	// 3. Skip <status_code> - 0 Operation successful
	pointer = strtok(NULL, ",");
	
	
	/* 4. Read <http_status_code>
	 * 200 - OK
	 * 403 - FORBIDDEN
	 * 404 - NOT FOUND
	 * 409 - CONFLICT
	 * 411 - LENGTH REQUIRED
	 * 500 - INTERNAL SERVER ERROR
	 */
	_httpCode = atoi(pointer);
	pointer = strtok(NULL, ",");
	
	// 5. Read <data_size>
	data_size = atoi(pointer);
	pointer = strtok(NULL, ",");
	
	
	// 6. Read data received
	if (data_size >= 0)
	{
		// AT+QHTTPREAD=<wait_time*1000>
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[10])), (BG96_HTTP_TIMEOUT));

		// send command
		answer = sendCommand(command_buffer, "CONNECT", sBG96_ERROR, 10000);

		// check answer
		if (answer == 1)
		{
			// Read the data
			answer = waitFor("+QHTTPREAD: 0", 10000);
			if (answer == 0)
			{
				return 4;
			}

			// Add end of string in _buffer
			_buffer[_length] = '\0';

			return 0;
		}
		else if (answer == 2)
		{
			return 5;
		}
		else
		{
			// Timeout
			return 6;
		}
	}

	return 7;
}

/* Function: 	This function gets the status of a TCP or UDP socket
 * Parameters:	socketId: number of the socket Id
 * Return:		0: ok; 1: error
 */
uint8_t WaspBG96::getSocketStatus(uint8_t socketId)
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
	memset(socketStatus[socketId].service_type, 0x00, sizeof(socketStatus[socketId].service_type));

	// AT+QISTATE=<socketID>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[1])),	1, socketId);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);

	// check answer
	if(answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 3 )
		{
			getTCPErrorCode();
		}
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Error getting socket status\n"));
		#endif
		return 1;
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("_buffer:"));
		USB.println((char*)_buffer);
	#endif
	
	// Parse the response	
	// seek pattern in module response
	// the response is something similar to this:
	// List of (+QISTATE:<connectID>,<service_type>,<IP_address>,<remote_port>,<local_port>,<socket_state>,<contextID>,<serverID>,<access_mode>,<AT_port>)
	pointer = strstr((char*)_buffer, "+QISTATE:");

	if (pointer == NULL)
	{
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Error: Socket not open or null pointer1\n"));
		#endif
		return 1;
	}
	#if DEBUG_BG96 > 0
		USB.println(pointer);
	#endif
	

	// find first value skipping delimiters
	pointer = strtok(pointer, "+QISTATE: \",\r\n");

	// iterate through response
	for (int i = 0; i < 10; i++)
	{
		
		if (pointer == NULL)
		{
			#if DEBUG_BG96 > 0
				PRINT_BG96(F("Error: null pointer2\n"));
			#endif
			return 1;
		}
		

		if (i == 0)
		{
			socketStatus[socketId].id = (uint8_t) strtoul( pointer, NULL, 10);
		}
		else if (i == 1)
		{	
			//socketStatus[socketId].service_type = (uint8_t) strtoul( pointer, NULL, 10);
			strncpy(socketStatus[socketId].service_type, pointer, sizeof(socketStatus[socketId].service_type));			
		}
		
		else if (i == 2)
		{
			strncpy(socketStatus[socketId].remoteIp, pointer, sizeof(socketStatus[socketId].remoteIp));
			
		}
		else if (i == 3)
		{
			socketStatus[socketId].remotePort = (uint16_t) strtoul( pointer, NULL, 10);
		}
		else if (i == 4)
		{
			socketStatus[socketId].localPort = (uint16_t) strtoul( pointer, NULL, 10);
		}
		//Socket_state info:
		//0 “Initial”: connection has not been established
		//1 “Opening”: client is connecting or server is trying to listen
		//2 “Connected”: client/incoming connection has been established
		//3 “Listening”: server is listening
		//4 “Closing”: connection is closing
		else if (i == 5)
		{
			socketStatus[socketId].state = (uint16_t) strtoul( pointer, NULL, 10);			
		}
		
		// i=6 - Skip <contextID> parameter.
		// i=7 - Skip <serverID> parameter.
		// i=8 - Skip <acces_mode> parameter.
		// i=9 - Skip <AT_port> parameter.
		
		#if DEBUG_BG96 > 1
			USB.println(pointer);
		#endif
		pointer = strtok (NULL, " \",\r\n");
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("socketStatus.id:"));
		USB.println(socketStatus[socketId].id, DEC);
		PRINT_BG96(F("socketStatus.state:"));
		USB.println(socketStatus[socketId].state, DEC);
		if (socketStatus[socketId].state != 0)
		{
			PRINT_BG96(F("socketStatus.service_type:"));
			USB.println(socketStatus[socketId].service_type);
			PRINT_BG96(F("socketStatus.localPort:"));
			USB.println(socketStatus[socketId].localPort, DEC);
			PRINT_BG96(F("socketStatus.remoteIp:"));
			USB.println(socketStatus[socketId].remoteIp);
			PRINT_BG96(F("socketStatus.remotePort:"));
			USB.println(socketStatus[socketId].remotePort, DEC);
		}
	#endif

	return 0;

}


/* Function: 	This function gets the status of a TCP or UDP socket
 * Parameters:	socketId: number of the socket Id
 * Return:		0: ok; 1: error
 */
uint8_t WaspBG96::getSocketStatusSSL(uint8_t socketId)
{
	uint8_t answer;
	char delimiters[20];
	char command_buffer[20];
	char *pointer;
	
	// clear structure
	socketStatusSSL[socketId].id = 0;
	socketStatusSSL[socketId].state = 0;
	socketStatusSSL[socketId].localPort = 0;
	socketStatusSSL[socketId].remotePort = 0;
	memset(socketStatusSSL[socketId].remoteIp, 0x00, sizeof(socketStatusSSL[socketId].remoteIp));


		//  AT+QISSLSTATE=<socketID>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[6])), socketId);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);

	// check answer
	if(answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 3 )
		{
			getTCPErrorCode();
		}
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Error getting socket status\n"));
		#endif
		return 1;
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("_buffer:"));
		USB.println((char*)_buffer);
	#endif
	
	// Parse the response	
	// seek pattern in module response
	// the response is something similar to this:
	// List of (+QSSLSTATE:<clientID>,“SSLClient”,<IP_address>,<remote_port>,<local_port>,<socket_state>,<pdpctxID>,<serverID>,<access_mode>,<AT_port>,<sslctxID>
	strcpy_P(delimiters, (char*)pgm_read_word(&(table_SSL[7])));
	pointer = strstr((char*)_buffer, delimiters);
	//pointer = strstr((char*)_buffer, "+QISTATE:");

	if (pointer == NULL)
	{
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Error: Socket not open or null pointer1\n"));
		#endif
		return 1;
	}
	#if DEBUG_BG96 > 0
		USB.println(pointer);
	#endif
	

	// find first value skipping delimiters
	strcpy_P(delimiters, (char*)pgm_read_word(&(table_SSL[12])));
	//pointer = strstr((char*)_buffer, delimiters);
	//pointer = strtok(pointer, "+QISTATE: \",\r\n");
	pointer = strtok(pointer, delimiters);

	// iterate through response
	for (int i = 0; i < 10; i++)
	{
		
		if (pointer == NULL)
		{
			#if DEBUG_BG96 > 0
				PRINT_BG96(F("Error: null pointer2\n"));
			#endif
			return 1;
		}
		

		if (i == 0)
		{
			socketStatusSSL[socketId].id = (uint8_t) strtoul( pointer, NULL, 10);
		}
		// i=1 - Skip “SSLClient” 
		else if (i == 2)
		{	
			strncpy(socketStatusSSL[socketId].remoteIp, pointer, sizeof(socketStatusSSL[socketId].remoteIp));
		}
		
		else if (i == 3)
		{
			socketStatusSSL[socketId].remotePort = (uint16_t) strtoul( pointer, NULL, 10);
			
		}
		else if (i == 4)
		{
			socketStatusSSL[socketId].localPort = (uint16_t) strtoul( pointer, NULL, 10);
		}		
		//Socket_state info:
		//0 “Initial”: connection has not been established
		//1 “Opening”: client is connecting or server is trying to listen
		//2 “Connected”: client/incoming connection has been established
		//3 “Listening”: server is listening
		//4 “Closing”: connection is closing
		else if (i == 5)
		{
			socketStatusSSL[socketId].state = (uint16_t) strtoul( pointer, NULL, 10);			
		}
		
		// i=6 - Skip <pdpctxID> parameter.
		// i=7 - Skip <serverID> parameter.
		// i=8 - Skip <acces_mode> parameter.
		// i=9 - Skip <AT_port> parameter.
		// i=9 - Skip <sslctxID> parameter.
		
		#if DEBUG_BG96 > 1
			USB.println(pointer);
		#endif
		pointer = strtok (NULL, " \",\r\n");
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("SocketStatusSSL.id:"));
		USB.println(socketStatusSSL[socketId].id, DEC);
		PRINT_BG96(F("SocketStatusSSL.state:"));
		USB.println(socketStatusSSL[socketId].state, DEC);
		if (socketStatusSSL[socketId].state != 0)
		{
			PRINT_BG96(F("SocketStatusSSL.localPort:"));
			USB.println(socketStatusSSL[socketId].localPort, DEC);
			PRINT_BG96(F("SocketStatusSSL.remoteIp:"));
			USB.println(socketStatusSSL[socketId].remoteIp);
			PRINT_BG96(F("SocketStatusSSL.remotePort:"));
			USB.println(socketStatusSSL[socketId].remotePort, DEC);
		}
	#endif

	return 0;

}

// Public Methods /////////////////////////////////////////////////////////////

/* Function: 	This function inits the BG96 module
 * Return:	0 if OK
 * 			1 for no comunication
 * 			2 if error switching CME errors to numeric response
 * 			3 if error disabling the echo from the module 
 * 			4 if no DS2413 was detected
 * 			5 if is not a DS2413
 */
uint8_t WaspBG96::ON()
{
	uint8_t counter;
	uint8_t answer;
	char command_buffer[50];

	// set UART0 multiplexer to Socket0
	//Utils.setMuxSocket0();
	
	// set UART1 multiplexer to Socket1
	Utils.setMuxSocket1();

	// Set UART
	//_uart = UART0;
	_uart = SOCKET1;
	_baudrate = sBG96_RATE;
	beginUART();
	
	//Switch ON
	pinMode(GPRS_PW,OUTPUT);
	
	for (int i = 0; i<5; i++){
		
		digitalWrite(GPRS_PW,HIGH);
		delay(0.1);
		digitalWrite(GPRS_PW,LOW);
		delay(0.02);
	}
	digitalWrite(GPRS_PW,HIGH);
	delay(1000);
	//delayMicroseconds(500);
	
	
	// Try to find a device on the bus *
	  oneWireDS.reset_search();
	  delay(250);
	  if (!oneWireDS.search(addressDS)) 
	  {
		#if DEBUG_DS2413 > 0
			USB.print(F("DS2413 address:"));
			printBytes(addressDS, 8);
		#endif

		#if DEBUG_DS2413 > 0
			USB.println(F("No device found on the bus!"));
		#endif
		oneWireDS.reset_search();
		return 4;
	  }
	 
	 #if DEBUG_DS2413 > 0
		 USB.print(F("DS2413 chip found on address: "));
		 for(int i=0; i<8;i++)
		 {
		  USB.print(addressDS[i],HEX);
		  USB.print(F(" "));
		 }
		  USB.println();
	  #endif

	  // Make sure we have a DS2413 
	  if (addressDS[0] != DS2413_FAMILY_ID) 
	  {
		#if DEBUG_DS2413 > 0
			USB.print(F("DS2413 address:"));
			printBytes(addressDS, 8);
		#endif

		#if DEBUG_DS2413 > 0
			USB.println(F(" is not a DS2413!"));
		#endif
		return 5;
	  }
	  
	  #if DEBUG_DS2413 > 0
		USB.println(F("IOs en estado alto"));
	  #endif
	  write(0x03);
	  #if DEBUG_DS2413 > 0  
		USB.print(F("IO_A = PWRKEY - Pulso - low"));
	  #endif	  
	  write(0x02);
	  delay(1000);
	  #if DEBUG_DS2413 > 0
		USB.println(F(" - high.")); 
	  #endif
	  write(0x03);
	  
	  
	  //Waitting a little bit to module start.
	  delay(10000);
	
	
	// Check communication with the module sending a basic AT command
	counter = 15;
	answer = 0;
	while ((counter > 0) && (answer == 0))
	{
		answer = sendCommand("AT\r", sBG96_OK, 1000);
		counter--;
	}

	if (answer == 0)
	{
		// No comunication with the module
		// Power off and return an error
		//PWR.powerSocket(_uart, LOW);		//SOCKET0
		digitalWrite(GPRS_PW, LOW);

		// Error code for no communication
		return 1;
	}


	// Set Report Mobile Equipment Error (CMEE)
	counter = 3;
	answer = 0;
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[19])));	//AT+CMEE=1\r
	while ((counter > 0) && (answer == 0))
	{
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR, 500);
		counter--;
	}
	if (answer != 1)
	{
		// Error switching CME errors to numeric response
		// Power off and return an error
		PWR.powerSocket(_uart, LOW);

		// Error code for error switching CME errors to numeric response
		return 2;
	}


	// Disable command echo
	counter = 3;
	answer = 0;
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[20])));	//ATE0\r
	while ((counter > 0) && (answer == 0))
	{
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR, 500);
		counter--;
	}
	if (answer != 1)
	{
		// Error disabling the echo from the module
		// Power off and return an error
		PWR.powerSocket(_uart, LOW);

		// Error code disabling the echo from the module
		return 3;
	}

	return 0;
}

/* Function: 	This function powers off the LE910 module
 * Return:	 nothing
 */
uint8_t WaspBG96::OFF()
{
	uint8_t answer;
	uint8_t status = 0;
	uint8_t counter = 3;
	char command_buffer[20];

	// "AT+CPOWD=1\r"
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[44])));

	// send command
	//answer = sendCommand(command_buffer, sBG96_OK, 2000);

	// Software Shut Down
	/*
	while ((counter > 0) && (status == 0))
	{
		status = sendCommand(command_buffer, sBG96_OK, 2000);
		
		waitFor(sBG96_PWDOWN, sBG96_ERROR_CODE, sBG96_ERROR, 10000);
		counter--;
	}*/
	
	status = sendCommand(command_buffer, sBG96_OK, 2000);
		
	answer = waitFor(sBG96_PWDOWN, sBG96_ERROR_CODE, sBG96_ERROR, 10000);
	
	// check response
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	delay(5000);
	
	// close UART1	
	_uart = SOCKET1;	
	closeUART();

	// Switch OFF.	
	digitalWrite(GPRS_PW,LOW);	
	
	return 0;
}

/* Function: 	This function sets a PIN / PUK code
 * Parameters: code: string with the requested code
 * Return:	0 if OK
 * 			1 if error
 */
uint8_t WaspBG96::enterPIN(char* code)
{
	return enterPIN(code, NULL);
}

/* Function: 	This function sets a PIN / PUK code
 * Parameters:
 * 		code: string with the requested code
 * 		new_code: string with the new code (only for SIM PUK or SIM PUK2)
 * Return:	0 if OK, 1 if error
 */
uint8_t WaspBG96::enterPIN(char* code, char* new_code)
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
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);

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
uint8_t WaspBG96::checkPIN()
{
	char command_buffer[20];
	char command_answer[20];
	uint8_t answer;

	// command: AT+CPIN?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_PIN[0])));

	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);
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

/* Function: This function send one AT command to the module and get the answer.
 * Return:
 * 		0 for OK and 1 for NOK. 
 */
uint8_t WaspBG96::sendATcommand(char* ATcommand, char* ATanswer, uint16_t timeout)
{
	char command_buffer[50];
	char command_answer[20];
	uint8_t answer;
	USB.print(F("Manual AT: "));
	USB.println(ATcommand);
	// command: AT command\r
	snprintf(command_buffer, sizeof(command_buffer), "%s\r", ATcommand);

	answer = sendCommand(command_buffer, ATanswer, sBG96_ERROR, timeout);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 255;
	}

	return 0;
}



/* Function: 	This function checks connection status
 * Parameters:	time: max allowed time in seconds to connect
 * Return:	0 If the module is connected to the network
 * 			1 not registered, ME is not currently searching for a new operator to register to
 * 			2 not registered, but ME is currently searching for a new operator to register to
 * 			3 registration denied
 * 			4 unknown
 */
uint8_t WaspBG96::checkConnection(uint8_t time)
{
	uint8_t answer;
	uint8_t status;
	uint8_t value;
	uint32_t previous;

	char command_buffer[40];
	char command_answer[20];

	answer = 0;
	previous = millis();

	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[0])));		//AT+CREG?\r
	strcpy_P(command_answer, (char*)pgm_read_word(&(table_AT[1])));		//+CREG: 0,

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
			#if DEBUG_BG96 > 1
				PRINT_BG96(F("Break condition\n"));
				PRINT_BG96(F("answer:"));
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

	if (((answer != 1) && (answer != 5)) || ((millis() - previous) > (uint32_t) time * 1000))
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
uint8_t WaspBG96::checkConnectionEPS(uint8_t time)
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
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[41])));

	//// 2. Generate answer
	// "+CEREG: 0,"
	strcpy_P(command_answer, (char*)pgm_read_word(&(table_AT[42])));

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

		answer = sendCommand(command_buffer, command_answer, sBG96_ERROR_CODE, 2000);

		if (answer == 1)
		{
			// get whole response
			status = waitFor(sBG96_OK, 500);

			if (status == 1)
			{
				parseUint8(&status, "\r\n OK");
				#if DEBUG_BG96 > 1
					PRINT_BG96(F("----> status:"));
					USB.println(status,DEC);
				#endif
			}
		}

		// check status from response
		if ((status == 1) || (status == 5))
		{
			#if DEBUG_BG96 > 1
				PRINT_BG96(F("Break condition\n"));
				PRINT_BG96(F("status:"));
				USB.println(status,DEC);
			#endif
			break;
		}
		else if (status == 2)
		{
			// continue waiting for correct response
			#if DEBUG_BG96 > 0
				PRINT_BG96(F("Continue waiting for correct response\n"));
			#endif
		}

		delay(1000);

		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < previous) previous = millis();

		// check timeout error
		if ((millis() - previous) > ((uint32_t)time * 1000))
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

/*
 * 
 * 
 * 
 */
uint8_t WaspBG96::gprsConnection(char* apn, char* gprsband, char* network, uint8_t operator_type)
{
	uint8_t answer;	
	uint8_t status;

	char command_buffer[40];
	char answer1[20];
	char answer2[20];

	answer = 0;
	
	
	//// 1.Network disabled
	// AT+CFUN=0\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[43])), 0);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	//delay(2000);
	
	// 2.Setting band parameter. **SACAR FUERA COMO FUNCION DE CONFIGURACIÓN.
	answer = setBand(gprsband, "0", "80000");
	
	#if DEBUG_BG96 > 1
		USB.print(F("GPRS setBand = "));
		USB.println(answer, DEC);
	#endif
	
	if (answer != 0)
	{	
		return 2;
	}
	
	// 3.Setting module to GSM network.
	answer = setMode(1, "01", 1);
	#if DEBUG_BG96 > 1
		USB.print(F("setMode = "));
		USB.println(answer, DEC);
	#endif
	
	if (answer != 0)
	{	
		return 3;
	}	
	
	
	//Befor do set_APN();
	//// 4.Define PDP Context
	// AT+CGDCONT=1,"IP","<apn>"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[29])), apn);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	
	#if DEBUG_BG96 == 2
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
		
		//Checking parameter values.
		sendCommand("AT+CGDCONT?\r", sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);
		//USB.println(answer, DEC);
		USB.println(_buffer, _length);
	#endif
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 4;
	}
	
	
	// AT+QICSGP=<contextID>[,<context_t ype>,<APN>[,<username>,<passwor d>)[,<authentication>]]]
	// "AT+QICSGP=1,1,\"%s\",\"%s\",\"%s\",1\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[36])), _apn, _apn_login, _apn_password);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 15000);

	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 5;
	}
	
	//// 5.Modulo conectado
	// AT+CFUN=1\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[43])), 1);
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	//USB.println(_buffer, _length);	
	//USB.println(answer, DEC);
	//USB.println(_buffer, _length);
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 6;
	}
	
	//When CFUN=1, waitting a little bit.
	delay(5000);
	
	// 6.Connecting to network. 
	// AT+COPS
	answer = setOperator(network, 0, operator_type);
	if (answer != 0)
	{	
		return 7;
	}
	
	return 0;
}





/*
 *
 *
 */
uint8_t WaspBG96::gprsContextActivation(uint8_t mode)
{
	uint8_t answer;
	char command_buffer[20];
	
	/*
	// AT+QICSGP=<contextID>[,<context_t ype>,<APN>[,<username>,<passwor d>)[,<authentication>]]]
	// "AT+QICSGP=1,1,\"%s\",\"%s\",\"%s\",1\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[36])), _apn, _apn_login, _apn_password);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 15000);

	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("GPRS context activation:"));
		USB.println(mode, DEC);
	#endif
	*/
	
	answer = contextActivation(mode,5);
	
	if (answer != 0)
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
 * CONNECT TO THE Network - (Context Activation)
 * Parameters: mode: 1 - Activate; 0 - Deactivated
 * 			   retries: Retries for context activation
 * Return: 0 If OK or 1 If error
 *
 */
uint8_t WaspBG96::contextActivation(uint8_t mode, uint8_t retries)
{
	uint8_t answer;
	char command_buffer[15];	
	//uint8_t counter = 15;
	answer = 0;
	
	while ((retries > 0) && (answer != 1))
	{
		// "AT+QIACT=<mode>\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[38])), mode);
		#if DEBUGAT > 0
			USB.println(command_buffer);
		#endif
		
		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
		#if DEBUG_BG96 > 1
			USB.println(answer);
			USB.println(_buffer, _length);
		#endif
		
		retries--;
		delay(1000);
	}
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Context activation:"));
		USB.println(mode, DEC);
	#endif
	
	if (mode == 1)
	{
		// "AT+QIACT?\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[39])));
		#if DEBUGAT > 0
			USB.println(command_buffer);
		#endif
		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
		#if DEBUG_BG96 > 1
			USB.println(_buffer, _length);
		#endif
		
		// check answer
		if (answer == 1)
		{
			char aux[30];
			char* pointer;
			pointer = strchr((char*)_buffer, '"');

			// skip command name within response buffer
			if (pointer != NULL)
			{
				pointer++;
				_length = strlen(pointer);
				memmove((char*)_buffer, pointer, strlen(pointer));
			}

			// success response format: "\r\n<info>\r\n"			
			answer = parseString(_ip, sizeof(_ip), " \"\r\n");		
		}	
		 
		#if DEBUG_BG96 > 1
			PRINT_BG96(F("IP address: "));
			USB.println(_ip);
		#endif
	}
	
	return 0;
}

/*
 * SETUP GPRS/NB-IOT BAND
 * at+qcfg="band",0,<gprsband>,<nbiotband>,1 // Configuracion para la banda 20=80000  ** Generar tabla para facilitar la config
 */
uint8_t WaspBG96::setBand(char* gprsband, char* catm1band, char* nbiotband)
{
	uint8_t answer;
	char command_buffer[40];

	// "AT+CBANDCFG="NB-IOT",<band>\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[53])), gprsband, catm1band, nbiotband);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);
	
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
		
		//Verificar que valores tiene el parametro.
		answer = sendCommand("AT+QCFG=\"band\"\r", sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);
		USB.println(answer, DEC);
		USB.println(_buffer, _length);
	#endif

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
 * SETUP NB-IOT MODE 
 * Configure RAT(s) to be Searched
 * 0 Automatic, 1 GSM only, 3 LTE only.
 */
uint8_t WaspBG96::setMode(uint8_t scanMode, char* scanseq, uint8_t iotmode)
{
	uint8_t answer;
	char command_buffer[40];

	// "AT+QCFG="nwscanmode",3,1\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[60])), scanMode);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);
		
		//Verificar que valores tiene el parametro.
		sendCommand("AT+QCFG=\"nwscanmode\"\r", sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

		USB.println(_buffer, _length);
	#endif

	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	// "at+qcfg="nwscanseq",03,1\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[61])), scanseq);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
		
		//Verificar que valores tiene el parametro.
		sendCommand("AT+QCFG=\"nwscanseq\"\r", sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

		USB.println(_buffer, _length);
	#endif
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 2;
	}
	
	// at+qcfg="iotopmode",<mode>,1\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[62])), iotmode);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
		
		//Verificar que valores tiene el parametro.
		sendCommand("AT+QCFG=\"iotopmode\"\r", sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

		USB.println(_buffer, _length);
	#endif
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 3;
	}
	
	// at+qcfg="servicedomain",1,1\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[56])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);;	
		
		//Verificar que valores tiene el parametro.
		sendCommand("AT+QCFG=\"servicedomain\"\r", sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

		USB.println(_buffer, _length);
	#endif
	
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

/*
 * SETUP NB-IOT OPERATOR - Set operator manualy 
 * +COPS: Operator list
 * Parameter: operatornumber: Numeric <oper>. GSM/LTE location area identification number.
 * 			  Act: Access technology selected. Values 0- GSM, 8 - LTE CatM1, 9 - LTE Cat NB1.
 * Return 0 if is OK - 1 if error is occurried
 */
uint8_t WaspBG96::setOperator(char* operatornumber, uint8_t Act, uint8_t operator_type)
{
	uint8_t answer;
	char command_buffer[30];
	
	if (operatornumber == 0)
	{		
		// "AT+COPS=0\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[52])));
		#if DEBUGAT > 0 
			USB.println(command_buffer); 
		#endif
		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 30000);
		#if DEBUG_BG96 > 1
			PRINT_BG96(F("NB-IoT set operator (0 - Default):"));
			USB.println(_buffer, _length);
		#endif
	}
	else
	{
		// "AT+COPS=1,2,""<operatornumber>",<Act>\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[59])), operator_type, operatornumber, Act);
		#if DEBUGAT > 0 
			USB.println(command_buffer); 
		#endif		
		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 30000);
		#if DEBUG_BG96 > 1
			PRINT_BG96(F("NB-IoT set operator:"));
			USB.println(_buffer, _length);
		#endif
	}

	#if DEBUG_BG96 > 1	
		PRINT_BG96(F("NB-IoT operator selected:"));
		
		// "AT+COPS?"\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[24])));

		// send command
		sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
		USB.println(_buffer, _length);		
	#endif

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
 * SETUP NB-IOT Preferred selection between CAT-M and NB-IoT
 * +CMNB: ((1-Cat-M),(2-NB-IoT),(3-Cat-M And NB-IoT))
 * Parameter: mode: (1-Cat-M),(2-NB-IoT),(3-Cat-M And NB-IoT)
 * Return: 0 if is OK and 1 if error has ocurried
 */
uint8_t WaspBG96::nbiotprefermode(uint8_t mode)
{
	uint8_t answer;
	char command_buffer[20];

	// "AT+CNMP=<mode>\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[55])), mode);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 15000);
	
	char aux[30];

	// success response format: "\r\n<info>\r\n"
	answer = parseString(aux, sizeof(aux), " \r\n");

	if (answer == 0)
	{
		memset(_buffer, 0x00 ,sizeof(_buffer));
		_length = strlen(aux);
		strncpy((char*)_buffer, aux, strlen(aux));

		#if DEBUG_BG96 > 1
			PRINT_BG96(F("NB-IoT or Cat-M selection:"));
			USB.println(mode, DEC);
		#endif

		return 0;
	}

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
 * SETUP NB-IOT setting parameters PSM (Power Save Mode)
 * AT+CPSMS=0,,,"<_PeriodicTAU>","<_ActiveTimer>"
 * Parameters: PeriodicTAU: Time value in binary format
 * 			   ActiveTimer: Time value in binary format
 * Return: 0 if is OK and 1 if error has ocurried
 */
uint8_t WaspBG96::nbiotSettingPSM(char* PeriodicTAU, char* ActiveTimer)
{
	uint8_t answer;
	char command_buffer[40];
	
	memset(_PeriodicTAU, '\0', sizeof(_PeriodicTAU));
	memset(_ActiveTimer, '\0', sizeof(_ActiveTimer));	

	strncpy(_PeriodicTAU, PeriodicTAU, min(sizeof(_PeriodicTAU), strlen(PeriodicTAU)));
	strncpy(_ActiveTimer, ActiveTimer, min(sizeof(_ActiveTimer), strlen(ActiveTimer)));	

	// "AT+CPSMS=0,,,"<_PeriodicTAU>","<_ActiveTimer>"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[54])), _PeriodicTAU, _ActiveTimer);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif
	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);	

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("NB-IoT PSM settings:"));
		// Reading PSM parameters
		sendCommand("AT+CPSMS?\r", sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
		USB.println(_buffer, _length);
	#endif
	
	return 0;	
	
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
 * SETUP NB-IOT set PSM (Power Save Mode)
 * AT+CPSMS=<mode> //mode=[0,1]
 * Parameters: mode: 1 - enable or 0 - disabled
 * 			   wait: 1 - wait to enter PSM mode or 0 no wait to enter or not enter in PSM mode
 * Return: 0 if is OK, 1 if error is ocurried
 */
uint8_t WaspBG96::nbiotSetPSM(bool mode, bool wait)
{
	uint8_t answer;
	uint8_t answer2 = 0;
	char command_buffer[20];	
	
	if (wait != 1)
	{
		// "AT+CPSMS=<mode>"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[55])), mode);
		#if DEBUGAT > 0 
			USB.println(command_buffer); 
		#endif

		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	}
	else
	{	
		// "AT+CPSMS=<mode>"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[55])), mode);
		#if DEBUGAT > 0 
			USB.println(command_buffer); 
		#endif
		USB.println(F("Waiting module enter to PSM mode..."));
		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
		#if DEBUG_BG96 > 1		
			USB.println(answer, DEC);
			USB.println(_buffer, _length);
		#endif
		
		//uint8_t counter = 4;
		//answer2 = 0;
		//while ((counter > 0) && (answer2 == 0))
		//{
			//Waiting for module enter in PSM mode.
			answer2 = waitFor("PSM POWER DOWN\r", 40000);
			#if DEBUG_BG96 > 1
				USB.print(F("Answer2: "));
				USB.println(answer2, DEC);			
			//check RRC status.
			// send command
			//answer = sendCommand("AT+QCSCON?\r", sBG96_OK, sBG96_ERROR, 1000);

			#endif	
			//counter--;			
		//}
	}
	
	#if DEBUG_BG96 > 1
		PRINT_BG96(F("NB-IoT PSM mode (0 disabled, 1 enable): "));						
		USB.println(mode, DEC);					
	#endif
	
	if (answer2 == 1)
		{
			memset(_buffer, 0x00 ,sizeof(_buffer));
			strncpy((char*)_buffer, "DONE!", 5);
		}
	
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
 * SETUP NB-IOT get PSM (Power Save Mode) values
 * AT+QPSMS?
 */
uint8_t WaspBG96::nbiotGetPSMValues()
{
	uint8_t answer;
	char command_buffer[20];	

	// "AT+QPSMS?"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[51])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}	
	
	char aux[30];

	// success response format: "\r\n<info>\r\n"
	answer = parseString(aux, sizeof(aux), "\r\n");

	if (answer == 0)
	{
		memset(_buffer, 0x00 ,sizeof(_buffer));
		_length = strlen(aux);
		strncpy((char*)_buffer, aux, strlen(aux));
	}
	

	return 0;
}

/*
 * NB-IOT PSM Wake UP
 * Pulse on PWRKEY pin
 */
uint8_t WaspBG96::nbiotPSMWakeUp()
{
	uint8_t answer;
	uint8_t counter;	
	
	Utils.setMuxSocket1();
	beginUART();
	
	/*
	//Pulse on PWRKEY pin.
	digitalWrite(GPRS_PIN, HIGH); //Pin PWRKEY
	delay(1000);
	digitalWrite(GPRS_PIN, LOW); //Pin PWRKEY
	//delay(1000);
	* */
	
	#if DEBUG_DS2413 > 0
		USB.println(F("IOs en estado alto"));
	  #endif
	  write(0x03);
	  #if DEBUG_DS2413 > 0  
		USB.print(F("IO_A = PWRKEY - Pulso - low"));
	  #endif	  
	  write(0x02);
	  delay(1000);
	  #if DEBUG_DS2413 > 0
		USB.println(F(" - high.")); 
	  #endif
	  write(0x03);

	// Check communication with the module sending a basic AT command
	counter = 15;
	answer = 0;
	while ((counter > 0) && (answer == 0))
	{
		answer = sendCommand("AT\r", sBG96_OK, 1000);
		counter--;
	}

	if (answer == 0)
	{
		return 1;
	}

	return 0;
}

/*
 * NB-IOT Send UDP packet
 * at+q
 */
uint8_t WaspBG96::nbiotSendUDP(char* ipRemote, uint16_t _port, char* UDPData, bool waitForResponse)
{
	uint8_t answer;
	char command_buffer[200];
	uint8_t data_length = 0;
	
	memset(_ipRemote, '\0', sizeof(_ipRemote));
	memset(_UDPData, '\0', sizeof(_UDPData));		

	strncpy(_ipRemote, ipRemote, min(sizeof(_ipRemote), strlen(ipRemote)));	
	strncpy(_UDPData, UDPData, min(sizeof(_UDPData), strlen(UDPData)));
	//memcpy ( &UDPData[strlen(UDPData)], "\r", strlen("\r") );	
	//data_length = strlen(_UDPData);
	
	//Start UDP Service 
	// "AT+QIOPEN=1,2,\"UDP SERVICE\","127.0.0.1",0,3030,0
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[63])));
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
		
		// checking values.
		answer = sendCommand("AT+QISTATE\r", sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);
	#endif
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 2;
	}	
	
	//Send UDP Data to Remote
	// "AT+QISEND=2,%u,\"%s\",%d\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[64])), strlen(UDPData), ipRemote, _port);
	#if DEBUGAT > 0 
		USB.println(command_buffer); 
	#endif	
	
	//test data
	//40020000b66576656e7473ff7b22616363657373546f6b656e223a22645f736b5f4771565555355234346a4d30626d50613467563338547869222c226e616d65223a2274656d7065726174757265222c2264617461223a223235227d
	// send command
	answer = sendCommand(command_buffer, ">", sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// send command
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[66])), _UDPData);
		
	answer = sendCommand(command_buffer, "SEND OK", sBG96_ERROR_CODE, sBG96_ERROR, 5000);	
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 4;
	}
	// waiting a little bit
	delay(1500);
		
	if (waitForResponse == 1)
	{
		//Recive Data from remote	
		answer = waitFor("+QIURC: \"recv\",2", sBG96_ERROR_CODE, sBG96_ERROR, 7000);
		
		if (answer == 1)
		{
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[65])));
			sendCommand(command_buffer, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
		}
		
		#if DEBUG_BG96 == 2
			USB.print(F("Answer value: "));
			USB.println(answer, DEC);
			USB.println(_buffer, _length);	
		#endif
		
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return 5;
		}
	}
	
	// Close UDP socket
	// "AT+QICLOSE=2
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[67])));
	
	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);
	
	if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return 6;
		}	

	return 0;
}

/* This function manages the sleep mode
 * Parameters:	mode: 0 disabled or 1 enabled
 * Return:	0 if 'OK', '1' if error
*/
uint8_t WaspBG96::nbiotSleepMode(uint8_t mode)
{
	uint8_t answer;
	char command_buffer[20];
	
	if (mode == 0)
	{	
		//Starting UART. It's necessary if Waspmote DeepSleep is activated.
		Utils.setMuxSocket1();
		beginUART();
		
		//digitalWrite(XBEE_SLEEP, HIGH); //Pin DTR HIGH. Module wake up. SOCKET0
		//digitalWrite(LED1, HIGH); //Pin DTR HIGH - SOCKET1
		write(0x01);
		
		// Check communication with the module sending a basic AT command
		uint8_t counter = 15;
		answer = 0;
		while ((counter > 0) && (answer == 0))
		{
			answer = sendCommand("AT\r", sBG96_OK, 1000);
			counter--;
		}
		
		if (answer == 0)
		{		
			USB.println(F("Sleep mode active"));
			return 1;
		}
		else
		{
			USB.println(F("Module wake-up!"));
			//return 0;
		}
		
	}
	/* BORRAR
	if (mode == 2)
	{
		Utils.setMuxSocket1();
		beginUART();
		delay(1000);
		
		//digitalWrite(XBEE_SLEEP, HIGH); //Pin DTR HIGH. Module wake up. SOCKET0
		digitalWrite(LED1, HIGH); //Pin DTR HIGH - SOCKET1
		
		// Check communication with the module sending a basic AT command
		uint8_t counter = 15;
		answer = 0;
		while ((counter > 0) && (answer == 0))
		{
			answer = sendCommand("AT\r", sBG96_OK, 1000);
			counter--;
		}
		
		if (answer == 0)
		{		
			USB.println(F("Sleep mode active"));
			return 1;
		}
		else
		{
			USB.println(F("Module wake-up!"));
			//return 0;
		}
		
	}
	* */

	// "AT+CSCLK=<mode>\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[68])), mode);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	
	//digitalWrite(XBEE_SLEEP, LOW); //Pin DTR LOW. Module can enter into sleep mode. SOCKET0
	//digitalWrite(LED1, LOW); //Pin DTR LOW - SOCKET1
	write(0x03);
	
	if (mode == 1)
	{
		// Check communication with the module sending a basic AT command
		uint8_t counter = 15;
		answer = 1;
		while ((counter > 0) && (answer == 1))
		{
			answer = sendCommand("AT\r", sBG96_OK, 500);
			delay(1000);
			counter--;
		}
		
		if (answer == 0)
		{		
			USB.println(F("Sleep mode activated"));
			return 0;
		}
		else
		{
			return 2;
		}
	}
	return 0;
}

/*
 * SETUP NB-IOT setting parameters eDRX
 * * Parameters: n: 0 to disable and 1 to enable.
 * 				 ActType: Time value in binary format
 * 			   	 eDRX_value: Time value in binary format
 * Return: 0 if is OK and 1 if error has ocurried
 * 
 */
uint8_t WaspBG96::settingeIDRX(uint8_t n, uint8_t ActType, char* _eIDRX_value)
{
	uint8_t answer;
	char command_buffer[40];
	
	if ( n == 0){
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[30])));
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	}
	else
	{
		// "AT+CEDRXS=%u,%u,%s\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[69])), n, ActType, _eIDRX_value);
		#if DEBUG_BG96 > 0 
			USB.println(command_buffer); 
		#endif
		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);	

		#if DEBUG_BG96 > 1
			PRINT_BG96(F("NB-IoT eDRX settings:"));
			// Reading PSM parameters
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[71])));
			sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
			USB.println(_buffer, _length);
		#endif
	}
	
	
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
 * 		method: selected HTTP method:	WaspBG96::HTTP_GET
 * 										WaspBG96::HTTP_POST * 										
 *		url: host name or IP address of the server
 *		port: server port
 *		resource: parameter indicating the HTTP resource, object of the	request
 * Return:	'0' if OK
 * 			'x' if error. See http()
 */
uint8_t WaspBG96::http(uint8_t method,
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
 * 		method: selected HTTP method:	WaspBG96::HTTP_GET
 * 										WaspBG96::HTTP_POST * 										
 *		url: host name or IP address of the server
 *		port: server port
 *		resource: parameter indicating the HTTP resource, object of the	request
 * Return:	'0' if OK
 * 			'x' if error. See http()
 */
uint8_t WaspBG96::https(uint8_t method,
						char* url,
						uint16_t port,
						char* resource)
{
	return https(method,
				url,
				port,
				resource,
				NULL);
}


/* Function: 	This function performs a HTTP request
 * Parameters:
 * 		method: selected HTTP method:	WaspBG96::HTTP_GET
 * 										WaspBG96::HTTP_POST 
 * 										WaspBG96::HTTP_POST_FRAME
 *		url: host name or IP address of the server
 *		port: server port
 *		resource: parameter indicating the HTTP resource, object of the	request
 *		data: data to send in HTTP method
 *
 * Return:	10 if OK
 * 			11 if error setting context id
 * 			12 if error sending url
 * 			13 if error sending POST 
 * 			14 if wrong method has been selected * 
 *			20 if OK
 * 			21 if timeout waiting HTTP GET response
 * 			22 if timeout waiting HTTP POST response
 * 			23 if error waiting response
 * 			24 if error reading the response
 * 			25,26 if error reading the response
 * 			27 error waiting response function
 */
uint8_t WaspBG96::http(uint8_t method,
						char* url,
						uint16_t port,
						char* resource,
						char* data)
{
	uint8_t answer;
	int16_t http_data;

	// 2. Configure parameters	and send the request
	answer = httpRequest(method, url, port, resource, data);
	if (answer != 0)
	{
		USB.println(answer, DEC);
		return answer+10;	// 10 to 19 error codes
	}

	// 3. Wait for the response	
	answer = httpWaitResponse(method, BG96_HTTP_TIMEOUT);
	if (answer != 0)
	{
		return answer+20;	// 20 to 29 error codes
	}

	return 0;
}

/* Function: 	This function performs a HTTP request
 * Parameters:
 * 		method: selected HTTP method:	WaspBG96::HTTP_GET
 * 										WaspBG96::HTTP_HEAD
 * 										WaspBG96::HTTP_DELETE
 * 										WaspBG96::HTTP_POST
 * 										WaspBG96::HTTP_PUT
 * 										WaspBG96::HTTP_POST_FRAME
 *		url: host name or IP address of the server
 *		port: server port
 *		resource: parameter indicating the HTTP resource, object of the	request
 *		data: data to send in HTTP method
 *
 * Return:	0 if OK
 * 			1 SSL context error
 * 			2 SSL version error
 * 			3 SSL ciphersuite error
 * 			4 SSL seclevel error
 * 			6 SSL cacert error
 * 			10 if OK
 * 			11 if error setting context id
 * 			12 if error sending url
 * 			13 if error sending POST 
 * 			14 if wrong method has been selected * 
 *			20 if OK
 * 			21 if timeout waiting HTTP GET response
 * 			22 if timeout waiting HTTP POST response
 * 			23 if error waiting response
 * 			24 if error reading the response
 * 			25, 26 if error reading the response
 * 			27 error waiting response function

 */
uint8_t WaspBG96::https(uint8_t method,
						char* url,
						uint16_t port,
						char* resource,
						char* data)
{
	uint8_t answer;
	int16_t http_data;
	char command_buffer[200];
	
	//// 1. Data connection must be activated.
	
	//// 2. Setting SSL configuration
	// "AT+QHTTPCFG=\"sslctxid\",1\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_HTTP[13])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 1;
	}
	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[0])), 1, 1);

	// send command
	// "AT+QSSLCFG=\"sslversion\",%u,%u\r"
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 2;
	}
	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[1])), 1, "0X0005");
	
	// send command
	// "AT+QSSLCFG=\"ciphersuite\",%u,%s\r"
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 3;
	}
	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[2])), 1, 1);
	
	// send command
	// "AT+QSSLCFG=\"seclevel\",%u,%u\r"
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 4;
	}
	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[3])), 1, "ca.pem");
	
	// send command
	// "AT+QSSLCFG=\"cacert\",%u,\"%s\"\r"
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 5;
	}

	// 2. Configure parameters	and send the request
	answer = httpRequest(method, url, port, resource, data);
	if (answer != 0)
	{
		USB.println(answer, DEC);
		return answer+10;	// 16 to 19 error codes
	}

	// 3. Wait for the response	
	answer = httpWaitResponse(method, BG96_HTTP_TIMEOUT);
	if (answer != 0)
	{
		return answer+20;	// 20 to 27 error codes
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
 * Return:	10 if OK
 * 			11 if error setting context id
 * 			12 if error sending url
 * 			13 if error sending POST 
 * 			14 if wrong method has been selected * 
 *			20 if OK
 * 			21 if timeout waiting HTTP GET response
 * 			22 if timeout waiting HTTP POST response
 * 			23 if error waiting response
 * 			24 if error reading the response
 * 			25,26 if error reading the response
 * 			27 error waiting response function
 */
uint8_t WaspBG96::sendFrameToMeshlium(char* url,
									uint16_t port,
									uint8_t* data,
									uint16_t length)
{
	uint8_t answer;
	int16_t http_data;
	
	// 2. Configure parameters	and send the request
	answer = httpRequest(WaspBG96::HTTP_POST_FRAME, url, port, NULL, data, length);
	if (answer != 0)
	{
		return answer+10;	// 16 to 19 error codes
	}

	// 3. Wait for the response
	answer = httpWaitResponse(WaspBG96::HTTP_POST_FRAME, BG96_HTTP_TIMEOUT);
	if (answer != 0)
	{
		return answer+20;	// 20 to 27 error codes
	}

	return 0;
}

/* Function: 	This function configures and open a socket
 * Parameters:	socketId: number of the socket Id
 * 				protocol: TCP or UDP
 * 				remote_IP: address of the remote host (IPv6 allowed)
 * 				remote_port: remote host port to contact
 * Return:		0 if OK; 'x' if error (see below)
 */
uint8_t WaspBG96::openSocketClient(uint8_t socketId,
								char* protocol,
								char* remote_IP,
								uint16_t remote_port)
{
	return openSocketClient(socketId,
							protocol,
							remote_IP,
							remote_port,
							0);
}

/* Function: 	This function configures and opens a socket
 * Parameters:	socketId: number of the socket Id
 * 				protocol: TCP or UDP
 * 				remote_IP: address of the remote host (IPv6 allowed)
 * 				remote_port: remote host port to contact
 * 				local_port: UDP connections local port
 * Return:		0 if OK; 'x' if error (see below)
 */
uint8_t WaspBG96::openSocketClient(uint8_t socketId,
								char* protocol,
								char* remote_IP,
								uint16_t remote_port,
								uint16_t local_port)
{
	char* pointer;
	uint8_t error;
	uint8_t answer;
	char command_buffer[100];
	
	//// 1. Data connection must be activated.
	
	//// 2. Check socket status		
	answer = getSocketStatus(socketId);
	if (answer == 0)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		if (answer == 1)
		{
			PRINT_BG96(F("Error opening socket - Socket is already opened\n"));
		}

		return 23;
	}
	
	//// 3. Socket Configuration Extended
	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Configuring connection\n"));
	#endif


	// "AT+QIOPEN=1,<connectID>,\"<service_type>\",\"<IP_address/domain_name>\",<remote_port>,<local_port>,0\r"
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[0])),
				socketId,
				protocol,
				remote_IP,
				remote_port,
				local_port);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 23;
	}
	
	//Waitting for command response.
	answer = waitFor("+QIOPEN: ", (15000));
		if (answer == 0)
		{
			return 11;
		}		
	
	// 2. Read the whole response: "+QHTTPGET: <http_status_code>,<content_type>,<data_size>\r
	answer = waitFor("\r", 5000);
	if (answer == 0)
	{
		return 2;
	}
	
	// find first value skipping delimiters	
	#if DEBUG_BG96 > 0
		USB.println(_buffer, DEC);
	#endif
	pointer = strtok((char*)_buffer, ",");
	
	// iterate through response
	for (int i = 0; i < 2; i++)
	{
		if (pointer == NULL)
		{
			#if DEBUG_BG96 > 0
				PRINT_BG96(F("Error: null pointer2\n"));
				USB.println(pointer);
			#endif
			return 1;
		}
		#if DEBUG_BG96 > 0
			USB.println(pointer);
		#endif
		
		if (i == 1)
		{
			_socketerror = atoi(pointer);
			if (_socketerror != 0){
				return _socketerror;
			} 
		}
		pointer = strtok (NULL, " ,\r\n");
	}
	
	answer = getSocketStatus(socketId);
	// check answer
	if (answer != 0)
	{
		// if state is closed then break
			if (socketStatus[socketId].state == 4)
			{
				PRINT_BG96(F("Socket is closed\n"));
			}
	}

}


/* Function: 	This function configures and opens a socket SSL
 * Parameters:
 * 		socketId: Secure Socket Identifier (must be 1 because until now SSL block manage only 1 socket)
 * 		remote_IP: address of the remote host 
 * 		remote_port: remote host port to contact
 * Return:
 * 		0 if OK
 * 		1 SSL version error
 * 		2 ciphersuite error
 * 		3 seclevel error
 * 		4 cacert error
 * 		5 SSL socket status error
 * 		6 open SSL socket error
 * 		7 open SSL socket error 2
 * 		8 open SSL socket error 3
 * 		99 null pinter
 */
uint8_t WaspBG96::openSocketSSL(uint8_t socketId,
								char* remote_IP,
								uint16_t remote_port)
{
	char* pointer;
	uint8_t error;
	uint8_t answer;
	char command_buffer[100];
	char answer_buffer[50];
	
	//// 1. Data connection must be activated.
	
	//// 2. Setting SSL configuration
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[0])), 1, 1);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 1;
	}
	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[1])), 1, "0X0005");
	
	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 2;
	}
	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[2])), 1, 1);
	
	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 3;
	}
	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[3])), 1, "ca.pem");
	
	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 4;
	}
	
	
	answer = getSocketStatusSSL(socketId);
	if (answer == 0)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		if (answer == 1)
		{
			PRINT_BG96(F("Error opening socket - Socket is already opened\n"));
		}

		return 5;
	}
	
	//// 3. Socket Configuration Extended
	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Configuring connection\n"));
	#endif
	

	// AT+QSSLOPEN=<pdpctxID>,<sslctxID>,<clientID>,<serveraddr>,<server_port>[,<access_mode>]
	memset(command_buffer, '\0', sizeof(command_buffer));
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[4])), 1, 1, socketId, remote_IP, remote_port);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	
	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();

			#if DEBUG_BG96 > 0
				printErrorCode();
			#endif
		}
		else if ( answer == 4 )
		{
			getTCPErrorCode();
		}

		return 6;
	}
	
	sprintf_P(answer_buffer, (char*)pgm_read_word(&(table_SSL[11])));
	//Waitting for command response.
	answer = waitFor(answer_buffer, (15000));
		if (answer == 0)
		{
			return 7;
		}		
	
	// 2. Read the whole response: +QSSLOPEN: <clientID>,<err>\r
	answer = waitFor("\r", 5000);
	if (answer == 0)
	{
		return 8;
	}
	
	// find first value skipping delimiters	
	#if DEBUG_BG96 > 0
		USB.println(_buffer, DEC);
	#endif
	pointer = strtok((char*)_buffer, ",");
	
	// iterate through response
	for (int i = 0; i < 2; i++)
	{
		if (pointer == NULL)
		{
			#if DEBUG_BG96 > 0
				PRINT_BG96(F("Error: null pointer2\n"));
				USB.println(pointer);
			#endif
			return 99;
		}
		#if DEBUG_BG96 > 0
			USB.println(pointer);
		#endif
		
		if (i == 1)
		{
			_socketerror = atoi(pointer);
			if (_socketerror != 0){
				USB.print(F("Error socket: "));
				USB.println(_socketerror);
			} 
		}
		pointer = strtok (NULL, " ,\r\n");
	}
	
	
	answer = getSocketStatusSSL(socketId);
	// check answer
	if (answer != 0)
	{
		// if state is closed then break
			if (socketStatus[socketId].state == 4)
			{
				PRINT_BG96(F("Socket is closed\n"));
			}
	}
	
	return 0;
}


/* Function: 	This function closes a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * Return:	0 Socket Closed
 * 			1 if error sending the command
 * 			2 if timeout shutting down the socket
 */
uint8_t WaspBG96::closeSocketClient(uint8_t socketId)
{
	uint8_t answer;
	char command_buffer[20];

	//// 1. Check socket status
	answer = getSocketStatus(socketId);

	if ((answer == 1) || (socketStatus[socketId].state == 4))
	{
		#if DEBUG_BG96 > 1
			PRINT_BG96(F("Socket status: closed\n"));
		#endif
		return 0;
	}

	//// 2. Close connection
	// AT+QICLOSE=<socketId>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[4])), socketId);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 12000);

	// check answer
	if(answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}

		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Error closing connection\n"));
		#endif
		return 1;
	}

	//// 3. Wait the shutdown of the socket
	uint32_t previous = millis();

	do
	{
		// get socket status
		answer = getSocketStatus(socketId);
		if (answer != 1)
		{
			#if DEBUG_BG96 > 0
				PRINT_BG96(F("Error getting socket status\n"));
			#endif
			return 2;
		}

		if ((answer == 1) || (socketStatus[socketId].state == 4))
		{
			#if DEBUG_BG96 > 1
				PRINT_BG96(F("Socket closed\n"));
			#endif
			return 0;
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();

		delay(1000);

	} while ((millis() - previous) < BG96_IP_TIMEOUT);


	return 3;
}

/* Function: 	This function closes a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * Return:	0 Socket Closed
 * 			1 if error sending the command
 * 			2 if timeout shutting down the socket
 */
uint8_t WaspBG96::closeSocketSSL(uint8_t socketId)
{
	uint8_t answer;
	char command_buffer[20];

	//// 1. Check socket status
	answer = getSocketStatusSSL(socketId);

	if ((answer == 1) || (socketStatusSSL[socketId].state == 4))
	{
		#if DEBUG_BG96 > 1
			PRINT_BG96(F("Socket status: closed\n"));
		#endif
		return 0;
	}

	//// 2. Close connection
	// AT+QICLOSE=<socketId>\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[10])), socketId);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 12000);

	// check answer
	if(answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}

		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Error closing SSL connection\n"));
		#endif
		return 1;
	}

	//// 3. Wait the shutdown of the socket
	uint32_t previous = millis();

	do
	{
		// get socket status
		answer = getSocketStatusSSL(socketId);
		if (answer != 1)
		{
			#if DEBUG_BG96 > 0
				PRINT_BG96(F("Error getting SSL socket status\n"));
			#endif
			return 2;
		}

		if ((answer == 1) || (socketStatusSSL[socketId].state == 4))
		{
			#if DEBUG_BG96 > 1
				PRINT_BG96(F("Socket SSL closed\n"));
			#endif
			return 0;
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();

		delay(1000);

	} while ((millis() - previous) < BG96_IP_TIMEOUT);


	return 3;
}



/* Function: 	This function sends data through a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * 				data: string with the data
 * Return:		'0' if OK; 'x' if error
 */
uint8_t WaspBG96::send(uint8_t socketId, char* data)
{
	return send(socketId, (uint8_t*)data, strlen(data));
}


/* Function: 	This function sends data through a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * 				data: buffer with the data
 * 				data_length: length of the data buffer
 * Return:		0 if OK, 'x' error
 */
uint8_t WaspBG96::send(uint8_t socketId,
					uint8_t* data,
					uint16_t data_length)
{
	uint8_t answer;
	char command_buffer[500];

	//// 1. Check socket status
	answer = getSocketStatus(socketId);

	// check answer error
	if (answer != 0)
	{
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Error checking socket status\n"));
		#endif
		return 1;
	}

	// check correct socket status
	if ((socketStatus[socketId].state == 1) ||
		(socketStatus[socketId].state == 3) ||
		(socketStatus[socketId].state == 4))
	{
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Incorrect socket status\n"));
		#endif
		return 2;
	}
	
	// get if it is TCP or UDP
	if (strcmp(socketStatus[socketId].service_type, "TCP") == 0)
	{
		//// 2. Send data
		// AT+QISEND=<socketId>,<data_length>\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[2])), socketId, data_length);
	
	}
	
	else if (strcmp(socketStatus[socketId].service_type, "UDP") == 0)
	{
		//// 2. Send data
		// AT+QISEND=<socketId>,<data_length>\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[2])), socketId, data_length);
	}
	
	answer = sendCommand(command_buffer, ">", sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	 if ( answer == 3 )
		{
			getTCPErrorCode();
		}
	
	snprintf(command_buffer, 500, "%s", data);
	
	// send command		
	answer = sendCommand(command_buffer, "SEND OK", sBG96_ERROR_CODE, sBG96_ERROR, 5000);	
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
	#endif
	if ( answer == 3 )
		{
			getTCPErrorCode();
		}
		
	
	//Recive Data from remote	
	waitFor("+QIURC: \"recv\"", sBG96_ERROR_CODE, sBG96_ERROR, 10000);
	
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[2])), socketId, 0);
		
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);	
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	if ( answer == 3 )
		{
			getTCPErrorCode();
		}

	char *pointer;
	pointer = strstr((char*)_buffer, "+QISEND:");
	
	// find first value skipping delimiters
	pointer = strtok(pointer, "+QISEND: ,\r\n");
	
	for (int i = 0; i<3; i++)
	{
		if (i == 0){
			socketInfo[socketId].id = (uint8_t) strtoul( (char *)socketId, NULL, 10);
			socketInfo[socketId].sent = (uint16_t) strtoul( pointer, NULL, 10);
			#if DEBUG_BG96 > 1
				USB.print(F("Total length of sent data: "));
				USB.println(pointer);
			#endif
		}
		else if ( i == 1)
		{
			socketInfo[socketId].ack = (uint16_t) strtoul( pointer, NULL, 10);
			#if DEBUG_BG96 > 1
				USB.print(F("Total length of acknowledged data: "));
				USB.println(pointer);
			#endif
		}
		else if ( i == 2)
		{
			socketInfo[socketId].notack = (uint16_t) strtoul( pointer, NULL, 10);
			#if DEBUG_BG96 > 1
				USB.print(F("Total length of unacknowledged data: "));
				USB.println(pointer);
			#endif
		}
				
		pointer = strtok (NULL, ",\r\n");		
	}
	
	delay(1000);
	return 0;
	
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
uint8_t WaspBG96::sendSSL(uint8_t socketId, char* data)
{
	return sendSSL(socketId, (uint8_t*)data, strlen(data));
}

/* Function: 	This function sends data through a socket previously opened
 * Parameters:	socketId: number of the socket Id
 * 				data: buffer with the data
 * 				data_length: length of the data buffer
 * Return:		0 if OK, 'x' error
 */
uint8_t WaspBG96::sendSSL(uint8_t socketId,
						uint8_t* data,
						uint16_t data_length)
{
	uint8_t answer;
	char command_buffer[500];
	char answer_buffer[20];

	//// 1. Check socket status
	answer = getSocketStatusSSL(socketId);

	// check answer error
	if (answer != 0)
	{
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Error checking SSL socket status\n"));
		#endif
		return 1;
	}

	// check correct socket status
	if ((socketStatus[socketId].state == 1) ||
		(socketStatus[socketId].state == 3) ||
		(socketStatus[socketId].state == 4))
	{
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Incorrect SSL socket status\n"));
		#endif
		return 2;
	}
	
	// get if it is TCP or UDP
	
		//// 2. Send data
		// AT+QSSLSEND=<socketId>,<data_length>\r
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[13])), socketId, data_length);
	
	
	answer = sendCommand(command_buffer, ">", sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);
		USB.println(_buffer, _length);	
	#endif
	 if ( answer == 3 )
		{
			getTCPErrorCode();
		}
	
	snprintf(command_buffer, sizeof(command_buffer), "%s", data);
	// send command		
	answer = sendCommand(command_buffer, "SEND OK", sBG96_ERROR_CODE, sBG96_ERROR, 5000);	

	#if DEBUG_BG96 == 2
		USB.print(F("Answer value: "));
		USB.println(answer, DEC);	
	#endif
	if ( answer == 3 )
		{
			getTCPErrorCode();
		}
		
	sprintf_P(answer_buffer, (char*)pgm_read_word(&(table_SSL[14])));
	//Recive Data from remote	
	waitFor(answer_buffer, sBG96_ERROR_CODE, sBG96_ERROR, 10000);	
	
	delay(1000);
	return 0;
}


/* Function: 	This function read data received in the module
 * Parameters:	socketId: number of the socket Id
 * Return: 		'0' if OK; 'x' if error
 *
 */
uint8_t WaspBG96::receive(uint8_t socketId)
{
	return receive(socketId, 0);
}

/* Function: 	This function read data received in the module
 * Parameters:	socketId: number of the socket Id
 * 				timeout: number of ms to wait for incoming bytes
 * Return: 		'0' if OK; 'x' if error
 */
uint8_t WaspBG96::receive(uint8_t socketId, uint32_t timeout)
{
	uint8_t answer;
	int incoming_bytes;
	char command_buffer[25];
	char command_answer[25];
	uint32_t nBytes = 0;
	uint32_t readBufferBytes = 0;
	uint32_t previous;
	uint16_t _unreaddata;

	previous = millis();

	
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[3])), socketId, 0);
		
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);	
		#if DEBUG_BG96 == 2
			USB.print(F("Answer value: "));
			USB.println(answer, DEC);
			USB.println(_buffer, _length);	
		#endif
		if ( answer != 1 )
		{
			getTCPErrorCode();
		}

		char *pointer;
		pointer = strstr((char*)_buffer, "+QIRD:");
		
		// find first value skipping delimiters
		pointer = strtok(pointer, "+QIRD: ,\r\n");
		
		for (int i = 0; i<3; i++)
		{
			if (i == 0){
				socketInfo[socketId].received = (uint16_t) strtoul( pointer, NULL, 10);
				
				#if DEBUG_BG96 > 0
					USB.print(F("Total length of received data: "));
					USB.println(pointer);
				#endif
			}
			else if ( i == 1)
			{
				socketInfo[socketId].readed = (uint16_t) strtoul( pointer, NULL, 10);
				
				#if DEBUG_BG96 > 0
					USB.print(F("Length of read data: "));
					USB.println(pointer);
				#endif
			}
			else if ( i == 2)
			{
				socketInfo[socketId].notreaded = (uint16_t) strtoul( pointer, NULL, 10);
				
				#if DEBUG_BG96 > 0
					USB.print(F("Length of unread data: "));
					USB.println(pointer);
				#endif
				_unreaddata = atoi(pointer);
			}
				
			pointer = strtok (NULL, ",\r\n");		
		}
		
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_IP[3])), socketId, _unreaddata);
		
		answer = sendCommand(command_buffer, "\r\nOK", sBG96_ERROR_CODE, sBG96_ERROR, 5000);	
		#if DEBUG_BG96 == 2
			USB.print(F("Answer value: "));
			USB.println(answer, DEC);
			USB.println(_buffer, _length);	
		#endif
		if ( answer != 1 )
		{
			getTCPErrorCode();
		}
	
	return 0;
}




/* Function: 	This function read data received in the module
 * Parameters:	socketId: number of the socket Id
 * Return:		'0' if ok; 'x' if error
 */
uint8_t WaspBG96::receiveSSL(uint8_t socketId)
{
	return receiveSSL(socketId, 0);
}

/* Function: 	This function read data received in the module
 * Parameters:	socketId: number of the socket Id
 * 				timeout: number of ms to wait for incoming bytes
 * Return:		'0' if ok; 'x' if error
 */
uint8_t WaspBG96::receiveSSL(uint8_t socketId, uint32_t timeout)
{
	uint8_t answer;
	int incoming_bytes;
	char command_buffer[25];
	char command_answer[25];
	//uint32_t nBytes = 0;
	//uint32_t readBufferBytes = 0;
	uint32_t previous;
	uint16_t _unreaddata;
	char delimiters[20];

	previous = millis();
		
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_SSL[15])), socketId);
		
		answer = sendCommand(command_buffer, "\r\nOK", sBG96_ERROR_CODE, sBG96_ERROR, 5000);	
		#if DEBUG_BG96 == 2
			USB.print(F("Answer value: "));
			USB.println(answer, DEC);
			USB.println(_buffer, _length);	
		#endif
		if ( answer != 1 )
		{
			getTCPErrorCode();
		}
		
		char *pointer;
		sprintf_P(delimiters, (char*)pgm_read_word(&(table_SSL[9])));
		pointer = strstr((char*)_buffer, delimiters);
		
		// find first value skipping delimiters
		sprintf_P(delimiters, (char*)pgm_read_word(&(table_SSL[16])));
		pointer = strtok(pointer, delimiters);		
		
		//save the size of data received
		socketStatusSSL[socketId].received = (uint16_t) strtoul( pointer, NULL, 10);
				
		#if DEBUG_BG96 > 0
			USB.print(F("Total length of received data: "));
			USB.println(pointer);
		#endif
		
		pointer = strtok (NULL, "\r\n");
	
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
uint8_t WaspBG96::manageSSL(	uint8_t socketId,
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
 * 				1 if error ocurried creating file.
 * 
 */
uint8_t WaspBG96::manageSSL(	uint8_t socketId,
							uint8_t action,
							uint8_t dataType,
							char *data)
{
	uint8_t answer;
	char command_buffer[50];
	char command_answer[50];
	char filename[15];

	// clear buffers
	memset(command_buffer,0x00,sizeof(command_buffer));
	memset(command_answer,0x00,sizeof(command_answer));
	memset(filename,0x00,sizeof(filename));
	
	// Set filename of certificate.
	if (dataType == WaspBG96::SSL_TYPE_CA_CERT)
	{
		//filename = "ca";
		//strncpy(filedata, data, sizeof(filedata));
		snprintf(filename, sizeof(filename), "%s.pem", "ca");
	}
	
	//Steps to save the certificate
	if (action == WaspBG96::SSL_ACTION_STORE)
	{
		//// 1. Save certificate
		//// create the certificate file
		// "AT+QFUPL=<filename>,<file_size>\r"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FILE[0])), filename, strlen(data), 5);

		// send command
		answer = sendCommand(command_buffer, "CONNECT", sBG96_ERROR_CODE, sBG96_ERROR);

		// check response
		// If the file has already been created,
		// the module returns error, so we continue if error
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
				// If file exist, delete and create again.
				if (_errorCode == 407)
				{
					// delete certificate file.
					sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FILE[7])), filename);

					// send command
					answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);
					
					if (answer == 1)
					{	
						//create the file
						sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FILE[0])), filename, strlen(data), 5);

						// send command
						answer = sendCommand(command_buffer, "CONNECT", sBG96_ERROR_CODE, sBG96_ERROR);
					}
				}
			}
		}
		
		//// Verify the file
		// "+QFUPL: %d"
		sprintf_P(command_answer, (char*)pgm_read_word(&(table_FILE[8])), strlen(data));

		// send data file and verify if the file is created ok
		answer = sendCommand(data, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);

		// check response
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return 2;
		}
		
		if (find(_buffer, _length, command_answer) == true)
		{
			#if DEBUG_BG96 > 0
				PRINT_BG96(F("File created ok!\n"));
			#endif
			//return 2;
		}
		
		/*
		// delete certificate file.
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FILE[7])), "*");

		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);

		// check response
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return -2;
		}
		* */
		return 0;
	}
	
	// Read a file
	if (action == WaspBG96::SSL_ACTION_READ)
	{
		char *pointer;
		char delimiters[10];
		uint8_t filehandle;
		uint16_t filesize;
		
		//Known the file size to be readed
		// "+QFUPL: %d"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FILE[6])), filename);

		// send data file and verify if the file is created ok
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);

		// check response
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return 10;
		}
		
		strcpy_P(delimiters, (char*)pgm_read_word(&(table_FILE[12])));
		pointer = strstr((char*)_buffer, delimiters);
	
		// find first value skipping delimiters
		pointer = strtok(pointer, delimiters);
		// Skip file name parameter
		pointer = strtok (NULL, " ,\r\n");		
		//Getting file size
		#if DEBUG_BG96 > 0
			USB.println(pointer);
		#endif
		filesize = atoi(pointer);
		
		
		//Open the file to be readed
		//"AT+QFOPEN=\"%s\"\r"
		// "+QFUPL: %d"
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FILE[3])), filename);

		// send data file and verify if the file is created ok
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);

		// check response
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return 11;
		}
		
		#if DEBUG_BG96 > 0
			USB.println(_buffer, _length);
		#endif
		
		strcpy_P(delimiters, (char*)pgm_read_word(&(table_FILE[9])));
		pointer = strstr((char*)_buffer, delimiters);
	
		// find first value skipping delimiters
		pointer = strtok(pointer, "+QFOPEN: \r\n");
		filehandle = atoi(pointer);
		#if DEBUG_BG96 > 0
			USB.println(pointer);
		#endif
		
		
		//Read the file
		uint16_t readed = 0;
		while ( readed <= filesize)
		{
			// "AT+QFSEEK=%u,%d,%u\r"			
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FILE[11])), filehandle, readed, 0);

			// send data file and verify if the file is created ok
			answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);
			// check response
			if (answer != 1)
			{
				if (answer == 2)
				{
					getErrorCode();
				}
				return 12;
			}
			
			// "AT+QFREAD=%u,%d\r"
			// Initial response: "+QFUPL: %d"
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FILE[4])), filehandle, 500);

			// send data file and verify if the file is created ok
			answer = sendCommand(command_buffer, "\r\nOK", sBG96_ERROR_CODE, sBG96_ERROR, 5000);
			
			/*
			// check response
			if (answer != 1)
			{
				if (answer == 2)
				{
					getErrorCode();
				}
				return 12;
			}
			* */
			if (readed == 0)
			{
				PRINT_BG96(F("File content: \n"));
			}
			readed = readed+500;	
			#if DEBUG_BG96 > 0	
				USB.println(_buffer, _length);
			#endif
			return 0;
		}
	}
	
	//Steps to delete the certificate
	if (action == WaspBG96::SSL_ACTION_DELETE)
	{
		// delete certificate file.
		sprintf_P(command_buffer, (char*)pgm_read_word(&(table_FILE[7])), filename);

		// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR);

		// check response
		if (answer != 1)
		{
			if (answer == 2)
			{
				getErrorCode();
			}
			return 20;
		}
	}
	
	return 5;
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
uint8_t WaspBG96::gpsStart()
{
	uint8_t answer;
	char command_buffer[50];
	//char command_answer[10];

	//// 1. Set reset mode
	// AT+QGPS=1\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[2])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);

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

uint8_t WaspBG96::gpsNmeatype(uint8_t nmeatype, uint8_t nmeatype_value)
{
	uint8_t answer;
	char command_buffer[50];
	char command_answer[10];
	
	//// 1. Enable NMEA type
	// AT+QGPSCFG=\"nmeasrc\",%u\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[3])), 1);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);

		// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	
	///// 1. Set nmea type
	switch(nmeatype)
	{
		case WaspBG96::gpsnmeatype:			
			// "AT+QGPSCFG=\"gpsnmeatype\",%u\r"
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[4])), nmeatype_value);
			
			break;		
			
		case WaspBG96::glonassnmeatype:
			// "AT+QGPSCFG=\"glonassnmeatype\",%u\r"
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[5])), nmeatype_value);
			
			break;		
			
		case WaspBG96::galileonmeatype:
			// "AT+QGPSCFG=\"galileonmeatype\",%u\r"
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[6])), nmeatype_value);
			
			break;
		
		case WaspBG96::beidounmeatype:
			// "AT+QGPSCFG=\"beidounmeatype\",%u\r"
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[7])), nmeatype_value);
			
			break;
		
		case WaspBG96::gsvextnmeatype:
			// "AT+QGPSCFG=\"gsvextnmeatype\",%u\r"
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[8])), nmeatype_value);
			
			break;
	}
		
	// send command
		answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);

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
 * Function: It gets the NMEA string
 *
 */
uint8_t WaspBG96::getNMEA(uint8_t nmea)
{	
	uint8_t answer;
	char command_buffer[50];
	char nmea_type[7];
	memset( nmea_type, 0x00, sizeof(nmea_type) );
	
	switch(nmea)
	{
		case BG96_GGA:
			// "AT+QGPSGNMEA=\"%s\"\r"
			strcpy_P(nmea_type, (char*)pgm_read_word(&(table_GPS[18])));
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), nmea_type);
			
			break;
		case BG96_GSA:
			// "AT+QGPSGNMEA=\"%s\"\r"
			strcpy_P(nmea_type, (char*)pgm_read_word(&(table_GPS[21])));
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), nmea_type);
			
			break;
		case BG96_GNS:
			// "AT+QGPSGNMEA=\"%s\"\r"
			strcpy_P(nmea_type, (char*)pgm_read_word(&(table_GPS[23]))); 
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), nmea_type);
			
			break;
		case BG96_VTG:
			// "AT+QGPSGNMEA=\"%s\"\r"
			strcpy_P(nmea_type, (char*)pgm_read_word(&(table_GPS[22])));
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), nmea_type);
			
			break;
		case BG96_RMC:
			// "AT+QGPSGNMEA=\"%s\"\r"
			strcpy_P(nmea_type, (char*)pgm_read_word(&(table_GPS[19])));
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), nmea_type);
			
			break;
		case BG96_GSV:
			// "AT+QGPSGNMEA=\"%s\"\r"
			strcpy_P(nmea_type, (char*)pgm_read_word(&(table_GPS[20])));
			sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[17])), nmea_type);
			
			break;
	}
	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);

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


/* Function: Stops the GPS engine
 * Return:	'0' if OK; '1' error
 */
uint8_t WaspBG96::gpsStop()
{
	uint8_t answer;
	char command_buffer[20];

	// AT+QGPSEND\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_GPS[0])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 1000);

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
int8_t WaspBG96::checkGPS()
{
	char *pointer;
	uint8_t answer;
	char command_buffer[20];
	char command_pattern[20];

	//// 1. Check if the GPS position is fixed
	// AT+QGPSLOC=?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_GPS[15])));

	// pattern <--- "+QGPSLOC: ,"
	strcpy_P(command_pattern, (char*)pgm_read_word(&(table_GPS[24])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);

	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			uint8_t status;
			char format[20];

			// wait for " <err>\r\n"
			status = waitFor((char*)"\r\n", 3000);

			if (status == 0)
			{
				#if DEBUG_BG96 > 0
					PRINT_BG96(F("no response\n"));
				#endif
				_fixMode = 0;
				return -1;
			}
			else
			{
				parseUint32((uint32_t*)&_errorCode, " \r\n");
				
				if (_errorCode == 516)
				{
					#if DEBUG_BG96 > 0
						USB.println( _errorCode );
					#endif
					_fixMode = 0;
					return 0;
				}
				else
				{
					USB.println( _errorCode );
				}
			}
		}
		return 1;
	}

	// check if there is not any available data in _buffer
	// If so, _buffer has the following string within it:
	// "$GPSACP: ,,,...."
	if (find(_buffer, _length, command_pattern) == true)
	{
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("pattern not found\n"));
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

	// pattern <--- "\r\n+QGPSLOC: .,"
	strcpy_P(command_pattern, (char*)pgm_read_word(&(table_GPS[24])));

	// skip first characters
	pointer = strtok((char*)_buffer, command_pattern);
	if (pointer == NULL)
	{
		return 3;
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("UTC:"));
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

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Latitude:"));
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

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Longitude:"));
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

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("HDOP:"));
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

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Altitude:"));
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

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Fix mode:"));
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

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Course over ground:"));
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

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Speed over ground (kmh):"));
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

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Speed over ground (knots):"));
		USB.println(pointer);
	#endif

	// skip ','
	pointer = strtok(NULL, ",");
	if (pointer == NULL)
	{
		return 13;
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Get date:"));
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

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Num Satellites:"));
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
float WaspBG96::convert2Degrees(char* input, char indicator)
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
uint8_t WaspBG96::waitForSignal()
{
	return waitForSignal(60000, -1.0);
}


/* Function:	It waits for satellites signal
 * Parameters:	timeout: milliseconds to wait for signal
 * Return:		'0' if OK; '1' if error
 */
uint8_t WaspBG96::waitForSignal(uint32_t timeout)
{
	return waitForSignal(timeout, -1.0);
}


/* Function:	It waits for satellites signal
 * Parameters:	timeout: milliseconds to wait for signal
 * Return:		'0' if OK; '1' if error
 */
uint8_t WaspBG96::waitForSignal(uint32_t timeout, float desired_HDOP)
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

		#if DEBUG_BG96 > 1
			PRINT_BG96(F("checkGPS answer: "));
			USB.println(answer);
		#endif

		if (answer == 0)
		{
			if ((_fixMode == 2) || (_fixMode == 3))
			{
				// Good options:
				// 	2 - 2D fix
				// 	3 - 3D fix
				#if DEBUG_BG96 > 1
					PRINT_BG96(F("_fixMode ok\n"));
				#endif
				break;
			}
			else
			{
				#if DEBUG_BG96 > 1
					PRINT_BG96(F("_fixMode is not correct yet. _fixmode = "));
					USB.println(_fixMode, DEC);
				#endif
			}
		}
		else
		{

			#if DEBUG_BG96 > 1
			PRINT_BG96(F("checkGPS error\n"));
			#endif
		}

		delay(500);

		if (millis()-previous > timeout)
		{
			// timeout error
			#if DEBUG_BG96 > 0
				PRINT_BG96(F("_fixMode error timeout ==> Exit function\n"));
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
		#if DEBUG_BG96 > 0
			PRINT_BG96(F("_hdop not valid\n"));
		#endif
		return 1;
	}

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
uint8_t WaspBG96::getTemp()
{
	int answer;
	char *ptr;
	char command_answer[20];
	char command_buffer[20];

	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[21])));	//AT+QTEMP
	strcpy_P(command_answer, (char*)pgm_read_word(&(table_AT[22])));	//+QADC:

	// send command
	answer = (int)sendCommand(command_buffer, command_answer, sBG96_ERROR, 2000);
	if (answer != 1)
	{
		return 1;
	}

	answer = waitFor(sBG96_OK, 2000);
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
uint8_t WaspBG96::getRSSI()
{
	uint8_t answer;
	uint8_t error;
	char command_buffer[30];
	char delimiters[30];

	// AT+CSQ\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[5])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR, 2000);

	// check answer
	if (answer == 1)
	{
		// delimiters <-- "AT+CSQ\r\n: ,"
		strcpy_P(delimiters, (char*)pgm_read_word(&(table_AT[33])));

		error = parseInt(&_rssi, delimiters);

		if (error != 0)
		{
			return 1;
		}

		#if DEBUG_BG96 > 0
			USB.print(F("Raw RSSI: "));
			USB.println(_rssi, DEC);
		#endif

		// converts the RSSI from the command to dBm
		switch(_rssi)
		{
			case 0:
				_rssi = -113;
			case 99:
				_rssi = -1000;
				break;
			case 1:
				_rssi = -111;
				break;
			case 31:
				_rssi = -51;
				break;
			default:
				_rssi = (_rssi * 2) - 113;
		}

		return 0;
	}

	return 1;

}


/* Function: This function gets the operator name
 * Return:	'0' if OK; 'x' if error
*/
uint8_t WaspBG96::getOperator(char* answer_storage)
{
	uint8_t answer;
	char command_buffer[50];
	char* pointer;

	// AT+COPS?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[24])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 5000);

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

/* Function: This function search the operator names and numbers.
 * Return:	'0' if OK; 'x' if error
*/
uint8_t WaspBG96::scanOperators()
{
	uint8_t answer;
	char command_buffer[50];
	char* pointer;
	
	USB.println(F("This operation could take a time..."));
	// AT+COPS?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[58])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 35000);

	// check answer
	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}
	/*
	// parse response: "+COPS: 0,0,"<answer>",7"\r\n
	pointer = strtok((char*)_buffer, "\"");

	if (pointer == NULL)
	{
		return 2;
	}

	strcpy(answer_storage, (char*) strtok(NULL, "\""));
	*/

	return 0;
}


/* Function: 	This function gets info from the module
 * Parameters:	info_req:
 * 					WaspBG96::INFO_HW
 * 					WaspBG96::INFO_MANUFACTURER_ID
 * 					WaspBG96::INFO_MODEL_ID
 * 					WaspBG96::INFO_REV_ID
 * 					WaspBG96::INFO_IMEI
 * 					WaspBG96::INFO_IMSI
 * 					WaspBG96::INFO_ICCID
 *					WaspBG96::INFO_CSQ
 * 					WaspBG96::INFO_QNWINFO
 * 					WaspBG96::INFO_QCSQ
 * 					WaspBG96::INFO_QSPN
 * Return:	0 if OK; 1 if error
*/
int8_t WaspBG96::getInfo(uint8_t info_req)
{
	uint8_t answer;
	char command_buffer[50];

	switch (info_req)
	{
		case 0:
			// Hardware revision
			// "ATI\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[12])));
			break;
		case 1:
			// Manufacturer identification
			// "AT+CGMI\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[13])));
			break;
		case 2:
			// Model identification
			// "AT+CGMM\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[14])));
			break;
		case 3:
			// Revision identification
			// "AT+CGMR\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[15])));
			break;
		case 4:
			// IMEI
			// "AT+CGSN\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[16])));
			break;
		case 5:
			// IMSI
			// "AT+CIMI\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[17])));
			break;
		case 6:
			// ICCID
			// "AT+CCID\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[18])));
			break;
		case 7:
			// CSQ
			// "AT+CSQ\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[5])));
			break;
		case 8:
			// QNWINFO
			// "AT+QNWINFO\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[6])));
			break;
		case 9:
			// QCSQ
			// "AT+QCSQ\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[7])));
			break;
		case 10:
			// QSPN
			// "AT+QSPN\r"
			strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[8])));
			break;
	}

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR, 2000);

	// check answer
	if (answer == 1)
	{
		char aux[60];
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
		answer = parseString(aux, sizeof(aux), "\r\n");

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

/* Ping to Remote Server
 *
 *
 */
uint8_t WaspBG96::getPing(char*  host)
{
	uint8_t answer;
	char command_buffer[30];

	// AT+QPING=1,\"%s\"\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[31])), host);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);

	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("Ping configuration:"));
		USB.println(command_buffer);
	#endif

	return 0;
}


/* Configure Address of DNS Server
 *
 *
 */
uint8_t WaspBG96::setDNSServer(char*  pridnsaddr, char* secdnsaddr)
{
	uint8_t answer;
	char command_buffer[30];
		
	// AT+QIDNSCFG=<contextID=1>,<pri dnsaddr>[,<secdnsaddr>]
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[10])), pridnsaddr, secdnsaddr);	 
	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	

	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("DNS configuration:"));
		sendCommand("AT+QIDNSCFG=1\r", sBG96_OK, 2000);
		USB.println(_buffer, _length);
	#endif

	return 0;
}


/*
 * This function sets the RTC time and date from the Network's response
 *
 * @return '0' if OK; '1' if error
 *
 */
uint8_t WaspBG96::setTimeFromBG96()
{
	int8_t answer, networkType;
	char format[60];
	char command_buffer[50];
	uint8_t year, month, day;
	uint8_t hour, minute, second, timezone;
	bool RTC_status;

	// AT+CCLK?\r
	strcpy_P(command_buffer, (char*)pgm_read_word(&(table_AT[25])));

	// send command
	answer =  sendCommand(command_buffer, "\"", sBG96_ERROR, 2000);

	if (answer == 1)
	{
		waitFor("\"", 2000);

		// format <-- "%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%hhd\""
		strcpy_P(format, (char*)pgm_read_word(&(table_AT[35])));

		sscanf(	(char*)_buffer,
				format,
				&year,
				&month,
				&day,
				&hour,
				&minute,
				&second,
				&timezone);

		#if DEBUG_BG96 > 0
			PRINT_BG96(F("Network time:"));
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

		#if DEBUG_BG96 > 0
			USB.print(F("RTC time before: "));
			USB.println(RTC.getTime());
		#endif

		// set Time & Date
		RTC.setTime( year, month, day, (uint8_t)RTC.dow((int)year, (int)month, (int)day), hour, minute, second);

		#if DEBUG_BG96 > 0
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
void WaspBG96::set_APN( char* apn)
{

	set_APN( apn, NULL, NULL);
}

/* This function sets the apn, login and password from operator
 * Parameters:	apn: operator APN
 * 				login: login or user
 * 				password: password
 * Return: nothing
*/
void WaspBG96::set_APN( char* apn, char* login, char* password)
{

	memset(_apn, '\0', sizeof(_apn));
	memset(_apn_login, '\0', sizeof(_apn_login));
	memset(_apn_password, '\0', sizeof(_apn_password));

	strncpy(_apn, apn, min(sizeof(_apn), strlen(apn)));
	strncpy(_apn_login, login, min(sizeof(_apn_login), strlen(login)));
	strncpy(_apn_password, password, min(sizeof(_apn_password), strlen(password)));

}

/* This function sets the eIDRX parameters
 *  Parameters: uint8_t status: 0: eIDRX disabled and 1: eIDRX enabled
 * Return: nothing
*/
void WaspBG96::set_eIDRX(uint8_t status)
{

	set_eIDRX( status, NULL);
}

/* This function sets the eIDRX parameters
 * Parameters:	 uint8_t status: 0: eIDRX disabled and 1: eIDRX enabled
 * 				 char* eIDRX_time: time parameter  (binary)	
 * 				password: password
 * Return: nothing
*/
void WaspBG96::set_eIDRX( uint8_t status, char* eIDRX_time)
{
	if (status == 1){
		memset(_eIDRX_value, '\0', sizeof(_eIDRX_value));	
		strncpy(_eIDRX_value, eIDRX_time, min(sizeof(_eIDRX_value), strlen(eIDRX_time)));
		// eIDRX enabled
		_eIDRX_status = 1;
	}
	else if ( status == 0){
		_eIDRX_status = 0;
	}

}

/* This function shows the apn, login and password constants
 *
 * Return: nothing
*/
void WaspBG96::show_APN()
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

/* Synchronize Local Time with NTP Server
 * Parameter: host: The address of NTP server.
 * 			  port: The port of NTP server. The range is 1-65535.
 *
 * Return: '0' if OK; 'x' if error
*/
uint8_t WaspBG96::syncLocalTimeNTP(char* host, uint16_t port )
{
	uint8_t answer;
	char command_buffer[30];

	// AT+QNTP1,\"%s\",%d\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[34])), host, port);

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);

	if (answer != 1)
	{
		if (answer == 2)
		{
			getErrorCode();
		}
		return 1;
	}

	#if DEBUG_BG96 > 1
		PRINT_BG96(F("NTP configuration:"));
		sendCommand("AT+QNTP?\r", sBG96_OK, 2000);
		USB.println(_buffer, _length);
		PRINT_BG96(F("local clock time:"));
		sendCommand("AT+CCLK?\r", sBG96_OK, 2000);
		USB.println(_buffer, _length);
	#endif
	
	// AT+CCLK?\r
	sprintf_P(command_buffer, (char*)pgm_read_word(&(table_AT[25])));

	// send command
	answer = sendCommand(command_buffer, sBG96_OK, sBG96_ERROR_CODE, sBG96_ERROR, 2000);
	
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

// DS2413 Pin expander function.
bool WaspBG96::write(uint8_t state)
{
  uint8_t ack = 0;
  
  /* Top six bits must '1' */
  state |= 0xFC;
  
  oneWireDS.reset();
  oneWireDS.select(addressDS);
  oneWireDS.write(DS2413_ACCESS_WRITE);
  oneWireDS.write(state);
  oneWireDS.write(~state);                    /* Invert data and resend     */    
  ack = oneWireDS.read();                     /* 0xAA=success, 0xFF=failure */  
  if (ack == DS2413_ACK_SUCCESS)
  {
    oneWireDS.read();                          /* Read the status byte      */
  }
  oneWireDS.reset();
    
  return (ack == DS2413_ACK_SUCCESS ? true : false);
}

void WaspBG96::printBytes(uint8_t* addr, uint8_t count) 
{
  for (uint8_t i = 0; i < count; i++) 
  {
    USB.print(addr[i]>>4, HEX);
    USB.print(addr[i]&0x0f, HEX);
    USB.print(" ");
  }

    USB.println();
}


/* This function shows the error code number stored in the related attribute
 *
 * @return: nothing
 */
void WaspBG96::printErrorCode()
{
	printErrorCode(_errorCode);
}



#if DEBUG_BG96 > 0
/* This function shows the error code indicated as input
 *
 * @return: nothing
 */
void WaspBG96::printErrorCode( uint16_t error )
{
	PRINT_BG96(F("==> ERROR CODE: "));
	switch (error)
	{
		case BG96_CME_ERROR_0000: USB.println(F("phone failure")); break;
		case BG96_CME_ERROR_0001: USB.println(F("No connection to phone")); break;
		case BG96_CME_ERROR_0002: USB.println(F("phone-adaptor link reserved")); break;
		case BG96_CME_ERROR_0003: USB.println(F("operation not allowed")); break;
		case BG96_CME_ERROR_0004: USB.println(F("operation not supported")); break;
		case BG96_CME_ERROR_0005: USB.println(F("PH-SIM PIN required")); break;
		case BG96_CME_ERROR_0010: USB.println(F("SIM not inserted")); break;
		case BG96_CME_ERROR_0011: USB.println(F("SIM PIN required")); break;
		case BG96_CME_ERROR_0012: USB.println(F("SIM PUK required")); break;
		case BG96_CME_ERROR_0013: USB.println(F("SIM failure")); break;
		case BG96_CME_ERROR_0014: USB.println(F("SIM busy")); break;
		case BG96_CME_ERROR_0015: USB.println(F("SIM wrong")); break;
		case BG96_CME_ERROR_0016: USB.println(F("incorrect password")); break;
		case BG96_CME_ERROR_0017: USB.println(F("SIM PIN2 required")); break;
		case BG96_CME_ERROR_0018: USB.println(F("SIM PUK2 required")); break;
		case BG96_CME_ERROR_0020: USB.println(F("memory full")); break;
		case BG96_CME_ERROR_0021: USB.println(F("invalid index")); break;
		case BG96_CME_ERROR_0022: USB.println(F("not found")); break;
		case BG96_CME_ERROR_0023: USB.println(F("memory failure")); break;
		case BG96_CME_ERROR_0024: USB.println(F("text string too long")); break;
		case BG96_CME_ERROR_0025: USB.println(F("invalid characters in text string")); break;
		case BG96_CME_ERROR_0026: USB.println(F("dial string too long")); break;
		case BG96_CME_ERROR_0027: USB.println(F("invalid characters in dial string")); break;
		case BG96_CME_ERROR_0030: USB.println(F("no network service")); break;
		case BG96_CME_ERROR_0031: USB.println(F("network time-out")); break;
		case BG96_CME_ERROR_0032: USB.println(F("network not allowed - emergency calls only")); break;
		case BG96_CME_ERROR_0040: USB.println(F("network personalization PIN required")); break;
		case BG96_CME_ERROR_0041: USB.println(F("network personalization PUK required")); break;
		case BG96_CME_ERROR_0042: USB.println(F("network subset personalization PIN required")); break;
		case BG96_CME_ERROR_0043: USB.println(F("network subset personalization PUK required")); break;
		case BG96_CME_ERROR_0044: USB.println(F("service provider personalization PIN required")); break;
		case BG96_CME_ERROR_0045: USB.println(F("Service provider personalization PUK required")); break;
		case BG96_CME_ERROR_0046: USB.println(F("corporate personalization PIN required")); break;
		case BG96_CME_ERROR_0047: USB.println(F("corporate personalization PUK required")); break;
		case BG96_CME_ERROR_0100: USB.println(F("unknown")); break;
		case BG96_CME_ERROR_0770: USB.println(F("SIM invalid")); break;
		case BG96_CME_ERROR_0103: USB.println(F("Illegal MS (#3)*")); break;
		case BG96_CME_ERROR_0106: USB.println(F("Illegal ME (#6)*")); break;
		case BG96_CME_ERROR_0107: USB.println(F("GPRS service not allowed (#7)*")); break;
		case BG96_CME_ERROR_0111: USB.println(F("PLMN not allowed (#11)*")); break;
		case BG96_CME_ERROR_0112: USB.println(F("Location area not allowed (#12)*")); break;
		case BG96_CME_ERROR_0113: USB.println(F("Roaming not allowed in this location area (#13)*")); break;
		case BG96_CME_ERROR_0132: USB.println(F("service option not supported (#32)*")); break;
		case BG96_CME_ERROR_0133: USB.println(F("requested service option not subscribed (#33)*")); break;
		case BG96_CME_ERROR_0134: USB.println(F("service option temporarily out of order (#34)*")); break;
		case BG96_CME_ERROR_0148: USB.println(F("unspecified GPRS error")); break;
		case BG96_CME_ERROR_0149: USB.println(F("PDP authentication failure")); break;
		case BG96_CME_ERROR_0150: USB.println(F("invalid mobile class")); break;
		case BG96_CME_ERROR_0407: USB.println(F("File already existed")); break;		
		case BG96_CME_ERROR_0550: USB.println(F("generic undocumented error")); break;
		case BG96_CME_ERROR_0551: USB.println(F("wrong state")); break;
		case BG96_CME_ERROR_0552: USB.println(F("wrong mode")); break;
		case BG96_CME_ERROR_0553: USB.println(F("context already activated")); break;
		case BG96_CME_ERROR_0554: USB.println(F("stack already active")); break;
		case BG96_CME_ERROR_0555: USB.println(F("activation failed")); break;
		case BG96_CME_ERROR_0556: USB.println(F("context not opened")); break;
		case BG96_CME_ERROR_0557: USB.println(F("cannot setup socket")); break;
		case BG96_CME_ERROR_0558: USB.println(F("cannot resolve DN")); break;
		case BG96_CME_ERROR_0559: USB.println(F("time-out in opening socket")); break;
		case BG96_CME_ERROR_0560: USB.println(F("cannot open socket")); break;
		case BG96_CME_ERROR_0561: USB.println(F("remote disconnected or time-out")); break;
		case BG96_CME_ERROR_0562: USB.println(F("connection failed")); break;
		case BG96_CME_ERROR_0563: USB.println(F("tx error")); break;
		case BG96_CME_ERROR_0564: USB.println(F("already listening")); break;
		case BG96_CME_ERROR_0568: USB.println(F("wrong PDP")); break;
		case BG96_CME_ERROR_0615: USB.println(F("FTP not connected")); break;
		case BG96_CME_ERROR_0623: USB.println(F("FTP write data closed")); break;
		case BG96_CME_ERROR_0642: USB.println(F("FTP open channel timeout")); break;
		case BG96_CME_ERROR_0643: USB.println(F("FTP communication timeout")); break;
		case BG96_CME_ERROR_0657: USB.println(F("Network survey error (No Carrier)*")); break;
		case BG96_CME_ERROR_0658: USB.println(F("Network survey error (Busy)*")); break;
		case BG96_CME_ERROR_0659: USB.println(F("Network survey error (Wrong request)*")); break;
		case BG96_CME_ERROR_0660: USB.println(F("Network survey error (Aborted)*")); break;
		case BG96_CME_ERROR_0257: USB.println(F("network rejected request")); break;
		case BG96_CME_ERROR_0258: USB.println(F("retry operation")); break;
		case BG96_CME_ERROR_0259: USB.println(F("invalid deflected to number")); break;
		case BG96_CME_ERROR_0260: USB.println(F("deflected to own number")); break;
		case BG96_CME_ERROR_0261: USB.println(F("unknown subscriber")); break;
		case BG96_CME_ERROR_0262: USB.println(F("service not available")); break;
		case BG96_CME_ERROR_0263: USB.println(F("unknown class specified")); break;
		case BG96_CME_ERROR_0264: USB.println(F("unknown network message")); break;
		case BG96_CME_ERROR_0680: USB.println(F("LU processing")); break;
		case BG96_CME_ERROR_0681: USB.println(F("Network search aborted")); break;
		case BG96_CME_ERROR_0682: USB.println(F("PTM mode")); break;
		case BG96_CME_ERROR_0683: USB.println(F("Active call state")); break;
		case BG96_CME_ERROR_0684: USB.println(F("SSL already activated")); break;
		case BG96_CMS_ERROR_0300: USB.println(F("ME failure")); break;
		case BG96_CMS_ERROR_0301: USB.println(F("SMS service of ME reserved")); break;
		case BG96_CMS_ERROR_0302: USB.println(F("operation not allowed")); break;
		case BG96_CMS_ERROR_0303: USB.println(F("operation not supported")); break;
		case BG96_CMS_ERROR_0304: USB.println(F("invalid PDU mode parameter")); break;
		case BG96_CMS_ERROR_0305: USB.println(F("invalid text mode parameter")); break;
		case BG96_CMS_ERROR_0310: USB.println(F("SIM not inserted")); break;
		case BG96_CMS_ERROR_0311: USB.println(F("SIM PIN required")); break;
		case BG96_CMS_ERROR_0312: USB.println(F("PH-SIM PIN required")); break;
		case BG96_CMS_ERROR_0313: USB.println(F("SIM failure")); break;
		case BG96_CMS_ERROR_0314: USB.println(F("SIM busy")); break;
		case BG96_CMS_ERROR_0315: USB.println(F("SIM wrong ")); break;
		case BG96_CMS_ERROR_0316: USB.println(F("SIM PUK required")); break;
		case BG96_CMS_ERROR_0317: USB.println(F("SIM PIN2 required")); break;
		case BG96_CMS_ERROR_0318: USB.println(F("SIM PUK2 required")); break;
		case BG96_CMS_ERROR_0320: USB.println(F("memory failure")); break;
		case BG96_CMS_ERROR_0321: USB.println(F("invalid memory index")); break;
		case BG96_CMS_ERROR_0322: USB.println(F("memory full")); break;
		case BG96_CMS_ERROR_0330: USB.println(F("SMSC address unknown")); break;
		case BG96_CMS_ERROR_0331: USB.println(F("no network service")); break;
		case BG96_CMS_ERROR_0332: USB.println(F("network time-out")); break;
		case BG96_CMS_ERROR_0340: USB.println(F("no +CNMA acknowledgement expected")); break;
		case BG96_CMS_ERROR_0500: USB.println(F("unknown error")); break;
		case BG96_CME_ERROR_1000: USB.println(F("SSL not activated")); break;
		case BG96_CME_ERROR_1001: USB.println(F("SSL certs and keys wrong or not stored")); break;
		case BG96_CME_ERROR_1003: USB.println(F("SSL already activated")); break;
		case BG96_CME_ERROR_1005: USB.println(F("SSL socket error")); break;
		case BG96_CME_ERROR_1008: USB.println(F("SSL not connected")); break;
		default: USB.println(F("UNKNOWN"));	break;
	}
}
#else
void WaspBG96::printErrorCode( uint16_t error )
{
	USB.print(F("==> ERROR CODE: "));
	USB.println( error, DEC);
}
#endif


// Preinstantiate Objects /////////////////////////////////////////////////////

WaspBG96 BG96 = WaspBG96();

///////////////////////////////////////////////////////////////////////////////
