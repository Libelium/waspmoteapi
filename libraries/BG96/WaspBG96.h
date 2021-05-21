/*! \file BG96.h
    \brief Library for managing Quectel BG96

    Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
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

    Version:		3.2
    Design:			David Gascón
    Implementation:	P.Moreno

 */

/*! \def BG96_h
    \brief The library flag
 */
#ifndef BG96_h
#define BG96_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <inttypes.h>
#include <WaspUART.h>
#include "./utility/BG96_constants.h"
#include <WaspOneWire.h>  // DS2413

/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

//! DEBUG_WASPBG96
/*! Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_BG96 	0	//2 max debug info
#define DEBUGAT		0	//2 max debug info
#define DEBUG_DS2413 0

// define print message
#define PRINT_BG96(str)	USB.print(F("[BG96] ")); USB.print(str);

// APN default settings
#define	BG96_APN		"APN"
#define	BG96_LOGIN		"user"
#define	BG96_PASSW		"password"

// Error Constants
#define sBG96_ERROR_CME		"+CME ERROR:"
#define sBG96_ERROR_CMS		"+CMS ERROR:"
#define sBG96_ERROR_CODE	"ERROR:"
#define sBG96_ERROR			"ERROR\r\n"
#define sBG96_OK 			"OK"
#define sBG96_PWDOWN 		"POWERED DOWN"


// BG96 Baud Rate
#define	sBG96_RATE	115200

#define BG96_GGA			0
#define BG96_GSA			1
#define BG96_GNS			2
#define BG96_VTG			3
#define BG96_RMC			4
#define BG96_GSV			5

// DS2413 defines
#define DS2413_ONEWIRE_PIN  GPRS_PIN

#define DS2413_FAMILY_ID    0x3A
#define DS2413_ACCESS_READ  0xF5
#define DS2413_ACCESS_WRITE 0x5A
#define DS2413_ACK_SUCCESS  0xAA
#define DS2413_ACK_ERROR    0xFF

//Bands definitions
#define B1				"1"
#define B2				"2"
#define B3				"4"
#define B4				"8"
#define B5				"10"
#define B8				"80"
#define B12				"800"
#define B13				"1000"
#define B18				"20000"
#define B19				"40000"
#define B20				"80000"
#define B26				"2000000"
#define B28				"8000000"
#define B39				"4000000000"
#define GSM900 			"00000001"
#define GSM1800			"00000002"
#define GSM850			"00000004"
#define GSM1900			"00000008"
#define GSM_ANYBAND		"0000000F"
#define NB_ANYBAND		"A0E189F"
#define M1_ANYBAND		"400A0E189F"

//Operator format
#define LALPHANUMERIC_OPERATOR	0
#define SALPHANUMERIC_OPERATOR	1
#define NUMERIC_OPERATOR		2

//eIDRX Settings
#define eIDRX_ENABLED 1
#define eIDRX_DISBLED 0
#define BG96_eIDRX_value "0010"

// Maximum packet size for FTP download
#define BG96_MAX_DL_PAYLOAD 490





//! Structure to define the info to be stored for all sockets
struct SocketInfo_t
{
	uint8_t id;			// from 1 to 6
	uint16_t sent;		// total length of sent data. Unit: byte.
	uint16_t ack;		// total length of acknowledged data. Unit: byte.
	uint16_t notack; 	// total length of unacknowledged data. Unit: byte.
	uint16_t received;	// total length of received data. Unit: byte.
	uint16_t readed;		// length of read data. Unit: byte.
	uint16_t notreaded;		// length of unread data. Unit: byte.
};


//! Structure to define the status to be stored for all sockets
struct SocketStatus_t
{
	uint8_t id;			// from 1 to 6
	char service_type[14]; // The socket service type
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
	uint16_t localPort;	// local port
	char remoteIp[16];	// remote IP address
	uint16_t remotePort;// remote port
	uint16_t received;	// total length of received data. Unit: byte.
};


/******************************************************************************
 * Class
 *****************************************************************************/
//! BG96 class

class WaspBG96 : public WaspUART
{

private:

	#define RADIO_BG96_UART_SIZE 512
	uint8_t class_buffer[RADIO_BG96_UART_SIZE];
	//!	Attribute for APN
	char _apn[30];

	//!	Attribute for APN login
	char _apn_login[30];

	//!	Attribute for APN password
	char _apn_password[30];

	//!	Attribute for HTTP POST content type
	char _contentType[80];

	//!	Attribute for PeriodicTAU - PSM parameter
	char _PeriodicTAU[9];

	//!	Attribute for ActiveTimer - PSM parameter
	char _ActiveTimer[9];

	//!	Attribute for eDRX value - eDRX parameter
	char _eIDRX_value[5];
	bool _eIDRX_status;

	uint8_t addressDS[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

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

	/*! Function: This function parses the error copde returned by the module
	 * after executing TCP/IP commands. At the  * point this function is called,
	 * the UART is supposed to have received: "ERROR: <err>\r\n"
	 *
	 * @return '0' ok; '1' error
	 */
	uint8_t getTCPErrorCode();



	//! This function waits the URC code and reads the data availble
	/*!
	\param	uint32_t wait_timeout: timeout for URC
	\return 0 if OK
 * 			1 if timeout waiting HTTP GET response
 * 			2 if timeout waiting HTTP POST response
 * 			3 if error waiting response
 * 			4 if error reading the response
 * 			5,6 if error reading the response
 * 			7 error waiting response function
	*/
	uint8_t httpWaitResponse(uint8_t method, uint32_t wait_timeout);

	//! This function configures the remote server and sends the request
	/*!
	\param	uint8_t method: selected HTTP method:	WaspBG96::HTTP_GET
													WaspBG96::HTTP_POST

	\param	char* url: host name or IP address of the server
	\param	uint16_t port: server port
	\param	char* resource: parameter indicating the HTTP resource, object of the
 					request
	\param	char* data: data to send in POST/PUT method
	\param	uint16_t data_length: data length to send in POST/PUT method
	\param	0 if OK
  			1 if error setting context id
  			2 if error sending url
  			3 if error sending POST
  			4 if wrong method has been selected
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

	bool write(uint8_t state);
	void printBytes(uint8_t* addr, uint8_t count) ;


public:

	char _ip[16]; // xxx.yyy.zzz.www - table_AT[34]
	char _ipRemote[16];
	uint16_t _errorCode;
	int _temp;
	int _tempInterval;
	int _rssi;
	uint8_t _networkType;
	uint8_t _incomingType;
	int _socketIndex;
	int _httpCode;
	uint16_t _socketerror;
	uint32_t _filesize;
	uint8_t _ftp_status;
	uint16_t _ftp_protocol_error;
	char _ftpWorkingDirectory[20];
	uint8_t _mqtt_status;
	uint8_t _mqtt_msgID;
	SocketInfo_t socketInfo[6];
	SocketStatus_t socketStatus[6];
	SocketStatusSSL_t socketStatusSSL[4];
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

	//! GNSS Mode Enumeration
	enum GPSModeEnum
	{
		GPS_MS_ASSISTED		= 0,
		GPS_MS_BASED		= 1,
		GPS_AUTONOMOUS		= 3,
	};

	//! GNSS Nmea Type Enumeration
	enum GNSSnmeaType
	{
		gpsnmeatype			= 0,
		glonassnmeatype		= 1,
		galileonmeatype		= 2,
		beidounmeatype		= 3,
		gsvextnmeatype		= 4,
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
		INFO_CSQ 				= 7,
		INFO_QNWINFO			= 8,
		INFO_QCSQ				= 9,
		INFO_QSPN				= 10,
	};

	//! HTTP method Enumeration
	enum HttpMethodEnumeration
	{
		HTTP_GET		= 0,
		HTTP_POST		= 1,
		HTTP_POST_FRAME	= 2,
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
	};

	//! Security data types
	enum SecurityDataTypesEnumeration
	{
		SSL_TYPE_CLIENT_CERT		= 0,
		SSL_TYPE_CA_CERT	= 1,
		SSL_TYPE_CLIENT_KEY		= 2,
	};

	//! SSL authentication mode
	enum SslAuthentication
	{
		SSL_CA_CERT	= 1,
		SSL_SERVER_CLIENT_AUTH	= 2,
	};

	//! FTP Session mode (Active or Passive)
	enum FtpSessionMode
	{
		FTP_ACTIVE		= 0,
		FTP_PASSIVE		= 1,
	};


	//! class constructor
    /*!
	\brief	It initializes some variables
	\param 	void
	\return void
    */
	WaspBG96();

	/*!
	\brief	This function inits the BG96 module
	\return 0 if OK
			1 for no comunication
			2 if error switching CME errors to numeric response
			3 if error disabling the echo from the module
			4 if error enabling RTC update with network time
	*/
	uint8_t ON();


	/*!
	\brief	This function powers off the BG96 module
	\return nothing
	*/
	uint8_t OFF();

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


		/*! GPRS CONNECTION STRUCTURE
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
	uint8_t gprsConnection(char* apn, char* gprsband, char* network, uint8_t operator_type);

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

	/*! NB-IOT CONNECTION STRUCTURE
	\brief	This function checks connection status and connect to data service
	\param	char apn
			uint32_t ltem1band
			uint16_t network
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
	uint8_t lteM1Connection(char* apn, char* ltem1band, char* network, uint8_t operator_type);

	/*! NB-IOT CONNECTION STRUCTURE
	\brief	This function checks connection status and connect to data service
	\param	char apn
			uint32_t nbiotband
			uint16_t network
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
	uint8_t nbiotConnection(char* apn, char* nbiotband, char* network, uint8_t operator_type);

	/*! NB-IOT BAND SETUP
	* +CBANDCFG: (CAT-M,NB-IOT),(1,2,3,4,5,8,12,13,17,18,19,20,26,28,32)
	\param	uint32_t gprsband: GPRS Network band
	param	uint32_t catm1band: LTE-M1 Network band
	\param	uint32_t nbiotband: NB_IoT Network band
	\return 0 If the band selected is ok

	*/
	uint8_t setBand(char* gprsband, char* catm1band, char* nbiotband);

	/*!Configure RAT(s) to be Searched
	* +CNMP: ((0-Automatic),(1-GSM Only),(3-LTE Only),(51-GSM And LTE Only))
	\param	uint8_t mode: Network scan mode
	\return 0 If the band selected is ok

	*/
	uint8_t setMode(uint8_t scanMode, char* scanseq, uint8_t iotmode);

	/*
	 * Set operator manualy.
	 * +COPS: Operator list
	 \param	uint16_t operatornumber: Operator number
	 */
	uint8_t setOperator(char* operatornumber, uint8_t Act, uint8_t operator_type);

	/*! SETUP NB-IOT Preferred selection between CAT-M and NB-IoT
  * +CMNB: ((1-Cat-M),(2-NB-IoT),(3-Cat-M And NB-IoT))
	\brief	This function checks connection status and connect to data service
	\param	uint8_t mode: Mode selected (1,2,3).
	\return 0 If the module is connected to data service
	*/
	uint8_t nbiotprefermode(uint8_t mode);

	/*! SETUP NB-IOT PSM setting parameters
  * AT+CPSMS=...
	\brief	This function set the PSM parameters
	\param
	\return 0 If the module is connected to data service
	*/
	uint8_t nbiotSettingPSM(char* PeriodicTAU, char* ActiveTimer);

	/*! SETUP NB-IOT PSM setting parameters
    \AT+CPSMS=...
	\brief	This function set the PSM parameters
	\param
	\return 0 If the module is connected to data service
	*/
	uint8_t nbiotSetPSM(bool mode, bool wait);

	/*! SETUP NB-IOT getting PSM values
    \AT+QPSMS?
	\brief	This function get the PSM values
	\return 0 If parameters are readed.
	*/
	uint8_t nbiotGetPSMValues();

	/*! NB-IOT PSM Wake UP
    \Pulse on PWRKEY pin.
	\brief	This function wake up the module from PSM mode.
	\return 0 If the module wake up and 1 if the module not wake up..
	*/
	uint8_t nbiotPSMWakeUp();

	/*! NB-IOT send UDP packet
	*
	\param	uint8_t
	\return 0 If the band selected is ok

	*/
	uint8_t nbiotSendUDP(char* ipRemote, uint16_t _port, char* UDPData, bool waitForResponse);

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
	\brief	This function deactivates/activates the NB-IOT context, eventually
			proceeding with the authentication with the parameters given with
			PASSW and USERID
	\param	uint8_t mode: NB-IoT/GPRS context activation mode
				\arg	0 - context deactivation request
				\arg	1 - context activation request
	\return 0 if OK
			1 if error checking socket status
	*/
	uint8_t contextActivation(uint8_t mode, uint8_t retries);

	/*!
	\brief	Configure Address of DNS Server
	\param	char* pridnsaddr: The primary DNS server address
			char* secdnsaddr: The secondary DNS server address
				Format: xxx.xxx.xxx.xxx
	\return 0 if OK
			1 if error
	*/
	uint8_t setDNSServer(char*  pridnsaddr, char* secdnsaddr);

	/*!
	\brief	Ping a Remote Server
	\param	char* host: The primary DNS server address
				Format: xxx.xxx.xxx.xxx or hostname (DNS server must be configured)
	\return 0 if OK
			1 if error
	*/
	uint8_t getPing(char*  host);

	/*!
	\brief	Synchronize Local Time with NTP Server
	\param	char* host: The address of NTP server.
				  port: The port of NTP server. The range is 1-65535.
	\return 0 if OK
			1 if error
	*/
	uint8_t syncLocalTimeNTP(char* host, uint16_t port );


/*! NB-IOT sleep mode
	*
	\param	uint8_t
	\return 0 If the band selected is ok

	/* This function manages the sleep mode
	 * Parameters:	mode: 0 disabled or 1 enabled
	 * Return:	0 if 'OK', '1' if error
	*/
	uint8_t nbiotSleepMode(uint8_t mode);

	/*! SETUP NB-IOT eDRX mode
    * AT+...
	\brief	This function set the eDRX parameters
	\param
	\return 0 If the module is connected to data service
	*/
	uint8_t settingeIDRX(uint8_t _eIDRX_status, uint8_t ActType,char* _eIDRX_value);

	/*!
	\brief	This function performs a HTTP request
	\param	uint8_t method: selected HTTP method:	WaspBG96::HTTP_GET
													WaspBG96::HTTP_HEAD
													WaspBG96::HTTP_DELETE
	\param	char* url: host name or IP address of the server
	\param	uint16_t port: server port
	\param	char* resource: parameter indicating the HTTP resource, object of the request
	\return	10 if OK
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
	uint8_t http(	uint8_t method,
					char* url,
					uint16_t port,
					char* resource);

	/*!
	\brief	This function performs a HTTP request
	\param	uint8_t method: selected HTTP method:	WaspBG96::HTTP_GET
													WaspBG96::HTTP_POST
													WaspBG96::HTTP_POST_FRAME
	\param	char* url: host name or IP address of the server
	\param	uint16_t port: server port
	\param	char* resource: parameter indicating the HTTP resource, object of the request
	\param	char* POST_PUT_data: data to send in POST/PUT method
	\param	uint16_t POST_PUT_length: data length to send in POST/PUT method
	\return	10 if OK
 * 			11 if error setting context id
 * 			12 if error sending url
 * 			13 if error sending POST
 * 			14 if wrong method has been selected *
 *			20 if OK
 * 			21 if timeout waiting HTTP GET response
 * 			22 if timeout waiting HTTP POST response
 * 			23 if error waiting response
 * 			24 if error reading the response
 * 			25,6 if error reading the response
 * 			27 error waiting response function
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
	\return	10 if OK
  			11 if error setting context id
  			12 if error sending url
  			13 if error sending POST
  			14 if wrong method has been selected *
 			20 if OK
  			21 if timeout waiting HTTP GET response
  			22 if timeout waiting HTTP POST response
  			23 if error waiting response
  			24 if error reading the response
  			25,26 if error reading the response
  			27 error waiting response function
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
	\Return:0 if OK
 * 			1 if error setting PDP context
 * 			2 if error setting username&password
 * 			3 if error setting file type
 * 			4 if error setting transfer mode
 * 			5 if error setting timeout
 * 			6 if error opening the FTP connection
 * 			7,8 if error reporting status connection
 * 			9 if operation status is not 0
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
			\arg WaspBG96::FTP_ACTIVE
			\arg WaspBG96::FTP_PASSIVE
	\return	0 if OK
 * 			1 if error setting PDP context
 * 			2 if error setting username&password
 * 			3 if error setting file type
 * 			4 if error setting transfer mode
 * 			5 if error setting timeout
 * 			6 if error opening the FTP connection
 * 			7,8 if error reporting status connection
 * 			9 if operation status is not 0
	*/
	uint8_t ftpOpenSession(	char* server,
							uint16_t port,
							char* username,
							char* password,
							uint8_t mode);

							/*!
	\brief	This function configures FTPS parameters and opens the connection
	\param	char* server: address of FTP server
	\param	uint16_t port: port of FTP server
	\param	char* username: authentication user identification string for FTP
	\param	char* password: authentication password for FTP
	* Return:	0 if OK
 * 			1 if error setting PDP context
 * 			2 if error setting username&password
 * 			3 if error setting file type
 * 			4 if error setting transfer mode
 * 			5 if error setting timeout
 * 			6 if error setting ssltype
 * 			7 if error setting sslctxid
 * 			8 if error setting ciphersuite
 * 			9 if error setting seclevel
 * 			10 if error setting sslversion
 * 			11 if error opening the FTP connection
 * 			12,13 if error reporting status connection
 * 			14 if operation status is not 0
	*/
	uint8_t ftpsOpenSession(	char* server,
							uint16_t port,
							char* username,
							char* password);

	/*!
	\brief	This function configures FTPS parameters and opens the connection
	\param	char* server: address of FTP server
	\param	uint16_t port: port of FTP server
	\param	char* username: authentication user identification string for FTP
	\param	char* password: authentication password for FTP
	\param	uint8_t mode: FTP session mode
			\arg WaspBG96::FTP_ACTIVE
			\arg WaspBG96::FTP_PASSIVE
	* Return:	0 if OK
 * 			1 if error setting PDP context
 * 			2 if error setting username&password
 * 			3 if error setting file type
 * 			4 if error setting transfer mode
 * 			5 if error setting timeout
 * 			6 if error setting ssltype
 * 			7 if error setting sslctxid
 * 			8 if error setting ciphersuite
 * 			9 if error setting seclevel
 * 			10 if error setting sslversion
 * 			11 if error opening the FTP connection
 * 			12,13 if error reporting status connection
 * 			14 if operation status is not 0
	*/
	uint8_t ftpsOpenSession(	char* server,
							uint16_t port,
							char* username,
							char* password,
							uint8_t mode);

	/*!
	\brief	This function closes the FTP connection
	\return	0 if OK; 1 if error
	 		1 if error
  			2, 3 if error waiting response
  			4 if operation status is not 0
	*/
	uint8_t ftpCloseSession();

	/*!
	\brief  This function deletes a file in the FTP server
	\param 	ftp_file: file to delete in FTP session
	\return	0 if OK; 1 if error
	*/
	uint8_t ftpDelete(char* ftp_file);

	/*!
	\brief 	This function reads the size of a file in a FTP server
	\param	char* FTP_file: file
	\return	'0' if OK, '1' if error
	*/
	uint8_t ftpFileSize( char* ftp_file);

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
	\brief  This function create a new directory of the FTP session
	\param 	dirpath: destiny directory in FTP server
	\return	0 if OK; 'x' if error
	*/
	uint8_t ftpCreateDirectory(char* dirpath);

	/*!
	\brief  This function delete a new directory of the FTP session
	\param 	dirpath: destiny directory in FTP server
	\return	0 if OK; 'x' if error
	*/
	uint8_t ftpDeleteDirectory(char* dirpath);

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
			8,9, 10 if error sending data or getting response
  			11 if error checking file size and file size uploaded
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
	\brief  This function check FTP session status
	\return	0 if OK; 'x' if error
	*/
	uint8_t ftpServerStatus();

	/*!
	\brief	This function configures and opens a socket
	\param	uint8_t socketId: number of the socket Id
	\param	char* protocol: TCP or UDP clients
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
							char* protocol,
							char* remote_IP,
							uint16_t remote_port);

	/*!
	\brief	This function configures and opens a socket
	\param	uint8_t socketId: number of the socket Id
	\param	char* protocol: TCP or UDP clients
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
							char* protocol,
							char* remote_IP,
							uint16_t remote_port,
							uint16_t local_port);

	/*!
	\brief	This function configures and opens a socket SSL
	\param	uint8_t socketId: number of the socket Id
	\param	char* remote_IP: address of the remote host
	\param	uint16_t remote_port: remote host port to contact
	\return	0 if OK
			1 SSL version error
			2 ciphersuite error
			3 seclevel error
			4 cacert error
			5 SSL socket status error
			6 open SSL socket error
			7 open SSL socket error 2
			8 open SSL socket error 3
			99 null pinter
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

	uint8_t getSocketStatusSSL(uint8_t socketId);

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

	/*!
	\brief	This function configures MQTT parameters and opens the connection
	\param	char* server: address of MQTT server
	\param	uint16_t port: port of MQTT server
	\param	uint8_t clientID: the client identifier
	\return	0 if OK
  			1 if error open network for MQTT client
  			2 if error network for MQTT client ocurried
  			3 if error connecting a Client to MQTT Server
  			4 if error client to MQTT Server command execution
  			5 if error client to MQTT Server connection status
 			90, 91 if error ocurried waiting the response - MQTT open network.
  			92, 93 if error ocurried waiting the response - Connect a Client to MQTT Server.
  			99 null pinter
	*/
	uint8_t mqttOpenSession(char* server,
							uint16_t port,
							char* clientID);

	/*!
	\brief	This function configures MQTT parameters and opens the connection
	\param	char* server: address of MQTT server
	\param	uint16_t port: port of MQTT server
	\param	char* username: authentication user identification string for MQTT
	\param	char* password: authentication password for MQTT
	\param	uint8_t clientID: the client identifier
	\return	0 if OK
  			1 if error open network for MQTT client
  			2 if error network for MQTT client ocurried
  			3 if error connecting a Client to MQTT Server
  			4 if error client to MQTT Server command execution
  			5 if error client to MQTT Server connection status
 				90, 91 if error ocurried waiting the response - MQTT open network.
  			92, 93 if error ocurried waiting the response - Connect a Client to MQTT Server.
  			99 null pinter
	*/
	uint8_t mqttOpenSession(char* server,
							uint16_t port,
							char* clientID,
							char* username,
							char* password);

	/*!
	\brief	This function configures MQTT with SSL parameters and opens the connection
	\param	uint8_t ssl_auth: The authentication mode
  									WaspBG96::SSL_CA_CERT: Manage server authentication
  									WaspBG96::SSL_SERVER_CLIENT_AUTH: Manage server and client authentication if requested by the remote server
	\param uint8_t socketId: Secure Socket Identifier (should be 2)
	\return	0 if OK
    			1 if error configuring MQTT session into SSL
    			2 if error setting seclevel
    			3 if error setting sslversion
    			4 if error setting ciphersuit
    			5 if error setting ignore local time
  				90 error setting the certificates
  				91 error setting CA certificate
  				92 error setting client certificate
  				93 error setting user key certificate
    			99 null pinter
	*/
	uint8_t mqttSslConfig(uint8_t ssl_auth, uint8_t socketId);



	/*!
	\brief	This function publish in a topic a MQTT message
	\param	uint16_t msgID: Message identifier of packet. The range is 0-65535. Should be 0 when qos=0.
	\param	uint8_t qos: The QoS level at which the client wants to publish the messages
  					0 At most once
  					1 At least once
 					2 Exactly once
	\param	bool retain: Whether or not the server will retain the message after it has been delivered to the
 					 0 The server will not retain the message after it has been delivered to the
 					   current subscribers
 					 1 The server will retain the message after it has been delivered to the current
 					   subscribers
	\param	char* topic: Topic that needs to be published
	\param	char* data: Message to be published
	\return	0 if OK
  				1 if error publising a message
  				2 if error publising a message and waitting OK
  				3, 4 if error waitting status report
  				5 if status <result> parameter is not 0
  				99 null pinter
	*/
	uint8_t mqttPublish(uint16_t msgID,
						uint8_t qos,
						bool retain,
						char* topic,
						char* data);

	/*!
	\brief	This function get the status connection to MQTT server
	\return	0 if OK
  				1 if error setting MQTT status
  				2 if error waitting response
  				99 null pinter
	*/
	uint8_t mqttSessionStatus();

	/*!
	\brief	The function is used to subscribe one topic
  \param	char* topic: Topic that the client wants to unsubscribe from
  \param	uint8_t qos: The QoS level at which the client wants to publish the messages.
	\return	0 if OK
    			1 if error unsubscribe from Topic
    			2, 3 if error waitting response
  				4 if failed to send packet
    			99 null pinter
	*/
	uint8_t mqttSubscribe(char* topic, uint8_t qos);

	/*!
	\brief	The function is used to subscribe one topic
	\param  uint16_t msgID: Message identifier of packet. The range is 1-65535
  \param	char* topic: Topic that the client wants to unsubscribe from
  \param	uint8_t qos: The QoS level at which the client wants to publish the messages.
	\return	0 if OK
    			1 if error unsubscribe from Topic
    			2,3 if error waitting response
  				4 if failed to send packet
    			99 null pinter
	*/
	uint8_t mqttSubscribe(uint16_t msgID, char* topic, uint8_t qos);

	/*!
	\brief	The function is used to unsubscribe from one topic
  \param char* topic: Topic that the client wants to unsubscribe from
	\return	0 if OK
  				1 if error unsubscribe from Topic
  				2, 3 if error waitting response
  				99 null pinter
	*/
	uint8_t mqttUnsubscribe(char* topic);

	/*!
	\brief	The function is used to unsubscribe from one topic
	\param uint16_t msgID: Message identifier of packet. The range is 1-65535
  \param char* topic: Topic that the client wants to unsubscribe from
	\return	0 if OK
  * 			1 if error unsubscribe from Topic
  * 			2, 3 if error waitting response
  * 			99 null pinter
	*/
	uint8_t mqttUnsubscribe(uint16_t msgID, char* topic);

	/*!
	\brief	The function is used to wait a data from a topic subscription
	\param uint16_t waitingtime: Wait time to get the data
	\return	0 if OK
  * 			1 if error ocurried waitting data
  * 			2 if error waitting response
  * 			99 null pinter
	*/
	uint8_t mqttWaittingData(uint16_t waitingtime);

	/*!
	\brief	This function close the connection to MQTT server
	\return	0 if OK
 					1 if error closing a MQTT connection
 					2, 3 if error ocurried waitting a response
 					4 if error ocurriend closing connection
 					99 null pinter
 */
	uint8_t mqttCloseSession();

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

	uint8_t gpsNmeatype(uint8_t nmeatype, uint8_t nmeatype_value);

	//! It gets the NMEA string
	uint8_t getNMEA(uint8_t nmea);

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


	//! This function gets the Operator name
	uint8_t getOperator(char* answer_storage);

	//! This function search the Operator names
	uint8_t scanOperators();

	/*!
	\brief 	This function gets info from the module
	\param	uint8_t info_req:
				WaspBG96::INFO_HW
				WaspBG96::INFO_MANUFACTURER_ID
				WaspBG96::INFO_MODEL_ID
				WaspBG96::INFO_REV_ID
				WaspBG96::INFO_IMEI
				WaspBG96::INFO_IMSI
				WaspBG96::INFO_ICCID
	\return		0 if OK
				1 if error
	*/
	int8_t getInfo(uint8_t info_req);

    /*!
	\brief 	This function sets the RTC time from network info
	\return '0' if OK; '1' if error
	 */
	uint8_t setTimeFromBG96();

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
	\brief 	This function sets the eIDRX parameters
	\param 	 uint8_t status: 0: eIDRX disabled and 1: eIDRX enabled
	\return void
	 */
	void set_eIDRX( uint8_t status);

    /*!
	\brief 	This function sets the eIDRX parameters
	\\param 	 uint8_t status: 0: eIDRX disabled and 1: eIDRX enabled
	\param 		 char* eIDRX_time: time parameter  (binary)
	\return void
	 */
	void set_eIDRX( uint8_t status, char* eIDRX_time);

    /*!
	\brief 	This function shows the apn, login and password constants
	\return '1' on success, '0' if error
	 */
	void show_APN();

	//! Print current _errorCode value
	void printErrorCode();

	//! Print error code given as input
	void printErrorCode(uint16_t error);

};

extern WaspBG96 BG96;

#endif
