/*! \file	WaspBG96_contants.h
    \brief 	Header file with constant definitions and flash strings

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
    Design:			David Gascon
    Implementation:	Pablo Moreno

 */


#ifndef flash_BG96_constants_h
#define flash_BG96_constants_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <avr/pgmspace.h>
#include "BG96_error_codes.h"


/******************************************************************************
 * COMMANDS (FLASH Definitions)
 ******************************************************************************/


/// table_AT  //////////////////////////////////////////////////////////////////

const char BG96_string_00[]	PROGMEM = "AT+CREG?\r";												//0
const char BG96_string_01[]	PROGMEM = "+CREG: 0,";												//1
const char BG96_string_02[]	PROGMEM = "AT+CGREG?\r";											//2
const char BG96_string_03[]	PROGMEM = "+CGREG: 0,";												//3
const char BG96_string_04[]	PROGMEM = "+CGDCONT=1,";											//4
const char BG96_string_05[]	PROGMEM = "AT+CSQ\r";												//5 - Signal quality report
const char BG96_string_06[]	PROGMEM = "AT+QNWINFO\r";											//6 - Query Network Information
const char BG96_string_07[]	PROGMEM = "AT+QCSQ\r";												//7 - Query and Report Signal Strength
const char BG96_string_08[]	PROGMEM = "AT+QSPN\r";												//8 - Display the Name of Registered Network
const char BG96_string_09[]	PROGMEM = "AT+QIGETERROR\r";										//9 - Query the Last Error Code
const char BG96_string_10[]	PROGMEM = "AT+QIDNSCFG=1,\"%s\",\"%s\"\r";							//10 - AT+QIDNSCFG=<contextID>,<pri dnsaddr>[,<secdnsaddr>]  - Configure Address of DNS Server
const char BG96_string_11[]	PROGMEM = "AT+QIDNSGIP=1,%s\r";										//11 - AT+QIDNSGIP Get IP Address by Domain Name
const char BG96_string_12[]	PROGMEM = "ATI\r";													//12
const char BG96_string_13[]	PROGMEM = "AT+CGMI\r";												//13
const char BG96_string_14[]	PROGMEM = "AT+CGMM\r";												//14
const char BG96_string_15[]	PROGMEM = "AT+QGMR\r";												//15
const char BG96_string_16[]	PROGMEM = "AT+CGSN\r";												//16
const char BG96_string_17[]	PROGMEM = "AT+CIMI\r";												//17
const char BG96_string_18[]	PROGMEM = "AT+CCID\r";												//18
const char BG96_string_19[]	PROGMEM = "AT+CMEE=1\r";											//19
const char BG96_string_20[]	PROGMEM = "ATE0\r";													//20
const char BG96_string_21[]	PROGMEM = "AT+QTEMP\r";												//21
const char BG96_string_22[]	PROGMEM = "AT+QGDCNT?\r";											//22
const char BG96_string_23[]	PROGMEM = "AT+QGDCNT=%u";											//23
const char BG96_string_24[]	PROGMEM = "AT+COPS?\r";												//24
const char BG96_string_25[]	PROGMEM = "AT+CCLK?\r";												//25 - Clock
const char BG96_string_26[]	PROGMEM = "AT+COPS=1,0,\"%s\",%u\r";								//26
const char BG96_string_27[]	PROGMEM = "GPRS: 1";												//27
const char BG96_string_28[]	PROGMEM = "GPRS: 0";												//28
const char BG96_string_29[]	PROGMEM = "AT+CGDCONT=1,\"IP\",\"%s\"\r";							//29
const char BG96_string_30[]	PROGMEM = "AT+CEDRXS=0\r";											//30
const char BG96_string_31[]	PROGMEM = "AT+QPING=1,\"%s\"\r";									//31  AT+QPING Ping a Remote Server
const char BG96_string_32[]	PROGMEM = "+IP: \"\r\n";											//32
const char BG96_string_33[]	PROGMEM = "AT+CSQ\r\n: ,";											//33
const char BG96_string_34[]	PROGMEM = "AT+QNTP=1,\"%s\",%d\r";									//34 - AT+QNTP Synchronize Local Time with NTP Server - AT+QNTP=<contextID>,<server> [,<port>][,<autosettime>]
const char BG96_string_35[]	PROGMEM = "%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%hhd\"";	//35
const char BG96_string_36[]	PROGMEM = "AT+QICSGP=1,1,\"%s\",\"%s\",\"%s\",1\r";					//36   AT+QICSGP=<contextID>[,<context_t ype>,<APN>[,<username>,<passwor d>)[,<authentication>]]]
const char BG96_string_37[]	PROGMEM = "AT+QIDEACT=%u\r";										//37
const char BG96_string_38[]	PROGMEM = "AT+QIACT=%u\r";											//38
const char BG96_string_39[]	PROGMEM = "AT+QIACT?\r";											//39
const char BG96_string_40[]	PROGMEM = "+QIACT: ";												//40
const char BG96_string_41[]	PROGMEM = "AT+CEREG?\r";											//41
const char BG96_string_42[]	PROGMEM = "+CEREG: 0,";												//42
const char BG96_string_43[]	PROGMEM = "AT+CFUN=%u\r";											//43
const char BG96_string_44[]	PROGMEM = "AT+QPOWD\r";												//44
const char BG96_string_45[]	PROGMEM = "POWERED DOWN\r";											//45
const char BG96_string_46[]	PROGMEM = "AT+CGATT?\r";											//46
const char BG96_string_47[]	PROGMEM = "+CGATT: 1";												//47
const char BG96_string_48[]	PROGMEM = "+CGATT: 0";												//48
const char BG96_string_49[]	PROGMEM = "AT+CGATT=%u\r";											//49
const char BG96_string_50[]	PROGMEM = "AT+CGNAPN\r";											//50
const char BG96_string_51[]	PROGMEM = "AT+CPSMS?\r";											//51
const char BG96_string_52[]	PROGMEM = "AT+COPS=0\r";											//52
const char BG96_string_53[]	PROGMEM = "AT+QCFG=\"band\",%s,%s,%s,1\r";							//53
const char BG96_string_54[]	PROGMEM = "AT+CPSMS=0,,,\"%s\",\"%s\"\r";							//54
const char BG96_string_55[]	PROGMEM = "AT+CPSMS=%u\r";											//55
const char BG96_string_56[]	PROGMEM = "AT+QCFG=\"servicedomain\",1,1\r";						//56
const char BG96_string_57[]	PROGMEM = "+CGNAPN: 1,\"\r\n";										//57
const char BG96_string_58[]	PROGMEM = "AT+COPS=?\r";											//58
const char BG96_string_59[]	PROGMEM = "AT+COPS=1,%u,\"%s\",%u\r";								//59
const char BG96_string_60[]	PROGMEM = "AT+QCFG=\"nwscanmode\",%u,1\r";							//60
const char BG96_string_61[]	PROGMEM = "AT+QCFG=\"nwscanseq\",%s,1\r";							//61
const char BG96_string_62[]	PROGMEM = "AT+QCFG=\"iotopmode\",%u,1\r";							//62
const char BG96_string_63[]	PROGMEM = "AT+QIOPEN=1,2,\"UDP SERVICE\",\"127.0.0.1\",0,3030,0\r";	//63
const char BG96_string_64[]	PROGMEM = "AT+QISEND=2,%u,\"%s\",%d\r";								//64
const char BG96_string_65[]	PROGMEM = "AT+QIRD=2\r";											//65
const char BG96_string_66[]	PROGMEM = "%s\r";													//66
const char BG96_string_67[]	PROGMEM = "AT+QICLOSE=2\r";											//67
const char BG96_string_68[]	PROGMEM = "AT+QSCLK=%u\r";											//68
const char BG96_string_69[]	PROGMEM = "AT+CEDRXS=%u,%u,\"%s\"\r";								//69
const char BG96_string_70[]	PROGMEM = "AT+QIGETERROR\r";										//70
const char BG96_string_71[]	PROGMEM = "AT+CEDRXS?\r";											//71
const char BG96_string_72[]	PROGMEM = "AT+CGDCONT?\r";											//72



const char* const table_AT[] PROGMEM =
{
	BG96_string_00,
	BG96_string_01,
	BG96_string_02,
	BG96_string_03,
	BG96_string_04,
	BG96_string_05,
	BG96_string_06,
	BG96_string_07,
	BG96_string_08,
	BG96_string_09,
	BG96_string_10,
	BG96_string_11,
	BG96_string_12,
	BG96_string_13,
	BG96_string_14,
	BG96_string_15,
	BG96_string_16,
	BG96_string_17,
	BG96_string_18,
	BG96_string_19,
	BG96_string_20,
	BG96_string_21,
	BG96_string_22,
	BG96_string_23,
	BG96_string_24,
	BG96_string_25,
	BG96_string_26,
	BG96_string_27,
	BG96_string_28,
	BG96_string_29,
	BG96_string_30,
	BG96_string_31,
	BG96_string_32,
	BG96_string_33,
	BG96_string_34,
	BG96_string_35,
	BG96_string_36,
	BG96_string_37,
	BG96_string_38,
	BG96_string_39,
	BG96_string_40,
	BG96_string_41,
	BG96_string_42,
	BG96_string_43,
	BG96_string_44,
	BG96_string_45,
	BG96_string_46,
	BG96_string_47,
	BG96_string_48,
	BG96_string_49,
	BG96_string_50,
	BG96_string_51,
	BG96_string_52,
	BG96_string_53,
	BG96_string_54,
	BG96_string_55,
	BG96_string_56,
	BG96_string_57,
	BG96_string_58,
	BG96_string_59,
	BG96_string_60,
	BG96_string_61,
	BG96_string_62,
	BG96_string_63,
	BG96_string_64,
	BG96_string_65,
	BG96_string_66,
	BG96_string_67,
	BG96_string_68,
	BG96_string_69,
	BG96_string_70,
	BG96_string_71,
	BG96_string_72,
};




/// table_PIN  /////////////////////////////////////////////////////////////////

const char BG96_PIN_00[]	PROGMEM = "AT+CPIN?\r";					//0
const char BG96_PIN_01[]	PROGMEM = "READY";						//1
const char BG96_PIN_02[]	PROGMEM = "SIM PIN";					//2
const char BG96_PIN_03[]	PROGMEM = "SIM PUK";					//3
const char BG96_PIN_04[]	PROGMEM = "PH-SIM PIN";					//4
const char BG96_PIN_05[]	PROGMEM = "PH-FSIM PIN";				//5
const char BG96_PIN_06[]	PROGMEM = "PH-FSIM PUK";				//6
const char BG96_PIN_07[]	PROGMEM = "SIM PIN2";					//7
const char BG96_PIN_08[]	PROGMEM = "SIM PUK2";					//8
const char BG96_PIN_09[]	PROGMEM = "PH-NET PIN";					//9
const char BG96_PIN_10[]	PROGMEM = "PH-NET PUK";					//10
const char BG96_PIN_11[]	PROGMEM = "PH-NETSUB PIN";				//11
const char BG96_PIN_12[]	PROGMEM = "PH-NETSUB PUK";				//12
const char BG96_PIN_13[]	PROGMEM = "PH-SP PIN";					//13
const char BG96_PIN_14[]	PROGMEM = "PH-SP PUK";					//14
const char BG96_PIN_15[]	PROGMEM = "PH-CORP PIN";				//15
const char BG96_PIN_16[]	PROGMEM = "PH-CORP PUK";				//16
const char BG96_PIN_17[]	PROGMEM = "+CPIN:";						//17
const char BG96_PIN_18[]	PROGMEM = "AT+CPIN=\"%s\"\r";			//18
const char BG96_PIN_19[]	PROGMEM = "AT+CPIN=\"%s\",\"%s\"\r";	//19

const char* const table_PIN[] PROGMEM =
{
	BG96_PIN_00,
	BG96_PIN_01,
	BG96_PIN_02,
	BG96_PIN_03,
	BG96_PIN_04,
	BG96_PIN_05,
	BG96_PIN_06,
	BG96_PIN_07,
	BG96_PIN_08,
	BG96_PIN_09,
	BG96_PIN_10,
	BG96_PIN_11,
	BG96_PIN_12,
	BG96_PIN_13,
	BG96_PIN_14,
	BG96_PIN_15,
	BG96_PIN_16,
	BG96_PIN_17,
	BG96_PIN_18,
	BG96_PIN_19,
};

/// table_HTTP  ////////////////////////////////////////////////////////////////

const unsigned long BG96_HTTP_TIMEOUT = 60;		// Timeout for HTTP and HTTPS functions in miliseconds
const unsigned long BG96_HTTP_CONF_TIMEOUT = 15;	// Timeout for HTTP and HTTPS functions in miliseconds

const char BG96_HTTP_00[]	PROGMEM = "/getpost_frame_parser.php?";				//0
const char BG96_HTTP_01[]	PROGMEM = "frame=";									//1
const char BG96_HTTP_02[]	PROGMEM = "application/x-www-form-urlencoded";		//2
const char BG96_HTTP_03[]	PROGMEM = "text/plain";								//3
const char BG96_HTTP_04[]	PROGMEM = "application/octet-stream";				//4
const char BG96_HTTP_05[]	PROGMEM = "multipart/form-data";					//5
const char BG96_HTTP_06[]	PROGMEM = "AT+QHTTPCFG=\"contextid\",%u\r";			//6
const char BG96_HTTP_07[]	PROGMEM = "AT+QHTTPCFG=\"responseheader\",%u\r";	//7
const char BG96_HTTP_08[]	PROGMEM = "AT+QHTTPURL=%u,%u\r";					//8
const char BG96_HTTP_09[]	PROGMEM = "AT+QHTTPGET=%u\r";						//9
const char BG96_HTTP_10[]	PROGMEM = "AT+QHTTPREAD=%u\r";						//10
const char BG96_HTTP_11[]	PROGMEM = "AT+QHTTPPOST=%u,%u,60\r";				//11
const char BG96_HTTP_12[]	PROGMEM = "%s:%u%s%s\r";								//12
const char BG96_HTTP_13[]	PROGMEM = "AT+QHTTPCFG=\"sslctxid\",1\r";			//13


const char* const table_HTTP[] PROGMEM =
{
	BG96_HTTP_00,
	BG96_HTTP_01,
	BG96_HTTP_02,
	BG96_HTTP_03,
	BG96_HTTP_04,
	BG96_HTTP_05,
	BG96_HTTP_06,
	BG96_HTTP_07,
	BG96_HTTP_08,
	BG96_HTTP_09,
	BG96_HTTP_10,
	BG96_HTTP_11,
	BG96_HTTP_12,
	BG96_HTTP_13,
};

/// table_IP  //////////////////////////////////////////////////////////////////

const uint32_t BG96_IP_TIMEOUT = 10000;		// Timeout for IP functions in miliseconds
const uint32_t BG96_IP_CONF_TIMEOUT = 15000;	// Timeout for IP functions in miliseconds

const char BG96_IP_SOCKET_00[]	PROGMEM = "AT+QIOPEN=1,%u,\"%s\",\"%s\",%ld,%u,0\r";			//0
const char BG96_IP_SOCKET_01[]	PROGMEM = "AT+QISTATE=%u,%u\r";									//1
const char BG96_IP_SOCKET_02[]	PROGMEM = "AT+QISEND=%u,%d\r";									//2
const char BG96_IP_SOCKET_03[]	PROGMEM = "AT+QIRD=%u,%d\r";									//3
const char BG96_IP_SOCKET_04[]	PROGMEM = "AT+QICLOSE=%u\r";									//4
const char BG96_IP_SOCKET_05[]	PROGMEM = "AT+QIGETERROR\r";									//5
const char BG96_IP_SOCKET_06[]	PROGMEM = "SEND OK";											//6


const char* const table_IP[] PROGMEM =
{
	BG96_IP_SOCKET_00,
	BG96_IP_SOCKET_01,
	BG96_IP_SOCKET_02,
	BG96_IP_SOCKET_03,
	BG96_IP_SOCKET_04,
	BG96_IP_SOCKET_05,
	BG96_IP_SOCKET_06,
};




/// table_GNSS  /////////////////////////////////////////////////////////////////

const char BG96_GPS_00[]	PROGMEM = "AT+QGPSEND\r";							//0
const char BG96_GPS_01[]	PROGMEM = "AT+QGPS=%u,%u,%u,%u,%u\r";				//1
const char BG96_GPS_02[]	PROGMEM = "AT+QGPS=1\r";							//2
const char BG96_GPS_03[]	PROGMEM = "AT+QGPSCFG=\"nmeasrc\",%u\r";			//3
const char BG96_GPS_04[]	PROGMEM = "AT+QGPSCFG=\"gpsnmeatype\",%u\r";		//4
const char BG96_GPS_05[]	PROGMEM = "AT+QGPSCFG=\"glonassnmeatype\",%u\r";	//5
const char BG96_GPS_06[]	PROGMEM = "AT+QGPSCFG=\"galileonmeatype\",%u\r";	//6
const char BG96_GPS_07[]	PROGMEM = "AT+QGPSCFG=\"beidounmeatype\",%u\r";		//7
const char BG96_GPS_08[]	PROGMEM = "AT+QGPSCFG=\"gsvextnmeatype\",%u\r";		//8
const char BG96_GPS_09[]	PROGMEM = "$GPGLL";									//9
const char BG96_GPS_10[]	PROGMEM = "$GPVTG";									//10
const char BG96_GPS_11[]	PROGMEM = "$GPGSA";									//11
const char BG96_GPS_12[]	PROGMEM = "$GPGGA";									//12
const char BG96_GPS_13[]	PROGMEM = "$GPRMC";									//13
const char BG96_GPS_14[]	PROGMEM = "$GPGSV";									//14
const char BG96_GPS_15[]	PROGMEM = "AT+QGPSLOC?\r";							//15
const char BG96_GPS_16[]	PROGMEM = "AT+QGPSLOC=%u\r";						//16
const char BG96_GPS_17[]	PROGMEM = "AT+QGPSGNMEA=\"%s\"\r";					//17
const char BG96_GPS_18[]	PROGMEM = "GGA";									//18
const char BG96_GPS_19[]	PROGMEM = "RMC";									//19
const char BG96_GPS_20[]	PROGMEM = "GSV";									//20
const char BG96_GPS_21[]	PROGMEM = "GSA";									//21
const char BG96_GPS_22[]	PROGMEM = "VTG";									//22
const char BG96_GPS_23[]	PROGMEM = "GNS";									//23
const char BG96_GPS_24[]	PROGMEM = "\r\n+QGPSLOC: .,";						//24


const char* const table_GPS[] PROGMEM =
{
	BG96_GPS_00,
	BG96_GPS_01,
	BG96_GPS_02,
	BG96_GPS_03,
	BG96_GPS_04,
	BG96_GPS_05,
	BG96_GPS_06,
	BG96_GPS_07,
	BG96_GPS_08,
	BG96_GPS_09,
	BG96_GPS_10,
	BG96_GPS_11,
	BG96_GPS_12,
	BG96_GPS_13,
	BG96_GPS_14,
	BG96_GPS_15,
	BG96_GPS_16,
	BG96_GPS_17,
	BG96_GPS_18,
	BG96_GPS_19,
	BG96_GPS_20,
	BG96_GPS_21,
	BG96_GPS_22,
	BG96_GPS_23,
	BG96_GPS_24,
};

/// table_SSL  /////////////////////////////////////////////////////////////////

const unsigned long BG96_SSL_TIMEOUT = 60000;		// Timeout for SSL functions in miliseconds

const char BG96_SSL_00[]	PROGMEM = "AT+QSSLCFG=\"sslversion\",%u,%u\r";				//0
const char BG96_SSL_01[]	PROGMEM = "AT+QSSLCFG=\"ciphersuite\",%u,%s\r";				//1
const char BG96_SSL_02[]	PROGMEM = "AT+QSSLCFG=\"seclevel\",%u,%u\r";				//2
const char BG96_SSL_03[]	PROGMEM = "AT+QSSLCFG=\"cacert\",%u,\"%s\"\r";				//3
const char BG96_SSL_04[]	PROGMEM = "AT+QSSLOPEN=%u,%u,%u,\"%s\",%u,0\r";				//4
const char BG96_SSL_05[]	PROGMEM = "+QSSLOPEN: ,\r\n";								//5
const char BG96_SSL_06[]	PROGMEM = "AT+QSSLSTATE=%u\r";								//6
const char BG96_SSL_07[]	PROGMEM = "+QSSLSTATE: ";									//7
const char BG96_SSL_08[]	PROGMEM = "AT+QSSLRECV=%u,%d\r";							//8
const char BG96_SSL_09[]	PROGMEM = "+QSSLRECV: ";									//9
const char BG96_SSL_10[]	PROGMEM = "AT+QSSLCLOSE=%u\r";								//10
const char BG96_SSL_11[]	PROGMEM = "+QSSLOPEN: ";									//11
const char BG96_SSL_12[]	PROGMEM = "+QSSLSTATE: \",\r\n";							//12
const char BG96_SSL_13[]	PROGMEM = "AT+QSSLSEND=%u,%d\r";							//13
const char BG96_SSL_14[]	PROGMEM = "+QSSLURC: \"recv\",";							//14
const char BG96_SSL_15[]	PROGMEM = "AT+QSSLRECV=%u\r";								//15
const char BG96_SSL_16[]	PROGMEM = "+QSSLRECV: \r\n";								//16
const char BG96_SSL_17[]	PROGMEM = "AT+QSSLCFG=\"clientcert\",%u,\"clientcert.pem\"\r";								//17
const char BG96_SSL_18[]	PROGMEM = "AT+QSSLCFG=\"clientkey\",%u,\"user_key.pem\"\r";								//18
const char BG96_SSL_19[]	PROGMEM = "AT+QSSLCFG=\"ignorelocaltime\",%u\r";								//19

const char* const table_SSL[] PROGMEM =
{
	BG96_SSL_00,
	BG96_SSL_01,
	BG96_SSL_02,
	BG96_SSL_03,
	BG96_SSL_04,
	BG96_SSL_05,
	BG96_SSL_06,
	BG96_SSL_07,
	BG96_SSL_08,
	BG96_SSL_09,
	BG96_SSL_10,
	BG96_SSL_11,
	BG96_SSL_12,
	BG96_SSL_13,
	BG96_SSL_14,
	BG96_SSL_15,
	BG96_SSL_16,
	BG96_SSL_17,
	BG96_SSL_18,
	BG96_SSL_19,
};

/// table_FILE  /////////////////////////////////////////////////////////////////

const unsigned long BG96_FILE_TIMEOUT = 60000;		// Timeout for file functions in miliseconds

const char BG96_FILE_00[]	PROGMEM = "AT+QFUPL=\"%s\",%u,%u\r";						//0
const char BG96_FILE_01[]	PROGMEM = "AT+QFLDS=\"UFS\"\r";								//1
const char BG96_FILE_02[]	PROGMEM = "AT+QFLST=\"*\"\r";								//2
const char BG96_FILE_03[]	PROGMEM = "AT+QFOPEN=\"%s\"\r";								//3
const char BG96_FILE_04[]	PROGMEM = "AT+QFREAD=%u,%u\r";								//4
const char BG96_FILE_05[]	PROGMEM = "AT+QFCLOSE=%u\r";								//5
const char BG96_FILE_06[]	PROGMEM = "AT+QFLST=\"%s\"\r";								//6
const char BG96_FILE_07[]	PROGMEM = "AT+QFDEL=\"%s\"\r";								//7
const char BG96_FILE_08[]	PROGMEM = "+QFUPL: %d";										//8
const char BG96_FILE_09[]	PROGMEM = "+QFOPEN: ";										//9
const char BG96_FILE_10[]	PROGMEM = "+QISEND: \r\n";									//10
const char BG96_FILE_11[]	PROGMEM = "AT+QFSEEK=%u,%ld,%u\r";							//11
const char BG96_FILE_12[]	PROGMEM = "+QFLST: ,\r\n";									//12



const char* const table_FILE[] PROGMEM =
{
	BG96_FILE_00,
	BG96_FILE_01,
	BG96_FILE_02,
	BG96_FILE_03,
	BG96_FILE_04,
	BG96_FILE_05,
	BG96_FILE_06,
	BG96_FILE_07,
	BG96_FILE_08,
	BG96_FILE_09,
	BG96_FILE_10,
	BG96_FILE_11,
	BG96_FILE_12,

};

/// table_FTP  /////////////////////////////////////////////////////////////////

const unsigned BG96_FTP_TIMEOUT = 60;		// Timeout for FTP functions in seconds

const char BG96_FTP_00[]	PROGMEM = "AT+QFTPCFG=\"contextid\",1\r";						//0
const char BG96_FTP_01[]	PROGMEM = "AT+QFTPCFG=\"account\",\"%s\",\"%s\"\r";				//1
const char BG96_FTP_02[]	PROGMEM = "AT+QFTPCFG=\"filetype\",%u\r";						//2
const char BG96_FTP_03[]	PROGMEM = "AT+QFTPCFG=\"transmode\",%u\r";						//3
const char BG96_FTP_04[]	PROGMEM = "AT+QFTPCFG=\"rsptimeout\",%u\r";						//4
const char BG96_FTP_05[]	PROGMEM = "AT+QFTPOPEN=\"%s\",%u\r";							//5
const char BG96_FTP_06[]	PROGMEM = "+QFTPOPEN: ";										//6
const char BG96_FTP_07[]	PROGMEM = "AT+QFTPCLOSE\r";										//7
const char BG96_FTP_08[]	PROGMEM = "+QFTPCLOSE: ";										//8
const char BG96_FTP_09[]	PROGMEM = "AT+QFTPDEL=\"%s\"\r";								//9
const char BG96_FTP_10[]	PROGMEM = "+QFTPDEL: ";											//10
const char BG96_FTP_11[]	PROGMEM = "AT+QFTPSIZE=\"%s\"\r";								//11
const char BG96_FTP_12[]	PROGMEM = "AT+QFTPPWD\r";										//12
const char BG96_FTP_13[]	PROGMEM = "+QFTPPWD: ";											//13
const char BG96_FTP_14[]	PROGMEM = "+QFTPSIZE: ";										//14
const char BG96_FTP_15[]	PROGMEM = "AT+QFTPCWD=\"%s\"\r";								//15
const char BG96_FTP_16[]	PROGMEM = "+QFTPCWD: ";											//16
const char BG96_FTP_17[]	PROGMEM = "AT+QFTPPUT=\"%s\",\"COM:\",0\r";						//17
const char BG96_FTP_18[]	PROGMEM = "+QFTPPUT: ";											//18
const char BG96_FTP_19[]	PROGMEM = "+++";												//19
const char BG96_FTP_20[]	PROGMEM = "AT+QFTPGET=\"%s\",\"%s\"\r";							//20
const char BG96_FTP_21[]	PROGMEM = "+QFTPGET: ";											//21
const char BG96_FTP_22[]	PROGMEM = "AT+QFTPMKDIR=\"%s\"\r";								//22
const char BG96_FTP_23[]	PROGMEM = "+QFTPMKDIR: ";										//23
const char BG96_FTP_24[]	PROGMEM = "AT+QFTPRMDIR=\"%s\"\r";								//24
const char BG96_FTP_25[]	PROGMEM = "+QFTPRMDIR: ";										//25
const char BG96_FTP_26[]	PROGMEM = "AT+QFTPSTAT\r";										//26
const char BG96_FTP_27[]	PROGMEM = "+QFTPSTAT: ";										//27
const char BG96_FTP_28[]	PROGMEM = "AT+QFTPCFG=\"ssltype\",%u\r";						//28
const char BG96_FTP_29[]	PROGMEM = "AT+QFTPCFG=\"sslctxid\",%u\r";						//29



const char* const table_FTP[] PROGMEM =
{
	BG96_FTP_00,
	BG96_FTP_01,
	BG96_FTP_02,
	BG96_FTP_03,
	BG96_FTP_04,
	BG96_FTP_05,
	BG96_FTP_06,
	BG96_FTP_07,
	BG96_FTP_08,
	BG96_FTP_09,
	BG96_FTP_10,
	BG96_FTP_11,
	BG96_FTP_12,
	BG96_FTP_13,
	BG96_FTP_14,
	BG96_FTP_15,
	BG96_FTP_16,
	BG96_FTP_17,
	BG96_FTP_18,
	BG96_FTP_19,
	BG96_FTP_20,
	BG96_FTP_21,
	BG96_FTP_22,
	BG96_FTP_23,
	BG96_FTP_24,
	BG96_FTP_25,
	BG96_FTP_26,
	BG96_FTP_27,
	BG96_FTP_28,
	BG96_FTP_29,

};

/// table_MQTT  /////////////////////////////////////////////////////////////////

const unsigned long BG96_MQTT_TIMEOUT = 60000;		// Timeout for MQTT functions in miliseconds

const char BG96_MQTT_00[]	PROGMEM = "AT+QMTOPEN=0,\"%s\",%u\r";						//0
const char BG96_MQTT_01[]	PROGMEM = "+QMTOPEN: ";										//1
const char BG96_MQTT_02[]	PROGMEM = "AT+QMTCONN?\r";							//2
const char BG96_MQTT_03[]	PROGMEM = "AT+QMTCONN=0,\"%s\",\"%s\",\"%s\"\r";			//3
const char BG96_MQTT_04[]	PROGMEM = "+QMTCONN: ";										//4
const char BG96_MQTT_05[]	PROGMEM = "AT+QMTSUB=0,%u,\"%s\",%u\r";						//5
const char BG96_MQTT_06[]	PROGMEM = "+QMTSUB: ";										//6
const char BG96_MQTT_07[]	PROGMEM = "AT+QMTUNS=0,%u,\"%s\"\r";						//7
const char BG96_MQTT_08[]	PROGMEM = "+QMTUNS: ";										//8
const char BG96_MQTT_09[]	PROGMEM = "AT+QMTPUB=0,%u,%u,%u,\"%s\"\r";					//9
const char BG96_MQTT_10[]	PROGMEM = "+QMTPUB: ";										//10
const char BG96_MQTT_11[]	PROGMEM = "AT+QMTDISC=0\r";									//11
const char BG96_MQTT_12[]	PROGMEM = "+QMTDISC: ";										//12
const char BG96_MQTT_13[]	PROGMEM = "+QMTSTAT: ";										//13
const char BG96_MQTT_14[]	PROGMEM = "+QMTRECV: 0,";										//14
const char BG96_MQTT_15[]	PROGMEM = "AT+QMTCFG=\"SSL\",%u,%u,%u\r";					//15



const char* const table_MQTT[] PROGMEM =
{
	BG96_MQTT_00,
	BG96_MQTT_01,
	BG96_MQTT_02,
	BG96_MQTT_03,
	BG96_MQTT_04,
	BG96_MQTT_05,
	BG96_MQTT_06,
	BG96_MQTT_07,
	BG96_MQTT_08,
	BG96_MQTT_09,
	BG96_MQTT_10,
	BG96_MQTT_11,
	BG96_MQTT_12,
	BG96_MQTT_13,
	BG96_MQTT_14,
	BG96_MQTT_15,

};


#endif
