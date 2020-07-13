/*! \file Wasp4G.h
    \brief Library for managing Telit LE910

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

    Version:		3.4
    Design:			David Gascón
    Implementation:	A. Gállego, Y. Carmona

 */

/*! \def Wasp4G_h
    \brief The library flag
 */
#ifndef Wasp4G_h
#define Wasp4G_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <inttypes.h>
#include <WaspUART.h>
#include "./utility/Wasp4G_constants.h"

/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

//! DEBUG_WASP4G
/*! Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_WASP4G 	0

//! Flag to enable the version number checking in OTA process
#define LE910_CHECK_VERSION

// define print message
#define PRINT_LE910(str)	USB.print(F("[LE910] ")); USB.print(str);

// APN default settings
#define	LE910_GPRS_APN		"APN"
#define	LE910_GPRS_LOGIN	"user"
#define	LE910_GPRS_PASSW	"password"

// Error Constants
#define LE910_ERROR_CME		"+CME ERROR:"
#define LE910_ERROR_CMS		"+CMS ERROR:"
#define LE910_ERROR_CODE	"ERROR:"
#define LE910_ERROR			"ERROR\r\n"
#define LE910_OK 			"OK"


static char LE910_OTA_FILE[] = "UPGRADE.TXT";


// LE910 Baud Rate
#define	LE910_RATE	115200

#define LE910_GGA			0
#define LE910_GSA			1
#define LE910_GLL			2
#define LE910_VTG			3
#define LE910_RMC			4
#define LE910_GSV			5

// Incoming data options
#define LE910_INCOMING_SMS	1
#define LE910_INCOMING_IP	2

// Patterns for module communication
#define LE910_DATA_TO_MODULE ">>>"
#define LE910_DATA_FROM_MODULE "<<<"

// Maximum packet size for FTP download
#define LE910_MAX_DL_PAYLOAD 490

// DS2413 constants
#define DS2413_ONEWIRE_PIN  GPRS_PIN

#define DS2413_RESET    	0x01
#define DS2413_INVERT_PIO   0x03
#define DS2413_FAMILY_ID    0x3A
#define DS2413_ACCESS_READ  0xF5
#define DS2413_ACCESS_WRITE 0x5A
#define DS2413_ACK_SUCCESS  0xAA
#define DS2413_ACK_ERROR    0xFF


//! Structure to define the info to be stored for all sockets
struct SocketInfo_t
{
	uint8_t id;			// from 1 to 6
	uint16_t sent;		// total num of bytes sent since socket was opened
	uint16_t received;	// total num of bytes received since socket was opened
	uint16_t size;		// total num of pending bytes to read which arrived through the socket
	uint16_t ack;		// total num of bytes sent and not yet acknowledged data since socket was opened
};


//! Structure to define the status to be stored for all sockets
struct SocketStatus_t
{
	uint8_t id;			// from 1 to 6
	uint8_t state;		// actual state of the socket
	char localIp[16];	// local IP address
	uint16_t localPort;	// local port
	char remoteIp[16];	// remote IP address
	uint16_t remotePort;// remote port
};


//! Structure to define the status to be stored for all sockets
struct SocketStatusSSL_t
{
	uint8_t id;			// from 1 to 6
	uint8_t state;		// actual state of the socket
};


/******************************************************************************
 * Class
 *****************************************************************************/
//! Wasp4G class

class Wasp4G : public WaspUART
{

private:

	#define RADIO_4G_UART_SIZE 512
	uint8_t class_buffer[RADIO_4G_UART_SIZE];

	//!	Attribute for APN
	char _apn[30];

	//!	Attribute for APN login
	char _apn_login[30];

	//!	Attribute for APN password
	char _apn_password[30];

	//!	Attribute for HTTP POST content type
	char _contentType[80];

	//! Array to store DS2413 address
	uint8_t DS2413_address[8] = {0,0,0,0,0,0,0,0};

	uint8_t DS2413_present = 0;

	uint8_t module_version = 0;

	/*! This function parses the error copde returned by the module. At the
	 * point this function is called, the UART is supposed to have received:
	 * "+CME ERROR: <err>\r\n" and the first part of the response has been
	 * already detected: "+CME ERROR:", so this function needs to parse the
	 * error code.
	 *
	 * If error code is parsed succesfully then the attribute _errorCode stores
	 * this error information
	 *
	 * @return '0' ok; '1' error
	 */
	uint8_t getErrorCode();

	//! This function configures the remote server and sends the request
	/*!
	\param	uint8_t method: selected HTTP method:	Wasp4G::HTTP_GET
													Wasp4G::HTTP_HEAD
													Wasp4G::HTTP_DELETE
													Wasp4G::HTTP_POST
													Wasp4G::HTTP_PUT
	\param	char* url: host name or IP address of the server
	\param	uint16_t port: server port
	\param	char* resource: parameter indicating the HTTP resource, object of the
 					request
	\param	char* data: data to send in POST/PUT method
	\param	uint16_t data_length: data length to send in POST/PUT method
	\param	0 if OK
				1 if error setting URL and port
				2 if error sending the request
				3 if error sending POST / PUT data
				4 if worng method has been selected
	*/
	uint8_t httpRequest(uint8_t method,
						char* url,
						uint16_t port,
						char* resource,
						char* data);

	uint8_t httpRequest(uint8_t method,
						char* url,
						uint16_t port,
						char* resource,
						uint8_t* data,
						uint16_t length);

	//! This function waits the URC code and reads the data availble
	/*!
	\param	uint32_t wait_timeout: timeout for URC
	\return 	0 if OK
				1 if timeout waiting the URC
				2 if error reading the URC
				3 if error reading the HTTP data
				4 if error reading the HTTP data
	*/
	uint8_t httpWaitResponse(uint32_t wait_timeout);

	uint8_t check_DS2413();

	uint8_t write_DS2413(uint8_t byte);

	uint8_t read_DS2413();

	uint8_t on_DS2413();

	uint8_t off_DS2413();

	uint8_t getModelVersion();

	WaspOneWire oneWire = WaspOneWire(DS2413_ONEWIRE_PIN);


public:

	char _ip[16]; // xxx.yyy.zzz.www
	uint16_t _errorCode;
	int _temp;
	int _tempInterval;
	int _rssi;
	uint8_t _networkType;
	uint8_t _incomingType;
	int _smsIndex;
	int _socketIndex;
	int _httpCode;
	uint32_t _filesize;
	char _smsStatus[12];
	char _smsNumber[20];
	char _smsDate[9];
	char _smsTime[12];
	char _ftpWorkingDirectory[20];
	SocketInfo_t socketInfo[6];
	SocketStatus_t socketStatus[6];
	SocketStatusSSL_t socketStatusSSL[1];
	uint8_t _wirelessNetwork;

	//! Profile definition for multiple sockets
	enum ProfileSocketEnum
	{
		CONNECTION_1 = 0,
		CONNECTION_2 = 1,
		CONNECTION_3 = 2,
		CONNECTION_4 = 3,
		CONNECTION_5 = 4,
		CONNECTION_6 = 5,
	};

	//! Socket Status definition
	enum SocketStatusEnum
	{
		STATUS_CLOSED			= 0,
		STATUS_ACTIVE			= 1,
		STATUS_SUSPENDED		= 2,
		STATUS_SUSPENDED_DATA	= 3,
		STATUS_LISTENING		= 4,
		STATUS_INCOMING			= 5,
		STATUS_OPENING			= 6,
	};

	//! Wireless Network enumeration
	enum WirelessNetworkEnum
	{
		NETWORK_GSM				= 12,
		NETWORK_UTRAN 			= 22,
		NETWORK_3GPP			= 25, // default
		NETWORK_EUTRAN_ONLY		= 28,
		NETWORK_GERAN_UTRAN		= 29,
		NETWORK_GERAN_EUTRAN	= 30,
		NETWORK_UTRAN_EUTRAN	= 31,
	};

	//! GPS Mode Enumeration
	enum GPSModeEnum
	{
		GPS_MS_ASSISTED		= 0,
		GPS_MS_BASED		= 1,
		GPS_AUTONOMOUS		= 3,
	};

	//! Module Information Enumeration
	enum ModuleInformationEnum
	{
		INFO_HW 				= 0,
		INFO_MANUFACTURER_ID 	= 1,
		INFO_MODEL_ID 			= 2,
		INFO_REV_ID 			= 3,
		INFO_IMEI 				= 4,
		INFO_IMSI 				= 5,
		INFO_ICCID 				= 6,
	};

	//! Network Type Enumeration
	enum NetworkTypeEnumeration
	{
		NETWORK_GPRS	= 0,
		NETWORK_EGPRS	= 1,
		NETWORK_WCDMA	= 2,
		NETWORK_HSDPA	= 3,
		NETWORK_LTE		= 4,
		NETWORK_UNKNOWN	= 5,
	};

	//! SMS Delete Flag
	enum DeleteFlagEnumeration
	{
		SMS_DELETE_MESSAGE	= 0,
		SMS_DELETE_ALL_1 	= 1,
		SMS_DELETE_ALL_2 	= 2,
		SMS_DELETE_ALL_3 	= 3,
		SMS_DELETE_ALL_4 	= 4,
	};

	//! HTTP method Enumeration
	enum HttpMethodEnumeration
	{
		HTTP_GET		= 0,
		HTTP_HEAD		= 1,
		HTTP_DELETE		= 2,
		HTTP_POST		= 3,
		HTTP_PUT		= 4,
		HTTP_POST_FRAME	= 5,
	};

	//! TCP/UDP sockets protocol enumeration
	enum MultisocketProtocolEnumeration
	{
		TCP = 0,
		UDP = 1,
	};

	//! Security data actions enumeration
	enum SecurityDataActionsEnumeration
	{
		SSL_ACTION_DELETE	= 0,
		SSL_ACTION_STORE	= 1,
		SSL_ACTION_READ		= 2,
		SSL_EMAIL_DISABLED	= 0,
		SSL_EMAIL_ENABLES	= 1,
	};

	//! E-mail security enumeration
	enum EmailSecurityEnumeration
	{
		EMAIL_NONSSL	= 0,
		EMAIL_SSL		= 1,
	};

	//! Security data types
	enum SecurityDataTypesEnumeration
	{
		SSL_TYPE_CERT		= 0,
		SSL_TYPE_CA_CERT	= 1,
		SSL_TYPE_RSA		= 2,
	};

	//! FTP Session mode (Active or Passive)
	enum FtpSessionMode
	{
		FTP_ACTIVE		= 0,
		FTP_PASSIVE		= 1,
	};

	//! Cipher Suites
	enum CipherSuite
	{
		CHOSEN_BY_REMOTE_SERVER			= 0,
		TLS_RSA_WITH_RC4_128_MD5		= 1,
		TLS_RSA_WITH_RC4_128_SHA		= 2,
		TLS_RSA_WITH_AES_128_CBC_SHA	= 3,
		TLS_RSA_WITH_NULL_SHA 			= 4,
		TLS_RSA_WITH_AES_256_CBC_SHA	= 5,

		V1_TLS_RSA_WITH_AES_256_CBC_SHA	= 3,
	};


	//! Autentification mode
	enum AuthMode
	{
		SSL_VERIFY_NONE					= 0,
		MANAGE_SERVER_AUTH				= 1,
		MANAGE_SERVER_AND_CLIENT_AUTH	= 2,
	};

	//! SSL/TLS protocol version
	enum SSLprotocolVersion
	{
		SSL_v3		= 0,
		TLS_v1_0	= 1,
		TLS_v1_1	= 2,
		TLS_v1_2	= 3,
	};


	//! class constructor
    /*!
	\brief	It initializes some variables
	\param 	void
	\return void
    */
	Wasp4G();

	/*!
	\brief	This function inits the LE910 module
	\return 0 if OK
			1 for no comunication
			2 if error switching CME errors to numeric response
			3 if error disabling the echo from the module
			4 if error enabling RTC update with network time
	*/
	uint8_t ON();


	/*!
	\brief	This function powers off the LE910 module
	\return nothing
	*/
	void OFF();

	/*!
	\brief	This function enters a PIN / PUK code
	\param 	char* code: string with the requested code
	\return	0 if OK; 1 if error
	*/
	uint8_t enterPIN(char* code);

	/*!
	\brief	This function enters a PIN / PUK code
	\param 	char* code: string with the requested code
	\param 	char* new_code: string with the new code (only for SIM PUK or SIM PUK2)
	\return	'0' if OK; '1' if error
	*/
	uint8_t enterPIN(char* code, char* new_code);

	/*!
	\brief	This function returns the result code for a PIN request
	\return	0 for PIN ready
			1 LE910 is awaiting SIM PIN
			2 LE910 is awaiting SIM PUK
			3 LE910 is awaiting phone-to-SIM card password.
			4 LE910 is awaiting phone-to-very-first-SIM card password.
			5 LE910 is awaiting phone-to-very-first-SIM card unblocking password.
			6 LE910 is awaiting SIM PIN2
			7 LE910 is awaiting SIM PUK2
			8 LE910 is awaiting network personalization password
			9 LE910 is awaiting network personalization unblocking password
			10 LE910 is awaiting network subset personalization password
			11 LE910 is awaiting network subset personalization unblocking password
			12 LE910 is awaiting service provider personalization password
			13 LE910 is awaiting service provider personalization unblocking password
			14 LE910 is awaiting corporate personalization password
			15 LE910 is awaiting corporate personalization unblocking password
			254 if not expected code returned
			255 if command error
	*/
	uint8_t checkPIN();

	/*!
	\brief	This function checks connection status
	\param	uint8_t time: max allowed time in seconds to connect
	\return 0 If the module is connected to the network
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
	*/
	uint8_t checkConnection(uint8_t time);
	uint8_t checkConnectionEPS(uint8_t time);

	/*!
	\brief	This function checks connection status and connect to data service
	\param	uint8_t time: max allowed time in seconds to connect
	\return 0 If the module is connected to data service
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
	*/
	uint8_t checkDataConnection(uint8_t time);

	/*!
	\brief	This function deactivates/activates the GPRS context, eventually
			proceeding with the authentication with the parameters given with
			#PASSW and #USERID
	\param	uint8_t mode: GPRS context activation mode
				\arg	0 - GPRS context deactivation request
				\arg	1 - GPRS context activation request
	\return 0 if OK
			1 if error checking socket status
	*/
	uint8_t gprsContextActivation(uint8_t mode);

	/*!
	\brief	This function sets the socket configuration parameters
	\param	uint8_t connId: socket connection identifier
	\param	uint8_t cid: PDP context identifier
	\param	uint16_t pktSz: packet size to be used by the TCP/UDP/IP stack for data sending
	\param	uint16_t maxTo: exchange timeout
	\param	uint16_t connTo: connection timeout if we can’t establish a connection
	\param	uint16_t txTo: data sending timeout
	\return 0 if OK
			1 if error checking socket status
	*/
	uint8_t socketConfiguration(uint8_t  connId,
								uint8_t  cid,
								uint16_t pktSz,
								uint16_t maxTo,
								uint16_t connTo,
								uint16_t txTo);


	/*!
	\brief	This function manages incoming data from serial port
	\param	unsigned long wait_time: maximum waiting time in milliseconds
	\return	0 for error or not data
			1 for SMS
			2 for IP data
	*/
	uint8_t	manageIncomingData(unsigned long wait_time);


	/*!
	\brief	This function sets the parameters to use SMS
	\return	0 if OK
			1 if error setting the SMS format
			2 if error selecting the storage
			3 if error setting the incoming SMS indication
	*/
	uint8_t configureSMS();

	/*!
	\brief	This function reads the last unread received message
	\param	uint32_t timeout: time to wait for a new SMS
	\return	0 if OK; 1 if error
	*/
	uint8_t readNewSMS();
	uint8_t readNewSMS(uint32_t timeout);


	/*!
	\brief	This function sends a SMS
	\param	char* phone_number: number to send the SMS
	\param	char* sms_string: body of the SMS
	\return	0 if OK
			1 if error setting the phone number
			2 if error sending the body
	*/
	uint8_t sendSMS(char* phone_number, char* sms_string);


	/*!
	\brief	This function reads a SMS
	\param	uint8_t sms_index: index of the SMS into the memory
	\return	0 if OK
			1 if error getting the SMS
			2 if error storing the message
	*/
	uint8_t readSMS(uint8_t sms_index);


	/*!
	\brief	This function deletes a SMS
	\param	uint8_t sms_index: index of the SMS into the memory
	\return	0 if OK
			1 if error deleting the SMS
	*/
	uint8_t deleteSMS(uint8_t sms_index);


	/*!
	\brief	This function deletes a SMS
	\param	uint8_t sms_index: index of the SMS into the memory
	\return	0 if OK
			1 if error deleting the SMS
	*/
	uint8_t deleteSMS(uint8_t sms_index, uint8_t del_flag);

	//! Function: 	This function stores the desired Content-Type for HTTP POST requests
	/*!
	\param uint8_t content: index number corresponding to content type.
	 				“0” – “application/x-www-form-urlencoded”
	 				“1” – “text/plain”
	 				“2” – “application/octet-stream”
	 				“3” – “multipart/form-data”
	\return	'0' if OK
	 		'x' if error
	 */
	uint8_t httpSetContentType(uint8_t content);

	//! Function: This function stores the desired Content-Type for HTTP POST requests
	/*!
	\param char* content: string corresponding to content type. i.e. "text/plain"
	\return '0' if OK
			'x' if error
	*/
	uint8_t httpSetContentType(char* content);

	/*!
	\brief	This function performs a HTTP request
	\param	uint8_t method: selected HTTP method:	Wasp4G::HTTP_GET
													Wasp4G::HTTP_HEAD
													Wasp4G::HTTP_DELETE
	\param	char* url: host name or IP address of the server
	\param	uint16_t port: server port
	\param	char* resource: parameter indicating the HTTP resource, object of the request
	\return	0 if OK
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
			16 if error setting URL and port
			17 if error sending the request
			18 if error sending POST / PUT data
			19 if wrong method has been selected
			20 if timeout waiting the URC
			21 if error reading the URC
			22 if error reading the HTTP status
			23 if error reading the HTTP data length
			24 if error reading the HTTP data
			25 if error code from 4G module while waiting for HTTP response
			26 if timeout waiting for HTTP response
			27 if HTTP response data length is zero
	*/
	uint8_t http(	uint8_t method,
					char* url,
					uint16_t port,
					char* resource);

	/*!
	\brief	This function performs a HTTP request
	\param	uint8_t method: selected HTTP method:	Wasp4G::HTTP_GET
													Wasp4G::HTTP_HEAD
													Wasp4G::HTTP_DELETE
													Wasp4G::HTTP_POST
													Wasp4G::HTTP_PUT
													Wasp4G::HTTP_POST_FRAME
	\param	char* url: host name or IP address of the server
	\param	uint16_t port: server port
	\param	char* resource: parameter indicating the HTTP resource, object of the request
	\param	char* POST_PUT_data: data to send in POST/PUT method
	\param	uint16_t POST_PUT_length: data length to send in POST/PUT method
	\return	0 if OK
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
			16 if error setting URL and port
			17 if error sending the request
			18 if error sending POST / PUT data
			19 if wrong method has been selected
			20 if timeout waiting the URC
			21 if error reading the URC
			22 if error reading the HTTP status
			23 if error reading the HTTP data length
			24 if error reading the HTTP data
			25 if error code from 4G module while waiting for HTTP response
			26 if timeout waiting for HTTP response
			27 if HTTP response data length is zero
	*/
	uint8_t http(	uint8_t method,
					char* url,
					uint16_t port,
					char* resource,
					char* data);


	/*!
	\brief	This function performs a HTTP request to send data to Meshlium. It
			is mandatory to use a Waspmote frame as input
	\param	char* url: host name or IP address of the Meshlium device
	\param	uint16_t port: server port
	\param	uint8_t* data: pointer to frame buffer
	\param	uint16_t length: data length to send in POST/PUT method
	\return	0 if OK
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
			16 if error setting URL and port
			17 if error sending the request
			18 if error sending POST / PUT data
			19 if wrong method has been selected
			20 if timeout waiting the URC
			21 if error reading the URC
			22 if error reading the HTTP status
			23 if error reading the HTTP data length
			24 if error reading the HTTP data
			25 if error code from 4G module while waiting for HTTP response
			26 if timeout waiting for HTTP response
			27 if HTTP response data length is zero
	*/
	uint8_t sendFrameToMeshlium(char* url,
								uint16_t port,
								uint8_t* data,
								uint16_t length);


	/*!
	\brief	This function configures FTP parameters and opens the connection
	\param	char* server: address of FTP server
	\param	uint16_t port: port of FTP server
	\param	char* username: authentication user identification string for FTP
	\param	char* password: authentication password for FTP
	\return	0 if OK
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
			16 if error opening the FTP connection
			17 if error setting the transfer type
	*/
	uint8_t ftpOpenSession(	char* server,
							uint16_t port,
							char* username,
							char* password);

	/*!
	\brief	This function configures FTP parameters and opens the connection
	\param	char* server: address of FTP server
	\param	uint16_t port: port of FTP server
	\param	char* username: authentication user identification string for FTP
	\param	char* password: authentication password for FTP
	\param	uint8_t mode: FTP session mode
			\arg Wasp4G::FTP_ACTIVE
			\arg Wasp4G::FTP_PASSIVE
	\return	0 if OK
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
			16 if error opening the FTP connection
			17 if error setting the transfer type
	*/
	uint8_t ftpOpenSession(	char* server,
							uint16_t port,
							char* username,
							char* password,
							uint8_t mode);

	/*!
	\brief	This function closes the FTP connection
	\return	0 if OK; 1 if error
	*/
	uint8_t ftpCloseSession();


	/*!
	\brief  This function deletes a file in the FTP server
	\param 	ftp_file: file to delete in FTP session
	\return	0 if OK; 1 if error
	*/
	uint8_t ftpDelete(char* ftp_file);

	/*!
	\brief  This function requests the current working directory in FTP server
	\return	0 if OK; 'x' if error
	*/
	uint8_t ftpGetWorkingDirectory();

	/*!
	\brief  This function changes the working directory of the FTP session
	\param 	dirname: destiny directory in FTP server
	\return	0 if OK; 'x' if error
	*/
	uint8_t ftpChangeWorkingDirectory(char* dirname);

	/*!
	\brief 	This function uses PUT to send a file to a FTP server
	\param	char* ftp_file: destiny file
	\param	char* sd_file: origin file
	\return	0 if OK
			1 if no SD present
			2 if file does not exist
			3 if error opening the file
			4 if error setting the pointer of the file
			5 if error getting the file size
			6 if error opening the PUT connection
			7 if error exiting from the data mode
			8 if error sending data
	*/
	uint8_t ftpUpload( char* ftp_file, char* sd_file);

	/*!
	\brief 	This function uses GET to read a file from a FTP server
	\param	char* SD_file: destiny file
	\param	char* FTP_file: origin file
	\return	0 if OK
			1 if server file size is zero
			2 if error reading the file size
			3 if SD not present
			4 if error creating the file in SD
			5 if error opening the file
			6 if error setting the pointer of the file
			7 if error opening the GET connection
			8 if the module returns error code after requesting data
			9 if error getting packet size
			10 if error in packet size mismatch
			11 if error writing SD error
			12 if no more retries getting data
			13 if file size mismatch
	*/
	uint8_t ftpDownload( char* sd_file,  char* ftp_file);

	/*!
	\brief 	This function reads the size of a file in a FTP server
	\param	char* FTP_file: file
	\return	'0' if OK, '1' if error
	*/
	uint8_t ftpFileSize( char* ftp_file);


	/*!
	\brief 	This function requests OTA
	\param	char* ftp_server: address of FTP server with OTA files
	\param	uint16_t ftp_port: port of FTP server with OTA files
	\param	char* ftp_user: authentication user identification string for FTP
	\param	char* ftp_pass: authentication password for FTP
	\return	0 if OK
			1 if SD not present
			2 if error downloading LE910_OTA_FILE (UPGRADE.TXT)
			3 if error opening FTP session
			4 if filename is different to 7 bytes
			5 if no "FILE" pattern found
			6 if "NO_FILE" is the filename
			7 if no "PATH" pattern found
			8 if no "SIZE" pattern found
			9 if no "VERSION" pattern found
			10 if invalid program version number
			11 if file size does not match in UPGRADE.TXT and server
			12 if error downloading binary file: server file size is zero
			13 if error downloading binary file: reading the file size
			14 if error downloading binary file: SD not present
			15 if error downloading binary file: error creating the file in SD
			16 if error downloading binary file: error opening the file
			17 if error downloading binary file: error setting the pointer of the file
			18 if error downloading binary file: error opening the GET connection
			19 if error downloading binary file: error module returns error code after requesting data
			20 if error downloading binary file: error  getting packet size
			21 if error downloading binary file: packet size mismatch
			22 if error downloading binary file: error writing SD
			23 if error downloading binary file: no more retries getting data
			24 if error downloading binary file: size mismatch
	*/
	uint8_t requestOTA(char* OTA_server,
						uint16_t OTA_port,
						char* OTA_username,
						char* OTA_password);
	/*!
	\brief 	This function requests OTA
	\param	char* ftp_server: address of FTP server with OTA files
	\param	uint16_t ftp_port: port of FTP server with OTA files
	\param	char* ftp_user: authentication user identification string for FTP
	\param	char* ftp_pass: authentication password for FTP
	\param	uint8_t ftp_mode: FTP session mode:
			\arg Wasp4G::FTP_ACTIVE
			\arg  Wasp4G::FTP_PASSIVE
	\return	0 if OK
			1 if SD not present
			2 if error downloading LE910_OTA_FILE (UPGRADE.TXT)
			3 if error opening FTP session
			4 if filename is different to 7 bytes
			5 if no "FILE" pattern found
			6 if "NO_FILE" is the filename
			7 if no "PATH" pattern found
			8 if no "SIZE" pattern found
			9 if no "VERSION" pattern found
			10 if invalid program version number
			11 if file size does not match in UPGRADE.TXT and server
			12 if error downloading binary file: server file size is zero
			13 if error downloading binary file: reading the file size
			14 if error downloading binary file: SD not present
			15 if error downloading binary file: error creating the file in SD
			16 if error downloading binary file: error opening the file
			17 if error downloading binary file: error setting the pointer of the file
			18 if error downloading binary file: error opening the GET connection
			19 if error downloading binary file: error module returns error code after requesting data
			20 if error downloading binary file: error  getting packet size
			21 if error downloading binary file: packet size mismatch
			22 if error downloading binary file: error writing SD
			23 if error downloading binary file: no more retries getting data
			24 if error downloading binary file: size mismatch
	*/
	uint8_t requestOTA(	char* ftp_server,
						uint16_t ftp_port,
						char* ftp_user,
						char* ftp_pass,
						uint8_t ftp_mode);


	/*!
	\brief	This function configures and opens a socket
	\param	uint8_t socketId: number of the socket Id
	\param	bool protocol: 0 for TCP_CLIENT and 1 for UDP_CLIENT
	\param	char* remote_IP: address of the remote host (IPv6 allowed)
	\param	uint16_t remote_port: remote host port to contact
	\return	0 if OK
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
			16 error getting socket status
			17 Socket with an active data transfer connection
			18 Socket suspended
			19 Socket suspended with pending data
			20 Socket listening
			21 Socket with an incoming connection. Waiting for the user accept or shutdown command
			22 Socket in opening process. The socket is not in Closed state but
				still not in Active or Suspended or Suspended with pending data state
			23 if error in Socket Configuration
			24 if error in Socket Configuration Extended 3
			25 if error sending the open command
			26 if timeout opening the socket
	*/
	uint8_t openSocketClient(uint8_t socketId,
							bool protocol,
							char* remote_IP,
							uint16_t remote_port);

	/*!
	\brief	This function configures and opens a socket
	\param	uint8_t socketId: number of the socket Id
	\param	bool protocol: 0 for TCP_CLIENT and 1 for UDP_CLIENT
	\param	char* remote_IP: address of the remote host (IPv6 allowed)
	\param	uint16_t remote_port: remote host port to contact
	\param	uint16_t local_port: UDP connections local port
	\return	0 if OK
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
			16 error getting socket status
			17 Socket with an active data transfer connection
			18 Socket suspended
			19 Socket suspended with pending data
			20 Socket listening
			21 Socket with an incoming connection. Waiting for the user accept or shutdown command
			22 Socket in opening process. The socket is not in Closed state but
				still not in Active or Suspended or Suspended with pending data state
			23 if error in Socket Configuration
			24 if error in Socket Configuration Extended 3
			25 if error sending the open command
			26 if timeout opening the socket
	*/
	uint8_t openSocketClient(uint8_t socketId,
							bool protocol,
							char* remote_IP,
							uint16_t remote_port,
							uint16_t local_port);

	/*!
	\brief	This function configures and opens a socket
	\param	uint8_t socketId: number of the socket Id
	\param	bool protocol: 0 for TCP and 1 for UDP
	\param	char* remote_IP: address of the remote host (IPv6 allowed)
	\param	uint16_t remote_port: remote host port to contact
	\param	uint16_t local_port: UDP connections local port
	\param	bool keep_alive: 0 disable, 1 enable
	\param	uint8_t keep_alive: From 0 (disabled) to 240 minutes
	\return	0 if OK
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
			16 error getting socket status
			17 Socket with an active data transfer connection
			18 Socket suspended
			19 Socket suspended with pending data
			20 Socket listening
			21 Socket with an incoming connection. Waiting for the user accept or shutdown command
			22 Socket in opening process. The socket is not in Closed state but
				still not in Active or Suspended or Suspended with pending data state
			23 if error in Socket Configuration
			24 if error in Socket Configuration Extended 3
			25 if error sending the open command
			26 if timeout opening the socket
	*/
	uint8_t openSocketClient(uint8_t socketId,
							bool protocol,
							char* remote_IP,
							uint16_t remote_port,
							uint16_t local_port,
							uint8_t keep_alive);

	/*!
	\brief	This function opens a socket listening for an incoming connection on
			a specified port
	\param	uint8_t socketId: number of the socket Id
	\param	bool protocol: 0 for TCP_SERVER and 1 for UDP_SERVER
	\param	uint16_t local_port: TCP/UDP connections local port
	\param	keep_alive: From 0 (disabled) to 240 minutes
	\return	0 if OK
			1: not registered, ME is not currently searching for a new operator to register to
			2: not registered, but ME is currently searching for a new operator to register to
			3: registration denied
			4: unknown
			6: not registered, ME is not currently searching for a new operator to register to
			8: not registered, but ME is currently searching for a new operator to register to
			9: registration denied
			10: unknown
			12: if error setting APN
			13: if error setting login
			14: if error setting password
			15: if error activating GPRS connection
			16: if error getting socket status
			17: if error in Socket Configuration
			18: if protocol input not valid
			19: if error opening the socket
	*/
	uint8_t openSocketServer(uint8_t socketId,
							bool protocol,
							uint16_t local_port);

	uint8_t openSocketServer(uint8_t socketId,
							bool protocol,
							uint16_t local_port,
							uint8_t keep_alive);



	/*!
	\brief	This function configures and opens a socket SSL
	\param	uint8_t socketId: number of the socket Id
	\param	char* remote_IP: address of the remote host (IPv6 allowed)
	\param	uint16_t remote_port: remote host port to contact
	\return	0 if OK
			1 not registered, ME is not currently searching for a new operator to register to
			2 not registered, but ME is currently searching for a new operator to register to
			3 registration denied
			4 unknown
			6 not registered, ME is not currently searching for a new operator to register to
			8 not registered, but ME is currently searching for a new operator to register to
			9 registration denied
			10 unknown
			12 if error setting APN
			13 if error setting login
			14 if error setting password
			15 if error activating GPRS connection
			16 if error getting SSL Socket Status
			17 if socket disabled
			19 if socket already open
			20 if error opening the socket
			21 if no response from module
	*/
	uint8_t openSocketSSL(	uint8_t socketId,
							char* remote_IP,
							uint16_t remote_port);


	/*!
	\brief	This function closes a socket previously opened
	\param	uint8_t socketId: number of the socket Id
	\return	0 Socket Closed
			1 if error sending the command
			2 if timeout shutting down the socket
	*/
	uint8_t closeSocketClient(uint8_t socketId);
	uint8_t closeSocketServer(uint8_t socketId, uint8_t protocol);


	/*!
	\brief	This function closes a SSL socket previously opened
	\param	uint8_t socketId: number of the socket Id
	\return	0 Socket Closed
			1 if error sending the command
			2 if timeout shutting down the socket
	*/
	uint8_t closeSocketSSL(uint8_t socketId);


	/*!
	\brief	This function gets the status of a TCP or UDP socket
	\param	uint8_t socketId: number of the socket Id
	\return	0 if OK; 1 if error
	*/
	uint8_t getSocketStatus(uint8_t socketId);
	uint8_t getAllSocketStatus();
	uint8_t getSocketStatusSSL(uint8_t socketId);

	/*!
	\brief 	This function manages the TCP/UDP socket profiles. If there is an
			incoming connection, it is accepted
	\param	uint32_t wait_time: time to wait for incoming connections
    */
	uint8_t	manageSockets();
	uint8_t	manageSockets(uint32_t wait_time);

	/*!
	\brief	This function gets info from a TCP or UDP socket
	\param	uint8_t socketId: number of the socket Id
	\return	0 if ok; 1 if error
	*/
	uint8_t getSocketInfo(uint8_t socketId);


	/*!
	\brief	This function sends data through a socket previously opened
	\param	uint8_t socketId: number of the socket Id
	\param	uint8_t* data: string with the data
	\return	0 if OK
			1 if error checking socket status
			2 if incorrect socket status
			3 if error sending data
			4 if error waiting confirmation from module
			5 if error getting socket status
			6 if timeout getting socket status
	*/
	uint8_t send(uint8_t socketId, char* data);

	/*!
	\brief	This function sends data through a socket previously opened
	\param	uint8_t socketId: number of the socket Id
	\param	uint8_t* data: buffer with the data
	\param	uint16_t data_length: length of the data buffer
	\return	0 if OK
			1 if error checking socket status
			2 if incorrect socket status
			3 if error sending data
			4 if error waiting confirmation from module
			5 if error getting socket status
			6 if timeout getting socket status
	*/
	uint8_t send(uint8_t socketId, uint8_t* data, uint16_t data_length);

	/*!
	\brief	This function sends data through a SSL socket previously opened
	\param	uint8_t socketId: number of the socket Id
	\param	uint8_t* data: string with the data
	\return	0 if OK
			1 if error checking socket status
			2 if incorrect socket status
			3 if error sending data
			4 if no response from module
			5 if error getting socket status
			6 if timeout waiting for correct socket status
	*/
	uint8_t sendSSL(uint8_t socketId, char* data);


	/*!
	\brief	This function sends data through a SSL socket previously opened
	\param	uint8_t socketId: number of the socket Id
	\param	uint8_t* data: buffer with the data
	\param	uint16_t data_length: length of the data buffer
	\return	0 if OK
			1 if error checking socket status
			2 if incorrect socket status
			3 if error sending data
			4 if no response from module
			5 if error getting socket status
			6 if timeout waiting for correct socket status
	*/
	uint8_t sendSSL(uint8_t socketId, uint8_t* data, uint16_t data_length);


	/*!
	\brief	This function read data received in the module
	\param	uint8_t socketId: number of the socket Id
	\return	0 if data received
			1 if no data received
			2 if error getting socket info
			3 if timeout waiting for data
			4 if error receiving data from module
			5 if error parsing length of data
			6 if error reading incoming bytes
	*/
	uint8_t receive(uint8_t socketId);

	/*!
	\brief	This function read data received in the module
	\param	uint8_t socketId: number of the socket Id
	\param	uint32_t timeout: timeout in ms to wait for response
	\return	0 if data received
			1 if no data received
			2 if error getting socket info
			3 if timeout waiting for data
			4 if error receiving data from module
			5 if error parsing length of data
			6 if error reading incoming bytes
	*/
	uint8_t receive(uint8_t socketId, uint32_t timeout);

	/*!
	\brief	This function reads data received in the module through SSL socket
	\param	uint8_t socketId: number of the socket Id
	\return	0 if ok
			1 if no answer from module
			2 if SSL socket disconnected
			3 if error code from module
			4 if no response from module
			5 if error parsing length of received data
			6 if error getting received data
			7 if error waiting module confirmation
	*/
	uint8_t receiveSSL(uint8_t socketId);

	/*!
	\brief	This function reads data received in the module through SSL socket
	\param	uint8_t socketId: number of the socket Id
	\param	uint32_t timeout: timeout in ms to wait for response
	\return	'0' if ok; 'x' if error
	*/
	uint8_t receiveSSL(uint8_t socketId, uint32_t timeout);



	/*!
	\brief	This function allows to store, delete and read security data
			(Certificate, CAcertificate, private key) into the non-volatile
			memory of the module
	\param 	socketId: Secure Socket Identifier (must be 1)
	\param 	action: Action to do:
						0 – Delete data from NVM
						1 – Store data into NVM
						2 – Read data from NVM
	\param 	dataType:
						0 – Certificate
						1 – CA certificate
						2 – RSA Private key
	\param 	data: string with the security data
	\param	cipherSuite:
	 					0 – Chiper Suite is chosen by remote Server [default]
	 					1 – TLS_RSA_WITH_RC4_128_MD5
	 					2 – TLS_RSA_WITH_RC4_128_SHA
	 					3 – TLS_RSA_WITH_AES_128_CBC_SHA
	 					4 – TLS_RSA_WITH_NULL_SHA
						5 – TLS_RSA_WITH_AES_256_CBC_SHA
	\param	authMode:
						0 – SSL Verify None[default]
 						1 – Manage server authentication
 						2 – Manage server and client authentication if requested by the remote server

	\return	0 if OK
			1 if error setting security data
			2 if error waiting module confirmation
			3 if error getting security data
			4 if error deleting security data
			5 if invalid action input
	 */
	uint8_t manageSSL(	uint8_t socketId,
						uint8_t action,
						uint8_t dataType);

	uint8_t manageSSL(	uint8_t socketId,
						uint8_t action,
						uint8_t dataType,
						char *data);

	uint8_t manageSSL(	uint8_t socketId,
						uint8_t action,
						uint8_t dataType,
						char *data,
						uint8_t cipherSuite,
						uint8_t authMode);


	/*!
	\brief	This function allows to configure the SSL/TLS protocol version
			NO SUPPORTED BY TELIT V1 MODULES
	\param	uint8_t socketId: Secure Socket Identifier (must be 1)
	\param	uint8_t version: SSL/TLS protocol version
	\return	'0' if ok; 1 if error
	*/
	uint8_t setSSLprotocol(	uint8_t socketId, uint8_t version);


	//! Latitude
	char _latitude[11];

	//! Variable : it stores the latitude indicator N: North; S: South
	char _latitudeNS;		//NS_indicator

	char _longitude[12];	//longitude

	//! Variable : it stores the longitude indicator E: East; W: West
	char _longitudeEW;		//EW_indicator

	float _altitude;		// altitude
	char _time[7];			// hhmmss
	char _date[7];			// ddmmyy
	uint8_t _numSatellites;		// satellites in use
	uint8_t _fixMode;		// satellites in use
	float _speedOG;			// speed over ground (Km/hr)
	char _courseOG[7];		// course over ground ddd.mm
	float _hdop;			// Horizontal Diluition of Precision

	/*!
	\brief 	Starts the GPS engine with hot start and stand alone mode
	\param 	uint8_t gps_mode:
				0: Pure MS Assisted - Location estimate from the network (MS Assisted mode).
				1: MS Based - Assistance Data from the network (MS Based mode).
				2: MS Assisted Based - Combination of MS-A and MS-B modes, location
				estimate computed both at UE and Network.
				3: Autonomous – Autonomous GPS mode of operation.
	\param 	uint8_t reset_mode:
				1 Coldstart
				2 Warmstart
				3 Hotstart
	\return 0 if OK
			1 if error setting the reset mode
			2 if error checking current GPS status
			3 if error starting the GPS engine in standalone mode
			4 if error setting NETWORK_UTRAN mode
			5 if error defining the PDP context
			6 if error setting authentication user ID
			7 if error setting authentication password
			8 if error setting socket configuration
			9 if error setting quality of service
			10 if error setting the SLP server
			11 if error setting the supported SUPL version
			12 if error updating terminal information
			13 if error enabling unsolicited response
			14 if error locking context for LCS use
			15 if error enabling GNSS (or GLONASS)
			16 if error in GPS Start Location Service Request
			17 if error checking data connection
			18 if incorrect GPS mode
	 */
	uint8_t gpsStart();
	uint8_t gpsStart(uint8_t gps_mode);
	uint8_t gpsStart(uint8_t gps_mode, uint8_t reset_mode);

	/*!
	\brief Stops the GPS engine
	\return 0 if OK; 1 if error
	 */
	uint8_t gpsStop();

	/*!
	\brief Checks GPS signal
	\return '1' if GPS status is unknown
		'2' if GPS status is not fixed
		'3' if GPS status is fixed in 2D mode
		'4' if GPS status is fixed in 3D mode
	 */
	int8_t checkGPS();

	/*!
	\brief Performs a HTTP request to AGPS server.
	\return '0' if OK
			'x' if error
	 */
	uint8_t gpsSendHttpRequest();

	//! It converts from the NMEA message and indicator to degrees
	float convert2Degrees(char* input, char indicator);


	/*!
	\brief 	It checks if receiver is connected to some satellite until time out
	\return '0' if OK; '1' if error
	*/
	uint8_t waitForSignal();

	/*!
	\brief 	It checks if receiver is connected to some satellite until time out
	\param 	uint32_t timeout: timeout to fix the satellites defined in seconds
	\return '0' if OK; '1' if error
	*/
	uint8_t waitForSignal(uint32_t timeout);


	/*!
	\brief 	It checks if receiver is connected to some satellite until time out
	\param 	uint32_t timeout: timeout to fix the satellites defined in seconds
	\param 	float desired_HDOP: Desired HDOP accuracy to wait for signal
	\return '0' if OK; '1' if error
	*/
	uint8_t waitForSignal(uint32_t timeout, float desired_HDOP);

	//! It gets the NMEA string
	bool getNMEAString(uint8_t NMEA);

	//! It sets the quality of service of GPS
	uint8_t gpsSetQualityOfService(	uint32_t horiz_accuracy,
									uint16_t vertic_accuracy,
									uint16_t rsp_time,
									uint32_t age_of_location_info,
									uint8_t location_type,
									uint8_t nav_profile,
									uint8_t velocity_request);

	/*!
	\brief 	This function gets the temperature interval or the temperature value
	\return	If interval mode selected
				-2 Extreme temperature lower bound.
				-1 Operating temperature lower bound.
				0 normal temperature.
				1 Operating temperature upper bound.
				2 Extreme temperature upper bound.
				-1000 if error

			If temperature value selected return temperature in Celsius
				-1000 if error
	*/
	uint8_t getTemp();

	/*!
	\brief 	This function gets the RSSI level
	\return	the value in dBm
			0 if error
	*/
	uint8_t getRSSI();


	/*!
	\brief 	This function gets the packet service network type
	\return	0 for GPRS network
			1 for EGPRS network
			2 for WCDMA network
			3 for HSDPA network
			4 for LTE network
			5 for unknown or not registered
			-1 if error
	*/
	uint8_t getNetworkType();

	//! This function gets the Operator name
	uint8_t getOperator(char* answer_storage);

	/*!
	\brief 	This function selects the Wireless Network
	\param 	uint8_t n:  it is the WDS-Side Stack used by the TA:
				Wasp4G::NETWORK_GSM
				Wasp4G::NETWORK_UTRAN
				Wasp4G::NETWORK_3GPP
				Wasp4G::NETWORK_EUTRAN_ONLY
				Wasp4G::NETWORK_GERAN_UTRAN
				Wasp4G::NETWORK_GERAN_EUTRAN
				Wasp4G::NETWORK_UTRAN_EUTRAN
	 */
	uint8_t setWirelessNetwork(uint8_t n);

	/*!
	\brief 	This function gets the current Wireless Network.
			The _wirelessNetwork parameter will store the WDS-Side Stack
			used by the TA:
				Wasp4G::NETWORK_GSM
				Wasp4G::NETWORK_UTRAN
				Wasp4G::NETWORK_3GPP
				Wasp4G::NETWORK_EUTRAN_ONLY
				Wasp4G::NETWORK_GERAN_UTRAN
				Wasp4G::NETWORK_GERAN_EUTRAN
				Wasp4G::NETWORK_UTRAN_EUTRAN
	\return	0 if OK
			1 if error
	 */
	uint8_t getWirelessNetwork();


	/*!
	\brief 	This function gets info from the module
	\param	uint8_t info_req:
				Wasp4G::INFO_HW
				Wasp4G::INFO_MANUFACTURER_ID
				Wasp4G::INFO_MODEL_ID
				Wasp4G::INFO_REV_ID
				Wasp4G::INFO_IMEI
				Wasp4G::INFO_IMSI
				Wasp4G::INFO_ICCID
	\return		0 if OK
				1 if error
	*/
	int8_t getInfo(uint8_t info_req);

    /*!
	\brief 	This function sets the RTC time from 4G network info
	\return '0' if OK; '1' if error
	 */
	uint8_t setTimeFrom4G();

    /*!
	\brief 	This function sets the apn from operator
	\param 	char* apn: apn from operator
	\return void
	 */
	void set_APN( char* apn);

    /*!
	\brief 	This function sets the apn, login and password from operator
	\param 	char* apn: apn from operator
	\param 	char* login: login from operator
	\param 	char* password: password from operator
	\return void
	 */
	void set_APN( char* apn, char* login, char* password);

    /*!
	\brief 	This function shows the apn, login and password constants
	\return '1' on success, '0' if error
	 */
	void show_APN();

	//! Print current _errorCode value
	void printErrorCode();

	//! Print error code given as input
	void printErrorCode(uint16_t error);


    /*!
	\brief 	This function sets the SMTP server address, used for E-mail sending.
	\param 	char* address: SMTP server address, string type. This parameter can	be either:
				- Any valid IP address in the format: xxx.xxx.xxx.xxx
				- Any host name to be solved with a DNS query
	\return	'0' if OK; 'x' if error
	*/
	uint8_t emailSetServerSMTP(char* address);

    /*!
	\brief 	This function sets the email sender parameters
	\param 	char* address: sender's email address
	\param 	char* user: sender's user address
	\param 	char* password: sender's email password
	\return	0 if OK
			1 if error setting the sender address
			2 if error setting the sender user
			3 if error setting the sender password
	*/
	uint8_t emailSetSender(char* address, char* user, char* password);

    /*!
	\brief 	This function activates context
	\param 	char* user: APN user
	\param 	char* password: APN password
	\return	'0' if OK; 'x' if error
	*/
	uint8_t emailActivateContext(char* user, char* password);

    /*!
	\brief 	This function sets the SMTP security and port
	\param 	uint8_t security:	Wasp4G::EMAIL_SSL
								Wasp4G::EMAIL_NONSSL
	\param 	uint16_t port: port number
	\return	'0' if OK; 'x' if error
	*/
	uint8_t emailConfigureSMTP(uint8_t security, uint16_t port);

    /*!
	\brief 	This function sends the email
	\param 	char* address: receiver's email address
	\param 	char* subject: subject of the email
	\param 	char* body: main text message of the email
	\return	0 if OK
			1 if error sending mail
			2 if error waiting for module confirmation
	*/
	uint8_t emailSend(char* address, char* subject, char* body);

    /*!
	\brief 	This function resets the actual e-mail parameters in the NVM of
	the module to the default ones. The values reset are:
		E-mail User Name
		E-mail Password
		E-mail Sender Address
		E-mail SMTP server
	\return	'0' if OK; 'x' if error
	*/
	uint8_t emailReset();

    /*!
	\brief 	This function saves the actual e-mail parameters in the NVM of the
	device. The values reset are:
		E-mail User Name
		E-mail Password
		E-mail Sender Address
		E-mail SMTP server
	\return	'0' if OK; 'x' if error
	*/
	uint8_t emailSave();
};

extern Wasp4G _4G;

#endif
