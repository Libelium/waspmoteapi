/*! 
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


#ifndef wifi_v3_constants_h
#define wifi_v3_constants_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <avr/pgmspace.h>
#include "wifi_error_codes.h"



/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

//! GLOBAL commands

static char WIFI_V3_OK[] 			= "OK";
static char WIFI_V3_ERROR[] 		= "ERROR";
static char WIFI_V3_CME_ERROR[] 	= "+CME ERROR";
static char WIFI_V3_READY[] 		= "READY";
static char WIFI_V3_CR_LF[] 		= "\r\n";
static char WIFI_V3_TCP_NOTIF[]		= "+KTCP_NOTIF: ";
static char WIFI_V3_TCP_DATA[]		= "+KTCP_DATA: ";
static char WIFI_V3_TCP_INCOMING[]	= "+KTCP_SRVREQ: ";
static char WIFI_V3_UDP_NOTIF[]		= "+KUDP_NOTIF: ";
static char WIFI_V3_UDP_DATA[]		= "+KUDP_DATA: ";
static char WIFI_V3_UDP_INCOMING[]	= "+KUDP_SRVREQ: ";
static char WIFI_V3_CONNECT[]		= "CONNECT";
static char WIFI_V3_MQTT_DATA[]		= "+KMQTT_DATA: ";
static char WIFI_V3_MQTT_IND[]		= "+KMQTT_IND: ";
static char WIFI_V3_HTTP_RES[]		= "HTTP/1.1 ";
static char WIFI_V3_MAC[]			= "+MACADDR: \"";
static char WIFI_V3_STATUS[]		= "+SRWSTASTATUS: ";
static char WIFI_V3_SRWAPSTA[]		= "+SRWAPSTA: ";
static char WIFI_V3_HTTP_ERROR[] 	= "+KHTTP_ERROR: ";	
static char WIFI_V3_HTTPS_ERROR[] 	= "+KHTTPS_ERROR: ";	

/******************************************************************************
 * COMMANDS (FLASH Definitions)
 ******************************************************************************/

const char str_wifi_v3_00[] PROGMEM	= "AT+RST\r";
const char str_wifi_v3_01[] PROGMEM	= "AT+CGMR\r";
const char str_wifi_v3_02[] PROGMEM	= "AT&F\r";
const char str_wifi_v3_03[] PROGMEM	= "AT+SRWCFG=%u,%u\r";
const char str_wifi_v3_04[] PROGMEM	= "AT+SRWSTACFG=%s,%s,%u\r";
const char str_wifi_v3_05[] PROGMEM	= "AT+SRWSTACON=%u\r";
const char str_wifi_v3_06[] PROGMEM	= "AT+SRWSTACON?\r";
const char str_wifi_v3_07[] PROGMEM	= "AT+SRWSTANETCFG=%u\r";
const char str_wifi_v3_08[] PROGMEM	= "AT+SRWSTANETCFG=%u,\"%s\"\r";
const char str_wifi_v3_09[] PROGMEM	= "AT+SRWSTANETCFG=%u,\"%s\",\"%s\"\r";
const char str_wifi_v3_10[] PROGMEM	= "AT+SRWSTANETCFG=%u,\"%s\",\"%s\",\"%s\"\r";
const char str_wifi_v3_11[] PROGMEM	= "AT+SRWAPCFG=%s,%s,%u,%u,%u\r";
const char str_wifi_v3_12[] PROGMEM	= "AT+SRWAPNETCFG=%u\r";
const char str_wifi_v3_13[] PROGMEM	= "AT+SRWAPNETCFG=%u,\"%s\",\"%s\",\"%s\",%u\r";
const char str_wifi_v3_14[] PROGMEM	= "AT+SRWSTADNSCFG=\"%s\"\r";
const char str_wifi_v3_15[] PROGMEM	= "AT+SRWSTADNSCFG=\"%s\",\"%s\"\r";
const char str_wifi_v3_16[] PROGMEM	= "AT+SRWSTADNSCFG=\"%s\",\"%s\",\"%s\"\r";
const char str_wifi_v3_17[] PROGMEM	= "AT+KPING=%s,%lu,%lu,%lu\r";
const char str_wifi_v3_18[] PROGMEM	= "AT+KTCPCFG=,%u,%s,%u\r";
const char str_wifi_v3_19[] PROGMEM	= "AT+KTCPCLOSE=%u,%u\r";
const char str_wifi_v3_20[] PROGMEM	= "AT+KTCPCNX=%u\r";
const char str_wifi_v3_21[] PROGMEM	= "AT+KTCPSND=%u,%s\r";
const char str_wifi_v3_22[] PROGMEM	= "AT+KTCPDEL=%u\r";
const char str_wifi_v3_23[] PROGMEM	= "AT+KTCPCFG?\r";
const char str_wifi_v3_24[] PROGMEM	= "AT+KHTTPCFG=0,%s,%u\r";
const char str_wifi_v3_25[] PROGMEM	= "AT+KHTTPCNX=%u\r";
const char str_wifi_v3_26[] PROGMEM	= "AT+KHTTPCLOSE=%u\r";
const char str_wifi_v3_27[] PROGMEM	= "AT+KHTTPGET=%u,%s\r";
const char str_wifi_v3_28[] PROGMEM	= "AT+KHTTPPOST=%u,%s\r";
const char str_wifi_v3_29[] PROGMEM	= "AT+KHTTPPUT=%u,%s\r";
const char str_wifi_v3_30[] PROGMEM	= "AT+KHTTPHEAD=%u,%s\r";
const char str_wifi_v3_31[] PROGMEM	= "AT+KHTTPDELETE=%u,%s\r";
const char str_wifi_v3_32[] PROGMEM	= "AT+KCERTSTORE=%u\r";
const char str_wifi_v3_33[] PROGMEM	= "AT+KCERTDELETE=%u\r";
const char str_wifi_v3_34[] PROGMEM	= "AT+KHTTPSCFG=0,%s,%u\r";
const char str_wifi_v3_35[] PROGMEM	= "AT+KHTTPSCNX=%u\r";
const char str_wifi_v3_36[] PROGMEM	= "AT+KHTTPSCLOSE=%u\r";
const char str_wifi_v3_37[] PROGMEM	= "AT+KHTTPSGET=%u,%s\r";
const char str_wifi_v3_38[] PROGMEM	= "AT+KHTTPSPOST=%u,%s\r";
const char str_wifi_v3_39[] PROGMEM	= "AT+KHTTPSPUT=%u,%s\r";
const char str_wifi_v3_40[] PROGMEM	= "AT+KHTTPSHEAD=%u,%s\r";
const char str_wifi_v3_41[] PROGMEM	= "AT+KHTTPSDELETE=%u,%s\r";
const char str_wifi_v3_42[] PROGMEM	= "AT+KMQTTCFG=%u,%s,%d,4,%s\r";
const char str_wifi_v3_43[] PROGMEM	= "AT+KMQTTCLOSE=%u\r";
const char str_wifi_v3_44[] PROGMEM	= "AT+KMQTTCNX=%u\r";
const char str_wifi_v3_45[] PROGMEM	= "AT+KMQTTDEL=%u\r";
const char str_wifi_v3_46[] PROGMEM	= "AT+KMQTTPUB=%u,%s,%u,%u,%s\r";
const char str_wifi_v3_47[] PROGMEM	= "AT+KMQTTPUBSTART=%u,%s,%u,%u,%s\r";
const char str_wifi_v3_48[] PROGMEM	= "AT+KMQTTSUB=%u,%s,%u\r";
const char str_wifi_v3_49[] PROGMEM	= "AT+KMQTTUNSUB=%u,%s\r";
const char str_wifi_v3_50[] PROGMEM	= "AT+KHTTPDEL=%u\r";
const char str_wifi_v3_51[] PROGMEM	= "AT+KHTTPSDEL=%u\r";
const char str_wifi_v3_52[] PROGMEM	= "AT+KUDPCFG=0,%u,%d\r";
const char str_wifi_v3_53[] PROGMEM	= "AT+KUDPCLOSE=%u\r";
const char str_wifi_v3_54[] PROGMEM	= "";
const char str_wifi_v3_55[] PROGMEM	= "AT+KUDPSND=%u,%s,%u,%s\r";
const char str_wifi_v3_56[] PROGMEM	= "AT+KUDPDEL=%u\r";
const char str_wifi_v3_57[] PROGMEM	= "AT+KUDPCFG?\r";
const char str_wifi_v3_58[] PROGMEM	= "AT+MACADDR?\r";
const char str_wifi_v3_59[] PROGMEM	= "/getpost_frame_parser.php?frame=";
const char str_wifi_v3_60[] PROGMEM	= "AT+SRWAPSTA?\r";
const char str_wifi_v3_61[] PROGMEM	= "AT+KTCPSTART=%u\r";

const char* const table_wifi_v3[] PROGMEM=
{
	str_wifi_v3_00, 
	str_wifi_v3_01,
	str_wifi_v3_02,
	str_wifi_v3_03,
	str_wifi_v3_04,
	str_wifi_v3_05,
	str_wifi_v3_06,
	str_wifi_v3_07,
	str_wifi_v3_08,
	str_wifi_v3_09,
	str_wifi_v3_10,
	str_wifi_v3_11,
	str_wifi_v3_12,
	str_wifi_v3_13,
	str_wifi_v3_14,
	str_wifi_v3_15,
	str_wifi_v3_16,
	str_wifi_v3_17,
	str_wifi_v3_18,
	str_wifi_v3_19,
	str_wifi_v3_20,
	str_wifi_v3_21,
	str_wifi_v3_22,
	str_wifi_v3_23,
	str_wifi_v3_24,
	str_wifi_v3_25,
	str_wifi_v3_26,
	str_wifi_v3_27,
	str_wifi_v3_28,
	str_wifi_v3_29,
	str_wifi_v3_30,
	str_wifi_v3_31,
	str_wifi_v3_32,
	str_wifi_v3_33,
	str_wifi_v3_34,
	str_wifi_v3_35,
	str_wifi_v3_36,
	str_wifi_v3_37,
	str_wifi_v3_38,
	str_wifi_v3_39,
	str_wifi_v3_40,
	str_wifi_v3_41,
	str_wifi_v3_42,
	str_wifi_v3_43,
	str_wifi_v3_44,
	str_wifi_v3_45,
	str_wifi_v3_46,
	str_wifi_v3_47,
	str_wifi_v3_48,
	str_wifi_v3_49,
	str_wifi_v3_50,
	str_wifi_v3_51,
	str_wifi_v3_52,
	str_wifi_v3_53,
	str_wifi_v3_54,
	str_wifi_v3_55,
	str_wifi_v3_56,
	str_wifi_v3_57,
	str_wifi_v3_58,
	str_wifi_v3_59,
	str_wifi_v3_60,
	str_wifi_v3_61,/*
	str_wifi_v3_62,
	str_wifi_v3_63,
	str_wifi_v3_64,
	str_wifi_v3_65,*/
};





#endif
