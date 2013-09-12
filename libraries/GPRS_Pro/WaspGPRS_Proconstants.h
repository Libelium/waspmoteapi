/*
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.1
 *  Design:		David Gascón
 *  Implementation:	Alejandro Gállego
 */
  
 
#ifndef WaspGPRS_Proconstants_h
#define WaspGPRS_Proconstants_h

#include <inttypes.h> 

 
//!Module fuses
#define GSM_FUSE	1		//Call(audio included) and SMS related funtions and constants
#define HTTP_FUSE	1		//HTTP related funtions and constants
#define FTP_FUSE	1		//FTP related funtions and constants
#define IP_FUSE		1		//TCP and UDP related funtions and constants
#define OTA_FUSE	1		//OTA related funcions

#define GPRS_debug_mode 0

#define BUFFER_SIZE 256		// Never must be lower than 256B

#define	AT_COMMAND	"AT"
#define OK_RESPONSE "OK"

// Power Modes Constants
#define POWER_FULL		"+CFUN=1"
#define	POWER_RF_OFF	"+CFUN=4"
#define	POWER_MIN		"+CFUN=0"
#define POWER_NO_SLEEP	"+CSCLK=0"
#define POWER_SLEEP		"+CSCLK=2"

#define SET_TIME		 "+CCLK="

#define	AT_GPRS_APN		"apn"
#define	AT_GPRS_LOGIN	"user_name"
#define	AT_GPRS_PASSW	"password"

// SIM Constants
#define AT_PIN					"+CPIN="
#define AT_CHANGE_PASSWORD		"+CPWD="

// IMEI - IMSI Constants
#define AT_GPRS_IMEI "+GSN"
#define AT_GPRS_IMEI_R "+GSN"
#define AT_GPRS_IMSI "+CIMI"

#if GSM_FUSE
	// Calls Constants
	#define AT_CALL		"D" // Start phonecall, needs phone number
	#define AT_HANG		"H" // Hang phonecall, no parameters
	#define AT_DTMF		"+CLDTMF="

	// Voice Mode Constants
	#define	AT_ID_INCALL	"+CLIP=1"

	// SMS Constants
	#define AT_SMS			"+CMGS=" // Set phone number to send SMS to, needs phone number
	#define AT_SMS_R		">"
	#define AT_SMS_MODE		"+CMGF=1" // Select text mode for SMS
	#define	AT_SMS_INFO		"+CNMI=2,1,0,0,0"
	#define	AT_SMS_READ		"+CMGR=" // Needs index of sms to read
	#define AT_SMS_MEMORY	"+CPMS="
	#define	AT_SMS_MEMORY_R	"+CPMS: "	
	#define	AT_SMS_DELETE	"+CMGD=" // Needs index of sms to delete

	// Sound Constants
	#define AT_SOUND_INT	"#CAP=2" // Set internal audio path
	#define AT_SOUND_EXT	"#CAP=1" // Set external audio path
	#define AT_VOLUME_SET	"+CLVL=" // Set volume for selected audio path, needs number (min)0..10(MAX)

	#define AT_SPEAKER_VOLUME		"L"
	#define AT_SPEAKER_MODE			"M"
	#define AT_CLIP_MODE			"+CLIP="
	#define AT_CLIR_MODE			"+CLIR="
	#define AT_PHONE_ACTIVITY		"+CPAS"
	#define AT_PHONE_ACTIVITY_R		"+CPAS:"
	#define AT_ALERT_SOUND_MODE		"+CALM="
	#define AT_ALERT_SOUND_LEVEL	"+CALS="
	#define AT_RINGER_SOUND_LEVEL	"+CRSL="
	#define AT_SPEAKER_LEVEL		"+CLVL="
	#define AT_MUTE					"+CMUT="
#endif

// FTP_HTTP Constants
#define	AT_GPRS_CFG		"+SAPBR="
#define	AT_GPRS			"GPRS"
	
#if FTP_FUSE

	#define AT_FTP_WAIT_CONFIG	10
	#define AT_FTP_WAIT_CONNEC	60

	#define AT_FTP_ID			"+FTPCID="
	#define AT_FTP_PORT			"+FTPPORT="
	#define AT_FTP_MODE			"+FTPMODE"
	#define AT_FTP_TYPE			"+FTPTYPE="
	#define AT_FTP_SERVER		"+FTPSERV="
	#define AT_FTP_UN			"+FTPUN="
	#define AT_FTP_PW			"+FTPPW="
	#define AT_FTP_PUT			"+FTPPUT="
	#define AT_FTP_PUT_NAME		"+FTPPUTNAME="
	#define AT_FTP_PUT_PATH		"+FTPPUTPATH="
	#define AT_FTP_GET			"+FTPGET="
	#define AT_FTP_GET_NAME		"+FTPGETNAME="
	#define AT_FTP_GET_PATH		"+FTPGETPATH="
	#define AT_FTP_GET_SIZE 	"+FTPSIZE"
	#define AT_FTP_STATUS		"+FTPSTATE"

#endif

#if HTTP_FUSE
	#define AT_HTTP_INIT 		"+HTTPINIT"
	#define AT_HTTP_PARAM		"+HTTPPARA="
	#define AT_HTTP_ACTION		"+HTTPACTION=" 
	#define AT_HTTP_ACTION_R	"+HTTPACTION:0,200," 
	#define AT_HTTP_READ 		"+HTTPREAD"
	#define AT_HTTP_READ_R 		"+HTTPREAD:"
	#define AT_HTTP_TERM 		"+HTTPTERM"
#endif

#define	AT_GPRS_IP "0.0.0.0"

// TCP/UDP  constants
#if IP_FUSE
	#define	AT_IP					"IP"
	#define AT_SINGLE_CONN			"+CIPMUX=0"
	#define AT_MULTI_CONN			"+CIPMUX=1"
	#define AT_IP_STATUS			"+CIPSTATUS"
	#define AT_IP_STATUS_R			"STATE: "
	#define AT_IP_SET_APN			"+CSTT="
	#define AT_IP_BRING 			"+CIICR"
	#define AT_IP_GET_IP			"+CIFSR"
	#define AT_IP_APP_MODE 			"+CIPMODE="
	#define AT_IP_HEADER 			"AT+CIPHEAD=1"
	#define	AT_IP_CLIENT 			"+CIPSTART="
	#define AT_TCP					"TCP"
	#define AT_UDP					"UDP"
	#define AT_CONNECTED_OK			"CONNECT OK"
	#define AT_CONNECTED_FAIL		"CONNECT FAIL"
	#define	AT_IP_SERVER			"+CIPSERVER="
	#define AT_IP_SEND				"+CIPSEND"
	#define AT_IP_SEND_R			"SEND OK"
	#define AT_IP_SEND_FAIL			"SEND FAIL"	
	#define	AT_IP_CLOSE				"+CIPCLOSE="
	#define AT_IP_CLOSE_R			"CLOSE OK"
	#define	AT_IP_QCLOSE			"+CIPQRCLOSE="
	#define	AT_IP_SHUT				"+CIPSHUT"
	#define AT_IP_QUERY_DNS			"+CDNSGIP="
	#define AT_IP_QUERY_DNS_R		"+CDNSGIP:"
	#define AT_IP_LOCAL_PORT		"+CLPORT="
	#define AT_IP_SAVE_CONF			"+CIPSCONT"
	#define AT_IP_HEADER			"+CIPHEAD="
	#define AT_IP_AUTOSENDING		"+CIPATS="
	#define AT_IP_SHOW_REMOTE_IP	"+CIPSRIP="
	#define AT_IP_PROTOCOL_HEADER	"+CIPSHOWTP="
	#define AT_IP_DISCARD_AT_DATA	"+CIPTXISS="
	#define AT_IP_GET_MANUALLY		"+CIPRXGET"
	#define AT_IP_UDP_EXTENDED		"+CIPUDPMODE="
	#define AT_IP_CGATT				"+CGATT"
#endif

// OTA  constants
#if OTA_FUSE
	#define OTA_ver_file	"/UPGRADE.TXT"
	#define NO_OTA			"NO_FILE"
#endif

#define AT_COMMAND_MODE		"+++"
#define AT_DATA_MODE		"O"
#define AT_DATA_MODE_R		"CONNECT"
#define AT_DATA_MODE_FAIL	"NO CARRIER"

#define	AT_GPRS_CHECK		"+CGATT?"
#define	AT_GPRS_CHECK_ON	"+CGATT: 1"
#define	AT_GPRS_CHECK_OFF	"+CGATT: 0"	
#define	AT_GPRS_ATT_ON		"+CGATT=1"
#define	AT_GPRS_ATT_OFF		"+CGATT=0"
#define	AT_GPRS_CELLID		"+CENG"
#define AT_GPRS_RSSI		"+CSQ"

//Various
#define AT_GET_OPERATOR			"+COPS?"
#define AT_GET_OPERATOR_R		"+COPS:"
#define AT_SET_PREF_OPERATOR	"+COPS="
#define AT_OPERATOR_LIST		"+CPOL?"
#define AT_OPERATOR_LIST_R		"+CPOL:"
#define AT_WHO_AM_I				"+CGMM"
#define AT_FIRMWARE				"+CGMR"
#define AT_FIRMWARE_R			"Revision:"

#define AT_IP_SET_DNS	"+CDNSCFG="
#define	AT_GPRS_DNS1 	"80.58.0.33"
#define	AT_GPRS_DNS2	"80.58.32.97"

//Error Constants
#define ERROR_CME	"+CME ERROR:"
#define ERROR_CMS	"+CMS ERROR:"
#define ERROR		"ERROR"


#endif
