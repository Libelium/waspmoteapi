/*! \file WaspWIFI_v3.h
    \brief Library for managing WIFI modules

    Copyright (C) 2021 Libelium Comunicaciones Distribuidas S.L.
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

    Implementation:	Yuri Carmona
 */

#ifndef WaspWIFI_PRO_V3_h
#define WaspWIFI_PRO_V3_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <inttypes.h>
#include <WaspUART.h>
#include "./utility/wifi_constants.h"


/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 * \Remarks do not enable mode 2 unless SOCKET1 is used
 */
#define DEBUG_WIFI_V3	0

// define print message
#define PRINT_WIFI_V3(str)	USB.print(F("[WIFI] ")); USB.print(str);


struct ap_client_t
{
	char 		ip[16]; 	// xxx.xxx.xxx.xxx
	char 		mac[18]; 	// xx.xx.xx.xx.xx.xx
};

/******************************************************************************
 * Class
 *****************************************************************************/
/*!
 * Class defines all the variables and functions used to manage WiFi modules
 */

class WaspWIFI_v3 : public WaspUART
{

private:

	#define RADIO_WIFI_V3_UART_SIZE 512
	uint8_t class_buffer[RADIO_WIFI_V3_UART_SIZE];
	
	uint8_t parseSTASTATUS();
	uint8_t parseSTAIP();
	uint8_t parseKPING();
	uint8_t parseKPINGSTAT();
	uint8_t parseCMEERROR();
	uint8_t parseHTTPERROR();
	uint8_t parseKTCP_DATA();
	uint8_t parseKTCP_NOTIF();
	uint8_t parseKTCP_SRVREQ();
	uint8_t parseKUDP_DATA();
	uint8_t parseKUDP_NOTIF();
	uint8_t parseKUDP_SRVREQ();
	uint8_t parseKMQTT_IND();
	uint8_t parseSRWAPSTA();
	uint8_t httpDeleteConfig();
	uint8_t httpsDeleteConfig();
	

public:

	//! class constructor
    WaspWIFI_v3()
    {
		// assign class pointer to UART buffer
		_buffer = class_buffer;
		_bufferSize = RADIO_WIFI_V3_UART_SIZE;
		
		_baudrate = 115200;
		_def_delay = 100;
	};


	// Attributes
	uint16_t 	_errorCode;
	//~ uint32_t 	_value;
	char 		_ip[16]; // aaa.bbb.ccc.ddd
	char 		_gw[16]; // aaa.bbb.ccc.ddd
	char 		_netmask[16]; // aaa.bbb.ccc.ddd
	char 		_dns1[16]; // aaa.bbb.ccc.ddd
	char 		_dns2[16]; // aaa.bbb.ccc.ddd
	char 		_essid[50];
	char 		_bssid[18];
	uint8_t		_channel;
	int8_t		_authmode;
	int8_t		_power;
	char 		_firmwareVersion[30];
	char 		_mac[18];
	
	uint16_t _cmeerror;
	uint16_t _pingBytes;
	uint16_t _pingTime;
	uint16_t _pingSent;
	uint16_t _pingReceived;
	uint16_t _pingLost;
	uint16_t _pingMinTime;
	uint16_t _pingMaxTime;
	
	uint8_t _tcpNotifSessionId;
	uint8_t _tcpNotifCode;	
	uint8_t	_tcpDataSessionId;
	uint16_t _tcpDataAvailable;
	uint8_t _tcpSessionId;
	uint8_t _tcpClientSessionId;
	char _tcpClientIp[16];
	uint16_t _tcpClientPort;
	
	uint8_t _udpNotifSessionId;
	uint8_t _udpNotifCode;	
	uint8_t	_udpDataSessionId;
	uint16_t _udpDataAvailable;
	uint8_t _udpSessionId;
	uint8_t _udpClientSessionId;
	char _udpClientIp[16];
	uint16_t _udpClientPort;
	
	uint8_t _httpSessionId = 1;
	uint16_t _httpResponseStatus;
	char _httpServer[50];
	uint16_t _httpPort;
	uint8_t _httpserror;
	
	uint8_t _mqttSessionId = 1;
	char _mqttServer[50];
	char _mqttClientID[50];
	uint16_t _mqttPort;
	char _mqtt_topic_data[50];
	uint8_t _mqttInd;
	uint8_t _mqttSec;
	
	ap_client_t client[10];
	uint8_t _apClients;

	// Public Methods
	uint8_t ON(uint8_t socket);
	void OFF(uint8_t socket);
	uint8_t resetValues();
	uint8_t softReset();
	void openUartBridge();

	// Configure mode: AP or Station
	uint8_t configureMode(uint8_t mode);
	uint8_t configureMode(uint8_t mode, uint8_t country);
	
	// Configure Network settings depending on the mode
	uint8_t configureStation(char* ssid, char* password);
	uint8_t configureStation(char* ssid, char* password, uint8_t autoconnect);
	uint8_t configureAp(char* ssid, char* passkey, uint8_t authmode);
	uint8_t configureAp(char* ssid, char* passkey, uint8_t authmode, uint8_t channel, uint8_t ssid_hidden);
	int8_t getConnectedDevices();
	
	uint8_t configureStationSettings(uint8_t dhcp);
	uint8_t configureStationSettings(uint8_t dhcp, char* ip);
	uint8_t configureStationSettings(uint8_t dhcp, char* ip, char* nm);
	uint8_t configureStationSettings(uint8_t dhcp, char* ip, char* nm, char* gw);
	
	uint8_t configureApSettings(uint8_t dhcp);
	uint8_t configureApSettings(uint8_t dhcp, char* ip, char* ip_start, char* ip_end, uint16_t lease_time);
	
	enum AuthenticationMode
	{
		AUTH_OPEN = 0,
		AUTH_WEP = 1,
		AUTH_WPA = 2,
		AUTH_WPA2 = 3, // default
		AUTH_WPA_WPA2 = 4,
	};
	
	enum ConnectionStatus
	{
		STATUS_DISCONNECTED = 0,
		STATUS_CONNECTED = 1,
	};
	
	enum ConnectionFailureReason
	{
		REASON_INTERNAL_FAILURE = 1,
		REASON_AUTH_NO_LONGER_VALID = 2,
		REASON_DEAUTH_STATION_LEAVING = 3,
		REASON_DISASSOCIATED_INACTIVITY = 4,
		REASON_DISASSOCIATED_AP_HANDLE_ERROR = 5,
		REASON_PACKET_RECEIVED_FROM_NONAUTH_STATION = 6,
		REASON_PACKET_RECEIVED_FROM_NONASSOC_STATION = 7,
		REASON_DISASSOCIATED_STATION_LEAVING = 8,
		REASON_STATION_REQUEST_REASSOC = 9,
		REASON_DISASSOCIATED_PWR_CAPABILITY_UNACCEPTABLE = 10,
		REASON_DISASSOCIATED_SUPPORTED_CHANNEL_UNACCEPTABLE = 11,
		REASON_INVALID_ELEMENT = 13,
		REASON_MIC_FAILURE = 14,
		REASON_FOUR_WAY_HANDSHAKE_TIMEOUT = 15,
		REASON_GROUP_KEY_HANDSHAKE_TIMEOUT = 16,
		REASON_ELEMENT_IN_FOUR_WAY_HANDSHAKE_DIFFERENT = 17,
		REASON_INVALID_GROUP_CIPHER = 18,
		REASON_INVALID_PAIRWISE_CIPHER = 19,
		REASON_AKMP = 20,
		REASON_UNSUPPORTED_RSNE_CAPABILITIES = 21,
		REASON_INVALID_RSNE_CAPABILITIES = 22,
		REASON_IEEE_AUTH_FAILED = 23,
		REASON_CIPHER_SUITE_REJECTED = 24,
		REASON_STATION_LOST_BEACONS_CONTINUOUSLY = 200,
		REASON_STATION_FAILED_TO_SCAN_TARGET_AP = 201,
		REASON_STATION_AUTH_FAILED_NOT_TIMEOUT = 202,
		REASON_STATION_AUTH_FAILED_NOT_TIMEOUT_NOT_MANY_STATIONS = 203,
		REASON_HANDHASKE_FAILED = 204,
	};	
		
	enum DhcpEnabled
	{
		DHCP_DISABLED = 0,
		DHCP_ENABLED = 1, // default
	};
	
	uint8_t _status;
	uint8_t _reason;
	uint8_t connect();
	uint8_t disconnect();
	
	
	//~ uint8_t setESSID(char* ssid);
	//~ uint8_t setESSID(uint8_t n, char* ssid);
	//~ uint8_t getESSID();
	//~ uint8_t setPassword(uint8_t securityMode);
	//~ uint8_t setPassword(uint8_t securityMode, char* pass);
	//~ uint8_t setPassword(uint8_t n, uint8_t securityMode, char* pass);
	//~ uint8_t setWorkingMode(uint8_t n);
	//~ uint8_t setServerPoolSize(uint8_t range);

	//~ uint8_t reportStatus();
	//~ uint8_t reportStatus4();
	//~ uint8_t reportStatusComplete();
	bool isConnected();
	bool isConnected(uint32_t);
	bool stationStatus();
	//~ bool isConnectedMultiple();
	//~ bool isConnected(uint32_t total_time,uint32_t period_time);
	
	uint8_t ping(char* ip);
	uint8_t ping(char* ip, uint32_t count, uint32_t timeout, uint32_t interval);

	// Print functions
	//~ void printErrorCode();
	//~ void printErrorCode(uint16_t error);
	//~ void printSockets();
	//~ uint8_t scan();

	// Common API functions
	uint8_t parseResponse(uint16_t* number);
	//~ uint8_t parseResponse2(uint16_t* number);
	//~ uint8_t parseResponse3();
	//~ uint8_t parseResponse4();
	//~ uint8_t parseResponse5(int* number);

	//~ uint16_t getResponseValue();
	//~ uint16_t getResponseValue2();
	//~ uint8_t getResponseValue3();
	//~ uint8_t getResponseValue4(uint8_t index);
	//~ uint8_t getResponseValue5();

	//~ uint8_t changeBaudRate(uint32_t rate);
	//~ uint8_t userAbort();
	//~ uint8_t socketAbort();

	// IP address
	//~ uint8_t setIP(char* ip);
	//~ uint8_t getIP();
	uint8_t setDNS(char* dns);
	uint8_t setDNS(char* dns, char* dns_backup);
	uint8_t setDNS(char* dns, char* dns_backup, char* dns_fallback);
	//~ uint8_t setGateway(char* ip);
	//~ uint8_t getGateway();
	//~ uint8_t setNetmask(char* ip);
	//~ uint8_t getNetmask();

	// HTTP functions
	//~ uint8_t setURL(	char* protocol,
					//~ char* host,
					//~ char* port,
					//~ char* link );

	//~ uint8_t getURL( char* protocol,
					//~ char* host,
					//~ char* port,
					//~ char* link );

	//~ uint8_t post( char* text );
	//~ uint8_t setContentType(char* str);

	//~ uint8_t sendFrameToMeshlium(char* protocol,
								//~ char* host,
								//~ char* port,
								//~ uint8_t* buffer,
								//~ uint16_t length);

	// Meshlium
	uint8_t formatMeshliumData(char* buffer, uint8_t* data, uint16_t length);



	enum TcpMode
	{
		TCP_CLIENT = 0,
		TCP_SERVER = 1,
		TCP_CHILD = 2,
		TCP_SECURE_CLIENT = 3,
	};
	

	enum TcpCloseMode
	{
		TCP_CLOSE_ABORT = 0,
		TCP_CLOSE_COMPLETE = 1,
	};
	
	
	enum UdpMode
	{
		UDP_CLIENT = 0,
		UDP_SERVER = 1,
		UDP_CHILD = 2,
		UDP_SECURE_CLIENT = 3,
	};
	

	enum UdpCloseMode
	{
		UDP_CLOSE_ABORT = 0,
		UDP_CLOSE_COMPLETE = 1,
	};
	
	
	// TCP functions
	uint8_t tcpConfiguration(uint8_t mode, uint16_t tcp_port);
	uint8_t tcpConfiguration(uint8_t mode, char* tcp_remote_address, uint16_t tcp_port);
	uint8_t tcpSetClient(char* tcp_remote_address, uint16_t tcp_port);
	uint8_t tcpSetSecureClient(char* tcp_remote_address, uint16_t tcp_port);
	uint8_t tcpSetServer(uint16_t tcp_port);
	uint8_t tcpConnect(uint8_t tcp_session_id);
	uint8_t tcpWaitClientConnection(uint16_t timeout);	
	uint8_t tcpSend(uint8_t tcp_session_id, char* data);
	uint8_t tcpReceive(uint8_t tcp_session_id);
	uint8_t tcpReceive(uint8_t tcp_session_id, uint16_t timeout);
	uint8_t tcpDeleteConfiguration(uint8_t tcp_session_id);
	uint8_t tcpClose(uint8_t tcp_session_id);
	uint8_t tcpClose(uint8_t tcp_session_id, uint8_t closing_type);
	uint8_t tcpCloseAllSockets();
	uint8_t tcpSendHTTP(uint8_t tcp_session_id, char* data);
	
	//UDP functions
	uint8_t udpConfiguration(uint8_t mode, uint16_t udp_port);
	uint8_t udpSetClient(uint16_t udp_port);
	uint8_t udpSetServer(uint16_t udp_port);
	uint8_t udpSend(uint8_t udp_session_id, char* remote_address, uint16_t remote_port, char* data);
	uint8_t udpReceive(uint8_t udp_session_id, uint16_t timeout);
	uint8_t udpDeleteConfiguration(uint8_t tcp_session_id);
	uint8_t udpClose(uint8_t udp_session_id);
	uint8_t udpClose(uint8_t udp_session_id, uint8_t closing_type);
	uint8_t udpCloseAllSockets();
	
	// HTTP functions
	uint8_t httpConfiguration(char http_server[]);
	uint8_t httpConfiguration(char http_server[], uint16_t http_port);
	uint8_t httpOpenConnection();
	uint8_t httpCloseConnection();
	uint8_t httpGet(char http_path[]);
	uint8_t httpPost(char http_path[], char data[]);
	uint8_t httpPut(char http_path[], char data[]);
	uint8_t httpHead(char http_path[]);
	uint8_t httpDelete(char http_path[]);
	
	// HTTPS functions
	uint8_t httpsConfiguration(char http_server[]);
	uint8_t httpsConfiguration(char http_server[], uint16_t http_port);
	uint8_t httpsOpenConnection();
	uint8_t httpsCloseConnection();
	uint8_t httpsGet(char http_path[]);
	uint8_t httpsPost(char http_path[], char data[]);
	uint8_t httpsPut(char http_path[], char data[]);
	uint8_t httpsHead(char http_path[]);
	uint8_t httpsDelete(char http_path[]);
	uint8_t setCA(uint8_t type, char* cert);
	uint8_t deleteCA(uint8_t type);
	
	// MQTT functions
	uint8_t mqttConfiguration(char mqtt_server[], char client_id[], uint16_t mqtt_port, uint8_t security);
	uint8_t mqttOpenConnection();
	uint8_t mqttCloseConnection();
	uint8_t mqttDeleteSession();
	uint8_t mqttGetTopicData(char topic[], uint8_t qos);
	uint8_t mqttSubscribeTopic(char topic[], uint8_t qos);
	uint8_t mqttUnsubscribeTopic(char topic[]);
	uint8_t mqttPublishTopic(char topic[], uint8_t qos, uint8_t retained, char data[]);
	uint8_t mqttReceive(uint32_t timeout);
	
	// Meshlium functions
	uint8_t sendFrameToMeshlium(	char* protocol,
									char* host,
									uint16_t port,
									uint8_t* data,
									uint16_t length );
	
	//~ uint8_t tcpSetClient(char* tcp_remote_address, uint16_t tcp_port);
	//~ uint8_t tcpSetServer(uint16_t tcp_port);
	//~ uint8_t tcpConnect(uint8_t tcp_session_id);
	//~ uint8_t tcpWaitClientConnection(uint16_t timeout);	
	//~ uint8_t tcpSend(uint8_t tcp_session_id, char* data);
	//~ uint8_t tcpReceive(uint8_t tcp_session_id, uint16_t timeout);
	//~ uint8_t tcpDeleteConfiguration(uint8_t tcp_session_id);
	//~ uint8_t tcpClose(uint8_t tcp_session_id);
	//~ uint8_t tcpClose(uint8_t tcp_session_id, uint8_t closing_type);
	//~ uint8_t tcpCloseAllSockets();


	//~ uint8_t setUDP(char* host, char* remote_port );
	//~ uint8_t setUDP(char* host, char* remote_port, char* local_port);
	
	//~ uint8_t closeDownSockets();
	//~ uint8_t getAllSocketStatus();
	//~ uint8_t getSocketStatus(uint16_t handle);


	// Time Server settings
	//~ uint8_t setTimeServer(char* ip);
	//~ uint8_t setTimeServer(uint8_t n, char* ip);
	//~ uint8_t timeActivationFlag(bool flag);
	//~ uint8_t setGMT(int8_t gmt);
	//~ uint8_t reportStatus8();
	//~ uint8_t setTimeFromWIFI();

	// OTA programming
	//~ uint8_t requestOTA(	char* server,
						//~ char* port,
						//~ char* user,
						//~ char* pass);

	// Roaming mode
	//~ uint8_t roamingMode(uint8_t mode);
	//~ uint8_t setScanInterval(uint8_t n);
	//~ uint8_t setLowThreshold(uint8_t n);
	//~ uint8_t setHighThreshold(uint8_t n);

	// Power settings
	//~ uint8_t setPower(uint8_t power);
	//~ uint8_t getPower();

	// SSL/TLS
	//~ uint8_t setCA(char* ca);
	//~ uint8_t sslHandshake(	uint8_t handle );

	// Firmware
	uint8_t getFirmwareVersion();

	// MAC address
	uint8_t getMAC();
		
	enum QoSModes
	{
		QOS_1,
		QOS_2,
		QOS_3,
	};	
	
	enum RetainedFlag
	{
		NOT_RETAINED,
		RETAINED,
	};	
		
	
	enum ConfigureModes
	{
		MODE_DISABLED = 0, //default
		MODE_STATION = 1,
		MODE_ACCESS_POINT = 2,
		MODE_COMBINED = 3,
	};
	
	enum ConfigureCountry
	{
		COUNTRY_CHINA = 0, // default
		COUNTRY_JAPAN = 1,
		COUNTRY_US = 2,
		COUNTRY_EU = 3,
	};
	
	enum ConfigureAutoconnect
	{
		AUTOCONNECT_DISABLED = 0, // default
		AUTOCONNECT_ENABLED = 1,
	};
	
	enum MQTTSecurity
	{
		MQTT_TLS_DISABLED = 0, // default
		MQTT_TLS_ENABLED = 1,
	};
	
};

extern WaspWIFI_v3 WIFI_PRO_V3;

#endif
