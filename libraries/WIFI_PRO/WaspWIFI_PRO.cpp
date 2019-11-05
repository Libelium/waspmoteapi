/*! \file WaspWIFI_PRO.cpp
 *  \brief Library for managing WIFI_PRO modules
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
 *  Version:		3.5
 *  Design:			David Gascón
 *  Implementation:	Yuri Carmona
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

#include "WaspWIFI_PRO.h"

//! MACROS
#define NARGS_SEQ(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,N,...) N
#define NARGS(...) NARGS_SEQ(__VA_ARGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define GEN_ATCOMMAND1(...) generator(1, NARGS(__VA_ARGS__) - 1, __VA_ARGS__)
#define GEN_ATCOMMAND2(...) generator(2, NARGS(__VA_ARGS__) - 1, __VA_ARGS__)
#define GEN_ATCOMMAND3(...) generator(3, NARGS(__VA_ARGS__) - 1, __VA_ARGS__)
#define GEN_ATQUERY(...) 	generator(4, NARGS(__VA_ARGS__) - 1, __VA_ARGS__)
#define GEN_ATQUERY2(...) 	generator(5, NARGS(__VA_ARGS__) - 1, __VA_ARGS__)


/// PRIVATE METHODS ////////////////////////////////////////////////////////////


void WaspWIFI_PRO::generator(uint8_t type, int n, const char *cmdCode, ...)
{
	// define pointer
	char* pointer;

	// clear buffer
	memset( _command, 0x00, sizeof(_command) );

	// add "at+i"
    strncat(_command, AT_I, strlen(AT_I) );
	// add command code
    strncat(_command, cmdCode, strlen(cmdCode) );

    // if number of arguments is greater than zero
	// then add the corresponding delimiter
	if (n > 0)
	{
		// Add delimiter type
		switch (type)
		{
			case TYPE_SET_EQ:	strncat(_command, "=",  1 );	break;
			case TYPE_SET_DOT:	strncat(_command, ":",  1 );	break;
			case TYPE_ASSIGN:	strncat(_command, "~",  1 );	break;
			default:
				#if DEBUG_WIFI_PRO > 0
					PRINT_WIFI_PRO(F("error type\n"));
				#endif
				return (void)0;
		}
	}
	else if (n == 0)
	{
		// Add delimiter type
		switch (type)
		{
			case TYPE_READ:		strncat(_command, "?",  1 );	break;
			case TYPE_ALLOWED:	strncat(_command, "=?", 2 );	break;
			default: break;
		}
	}

	// if it is a set command type add argument in list adding ',' in between
    if(	(type == TYPE_SET_EQ)
    || 	(type == TYPE_SET_DOT) )
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
			if (pointer == NULL)
			{
				continue;
			}

			// add ',' except for the first argument
			if (i != 0)
			{
				strncat(_command, ",", 1 );
			}

			// calculate size after adding the new argument to check if
			// the new arguments fits inside the buffer or not
			size_t next_size = strlen(pointer) + strlen( _command ) + strlen("\r");

			if (next_size < sizeof( _command)-1)
			{
				// add the new argument to buffer
				strncat( _command, pointer, strlen(pointer));
			}
			else
			{
				//error
				#if DEBUG_WIFI_PRO > 0
					PRINT_WIFI_PRO(F("not enough buffer size\n"));
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
    #if DEBUG_WIFI_PRO > 1
		PRINT_WIFI_PRO(F("_command: "));
		USB.println( _command );
	#endif
}



void WaspWIFI_PRO::printErrorCode()
{
	printErrorCode( _errorCode);
}

#if DEBUG_WIFI_PRO > 0
void WaspWIFI_PRO::printErrorCode( uint16_t error )
{
	PRINT_WIFI_PRO(F("==> ERROR CODE: "));
	switch (error)
	{
		case ERROR_CODE_0000: USB.println(F("Timeout")); break;
		case ERROR_CODE_0010: USB.println(F("SD not present")); break;
		case ERROR_CODE_0011: USB.println(F("file not created")); break;
		case ERROR_CODE_0012: USB.println(F("SD error open file")); break;
		case ERROR_CODE_0013: USB.println(F("SD error set file offset")); break;
		case ERROR_CODE_0014: USB.println(F("SD error writing")); break;
		case ERROR_CODE_0020: USB.println(F("rx buffer full")); break;
		case ERROR_CODE_0021: USB.println(F("error downloading UPGRADE.TXT")); break;
		case ERROR_CODE_0022: USB.println(F("filename in UPGRADE.TXT is not a 7-byte name")); break;
		case ERROR_CODE_0023: USB.println(F("no FILE label is found in UPGRADE.TXT")); break;
		case ERROR_CODE_0024: USB.println(F("NO_FILE is defined as FILE in UPGRADE.TXT")); break;
		case ERROR_CODE_0025: USB.println(F("no PATH label is found in UPGRADE.TXT")); break;
		case ERROR_CODE_0026: USB.println(F("no SIZE label is found in UPGRADE.TXT")); break;
		case ERROR_CODE_0027: USB.println(F("no VERSION label is found in UPGRADE.TXT")); break;
		case ERROR_CODE_0028: USB.println(F("version indicated in UPGRADE.TXT is lower/equal to Waspmote's version")); break;
		case ERROR_CODE_0029: USB.println(F("file size does not match the indicated in UPGRADE.TXT")); break;
		case ERROR_CODE_0030: USB.println(F("error downloading binary file")); break;
		case ERROR_CODE_0031: USB.println(F("invalid data length")); break;
		case ERROR_CODE_0041: USB.println(F("Illegal delimiter")); break;
		case ERROR_CODE_0042: USB.println(F("Illegal value")); break;
		case ERROR_CODE_0043: USB.println(F("CR expected ")); break;
		case ERROR_CODE_0044: USB.println(F("Number expected")); break;
		case ERROR_CODE_0045: USB.println(F("CR or ‘,’ expected")); break;
		case ERROR_CODE_0046: USB.println(F("DNS expected")); break;
		case ERROR_CODE_0047: USB.println(F("‘:’ or ‘~’ expected")); break;
		case ERROR_CODE_0048: USB.println(F("String expected")); break;
		case ERROR_CODE_0049: USB.println(F("‘:’ or ‘=’ expected")); break;
		case ERROR_CODE_0050: USB.println(F("Text expected")); break;
		case ERROR_CODE_0051: USB.println(F("Syntax error")); break;
		case ERROR_CODE_0052: USB.println(F("‘,’ expected")); break;
		case ERROR_CODE_0053: USB.println(F("Illegal cmd code")); break;
		case ERROR_CODE_0054: USB.println(F("Error when setting parameter")); break;
		case ERROR_CODE_0055: USB.println(F("Error when getting parameter value")); break;
		case ERROR_CODE_0056: USB.println(F("User abort")); break;
		case ERROR_CODE_0057: USB.println(F("Error when trying to establish PPP")); break;
		case ERROR_CODE_0058: USB.println(F("Error when trying to establish SMTP")); break;
		case ERROR_CODE_0059: USB.println(F("Error when trying to establish POP3")); break;
		case ERROR_CODE_0060: USB.println(F("Single session body for MIME exceeds the maximum allowed")); break;
		case ERROR_CODE_0061: USB.println(F("Internal memory failure")); break;
		case ERROR_CODE_0062: USB.println(F("User aborted the system")); break;
		case ERROR_CODE_0063: USB.println(F("~CTSH needs to be LOW to change to hardware flow control")); break;
		case ERROR_CODE_0064: USB.println(F("User aborted last cmd using ‘---’")); break;
		case ERROR_CODE_0065: USB.println(F("iChip unique ID already exists")); break;
		case ERROR_CODE_0066: USB.println(F("Error when setting the MIF parameter")); break;
		case ERROR_CODE_0067: USB.println(F("Cmd ignored as irrelevant")); break;
		case ERROR_CODE_0068: USB.println(F("iChip serial number already exists")); break;
		case ERROR_CODE_0069: USB.println(F("Timeout on host communication")); break;
		case ERROR_CODE_0070: USB.println(F("Modem failed to respond")); break;
		case ERROR_CODE_0071: USB.println(F("No dial tone response")); break;
		case ERROR_CODE_0072: USB.println(F("No carrier modem response")); break;
		case ERROR_CODE_0073: USB.println(F("Dial failed")); break;
		case ERROR_CODE_0074: USB.println(F("WLAN connection lost")); break;
		case ERROR_CODE_0075: USB.println(F("Access denied to ISP server")); break;
		case ERROR_CODE_0076: USB.println(F("Unable to locate POP3 server")); break;
		case ERROR_CODE_0077: USB.println(F("POP3 server timed out")); break;
		case ERROR_CODE_0078: USB.println(F("Access denied to POP3 server")); break;
		case ERROR_CODE_0079: USB.println(F("POP3 failed ")); break;
		case ERROR_CODE_0080: USB.println(F("No suitable message in mailbox")); break;
		case ERROR_CODE_0081: USB.println(F("Unable to locate SMTP server")); break;
		case ERROR_CODE_0082: USB.println(F("SMTP server timed out")); break;
		case ERROR_CODE_0083: USB.println(F("SMTP failed")); break;
		case ERROR_CODE_0086: USB.println(F("Writing to internal non-volatile parameters database failed")); break;
		case ERROR_CODE_0087: USB.println(F("Web server IP registration failed")); break;
		case ERROR_CODE_0088: USB.println(F("Socket IP registration failed")); break;
		case ERROR_CODE_0089: USB.println(F("E-mail IP registration failed")); break;
		case ERROR_CODE_0090: USB.println(F("IP registration failed for all methods specified")); break;
		case ERROR_CODE_0094: USB.println(F("In Always Online mode, connection was lost and re-established")); break;
		case ERROR_CODE_0096: USB.println(F("A remote host, which had taken over iChip through the LATI port, was disconnected")); break;
		case ERROR_CODE_0100: USB.println(F("Error restoring default parameters")); break;
		case ERROR_CODE_0101: USB.println(F("No ISP access numbers defined")); break;
		case ERROR_CODE_0102: USB.println(F("No USRN defined")); break;
		case ERROR_CODE_0103: USB.println(F("No PWD entered")); break;
		case ERROR_CODE_0104: USB.println(F("No DNS defined")); break;
		case ERROR_CODE_0105: USB.println(F("POP3 server not defined")); break;
		case ERROR_CODE_0106: USB.println(F("MBX (mailbox) not defined")); break;
		case ERROR_CODE_0107: USB.println(F("MPWD (mailbox password) not defined")); break;
		case ERROR_CODE_0108: USB.println(F("TOA (addressee) not defined")); break;
		case ERROR_CODE_0109: USB.println(F("REA (return e-mail address) not defined")); break;
		case ERROR_CODE_0110: USB.println(F("SMTP server not defined")); break;
		case ERROR_CODE_0111: USB.println(F("Serial data overflow")); break;
		case ERROR_CODE_0112: USB.println(F("Illegal cmd when modem online")); break;
		case ERROR_CODE_0113: USB.println(F("Remote firmware update attempted but not completed. The original firmware remained intact.")); break;
		case ERROR_CODE_0114: USB.println(F("E-mail parameters update rejected")); break;
		case ERROR_CODE_0115: USB.println(F("SerialNET could not be started due to missing parameters")); break;
		case ERROR_CODE_0116: USB.println(F("Error parsing a new trusted CA certificate")); break;
		case ERROR_CODE_0117: USB.println(F("Error parsing a new Private Key")); break;
		case ERROR_CODE_0118: USB.println(F("Protocol specified in the USRV parameter does not exist or is unknown")); break;
		case ERROR_CODE_0119: USB.println(F("WPA passphrase too short has to be 8-63 chars")); break;
		case ERROR_CODE_0122: USB.println(F("SerialNET error: Host Interface undefined (HIF=0)")); break;
		case ERROR_CODE_0123: USB.println(F("SerialNET mode error: Host baud rate cannot be determined")); break;
		case ERROR_CODE_0124: USB.println(F("SerialNET over TELNET error: HIF parameter must be set to 1 or 2")); break;
		case ERROR_CODE_0125: USB.println(F("Invalid WEP key")); break;
		case ERROR_CODE_0126: USB.println(F("Invalid parameters’ profile number")); break;
		case ERROR_CODE_0128: USB.println(F("Product ID already exists")); break;
		case ERROR_CODE_0129: USB.println(F("HW pin can not be changed after Product-ID was set ")); break;
		case ERROR_CODE_0200: USB.println(F("Socket does not exist")); break;
		case ERROR_CODE_0201: USB.println(F("Socket empty on receive")); break;
		case ERROR_CODE_0202: USB.println(F("Socket not in use")); break;
		case ERROR_CODE_0203: USB.println(F("Socket down")); break;
		case ERROR_CODE_0204: USB.println(F("No available sockets")); break;
		case ERROR_CODE_0206: USB.println(F("PPP open failed for socket")); break;
		case ERROR_CODE_0207: USB.println(F("Error creating socket")); break;
		case ERROR_CODE_0208: USB.println(F("Socket send error")); break;
		case ERROR_CODE_0209: USB.println(F("Socket receive error")); break;
		case ERROR_CODE_0210: USB.println(F("PPP down for socket")); break;
		case ERROR_CODE_0212: USB.println(F("Socket flush error ")); break;
		case ERROR_CODE_0215: USB.println(F("No carrier error on socket operation")); break;
		case ERROR_CODE_0216: USB.println(F("General exception")); break;
		case ERROR_CODE_0217: USB.println(F("Out of memory")); break;
		case ERROR_CODE_0218: USB.println(F("An STCP (Open Socket) cmd specified a local port number that is already in use")); break;
		case ERROR_CODE_0219: USB.println(F("SSL initialization/internal CA certificate loading error")); break;
		case ERROR_CODE_0220: USB.println(F("SSL3 negotiation error")); break;
		case ERROR_CODE_0221: USB.println(F("Illegal SSL socket handle. Must be an open and active TCP socket.")); break;
		case ERROR_CODE_0222: USB.println(F("Trusted CA certificate does not exist")); break;
		case ERROR_CODE_0224: USB.println(F("Decoding error on incoming SSL data")); break;
		case ERROR_CODE_0225: USB.println(F("No additional SSL sockets available")); break;
		case ERROR_CODE_0226: USB.println(F("Maximum SSL packet size (2KB) exceeded")); break;
		case ERROR_CODE_0227: USB.println(F("AT+iSSND cmd failed because size of stream sent exceeded 2048 bytes")); break;
		case ERROR_CODE_0228: USB.println(F("AT+iSSND cmd failed because checksum calculated does not match checksum sent by host")); break;
		case ERROR_CODE_0229: USB.println(F("SSL parameters are missing ")); break;
		case ERROR_CODE_0230: USB.println(F("Maximum packet size (4GB) exceeded")); break;
		case ERROR_CODE_0300: USB.println(F("HTTP server unknown")); break;
		case ERROR_CODE_0301: USB.println(F("HTTP server timeout ")); break;
		case ERROR_CODE_0303: USB.println(F("No URL specified ")); break;
		case ERROR_CODE_0304: USB.println(F("Illegal HTTP host name")); break;
		case ERROR_CODE_0305: USB.println(F("Illegal HTTP port number")); break;
		case ERROR_CODE_0306: USB.println(F("Illegal URL address")); break;
		case ERROR_CODE_0307: USB.println(F("URL address too long ")); break;
		case ERROR_CODE_0308: USB.println(F("The AT+iWWW cmd failed because iChip does not contain a home page")); break;
		case ERROR_CODE_0309: USB.println(F("WEB server is already active with a different backlog.")); break;
		case ERROR_CODE_0400: USB.println(F("MAC address exists")); break;
		case ERROR_CODE_0401: USB.println(F("No IP address")); break;
		case ERROR_CODE_0402: USB.println(F("Wireless LAN power set failed")); break;
		case ERROR_CODE_0403: USB.println(F("Wireless LAN radio control failed")); break;
		case ERROR_CODE_0404: USB.println(F("Wireless LAN reset failed")); break;
		case ERROR_CODE_0405: USB.println(F("Wireless LAN hardware setup failed")); break;
		case ERROR_CODE_0406: USB.println(F("Cmd failed because WiFi module is currently busy")); break;
		case ERROR_CODE_0407: USB.println(F("Illegal WiFi channel")); break;
		case ERROR_CODE_0408: USB.println(F("Illegal SNR threshold")); break;
		case ERROR_CODE_0409: USB.println(F("WPA connection process has not yet completed")); break;
		case ERROR_CODE_0410: USB.println(F("The network connection is offline (modem)")); break;
		case ERROR_CODE_0411: USB.println(F("Cmd is illegal when Bridge mode is active")); break;
		case ERROR_CODE_0501: USB.println(F("Communications platform already active")); break;
		case ERROR_CODE_0505: USB.println(F("Cannot open additional FTP session – all FTP handles in use")); break;
		case ERROR_CODE_0506: USB.println(F("Not an FTP session handle")); break;
		case ERROR_CODE_0507: USB.println(F("FTP server not found")); break;
		case ERROR_CODE_0508: USB.println(F("Timeout when connecting to FTP server")); break;
		case ERROR_CODE_0509: USB.println(F("Failed to login to FTP server (bad username or password or account)")); break;
		case ERROR_CODE_0510: USB.println(F("FTP cmd could not be completed")); break;
		case ERROR_CODE_0511: USB.println(F("FTP data socket could not be opened")); break;
		case ERROR_CODE_0512: USB.println(F("Failed to send data on FTP data socket")); break;
		case ERROR_CODE_0513: USB.println(F("FTP shutdown by remote server")); break;
		case ERROR_CODE_0550: USB.println(F("Telnet server not found")); break;
		case ERROR_CODE_0551: USB.println(F("Timeout when connecting to Telnet server")); break;
		case ERROR_CODE_0552: USB.println(F("Telnet cmd could not be completed")); break;
		case ERROR_CODE_0553: USB.println(F("Telnet session shutdown by remote server")); break;
		case ERROR_CODE_0554: USB.println(F("A Telnet session is not currently active")); break;
		case ERROR_CODE_0555: USB.println(F("A Telnet session is already open")); break;
		case ERROR_CODE_0556: USB.println(F("Telnet server refused to switch to BINARY mode")); break;
		case ERROR_CODE_0557: USB.println(F("Telnet server refused to switch to ASCII mode")); break;
		case ERROR_CODE_0560: USB.println(F("Client could not retrieve a ring response e-mail")); break;
		case ERROR_CODE_0561: USB.println(F("Remote peer closed the SerialNET socket")); break;
		case ERROR_CODE_0570: USB.println(F("PING destination not found")); break;
		case ERROR_CODE_0571: USB.println(F("No reply to PING request")); break;
		case ERROR_CODE_0600: USB.println(F("Port Forwarding Rule will create ambiguous NAT entry")); break;
		case ERROR_CODE_0084:
		case ERROR_CODE_0085:
		case ERROR_CODE_0091:
		case ERROR_CODE_0092:
		case ERROR_CODE_0093:
		case ERROR_CODE_0098:
		case ERROR_CODE_0099:
		case ERROR_CODE_0120:
		case ERROR_CODE_0121:
		case ERROR_CODE_0223:
		case ERROR_CODE_0302:
		case ERROR_CODE_0500:
		case ERROR_CODE_0502:
		case ERROR_CODE_0503:
		case ERROR_CODE_0504:
		case ERROR_CODE_0514:
		case ERROR_CODE_0558:
		case ERROR_CODE_0559: USB.println(F("RESERVED")); break;
		default: USB.println(F("UNKNOWN ***"));
	}
}
#else
void WaspWIFI_PRO::printErrorCode( uint16_t error )
{
	USB.print(F("==> ERROR CODE: "));
	USB.println( error, DEC);
}
#endif



/*
 * name: print all info in 'socket' structure
 *
 * @return	'0' if ok; '1' error
 *
 */
void WaspWIFI_PRO::printSockets()
{
	bool first = true;
	for (int i = 0; i < 10; i++)
	{
		if (socket[i].status == 0)
		{
			if (first)
			{
				first = false;
				USB.println(F("++++++++++++++"));
			}
			USB.print(F("handle:"));
			USB.println(socket[i].handle);
			USB.print(F("ip:"));
			USB.println(socket[i].ip);
			USB.print(F("port:"));
			USB.println(socket[i].port);
			USB.println(F("++++++++++++++"));
		}
	}
}




/*
 * name: getErrorCode()
 * This function waits until a ')' character is found in order to parse the
 * complete " (%u)" string. This function must be called after receiving a
 * "I/ERROR" response from the module because the complete "I/ERROR (%u)" is
 * going to be received
 *
 * If error code is parsed succesfully then the attribute _errorCode stores
 * this error information
 *
 * @return	'0' error; '1' ok
 */
uint16_t WaspWIFI_PRO::getErrorCode()
{
	uint8_t status;
	char format[20];

	// " (%u)"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[0])));


	// wait for "(nnn)" last parenthesis character
	status = waitFor((char*)")", 3000 );

	#if DEBUG_WIFI_PRO > 0
		PRINT_WIFI_PRO(F("I/ERROR\n"));
	#endif

	if (status == 0)
	{
		return 0;
	}
	else
	{
		// get error code from response
		sscanf( (char*)_buffer, format, &_errorCode );

		#if WIFI_DEBUG > 0
			printErrorCode( _errorCode );
		#endif
		return 1;
	}

}



/*
 * name: getResponse
 * @brief	Wait for "(nnn)" last parenthesis character
 * @return	'0' error; '1' ok; 'otherwise' see error code table
 */
uint16_t WaspWIFI_PRO::getResponse()
{
	uint8_t status;

	// wait for "(nnn)" last parenthesis character
	status = waitFor((char*)")", 3000 );

	if (status == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}



/*
 * name: getResponseValue
 * @brief 	This function expects to receive a response with the following
 * 			format: I/<value><CR><LF>. So, this function tries to get this
 * 			response and parse the <value> field
 *
 * @return	'0' error; '1' ok
 */
uint16_t WaspWIFI_PRO::getResponseValue()
{
	uint8_t status;
	char format_error[20];
	char format_ok[20];
	int result;

	// "I/ERROR (%u)\r\n"
	strcpy_P( format_error, (char*)pgm_read_word(&(table_WIFI_FORMAT[1])));
	// "I/%lu\r\n"
	strcpy_P( format_ok, (char*)pgm_read_word(&(table_WIFI_FORMAT[2])));

	// wait for "\r\n"
	status = waitFor( EOL_CR_LF, 20000);

	if (status == 0)
	{
		// timeout
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("[getResponseValue] No answer\n"));
		#endif
		_errorCode = ERROR_CODE_0000;
		return 0;
	}
	else
	{
		// check: I/ERROR(<err>)<CR><LF>
		if (find( _buffer, _length, I_ERROR) == true)
		{
			result = sscanf( (char*)_buffer, format_error, &_errorCode );

			if (result != 1)
			{
				_errorCode = 1;
			}

			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("[getResponseValue] I/ERROR found: "));
				printErrorCode();
			#endif
			return 0;
		}

		// check: I/<value><CR><LF>
		if (find( _buffer, _length, I_SLASH) == true)
		{
			result = sscanf( (char*)_buffer, format_ok, &_value );

			if (result == 1)
			{
				return 1;
			}
			else
			{
				#if DEBUG_WIFI_PRO > 0
					PRINT_WIFI_PRO(F("[getResponseValue] I/ found but no <value>\n"));
				#endif
				return 0;
			}
		}

		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("[getResponseValue] No pattern found:"));
			USB.println( _buffer, _length );
		#endif
		return 0;
	}

}


/*
 * name: getResponseValue2
 * @brief	This function expects to receive a response with the following
 * 			format: <value><CR><LF>. So, this function tries to get this
 * 			response and parse the <value> field
 *
 * @return	'0' error; '1' ok
 */
uint16_t WaspWIFI_PRO::getResponseValue2()
{
	uint8_t status;
	char pattern[20];
	char format_ok[20];
	char format_error[20];
	int result;

	// "\r\n"
	strcpy_P( pattern, (char*)pgm_read_word(&(table_WIFI_FORMAT[3])));
	// "ERROR ("
	strcpy_P( format_error, (char*)pgm_read_word(&(table_WIFI_FORMAT[4])));
	// "%lu\r\n"
	strcpy_P( format_ok, (char*)pgm_read_word(&(table_WIFI_FORMAT[5])));

	// wait for "\r\n"
	status = waitFor( pattern, format_error, 10000 );

	if (status == 0)
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 0;
	}
	else if (status == 1)
	{
		// pattern found then parse: <value><CR><LF>
		result = sscanf( (char*)_buffer, format_ok, &_value );

		if (result == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}

		return 0;
	}
	else if (status == 2)
	{
		// error pattern found then parse: "<errCode>)"
		status = getErrorCode();
		if (status == 1)
		{
			printErrorCode(_errorCode);
		}
		return 0;
	}
	else
	{
		return 0;
	}

}



/*
 * name: getResponseValue3
 * @brief	This function expects to receive a response with the following
 * 			format: "<hn1>,<hn2>,...,<hnbacklog>)". So, this function tries to
 * 			get these responses and parse the <hn> fields
 *
 * @return	'0' error; '1' ok
 */
uint8_t WaspWIFI_PRO::getResponseValue3()
{
	uint8_t status;
	char* pointer;
	int i = 0;
	char delimiters[20];

	// " ,)"
	strcpy_P( delimiters, (char*)pgm_read_word(&(table_WIFI_FORMAT[17])));

	// wait for ")"
	status = waitFor((char*)")", 1000 );

	if (status == 0)
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 0;
	}
	else if (status == 1)
	{
		pointer = strtok((char*)_buffer, delimiters);
		while ((pointer != NULL) && (i<_backlog))
		{
			if (atoi(pointer) == -1)
			{
				socket[i].status = -1;
			}
			else
			{
				socket[i].status = 0;
				socket[i].handle = atoi(pointer);
				#if DEBUG_WIFI_PRO > 1
					PRINT_WIFI_PRO(F("socket["));
					USB.print(i,DEC);
					USB.print(F("].handle="));
					USB.println(socket[i].handle,DEC);
				#endif
			}
			pointer = strtok (NULL, delimiters);
			i++;
		}

		return 1;
	}
	else
	{
		return 0;
	}
}




/*
 * name: getResponseValue4
 * This function expects to receive a response with the following format:
 * 		"<xxx.xxx.xxx.xxx>:<port>)"
 * So, this function tries to get these responses and parse the <hn> fields
 *
 * @return	'0' error; '1' ok
 */
uint8_t WaspWIFI_PRO::getResponseValue4(uint8_t index)
{
	uint8_t status;
	char* pointer;

	// wait for ")"
	status = waitFor((char*)")", 1000);

	if (status == 0)
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 0;
	}
	else if (status == 1)
	{
		// split string into pieces
		pointer = strtok((char*)_buffer, " :)");
		if (pointer == NULL) return 0;

		// get first field: IP address
		memset(socket[index].ip, 0x00, 16);
		if (strlen(pointer) > 15) return 0;
		strncpy(socket[index].ip, pointer, strlen(pointer) );
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("socket["));
			USB.print(index,DEC);
			USB.print(F("].ip:"));
			USB.println(socket[index].ip);
		#endif

		// get second field: port
		pointer = strtok (NULL, " :)");
		if (pointer == NULL) return 0;
		socket[index].port = atoi(pointer);
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("socket["));
			USB.print(index,DEC);
			USB.print(F("].port:"));
			USB.println(socket[index].port);
		#endif

		return 1;
	}
	else
	{
		return 0;
	}
}



/*
 * name: getResponseValue5
 * @brief	This function expects to receive a response with the following
 * 			format: "<sock0sz>, <sock1sz>, ... ,<sock9sz>)"
 * 			So, this function tries to get these responses and parse the <hn>
 * 			fields. It is used by the AT+iRP4 function to parse info after
 * 			finding "I/("
 * @return	'0' error; '1' ok
 */
uint8_t WaspWIFI_PRO::getResponseValue5()
{
	uint8_t status;
	char* pointer;
	int i = 0;
	char delimiters[20];

	// " ,)"
	strcpy_P( delimiters, (char*)pgm_read_word(&(table_WIFI_FORMAT[17])));

	// wait for ")"
	status = waitFor((char*)")", 1000 );

	if (status == 0)
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 0;
	}
	else if (status == 1)
	{
		pointer = strtok((char*)_buffer, delimiters);
		while ((pointer != NULL) && (i < _backlog))
		{
			socket[i].size = atoi(pointer);
			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("socket["));
				USB.print(i,DEC);
				USB.print(F("].size="));
				USB.println(socket[i].size,DEC);
			#endif

			pointer = strtok (NULL, delimiters);
			i++;
		}

		return 1;
	}
	else
	{
		return 0;
	}
}




/*
 * name: parseResponse
 * @brief	When this function is called, the answer to be parsed must be in
 * 			'_buffer'. Then the pattern "nnn)" is found and parsed.
 * @param 	uint16_t* number: pointer to number to parse in "nnn)"
 * @return	'0' ok; '1' error
 */
uint8_t WaspWIFI_PRO::parseResponse( uint16_t* number )
{
	int result;
	char format[10];

	// "%u)"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[12])));

	// parse "nnn)" contents in _buffer
	result = sscanf( (char*)_buffer, format, number );

	if (result == 0)
	{
		*number = 0;
		return 1;
	}

	return 0;
}



/*
 * name: parseResponse2
 * @param uint16_t* number: pointer to number to parse in "nnn:"
 * @return	'0' ok; '1' error
 */
uint8_t WaspWIFI_PRO::parseResponse2(uint16_t* number)
{
	int result;
	char format[10];

	// "I/%u:"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[13])));

	// parse "I/<sz>:" contents in _buffer
	result = sscanf( (char*)_buffer, format, number );

	if (result == 0)
	{
		*number = 0;
		return 1;
	}

	return 0;
}


/*
 * name: parseResponse3
 * @param uint16_t* number: pointer to number to parse in "nnn:"
 * @return	'0' ok; '1' error
 */
uint8_t WaspWIFI_PRO::parseResponse3()
{
	int result;
	uint8_t error;
	char format[50];

	// define time vars
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t yearH;
	uint8_t gmt_hour;
	uint8_t gmt_min;

	// "%02u%02u-%02u-%02uT%02u:%02u:%02u+%02u:%02u"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[14])));

	/* At this point, _buffer is supposed to have a pattern like this:
	*  "AT+iRP8\r\nYYYY-MM-DDTHH:MM:SS+HH:MM\r\nI/OK"
	* So, parse time settings
	*/

	char* pointer = strstr( (char*) _buffer, EOL_CR_LF);
	if (pointer == NULL) return 1;

	// go to correct index
	pointer++;
	pointer++;


	// parse "YYYY-MM-DDTHH:MM:SS+HH:MM" contents in _buffer
	result = sscanf(pointer,
					format,
					&yearH,
					&year,
					&month,
					&date,
					&hour,
					&minute,
					&second,
					&gmt_hour,
					&gmt_min);

	if (result != 9)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("parse failed\n"));
		#endif
		return 1;
	}

	// check good contents
	if ((year == 0)
	||	(month == 0)
	||	(date == 0))
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("bad RP8 answer\n"));
		#endif
		return 1;
	}

	// set time to RTC
	RTC.ON();
	error = RTC.setTime(year,
						month,
						date,
						RTC.dow(year, month, date),
						hour,
						minute,
						second);
	if (error == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}





/*
 * name: parseResponse4
 * Parse the info stored in _buffer with the format:
 * 		AT+i!rp10\r\n
 * 		<SSID>,<BSSID>,<security type>,<WPA status>,<channel>,<SNR>\r\n
 * 		I/OK\r\n
 *
 * @return	'0' ok; '1' error
 */
uint8_t WaspWIFI_PRO::parseResponse4()
{
	char* pointer;
	int i = 0;
	char delimiters[10];

	// delimiter chars are: " ,"
	strcpy_P( delimiters, (char*)pgm_read_word(&(table_WIFI_FORMAT[23])));

	// find first "\r\n"
	pointer = strstr((char*) _buffer, EOL_CR_LF);
	if (pointer == NULL) return 1;

	// move to start skipping "\r\n" chars
	pointer++;
	pointer++;

	// At this moment, pointer: <ssid>,<bssid>,<security>,<WPA>,<ch>,<SNR>\r\n
	pointer = strtok( pointer, delimiters);
	while ((pointer != NULL) && (i<6))
	{
		if (i == 0)
		{
			strncpy( _essid, pointer, sizeof(_essid) );
		}
		else if (i == 1)
		{
			strncpy( _bssid, pointer, sizeof(_bssid) );
		}
		else if (i == 4)
		{
			_channel = atoi(pointer);
		}
		else if (i == 5)
		{
			_snr = atoi(pointer);
		}

		pointer = strtok (NULL, delimiters);
		i++;
	}

	return 0;

}


/*
 * name: parseResponse
 * @brief	When this function is called, the answer to be parsed must be in
 * 			'_buffer'. Then the pattern "nnn)" is found and parsed.
 * @param 	uint16_t* number: pointer to number to parse in "nnn)"
 * @return	'0' ok; '1' error
 */
uint8_t WaspWIFI_PRO::parseResponse5( int* number )
{
	int result;
	char format[10];

	// "%d)"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[25])));

	// parse "nnn)" contents in _buffer
	result = sscanf( (char*)_buffer, format, number );

	if (result == 0)
	{
		*number = 0;
		return 1;
	}

	return 0;
}


/// PUBLIC METHODS /////////////////////////////////////////////////////////////


/*!
 * @brief	It powers on the module and checks communication via UART
 * @param 	socket: SOCKET0 or SOCKET1
 * @return 	'0' ok; '1' error
 *
 */
uint8_t	WaspWIFI_PRO::ON( uint8_t socket )
{
	uint8_t status;
	int retries;
	int total_attempts = 2;

	// store the UART to be used
	_uart = socket;
	_baudrate = 115200;
	_def_delay = 50;

	while (total_attempts > 0)
	{

		// select multiplexer
		if (_uart == SOCKET0)
		{
			Utils.setMuxSocket0();
		}
		else if (_uart == SOCKET1)
		{
			Utils.setMuxSocket1();
		}
		else
		{
			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("wrong socket selection\n"));
			#endif
			return 1;
		}

		// open mcu uart
		beginUART();

		// power up depending on the chosen SOCKET
		PWR.powerSocket(_uart, HIGH);

		// wait power-up time
		delay(500);

		// flush uart
		serialFlush(_uart);

		// try several attempts to communicate with the module
		retries = 5;
		do
		{
			// send AT+i, wait for I/OK
			status = sendCommand(AT, I_OK, 1000);

			if (status == 1)
			{
				return 0;
			}
			else
			{
				#if DEBUG_WIFI_PRO > 1
					PRINT_WIFI_PRO(F("no answer received\n"));
				#endif
			}
			retries--;
			delay(100);
		}
		while (retries > 0);

		/// if problems ==> switch off -> switch on -> and try again
		OFF(socket);
		delay(1000);

		// decrement
		total_attempts--;
	}

	return 1;
}



/*
 *
 * name: OFF
 * @param socket: socket where the module is plugged
 * @return void
 */
void WaspWIFI_PRO::OFF( uint8_t socket )
{
	// close UART0
	closeUART();

	// unselect multiplexer
    if (_uart == SOCKET0)	Utils.setMuxUSB();
    if (_uart == SOCKET1)	Utils.muxOFF1();

	// switch module OFF
	PWR.powerSocket(_uart, LOW);

	delay(100);
}






/*
 * name: resetValues
 * @param void
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::resetValues()
{
	char cmd_name[20];

	// "FD"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[1])));

	// generate "AT+iFD\r"
	GEN_ATCOMMAND1(cmd_name);

	// send command
	uint8_t status = sendCommand( _command, I_OK, 500 );

	if (status == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



/*!
 *
 * @param 	char* ssid: string defines the ESSID
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::setESSID( char* ssid )
{
	char cmd_name[20];

	// "WLSI"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[2])));

	// generate "AT+iWLSI=<ssid>\r"
	GEN_ATCOMMAND1(cmd_name, ssid);

	// if a password was set, setting ESSID can take a while
	// it is recommended to wait for 20secs
	uint8_t status = sendCommand( _command, I_OK, 20000 );

	if (status == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}




/*
 * name: setESSID
 * @param uint8_t n: index for the new ESSID profile
 * @param char* ssid: name of the AP
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::setESSID(uint8_t n, char* ssid)
{
	char cmd_name[20];
	char gen_cmd_name[20];
	char format[20];

	// "WSI"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[48])));

	// "%s%01u"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[16])));

	snprintf(gen_cmd_name, sizeof(gen_cmd_name), format, cmd_name, n);

	// generate "AT+iWSIn=<ssid>\r"
	GEN_ATCOMMAND1(gen_cmd_name, ssid);

	// if a password was set, setting ESSID can take a while
	// it is recommended to wait for 20secs
	uint8_t status = sendCommand( _command, I_OK, 20000 );

	if (status == 1)
	{
		return 0;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*
 * name: getESSID
 *
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::getESSID()
{
	char cmd_name[20];
	char format[20];
	int result = 0;

	// "WLSI"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[2])));

	// "AT+iWLSI?\r\n%s\r\n"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[30])));

	// generate "AT+iWLSI?\r"
	GEN_ATQUERY(cmd_name);

	// send command
	uint8_t status = sendCommand(_command, AT_OK, AT_ERROR, 500);

	if (status == 1)
	{
		result = sscanf( (char*)_buffer, format, _essid);

		if (result != 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}

	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*!
 * @param 	uint8_t securityMode: type of encryption
 * 		@arg	OPEN
 * 		@arg	WEP64
 * 		@arg	WEP128
 * 		@arg	WPA
 * 		@arg	WPA2
 * @param 	char* pass: string for the password
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::setPassword(uint8_t securityMode)
{
	return setPassword(0, securityMode, "");
}


/*!
 * @param 	uint8_t securityMode: type of encryption
 * 		@arg	OPEN
 * 		@arg	WEP64
 * 		@arg	WEP128
 * 		@arg	WPA
 * 		@arg	WPA2
 * @param 	char* pass: string for the password
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::setPassword( uint8_t securityMode, char* pass)
{
	return setPassword(0, securityMode, pass);
}



/*!
 * @param 	uint8_t n: index of profile (from 0 to 9)
 * @param 	uint8_t securityMode: type of encryption
 * 		@arg	OPEN
 * 		@arg	WEP64
 * 		@arg	WEP128
 * 		@arg	WPA
 * 		@arg	WPA2
 * @param 	char* pass: string for the password
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::setPassword(uint8_t n, uint8_t securityMode, char* pass)
{
	uint8_t status;
	char cmd_name[20];
	char gen_cmd_name[20];
	char param1[20];
	char format[20];


	/// 1. Set Security mode: WPA, WPA2...

	// "WST"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[4])));
	// "%s%01u"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[16])));

	// create complete command name: "WSTn"
	snprintf(gen_cmd_name, sizeof(gen_cmd_name), format, cmd_name, n);

	// convert to string
	utoa( securityMode, param1, 10 );

	// generate "AT+iWSTn=<securityMode>\r"
	GEN_ATCOMMAND1(gen_cmd_name, param1);

	// send command
	status = sendCommand( _command, I_OK, 300 );

	if (status != 1)
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}


	/// 2. Set password key
	switch( securityMode )
	{
		case OPEN:
					// No extra settings needed
					break;

		case WEP64:
		case WEP128:
					// "WKY"
					strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[5])));
					// generate command name "WKYn"
					snprintf(gen_cmd_name, sizeof(gen_cmd_name), format, cmd_name, n);
					// generate "AT+iWKYn=<pass>\r"
					GEN_ATCOMMAND1(gen_cmd_name, pass);
					break;

		case WPA:
		case WPA2:
					// "WPP"
					strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[6])));
					// generate command name "WPPn"
					snprintf(gen_cmd_name, sizeof(gen_cmd_name), format, cmd_name, n);
					// generate "AT+iWPPn=<pass>\r"
					GEN_ATCOMMAND1(gen_cmd_name, pass);
					break;
		default:
				return 1;
	}


	// Setting password can take a while
	// it is recommended to wait for 20secs
	status = sendCommand( _command, I_OK, 20000 );

	if (status == 1)
	{
		return 0;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*!
 * @brief	It sets the working mode of the WiFi module:
 * 		@arg	MODE_STATION (0)
 * 		@arg	MODE_ACCESS_POINT (1)
 * @return	'0' if ok, '1' if error
 *
 */
uint8_t WaspWIFI_PRO::setWorkingMode(uint8_t n)
{
	char cmd_name[20];
	char gen_cmd_name[20];
	char format[20];
	char param1[20];

	// convert to string
	utoa( n, param1, 10 );

	// "STAP"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[61])));

	// generate "AT+iSTAP=<n>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	uint8_t status = sendCommand( _command, I_OK, 1000 );

	if (status == 1)
	{
		return 0;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*!
 * @brief	Sets number of addresses to be allocated in the IP pool of iChip’s
 * 			DHCP server
 * @param	uint8_t range: number of IP addresses in pool (1 to 255).
 * 			Default: 0 DHCP server is inactive
 * @return	'0' if ok, '1' if error
 *
 */
uint8_t WaspWIFI_PRO::setServerPoolSize(uint8_t range)
{
	char cmd_name[20];
	char gen_cmd_name[20];
	char format[20];
	char param1[20];

	// convert to string
	utoa( range, param1, 10 );

	// "DPSZ"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[61])));

	// generate "AT+iDPSZ=<range>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	uint8_t status = sendCommand( _command, I_OK, 1000 );

	if (status == 1)
	{
		return 0;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*
 * name: softReset
 * @param
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::softReset()
{
	uint8_t status;
	char cmd_name[20];

	// "DOWN"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[3])));

	// gen "AT+iDOWN\r"
	GEN_ATCOMMAND1(cmd_name);

	// send command
	status = sendCommand( _command, I_OK, I_ONLINE, I_ERROR, 5000 );

	if (status == 0)
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
	else if (status == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("softReset I/OK\n"));
		#endif
	}
	else if (status == 2)
	{
		return 0;
	}
	else if (status == 3)
	{
		// check error code
		getErrorCode();
		return 0;
	}

	// wait for correct following response: I/ONLINE or I/ERROR (056)
	status = waitFor( I_ONLINE, I_ERROR, 5000 );

	if (status == 1)
	{
		// I/ONLINE
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("softReset I/ONLINE\n"));
		#endif
		return 0;
	}
	else if (status == 2)
	{
		// get error code
		uint16_t error = getErrorCode();
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("softReset I/ERROR:"));
			USB.println(error, DEC);
		#endif
	}
	else
	{
		// timeout
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("softReset timeout\n"));
		#endif
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

	return 1;
}




/*
 * name: reportStatus
 * @param
 * @return
 * 		0: Wireless LAN adapter not present
 * 		1: Wireless LAN adapter disabled
 * 		2: Searching for initial connection
 * 		4: Connected
 * 		5: Out of range
 * 		6: timeout
 * 		7: I/OK before connection report
 * 		8: error
 *
 */
uint8_t WaspWIFI_PRO::reportStatus()
{
	uint8_t status;
	char cmd_name[20];
	char pattern[30];
	char format_ok[20];

	// "RP10"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[0])));
	// ")\r\n"
	strcpy_P( format_ok, (char*)pgm_read_word(&(table_WIFI_FORMAT[6])));
	// "AT+iRP10\r\nI/(%u,%u,%u,%u)"
	strcpy_P( pattern, (char*)pgm_read_word(&(table_WIFI_FORMAT[7])));

	// gen "AT+iRP10\r"
	GEN_ATCOMMAND1(cmd_name);

	// send command
	status = sendCommand( _command, format_ok, I_OK, I_ERROR, 300 );

	if (status == 0)
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 6;
	}
	else if (status == 1)
	{
		// define a string buffer to copy the answer
		char aux[100]={};

		// check correct length to be copied
		uint16_t size = _length;
		if (size >= sizeof(aux))
		{
			size = sizeof(aux)-1;
		}

		// copy mem block
		memcpy( aux, _buffer, size);

		// get all fields from answer
		uint16_t port;

		sscanf( aux, pattern, &port, &_rate, &_level, &_quality );

		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("reportStatus:"));
			USB.println( _buffer, _length );
			PRINT_WIFI_PRO(F("port:"));
			USB.println( port, DEC );
			PRINT_WIFI_PRO(F("_rate:"));
			USB.println( _rate, DEC );
			PRINT_WIFI_PRO(F("_level:"));
			USB.println( _level, DEC );
			PRINT_WIFI_PRO(F("_quality:"));
			USB.println( _quality, DEC );
		#endif
		return port;
	}
	else if (status == 2)
	{
		return 7;
	}
	else
	{
		return 8;
	}
}



/*!
 * @brief	Gets a report of the current WLAN connection
 * @return	0: ok; 1: error
 *
 */
uint8_t WaspWIFI_PRO::reportStatusComplete()
{
	uint8_t status;
	uint8_t error;
	char cmd_name[20];
	char empty[30];

	// "!RP10"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[47])));
	// "AT+i!rp10\r\nI/OK"
	strcpy_P( empty, (char*)pgm_read_word(&(table_WIFI_FORMAT[15])));

	// gen "AT+i!RP10\r"
	GEN_ATCOMMAND1(cmd_name);

	// send command
	status = sendCommand( _command, I_OK_EOL, empty, I_ERROR, 500 );

	if (status == 1)
	{
		error = parseResponse4();

		if (error != 0)
		{
			return 1;
		}
		return 0;
	}
	else if (status == 2)
	{
		return 1;
	}
	else if (status == 3)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/*
 * name: isConnected
 *
 * @return
 * 		true: connected
 * 		false: NOT connected
 *
 */
bool WaspWIFI_PRO::isConnected()
{
	const uint32_t TOTAL_TIMEOUT = 30000;
	const uint32_t PERIOD_TIMEOUT = 5000;
	return isConnected(TOTAL_TIMEOUT, PERIOD_TIMEOUT);
}


/*
 * name: isConnectedMultiple
 *
 * @return
 * 		true: connected
 * 		false: NOT connected
 *
 */
bool WaspWIFI_PRO::isConnectedMultiple()
{
	const uint32_t TOTAL_TIMEOUT = 180000;
	const uint32_t PERIOD_TIMEOUT = 90000;
	return isConnected(TOTAL_TIMEOUT, PERIOD_TIMEOUT);
}


/*
 * name: isConnected
 * @param uint32_t total_time: time to wait until function answers error
 * @param uint32_t period_time: time to wait until a SW reset id done to restart
 * @return
 * 		true: connected
 * 		false: NOT connected
 *
 */
bool WaspWIFI_PRO::isConnected(uint32_t total_time, uint32_t period_time)
{
	const uint32_t TOTAL_TIMEOUT = total_time;
	const uint32_t PERIOD_TIMEOUT = period_time;
	uint32_t total_start = millis();
	uint32_t period_start;
	uint8_t error;
	uint8_t status;
	bool step1Done = false;

	while (millis()-total_start < TOTAL_TIMEOUT)
	{
		/// 1. Check report status for correct association
		period_start = millis();

    	if (step1Done == false)
		{
			while (millis()-period_start < PERIOD_TIMEOUT)
			{
				// get status
				status = reportStatus();

				if (status == 4)
				{
					// WiFi connected
					// Now go to step 2 (wait for IP address)
					step1Done = true;
					break;
				}
				else
				{
					// Not correct status
					#if DEBUG_WIFI_PRO > 1
						PRINT_WIFI_PRO(F("reportStatus:"));
						USB.println(status,DEC);
					#endif
				}
				// wait for new status request
				delay(500);

				// Condition to avoid an overflow (DO NOT REMOVE)
				if (millis() < period_start) period_start = millis();
			}
		}


		/// 2. Wait for getting IP for full functionality
		period_start = millis();

		if (step1Done == true)
		{
			while (millis()-period_start < PERIOD_TIMEOUT)
			{
				error = getIP();

				if (error == 0)
				{
					return true;
				}
				else
				{
					delay(500);
				}

				// Condition to avoid an overflow (DO NOT REMOVE)
				if (millis() < period_start) period_start = millis();
			}
		}


		/// 3. After PERIOD_TIMEOUT: soft reset and start again

		// update flag to start again
		step1Done = false;

		// to re-start connection request again
		error = softReset();

		if (error == 0)
		{
			// WiFi softReset OK
		}
		else
		{
			// WiFi softReset ERROR
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < total_start) total_start = millis();
	}

	return false;
}




/*
 * name: ping
 * Sends a two-byte ICMP PING request packet to the remote host defined by host.
 * @param 	char* host: Logical name of the target host or a host IP address.
 * 			The host name may be any legal Internet server name, which can be
 * 			resolved by the iChip’s DNS (Domain Name Server) settings. The host
 * 			name may also be specified as an absolute IP address given in DOT form.


 * @return
 *
 */
uint8_t WaspWIFI_PRO::ping( char* host )
{
	char cmd_name[20];
	uint8_t error = 0;

	// "PING"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[7])));

	// generate "AT+iPING:<host>\r"
	GEN_ATCOMMAND2(cmd_name, host);

	// send command
	uint8_t status = sendCommand( _command, AT_OK2, AT_ERROR, 10000);

	if (status == 1)
	{
		getResponse();
		error = parseResponse( &_rtt );
		if (error == 0)
		{
			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("rtt(ms)="));
				USB.println( _rtt, DEC );
			#endif
		}
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*
 * name: setIP
 * Permanently sets iChip’s default IP address to IP address. The address will
 * be stored in the DIP parameter. The DIP parameter’s value is copied into the
 * IPA parameter after power-up and after the AT+iDOWN command.
 * By default, this parameter is empty (0.0.0.0): No static IP address defined.
 * IP address will be resolved through a DHCP server, if one is available (LAN)
 * or PPP (Modem).
 *
 * @param char* ip: ip address to set
 * @remarks "255.255.255.255" is reserved
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setIP(char* ip)
{
	char cmd_name[20];

	// "DIP"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[35])));

	// generate "AT+iDIP=<ip>\r"
	GEN_ATCOMMAND1(cmd_name, ip);

	// send command
	uint8_t status = sendCommand( _command, I_OK, I_ERROR, 5000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/*
 * name: getIP
 * Report the current IP address
 *
 * @return
 *
 */
uint8_t WaspWIFI_PRO::getIP()
{
	char cmd_name[20];
	char format[20];
	char no_ip[20];
	int result = 0;

	// "IPA"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[8])));

	// "AT+iIPA?\r\n%s\r\n"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[8])));
	// "0.0.0.0"
	strcpy_P( no_ip, (char*)pgm_read_word(&(table_WIFI_FORMAT[9])));

	// generate "AT+iIPA?\r"
	GEN_ATQUERY(cmd_name);

	// send command
	uint8_t status = sendCommand( _command, AT_OK, AT_ERROR, 500 );

	if (status == 1)
	{
		result = sscanf( (char*)_buffer, format, _ip );

		if (result != 0)
		{
			if (strstr((char*)_buffer, no_ip) != NULL)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 1;
		}

	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*
 * name: setDNS
 * @brief Sets the Domain Name Server IP Address.
 * Use n=1 to define the Primary IP address of the Domain Name Server associated
 * with the ISP.
 * Use n=2 to define the alternate IP address.
 * IP::=<nnn>.<nnn>.<nnn>.<nnn> where, <nnn>: [000..255]
 *
 * @param uint8_t n: primary(1) or secondary(2) DNS server
 * @param char* ip: ip address to set
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setDNS(char* ip)
{
	return setDNS(1,ip);
}

/*
 * name: setDNS
 * @brief Sets the Domain Name Server IP Address.
 * Use n=1 to define the Primary IP address of the Domain Name Server associated
 * with the ISP.
 * Use n=2 to define the alternate IP address.
 * IP::=<nnn>.<nnn>.<nnn>.<nnn> where, <nnn>: [000..255]
 *
 * @param uint8_t n: primary(1) or secondary(2) DNS server
 * @param char* ip: ip address to set
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setDNS(uint8_t n, char* ip)
{
	char cmd_name[20];
	uint8_t status;

	if (n == 1)
	{
		// "DNS1"
		strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[36])));
	}
	else if (n == 2)
	{
		// "DNS2"
		strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[37])));
	}
	else
	{
		return 1;
	}

	// generate "AT+iDNSn=<ip>\r"
	GEN_ATCOMMAND1(cmd_name, ip);

	// send command
	status = sendCommand( _command, I_OK, I_ERROR, 1000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}

/*
 * name: getDNS
 * Report the current DNS address
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::getDNS(uint8_t n)
{
	char cmd_name[20];
	char format[20];
	char no_ip[20];
	int result = 0;
	char* dns_pointer;

	if (n == 1)
	{
		// "DNS1"
		strcpy_P(cmd_name, (char*)pgm_read_word(&(table_WiReach[36])));
		// "AT+iDNS1?\r\n%s\r\n"
		strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[28])));
		// set dns1 as pointer
		dns_pointer = _dns1;
	}
	else if (n == 2)
	{
		// "DNS2"
		strcpy_P(cmd_name, (char*)pgm_read_word(&(table_WiReach[37])));
		// "AT+iDNS2?\r\n%s\r\n"
		strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[29])));
		// set dns2 as pointer
		dns_pointer = _dns2;
	}
	else
	{
		return 1;
	}

	// "0.0.0.0"
	strcpy_P(no_ip, (char*)pgm_read_word(&(table_WIFI_FORMAT[9])));

	// generate "AT+iDNS<n>?\r"
	GEN_ATQUERY(cmd_name);

	// send command
	uint8_t status = sendCommand(_command, AT_OK, AT_ERROR, 500);

	if (status == 1)
	{
		result = sscanf( (char*)_buffer, format, dns_pointer);

		if (result != 0)
		{
			if (strstr((char*)_buffer, no_ip) != NULL)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 1;
		}

	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}


/*
 * name: setGateway
 * @brief Permanently sets the IP address of the gateway to be used by iChip.
 *
 * @param char* ip: ip address to set
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setGateway(char* ip)
{
	char cmd_name[20];
	uint8_t status;

	// "IPG"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[38])));

	// generate "AT+iIPG=<ip>\r"
	GEN_ATCOMMAND1(cmd_name, ip);

	// send command
	status = sendCommand( _command, I_OK, I_ERROR, 1000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/*
 * name: getGateway
 * @brief Get the current gateway IP
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::getGateway()
{
	char cmd_name[20];
	char format[20];
	char no_ip[20];
	int result = 0;

	// "IPG"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[38])));

	// "AT+iIPG?\r\n%s\r\n"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[26])));
	// "0.0.0.0"
	strcpy_P( no_ip, (char*)pgm_read_word(&(table_WIFI_FORMAT[9])));

	// generate "AT+iIPG?\r"
	GEN_ATQUERY(cmd_name);

	// send command
	uint8_t status = sendCommand(_command, AT_OK, AT_ERROR, 500);

	if (status == 1)
	{
		result = sscanf( (char*)_buffer, format, _gw );

		if (result != 0)
		{
			if (strstr((char*)_buffer, no_ip) != NULL)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 1;
		}

	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*
 * name: setNetmask
 * @brief Sets the Sub Net to IP mask.
 *
 * @param char* ip: ip address to set
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setNetmask(char* ip)
{
	char cmd_name[20];
	uint8_t status;

	// "SNET"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[39])));

	// generate "AT+iSNET=<ip>\r"
	GEN_ATCOMMAND1(cmd_name, ip);

	// send command
	status = sendCommand( _command, I_OK, I_ERROR, 1000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}


/*
 * name: getNetmask
 * @brief Gets the current subnet mask
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::getNetmask()
{
	char cmd_name[20];
	char format[20];
	char no_ip[20];
	int result = 0;

	// "SNET"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[39])));

	// "AT+iSNET?\r\n%s\r\n"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[27])));
	// "0.0.0.0"
	strcpy_P( no_ip, (char*)pgm_read_word(&(table_WIFI_FORMAT[9])));

	// generate "AT+iSNET?\r"
	GEN_ATQUERY(cmd_name);

	// send command
	uint8_t status = sendCommand(_command, AT_OK, AT_ERROR, 500);

	if (status == 1)
	{
		result = sscanf((char*)_buffer, format, _netmask);

		if (result != 0)
		{
			if (strstr((char*)_buffer, no_ip) != NULL)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 1;
		}

	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/*
 * name: getURL
 * Report the current IP address
 *
 * @return
 *
 * AT+iRLNK:"http://pruebas.libelium.com:80/getpost_frame_parser.php?counter=1"
 *
 */
uint8_t WaspWIFI_PRO::getURL(char* protocol,
							char* host,
							char* port,
							char* link )
{
	// define buffer for url: Maximum 256 chars
	char url[257];
	char cmd_name[20];
	char format[20];
	uint8_t status;

	// clear buffer
	memset( url, 0x00, sizeof(url) );

	// init variable
	_errorCode = ERROR_CODE_0000;

	// "\"%s://%s:%s/%s\""
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[10])));

	int n = snprintf( url, sizeof(url), format, protocol, host, port, link );

	if ((n>0) && (n<(int)sizeof(url)))
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("URL:"));
			USB.println( url );
			PRINT_WIFI_PRO(F("URL length:"));
			USB.println( strlen(url), DEC);
		#endif
	}
	else
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("[getURL] url too large. n:"));
			USB.println( n, DEC);
		#endif
		_errorCode = ERROR_CODE_0031;
		return 1;
	}

	// "RLNK"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[9])));

	// generate "AT+iRLNK:<url>\r"
	GEN_ATCOMMAND1(cmd_name, url);

	// send command
	status = sendCommand( _command, I_OK_EOL, AT_ERROR, 5000 );

	if (status == 1)
	{
		// The module must answer: "I/<sz>\r\n<binary data stream>I/ONLINE"
		// Check this type of answer
		status = getResponseValue();

		if (status == 0)
		{
			// if error was captured return with code
			if (_errorCode != ERROR_CODE_0000)
			{
				return 1;
			}

			status =  waitFor( AT_ONLINE, 15000);
			_errorCode = ERROR_CODE_0000;
			return 1;
		}
		else
		{
			status = waitFor( AT_ONLINE, 15000);

			if (status == 1)
			{
				_length -= strlen(AT_ONLINE);
				_buffer[_length] = '\0';
				return 0;
			}
			else
			{
				_errorCode = ERROR_CODE_0000;
				return 1;
			}
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}



/*
 * name: setURL
 * Sets the URL address string used for downloading web pages and files and
 * uploading files to web servers.
 *
 * @return
 *
 * Example command:
 * 	AT+iURL=“<Protocol>://<host>[:<port>]/[<absolute_link>]”
 *
 */
uint8_t WaspWIFI_PRO::setURL(char* protocol,
							char* host,
							char* port,
							char* link )
{
	char url[512];
	char url_template[50];
	char cmd_name[20];
	uint8_t status;

	// clear buffer
	memset( url, 0x00, sizeof(url) );
	memset( url_template, 0x00, sizeof(url_template) );

	// "\"%s://%s:%s/%s\""
	strcpy_P( url_template, (char*)pgm_read_word(&(table_WiReach[11])));

	// Create "<prot>://<host>:<port>/<link>"
	snprintf( url, sizeof(url), url_template, protocol, host, port, link );

	// "URL"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[13])));

	// generate "AT+iURL=<url>\r"
	GEN_ATCOMMAND1(cmd_name, url);

	// send command
	status = sendCommand( _command, I_OK, AT_ERROR, 5000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}



/*
 * name: post
 * Submits a plain text POST request to a web server defined in the URL param
 *
 * @remarks 	The url address must be set with the setURL() function
 * @remarks 	The “Content-type:” field of the POST request is defined by the
 * 				CTT parameter.
 * @return
 *
 * <text> must be  <ASCII text line><CRLF> ...<CRLF>.<CRLF>
 *
 */
uint8_t WaspWIFI_PRO::post( char* text )
{
	char cmd_name[20];
	uint8_t status;
	uint16_t size;
	char ending[20];

	// "\r\n.\r\n"
	strcpy_P( ending, (char*)pgm_read_word(&(table_WIFI_FORMAT[24])));

	// claculate buffer size
	size = strlen(text)+ strlen(ending) + 1;

	char aux[size];

	// clear buffer
	memset( aux, 0x00, sizeof(aux) );

	// init variable
	_errorCode = ERROR_CODE_0000;


	// copy text and add ending
	strncat( aux, text, strlen(text) );
	strncat( aux, ending, strlen(ending) );

	// "SLNK"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[12])));

	// generate "AT+iSLNK:<text>\r\n.\r\n"
	GEN_ATCOMMAND2(cmd_name, aux);

	// send command
	status = sendCommand( _command, I_OK_EOL, AT_ERROR, 5000 );

	if (status == 1)
	{
		// The module must answer: "I/<sz>\r\n"
		// Check this type of answer
		status = getResponseValue();

		if (status == 0)
		{
			// if error was captured return with code
			if (_errorCode != ERROR_CODE_0000)
			{
				return 1;
			}

			// wait the module to be ready again
			status =  waitFor( AT_ONLINE, 15000 );
			_errorCode = ERROR_CODE_0000;
			return 1;
		}
		else
		{
			// wait the module to be ready again
			status = waitFor( AT_ONLINE, 15000);

			if (status == 1)
			{
				_length -= strlen(AT_ONLINE);
				_buffer[_length] = '\0';
				return 0;
			}
			else
			{
				_errorCode = ERROR_CODE_0000;
				return 1;
			}
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}




/**
 * @brief 	Defines the contents of the “Content-type:” field that is sent in
 * 			the POST request by the AT+iSLNK command. This field specifies the
 * 			type of file being sent
 *
 * @param 	char* str: type of file being sent by the AT+iSLNK command
 * @return
 * 			'0' if ok
 * 			'1' if error
 */
uint8_t WaspWIFI_PRO::setContentType(char* str)
{
	char cmd_name[20];

	// "CTT"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[53])));

	// generate "AT+iCTT=<string>\r"
	GEN_ATCOMMAND1(cmd_name, str);

	// send command
	uint8_t status = sendCommand( _command, I_OK, I_ERROR, 5000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/**
 * @brief  Send HTTTP request with Frame contents from Waspmote to Meshlium
 *
 * @param	char* protocol: "http" or "https"
 * @param	char* host: Web Server Name (IP address or DNS server name)
 * @param	char* port: Port number on server. Default: 80 (http), 443 (https)
 * @param	uint8_t* data: pointer to be used with frame.buffer
 * @param	uint16_t length: length of buffer to be used with frame.length
 *
 * @return 	'0' if ok; '1' if error
 *
 */
uint8_t WaspWIFI_PRO::sendFrameToMeshlium(	char* protocol,
											char* host,
											char* port,
											uint8_t* data,
											uint16_t length )
{
	char cmd_name[20];
	char host_header[150];
	uint8_t status;
	uint16_t size = 0;

	// "\"%s://%s:%s/getpost_frame_parser.php?frame="
	// "<protocol>://<host>:<port>/getpost_frame_parser.php?frame="
	sprintf_P( host_header, (char*)pgm_read_word(&(table_WiReach[10])), protocol, host, port);

	// calculate total size of buffer
	size = strlen(host_header)
			+ length*2
			+ 1;

	// define buffers
	char url[size];
	char aux[3];

	// clear buffer
	memset( url, 0x00, sizeof(url) );
	memset( aux, 0x00, sizeof(aux) );

	// init variable
	_errorCode = ERROR_CODE_0000;

	// compose "<prot>://<host>:<port>/getpost_frame_parser.php?frame="
	strncat( url, host_header, strlen(host_header));

	// make conversion and concatenate to url
	for (uint16_t i=0 ; i<length; i++)
	{
		Utils.hex2str( &data[i], aux, 1);
		strncat( url, aux, 2 );
	}
	// add ending character to string
	strncat( url, "\"", 1 );

	// check maximum length for url
	if (strlen(url) > 256)
	{
		PRINT_WIFI_PRO(F("Error. Max URL size is 256. Current length: "));
		USB.println( strlen(url), DEC);
		PRINT_WIFI_PRO(F("Current URL: "));
		USB.println(url);
		_errorCode = ERROR_CODE_0042;
		return 1;
	}


	// "RLNK"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[9])));

	// generate "AT+iRLNK:<url>\r"
	GEN_ATCOMMAND1(cmd_name, url);

	// send command
	status = sendCommand( _command, I_OK_EOL, AT_ERROR, 5000);

	if (status == 1)
	{
		// The module must answer: "I/<sz>\r\n"
		// Check this type of answer
		status = getResponseValue();

		if (status == 0)
		{
			// if error was captured return with code
			if (_errorCode != ERROR_CODE_0000)
			{
				return 1;
			}

			// error
			// wait for online message from module
			status =  waitFor( AT_ONLINE, 15000);

			_errorCode = ERROR_CODE_0000;
			return 1;
		}
		else
		{
			// wait for online message from module
			status = waitFor( AT_ONLINE, 15000);
			return 0;
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}






/*!
 * @brief Opens an FTP link to an FTP server
 *
 * @param char* server: Logical name of the FTP or the server’s IP address
 * @param char* port: 	Optional FTP port in the range 0..65535 (def:21)
 * @param char* user: 	FTP user’s name
 * @param char* pass: 	FTP user’s password
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpOpenSession(char* server,
									char* port,
									char* user,
									char* pass)
{
	char cmd_name[20];
	uint8_t status;

	// "FOPN"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[14])));

	// generate "AT+iFOPN:<server>,<port>:<user>,<pass>\r"
	GEN_ATCOMMAND2(cmd_name, server, port, user, pass);

	// change second comma ',' to ':'
	char* pointer;
	pointer = strchr( _command, ',');
	if (pointer == NULL) return 1;
	pointer = strchr( pointer+1, ',');
	if (pointer == NULL) return 1;
	*pointer = ':';

	uint32_t previous = millis();
	// send command
	status = sendCommand(_command, I_SLASH, AT_ERROR, 15000);

	if (status == 1)
	{
		// The module must answer: "<sz>\r\n"
		// Check this type of answer
		status = getResponseValue2();

		if (status == 0)
		{
			_errorCode = ERROR_CODE_0000;
			return 1;
		}
		else
		{
			// update FTP handler
			_ftp_handle = (uint16_t)_value;
			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("FTP handle: "));
				USB.println( _ftp_handle, DEC );
				PRINT_WIFI_PRO(F("_buffer:"));
				USB.println( _buffer, _length );
			#endif
			return 0;
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("FTP openSession ERROR\n"));
		#endif
		return 1;
	}
	else
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("FTP openSession TIMEOUT\n"));
		#endif
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}





/*!
 * @brief Opens a secure FTP link to a secure FTP server
 *
 * @param char* server: Logical name of the FTP or the server’s IP address
 * @param char* port: 	Optional FTP port in the range 0..65535 (def:21)
 * @param char* user: 	FTP user’s name
 * @param char* pass: 	FTP user’s password
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpSecureOpenSession(char* server,
											char* port,
											char* user,
											char* pass)
{
	char cmd_name[20];
	uint8_t status;

	// "FOPS"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[60])));

	// generate "AT+iFOPS:<server>,<port>:<user>,<pass>\r"
	GEN_ATCOMMAND2(cmd_name, server, port, user, pass );

	// change second comma ',' to ':'
	char* pointer;
	pointer = strchr( _command, ',');
	if (pointer == NULL) return 1;
	pointer = strchr( pointer+1, ',');
	if (pointer == NULL) return 1;
	*pointer = ':';

	uint32_t previous = millis();
	// send command
	status = sendCommand(_command, I_SLASH, AT_ERROR, 30000);

	if (status == 1)
	{
		// The module must answer: "<sz>\r\n"
		// Check this type of answer
		status = getResponseValue2();

		if (status == 0)
		{
			_errorCode = ERROR_CODE_0000;
			return 1;
		}
		else
		{
			// update FTP handler
			_ftp_handle = (uint16_t)_value;
			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("FTP handle: "));
				USB.println( _ftp_handle, DEC );
				PRINT_WIFI_PRO(F("_buffer:"));
				USB.println( _buffer, _length );
			#endif
			return 0;
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("FTP openSession ERROR\n"));
		#endif
		return 1;
	}
	else
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("FTP openSession TIMEOUT\n"));
		#endif
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}







/*!
 * @brief Reports an FTP file size
 *
 * @param char* path: File pathname in server
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpFileSize( uint16_t handle, char* path )
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;

	// init attribute
	_filesize = 0;

	// convert to string
	utoa( handle, param1, 10 );

	// "FSZ"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[15])));

	// generate "AT+iFSZ:<F_hn>,<path>\r"
	GEN_ATCOMMAND2(cmd_name, param1, path );

	// send command
	status = sendCommand( _command, I_SLASH, AT_ERROR, 15000 );

	if (status == 1)
	{
		// The module must answer: "<sz>\r\n"
		// Check this type of answer
		status = getResponseValue2();

		if (status == 0)
		{
			_errorCode = 1;
			return 1;
		}
		else
		{
			_filesize = _value;

			// wait for online message from module
			status = waitFor( I_OK_EOL, 5000);
			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("FTP file size: "));
				USB.println( _filesize, DEC );
			#endif
			return 0;
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}








/*!
 * @brief	Downloads a file from an FTP server
 *
 * @param 	char* server_path: File pathname inside FTP server
 * @param 	char* sd_path: File pathname in SD card
 *
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpDownload( uint16_t handle, char* server_path, char* sd_path )
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;
	uint8_t error;
	uint32_t server_filesize = 0;
	uint32_t sd_filesize = 0;
	uint16_t nBytes;
	unsigned long previous;

	/// Prepare SD card for downloading

	// define file variable
	SdFile file;

	// get current state of SD card power supply
	bool sd_active = SPI.isSD;

	// switch SD card ON
	SD.ON();

	// go to Root directory
	SD.goRoot();

	// check if the card is there or not
	if (!SD.isSD())
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("SD not present\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		_errorCode = ERROR_CODE_0010;
		return 1;
	}

	// Delete file in the case it exists
	if (SD.isFile(sd_path) == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("delete file\n"));
		#endif
		SD.del(sd_path);
	}

	// Creates a file in that folder
	if (!SD.create(sd_path))
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("file not created\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		_errorCode = ERROR_CODE_0011;
		return 1;
	}

	// search file in current directory and open it in write mode
	if (!SD.openFile(sd_path, &file, O_READ | O_WRITE | O_SYNC))
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("error opening file\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		_errorCode = ERROR_CODE_0012;
		return 1;
	}

	// jump over zero 'offset'
	if (!file.seekSet(0))
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("setting file offset\n"));
		#endif
		file.close();
		if (sd_active == false)
		{
			SD.OFF();
		}
		_errorCode = ERROR_CODE_0013;
		return 1;
	}

	/// Change Baudrate to 9600 bps
	error = changeBaudRate(9600);

	if (error == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("Error changing baudrate\n"));
		#endif
		return 1;
	}

	/// Get filesize (for backup)
	error = ftpFileSize(handle, server_path);
	if (error == 0)
	{
		server_filesize = _filesize;
	}
	else
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("Error retrieving file size\n"));
		#endif
		return 1;
	}


	/// STEP1. Send command to retrieve file, wait for ok and size of data stream

	// convert to string
	utoa(handle, param1, 10);

	// "FRCV"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[16])));

	// generate "AT+iFRCV:<F_hn>,<path>\r"
	GEN_ATCOMMAND2(cmd_name, param1, server_path);

	status = sendCommand(_command, I_OK_EOL, AT_ERROR, 15000);

	if (status == 1)
	{
		// The module must answer: "I/<sz>\r\n"
		// Check this type of answer
		status = getResponseValue();

		if (status == 0)
		{
			// check if there was error: "FTP data socket could not be opened"
			// in this case it is possible to retry again after a few seconds
			if (_errorCode == ERROR_CODE_0511)
			{
				#if DEBUG_WIFI_PRO > 0
					PRINT_WIFI_PRO(F("There was error 511 --> retry\n"));
				#endif
				delay(1000);

				status = sendCommand( _command, I_OK_EOL, AT_ERROR, 15000);

				if (status == 1)
				{
					// The module must answer: "I/<sz>\r\n"
					// Check this type of answer
					status = getResponseValue();
				}
			}

			if (status == 0)
			{
				/// Change Baudrate to 115200 bps
				changeBaudRate(115200);
				#if DEBUG_WIFI_PRO > 0
					PRINT_WIFI_PRO(F("No file size value from server\n"));
				#endif
				return 1;
			}
		}

		// proceed
		if ((_value == 0) && (server_filesize > 0))
		{
			_value = server_filesize;
		}
		else if ((_value > 0) && (server_filesize > 0))
		{
			/* go down to step2 and proceed with the
			* reading of the file and writing info
			* to SD card */
		}
		else
		{
			/// Change Baudrate to 115200 bps
			changeBaudRate(115200);

			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("unknown file size\n"));
			#endif
			return 1;
		}

	}
	else if (status == 2)
	{
		getErrorCode();
		// Change Baudrate to 115200 bps
		changeBaudRate(115200);

		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("I/ERROR\n"));
		#endif
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		// Change Baudrate to 115200 bps
		changeBaudRate(115200);

		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("timeout\n"));
		#endif
		return 1;
	}

	/// STEP2. read incoming data and save it in Waspmote SD card

	server_filesize = _value;

	// get actual instant
	previous = millis();

	// write incoming data to file
    while (server_filesize > 0)
    {

		// check if buffer is full, means data lost almost 100% sure
		if (serialAvailable(_uart) >= (_bufferSize-1))
		{
			// abort tx
			userAbort();
			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("Error: rx buffer full while download\n"));
			#endif
			_errorCode = ERROR_CODE_0020;
			return 1;
		}

		// read "_buffer"-size data block
		if (server_filesize > _bufferSize)
		{
			nBytes = readBuffer((int)(_bufferSize/2));
		}
		else
		{
			nBytes = readBuffer(server_filesize);
		}

		// decrement number of read bytes
		server_filesize -= nBytes;

		// write data to file if there is something to be written
		if (nBytes > 0)
		{
			if (file.write(_buffer, nBytes) != (int)nBytes)
			{
				// abort tx
				userAbort();

				#if DEBUG_WIFI_PRO > 0
					PRINT_WIFI_PRO(F("Writing SD error\n"));
				#endif
				file.close();

				if (sd_active == false)
				{
					SD.OFF();
				}

				_errorCode = ERROR_CODE_0014;
				return 1;
			}

			// update time counter
			previous = millis();
		}

		// check time since last reading
		if ((millis() - previous) > 10000)
		{
			// abort tx
			userAbort();

			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("No incoming data timeout\n"));
			#endif
			return 1;
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < previous) previous = millis();
	}

	// Close file
	file.close();

	// wait for online message from module
	status = waitFor( AT_ONLINE, 10000 );

	// wait for I/ONLINE message
	if (status == 0)
	{
		_errorCode = 1;
		// Change Baudrate to 115200 bps
		changeBaudRate(115200);
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No I/ONLINE message\n"));
		#endif
		return 1;
	}

	// update file size in SD card
	sd_filesize = SD.getFileSize(sd_path);

	// save the actual server file size
	server_filesize = _value;

	// check size mismatch
	if (sd_filesize != server_filesize)
	{
		// Change Baudrate to 115200 bps
		changeBaudRate(115200);
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("File size mismatch\n"));
			PRINT_WIFI_PRO(F("sd_filesize:"));
			USB.println(sd_filesize);
			PRINT_WIFI_PRO(F("server_filesize:"));
			USB.println(server_filesize);
		#endif
		return 1;
	}

	#if DEBUG_WIFI_PRO > 1
		PRINT_WIFI_PRO(F("DOWNLOAD OK\n"));
		PRINT_WIFI_PRO(F("sd_filesize:"));
		USB.println(sd_filesize,DEC);
		PRINT_WIFI_PRO(F("server_filesize:"));
		USB.println(server_filesize,DEC);
	#endif

	// set SD card off
	if (sd_active == false)
	{
		SD.OFF();
	}

	/// Change Baudrate to 115200 bps
	error = changeBaudRate(115200);

	if (error == 1)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error changing baudrate"));
		#endif
		return 1;
	}

	return 0;


}



/*!
 * @brief	Creates a new directory on the FTP server’s file system
 *
 * @param	char* path: Directory pathname
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpMakeDir(uint16_t handle, char* path)
{
	char cmd_name[20];
	char param1[20];

	// convert to string
	utoa( handle, param1, 10);

	// "FMKD"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[54])));

	// generate "AT+iFMKD:<handle>,<path>\r"
	GEN_ATCOMMAND2( cmd_name, param1, path );

	// send command
	uint8_t status = sendCommand( _command, AT_OK, AT_ERROR, 15000 );

	if (status == 1)
	{
		// ok
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}





/*!
 * @brief	Changes the current FTP working directory
 *
 * @param	uint16_t handle: An open FTP session handle
 * @param	char* path: New directory pathname
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpChangeCWD(uint16_t handle, char* path)
{
	char cmd_name[20];
	char param1[20];

	// convert to string
	utoa( handle, param1, 10);

	// "FMKD"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[55])));

	// generate "AT+iFMKD:<handle>,<path>\r"
	GEN_ATCOMMAND2( cmd_name, param1, path );

	// send command
	uint8_t status = sendCommand(_command, AT_OK, AT_ERROR, 10000);

	if (status == 1)
	{
		// ok
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}





/*!
 * @brief	Returns a full FTP directory listing via USB port
 *
 * @param	uint16_t handle: An open FTP session handle
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpListing(uint16_t handle)
{
	return ftpListing(handle, NULL);
}


/*!
 * @brief	Returns a full FTP directory listing via USB port
 *
 * @param	uint16_t handle: An open FTP session handle
 * @param	char* path: directory pathname to list
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpListing(uint16_t handle, char* path)
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;
	uint8_t error;
	uint32_t previous;
	int nBytes;


	/// Prepare SD card

	// define file variable
	SdFile file;

	// get current state of SD card power supply
	bool sd_active = SPI.isSD;

	// switch SD card ON
	SD.ON();

	// go to Root directory
	SD.goRoot();

	// check if the card is there or not
	if (!SD.isSD())
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: SD not present\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		_errorCode = ERROR_CODE_0010;
		return 1;
	}

	// Delete file in the case it exists
	if (SD.isFile(WIFI_PRO_LISTFILE) == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("delete file\n"));
		#endif
		SD.del(WIFI_PRO_LISTFILE);
	}

	// Creates a file in that folder
	if (!SD.create(WIFI_PRO_LISTFILE))
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: SD file not created\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		_errorCode = ERROR_CODE_0011;
		return 1;
	}

	// search file in current directory and open it in write mode
	if (!SD.openFile(WIFI_PRO_LISTFILE, &file, O_READ | O_WRITE | O_SYNC))
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: opening file\n"));
		#endif

		if (sd_active == false)
		{
			SD.OFF();
		}
		_errorCode = ERROR_CODE_0012;
		return 1;
	}

	// jump over zero 'offset'
	if (!file.seekSet(0))
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: setting file offset\n"));
		#endif
		file.close();

		if (sd_active == false)
		{
			SD.OFF();
		}
		_errorCode = ERROR_CODE_0013;
		return 1;
	}


	/// Change Baudrate to 9600 bps:
	error = changeBaudRate(9600);

	if (error != 0)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("error baudrate1\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}


	/// Scan and store info:

	// convert to string
	utoa(handle, param1, 10);

	// "FDL"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[56])));

	if (path == NULL)
	{
		// gen "AT+iFDL:<handle>\r"
		GEN_ATCOMMAND2(cmd_name, param1);
	}
	else
	{
		// gen "AT+iFDL:<handle>,<path>\r"
		GEN_ATCOMMAND2(cmd_name, param1, path);
	}

	// clear uart buffer before sending command
	if (_flush_mode == true)
	{
		serialFlush(_uart);
	}

	// send command manually
	printString( _command, _uart);

	status = waitFor( I_OK_EOL, 5000 );

	if (status != 1)
	{
		if (sd_active == false)
		{
			SD.OFF();
		}

		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No I_OK_EOL timeout\n"));
		#endif

		_errorCode = ERROR_CODE_0000;
		return 1;
	}

	delay(500);

	// update time counter
	previous = millis();

	nBytes = serialAvailable(_uart);

	while (nBytes > 0)
	{
		nBytes = readBuffer(_bufferSize);

		// write data to file if there is something to be written
		if (nBytes > 0)
		{
			if (file.write( _buffer, nBytes) != nBytes)
			{
				// abort
				userAbort();

				#if DEBUG_WIFI_PRO > 0
					PRINT_WIFI_PRO(F("Writing SD error\n"));
				#endif
				file.close();

				if (sd_active == false)
				{
					SD.OFF();
				}

				_errorCode = ERROR_CODE_0014;
				return 1;
			}
		}

		// check elapsed time
		if ((millis() - previous) > 10000)
		{
			// abort
			userAbort();

			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("No incoming data timeout\n"));
			#endif

			if (sd_active == false)
			{
				SD.OFF();
			}
			_errorCode = ERROR_CODE_0000;
			return 1;
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < previous) previous = millis();
	}

	// Close file
	file.close();

	delay(1000);

	/// Change Baudrate to 115200 bps
	error = changeBaudRate(115200);

	if (error != 0)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("error baudrate2\n"));
		#endif
	}

	if (sd_active == false)
	{
		SD.OFF();
	}

	return 0;
}





/*!
 * @brief	Closes the FTP link
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpCloseSession(uint16_t handle)
{
	char cmd_name[20];
	char param1[20];

	// convert to string
	utoa( handle, param1, 10 );

	// "FCLS"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[17])));

	// generate "AT+iFCLS:<handler>\r"
	GEN_ATCOMMAND2( cmd_name, param1 );

	// send command
	uint8_t status = sendCommand( _command, AT_OK, AT_ERROR, 5000 );

	if (status == 1)
	{
		// wait for online message from module
		status = waitFor( AT_ONLINE, 10000 );
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		return 1;
	}
}




/*
 * name: changeBaudRate
 * Change the baudrate of the module by entering into autodetection mode
 *
 * @param uint32_t rate: baudrate to set
 * @return
 * 		'0' if ok
 * 		'1' see errors
 *
 */
uint8_t WaspWIFI_PRO::changeBaudRate(uint32_t rate)
{
	char cmd_name[20];
	uint8_t status;

	/// STEP1: check actual comm

	status = sendCommand( AT, I_OK, 3000 );

	if (status == 1)
	{
		//do nothing
	}
	else if (status == 2)
	{
		getErrorCode();
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("[changeBaudRate] I/ERROR\n"));
		#endif
		return 1;
	}
	else
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("[changeBaudRate] step1 no answer\n"));
		#endif
		return 1;
	}

	/// STEP2: enter in auto baudrate mode

	// "BDRA"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[18])));

	// generate "AT+iBDRA\r"
	GEN_ATCOMMAND1( cmd_name );

	// send command
	status = sendCommand( _command, I_OK, 3000 );

	if (status != 1)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("[changeBaudRate] no answer1\n"));
		#endif
		return 1;
	}

	/// STEP3: check new baudrate settings

	// close UART
	closeSerial(_uart);
	delay(1000);

	// update attribute
	_baudrate = rate;

	// open UART
	beginSerial( _baudrate, _uart );
	delay(1000);
	serialFlush(_uart);

	// check new baudrate
	status = sendCommand( AT, I_OK, 3000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("[changeBaudRate] I/ERROR\n"));
		#endif
		_baudrate = 115200;
		beginSerial( _baudrate, _uart );
		return 1;
	}
	else
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("[changeBaudRate] no answer2\n"));
		#endif
		_baudrate = 115200;
		beginSerial( _baudrate, _uart );
		return 1;
	}
}








/*!
 * name: uploadFTP
 * Upload a file from SD card to an FTP server
 *
 * @param 	char* server_path: FTP server file path name
 * 			If the file is in the root directory: "FILE1.TXT" or "/FILE1.TXT"
 * 			If the file is inside a folder: "/FOLDER1/FILE1.TXT"
 * @param 	char* sd_path: SD card file path name
 * 			If the file is in the root directory: "FILE2.TXT" or "/FILE2.TXT"
 * 			If the file is inside a folder: "/FOLDER2/FILE2.TXT"
 *
 * @return '0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::ftpUpload( uint16_t handle, char* server_path, char* sd_path )
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;
	uint8_t error;
	uint32_t sd_filesize;

	/// Prepare SD card for downloading

	// define file variable
	SdFile file;

	// get current state of SD card power supply
	bool sd_active = SPI.isSD;

	// switch SD card ON
	SD.ON();

	// go to Root directory
	SD.goRoot();

	// check if the card is there or not
	if (!SD.isSD())
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: SD not present\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}

	// Delete file in the case it exists
	if (!SD.isFile(sd_path))
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: file does not exist\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}

	// search file in current working directory and open it
	// exit if error and modify the general flag with FILE_OPEN_ERROR
	if(!SD.openFile((char*)sd_path, &file, O_RDONLY))
	{
		// SD error
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: opening file\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}

	// set pointer to the beginning of the file
	if(!file.seekSet(0))
	{
		// SD error
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: setting initial offset in file\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}


	/// STEP1. Send command to open a new file in server

	// convert to string
	utoa( handle, param1, 10 );

	// "FSTO"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[19])));

	// generate "AT+iFSTO:<F_hn>,<path>\r"
	GEN_ATCOMMAND2(cmd_name, param1, server_path );

	status = sendCommand( _command, I_OK, AT_ERROR, 15000 );

	if (status == 1)
	{
		/* go down to step2 and proceed with the
		 * reading of the SD file and sending info
		 * to the server */
	}
	else if (status == 2)
	{
		getErrorCode();

		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("I/ERROR\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;

		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No answer timeout1\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}


	/// STEP2. send data from Waspmote to FTP server

	sd_filesize = SD.getFileSize(sd_path);
	uint32_t aux = sd_filesize;
	char cmd[100];
	char format[20];
	int nBytes = 0;
	uint8_t flowByte = 0;
	bool flowControlEnabled=false;

	// get actual instant
	unsigned long previous = millis();

	// "FSND"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[21])));
	// "%s%s:%s,%lu:"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[11])));

	// Create "AT+iFSND:<F_hn>,<sd_filesize>:"
	snprintf( cmd, sizeof(cmd), format, AT_I, cmd_name, param1, sd_filesize );

	// send command
	sendCommand( (uint8_t*) cmd, strlen(cmd));
	serialFlush(_uart);

	// send data via WiFi
    while (sd_filesize > 0)
    {
		// read "_buffer"-size data block
		if(sd_filesize>_bufferSize)
		{
			nBytes = file.read( _buffer, _bufferSize );
		}
		else
		{
			nBytes = file.read( _buffer, sd_filesize );
		}

		// decrement number of read bytes
		if (nBytes != -1)
		{
			sd_filesize -= nBytes;
			previous = millis();
		}

		// write data to file if there is something to be written
		if (nBytes > 0)
		{
			for (int i = 0; i < nBytes; i++)
			{
				// check Flow Control from iChip
				while ((serialAvailable(_uart)>0) || flowControlEnabled)
				{
					if (serialAvailable(_uart) > 0)
					{
						flowByte = serialRead(_uart);
					}

					//check meaning
					if (flowByte == 0x16)
					{
						flowControlEnabled = true;
						#if DEBUG_WIFI_PRO > 0
							PRINT_WIFI_PRO(F("Flow Control enabled. Wait...\n"));
						#endif
					}
					else if (flowByte == 0x18)
					{
						flowControlEnabled = false;
						#if DEBUG_WIFI_PRO > 0
							PRINT_WIFI_PRO(F("Flow Control disabled. Continue!!\n"));
						#endif
					}
					else if (flowByte == 0x05)
					{
						// wait for message from module
						status = waitFor( I_ERROR, 10000 );

						// wait for I/OK message
						if (status == 1)
						{
							getErrorCode();
						}
						#if DEBUG_WIFI_PRO > 0
						PRINT_WIFI_PRO(F("Flow Control ERROR. Stop.\n"));
						#endif
						if (sd_active == false)
						{
							SD.OFF();
						}
						return 1;
					}

					// check time since last reading
					if ((millis() - previous) > 10000)
					{
						#if DEBUG_WIFI_PRO > 0
							PRINT_WIFI_PRO(F("No data timeout\n"));
						#endif
						if (sd_active == false)
						{
							SD.OFF();
						}
						return 1;
					}

					// Condition to avoid an overflow (DO NOT REMOVE)
					if (millis() < previous) previous = millis();
				}

				// if no Flow Control is active then
				// print the byte into the UART
				printByte( _buffer[i], _uart);
			}
		}

		// check time since last reading
		if ((millis() - previous) > 10000)
		{
			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("No data timeout\n"));
			#endif
			if (sd_active == false)
			{
				SD.OFF();
			}
			return 1;
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < previous) previous = millis();
	}

	// Close file
	file.close();

	// wait for online message from module
	status = waitFor( I_OK, 10000 );

	// wait for I/OK message
	if (status == 0)
	{
		_errorCode = 1;

		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No I/OK found\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}


	/// STEP3. close FTP file

	// "FCLF"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[22])));

	// generate "AT+iFCLF:<F_hn>\r"
	GEN_ATCOMMAND2(cmd_name, param1 );

	status = sendCommand( _command, I_OK, AT_ERROR, 15000 );

	if (status == 1)
	{
		/* go down */
	}
	else if (status == 2)
	{
		getErrorCode();

		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("I/ERROR\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;

		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No answer timeout2\n"));
		#endif
		if (sd_active == false)
		{
			SD.OFF();
		}
		return 1;
	}

	// set SD card off
	if (sd_active == false)
	{
		SD.OFF();
	}


	/// STEP4. check both file sizes (SD and server)
	sd_filesize = aux;
	error = ftpFileSize(handle, server_path);

	if (error == 1)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error getting server filesize\n"));
		#endif
		return 1;
	}

	if (sd_filesize != _filesize)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("SD/Server files size mismatch\n"));
		#endif
		return 1;
	}

	#if DEBUG_WIFI_PRO > 1
		PRINT_WIFI_PRO(F("UPLOAD OK\n"));
	#endif

	return 0;


}







/*
 * name: setTCPclient
 * Opens a Transmission Control Protocol (TCP) client socket and attempts to
 * connect it to the specified <port> on a server defined by <host>
 *
 * @param char* host: Logical name of the target server or a host IP address
 * @param char* remote_port: 0..65535, target port
 * @remarks Module uses the port range [1025 to 2048] when assigning default local ports
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setTCPclient(	char* host, char* remote_port )
{
	return setTCPclient(host, remote_port, NULL);
}




/*
 * name: setTCPclient
 * Opens a Transmission Control Protocol (TCP) client socket and attempts to
 * connect it to the specified <port> on a server defined by <host>
 *
 * @param char* host: Logical name of the target server or a host IP address
 * @param char* remote_port: 0..65535, target port
 * @param char* local_port: Optional local port on iChip
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setTCPclient(	char* host,
									char* remote_port,
									char* local_port )
{
	char cmd_name[20];
	uint8_t status;

	// "STCP"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[23])));

	// generate "AT+iSTCP:<host>,<port>[,<lport>]\r"
	if (local_port == NULL)
	{
		GEN_ATCOMMAND2(cmd_name, host, remote_port);
	}
	else
	{
		GEN_ATCOMMAND2(cmd_name, host, remote_port, local_port);
	}

	// send command
	status = sendCommand( _command, (char*)"I/0", AT_ERROR, 15000 );

	if (status == 1)
	{
		// The module must answer: "<sock handle>\r\n"
		// Check this type of answer
		status = getResponseValue2();

		if (status == 0)
		{
			_errorCode = 1;
			return 1;
		}
		else
		{
			_socket_handle = _value;

			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("TCP socket open\n"));
			#endif
			return 0;
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;

		// manage socket abort
		socketAbort();
		return 1;
	}

}





/*
 * name: setTCPserver
 * Opens a TCP listening socket on the local IP address and the specified port
 * <port>. The <backlog> parameter specifies the maximum number of remote
 * concurrent connections allowed through the listening socket (from 1 to 10).
 *
 * @param char* local_port: Local port on iChip
 * @param uint8_t backlog: 	Specifies the maximum number of active connections that
 * 							may be concurrently established via the listening socket
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setTCPserver(	char* local_port,
									uint8_t backlog)
{
	char cmd_name[20];
	uint8_t status;
	char param1[20];
	uint8_t backlog_value = backlog;

	// check backlog number
	if ((backlog_value > 10) || (backlog_value == 0))
	{
		backlog_value = 10;
	}

	// convert to string
	utoa( (uint16_t) backlog, param1, 10 );

	// init attributes
	_backlog = 0;
	for (int i = 0; i < 10; i++)
	{
		socket[i].status = -1;
	}

	// "LTCP"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[25])));

	// generate "AT+iLTCP:<local_port>,<backlog>\r"
	GEN_ATCOMMAND2(cmd_name, local_port, param1);

	// send command
	status = sendCommand( _command, (char*)"I/0", AT_ERROR, 10000 );

	if (status == 1)
	{
		// The module must answer: "<sock handle>\r\n"
		// Check this type of answer
		status = getResponseValue2();

		if (status == 0)
		{
			_errorCode = 1;
			return 1;
		}
		else
		{
			_socket_handle = _value;
			_backlog = _value;
			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("TCP server open. backlog="));
				USB.println(_backlog,DEC);
			#endif
			return 0;
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;

		// manage socket abort
		socketAbort();
		return 1;
	}
}





/*
 * name: getAllSocketStatus
 * Retrieves handles of active socket connections established through the
 * listening socket identified by <hn>.
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::getAllSocketStatus()
{
	char cmd_name[20];
	uint8_t status;
	char param1[20];

	// convert to string
	utoa(_backlog, param1, 10 );


	/// 1. Get all Listening Socket’s Active Connection Status

	// "LSST"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[26])));

	// generate "AT+iLSST:<hn>\r"
	GEN_ATCOMMAND2(cmd_name, param1);

	// send command
	status = sendCommand( _command, AT_OK2, AT_ERROR, 1000 );

	if (status == 1)
	{
		// The module must answer: "<hn1>,<hn2>,...,<hnbacklog>)"
		// Check this type of answer
		status = getResponseValue3();

		if (status == 0)
		{
			_errorCode = 1;
			return 1;
		}
		else
		{
			_socket_handle = _value;

			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("TCP list ok\n"));
			#endif
			/*
			 * 	go down to step 2
			 */
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}


	/// 2. Get Peer Name for All Specified Sockets

	// "GPNM"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[31])));

	for (int i = 0; i < _backlog; i++)
	{
		if (socket[i].status==0)
		{
			// convert to string
			utoa( socket[i].handle, param1, 10 );

			// generate "AT+iGPNM:<hn>\r"
			GEN_ATCOMMAND2(cmd_name, param1);

			// send command
			status = sendCommand(_command, AT_OK2, AT_ERROR, 1000);

			if (status == 1)
			{
				// The module must answer: "<xxx.xxx.xxx.xxx>:<port>)"
				// Check this type of answer
				status = getResponseValue4(i);

				if (status == 0)
				{
					_errorCode = 1;
					return 1;
				}
				else
				{
					continue;
				}
			}
			else if (status == 2)
			{
				getErrorCode();
				return 1;
			}
			else
			{
				// timeout error
				_errorCode = ERROR_CODE_0000;
				return 1;
			}
		}
	}



	/// 3. report status of the sockets and parse info
	status = reportStatus4();

	// check response
	if (status != 0)
	{
		return 1;
	}

	return 0;
}





/*
 * name: getSocketStatus
 * Retrieves handles of active socket connections established through the
 * listening socket identified by <hn>.
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::getSocketStatus(uint16_t handle)
{
	char cmd_name[20];
	uint8_t status;
	uint8_t error;
	char param1[20];
	int sockstat;

	// convert to string
	utoa(handle, param1, 10 );

	// "SCS"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[28])));

	// generate "AT+iSCS:<hn>\r"
	GEN_ATCOMMAND2(cmd_name, param1);

	// send command expecting "I/("
	status = sendCommand( _command, AT_OK2, AT_ERROR, 1000 );

	if (status == 1)
	{
		getResponse();
		error = parseResponse5( &sockstat );
		if (error == 0)
		{
			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("Socket Status="));
				USB.println( sockstat, DEC );
			#endif
		}

		if (sockstat >= 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		return 1;
	}
}






/*
 * name: setUDP
 * @brief	Opens a UDP (User Datagram Protocol) socket and sets the remote
 * 			system’s <host>:<port> address
 * @param 	char* host: Logical name of the target server or a host IP address
 * @param 	char* remote_port: 0..65535, target port
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setUDP( char* host, char* remote_port )
{
	return setUDP(host, remote_port, NULL);
}




/*
 * name: setUDP
 * @brief	Opens a Transmission Control Protocol (TCP) client socket and
 * 			attempts to connect it to the specified <port> on a server defined
 * 			by <host>
 * @param 	char* host: Logical name of the target server or a host IP address
 * @param 	char* remote_port: 0..65535, target port
 * @param 	char* local_port: Optional local port on iChip
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setUDP(	char* host,
								char* remote_port,
								char* local_port )
{
	char cmd_name[20];
	uint8_t status;

	// "SUDP"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[24])));

	// generate "AT+iSUDP:<host>,<port>[,<lport>]\r"
	if (local_port == NULL)
	{
		GEN_ATCOMMAND2(cmd_name, host, remote_port);
	}
	else
	{
		GEN_ATCOMMAND2(cmd_name, host, remote_port, local_port);
	}

	// send command
	status = sendCommand( _command, (char*)"I/0", AT_ERROR, 15000);

	if (status == 1)
	{
		// The module must answer: "<sock handle>\r\n"
		// Check this type of answer
		status = getResponseValue2();

		if (status == 0)
		{
			_errorCode = 1;
			return 1;
		}
		else
		{
			_socket_handle = _value;

			#if DEBUG_WIFI_PRO > 1
				PRINT_WIFI_PRO(F("UDP socket open\n"));
			#endif
			return 0;
		}
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;

		// manage socket abort
		socketAbort();
		return 1;
	}

}



/*
 * name: send
 * Sends a byte stream to the socket specified by the socket handle
 *
 * @param char* data: data to send
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::send(uint16_t handle, char* data)
{
	return send(handle, (uint8_t*) data, strlen(data));
}


/*
 * name: send
 * Sends a byte stream to the socket specified by the socket handle
 *
 * @param uint8_t* data: pointer to buffer of data to send
 * @param uint16_t length: length of the buffer to send
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::send(uint16_t handle, uint8_t* data, uint16_t length)
{
	char cmd_name[20];
	char param1[20];
	char param2[20];
	uint8_t status;
	
	// convert to string
	utoa(handle, param1, 10 );
	utoa(length, param2, 10 );

	// "SSND%"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[29])));

	// generate "AT+iSSND%:<hn>,<sz>\r"
	GEN_ATCOMMAND2(cmd_name, param1, param2);

	// the final command: "AT+iSSND%:<hn>,<sz>:<stream>"
	_command[strlen(_command)-1] = ':';
	setDelay(0);
	// send command
	sendCommand((uint8_t*)_command, strlen(_command));
	sendCommand(data,length);
	setDelay(100);
	// wait for responses
	status = waitFor( I_OK, AT_ERROR, 15000);

	// check response
	if (status == 1)
	{
		// ok
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}




/*
 * name: receive
 * Receive a byte stream from default stored socket handle
 *
 * @param uint32_t timeout: time to wait for data
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::receive(uint16_t handle)
{
	return receive(handle, 1000);
}


/*
 * name: send
 * Sends a byte stream to the socket specified by the socket handle
 *
 * @param uint32_t timeout: time to wait for data
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::receive(uint16_t handle, uint32_t timeout)
{
	char cmd_name[20];
	char format_empty[20];
	char param1[20];
	uint8_t error;
	uint8_t status;
	uint16_t length;
	uint32_t previous;

	// convert to string
	utoa( handle, param1, 10 );

	// "SRCV"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[30])));

	// "I/0\r\n"
	strcpy_P( format_empty, (char*)pgm_read_word(&(table_WIFI_FORMAT[18])));

	// generate "AT+iSRCV:<hn>\r"
	GEN_ATCOMMAND2(cmd_name, param1);

	// get previous time instant
	previous = millis();

	while (millis()-previous < timeout)
	{
		// send command and wait for first "\r\n" occurrence
		status = sendCommand( _command, EOL_CR_LF, 1000 );

		if (status == 0)
		{
			return 1;
		}

		// wait for EOL
		status = waitFor( format_empty, (char*)":", AT_ERROR, 1000 );

		if (status == 1)
		{
			// no data received yet. Wait 500ms and continue to ask for more
			continue;
		}
		else if (status == 2)
		{
			// data received "I/xxx:"--> parse data
			error = parseResponse2(&length);
			if (error == 0)
			{
				readBuffer(length);
			}
			return 0;
		}
		else if (status == 3)
		{
			//getErrorCode();
			// no data received yet. Wait 500ms and continue to ask for more
			delay(100);
			//Insert dependencies on type of error??
			continue;
		}
		else
		{
			// timeout error
			_errorCode = ERROR_CODE_0000;
			return 1;
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < previous) previous = millis();
	}

	return 1;

}





/*
 * name: closeSocket
 * Opens a Transmission Control Protocol (TCP) client socket and attempts to
 * connect it to the specified <port> on a server defined by <host>.
 * The attribute '_socket_handle' is used as socket handler
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::closeSocket()
{
	return 	closeSocket(_socket_handle);
}



/*
 * name: closeSocket
 * Opens a Transmission Control Protocol (TCP) client socket and attempts to
 * connect it to the specified <port> on a server defined by <host>
 *
 * @param uint16_t* handle: handler of the socket to be closed
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::closeSocket(uint16_t handle)
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;

	// convert to string
	utoa( handle, param1, 10 );

	// "SCLS"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[34])));

	// generate "AT+iSCLS:<hn>\r"
	GEN_ATCOMMAND2(cmd_name, param1);

	// send command
	status = sendCommand( _command, I_OK, AT_ERROR, 15000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*
 * name: closeDownSockets
 * Close all down status sockets
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::closeDownSockets()
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;

	// "SCLS"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[34])));

	for (int i = 0; i < _backlog; i++)
	{
		// check if socket is down and then close it
		if (socket[i].size==-203)
		{
			// convert to string
			utoa( socket[i].handle, param1, 10 );

			// generate "AT+iSCLS:<hn>\r"
			GEN_ATCOMMAND2(cmd_name, param1);

			// send command
			status = sendCommand( _command, I_ONLINE, AT_ERROR, 10000 );

			if (status == 1)
			{
				#if DEBUG_WIFI_PRO > 1
					PRINT_WIFI_PRO(F("Socket closed with hn:"));
					USB.println(socket[i].handle);
					USB.println(F("--------------------------------"));
				#endif
				continue;
			}
			else if (status == 2)
			{
				getErrorCode();
				//return 1;
			}
			else
			{
				// timeout error
				_errorCode = ERROR_CODE_0000;
				return 1;
			}
		}
	}

	return 0;
}




/*!
 * @brief	Sets the network time server name or IP
 * @param 	char* ip: Logical name of the target server or a host IP address
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setTimeServer(char* ip)
{
	return setTimeServer(1, ip);
}


/*!
 * @brief	Sets the network time server name or IP
 * @param 	uint8_t n: 	'1' to define the primary time server
 * 					 	'2' to define an alternate time server
 * @param 	char* ip: Logical name of the target server or a host IP address
 *
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setTimeServer(uint8_t n, char* ip)
{
	char cmd_name[20];
	uint8_t status;

	if (n == 1)
	{
		// "NTS1"
		strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[40])));
	}
	else if (n == 2)
	{
		// "NTS2"
		strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[41])));
	}
	else
	{
		return 1;
	}


	// generate "AT+iNTSx=<ip>\r"
	GEN_ATCOMMAND1(cmd_name, ip);

	// send command
	status = sendCommand( _command, I_OK, AT_ERROR, 1000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}



/*
 * name: timeActivationFlag
 * Sets the network time-of-day activation flag to 'flag'. If this flag is
 * enabled (1), iChip will retrieve an updated time reading the next time it
 * goes online
 *
 * @param bool flag: '1' is enabled. '0' is disabled
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::timeActivationFlag(bool flag)
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;

	// convert to string
	utoa( flag, param1, 10 );

	// "NTOD"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[42])));

	// generate "AT+iNTOD=<flag>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	status = sendCommand( _command, I_OK, AT_ERROR, 1000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}




/*!
 * @brief	Permanently sets iChip location’s Greenwich mean time offset, in
 * 			hours. Range: from -12 to 12
 * @param 	bool flag: '1' is enabled. '0' is disabled
 *
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setGMT(int8_t gmt)
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;

	// convert to string
	itoa( gmt, param1, 10 );

	// "GMT0"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[43])));

	// generate "AT+iGMT0=<gmt>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	status = sendCommand(_command, I_OK, AT_ERROR, 1000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}



/*
 * name: reportStatus4
 *
 *
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::reportStatus4()
{
	char cmd_name[20];
	uint8_t status;

	// "RP4"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[46])));

	// gen "AT+iRP4\r"
	GEN_ATCOMMAND1(cmd_name);

	// send command
	status = sendCommand( _command, AT_OK2, AT_ERROR, 1000 );

	if (status == 1)
	{
		status = getResponseValue5();

		if (status == 0)
		{
			return 1;
		}
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}




/*
 * name: reportStatus8
 *
 *
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::reportStatus8()
{
	char cmd_name[20];
	uint8_t status;

	// "RP8"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[44])));

	// gen "AT+iRP8\r"
	GEN_ATCOMMAND1(cmd_name);

	// send command
	status = sendCommand( _command, I_OK, AT_ERROR, 1000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}




/*!
 * @brief	Returns a list of all APs available in the surrounding area
 *
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::scan()
{
	char cmd_name[20];
	uint8_t status;
	uint8_t error;
	uint32_t previous;
	int nBytes;

	/// Prepare SD card

	// define file variable
	SdFile file;

	// switch SD card ON
	SD.ON();

	// go to Root directory
	SD.goRoot();

	// check if the card is there or not
	if (!SD.isSD())
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: SD not present"));
		#endif
		SD.OFF();
		_errorCode = ERROR_CODE_0010;
		return 1;
	}

	// Delete file in the case it exists
	if (SD.isFile(WIFI_PRO_SCANFILE) == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("delete file\n"));
		#endif
		SD.del(WIFI_PRO_SCANFILE);
	}

	// Creates a file in that folder
	if (!SD.create(WIFI_PRO_SCANFILE))
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: SD file not created\n"));
		#endif
		SD.OFF();
		_errorCode = ERROR_CODE_0011;
		return 1;
	}

	// search file in current directory and open it in write mode
	if (!SD.openFile(WIFI_PRO_SCANFILE, &file, O_READ | O_WRITE | O_SYNC))
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: opening file\n"));
		#endif
		SD.OFF();
		_errorCode = ERROR_CODE_0012;
		return 1;
	}

	// jump over zero 'offset'
	if (!file.seekSet(0))
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: setting file offset\n"));
		#endif
		file.close();
		SD.OFF();
		_errorCode = ERROR_CODE_0013;
		return 1;
	}


	/// Change Baudrate to 9600 bps:
	error = changeBaudRate(9600);

	if (error != 0)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("error baudrate1\n"));
		#endif
		return 1;
	}


	/// Scan and store info:
	// "RP20"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[49])));

	// gen "AT+iRP20\r"
	GEN_ATCOMMAND1(cmd_name);

	// clear uart buffer before sending command
	if ( _flush_mode == true)
	{
		serialFlush(_uart);
	}
	// send command manually
	printString( _command, _uart );

	// wait for "at+irp20\r\n"
	status = waitFor( cmd_name, 1000 );
	status = waitFor( EOL_CR_LF, 1000 );

	if (status != 1)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No response from module\n"));
		#endif
		return 1;
	}

	// check for incoming data while 3 seconds
	previous = millis();
	while (serialAvailable(_uart) == 0)
	{
		if (millis()-previous > 3000)
		{
			break;
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < previous) previous = millis();
	}

	// update time counter
	previous = millis();

	// clear buffer
	memset( _buffer, 0x00, _bufferSize );
	_length = 0;

	nBytes = serialAvailable(_uart);

	while (nBytes > 0)
	{
		nBytes = readBuffer(_bufferSize);

		// write data to file if there is something to be written
		if (nBytes > 0)
		{
			if (file.write( _buffer, nBytes) != nBytes)
			{
				// abort
				userAbort();

				#if DEBUG_WIFI_PRO > 0
					PRINT_WIFI_PRO(F("Writing SD error\n"));
				#endif
				file.close();
				SD.OFF();

				_errorCode = ERROR_CODE_0014;
				return 1;
			}
		}

		// check elapsed time
		if ((millis() - previous) > 5000)
		{
			// abort
			userAbort();

			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("No incoming data timeout\n"));
			#endif
			return 1;
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if (millis() < previous) previous = millis();
	}

	// Close file
	file.close();

	delay(1000);

	/// Change Baudrate to 115200 bps
	error = changeBaudRate(115200);

	if (error != 0)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error baudrate2\n"));
		#endif
		return 1;
	}

	SD.OFF();

	return 0;

}







/*
 * name: setTimeFromWIFI
 *
 *
 *
 * @return
 * 		'0' if ok
 * 		'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setTimeFromWIFI()
{
	uint8_t error;
	int retries = 10;

	do
	{
		error = reportStatus8();

		if (error == 0)
		{
			// parse timestamp parse
			error = parseResponse3();

			if (error == 0)
			{
				return 0;
			}
		}
		else
		{
			// error
			return 1;
		}

		// decrement retries counter
		retries--;

		// wait
		delay(1000);

	}while (retries > 0);

	return 1;
}





/*
 * name: userAbort
 * While the iChip is in Internet mode attending to Internet communications, it
 * is possible to break into the communications and abort the Internet mode in
 * an orderly manner. This is achieved by sending the iChip a sequence of three
 * (+) ASCII characters (+++) after a half second silence period. In response to
 * this, the iChip:
 * 	- Shuts down Internet communications.
 * 	- Terminates data transmission to the host.
 * 	- Performs a software reset.
 * 	- Responds with an I/ERROR (056) message.
 * 	- Returns to command mode.
 *
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::userAbort()
{
	uint8_t status;
	char cmd_name[20];

	// "+++"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[45])));

	// send command
	status = sendCommand( cmd_name, I_ERROR, 10000 );

	if (status == 0)
	{
		// check error code
		getErrorCode();
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("userAbort OK\n"));
		#endif
		return 0;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

}




/*
 * name: socketAbort
 * While the iChip is in Internet mode, during a TCP or UDP socket operation, it
 * is possible to override iChip’s normal timeout procedure and abort the current
 * socket operation in an orderly manner. This is achieved by sending the iChip
 * a sequence of three ASCII (-) characters (---) following a half second
 * silence period. The socket commands to which this applies are: STCP, SUDP,
 * SSND, and SFSH. When iChip detects the socket abort command, it aborts the
 * last socket command and returns an I/ERROR following the STCP and SUDP
 * commands, or I/OK during an SSND or SFSH command.
 *
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::socketAbort()
{
	uint8_t status;
	char cmd_name[20];

	// "---"
	strcpy_P(cmd_name, (char*)pgm_read_word(&(table_WiReach[63])));

	// send command
	status = sendCommand(cmd_name, I_ERROR, 10000);

	if (status == 0)
	{
		// check error code
		getErrorCode();
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("userAbort OK\n"));
		#endif
		return 0;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/*!
 * @brief	This function enables/disables the Roaming Mode
 * @param 	uint8_t mode: ENABLED or DISABLED
 * @return 	'0' if ok; '1' if error
 */
uint8_t WaspWIFI_PRO::roamingMode(uint8_t mode)
{
	uint8_t status;
	char cmd_name[20];
	char param1[20];

	if ((mode!=ENABLED) && (mode!=DISABLED))
	{
		return 1;
	}

	// convert to string
	utoa( (uint16_t) mode, param1, 10 );

	// "WROM"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[50])));

	// generate "AT+iWROM=<mode>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	status = sendCommand( _command, I_OK, I_ERROR, 1000 );

	if (status == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("roamingMode OK\n"));
		#endif
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/*!
 * @brief	Sets the time interval – n – between consecutive scans that
 * 			iChip performs for APs in its vicinity
 * @param 	uint8_t n: 1-3600 seconds (default: 5 seconds)
 * @return 	'0' if ok; '1' if error
 */
uint8_t WaspWIFI_PRO::setScanInterval(uint8_t n)
{
	uint8_t status;
	char cmd_name[20];
	char param1[20];

	// convert to string
	utoa( (uint16_t) n, param1, 10 );

	// "WPSI"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[59])));

	// generate "AT+iWPSI=<n>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	status = sendCommand( _command, I_OK, I_ERROR, 1000);

	if (status == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("Set Low Threshold OK\n"));
		#endif
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/*!
 * @brief	Sets a low SNR threshold for iChip in Roaming mode. If the SNR value
 * 			of the signal from the AP that iChip is currently associated with
 * 			drops below n, iChip is triggered by the SNR low event
 * @param 	uint8_t n: 0-254 dB (default: 10 dB)
 * @return 	'0' if ok; '1' if error
 */
uint8_t WaspWIFI_PRO::setLowThreshold(uint8_t n)
{
	uint8_t status;
	char cmd_name[20];
	char param1[20];

	// convert to string
	utoa( (uint16_t) n, param1, 10 );

	// "WSRL"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[57])));

	// generate "AT+iWSRL=<n>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	status = sendCommand( _command, I_OK, I_ERROR, 1000);

	if (status == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("Set Low Threshold OK\n"));
		#endif
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/*!
 * @brief	Sets a high SNR threshold for iChip in Roaming mode. iChip will
 * 			re-associate only with APs having SNR that is better than n
 * @param 	uint8_t n: 10-254 dB (default: 30 dB)
 * @return 	'0' if ok; '1' if error
 */
uint8_t WaspWIFI_PRO::setHighThreshold(uint8_t n)
{
	uint8_t status;
	char cmd_name[20];
	char param1[20];

	// convert to string
	utoa( (uint16_t) n, param1, 10 );

	// "WSRH"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[58])));

	// generate "AT+iWSRH=<n>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	status = sendCommand( _command, I_OK, I_ERROR, 1000 );

	if (status == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("Set High Threshold OK\n"));
		#endif
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*!
 * @brief	Sets the transmission power of WLAN chipset. Range: 0-14. Def: 14
 *
 * Command formula:
 * In any case the tranform formula is y = x*2 + 3.
 * at+iwlpw=14 is transformed to 14 * 2 + 3 = 31.
 * So 31 should be transformed (31 - 3)/2 = 14.
 * The value 31 is in 0,5dbm.
 *
 * @remarks After a HW or SW reset, WLPW returns to its default value
 * @param char* host: Logical name of the target server or a host IP address
 * @return '0' if ok; '1' if error
 *
 */
uint8_t WaspWIFI_PRO::setPower(uint8_t power)
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;

	// convert to string
	utoa( (uint16_t) power, param1, 10 );

	// "WLPW"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[51])));

	// generate "AT+iWLPW=<n>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	status = sendCommand( _command, I_OK, AT_ERROR, 1000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}




/*!
 * @brief	Gets the transmission power of WLAN chipset. Range: 0-14. Def: 14
 *
 * Command formula:
 * In any case the tranform formula is y = x*2 + 3.
 * at+iwlpw=14 is transformed to 14 * 2 + 3 = 31.
 * So 31 should be transformed (31 - 3)/2 = 14.
 * The value 31 is in 0,5dbm.
 *
 * @remarks After a HW or SW reset, WLPW returns to its default valuepl
 *
 * @return '0' if ok; '1' if error
 *
 */
uint8_t WaspWIFI_PRO::getPower()
{
	char cmd_name[20];
	uint8_t status;

	// "WLPW"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[51])));

	// generate "AT+iWLPW?\r"
	GEN_ATQUERY(cmd_name);

	// send command
	status = sendCommand(_command, I_OK, AT_ERROR, 1000);

	if (status == 1)
	{
		char delimiters[100];
		strcat(delimiters, _command);
		strcat(delimiters, I_OK);
		strcat(delimiters, EOL_CR_LF);
		if (parseUint8(&_power, delimiters) != 0)
		{
			return 1;
		}

		// make conversion _power = (_power - 3)/2
		_power = (uint8_t)((_power-3)/2);
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}

	return 1;
}





/*!
 * @brief	Sets the certificates of the trusted certificate authorities. iChip
 * 			accepts a server’s identity only if its certificate is signed by one
 * 			of these authorities
 *
 * @param	char* ca: it is referenced as the trusted certificate authority’s
 * 			certificate during SSL3/TLS1 socket connection establishment
 * 			(handshake). iChip establishes an SSL3/TLS1 socket connection only
 * 			to servers having a certificate authenticated by this certificate
 * 			authority. iChip expects cert to be multiple lines separated by
 * 			<CR>, beginning with:-----BEGIN CERTIFICATE----- and terminating
 * 			with: -----END CERTIFICATE-----. cert should include an RSA
 * 			encryption public key of 1024 or 2048 bit. The signature algorithm
 * 			may be MD2, MD5 or SHA1. Maximum size of cert is 1500 characters.
 *
 * @return	'0' if ok; 'x' see errors
 *
 */
uint8_t WaspWIFI_PRO::setCA(char* ca)
{
	char cmd_name[20];
	uint8_t status;
	uint8_t error;

	/// Change Baudrate to 9600 bps:
	error = changeBaudRate(9600);

	if (error != 0)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("error changing baudrate\n"));
		#endif
		return 1;
	}

	// "CA"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[52])));

	serialFlush(_uart);

	// print "AT+iCA=<ca>\r"
	printString("AT+iCA=", _uart);
	printString(ca, _uart);

	/*
	 * Wait for different lines until a good o bad answer is received
	 */
	status = 3;

	while (status == 3)
	{
		status = waitFor(I_OK, AT_ERROR, EOL_CR_LF,100);
	}

	#if DEBUG_WIFI_PRO > 0
	switch (status)
		{
			case 0: PRINT_WIFI_PRO(F("status 0\n")); break;
			case 1: PRINT_WIFI_PRO(F("status 1\n")); break;
			case 2: PRINT_WIFI_PRO(F("status 2\n")); break;
			case 3: PRINT_WIFI_PRO(F("status 3\n")); break;
			default:PRINT_WIFI_PRO(F("default\n")); break;
		}
	USB.println(_buffer, _length);
	#endif


	/// Change Baudrate to 115200 bps
	error = changeBaudRate(115200);

	if (error != 0)
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("error changing baudrate\n"));
		#endif
		return 1;
	}

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error code found\n"));
		#endif
		return 1;
	}
	else
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No answer\n"));
		#endif
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/* requestOTA() - It downloads a new OTA file if OTA is necessary
 *
 * This function downloads a new OTA file if OTA is necessary
 *
 * Returns
 * 	'1' if error (see error code)
*/
uint8_t WaspWIFI_PRO::requestOTA(char* server,
								char* port,
								char* user,
								char* pass)
{
	uint8_t error;
	char* str_pointer;
	char aux_name[8];
	char path[100];
	char aux_str[10];
	long int aux_size;
	uint8_t aux_version;
	int length;
	char format_file[10];
	char format_path[10];
	char format_size[10];
	char format_version[10];
	uint16_t handle;

	// set to zero the buffer 'path'
	memset(path, 0x00, sizeof(path));

	// switch SD card ON
	SD.ON();

	// go to Root directory
	SD.goRoot();

	// check if the card is there or not
	if (!SD.isSD())
	{
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error: SD not present\n"));
		#endif
		SD.OFF();
		_errorCode = ERROR_CODE_0010;
		return 1;
	}

	// Delete file in the case it exists
	if (SD.isFile(OTA_ver_file) == 1)
	{
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("delete file\n"));
		#endif
		SD.del(OTA_ver_file);
	}

	// switch off the SD card
	SD.OFF();

	////////////////////////////////////////////////////////////////////////////
	// 1. Download config file
	////////////////////////////////////////////////////////////////////////////

	#if DEBUG_WIFI_PRO > 1
		PRINT_WIFI_PRO(F("Downloading OTA config file...\n"));
	#endif

    // Open FTP session
    error = ftpOpenSession( server, port, user, pass );

    // check response
    if (error == 0)
    {
		handle = _ftp_handle;
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("Open FTP session OK\n"));
		#endif
    }
    else
    {
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error opening FTP session\n"));
		#endif
		return 1;
    }

	// get OTA_ver_file
	error = ftpDownload(handle, OTA_ver_file, OTA_ver_file);

    // check if file was downloaded correctly
    if (error == 0)
    {
		#if DEBUG_WIFI_PRO > 1
			PRINT_WIFI_PRO(F("OTA_ver_file downloaded OK\n"));
		#endif
	}
    else
    {
		_errorCode = ERROR_CODE_0021;
		ftpCloseSession(handle);
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("ERROR downloading OTA_ver_file\n"));
		#endif
		return 1;
    }


	////////////////////////////////////////////////////////////////////////////
	// 2. Analyze OTA_ver_file
	////////////////////////////////////////////////////////////////////////////

	// "FILE:"
	strcpy_P( format_file, (char*)pgm_read_word(&(table_WIFI_FORMAT[19])));
	// "PATH:"
	strcpy_P( format_path, (char*)pgm_read_word(&(table_WIFI_FORMAT[20])));
	// "SIZE:"
	strcpy_P( format_size, (char*)pgm_read_word(&(table_WIFI_FORMAT[21])));
	// "VERSION:"
	strcpy_P( format_version, (char*)pgm_read_word(&(table_WIFI_FORMAT[22])));


	SD.ON();
	SD.goRoot();

	// clear buffer
	memset(_buffer, 0x00, _bufferSize);

	// Reads the file and copy to '_buffer'
	SD.cat(OTA_ver_file, 0, _bufferSize);
	strcpy((char*)_buffer, SD.buffer );

	/// 1. Search the file name
	str_pointer = strstr((char*) _buffer, format_file);
	if (str_pointer != NULL)
	{
		// Copy the FILE contents:
		// get string length and check it is equal to 7
		length = strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		if (length != 7)
		{
			_errorCode = ERROR_CODE_0022;
			ftpCloseSession(handle);
			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("length:"));
				USB.println(length);
			#endif
			return 1;
		}
		// copy string
		strncpy(aux_name, strchr(str_pointer, ':')+1, 7);
		aux_name[7] = '\0';
	}
	else
	{
		SD.OFF();
		ftpCloseSession(handle);
		_errorCode = ERROR_CODE_0023;
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No FILE label\n"));
		#endif
		return 1;
	}

	/// 2. Check if NO_FILE is the filename
	if (strcmp(aux_name,NO_OTA) == 0)
	{
		ftpCloseSession(handle);
		_errorCode = ERROR_CODE_0024;
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(NO_OTA);
			USB.println(NO_OTA);
		#endif
		return 1;
	}

	/// 3. Search the path
	str_pointer = strstr((char*) _buffer, format_path);
	if (str_pointer != NULL)
	{
		// copy the PATH contents
		length = strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		strncpy(path, strchr(str_pointer, ':') + 1, length );
		path[length] = '\0';

		// delete actual program
		SD.del(aux_name);
	}
	else
	{
		SD.OFF();
		ftpCloseSession(handle);
		_errorCode = ERROR_CODE_0025;
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No PATH label\n"));
		#endif
		return 1;
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
	}
	else
	{
		SD.OFF();
		ftpCloseSession(handle);
		_errorCode = ERROR_CODE_0026;
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No SIZE label\n"));
		#endif
		return 1;
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
	}
	else
	{
		SD.OFF();
		ftpCloseSession(handle);
		_errorCode = ERROR_CODE_0027;
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("No VERSION label\n"));
		#endif
		return 1;
	}

	// print configuration file contents
	USB.println(F("--------------------------------"));
	PRINT_WIFI_PRO(F("FILE:"));
	USB.println(aux_name);
	PRINT_WIFI_PRO(F("PATH:"));
	USB.println(path);
	PRINT_WIFI_PRO(F("SIZE:"));
	USB.println(aux_size);
	PRINT_WIFI_PRO(F("VERSION:"));
	USB.println(aux_version,DEC);
	USB.println(F("--------------------------------"));

	// get actual program version
	uint8_t prog_version = Utils.getProgramVersion();
	// get actual program name (PID)
	char prog_name[8];
	Utils.getProgramID(prog_name);

	// check if version number
	#ifdef CHECK_VERSION
	if (strcmp(prog_name,aux_name) == 0)
	{
		if (prog_version >= aux_version)
		{
			ftpCloseSession(handle);
			_errorCode = ERROR_CODE_0028;

			// if we have specified the same program id and lower/same version
			// number, then do not proceed with OTA
			PRINT_WIFI_PRO(F("Invalid version: current="));
			USB.print(prog_version,DEC);
			USB.print(F("; new="));
			USB.println(aux_version,DEC);
			return 1;
		}
	}
	#endif


	////////////////////////////////////////////////////////////////////////////
	// 3. Download binary file
	////////////////////////////////////////////////////////////////////////////

	// create server file complete path: path + filename
	char server_file[100];
	if (path[strlen(path)-1] == '/')
	{
		snprintf(server_file, sizeof(server_file), "%s%s", path, aux_name);
	}
	else
	{
		snprintf(server_file, sizeof(server_file), "%s/%s", path, aux_name);
	}

	#if DEBUG_WIFI_PRO > 0
		PRINT_WIFI_PRO(F("Downloading OTA FILE\n"));
		PRINT_WIFI_PRO(F("Server file:"));
		USB.println(server_file);
		PRINT_WIFI_PRO(F("SD file:"));
		USB.println(aux_name);
	#endif


	// get binary file
	error = ftpDownload(handle, server_file, aux_name);

	if (error == 0)
	{
		// check if size matches
		SD.ON();
		// get file size
		int32_t sd_file_size = SD.getFileSize(aux_name);
		if (sd_file_size != aux_size)
		{
			SD.OFF();
			ftpCloseSession(handle);
			_errorCode = ERROR_CODE_0029;
			#if DEBUG_WIFI_PRO > 0
				PRINT_WIFI_PRO(F("Size does not match\n"));
				PRINT_WIFI_PRO(F("sd_file_size:"));
				USB.println(sd_file_size);
				PRINT_WIFI_PRO(F("UPGRADE.TXT size field:"));
				USB.println(aux_size);
			#endif
			return 1;
		}
		#if DEBUG_WIFI_PRO > 1
			SD.ls();
		#endif
		ftpCloseSession(handle);
		Utils.loadOTA(aux_name,aux_version);
		return 0;
	}
	else
	{
		SD.OFF();
		ftpCloseSession(handle);
		_errorCode = ERROR_CODE_0030;
		#if DEBUG_WIFI_PRO > 0
			PRINT_WIFI_PRO(F("Error getting binary\n"));
		#endif
		return 1;
	}

	return 1;
}


/*
 * name: getFirmwareVersion
 *
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::getFirmwareVersion()
{
	char cmd_name[20];
	char delimiter[20];
	int result = 0;

	// "RP1"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[64])));

	// "\r\n"
	strcpy_P( delimiter, (char*)pgm_read_word(&(table_WIFI_FORMAT[3])));

	// generate "AT+RP1\r"
	GEN_ATCOMMAND1(cmd_name);

	// send command
	uint8_t status = sendCommand(_command, I_OK, I_ERROR, 500);

	if (status == 1)
	{
		status = parseString(_firmwareVersion, sizeof(_firmwareVersion), delimiter, 2);

		if (status == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}

	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}



/*
 * name: sslHandshake
 * Negotiate the SSL handshake for a given TCP connection by its handle
 *
 * @param uint8_t handle: TCP handle connection
 *
 * @return
 * 		'0' if ok
 * 		'1' see errors
 *
 */
uint8_t WaspWIFI_PRO::sslHandshake(uint8_t handle)
{
	char cmd_name[20];
	char param1[20];
	uint8_t status;

	// convert to string
	utoa( (uint16_t) handle, param1, 10 );

	// "SSL"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[65])));

	// generate "AT+iSSL:<handle>\r"
	GEN_ATCOMMAND1(cmd_name, param1);

	// send command
	status = sendCommand( _command, I_OK, AT_ERROR, 15000 );

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;

		return 1;
	}

}

/*
 * name: getMAC
 *
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_PRO::getMAC()
{
	char cmd_name[20];
	char format[20];
	int result = 0;

	// "MACA"
	strcpy_P( cmd_name, (char*)pgm_read_word(&(table_WiReach[66])));

	// "AT+iMACA?\r\n%s\r\n"
	strcpy_P( format, (char*)pgm_read_word(&(table_WIFI_FORMAT[31])));

	// generate "AT+iWLSI?\r"
	GEN_ATQUERY(cmd_name);

	// send command
	uint8_t status = sendCommand(_command, AT_OK, AT_ERROR, 500);

	if (status == 1)
	{
		result = sscanf( (char*)_buffer, format, _mac);

		if (result != 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}

	}
	else if (status == 2)
	{
		getErrorCode();
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0000;
		return 1;
	}
}

// Preinstantiate Objects /////////////////////////////////////////////////////

WaspWIFI_PRO WIFI_PRO = WaspWIFI_PRO();

///////////////////////////////////////////////////////////////////////////////
