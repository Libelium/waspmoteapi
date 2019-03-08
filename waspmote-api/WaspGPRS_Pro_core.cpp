/*
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.2
 *  Design:			David Gascón
 *  Implementation:	Alejandro Gállego
 */


#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif


#include "WaspGPRS_Pro_core.h"





const char POWER_FULL[]			PROGMEM = "+CFUN=1";		//0
const char POWER_RF_OFF[]		PROGMEM = "+CFUN=4";		//1
const char POWER_MIN[]			PROGMEM = "+CFUN=0";		//2
const char POWER_NO_SLEEP[]		PROGMEM = "+CSCLK=0";		//3
const char POWER_SLEEP[]		PROGMEM = "+CSCLK=2";		//4

const char SET_TIME[]			PROGMEM = "+CCLK=";			//5

const char AT_PIN[]				PROGMEM = "+CPIN=";			//6
const char AT_CHANGE_PASSWORD[]	PROGMEM = "+CPWD=";			//7

const char AT_GPRS_IMEI[]		PROGMEM = "+GSN";			//8
const char AT_GPRS_IMSI[]		PROGMEM = "+CIMI";			//9

const char AT_COMMAND_MODE[]	PROGMEM = "+++";			//10
const char AT_DATA_MODE[]		PROGMEM = "O";				//11
const char AT_DATA_MODE_R[]		PROGMEM = "CONNECT";		//12
const char AT_DATA_MODE_FAIL[]	PROGMEM = "NO CARRIER";		//13

const char AT_GPRS_CHECK_ATT[]	PROGMEM = "+CGATT?";		//14
const char AT_GPRS_CHECK_ON[]	PROGMEM = "+CGATT: 1";		//15
const char AT_GPRS_CHECK_OFF[]	PROGMEM = "+CGATT: 0";		//16
const char AT_GPRS_ATT_ON[]		PROGMEM = "+CGATT=1";		//17
const char AT_GPRS_ATT_OFF[]	PROGMEM = "+CGATT=0";		//18
const char AT_GPRS_CELLID[]		PROGMEM = "+CENG";			//19
const char AT_GPRS_RSSI[]		PROGMEM = "+CSQ";			//20

//Various
const char AT_GET_OPERATOR[]		PROGMEM = "+COPS?";		//21
const char AT_GET_OPERATOR_R[]		PROGMEM = "+COPS:";		//22
const char AT_SET_PREF_OPERATOR[]	PROGMEM = "+COPS=";		//23
const char AT_OPERATOR_LIST[]		PROGMEM = "+CPOL?";		//24
const char AT_OPERATOR_LIST_R[]		PROGMEM = "+CPOL:";		//25
const char AT_WHO_AM_I[]			PROGMEM = "+CGMM";		//26
const char AT_FIRMWARE[]			PROGMEM = "+CGMR";		//27
const char AT_FIRMWARE_R[]			PROGMEM = "Revision:";	//28

const char AT_IP_SET_DNS[]			PROGMEM = "+CDNSCFG=";	//29

// FTP_HTTP Constants
const char AT_GPRS_CFG[]			PROGMEM = "+SAPBR=";	//30
const char AT_GPRS[]				PROGMEM = "GPRS";		//31

//Set mode and connection constants
const char NUMERIC_ERROR[]		PROGMEM = "+CMEE=1";		//32
const char NO_ECHO[]			PROGMEM = "E0";				//33
const char CHECK[]				PROGMEM = "+CREG?";			//34
const char HOME_NETWORK[]		PROGMEM = "+CREG: 0,";		//35
const char ROAMING[]			PROGMEM = "+CREG: 0,5";		//36
const char CON_TYPE[]			PROGMEM = "CONTYPE";		//37
const char APN[]				PROGMEM = "APN";			//38
const char USER[]				PROGMEM = "USER";			//39
const char PWD[]				PROGMEM = "PWD";			//40

//Constants for manageIncomingData
const char INCOMING_CALL[]		PROGMEM = "+CLIP";			//41
const char INCOMING_SMS[]		PROGMEM = "+CMTI";			//42

const char GET_BAND[]			PROGMEM = "+CBAND";			//43
const char BEARER_RES[]			PROGMEM = "+SAPBR: ";		//44
const char AT_GPRS_CHECK[]		PROGMEM = "+CGREG?";		//45
const char AT_GPRS_CHECK_RES[]	PROGMEM = "+CGREG: 0,";		//46

const char* const table_MISC[] PROGMEM =
{
	//Power constants
	POWER_FULL,				//0
	POWER_RF_OFF,			//1
	POWER_MIN,				//2
	POWER_NO_SLEEP,			//3
	POWER_SLEEP,			//4

	SET_TIME,				//5

	AT_PIN,					//6
	AT_CHANGE_PASSWORD,		//7

	AT_GPRS_IMEI,			//8
	AT_GPRS_IMSI,			//9

	AT_COMMAND_MODE,		//10
	AT_DATA_MODE,			//11
	AT_DATA_MODE_R,			//12
	AT_DATA_MODE_FAIL,		//13

	AT_GPRS_CHECK_ATT,		//14
	AT_GPRS_CHECK_ON,		//15
	AT_GPRS_CHECK_OFF,		//16
	AT_GPRS_ATT_ON,			//17
	AT_GPRS_ATT_OFF,		//18
	AT_GPRS_CELLID,			//19
	AT_GPRS_RSSI,			//20

	//Various
	AT_GET_OPERATOR,		//21
	AT_GET_OPERATOR_R,		//22
	AT_SET_PREF_OPERATOR,	//23
	AT_OPERATOR_LIST,		//24
	AT_OPERATOR_LIST_R,		//25
	AT_WHO_AM_I,			//26
	AT_FIRMWARE,			//27
	AT_FIRMWARE_R,			//28

	AT_IP_SET_DNS,			//29

	// FTP_HTTP Constants
	AT_GPRS_CFG,			//30
	AT_GPRS,				//31

	//Set mode and connection constants
	NUMERIC_ERROR,			//32
	NO_ECHO,				//33
	CHECK,					//34
	HOME_NETWORK,			//35
	ROAMING,				//36
	CON_TYPE,				//37
	APN,					//38
	USER,					//39
	PWD,					//40

	//Constants for manageIncomingData
	INCOMING_CALL,			//41
	INCOMING_SMS,			//42


	GET_BAND,				//43
	BEARER_RES,				//44
	AT_GPRS_CHECK,			//45
	AT_GPRS_CHECK_RES,		//46
};


#if GSM_FUSE

	// Calls Constants
const char AT_CALL[]				PROGMEM = "D";				//0
const char AT_HANG[]				PROGMEM = "H";				//1
const char AT_DTMF[]				PROGMEM = "+CLDTMF=";		//2

	// Voice Mode Constants
const char AT_ID_INCALL[]			PROGMEM = "+CLIP=1";		//3

	// SMS Constants
const char AT_SMS[]					PROGMEM = "+CMGS=";			//4
const char AT_SMS_R[]				PROGMEM = ">";				//5
const char AT_SMS_MODE[]			PROGMEM = "+CMGF=1";		//6
const char AT_SMS_INFO[]			PROGMEM = "+CNMI=2,1,0,0,0";//7
const char AT_SMS_READ[]			PROGMEM = "+CMGR=";			//8
const char AT_SMS_MEMORY[]			PROGMEM = "+CPMS=";			//9
const char AT_SMS_MEMORY_R[]		PROGMEM = "+CPMS: ";		//10
const char AT_SMS_DELETE[]			PROGMEM = "+CMGD=";			//11

	// Sound Constants
const char AT_SOUND_INT[]			PROGMEM = "#CAP=2";			//12
const char AT_SOUND_EXT[]			PROGMEM = "#CAP=1";			//13
const char AT_VOLUME_SET[]			PROGMEM = "+CLVL=";			//14

const char AT_SPEAKER_VOLUME[]		PROGMEM = "L";				//15
const char AT_SPEAKER_MODE[]		PROGMEM = "M";				//16
const char AT_CLIP_MODE[]			PROGMEM = "+CLIP=";			//17
const char AT_CLIR_MODE[]			PROGMEM = "+CLIR=";			//18
const char AT_PHONE_ACTIVITY[]		PROGMEM = "+CPAS";			//19
const char AT_PHONE_ACTIVITY_R[]	PROGMEM = "+CPAS:";			//20
const char AT_ALERT_SOUND_MODE[]	PROGMEM = "+CALM=";			//21
const char AT_ALERT_SOUND_LEVEL[]	PROGMEM = "+CALS=";			//22
const char AT_RINGER_SOUND_LEVEL[]	PROGMEM = "+CRSL=";			//23
const char AT_SPEAKER_LEVEL[]		PROGMEM = "+CLVL=";			//24
const char AT_MUTE[]				PROGMEM = "+CMUT=";			//25


const char* const table_GSM[] PROGMEM =
{
	AT_CALL,				//0
	AT_HANG,				//1
	AT_DTMF,				//2

	// Voice Mode Constants
	AT_ID_INCALL,			//3

	// SMS Constants
	AT_SMS,					//4
	AT_SMS_R,				//5
	AT_SMS_MODE,			//6
	AT_SMS_INFO,			//7
	AT_SMS_READ, 			//8
	AT_SMS_MEMORY,			//9
	AT_SMS_MEMORY_R,		//10
	AT_SMS_DELETE,			//11

	// Sound Constants
	AT_SOUND_INT,			//12
	AT_SOUND_EXT,			//13
	AT_VOLUME_SET,			//14

	AT_SPEAKER_VOLUME,		//15
	AT_SPEAKER_MODE,		//16
	AT_CLIP_MODE,			//17
	AT_CLIR_MODE,			//18
	AT_PHONE_ACTIVITY,		//19
	AT_PHONE_ACTIVITY_R,	//20
	AT_ALERT_SOUND_MODE,	//21
	AT_ALERT_SOUND_LEVEL,	//22
	AT_RINGER_SOUND_LEVEL,	//23
	AT_SPEAKER_LEVEL,		//24
	AT_MUTE,				//25
};
#endif

#if FTP_FUSE

const unsigned long AT_FTP_WAIT_CONFIG = 10000;
const unsigned long AT_FTP_WAIT_CONNEC = 60000; // milliseconds
const unsigned long AT_FTP_MAX_TIME = 300000; 	// milliseconds

const char AT_FTP_ID[]			PROGMEM = "+FTPCID=";		//0
const char AT_FTP_PORT[]		PROGMEM = "+FTPPORT=";		//1
const char AT_FTP_MODE[]		PROGMEM = "+FTPMODE";		//2
const char AT_FTP_TYPE[]		PROGMEM = "+FTPTYPE=";		//3
const char AT_FTP_SERVER[]		PROGMEM = "+FTPSERV=";		//4
const char AT_FTP_UN[]			PROGMEM = "+FTPUN=";		//5
const char AT_FTP_PW[]			PROGMEM = "+FTPPW=";		//6
const char AT_FTP_PUT[]			PROGMEM = "+FTPPUT=";		//7
const char AT_FTP_PUT_NAME[]	PROGMEM = "+FTPPUTNAME=";	//8
const char AT_FTP_PUT_PATH[]	PROGMEM = "+FTPPUTPATH=";	//9
const char AT_FTP_GET[]			PROGMEM = "+FTPGET=";		//10
const char AT_FTP_GET_NAME[]	PROGMEM = "+FTPGETNAME=";	//11
const char AT_FTP_GET_PATH[]	PROGMEM = "+FTPGETPATH=";	//12
const char AT_FTP_GET_SIZE[]	PROGMEM = "+FTPSIZE";		//13
const char AT_FTP_STATUS[]		PROGMEM = "+FTPSTATE";		//14


const char* const table_FTP[] PROGMEM =
{
	AT_FTP_ID,			//0
	AT_FTP_PORT,		//1
	AT_FTP_MODE,		//2
	AT_FTP_TYPE,		//3
	AT_FTP_SERVER,		//4
	AT_FTP_UN,			//5
	AT_FTP_PW,			//6
	AT_FTP_PUT,			//7
	AT_FTP_PUT_NAME,	//8
	AT_FTP_PUT_PATH,	//9
	AT_FTP_GET,			//10
	AT_FTP_GET_NAME,	//11
	AT_FTP_GET_PATH,	//12
	AT_FTP_GET_SIZE,	//13
	AT_FTP_STATUS,		//14
};
#endif

#if HTTP_FUSE

const unsigned long HTTP_TIMEOUT = 60000;		// Timeout for HTTP and HTTPS functions in miliseconds
const unsigned long HTTP_CONF_TIMEOUT = 15000;	// Timeout for HTTP and HTTPS functions in miliseconds

const char AT_HTTP_INIT[]		PROGMEM = "+HTTPINIT";			//0
const char AT_HTTP_PARAM[]		PROGMEM = "+HTTPPARA=";			//1
const char AT_HTTP_ACTION[]		PROGMEM = "+HTTPACTION=";		//2
const char AT_HTTP_ACTION_R[]	PROGMEM = "+HTTPACTION:";		//3
const char AT_HTTP_READ[]		PROGMEM = "+HTTPREAD";			//4
const char AT_HTTP_READ_R[]		PROGMEM = "+HTTPREAD:";			//5
const char AT_HTTP_TERM[]		PROGMEM = "+HTTPTERM";			//6
const char AT_HTTP_CID[]		PROGMEM = "CID";				//7
const char AT_HTTP_URL[]		PROGMEM = "URL";				//8
const char AT_HTTP_DATA[]		PROGMEM = "+HTTPDATA=";			//9
const char AT_HTTP_DATA_R[]		PROGMEM = "DOWNLOAD";			//10
const char AT_HTTP_PARA_CONT[]	PROGMEM = "+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"";			//11
const char FRAME_HEADER_FIELD[]	PROGMEM = "frame=";				//12


const char* const table_HTTP[] PROGMEM =
{
	AT_HTTP_INIT,		//0
	AT_HTTP_PARAM,		//1
	AT_HTTP_ACTION,		//2
	AT_HTTP_ACTION_R,	//3
	AT_HTTP_READ,		//4
	AT_HTTP_READ_R,		//5
	AT_HTTP_TERM,		//6
	AT_HTTP_CID,		//7
	AT_HTTP_URL,		//8
	AT_HTTP_DATA,		//9
	AT_HTTP_DATA_R,		//10
	AT_HTTP_PARA_CONT,	//11
	FRAME_HEADER_FIELD,	//12
};
#endif

#if IP_FUSE

const unsigned long TCP_CONNECTION_TIME_1 = 30000;
const unsigned long TCP_CONNECTION_TIME_2 = 60000; // milliseconds


const char AT_IP[]					PROGMEM = "IP";				//0
const char AT_SINGLE_CONN[]			PROGMEM = "+CIPMUX=0";		//1
const char AT_MULTI_CONN[]			PROGMEM = "+CIPMUX=1";		//2
const char AT_IP_STATUS[]			PROGMEM = "+CIPSTATUS";		//3
const char AT_IP_STATUS_R[]			PROGMEM = "STATE: ";		//4
const char AT_IP_SET_APN[]			PROGMEM = "+CSTT=";			//5
const char AT_IP_BRING[]			PROGMEM = "+CIICR";			//6
const char AT_IP_GET_IP[]			PROGMEM = "+CIFSR";			//7
const char AT_IP_APP_MODE[]			PROGMEM = "+CIPMODE=";		//8
const char AT_IP_HEADER_1[]			PROGMEM = "AT+CIPHEAD=1";	//9
const char AT_IP_CLIENT[]			PROGMEM = "+CIPSTART=";		//10
const char AT_TCP[]					PROGMEM = "TCP";			//11
const char AT_UDP[]					PROGMEM = "UDP";			//12
const char AT_CONNECTED_OK[]		PROGMEM = "CONNECT OK";		//13
const char AT_CONNECTED_FAIL[]		PROGMEM = "CONNECT FAIL";	//14
const char AT_IP_SERVER[]			PROGMEM = "+CIPSERVER=";	//15
const char AT_IP_SEND[]				PROGMEM = "+CIPSEND";		//16
const char AT_IP_SEND_R[]			PROGMEM = "SEND OK";		//17
const char AT_IP_SEND_FAIL[]		PROGMEM = "SEND FAIL";		//18
const char AT_IP_CLOSE[]			PROGMEM = "+CIPCLOSE=";		//19
const char AT_IP_CLOSE_R[]			PROGMEM = "CLOSE OK";		//20
const char AT_IP_QCLOSE[]			PROGMEM = "+CIPQRCLOSE=";	//21
const char AT_IP_SHUT[]				PROGMEM = "+CIPSHUT";		//22
const char AT_IP_QUERY_DNS[]		PROGMEM = "+CDNSGIP=";		//23
const char AT_IP_QUERY_DNS_R[]		PROGMEM = "+CDNSGIP:";		//24
const char AT_IP_LOCAL_PORT[]		PROGMEM = "+CLPORT=";		//25
const char AT_IP_SAVE_CONF[]		PROGMEM = "+CIPSCONT";		//26
const char AT_IP_HEADER[]			PROGMEM = "+CIPHEAD=";		//27
const char AT_IP_AUTOSENDING[]		PROGMEM = "+CIPATS=";		//28
const char AT_IP_SHOW_REMOTE_IP[]	PROGMEM = "+CIPSRIP=";		//29
const char AT_IP_PROTOCOL_HEADER[]	PROGMEM = "+CIPSHOWTP=";	//30
const char AT_IP_DISCARD_AT_DATA[]	PROGMEM = "+CIPTXISS=";		//31
const char AT_IP_GET_MANUALLY[]		PROGMEM = "+CIPRXGET";		//32
const char AT_IP_UDP_EXTENDED[]		PROGMEM = "+CIPUDPMODE=";	//33
const char AT_IP_CGATT[]			PROGMEM = "+CGATT";			//34

// IP states
const char IP_INITIAL[]				PROGMEM = "IP INITIAL";			//35
const char IP_START[]				PROGMEM = "IP_START";			//36
const char IP_CONFIG[]				PROGMEM = "IP CONFIG";			//37
const char IP_GPRSACT[]				PROGMEM = "IP GPRSACT";			//38
const char IP_STATUS[]				PROGMEM = "IP STATUS";			//39
const char IP_PROCESSING[]			PROGMEM = "IP PROCESSING";		//40
const char TCP_CONNECTING[]			PROGMEM = "TCP CONNECTING";		//41
const char UDP_CONNECTING[]			PROGMEM = "UDP CONNECTING";		//42
const char SERVER_LISTENING[]		PROGMEM = "SERVER LISTENING";	//43
const char CONNECT_OK[]				PROGMEM = "CONNECT OK";			//44
const char TCP_CLOSING[]			PROGMEM = "TCP CLOSING";		//45
const char UDP_CLOSING[]			PROGMEM = "UDP CLOSING";		//46
const char TCP_CLOSED[]				PROGMEM = "TCP CLOSED";			//47
const char UDP_CLOSED[]				PROGMEM = "UDP CLOSED";			//48
const char PDP_DEACT[]				PROGMEM = "PDP DEACT";			//49


const char GET_MANUAL[]				PROGMEM = "+CIPRXGET";			//50
const char IP_DATA[]				PROGMEM = "+IPD,";				//51
const char GET_DATA[]				PROGMEM = "+CIPRXGET=2,";		//52
const char IP_MULTI_DATA[]			PROGMEM = "+RECEIVE,";			//53



const char* const table_IP[] PROGMEM =
{
	AT_IP,					//0
	AT_SINGLE_CONN,			//1
	AT_MULTI_CONN,			//2
	AT_IP_STATUS,			//3
	AT_IP_STATUS_R,			//4
	AT_IP_SET_APN,			//5
	AT_IP_BRING,			//6
	AT_IP_GET_IP,			//7
	AT_IP_APP_MODE,			//8
	AT_IP_HEADER_1,			//9
	AT_IP_CLIENT,			//10
	AT_TCP,					//11
	AT_UDP,					//12
	AT_CONNECTED_OK,		//13
	AT_CONNECTED_FAIL,		//14
	AT_IP_SERVER,			//15
	AT_IP_SEND,				//16
	AT_IP_SEND_R,			//17
	AT_IP_SEND_FAIL,		//18
	AT_IP_CLOSE,			//19
	AT_IP_CLOSE_R,			//20
	AT_IP_QCLOSE,			//21
	AT_IP_SHUT,				//22
	AT_IP_QUERY_DNS,		//23
	AT_IP_QUERY_DNS_R,		//24
	AT_IP_LOCAL_PORT,		//25
	AT_IP_SAVE_CONF,		//26
	AT_IP_HEADER,			//27
	AT_IP_AUTOSENDING,		//28
	AT_IP_SHOW_REMOTE_IP,	//29
	AT_IP_PROTOCOL_HEADER,	//30
	AT_IP_DISCARD_AT_DATA,	//31
	AT_IP_GET_MANUALLY,		//32
	AT_IP_UDP_EXTENDED,		//33
	AT_IP_CGATT,			//34

// IP states
	IP_INITIAL,				//35
	IP_START,				//36
	IP_CONFIG,				//37
	IP_GPRSACT,				//38
	IP_STATUS,				//39
	IP_PROCESSING,			//40
	TCP_CONNECTING,			//41
	UDP_CONNECTING,			//42
	SERVER_LISTENING,		//43
	CONNECT_OK,				//44
	TCP_CLOSING,			//45
	UDP_CLOSING,			//46
	TCP_CLOSED,				//47
	UDP_CLOSED,				//48
	PDP_DEACT,				//49

	GET_MANUAL,				//50
	IP_DATA,				//51
	GET_DATA,				//52
	IP_MULTI_DATA,			//53
};
#endif

#if OTA_FUSE

const char OTA_ver_file[]	PROGMEM = "/UPGRADE.TXT";	//0
const char NO_OTA[]			PROGMEM = "NO_FILE";		//1
const char FILE_TAG[]		PROGMEM = "FILE:";			//2
const char PATH_TAG[]		PROGMEM = "PATH:";			//3
const char VERSION_TAG[]	PROGMEM = "VERSION:";		//4


const char* const table_OTA_GPRS[] PROGMEM =
{
	OTA_ver_file,	//0
	NO_OTA,			//1
	FILE_TAG,		//2
	PATH_TAG,		//3
	VERSION_TAG,	//4
};
#endif


// Constructors ////////////////////////////////////////////////////////////////

WaspGPRS_Pro_core::WaspGPRS_Pro_core(){
	_baudRate=GPRS_PRO_RATE;
	_pwrMode=GPRS_PRO_ON;
	_socket=1;
	not_ready=1;

	memset(_apn, '\0', sizeof(_apn));
	memset(_apn_login, '\0', sizeof(_apn_login));
	memset(_apn_password, '\0', sizeof(_apn_password));
	strncpy(_apn, AT_GPRS_APN, min(sizeof(_apn), strlen(AT_GPRS_APN)));
	strncpy(_apn_login, AT_GPRS_LOGIN, min(sizeof(_apn_login), strlen(AT_GPRS_LOGIN)));
	strncpy(_apn_password, AT_GPRS_PASSW, min(sizeof(_apn_password), strlen(AT_GPRS_PASSW)));

}


// Private Methods /////////////////////////////////////////////////////////////

#if IP_FUSE
/* getIP() - Gets IP direction when configure a TCP/UDP profiles
 *
 * This function gets IP direction when configure a TCP/UDP profiles and stores it in 'IP_direction'
 *
 * Returns '1' on success and '0' if error
*/
uint8_t WaspGPRS_Pro_core::getIP(){
	int i;
	unsigned long previous;

	serialFlush(_socket);

	//AT_IP_GET_IP
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[7])));	//+CIFSR
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "AT%s\r\n", str_aux1);
	printString(buffer_GPRS, _socket);

	previous=millis();
	i=0;
	do{
		while ((!serialAvailable(_socket)) && ((millis() - previous) < 1000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		IP_dir[i]=serialRead(_socket);
		if (((0x2F < IP_dir[i]) && (IP_dir[i] < 0x3A)) || (IP_dir[i] == '.')) // Only moves the cursor when it's a number or a dot
		{
			i++;
		}
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while (((!((IP_dir[i] == '\r') && (i != 0))) && (IP_dir[i] != 'E')) && ((millis() - previous) < 1000));
	IP_dir[i]='\0';

	if (IP_dir[0] == '\0')
	{
		return 0;
	}

	return 1;
}

/* checkIPstatus() - get the status of the IP connection
 *
 * This function gets the status of the IP connection
 *
 * Returns a number with the state
*/
uint8_t WaspGPRS_Pro_core::checkIPstatus(){
	uint8_t answer = 10;
	int it = 0;

	memset(str_aux3, '\0', sizeof(str_aux3) );

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[3])));	//"+CIPSTATUS"
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[4])));	//"STATE: "
	answer=sendCommand1(str_aux1, str_aux2);

	if (answer == 1)
	{
		do{
			str_aux3[it]=serialRead(_socket);
			it++;
		}while (str_aux3[it-1] != '\n');

		if (strstr(str_aux3, "IP INITIAL") != NULL)
		{
			return 1;
		}
		if (strstr(str_aux3, "IP START") != NULL)
		{
			return 2;
		}
		if (strstr(str_aux3, "IP CONFIG") != NULL)
		{
			return 3;
		}
		if (strstr(str_aux3, "IP GPRSACT") != NULL)
		{
			return 4;
		}
		if ((strstr(str_aux3, "IP STATUS") != NULL) || (strstr(str_aux3, "IP PROCESSING") != NULL))
		{
			return 5;
		}
		if ((strstr(str_aux3, "TCP CONNECTING") != NULL) || (strstr(str_aux3, "UDP CONNECTING") != NULL) || (strstr(str_aux3, "SERVER LISTENING") != NULL))
		{
			return 6;
		}
		if (strstr(str_aux3, "CONNECT OK") != NULL)
		{
			return 7;
		}
		if ((strstr(str_aux3, "TCP CLOSING") != NULL) || (strstr(str_aux3, "UDP CLOSING") != NULL))
		{
			return 8;
		}
		if ((strstr(str_aux3, "TCP CLOSED") != NULL) || (strstr(str_aux3, "UDP CLOSED") != NULL))
		{
			return 9;
		}
		if (strstr(str_aux3, "PDP DEACT") != NULL)
		{
			return 10;
		}
		answer = 0;
	}

	if (answer == 0)
	{
		return 0;
	}

	return 11;
}
#endif


/* getIfReady() - gets if GPRS module is ready or not
 *
 * This function gets if GPRS module is ready or not
 *
 * Returns nothing. It changes the value of 'not_ready'
*/
void WaspGPRS_Pro_core::getIfReady(){
	uint8_t answer=0;

	// clean rx buffer
    serialFlush(_socket);

	printString(AT_COMMAND, _socket);
	printByte('\r', _socket);
	printByte('\n', _socket);
	delay(10);
	answer = waitForData(OK_RESPONSE, 2000, millis(), 0);
	if (answer == 1)
	{
		not_ready=0;
	}
	else
	{
		not_ready=1;
	}
}

/* checkGPRS() - checks if GPRS connection is OK
 *
 * This function checks if GPRS connection is OK
 *
 * Returns '1' on success and '0' if error
*/
uint8_t WaspGPRS_Pro_core::checkGPRS_at(unsigned long time){

	uint8_t answer = 0;
	unsigned long previous;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[14])));	//AT_GPRS_CHECK_ATT
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[15])));	//AT_GPRS_CHECK_ON
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[16])));	//AT_GPRS_CHECK_OFF

	previous = millis();

	do{
		answer = sendCommand2(str_aux1, str_aux2, str_aux3);
	}while ((answer != 1) && ((millis() - previous) < (time * 1000)));

	if (answer != 1)
	{
		return 0;
	}

	return 1;
}

/* checkGPRS() - checks if GPRS connection is OK
 *
 * This function checks if GPRS connection is OK
 *
 * Returns '1' when connected,
 * '0' if not registered and the module is not currently searching a new operator,
 * '-2' if not registered, but the module is currently searching a new operator,
 * '-3' if registration denied
 * '-4' if the state is unknown
*/
int8_t WaspGPRS_Pro_core::checkGPRS(unsigned long time){

	int8_t answer=0;
	unsigned long previous;

	// AT+CGREG?
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[45])));  //"+CGREG?"
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[46])));  //"+CGREG: 0,"
	previous = millis();
	do{
		// Sends the command and waits for the answer (0,1 for home network and 0,5 for roaming)
		answer = sendCommand1(str_aux1, str_aux2, 3000, 1);

		// Check if pattern "+CGREG: 0," was found
		if (answer == 1)
		{
			// read status
			answer = serialRead(_socket) - 0x30;
		}
		delay(500);

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();

	}while (((answer == 2) || (answer == 4) || (answer == 0)) && ((millis() - previous) < (time * 1000)));

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("GPRS status: "));
		USB.println(answer, DEC);
	#endif

	// check correct answer
	if ( (answer == 1) || (answer == 5) )
	{
		return 1;
	}

	// if error return corresponding flag
	return -answer;
}


// AT Comands ///////////////////////////////////////////////////////////////////

/*
 * sendCommand1
 *
 * It sends an AT command to the module for a maximum of 'DEFAULT_TIMEOUT'
 * milliseconds and tries to seek the patterns specified in 'expectedAnswer'
 *
 * Returns
 * 	'1' if 'expectedAnswer' has been detected,
 * 	'0' if not detected
 */
uint8_t WaspGPRS_Pro_core::sendCommand1(const char* theText,
								   const char* expectedAnswer)
{
    return sendCommand1(theText, expectedAnswer, DEFAULT_TIMEOUT, SEND_ONCE);
}

/*
 * sendCommand1
 *
 * It sends an AT command to the module for a maximum of 'max_timeout'
 * milliseconds and tries to seek the patterns specified in 'expectedAnswer'
 *
 * Returns
 * 	'1' if 'expectedAnswer1' has been detected,
 * 	'2' if 'expectedAnswer2' has been detected,
 * 	'0' if not detected
 */
uint8_t WaspGPRS_Pro_core::sendCommand1(const char* theText,
								   const char* expectedAnswer,
								   unsigned long max_timeout,
								   int num_tries)
{
	unsigned long timeout = 0;

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Send command with 1 answer: "));
		USB.print(F("AT"));
		USB.println(theText);
	#endif

	beginSerial(_baudRate, _socket);
	// try sending the command
	// wait for serial response
    timeout = millis();
    serialFlush(_socket);
    while ( (!serialAvailable(_socket)) && ((millis() - timeout) < max_timeout))
	{
        if (num_tries > 0)
		{
            printString("AT", _socket);
            printString(theText, _socket);
            printString("\r\n", _socket);
			num_tries--;
        }
        delay(DELAY_ON_SEND);
    }

	int answer= waitForData( expectedAnswer, max_timeout, timeout, 0);

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Answer received: "));
		USB.println(answer, DEC);
	#endif

    return answer;
}

/*
 * sendCommand2
 *
 * It sends an AT command to the module for a maximum of 'DEFAULT_TIMEOUT'
 * milliseconds and tries to seek the patterns specified in 'expectedAnswer1'
 * and 'expectedAnswer2'
 *
 * Returns
 * 	'1' if 'expectedAnswer1' has been detected,
 * 	'2' if 'expectedAnswer2' has been detected,
 * 	'0' if not detected
 */
uint8_t WaspGPRS_Pro_core::sendCommand2(	const char* theText,
									const char* expectedAnswer1,
									const char* expectedAnswer2)
{
    return sendCommand2(	theText,
							expectedAnswer1,
							expectedAnswer2,
							DEFAULT_TIMEOUT,
							SEND_ONCE	);
}

/*
 * sendCommand2
 *
 * It sends an AT command to the module for a maximum of 'max_timeout'
 * milliseconds and tries to seek the patterns specified in 'expectedAnswer1'
 * and 'expectedAnswer2'
 *
 * Returns
 * 	'1' if 'expectedAnswer1' has been detected,
 * 	'2' if 'expectedAnswer2' has been detected,
 * 	'0' if not detected
 */
uint8_t WaspGPRS_Pro_core::sendCommand2(	const char* theText,
									const char* expectedAnswer1,
									const char* expectedAnswer2,
									unsigned long max_timeout,
									int num_tries)
{
    unsigned long timeout = 0;

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Send command with 2 answers: "));
		USB.print(F("AT"));
		USB.println(theText);
	#endif

	beginSerial(_baudRate, _socket);
	// try sending the command
	// wait for serial response
    timeout = millis();
    serialFlush(_socket);
    while((!serialAvailable(_socket)) && ((millis() - timeout) < max_timeout))
	{
        if (num_tries > 0)
		{
            printString("AT", _socket);
            printString(theText, _socket);
            printString("\r\n", _socket);
			num_tries--;
        }
        delay(DELAY_ON_SEND);
    }

    int answer= waitForData( expectedAnswer1, expectedAnswer2, max_timeout, timeout, 0, 2);

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Answer received: "));
		USB.println(answer, DEC);
	#endif

    return answer;
}


/*
 * waitForData
 *
 * It waits for data from the module for a maximum of max_timeout seconds and
 * tries to seek the pattern specified in 'expectedAnswer'
 *
 * Returns
 * 	'1' if 'expectedAnswer' has been detected,
 * 	'0' if not detected
 */
uint8_t WaspGPRS_Pro_core::waitForData(	const char* expectedAnswer,
									unsigned long max_timeout,
									unsigned long timeout,
									int seconds)
{
	return (waitForData( expectedAnswer, expectedAnswer, max_timeout, timeout, seconds, 1));
}



/*
 * waitForData
 *
 * It waits for data from the module for a maximum of max_timeout seconds and
 * tries to seek the patterns specified in 'expectedAnswer1' and
 * 'expectedAnswer2'
 *
 * Returns
 * 	'1' if 'expectedAnswer1' has been detected,
 * 	'2' if 'expectedAnswer2' has been detected,
 * 	'0' if not detected
 */
uint8_t WaspGPRS_Pro_core::waitForData(	const char* expectedAnswer1,
									const char* expectedAnswer2,
									unsigned long max_timeout,
									unsigned long timeout,
									int seconds,
									int n_answers)
{
	char theCommand[100];

	memset(theCommand, '\0', sizeof(theCommand));

	int theLength1 = 0;
	int theLength2 = 0;
	int minLength;
	int maxLength;
	int it=0;
	uint8_t first=1;
	char aux;


	#if GPRS_debug_mode>1
		PRINT_GPRS(F("Excepted answer 1: "));
		USB.println(expectedAnswer1);
		PRINT_GPRS(F("Excepted answer 2: "));
		USB.println(expectedAnswer2);
	#endif
	// Gets the maximum length and the minimum length of the 2 strings
	theLength1=strlen(expectedAnswer1);
	minLength=theLength1;
	maxLength=theLength1;

	if (n_answers > 1)
	{
		theLength2=strlen(expectedAnswer2);
		if(minLength>theLength2)
		{
			minLength=theLength2;
		}
		if(maxLength<theLength2)
		{
			maxLength=theLength2;
		}
	}

	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}

	while ((millis() - timeout) < max_timeout)
	{
		while (!serialAvailable(_socket) && ((millis() - timeout) < max_timeout))
		{
			delay(10);

			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < timeout) timeout = millis();
		}

		while (serialAvailable(_socket))
		{

			if ( first == 1 )	// Gets data from serial port until 'minLength'
			{
				theCommand[it] = serialRead(_socket);
				it++;
				#if GPRS_debug_mode>1
					PRINT_GPRS(F("Command answer 1: "));
					USB.println(theCommand);
					PRINT_GPRS(F("Length: "));
					USB.println(strlen(theCommand), DEC);
				#endif
				if (it > minLength)
				{
					if ((n_answers > 1) && (minLength < maxLength))
					{
						first = 2;
					}
					else
					{
						first = 0;
					}
				}
			}
			else if (first == 2)	// Gets data from serial port increasing the length of 'theCommand' from minLength to maxLength
			{
				if (serialAvailable(_socket))
				{
					it=minLength;
					minLength++;
					theCommand[minLength]=serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						PRINT_GPRS(F("Command answer 2: "));
						USB.println(theCommand);
						PRINT_GPRS(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
				if (minLength >= maxLength)
				{
					first=0;
				}
			}
			else
			{
				if (serialAvailable(_socket))
				{
					for (it=0; it<maxLength; it++)
					{
						theCommand[it] = theCommand[it+1];
					}
					theCommand[it] = serialRead(_socket);
					delay(20);
					#if GPRS_debug_mode>1
						PRINT_GPRS(F("Command answer 3: "));
						USB.println(theCommand);
						PRINT_GPRS(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
			}

			if (strstr(theCommand, expectedAnswer1) != NULL)
			{
				if ((strcmp(expectedAnswer1, ERROR_CME) == 0) || (strcmp(expectedAnswer1, ERROR_CMS) == 0))
				{
					#if GPRS_debug_mode>0
						PRINT_GPRS(F("special error"));
					#endif
					while (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);

					do{ // Gets the length of the data string
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code,DEC);
					#endif
				}
				return 1;
			}

			if ((strstr(theCommand, expectedAnswer2) != NULL) && (n_answers > 1))
			{
				if ((strcmp(expectedAnswer2, ERROR_CME) == 0) || (strcmp(expectedAnswer2, ERROR_CMS) == 0))
				{
					#if GPRS_debug_mode>0
						PRINT_GPRS(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				return 2;
			}

		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < timeout) timeout = millis();
	}

	memset(buffer_temporal, '\0', sizeof(buffer_temporal));
	strcpy(buffer_temporal, theCommand);

	return 0;
}


#if FTP_FUSE
//FTP private functions
/*
 * Returns
 * '1'   if OK
 * '-13' if error setting the file name in the FTP server
 * '-14' if error setting the path of the file in the FTP server
 * '-15' if error opening the FTP session
 * '-16' if error when request to send data
 * '-17' if error sending data to the FTP,
 * '-18' if error waiting for send more data
 * '-19' if error when setting Upload File with CME error code available,
 * '-20' if error closing the FTP session
 * '-24' if error opening SD file
 * '-25' if error when setting pointer to the beginning of the file
 * '-48' if error setting the file name in the FTP server with CME error code available,
 * '-49' if error setting the path of the file in the FTP server with CME error code available
 * '-50' if error opening the FTP session with CME error code available,
 * '-51' if error closing the FTP session with CME error code available
 * '-57' if FTP is busy sending data
 */
int8_t WaspGPRS_Pro_core::sendDataFTP(const char* file, const char* path){

	int32_t file_size;
	unsigned long previous = 0;
	uint8_t answer=0, count = 10, error_counter = 5;
	int j = 0;
	int i;
	int max_FTP_data = 0, aux2;

	SdFile file_up;

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Inside sendDataFTP\n"));
	#endif

	// Check the FTP is ready
	previous = millis();
	while( FTPstatus() == 2 )
	{
		delay(1000);
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();

		if ((millis()-previous) > AT_FTP_WAIT_CONNEC )
		{
			#if GPRS_debug_mode>0
				PRINT_GPRS(F("FTP busy\n"));
			#endif
			return -57;
		}
	}

	// Sets server path and name
	delay(50);
	delay(50);
	delay(50);
	delay(50);

	// SET UPLOAD FILE NAME: AT+FTPPUTNAME=""
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[8])));	//"+FTPPUTNAME="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, strrchr(path, '/'));
	count=7;
	do{
		answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG, SEND_ONCE);
		count--;
	}while ((answer != 1) && (count > 0));
	if(answer == 0)
	{
		return -13;
	}
	else if(answer == 2)
	{
		return -48;
	}

	delay(50);
	delay(50);
	delay(50);
	delay(50);

	// SET UPLOAD FILE PATH: AT+FTPPUTPATH=<value>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[9])));	//"+FTPPUTPATH="
	if (path == strrchr(path, '/'))
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"/\"", str_aux1);
	}
	else
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, path);
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS + 1] = '\0';
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS] = '\"';
	}
	count=7;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG, SEND_ONCE);
		count--;
	}while ((answer != 1) && (count > 0));
	if(answer == 0)
	{
		return -14;
	}
	else if(answer == 2)
	{
		return -49;
	}

	// Delay to wait to perform the ftp session
	delay(500);

	// open connection with FTP server
	answer = openFTPPUTconnection();

	if( answer != 1 )
	{
		return answer;
	}

	max_FTP_data = 0;

	// Gets the length of the data string
	aux2 = serialRead(_socket);
	previous=millis();
	do{
		max_FTP_data*=10;
		max_FTP_data+=aux2-0x30;
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 20000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		aux2=serialRead(_socket);
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((aux2 != '\r') && ((millis()-previous) < 20000));

	serialFlush(_socket);

	j=0;
	file_size = SD.getFileSize(file);

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("File size on SD: "));
		USB.println(file_size, DEC);
	#endif

	if(!SD.openFile((char*)file, &file_up, O_RDONLY))
	{
		// SD error
		#if GPRS_debug_mode>0
			PRINTLN_GPRS(F("Error: opening file"));
		#endif

		// Tries to close the connection
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//+FTPPUT=
		snprintf(str_aux2, sizeof(str_aux2), "%s2,0", str_aux1);
		sendCommand2(str_aux2, "+FTPPUT:1,0", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);

		return -24;
	}

	// set pointer to the beginning of the file
	if(!file_up.seekSet(0))
	{
		// SD error
		#if GPRS_debug_mode>0
			PRINTLN_GPRS(F("Error: setting initial offset in file"));
		#endif

		// Close file
		file_up.close();

		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//+FTPPUT=
		snprintf(str_aux2, sizeof(str_aux2), "%s2,0", str_aux1);
		sendCommand2(str_aux2, "+FTPPUT:1,0", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);

		return -25;
	}

	// Starts to send data
	do{

		if (max_FTP_data > BUFFER_SIZE)
		{
			j = file_up.read(buffer_GPRS, BUFFER_SIZE);
		}
		else
		{
			j = file_up.read(buffer_GPRS, max_FTP_data);
		}


		if (j == -1)
		{
			// SD error
			#if GPRS_debug_mode>0
				PRINTLN_GPRS(F("Error: reading the file"));
			#endif
			j = 0;
			error_counter--;
		}
		else
		{
			error_counter = 5;
		}

		file_size-=j;

		// AT+FTPPUT=2,<n>
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//+FTPPUT=
		snprintf(str_aux3, sizeof(str_aux3), "%s2,%u", str_aux1, j); // Requests to send the data string
		answer=sendCommand2(str_aux3, "+FTPPUT:2,", "+FTPPUT:1,0", AT_FTP_WAIT_CONNEC, SEND_ONCE);
		if (answer != 1)
		{
			// Close file
			file_up.close();

			// Tries to close the connection
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//AT_FTP_PUT
			snprintf(str_aux2, sizeof(str_aux2), "%s2,0", str_aux1);
			sendCommand2(str_aux2, "+FTPPUT:1,0", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);

			return -16;
		}

		// Sends the data from the file
		for (i = 0; i < j; i++)
		{
			printByte(buffer_GPRS[i], _socket);
		}
		previous = millis();
		while ( (!serialAvailable(_socket)) && ((millis()-previous) < 10000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		answer=waitForData("OK", AT_FTP_WAIT_CONNEC, millis(), 0);
		if (answer != 1)
		{
			// Close file
			file_up.close();

			// Tries to close the connection
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//AT_FTP_PUT
			snprintf(str_aux2, sizeof(str_aux2), "%s2,0", str_aux1);
			sendCommand2(str_aux2, "+FTPPUT:1,0", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);

			return -17;
		}

		answer=waitForData("+FTPPUT:1,", AT_FTP_WAIT_CONNEC, millis(), 0);
		if (answer != 1)
		{
			// Close file
			file_up.close();

			// Tries to close the connection
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//AT_FTP_PUT
			snprintf(str_aux2, sizeof(str_aux2), "%s2,0", str_aux1);
			sendCommand2(str_aux2, "+FTPPUT:1,0", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);

			return -18;
		}

		aux2=serialRead(_socket);
		if (aux2 != 0x31)
		{
			FTP_error_code=0;

			count = 0;
			do{
				str_aux1[count] = serialRead(_socket);
				count++;
			}while (str_aux1[count - 1] != '\r');
			str_aux1[count - 1] = '\0';
			FTP_error_code = atoi(str_aux1);

			#if GPRS_debug_mode>0
				PRINT_GPRS(F("FTP error code: "));
				USB.println(FTP_error_code, DEC);
			#endif

			CME_CMS_code = FTP_error_code;

			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//AT_FTP_PUT
			snprintf(str_aux3, sizeof(str_aux3), "AT%s2,0\r\n", str_aux1);
			printString(str_aux3, _socket);
			previous = millis();
			while ( (!serialAvailable(_socket)) && ((millis()-previous) < 10000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			answer=waitForData("+FTPPUT:1,0", AT_FTP_WAIT_CONNEC, millis(), 0);

			// Close file
			file_up.close();

			return -40;
		}
		serialRead(_socket); //Discard ',' character

		// Gets the length of the data string
		max_FTP_data=0;
		count = 0;
		do{
			str_aux1[count] = serialRead(_socket);
			count++;
		}while (str_aux1[count - 1] != '\r');
		str_aux1[count - 1] = '\0';
		max_FTP_data = atoi(str_aux1);

		j = 0;
	}while ((file_size > 0) && (error_counter > 0));

	// Close file
	file_up.close();

	// CLOSE TRANSMISSION: AT+FTPPUT=2,0
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//+FTPPUT=
	snprintf(str_aux2, sizeof(str_aux2), "%s2,0", str_aux1);
	answer=sendCommand2(str_aux2, "+FTPPUT:1,0", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);
	if(answer == 0)
	{
		return -20;
	}
	else if(answer == 2)
	{
		return -51;
	}

	return 1;
}

/*
 * This function opens connection with the FTP server
 *
 * Returns
 * '1'   if OK
 * '-15' if error opening the FTP session
 * '-19' if error when setting Upload File with CME error code available,
 * '-50' if error opening the FTP session with CME error code available,
 */
int8_t WaspGPRS_Pro_core::openFTPPUTconnection()
{
	unsigned long previous = 0;
	uint8_t answer=0, count = 10;
	int aux2;
	bool success=false;

	// set put retries (once is enough, more has been proved to solve nothing)
	int put_retries=1;

	do{
		// initialize variables
		success = false;

		// SET UPLOAD FILE: AT+FTPPUT=1
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//"+FTPPUT="
		snprintf(str_aux2, sizeof(str_aux2), "%s1", str_aux1);
		answer = sendCommand2(str_aux2, "+FTPPUT:1,", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);
		if(answer == 0)
		{
			// TRIES TO CLOSE THE CONNECTION: AT+FTPPUT=2,0
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//"+FTPPUT="
			snprintf(str_aux2, sizeof(str_aux2), "%s2,0", str_aux1);
			sendCommand2(str_aux2, "+FTPPUT:1,0", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);

			return -15;
		}
		else if(answer == 2)
		{
			return -50;
		}
		else
		{
			// Acknowledged pattern:   +FTPPUT:1,
			// Response to be checked: +FTPPUT:1,1,<maxlength>
			count = 0;
			memset(str_aux1, '\0', sizeof(str_aux1) );
			previous=millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 20000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}
				str_aux1[count] = serialRead(_socket);
				count++;
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((str_aux1[count - 1] != ',') && ((millis()-previous) < 20000));

			str_aux1[count - 1] = '\0';

			aux2 = atoi(str_aux1);

			if (aux2 != 1)
			{
				// TRIES TO CLOSE THE CONNECTION: AT+FTPPUT=2,0
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));	//"+FTPPUT="
				snprintf(str_aux2, sizeof(str_aux2), "%s2,0", str_aux1);
				sendCommand2(str_aux2, "+FTPPUT:1,0", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);

				CME_CMS_code = aux2;

				success = false;
			}
			else
			{
				success = true;
			}
		}

		// decrease counter
		put_retries--;
	}
	while( (put_retries > 0) && (success == false) );

	// check success
	if( success == false )
	{
		return -19;
	}

	return 1;

}

/*
 * readDataFTP
 *
 * This function reads data via FTP
 *
 * Returns
 * '1'   if OK
 * '-12' if error using SD card
 * '-13' if error setting the file name in the FTP server
 * '-14' if error setting the path of the file in the FTP server
 * '-15' if error starting the SD
 * '-16' if error creating the file
 * '-17' if error requesting data to the FTP,
 * '-18' if error saving data into the SD
 * '-19' if error requesting more data to the FTP
 * '-48' if error setting the file name in the FTP server with CME error code available,
 * '-49' if error setting the path of the file in the FTP server with CME error code available
 * '-50' if error opening the FTP session with CME error code available,
 * '-51' if error requesting data to the FTP with CME error code available
 * '-52' if error requesting more data to the FTP with CME error code available,
 * '-53' setting the file name in the FTP to get the file size with CME error code available,
 * '-54' setting the path in the FTP to get the file size with CME error code available
 * '-57' if FTP is busy sending data
 *
 */
int8_t WaspGPRS_Pro_core::readDataFTP(const char* file, const char* path){

	unsigned long previous;
	long size_pointer = 0, file_size;
	uint8_t answer = 0, count = 10;
	int FTP_data = 0, i;

	SdFile file_down;

	#if GPRS_debug_mode>0
		PRINTLN_GPRS(F("Inside readDataFTP"));
		PRINT_GPRS(F("FTP file: "));
		USB.println(file);
		PRINT_GPRS(F("SD file:"));
		USB.println(path);
	#endif

	previous = millis();
	while ((FTPstatus() == 2) && ((millis()-previous) < AT_FTP_WAIT_CONNEC) )
	{
		delay(1000);
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}

	if ((millis()-previous) > AT_FTP_WAIT_CONNEC )
	{
		#if GPRS_debug_mode>0
			PRINTLN_GPRS(F("FTP busy"));
		#endif
		return -57;
	}

	// First goes to the main directory
	if (SD.goRoot() != 1)
	{
		return -15;
	}

	SD.del(path);

	// Then goes to the file directory in SD card
	if (SD.create(path) != 1)
	{
		return -16;
	}


	file_size = getfilesizeFTP(file);
	if (file_size < 0)
	{
		return file_size;
	}
	// Sets server path and name
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[11])));	//AT_FTP_GET_NAME
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, strrchr(file, '/'));
	count = 7;
	do{
		answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG, SEND_ONCE);
		count--;
	}while ((answer != 1) && (count > 0));
	if(answer == 0)
	{
		return -12;
	}
	else if(answer == 2)
	{
		return -48;
	}

	delay(50);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[12])));	//AT_FTP_GET_PATH
	if (file == strrchr(file, '/'))
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"/\"", str_aux1);
	}
	else
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, file);
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS + 1] = '\0';
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS] = '\"';
	}
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG, SEND_ONCE);
	if(answer == 0)
	{
		return -13;
	}
	else if(answer == 2)
	{
		return -49;
	}

	delay(50);
	// Opens the FTP get session
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[10])));	//AT_FTP_GET
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s1", str_aux1);
	count=3;
	do{
		answer=sendCommand2(buffer_GPRS, "+FTPGET:1,1", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);
		count--;
	}while ((answer != 1) && (count > 0));
	if(answer == 0)
	{
		return -14;
	}
	else if(answer == 2)
	{
		return -50;
	}
	i=0;

	if(!SD.openFile((char*)path, &file_down, O_WRITE))
	{
		// SD error
		#if GPRS_debug_mode>0
			PRINTLN_GPRS(F("Error: opening file"));
		#endif
		return -12;
	}

	// set pointer to the beginning of the file
	if(!file_down.seekSet(0))
	{
		// SD error
		#if GPRS_debug_mode>0
			PRINTLN_GPRS(F("Error: setting initial offset in file"));
		#endif

		// Close file
		file_down.close();

		return -12;
	}

	delay(1000);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[10])));	//AT_FTP_GET
	#if BUFFER_SIZE>BUFFER_UART
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s2,%d", str_aux1, BUFFER_UART);
	#else
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s2,%d", str_aux1, BUFFER_SIZE);
	#endif
		//snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s2,200", str_aux1);
	answer=sendCommand2(buffer_GPRS, "+FTPGET:2,", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);
	if(answer == 0)
	{
		return -17;
	}
	else if(answer == 2)
	{
		return -51;
	}

	previous=millis();

	FTP_data=0;
	while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC) )
	{
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}

	count = 0;
	previous = millis();
	do{	// Gets the length of the data string
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC) )
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		str_aux1[count] = serialRead(_socket);
		count++;
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((str_aux1[count - 1] != '\r') && ((millis()-previous) < AT_FTP_WAIT_CONNEC) );

	str_aux1[count - 1] = '\0';
	FTP_data = atoi(str_aux1);


	serialRead(_socket);



	if ((millis()-previous) > AT_FTP_WAIT_CONNEC )
	{
		return -17;
	}

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("FTP data: "));
		USB.println(FTP_data, DEC);
	#endif

	while ((file_size > size_pointer) && ((millis()-previous) < AT_FTP_WAIT_CONNEC) )
	{
		previous=millis();
		while ((serialAvailable(_socket) < FTP_data) && ((millis()-previous) < AT_FTP_WAIT_CONNEC) )
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}

		for (i = 0; i < FTP_data; i++)
		{
			buffer_GPRS[i] = serialRead(_socket);
		}

		count = 5;
		do{
			i = file_down.write((uint8_t*)buffer_GPRS, FTP_data);

			if (i != FTP_data)
			{
				count--;
				// set pointer to the beginning of the file
				if(!file_down.seekSet(size_pointer))
				{
					// SD error
					#if GPRS_debug_mode>0
						PRINTLN_GPRS(F("Error: setting initial offset in file"));
					#endif

					// Close file
					file_down.close();

					return -12;
				}
			}
		}while ((i != FTP_data) && (count > 0));

		size_pointer += FTP_data;

		#if GPRS_debug_mode>0
			PRINT_GPRS(F("Bytes stored: "));
			USB.print(size_pointer, DEC);
			USB.print(F("/"));
			USB.println(file_size, DEC);
		#endif

		if (count == 0)
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[10])));	//AT_FTP_GET
			snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s2,0", str_aux1);
			waitForData("+FTPGET:1,64", AT_FTP_WAIT_CONNEC, millis(), 0);
			return -18;

		}

		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[10])));	//AT_FTP_GET
		#if BUFFER_SIZE>BUFFER_UART
			snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s2,%d", str_aux1, BUFFER_UART);
		#else
			snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s2,%d", str_aux1, BUFFER_SIZE);
		#endif
		//snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s2,200", str_aux1);
		answer=sendCommand2(buffer_GPRS, "+FTPGET:2,", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);
		if(answer == 0)
		{
			file_down.close();
			return -19;
		}
		else if(answer == 2)
		{
			file_down.close();
			return -52;
		}


		count = 0;
		previous = millis();
		do{	// Gets the length of the data string
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			str_aux1[count] = serialRead(_socket);
			count++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((str_aux1[count - 1] != '\r') && ((millis()-previous) < AT_FTP_WAIT_CONNEC ));

		str_aux1[count - 1] = '\0';
		FTP_data = atoi(str_aux1);

		serialRead(_socket); // Skips '\n'
		#if GPRS_debug_mode>0
			PRINT_GPRS(F("FTP data: "));
			USB.println(FTP_data, DEC);
		#endif
	}


	file_down.close();

	if ((millis()-previous) > AT_FTP_WAIT_CONNEC )
	{
		return -53;
	}

	answer = waitForData("+FTPGET:1,0", AT_FTP_WAIT_CONNEC, millis(), 0);
	if (answer != 1)
	{
		return -54;
	}

	return 1;
}

/*
 * '-21' setting the file name in the FTP to get the file size
 * '-22' setting the path in the FTP to get the file size
 * '-23' if error getting the file size (no answer from module)
 * '-53' setting the file name in the FTP to get the file size with CME error code available,
 * '-54' setting the path in the FTP to get the file size with CME error code available
 * '-55' if error getting the file size with CME error code available
 * '-56' if FTP is busy error getting the size of the file from the FTP
 */
long WaspGPRS_Pro_core::getfilesizeFTP(const char* path){

	unsigned long previous=0;
	long size=0;
	uint8_t answer=0;
	int n_bytes=0;


	#if GPRS_debug_mode>0
		PRINTLN_GPRS(F("Inside FTPsize"));
	#endif

	previous = millis();
	while ((FTPstatus() == 2) && ((millis()-previous) < AT_FTP_WAIT_CONNEC ))
	{
		delay(1000);
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}

	if ((millis()-previous) > AT_FTP_WAIT_CONNEC )
	{
		#if GPRS_debug_mode>0
			USB.println(F("FTP busy"));
		#endif
		return -56;
	}

	// Sets server path and name
	delay(50);
	// AT+FTPGETNAME="<name>"
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[11])));	//+FTPGETNAME=
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, strrchr(path,'/'));
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG, SEND_ONCE);
	if(answer == 0)
	{
		return -21;
	}
	else if(answer == 2)
	{
		return -53;
	}

	delay(50);
	// +FTPGETPATH="<path>"
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[12])));	//+FTPGETPATH=
	if (path == strrchr(path, '/'))
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"/\"", str_aux1);
	}
	else
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, path);
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS + 1] = '\0';
		buffer_GPRS[strrchr(buffer_GPRS, '/') - buffer_GPRS] = '\"';
	}
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, AT_FTP_WAIT_CONFIG, SEND_ONCE);
	if(answer == 0)
	{
		return -22;
	}
	else if(answer == 2)
	{
		return -54;
	}

	delay(50);
	// AT+FTPSIZE
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[13])));	//+FTPSIZE
	answer=sendCommand2(str_aux1, "+FTPSIZE:1,0,", ERROR_CME, AT_FTP_WAIT_CONNEC, SEND_ONCE);
	if(answer == 0)
	{
		return -23;
	}
	else if(answer == 2)
	{
		return -55;
	}

	n_bytes = 0;
	previous = millis();
	do{	// Gets the length of the data string
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < AT_FTP_WAIT_CONNEC ))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		str_aux1[n_bytes] = serialRead(_socket);
		n_bytes++;
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((str_aux1[n_bytes - 1] != '\r') && ((millis()-previous) < AT_FTP_WAIT_CONNEC ));

	str_aux1[n_bytes - 1] = '\0';
	size = atol(str_aux1);


	if ((millis()-previous) > AT_FTP_WAIT_CONNEC )
	{
		#if GPRS_debug_mode>0
			PRINTLN_GPRS(F("Timeout"));
		#endif
		return -56;
	}

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Size in FTP: "));
		USB.println(size, DEC);
	#endif

	return size;

}

/* FTPstatus() - Checks if the FTP is busy
 *
 * This function checks if the FTP is busy or idle
 *
 * Returns '2' if FTP is busy, '1' if FTP is idle and '0' if error.
*/
int8_t WaspGPRS_Pro_core::FTPstatus(){
	unsigned long previous;
	int8_t answer;

	// GET THE FTP STATE: AT+FTPSTATE
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[14])));	//"+FTPSTATE"
	answer = sendCommand2(str_aux1, str_aux1, ERROR_CME);
	if (answer == 1)
	{
		previous = millis();
		while((serialAvailable(_socket) < 2) && ((millis() - previous) < 2000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		if ((millis() - previous) > 2000)
		{
			return 0;
		}

		serialRead(_socket);	//':'
		serialRead(_socket);	//' '
		return (serialRead(_socket) - 0x2F);
	}
	else if (answer == 2)
	{
		return -2;
	}
	return 0;
}
#endif


/* closeGPRS_HTTP_FTP_connection(uint8_t) - closes at opened connection for FTP or HTTP
 *
 * This function closes a GPRS connection with the carrier server to get access
 * to the HTTP and FTP applications
 *
 * It can closes 3 different profiles (1-3)
 *
 * Returns
 * 	'1' on success
 * 	'0' if error
 * 	'-2' error with CME error code available
*/
int8_t WaspGPRS_Pro_core::closeGPRS_HTTP_FTP_connection(uint8_t n_conf){

	int answer;

	// CLOSE CONNECTION: AT+SAPBR=0,<n_conf>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[30])));	//"+SAPBR="
	snprintf(str_aux3, sizeof(str_aux3), "%s0,%u", str_aux1, n_conf); // Closes connection
	answer=sendCommand2(str_aux3, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}

	return 1;
}



/* openGPRS_HTTP_FTP_connection(uint8_t n_conf)
 *
 * Open Connection for data transmission for both HTTP and FTP features *
 *
 * Returns
 * '1' on success
 * '-1' if no GPRS connection
 * '-2' if error opening the connection,
 * '-3' if error getting the IP address
*/
int8_t WaspGPRS_Pro_core::openGPRS_HTTP_FTP_connection(uint8_t n_conf)
{

	uint8_t i = 0;
	int8_t answer;
	unsigned long previous;
	uint16_t counter = 0;

	//Checks the GPRS connection
	answer = checkGPRS(90);
	if (answer != 1)
	{
		return -1;
	}

	// OPEN CONNECTION: AT+SAPBR=1,<n_conf>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[30])));	//"+SAPBR="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s1,%u", str_aux1, n_conf);
	counter = 5;
    do{
        counter--;
		answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME, 20000, SEND_ONCE);

		// If CME ERROR check if connection is already up
		if (answer == 2)
		{
			// AT+SAPBR=2,<n_conf>
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[30]))); 	//"+SAPBR="
			snprintf(str_aux1, sizeof(str_aux1), "%s2,%u", str_aux3, n_conf);
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[44])));	//"+SAPBR: "
			snprintf(str_aux2, sizeof(str_aux2), "%s%u,", str_aux3, n_conf);
			answer = sendCommand2(str_aux1, str_aux2, ERROR_CME);
			if (answer == 1)
			{
				// read status
				answer = serialRead(_socket) - 0x30;
				#if GPRS_debug_mode>0
					PRINT_GPRS(F("Connection status: "));
					USB.println(answer, DEC);
				#endif
			}
			delay(10000);
		}

    }while ((answer != 1) && (counter != 0));

    if ((counter == 0) && (answer != 1))
	{
        return -2;
    }

	// AT+SAPBR=2,<n_conf>
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[30])));	//AT_GPRS_CFG
	snprintf(str_aux1, sizeof(str_aux1), "%s2,%u", str_aux3, n_conf);
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[44])));	//BEARER_RES
	snprintf(str_aux2, sizeof(str_aux2), "%s%u,1,\"", str_aux3, n_conf);
	counter = 10;
    do{
		previous = millis();
        counter--;
        answer = sendCommand1(str_aux1, str_aux2);
		if (answer == 1)
		{
			i = 0;
			do{
				while ((!serialAvailable(_socket)) && ((millis()-previous) < 10000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}
				IP_dir[i] = serialRead(_socket);
				i++;
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((IP_dir[i-1] != '"') && ((millis()-previous) < 10000));
			IP_dir[i-1] = '\0';
		}

    }while ((answer != 1) && (counter != 0));

    if (counter == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
        return -3;
    }

    return 1;
}


#if HTTP_FUSE



/* initHTTP
 *
 * Initializes HTTP connection
 *
 * Returns
 * '1' on success
 * '-4' if error initializing the HTTP service
 * '-5' if error setting CID the HTTP service
 * '-6' if error setting the url the HTTP service
 * '-10' if error initializing the HTTP service with CME error code available,
 * '-11' if error setting CID the HTTP service with CME error code available,
 * '-12' if error setting the url the HTTP service with CME error code available,
*/
int8_t WaspGPRS_Pro_core::initHTTP(	const char* url,
								uint8_t* data,
								int length,
								uint8_t n_conf,
								uint8_t frame_flag)
{
	uint16_t counter;
	int8_t answer;
	char aux[3];
	memset( aux, 0x00, sizeof(aux) );

	// INIT HTTP CONNECTION: AT+HTTPINIT
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[0])));	//AT_HTTP_INIT
	serialFlush(_socket);
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME); // Initializes HTTP service
	if (answer == 0)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -4;
	}
	else if (answer == 2)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -10;
	}

	// AT+HTTPPARA="CID",1
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[1])));	//AT_HTTP_PARAM
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_HTTP[7])));	//AT_HTTP_CID
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\",%u", str_aux1, str_aux2, n_conf); // Sets HTTP values
	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -5;
	}
	else if (answer == 2)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -11;
	}

	// SET URL: AT+HTTPPARA="URL",<url>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[1])));	//AT_HTTP_PARAM
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_HTTP[8])));	//AT_HTTP_URL
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "AT%s\"%s\",\"%s", str_aux1, str_aux2, url);

	counter=strlen(buffer_GPRS);

  #if GPRS_debug_mode>0
    PRINT_GPRS(F(""));
  #endif
	for(uint16_t x=0; x < counter; x++)
	{
		printByte(buffer_GPRS[x], _socket);
		#if GPRS_debug_mode>0
			USB.print(char(buffer_GPRS[x]));
		#endif
	}

	// In the case we have a frame, we introduce this field
	if( frame_flag == FRAME_ENABLED )
	{
		// Get FRAME_HEADER_FIELD from Flash: "frame="
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[12])));
		printString(str_aux1, _socket);
		#if GPRS_debug_mode>0
			USB.print(str_aux1);
		#endif
	}

	for(int x=0; x < length; x++)
	{
		if( frame_flag == FRAME_ENABLED )
		{
			// make conversion from byte to hex representation in ASCII (2Bytes)
			Utils.hex2str(&data[x], aux, 1);
			printByte(aux[0], _socket);
			printByte(aux[1], _socket);
			#if GPRS_debug_mode>0
				USB.print(char(aux[0]));
				USB.print(char(aux[1]));
			#endif
		}
		else
		{
			printByte(data[x], _socket);
			#if GPRS_debug_mode>0
				USB.print(char(data[x]));
			#endif
		}
	}
	printByte('"', _socket);
	printByte('\r', _socket);
	printByte('\n', _socket);
	#if GPRS_debug_mode>0
		USB.println("\"");
	#endif

	answer=waitForData(OK_RESPONSE, ERROR_CME, HTTP_TIMEOUT, millis(), 0, 2);
	if (answer == 0)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -6;
	}
	else if (answer == 2)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -12;
	}

	return 1;

}


/* setPOSTdata
 *
 * Configures the HTTP content parameter and sends the POST data to the module
 *
 * Returns
 * '1' on success
 * '-16' if error configuring the HTTP content parameter,
 * '-17' if error configuring the HTTP content parameter with CME error code available,
 * '-18' if error sending the POST data
 * '-19' if error sending the POST data with CME error code available
*/
int8_t WaspGPRS_Pro_core::setPOSTdata(uint8_t* POST_data, int length, uint8_t frame_flag)
{

	int8_t answer;
	char aux[3];
	int length_to_set;
	memset( aux, 0x00, sizeof(aux) );

	strcpy_P(buffer_GPRS, (char*)pgm_read_word(&(table_HTTP[11])));	//+HTTPPARA...
	answer = sendCommand2(buffer_GPRS,  OK_RESPONSE, ERROR_CME, HTTP_CONF_TIMEOUT, SEND_ONCE);

	if (answer == 0)
	{
		return -16;
	}
	else if (answer == 2)
	{
		return -17;
	}

	// In the case we have a frame, length is doubled
	if( frame_flag == FRAME_ENABLED )
	{
		// calculate length to be set: length*2 and the "frame="
		strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[12])));
		length_to_set = length * 2 + strlen(str_aux3);
	}
	else
	{
		length_to_set = length;
	}

	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_HTTP[9])));	//+HTTPDATA=
	snprintf(str_aux1, sizeof(str_aux1), "%s%d,30000", str_aux2, length_to_set);
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_HTTP[10])));	//DOWNLOAD
	answer = sendCommand2(str_aux1,  str_aux2, ERROR_CME, HTTP_CONF_TIMEOUT, SEND_ONCE);
	if (answer == 1)
	{
		// In the case we have a frame, we introduce this field
		if( frame_flag == FRAME_ENABLED )
		{
			printString(str_aux3, _socket);
		}

		for(int16_t x = 0; x < length; x++)
		{
			if( frame_flag == FRAME_ENABLED )
			{
				// make conversion from byte to hex representation in ASCII (2Bytes)
				Utils.hex2str(&POST_data[x], aux, 1);
				printByte(aux[0], _socket);
				printByte(aux[1], _socket);
			}
			else
			{
				printByte(POST_data[x], _socket);
			}
		}

		answer = waitForData(OK_RESPONSE, millis(), DEFAULT_TIMEOUT, 0);

		if (answer == 1)
		{
			return 1;
		}
		else
		{
			return -19;
		}
	}

	return -18;

}

/* sendHTTP
 *
 * Send the HTTP request.
 *
 * 'method' stands for GET=0 or POST=1
 *
 * Returns
 * 'HTTP_total_data" when ok with the number of bytes
 * '-7' if error starting HTTP session
 * '-13' if error starting HTTP sesion with CME error code available,
 * '-20' if error getting data from url with CME error code available,
 *
*/
int WaspGPRS_Pro_core::sendHTTP(uint8_t n_conf, uint8_t method)
{
	int8_t answer;
	uint8_t i = 0;
	unsigned long previous;
	int HTTP_code;
	int HTTP_total_data;
	uint16_t counter = 0;

	// set number of retries for http action
	counter = 3;

	do
	{
		memset(buffer_GPRS, '\0', sizeof(buffer_GPRS) );
		HTTP_code = 0;

		// START HTTP SESSION: +HTTPACTION=<method>
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_HTTP[2])));	//+HTTPACTION=
		snprintf(str_aux1, sizeof(str_aux1), "%s%d", str_aux2, method);
		strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[3])));	//+HTTPACTION:
		snprintf(str_aux2, sizeof(str_aux2), "%s%d,", str_aux3, method);
		answer = sendCommand2(str_aux1,  str_aux2, ERROR_CME, HTTP_TIMEOUT, SEND_ONCE);
		if (answer == 1)
		{
			//Reads the HTTP status codes
			previous = millis();
			i = 0;
			do{
				while ((!serialAvailable(_socket)) && ((millis()-previous) < 10000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}
				buffer_GPRS[i] = serialRead(_socket);
				i++;
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((buffer_GPRS[i-1] != ',') && ((millis()-previous) < 10000));

			buffer_GPRS[i-1] = '\0';

			HTTP_code = atoi(buffer_GPRS);
		}

		counter--;

	}while ((answer != 1) && (HTTP_code != 200) && (counter > 0));

	if (answer == 0)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -7;
	}
	else if (answer == 2)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -13;
	}

	// HTTP_code MUST be equal to 200
	if (HTTP_code != 200)
	{
		closeHTTP();
		//closeGPRS_HTTP_FTP_connection(n_conf);
		CME_CMS_code=HTTP_code;
		return -20;
	}

	//Gets the data length
	memset(str_aux1, '\0', sizeof(str_aux1));
	previous = millis();
	i = 0;
	do{
		while ((!serialAvailable(_socket)) && ((millis()-previous) < 10000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		str_aux1[i] = serialRead(_socket);
		i++;
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((str_aux1[i-1] != '\r') && ((millis()-previous) < 10000));

	str_aux1[i-1] = '\0';
	HTTP_total_data = atoi(str_aux1);

	#if GPRS_debug_mode>0
		PRINTLN_GPRS(F("HTTP data available: "));
		USB.println(HTTP_total_data, DEC);
	#endif

	return HTTP_total_data;

}


/* readHTTP
 *
 * Read data from GPRS module
 *
 * Returns
 * '1' on success
 * '2' if buffer_GPRS is full. The answer from the server is limited by the
 * 		length of buffer_GPRS. To increase the length of the answer, increase the
 * 		BUFFER_SIZE constant.
 * '-8' if error getting data from url
 * '-14' if error getting data from url with CME error code available,
 *
*/
int16_t WaspGPRS_Pro_core::readHTTP(	uint16_t HTTP_total_data,
								uint8_t n_conf)
{

	uint8_t i = 0;
	char aux;
	int8_t answer;
	unsigned long previous = millis();
	uint16_t counter = 0;
	uint16_t retries = 3;
	int HTTP_data;

	memset(buffer_GPRS, '\0', BUFFER_SIZE);

	do{
		// READ DATA: AT+HTTPREAD
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));	//AT_HTTP_READ
		snprintf(str_aux3, sizeof(str_aux3), "%s=%u,100", str_aux1, counter); 			// Reads url data
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[5])));	//AT_HTTP_READ_R
		answer = sendCommand2(str_aux3, str_aux1, ERROR_CME, 2000, 1);
		if (answer == 0)
		{
			if( retries>0 )
			{
				retries--;
				continue;
			}
			else
			{
				closeHTTP();
				closeGPRS_HTTP_FTP_connection(n_conf);
				return -8;
			}
		}
		else if (answer == 2)
		{
			closeHTTP();
			closeGPRS_HTTP_FTP_connection(n_conf);
			return -14;
		}

		i = 0;
		previous = millis();
		do{
			str_aux1[i] = serialRead(_socket);
			i++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((str_aux1[i - 1] != '\r') && (millis()-previous < 2000));
		str_aux1[i - 1] = '\0';
		HTTP_data = atoi(str_aux1);


		#if GPRS_debug_mode>0
			PRINT_GPRS(F("HTTP data: "));
			USB.println(HTTP_data, DEC);
		#endif

		serialRead(_socket);	// Skips '\n'

		// wait for all data to be received
		previous=millis();
		while ((serialAvailable(_socket) < HTTP_data) && (millis()-previous < 10000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}

		aux=0;
		previous=millis();
		do{
			if (counter < BUFFER_SIZE)
			{
				buffer_GPRS[counter]=serialRead(_socket);
				counter++;
				#if GPRS_debug_mode>1
					PRINT_GPRS(char(buffer_GPRS[counter-1]));
					USB.print(F("   "));
					USB.println(counter, DEC);
				#endif
			}
			else
			{
				serialRead(_socket);
			}
			aux++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((aux < HTTP_data) && (millis()-previous < 10000));
		waitForData(OK_RESPONSE, HTTP_TIMEOUT, millis(), 0);

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((HTTP_total_data > counter) && (counter < BUFFER_SIZE) && (millis()-previous < 10000));

	if (counter < BUFFER_SIZE)
	{
		buffer_GPRS[counter] = '\0';
	}
	else
	{
		buffer_GPRS[counter - 1] = '\0';
	}

	closeHTTP();

	//~ closeGPRS_HTTP_FTP_connection(n_conf);

	if (counter >= BUFFER_SIZE)
	{
		return 2;
	}

	return 1;

}

/* closeHTTP
 *
 * Close the HTTP service
 *
 * Returns
 * '1' on success
 * '-9' if error closing the HTTP service
 * '-15' if error closing the HTTP service with CME error code available
 *
*/
int8_t WaspGPRS_Pro_core::closeHTTP(){

	uint8_t answer;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));	//AT_HTTP_TERM
	answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		return -9;
	}
	else if (answer == 2)
	{
		return -15;
	}

	return 1;

}

#endif
// Public Methods //////////////////////////////////////////////////////////////


//Power functions
/* ON(void) - opens UART1 and powers the SIM900 module
 *
 * It opens UART1 and powers the SIM900 module
 *
 * Returns nothing
*/
int8_t WaspGPRS_Pro_core::ON(){

	detachInterrupt(RXD1_PIN);
	detachInterrupt(TXD1_PIN);

	#if GPRS_debug_mode==1
		PRINTLN_GPRS(F("Debug mode 1"));
	#endif
	#if GPRS_debug_mode==2
		PRINTLN_GPRS(F("Debug mode 2"));
	#endif

	if (RTC.isON == 0 )
	{
		RTC.ON();
		RTC.clearAlarmFlag();
		RTC.OFF();
	}
	else
	{
		RTC.clearAlarmFlag();
	}
	begin();
	return (setMode(GPRS_PRO_ON));
}

/* begin(void) - initialize SIM900 module
 *
 * This function powers up the SIM900 module and open Serial Port at velocity selected by the user
 * By default, it will be at 38400bps
 *
 * Returns nothing
*/
void WaspGPRS_Pro_core::begin(){
	_baudRate=GPRS_PRO_RATE;
	Utils.setMuxSocket1();
	beginSerial(_baudRate, _socket);
}

/* close(void) - closes UART used by SIM900 module
 *
 * This function closes UART used by SIM900 module
 *
 * Returns nothing
*/
void WaspGPRS_Pro_core::close(){
	closeSerial(_socket);
	Utils.setMux(LOW, LOW);
}

/* OFF(void) - closes UART1 and powers off the SIM900 module
 *
 * This function closes UART1 and powers off the SIM900 module
 *
 * Returns nothing
*/
int8_t WaspGPRS_Pro_core::OFF(){
	int8_t answer;

    answer = setMode(GPRS_PRO_POWER_OFF);
	close();
	if ( RTC.isON == 2 )
	{
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
	return answer;
}

/* setMode(uint8_t) - Sets GPRS Power Mode
 *
 * This function selects the active power mode among: ON, SLEEP/HIBERNATE and OFF
 * It does not close the serial port, only sends the proper command to GPRS module
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
*/
int8_t WaspGPRS_Pro_core::setMode(uint8_t pwrMode){

	uint8_t answer=0;
	uint8_t battery_level;
	uint8_t counter, global_counter;

	switch (pwrMode)
	{
		case GPRS_PRO_ON:

			battery_level = PWR.getBatteryLevel();

			//GPRS_Pro v1.0

			// Comment the next two lines if there aren't transistors (jumper must be soldered)
			//pinMode(DIGITAL6, OUTPUT);
			//digitalWrite(DIGITAL6, HIGH);


			/*pinMode(GPRS_PW, OUTPUT);
			digitalWrite(GPRS_PW, LOW);
			getIfReady();
			#if GPRS_debug_mode>0
				USB.print("not_ready: ");
				USB.println(not_ready, DEC);
			#endif
			if (not_ready == 1) // if the module is started skip the start pulse
			{
				delay(500);
				digitalWrite(GPRS_PW, HIGH);
				delay(2000);
				digitalWrite(GPRS_PW, LOW);
			}

			counter=10;
			global_counter = 5;
			while ((not_ready == 1) && (global_counter > 0))
			{
				getIfReady();

				#if GPRS_debug_mode>0
					USB.print("not_ready: ");
					USB.println(not_ready, DEC);
				#endif
				counter--;
				if (counter == 0)
				{
					delay(500);
					digitalWrite(GPRS_PW, HIGH);
					delay(2000);
					digitalWrite(GPRS_PW, LOW);
					counter=10;
					global_counter--;
				}
			}*/


			// GPRS_Pro v2.0
			pinMode(GPRS_PW, OUTPUT);
			digitalWrite(GPRS_PW, LOW);
			delay(500);
			digitalWrite(GPRS_PW, HIGH);

			delay(500);
			getIfReady();
			#if GPRS_debug_mode>0
				PRINT_GPRS(F("not_ready: "));
				USB.println(not_ready, DEC);
			#endif

			counter = 15;
			global_counter = 3;
			while ((not_ready == 1) && (global_counter > 0))
			{
				getIfReady();
				#if GPRS_debug_mode>0
					PRINT_GPRS(F("not_ready: "));
					USB.println(not_ready, DEC);
				#endif
				counter--;
				delay(1000);
				if (counter == 0)
				{
					#if GPRS_debug_mode>0
						PRINTLN_GPRS(F("Restarting"));
					#endif
					delay(500);
					digitalWrite(GPRS_PW, LOW);
					delay(2000);
					digitalWrite(GPRS_PW, HIGH);
					counter = 15;
					global_counter--;
				}
			}

			if (global_counter > 0)
			{
				// All versions
				// Enables numeric error codes: AT+CMEE=1
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[32])));	//NUMERIC_ERROR
				sendCommand2(str_aux1,OK_RESPONSE, ERROR, 500, 1);

				// Disables command echoes: ATE0
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[33])));	//NO_ECHO
				sendCommand2(str_aux1,OK_RESPONSE, ERROR, 500, 1);

				// Disable slow clock: AT+CSCLK=0
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[3])));	//POWER_NO_SLEEP
				answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR, 500, 1);

				// Set Phone to Full Functionality: AT+CFUN=1
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[0])));	//POWER_FULL
				answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME, 500, 1);

				if (battery_level < 30)
				{
					PRINTLN_GPRS(F("\n********************"));
					PRINTLN_GPRS(F("Danger! Low battery!"));
					PRINTLN_GPRS(F("********************"));
					answer = 3;
				}
			}
			else
			{
				digitalWrite(GPRS_PW, LOW);
				answer = 0;
			}

			break;

		case GPRS_PRO_FULL:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[3])));	//POWER_NO_SLEEP
			answer=sendCommand1(str_aux1, OK_RESPONSE);
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[0])));	//POWER_FULL
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			break;

		case GPRS_PRO_RF_OFF:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[3])));	//POWER_NO_SLEEP
			answer=sendCommand1(str_aux1, OK_RESPONSE);
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[1])));	//POWER_RF_OFF
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			break;

		case GPRS_PRO_MIN:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[3])));	//POWER_NO_SLEEP
			answer=sendCommand1(str_aux1, OK_RESPONSE);
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[2])));	//POWER_MIN
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			break;

		case GPRS_PRO_SLEEP:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[4])));	//POWER_SLEEP
			answer=sendCommand1(str_aux1, OK_RESPONSE);
			break;

		case GPRS_PRO_POWER_OFF:
			// GPRS_Pro v1.0
			/*delay(500);
			digitalWrite(GPRS_PW, HIGH);
			delay(2000);
			digitalWrite(GPRS_PW, LOW);
			delay(500);

			// Comment the next two lines if there aren't transistors (jumper must be soldered)
			//pinMode(DIGITAL6, OUTPUT);
			//digitalWrite(DIGITAL6, LOW);

			*/

			// GPRS_Pro v2.0
			pinMode(GPRS_PW, OUTPUT);
			digitalWrite(GPRS_PW, LOW);
			answer=1;
			_pwrMode=pwrMode;

			// All versions
			delay(1000);
			getIfReady();
			if (not_ready == 1)
			{
				answer = 1;
			}
			else
			{
				answer = 0;
			}

			break;
	}
	if (answer == 1)
	{
		_pwrMode=pwrMode;
		return 1;
	}
	else if (answer > 1)
	{
		return -answer;
	}

	return 0;
}

/* getMode(void) - Gets GPRS_Pro Power Mode
 *
 * This function gets the actual GPRS_Pro Power Mode. Possible values are ON, FULL, RF_OFF, MIN, SLEEP and POWER_OFF
 *
 * Returns the power mode
*/
uint8_t	WaspGPRS_Pro_core::getMode(){
	return	_pwrMode;
}

/* setTime() - Sets time and date to GPRS_Pro module from RTC
 *
 * Sets time and date to GPRS_Pro module from RTC
 *
 * Returns '1' on success , '0' if error and '2' if error with CME error response.
*/
uint8_t WaspGPRS_Pro_core::setTime(){

	bool RTC_ant=false;
	int8_t answer;

	if (RTC.isON != 1) // Checks if the RTC is on
	{
		RTC_ant=true;
		RTC.ON();
	}

	RTC.getTime(); //Gets time from RTC

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[5])));	//SET_TIME
	snprintf(buffer_GPRS, sizeof(buffer_GPRS)
		, "%s\"%02u/%02u/%02u,%02u:%02u:%02u+00\""
		, str_aux1
		, RTC.year
		, RTC.month
		, RTC.date
		, RTC.hour
		, RTC.minute
		, RTC.second
		);

	if (RTC_ant) // Powers off the RTC if before it was off
	{
		RTC.OFF();
	}

	answer=sendCommand2( buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer == 2)
	{
		return -answer;
	}
	else
	{
		return answer;
	}
}

/* check(unsigned long) - Checks if GPRS is connected to the network
 *
 * This function checks if GPRS module is connected to the network. If not, it
 * has no sense working with GPRS.
 *
 * It sends a command to GPRS module DEFAULT_TIMEOUT times. If GPRS module does
 * not connect within these tries, function
 * exits.
 *
 * Returns '1' when connected,
 * '0' if not registered and the module is not currently searching a new operator,
 * '-2' if not registered, but the module is currently searching a new operator,
 * '-3' if registration denied
 * '-4' if the state is unknown
 */
int8_t WaspGPRS_Pro_core::check(unsigned long time){

	unsigned long previous;
	int8_t answer;

	// CHECK NETWORK REGISTRATION: AT+CREG?
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[34])));	//CHECK
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[35])));	//CHECK_RES

	previous = millis();

	do{
		// Sends the command and waits for the answer (0,1 for home network and 0,5 for roaming)
		answer = sendCommand1(str_aux1, str_aux2, 3000, 1);

		if (answer == 1)
		{
			answer = serialRead(_socket) - 0x30;
		}
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while (((answer == 2) || (answer == 4) || (answer == 0)) && ((millis() - previous) < (time * 1000)));

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Network status: "));
		USB.println(answer, DEC);
	#endif

	// check correct answer
	if ( (answer == 1) || (answer == 5) )
	{
		return 1;
	}

	// if error return corresponding flag
	//setDefault();
	return -answer;


}


//SIM functions
/* setPIN(const char*) - sets PIN to the SIM
 *
 * This function sets the specified PIN to the SIM
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t	WaspGPRS_Pro_core::setPIN(const char* pin){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[6])));	//AT_PIN
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, pin);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);

	if (answer == 2)
	{
		return -2;
	}

	return answer;
}

/* changePIN(const char*, const char*) - changes PIN number to the SIM
 *
 * This function changes the PIN number to the SIM
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::changePIN(const char* old_pin, const char* new_pin){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[7])));	//AT_CHANGE_PASSWORD
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"SC\",\"%s\",\"%s\"", str_aux1, old_pin, new_pin);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);

	if (answer == 2)
	{
		return -2;
	}

	return answer;

}

/* getIMEI() - gets the IMEI from the SIM card
 *
 * This function gets the IMEI from the SIM card. It stores the IMEI into 'buffer_GPRS' variable.
 *
 * Returns '1' on success and '0' if error
*/
int8_t WaspGPRS_Pro_core::getIMEI(){

	int8_t answer,counter;
	unsigned long previous;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[8])));	//AT_GPRS_IMEI
	answer=sendCommand1(str_aux1, "\r\n");

	if (answer == 1)
	{
		previous=millis();
		counter=0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) <= 2000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			buffer_GPRS[counter]=serialRead(_socket);
			if ((buffer_GPRS[counter] != '\r') && (buffer_GPRS[counter] != '\n'))
			{
				counter++;
			}
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((buffer_GPRS[counter] != '\r') && ((millis()-previous) <= 2000));

		if (buffer_GPRS[counter] == '\r')
		{
			buffer_GPRS[counter]='\0';
			return 1;
		}
	}

	return 0;

}

/* getIMSI() - gets the IMSI from the SIM card
 *
 * This function gets the IMSI from the SIM card. It stores the IMSI into 'buffer_GPRS' variable.
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::getIMSI(){

	unsigned long previous;
	int8_t counter=0,answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[9])));	//AT_GPRS_IMSI
	answer=sendCommand2(str_aux1, "\r\n", ERROR_CME);

	if (answer == 1)
	{
		previous=millis();
		counter=0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			buffer_GPRS[counter]=serialRead(_socket);
			if ((buffer_GPRS[counter] != '\r') && (buffer_GPRS[counter] != '\n'))
			{
				counter++;
			}
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((((buffer_GPRS[counter] != '\r') && (buffer_GPRS[counter] != '\n')) || (counter == 0)) && ((millis()-previous) < 3000));

		if (buffer_GPRS[counter] == '\r')
		{
			buffer_GPRS[counter]='\0';
			return 1;
		}
	}
	else if (answer == 2)
	{
		return -2;
	}

	return 0;
}


#if GSM_FUSE
//Call functions
/* makeCall(const char*) - makes a call to the seleted telephone number
 *
 * This function makes a call to the given telephone number.
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::makeCall(const char* tlfNumber){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[0])));	//AT_CALL
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%s;", str_aux1, tlfNumber);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);

	if (answer != 1)
	{
		return 0;
	}
	return 1;

}

/* makelostCall(const char* , uint8_t) - makes a lost call to the seleted telephone number
 *
 * This function makes a call to the given telephone number and its duration is specified by the other input.
 * After 'timeCall' seconds, hang the call up.
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::makeLostCall(const char* tlfNumber, uint8_t timeCall){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[0])));	//AT_CALL
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%s;", str_aux1, tlfNumber);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);

	if (answer == 1)
	{
		for (int a=0; a < timeCall ; a++)
		{
			delay(1000);
		}
		hangUp();
		return 1;
	}

	return 0;
}

/* setInfoIncomingCall() - set the info shown when an incoming call is received
 *
 * This function sets the info shown when an incoming call is received
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
 */
int8_t	WaspGPRS_Pro_core::setInfoIncomingCall(){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[3])));	//AT_ID_INCALL
	answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);

	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}

	return 1;
}

/* readCall(const char*) - set in 'buffer_GPRS' variable the tlf number of the incoming call
 *
 * This function sets in 'tlfIN' variable the tlf number of the incoming call
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * 'data' must contains the tlfn number, something like that: aaaa"+34666999888"aaa
 *
 * Returns '1' on success and '0' if error
*/
uint8_t	WaspGPRS_Pro_core::readCall(){
	uint8_t a = 0;
	unsigned long previous;

	memset(buffer_GPRS, '\0', sizeof(buffer_GPRS) );

	previous = millis();

	// Reads up to the phone number
	do{
		while (!serialAvailable(_socket) && ((millis()-previous) < 2000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}

		buffer_GPRS[0] = serialRead(_socket);	// Reads a byte

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((buffer_GPRS[0] != '"') && ((millis() - previous) < 2000));

	if ((millis() - previous) > 2000)
	{
		return 0;
	}

	// Stores in buffer_GPRS the phone number
	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Phone number: "));
	#endif
	previous = millis();
	do{
		while (!serialAvailable(_socket) && ((millis()-previous) < 2000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}

		buffer_GPRS[a] = serialRead(_socket);	// Reads a byte
		#if GPRS_debug_mode>0
			USB.print(char(buffer_GPRS[a]));
		#endif
		a++;
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((buffer_GPRS[a-1] != '"') && ((millis() - previous) < 2000));

	buffer_GPRS[a - 1] = '\0';

	if ((millis() - previous) > 2000)
	{
		return 0;
	}

	return 1;

}

/* hangUp() - hangs the call up
 *
 * This function hangs all the active calls up.
 *
 * Returns '1' on success and '0' if error
*/
uint8_t WaspGPRS_Pro_core::hangUp(){
	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[1])));	//AT_HANG
	answer=sendCommand1(str_aux1, OK_RESPONSE);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* setMonitorVolume(uint8_t) - Sets the monitor speaker loudness
 *
 * This function sets the monitor speaker loudness from 0 to 9
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro_core::setMonitorVolume(uint8_t volume){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[15])));	//AT_SPEAKER_VOLUME
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, volume);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* setMonitorMode(uint8_t) - Sets the monitor speaker mode
 *
 * This function sets the monitor speaker mode from 0 to 9
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro_core::setMonitorMode(uint8_t mode){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[16])));	//AT_SPEAKER_MODE
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, mode);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);

	if (answer != 1)
	{
		return 0;
	}
	return 1;

}

/* setCLIPresentation(uint8_t) - Enables or disables the presentation of the incoming call
 *
 * This function enables or disables the presentation of the incoming call
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro_core::setCLIPresentation(uint8_t mode){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[17])));	//AT_CLIP_MODE
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, mode);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);

	if (answer != 1)
	{
		return 0;
	}
	return 1;

}

/* setCLIRestriction(uint8_t) - Restricts or enables the presentation of the CLI to the called party when originating a call.
 *
 * This function restricts or enables the presentation of the CLI to the called party when originating a call.
 *
 * Allowed modes DEFAULT_CLIR='0', INVOKE_CLIR='1' or SUPPRESS_CLIR='2'
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro_core::setCLIRestriction(uint8_t mode){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[18])));	//AT_CLIR_MODE
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, mode);
	answer=sendCommand1(buffer_GPRS, OK_RESPONSE);

	if (answer != 1)
	{
		return 0;
	}
	return 1;

}

/* getPhoneStatus() - Gets the phone activity status
 *
 *This function gets the phone activity status
 *
 *Return '0' for error, '1'= Ready, '2'= Unknown,'3'= Ringing, '4'= Call in progress
*/
uint8_t WaspGPRS_Pro_core::getPhoneActStatus(){
	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[19])));	//AT_PHONE_ACTIVITY
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_GSM[20])));	//AT_PHONE_ACTIVITY_R
	answer=sendCommand2(str_aux1, str_aux2, ERROR);

	if (answer != 1)
	{
		return 0;
	}
	else
	{
		serialRead(_socket);	// ' '
		answer=serialRead(_socket)-0x30;
		if (answer == 0)
		{
			answer=1;
		}
	}

	return answer;
}

/* setLoudspeakerLevel() - Sets loudspeaker volume
 *
 * This function sets loudspeaker volume level between 0-100
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
*/
uint8_t WaspGPRS_Pro_core::setLoudspeakerLevel(uint8_t volume){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[24])));	//AT_SPEAKER_LEVEL
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, volume);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);

	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}

	return 1;
}

/* setCallAlert(uint8_t) - Configures the mode of calls alert
 *
 * This function configures the mode of calls alert
 *
 * Returns '1' on success, '0' if error setting the sound mode, '-2' if error setting the sound mode with CME error code available,
 * '-3' if error setting the sound type, '-4' if error setting the sound type with CME error code available,
 * '-5' if error setting the ring level, '-6' if error setting the ring level with CME error code available,
*/
uint8_t WaspGPRS_Pro_core::setCallAlert(uint8_t mode){
	return setCallAlert(mode, 0, 0);
}

/* setCallAlert(uint8_t,uint8_t, uint8_t) - Configures the mode of calls alert
 *
 * This function configures the mode of calls alert
 *
 * Returns '1' on success, '0' if error setting the sound mode, '-2' if error setting the sound mode with CME error code available,
 * '-3' if error setting the sound type, '-4' if error setting the sound type with CME error code available,
 * '-5' if error setting the ring level, '-6' if error setting the ring level with CME error code available,
*/
uint8_t WaspGPRS_Pro_core::setCallAlert(uint8_t mode,uint8_t sound_type, uint8_t ring_level){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[21])));	//AT_ALERT_SOUND_MODE
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, mode);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[22])));	//AT_ALERT_SOUND_LEVEL
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", AT_ALERT_SOUND_LEVEL, sound_type);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		return -3;
	}
	else if (answer == 2)
	{
		return -4;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[23])));	//AT_RINGER_SOUND_LEVEL
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", AT_RINGER_SOUND_LEVEL, ring_level);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		return -5;
	}
	else if (answer == 2)
	{
		return -6;
	}

	return 1;
}

/* setMute(uint8_t) - Enables or disables mute during a call
 *
 * This function enables or disables mute during a call
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
*/
uint8_t WaspGPRS_Pro_core::setMute(uint8_t mute_mode){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[25])));	//AT_MUTE
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, mute_mode);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);

	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}
	return 1;
}


//SMS functions
/* setTextModeSMS() - set the text mode to the sms
 *
 * This function sets the text mode to the sms
 *
 * Returns '1' on success and '0' if error
 */
uint8_t WaspGPRS_Pro_core::setTextModeSMS(){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[6])));	//AT_SMS_MODE
	answer=sendCommand1(str_aux1, OK_RESPONSE);

	if (answer != 1)
	{
		return 0;
	}

	return 1;
}

/* sendSMS(const char*, const char*) - sends a SMS to the specified number
 *
 * This function sends an SMS to the specified number.
 *
 * Returns '1' on success,'0' if error, '-2' if error sending the SMS and '-3' if error sending the SMS with CMS error code available
*/
int8_t WaspGPRS_Pro_core::sendSMS(const char* smsText, const char* tlfNumber){

	uint8_t answer=0;

	setTextModeSMS();

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[4])));	//AT_SMS
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, tlfNumber);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[5])));	//AT_SMS_R
	answer=sendCommand1(buffer_GPRS, str_aux1);
	if (answer != 1)
	{
		return 0;
	}

	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%c", smsText, 0x1A);
	printString(buffer_GPRS, _socket);
	answer=waitForData(OK_RESPONSE, ERROR_CMS, DEFAULT_TIMEOUT, millis(), 0, 2);

	if (answer == 0)
	{
		return -2;
	}
	else if (answer == 2)
	{
		return -3;
	}

	return 1;
}

/* setInfoIncomingSMS() - set the info shown when an incoming SMS is received
 *
 * This function sets the info shown when an incoming SMS is received
 *
 * Returns '1' on success and '0' if error
 */
uint8_t WaspGPRS_Pro_core::setInfoIncomingSMS(){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[7])));	//AT_SMS_INFO
	answer=sendCommand1(str_aux1, OK_RESPONSE);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* incomingSMS(uint8_t ) - Gets the index of the incoming SMS
 *
 * This function gets the index of the incoming SMS
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * Returns the index of SMS, '0' if error
*/
//int8_t WaspGPRS_Pro_core::incomingSMS(const char* smsData){
uint8_t WaspGPRS_Pro_core::incomingSMS(){

	unsigned long previous;
	int count;


	previous = millis();
	do{

		while (((millis() - previous) < 1000) && (serialAvailable(_socket) == 0))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while (((millis() - previous) < 1000) && (serialRead(_socket) != ','));

	count = 0;
	previous = millis();
	do{
		buffer_GPRS[count] = serialRead(_socket);
		count++;

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((buffer_GPRS[count-1] != '\r') && ((millis() - previous) < 1000) && (count < BUFFER_SIZE));

	buffer_GPRS[count-1] = '\0';

	count = atoi(buffer_GPRS);

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("SMS index: "));
		USB.println(count, DEC);
	#endif

	if ((millis() - previous) > 1200)
	{
		return 0;
	}

	return count;

}

/* readSMS() - set in 'tlfIN' and 'buffer_GPRS' variables the tlf number and text of the incoming SMS
 *
 * This function sets in 'tlfIN' and 'buffer_GPRS' variables the tlf number and text of the incoming SMS
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * Returns '1' on success, '0' if error and '-1' if no memory
*/
int8_t WaspGPRS_Pro_core::readSMS(uint8_t sms_index){

	int8_t answer = 0;
	unsigned long previous;
	int counter = 0;

	setTextModeSMS();

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[8])));	//AT_SMS_READ
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, sms_index);
	answer = sendCommand2(buffer_GPRS, "+CMGR:", ERROR_CMS);

	if (answer == 1)
	{
		counter = 0;
		previous = millis();

		// reads up to the sender phone number
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			if (serialRead(_socket) == '"')
			{
				counter++;
			}
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((counter < 3) && ((millis() - previous) < 2000));

		// stores in 'tlfIN' the sender phone number
		#if GPRS_debug_mode>0
			PRINT_GPRS(F("Phone number "));
		#endif
		counter = 0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			tlfIN[counter] = serialRead(_socket);
			#if GPRS_debug_mode>0
				USB.print(char(tlfIN[counter]));
			#endif
			counter++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((tlfIN[counter-1] != '"') && ((millis() - previous) < 2000));
		tlfIN[counter-1] = '\0';

		// reads up to the message text
		counter = 0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			buffer_GPRS[0] = serialRead(_socket);
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((buffer_GPRS[0] != '\n') && ((millis() - previous) < 2000));

		// stores the message text in 'buffer_GPRS'
		#if GPRS_debug_mode>0
			USB.println(F(""));
			PRINT_GPRS(F("SMS body "));
		#endif
		counter = 0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			buffer_GPRS[counter] = serialRead(_socket);
			#if GPRS_debug_mode>0
				USB.print(char(buffer_GPRS[counter]));
			#endif
			counter++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((strstr(buffer_GPRS, "OK\r\n") == NULL) && ((millis() - previous) < 2000));
		buffer_GPRS[counter-6] = '\0';
		#if GPRS_debug_mode>0
			USB.println(F(""));
		#endif

		return 1;

	}
	else if (answer == 2)
	{
		return -2;
	}

	return 0;
}

/* getTotalSMS() - Gets the number of total SMS stored in the SIM
 *
 * This function gets the number of total SMS stored in the SIM
 *
 * Returns the number of SMS or '-2' if error
*/
int8_t WaspGPRS_Pro_core::getTotalSMS(){

	int8_t answer, count;
	unsigned long previous;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[9])));	//AT_SMS_MEMORY
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"SM\",\"SM\",\"SM\"", str_aux1);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[10])));	//AT_SMS_MEMORY_R
	answer=sendCommand1(buffer_GPRS, str_aux1);


	if (answer == 1)
	{
		count=serialRead(_socket);
		answer=0;

		previous = millis();
		// Gets the number of SMS in the memory
		do{
			answer*=10;
			answer+=count-0x30;
			count=serialRead(_socket);
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((count != ',') && ((millis()-previous) < 1000));

		return answer;
	}
	return -2;
}

/* deleteSMS(uint8_t ) - deletes a sms in the memory
 *
 * This function deletes a sms in the memory selected by sms_index
 *
 * Returns '1' on success '0' if error and '-2' if error with CMS error code available
*/
uint8_t WaspGPRS_Pro_core::deleteSMS(uint8_t sms_index){

	int8_t answer;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[11])));	//AT_SMS_DELETE
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, sms_index);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CMS);

	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}

	return 1;
}
#endif


/* manageIncomingData() - manage incoming data from serial port, executing proper functions to store received data
 *
 * This function manages incoming data from serial port, executing proper functions to store received data
 *
 * Returns '1' for call, '2' for SMS, '3' for IP data and '0' for error or not data
*/
int8_t	WaspGPRS_Pro_core::manageIncomingData(){

	int16_t a;							 //counter and auxiliar variable
	unsigned long previous = 0;
	char str_aux4[6], str_aux5[10];

	memset(buffer_GPRS, '\0', sizeof(buffer_GPRS) );
	a=0;


	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[41])));	//INCOMING_CALL
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[42])));	//INCOMING_SMS

	#if IP_FUSE==1
		strcpy_P(str_aux3, (char*)pgm_read_word(&(table_IP[50])));		//GET_MANUAL
		strcpy_P(str_aux4, (char*)pgm_read_word(&(table_IP[51])));		//IP_DATA
		strcpy_P(str_aux5, (char*)pgm_read_word(&(table_IP[53])));		//IP_MULTI_DATA
	#endif
	// Wait for data
	//serialFlush(_socket);
	previous = millis();
  #if GPRS_debug_mode>0
    PRINT_GPRS(F(""));
  #endif
	while (((millis()-previous) < 20000) && (a < BUFFER_SIZE) && (a >= 0))
	{
		if (serialAvailable(_socket) != 0)
		{
			buffer_GPRS[a] = serialRead(_socket);	// Reads a byte
			a++;
			#if GPRS_debug_mode>0
				USB.print(char(buffer_GPRS[a-1]));
			#endif

			// Check the received data

			if ((strstr(buffer_GPRS, str_aux1)) != NULL)
			{
				#if GPRS_debug_mode>0
					PRINTLN_GPRS(F("Incoming call"));
				#endif
				#if GSM_FUSE==1
				if (readCall() == 1)
				{
					a = -1;
				}
				else
				{
					a = 0;
				}
				#endif
				#if GSM_FUSE==0
					a = 0;
				#endif
			}
			else if ((strstr(buffer_GPRS, str_aux2)) != NULL)
			{
				#if GPRS_debug_mode>0
					PRINTLN_GPRS(F("Incoming SMS"));
				#endif

				#if GSM_FUSE==1
				a = incomingSMS();
				if(a != 0)
				{
					readSMS(a);
					a = -2;
				}
				else
				{
					a = 0;
				}
				#endif
				#if GSM_FUSE==0
					a = 0;
				#endif
			}
			#if IP_FUSE==1
			else if (((strstr(buffer_GPRS, str_aux3)) != NULL) || ((strstr(buffer_GPRS, str_aux4)) != NULL) || ((strstr(buffer_GPRS, str_aux5)) != NULL) || (IP_app_mode == 1))
			{
				#if GPRS_debug_mode>0
					PRINTLN_GPRS(F("Incoming IP data"));
				#endif

				buffer_GPRS[a] = '\0';


				a = readIPData();
				if(a != 0)
				{
					a = -3;
				}
				else
				{
					a = 0;
				}
			}
			#endif
		}
		else
		{
			delay(100);
		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}

	if (a == 0)
	{
		return 0;
	}

	return -a;

}

/*switchtoDataMode() - switchs from command mode to data mode
 *
 * This function switchs from command mode to data modes
 *
 * Returns '1' on success, '0' if error and '-2' if connection is not successfully resumed
*/
int8_t WaspGPRS_Pro_core::switchtoDataMode(){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//AT_DATA_MODE
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[12])));	//AT_DATA_MODE_R
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[13])));	//AT_DATA_MODE_FAIL
	answer=sendCommand2(AT_DATA_MODE, AT_DATA_MODE_R, AT_DATA_MODE_FAIL);

	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}

	return 1;
}

/*switchtoCommandMode() - switchs from data mode to command mode
 *
 * This function switchs from data mode to command mode
 *
 * Returns '1' on success and '0' if error
*/
int8_t WaspGPRS_Pro_core::switchtoCommandMode(){

	uint8_t answer=0;

	delay(1000);	//waits one second after the last data send
	printByte('+', _socket);
	printByte('+', _socket);
	printByte('+', _socket);
	answer=waitForData(OK_RESPONSE, 5000, millis(), 0);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* sendCommand(ATcommand) - sends any command to GPRS module
 *
 * This function sends any command to GPRS module
 *
 * It stores in 'buffer_GPRS' variable the answer returned by the GPRS module
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::sendCommand(const char* ATcommand){

	uint8_t timeout=0;
	uint8_t i=0;

	memset(buffer_GPRS, 0x00, sizeof(buffer_GPRS) );
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "AT%s%c%c", ATcommand, '\r', '\n');

	serialFlush(_socket);

	printString(buffer_GPRS, _socket);
	delay(DELAY_ON_SEND);

	while ( timeout < 5 )
	{
		while (!serialAvailable(_socket) && (timeout < 5))
		{
			timeout++;
			delay(1000);
		}
		while (serialAvailable(_socket) && (timeout < 5))
		{
			if (i < BUFFER_SIZE)
			{
				buffer_GPRS[i] = serialRead(_socket);
				i++;
			}
			else
			{
				serialRead(_socket);
			}
			delay(20);
			timeout=0;
			if (i >= 199)
			{
				timeout=5;
			}
		}
	}

	if (i < BUFFER_SIZE)
	{
		buffer_GPRS[i] = '\0';
	}
	else
	{
		buffer_GPRS[i - 1] = '\0';
	}

	if ( i < 5 )
	{
		return 0;
	}
	return 1;
}

//HTTP and FTP functions
/* configureGPRS_HTTP_FTP(uint8_t) - configures GPRS connection with login,
 * password and other parameters
 *
 * This function creates a GPRS connection with the carrier server to get
 * access to the HTTP and FTP applications
 *
 * It can configure 3 different profiles (1-3)
 *
 * Returns
 * '1' on success
 * '0' if error
 * '-2' if error setting the type of internet connection,
 * '-3' if error setting the apn
 * '-4' if error setting the user name
 * '-5' if error setting the password
 * '-6' if error saving the configuration
*/
int8_t WaspGPRS_Pro_core::configureGPRS_HTTP_FTP(uint8_t n_conf){

	int count=5;

	// SET TYPE OF INTERNET CONNECTION: AT+SAPBR=3,<n_conf>,"CONTYPE","GPRS"
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[30])));	//AT_GPRS_CFG
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[37])));	//CON_TYPE
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[31])));	//GPRS
    snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s3,%u,\"%s\",\"%s\"", str_aux1, n_conf, str_aux2, str_aux3); // Configures the connection
    count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));

    if (count == 0)
	{
        return -2;
    }

    // SET APN: AT+SAPBR=3,<n_conf>,"APN",<AT_GPRS_APN>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[30])));	//AT_GPRS_CFG
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[38])));	//APN
    snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s3,%u,\"%s\",\"%s\"", str_aux1, n_conf, str_aux2, _apn);
    count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));
    if (count == 0)
	{
        return -3;
    }

    // SET USER: AT+SAPBR=3,<n_conf>,"USER",<AT_GPRS_LOGIN>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[30])));	//AT_GPRS_CFG
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[39])));	//USER
    snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s3,%u,\"%s\",\"%s\"", str_aux1, n_conf, str_aux2, _apn_login);
    count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));
    if (count == 0)
	{
        return -4;
    }

    // SET PASSWORD: AT+SAPBR=3,<n_conf>,"PWD",<AT_GPRS_PASSW>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[30])));	//AT_GPRS_CFG
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[40])));	//PWD
    snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s3,%u,\"%s\",\"%s\"", str_aux1, n_conf, str_aux2, _apn_password);
    count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));
    if (count == 0)
	{
        return -5;
    }

    // SAVE CONFIGURATION: AT+SAPBR=5,<n_conf>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[30])));	//AT_GPRS_CFG
    snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s5,%u", str_aux1, n_conf); // Saves configuration
	count=5;
    do{
        count--;
    }while ((sendCommand1(buffer_GPRS, OK_RESPONSE) != 1) && (count != 0));
    if (count == 0)
	{
        return -6;
    }

    return 1;
}

#if FTP_FUSE
/* uploadFile(const char*, const char*, const char*, const char*, const char* ,
 * const char*, uint8_t) - uploads a file to a FTP server
 *
 * This function uploads a file to a FTP server
 *
 * Returns
 * '1' on success
 * '0' if error opening connection with the GPRS provider
 * '-1' if no GPRS connection
 * '-2' if error opening the connection,
 * '-3' if error getting the IP address
 * '-4' if error setting the FTP/HTTP ID (no answer from module)
 * '-5' if error setting the FTP mode (no answer from module)
 * '-6' if error setting the FTP type (no answer from module)
 * '-7' if error setting the FTP server(no answer from module)
 * '-8' if error setting the FTP port (no answer from module)
 * '-9' if error setting the user name,
 * '-10' if error setting the password
 * '-11' if error starting the SD
 * '-12' if error taking the file size in the SD,
 * '-13' if error setting the file name in the FTP server (no answer from module)
 * '-14' if error setting the path of the file in the FTP server (no answer from module)
 * '-15' if error opening the FTP session (no answer from module)
 * '-16' if error when request to send data
 * '-17' error sending data to the FTP,
 * '-18' if error waiting for send more data
 * '-19' if error when setting Upload File (with CME error code available)
 * '-20' if error closing the FTP session (no answer from module)
 * '-21' setting the file name in the FTP to get the file size
 * '-22' setting the path in the FTP to get the file size
 * '-23' if error getting the file size (no answer from module)
 * '-24' if error opening SD file
 * '-25' if error when setting pointer to the beginning of the file
 * '-40' if error from FTP when the module sends data with error code available,
 * '-41' if error setting the FTP/HTTP ID with CME error code available
 * '-42' if error setting the FTP mode (with CME error code available)
 * '-43' if error setting the FTP type (with CME error code available)
 * '-44' if error setting the FTP server (with CME error code available)
 * '-45' if error setting the FTP port (with CME error code available)
 * '-46' if error setting the user name (with CME error code available)
 * '-47' if error setting the password (with CME error code available)
 * '-48' if error setting the file name in the FTP server (with CME error code available)
 * '-49' if error setting the path of the file in the FTP server (with CME error code available)
 * '-50' if error opening the FTP session (with CME error code available)
 * '-51' if error closing the FTP session (with CME error code available)
 * '-53' setting the file name in the FTP to get the file size (with CME error code available)
 * '-54' setting the path in the FTP to get the file size (with CME error code available)
 * '-55' if error getting the file size (with CME error code available)
 * '-56' if FTP is busy error getting the size of the file from the FTP
 * '-57' if FTP is busy sending data
 * '-58' if timeout
*/
int8_t WaspGPRS_Pro_core::uploadFile(	const char* file,
									const char* path,
									const char* user,
									const char* passw,
									const char* ftp_server,
									const char* ftp_port,
									uint8_t n_conf)
{

	unsigned long previous = 0;
	int8_t answer = 0;
	uint8_t count = 10;
	uint8_t ftp_retries;
	long sd_size = 0;
	long ftp_size = 0;
	int CME_aux = 0;

	//closeGPRS_HTTP_FTP_connection(n_conf);

	// Opens the GPRS connection and gets IP address
	answer = openGPRS_HTTP_FTP_connection(n_conf);
	if (answer != 1)
	{
		return answer;
	}

	// YURI DELAY
	delay(100);

	// SET FTP BEARER PROFILE IDENTIFIER: AT+FTPCID=<n_conf>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[0])));	//"+FTPCID="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, n_conf);
	count=10;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -4;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -41;
	}

	// YURI DELAY
	delay(100);

	// SET ACTIVE OR PASSIVE FTP MODE: AT+FTPMODE=1
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[2])));	//"+FTPMODE"
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=1", str_aux1);
	count=10;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -5;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -42;
	}

	// YURI DELAY
	delay(100);

	// SET THE TYPE OF DATA TO BE TRANSFERRED: AT+FTPTYPE="I" (Binary sessions)
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[3])));	//"+FTPTYPE="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"I\"", str_aux1);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -6;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -43;
	}

	// YURI DELAY
	delay(100);

	// SET FTP SERVER ADDRESS: AT+FTPSERV="<ftp_server>"
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[4])));	//"+FTPSERV="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, ftp_server);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -7;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -44;
	}
	// YURI DELAY
	delay(100);

	// SET FTP CONTROL PORT: AT+FTPPORT=<ftp_port>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[1])));	//"+FTPPORT="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%s", str_aux1, ftp_port);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -8;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -45;
	}
	// YURI DELAY
	delay(100);

	// SET FTP USER NAME: AT+FTPUN="<user>"
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[5])));	//"+FTPUN="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, user);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -9;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -46;
	}
	// YURI DELAY
	delay(100);

	// SET FTP PASSWORD: AT+FTPPW="<passw>"
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[6])));	//"+FTPPW="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, passw);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -10;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -47;
	}
	// YURI DELAY
	delay(100);


	// SD SET UP: First goes to the main directory
	SD.ON();
	if (SD.goRoot() != 1)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		SD.OFF();
		return -11;
	}

	// get File Size
	count = 3;
	do{
		sd_size = SD.getFileSize(file);
		count--;
	}while ((sd_size == -1) && (count != 0));

	// check counter
	if (count == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		SD.OFF();
		return -12;
	}


	// SEND DATA for several retries
	previous = millis();
	ftp_retries = 4;
	do{
		answer = sendDataFTP(file, path);
		CME_aux = CME_CMS_code;
		ftp_retries--;
		ftp_size = getfilesizeFTP(path);

		#if GPRS_debug_mode>0
			PRINT_GPRS(F("Return from sendDataFTP: "));
			USB.println(answer, DEC);
			PRINT_GPRS(F("ftp_size: "));
			USB.println(ftp_size, DEC);
			PRINT_GPRS(F("file size SD: "));
			USB.println(sd_size, DEC);
			PRINT_GPRS(F("ftp_retries: "));
			USB.println(ftp_retries, DEC);
			PRINT_GPRS(F("CME_CMS_code: "));
			USB.println(CME_CMS_code, DEC);
		#endif

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();

	}while( (ftp_size != sd_size) &&
			(ftp_retries > 0) &&
			((millis() - previous) < AT_FTP_MAX_TIME) );


	SD.OFF();

	if ( ftp_size != sd_size )
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		if (answer != 1)
		{
			CME_CMS_code = CME_aux;
			return answer;
		}
		else
		{
			return ftp_size;
		}
	}

	closeGPRS_HTTP_FTP_connection(n_conf);

	return 1;
}

/* downloadFile(const char*, const char*, const char*, const char*, const char* ,
 * const char*, uint8_t) - downloads a file from a FTP server
 *
 * This function downloads a file from a FTP server
 *
 * Returns '1' on success and '0' if error opening connection with the GPRS provider
 * '-1' error downloading the file
 * '-2' if error opening the connection,
 * '-3' if error getting the IP address
 * '-4' if error setting the FTP/HTTP ID
 * '-5' if error setting the FTP mode
 * '-6' if error setting the FTP type,
 * '-7' if error setting the FTP server
 * '-8' if error setting the FTP port
 * '-9' if error setting the user name,
 * '-10' if error setting the password
 * '-12' if error setting the file name in the FTP server,
 * '-13' if error setting the path of the file in the FTP server
 * '-14' if error opening the FTP session,
 * '-15' if error starting the SD
 * '-16' if error creating the file
 * '-17' error requesting data to the FTP,
 * '-18' if error saving data into the SD
 * '-19' if error requesting more data to the FTP
 * '-21' setting the file name in the FTP to get the file size
 * '-22' setting the path in the FTP to get the file size
 * '-23' if error getting the file size
 * '-41' if error setting the FTP/HTTP ID with CME error code available
 * '-42' if error setting the FTP mode with CME error code available,
 * '-43' if error setting the FTP type with CME error code available
 * '-44' if error setting the FTP server with CME error code available,
 * '-45' if error setting the FTP port with CME error code available
 * '-46' if error setting the user name with CME error code available,
 * '-47' if error setting the password with CME error code available
 * '-48' if error setting the file name in the FTP server with CME error code available,
 * '-49' if error setting the path of the file in the FTP server with CME error code available
 * '-50' if error opening the FTP session with CME error code available,
 * '-51' if error requesting data to the FTP with CME error code available
 * '-52' if error requesting more data to the FTP with CME error code available,
 * '-53' setting the file name in the FTP to get the file size with CME error code available,
 * '-54' setting the path in the FTP to get the file size with CME error code available
 * '-55' if error getting the file size with CME error code available
 * '-56' if FTP is busy error getting the size of the file from the FTP
 * '-57' if FTP is busy sending data
 * '-58' if timeout
*/
int8_t WaspGPRS_Pro_core::downloadFile(	const char* file,
									const char* path,
									const char* user,
									const char* passw,
									const char* ftp_server,
									const char* ftp_port,
									uint8_t n_conf)
{

	unsigned long previous=0;
	int8_t answer=0;
	uint8_t count=10;
	long ftp_size=0;
	uint8_t ftp_retries;
	long sd_size = 0;

	//~ closeGPRS_HTTP_FTP_connection(n_conf);


	// Opens the GPRS connection and gets IP address
	answer = openGPRS_HTTP_FTP_connection(n_conf);
	if (answer != 1)
	{
		return answer;
	}

	delay(100);

	// SET FTP BEARER PROFILE IDENTIFIER: AT+FTPCID=<n_conf>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[0])));	//"+FTPCID="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, n_conf);
	count=10;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -4;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -41;
	}

	delay(100);

	// SET ACTIVE OR PASSIVE FTP MODE: AT+FTPMODE=1
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[2])));	//"+FTPMODE"
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=1", str_aux1);
	count=10;
	do{
		answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -5;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -42;
	}

	delay(100);

	// SET THE TYPE OF DATA TO BE TRANSFERRED: AT+FTPTYPE="I" (Binary sessions)
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[3])));	//"+FTPTYPE="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"I\"", str_aux1);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -6;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -43;
	}

	delay(100);

	// SET FTP SERVER ADDRESS: AT+FTPSERV="<ftp_server>"
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[4])));	//"+FTPSERV="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, ftp_server);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -7;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -44;
	}

	delay(100);

	// SET FTP CONTROL PORT: AT+FTPPORT=<ftp_port>
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[1])));	//"+FTPPORT="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%s", str_aux1, ftp_port);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -8;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -45;
	}

	delay(100);

	// SET FTP USER NAME: AT+FTPUN="<user>"
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[5])));	//"+FTPUN="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, user);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -9;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -46;
	}

	delay(100);

	// SET FTP PASSWORD: AT+FTPPW="<passw>"
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[6])));	//"+FTPPW="
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, passw);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
	if (answer == 0)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -10;
	}
	else if (answer == -2)
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		return -47;
	}

	delay(100);

	SD.ON();
	ftp_retries = 3;
	previous = millis();
	do{
		answer = readDataFTP(file, path);
		ftp_size = getfilesizeFTP(file);
		sd_size = SD.getFileSize(path);
		#if GPRS_debug_mode>0
			PRINT_GPRS(F("Return from readDataFTP: "));
			USB.println(answer, DEC);
			PRINT_GPRS(F("ftp_size: "));
			USB.println(ftp_size, DEC);
			PRINT_GPRS(F("ftp_retries: "));
			USB.println(ftp_retries, DEC);
			PRINT_GPRS(F("file size SD: "));
			USB.println(sd_size, DEC);
		#endif
		ftp_retries--;
	}while(	(ftp_size != sd_size)
			&& (ftp_retries > 0)
			&& ((millis() - previous) < AT_FTP_MAX_TIME));

	SD.OFF();

	if( ftp_size != sd_size )
	{
		closeGPRS_HTTP_FTP_connection(n_conf);
		if (answer == 1)
		{
			return -1;
		}
		return answer;
	}

	closeGPRS_HTTP_FTP_connection(n_conf);

	return 1;
}
#endif

#if HTTP_FUSE

/* readURL(const char*, uint8_t) - access to the specified URL and stores the
 * info read in 'buffer_GPRS' variable.
 *
 * USE IT ONLY WITH GET REQUESTS
 *
 * This function access to the specified URL and stores the info read in
 * 'buffer_GPRS' variable
 *
 * Returns
 * '0' if error
 * '1' on success
 * '2' if buffer_GPRS is full. The answer from the server is limited by the
 * 		length of buffer_GPRS. To increase the length of the answer, increase the
 * 		BUFFER_SIZE constant.
 * '-1' if no GPRS connection
 * '-2' if error opening the connection,
 * '-3' if error getting the IP address,
 * '-4' if error initializing the HTTP service
 * '-5' if error setting CID the HTTP service
 * '-6' if error setting the url the HTTP service
 * '-7' if error starting HTTP session
 * '-8' if error getting data from url
 * '-9' if error closing the HTTP service
 * '-10' if error initializing the HTTP service with CME error code available
 * '-11' if error setting CID the HTTP service with CME error code available
 * '-12' if error setting the url the HTTP service with CME error code available
 * '-13' if error starting HTTP sesion with CME error code available
 * '-14' if error getting data from url with CME error code available
 * '-15' if error closing the HTTP service with CME error code available
 * '-16' if error configuring the HTTP content parameter
 * '-17' if error configuring the HTTP content parameter with CME error code available
 * '-18' if error sending the POST data
 * '-19' if error sending the POST data with CME error code available
 * '-20' if error getting data from url with CME error code available
 */
int WaspGPRS_Pro_core::readURL(	const char* url, uint8_t n_conf)
{
		return (readURL(url, (uint8_t*)NULL, 0, n_conf, GET, FRAME_DISABLED));
}

/* readURL(const char*, uint8_t, int, uint8_t) - access to the specified URL
 * and stores the info read in 'buffer_GPRS' variable
 *
 * USE IT ONLY TO SEND FRAMES WITH GET REQUESTS
 *
 * This function access to the specified URL and stores the info read in
 * 'buffer_GPRS' variable
 *
 * Returns
 * '0' if error
 * '1' on success
 * '2' if buffer_GPRS is full. The answer from the server is limited by the
 * 		length of buffer_GPRS. To increase the length of the answer, increase the
 * 		BUFFER_SIZE constant.
 * '-1' if no GPRS connection
 * '-2' if error opening the connection,
 * '-3' if error getting the IP address,
 * '-4' if error initializing the HTTP service
 * '-5' if error setting CID the HTTP service
 * '-6' if error setting the url the HTTP service
 * '-7' if error starting HTTP session
 * '-8' if error getting data from url
 * '-9' if error closing the HTTP service
 * '-10' if error initializing the HTTP service with CME error code available
 * '-11' if error setting CID the HTTP service with CME error code available
 * '-12' if error setting the url the HTTP service with CME error code available
 * '-13' if error starting HTTP sesion with CME error code available
 * '-14' if error getting data from url with CME error code available
 * '-15' if error closing the HTTP service with CME error code available
 * '-16' if error configuring the HTTP content parameter
 * '-17' if error configuring the HTTP content parameter with CME error code available
 * '-18' if error sending the POST data
 * '-19' if error sending the POST data with CME error code available
 * '-20' if error getting data from url with CME error code available
 */
int WaspGPRS_Pro_core::readURL(	const char* url,
							uint8_t* data,
							uint16_t length,
							uint8_t n_conf)
{
	return readURL(url, data, length, n_conf, GET, FRAME_ENABLED);
}



/* readURL(const char*, uint8_t, int, uint8_t) - access to the specified URL
 * and stores the info read in 'buffer_GPRS' variable
 *
 * USE IT ONLY WITH POST REQUESTS
 *
 * This function access to the specified URL and stores the info read in
 * 'buffer_GPRS' variable
 *
 * Returns
 * '0' if error
 * '1' on success
 * '2' if buffer_GPRS is full. The answer from the server is limited by the
 * 		length of buffer_GPRS. To increase the length of the answer, increase the
 * 		BUFFER_SIZE constant.
 * '-1' if no GPRS connection
 * '-2' if error opening the connection,
 * '-3' if error getting the IP address,
 * '-4' if error initializing the HTTP service
 * '-5' if error setting CID the HTTP service
 * '-6' if error setting the url the HTTP service
 * '-7' if error starting HTTP session
 * '-8' if error getting data from url
 * '-9' if error closing the HTTP service
 * '-10' if error initializing the HTTP service with CME error code available
 * '-11' if error setting CID the HTTP service with CME error code available
 * '-12' if error setting the url the HTTP service with CME error code available
 * '-13' if error starting HTTP sesion with CME error code available
 * '-14' if error getting data from url with CME error code available
 * '-15' if error closing the HTTP service with CME error code available
 * '-16' if error configuring the HTTP content parameter
 * '-17' if error configuring the HTTP content parameter with CME error code available
 * '-18' if error sending the POST data
 * '-19' if error sending the POST data with CME error code available
 * '-20' if error getting data from url with CME error code available
 */
int WaspGPRS_Pro_core::readURL(	const char* url,
							const char* data,
							uint8_t n_conf)
{

	return readURL(url, (uint8_t*)data, strlen(data), n_conf, POST, FRAME_DISABLED );
}

/* readURL(const char*, uint8_t, int, uint8_t) - access to the specified URL
 * and stores the info read in 'buffer_GPRS' variable
 *
 * GET/POST WITH FRAME
 *
 * This function access to the specified URL and stores the info read in
 * 'buffer_GPRS' variable
 *
 * Returns
 * '0' if error
 * '1' on success
 * '2' if buffer_GPRS is full. The answer from the server is limited by the
 * 		length of buffer_GPRS. To increase the length of the answer, increase the
 * 		BUFFER_SIZE constant.
 * '-1' if no GPRS connection
 * '-2' if error opening the connection,
 * '-3' if error getting the IP address,
 * '-4' if error initializing the HTTP service
 * '-5' if error setting CID the HTTP service
 * '-6' if error setting the url the HTTP service
 * '-7' if error starting HTTP session
 * '-8' if error getting data from url
 * '-9' if error closing the HTTP service
 * '-10' if error initializing the HTTP service with CME error code available
 * '-11' if error setting CID the HTTP service with CME error code available
 * '-12' if error setting the url the HTTP service with CME error code available
 * '-13' if error starting HTTP sesion with CME error code available
 * '-14' if error getting data from url with CME error code available
 * '-15' if error closing the HTTP service with CME error code available
 * '-16' if error configuring the HTTP content parameter
 * '-17' if error configuring the HTTP content parameter with CME error code available
 * '-18' if error sending the POST data
 * '-19' if error sending the POST data with CME error code available
 * '-20' if error getting data from url with CME error code available
 */
int WaspGPRS_Pro_core::readURL(	const char* url,
							uint8_t* data,
							uint16_t length,
							uint8_t n_conf,
							uint8_t mode)
{
	return readURL(url, data, length, n_conf, mode, FRAME_ENABLED );

}

/* readURL(const char*, uint8_t, int, uint8_t) - access to the specified URL
 * and stores the info read in 'buffer_GPRS' variable
 *
 * Base function
 *
 * This function access to the specified URL and stores the info read in
 * 'buffer_GPRS' variable
 *
 * Returns
 * '0' if error
 * '1' on success
 * '2' if buffer_GPRS is full. The answer from the server is limited by the
 * 		length of buffer_GPRS. To increase the length of the answer, increase the
 * 		BUFFER_SIZE constant.
 * '-1' if no GPRS connection
 * '-2' if error opening the connection,
 * '-3' if error getting the IP address,
 * '-4' if error initializing the HTTP service
 * '-5' if error setting CID the HTTP service
 * '-6' if error setting the url the HTTP service
 * '-7' if error starting HTTP session
 * '-8' if error getting data from url
 * '-9' if error closing the HTTP service
 * '-10' if error initializing the HTTP service with CME error code available
 * '-11' if error setting CID the HTTP service with CME error code available
 * '-12' if error setting the url the HTTP service with CME error code available
 * '-13' if error starting HTTP session with CME error code available
 * '-14' if error getting data from url with CME error code available
 * '-15' if error closing the HTTP service with CME error code available
 * '-16' if error configuring the HTTP content parameter
 * '-17' if error configuring the HTTP content parameter with CME error code available
 * '-18' if error sending the POST data
 * '-19' if error sending the POST data with CME error code available
 * '-20' if error getting data from url with CME error code available
 */
int WaspGPRS_Pro_core::readURL(	const char* url,
							uint8_t* data,
							uint16_t length,
							uint8_t n_conf,
							uint8_t mode,
							uint8_t frame_flag )
{
	// define variables
	int answer;
	uint16_t HTTP_total_data;
	uint16_t http_retries;
	int HTTP_code;

	// Opens the GPRS connection and gets IP address
	if( isConnected(n_conf) == 0 )
	{
		answer = openGPRS_HTTP_FTP_connection(n_conf);
		if (answer != 1)
		{
			return answer;
		}
	}

	http_retries = 3;

	do
	{
		if (mode == GET)
		{
			// Inits the HTTP service and configures url and CID
			answer = initHTTP( url, data, length, n_conf, frame_flag);
			if (answer != 1)
			{
				return answer;
			}
		}
		else
		{
			// Inits the HTTP service and configures url and CID
			// enter 'FRAME_DISABLED' not to write any data, but teh URL
			answer = initHTTP( url, data, 0, n_conf, FRAME_DISABLED);
			if (answer != 1)
			{
				return answer;
			}

			// Sets the HTTP request
			answer = setPOSTdata(data, length, frame_flag);
			if (answer != 1)
			{
				return answer;
			}

		}

		// Sends the request to the url and waits for url data
		answer = sendHTTP( n_conf, mode);

		HTTP_code = CME_CMS_code;

		if(answer == -20 )
		{
			// check network failure and try again when "601" and "603"
			http_retries--;

			// if code 604 return with error
			if( CME_CMS_code == 604 )
			{
				http_retries = 0;
			}
		}
		else if (answer < 0)
		{
			return answer;
		}

		delay(500);

	}while( (http_retries > 0) && (answer < 0) );

	if (http_retries == 0)
	{
		closeHTTP();
		closeGPRS_HTTP_FTP_connection(n_conf);
		CME_CMS_code = HTTP_code;
		return -20;
	}

	// Stores in HTTP_total_data the length of the data received in GPRS_Pro module
	HTTP_total_data = answer;

	// Wait for data
	delay(500);

	// Reads received data from the GPRS_Pro module
	answer = readHTTP(HTTP_total_data, n_conf);

	return answer;
}


/* isConnected
 *
 * This function checks if the GPRS module is connected to the network and
 * there is an IP address related to this module
 *
 * Returns
 * 	'0' if error
 * 	'1' on success
*/
uint8_t WaspGPRS_Pro_core::isConnected( uint8_t n_conf )
{
	uint8_t connection;
	char str1[20];
	char str2[20];
	char str3[70];

	// AT+SAPBR=2,<n_conf>
	strcpy_P(str3, (char*)pgm_read_word(&(table_MISC[30])));	//AT_GPRS_CFG
	snprintf(str1, sizeof(str1), "%s2,%u", str3, n_conf);
	strcpy_P(str3, (char*)pgm_read_word(&(table_MISC[44])));	//"+SAPBR: "
	snprintf(str2, sizeof(str2), "%s%u,1,\"", str3, n_conf);

	connection = sendCommand1(str1,str2, 3000, SEND_ONCE);

	return connection;
}


#endif

/* getcurrentOperator() - Gets the currently selected operator from network
 *
 * This function gets the currently selected operator from network and stores it in 'operator_name'
 *
 * Returns '1' on success
 * '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::getcurrentOperator(){

	uint8_t answer=0;
	int i;
	unsigned long previous;

	serialFlush(_socket);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[21])));	//AT_GET_OPERATOR
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[22])));	//AT_GET_OPERATOR_R
	answer=sendCommand2(str_aux1, str_aux2, ERROR_CME);
	if (answer == 1)
	{
		previous=millis();
		while ((serialRead(_socket) != '"') && (millis()-previous < 10000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		i=0;
		do{
			while ((serialAvailable(_socket) == 0) && (millis()-previous < 10000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			buffer_GPRS[i]=serialRead(_socket);
			i++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((buffer_GPRS[i-1] != '"') && (millis()-previous < 10000));
		buffer_GPRS[i-1]='\0';

		return 1;
	}
	else if (answer == 2)
	{
		return -2;
	}

	return 0;
}

/* getAvailableOperators() - Gets the currently available operators from network
 *
 * This function gets the currently available operators from network and stores it in 'operators_list'
 *
 * Returns '1' on success
 * '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::getAvailableOperators(){

	uint8_t answer=0;
	int i,j,aux;
	unsigned long previous;

	serialFlush(_socket);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[24])));	//AT_OPERATOR_LIST
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[25])));	//AT_OPERATOR_LIST_R
	answer=sendCommand2(str_aux1, str_aux2, ERROR_CME);
	if (answer == 2)
	{
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}


	previous=millis();
	j=0;
	do{
		while ((serialRead(_socket) !=  ',') && ((millis()-previous)< 10000)) // Gets format used
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		i=0;
		aux=serialRead(_socket);
		do{
			while ((serialAvailable(_socket) == 0) && (millis()-previous < 10000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			operators_list[j].format=aux-0x30;
			aux=serialRead(_socket);
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((aux != ',') && (millis()-previous < 10000));
		while ((serialRead(_socket)!='"') && (millis()-previous < 10000)) // Gets operator name
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		i=0;
		do{
			while ((serialAvailable(_socket) == 0) && (millis()-previous < 10000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			operators_list[j].operator_name[i]=serialRead(_socket);
			i++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((operators_list[j].operator_name[i-1] != '"') && (millis()-previous < 10000));
		operators_list[j].operator_name[i-1]='\0';
		j++;
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((waitForData("OK", str_aux2, 20000, millis(), 0, 2) == 2)  && (millis()-previous < 10000) && (j < 5));

	return 1;
}

/* setPreferredOperator(int, uint8_t, const char*) - Sets the preferred operator in the operators list into GPRS module
 *
 * This function sets the preferred operator in the operators list into GPRS module
 *
 * Returns '1' on success
 * '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::setPreferredOperator(int index, uint8_t format, const char* preferred_operator){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[23])));	//AT_SET_PREF_OPERATOR
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u,%u,\"%s\"", str_aux1, index, format, preferred_operator);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);

	if (answer == 2)
	{
		return -2;
	}
	return answer;
}

/* getCellInfo() - gets the information from the cell where the module is connected
 *
 * This function gets the information from the cell where the module is connected
 *
 * It stores in 'RSSI' and 'cellID' variables the information from the cell
 *
 * Returns '1' on success
 * '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::getCellInfo(){

	unsigned long previous;
	uint8_t counter=0;
	int answer=0;

	// SWITCH ON ENGINEERING MODE: AT+CENG=1
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[19])));	//AT_GPRS_CELLID
	snprintf(str_aux2, sizeof(str_aux2), "%s=1", str_aux1);
	answer=sendCommand2(str_aux2, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return 0;
	}

	// QUERY CURRENT ENGINEERING MODE: AT+CENG?

	//request data
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[19])));	//AT_GPRS_CELLID
	snprintf(str_aux2, sizeof(str_aux2), "%s?", str_aux1);
	snprintf(str_aux3, sizeof(str_aux3), "%s:", str_aux1);
	answer=sendCommand2(str_aux2, str_aux3, ERROR);

	if (answer == 1)
	{
		answer = waitForData(str_aux3, 10000, millis(), 0);
		if (answer == 1)
		{
			//Reads the first line
			memset(buffer_GPRS, '\0', sizeof(buffer_GPRS) );
			memset(cellID, '\0', sizeof(cellID));

			counter = 0;
			previous=millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000));

				buffer_GPRS[counter] = serialRead(_socket);
				counter++;

			}while ((buffer_GPRS[counter - 1] != '\r')
						&& (counter < BUFFER_SIZE)
						&& ((millis() - previous) < 10000));

			buffer_GPRS[counter] = '\0';

			if ((millis() - previous) < 10000)
			{
				strtok(buffer_GPRS, ",");	//cell
				strtok(NULL, ",");	//arfcn
				strtok(NULL, ",");	//rxl
				strtok(NULL, ",");	//rxq
				strtok(NULL, ",");	//mcc
				strtok(NULL, ",");	//mnc
				strtok(NULL, ",");	//bsic
				strcpy(cellID, strtok(NULL, ",")); // cell ID
			}
		}
	}
	else
	{
		return 0;
	}

	// SWITCH OFF ENGINEERING MODE: AT+CENG=0
	snprintf(str_aux2, sizeof(str_aux2), "%s=0", str_aux1);
	answer=sendCommand2(str_aux2, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return 0;
	}

	// GET RSSI: AT+CSQ
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[20])));	//AT_GPRS_RSSI
	snprintf(str_aux2, sizeof(str_aux2), "%s: ", str_aux1);
	answer=sendCommand2(str_aux1, str_aux2, ERROR_CME);
	if (answer == 2)
	{
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}

	RSSI = 0; // Gets RSSI value, converts it from ASCII to -dBm

	memset(str_aux1, '\0', sizeof(str_aux1));

	counter = 0;
	previous=millis();
	do{
		while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000));

		str_aux1[counter] = serialRead(_socket);
		counter++;

	}while ((str_aux1[counter - 1] != ',')
				&& (counter < sizeof(str_aux1))
				&& ((millis() - previous) < 10000));

	str_aux1[counter-1] = '\0';

	RSSI = atoi(str_aux1);

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Raw RSSI: "));
		USB.println(RSSI, DEC);
	#endif

	switch(RSSI)
	{
		case 0:
			RSSI= -115;
			break;

		case 1:
			RSSI= -111;
			break;

		case 31:
			RSSI= -52;
			break;

		case 99:
			RSSI= 0;
			break;

		default:
			RSSI= ((RSSI - 2) * 2) - 110;
	}

	#if GPRS_debug_mode>0
		PRINT_GPRS(F("Processed RSSI: "));
		USB.println(RSSI, DEC);
	#endif

	return 1;
}

/* getWorkingBand() - Gets the currently working band
 *
 * This function gets the currently working band
 *
 * Returns '1' on success
 * '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::getWorkingBand(){

	uint8_t answer=0;
	int i;
	unsigned long previous;

	// clean buffer
	memset(buffer_GPRS, 0x00, sizeof(buffer_GPRS) );

	serialFlush(_socket);

	// GET BAND: AT+CBAND?
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[43])));	//GET_BAND
	snprintf(str_aux1, sizeof(str_aux1), "%s?", str_aux3);
	snprintf(str_aux2, sizeof(str_aux2), "%s:", str_aux3);
	answer=sendCommand2(str_aux1, str_aux2, ERROR_CME);
	if (answer == 1)
	{
		previous=millis();
		i=0;
		do{
			while ((serialAvailable(_socket) == 0) && (millis()-previous < 10000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			buffer_GPRS[i]=serialRead(_socket);
			i++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((buffer_GPRS[i-1] != ',') && (millis()-previous < 10000));
		buffer_GPRS[i-1]='\0';

		return 1;
	}
	else if (answer == 2)
	{
		return -2;
	}

	return 0;
}


#if IP_FUSE
//TCP and UDP functions
/* configureGPRS_TCP_UDP(uint8_t) - configures GPRS connection with login, password and some other parameters to use TCP or UDP connections
 *
 * This function creates a GPRS connection with the carrier server to get access to the internet
 *
 * Returns '1' on success
 * '0' if error
 * '-2' if error dettaching the GPRS connection,
 * '-3' if error attaching the GPRS connection
 * '-4' if error setting the application mode,
 * '-5' if error setting the connection mode
 * '-6' if error establishing the connection with the GPRS provider,
 * '-15' if error dettaching the GPRS connection with CME error code available,
 * '-16' if error attaching the GPRS connection with CME error code available.
*/
int8_t WaspGPRS_Pro_core::configureGPRS_TCP_UDP(uint8_t mode){
	return( configureGPRS_TCP_UDP(mode, 0));
}

/* configureGPRS_TCP_UDP(uint8_t, uint8_t) - configures GPRS connection with login, password and some other parameters to use TCP or UDP connections
 *
 * This function creates a GPRS connection with the carrier server to get access to the internet
 *
 * Returns '1' on success
 * '0' if error
 * '-2' if error dettaching the GPRS connection,
 * '-3' if error attaching the GPRS connection
 * '-4' if error setting the application mode,
 * '-5' if error setting the connection mode
 * '-6' if error establishing the connection with the GPRS provider,
 * '-7' if error
 * '-15' if error dettaching the GPRS connection with CME error code available,
 * '-16' if error attaching the GPRS connection with CME error code available
*/
int8_t WaspGPRS_Pro_core::configureGPRS_TCP_UDP(uint8_t mode, uint8_t app_mode){

	uint8_t answer=0;
	uint8_t count;
	uint8_t state;
	unsigned long previous;

	memset( IP_dir, '\0', sizeof(IP_dir));

	// First restart TCP/UDP connection
	answer = checkGPRS(90);
	if (answer != 1)
	{
		return -1;
	}

	state = checkIPstatus(); // Checks the GPRS state to send the correct shutdown order

	count = 10;

	/*if (checkGPRS_at() == 1) // Dettach GPRS
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[18])));	//AT_GPRS_ATT_OFF
		do{
			answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			count--;
		}while ((count != 0) && (answer != 1));

		if(answer == 0)
		{
			return -2;
		}
		else if(answer == 2)
		{
			return -15;
		}
	}



	// Attaching...
	count = 10;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[17])));	//AT_GPRS_ATT_ON
	do{
		delay(5000);
		answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((count != 0) && (answer != 1));
	if(answer == 0)
	{
		return -3;
	}
	else if(answer == 2)
	{
		return -16;
	}

	previous = millis();
	while ((checkGPRS_at() != 1) && ((millis() - previous) < TCP_CONNECTION_TIME_2))
	{
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}

	if ((millis() - previous) > TCP_CONNECTION_TIME_2)
	{
		return -17;
	}*/


	if (checkGPRS_at(2) == 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[17])));	//AT_GPRS_ATT_ON
		answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME, 20000, SEND_ONCE);

		if(answer == 0)
		{
			return -3;
		}
		else if(answer == 2)
		{
			return -16;
		}

	}
	answer = checkGPRS_at(60);
	if (answer != 1)
	{
		return -17;
	}


	// Set the application mode: transparent or not transparent
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[8])));	//AT_IP_APP_MODE
	if (app_mode == 0)
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s0", str_aux1);
	}
	else
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s1", str_aux1);

	}

	count=10;
	do{
		answer = sendCommand1(buffer_GPRS, OK_RESPONSE);
		count--;
	}while ((count != 0) && (answer != 1));
	if(answer == 0)
	{
		return -4;
	}

	IP_app_mode = app_mode;



	IPHeader(1);

	// Now it must be in state 1: IP INITIAL

	// Sets the connection mode: single or multiple
	switch (mode)
	{
		case 0:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[1])));	//AT_SINGLE_CONN
			break;
		case 1:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[2])));	//AT_MULTI_CONN
			break;
	}

	answer = sendCommand1(str_aux1, OK_RESPONSE);
	if(answer == 0)
	{
		return -5;
	}

	IP_mode = mode;


	count = 10;
	state = checkIPstatus();

	previous = millis();
	do{
		switch (state) // Here, 'state' contains the IP state
		{
			case 1:
				// Start Task and Set APN, USER NAME, PASSWORD: AT+CSTT=<apn>,<username>,<password>
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[5]))); //+CSTT=
				snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\",\"%s\",\"%s\"",str_aux1, _apn, _apn_login, _apn_password);
				answer = sendCommand1(buffer_GPRS, OK_RESPONSE);
				break;
			case 2:
				// Bring Up Wireless Connection with GPRS: AT+CIICR
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[6]))); //+CIICR
				answer = sendCommand1(str_aux1, OK_RESPONSE, TCP_CONNECTION_TIME_1 / 2, SEND_ONCE);
				break;
			case 3:
				delay(1000);
				count--;
				break;
			case 4: // Gets IP direction
				answer = getIP();
				break;
			default:
				delay(1000);
				count--;
				break;
		}

		if (answer != 1) //here, answer contains the response from the module
		{
			count--;
		}

		state = checkIPstatus();

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();

	}while ((count != 0) && (state != 5) && ((millis() - previous) < TCP_CONNECTION_TIME_2));

	if ((millis() - previous) > TCP_CONNECTION_TIME_2)
	{
		CME_CMS_code = answer;
		return -7;
	}

	if ((count <= 0) || (IP_dir[0] == '\0'))
	{
		return -6;
	}
	else
	{
		return 1;
	}
}

/* setLocalPort(const char*, uint16_t) - Sets the number of the internal port for TCP or UDP connections
 *
 * This function sets the number of the internal port for TCP or UDP connections
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro_core::setLocalPort(const char* mode, uint16_t port){

	uint8_t answer = 0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[25])));	//AT_IP_LOCAL_PORT
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\",%u", str_aux1, mode, port);
	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		return 0;
	}
	return 1;

}

/* saveGPRS_TCP_UDPconfiguration() - Saves the configuration into the internal NVRAM of the GPRS module
 *
 * This function saves the configuration into the internal NVRAM of the GPRS module
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro_core::saveGPRS_TCP_UDPconfiguration(){
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[26])));	//AT_IP_SAVE_CONF
	return( sendCommand1(str_aux1, OK_RESPONSE));
}

/* createSocket(uint8_t, const char*) - creates a TCP/IP connection to the specified IP and PORT
 *
 * This function creates a TCP/IP connection to the specified IP and PORT
 *
 * In multi connection mode you must specify a number of connection (0-7).
 *
 * Returns '1' on success, '0' if error setting the connection, '-2' if error setting the connection wit CME error code available
 * and '-3' if time out waiting the connection
*/
int8_t WaspGPRS_Pro_core::createSocket( uint8_t working_mode, const char* port){
	return( createSocket( working_mode, 0, 0, port));
}

/* createSocket(uint8_t, const char*,const char*) - creates a TCP/IP connection to the specified IP and PORT
 *
 * This function creates a TCP/IP connection to the specified IP and PORT
 *
 * In multi connection mode you must specify a number of connection (0-7).
 *
 * Returns '1' on success, '0' if error setting the connection, '-2' if error setting the connection wit CME error code available
 * and '-3' if time out waiting the connection
*/
int8_t WaspGPRS_Pro_core::createSocket( uint8_t working_mode, const char* ip,const char* port){
	return( createSocket( working_mode, 0, ip, port));
}

/* createSocket(uint8_t, uint8_t, const char*, const char*) - creates a TCP/IP connection to the specified IP and PORT
 *
 * This function creates a TCP/IP connection to the specified IP and PORT
 *
 * In multi connection mode you must specify a number of connection (0-7).
 *
 * Returns '1' on success, '0' if error setting the connection, '-2' if error setting the connection wit CME error code available
 * and '-3' if time out waiting the connection
*/
int8_t WaspGPRS_Pro_core::createSocket( uint8_t working_mode, uint8_t n_connection, const char* ip, const char* port){

	uint8_t answer = 0;

	switch (IP_mode)
	{
		case 0: // Single mode
			switch (working_mode)
			{
				case UDP_CLIENT:
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[33])));	//AT_IP_UDP_EXTENDED
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s0", str_aux1);
					answer |= sendCommand1(buffer_GPRS, OK_RESPONSE);
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[10])));	//AT_IP_CLIENT
					strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[12])));	//AT_UDP
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\",\"%s\",\"%s\"", str_aux1, str_aux2, ip, port);
					answer |= sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					break;
				case TCP_CLIENT:
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[10])));	//AT_IP_CLIENT
					strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[11])));	//AT_TCP
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\",\"%s\",\"%s\"", str_aux1, str_aux2, ip, port);
					answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					break;
				case TCP_SERVER:
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[15])));	//AT_IP_SERVER
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s1,\"%s\"", str_aux1, port);
					answer = sendCommand1(buffer_GPRS, OK_RESPONSE);
					break;
				case UDP_EXTENDED:
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[33])));	//AT_IP_UDP_EXTENDED
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s1", str_aux1);
					answer |= sendCommand1(buffer_GPRS, OK_RESPONSE);
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[10])));	//AT_IP_CLIENT
					strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[12])));	//AT_UDP
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\",\"%s\",\"%s\"", str_aux1, str_aux2, ip, port);
					answer |= sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[33])));	//AT_IP_UDP_EXTENDED
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s2,\"%s\",\"%s\"", str_aux1, ip, port);
					answer |= sendCommand1(buffer_GPRS, OK_RESPONSE);
					break;
			}
			break;

		case 1: // Multi mode
			switch (working_mode)
			{
				case UDP_CLIENT:
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[10])));	//AT_IP_CLIENT
					strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[12])));	//AT_UDP
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u,\"%s\",\"%s\",\"%s\"", str_aux1, n_connection, str_aux2, ip, port);
					answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					break;
				case TCP_CLIENT:
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[10])));	//AT_IP_CLIENT
					strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[11])));	//AT_TCP
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u,\"%s\",\"%s\",\"%s\"", str_aux1, n_connection, str_aux2, ip, port);
					answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);
					break;
				case TCP_SERVER:
					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[15])));	//AT_IP_SERVER
					snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s1,\"%s\"", str_aux1, port);
					answer = sendCommand1(buffer_GPRS, OK_RESPONSE);
					break;
			}
			break;
	}

	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}

	if (working_mode < 2)
	{
		// Waits TCP_CONNECTION_TIME_1 to connect
		if (IP_app_mode == 0)
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[13])));	//AT_CONNECTED_OK
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[14])));	//AT_CONNECTED_FAIL
			answer = waitForData(str_aux1, str_aux2, TCP_CONNECTION_TIME_1, millis(), 0, 2);
		}
		else
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[14])));	//AT_CONNECTED_FAIL
			answer = waitForData("CONNECT\r\n", str_aux1, TCP_CONNECTION_TIME_1, millis(), 0, 2);
		}

		if (answer == 0)
		{
			return -3;

		}
	}


	return 1;
}

/* sendData(const char*) - sends 'data' to the specified to 'n_connection'
 *
 * This function sends 'data' to the specified to 'n_connection'.
 * In single connection not specifies 'n_connection'.
 *
 * Returns
 * '1' on success,
 * '0' if error waiting the response of the module,
 * '-2' if error with CME error code available
 * '-3' if no feedback detected
 * '-4' if the send fails
*/
int8_t WaspGPRS_Pro_core::sendData(const char* data){
	return( sendData((uint8_t*)data, strlen(data),(uint8_t) NULL));
}

/* sendData(const char*, uint8_t) - sends 'data' to the specified to 'n_connection'
 *
 * This function sends 'data' to the specified to 'n_connection'.
 * In single connection not specifies 'n_connection'.
 *
 * Returns
 * '1' on success,
 * '0' if error waiting the response of the module,
 * '-2' if error with CME error code available
 * '-3' if no feedback detected
 * '-4' if the send fails
*/
int8_t WaspGPRS_Pro_core::sendData(const char* data, uint8_t n_connection){
	return( sendData((uint8_t*)data, strlen(data), n_connection));
}

/* sendData(uint8_t*, int) - sends 'data' to the specified to 'n_connection'
 *
 * This function sends 'data' to the specified to 'n_connection'.
 * In single connection not specifies 'n_connection'.
 *
 * Returns
 * '1' on success,
 * '0' if error waiting the response of the module,
 * '-2' if error with CME error code available
 * '-3' if no feedback detected
 * '-4' if the send fails
*/
int8_t WaspGPRS_Pro_core::sendData(uint8_t* data, int length){
	return( sendData(data, length, (uint8_t)NULL));
}

/* sendData(uint8_t*, int, uint8_t) - sends 'data' to the specified to 'n_connection'
 *
 * This function sends 'data' to the specified to 'n_connection'.
 * In single connection not specifies 'n_connection'.
 *
 * Returns
 * '1' on success,
 * '0' if error waiting the response of the module,
 * '-2' if error with CME error code available
 * '-3' if no feedback detected
 * '-4' if the send fails
*/
int8_t WaspGPRS_Pro_core::sendData(uint8_t* data, int length, uint8_t n_connection){

	uint8_t answer=0, count=10;

	if (IP_app_mode == 0)
	{
		// Non transparent mode
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[16])));	//AT_IP_SEND
		switch (IP_mode){
			case 0: // Single mode
				snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=%d", str_aux1, length);
				break;
			case 1: // Multi mode
				snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=%c,%d", str_aux1, n_connection+0x30, length);
				break;
		}

		count=5;
		// Waits the connection  to send data
		do{
			answer = sendCommand2(buffer_GPRS, ">", ERROR_CME);
			count--;
		}while ((answer != 1) && (count != 0));

		if (answer == 0)
		{
			return 0;
		}
		else if (answer == 2)
		{
			return -2;
		}

		// Sends data
		count=5;

		do{
			// Sends data and waits 30 seconds for the feedback
			for(int x = 0; x < length; x++)
			{
				printByte(data[x], _socket);
			}

			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[17])));	//AT_IP_SEND_R
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[18])));	//AT_IP_SEND_FAIL
			answer = waitForData(str_aux1, str_aux2, 30000, millis(), 0, 2);
			count--;
		}while ((answer != 1) && (count != 0));

		if (answer == 0)
		{
			return -3;
		}
		else if (answer == 2)
		{
			return -4;
		}
	}
	else
	{
		// Transparent mode
		for(int x = 0; x < length; x++)
		{
			printByte(data[x], _socket);
		}
	}

	return 1;
}

/* readIPData(char*) - Gets data receive from a TCP or UDP connection and stores it in 'buffer_GPRS'
 *
 * This function gets data receive from a TCP or UDP connection and stores it in 'buffer_GPRS'.
 *
 * In multi connection mode also stores the connection number in 'IP_data_from.
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * Returns '1' on success and '0' if error
*/
int8_t WaspGPRS_Pro_core::readIPData(){
	int IP_data_length=0,IP_data_from=0;
	int i=0,j;
	int8_t answer=0;
	unsigned long previous;

	if (IP_mode == 0)
	{
		// Single connection mode

		if (IP_app_mode == 0)
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[50])));	//GET_MANUAL
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[51])));	//IP_DATA

			// Non transparent mode

			if (strstr(buffer_GPRS, str_aux1) != NULL)
			{
				#if GPRS_debug_mode>0
					PRINTLN_GPRS(F("Get data manually..."));
				#endif
				answer = GetDataManually(BUFFER_SIZE, 0);
			}
			else if (strstr(buffer_GPRS, str_aux2) != NULL)
			{
				#if GPRS_debug_mode>0
					PRINTLN_GPRS(F("Get data..."));
				#endif

				memset(buffer_GPRS, '\0', sizeof(buffer_GPRS) );

				previous = millis();
				i = 0;
				do{
					while((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
					{
						// Condition to avoid an overflow (DO NOT REMOVE)
						if( millis() < previous)
						{
							previous = millis();
						}

						delay(10);
					}

					buffer_GPRS[i] = serialRead(_socket);
					i++;

					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}while ((buffer_GPRS[i-1] != ':') && ((millis() - previous) < 1000));

				if ((millis() - previous) > 1000)
				{
					return 0;
				}

				buffer_GPRS[i-1] = '\0';


				IP_data_length = atoi(buffer_GPRS);

				#if GPRS_debug_mode>0
					PRINT_GPRS(F("N bytes: "));
					USB.println(IP_data_length);
				#endif

				if (IP_data_length >= BUFFER_SIZE)
				{
					IP_data_length = BUFFER_SIZE - 1;
				}

				i = 0;
        #if GPRS_debug_mode>1
          PRINT_GPRS(F(""));
        #endif
				do{
					while((serialAvailable(_socket) == 0) && ((millis()- previous) < 1000))
					{
						// Condition to avoid an overflow (DO NOT REMOVE)
						if( millis() < previous) previous = millis();
					}

					buffer_GPRS[i] = serialRead(_socket);
					i++;
					#if GPRS_debug_mode>1
						USB.print(char(buffer_GPRS[i-1]));
					#endif
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();

				}while ((i < IP_data_length) && ((millis()- previous) < 10000));
				buffer_GPRS[i] = '\0';


				#if GPRS_debug_mode>0
					PRINT_GPRS(F("Data received: "));
					USB.println(buffer_GPRS);
				#endif
				answer = 1;

			}
			else
			{
				i = 0;
				previous=millis();
        #if GPRS_debug_mode>1
          PRINT_GPRS(F(""));
        #endif
				do{
					while((serialAvailable(_socket) == 0) && ((millis()- previous) < 10000))
					{
						// Condition to avoid an overflow (DO NOT REMOVE)
						if( millis() < previous) previous = millis();
					}

					buffer_GPRS[i] = serialRead(_socket);
					i++;
					#if GPRS_debug_mode>1
						USB.print(char(buffer_GPRS[i-1]));
					#endif
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();

				}while ((i < BUFFER_SIZE) && ((millis()- previous) < 10000));
			}

		}
		else
		{
			// Transparent mode

			#if GPRS_debug_mode>0
				PRINTLN_GPRS(F("Get data in transparent mode..."));
			#endif
			memset(buffer_GPRS + 1, '\0', sizeof(buffer_GPRS) - 1);
			i = 1;
			previous = millis();

      #if GPRS_debug_mode>1
        PRINT_GPRS(F(""));
      #endif
			while ((i < BUFFER_SIZE) && ((millis() - previous) < 5000))
			{
				j = serialAvailable(_socket);
				if (j != 0)
				{
					do{
						buffer_GPRS[i] = serialRead(_socket);

						#if GPRS_debug_mode>1
							USB.print(char(buffer_GPRS[i]));
						#endif
						j--;
						i++;
					}while ((j > 0) && (i < (BUFFER_SIZE)));
					previous = millis();
				}
				else
				{
					delay(10);
				}
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();

			}
			answer = 1;

			#if GPRS_debug_mode>0
        PRINT_GPRS(F("bytes received"));
				USB.println(i, DEC);
			#endif
		}
	}
	else
	{
		// Multiconnection mode, only non transparent



		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[5])));	//GET_MANUAL
		if (strstr(buffer_GPRS, str_aux1) != NULL)
		{

			#if GPRS_debug_mode>0
				PRINTLN_GPRS(F("Get data manually in multiconnection mode..."));
			#endif
			// Gets the number of the connection
			previous = millis();
			i = 0;
			do{
				while((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous)
					{
						previous = millis();
					}

					delay(10);
				}

				buffer_GPRS[i] = serialRead(_socket);
				i++;

				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((buffer_GPRS[i-1] != ',') && ((millis() - previous) < 1000));

			if ((millis() - previous) > 1000)
			{
				return 0;
			}

			buffer_GPRS[i-1] = '\0';

			IP_data_from = atoi(buffer_GPRS);

			#if GPRS_debug_mode>0
				PRINT_GPRS(F("N connection: "));
				USB.println(IP_data_from);
			#endif

			answer = GetDataManually(BUFFER_SIZE, IP_data_from);

			#if GPRS_debug_mode>0
				PRINT_GPRS(F("Data received: "));
				USB.println(buffer_GPRS);
			#endif
			answer = 1;
		}
		else
		{

			#if GPRS_debug_mode>0
				PRINTLN_GPRS(F("Get data in multiconnection mode..."));
			#endif
			// Gets the number of the connection
			previous = millis();
			i = 0;
			do{
				while((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous)
					{
						previous = millis();
					}

					delay(10);
				}

				buffer_GPRS[i] = serialRead(_socket);
				i++;

				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((buffer_GPRS[i-1] != ',') && ((millis() - previous) < 1000));

			if ((millis() - previous) > 1000)
			{
				return 0;
			}

			buffer_GPRS[i-1] = '\0';

			IP_data_from = atoi(buffer_GPRS);

			#if GPRS_debug_mode>0
				PRINT_GPRS(F("N connection: "));
				USB.println(IP_data_from);
			#endif

			previous = millis();
			i = 0;
			do{
				while((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous)
					{
						previous = millis();
					}

					delay(10);
				}

				buffer_GPRS[i] = serialRead(_socket);
				i++;

				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((buffer_GPRS[i-1] != ':') && ((millis() - previous) < 1000));

			buffer_GPRS[i-1] = '\0';

			IP_data_length = atoi(buffer_GPRS);

			#if GPRS_debug_mode>0
				PRINT_GPRS(F("N bytes: "));
				USB.println(IP_data_length);
			#endif

			if (IP_data_length >= BUFFER_SIZE)
			{
				IP_data_length = BUFFER_SIZE - 1;
			}
			//Discard '\r' and '\n'
			serialRead(_socket);
			serialRead(_socket);
			i = 0;

      #if GPRS_debug_mode>1
        PRINT_GPRS(F(""));
      #endif
			do{
				while((serialAvailable(_socket) == 0) && ((millis()- previous) < 1000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}

				buffer_GPRS[i] = serialRead(_socket);
				i++;
				#if GPRS_debug_mode>1
					USB.print(char(buffer_GPRS[i-1]));
				#endif
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();

			}while ((i < IP_data_length) && ((millis()- previous) < 10000));
			buffer_GPRS[i] = '\0';


			#if GPRS_debug_mode>0
				PRINT_GPRS(F("Data received: "));
				USB.println(buffer_GPRS);
			#endif
			answer = 1;

		}
	}

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* closeSocket() - closes the socket specified by 'socket'
 *
 * This function closes the connection specified by 'n_connection'.
 * In single not specifies number of connenction. For server use 8
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::closeSocket(){
	return( closeSocket((uint8_t)NULL));
}

/* closeSocket(uint8_t) - closes the socket specified by 'socket'
 *
 * This function closes the connection specified by 'n_connection'.
 * In single not specifies number of connenction. For server use 8
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::closeSocket(uint8_t n_connection){

	uint8_t answer=0;

	if (n_connection == 8)
	{
		// Closes TCP server
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[15])));	//AT_IP_SERVER
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s0", str_aux1);
		answer=sendCommand1(buffer_GPRS, OK_RESPONSE);
	}
	else
	{
		// Closes TCP or UDP client
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[19])));	//AT_IP_CLOSE
		switch (IP_mode)
		{
			case 0: // Single mode
				snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s0", str_aux1);
				break;
			case 1: // Multiconnection mode
				snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%c,0", str_aux1, n_connection+0x30);
				break;
		}

		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[20])));	//AT_IP_CLOSE_R
		answer = sendCommand1(buffer_GPRS, str_aux1);
	}

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* QuickcloseSocket(socket) - Enables/disables to close the connection quickly
 *
 * This function enables/disables to close the connection quickly.
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::QuickcloseSocket(uint8_t mode){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[21])));	//AT_IP_QCLOSE
	switch (mode)
	{
		case 0:
			snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s0", str_aux1);
			break;
		case 1:
			snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s1", str_aux1);
			break;
	}

	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* getIPfromDNS(const char*) - Gets the IP direction from a URL using DNS servers
 *
 * This function gets the IP direction from a URL using DNS servers
 *
 * Returns '1' on success, '0' if error
*/
uint8_t WaspGPRS_Pro_core::getIPfromDNS(const char* IP_query){

	unsigned long previous;
	uint8_t aux;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[23])));	//AT_IP_QUERY_DNS
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, IP_query);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[24])));	//AT_IP_QUERY_DNS_R
	aux = sendCommand2(buffer_GPRS, str_aux1, ERROR);
	if (aux == 1)
	{
		previous = millis();
		aux = serialRead(_socket);
		if (aux == '0')
		{
			return 0;
		}
		aux = 0;
		while ((aux < 3) && ((millis()- previous) < 1000))
		{
			while((serialRead(_socket) != '"') && ((millis()- previous) < 1000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			aux++;

			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}
		aux=0;
		do{
			buffer_GPRS[aux]=serialRead(_socket);
			aux++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((buffer_GPRS[aux-1] != '"') && ((millis()- previous) < 1000));
		buffer_GPRS[aux-1]='\0';
		return 1;
	}
	else
	{
		return 0;
	}
	return 1;
}

/* IPHeader(uint8_t) - Adds an IP head at the beginning of a package received
 *
 * This function adds an IP head at the beginning of a package received
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::IPHeader(uint8_t on_off){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[27])));	//AT_IP_HEADER
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, on_off);

	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* SetAutoSendingTimer(uint8_t) - Sets a timer when module is sending data
 *
 * This function sets a timer when module is sending data
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::SetAutoSendingTimer(uint8_t mode){
	return( SetAutoSendingTimer(mode, 0));
}

/* SetAutoSendingTimer(uint8_t, uint8_t) - Sets a timer when module is sending data
 *
 * This function sets a timer when module is sending data
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::SetAutoSendingTimer(uint8_t mode, uint8_t time){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[28])));	//AT_IP_AUTOSENDING
	switch (mode)
	{
		case 0:
			snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s0", str_aux1);
			break;
		case 1:
			snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s1,%u", str_aux1, time);
			break;
	}

	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* ShowRemoteIP(uint8_t) - Enables or disables to show remote IP address and port when received data
 *
 * This function enables or disables to show remote IP address and port when received data
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::ShowRemoteIP(uint8_t on_off){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[29])));	//AT_IP_SHOW_REMOTE_IP
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, on_off);

	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* ShowProtocolHeader(uint8_t) - Enables or disables to show transfer protocol in IP head when received data
 *
 * This function enables or disables to show transfer protocol in IP head when received data
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::ShowProtocolHeader(uint8_t on_off){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[30])));	//AT_IP_PROTOCOL_HEADER
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, on_off);

	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* DiscardInputATData(uint8_t) - Enables or disables to discard input AT data in TCP data send
 *
 * This function enables or disables show to discard input AT data in TCP data send
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::DiscardInputATData(uint8_t on_off){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[31])));	//AT_IP_DISCARD_AT_DATA
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s%u", str_aux1, on_off);

	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

/* SetDataManually(uint8_t) - Enables or disables to get data manually from a TCP or UDP connection
 *
 * This function enables or disables show to get data manually from a TCP or UDP connection
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::SetDataManually(uint8_t on_off){
	return SetDataManually(on_off, 0);
}

/* SetDataManually(uint8_t, uint8_t) - Enables or disables to get data manually from a TCP or UDP connection
 *
 * This function enables or disables show to get data manually from a TCP or UDP connection
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::SetDataManually(uint8_t on_off, uint8_t id){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[32])));	//AT_IP_GET_MANUALLY
	if (IP_mode == 0)
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=%u", str_aux1, on_off);
	}
	else
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=%u,%u", str_aux1, on_off, id);
	}

	answer = sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		return 0;
	}

	return 1;
}

/* GetDataManually(uint16_t) - Gets data manually from a TCP or UDP connection
 *
 * This function gets data manually from a TCP or UDP connection
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::GetDataManually(uint16_t data_length){
	return GetDataManually(data_length, 0);
}

/* GetDataManually(uint16_t, uint8_t) - Gets data manually from a TCP or UDP connection
 *
 * This function gets data manually from a TCP or UDP connection
 *
 * Returns '1' on success, '0' if error and '2' if buffer_GPRS is full. The answer from the server is
 * limited by the length of buffer_GPRS. To increase the length of the answer, increase the BUFFER_SIZE constant.
*/
int8_t WaspGPRS_Pro_core::GetDataManually(uint16_t data_length, uint8_t id){

	uint8_t answer=0;
	uint8_t i=0,IP_data_length;
	unsigned long previous;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[32])));	//AT_IP_GET_MANUALLY
	if (IP_mode == 0)
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=2,%u", str_aux1, data_length);
	}
	else
	{
		snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s=2,%u,%u", str_aux1, id, data_length);
	}
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[52])));	//GET_DATA
	answer = sendCommand2(buffer_GPRS, str_aux1, ERROR);

	switch (answer)
	{
		case 0:
			return 0;
			break;
		case 1:
			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((serialRead(_socket) != ':') && ((millis() - previous) < 10000));
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((serialRead(_socket) != ',') && ((millis() - previous) < 10000));

			if (IP_mode == 1)
			{
				do{
					while((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000))
					{
						// Condition to avoid an overflow (DO NOT REMOVE)
						if( millis() < previous) previous = millis();
					}
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}while ((serialRead(_socket) != ',') && ((millis() - previous) < 10000));
			}

			// Gets the length of the data string
/*			IP_data_length=0;
			aux=serialRead(_socket);
			do{
				IP_data_length*=10;
				IP_data_length+=(aux-0x30);
				aux=serialRead(_socket);
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((aux != ',') && ((millis() - previous) < 10000));*/

			IP_data_length=0;
			i = 0;
			do{
				str_aux1[i] = serialRead(_socket);
				i++;
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((str_aux1[i - 1] != ',') && ((millis() - previous) < 10000));
			str_aux1[i - 1] = '\0';
			IP_data_length = atoi(str_aux1);

			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((serialRead(_socket) != '\n') && ((millis() - previous) < 10000));


			i = 0;
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000))
				{
					// Condition to avoid an overflow (DO NOT REMOVE)
					if( millis() < previous) previous = millis();
				}
				if (i < BUFFER_SIZE)
				{
					buffer_GPRS[i] = serialRead(_socket);
				}
				else
				{
					serialRead(_socket);
				}
				i++;
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}while ((i < (IP_data_length-1)) && ((millis() - previous) < 10000));

			if (i < BUFFER_SIZE)
			{
				buffer_GPRS[i] = '\0';
			}
			else
			{
				buffer_GPRS[BUFFER_SIZE - 1] = '\0';
			}

			break;

		case 2:
			return 0;
			break;
	}

	if (i >= BUFFER_SIZE)
	{
		return 2;
	}

	return 1;
}

/* setDNS() - Sets the directions of DNS servers from GPRS_Proconstants.h
 *
 * This function sets the directions of DNS servers from GPRS_Proconstants.h
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::setDNS(){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[29])));	//AT_IP_SET_DNS
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\",\"%s\"", str_aux1, AT_GPRS_DNS1, AT_GPRS_DNS2);

	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);

	if (answer == 2)
	{
		return -2;
	}

	return answer;
}

/* setDNS(const char*) - Sets the direction of DNS server
 *
 * This function sets the direction of DNS server
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::setDNS(const char* DNS_dir){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[29])));	//AT_IP_SET_DNS
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\"", str_aux1, DNS_dir);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);

	if (answer == 2)
	{
		return -2;
	}

	return answer;
}

/* setDNS(const char*, const char*) - Sets the directions of DNS servers
 *
 * This function sets the directions of DNS servers
 *
 * Returns '1' on success, '0' if error and '-2' if CME error code available
*/
int8_t WaspGPRS_Pro_core::setDNS(const char* DNS_dir1, const char* DNS_dir2){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[29])));	//AT_IP_SET_DNS
	snprintf(buffer_GPRS, sizeof(buffer_GPRS), "%s\"%s\",\"%s\"", str_aux1, DNS_dir1, DNS_dir2);
	answer=sendCommand2(buffer_GPRS, OK_RESPONSE, ERROR_CME);

	if (answer == 2)
	{
		return -2;
	}

	return answer;
}
#endif

/* setDefault() - Sets all current parameters to the manufacturer defined profile.
 *
 * This function sts all current parameters to the manufacturer defined profile.
 *
 * Returns '1' on success and '0' if error
*/
int8_t WaspGPRS_Pro_core::setDefault(){

	return (sendCommand1("&F0", OK_RESPONSE));

}

/* whoamI() - Gets the model of the module
 *
 * This function gets the model of the module and saves it in 'buffer_GPRS'
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::whoamI(){
	int8_t answer, x;
	unsigned long previous;

	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[26])));	//AT_WHO_AM_I
	answer=sendCommand1(str_aux1, "\r\n");

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			buffer_GPRS[x]=serialRead(_socket);
			x++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((buffer_GPRS[x-1] != '\r') && ((millis() - previous) < 5000));
		buffer_GPRS[x-1]='\0';
	}

	return answer;

}

/* firmware_version() - Gets the firmware version of the module
 *
 * This function gets the firmware version of the module and saves it in 'buffer_GPRS'
 *
 * Returns '1' on success, '0' if error
*/
int8_t WaspGPRS_Pro_core::firmware_version(){
	int8_t answer, x;
	unsigned long previous;

	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[27])));	//AT_FIRMWARE
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[28])));	//AT_FIRMWARE_R
	answer=sendCommand1(str_aux1, str_aux2);

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous) previous = millis();
			}
			buffer_GPRS[x]=serialRead(_socket);
			x++;
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}while ((buffer_GPRS[x-1] != '\r') && ((millis() - previous) < 5000));
		buffer_GPRS[x-1]='\0';
	}

	return answer;

}

/* set_APN(char*) - Shows the apn, login and password constants
 *
 * This function shows the apn, login and password constants
 *
 * Returns nothing
*/
void WaspGPRS_Pro_core::set_APN( char* apn){

	set_APN( apn, NULL, NULL);
}

/* set_APN(char*, char*, char*) - Shows the apn, login and password constants
 *
 * This function shows the apn, login and password constants
 *
 * Returns nothing
*/
void WaspGPRS_Pro_core::set_APN( char* apn, char* login, char* password){

	memset(_apn, '\0', sizeof(_apn));
	memset(_apn_login, '\0', sizeof(_apn_login));
	memset(_apn_password, '\0', sizeof(_apn_password));

	strncpy(_apn, apn, min(sizeof(_apn), strlen(apn)));
	strncpy(_apn_login, login, min(sizeof(_apn_login), strlen(login)));
	strncpy(_apn_password, password, min(sizeof(_apn_password), strlen(password)));
}

/* show_APN() - Shows the apn, login and password constants
 *
 * This function shows the apn, login and password constants
 *
 * Returns nothing
*/
void WaspGPRS_Pro_core::show_APN(){
	// APN parameters depends on SIM
	PRINT_GPRS(F("APN: "));
	USB.println(_apn);
	PRINT_GPRS(F("LOGIN: "));
	USB.println(_apn_login);
	PRINT_GPRS(F("PASSWORD: "));
	USB.println(_apn_password);
}

#if OTA_FUSE
/* requestOTA(const char*, const char*, const char*, const char*) - It downloads a new OTA file if OTA is necessary
 *
 * This function downloads a new OTA file if OTA is necessary
 *
 * Returns '1' if success, '-2' if error and '-4' if error setting the type of internet connection,
 * '-5' if error setting the apn, '-6' if error setting the user name, '-7' if error setting the password
 * '-8' if error saving the configuration, '-9' if error opening connection with the GPRS provider, '-10' error downloading OTA version file, '-11' if error getting the IP address
 * '-12' if error setting the FTP/HTTP ID, '-13' if error setting the FTP mode, '-14' if error setting the FTP type,
 * '-15' if error setting the FTP server, '-16' if error setting the FTP port, '-17' if error setting the user name,
 * '-18' if error setting the password, '-21' if error setting the file name in the FTP server,
 * '-22' if error setting the path of the file in the FTP server, '-23' if error opening the FTP session,
 * '-24' if error starting the SD, '-25' if error creating the file, '-26' error requesting data to the FTP,
 * '-27' if error saving data into the SD, '-28' if error requesting more data to the FTP, '-30' setting the file name in the FTP to get the file size
 * '-31' setting the path in the FTP to get the file size, '-32' if error getting the file size
 * '-50' if error setting the FTP/HTTP ID with CME error code available, '-51' if error setting the FTP mode with CME error code available,
 * '-52' if error setting the FTP type with CME error code available, '-53' if error setting the FTP server with CME error code available,
 * '-54' if error setting the FTP port with CME error code available, '-55' if error setting the user name with CME error code available,
 * '-56' if error setting the password with CME error code available, '-57' if error setting the file name in the FTP server with CME error code available,
 * '-58' if error setting the path of the file in the FTP server with CME error code available, '-59' if error opening the FTP session with CME error code available,
 * '-60' if error requesting data to the FTP with CME error code available, '-61' if error requesting more data to the FTP with CME error code available,
 * '-62 setting the file name in the FTP to get the file size with CME error code available,
 * '-63' setting the path in the FTP to get the file size with CME error code available, '-64' if error getting the file size with CME error code available,
 * '-65' if FTP is busy, '-66' if there isn't FILE tag, '-67' if there isn't PATH tag, '-68' if there isn't VERSION tag,'-69' if OTA is not necessary,
 * '-70' if OTA files are the same program version, '-71' if error opening connection with the GPRS provider, '-72' error downloading OTA file, '-73' if error getting the IP address
 * '-74' if error setting the FTP/HTTP ID, '-75' if error setting the FTP mode, '-76' if error setting the FTP type,
 * '-77' if error setting the FTP server, '-78' if error setting the FTP port, '-79' if error setting the user name,
 * '-80' if error setting the password, '-83' if error setting the file name in the FTP server,
 * '-84' if error setting the path of the file in the FTP server, '-85' if error opening the FTP session,
 * '-86' if error starting the SD, '-87' if error creating the file, '-88' error requesting data to the FTP,
 * '-89' if error saving data into the SD, '-90' if error requesting more data to the FTP, '-92' setting the file name in the FTP to get the file size
 * '-93' setting the path in the FTP to get the file size, '-94' if error getting the file size
 * '-112' if error setting the FTP/HTTP ID with CME error code available, '-113' if error setting the FTP mode with CME error code available,
 * '-114' if error setting the FTP type with CME error code available, '-115' if error setting the FTP server with CME error code available,
 * '-116' if error setting the FTP port with CME error code available, '-117' if error setting the user name with CME error code available,
 * '-118' if error setting the password with CME error code available, '-119' if error setting the file name in the FTP server with CME error code available,
 * '-120' if error setting the path of the file in the FTP server with CME error code available, '-121' if error opening the FTP session with CME error code available,
 * '-122' if error requesting data to the FTP with CME error code available, '-123' if error requesting more data to the FTP with CME error code available,
 * '-124' setting the file name in the FTP to get the file size with CME error code available,
 * '-125' setting the path in the FTP to get the file size with CME error code available, '-126' if error getting the file size with CME error code available
 * and '-127' if FTP is busy
*/
int8_t WaspGPRS_Pro_core::requestOTA(const char* FTP_server, const char* FTP_port, const char* FTP_username, const char* FTP_password){

	int8_t answer;
	char aux_ver[4];
	int8_t version;
	char* str_pointer;
	char aux_name[8];
	char programID[8];
	char SD_file[20];
	char FTP_file[70];

	SD.ON();
	SD.goRoot();
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_OTA_GPRS[0])));	//OTA_ver_file
	SD.del(str_aux1);
	SD.OFF();
	answer = configureGPRS_HTTP_FTP(1);
	if (answer == 1)
	{
		#if GPRS_debug_mode>0
			PRINTLN_GPRS(F("Downloading OTA VER FILE"));
		#endif
		strcpy_P(SD_file, (char*)pgm_read_word(&(table_OTA_GPRS[0])));	//OTA_ver_file
		snprintf(FTP_file, sizeof(FTP_file), ".gprs%s", SD_file);
		answer = downloadFile(FTP_file, SD_file, FTP_username, FTP_password, FTP_server, FTP_port, 1);
		if (answer == 1)
		{

			SD.ON();
			SD.goRoot();

			// Reads the file
			strcpy(buffer_GPRS, SD.cat(SD_file, 0, BUFFER_SIZE));
			// Searchs the file name
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_OTA_GPRS[2])));	//FILE_TAG
			str_pointer = strstr(buffer_GPRS, str_aux1);
			if (str_pointer != NULL)
			{

				strncpy(aux_name, strchr(buffer_GPRS, ':') + 1, 7);
				aux_name[7] = '\0';

				#if GPRS_debug_mode>0
					PRINT_GPRS(F("OTA file: "));
					USB.println(aux_name);
				#endif
				// Searchs the file name
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_OTA_GPRS[3])));	//PATH_TAG
				str_pointer = strstr(buffer_GPRS, str_aux1);
				if (str_pointer != NULL)
				{
					strncpy(str_aux3, strchr(str_pointer, ':') + 1, strchr(str_pointer, '\n') - (strchr(str_pointer, ':')));

					str_aux3[strchr(str_aux3, '\n') - str_aux3] = '\0';

					#if GPRS_debug_mode>0
						PRINT_GPRS(F("File path: "));
						USB.println(str_aux3);
					#endif
					strcat(str_aux3,"/");
					strcat(str_aux3,aux_name);

					strcpy_P(str_aux1, (char*)pgm_read_word(&(table_OTA_GPRS[4])));	//VERSION_TAG
					str_pointer = strstr(buffer_GPRS, str_aux1);

					if (str_pointer != NULL)
					{

						strncpy(aux_ver, strchr(str_pointer, ':') + 1, strchr(str_pointer, '\n') - (strchr(str_pointer, ':')));
						aux_ver[strchr(aux_ver, '\n') - aux_ver] = '\0';

						version = atoi(aux_ver);

						#if GPRS_debug_mode>0
							PRINT_GPRS(F("Version: "));
							USB.println(version, DEC);
						#endif

						SD.del(aux_name);

						strcpy_P(str_aux1, (char*)pgm_read_word(&(table_OTA_GPRS[1])));	//NO_OTA
						if (strcmp(aux_name, str_aux1) != 0)
						{
							#if GPRS_debug_mode>0
								PRINTLN_GPRS(F("Downloading OTA FILE"));
							#endif

							Utils.getProgramID(programID);
							// check if the program have a new version or if it is a different code
							if (((strcmp(aux_name, programID) == 0) && (version > Utils.getProgramVersion())) || (strcmp(aux_name, programID) != 0))
							{
								snprintf(buffer_GPRS, sizeof(buffer_GPRS), ".gprs%s", str_aux3);
								strcpy(FTP_file, buffer_GPRS);
								answer = downloadFile(FTP_file, aux_name, FTP_username, FTP_password, FTP_server, FTP_port, 1);
								if (answer == 1)
								{
									#if GPRS_debug_mode>0
										SD.ON();
										SD.ls();
										SD.OFF();
									#endif
									Utils.loadOTA(aux_name, version);
									return 1;
								}
								else
								{

									SD.OFF();
									return answer - 71;
								}
							}
							else
							{
								#if GPRS_debug_mode>0
									PRINTLN_GPRS(F("Same program version, no OTA required"));
								#endif
								SD.OFF();
								return -70;
							}
						}
						else
						{

							#if GPRS_debug_mode>0
								PRINTLN_GPRS(F("No OTA"));
							#endif
							SD.OFF();
							return -69;
						}
					}
					else
					{
						SD.OFF();
						return -68;
					}
				}
				else
				{
					SD.OFF();
					return -67;
				}

			}
			else
			{
				SD.OFF();
				return -66;
			}
		}
		else
		{
			return answer - 9;
		}
	}
	else
	{
		return answer - 2;
	}

	return 0;

}

#endif
