/*! \file	Wasp4G_contants.h
    \brief 	Header file with constant definitions and flash strings

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
    Design:			David Gascon
    Implementation:	Alejandro Gállego

 */


#ifndef flash_4g_constants_h
#define flash_4g_constants_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <avr/pgmspace.h>
#include "Wasp4G_error_codes.h"


/******************************************************************************
 * COMMANDS (FLASH Definitions)
 ******************************************************************************/


/// table_4G  //////////////////////////////////////////////////////////////////

const char LE910_string_00[]	PROGMEM = "AT+CREG?\r";						//0
const char LE910_string_01[]	PROGMEM = "+CREG: 0,";						//1
const char LE910_string_02[]	PROGMEM = "AT+CGREG?\r";					//2
const char LE910_string_03[]	PROGMEM = "+CGREG: 0,";						//3
const char LE910_string_04[]	PROGMEM = "+CGDCONT=1,";					//4
const char LE910_string_05[]	PROGMEM = "AT#USERID=\"%s\"\r";				//5
const char LE910_string_06[]	PROGMEM = "AT#PASSW=\"%s\"\r";				//6
const char LE910_string_07[]	PROGMEM = "#GPRS";							//7
const char LE910_string_08[]	PROGMEM = "AT#TEMPMON=1\r";					//8
const char LE910_string_09[]	PROGMEM = "#TEMPMEAS: ";					//9
const char LE910_string_10[]	PROGMEM = "AT+CSQ\r\n: ,";					//10
const char LE910_string_11[]	PROGMEM = "AT#PSNT?\r";						//11
const char LE910_string_12[]	PROGMEM = "AT#HWREV\r";						//12
const char LE910_string_13[]	PROGMEM = "AT#CGMI\r";						//13
const char LE910_string_14[]	PROGMEM = "AT#CGMM\r";						//14
const char LE910_string_15[]	PROGMEM = "AT#CGMR\r";						//15
const char LE910_string_16[]	PROGMEM = "AT#CGSN\r";						//16
const char LE910_string_17[]	PROGMEM = "AT#CIMI\r";						//17
const char LE910_string_18[]	PROGMEM = "AT#CCID\r";						//18
const char LE910_string_19[]	PROGMEM = "AT+CMEE=1\r";					//19
const char LE910_string_20[]	PROGMEM = "ATE0\r";							//20
const char LE910_string_21[]	PROGMEM = "AT#NITZ=7\r";					//21
const char LE910_string_22[]	PROGMEM = "+CMTI";							//22
const char LE910_string_23[]	PROGMEM = "SRING: ";						//23
const char LE910_string_24[]	PROGMEM = "AT+COPS?\r";						//24
const char LE910_string_25[]	PROGMEM = "AT+CCLK?\r";						//25
const char LE910_string_26[]	PROGMEM = "AT#GPRS?\r";						//26
const char LE910_string_27[]	PROGMEM = "GPRS: 1";						//27
const char LE910_string_28[]	PROGMEM = "GPRS: 0";						//28
const char LE910_string_29[]	PROGMEM = "AT+CGDCONT=1,\"IP\",\"%s\"\r";	//29
const char LE910_string_30[]	PROGMEM = "AT%s\"%s\"\r";					//30
const char LE910_string_31[]	PROGMEM = "AT#GPRS=%u\r";					//31
const char LE910_string_32[]	PROGMEM = "+IP: \"\r\n";					//32
const char LE910_string_33[]	PROGMEM = "AT+CSQ\r\n: ,";					//33
const char LE910_string_34[]	PROGMEM = "AT#PSNT?: ,\r\n";				//34
const char LE910_string_35[]	PROGMEM = "%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%*c%2hhu%hhd\"";//35
const char LE910_string_36[]	PROGMEM = "AT+CMGL=\"REC UNREAD\"\r";		//36
const char LE910_string_37[]	PROGMEM = "AT#SA=%u,1\r";					//37
const char LE910_string_38[]	PROGMEM = "AT+WS46=%u\r";					//38
const char LE910_string_39[]	PROGMEM = "+CMGL: ";						//39
const char LE910_string_40[]	PROGMEM = "+CMGR: ";						//40
const char LE910_string_41[]	PROGMEM = "AT+CEREG?\r";					//41
const char LE910_string_42[]	PROGMEM = "+CEREG: 0,";						//42
const char LE910_string_43[]	PROGMEM = "AT+WS46?\r";						//43
const char LE910_string_44[]	PROGMEM = "AT#SHDN\r";						//44

const char* const table_4G[] PROGMEM =
{
	LE910_string_00,
	LE910_string_01,
	LE910_string_02,
	LE910_string_03,
	LE910_string_04,
	LE910_string_05,
	LE910_string_06,
	LE910_string_07,
	LE910_string_08,
	LE910_string_09,
	LE910_string_10,
	LE910_string_11,
	LE910_string_12,
	LE910_string_13,
	LE910_string_14,
	LE910_string_15,
	LE910_string_16,
	LE910_string_17,
	LE910_string_18,
	LE910_string_19,
	LE910_string_20,
	LE910_string_21,
	LE910_string_22,
	LE910_string_23,
	LE910_string_24,
	LE910_string_25,
	LE910_string_26,
	LE910_string_27,
	LE910_string_28,
	LE910_string_29,
	LE910_string_30,
	LE910_string_31,
	LE910_string_32,
	LE910_string_33,
	LE910_string_34,
	LE910_string_35,
	LE910_string_36,
	LE910_string_37,
	LE910_string_38,
	LE910_string_39,
	LE910_string_40,
	LE910_string_41,
	LE910_string_42,
	LE910_string_43,
	LE910_string_44,
};




/// table_PIN  /////////////////////////////////////////////////////////////////

const char LE910_PIN_00[]	PROGMEM = "AT+CPIN?\r";		//0
const char LE910_PIN_01[]	PROGMEM = "READY";			//1
const char LE910_PIN_02[]	PROGMEM = "SIM PIN";		//2
const char LE910_PIN_03[]	PROGMEM = "SIM PUK";		//3
const char LE910_PIN_04[]	PROGMEM = "PH-SIM PIN";		//4
const char LE910_PIN_05[]	PROGMEM = "PH-FSIM PIN";	//5
const char LE910_PIN_06[]	PROGMEM = "PH-FSIM PUK";	//6
const char LE910_PIN_07[]	PROGMEM = "SIM PIN2";		//7
const char LE910_PIN_08[]	PROGMEM = "SIM PUK2";		//8
const char LE910_PIN_09[]	PROGMEM = "PH-NET PIN";		//9
const char LE910_PIN_10[]	PROGMEM = "PH-NET PUK";		//10
const char LE910_PIN_11[]	PROGMEM = "PH-NETSUB PIN";	//11
const char LE910_PIN_12[]	PROGMEM = "PH-NETSUB PUK";	//12
const char LE910_PIN_13[]	PROGMEM = "PH-SP PIN";		//13
const char LE910_PIN_14[]	PROGMEM = "PH-SP PUK";		//14
const char LE910_PIN_15[]	PROGMEM = "PH-CORP PIN";	//15
const char LE910_PIN_16[]	PROGMEM = "PH-CORP PUK";	//16
const char LE910_PIN_17[]	PROGMEM = "+CPIN:";			//17
const char LE910_PIN_18[]	PROGMEM = "AT+CPIN=\"%s\"\r";	//18
const char LE910_PIN_19[]	PROGMEM = "AT+CPIN=\"%s\",\"%s\"\r";	//19

const char* const table_PIN[] PROGMEM =
{
	LE910_PIN_00,
	LE910_PIN_01,
	LE910_PIN_02,
	LE910_PIN_03,
	LE910_PIN_04,
	LE910_PIN_05,
	LE910_PIN_06,
	LE910_PIN_07,
	LE910_PIN_08,
	LE910_PIN_09,
	LE910_PIN_10,
	LE910_PIN_11,
	LE910_PIN_12,
	LE910_PIN_13,
	LE910_PIN_14,
	LE910_PIN_15,
	LE910_PIN_16,
	LE910_PIN_17,
	LE910_PIN_18,
	LE910_PIN_19,
};


/// table_SMS  /////////////////////////////////////////////////////////////////

const unsigned long LE910_SMS_TIMEOUT = 60000;		// Timeout for SMS functions in miliseconds

const char LE910_SMS_00[]	PROGMEM = "AT+CMGF=1\r";						//0
const char LE910_SMS_01[]	PROGMEM = "AT+CPMS=\"SM\",\"SM\",\"SM\"\r";		//1
const char LE910_SMS_02[]	PROGMEM = "AT+CNMI=2,1,0,0,0\r";				//2
const char LE910_SMS_03[]	PROGMEM = "AT+CMGR=%u\r";						//3
const char LE910_SMS_04[]	PROGMEM = "AT+CMGS=\"%s\"\r";					//4
const char LE910_SMS_05[]	PROGMEM = "AT+CMGD=%u\r";						//5
const char LE910_SMS_06[]	PROGMEM = "AT+CMGD=%u,%u\r";					//6
const char LE910_SMS_07[]	PROGMEM = "AT+CSMP=17,167,0,0\r";				//7

const char* const table_SMS[] PROGMEM =
{
	LE910_SMS_00,
	LE910_SMS_01,
	LE910_SMS_02,
	LE910_SMS_03,
	LE910_SMS_04,
	LE910_SMS_05,
	LE910_SMS_06,
	LE910_SMS_07,
};



/// table_HTTP  ////////////////////////////////////////////////////////////////

const unsigned long LE910_HTTP_TIMEOUT = 60000;		// Timeout for HTTP and HTTPS functions in miliseconds
const unsigned long LE910_HTTP_CONF_TIMEOUT = 15000;	// Timeout for HTTP and HTTPS functions in miliseconds

const char LE910_HTTP_00[]	PROGMEM = "AT#HTTPCFG=0,\"%s\",%u\r";			//0
const char LE910_HTTP_01[]	PROGMEM = "AT#HTTPQRY=0,%u,\"%s\"\r";			//1
const char LE910_HTTP_02[]	PROGMEM = "AT#HTTPSND=0,%u,\"%s\",%u,%s\r";		//2
const char LE910_HTTP_03[]	PROGMEM = "#HTTPRING: 0,";						//3
const char LE910_HTTP_04[]	PROGMEM = "AT#HTTPRCV=%u,%u\r";					//4
const char LE910_HTTP_05[]	PROGMEM = "/getpost_frame_parser.php";			//5
const char LE910_HTTP_06[]	PROGMEM = "frame=";								//6
const char LE910_HTTP_07[]	PROGMEM = "application/x-www-form-urlencoded";	//7
const char LE910_HTTP_08[]	PROGMEM = "text/plain";							//8
const char LE910_HTTP_09[]	PROGMEM = "application/octet-stream";			//9
const char LE910_HTTP_10[]	PROGMEM = "multipart/form-data";				//10

const char* const table_HTTP[] PROGMEM =
{
	LE910_HTTP_00,
	LE910_HTTP_01,
	LE910_HTTP_02,
	LE910_HTTP_03,
	LE910_HTTP_04,
	LE910_HTTP_05,
	LE910_HTTP_06,
	LE910_HTTP_07,
	LE910_HTTP_08,
	LE910_HTTP_09,
	LE910_HTTP_10,
};



/// table_FTP  /////////////////////////////////////////////////////////////////

const uint32_t LE910_FTP_TIMEOUT = 60000;		// Timeout for FTP and FTPS functions in miliseconds
const uint32_t LE910_FTP_CONF_TIMEOUT = 15000;	// Timeout for FTP and FTPS functions in miliseconds

const char LE910_FTP_00[]	PROGMEM = "AT#FTPOPEN=\"%s:%u\",\"%s\",\"%s\",%u\r";	// 0
const char LE910_FTP_01[]	PROGMEM = "AT#FTPCLOSE\r";					// 1
const char LE910_FTP_02[]	PROGMEM = "AT#FTPPUT=\"%s\",0\r";			// 2
const char LE910_FTP_03[]	PROGMEM = "AT#FTPGETPKT=\"%s\"\r";			// 3
const char LE910_FTP_04[]	PROGMEM = "AT#FTPTYPE=0\r";					// 4
const char LE910_FTP_05[]	PROGMEM = "AT#FTPFSIZE=\"%s\"\r";			// 5
const char LE910_FTP_06[]	PROGMEM = "AT#FTPRECV=%u\r";				// 6
const char LE910_FTP_07[]	PROGMEM = "#FTPMSG";						// 7
const char LE910_FTP_08[]	PROGMEM = "AT#FTPGETPKT?\r";				// 8
const char LE910_FTP_09[]	PROGMEM = "AT#FTPAPPEXT=%u\r";				// 9
const char LE910_FTP_10[]	PROGMEM = "#FTPGETPKT: %s,0,";				// 10
const char LE910_FTP_11[]	PROGMEM = "+++";							// 11
const char LE910_FTP_12[]	PROGMEM = "NO CARRIER";						// 12
const char LE910_FTP_13[]	PROGMEM = "#FTPRECV: ";						// 13
const char LE910_FTP_14[]	PROGMEM = "AT#FTPDELE=\"%s\"\r";			// 14
const char LE910_FTP_15[]	PROGMEM = "AT#FTPPWD\r";					// 15
const char LE910_FTP_16[]	PROGMEM = "AT#FTPLIST\r";					// 16
const char LE910_FTP_17[]	PROGMEM = "AT#FTPCWD=\"%s\"\r";				// 17

const char* const table_FTP[] PROGMEM =
{
	LE910_FTP_00,
	LE910_FTP_01,
	LE910_FTP_02,
	LE910_FTP_03,
	LE910_FTP_04,
	LE910_FTP_05,
	LE910_FTP_06,
	LE910_FTP_07,
	LE910_FTP_08,
	LE910_FTP_09,
	LE910_FTP_10,
	LE910_FTP_11,
	LE910_FTP_12,
	LE910_FTP_13,
	LE910_FTP_14,
	LE910_FTP_15,
	LE910_FTP_16,
	LE910_FTP_17,
};




/// table_IP  //////////////////////////////////////////////////////////////////

const uint32_t LE910_IP_TIMEOUT = 10000;		// Timeout for IP functions in miliseconds
const uint32_t LE910_IP_CONF_TIMEOUT = 15000;	// Timeout for IP functions in miliseconds

const char LE910_IP_SOCKET_00[]	PROGMEM = "AT#SS=%u\r";						//0
const char LE910_IP_SOCKET_01[]	PROGMEM = "AT#SI=%u\r";						//1
const char LE910_IP_SOCKET_02[]	PROGMEM = "AT#SCFG=%u,%u,%u,%u,%u,%u\r";	//2
const char LE910_IP_SOCKET_03[]	PROGMEM = "AT#SCFGEXT=%u,%u,%u,%u\r";		//3
const char LE910_IP_SOCKET_04[]	PROGMEM = "#SCFGEXT2=";						//4
const char LE910_IP_SOCKET_05[]	PROGMEM = "AT#SCFGEXT3=%u,1\r";				//5
const char LE910_IP_SOCKET_06[]	PROGMEM = "AT#SD=%u,%d,%u,\"%s\",0,%u,1\r";	//6
const char LE910_IP_SOCKET_07[]	PROGMEM = "AT#SH=%u\r";						//7
const char LE910_IP_SOCKET_08[]	PROGMEM = "AT#SSENDEXT=%u,%u\r";			//8
const char LE910_IP_SOCKET_09[]	PROGMEM = "#SRECV: %u,";					//9
const char LE910_IP_SOCKET_10[]	PROGMEM = "AT#SSLSECDATA=%u,%u,%u,%u\r";	//10
const char LE910_IP_SOCKET_11[]	PROGMEM = "AT#SSLSECDATA=%u,%u,%u\r";		//11
const char LE910_IP_SOCKET_12[]	PROGMEM = "AT#SSLD=1,%u,\"%s\",0,1\r";		//12
const char LE910_IP_SOCKET_13[]	PROGMEM = "AT#SSLS=%u\r";					//13
const char LE910_IP_SOCKET_14[]	PROGMEM = "AT#SSLSEND=%u\r";				//14
const char LE910_IP_SOCKET_15[]	PROGMEM = "AT#SSLRECV=%u,%u\r";				//15
const char LE910_IP_SOCKET_16[]	PROGMEM = "#SSLRECV: ";						//16
const char LE910_IP_SOCKET_17[]	PROGMEM = "TIMEOUT\r\n";					//17
const char LE910_IP_SOCKET_18[]	PROGMEM = "DISCONNECTED\r\n";				//18
const char LE910_IP_SOCKET_19[]	PROGMEM = "AT#SSLH=%u\r";					//19
const char LE910_IP_SOCKET_20[]	PROGMEM = "#SS: ";							//20
const char LE910_IP_SOCKET_21[]	PROGMEM = "#SS: ,\r\n";						//21
const char LE910_IP_SOCKET_22[]	PROGMEM = "#SSLS: ";						//22
const char LE910_IP_SOCKET_23[]	PROGMEM = "#SSLS: ,\r\n";					//23
const char LE910_IP_SOCKET_24[]	PROGMEM = "#SI: ";							//24
const char LE910_IP_SOCKET_25[]	PROGMEM = "#SI: ,\r\n";						//25
const char LE910_IP_SOCKET_26[]	PROGMEM = "AT#SRECV=%u,%u\r";				//26
const char LE910_IP_SOCKET_27[]	PROGMEM = "#SSLSECDATA: ";					//27
const char LE910_IP_SOCKET_28[]	PROGMEM = "AT#SCFGEXT=%u,%u,%u,%u,%u\r";	//28
const char LE910_IP_SOCKET_29[]	PROGMEM = "AT#SL=%u,%u,%u,%u\r";			//29
const char LE910_IP_SOCKET_30[]	PROGMEM = "AT#SLUDP=%u,%u,%u\r";			//30
const char LE910_IP_SOCKET_31[]	PROGMEM = "AT#SS\r";						//31
const char LE910_IP_SOCKET_32[]	PROGMEM = "#SS: %u,";						//32
const char LE910_IP_SOCKET_33[]	PROGMEM = "AT#SSLEN=%u,%u\r";				//33
const char LE910_IP_SOCKET_34[]	PROGMEM = "AT#SSLSECCFG=%u,%u,%u\r";		//34
const char LE910_IP_SOCKET_35[]	PROGMEM = "AT#SSLSECCFG2=%u,%u\r";			//35

const char* const table_IP[] PROGMEM =
{
	LE910_IP_SOCKET_00,
	LE910_IP_SOCKET_01,
	LE910_IP_SOCKET_02,
	LE910_IP_SOCKET_03,
	LE910_IP_SOCKET_04,
	LE910_IP_SOCKET_05,
	LE910_IP_SOCKET_06,
	LE910_IP_SOCKET_07,
	LE910_IP_SOCKET_08,
	LE910_IP_SOCKET_09,
	LE910_IP_SOCKET_10,
	LE910_IP_SOCKET_11,
	LE910_IP_SOCKET_12,
	LE910_IP_SOCKET_13,
	LE910_IP_SOCKET_14,
	LE910_IP_SOCKET_15,
	LE910_IP_SOCKET_16,
	LE910_IP_SOCKET_17,
	LE910_IP_SOCKET_18,
	LE910_IP_SOCKET_19,
	LE910_IP_SOCKET_20,
	LE910_IP_SOCKET_21,
	LE910_IP_SOCKET_22,
	LE910_IP_SOCKET_23,
	LE910_IP_SOCKET_24,
	LE910_IP_SOCKET_25,
	LE910_IP_SOCKET_26,
	LE910_IP_SOCKET_27,
	LE910_IP_SOCKET_28,
	LE910_IP_SOCKET_29,
	LE910_IP_SOCKET_30,
	LE910_IP_SOCKET_31,
	LE910_IP_SOCKET_32,
	LE910_IP_SOCKET_33,
	LE910_IP_SOCKET_34,
	LE910_IP_SOCKET_35,
};




/// table_GPS  /////////////////////////////////////////////////////////////////

const char LE910_GPS_00[]	PROGMEM = "AT$GPSP=%u\r";						//0
const char LE910_GPS_01[]	PROGMEM = "AT$GPSSLSR=%u,%u,,,,,%u\r";			//1
const char LE910_GPS_02[]	PROGMEM = "AT$GPSR=%u\r";						//2
const char LE910_GPS_03[]	PROGMEM = "$GPSGLO";							//3
const char LE910_GPS_04[]	PROGMEM = "AT$GPSACP\r";						//4
const char LE910_GPS_05[]	PROGMEM = "$GPSNMUN=3,";						//5
const char LE910_GPS_06[]	PROGMEM = "CONNECT\r\n";						//6
const char LE910_GPS_07[]	PROGMEM = "$GPGLL";								//7
const char LE910_GPS_08[]	PROGMEM = "$GPVTG";								//8
const char LE910_GPS_09[]	PROGMEM = "$GPGSA";								//9
const char LE910_GPS_10[]	PROGMEM = "$GPGGA";								//10
const char LE910_GPS_11[]	PROGMEM = "$GPRMC";								//11
const char LE910_GPS_12[]	PROGMEM = "$GPGSV";								//12
const char LE910_GPS_13[]	PROGMEM = "AT$GPSP?\r";							//13
const char LE910_GPS_14[]	PROGMEM = "GPSP: 1";							//14
const char LE910_GPS_15[]	PROGMEM = "$GPSACP: ,";							//15
const char LE910_GPS_16[]	PROGMEM = "\r\n$GPSACP: .,";					//16
const char LE910_GPS_17[]	PROGMEM = "AT$GPSNMUN=3,%u,%u,%u,%u,%u,%u\r";	//17
const char LE910_GPS_18[]	PROGMEM = "+++";								//18
const char LE910_GPS_19[]	PROGMEM = "AT$GPSQOS=%lu,%u,%u,%lu,%u,%u,%u\r";	//19
const char LE910_GPS_20[]	PROGMEM = "AT$SUPLV=%u\r";						//20
const char LE910_GPS_21[]	PROGMEM = "AT$SLP=1,\"supl.nokia.com:7275\"\r";	//21
const char LE910_GPS_22[]	PROGMEM = "AT$LCSTER=1,,,1\r";					//22
const char LE910_GPS_23[]	PROGMEM = "AT$LICLS=1\r";						//23
const char LE910_GPS_24[]	PROGMEM = "AT$LCSLK=1,1\r";						//24
const char LE910_GPS_25[]	PROGMEM = "AT$GPSGLO=1\r";						//25
const char LE910_GPS_26[]	PROGMEM = "AT#AGPSSND\r";						//26

const char* const table_GPS[] PROGMEM =
{
	LE910_GPS_00,
	LE910_GPS_01,
	LE910_GPS_02,
	LE910_GPS_03,
	LE910_GPS_04,
	LE910_GPS_05,
	LE910_GPS_06,
	LE910_GPS_07,
	LE910_GPS_08,
	LE910_GPS_09,
	LE910_GPS_10,
	LE910_GPS_11,
	LE910_GPS_12,
	LE910_GPS_13,
	LE910_GPS_14,
	LE910_GPS_15,
	LE910_GPS_16,
	LE910_GPS_17,
	LE910_GPS_18,
	LE910_GPS_19,
	LE910_GPS_20,
	LE910_GPS_21,
	LE910_GPS_22,
	LE910_GPS_23,
	LE910_GPS_24,
	LE910_GPS_25,
	LE910_GPS_26,
};




/// table_OTA_LE910 ////////////////////////////////////////////////////////////

const char LE910_OTA_00[]	PROGMEM = "/UPGRADE.TXT";	//0
const char LE910_OTA_01[]	PROGMEM = "NO_FILE";		//1
const char LE910_OTA_02[]	PROGMEM = "FILE:";			//2
const char LE910_OTA_03[]	PROGMEM = "PATH:";			//3
const char LE910_OTA_04[]	PROGMEM = "SIZE:";			//4
const char LE910_OTA_05[]	PROGMEM = "VERSION:";		//5

const char* const table_OTA_LE910[] PROGMEM =
{
	LE910_OTA_00,
	LE910_OTA_01,
	LE910_OTA_02,
	LE910_OTA_03,
	LE910_OTA_04,
	LE910_OTA_05,
};


/// table_EMAIL_LE910 ////////////////////////////////////////////////////////////

const char LE910_EMAIL_00[]	PROGMEM = "AT#ESMTP=\"%s\"\r";				//0
const char LE910_EMAIL_01[]	PROGMEM = "AT#EADDR=\"%s\"\r";				//1
const char LE910_EMAIL_02[]	PROGMEM = "AT#EUSER=\"%s\"\r";				//2
const char LE910_EMAIL_03[]	PROGMEM = "AT#EPASSW=\"%s\"\r";				//3
const char LE910_EMAIL_04[]	PROGMEM = "AT#EMAILD=\"%s\"\r";				//4
const char LE910_EMAIL_05[]	PROGMEM = "AT#SGACT=1,1,\"%s\",\"%s\"\r";	//5
const char LE910_EMAIL_06[]	PROGMEM = "#SGACT: ";						//6
const char LE910_EMAIL_07[]	PROGMEM = "AT#SMTPCFG=%u,%i\r";				//7
const char LE910_EMAIL_08[]	PROGMEM = "AT#EMAILD=\"%s\",\"%s\"\r";		//8
const char LE910_EMAIL_09[]	PROGMEM = "AT#ERST\r";						//9
const char LE910_EMAIL_10[]	PROGMEM = "AT#ESAV\r";						//10


const char* const table_EMAIL_LE910[] PROGMEM =
{
	LE910_EMAIL_00,
	LE910_EMAIL_01,
	LE910_EMAIL_02,
	LE910_EMAIL_03,
	LE910_EMAIL_04,
	LE910_EMAIL_05,
	LE910_EMAIL_06,
	LE910_EMAIL_07,
	LE910_EMAIL_08,
	LE910_EMAIL_09,
	LE910_EMAIL_10,
};



#endif
