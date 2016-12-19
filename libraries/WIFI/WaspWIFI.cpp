/*! \file WaspWIFI.cpp
 *  \brief Library for managing WIFI modules
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
 *  Version:		3.0
 *  Design:			David Gascón
 *  Implementation:	Joaquin Ruiz, Yuri Carmona
 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif

#include "WaspWIFI.h"
///////////////////////////////////////////////////////////////////////////////


/******************************************************************************
 * COMMANDS (FLASH Definitions)
 ******************************************************************************/


/// table_WIFI /////////////////////////////////////////////////////////////////

const char str_reboot[] 			PROGMEM	= "reboot\r"; 			// 0
const char str_error[] 				PROGMEM	= "ERR\0"; 				// 1
const char str_no_matching[] 		PROGMEM	= "No matching APs\0"; 	// 2
const char str_failed[] 			PROGMEM	= "FAILED\0"; 			// 3
const char str_found[] 				PROGMEM	= "Found 0\0"; 			// 4
const char str_open[] 				PROGMEM	= "*OPEN*\0"; 			// 5
const char str_set_sys_p[]			PROGMEM	= "set s p 0x4000\r"; 	// 6
const char str_set_channel[]		PROGMEM	= "set w c "; 			// 7
const char str_set_AutojoinAuth[]	PROGMEM	= "set w a "; 			// 8
const char str_set_JoinMode[]		PROGMEM	= "set w j "; 			// 9
const char str_set_AuthKey_wep[]	PROGMEM	= "set w k "; 			// 10
const char str_set_AuthKey_nowep[]	PROGMEM	= "set w p "; 			// 11
const char str_set_APretries[]		PROGMEM	= "set w l "; 			// 12
const char str_set_ScanOptions[]	PROGMEM	= "set w m "; 			// 13
const char str_scan[]				PROGMEM	= "scan "; 				// 14
const char str_set_ESSID[]			PROGMEM	= "set w s "; 			// 15
const char str_set_TXRate[]			PROGMEM	= "set w r ";			// 16
const char str_set_TXPower[]		PROGMEM	= "set w tx ";			// 17
const char str_set_IPWindow[]		PROGMEM	= "set w w ";			// 18
const char str_join[]				PROGMEM	= "join ";				// 19
const char str_joinAPnum[]			PROGMEM	= "join # ";			// 20
const char str_leave[]				PROGMEM	= "leave\r";			// 21
const char str_set_joinTime[]		PROGMEM	= "set o j ";			// 22
const char str_sendPing[]			PROGMEM	= "ping ";				// 23
const char str_set_time_address[]	PROGMEM	= "set t a ";			// 24
const char str_set_time_port[]		PROGMEM	= "set t p ";			// 25
const char str_set_time_enable[]	PROGMEM	= "set t e ";			// 26
const char str_set_wake_timer[]		PROGMEM	= "set s w ";			// 27
const char str_set_sleep_timer[]	PROGMEM	= "set s s ";			// 28
const char str_set_debug_mode[]		PROGMEM	= "set s p ";			// 29
const char str_set_GW[]				PROGMEM	= "set i g ";			// 30
const char str_set_Netmask[]		PROGMEM	= "set i n ";			// 31
const char str_set_ip_host[]		PROGMEM	= "set i h ";			// 32 
const char str_set_ip_remote[]		PROGMEM	= "set i r ";			// 33
const char str_set_LocalPort[]		PROGMEM	= "set i l ";			// 34
const char str_set_ip[]				PROGMEM	= "set i a ";			// 35
const char str_set_dhcp_options[]	PROGMEM	= "set i d ";			// 36
const char str_set_IPoptions[]		PROGMEM	= "set i f ";			// 37
const char str_set_ConnectionOpts[]	PROGMEM	= "set i p ";			// 38
const char str_set_TCPpassw[]		PROGMEM	= "set o p ";			// 39
const char str_set_dns_address[]	PROGMEM	= "set d a ";			// 40
const char str_set_dns_name[]		PROGMEM	= "set d n ";			// 41
const char str_set_dns_backup[]		PROGMEM	= "set d b ";			// 42
const char str_set_ftp_address[]	PROGMEM	= "set f a ";			// 43
const char str_set_ftp_remote[]		PROGMEM	= "set f r ";			// 44
const char str_set_ftp_mode[]		PROGMEM	= "set f m ";			// 45
const char str_set_ftp_time[]		PROGMEM	= "set f t ";			// 46
const char str_set_ftp_user[]		PROGMEM	= "set f u ";			// 47
const char str_set_ftp_pass[]		PROGMEM	= "set f p ";			// 48
const char str_set_ftp_dir[]		PROGMEM	= "set f d ";			// 49 
const char str_set_ftp_get_file[]	PROGMEM	= "ftp g ";				// 50
const char str_timeout[]			PROGMEM	= "timeout\0";			// 51
const char str_set_ftp_put_file[]	PROGMEM	= "ftp p ";				// 52
const char str_open_answer[]		PROGMEM	= "OPEN\0";				// 53
const char str_ip_host_0[]			PROGMEM	= "set i h 0\r";		// 54
const char str_ip_remote_80[]		PROGMEM	= "set i r 80\r";		// 55 
const char str_com_remote[]			PROGMEM	= "set c r ";			// 56
const char str_opt_format_1[]		PROGMEM	= "set o f 1\r";		// 57
const char str_exit[]				PROGMEM	= "exit\r";				// 58
const char str_close[]				PROGMEM	= "close\r";			// 59 
const char str_broadcast_address[]	PROGMEM	= "set b a ";			// 60
const char str_broadcast_interval[]	PROGMEM	= "set b i ";			// 61
const char str_broadcast_port[]		PROGMEM	= "set b p ";			// 62 
const char str_device_id[]			PROGMEM	= "set o d ";			// 63 
const char str_adhoc_beacon[]		PROGMEM	= "set a b ";			// 64
const char str_adhoc_probe[]		PROGMEM	= "set a p ";			// 65 
const char str_factory_reset[]		PROGMEM	= "factory RESET\r";	// 66 
const char str_sleep[]				PROGMEM	= "sleep\r";			// 67
const char str_time[]				PROGMEM	= "time\r";				// 68
const char str_lookup[]				PROGMEM	= "lookup ";			// 69 
const char str_set_BaudRate[]		PROGMEM	= "set u b ";			// 70
const char str_save[]				PROGMEM	= "save\r";				// 71 
const char str_get_ip[]				PROGMEM	= "get ip\r";			// 72
const char str_get_ip_answer[]		PROGMEM	= "IF=UP";				// 73
const char str_show_connection[]	PROGMEM	= "show c\r";			// 74
const char str_show_net[]			PROGMEM	= "show n\r";			// 75
const char str_show_rssi[]			PROGMEM	= "show r\r";			// 76
const char str_show_stats[]			PROGMEM	= "show s\r";			// 77
const char str_show_time[]			PROGMEM	= "show t\r";			// 78
const char str_get_adhoc_set[]		PROGMEM	= "get a\r";			// 79
const char str_get_broadcast_set[]	PROGMEM	= "get b\r";			// 80
const char str_get_comm_set[]		PROGMEM	= "get c\r";			// 81
const char str_get_dns_set[]		PROGMEM	= "get d\r";			// 82
const char str_get_ftp_set[]		PROGMEM	= "get f\r";			// 83
const char str_get_ip_set[]			PROGMEM	= "get i\r";			// 84
const char str_get_mac_set[]		PROGMEM	= "get m\r";			// 85
const char str_get_option_set[]		PROGMEM	= "get o\r";			// 86
const char str_get_system_set[]		PROGMEM	= "get s\r";			// 87
const char str_get_time_set[]		PROGMEM	= "get t\r";			// 88
const char str_get_wlan_set[]		PROGMEM	= "get w\r";			// 89
const char str_get_uart_set[]		PROGMEM	= "get u\r";			// 90
const char str_get_soft_version[]	PROGMEM	= "ver\r";				// 91
const char str_set_comm_size[]		PROGMEM	= "set c s ";			// 92
const char str_set_comm_timer[]		PROGMEM	= "set c t ";			// 93
const char str_opt_format_7[]		PROGMEM	= "set o f 7\r";		// 94
const char str_sys_io_7[]			PROGMEM	= "set s i 0x7\r";		// 95
const char request_http_frame[]		PROGMEM	= "GET$/getpost_frame_parser.php?frame=";	// 96
const char uart_mode[]				PROGMEM	= "set u m %u\r";		// 97
const char http_ok[]				PROGMEM	= "200 OK";				// 98
const char cmd_mode_request[]		PROGMEM	= "$$$";				// 99
const char cmd_mode_answer[]		PROGMEM	= "CMD";				// 100
const char save_answer[]			PROGMEM	= "Storing in config";	// 101
const char ok_answer[]				PROGMEM	= "OK";					// 102
const char reboot_answer[]			PROGMEM	= "*Reboot*";			// 103	
const char aok_answer[]				PROGMEM	= "AOK";				// 104
const char exit_answer[]			PROGMEM	= "EXIT";				// 105	
const char ftp_error_answer[]		PROGMEM	= "FTP ERR";			// 106
const char str_get_time_unix[]		PROGMEM	= "show t t\r";			// 107



	

const char* const table_WIFI[] PROGMEM= 	  
{   
	str_reboot, 			// 0
	str_error,				// 1
	str_no_matching,		// 2
	str_failed,				// 3
	str_found,				// 4
	str_open,				// 5
	str_set_sys_p,			// 6
	str_set_channel,		// 7
	str_set_AutojoinAuth,	// 8
	str_set_JoinMode,		// 9
	str_set_AuthKey_wep,	// 10
	str_set_AuthKey_nowep,	// 11
	str_set_APretries,		// 12
	str_set_ScanOptions,	// 13
	str_scan,				// 14
	str_set_ESSID,			// 15
	str_set_TXRate,			// 16
	str_set_TXPower,		// 17
	str_set_IPWindow,		// 18
	str_join,				// 19
	str_joinAPnum,			// 20
	str_leave,				// 21
	str_set_joinTime,		// 22
	str_sendPing,			// 23
	str_set_time_address,	// 24
	str_set_time_port,		// 25
	str_set_time_enable,	// 26
	str_set_wake_timer,		// 27
	str_set_sleep_timer,	// 28
	str_set_debug_mode,		// 29
	str_set_GW, 			// 30
	str_set_Netmask,		// 31
	str_set_ip_host,		// 32
	str_set_ip_remote,		// 33
	str_set_LocalPort,		// 34
	str_set_ip,				// 35
	str_set_dhcp_options,	// 36
	str_set_IPoptions,		// 37
	str_set_ConnectionOpts,	// 38
	str_set_TCPpassw,		// 39
	str_set_dns_address,	// 40
	str_set_dns_name,		// 41
	str_set_dns_backup,		// 42
	str_set_ftp_address,	// 43
	str_set_ftp_remote,		// 44
	str_set_ftp_mode,		// 45
	str_set_ftp_time,		// 46
	str_set_ftp_user,		// 47
	str_set_ftp_pass,		// 48
	str_set_ftp_dir,		// 49
	str_set_ftp_get_file,	// 50
	str_timeout,			// 51
	str_set_ftp_put_file,	// 52
	str_open_answer,		// 53
	str_ip_host_0,			// 54
	str_ip_remote_80,		// 55
	str_com_remote,			// 56
	str_opt_format_1,		// 57
	str_exit,				// 58
	str_close,				// 59
	str_broadcast_address,	// 60
	str_broadcast_interval,	// 61
	str_broadcast_port,		// 62
	str_device_id,			// 63
	str_adhoc_beacon,		// 64
	str_adhoc_probe,		// 65
	str_factory_reset,		// 66
	str_sleep,				// 67
	str_time,				// 68
	str_lookup,				// 69
	str_set_BaudRate,		// 70
	str_save,				// 71
	str_get_ip,				// 72
	str_get_ip_answer,		// 73
	str_show_connection,	// 74
	str_show_net,			// 75
	str_show_rssi,			// 76
	str_show_stats,			// 77
	str_show_time,			// 78
	str_get_adhoc_set,		// 79
	str_get_broadcast_set,	// 80
	str_get_comm_set,		// 81
	str_get_dns_set,		// 82
	str_get_ftp_set,		// 83
	str_get_ip_set,			// 84
	str_get_mac_set,		// 85
	str_get_option_set,		// 86
	str_get_system_set,		// 87
	str_get_time_set,		// 88
	str_get_wlan_set,		// 89
	str_get_uart_set,		// 90
	str_get_soft_version,	// 91
	str_set_comm_size,		// 92
	str_set_comm_timer,		// 93
	str_opt_format_7,		// 94
	str_sys_io_7,			// 95
	request_http_frame,		// 96
	uart_mode,				// 97
	http_ok,				// 98
	cmd_mode_request,		// 99
	cmd_mode_answer,		// 100
	save_answer,			// 101
	ok_answer,				// 102
	reboot_answer,			// 103
	aok_answer,				// 104
	exit_answer,			// 105
	ftp_error_answer,		// 106
	str_get_time_unix,			// 107
};



/******************************************************************************/

// Private Methods ////////////////////////////////////////////////////////////

//! Switches to command Mode
uint8_t WaspWIFI::commandMode()
{	
	// number of retries
	char question[30];
	char buffer[20];
	
	char cmd_mode_request[20];
	char cmd_mode_answer[20];
	char save_answer[20];
	char ok_answer[20];
	char reboot_answer[20];

	// Copy strings from Flash memory
	strcpy_P(cmd_mode_request, (char*)pgm_read_word(&(table_WIFI[99]))); // "$$$"
	strcpy_P(cmd_mode_answer, (char*)pgm_read_word(&(table_WIFI[100]))); // "CMD"
	strcpy_P(save_answer, (char*)pgm_read_word(&(table_WIFI[101]))); // "Storing in config"
	strcpy_P(ok_answer, (char*)pgm_read_word(&(table_WIFI[102]))); // "OK"	
	strcpy_P(reboot_answer, (char*)pgm_read_word(&(table_WIFI[103]))); // "*Reboot*"	
	
	////////////////////////////////////////////////////////////
	// Check first if the module has already been set at 115200
	////////////////////////////////////////////////////////////		
	
	// WIFI_BAUDRATE is '115200'
	baud_rate = WIFI_BAUDRATE;	
	
	// wait for RN171 uart port stabilization
	delay(3000);
	
	closeSerial(_uartWIFI);
	beginSerial(baud_rate, _uartWIFI);
	serialFlush(_uartWIFI);
	
	// "$$$"
	delay(250);
	if( sendCommand(cmd_mode_request, cmd_mode_answer, 5000) != 1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("ERR entering CMD at 115200"));
		#endif
	}
	else
	{
		#ifdef DEBUG_WIFI
		USB.print(F("enter CMD at ")); 
		USB.println(WIFI_BAUDRATE);
		#endif
		
		return 1;
	}	
	
	//////////////////////////////////////////////
	// If not, enter in command mode at 9600
	//////////////////////////////////////////////	
	OFF();	
	baud_rate = 9600;	
	
	// select multiplexer
    if (_uartWIFI == SOCKET0) Utils.setMuxSocket0();
    if (_uartWIFI == SOCKET1) Utils.setMuxSocket1();
	
	// power up depending on the chosen SOCKET
    PWR.powerSocket(_uartWIFI, HIGH);
    
    // wait for RN171 uart port stabilization
	delay(3000);
	
	closeSerial(_uartWIFI);
	beginSerial(baud_rate, _uartWIFI);
	serialFlush(_uartWIFI);
  
	// "$$$"
	delay(250);
	if( sendCommand(cmd_mode_request, cmd_mode_answer, 5000) != 1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("ERR: $$$"));
		#endif
		return 0;
	}
	
	// "set u b 115200"
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[70])));
	snprintf(question, sizeof(question), "%s%lu\r", buffer, WIFI_BAUDRATE);		
	if( sendCommand(question, ok_answer, 500) != 1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("ERR: set u b 115200"));
		#endif
		return 0;
	}
	
	// "set s p 0x4000\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[6])));	
	if( sendCommand(question, ok_answer, 500) != 1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("ERR: set s p 0x4000"));
		#endif
		return 0;
	}
	
	// "set s i 0x7\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[95])));	
	if( sendCommand(question, ok_answer, 500) != 1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("ERR: set s i 0x7"));
		#endif
		return 0;
	}
  
	// "save\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[71])));
	if( sendCommand(question, save_answer, 500) != 1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("ERR: save"));
		#endif
		return 0;
	}
	
	// "reboot\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[0])));
	if( sendCommand(question, reboot_answer, 500) != 1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("ERR: reboot"));
		#endif
		return 0;
	}
	
	
	//////////////////////////////////////////////
	// Enter in command mode at 115200
	//////////////////////////////////////////////		
	
	baud_rate = WIFI_BAUDRATE;	
	
	// wait for RN171 uart port stabilization
	delay(3000);
	
	closeSerial(_uartWIFI);
	beginSerial(baud_rate, _uartWIFI);
	serialFlush(_uartWIFI);
	
	// "$$$"
	delay(250);
	if( sendCommand(cmd_mode_request, cmd_mode_answer, 5000) != 1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("ERR entering CMD at 115200"));
		#endif
	}
	else
	{
		#ifdef DEBUG_WIFI
		USB.print(F("enter CMD at ")); 
		USB.println(WIFI_BAUDRATE);
		#endif
		
		return 1;
	}	
	
	serialFlush(_uartWIFI); 
	return 0; 	
}

//! Checks if 'word' is contained in 'text'.
bool WaspWIFI::contains(const char* text, char* word)
{
	char* pch;
	
	pch = strstr(text,word);
	
	if(pch != NULL)
	{
		return true;
	}
	else
	{		
		return false;
	}
}


/*
 * checkAnswer - read from UART and check answer specified as input parameter
 * 
 */
uint8_t WaspWIFI::checkAnswer(char* pattern)
{
	uint8_t i=0;
	
	memset(answer, 0x00, sizeof(answer));
	
	// check available data
    while(serialAvailable(_uartWIFI))
    {
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{			
			i++;
			latencyDelay();
		}
    }
	answer[i]='\0'; 
		
	// Checks the answer seeking the pattern
	if(contains(answer,pattern))
	{
		return 1;
	}
	else 
	{
		return 0; 
	}

}




//! Reads data over the UART.
uint8_t WaspWIFI::readData(uint8_t len)
{	
	uint16_t i=0;
	length=0;
	
	char str_aok[20];
	char str_error[20];
	char str_failed[20];
	char str_exit[20];

	// Copy strings from Flash memory
	strcpy_P( str_aok, (char*)pgm_read_word(&(table_WIFI[104]))); 	// "AOK"
	strcpy_P( str_error, (char*)pgm_read_word(&(table_WIFI[1]))); 	// "ERR"
	strcpy_P( str_failed, (char*)pgm_read_word(&(table_WIFI[3]))); 	// "FAILED"
	strcpy_P( str_exit, (char*)pgm_read_word(&(table_WIFI[105]))); 	// "EXIT"	
	
	
	if (serialAvailable(_uartWIFI))
	{ 
		// If there are data available...
		if (len!=0)
		{
			if(!waitForData(len+3))
			{
				return 0;
			}
		}
		// Waits until there are lenght + 3 data in the uart.
		while(serialAvailable(_uartWIFI))
		{
			// While serial available over the uart...
			if ((i<(sizeof(answer)-1))&&((answer[i]=serialRead(_uartWIFI))!='\0'))
			{
				i++; 
			}
			latencyDelay();
		}
	} 
	answer[i]='\0';
	// set length 
	length=i;
	
	// Checks the answer.
	if (contains(answer, str_aok))
	{
		return 1;
	}
	else
	{
		if( contains(answer, str_error)	||
			contains(answer, Disconn_pattern)||
			contains(answer, str_failed)	)
		{  
			#ifdef DEBUG_WIFI
			USB.println(answer); 
			#endif
			return 0;
		}
		else 
		{  	
			// checking for UDP conenctions
			if (contains( answer, str_exit))
			{
				return 1;
			}
			return 0;
		}
	}
}

//! Sends the command 'comm' over the UART.
uint8_t WaspWIFI::sendCommand(char* comm)
{
	uint8_t i=0;
  	
	#ifdef DEBUG_WIFI
	USB.println(comm); 
	#endif

	// necessary to re-begin serial comm 
	beginSerial(baud_rate, _uartWIFI); 
	delay(100);
	
	// Writes 'comm' over the UART.
	serialFlush(_uartWIFI); 
	
	printString(comm,_uartWIFI); 
	delay(100);
	
	// Waits an answer from the UART
	if( !waitForData(1) )
	{
		return 0;
	}
		
	// get sentence length
	i=strlen(comm);
		
	// Calls readData to take and to check the answer.
	return readData(i);
}




/*******************************************************************************
 * sendCommand
 * 
 * This function sends a command 'comm' over the UART. Then expects to receive
 * the correct answer specified by 'pattern' within a given 'timeout'
 * 
 * The input parameters:
 * 	'comm': command to be sent to the module
 * 	'pattern': correct answer to the command expected from the module 
 * 	'timeout': number of milliseconds to wait for the response 
 * 
 * Returns:
 * 	'1' if OK
 * 	'0' if error
 * 
 ******************************************************************************/
uint8_t WaspWIFI::sendCommand(char* comm, char* pattern, unsigned long timeout)
{
	uint8_t i=0;
  	
	// clear uart buffer
	serialFlush(_uartWIFI); 
	
	// print command
	printString(comm,_uartWIFI); 
	delay(100);
	
	/// read answer
	
	// clear buffer
	memset(answer, 0x00, sizeof(answer));
	
	unsigned long previous = millis();
	
	// check available data
    while( (millis() - previous) < timeout )
    {
		
		if(serialAvailable(_uartWIFI))
		{
			if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
			{			
				i++;
				latencyDelay();
			}
		}
			
		// Checks the answer seeking the pattern
		if( strlen(answer) >= strlen(comm) )
		{
			if(contains(answer,pattern))
			{			
				return 1;
			}
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < timeout) timeout = millis();
	}
		
	// timeout
	return 0; 
}



/*******************************************************************************
 * sendCommand
 * 
 * This function sends a command 'comm' over the UART. Then expects to receive
 * the correct answer specified by 'pattern' within a given 'timeout'. If an 
 * error pattern specified by 'err_pattern' is received the this functions 
 * returns with error. Another boolean 'flush' input specifies if UART flush is 
 * required prior to sending the command 
 * 
 * Returns:
 * 	'1' if OK
 * 	'0' if error
 * 
 ******************************************************************************/
uint8_t WaspWIFI::sendCommand(	char* comm, 
								char* pattern, 
								char* err_pattern, 
								unsigned long timeout,
								bool flush)
{
	uint8_t i=0;
  	
	// clear uart buffer
	if( flush == true )
	{
		serialFlush(_uartWIFI); 		
	}
	
	// print command
	printString(comm,_uartWIFI); 
	delay(100);
	
	/// read answer
	
	// clear buffer
	memset(answer, 0x00, sizeof(answer));
	
	unsigned long previous = millis();
	
	// check available data
    while( (millis() - previous) < timeout )
    {
		
		if(serialAvailable(_uartWIFI))
		{
			if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
			{			
				i++;				
			}
		}
			
		// Checks the answer seeking the pattern
		if( strlen(answer) >= strlen(comm) )
		{
			if(contains(answer,pattern))
			{				
				return 1;
			}
			if(contains(answer,err_pattern))
			{		
				return 0;
			}
		}
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < timeout) timeout = millis();
	}
	
	// timeout
	return 0; 
}



/*
 * 
 * name: sendCommand
 * @param	char* command: command to be sent
 * @param	char* ans1: expected answer
 * @param	char* ans2: expected answer
 * @param	char* ans3: expected answer
 * @param	char* ans4: expected answer
 * @param	uint32_t timeout: time to wait for response
 * @return 	'0' if timeout error, 
 * 			'1' if ans1
 * 			'2' if ans2
 * 			'3' if ans3
 * 			'4' if ans4
 * 
 */
uint8_t  WaspWIFI::sendCommand(	char* command, 
								char* ans1, 
								char* ans2, 
								char* ans3, 
								char* ans4, 
								uint32_t timeout)
{
	// index counter
	uint8_t i = 0;
  	
	// clear uart buffer before sending command
	serialFlush(_uartWIFI); 	
	
	/// 1. print command
	printString( command, _uartWIFI ); 
	
	/// 2. read answer	
	// clear buffer
	memset( answer, 0x00, sizeof(answer) );
	uint16_t length = 0;
	
	// get actual instant
	unsigned long previous = millis();
	
	// check available data for 'timeout' milliseconds
    while( (millis() - previous) < timeout )
    {
		if( serialAvailable(_uartWIFI) )
		{
			if ( i < (sizeof(answer)-1) )
			{	
				answer[i++] = serialRead(_uartWIFI);				
				length++;				
			}
		}
			
		// Check 'ans1'
		if( find( (uint8_t*)answer, length, ans1 ) == true )
		{				
			return 1;
		}
		
		// Check 'ans2'
		if( ans2 != NULL )
		{
			if( find( (uint8_t*)answer, length, ans2 ) == true )
			{		
				return 2;
			}
		}
		
		// Check 'ans3'
		if( ans3 != NULL )
		{
			if( find( (uint8_t*)answer, length, ans3 ) == true )
			{		
				return 3;
			}
		}
		
		// Check 'ans4'
		if( ans4 != NULL )
		{
			if( find( (uint8_t*)answer, length, ans4 ) == true )
			{		
				return 4;
			}
		}	
		
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}
		
	// timeout
	return 0; 
	
}



/*
 * 
 * name: latencyDelay
 * This function waits for specific time depending on the baudrate used.
 * 
 * Latency time for ensure there is no more data is calculated suposing the 
 * worst condition: 1start+8data+1parity+2stop = 12 bits per byte
 * 
 */
void WaspWIFI::latencyDelay()
{
	// In the case there are not any bytes left in the incoming uart
	// wait for the time one byte needs for tranmission regarding the baudrate
	if (serialAvailable(_uartWIFI) == 0)
	{
		switch (baud_rate)
		{
			case 115200:	delayMicroseconds(105); 	break;
			case 57600:		delayMicroseconds(209); 	break;
			case 38400:		delayMicroseconds(313); 	break;
			case 19200:		delayMicroseconds(625); 	break;
			case 9600:		delay(1); 	break;
			case 4800:		delay(3); 	break;
			case 2400:		delay(5); 	break;
			case 1800:		delay(7); 	break;
			case 1200:		delay(10); 	break;
			case 600:		delay(20); 	break;
			case 300:		delay(40); 	break;
			default:					break;			
		}
	}
}




/*
 * 
 * name: find
 * @param	uint8_t* buffer: pointer to buffer to be scanned
 * @param	uint16_t length: actual length of buffer
 * @param	char* pattern: pattern to find
 * @return 	'0' not found, 
 * 			'1' pattern found
 * 
 */
bool WaspWIFI::find( uint8_t* buffer, uint16_t length, char* pattern)
{
	int result;
	
	if( length >= strlen(pattern) )
	{		
		for(uint16_t i = 0; i <= length-strlen(pattern); i++)
		{
			result = memcmp( &buffer[i], pattern, strlen(pattern) );
			
			if( result == 0 )
			{
				return true;
			}
		}
	}
	
	return false;
}




//! Saves current configuration and reboots the device in order to new 
//! configuration takes effect.
uint8_t WaspWIFI::saveReboot()
{
	char question[20];
    char buffer1[20];
    char buffer2[20];
    char buffer3[20];
    char buffer4[20];

	uint16_t i=0;
	
	// Saves current configurations.
	storeData();
		
	// Reboots the module. (don't call reset() because this is special reboot
	// for auto-connect, etc...)
	// copy "reboot\r" string
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[0]))); 
	serialFlush(_uartWIFI);	
	printString(question,_uartWIFI);
	
	// Waits an answer from the UART.
	if(!waitForData(15,5000))
	{
		return 0;
	}
	while(serialAvailable(_uartWIFI))
	{
		if((answer[i]=serialRead(_uartWIFI))!='\0')
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0';
    
	// Copy strings from Flash memory
	strcpy_P(buffer1, (char*)pgm_read_word(&(table_WIFI[1]))); // "ERR\0"
	strcpy_P(buffer2, (char*)pgm_read_word(&(table_WIFI[2]))); // "No matching APs\0"
	strcpy_P(buffer3, (char*)pgm_read_word(&(table_WIFI[3]))); // "FAILED\0"
	strcpy_P(buffer4, (char*)pgm_read_word(&(table_WIFI[4]))); // "Found 0\0"	
	  
	// Check if the answer contains Error messages, 
	// including connection error messages.
	if(	contains( answer, buffer1)	||
		contains( answer, buffer2)	||
		contains( answer, buffer3)	||
		contains( answer, buffer4)	)
	{  
		#ifdef DEBUG_WIFI
		USB.println(answer);  
		#endif
		return 0; 
	}
	else 
	{  
		return 1;
	}
	return 0;
}

//! Opens TCP connection, and checks that everything are going good.
uint8_t WaspWIFI::open()
{
	char buffer[20];
	uint8_t i=0;  
		
	#ifdef DEBUG_WIFI
	USB.println(F("open"));

	#endif
   
	// flush uart
	serialFlush(_uartWIFI);
	
	// Sends command 'open' to open the connection configured before.
	printString("open\r",_uartWIFI);
	
	// Waits an answer from the UART.
	if(!waitForData(20))
	{	
		#ifdef DEBUG_WIFI
		USB.println(F("waitForData timeout"));
		#endif
		return 0;
	}
	while(i<20)
	{
		if ((answer[i]=serialRead(_uartWIFI))!='\0')
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0';
  
	// Checks the answer.
	// Copy "*OPEN*\0"
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[5]))); 
	if (contains(answer,buffer))
	{
		return 1;
	}
	else
	{
		#ifdef DEBUG_WIFI
		USB.println(F("answer does NOT contain OPEN:"));
		USB.println(answer);	
		#endif
		return 0;  
	}
}

//! Opens http connection, and checks that everything are going good.
uint8_t WaspWIFI::openHTTP()
{
	char buffer[20];
	uint16_t i=0;
	
	#ifdef DEBUG_WIFI
	USB.println(F("open"));
	#endif	
	
	// Sends command 'open' to open the connection configured before.
	serialFlush(_uartWIFI);
	printString("open\r",_uartWIFI);
  
	// Waits an answer from the UART.
	if(!waitForData(20,5000))
	{
		return 0;
	}
	while( serialAvailable(_uartWIFI) && i<(sizeof(answer)-1) )
	{
		if((i<(sizeof(answer)-1))&&((answer[i]=serialRead(_uartWIFI))!='\0'))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0';
  
	// Checks the answer.
	// Copy "*OPEN*\0"
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[5]))); 
	if(contains(answer,buffer))
	{
		#ifdef DEBUG_WIFI
		USB.println(answer); 
		#endif
		return 1;
	}
	else
	{
		return 0;  
	}
}
	
//! Reads a broadcast message and parses it.
void WaspWIFI::parseBroadcast()
{
	int i=0;
	
	// Reboots to waits those UDP messages.
	saveReboot();
	while(1)
	{
		// Waits the UDP message (lenght ~90)
		if(!waitForData(90))
		{
			return (void)0;
		}
		while(serialAvailable(_uartWIFI))
		{
			answer[i]=serialRead(_uartWIFI);
			i++;
		}
		i=0;
		
		// First characters = MAC address.
		while (i<6)
		{
			USB.print(answer[i]); i++;
		}
		USB.println();
		i=60;
		// Device ID string.
		while (i<92)
		{
			USB.print(answer[i]);
			i++;
		}
		USB.println(); 
	}

}

// Public Methods /////////////////////////////////////////////////////////////

// Constructors ///////////////////////////////////////////////////////////////

//! Class constructor. Initializes the necessary variables.
WaspWIFI::WaspWIFI()
{
	_uartWIFI=1;
	scanTime=200;
	scanPassive=false;
	baud_rate=WIFI_BAUDRATE;
	
	// "*CLOS*" pattern
	CLOS_pattern[0]=(char)0x2a;
	CLOS_pattern[1]=(char)0x43;
	CLOS_pattern[2]=(char)0x4c;
	CLOS_pattern[3]=(char)0x4f;
	CLOS_pattern[4]=(char)0x53;
	CLOS_pattern[5]=(char)0x2a;
	CLOS_pattern[6]=(char)0x00;	
	
	// "Disconn" pattern
	Disconn_pattern[0]=(char)0x44;
	Disconn_pattern[1]=(char)0x69;
	Disconn_pattern[2]=(char)0x73;
	Disconn_pattern[3]=(char)0x63;
	Disconn_pattern[4]=(char)0x6f;
	Disconn_pattern[5]=(char)0x6e;
	Disconn_pattern[6]=(char)0x6e;
	Disconn_pattern[7]=(char)0x00;	
	
	// "timeout=" pattern
	timeout_pattern[0]=(char)0x74;
	timeout_pattern[1]=(char)0x69;
	timeout_pattern[2]=(char)0x6d;
	timeout_pattern[3]=(char)0x65;
	timeout_pattern[4]=(char)0x6f;
	timeout_pattern[5]=(char)0x75;
	timeout_pattern[6]=(char)0x74;
	timeout_pattern[7]=(char)0x3d;
	timeout_pattern[8]=(char)0x00;	
}

// Basic Methods //////////////////////////////////////////////////////////////



//! Powers on the module and enters in command mode.
bool WaspWIFI::ON(uint8_t sock)
{	
	// set the uart 
	if (sock == SOCKET0) _uartWIFI = SOCKET0;
	if (sock == SOCKET1) _uartWIFI = SOCKET1;

	// previous power down prior to power up
	OFF();
	
    // select multiplexer
    if (_uartWIFI == SOCKET0) Utils.setMuxSocket0();
    if (_uartWIFI == SOCKET1) Utils.setMuxSocket1();
    	
	// power up depending on the chosen SOCKET
    PWR.powerSocket(_uartWIFI, HIGH);
	
	// enter in command mode at 115200bps
	if( commandMode() == 1 )
	{
		// update Waspmote Register
		if(_uartWIFI == SOCKET0)	WaspRegister |= REG_SOCKET0;
		if(_uartWIFI == SOCKET1)	WaspRegister |= REG_SOCKET1;
		return 1;
	}
	else
	{
		return 0;
	}
}



//! Closes the UART and powers off the module.
void WaspWIFI::OFF()
{
	// Exits from command mode. (not mandatory)
	//~ printString("exit\r",_uartWIFI); 
	#ifdef DEBUG_WIFI	
	USB.println(F("*OFF")); 
	#endif
	
	// close UART
	closeSerial(_uartWIFI);
   
	// unselect multiplexer 
    if (_uartWIFI == SOCKET0)	Utils.setMuxUSB();
    if (_uartWIFI == SOCKET1)	Utils.muxOFF1();
    
    // switch module OFF
	PWR.powerSocket(_uartWIFI, LOW);
	
	// update Waspmote Register
	if(_uartWIFI == SOCKET0)	WaspRegister &= ~(REG_SOCKET0);
	if(_uartWIFI == SOCKET1)	WaspRegister &= ~(REG_SOCKET1);		

	delay(500);
}

// Access point configuration methods /////////////////////////////////////////

//! Sets the wlan channel, 1-13 is the valid range for a fixed channel.
uint8_t WaspWIFI::setChannel(uint8_t val)
{
	char question[50];	
	char buffer[20];
	
	// Copy "set w c "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[7]))); 
	
	snprintf(question, sizeof(question), "%s%d\r",buffer,val);
	return sendCommand(question);
}

//! Sets the authentication mode.
uint8_t WaspWIFI::setAutojoinAuth(uint8_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set w a "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[8]))); 
	snprintf(question, sizeof(question), "%s%d\r",buffer,val);
	return sendCommand(question, (char*)"AOK", 5000);
}

//! Sets the policy for automatically joining/associating with network 
//! access points.
uint8_t WaspWIFI::setJoinMode(uint8_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set w j "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[9]))); 
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	 
	// Send command to join wlan 
	if( sendCommand(question, (char*)"AOK", 5000)==1 )
	{		
		return 1; 		
	}
	
	return 0;
}
	
//! Sets the Key or the passphrase of the wlan.
uint8_t WaspWIFI::setAuthKey(uint8_t secMode, char* pass)
{
	char question[128];
	char buffer[20];
	char *pass2 = (char *)malloc(27);
	char numch[2];
	uint8_t i=0, j=0;
  
	// If WEP, translate to HEX and sets key.
	if (secMode==WEP)
	{
		while (i<13)
		{
			snprintf(numch, sizeof(numch), "%x",pass[i]); 
			/*serialFlush(_usb);
			serialWrite(numch[0],_usb); serialWrite(numch[1],_usb); 
			serialWrite('\n',_usb);*/
			pass2[j]=numch[0]; j++; 
			pass2[j]=numch[1]; j++;
			i++;
		}
		pass2[26]='\0';
	
		// Copy "set w k "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[10]))); 
		snprintf(question, sizeof(question), "%s%s\r", buffer, pass2); 
	}
	// If not, sets passphrase in ASCII.
	else
	{
		// Copy "set w p "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[11]))); 	  
		snprintf(question, sizeof(question), "%s%s\r", buffer, pass); 
	}
	// Sends the command over the UART.
	return sendCommand(question, (char*)"AOK", 5000);
}

//! Sets the link monitor timeout threshold.
uint8_t WaspWIFI::setAPretries(uint8_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set w l "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[12]))); 
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	return sendCommand(question);
}
	
//! Sets the Scan options, but does not launch the scan.
uint8_t WaspWIFI::setScanOptions(uint16_t time, char* mask, bool passive)
{
	char question[128];
	char buffer[20];
	scanTime=time;
	scanPassive=passive;
	
	// Copy "set w m "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[13]))); 
	snprintf(question, sizeof(question), "%s%s\r", buffer, mask);
	return sendCommand(question);
}
	
//! Launches the scan.
void WaspWIFI::scan()
{
	char question[50];
	char buffer[20];
	uint16_t i=0;
	
	// Copy "scan "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[14]))); 
	
	// Sets the command depending of if it is Passive.
	if (scanPassive==false)
    { 
		snprintf(question, sizeof(question), "%s%d\r", buffer, scanTime);
	}
	else 
    {
		snprintf(question, sizeof(question), "%s%d P\r", buffer, scanTime);
	}
	serialFlush(_uartWIFI);
	
	
	printString(question,_uartWIFI);
	// Waits an answer from the UART.
	if(!waitForData(20))
	{
		return (void)0;
	}
	while(serialAvailable(_uartWIFI))
	{
		if( ((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)) )
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	answer[511]='\0'; 
	// Shows the results of the scan.
	USB.println(answer); 

}
	
//! Sets the ESSID of the wlan.
uint8_t WaspWIFI::setESSID(char* ssid)
{
	char question[128];
	char buffer[20];
	
	// Copy "set w s "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[15]))); 
	snprintf(question, sizeof(question), "%s%s\r", buffer, ssid);
	return sendCommand(question);
}
	
//! Sets the Transmission Rate.
uint8_t WaspWIFI::setTXRate(uint8_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set w r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[16]))); 
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	return sendCommand(question);
}
	
//! Sets the Transmission Power.
uint8_t WaspWIFI::setTXPower(uint8_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set w tx "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[17]))); 
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	return sendCommand(question);  
}
	
//! Sets the IP Window value.
uint8_t WaspWIFI::setIPWindow(uint16_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set w w "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[18]))); 
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	return sendCommand(question);
}
	
//! Joins the chosen ssid.
uint8_t WaspWIFI::join(char* ssid)
{
	char question[128];
	char buffer[20];
	char str_get_ip_answer[20];
	int retries=5;
	
	
	// Copy "join "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[19]))); 
	// Copy "IF=UP"
	strcpy_P(str_get_ip_answer, (char*)pgm_read_word(&(table_WIFI[73])));	
	
	// Sends command to join an Access Point.
	snprintf(question, sizeof(question), "%s%s\r", buffer, ssid);
	serialFlush(_uartWIFI); 
	
	// in the case it is static IP there is no answer when joining
	// so it is necessary to ask for it
	if( _dhcpOpts == DHCP_OFF )
	{		
		while( retries>0 )
		{	
			// "join ??" command
			if( sendCommand( question, (char*)"Associated!", Disconn_pattern, 10000, true) == 1)
			{
				// Copy "get ip\r"
				strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[72])));
				// "IF=UP"
				strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[73])));
				
				// "get ip"
				if( sendCommand( question, buffer, 10000) == 1)
				{				
					return 1;
				}		
			}
			
			// retry
			leave();
			delay(500);		
			retries--;				
		}
			
		return 0;
	}	
	
	unsigned long timeout = 10000;
	
	while( retries>0 )
	{
		// send command
		if( sendCommand( question, str_get_ip_answer, Disconn_pattern, timeout, false) == 1)
		{
			return 1;
		}
		
		// retry
		leave();
		delay(500);		
		retries--;	
	}
	
	// if the module did not connect or returned error then call "leave" 
	// function and return error in the case leave does not respond, then 
	// reboot the module because it might have entered a non-command mode state
	if(leave() != 1)
	{
		ON(_uartWIFI);
	}
	return 0;
}
	
//! Joins a network AP from the scan list.
uint8_t WaspWIFI::joinAPnum(uint8_t val)
{
	char question[50];
	char buffer[20];
  
	// Copy "join # "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[20]))); 
	
	// Sends command to join an Access Point.
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	serialFlush(_uartWIFI); //serialFlush(_usb);
	if(sendCommand(question))
	{
		// Checks 3 times if it is correctly connected.
		if (!isConnected()) if(!isConnected()) if(!isConnected())
		{  
			return 0; 
		}
		return 1; 
	}
	return 0;
}
	
//! If connected, leaves the connected network
uint8_t WaspWIFI::leave()
{
	char question[20];
	
	// Copy "leave\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[21]))); 
	
	return sendCommand(question);
}
	
//! Join timer is the time in milliseconds the join function will wait for an
//! access point to complete the association process. This timer is also the 
//! timeout for the WPA handshaking process.
uint8_t WaspWIFI::setJoinTime(uint16_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set o j "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[22]))); 
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	return sendCommand(question);
}

// Connection Configuration Methods ///////////////////////////////////////////

//! Sends a ping to a remote specified host.
void WaspWIFI::sendPing(ipAddr ip)
{
	char question[128];
	char buffer[20];
	uint16_t i=0;
	
	// Copy "ping "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[23]))); 
	
	// Sends the command over the uart.
	snprintf(question, sizeof(question), "%s%s 10\r", buffer, ip);
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
	
	// Waits an answer from the uart.
	if(!waitForData(15))
	{
		return (void)0;
	}
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	// Shows the result of the ping.
	answer[i]='\0'; 
	USB.println(answer); 
}
	
//! Synchronizes the time from the server.
uint8_t WaspWIFI::setTimeFromServer(ipAddr ip, uint16_t port, uint8_t interval)
{
	char question[128];
	char buffer[20];
	uint8_t u1, u2, u3;
	
	// Copy "set t a "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[24])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, ip);
	u1=sendCommand(question);
	
	// Copy "set t p "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[25])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, port);
	u2=sendCommand(question);
	
	// Copy "set t e "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[26])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, interval);
	u3=sendCommand(question);
	
	if ((u1==1)&&(u2==1)&&(u3==1))
		return 1;
	else
		return 0;  
}

//! Sets the sleep time and the wake time (in seconds).
uint8_t WaspWIFI::setSleep(uint8_t sTime, uint8_t sCycle)
{
	char question[50];
	char buffer[20];
	uint8_t u1,u2;
	
	// Copy "set s w "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[27])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, sTime);
	u1= sendCommand(question);
	
	// Copy "set s s "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[28])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, sCycle);
	u2= sendCommand(question);
	
	if ((u1==1)&&(u2==1))
	{
		if (saveReboot()==1)
		{
			// enter in command mode
			if( commandMode() == 1 )
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

//! Controls debug print messages. This configures the debug messages
//! printed by the WiFly module on the UART.
uint8_t WaspWIFI::setDebugMode(uint8_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set s p "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[29])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	return sendCommand(question);
}

//! Sets the Gateway address.
uint8_t WaspWIFI::setGW(ipAddr ip)
{
	char question[128];
	char buffer[20];
	
	// Copy "set i g "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[30])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, ip);
	return sendCommand(question);
}

//! Sets the netmask.
uint8_t WaspWIFI::setNetmask(ipAddr netmask)
{
	char question[128];
	char buffer[20];
	
	// Copy "set i n "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[31])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, netmask);
	return sendCommand(question);  
}

//! Sets the Remote Host.
uint8_t WaspWIFI::setRemoteHost(ipAddr ip, uint16_t port)
{
	char question[128];
	char buffer[20];
	
	// Copy "set i h "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[32])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, ip);
  
	if (sendCommand(question)==1)
	{	
		// Copy "set i r "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[33])));
		snprintf(question, sizeof(question), "%s%d\r", buffer, port);
		return sendCommand(question);
	}
	return 0;
}

//! Sets the Local Port.
uint8_t WaspWIFI::setLocalPort(uint16_t port)
{
	char question[50];
	char buffer[20];
	
	// Copy "set i l "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[34])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, port);
	return sendCommand(question);  
}

//! Sets the IP address.
uint8_t WaspWIFI::setIp(ipAddr ip)
{
	char question[128];
	char buffer[20];
	
	// Copy "set i a "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[35])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, ip);
	return sendCommand(question);  
}

//! Sets the DHCP options.
uint8_t WaspWIFI::setDHCPoptions(uint8_t val)
{
	char question[50];
	char buffer[20];
	
	_dhcpOpts = val;
	
	// Copy "set i d "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[36])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	return sendCommand(question, (char*)"AOK", 5000);  
}

//! Sets the IP options.
uint8_t WaspWIFI::setIPoptions(uint8_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set i f "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[37])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	return sendCommand(question);
}

//! Sets the connection options. (TCP, UDP, HTTP...) Value is a bit 
//! mapped setting.
uint8_t WaspWIFI::setConnectionOptions(uint8_t val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set i p "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[38])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, val);
	return sendCommand(question, (char*)"AOK", 5000);  
}
	
//! Sets the TCP connection password. Provides minimal authentication by 
//! requiring any remote device that connects to send and match a challenge
//! <val>. When set, all newly opened connections must first send the exact
//! characters that match the stored password, otherwise the WIFI module  
//! will close the connection.
uint8_t WaspWIFI::setTCPpassw(char* password)
{
	char question[128];
	char buffer[20];
	
	// Copy "set o p "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[39])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, password);
	return sendCommand(question);  
}

//! Sets the IP address, host and backup host of the DNS main 
//! or auxiliary server.
uint8_t WaspWIFI::setDNS(uint8_t type, ipAddr ip, char* name)
{
	char question[128];
	char buffer[20];
	
	// Copy "set d a "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[40])));
  
	// Sets the dns address.
	snprintf(question, sizeof(question), "%s%s\r", buffer, ip);
	if(sendCommand(question)==1)
	{
		// Depending on MAIN or AUX, sets DNS name or backup.
		if (type==MAIN)
		{	
			// Copy "set d n "
			strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[41])));
			snprintf(question, sizeof(question), "%s%s\r", buffer, name);
			return sendCommand(question);
		}
		else
		{	
			// Copy "set d b "
			strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[42])));
			snprintf(question, sizeof(question), "%s%s\r", buffer, name);
			return sendCommand(question);
		}
	}
	return 0;
}

//! Sets the FTP parameters.
uint8_t WaspWIFI::setFTP(	ipAddr ip, 
							uint16_t port, 
							uint8_t mode, 
							uint8_t timeout)
{
	char question[128];
	char buffer[20];
	uint8_t u1, u2, u3, u4;
	
	// Copy "set f a "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[43])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, ip);
	u1=sendCommand(question);
		
	// Copy "set f r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[44])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, port);
	u2=sendCommand(question);
		
	// Copy "set f m "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[45])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, mode);
	u3=sendCommand(question);
		
	// Copy "set f t "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[46])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, timeout*8);
	u4=sendCommand(question);
	
	if ((u1==1)&&(u2==1)&&(u3==1)&&(u4==1))
		return 1;
	else
		return 0;
}
	
//! Opens the ftp connection using the user and the password given.
uint8_t WaspWIFI::openFTP(char* user, char* password)
{
	char question[128];
	char buffer[20];
	uint8_t u1,u2;
		
	// Copy "set f u "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[47])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, user);
	u1=sendCommand(question);
			
	// Copy "set f p "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[48])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, password);
	u2=sendCommand(question);
  
	// Reboots
	if ((u1==1)&&(u2==1)&&(saveReboot()==1))
	{
		// Enters in command mode.
		while(commandMode()!=1){}
		return 1;
	}
	return 0;
}

//! Gets the file via FTP.
uint8_t WaspWIFI::getFile(	char* filename, 
							char* local_folder, 
							char* remote_folder)
{
	char question[128];
	char buffer[20];
	int maxBuffer=256;
	int i=0;
	int readRet=0;
	unsigned long previous;
	bool end, timeout;
	unsigned long total=0;
		
	// get statistics
	getStats();	
	
	// Local variables
	SdFile file;	
	
	// switch SD card ON
	SD.ON();
	
	// go to Root directory
	SD.goRoot();
			
	// check if the card is there or not
	if( !SD.isSD() )
	{	
		#ifdef DEBUG_WIFI
		USB.println(F("Error: SD not present"));  
		#endif 
		SD.OFF();
		return 0;
	}
	
	// Create folder in the case it does not exist
	if( (strcmp(local_folder,".")==0) || (strcmp(local_folder,"/")==0) )
	{
		// root directory selected 
		// do nothing
	}
	else if( SD.isDir(local_folder) == 1 )
	{
		// Selects SD card local folder		
		if( !SD.cd(local_folder) )
		{	
			#ifdef DEBUG_WIFI
			USB.println(F("Error: SD cd"));  
			#endif 
			SD.OFF();
			return 0;
		}
	}
	else if( SD.isDir(local_folder) == -1 )
	{
		#ifdef DEBUG_WIFI
		USB.println(F("create folder")); 
		#endif
		if( SD.mkdir(local_folder) == false )
		{
			// not created
			#ifdef DEBUG_WIFI
			USB.println(F("Error: directory not created"));  
			#endif  
			SD.OFF();
			return 0;
		}	
	
		// Selects SD card local folder		
		if( !SD.cd(local_folder) )
		{	
			#ifdef DEBUG_WIFI
			USB.println(F("Error: SD cd"));  
			#endif 
			SD.OFF();
			return 0;
		}
	}
	
	// Delete file in the case it exists
	if( SD.isFile(filename) == 1 )
	{
		#ifdef DEBUG_WIFI
		USB.println(F("delete file")); 
		#endif
		SD.del(filename);
	}
	
	// Creates a file in that folder.
	SD.create(filename);

	// search file in current directory and open it in write mode
	if(!SD.openFile(filename, &file, O_READ | O_WRITE | O_SYNC))    
	{	
		#ifdef DEBUG_WIFI
		USB.println(F("Error: opening file")); 
		#endif
		SD.OFF();
		return 0;
	}
        
	// jump over zero 'offset'
	if(!file.seekSet(0))
	{	
		#ifdef DEBUG_WIFI
		USB.println(F("Error: setting file offset"));  
		#endif
		file.close();
		SD.OFF();		
		return 0;
	}	
	
	/******************************
	 *  CHANGE BAUDRATE TO 9600 bps
	 *****************************/
	
	printString("set uart instant 9600\r",_uartWIFI);
	delay(100);
	closeSerial(_uartWIFI);
	delay(100);
	baud_rate=9600;
	beginSerial(baud_rate,_uartWIFI);
	delay(100);
	serialFlush(_uartWIFI);
	delay(100);
	
		
	// Sets the directory in the FTP server to get the file
	// Copy "set f d "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[49])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, remote_folder);
	
	if( sendCommand(question) !=1 )
	{
		#ifdef DEBUG_WIFI
		USB.println(F("Error: setting FTP server directory"));  
		#endif
		return 0; 
	}			
	
	
	// Sends the command that gets the file.
	// Copy "ftp g "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[50])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, filename);		
	serialFlush(_uartWIFI);
		
	#ifdef DEBUG_WIFI
	USB.println(question);
	beginSerial(baud_rate,_uartWIFI);
	delay(100); 
	#endif	

	// clear buffer
	memset(answer, 0x00, sizeof(answer));		
	
	// Copy strings from Flash memory
	char str_timeout[20];
	char str_close[20];
	char str_error[20];
	char str_open[20];		
	char ftp_error_answer[20];
	
	// Copy "timeout\0"
	strcpy_P(str_timeout, (char*)pgm_read_word(&(table_WIFI[51])));
	// Copy "*CLOS*"
	strcpy(str_close, CLOS_pattern);
	// Copy "ERR\0"
	strcpy_P(str_error, (char*)pgm_read_word(&(table_WIFI[1])));
	// Copy "*OPEN*"
	strcpy_P( str_open, (char*)pgm_read_word(&(table_WIFI[5])));
	// Copy "FTP ERR"
	strcpy_P( ftp_error_answer, (char*)pgm_read_word(&(table_WIFI[106])));	
	
	
	////////////////////////////////////////////////////////////////////////
	// OPEN
	////////////////////////////////////////////////////////////////////////
	
	// Send FTP GET commmand waiting for different answers:
	//	OK:"*OPEN*"
	//	ERROR: "timeout\0"
	//	ERROR:"*CLOS*"
	//	ERROR:"ERR\0"
	uint8_t result = sendCommand(question, 
									str_open, 
									str_timeout, 
									str_close, 
									str_error, 
									FTP_TIMEOUT );
	
	if( result == 0 )
	{
		#ifdef DEBUG_WIFI
		USB.println(F("FTP_TIMEOUT2"));
		#endif	
		baud_rate=WIFI_BAUDRATE;
		ON(_uartWIFI);
		return 0;
	}
	
	if( result == 2 )
	{
		#ifdef DEBUG_WIFI
		USB.println(F("timeout pattern"));
		#endif	
		baud_rate=WIFI_BAUDRATE;
		ON(_uartWIFI);
		return 0;			
	}
	
	if( result == 3 )
	{
		#ifdef DEBUG_WIFI
		USB.println(F("close pattern"));
		#endif	
		baud_rate=WIFI_BAUDRATE;
		ON(_uartWIFI);
		return 0;			
	}
	
	if( result == 4 )
	{
		#ifdef DEBUG_WIFI
		USB.println(F("ERR pattern"));
		#endif	
		baud_rate=WIFI_BAUDRATE;
		ON(_uartWIFI);
		return 0;			
	}
	
			
	////////////////////////////////////////////////////////////////////////////
	// RECEPTION OF FILE			
	////////////////////////////////////////////////////////////////////////////
	if( result != 1 )
	{
		// *OPEN* pattern NOT found 
		return 0;
	}	
	
	// In this point of the function:
	// *OPEN* pattern has been found 
	// The rest of the file is currently being 
	// written via UART from the WiFi module	
	
	// If there is no problem *OPEN* should appear 
	// but no "FTP ERR" should be received
	if( find( (uint8_t*)answer, sizeof(answer), ftp_error_answer ) == false)
	{		
		// set index in answer to the beginning
		i=0;	
		memset( answer, 0x00, sizeof(answer) );	
		
		end = false;
		timeout = false;
		previous = millis();
		
		/* define the prevention block size which is calculated as the 
		 * maximum of the strings to be checked while the file is downloaded
		 * these strings are written by the module to indicate errors, pauses
		 * or to indicate the finalization of the downloading process
		 * the strings to be scanned are: "*CLOS*", "timeout=" and "Disconn".
		 * Thus, the prevention block is not written in the SD file until it 
		 * has been checked in the next loop			 
		 *        ______________________________________________________
		 *       |   |   |   |   |   |        |   |   |   |             |
		 * 1st:  |   |   |   |   |   |  ..... |   |   |   | PREVENTION  |
		 *       |___|___|___|___|___|________|___|___|___|_____________|			 
		 * 
		 *        ______________________________________________________
		 *       |               |   |        |   |   |   |             |
		 * 2nd:  |  PREVENTION   |   |  ..... |   |   |   | PREVENTION  |
		 *       |_______________|___|________|___|___|___|_____________|
		 * 
		 * 
		 */			
		const int PREVENTION_BLOCK = strlen(timeout_pattern)-1;	
		int nBytes;
		while( !end && !timeout )
		{						
			// check "timeout=" pattern
			if( findPattern( (uint8_t*)answer, timeout_pattern, readRet) != -1 )
			{									
				#ifdef DEBUG_WIFI
				USB.println(F("err pattern3")); 
				USB.print(F("\nanswer:"));
				USB.println( (uint8_t*)answer, readRet);
				#endif		
				SD.OFF();	
				baud_rate = WIFI_BAUDRATE;
				ON(_uartWIFI);
				return 0;
			}						
			
			// check "Disconn" pattern
			if( findPattern( (uint8_t*)answer, Disconn_pattern, readRet) != -1 )
			{									
				#ifdef DEBUG_WIFI
				USB.println(F("err pattern2")); 
				USB.print(F("\nanswer:"));
				USB.println( (uint8_t*)answer, readRet);
				#endif	
				SD.OFF();		
				baud_rate = WIFI_BAUDRATE;
				ON(_uartWIFI);
				return 0;
			}
			
			// check end of transmission: "*CLOS*" pattern			
			if( findPattern((uint8_t*)answer,CLOS_pattern,readRet) != -1 )
			{								
				#ifdef DEBUG_WIFI
				USB.println(F("end of file")); 
				#endif	
				// substract ending pattern from number of read bytes					
				readRet = readRet-strlen(CLOS_pattern);
				end = true;
			}		
			
			// calculate number of bytes to be written into file
			if( (readRet>PREVENTION_BLOCK)&&(end == false) )
			{
				// regular writing: Write all except for the prev. block
				nBytes = readRet-PREVENTION_BLOCK;
			}				
			else if( end == true)
			{
				// end of file: 'readRet' counter avoids the ending pattern
				nBytes = readRet;
			}
			else
			{
				// not enough data and not end of file: Do not write 
				nBytes = 0;					
			}	
			
			// write data to file if there is something to be written						
			if( nBytes > 0 )
			{
				if( file.write((uint8_t*)answer, nBytes) != nBytes )
				{
					#ifdef DEBUG_WIFI
					USB.println(F("WRITING ERR")); 
					#endif
					file.close(); 
					SD.OFF();
					baud_rate=WIFI_BAUDRATE;
					ON(_uartWIFI);
					return 0;    
				}	
			}
			
			// check the end of transmission
			if( end == true )
			{			
				#ifdef DEBUG_WIFI
				USB.println(F("-----> end==true")); 
				#endif					
				break;
			}			

			// Copy 'prevention block' from the end to the beginning of 
			// 'answer' when received more than PREVENTION_BLOCK bytes
			if( readRet > PREVENTION_BLOCK )
			{
				for(int t = 0; t<PREVENTION_BLOCK; t++)
				{
					answer[t] = answer[t+nBytes];
				}
				// set offset to the end of the block
				i = PREVENTION_BLOCK;
				readRet = PREVENTION_BLOCK;
			}
			else
			{
				// there are less than PREVENTION_BLOCK bytes to be checked 
				// in  'answer', so assign 'readRet' to 'i' counter
				i=readRet;
			}

			// Read all available data we can store in 'answer'
			bool escape=false;	
			if(	serialAvailable(_uartWIFI) > 0 )
			{
				while( serialAvailable(_uartWIFI) && !escape )
				{					
					// set last previous instant when data was received					
					previous = millis();
				
					// read data
					if( i<maxBuffer )
					{
						answer[i] = serialRead(_uartWIFI);						
						i++;
						total++;
					}
					else
					{
						// buffer completed
						escape=true;
					}
				}
				// Update counters
				readRet=i;
				i=0;	
			}
			else if( i>0 )
			{
				// no available data but 'i' pending bytes to be kept in 'answer'
				readRet=i;
				//i=i;
			}
			else
			{				
				// Update counters to zero
				readRet=0;
				i=0;	
			}
			
			// check the timeout overflow
			if( millis()< previous )
			{
				previous = millis();
			}
			
			if( (millis()-previous)>FTP_TIMEOUT )
			{
				timeout = true;
			}	
		}			
		
		// check timeout
		if( timeout == true )
		{			
			#ifdef DEBUG_WIFI
			USB.println(F("FTP_TIMEOUT")); 
			for(uint16_t t = 0; t < sizeof(answer); t++)
			{
				USB.printHex(answer[t]);
			}
			USB.println();								
			#endif
			SD.OFF();	
			baud_rate=WIFI_BAUDRATE;
			ON(_uartWIFI);
			return 0;				
		}	
		
		if( end == false )
		{	
			#ifdef DEBUG_WIFI
			USB.println(F("FALSE END")); 
			#endif	
			SD.OFF();	
			baud_rate=WIFI_BAUDRATE;
			ON(_uartWIFI);
			return 0;					
		}
		
//~ 			// check if not received bytes but received *CLOS* => false positive			
//~ 			if( total <= strlen(CLOS_pattern) )
//~ 			{	
//~ 				#ifdef DEBUG_WIFI
//~ 				USB.print(F("total="));
//~ 				USB.println(total);			 
//~ 				#endif	
//~ 				SD.OFF();	 
//~ 				baud_rate=WIFI_BAUDRATE;
//~ 				ON(_uartWIFI);
//~ 				return 0;					
//~ 			}			
		
		#ifdef DEBUG_WIFI
		USB.println(F("DOWNLOAD OK"));
		USB.print(F("\n\n\n"));		 									
		// get statistics
		getStats();	
		#endif	
		
		// CHANGE BAUDRATE TO 115200 bps
		printString("set uart instant 115200\r",_uartWIFI);
		delay(100);
		closeSerial(_uartWIFI);
		delay(100);
		baud_rate=WIFI_BAUDRATE;
		beginSerial(baud_rate,_uartWIFI);
		delay(100);
		serialFlush(_uartWIFI);
		delay(100);
		SD.OFF();		
		return 1;
	}
	else
	{
		// Otherwise means error while 'get ftp' command.
		#ifdef DEBUG_WIFI
		USB.println(F("ERR appeared in module response"));
		USB.print(F("\nanswer:"));
		for(int q = 0; q<readRet ; q++)
		{
			USB.print(answer[q]);
		}
		USB.println();			
		#endif
		SD.OFF();				
		baud_rate=WIFI_BAUDRATE;
		ON(_uartWIFI);
		return 0;
	}	
	
	
	#ifdef DEBUG_WIFI
	USB.println(F("SEND CMD ERR")); 
	#endif
	SD.OFF();
	baud_rate=WIFI_BAUDRATE;
	ON(_uartWIFI);
	return 0;
}



//! Uploads a file via FTP.
uint8_t WaspWIFI::uploadFile(	char* filename, 
								char* local_folder,
								char* remote_folder)
{
	char question[128];
	char buffer[20];
	uint16_t i=0, plong=0;
	long int size, size_aux=0;
	int readRet;
	int count;	
	int flwSet_aux=0;
	long int WTX_aux=0;
	bool timeout;
	unsigned long previous;
	long int total=0;
	
	// Local variable  
	SdFile file;	
	
	// size of the buffer to use when reading
	int maxBuffer = 200;  
	// buffer so as to store data
	uint8_t bufferSD[maxBuffer]; 
	
	// get statistics
	getStats();
	
	// store the actual statistics
	flwSet_aux = flwSet;		
	WTX_aux = WTX;		
	
	// check stats are OK
	if(flwSet_aux == -1)
	{	
		#ifdef DEBUG_WIFI
		USB.println(F("flwSet==-1")); 
		#endif
		return 0;
	}	
	
	if( WTX_aux == -1 )
	{	
		#ifdef DEBUG_WIFI
		USB.println(F("WTX_aux==-1")); 
		#endif 
		return 0;
	}	
	
	
	/******************************
	 *  CHANGE BAUDRATE TO 9600 bps
	*****************************/
	
	printString("set uart instant 9600\r",_uartWIFI);
	delay(100);
	closeSerial(_uartWIFI);
	delay(100);
	baud_rate=9600;
	beginSerial(baud_rate,_uartWIFI);
	delay(100);
	serialFlush(_uartWIFI);
	delay(100);
	
	 		
	// Copy "set f d "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[49])));
 
	// Sets the directory in the FTP server to upload the file
	snprintf(question, sizeof(question), "%s%s\r", buffer, remote_folder);	
	
	if( sendCommand(question) == 1 )
	{
		// Copy "ftp p "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[52])));
		
		// Sends the command that uploads the file.
		snprintf(question, sizeof(question), "%s%s\r", buffer, filename);
		serialFlush(_uartWIFI);		
		
		#ifdef DEBUG_WIFI
		USB.println(question); 
		#endif
		
		serialFlush(_uartWIFI);
		printString(question,_uartWIFI);
    
		// Waits an answer over the uart.
		plong=strlen(question);
		plong=plong+10;
		if(!waitForData(plong))
		{			
			#ifdef DEBUG_WIFI
			USB.println(F("FTP_TIMEOUT1")); 
			#endif
			baud_rate=WIFI_BAUDRATE;
			ON(_uartWIFI);
			return 0;
		}

		i=0;
		answer[i]='\0';
						
		char buffer1[20];
		char buffer2[20];
		char buffer3[20];
		char buffer4[20];
		
		// Copy "timeout\0"
		strcpy_P(buffer1, (char*)pgm_read_word(&(table_WIFI[51])));
		// Copy "OPEN\0"
		strcpy_P(buffer2, (char*)pgm_read_word(&(table_WIFI[53])));
		// Copy "ERR\0"
		strcpy_P(buffer3, (char*)pgm_read_word(&(table_WIFI[1])));
		// Copy "*CLOS*"
		strcpy(buffer4, CLOS_pattern);	
		
		previous=millis();
		
		// Checks the answer (Until "timeout\0", "OPEN\0" or "ERR\0")		
		while(!(contains( answer, buffer1)	||
				contains( answer, buffer2)	||
				contains( answer, buffer3)) )
		{ 
			i=0; 
			delay(500);		

			if(serialAvailable(_uartWIFI))
			{
				while(serialAvailable(_uartWIFI))
				{
					if( (i<(sizeof(answer)-1)) && ((answer[i]=serialRead(_uartWIFI))!='\0') )
					{
						i++;
					}
					// wait
					delay(10);		
				}
			}
			answer[i]='\0';					
			
			// check millis overflow
			if(previous > millis())
			{
				previous=millis();
			}
			
			// check timeout if no answer is received to 'ftp put' command
			if( (millis()-previous)>FTP_TIMEOUT )
			{
				#ifdef DEBUG_WIFI
				USB.println(F("FTP_TIMEOUT2")); 
				#endif
				baud_rate=WIFI_BAUDRATE;
				ON(_uartWIFI);
				return 0;
			}	
		}
		
				
		// "OPEN\0" means connected correctly and waiting the file.
		if (contains(answer,buffer2))
		{			
			// switch SD card ON
			SD.ON();
	
			// go to Root directory
			SD.goRoot();
			
			
			// Selects SD card local folder
			if( (strcmp(local_folder,".")==0) || (strcmp(local_folder,"/")==0) )
			{
				// root directory selected 
				// do nothing
			}
			else if(!SD.cd(local_folder))
			{
				// SD error		
				#ifdef DEBUG_WIFI
				USB.println(F("Error: Local folder not valid")); 
				#endif
				baud_rate=WIFI_BAUDRATE;
				ON(_uartWIFI);
				return 0;
			}
			
			// check file existance
			if( SD.isFile(filename) != 1 )
			{		
				// SD error		
				#ifdef DEBUG_WIFI
				USB.println(F("Error: filename not valid")); 
				#endif	
				baud_rate=WIFI_BAUDRATE;
				ON(_uartWIFI);	
				return 0;
			} 
			
			// get file size
			size=SD.getFileSize(filename);
			size_aux=size;
			
			if(size == -1)
			{	
				#ifdef DEBUG_WIFI
				USB.println(F("Error: size==-1")); 
				#endif
				baud_rate=WIFI_BAUDRATE;
				ON(_uartWIFI);	
				return 0;
			}	
		
			// search file in current working directory and open it 
			// exit if error and modify the general flag with FILE_OPEN_ERROR
			if(!SD.openFile((char*)filename, &file, O_RDONLY))
			{
				// SD error		
				#ifdef DEBUG_WIFI
				USB.println(F("Error: opening file"));  
				#endif
				baud_rate=WIFI_BAUDRATE;
				ON(_uartWIFI);
				return 0;
			}
	  
			// set pointer to the beginning of the file
			if(!file.seekSet(0))	
			{
				// SD error		
				#ifdef DEBUG_WIFI
				USB.println(F("Error: setting initial offset in file")); 
				#endif
				baud_rate=WIFI_BAUDRATE;
				ON(_uartWIFI);
				return 0;
			}
  
			// Read first time from file, 'maxBuffer' bytes
			readRet = file.read(bufferSD, sizeof(bufferSD));
			
			count=0;
			while( readRet == -1 )
			{
				#ifdef DEBUG_WIFI
				USB.println(F("Error: reading file")); 
				#endif
				// read again
				readRet = file.read(bufferSD, sizeof(bufferSD));
				if( count >3) break;
				count++;
			}
				
			// second, read the data and store it in the buffer
			// Breaks in the case it exceeds its size.
			while( (readRet > 0) && (size > 0) )
			{	
				// Send data stored in bufferSD until file ends
				for( int j=0; j<readRet; ++j)
				{
					printByte(bufferSD[j],_uartWIFI);
					size--;
					if( size <=0 ) break;
				}
		
				// update read bytes counter
				total=total+readRet;
				
				// Break in the case the file ends
				//if( readRet<maxBuffer ) break;	
		
				// insert delay so as to flush the RX buffer after send info
				//~ delay(500);
				delay(50);
				
				
				// Read other block of data from SD file	
				readRet = file.read(bufferSD, sizeof(bufferSD));
				
				count=0;
				while( readRet == -1 )
				{
					readRet = file.read(bufferSD, sizeof(bufferSD));
					if( count >3) break;
					count++;
					#ifdef DEBUG_WIFI
					USB.println(F("Error: reading file2")); 
					#endif					
				}
					
				// check if error when uploading		
				if(serialAvailable(_uartWIFI))
				{
					#ifdef DEBUG_WIFI
					USB.println(F("Error: module answers when uploading:")); 
					while(serialAvailable(_uartWIFI))
					{
						USB.printHex(serialRead(_uartWIFI));
					}
					USB.println();
					#endif
					baud_rate=WIFI_BAUDRATE;
					ON(_uartWIFI);
					return 0;											
				}				
			}
					
			// Close file
			file.close();
				
			// set SD card off
			SD.OFF();
			
			// wait a little period of time so as to send the finishing pattern
			delay(1000);
			
			// Send *CLOS* to indicate the end of the file and connection
			printString(buffer4,_uartWIFI);
			
			// Waits an answering "*CLOS*" to check the connection from and 
			// to the FTP server is correctly closed.
			i=1;
			previous=millis();
			answer[0]='\0';	
			timeout=false;		
			while( !contains(answer,buffer4) && !timeout )
			{ 				
				i--;
				while(!serialAvailable(_uartWIFI) && !timeout )
				{
					if( (millis()-previous)>FTP_TIMEOUT )
					{
						timeout=true;
					}
				}
				while(serialAvailable(_uartWIFI) && !timeout )
				{
					if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
					{
						i++;
					}
					// wait
					delay(10);
				
					if( (millis()-previous)>FTP_TIMEOUT )
					{
						timeout=true;
					}
				}
				answer[i]='\0';				

				if(previous > millis())
				{
					previous=millis();
				}
				
				if( (millis()-previous)>FTP_TIMEOUT )
				{
					timeout=true;
				}
				delay(500);	
			}			
			
			// check for timeout
			if( timeout == true )	
			{
				#ifdef DEBUG_WIFI
				USB.println(F("FTP_TIMEOUT3")); 
				#endif
				baud_rate=WIFI_BAUDRATE;
				ON(_uartWIFI);
				return 0;
			}				
			
			// get the new stats
			getStats();
	
			// update statistics:
			flwSet_aux = flwSet - flwSet_aux;
			WTX_aux = WTX - WTX_aux;
				
			#ifdef DEBUG_WIFI
			USB.print(F("**********\r\nflwSet_aux:")); 
			USB.println(flwSet_aux,DEC);
			USB.print(F("WTX_aux:")); 
			USB.println(WTX_aux);
			USB.print(F("size_aux:")); 
			USB.println(size_aux);
			USB.println(F("**********"));
			#endif
			
			// check stats are OK
			if( flwSet_aux != 0)
			{	
				baud_rate=WIFI_BAUDRATE;
				ON(_uartWIFI);
				return 0;
			}
			
			if( (total != WTX_aux) || (size_aux != total) )
			{
				baud_rate=WIFI_BAUDRATE;
				ON(_uartWIFI);
				return 0;
			}
						
			// upload OK
			baud_rate=WIFI_BAUDRATE;
			ON(_uartWIFI);
			return 1;
		}
		else
		{		
			#ifdef DEBUG_WIFI
			USB.println(F("OPEN did not appear in answer:")); 
			USB.println(answer);
			#endif
			baud_rate=WIFI_BAUDRATE;
			ON(_uartWIFI);
			return 0;
		}
		// Otherwise means error while 'put ftp' command.
	}
			
	#ifdef DEBUG_WIFI
	USB.println(F("Send Command question ERROR")); 
	#endif
	baud_rate=WIFI_BAUDRATE;
	ON(_uartWIFI);
	return 0;
}

// Connection Configuration Methods ///////////////////////////////////////////

/*******************************************************************************
 * getURL
 * 
 * This function expects the HTTP request as a string. The request and body must
 * be included within the 'request' input
 * 
 * The input parameters:
 * 	'opt': option for addressing: 'DNS' or 'IP'
 * 	'host': url of server
 * 	'request': request of the HTTP query
 * 
 * Example of use:
 * 	WIFI.getURL(	DNS, 
 * 					"pruebas.libelium.com", 
 * 					"GET$/test-get-post.php?value=1");
 * 
 ******************************************************************************/
uint8_t WaspWIFI::getURL(uint8_t opt, char* host, char* request)
{
	// call HTTP request with port number 80 (default)
	return getURL(opt, host, 80, request);	
}	
	
	
/*******************************************************************************
 * getURL
 * 
 * This function expects the HTTP request as a string. The request and body must
 * be included within the 'request' input
 * 
 * The input parameters:
 * 	'opt': option for addressing: 'DNS' or 'IP'
 * 	'host': url of server
 * 	'port': server port
 * 	'request': request of the HTTP query
 * 
 * Example of use:
 * 	WIFI.getURL(	DNS, 
 * 					"pruebas.libelium.com", 
 * 					80,
 * 					"GET$/test-get-post.php?value=1");
 * 
 ******************************************************************************/
uint8_t WaspWIFI::getURL(	uint8_t opt, 
							char* host, 
							int port, 
							char* request)
{
	uint8_t result=0;
	char aux[sizeof(answer)];
	char question[512];
	char buffer[20];
	char HTTP_OK[20];
	uint8_t u1,u2,u3,u4,u5,u6;
  
  
	// If the address is given by a IP address.
	if ( opt == IP )
	{						
		// Copy "set i h "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[32])));
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u1 = sendCommand(question);
		u2 = 1;
	}
	// If the address is given by a URL address.
	else if( opt == DNS )
	{		
		// Turn on DNS. set ip host 0. 			
		// Copy "set i h 0\r"
		strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[54])));
		u1 = sendCommand(question);	
		
		// Set the web server name			
		// Copy "set d n "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[41])));		
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u2 = sendCommand(question);
	}
	else
	{
		return 0;
	}
		
	// Set the web server port introduced as input		
	// Copy "set i r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[33])));
	snprintf(question, sizeof(question),"%s%u\r", buffer, port );		
	u3 = sendCommand(question);
	
	// set com remote
	// Copy "set c r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[56])));
	snprintf(question, sizeof(question),"%s%s\r", buffer, request);
	u4 = sendCommand(question);
	
	// Send header automatically when connection is open	
	// Copy "set o f 1\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[57])));
	u5 = sendCommand(question);
	
	// Use UART mode by default
	// Copy "set u m %u\r"
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[97])));
	snprintf(question, sizeof(question), buffer, 0);
	u6 = sendCommand(question);
	
	// If everything is Ok, even it is correctly connected.
	if ((u1==1)&&(u2==1)&&(u3==1)&&(u4==1)&&(u5==1)&&(u6==1) )
	{ 		
		// introduce a 500ms delay to wait for configuration before 
		// opening the HTTP connection
		delay(500);
		
		// Opens the HTTP connection. With the default UART mode, 
		// the request is sent when opening the connection
		if(openHTTP())  
		{ 			
			// Reads the answer of the HTTP query.
			read(NOBLO,20000); 
			
			// backup copy of the answer			
			memcpy(aux, answer, sizeof(answer));	
			
			// Copy "200 OK"
			strcpy_P(HTTP_OK, (char*)pgm_read_word(&(table_WIFI[98])));
			
			if(findPattern((uint8_t*)answer, HTTP_OK, length)==-1)
			{	
				#ifdef DEBUG_WIFI
				USB.println(F("200 OK Not Found"));		
				#endif	
				result = 0;
			}
			else
			{	
				// HTTP OK
				result = 1;
			}
		}
		else
		{
			#ifdef DEBUG_WIFI
			USB.print(F("openHTTP failed."));		
			#endif	
			result = 0;
		}
	}
	else
	{
		result = 0;
	}

	/* When HTTP retrieve is done, the WiFi module exits command mode so 
	 * it is mandatory to enter command mode again. Then, the module is 
	 * suposed to be already joined to network and a second 'getURL' call
	 * could be done as a retry if the first one fails
	 */
	if(commandMode()!=1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("CMD not entered"));	
		#endif	
		result = 0;
	}	
	
	if( result == 1)	
	{
		// get the backup of the answer when OK
		memcpy(answer, aux, sizeof(answer));
	}
	
	return result;  
}



/*******************************************************************************
 * getURL
 * 
 * This function expects the HTTP request as a string. The request and body must
 * be included within the 'request' input
 * 
 * The input parameters:
 * 	'opt': option for addressing: 'DNS' or 'IP'
 * 	'host': url of server
 * 	'url': url of the HTTP query
 * 	'body': body of the HTTP get query
 *  
 * Example of use:
 * 	WIFI.getURL(	DNS, 
 * 					"pruebas.libelium.com", 
 * 					"GET$/test-get-post.php?",
 * 					"value1=1&value2=2&value3=3&value4=4&value5=5&value6=6");
 * 
 ******************************************************************************/
uint8_t WaspWIFI::getURL(	uint8_t opt, 
							char* host, 
							char* url, 
							char* body)
{
	return getURL(opt, host, 80, url, body);
}

/*******************************************************************************
 * getURL
 * 
 * This function expects the HTTP request as a string. The request and body must
 * be included within the 'request' input
 * 
 * The input parameters:
 * 	'opt': option for addressing: 'DNS' or 'IP'
 * 	'host': url of server
 * 	'port': port of server
 * 	'url': url of the HTTP query
 * 	'body': body of the HTTP get query
 * 
 * Example of use:
 * 	WIFI.getURL(	DNS, 
 * 					"pruebas.libelium.com", 
 * 					80, 
 * 					"GET$/test-get-post.php?",
 * 					"value1=1&value2=2&value3=3&value4=4&value5=5&value6=6");
 * 
 ******************************************************************************/
uint8_t WaspWIFI::getURL(	uint8_t opt, 
							char* host, 
							int port, 
							char* url, 
							char* body)
{
	uint8_t result=0;
	char aux[sizeof(answer)];
	char question[512];
	char buffer[20];
	char HTTP_OK[20];
	uint8_t u1,u2,u3,u4,u5,u6;
  
  
	// If the address is given by a IP address.
	if( opt == IP )
	{						
		// Copy "set i h "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[32])));
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u1 = sendCommand(question);
		u2 = 1;
	}
	// If the address is given by a URL address.
	else if( opt == DNS )
	{		
		// Turn on DNS. set ip host 0. 			
		// Copy "set i h 0\r"
		strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[54])));
		u1 = sendCommand(question);	
		
		// Set the web server name			
		// Copy "set d n "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[41])));		
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u2 = sendCommand(question);
	}
	else
	{
		return 0;
	}
			
	// Set the web server port introduced as input		
	// Copy "set i r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[33])));
	snprintf(question, sizeof(question),"%s%u\r", buffer, port );		
	u3 = sendCommand(question);
	
	// set com remote
	// Copy "set c r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[56])));
	snprintf(question, sizeof(question),"%s%s\r", buffer, url);
	u4 = sendCommand(question);
	
	// Send header automatically when connection is open	
	// Copy "set o f 1\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[57])));
	u5 = sendCommand(question);
	
	// Use UART data trigger mode, which causes the module to make a TCP/HTTP 
	// connection upon incoming UART data
	// Copy "set u m %u\r"
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[97])));
	snprintf(question, sizeof(question), buffer, 2);
	u6 = sendCommand(question);
	
	// If everything is Ok, even it is correctly connected.
	if ((u1==1)&&(u2==1)&&(u3==1)&&(u4==1)&&(u5==1)&&(u6==1) )
	{ 		
		// introduce a 500ms delay to wait for configuration before 
		// opening the HTTP connection
		delay(500);
		
		// Opens the HTTP connection.
		if(openHTTP())  
		{ 		
			// Once the connection is open, we send the string with 
			// the body of the HTTP GET request
			printString( body, _uartWIFI);
			
			// Reads the answer of the HTTP query.
			read(NOBLO,20000); 
			
			// backup copy of the answer			
			memcpy(aux, answer, sizeof(answer));			
			
			// Copy "200 OK"
			strcpy_P(HTTP_OK, (char*)pgm_read_word(&(table_WIFI[98])));			
			
			if(findPattern((uint8_t*)answer, HTTP_OK, length)==-1)
			{	
				#ifdef DEBUG_WIFI
				USB.println(F("200 OK not found"));		
				#endif	
				result = 0;
			}
			else
			{	
				// HTTP OK
				result = 1;
			}
		}
		else
		{
			#ifdef DEBUG_WIFI
			USB.print(F("openHTTP failed."));		
			#endif	
			result = 0;
		}
	}
	else
	{
		result = 0;
	}

	/* When HTTP retrieve is done, the WiFi module exits command mode so 
	 * it is mandatory to enter command mode again. Then, the module is 
	 * suposed to be already joined to network and a second 'getURL' call
	 * could be done as a retry if the first one fails
	 */
	if(commandMode()!=1)
	{
		#ifdef DEBUG_WIFI
		USB.println(F("CMD not entered"));	
		#endif	
		result = 0;
	}	
	
	if( result == 1)	
	{
		// get the backup of the answer when OK
		memcpy(answer, aux, sizeof(answer));
	}
	
	return result;  
}




 
/*******************************************************************************
 * getURL
 * 
 * This function expects an array of bytes including the info about the sensor
 * data. This function has been created to be used with the Waspmote Frame Class
 * 
 * The input parameters:
 * 	'opt': option for addressing: 'DNS' or 'IP'
 * 	'host': url of the Meshlium device
 * 	'request': request of the HTTP query
 * 	'frame': pointer to the array of bytes of the frame
 * 	'len': length of the data frame 
 * 
 ******************************************************************************/
uint8_t WaspWIFI::getURL(	uint8_t opt, 
							char* host, 
							char* request, 
							uint8_t* frame, 
							uint16_t len)
{	
	// use the 80 remote port as default port	
	return sendHTTPframe( opt, host, 80, request, frame, len );	
}



/*******************************************************************************
 * sendHTTPframe
 * 
 * This function is used to send Waspmote Frames from Waspmote to Meshlium
 * using the Sensor Parser of the Meshlium machine so as to store all Data 
 * Frames inside the DataBase of Meshlium.
 * 
 * These are the input parameters:
 * 	'opt': option for addressing: 'DNS' or 'IP'
 * 	'host': url of the Meshlium device
 * 	'port': port number 
 * 	'frame': pointer to the array of bytes of the frame
 * 	'len': length of the data frame
 * 
 * Example of use:
 * 	WIFI.sendHTTPframe(IP, "10.10.10.1", 80, frame.buffer, frame.length);
 * 
 ******************************************************************************/
uint8_t WaspWIFI::sendHTTPframe(uint8_t opt, 
								char* host, 
								int port, 
								uint8_t* frame, 
								uint16_t len)
{		
	// define local buffer
	char request[100];
	
	// Copy "GET$/getpost_frame_parser.php?frame="
	strcpy_P(request, (char*)pgm_read_word(&(table_WIFI[96])));
	
	return sendHTTPframe( opt, host, port, request, frame, len );	
}

/*******************************************************************************
 * sendHTTPframe
 * 
 * This function is used to send Waspmote Frames from Waspmote to Meshlium
 * using the Sensor Parser of the Meshlium machine so as to store all Data 
 * Frames inside the DataBase of Meshlium.
 * 
 * These are the input parameters:
 * 	'opt': option for addressing: 'DNS' or 'IP'
 * 	'host': url of the Meshlium device
 * 	'port': port number 
 * 	'request': request of the HTTP query
 * 	'frame': pointer to the array of bytes of the frame
 * 	'len': length of the data frame
 * 
 * Example of use:
 * 	WIFI.sendHTTPframe(	IP
 * 						, "10.10.10.1"
 * 						, 80
 * 						, "GET$/getpost_frame_parser_pruebas.php?frame="
 * 						, frame.buffer, frame.length);
 * 
 ******************************************************************************/
uint8_t WaspWIFI::sendHTTPframe(uint8_t opt, 
								char* host, 
								int port, 
								char* request, 
								uint8_t* frame, 
								uint16_t len)
{	
	uint8_t result=0;
	char question[300];
	char aux[sizeof(answer)];
	char buffer[20];
	char HTTP_OK[20];
	unsigned long WTX_aux=0;
	unsigned long numBytes=0;
	uint8_t u1,u2,u3,u4,u5;	  
  
	// If the address is given by a IP address.
	if (opt==IP)
	{
		// Copy "set i h "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[32])));
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u1=sendCommand(question);
		u2=1;
	}
	// If the address is given by a URL address.
	else
	{
		// Turn on DNS. set ip host 0. 			
		// Copy "set i h 0\r"
		strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[54])));
		u1=sendCommand(question);	
		
		// Set the web server name			
		// Copy "set d n "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[41])));		
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u2=sendCommand(question);
	}
	
	// Set the web server port introduced as input		
	// Copy "set i r \r"
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[33])));
	snprintf(question, sizeof(question),"%s%u\r", buffer, port );		
	u3 = sendCommand(question);
						
	// set com remote
	// Copy "set c r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[56])));	
	snprintf(question, sizeof(question),"%s%s\r", buffer, request);	
	u4=sendCommand(question);
	
	// Append sensor data in ASCII hex format
	/* For example, if the incoming UART data is 6 bytes of binary data with 
	* hex values 0x01, 0xAB, 0x03, 0xFF, 0x05, and 0x06, the module sends this
	* string GET /user-prog.php?DATA=01AB03FF0506\n\n to the web server.
	*/
	// Copy "set o f 7\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[94])));
	u5=sendCommand(question);
	
	storeData();
	
	// update stats
	getStats();
	WTX_aux = WTX;	
	
	// If everything is Ok, even it is correctly connected.
	if ((u1==1)&&(u2==1)&&(u3==1)&&(u4==1)&&(u5==1)&&(isConnected()))
	{		
		// introduce a 500ms delay to wait for configuration before 
		// opening the HTTP connection
		delay(500);
		
		// Opens the HTTP connection.
		if(openHTTP())  
		{		
			for(uint16_t i = 0; i < len; i++)
			{
				printByte(frame[i],_uartWIFI);				
			}	
			
			// Reads the answer of the HTTP query.
			read(NOBLO,20000); 			
			
			// backup copy of the answer			
			memcpy(aux, answer, sizeof(answer));
			
			// Copy "200 OK"
			strcpy_P(HTTP_OK, (char*)pgm_read_word(&(table_WIFI[98])));			
			
			if( strstr(answer, HTTP_OK ) == NULL )
			{	
				#ifdef DEBUG_WIFI
				USB.println(F("200 OK not found"));
				#endif
				result = 0;
			}
						
			/* When HTTP retrieve is done, the WiFi module exits command mode so 
			 * it is mandatory to enter command mode again. Then, the module is 
			 * suposed to be already joined to network and a second 'getURL' call
			 * could be done as a retry if the first one fails
			 */
			if(commandMode()!=1)
			{
				#ifdef DEBUG_WIFI
				USB.println(F("CMD no entered"));	
				#endif	
				result = 0;
			}

			// update stats	
			getStats();
			WTX_aux=WTX-WTX_aux;
			
			// calculate number of frame bytes sent via TCP socket
			// Example: GET /userprog.php?DATA=01AB03FF0506\n\n
			// decrese numBytes by "GET /userprog.php?DATA=" and "\n\n"
			numBytes=WTX_aux-strlen(request)-4;
						
			// check number of sent bytes with frame length 
			// (multiplied by 2 because is translated from binary to ascii)
			if(numBytes < 2*len)
			{
				#ifdef DEBUG_WIFI
				USB.println(F("TX failed"));
				#endif
				result = 0;	
			}
			
			// HTTP OK				
			result = 1;
		}
		else
		{
			#ifdef DEBUG_WIFI
			USB.println(F("openHTTP failed"));
			#endif
			result = 0;
		}
	}
	else
	{
		result = 0;
	}

	if( result == 1 )
	{
		// get the backup of the answer when OK
		memcpy(answer, aux, sizeof(answer));
	}
	else
	{
		// when no success no commandMode function has been called
		// so, we enter in command mode in that case
		if(commandMode()!=1)
		{
			#ifdef DEBUG_WIFI
			USB.println(F("CMD no entered"));	
			#endif	
			result = 0;
		}
	}	
	
	return result;  
}




//! Sets the configuration and opens a TCP client connection.
uint8_t WaspWIFI::setTCPclient(	ipAddr ip_remote,
								uint16_t port_remote,
								uint16_t port_local)
{
	return setTCPclient(IP, (char*)ip_remote, port_remote, port_local);
}


//! Sets the configuration and opens a TCP client connection.
uint8_t WaspWIFI::setTCPclient(	uint8_t opt, 
								char*	host,
								uint16_t port_remote,
								uint16_t port_local)
{
	char question[128];
	char buffer[20];
	uint8_t u1,u2,u3,u4,u5;  
	
	// If the address is given by a IP address.
	if ( opt == IP )
	{						
		// Copy "set i h "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[32])));
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u1 = sendCommand(question);
		u2 = 1;
	}
	// If the address is given by a URL address.
	else if( opt == DNS )
	{		
		// Turn on DNS. set ip host 0. 			
		// Copy "set i h 0\r"
		strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[54])));
		u1 = sendCommand(question);	
		
		// Set the web server name			
		// Copy "set d n "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[41])));		
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u2 = sendCommand(question);
	}
	else
	{
		return 0;
	}
  
	// set the remote host port number
	// Copy "set i r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[33])));
	snprintf(question, sizeof(question),"%s%u\r", buffer, port_remote);
	u3=sendCommand(question);
	
	// set the local port number
	// Copy "set i l "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[34])));
	snprintf(question, sizeof(question), "%s%u\r", buffer, port_local);
	u4=sendCommand(question);
	
	// set com remote
	// Copy "set c r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[56])));
	snprintf(question, sizeof(question),"%s0\r", buffer);
	u5 = sendCommand(question);
	
	// Checks if everything is Ok, even if It's correctly connected.
	if ((u1==1)&&(u2==1)&&(u3==1)&&(u4==1)&&(u5==1)&&(isConnected()))
	{ 
		// Opens the Connection, and lets it open until calling close().
		return open();
	}
	
	#ifdef DEBUG_WIFI
	USB.println(F("setTCPclient ERROR")); 
	USB.print(F("u1:"));  
	USB.println(u1,DEC);  
	USB.print(F("u2:"));  
	USB.println(u2,DEC);  
	USB.print(F("u3:"));  
	USB.println(u3,DEC);  
	USB.print(F("u4:"));  
	USB.println(u4,DEC);  
	#endif
	
	return 0;
}
	

	
//! Sets the configuration and opens a TCP server connection.
uint8_t WaspWIFI::setTCPserver(uint16_t port_local)
{
	char question[50];
	char buffer[20];
	uint8_t u1;  
	
	// Copy "set i l "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[34])));
	
	// Configures TCP port and listens on the connection.
	snprintf(question, sizeof(question), "%s%d\r", buffer, port_local);
	u1=sendCommand(question);
	
	// Checks if everything is Ok, even if It's correctly connected.
	if ((u1==1)&&(isConnected()))
	{
		return 1;
	}
	return 0;
}


	
//! Sets the configuration and opens a UDP client connection.
uint8_t WaspWIFI::setUDPclient(	ipAddr ip_remote, 
								uint16_t port_remote, 
								uint16_t port_local)
{
	return setUDPclient(IP, (char*)ip_remote, port_remote, port_local);
}

	
//! Sets the configuration and opens a UDP client connection.
uint8_t WaspWIFI::setUDPclient(	uint8_t opt,
								char*	host, 
								uint16_t port_remote, 
								uint16_t port_local)
{
	char question[128];
	char buffer[20];
	uint8_t u1,u2,u3,u4,u5;
  
	// Configures UDP host and ports.
	
		// If the address is given by a IP address.
	if ( opt == IP )
	{						
		// Copy "set i h "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[32])));
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u1 = sendCommand(question);
		u2 = 1;
	}
	// If the address is given by a URL address.
	else if( opt == DNS )
	{		
		// Turn on DNS. set ip host 0. 			
		// Copy "set i h 0\r"
		strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[54])));
		u1 = sendCommand(question);	
		
		// Set the web server name			
		// Copy "set d n "
		strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[41])));		
		snprintf(question, sizeof(question),"%s%s\r", buffer, host);
		u2 = sendCommand(question);
	}
	else
	{
		return 0;
	}
	
	// Copy "set i r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[33])));	
	snprintf(question, sizeof(question),"%s%u\r", buffer, port_remote);
	u3=sendCommand(question);
		
	// Copy "set i l "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[34])));
	snprintf(question, sizeof(question), "%s%u\r", buffer, port_local);
	u4=sendCommand(question);	
		
	// set com remote
	// Copy "set c r "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[56])));
	snprintf(question, sizeof(question),"%s0\r", buffer);
	u5 = sendCommand(question);
	
	// Checks if everything is Ok, even if It's correctly connected.
	if ((u1==1)&&(u2==1)&&(u3==1)&&(u4==1)&&(u5==1)&&(isConnected()))
	{ 
		// Exits from command mode, and then the UDP messages 
		// can be sent and received.
		// Copy "exit\r"
		strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[58])));
		return sendCommand(question);	
	}
	return 0;

}
	
//! Sets the configuration and opens a UDP server connection.
uint8_t WaspWIFI::setUDPserver(uint16_t port_local)
{
	char question[50];
	char buffer[20];
	uint8_t u1;
	
	// Configures UDP port. 		
	// Copy "set i l "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[34])));
	snprintf(question, sizeof(question), "%s%u\r", buffer, port_local);
	u1=sendCommand(question);
	
	// Checks if everything is Ok, even if It's correctly connected.
	if ((u1==1)&&(isConnected()))
	{
		// Exits from command mode, and then the UDP messages 
		// can be sent and received.
		// Copy "exit\r"
		strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[58])));
		return sendCommand(question);
	}
  return 0;
}


int WaspWIFI::read(uint8_t blo)
{
	// wait for 2 secs when NOBLO is selected
	return read(blo,2000);
}	


//! Reads data from the opened connection.
int WaspWIFI::read(uint8_t blo, unsigned long time)
{
	// set length attribute to zero
	length=0;
  
	// Waits an answer.
	unsigned long t1=millis();
	
	// if it is blocking, wait until is received
	if (blo==BLO)
	{ 
		while(!serialAvailable(_uartWIFI)){} 
	}
	// if it isn't wait until something is received or 2 seconds
	else
	{
		while(!serialAvailable(_uartWIFI))
		{
			if (millis()-t1>time) return 0;
		}
	}  
	
	// Read all incoming data and store it in 'answer' buffer
	while( serialAvailable(_uartWIFI) && (length < (int)(sizeof(answer)-1) ) )
	{
		if (((answer[length]=serialRead(_uartWIFI))!='\0')&&( length < (int)(sizeof(answer)-1) ))
		{
			length++; 
		}
		latencyDelay();
    }
    answer[length]='\0'; 
  
	// Prints the answer.
	#ifdef DEBUG_WIFI
    USB.print(F("R: "));
    USB.println(answer); 
    #endif
    
	// Returns the number of characters of the answer.
	return length;
}
	
//! Sends data to the opened connection.
void WaspWIFI::send(char* data)
{	
	// Writes what we want to send on the UART. 
	printString(data,_uartWIFI);	
	
	// delay not lo lose any byte 
	delay(3);  
}

//! Sends data to the opened connection.
void WaspWIFI::send(uint8_t* data, uint16_t len)
{ 
	// Writes what we want to send on the UART. 
	for (uint16_t i=0; i<len; i++)
	{
		printByte(data[i],_uartWIFI);
	}   
	
	// delay not lo lose any byte 
	delay(3);
}


//! Closes current connection.
uint8_t WaspWIFI::close()
{
	char question[20];
	
	// Enters in command mode.
	while(commandMode()!=1){}
	
	// Send command 'close'.
	// Copy "close\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[59])));
	return sendCommand(question);
}

//! Configures and sends broadcast packages.
uint8_t WaspWIFI::sendAutoBroadcast(ipAddr ip_network, 
									uint16_t port_remote, 
									uint8_t interval, 
									char* id)
{ 
	char question[128];
	char buffer[20];
	uint8_t u0, u1, u2, u3, u4;
  
	// Configure Broadcast settings:
	
	// set UDP connection Options
	u0=setConnectionOptions(UDP);
		
	// set broadcast address
	// Copy "set b a "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[60])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, ip_network);
	u1=sendCommand(question);
 
	// set broadcast interval
	// Copy "set b i "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[61])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, interval); //2-256
	u2=sendCommand(question);
		
	// set broadcast port
	// Copy "set b p "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[62])));
	snprintf(question, sizeof(question), "%s%u\r", buffer, port_remote);
	u3=sendCommand(question);
		
	// set configurable Device ID (this is part of the UDP packet sent)
	// Copy "set o d "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[63])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, id);
	u4=sendCommand(question);
	
	if ((u0==1)&&(u1==1)&&(u2==1)&&(u3==1)&&(u4==1))
		// If everything Ok, automatically UDP broadcast messages are sent.
		return 1;
	else
		return 0;
}
	
//! Configures and opens an adhoc connection.
uint8_t WaspWIFI::setAdhocOptions(uint16_t beacon, uint16_t probe_interval)
{
	char question[50];
	char buffer[20];
	uint8_t u0, u1, u2;
  
	// Configure ADHOC settings.
	u0=setDHCPoptions(AUTO_IP);
		
	// Copy "set a b "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[64])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, beacon);
	u1=sendCommand(question);
		
	// Copy "set a p "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[65])));
	snprintf(question, sizeof(question), "%s%d\r", buffer, probe_interval);
	u2=sendCommand(question);
	
	if ((u0==1)&&(u1==1)&&(u2==1))
		// If everything correct, call join_mode -> create_AdHoc.
		return setJoinMode(CREATE_ADHOC);
	else
		return 0;
}

// Device Configuration ///////////////////////////////////////////////////////

//! Reboots the device (ON-OFF-ON).
void WaspWIFI::reset()
{
	char question[20];
	uint8_t i=0;
	
	// Sends reboot command.
	// Copy "reboot\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[0])));
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer from the UART.	
	if(!waitForData(8,1000))
	{
		return (void)0;
	}
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0';
	
	// re-initilizate
	ON(_uartWIFI);
}
	
	
//! Restores the default settings of the device.
void WaspWIFI::resetValues()
{
	char question[20];
	
	// Sends reset command.
	// Copy "factory RESET\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[66])));
	sendCommand(question);
	delay(500);
	
	serialFlush(_uartWIFI); 
	printString("reboot\r",_uartWIFI); 
	delay(500);
	
	// switch ON the module and enter in command mode
	ON(_uartWIFI);
}

	
	
//! Synchronizes the time.
void WaspWIFI::synchronizeTime()
{
	char question[20];
	
	// Copy "time\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[68])));
	sendCommand(question);  
}
	
	
//! Performs a DNS query on the supplied hostname.
int WaspWIFI::resolve(char* name)
{
	char question[128];
	char buffer[20];
	uint16_t i=0;
  
  	// set length attribute to zero
	length=0;
  
	// Sends lookup command.
	// Copy "lookup "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[69])));
	snprintf(question, sizeof(question), "%s%s\r", buffer, name);
	
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
	
	// Waits an answer from the module.
	i=strlen(question);
	i=i+5;
	if(!waitForData(i))
	{
		return 0;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0';  
	
	// set length attribute to number of read bytes
	length=i;
	
	// Prints the result of the query.  
	//~ #ifdef DEBUG_WIFI
	USB.print(F("R: ")); 
	USB.println(answer); 
	//~ #endif
	
	return length;
}
	
//! Sets the UART baud rate.
uint8_t WaspWIFI::setBaudRate(long val)
{
	char question[50];
	char buffer[20];
	
	// Copy "set u b "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[70])));
	snprintf(question, sizeof(question), "%s%lu\r", buffer, val);
	return sendCommand(question);
}
	
//! Saves current configuration.
uint8_t WaspWIFI::storeData()
{
	char question[20];
	
	// Copy "save\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[71])));
	return sendCommand(question);
}

// Status Information /////////////////////////////////////////////////////////

//! Checks if the module is connected to the Access Point 
//! (Check if it has an IP address).
bool WaspWIFI::isConnected()
{	
	return isConnected(10000);
}

//! Checks if the module is connected to the Access Point 
//! (Check if it has an IP address).
bool WaspWIFI::isConnected(unsigned long timeout)
{
	char question[20];
	char buffer[20];	
	bool result = false;	
	
	#ifdef DEBUG_WIFI
	USB.println(F("get ip\r"));  
	#endif
	
	// Copy "get ip\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[72])));	
	// Copy "IF=UP"
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[73])));
	
	result = sendCommand( question, buffer, timeout);
		
	if (contains(answer,buffer))
	{ 	
		#ifdef DEBUG_WIFI
		USB.println(F("contains IF=UP"));  
		#endif		
	}
	else 
	{ 	
		#ifdef DEBUG_WIFI
		USB.println(F("DOES NOT contain IF=UP"));  
		USB.println(answer);		
		#endif 
	}
	
	return result;
}

//! Displays connection status
void WaspWIFI::getConnectionInfo()
{
	char question[20];
	uint16_t i=0;
	uint8_t temp;
  
	// Sends command over the UART.
	// Copy "show c\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[74])));
	
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	if(!waitForData(i))
	{
		return (void)0;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0';	
	
	/* answer must contain a response formatted as 8<XYZ> where 'X' indicates the 
	 * channel; 'Y' shows info about DNS server and authentication; and 'Z' shows 
	 * the TCP status */
	char* ptr=strchr(answer, '8');
	
	if( ptr == NULL )
	{
		#ifdef DEBUG_WIFI
		USB.print(F("error getting Connection Info")); 		
		#endif	
		return (void)0;
	}
	
	#ifdef DEBUG_WIFI
	USB.print(F("Chann: ")); 
	USB.println(ptr[1]);
	#endif	
  
	// Parses the answer and shows it.
	if (int(ptr[2]>=int('A')))
		temp = int(ptr[2])-int('A')+10;
	else
		temp = int(ptr[2])-int('0');
		
	if ( (temp & 1) == 1 )
		USB.println(F("Assoc: OK"));	
	if ( (temp & 2) == 2 )
		USB.println(F("Authen: OK"));	
	if ( (temp & 4) == 4 )
		USB.println(F("DNS server = contacted"));
	if ( (temp & 8) == 8 )
		USB.println(F("DNS found = resolved"));
	if (ptr[3]=='0')
		USB.println(F("TCP status = Idle"));
	if (ptr[3]=='1')
		USB.println(F("TCP status = Connected"));
	if (ptr[3]=='3')
		USB.println(F("TCP status = NOIP"));
	if (ptr[3]=='4')
		USB.println(F("TCP status = Connecting")); 	
}
	
	
//! Displays current network status, association, authentication, etc.
void WaspWIFI::getAPstatus()
{
	char question[20];
	uint16_t i=0;
  
	// Copy "show n\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[75])));
	
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
	
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	if(!waitForData(i))
	{
		return (void)0;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	//~ #ifdef DEBUG_WIFI	
	// seek start of info in 'answer
	char* start=strstr(answer,"SSid");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	//~ #endif
}


//! Displays current last received signal strenght.
void WaspWIFI::getRSSI()
{
	char question[20];
	uint16_t i=0;
    
	// Copy "show r\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[76])));
 
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0';	
	
	/* The response is something like:
		RSSI=(-43) dBm
		<2.32> 
	 */ 
	
	// init variable
	this->rssi = 0;
	char rssi_str[10];
	char* start_val = strchr(answer,'(');
	char* end_val = strchr(answer,')');
	if( (start_val != NULL)&&(end_val != NULL) )
	{
		int len = (int)end_val-(int)start_val -1 ;
		if( len < (int)sizeof(rssi_str) )
		{
			memset(rssi_str, 0x00, sizeof(rssi_str) );
			memcpy(rssi_str, start_val+1, len);
			this->rssi = atoi(rssi_str);
		}
	}
	
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"RSSI");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}
	
	
//! Displays current statistics, packet rx/tx counters, etc.
void WaspWIFI::getStats()
{
	char question[20];
	uint16_t i=0;  
	char* start;
    char* end;
    char value[50];	
    uint16_t m;	
    
	// Copy "show s\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[77])));
		
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.	
	i=strlen(question);
	i=i+5;	
	if( !waitForData(i) )
	{
		return (void)0;
	}
	
	// delay to wait for all data
	//~ delay(100);
	delay(500); // at 9600 is slower
	
	// get answer
	memset( answer, 0x00, sizeof(answer) );
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
	}
	answer[i]='\0'; 
		
	// Show the information
	#ifdef DEBUG_WIFI		
	char* st= strstr((const char*)answer,"Conns");
	if( st!=NULL )
	{
		USB.println(st);	
	}
	#endif
	
	//initialize attributes
	
	/// store 'WRX' variable from answer
	start=strstr((const char*)answer,"WRX=");	
	if( start != NULL)
	{
		// put pointer to the beginning of the value to be read		
		start=strchr((const char*)start,'/');	
		start=start+1;
		
		// seek end of value
		end=strchr((const char*)start,',');		
		if( end != NULL)
		{
			// get value in characters	
			memset(value, 0x00, sizeof(value) );
			for(m = 0; m < sizeof(value)-1; m++)
			{
				value[m]=start[m];
				if( start[m] == ',' )
				{
					break;
				}
			}
			value[m]='\0';
			// convert from string to integer
			WRX = atol(value);			
		}
		else
		{
			WRX = -1;			
		}		
	}
	else
	{
		WRX = -1;
	}
	
	
	/// store 'WTX' variable from answer
	start=strstr((const char*)answer,"WTX=");	
	if( start != NULL)
	{
		// put pointer to the beginning of the value to be read		
		start=strchr((const char*)start,'/');	
		start=start+1;
		
		// seek end of value
		end=strchr((const char*)start,',');		
		if( end != NULL)
		{
			// get value in characters	
			memset(value, 0x00, sizeof(value) );		
			for(m = 0; m < sizeof(value)-1; m++)
			{
				value[m]=start[m];
				if( start[m] == ',' )
				{
					break;
				}
			}
			value[m]='\0';
			// convert from string to integer
			WTX = atol(value);			
		}
		else
		{
			WTX = -1;			
		}		
	}
	else
	{
		WTX = -1;
	}
	
	
	/// store 'FlwSet' variable from answer
	start=strstr((const char*)answer,"FlwSet=");	
	if( start != NULL)
	{
		// put pointer to the beginning of the value to be read
		start=start+strlen("FlwSet=");
		
		// seek end of value
		end=strchr((const char*)start,',');		
		if( end != NULL)
		{
			// get value in characters	
			memset(value, 0x00, sizeof(value) );		
			for(m = 0; m < sizeof(value)-1; m++)
			{
				value[m]=start[m];
				if( start[m] == ',' )
				{
					break;
				}
			}
			value[m]='\0';
			// convert from string to integer
			flwSet=atoi(value);			
		}
		else
		{
			flwSet=-1;			
		}		
	}
	else
	{
		flwSet=-1;
	}	
	
	#ifdef DEBUG_WIFI		
	USB.print(F("WRX:"));	
	USB.println(WRX,DEC);
	USB.print(F("WTX:"));
	USB.println(WTX,DEC);
	USB.print(F("flwSet:"));
	USB.println(flwSet);	
	#endif	
}
	
//! Displays number of seconds since last powerup or reboot.
void WaspWIFI::getUpTime()
{
	char question[20];
	uint16_t i=0;
  
	// Copy "show t\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[78])));
	
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
	// Waits an answer.	
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"Time");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}
	
//! Displays all adhoc settings.
void WaspWIFI::getAdhocSettings()
{
	char question[20];
	uint16_t i=0;
  
	// Copy "get a\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[79])));
	
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
	
	// Waits an answer.	
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"Beacon");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}
	
//! Displays the broadcast settings.
void WaspWIFI::getBroadcastSettings()
{
	char question[20];
	uint16_t i=0;
  
	// Copy "get b\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[80])));
	
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"BCAST=");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}

//! Displays comm. settings
void WaspWIFI::getComSettings()
{
	char question[20];
	uint16_t i=0;
  
	// Copy "get c\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[81])));
	
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 

	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"OPEN=");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}

//! Displays DNS settings.
void WaspWIFI::getDNSsettings()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "get d\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[82])));
	
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"DNS=");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}

//! Displays FTP settings.
void WaspWIFI::getFTPsettings()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "get f\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[83])));
  
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
	
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"FTP=");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}

//! Displays IP address and port number settings.
void WaspWIFI::getIP()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "get i\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[84])));
  
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	
	memset( answer, 0x00, sizeof(answer) );
		
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	//~ #ifdef DEBUG_WIFI		
	// seek start of info in 'answer
	char* start=strstr(answer,"IF=");
	if( start!=NULL )
	{
		// Shows the info
		USB.println(start);		
	}	
	else
	{
		USB.println(F("No ip"));
	}
	//~ #endif
	
}

//! Displays the device MAC address.
void WaspWIFI::getMAC()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "get m\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[85])));
  
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"Mac Addr=");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}

//! Displays the option settings like device ID.
void WaspWIFI::getOptionSettings()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "get o\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[86])));
	
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);

	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"JoinTmr=");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}

//! Displays system settings, sleep, wake timers,etc.
void WaspWIFI::getSystemSettings()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "get s\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[87])));
  
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"get s");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(&start[6]);
	#endif
}


//! Displays the time server UDP address and port number.
void WaspWIFI::getTime()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "get t\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[88])));

	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
	
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"TimeEna=");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}

//! Displays the ssid, channel and other wlan settings.
void WaspWIFI::getWLANsettings()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "get w\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[89])));
	
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"SSID=");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}


//! Displays the UART settings.
void WaspWIFI::getUARTsettings()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "get u\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[90])));
  
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0'; 
	
	#ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"Baudrate=");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	#endif
}

//! Returns the software release version of the WIFI module.
void WaspWIFI::getVersion()
{
	char question[20];
	uint16_t i=0;
	
	// Copy "ver\r"
	strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[91])));
	
	// Sends the command.
	serialFlush(_uartWIFI);
	
	printString(question,_uartWIFI);
  
	// Waits an answer.
	i=strlen(question);
	i=i+5;
	// Waits an answer from the UART
	if(!waitForData(i))
	{		
		return (void)false;
	}
	i=0;
	while(serialAvailable(_uartWIFI))
	{
		if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
		{
			i++;
		}
		latencyDelay();
	}
	answer[i]='\0';
	
	//~ #ifdef DEBUG_WIFI
	// seek start of info in 'answer
	char* start=strstr(answer,"Ver");
	
	if( start==NULL )
	{
		return (void)0;
	}
	
	// Shows the info
	USB.println(start);
	//~ #endif
}


/*
 * sets the flush size. An IP packet will be sent each time “value” bytes are
 * received. Default is 64 bytes. It is recommended to set this value to the
 * largest possible setting to maximize TCP/IP performance. Maximum value = 
 * 1420 (at 9600) bytes. 
 */
uint8_t WaspWIFI::setCommSize(unsigned int val)
{
	char question[50];	
	char buffer[20];
	
	// Copy "set c s "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[92]))); 
	
	snprintf(question, sizeof(question), "%s%d\r",buffer,val);
	return sendCommand(question);
}

/*
 * sets the flush timer, this is used to make sure that any partial data sitting 
 * the RX buffer if no additional data is seen for “value” milliseconds. For 
 * example set comm time 1000 would wait for 1 second after no data was sent
 */
uint8_t WaspWIFI::setCommTimer(unsigned int val)
{
	char question[50];	
	char buffer[20];
	
	// Copy "set c t "
	strcpy_P(buffer, (char*)pgm_read_word(&(table_WIFI[93]))); 
	
	snprintf(question, sizeof(question), "%s%d\r",buffer,val);
	return sendCommand(question);
}


/*
 * This function waits to have "numBytes" bytes available in input buffer data.
 * If this number of bytes are present in UART input buffer then return '1'
 * If they are not received within a period of time return '0'. 
 * 
 */
uint8_t WaspWIFI::waitForData(int numBytes)
{	
	return waitForData(numBytes, FTP_TIMEOUT);
}


/*
 * This function waits to have "numBytes" bytes available in input buffer data.
 * If this number of bytes are present in UART input buffer then return '1'
 * If they are not received within a period of time return '0'. 
 * 
 */
uint8_t WaspWIFI::waitForData(int numBytes, unsigned long timeout)
{	
	unsigned long previous=millis();
	
	while(serialAvailable(_uartWIFI)<numBytes )
	{
		if(	millis()-previous > timeout)
		{
			return 0;
		}
		if(	millis() < previous )
		{
			previous = millis();
		}
	}
	return 1;
}

/*
 * This function seeks the pattern indicated inside the input array of bytes
 * which is delimited by length number of bytes.
 * Returns:
 * 	'-1' if pattern is not inside the input array
 * 	'index' of the pattern in the case it is found
 * 
 */
int WaspWIFI::findPattern(uint8_t* input, char* pattern, int len)
{
	bool success;
	int patLen=strlen(pattern);
	
	if(len<patLen)
	{
		return -1;
	}
	
	// iterate through the input array of bytes	
	for(int i = 0; i < len-patLen+1; i++)
	{
		// check the first byte and if there is a coincidence
		// then check the rest of the pattern
		if( input[i] == pattern[0] )
		{
			success=true;
			for(int j=1; j<patLen; j++)
			{
				if( input[i+j] != pattern[j] )
				{			
					// no coincidence, seek more
					success=false;
					j=patLen;
					//~ break;
				}
			}
			// if pattern matches, then return the index to the pattern		
			if( success == true )
			{
				return i;
			}
		}
		
	}
	
	return -1;
}


/* requestOTA() - It downloads a new OTA file if OTA is necessary
 *
 * This function downloads a new OTA file if OTA is necessary
 *
 * Returns  
 * 	'0' if error 
 * 	'-1' if error downloading UPGRADE.TXT
 * 	'-2' if filename in UPGRADE.TXT is not a 7-byte name
 * 	'-3' if no FILE label is found in UPGRADE.TXT
 * 	'-4' if NO_FILE is defined as FILE in UPGRADE.TXT
 * 	'-5' if no PATH label is found in UPGRADE.TXT
 * 	'-6' if no SIZE label is found in UPGRADE.TXT
 * 	'-7' if no VERSION label is found in UPGRADE.TXT
 * 	'-8' if version indicated in UPGRADE.TXT is lower/equal to Waspmote's version
 * 	'-9' if file size does not match the indicated in UPGRADE.TXT
 * 	'-10' if error downloading binary file
*/
int8_t WaspWIFI::requestOTA()
{
	int8_t ans;
	char* str_pointer;
	char aux_name[8];
	char path[60];
	char aux_str[10];
	long int aux_size;
	uint8_t aux_version;
	int len;
	char slash[] = "/";
	char dot[] = ".";


	// set to zero the buffer 'path'
	memset(path, 0x00, sizeof(path));
	memset(answer, 0x00, sizeof(answer));
	
	// set SD ON and delete actual OTA_ver_file
	SD.ON();
	SD.goRoot();
	SD.del(OTA_ver_file);
	SD.OFF();
	
	#ifdef DEBUG_WIFI
	USB.println(F("Downloading OTA VER FILE"));
	#endif
	
	// get OTA_ver_file
	ans = getFile( (char*)OTA_ver_file, slash, dot);
	
    // check if file was downloaded correctly
    if( ans == 1)
    {
		#ifdef DEBUG_WIFI
		USB.println(F("OTA_ver_file downloaded OK")); 
		#endif
	} 
    else
    {
		#ifdef DEBUG_WIFI
		USB.println(F("ERROR downloading OTA_ver_file"));
		#endif
		return -1;
    }
	
	// analyze OTA_ver_file 
	SD.ON();
	SD.goRoot();
	
	// Reads the file and copy to 'answer' buffer
	strcpy(answer, SD.cat(OTA_ver_file, 0, sizeof(answer)));
	
	/// 1. Search the file name
	str_pointer = strstr(answer, "FILE:");
	if (str_pointer != NULL)
	{	
		// Copy the FILE contents:
		// get string length and check it is equal to 7
		len = strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		if( len != 7 )
		{
			#ifdef DEBUG_WIFI
			USB.print(F("len:"));
			USB.println(len);
			#endif			
			return -2;
		}
		// copy string
		strncpy(aux_name, strchr(str_pointer, ':')+1, 7);
		aux_name[7] = '\0';
				
		#ifdef DEBUG_WIFI
		USB.print(F("FILE:"));
		USB.println(aux_name);	
		#endif
	}
	else
	{
		#ifdef DEBUG_WIFI
		USB.println(F("No FILE label"));
		#endif
		SD.OFF();
		return -3;
	}	
	
	/// 2. Check if NO_FILE is the filename
	if(strcmp(aux_name,NO_OTA) == 0)
	{
		#ifdef DEBUG_WIFI
		USB.println(NO_OTA);	
		#endif
		return -4;
	}
	
	/// 3. Search the path 
	str_pointer = strstr(answer, "PATH:");
	if (str_pointer != NULL)
	{
		// copy the PATH contents
		len = strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		strncpy(path, strchr(str_pointer, ':') + 1, len );
		path[len] = '\0';
					
		#ifdef DEBUG_WIFI
		USB.print(F("PATH:"));
		USB.println(path);
		#endif		
				
		// delete actual program	
		SD.del(aux_name);	
	}
	else
	{	
		#ifdef DEBUG_WIFI
		USB.println(F("No PATH label"));
		#endif
		SD.OFF();
		return -5;
	}
	
	/// 4. Search file size 
	str_pointer = strstr(answer, "SIZE:");
	if (str_pointer != NULL)
	{
		// copy the SIZE contents
		len=strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		// check length does not overflow
		if( len >= (int)sizeof(aux_str) )
		{
			len = sizeof(aux_str)-1;
		}
		strncpy(aux_str, strchr(str_pointer, ':')+1, len);
		aux_str[len] = '\0';
		
		// converto from string to int
		aux_size = atol(aux_str);
					
		#ifdef DEBUG_WIFI
		USB.print(F("SIZE:"));
		USB.println(aux_size);
		#endif			
	}
	else
	{	
		#ifdef DEBUG_WIFI
		USB.println(F("No SIZE label"));
		#endif
		SD.OFF();
		return -6;
	}
	
	/// 5. Search Version
	str_pointer = strstr(answer, "VERSION:");
	if (str_pointer != NULL)
	{
		// copy the SIZE contents
		len = strchr(str_pointer, '\n')-1-strchr(str_pointer, ':');
		// check length does not overflow
		if( len >= (int)sizeof(aux_str))
		{
			len = sizeof(aux_str)-1;
		}
		strncpy(aux_str, strchr(str_pointer, ':')+1, len);
		aux_str[len] = '\0';	
		
		// convert from string to uint8_t
		aux_version=(uint8_t)atoi(aux_str);
					
		#ifdef DEBUG_WIFI
		USB.print(F("VERSION:"));
		USB.println(aux_version,DEC);
		#endif			
	}
	else
	{	
		#ifdef DEBUG_WIFI
		USB.println(F("No VERSION label"));
		#endif
		SD.OFF();
		return -7;
	}	
	
	// get actual program version
	uint8_t prog_version = Utils.getProgramVersion();
	// get actual program name (PID)
	char prog_name[8];
	Utils.getProgramID(prog_name);
	
	// check if version number 
	#ifdef CHECK_VERSION
	if( strcmp(prog_name,aux_name)==0 )
	{
		if( prog_version >= aux_version )
		{
			// if we have specified the same program id and lower/same version 
			// number, then do not proceed with OTA
			#ifdef DEBUG_WIFI
			USB.print(F("Invalid version\nactual:"));
			USB.println(prog_version,DEC);
			USB.print(F("new:"));
			USB.println(aux_version,DEC);
			#endif
			return -8;
		}
	}	
	#endif
	
	///6. get binary file and perform OTA
	#ifdef DEBUG_WIFI
	USB.println(F("Downloading OTA FILE"));
	#endif	
	
	// check if path matches root directory, then set "."				
	if(strcmp(path,slash)==0)
	{
		strncpy( path, dot, strlen(dot) );
	}		
	
	// get binary file
	ans = getFile((char*)aux_name, slash, path);
		
	if (ans == 1)
	{
		// check if size matches
		SD.ON();
		// get file size
		int32_t sd_file_size = SD.getFileSize(aux_name);
		if( sd_file_size != aux_size )
		{
			#ifdef DEBUG_WIFI
			USB.println(F("Size does not match"));
			USB.print(F("sd_file_size:"));
			USB.println(sd_file_size);
			USB.print(F("UPGRADE.TXT size field:"));
			USB.println(aux_size);			
			#endif	
			SD.OFF();
			return -9;			
		}
		#ifdef DEBUG_WIFI
		SD.ls();
		#endif
		Utils.loadOTA(aux_name,aux_version);
		return 1;
	}
	else
	{
		#ifdef DEBUG_WIFI
		USB.println(F("Error getting binary"));
		#endif	
		SD.OFF();
		return -10;
	}
		
	
	return 0;
}

//! Set RTC date taken from WiFi module
uint8_t WaspWIFI::setRTCfromWiFi()
{
	
	char question[20];
	uint16_t i=0;
	uint32_t timelong;
	timestamp_t date;
	
	
	// Check if module did set the time
	// If it fails 3 times will return error
	uint8_t retries = 3;
	while (retries > 0)
	{
		synchronizeTime();
		// Wait for 100 ms so module set the time
		delay(100);
		
		// Copy "show t t\r"
		strcpy_P(question, (char*)pgm_read_word(&(table_WIFI[107])));

		// Sends the command.
		serialFlush(_uartWIFI);
		
		printString(question,_uartWIFI);
		
		// Waits an answer.
		i=strlen(question);
		i=i+5;
		
		// Waits an answer from the UART
		if(!waitForData(i))
		{		
			return 1;
		}
		i=0;
		while(serialAvailable(_uartWIFI))
		{
			if (((answer[i]=serialRead(_uartWIFI))!='\0')&&(i<(sizeof(answer)-1)))
			{
				i++;
			}
			latencyDelay();
		}
		answer[i]='\0'; 
		retries--;
		// Check if module did set the time
		if ( findPattern((uint8_t*)answer, (char*)"NOT SET",i) == -1 )
		{
			retries = 0;
		}
		else if ((findPattern((uint8_t*)answer, (char*)"NOT SET",i)!=-1) && retries == 0)
		{
			return 1;
		}
	}
	
	// seek start of info in 'answer'
	char* start = strstr(answer,"RTC");
	char* end = strchr(start,'\r');
	if( start!=NULL && end!=NULL )
	{
		start=strchr(start,'=');
		
		if (start!=NULL)
		{
			// calculate length
			start ++;
			uint8_t len = 0;
			len = end-start;
			
			// check if epoch time will fix in time
			char time[11];
			if( len > sizeof(time)-1 )
			{
				return 1;
			}
			
			// save epoch time in timelong
			memset(time,'\0',sizeof(time));
			memcpy(time,start,len);
			sscanf(time,"%lu",&timelong);
			int32_t aux = 3600*(int32_t)RTC.getGMT();
			timelong += aux;

			// set new time based on server WIFI epoch time
			RTC.breakTimeAbsolute(timelong, &date);	
			RTC.ON();
			RTC.setTime(date.year,
						date.month,
						date.date,
						date.day,
						date.hour,
						date.minute,
						date.second);
			return 0;
		}
	}
	return 1;
}

// Preinstantiate Objects /////////////////////////////////////////////////////

WaspWIFI WIFI=WaspWIFI();

///////////////////////////////////////////////////////////////////////////////
