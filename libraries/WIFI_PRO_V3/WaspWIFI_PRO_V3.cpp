/*! \file WaspWIFI_v3.cpp
 *  \brief Library for managing WiFi modules
 *
 *  Copyright (C) 2021 Libelium Comunicaciones Distribuidas S.L.
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
 *  Implementation:	Yuri Carmona
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

#include "WaspWIFI_PRO_V3.h"


/**
 * @brief	It powers on the module and checks communication via UART
 * @param 	socket: SOCKET0 or SOCKET1
 * @return 
 * 	@arg '0' ok
 * 	@arg '1' error
 *
 */
uint8_t	WaspWIFI_v3::ON(uint8_t socket)
{
	uint8_t status;
	int retries;
	int total_attempts = 2;

	// store the UART to be used
	_uart = socket;

	while (total_attempts-- > 0)
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
			#if DEBUG_WIFI_V3 > 0
				PRINT_WIFI_V3(F("wrong socket selection\n"));
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
			status = sendCommand((char*)"AT\r", WIFI_V3_OK, 1000);

			if (status == 1)
			{
				return 0;
			}
			else
			{
				#if DEBUG_WIFI_V3 > 1
					PRINT_WIFI_V3(F("no answer received\n"));
				#endif
			}
			retries--;
			delay(100);
		}
		while (retries > 0);

		/// if problems ==> switch off -> switch on -> and try again
		OFF(socket);
		delay(1000);
	}

	return 1;
}



/**
 * @brief Switch off the module and close the UART
 * @param socket: socket where the module is plugged
 * @return void
 */
void WaspWIFI_v3::OFF(uint8_t socket)
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
 * name: softReset
 * @param
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::softReset()
{
	uint8_t status;
	char command[20];

	// "AT+RST\r"
	strcpy_P(command, (char*)pgm_read_word(&(table_wifi_v3[0])));

	// send command
	status = sendCommand(command, WIFI_V3_OK, WIFI_V3_ERROR, 5000 );

	if (status == 0)
	{
		// timeout
		_errorCode = ERROR_CODE_0;
		return 1;
	}
	else if (status == 1)
	{
		#if DEBUG_WIFI_V3 > 1
			PRINT_WIFI_V3(F("softReset OK\r\n"));
		#endif
	}
	else if (status == 2)
	{
		return 2;
	}

	// wait for READY
	status = waitFor(WIFI_V3_READY, WIFI_V3_ERROR, 5000);

	if (status == 1)
	{		
		#if DEBUG_WIFI_V3 > 1
			PRINT_WIFI_V3(F("softReset READY\r\n"));
		#endif
		return 0;
	}
	else if (status == 2)
	{
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3(F("softReset ERROR\r\n"));
		#endif
	}
	else
	{
		// timeout
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3(F("softReset timeout\n"));
		#endif
		_errorCode = ERROR_CODE_0;
		return 1;
	}

	return 1;
}



/*
 * name: getFirmwareVersion
 *
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::getFirmwareVersion()
{
	char command[20];

	// "AT+CGMR\r"
	strcpy_P( command, (char*)pgm_read_word(&(table_wifi_v3[1])));

	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_ERROR, 500);

	if (status == 1)
	{
		status = parseString(_firmwareVersion, sizeof(_firmwareVersion), WIFI_V3_CR_LF, 1);

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
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0;
		return 1;
	}
}


/*
 * name: getFirmwareVersion
 *
 * @return	'0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::getMAC()
{
	char command[20];

	// "AT+MACADDR?\r"
	strcpy_P( command, (char*)pgm_read_word(&(table_wifi_v3[58])));

	// send command
	uint8_t status = sendCommand(command, WIFI_V3_MAC, WIFI_V3_ERROR, 500);

	if (status == 1)
	{
		waitFor("\"",100);
		status = parseString(_mac, sizeof(_mac), WIFI_V3_CR_LF, 1);

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
		return 1;
	}
	else
	{
		// timeout error
		_errorCode = ERROR_CODE_0;
		return 1;
	}
}



/**
 * @brief Factory default settings
 * @param void
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::resetValues()
{
	char command[20];

	delay(1000);
	
	// "AT&F\r"
	
	strcpy_P(command, (char*)pgm_read_word(&(table_wifi_v3[2])));

	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, 5000);

	if (status == 1)
	{		
		#if DEBUG_WIFI_V3 > 1
			PRINT_WIFI_V3(F("resetValues OK\r\n"));
		#endif		
	}
	else
	{
		return 1;
	}
	
	// wait for READY
	status = waitFor(WIFI_V3_READY, WIFI_V3_ERROR, 5000);

	if (status == 1)
	{		
		#if DEBUG_WIFI_V3 > 1
			PRINT_WIFI_V3(F("resetValues READY\r\n"));
		#endif
		return 0;
	}
	else if (status == 2)
	{
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3(F("resetValues ERROR\r\n"));
		#endif
	}
	else
	{
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3(F("resetValues timeout\r\n"));
		#endif
		_errorCode = ERROR_CODE_0;
		return 2;
	}

	return 3;
	
}



/**
 * @brief Configure the local device to operate as a Wi-Fi station, 
 * 	Wi-Fi access point, or combined station/access point, or display the 
 * 	current configuration settings
 * 
 * @param mode: ConfigureMode enum
 * 
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::configureMode(uint8_t mode)
{
	return configureMode(mode, COUNTRY_CHINA);	
}

/**
 * @brief Configure the local device to operate as a Wi-Fi station, 
 * 	Wi-Fi access point, or combined station/access point, or display the 
 * 	current configuration settings
 * 
 * @param mode: ConfigureMode enum
 * @param country: ConfigureCountry enum
 * 
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::configureMode(uint8_t mode, uint8_t country)
{
	char command[50];

	// "AT+SRWCFG=<mode>[,<country>]\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[3])), mode, country);

	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_ERROR, 3000);

	if (status == 1)
	{		
		#if DEBUG_WIFI_V3 > 1
			PRINT_WIFI_V3(F("configure OK\r\n"));
		#endif
		return 0;
	}
	else
	{
		return 1;
	}	
}




/**
 * @brief Configure or display the connection details the local device 
 * will use to connect to an AP, include the SSID of the AP to connect 
 * to, the password to use, and autoconnect state.
 * 
 * @param ssid: AP SSID
 * @param password: AP credentials
 * @param 
 * 
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::configureStation(char* ssid, char* password)
{
	return configureStation(ssid, password, AUTOCONNECT_DISABLED);
}


/**
 * @brief Configure or display the connection details the local device 
 * will use to connect to an AP, include the SSID of the AP to connect 
 * to, the password to use, and autoconnect state.
 * 
 * @param ssid: AP SSID
 * @param password: AP credentials
 * @param autoconnect: 
 * 
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::configureStation(char* ssid, char* password, uint8_t autoconnect)
{
	char command[100];
	
	// "AT+SRWSTACFG=<ssid>,<password>[,<autoconnect>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[4])), ssid, password, autoconnect);

	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_ERROR, 1000);

	if (status == 1)
	{		
		if (autoconnect)
		{
			softReset();
			
			status = isConnected(10000);
			
			if (status)
			{
				return 0;
			}
		}
		
		return 0;
	}
	else
	{
		return 1;
	}	
}



/**
 * @brief Configure the local device to be used as an Access Point (AP).
 *  
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::configureAp(char* ssid, char* passkey, uint8_t authmode)
{
	return configureAp(ssid, passkey, authmode, 0, 0);
}

uint8_t WaspWIFI_v3::configureAp(char* ssid, char* passkey, uint8_t authmode, uint8_t channel, uint8_t ssid_hidden)
{
	char command[150];

	// "AT+SRWAPCFG=<ssid>,<passkey>,<auth_mode>[,<channel>][,<ssid_hidden]\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[11])), ssid, passkey, authmode, channel, ssid_hidden);

	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_ERROR, 2000);

	if (status == 1)
	{		
		return 0;
	}
	else
	{
		return 1;
	}	
}



/**
 * @brief Connect to AP
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::connect()
{
	char command[50];
	uint8_t error;
	uint8_t attempts = 2;
	
	//~ if (this->isConnected())
	//~ {
		//~ this->disconnect();
	//~ }

	// AT+SRWSTACON=<action>\r
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[5])), 1);

	// send command
	uint8_t status = sendCommand(command, (char*)"+SRWSTASTATUS: ", WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		#if DEBUG_WIFI_V3 > 1
			PRINT_WIFI_V3(F("+SRWSTASTATUS notification received\r\n"));
		#endif

		status = waitFor(WIFI_V3_CR_LF, WIFI_V3_ERROR, 5000);
		
		if (status != 1)
		{
			return 1;
		}

		error = parseSTASTATUS();
		
		// Proceed to wait for IP address if state is connected
		if ((error == 0) && (_status == 1))
		{
			status = waitFor((char*)"+SRWSTAIP: ", WIFI_V3_ERROR, 10000);
			
			if (status == 1)
			{
				#if DEBUG_WIFI_V3 > 1
					PRINT_WIFI_V3(F("+SRWSTAIP notification received\r\n"));
				#endif
			
				status = waitFor((char*)"\r\n", WIFI_V3_ERROR, 100);
				error = parseSTAIP();
				
				if (error == 0)
				{
					#if DEBUG_WIFI_V3 > 1
						PRINT_WIFI_V3(F("IP address assigned\r\n"));
						PRINT_WIFI_V3(F("IP address: "));
						USB.println(_ip);	
						PRINT_WIFI_V3(F("GW address: "));
						USB.println(_gw);	
						PRINT_WIFI_V3(F("Netmask address: "));
						USB.println(_netmask);	
					#endif
					return 0;
				}
				
				return 2;
			}
			else
			{
				return 2;	
			}						
		}
		// Process the reason of disconnect state
		else if ((error == 0) && (_status == 0))
		{
			#if DEBUG_WIFI_V3 > 1
				PRINT_WIFI_V3(F("Disconnect status: "));
				USB.println(_status, DEC);	
				PRINT_WIFI_V3(F("Disconnect reason: "));
				USB.println(_reason, DEC);	
			#endif
			
			return 3;
		}
	}
	else if (status == 2)
	{
		// ERROR
		return 4;
	}
	else
	{
		// no answer
		return 5;
	}
	
	return 6;
}

/**
 * @brief Disconnect to AP
 * 
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::disconnect()
{
	char command[50];

	// AT+SRWSTACON=<action>\r
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[5])), 0);

	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_ERROR, 1000);

	if (status == 1)
	{		
		#if DEBUG_WIFI_V3 > 1
			PRINT_WIFI_V3(F("Disconnect OK\r\n"));
		#endif
		return 0;
	}
	else
	{
		return 1;
	}	
}



/**
 * @brief Function to query the module if it is connected to AP or not
 * 
 * @return 'true' if connected, 'false' if not connected
 */
bool WaspWIFI_v3::isConnected()
{
	return isConnected(20000);
}

/**
 * @brief Function to query the module if it is connected to AP or not
 * 
 * @return 'true' if connected, 'false' if not connected
 */
bool WaspWIFI_v3::isConnected(uint32_t timeout)
{		
	uint16_t attempts = 10;
	uint32_t previous = millis();
	
	while (millis()- previous < timeout)
	{
		if (stationStatus() == true)
		{
			return true;
		}
		delay(2000);
	}
	
	return false;
}


/**
 * 
 */
bool WaspWIFI_v3::stationStatus()
{		
	char command[50];
	uint8_t error;

	// AT+SRWSTACON?\r
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[6])), 1);

	// send command
	uint8_t status = sendCommand(command, (char*)"+SRWSTASTATUS: ", WIFI_V3_ERROR, 1000);

	if (status == 1)
	{
		#if DEBUG_WIFI_V3 > 1
			PRINT_WIFI_V3(F("+SRWSTASTATUS notification received\r\n"));
		#endif

		status = waitFor((char*)"\r\n", WIFI_V3_ERROR, 500);
		
		if (status != 1)
		{
			return false;
		}

		error = parseSTASTATUS();
		
		// CONNECTED
		if ((error == 0) && (_status == 1))
		{
			status = waitFor((char*)"+SRWSTAIP: ", WIFI_V3_ERROR, 1000);
			
			if (status == 1)
			{
				#if DEBUG_WIFI_V3 > 1
					PRINT_WIFI_V3(F("+SRWSTAIP notification received\r\n"));
				#endif
			
				status = waitFor((char*)"\r\n", WIFI_V3_ERROR, 100);
				error = parseSTAIP();
				
				if (error == 0)
				{			
					return true;				
				}
				
				return false;				
			}
			else
			{
				return false;			
			}									
		}
		// DISCONNECTED
		else if ((error == 0) && (_status == 0))
		{
			return false;		
		}		
	}
	else
	{
		return false;
	}
	
	return false;	
}




/**
 * @brief Configure the network IP details (IP address, netmask,
 * gateway) for the station interface.
 * 
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::configureStationSettings(uint8_t dhcp)
{
	return configureStationSettings(dhcp, NULL, NULL, NULL);
}

uint8_t WaspWIFI_v3::configureStationSettings(uint8_t dhcp, char* ip)
{
	return configureStationSettings(dhcp, ip, NULL, NULL);
}

uint8_t WaspWIFI_v3::configureStationSettings(uint8_t dhcp, char* ip, char* nm)
{
	return configureStationSettings(dhcp, ip, nm, NULL);
}

uint8_t WaspWIFI_v3::configureStationSettings(uint8_t dhcp, char* ip, char* nm, char* gw)
{
	char command[200];

	// "AT+SRWSTANETCFG=<dhcp_enabled>[,<ip>[,<netmask>[,<gateway>]]]\r"
	if ((ip == NULL) && (nm == NULL) && (gw == NULL))
	{
		sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[7])), dhcp);
	}
	else if ((ip != NULL) && (nm == NULL) && (gw == NULL))
	{
		sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[8])), dhcp, ip);
	}
	else if ((ip != NULL) && (nm != NULL) && (gw == NULL))
	{
		sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[9])), dhcp, ip, nm);
	}
	else 
	{
		sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[10])), dhcp, ip, nm, gw);
	}
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_ERROR, 1000);

	if (status == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}



/**
 * @brief Configure the local device’s Wi-Fi AP network settings 
 * (network address, and DHCP server settings)
 *  
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::configureApSettings(uint8_t dhcp)
{
	return configureApSettings(dhcp, NULL, NULL, NULL, 0);
}

uint8_t WaspWIFI_v3::configureApSettings(uint8_t dhcp, char* ip, char* ip_start, char* ip_end, uint16_t lease_time)
{
	char command[200];

	// "AT+SRWAPNETCFG=<DHCP_enable>,[,<interface_IP>,<start_IP>,<end_IP>,<lease_time>]\r"
	if ((ip == NULL) || (ip_start == NULL) || (ip_end == NULL))
	{
		sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[12])), dhcp);
	}
	else 
	{
		sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[13])), dhcp, ip, ip_start, ip_end, lease_time);
	}
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 5000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 1;
	}
	else
	{
		return 2;
	}
}



/**
 * @brief Configure the local device’s Wi-Fi AP network settings 
 * (network address, and DHCP server settings)
 *  
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::setDNS(char* dns)
{
	return setDNS(dns, NULL, NULL);
}

uint8_t WaspWIFI_v3::setDNS(char* dns, char* dns_backup)
{
	return setDNS(dns, dns_backup, NULL);
}

uint8_t WaspWIFI_v3::setDNS(char* dns, char* dns_backup, char* dns_fallback)
{
	char command[200];

	// "AT+SRWSTADNSCFG=[<dns_main>][,<dns_backup>][,<dns_fallback>]]\r"
	if (dns_backup == NULL)
	{
		sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[14])), dns);
	}
	else if (dns_fallback == NULL)
	{
		sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[15])), dns, dns_backup);
	}
	else 
	{
		sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[16])), dns, dns_backup, dns_fallback);
	}
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_ERROR, 1000);

	if (status == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}




/**
 * @brief 
 *  
 * @return '0' if ok, '1' if error
 */
uint8_t WaspWIFI_v3::ping(char* ip)
{
	return ping(ip, 3, 1000, 1000);
}

uint8_t WaspWIFI_v3::ping(char* ip, uint32_t count, uint32_t timeout, uint32_t interval)
{
	char command[100];
	uint32_t iterations = count;
	uint8_t error;

	// "AT+KPING=<addr>[,[<count>][,[<timeout>][,<interval>]]]\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[17])), ip, count, timeout, interval);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_ERROR, 1000);

	if (status == 1)
	{
		do
		{		
			status = waitFor((char*)"+KPING: ", (char*)"+KPINGSTAT: ", timeout+5000);
			
			if (status == 1)
			{
				waitFor(WIFI_V3_CR_LF, 100);
	
				error = parseKPING();
				
				if (!error)
				{		
					#if DEBUG_WIFI_V3 > 1
						PRINT_WIFI_V3("PING -> Bytes: ");
						USB.print(this->_pingBytes);
						USB.print("; Time: ");
						USB.println(this->_pingTime);
					#endif
				}
			}
		}
		while ((status == 1) && (iterations-- > 0)); 
		
		if (status == 2)
		{
			waitFor(WIFI_V3_CR_LF, 100);
			
			error = parseKPINGSTAT();			
		}
		
		return 0;
	}
	else
	{
		return 1;
	}
}




/**
 * @brief Set up (configure) a TCP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure a server: AT+KTCPCFG=,1,,5005
 * Configure a CLIENT: AT+KTCPCFG=,0,192.168.100.183,5005
 * 
 */
uint8_t WaspWIFI_v3::tcpConfiguration(uint8_t mode, uint16_t tcp_port)
{
	return tcpConfiguration(mode, NULL, tcp_port);
}

uint8_t WaspWIFI_v3::tcpConfiguration(uint8_t mode, char* tcp_remote_address, uint16_t tcp_port)
{
	char command[100];
	uint8_t error;

	// "AT+KTCPCFG=,<mode>,[<tcp_remote_address>[,<tcp_port>]]\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[18])), mode, tcp_remote_address, tcp_port);
	
	// send command
	uint8_t status = sendCommand(command, (char*)"+KTCPCFG: ", WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		status = waitFor(WIFI_V3_OK, 1000);
		
		if (status != 1)
		{
			return 1;
		}
		
		error = parseUint8(&_tcpSessionId, WIFI_V3_CR_LF);
		
		PRINT_WIFI_V3("TCP session ID: ");
		USB.println(_tcpSessionId, DEC);
		
		if (error == 0)
		{
			return 0;
		}
	
		return 1;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}
}



/**
 * @brief Start a TCP connection by connecting to a remote server 
 * (as a client) or listening to a bound port (as a server).
 * 
 */
uint8_t WaspWIFI_v3::tcpConnect(uint8_t tcp_session_id)
{
	char command[100];
	uint8_t error;

	// "AT+KTCPCNX=<tcp_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[20])), tcp_session_id);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 1;
	}
	else
	{
		return 2;
	}
}


/**
 * @brief Configure and connect a TCP client socket
 * 
 */
uint8_t WaspWIFI_v3::tcpSetClient(char* tcp_remote_address, uint16_t tcp_port)
{
	uint8_t error = tcpConfiguration(TCP_CLIENT, tcp_remote_address, tcp_port);
	
	if (error != 0)
	{
		return 1;
	}
	
	delay(1000);
	
	error = tcpConnect(_tcpSessionId);
	
	if (error != 0)
	{
		return 2;
	}
	
	return 0;
}

/**
 * @brief Configure and connect a TCP client socket
 * 
 */
uint8_t WaspWIFI_v3::tcpSetSecureClient(char* tcp_remote_address, uint16_t tcp_port)
{
	uint8_t error = tcpConfiguration(TCP_SECURE_CLIENT, tcp_remote_address, tcp_port);
	
	if (error != 0)
	{
		return 1;
	}
	
	error = tcpConnect(_tcpSessionId);
	
	if (error != 0)
	{
		return 2;
	}
	
	return 0;
}

/** 
 * @brief Configure and connect a TCP server socket
 * 
 */
uint8_t WaspWIFI_v3::tcpSetServer(uint16_t tcp_port)
{
	uint8_t error = tcpConfiguration(TCP_SERVER, tcp_port);
	
	if (error != 0)
	{
		return 1;
	}
	
	PRINT_WIFI_V3("Open TCP session ID: ");
	USB.println(_tcpSessionId, DEC);
	
	delay(1000);
	
	error = tcpConnect(_tcpSessionId);
	
	if (error != 0)
	{		
		return 2;
	}
	
	return 0;
}


/** 
 * @brief Configure and connect a TCP server socket
 * 
 */
uint8_t WaspWIFI_v3::tcpCloseAllSockets()
{
	uint8_t error = 0;
	
	for (uint8_t i = 1; i<=64; i++)
	{
		error = tcpClose(i);
		error = tcpDeleteConfiguration(i);
	}
	
	return 0;
}



/**
 * @brief Start a TCP connection by connecting to a remote server 
 * (as a client) or listening to a bound port (as a server).
 * 
 */
uint8_t WaspWIFI_v3::tcpWaitClientConnection(uint16_t timeout)
{	
	uint8_t status = waitFor(WIFI_V3_TCP_INCOMING, timeout);

	if (status == 1)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		if (!parseKTCP_SRVREQ())
		{
			return 0;
		}
		return 1;
	}
	else 
	{
		return 2;
	}

}



/**
 * @brief Send data via TCP socket
 * 
 */
uint8_t WaspWIFI_v3::tcpSend(uint8_t tcp_session_id, char* data)
{
	uint8_t error;

	memset((char*)_buffer, 0x00, RADIO_WIFI_V3_UART_SIZE);
	// "AT+KTCPSND=<tcp_session_id>,<data>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[21])), tcp_session_id, data);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, WIFI_V3_TCP_NOTIF, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 1;
	}
	else if (status == 3)
	{
		return 2;
	}
	else if (status == 4)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseKTCP_NOTIF();
		return 3;
	}
	else 
	{
		return 4;
	}	
}



/**
 * @brief Send data via TCP socket
 * 
 */
uint8_t WaspWIFI_v3::tcpSendHTTP(uint8_t tcp_session_id, char* data)
{
	uint8_t error;

	memset((char*)_buffer, 0x00, RADIO_WIFI_V3_UART_SIZE);
	// "AT+KTCPSND=<tcp_session_id>,<data>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[61])), tcp_session_id, data);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		// Send cert to module and exit store mode
		printString(data, _uart);

		// Wait for "HTTP/1.1 " (Server response)
		status = waitFor("HTTP/1.1 ", WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);
		status = waitFor(" ", WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);
		_httpResponseStatus = strtod((char*)_buffer,NULL);
		status = waitFor(WIFI_V3_TCP_NOTIF, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);
		
		if (status == 1)
		{
			parseKTCP_NOTIF();
		}
		else
		{
			return 0;
		}
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}	
}




/**
 * @brief Start a TCP connection by connecting to a remote server 
 * (as a client) or listening to a bound port (as a server).
 * 
 */
uint8_t WaspWIFI_v3::tcpReceive(uint8_t tcp_session_id)
{
	return tcpReceive(tcp_session_id, 10000);
}


/**
 * @brief Start a TCP connection by connecting to a remote server 
 * (as a client) or listening to a bound port (as a server).
 * 
 */
uint8_t WaspWIFI_v3::tcpReceive(uint8_t tcp_session_id, uint16_t timeout)
{
	uint8_t status = waitFor(WIFI_V3_TCP_DATA, timeout);

	if (status == 1)
	{
		if (!parseKTCP_DATA())
		{
			return 0;
		}
		return 1;
	}
	else 
	{
		return 2;
	}
}






/**
 * @brief Close the specified TCP session
 * 
 */
uint8_t WaspWIFI_v3::tcpClose(uint8_t tcp_session_id)
{
	return tcpClose(tcp_session_id, TCP_CLOSE_COMPLETE);
}

uint8_t WaspWIFI_v3::tcpClose(uint8_t tcp_session_id, uint8_t closing_type)
{
	char command[100];

	// "AT+KTCPCLOSE=<tcp_session_id>,<closing_type>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[19])), tcp_session_id, closing_type);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, WIFI_V3_TCP_NOTIF, 10000);

	if (status == 1)
	{		
		return tcpDeleteConfiguration(tcp_session_id);
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else if (status == 3)
	{		
		return 3;
	}
	else if (status == 4)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseKTCP_NOTIF();
		return 4;
	}
	else
	{
		return 5;
	}
}


/**
 * 
 */
uint8_t WaspWIFI_v3::tcpDeleteConfiguration(uint8_t tcp_session_id)
{
	char command[100];
	
	// Delete TCP configuration
	// "AT+KTCPDEL=<tcp_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[22])), tcp_session_id);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{	
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 1;
	}
	else
	{
		return 2;
	}
}




/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
 uint8_t WaspWIFI_v3::httpConfiguration(char http_server[])
{
	return httpConfiguration(http_server, 80);
}
 
uint8_t WaspWIFI_v3::httpConfiguration(char http_server[], uint16_t http_port)
{
	char command[100];
	uint8_t error;

	httpDeleteConfig();

	// "AT+KHTTPCFG=,<mode>,[<http_remote_address>[,<http_port>]]\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[24])), http_server, http_port);
	
	// send command
	uint8_t status = sendCommand(command, (char*)"+KHTTPCFG: ", WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		status = waitFor(WIFI_V3_OK, 1000);
		
		if (status != 1)
		{
			return 1;
		}
		
		error = parseUint8(&_httpSessionId, WIFI_V3_CR_LF);
		
		memcpy(_httpServer, http_server,sizeof(_httpServer));
		_httpPort = http_port;
		
		#if DEBUG_WIFI_V3 >0
			PRINT_WIFI_V3("HTTP session ID: ");
			USB.println(_httpSessionId, DEC);
		#endif
		
		if (error == 0)
		{
			return 0;
		}
	
		return 1;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}
}


/**
 * @brief Delete an HTTP session.
 * 
 * Examples:
 * Configure: AT+KHTTPDEL=1
 * 
 */
uint8_t WaspWIFI_v3::httpDeleteConfig()
{
	char command[100];
	uint8_t error;

	// "AT+KHTTPDEL=<http_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[50])), _httpSessionId);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}
}



/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpGet(char http_path[])
{
	uint8_t error;
	
	error = httpConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	
	error = httpOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	memset(_buffer, 0x00, sizeof(_buffer));
	
	// "AT+KHTTPSGET=,<http_session_id>,<request_url>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[27])), _httpSessionId, http_path);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_HTTPS_ERROR, 10000);
	if (status == 1)
	{
		waitFor(WIFI_V3_HTTP_RES,1000);	
		waitFor(WIFI_V3_CR_LF,500);
		
		char* ptr = strtok((char*)_buffer," ");

		_httpResponseStatus = strtod(ptr,NULL);

		//~ #if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		//~ #endif
		
		httpCloseConnection();
		httpDeleteConfig();
		return 0;
		
	}
	else if (status == 2)
	{
		httpCloseConnection();
		httpDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpCloseConnection();
		httpDeleteConfig();
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpPost(char http_path[], char data[])
{
	uint8_t error;
	
	error = httpConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	error = httpOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	memset(_buffer, 0x00, sizeof(_buffer));
	
	// "AT+KHTTPSGET=,<http_session_id>,<request_url>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[28])), _httpSessionId, http_path);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		printString(data,_uart);
		delay(100);
		printString("+++",_uart);
		
		waitFor(WIFI_V3_HTTP_RES,2000);	
		waitFor(WIFI_V3_CR_LF,500);
		
		char* ptr = strtok((char*)_buffer," ");
		_httpResponseStatus = strtod(ptr,NULL);
		
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		#endif
		
		
		httpCloseConnection();
		httpDeleteConfig();
		return 0;
		
	}
	else if (status == 2)
	{
		httpCloseConnection();
		httpDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpCloseConnection();
		httpDeleteConfig();
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpPut(char http_path[], char data[])
{
	uint8_t error;
	
	error = httpConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	error = httpOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	memset(_buffer, 0x00, sizeof(_buffer));
	
	// "AT+KHTTPSGET=,<http_session_id>,<request_url>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[29])), _httpSessionId, http_path);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		printString(data,_uart);
		delay(100);
		printString("+++",_uart);
		
		waitFor(WIFI_V3_HTTP_RES,2000);	
		waitFor(WIFI_V3_CR_LF,500);
		
		char* ptr = strtok((char*)_buffer," ");
		_httpResponseStatus = strtod(ptr,NULL);
		
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		#endif
		
		
		httpCloseConnection();
		httpDeleteConfig();
		return 0;
		
	}
	else if (status == 2)
	{
		httpCloseConnection();
		httpDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpCloseConnection();
		httpDeleteConfig();
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpHead(char http_path[])
{
	uint8_t error;
	
	error = httpConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	error = httpOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	memset(_buffer, 0x00, sizeof(_buffer));
	
	// "AT+KHTTPSGET=,<http_session_id>,<request_url>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[30])), _httpSessionId, http_path);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);
	if (status == 1)
	{
		waitFor(WIFI_V3_HTTP_RES,2000);	
		waitFor(WIFI_V3_CR_LF,500);
		
		char* ptr = strtok((char*)_buffer," ");
		_httpResponseStatus = strtod(ptr,NULL);
		
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		#endif

		httpCloseConnection();
		httpDeleteConfig();
		return 0;		
	}
	else if (status == 2)
	{
		httpCloseConnection();
		httpDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpCloseConnection();
		httpDeleteConfig();
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpDelete(char http_path[])
{
	char command[100];
	uint8_t error;
	
	error = httpConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	
	error = httpOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	// "AT+KHTTPDELETE=,<http_session_id>,<request_url>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[31])), _httpSessionId, http_path);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		waitFor(WIFI_V3_HTTP_RES,2000);	
		waitFor(WIFI_V3_CR_LF,500);
		
		char* ptr = strtok((char*)_buffer," ");
		_httpResponseStatus = strtod(ptr,NULL);
		
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		#endif
		
		
		httpCloseConnection();
		httpDeleteConfig();
		return 0;
		
	}
	else if (status == 2)
	{
		httpCloseConnection();
		httpDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpCloseConnection();
		httpDeleteConfig();
		return 3;
	}
}



/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpOpenConnection()
{
	
	char command[50];
	uint8_t error;

	// "AT+KHTTPCNX=<http_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[25])), _httpSessionId);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseHTTPERROR();
		return 3;
	}	
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpCloseConnection()
{
	
	char command[50];
	uint8_t error;

	// "AT+KHTTPCNX=<http_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[26])), _httpSessionId);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		status = waitFor(WIFI_V3_OK, 1000);
		
		if (status != 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}

	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}	
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KCERTSTORE=<type>\
 * type = 0 -> Root Certificate
 * type = 1 -> Local Certificate
 * 
 */
uint8_t WaspWIFI_v3::setCA(uint8_t type, char* cert)
{
	
	char command[50];
	uint8_t error;
	
	deleteCA(type);

	// "AT+KCERTSTORE=<type>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[32])), type);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		// Send cert to module and exit store mode
		printString(cert, _uart);
		delay(100);
		printString("+++", _uart);
		
		// Wait for "OK"
		status = waitFor(WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 1000);
	
		if (status != 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}

	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}	
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * @return 0 
 * Examples:
 * Configure: AT+KCERTDELETE=<type>\
 * type = 0 -> Root Certificate
 * type = 1 -> Local Certificate
 * 
 */
uint8_t WaspWIFI_v3::deleteCA(uint8_t type)
{
	
	char command[50];

	// "AT+KCERTSTORE=<type>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[33])), type);
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 1000);
	
	if(status != 1)
	{
		return 1;
	}
	
	return 0;
}



/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
 uint8_t WaspWIFI_v3::httpsConfiguration(char http_server[])
{
	return httpConfiguration(http_server, 80);
}
 
uint8_t WaspWIFI_v3::httpsConfiguration(char http_server[], uint16_t http_port)
{
	char command[100];
	uint8_t error;

	httpsDeleteConfig();

	// "AT+KHTTPCFG=,<mode>,[<http_remote_address>[,<http_port>]]\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[34])), http_server, http_port);
	
	// send command
	uint8_t status = sendCommand(command, (char*)"+KHTTPSCFG: ", WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		status = waitFor(WIFI_V3_OK, 1000);
		
		if (status != 1)
		{
			return 1;
		}
		
		error = parseUint8(&_httpSessionId, WIFI_V3_CR_LF);
		
		#if DEBUG_WIFI_V3 >0
			PRINT_WIFI_V3("HTTP session ID: ");
			USB.println(_httpSessionId, DEC);
		#endif
		
		memcpy(_httpServer, http_server,sizeof(_httpServer));
		_httpPort = http_port;
		
		if (error == 0)
		{
			return 0;
		}
	
		return 1;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpsGet(char http_path[])
{
	uint8_t error;
	
	error = httpsConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	error = httpsOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	memset(_buffer, 0x00, sizeof(_buffer));
	
	// "AT+KHTTPSGET=,<http_session_id>,<request_url>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[37])), _httpSessionId, http_path);
	USB.println("Enviando");
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		waitFor(WIFI_V3_HTTP_RES,1000);	
		waitFor(WIFI_V3_CR_LF,500);
		char* ptr = strtok((char*)_buffer," ");

		_httpResponseStatus = strtod(ptr,NULL);

		//~ #if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		//~ #endif
		
		
		httpsCloseConnection();
		httpsDeleteConfig();
		return 0;
		
	}
	else if (status == 2)
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpsPost(char http_path[], char data[])
{
	uint8_t error;
	
	error = httpsConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	
	error = httpsOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	memset(_buffer, 0x00, sizeof(_buffer));
	
	// "AT+KHTTPSGET=,<http_session_id>,<request_url>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[38])), _httpSessionId, http_path);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);
	if (status == 1)
	{
		printString(data,_uart);
		delay(100);
		printString("+++",_uart);
		
		waitFor(WIFI_V3_HTTP_RES,2000);	
		waitFor(WIFI_V3_CR_LF,500);
		
		char* ptr = strtok((char*)_buffer," ");
		_httpResponseStatus = strtod(ptr,NULL);
		
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		#endif
		
		
		httpsCloseConnection();
		httpsDeleteConfig();
		return 0;
		
	}
	else if (status == 2)
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpsPut(char http_path[], char data[])
{
	char command[100];
	uint8_t error;
	
	error = httpsConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	
	error = httpsOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	memset(_buffer, 0x00, sizeof(_buffer));
	
	// "AT+KHTTPSGET=,<http_session_id>,<request_url>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[39])), _httpSessionId, http_path);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		printString(data,_uart);
		delay(100);
		printString("+++",_uart);
		
		waitFor(WIFI_V3_HTTP_RES,2000);	
		waitFor(WIFI_V3_CR_LF,500);
		
		char* ptr = strtok((char*)_buffer," ");
		_httpResponseStatus = strtod(ptr,NULL);
		
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		#endif
		
		
		httpsCloseConnection();
		httpsDeleteConfig();
		return 0;
		
	}
	else if (status == 2)
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpsHead(char http_path[])
{
	uint8_t error;
	
	error = httpsConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	
	error = httpOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	memset(_buffer, 0x00, sizeof(_buffer));
	
	// "AT+KHTTPSGET=,<http_session_id>,<request_url>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[40])), _httpSessionId, http_path);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		waitFor("HTTP/1.1 ",2000);	
		waitFor(" OK",500);
		
		char* ptr = strtok((char*)_buffer," ");
		_httpResponseStatus = strtod(ptr,NULL);
		
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		#endif
		
		
		httpsCloseConnection();
		httpsDeleteConfig();
		return 0;
		
	}
	else if (status == 2)
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpsDelete(char http_path[])
{
	uint8_t error;
	
	error = httpsConfiguration(_httpServer, _httpPort);
	if (error != 0)
	{
		return 1;
	}
	
	
	error = httpsOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	memset(_buffer, 0x00, sizeof(_buffer));
	
	// "AT+KHTTPSGET=,<http_session_id>,<request_url>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[41])), _httpSessionId, http_path);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_CONNECT, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{		
		waitFor("HTTP/1.1 ",2000);	
		waitFor(" OK",500);
		
		char* ptr = strtok((char*)_buffer," ");
		_httpResponseStatus = strtod(ptr,NULL);
		
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_httpResponseStatus);
		#endif
		
		delay(1000);
		
		httpsCloseConnection();
		httpsDeleteConfig();
		return 0;
		
	}
	else if (status == 2)
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		httpsCloseConnection();
		httpsDeleteConfig();
		return 3;
	}
}



/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpsOpenConnection()
{
	
	char command[50];
	uint8_t error;

	// "AT+KHTTPCNX=<http_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[35])), _httpSessionId);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_HTTPS_ERROR, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseHTTPERROR();
		return 3;
	}	
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::httpsCloseConnection()
{
	
	char command[50];
	uint8_t error;

	// "AT+KHTTPSCNX=<http_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[36])), _httpSessionId);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		status = waitFor(WIFI_V3_OK, 1000);
		
		if (status != 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}

	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}	
}


/**
 * @brief Delete an HTTP session.
 * 
 * Examples:
 * Configure: AT+KHTTPDEL=1
 * 
 */
uint8_t WaspWIFI_v3::httpsDeleteConfig()
{
	char command[30];
	uint8_t error;

	memset(command, 0x00, sizeof(command));

	// "AT+KHTTPSDEL=<https_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[51])), _httpSessionId);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}
}




/**
 * @brief Set up (configure) a MQTT session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::mqttConfiguration(char mqtt_server[], char client_id[], uint16_t mqtt_port, uint8_t security)
{
	char command[100];
	uint8_t error;

	mqttDeleteSession();

	// "AT+KHTTPCFG=,<security>,<mqtt_server>,<mqtt_port>,4,<client_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[42])), security, mqtt_server, mqtt_port, client_id);
	
	// send command
	uint8_t status = sendCommand(command, (char*)"+KMQTTCFG: ", WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		status = waitFor(WIFI_V3_OK, 1000);
		
		if (status != 1)
		{
			return 1;
		}
		
		error = parseUint8(&_mqttSessionId, WIFI_V3_CR_LF);
		
		#if DEBUG_WIFI_V3 >0
			PRINT_WIFI_V3("HTTP session ID: ");
			USB.println(_httpSessionId, DEC);
		#endif
		
		memcpy(_mqttServer, mqtt_server,sizeof(_mqttServer));
		memcpy(_mqttClientID, client_id,sizeof(_mqttClientID));
		_mqttPort = mqtt_port;
		_mqttSec = security;
		
		if (error == 0)
		{
			return 0;
		}
	
		return 1;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}
}

/**
 * @brief Susbscribe to an MQTT topic and display data.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::mqttGetTopicData(char topic[], uint8_t qos)
{
	char command[100];
	uint8_t error;
	
	error = mqttConfiguration(_mqttServer, _mqttClientID, _mqttPort, _mqttSec);
	
	if (error != 0)
	{
		return 1;
	}
	
	error = mqttOpenConnection();
	
	if (error != 0)
	{
		return 1;
	}
	
	memset(_mqtt_topic_data, 0x00, sizeof(_mqtt_topic_data));
	mqttUnsubscribeTopic(topic);
	delay(500);
	// "AT+KMQTTSUB=<mqtt_session_id>,<topic>,<qos>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[48])), _mqttSessionId, topic, qos);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		// "AT+KMQTTDATA=<mqtt_session_id>,<topic>,"
		memset(command,0x00,sizeof(command));
		sprintf(command, "%s%u,\"%s\",\"", WIFI_V3_MQTT_DATA, _mqttSessionId, topic);
		waitFor(command,1000);	
		waitFor(WIFI_V3_CR_LF,1000);
		
		// Extract data from response
		char* ptr = strtok((char*)_buffer,"\"");
		memcpy(_mqtt_topic_data, ptr, sizeof(_mqtt_topic_data));

		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_mqtt_topic_data);
		#endif
		
		mqttUnsubscribeTopic(topic);
		
		mqttCloseConnection();
		
		mqttDeleteSession();
		return 0;
		
	}
	else if (status == 2)
	{
		mqttCloseConnection();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		mqttCloseConnection();
		return 3;
	}
}


/**
 * @brief Susbscribe to an MQTT topic and display data.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::mqttSubscribeTopic(char topic[], uint8_t qos)
{
	char command[100];
	uint8_t error;
	
	error = mqttConfiguration(_mqttServer, _mqttClientID, _mqttPort, _mqttSec);
	
	if (error != 0)
	{
		return 1;
	}
	
	error = mqttOpenConnection();
	
	if (error != 0)
	{
		return 1;
	}
	
	memset(_mqtt_topic_data, 0x00, sizeof(_mqtt_topic_data));
	mqttUnsubscribeTopic(topic);
	delay(1000);
	// "AT+KMQTTSUB=<mqtt_session_id>,<topic>,<qos>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[48])), _mqttSessionId, topic, qos);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		// "+KMQTTDATA=<mqtt_session_id>,<topic>,"
		memset(command,0x00,sizeof(command));
		sprintf(command, "%s%u,\"%s\",\"", WIFI_V3_MQTT_DATA, _mqttSessionId, topic);
		waitFor(command,1000);	
		waitFor(WIFI_V3_CR_LF,1000);
		
		// Extract data from response
		char* ptr = strtok((char*)_buffer,"\"");
		memcpy(_mqtt_topic_data, ptr, sizeof(_mqtt_topic_data));

		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3("Response status: ");
			USB.println(_mqtt_topic_data);
		#endif
		
		return 0;
		
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		mqttCloseConnection();
		mqttDeleteSession();
		return 2;
	}
	else
	{
		mqttCloseConnection();
		mqttDeleteSession();
		return 3;
	}
}

/**
 * @brief Susbscribe to an MQTT topic and display data.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::mqttUnsubscribeTopic(char topic[])
{
	char command[100];
	uint8_t error;

	// "AT+KMQTTUNSUB=<mqtt_session_id>,<topic>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[49])), _mqttSessionId, topic);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}
}


/**
 * @brief Susbscribe to an MQTT topic and display data.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::mqttPublishTopic(char topic[], uint8_t qos, uint8_t retained, char data[])
{
	char command[100];
	uint8_t error;
	
	error = mqttConfiguration(_mqttServer, _mqttClientID, _mqttPort, _mqttSec);
	if (error != 0)
	{
		return 1;
	}
	
	error = mqttOpenConnection();
	if (error != 0)
	{
		return 1;
	}
	
	delay(500);
	// "AT+KMQTTPUB=<mqtt_session_id>,<topic>,<qos>,<retained>,<data>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[46])), _mqttSessionId, topic, qos, retained, data);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		if (qos != QOS_1)
		{
			parseKMQTT_IND();
			if (_mqttInd == 4)
			{
				mqttCloseConnection();
				mqttDeleteSession();
				return 0;
			}
			else 
			{
				mqttCloseConnection();
				mqttDeleteSession();
				return 1;
			}			
		}
		mqttCloseConnection();
		mqttDeleteSession();
		return 0;				
	}
	else if (status == 2)
	{
		mqttCloseConnection();
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		mqttCloseConnection();
		return 3;
	}
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::mqttOpenConnection()
{
	
	char command[50];
	uint8_t error;
	
	mqttCloseConnection();

	delay(1000);

	// "AT+KMQTTCNX=<mqtt_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[44])), _mqttSessionId);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);
	if (status == 1)
	{
		waitFor(WIFI_V3_MQTT_IND,1000);
		
		parseKMQTT_IND();
		
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}	
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::mqttCloseConnection()
{
	
	char command[50];
	uint8_t error;

	// "AT+KMQTTCLOSE=<mqtt_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[43])), _mqttSessionId);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}		
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::mqttDeleteSession()
{
	
	char command[50];
	uint8_t error;

	// "AT+KMQTTDELETE=<mqtt_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[45])), _mqttSessionId);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}		
}


/**
 * @brief Set up (configure) a HTTP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure: AT+KHTTPCFG=,1,,5005
 * 
 */
uint8_t WaspWIFI_v3::mqttReceive(uint32_t timeout)
{	
	// send command
	uint8_t status = waitFor(WIFI_V3_MQTT_DATA, WIFI_V3_STATUS, timeout);

	if (status == 1)
	{
		waitFor(WIFI_V3_CR_LF);
		
		char* ptr = strtok((char*)_buffer,"\",");
		ptr = strtok(NULL,"\",");
		ptr = strtok(NULL,"\",");
		
		memcpy(_mqtt_topic_data, ptr, sizeof(_mqtt_topic_data));

		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}		
}



/**
 * @brief Set up (configure) a TCP session, or display the current configuration of all sessions.
 * 
 * Examples:
 * Configure a server: AT+KTCPCFG=,1,,5005
 * Configure a CLIENT: AT+KTCPCFG=,0,192.168.100.183,5005
 * 
 */
uint8_t WaspWIFI_v3::udpConfiguration(uint8_t mode, uint16_t udp_port)
{
	char command[100];
	uint8_t error;

	// "AT+KUDPCFG=<cnx_cnf>,<mode>[,<udp_port>]]\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[52])), mode, udp_port);
	
	// send command
	uint8_t status = sendCommand(command, (char*)"+KUDPCFG: ", WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{
		status = waitFor(WIFI_V3_OK, 1000);
		
		if (status != 1)
		{
			return 1;
		}
		
		delay(1000);
		
		error = parseUint8(&_udpSessionId, WIFI_V3_CR_LF);

		if (error == 0)
		{
			return 0;
		}
	
		return 1;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else
	{
		return 3;
	}
}


/**
 * @brief Configure and connect a UDP client socket
 * 
 */
uint8_t WaspWIFI_v3::udpSetClient(uint16_t udp_port)
{
	uint8_t error = udpConfiguration(UDP_CLIENT, udp_port);
	
	if (error != 0)
	{
		return 1;
	}
		
	return 0;
}

/** 
 * @brief Configure and connect a UDP server socket
 * 
 */
uint8_t WaspWIFI_v3::udpSetServer(uint16_t udp_port)
{
	uint8_t error = udpConfiguration(UDP_SERVER, udp_port);
	
	if (error != 0)
	{
		return 1;
	}

	return 0;
}


/**
 * @brief Send data via TCP socket
 * 
 */
uint8_t WaspWIFI_v3::udpSend(uint8_t udp_session_id, char* remote_address, uint16_t remote_port, char* data)
{
	uint8_t error;

	memset((char*)_buffer, 0x00, RADIO_WIFI_V3_UART_SIZE);
	// "AT+KUDPSND=<udp_session_id>,<data>\r"
	sprintf_P((char*)_buffer, (char*)pgm_read_word(&(table_wifi_v3[55])), udp_session_id, remote_address, remote_port, data);
	
	// send command
	uint8_t status = sendCommand((char*)_buffer, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, WIFI_V3_TCP_NOTIF, 10000);

	if (status == 1)
	{
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 1;
	}
	else if (status == 3)
	{
		return 2;
	}
	else if (status == 4)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseKUDP_NOTIF();
		return 3;
	}
	else 
	{
		return 4;
	}
}




/**
 * @brief Start a TCP connection by connecting to a remote server 
 * (as a client) or listening to a bound port (as a server).
 * 
 */
uint8_t WaspWIFI_v3::udpReceive(uint8_t udp_session_id, uint16_t timeout)
{
	char response[25];
	memset (response, 0x00, sizeof(response));
	
	snprintf(response,sizeof(response),"%s%u,",WIFI_V3_UDP_DATA,_udpSessionId);
	
	uint8_t status = waitFor(response, timeout);

	if (status == 1)
	{
		if (!parseKUDP_DATA())
		{
			return 0;
		}
		return 1;
	}
	else 
	{
		return 2;
	}
}






/**
 * @brief Close the specified TCP session
 * 
 */
uint8_t WaspWIFI_v3::udpClose(uint8_t udp_session_id)
{
	char command[100];

	// "AT+KUDPCLOSE=<udp_session_id>,<closing_type>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[53])), udp_session_id);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, WIFI_V3_UDP_NOTIF, 10000);

	if (status == 1)
	{		
		return udpDeleteConfiguration(udp_session_id);
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 2;
	}
	else if (status == 3)
	{		
		return 3;
	}
	else if (status == 4)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseKUDP_NOTIF();
		return 4;
	}
	else
	{
		return 5;
	}
}

/** 
 * @brief Configure and connect a TCP server socket
 * 
 */
uint8_t WaspWIFI_v3::udpCloseAllSockets()
{
	uint8_t error = 0;
	
	for (uint8_t i = 1; i<=64; i++)
	{
		error = udpClose(i);
		error = udpDeleteConfiguration(i);
	}
	
	return 0;
}



/**
 * 
 */
uint8_t WaspWIFI_v3::udpDeleteConfiguration(uint8_t udp_session_id)
{
	char command[100];
	
	// Delete TCP configuration
	// "AT+KUDPDEL=<udp_session_id>\r"
	sprintf_P(command, (char*)pgm_read_word(&(table_wifi_v3[56])), udp_session_id);
	
	// send command
	uint8_t status = sendCommand(command, WIFI_V3_OK, WIFI_V3_CME_ERROR, WIFI_V3_ERROR, 10000);

	if (status == 1)
	{	
		return 0;
	}
	else if (status == 2)
	{
		waitFor(WIFI_V3_CR_LF, 500);
		parseCMEERROR();
		return 1;
	}
	else
	{
		return 2;
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
uint8_t WaspWIFI_v3::sendFrameToMeshlium(	char* protocol,
											char* host,
											uint16_t port,
											uint8_t* data,
											uint16_t length )
{
	char data_buffer[250];
	char aux[3];
	memset( aux, 0x00, sizeof(aux));
	memset(data_buffer, 0x00, sizeof(data_buffer));
	
	strcpy_P(data_buffer, (char*)pgm_read_word(&(table_wifi_v3[59])));
	
	for (uint16_t i=0 ; i<length; i++)
	{
		Utils.hex2str( &data[i], aux, 1);
		strncat( data_buffer, aux, 2 );
	}
	strncat( data_buffer, 0x00, 1 );
	
	uint8_t error;
	
	if (!strcmp("http", protocol))
	{
		error = httpConfiguration(host, port);
		if (error != 0)
		{
			
			return 1;
		}
		
				
		error = httpGet(data_buffer);
		if (error != 0)
		{
			return 1;
		}

		return 0;
		
	}
	if (!strcmp("https", protocol))
	{
		error = httpsConfiguration(host, port);
		if (error != 0)
		{
			#if DEBUG_WIFI_V3 >0
				PRINT_WIFI_V3("HTTP session ID: ");
				USB.println(_httpSessionId, DEC);
			#endif
			return 1;
		}
			
		error = httpsGet(data_buffer);
		if (error != 0)
		{
			#if DEBUG_WIFI_V3 >0
				PRINT_WIFI_V3("HTTP session ID: ");
				USB.println(_httpSessionId, DEC);
			#endif
			return 1;
		}
		
		return 0;
	}
	
	return 1;
}


/**
 * @brief  Get number of devices connected to the local AP
 *
 * @return 	'i' number of devices connected
 *
 */
int8_t WaspWIFI_v3::getConnectedDevices()
{
	char command[20];

	// "AT+SRWAPSTA?\r"
	strcpy_P( command, (char*)pgm_read_word(&(table_wifi_v3[60])));

	// send command
	uint8_t status = sendCommand(command, WIFI_V3_SRWAPSTA, WIFI_V3_OK, WIFI_V3_ERROR, 500);

	if (status == 1)
	{
		parseSRWAPSTA();
		if (status == 0)
		{
			return 0;
		}
	}
	else if (status == 2)
	{
		for (uint8_t i = 0; i<10; i++)
		{
			_apClients = 0;
			memset(client[i].mac, 0x00, sizeof(client[i].mac));
			memset(client[i].ip, 0x00, sizeof(client[i].ip));
		}
		return 0;
	}
}




////////////////////////////////////////////////////////////////////////

/**
 * @brief Private function to parse +SRWSTASTATUS response
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseSTASTATUS()
{
	// process a response format like:
	// (status = 0) +SRWSTASTATUS: <status>,<reason>
	// (status = 1) +SRWSTASTATUS: <status>,<ssid>,<bssid>,<channel>,<authmode>
	
	
	// In _buffer we have "<status>,<reason>" or "<status>,<ssid>,<bssid>,<channel>,<authmode>"
	// so lets parse <status> in first place
	
	char* ptr;
	uint32_t aux;
	
	ptr = strtok( (char*)_buffer, ",\r\n");
	
	if (ptr != NULL)
	{
		aux = strtoul(ptr, NULL, 10);
		_status = (uint8_t)aux;
		
		#if DEBUG_WIFI_V3 > 1
			PRINT_WIFI_V3(F("<status>: "));
			USB.println(_status, DEC);
		#endif
	}
	else
	{
		return 1;
	}
	
	// Process <reason>
	if (_status == STATUS_DISCONNECTED)
	{
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3(F("STATUS_DISCONNECTED\r\n"));
		#endif
		
		ptr = strtok(NULL, ",\r\n");
		
		if (ptr != NULL)
		{
			aux = strtoul(ptr, NULL, 10);
			_reason = (uint8_t)aux;
			
			#if DEBUG_WIFI_V3 > 0
				PRINT_WIFI_V3(F("Status failed. Reason: "));
				USB.println(_reason, DEC);
			#endif
			
			return 0;
		}
		else
		{
			return 2;
		}
	}
	
	// Process <ssid>,<bssid>,<channel>,<authmode>	
	if (_status == STATUS_CONNECTED)
	{
		#if DEBUG_WIFI_V3 > 0
			PRINT_WIFI_V3(F("STATUS_CONNECTED\r\n"));
		#endif
		
		ptr = strtok(NULL, ",\"");
		if (ptr == NULL)
		{
			return 0;
		}
		memcpy(_essid, ptr, sizeof(_essid));
		
		ptr = strtok(NULL, ",\"");
		if (ptr == NULL)
		{
			return 0;
		}
		memcpy(_bssid, ptr, sizeof(_bssid));
		
		ptr = strtok(NULL, ",\"");
		if (ptr == NULL)
		{
			return 0;
		}
		_channel = atoi(ptr);
		
		ptr = strtok(NULL, ",\"");
		if (ptr == NULL)
		{
			return 0;
		}
		_authmode = atoi(ptr);
		
		ptr = strtok(NULL, ",\"");
		if (ptr == NULL)
		{
			return 0;
		}
		_power = atoi(ptr);
		
		return 0;
	}
	
	return 3;	
}



/**
 * @brief Private function to parse +SRWSTAIP notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseSTAIP()
{
	// process a response format like:
	// +SRWSTAIP: <ip>,<netmask>,<gateway>	
	
	memset(_ip, 0x00, sizeof(_ip));
	memset(_netmask, 0x00, sizeof(_netmask));
	memset(_gw, 0x00, sizeof(_gw));
			
	char* ptr;
	
	ptr = strtok((char*)_buffer, (char*)"\",\r\n");
	
	for (uint8_t i = 0; i < 3; i++)
	{	
		if (ptr == NULL)
		{
			return 1;
		}
		
		switch (i)
		{
			case 0: 
				strncpy(_ip, ptr, sizeof(_ip)-1);
				break;
				
			case 1:
				strncpy(_netmask, ptr, sizeof(_netmask)-1);
				break;
				
			case 2:
				strncpy(_gw, ptr, sizeof(_gw)-1);
				break;
		
			default:
				break;
		}
		
		// iterate to next element
		ptr = strtok(NULL, (char*)"\",\r\n");
	}
	
	return 0;
}







/**
 * @brief Private function to parse +KPING notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseKPING()
{
	// process a response format like:
	// +KPING: <bytes>,<time>
	_pingBytes = 0;
	_pingTime = 0;
	
	char* ptr;
	
	ptr = strtok((char*)_buffer, (char*)",\r\n");
	
	for (uint8_t i = 0; i < 2; i++)
	{
		if (ptr == NULL)
		{
			return 1;
		}
		
		switch (i)
		{
			case 0: 
				_pingBytes = strtoul(ptr, NULL, 10);
				break;
				
			case 1:
				_pingTime = strtoul(ptr, NULL, 10);
				break;
		
			default:
				break;
		}
		
		// iterate to next element
		ptr = strtok(NULL, (char*)",\r\n");
	}
	
	return 0;
}



/**
 * @brief Private function to parse +KPINGSTAT notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseKPINGSTAT()
{
	// process a response format like:
	// +KPINGSTAT: <sent>,<received>,<lost>,<time>,<min_time>,<max_time>
	_pingSent = 0;
	_pingReceived = 0;
	_pingLost = 0;
	_pingTime = 0;
	_pingMinTime = 0;
	_pingMaxTime = 0;
	
	char* ptr;
	
	ptr = strtok((char*)_buffer, (char*)",\r\n");
	
	for (uint8_t i = 0; i < 6; i++)
	{
		if (ptr == NULL)
		{
			return 1;
		}
		
		switch (i)
		{
			case 0: 
				_pingSent = strtoul(ptr, NULL, 10);
				break;
				
			case 1:
				_pingReceived = strtoul(ptr, NULL, 10);
				break;
				
			case 2:
				_pingLost = strtoul(ptr, NULL, 10);
				break;
				
			case 3:
				_pingTime = strtoul(ptr, NULL, 10);
				break;
				
			case 4:
				_pingMinTime = strtoul(ptr, NULL, 10);
				break;
				
			case 5:
				_pingMaxTime = strtoul(ptr, NULL, 10);
				break;
		
			default:
				break;
		}
		
		// iterate to next element
		ptr = strtok(NULL, (char*)",\r\n");
	}
	
	return 0;
}




/**
 * @brief Private function to parse +KTCP_NOTIF notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseKTCP_NOTIF()
{
	// process a response format like:
	// +KTCP_NOTIF: <tcp_session_id>, <tcp_notif>
	_tcpNotifSessionId = 0;
	_tcpNotifCode = 0;
	
	char* ptr;
	waitFor(WIFI_V3_CR_LF);
	ptr = strtok((char*)_buffer, (char*)",\r\n");

	for (uint8_t i = 0; i < 2; i++)
	{
		if (ptr == NULL)
		{
			return 1;
		}
		
		switch (i)
		{
			case 0: 
				_tcpNotifSessionId = strtoul(ptr, NULL, 10);
				break;
				
			case 1:
				_tcpNotifCode = strtoul(ptr, NULL, 10);
				break;
		
			default:
				break;
		}
		
		// iterate to next element
		ptr = strtok(NULL, (char*)",\r\n");
	}
	
	//~ PRINT_WIFI_V3("TCP Nofiticacion --> Session ID: ");
	//~ USB.print(_tcpNotifSessionId,DEC);
	//~ USB.print("Code: ");
	//~ USB.println(_tcpNotifCode,DEC);
	
	return 0;
}



/**
 * @brief Private function to parse +KTCP_NOTIF notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseCMEERROR()
{
	// process a response format like:
	// +CME ERROR: <cme_error>
	_cmeerror = 0;
	
	char* ptr;
	
	ptr = strtok((char*)_buffer, (char*)": ,\r\n");
	
	for (uint8_t i = 0; i < 2; i++)
	{
		if (ptr == NULL)
		{
			return 1;
		}
		
		switch (i)
		{
			case 0: 
				_cmeerror = strtoul(ptr, NULL, 10);
				break;
				
			default:
				break;
		}
		
		// iterate to next element
		ptr = strtok(NULL, (char*)",\r\n");
	}
	
	PRINT_WIFI_V3("CME ERROR: ");
	USB.println(_cmeerror);
	
	return 0;
}


/**
 * @brief Private function to parse +KTCP_NOTIF notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseHTTPERROR()
{
	// process a response format like:
	// +CME ERROR: <cme_error>
	_httpserror = 0;
		
	char* ptr = strtok((char*)_buffer, ",");
	if (ptr == NULL)
	{
		return 1;
	}

	ptr = strtok(NULL, WIFI_V3_CR_LF);
	_httpserror = atoi(ptr);
	
	PRINT_WIFI_V3("HTTPS ERROR: ");
	USB.println(_httpserror, DEC);
	
	return 0;
}


/**
 * @brief Private function to parse +KTCP_NOTIF notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseKMQTT_IND()
{
	// process a response format like:
	// +CME ERROR: <cme_error>
	_mqttInd = 0;
	
	waitFor(WIFI_V3_MQTT_IND,12000);
	waitFor(WIFI_V3_CR_LF,100);

	char* ptr;
	ptr = strtok((char*)_buffer, ",");
	ptr = strtok(NULL, ",\r\n");
	_mqttInd = strtoul(ptr, NULL, 10);

	return 0;
}





/**
 * @brief Private function to parse +KTCP_DATA notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseKTCP_DATA()
{
	// process a response format like:
	// +KTCP_DATA: <tcp_session_id>,<ndata_available>,<data>
	_tcpDataSessionId = 0;
	_tcpDataAvailable = 0;
	uint8_t status = 0;
	
	// 1. tcp_session_id
	status = waitFor((char*)",", 100);
	
	if (status != 1)
	{
		return 1;
	}
	
	_buffer[_length-1] = 0x00;
	_tcpDataSessionId = strtoul((char*)_buffer, NULL, 10);
	
	
	// 2. ndata_available
	status = waitFor((char*)",", 100);
	
	if (status != 1)
	{
		return 2;
	}
	
	_buffer[_length-1] = 0x00;
	_tcpDataAvailable = strtoul((char*)_buffer, NULL, 10);

	// 3. data
	readBuffer(_tcpDataAvailable);

	return 0;
}




/**
 * @brief Private function to parse +KTCP_SRVREQ notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseKTCP_SRVREQ()
{
	// process a response format like:
	// +KTCP_SRVREQ: <tcp_session_id>,<tcp_client_session_id>,<client_ip>,<client_port>
	_tcpSessionId = 0;
	_tcpClientSessionId = 0;
	memset(_tcpClientIp, 0x00, sizeof(_tcpClientIp));
	_tcpClientPort = 0;
		
	char* ptr;
	uint16_t length;
	
	ptr = strtok((char*)_buffer, (char*)"\",\r\n");
	
	for (uint8_t i = 0; i < 4; i++)
	{
		if (ptr == NULL)
		{
			return 1;
		}
		
		switch (i)
		{
			case 0: 
				_tcpSessionId = strtoul(ptr, NULL, 10);
				break;
				
			case 1: 
				_tcpClientSessionId = strtoul(ptr, NULL, 10);
				break;
				
			case 2: 
				memcpy(_tcpClientIp, ptr, sizeof(_tcpClientIp)-1);
				length = strlen(ptr);
				if (length < sizeof(_tcpClientIp)-1);
				_tcpClientIp[length] = 0x00;
				break;
				
			case 3: 
				_tcpClientPort = strtoul(ptr, NULL, 10);
				break;
				
			default:
				break;
		}
		
		// iterate to next element
		ptr = strtok(NULL, (char*)"\",\r\n");
	}
	
	return 0;
}


/**
 * @brief Private function to parse +KTCP_DATA notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseKUDP_DATA()
{
	// process a response format like:
	// +KTCP_DATA: <tcp_session_id>,<ndata_available>,<data>
	_udpDataAvailable = 0;
	uint8_t status = 0;
	
	// 1. udp_data_available
	status = waitFor(",\"", 100);
	char* ptr = strtok((char*)_buffer,"\",");
	_udpDataAvailable = atoi(ptr);
	
	// 2. udp_client_IP
	waitFor("\",", 100);
	ptr = strtok((char*)_buffer,"\",");
	memcpy(_udpClientIp, ptr,sizeof(_udpClientIp));
	
	// 3. udp_remote_port
	waitFor(",", 100);
	ptr = strtok((char*)_buffer,",");
	_udpClientPort = atoi(ptr);
	
	// 4. data_received
	waitFor(WIFI_V3_CR_LF, 100);
	_length = _length - 2;

	return 0;
}



/**
 * @brief Private function to parse +KTCP_NOTIF notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseKUDP_NOTIF()
{
	// process a response format like:
	// +KTCP_NOTIF: <tcp_session_id>, <tcp_notif>
	_udpNotifSessionId = 0;
	_udpNotifCode = 0;
	
	char* ptr;
	
	ptr = strtok((char*)_buffer, (char*)",\r\n");
	
	for (uint8_t i = 0; i < 2; i++)
	{
		if (ptr == NULL)
		{
			return 1;
		}
		
		switch (i)
		{
			case 0: 
				_udpNotifSessionId = strtoul(ptr, NULL, 10);
				break;
				
			case 1:
				_udpNotifCode = strtoul(ptr, NULL, 10);
				break;
		
			default:
				break;
		}
		
		// iterate to next element
		ptr = strtok(NULL, (char*)",\r\n");
	}
	
	PRINT_WIFI_V3("UDP Nofiticacion --> Session ID: ");
	USB.print(_udpNotifSessionId);
	USB.print("Code: ");
	USB.println(_udpNotifCode);
	
	return 0;
}




/**
 * @brief Private function to parse +KTCP_SRVREQ notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseKUDP_SRVREQ()
{
	// process a response format like:
	// +KUDP_SRVREQ: <udp_session_id>,<udp_client_session_id>,<client_ip>,<client_port>
	_udpSessionId = 0;
	_udpClientSessionId = 0;
	memset(_tcpClientIp, 0x00, sizeof(_udpClientIp));
	_udpClientPort = 0;
		
	char* ptr;
	uint16_t length;
	
	ptr = strtok((char*)_buffer, (char*)"\",\r\n");
	
	for (uint8_t i = 0; i < 4; i++)
	{
		if (ptr == NULL)
		{
			return 1;
		}
		
		switch (i)
		{
			case 0: 
				_udpSessionId = strtoul(ptr, NULL, 10);
				break;
				
			case 1: 
				_udpClientSessionId = strtoul(ptr, NULL, 10);
				break;
				
			case 2: 
				memcpy(_udpClientIp, ptr, sizeof(_udpClientIp)-1);
				length = strlen(ptr);
				if (length < sizeof(_udpClientIp)-1);
				_udpClientIp[length] = 0x00;
				break;
				
			case 3: 
				_udpClientPort = strtoul(ptr, NULL, 10);
				break;
				
			default:
				break;
		}
		
		// iterate to next element
		ptr = strtok(NULL, (char*)"\",\r\n");
	}
	
	return 0;
}


/**
 * @brief Private function to parse +SRWAPSTA notification
 * 
 * @return '0' if ok, 'x' if error
 */
uint8_t WaspWIFI_v3::parseSRWAPSTA()
{
	char* ptr;
	uint16_t length;
	uint8_t i = 0;
	uint8_t status = 1;
	
	waitFor(WIFI_V3_CR_LF);
	
	ptr = strtok((char*)_buffer, "\"");
	ptr = strtok(NULL, "\",");
	memcpy(client[i].mac, ptr, sizeof(client[i].mac));
	
	ptr = strtok(NULL, "\",");
	memcpy(client[i].ip, ptr, sizeof(client[i].ip));
	
	i++;
	
	while (status)
	{
		status = waitFor(WIFI_V3_SRWAPSTA, WIFI_V3_OK);
		if (status == 2)
		{
			_apClients = i;
			
			for (uint8_t j = i; j<10; j++)
			{
				memset(client[j].mac, 0x00, sizeof(client[j].mac));
				memset(client[j].ip, 0x00, sizeof(client[j].ip));
			}
					
			return i;
		}
		waitFor(WIFI_V3_CR_LF);
		
		ptr = strtok((char*)_buffer, "\"");
		ptr = strtok(NULL, "\",");
		memcpy(client[i].mac, ptr, sizeof(client[i].mac));
		
		ptr = strtok(NULL, "\",");
		memcpy(client[i].ip, ptr, sizeof(client[i].ip));
		
		i++;
	}	
}





/**
 * 
 * 
 */
void WaspWIFI_v3::openUartBridge()
{
	serialFlush(0);
	serialFlush(1);
	USB.ON();
	
	while (1)
	{
		// UART1 ----> UART0 (USB)
		while(serialAvailable(1) > 0)
		{
			printByte(serialRead(1),0);
		}

		// USB (UART0) ----> UART1
		while(serialAvailable(0) > 0)
		{
			printByte(serialRead(0), 1);
		}
	}
}


uint8_t WaspWIFI_v3::formatMeshliumData(char* buffer, uint8_t* data, uint16_t length)
{
	char aux[3];
	memset( aux, 0x00, sizeof(aux) );
	
	if (data == NULL)
	{
		return 1;
	}
	
	sprintf_P(buffer,"%s", (char*)pgm_read_word(&(table_wifi_v3[59])));
	
	for (uint16_t i=0 ; i<length; i++)
	{
		Utils.hex2str( &data[i], aux, 1);
		strncat( buffer, aux, 2 );
	}
	strncat( buffer, 0x00, 1 );

	return 0;
}

// Preinstantiate Objects /////////////////////////////////////////////////////

WaspWIFI_v3 WIFI_PRO_V3 = WaspWIFI_v3();

///////////////////////////////////////////////////////////////////////////////
