/*! \file WaspWIFI_PRO.h
    \brief Library for managing WIFI modules

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

    Version:		3.2
    Design:			David Gascón
    Implementation:	Yuri Carmona
 */

#ifndef WaspWIFI_PRO_h
#define WaspWIFI_PRO_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <inttypes.h>
#include <WaspUART.h>
#include <stdarg.h>
#include "./utility/ati_generator.h"


/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 * \Remarks do not enable mode 2 unless SOCKET1 is used
 */
#define DEBUG_WIFI_PRO 	0

// define print message
#define PRINT_WIFI_PRO(str)	USB.print(F("[WIFI] ")); USB.print(str);



//! Command types
const uint8_t  TYPE_SET_EQ  = 1; // <par>=value
const uint8_t  TYPE_SET_DOT = 2; // <par>:value
const uint8_t  TYPE_ASSIGN	= 3; // <par>~value
const uint8_t  TYPE_READ	= 4; // <par>?
const uint8_t  TYPE_ALLOWED = 5; // <par>=?



//! AUTHENTICATION MODES //
enum authentication_modes
{
	OPEN = 0,			// no security
	WEP64 = 1,			// WEP 64
	WEP128 = 2,			// WEP 128
	WPA = 3,			// WPA-PSK with TKIP encryption
	WPA2 = 4,			// WPA2-PSK with TKIP or AES encryption
};


//! OTA CONSTANTS //
#define CHECK_VERSION	// when defined it enables the version cheking



//! Profile definition for multiple SSIDs
enum ProfileClientEnum
{
	PROFILE_0 = 0,
	PROFILE_1 = 1,
	PROFILE_2 = 2,
	PROFILE_3 = 3,
	PROFILE_4 = 4,
	PROFILE_5 = 5,
	PROFILE_6 = 6,
	PROFILE_7 = 7,
	PROFILE_8 = 8,
	PROFILE_9 = 9
};


//! Profile definition for different connections (SSID, TCP sockets, etc...)
enum WiFiWorkingMode
{
	MODE_STATION = 0,
	MODE_ACCESS_POINT = 1,
};

struct listen_socket_t
{
	uint16_t 	handle;		// socket handle
	int8_t 		status;		// 0: active; -1: non-active
	char 		ip[16]; 	// xxx.xxx.xxx.xxx
	uint16_t	port;		// remote connection port
	int			size;	 	// size of pending bytes
};

/******************************************************************************
 * Class
 *****************************************************************************/
//! WaspWIFI_PRO Class
/*!
	WaspWIFI_PRO Class defines all the variables and functions used to manage
	WIFI modules.
 */

class WaspWIFI_PRO : public WaspUART
{

private:

	#define RADIO_WIFI_UART_SIZE 512
	uint8_t class_buffer[RADIO_WIFI_UART_SIZE];

	//! Private Methods
	uint16_t getErrorCode();
	uint16_t getResponse();


	//! buffer for command generation
	char _command[300];
	void generator(uint8_t type, int n, const char *cmd_name, ...);


public:

	//! class constructor
    WaspWIFI_PRO()
    {
		// assign class pointer to UART buffer
		_buffer = class_buffer;
		_bufferSize = RADIO_WIFI_UART_SIZE;
	};


	// Attributes
	uint16_t 	_errorCode;
	uint16_t 	_rtt;
	uint32_t 	_value;
	char 		_ip[16]; // aaa.bbb.ccc.ddd
	char 		_gw[16]; // aaa.bbb.ccc.ddd
	char 		_netmask[16]; // aaa.bbb.ccc.ddd
	char 		_dns1[16]; // aaa.bbb.ccc.ddd
	char 		_dns2[16]; // aaa.bbb.ccc.ddd
	uint16_t 	_socket_handle;
	uint16_t 	_ftp_handle;
	uint8_t 	_backlog;
	uint32_t 	_filesize;
	uint16_t 	_rate;
	uint16_t 	_level;
	uint16_t 	_quality;
	char 		_essid[50];
	char 		_bssid[18];
	uint8_t		_channel;
	uint8_t		_snr;
	uint8_t		_power;
	listen_socket_t socket[10];
	char 		_firmwareVersion[30];
  char 		_mac[12];

	// Public Methods
	uint8_t ON(uint8_t socket);
	void OFF(uint8_t socket);
	uint8_t resetValues();

	// AP settings
	uint8_t setESSID(char* ssid);
	uint8_t setESSID(uint8_t n, char* ssid);
	uint8_t getESSID();
	uint8_t setPassword(uint8_t securityMode);
	uint8_t setPassword(uint8_t securityMode, char* pass);
	uint8_t setPassword(uint8_t n, uint8_t securityMode, char* pass);
	uint8_t setWorkingMode(uint8_t n);
	uint8_t setServerPoolSize(uint8_t range);
	uint8_t softReset();
	uint8_t reportStatus();
	uint8_t reportStatus4();
	uint8_t reportStatusComplete();
	bool isConnected();
	bool isConnectedMultiple();
	bool isConnected(uint32_t total_time,uint32_t period_time);
	uint8_t ping( char* host );

	// Print functions
	void printErrorCode();
	void printErrorCode(uint16_t error);
	void printSockets();
	uint8_t scan();

	// Common API functions
	uint8_t parseResponse(uint16_t* number);
	uint8_t parseResponse2(uint16_t* number);
	uint8_t parseResponse3();
	uint8_t parseResponse4();
	uint8_t parseResponse5(int* number);

	uint16_t getResponseValue();
	uint16_t getResponseValue2();
	uint8_t getResponseValue3();
	uint8_t getResponseValue4(uint8_t index);
	uint8_t getResponseValue5();

	uint8_t changeBaudRate(uint32_t rate);
	uint8_t userAbort();
	uint8_t socketAbort();

	// IP address
	uint8_t setIP(char* ip);
	uint8_t getIP();
	uint8_t setDNS(char* ip);
	uint8_t setDNS(uint8_t n, char* ip);
	uint8_t getDNS(uint8_t n);
	uint8_t setGateway(char* ip);
	uint8_t getGateway();
	uint8_t setNetmask(char* ip);
	uint8_t getNetmask();

	// HTTP functions
	uint8_t setURL(	char* protocol,
					char* host,
					char* port,
					char* link );

	uint8_t getURL( char* protocol,
					char* host,
					char* port,
					char* link );

	uint8_t post( char* text );
	uint8_t setContentType(char* str);

	uint8_t sendFrameToMeshlium(char* protocol,
								char* host,
								char* port,
								uint8_t* buffer,
								uint16_t length);


	// FTP functions
	uint8_t ftpOpenSession(	char* server,
							char* port,
							char* user,
							char* pass);

	uint8_t ftpSecureOpenSession(char* server,
									char* port,
									char* user,
									char* pass);

	uint8_t ftpCloseSession(uint16_t handle);

	uint8_t ftpFileSize(uint16_t handle, char* path);
	uint8_t ftpUpload(uint16_t handle, char* server_path, char* sd_path );
	uint8_t ftpDownload(uint16_t handle, char* server_path, char* sd_path);
	uint8_t ftpMakeDir(uint16_t handle, char* path);
	uint8_t ftpChangeCWD(uint16_t handle, char* path);
	uint8_t ftpListing(uint16_t handle);
	uint8_t ftpListing(uint16_t handle, char* path);

	// TCP/UDP functions
	uint8_t setTCPclient(char* host, char* remote_port );
	uint8_t setTCPclient(char* host, char* remote_port, char* local_port);
	uint8_t setUDP(char* host, char* remote_port );
	uint8_t setUDP(char* host, char* remote_port, char* local_port);
	uint8_t send(uint16_t handle, char* data);
	uint8_t send(uint16_t handle, uint8_t* data, uint16_t length);
	uint8_t receive(uint16_t handle);
	uint8_t receive(uint16_t handle, uint32_t timeout);
	uint8_t closeSocket();
	uint8_t closeSocket(uint16_t handle);
	uint8_t closeDownSockets();
	uint8_t setTCPserver(char* local_port, uint8_t backlog);
	uint8_t getAllSocketStatus();
	uint8_t getSocketStatus(uint16_t handle);


	// Time Server settings
	uint8_t setTimeServer(char* ip);
	uint8_t setTimeServer(uint8_t n, char* ip);
	uint8_t timeActivationFlag(bool flag);
	uint8_t setGMT(int8_t gmt);
	uint8_t reportStatus8();
	uint8_t setTimeFromWIFI();

	// OTA programming
	uint8_t requestOTA(	char* server,
						char* port,
						char* user,
						char* pass);

	// Roaming mode
	uint8_t roamingMode(uint8_t mode);
	uint8_t setScanInterval(uint8_t n);
	uint8_t setLowThreshold(uint8_t n);
	uint8_t setHighThreshold(uint8_t n);

	// Power settings
	uint8_t setPower(uint8_t power);
	uint8_t getPower();

	// SSL/TLS
	uint8_t setCA(char* ca);
	uint8_t sslHandshake(	uint8_t handle );

	// Firmware
	uint8_t getFirmwareVersion();

  // MAC address
  uint8_t getMAC();
};

extern WaspWIFI_PRO WIFI_PRO;

#endif
