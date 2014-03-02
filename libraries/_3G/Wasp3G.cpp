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
  

#include <Wasp3G.h>
#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif



#define	AT_COMMAND	"AT"
#define OK_RESPONSE "OK"

#define	_3G_APN "apn"
#define	_3G_LOGIN "login"
#define	_3G_PASSW "password"

#define GSM_DCS_1800 		128
#define GSM_EGSM_900		256
#define GSM_PGSM_900		512
#define GSM_450				1
#define GSM_480				2
#define GSM_750				4
#define GSM_850				8
#define GSM_RGSM_900		16
#define GSM_PCS_1900		32
#define WCDMA_IMT_2000		64
#define WCDMA_PCS_1900		128
#define WCDMA_III_1700		256
#define WCDMA_IV_1700		512
#define WCDMA_850			1024
#define WCDMA_800			2048
#define WCDMA_VII_2600		1
#define WCDMA_VIII_900		2
#define WCDMA_IX_1700		4

//Error Constants
#define ERROR_IP 	"+IP ERROR:"
#define ERROR_CME 	"+CME ERROR:"
#define ERROR_CMS 	"+CMS ERROR:"
#define ERROR		"ERROR"

//Power constants
const char POWER_FULL[]			PROGMEM	= "+CFUN=1";		//0
const char POWER_RF_OFF[] 		PROGMEM	= "+CFUN=4";		//1
const char POWER_MIN[]			PROGMEM	= "+CFUN=0";		//2
const char POWER_OFF[]			PROGMEM	= "+CPOF";			//3
const char SET_TIME[]			PROGMEM	= "+CCLK=";			//4

const char AT_3G_CHECK[]		PROGMEM	= "+CGATT?";		//5
const char AT_3G_CHECK_ON[]		PROGMEM	= "+CGATT: 1";		//6
const char AT_3G_CHECK_OFF[]	PROGMEM	= "+CGATT: 0";		//7
const char AT_3G_ATT_ON[]		PROGMEM	= "+CGATT=1";		//8
const char AT_3G_ATT_OFF[]		PROGMEM	= "+CGATT=0";		//9

const char _3G_CON[] 			PROGMEM	= "+CGSOCKCONT=";	//10
const char _3G_AUTH[]			PROGMEM	= "+CSOCKAUTH=1,";	//11

//SIM constants
const char SET_PIN[] 			PROGMEM	= "+CPIN=";			//12
const char GET_IMEI[] 			PROGMEM	= "+SIMEI?";		//13
const char GET_IMEI_R[]			PROGMEM	= "+SIMEI: ";		//14
const char GET_IMSI[] 			PROGMEM	= "+CIMI";			//15

//File system functions
const char CHANGE_DIR[]			PROGMEM	= "+FSCD=";			//16
const char CHANGE_DIR_BACK[]	PROGMEM	= "+FSCD=..";		//17
const char CHANGE_DIR_R[]		PROGMEM	= "+FSCD:";			//18
const char FILE_ATTRIB[]		PROGMEM	= "+FSATTRI=";		//19
const char FILE_ATTRIB_R[]		PROGMEM	= "+FSATTRI: ";		//20
const char DEL_FILE[]			PROGMEM	= "+FSDEL=";		//21
const char MEM_SIZE[]			PROGMEM	= "+FSMEM";			//22
const char LIST_DIR[]			PROGMEM	= "+FSLS";			//23

//Extra!

const char GET_RSSI[]			PROGMEM	= "+CSQ";			//24
const char OPERATOR_SEL[]		PROGMEM	= "+COPS";			//25
const char PREF_MODE[]			PROGMEM	= "+CNMP";			//26
const char PREF_BAND[]			PROGMEM	= "+CNBP";			//27

const char ACQ_ORDER[]			PROGMEM	= "+CNAOP";			//28
const char PREF_SERV_DOM[]		PROGMEM	= "+CNSDP";			//29
const char INQ_UE_SYS[]			PROGMEM	= "+CPSI?";			//30
const char INQ_UE_SYS_R[]		PROGMEM	= "+CPSI: ";		//31
const char NETWORK_MODE[]		PROGMEM	= "+CNSMOD?";		//32
const char NETWORK_MODE_R[]		PROGMEM	= "+CNSMOD: ";		//33

const char CELL_SYS_INFO[]		PROGMEM	= "+CCINFO";		//34
const char CELL_CHN_INFO[]		PROGMEM	= "+CSCHN";			//35
const char CELL_RADIO_PARAM[]	PROGMEM	= "+CSRP";			//36
const char CELL_SET_SYS_INFO[]	PROGMEM	= "+CRUS";			//37
const char CELL_SET_SYS_INFO_R[] PROGMEM	= "+CRUS: ";	//38


const char CHN_SCAN_STR[]		PROGMEM	= "+CNSVS";			//39
const char CHN_SCAN_NUM[]		PROGMEM	= "+CNSVN";			//40
const char NET_START_SCAN[]		PROGMEM	= "Network survey started...";	//41

//Miscelaneus constants
const char STORE_LOCATION[]		PROGMEM	= "+FSLOCA=";		//42
const char CHANGE_BAUDRATE[]	PROGMEM	= "+IPR=";			//43
const char AUDIO_OUT[]			PROGMEM	= "+CSDVC=";		//44
const char MUTE_MIC[]			PROGMEM	= "+CMUT=";			//45
const char GAIN_MIC[]			PROGMEM	= "+CMIC=";			//46
const char GAIN_SPEAKER[]		PROGMEM	= "+CLVL=";			//47
const char MUTE_SPEAKER[]		PROGMEM	= "+VMUTE";			//48
const char LVL_SPEAKER[]		PROGMEM	= "+CLVL=";			//49
const char XMODEM_RECEIVE[]		PROGMEM	= "+CTXFILE";		//50

const char AT_WHO_AM_I[]		PROGMEM	= "+CGMM";			//51
const char FIRMWARE_VER[]		PROGMEM	= "+CGMR";			//52
const char FIRMWARE_VER_R[]		PROGMEM	= "+CGMR: ";		//53

	
const char* const table_MISC[] PROGMEM = 
{   
	//Power constants
	POWER_FULL,				//0
	POWER_RF_OFF,			//1
	POWER_MIN,				//2
	POWER_OFF,				//3
	SET_TIME,				//4

	//Connection constants
	AT_3G_CHECK,			//5
	AT_3G_CHECK_ON,			//6
	AT_3G_CHECK_OFF,		//7
	AT_3G_ATT_ON,			//8
	AT_3G_ATT_OFF,			//9
	_3G_CON,				//10
	_3G_AUTH,				//11

	//SIM constants
	SET_PIN,				//12
	GET_IMEI,				//13
	GET_IMEI_R,				//14
	GET_IMSI,				//15
	
	//File system functions
	CHANGE_DIR,				//16
	CHANGE_DIR_BACK,		//17
	CHANGE_DIR_R,			//18
	FILE_ATTRIB,			//19
	FILE_ATTRIB_R,			//20
	DEL_FILE,				//21
	MEM_SIZE,				//22
	LIST_DIR,				//23

	//Network constants
	GET_RSSI,				//24
	OPERATOR_SEL,			//25
	PREF_MODE,				//26
	PREF_BAND,				//27
	ACQ_ORDER,				//28
	PREF_SERV_DOM,			//29
	INQ_UE_SYS,				//30
	INQ_UE_SYS_R,			//31
	NETWORK_MODE,			//32
	NETWORK_MODE_R,			//33

	CELL_SYS_INFO,			//34
	CELL_CHN_INFO,			//35
	CELL_RADIO_PARAM,		//36
	CELL_SET_SYS_INFO,		//37
	CELL_SET_SYS_INFO_R,	//38

	CHN_SCAN_STR,			//39
	CHN_SCAN_NUM,			//40
	NET_START_SCAN,			//41

	//Miscelaneus constants
	STORE_LOCATION,			//42
	CHANGE_BAUDRATE,		//43
	AUDIO_OUT,				//44
	MUTE_MIC,				//45
	GAIN_MIC,				//46
	GAIN_SPEAKER,			//47
	MUTE_SPEAKER,			//48
	LVL_SPEAKER,			//49
	XMODEM_RECEIVE,			//50
	AT_WHO_AM_I,			//51
	FIRMWARE_VER,			//52
	FIRMWARE_VER_R,			//53
};



//Call and SMS constants
#if GSM_FUSE	
const char CALL[]			PROGMEM	= "D";				//0
const char LINE_ID[]		PROGMEM	= "+CLIP=1";		//1
const char HANG_CALL[]		PROGMEM	= "+CHUP";			//2
const char AUTO_ANSWER[]	PROGMEM	= "ATS0=";			//3
const char CALL_ASNWER[]	PROGMEM	= "ATA";			//4

const char TONE[]			PROGMEM	= "+CPTONE=";		//5
const char MUTE_RINGER[]	PROGMEM	= "+CALM=";			//6
const char LVL_RINGER[]		PROGMEM	= "+CRSL=";			//7
const char LINE_ID_PRES[]	PROGMEM	= "+CLIP=";			//8
const char LINE_ID_REST[]	PROGMEM	= "+CLIR=";			//9
const char PHONE_ACT[]		PROGMEM	= "+CPAS";			//10

const char SMS_MODE[]		PROGMEM	= "+CMGF=1";		//11
const char SEND_SMS[]		PROGMEM	= "+CMGS=";			//12
const char SMS_INFO[]		PROGMEM	= "+CNMI=2,1,0,0,0";//13
const char SMS_READ[]		PROGMEM	= "+CMGR=";			//14
const char SMS_READ_R[]		PROGMEM	= "+CMGR:";			//15
const char SMS_MEMORY[]		PROGMEM	= "+CPMS=";			//16
const char SMS_MEMORY_R[]	PROGMEM	= "+CPMS: ";		//17
const char SMS_DELETE[]		PROGMEM	= "+CMGD="; 		//18
	
const char* const table_GSM[] PROGMEM = 
{   
	CALL,			//0
	LINE_ID,		//1
	HANG_CALL,		//2
	AUTO_ANSWER,	//3
	CALL_ASNWER,	//4
	
	TONE,			//5
	MUTE_RINGER,	//6
	LVL_RINGER,		//7
	LINE_ID_PRES,	//8
	LINE_ID_REST,	//9
	PHONE_ACT,		//10
	
	SMS_MODE,		//11
	SEND_SMS,		//12
	SMS_INFO,		//13
	SMS_READ,		//14
	SMS_READ_R,		//15
	SMS_MEMORY,		//16
	SMS_MEMORY_R,	//17
	SMS_DELETE,		//18
};
#endif

//Camera constants
#if CAMERA_FUSE
	
	#define VH_PIN				ANA6 
	#define VL_PIN				DIGITAL1
	#define FILTER_ENABLE		DIGITAL3
	#define POWER_LED			DIGITAL8
	#define POWER_LED2			DIGITAL6
	#define SENS_IR				ANALOG1
	#define SENS_LDR			ANALOG3
	#define THRESHOLD_LIGHT_1	350
	#define THRESHOLD_LIGHT_2	150
	#define THRESHOLD_IR		400
	
const char CAM_START[]			PROGMEM	= "+CCAMS";			//0
const char CAM_STOP[]			PROGMEM	= "+CCAME";			//1
const char CAM_DIM[]			PROGMEM	= "+CCAMSETD=";		//2
const char RES_STAMP[]			PROGMEM	= "80,48";			//3
const char RES_QQVGA[]			PROGMEM	= "160,120";		//4
const char RES_QCIF[]			PROGMEM	= "176,144";		//5
const char RES_QVGA[]			PROGMEM	= "320,240";		//6
const char RES_CIF[]			PROGMEM	= "352,288";		//7
const char RES_VGA[]			PROGMEM	= "640,480";		//8
const char RES_XGA[]			PROGMEM	= "1024,768";		//9
const char CAM_FPS[]			PROGMEM	= "+CCAMSETF=";		//10
const char CAM_ROT[]			PROGMEM	= "+CCAMSETR=";		//11
const char CAM_NIGHT[]			PROGMEM	= "+CCAMSETN=";		//12
const char CAM_WHITE[]			PROGMEM	= "+CCAMSETWB=";	//13
const char CAM_BRIGHT[]			PROGMEM	= "+CCAMSETB=";		//14
const char CAM_ZOOM[]			PROGMEM	= "+CCAMSETZ=";		//15
//const char CAM_TAKE_PIC[]		PROGMEM	= "+CCAMTP"
const char CAM_TAKE_PIC[]		PROGMEM	= "+CCAMTPEXT=100";	//16
const char CAM_SAVE_PIC[]		PROGMEM	= "+CCAMEP";		//17
const char CAM_NAME_PIC[]		PROGMEM	= "+CCAMSETPN=";	//18
const char CAM_TIME_STAMP[]		PROGMEM	= "+CCAMAFT=";		//19
const char CAM_START_VIDEO[]	PROGMEM	= "+CCAMRS";		//20
const char CAM_PAUSE_VIDEO[]	PROGMEM	= "+CCAMRP";		//21
const char CAM_RESUME_VIDEO[]	PROGMEM	= "+CCAMRR";		//22
const char CAM_STOP_VIDEO[]		PROGMEM	= "+CCAMRE";		//23
const char CAMA_MODE[]			PROGMEM	= "+CCAMMD=";		//24
const char CAMA_CH[]			PROGMEM	= "+CCAMCHL=";		//25

const char CAM_NO_SENSOR[]		PROGMEM	= "CAMERA NO SENSOR";		//26
const char CAM_INVALID_STATE[]	PROGMEM	= "CAMERA INVALID STATE";	//27
const char CAM_NO_MEM[]			PROGMEM	= "CAMERA NO MEMORY";		//28
const char CAM_NO_START[]		PROGMEM	= "CAMERA NOT START";		//29
const char CAM_EP[]				PROGMEM	= "Picture/";				//30
const char CAM_EV[]				PROGMEM	= "Video/";					//31

//Videocall related constants
const char V_CALL_START[]		PROGMEM	= "+VPMAKE=";	//32
const char V_CALL_END[]			PROGMEM	= "+VPEND";		//33
const char V_DMTF[]				PROGMEM	= "+VPDTMF=";	//34
const char V_RECORD[]			PROGMEM	= "+VPRECORD=";	//35
const char V_QUALITY[]			PROGMEM	= "+VPQLTY=";	//36

const char V_ACCEPTED[]			PROGMEM	= "VPACCEPT";		//37
const char V_RECV[]				PROGMEM	= "VPRINGBACK";		//38
const char V_SETUP[]			PROGMEM	= "VPSETUP";		//39
const char V_CONNECTED[]		PROGMEM	= "VPCONNECTED";	//40
const char V_END[]				PROGMEM	= "VPEND";			//41
const char V_INCOMING[]			PROGMEM	= "VPINCOM";		//42
	
	
const char* const table_CAMERA[] PROGMEM = 
{   
	CAM_START,			//0
	CAM_STOP,			//1
	CAM_DIM,			//2
	RES_STAMP,			//3
	RES_QQVGA,			//4
	RES_QCIF,			//5
	RES_QVGA,			//6
	RES_CIF,			//7
	RES_VGA,			//8
	RES_XGA,			//9
	CAM_FPS,			//10
	CAM_ROT,			//11
	CAM_NIGHT,			//12
	CAM_WHITE,			//13
	CAM_BRIGHT,			//14
	CAM_ZOOM,			//15
	CAM_TAKE_PIC,		//16
	CAM_SAVE_PIC,		//17
	CAM_NAME_PIC,		//18
	CAM_TIME_STAMP,		//19
	CAM_START_VIDEO,	//20
	CAM_PAUSE_VIDEO,	//21
	CAM_RESUME_VIDEO,	//22
	CAM_STOP_VIDEO,		//23
	CAMA_MODE,			//24
	CAMA_CH,			//25
	
	CAM_NO_SENSOR,		//26
	CAM_INVALID_STATE,	//27
	CAM_NO_MEM,			//28
	CAM_NO_START,		//29
	CAM_EP,				//30
	CAM_EV,				//31
	
	//Videocall related constants
	V_CALL_START,	//32
	V_CALL_END,		//33
	V_DMTF,			//34
	V_RECORD,		//35
	V_QUALITY,		//36
	
	V_ACCEPTED,		//37
	V_RECV,			//38
	V_SETUP,		//39
	V_CONNECTED,	//40
	V_END,			//41
	V_INCOMING,		//42
};
#endif

//FTP constants
#if FTP_FUSE
	
const char FTP_SERVER[]				PROGMEM	= "+CFTPSERV=";			//0
const char FTP_PORT[]				PROGMEM	= "+CFTPPORT=";			//1
const char FTP_MODE[]				PROGMEM	= "+CFTPMODE=";			//2
const char FTP_TYPE[]				PROGMEM	= "+CFTPTYPE=";			//3
const char FTP_UN[]					PROGMEM	= "+CFTPUN=";			//4
const char FTP_PW[]					PROGMEM	= "+CFTPPW=";			//5
const char FTP_GET_FILE[]			PROGMEM	= "+CFTPGETFILE=";		//6
const char FTP_GET_FILE_RES[]		PROGMEM	= "+CFTPGETFILE: ";		//7
const char FTP_GET_FILE_SIO[]		PROGMEM	= "+CFTPGET=";			//8
const char FTP_GET_FILE_RES_SIO[]	PROGMEM	= "+CFTPGET: ";			//9
const char FTP_PUT_FILE[]			PROGMEM	= "+CFTPPUTFILE=";		//10
const char FTP_PUT_FILE_RES[]		PROGMEM	= "+CFTPPUTFILE: ";		//11
const char FTP_PUT_FILE_SIO[]		PROGMEM	= "+CFTPPUT=";			//12
const char FTP_PUT_FILE_RES_SIO[]	PROGMEM	= "+CFTPPUT: BEGIN";	//13


const char ACQUIRE_SSL_STACK[]		PROGMEM	= "+CFTPSSTART";		//14
const char RELEASE_SSL_STACK[]		PROGMEM	= "+CFTPSSTOP";			//15
const char FTPS_LOGIN[]				PROGMEM	= "+CFTPSLOGIN";		//16
const char FTPS_LOGOUT[]			PROGMEM	= "+CFTPSLOGOUT";		//17
const char FTPS_GET_FILE[]			PROGMEM	= "+CFTPSGETFILE=";		//18
const char FTPS_GET_FILE_RES[]		PROGMEM	= "+CFTPSGETFILE: ";	//19
const char FTPS_GET_FILE_SIO[]		PROGMEM	= "+CFTPSGET=";			//20
const char FTPS_GET_FILE_RES_SIO[]	PROGMEM	= "+CFTPSGET: ";		//21
const char FTPS_PUT_FILE[]			PROGMEM	= "+CFTPSPUTFILE=";		//22
const char FTPS_PUT_FILE_RES[]		PROGMEM	= "+CFTPSPUTFILE: ";	//23
const char FTPS_PUT_FILE_SIO[]		PROGMEM	= "+CFTPSPUT=";			//24
const char FTPS_PUT_FILE_RES_SIO[]	PROGMEM	= "+CFTPSPUT: BEGIN";	//25

const char FTP_LIST[]				PROGMEM	= "+CFTPLIST";			//26
const char FTP_LIST_RES[]			PROGMEM	= "+CFTPLIST: ";		//27
	

const char* const table_FTP[] PROGMEM = 
{   
	FTP_SERVER,				//0
	FTP_PORT,				//1
	FTP_MODE,				//2
	FTP_TYPE,				//3
	FTP_UN,					//4
	FTP_PW,					//5
	FTP_GET_FILE,			//6
	FTP_GET_FILE_RES,		//7
	FTP_GET_FILE_SIO,		//8
	FTP_GET_FILE_RES_SIO,	//9
	FTP_PUT_FILE,			//10
	FTP_PUT_FILE_RES,		//11
	FTP_PUT_FILE_SIO,		//12
	FTP_PUT_FILE_RES_SIO,	//13
	
	ACQUIRE_SSL_STACK,		//14
	RELEASE_SSL_STACK,		//15
	FTPS_LOGIN,				//16
	FTPS_LOGOUT,			//17
	FTPS_GET_FILE,			//18
	FTPS_GET_FILE_RES,		//19
	FTPS_GET_FILE_SIO,		//20
	FTPS_GET_FILE_RES_SIO,	//21
	FTPS_PUT_FILE,			//22
	FTPS_PUT_FILE_RES,		//23
	FTPS_PUT_FILE_SIO,		//24
	FTPS_PUT_FILE_RES_SIO,	//25
	FTP_LIST,				//26
	FTP_LIST_RES,			//27
};
#endif

//SMTP and POP3 constants
#if MAIL_FUSE
	
const char SMTP_SERVER[]	PROGMEM	= "+SMTPSRV=";		//0
const char SMTP_AUTH[]		PROGMEM	= "+SMTPAUTH=";		//1
const char SMTP_FROM[]		PROGMEM	= "+SMTPFROM=";		//2
const char SMTP_RCPT[]		PROGMEM	= "+SMTPRCPT=";		//3
const char SMTP_SUBJECT[]	PROGMEM	= "+SMTPSUB=";		//4
const char SMTP_BODY[]		PROGMEM	= "+SMTPBODY=";		//5
const char SMTP_ATTACH[]	PROGMEM	= "+SMTPFILE=";		//6
const char SMTP_SEND[]		PROGMEM	= "+SMTPSEND";		//7
const char SMTP_SEND_R[]	PROGMEM	= "+SMTP: SUCCESS";	//8

const char POP3_SERVER[]	PROGMEM	= "+POP3SRV";		//9
const char POP3_IN[]		PROGMEM	= "+POP3IN";			//10
const char POP3_OUT[]		PROGMEM	= "+POP3OUT";		//11
const char POP3_LIST[]		PROGMEM	= "+POP3LIST";		//12
const char POP3_LIST_R[]	PROGMEM	= "+POP3:";			//13
const char POP3_HEADER[]	PROGMEM	= "+POP3HDR=";		//14
const char POP3_GET[]		PROGMEM	= "+POP3GET=";		//15
const char POP3_DEL[]		PROGMEM	= "+POP3DEL=";		//16
const char POP3_SUCCESS[]	PROGMEM	= "+POP3: SUCCESS";	//17
	

const char* const table_MAIL[] PROGMEM = 
{   
	SMTP_SERVER,	//0
	SMTP_AUTH,		//1
	SMTP_FROM,		//2
	SMTP_RCPT,		//3
	SMTP_SUBJECT,	//4
	SMTP_BODY,		//5
	SMTP_ATTACH,	//6
	SMTP_SEND,		//7
	SMTP_SEND_R,	//8
	
	POP3_SERVER,	//9
	POP3_IN,		//10
	POP3_OUT,		//11
	POP3_LIST,		//12
	POP3_LIST_R,	//13
	POP3_HEADER,	//14
	POP3_GET,		//15
	POP3_DEL,		//16
	POP3_SUCCESS,	//17
};
#endif

//HTTP constants
#if HTTP_FUSE
	
const char HTTP_ACT[] 		PROGMEM	= "+CHTTPACT=";			//0
const char HTTP_ACT_REQ[]	PROGMEM	= "+CHTTPACT: REQUEST";	//1
const char HTTP_ACT_DATA[]	PROGMEM	= "+CHTTPACT: ";		//2

const char HTTPS_START[]	PROGMEM	= "+CHTTPSSTART";		//3
const char HTTPS_STOP[]		PROGMEM	= "+CHTTPSSTOP";		//4
const char HTTPS_OPEN[]		PROGMEM	= "+CHTTPSOPSE";		//5
const char HTTPS_CLOSE[]	PROGMEM	= "+CHTTPSCLSE";		//6
const char HTTPS_SEND[]		PROGMEM	= "+CHTTPSSEND";		//7
const char HTTPS_RCV[]		PROGMEM	= "+CHTTPSRECV=1";		//8
const char HTTPS_DATA[]		PROGMEM	= "+CHTTPSRECV: ";		//9


const char* const table_HTTP[] PROGMEM = 
{   
	HTTP_ACT,		//0
	HTTP_ACT_REQ,	//1
	HTTP_ACT_DATA,	//2

	HTTPS_START,	//3
	HTTPS_STOP,		//4
	HTTPS_OPEN,		//5
	HTTPS_CLOSE,	//6
	HTTPS_SEND,		//7
	HTTPS_RCV,		//8
	HTTPS_DATA,		//9
};
#endif

//GPS constants
#if GPS_FUSE
const char START_GPS[]			PROGMEM	= "+CGPS=1,";		//0
const char START_GPS_COLD[]		PROGMEM	= "+CGPSCOLD";		//1
const char START_GPS_HOT[]		PROGMEM	= "+CGPSHOT";		//2
const char STOP_GPS[]			PROGMEM	= "+CGPS=0";		//3
const char GPS_SERVER[]			PROGMEM	= "+CGPSURL=";		//4
const char A_GPS_INFO[]			PROGMEM	= "+CAGPSINFO:";	//5
const char GPS_INFO[]			PROGMEM	= "+CGPSINFO";		//6
const char GPS_INFO_R[]			PROGMEM	= "+CGPSINFO:";		//7
const char ENABLE_AUTO_GPS[]	PROGMEM	= "+CGPSAUTO=1";	//8
const char DISABLE_AUTO_GPS[]	PROGMEM	= "+CGPSAUTO=0";	//9


const char* const table_GPS[] PROGMEM = 
{   
	START_GPS,			//0
	START_GPS_COLD,		//1
	START_GPS_HOT,		//2
	STOP_GPS,			//3
	GPS_SERVER,			//4
	A_GPS_INFO,			//5
	GPS_INFO,			//6
	GPS_INFO_R,			//7
	ENABLE_AUTO_GPS,	//8
	DISABLE_AUTO_GPS,	//9
};
#endif

//TCP/UDP constants
#if IP_FUSE

	#define RETRIES				10
	#define DELAY_SEND			0
	
const char IP_OPEN[]			PROGMEM	= "+NETOPEN=";		//0
const char IP_CLOSE[]			PROGMEM	= "+NETCLOSE";		//1
const char IP_APP_MODE[]		PROGMEM	= "+CIPMODE=";		//2
const char GET_IP[]				PROGMEM	= "+IPADDR";		//3
const char GET_IP_R[]			PROGMEM	= "+IPADDR:";		//4

const char TCP_CONNECT[]		PROGMEM	= "+TCPCONNECT=";	//5
const char TCP_SEND[]			PROGMEM	= "+TCPWRITE=";		//6
const char UDP_SEND[]			PROGMEM	= "+UDPSEND=";		//7
const char IP_SERVER[]			PROGMEM	= "+SERVERSTART";	//8

const char MULTI_OPEN[]			PROGMEM	= "+CIPOPEN=";		//9
const char MULTI_SEND[]			PROGMEM	= "+CIPSEND=";		//10
const char MULTI_CLOSE[]		PROGMEM	= "+CIPCLOSE=";		//11
const char TCP_SEND_OK[]		PROGMEM	= "Send ok";		//12
const char UDP_SEND_OK[]		PROGMEM	= "+UDPSEND:";		//13

const char SERVER_LIST[]		PROGMEM	= "+LISTCLIENT";	//14
const char SERVER_LIST_R[]		PROGMEM	= "+LISTCLIENT: ";	//15
const char SERVER_OPEN_CLIENT[]	PROGMEM	= "+ACTCLIENT=";	//16
const char SERVER_CLOSE_CLIENT[] PROGMEM	= "+CLOSECLIENT=";	//17

const char CONFIGURE_IP[]		PROGMEM	= "+CIPCCFG=";		//18

const char IPFROMDOM[]			PROGMEM	= "+CDNSGIP";		//19
const char DOMFROMIP[]			PROGMEM	= "+CDNSGHNAME";	//20

const char IPDATAMODE[]			PROGMEM	= "O";				//21
const char IPDATAMODE_R[]		PROGMEM	= "CONNECT";		//22
const char IPDATAMODE_FAIL[]	PROGMEM	= "NO CARRIER";		//23
	
	
const char* const table_IP[] PROGMEM = 
{   
	IP_OPEN,				//0
	IP_CLOSE,				//1
	IP_APP_MODE,			//2
	GET_IP,					//3
	GET_IP_R,				//4
	
	TCP_CONNECT,			//5
	TCP_SEND,				//6
	UDP_SEND,				//7
	IP_SERVER,				//8
	
	MULTI_OPEN,				//9
	MULTI_SEND,				//10
	MULTI_CLOSE,			//11
	TCP_SEND_OK,			//12
	UDP_SEND_OK,			//13
	
	SERVER_LIST,			//14
	SERVER_LIST_R,			//15
	SERVER_OPEN_CLIENT,		//16
	SERVER_CLOSE_CLIENT,	//17
	
	CONFIGURE_IP,			//18
	
	IPFROMDOM,				//19
	DOMFROMIP,				//20
	
	IPDATAMODE,				//21
	IPDATAMODE_R,			//22
	IPDATAMODE_FAIL,		//23
	
};
#endif

// Transmission constants
#if TRANSMISSION_FUSE

	#define INITIAL_PACKET	0x64
	#define ID_PACKET		0x65
	#define DATA_PACKET		0x66
	#define ACK_PACKET		0x67
	#define END_PACKET		0x68

	#define ACK_ASCII	0x06
	#define NACK_ASCII	0x15
	#define OK_ASCII	0x04
	#define NOK_ASCII	0x18

	#define SENDING_RETRIES	3

#endif


#define OTA_ver_file	"/UPGRADE.TXT"
#define NO_OTA			"NO_FILE"

// Constructors ////////////////////////////////////////////////////////////////

Wasp3G::Wasp3G(){
	_pwrMode=_3G_ON;
	_baudRate=_3G_RATE;
	_socket=1;
	ready=0;
	IP_flags=0;
}


// Private Methods /////////////////////////////////////////////////////////////
/* getIfReady() - gets if 3G module is ready or not
 *
 * This function gets if 3G module is ready or not
 *
 * Returns nothing. It changes the value of 'ready'
*/
void Wasp3G::getIfReady(){
	uint8_t answer=0;

	printString( AT_COMMAND, _socket);
	printByte( '\r', _socket);
	printByte( '\n', _socket);
	delay(200);
	answer=waitForData("OK", 2, 0, 0);
	if(answer == 1)
	{
		ready=1;
	}
	else
	{
		ready=0;
	}
}

/* parse(const char*, const char*) - parses 'data_expected' into 'data' string
*
* Return '1' if data_expected is in data, '0' if not.
*/
uint8_t Wasp3G::parse(const char* data, const char* data_expected){
	
	int it=0;
	bool theSame=false;
	int cont=0;
	int cont2=0;
	int ok;
	
	while (data[it] != '\0')
	{
		it++;
	}
	
	while (cont < it)	
	{
		if (data[cont] == data_expected[cont2])
		{
			cont2=0;
			while (data_expected[cont2] != '\0')
			{
				if (data[cont+cont2] == data_expected[cont2])
				{    
					cont2++;
					ok=true; 
				}
				else
				{
					ok=false; 
					break;
				}
			}  
			if (ok)
			{
				return 1;
			} 
		}
		cont++;
		cont2=0;
	}	
	return 0;
}


/* check3Gconnection() - checks if 3G connection is attached or not 
 *
 * This function checks if 3G connection is  attached or not
 *
 * Returns '1' if attached, '2' if not attached and '0' if error
*/
uint8_t Wasp3G::check3Gconnection(){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[5])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[6])));
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[7])));
	return( sendCommand2(str_aux1, str_aux2, str_aux3));
}

uint8_t Wasp3G::getXModemCheckSum(uint8_t* data){
	
	uint8_t aux=0;
	
	for (int x=0; x < 128; x++)
	{
		aux+=data[x];
	}
	
	return aux;
	

}

// AT Comands ///////////////////////////////////////////////////////////////////
uint8_t Wasp3G::sendCommand1(const char* theText, const char* expectedAnswer){
    return sendCommand1(theText, expectedAnswer, DEFAULT_TIMEOUT, 0);
}

uint8_t Wasp3G::sendCommand1(const char* theText, const char* expectedAnswer, int MAX_TIMEOUT, int sendOnce){
    char* theCommand = (char*) calloc(100, sizeof(char));
	if ( theCommand == NULL )
	{
		return -1;
	}
	
	int timeout = 0;

    int length=sprintf(theCommand, "AT%s\r\n", theText);
    
	#if _3G_debug_mode>0
		USB.print(F("Sending command with 1 answer: "));
		USB.print(theCommand);
	#endif
	
	// try sending the command
	// wait for serial response
    timeout = 0;
    serialFlush(_socket);
    while ( !serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
	{
        if (!sendOnce || !timeout)
		{
            printString(theCommand, _socket);
        }
        delay(DELAY_ON_SEND);
        timeout++;
    };
	
	free(theCommand);
	
	int answer = waitForData( expectedAnswer, MAX_TIMEOUT, timeout, 0);
	
	#if _3G_debug_mode>0
		USB.print(F("Answer: "));
		USB.println(answer, DEC);
	#endif
	
    return answer;
}

uint8_t Wasp3G::waitForData(const char* expectedAnswer, int MAX_TIMEOUT, int timeout, int seconds){
	char* theCommand = (char*) calloc(100, sizeof(char));
	if ( theCommand == NULL )
	{
		return -1;
	}
	
	int theLength = 0;
	int it=0;
	bool theSame=false;	
	uint8_t first=1;
	uint8_t match=0;
		
	for (it = 0; it < 100; it++)
	{
		theCommand[it] = '\0';
	}

	while (expectedAnswer[theLength] != '\0') 
	{
		theLength++;
	}
	
	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}
		
	while (timeout < MAX_TIMEOUT)
	{
		while (!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
		{
			timeout++;
			delay(10);
		}
		
		while (serialAvailable(_socket) && !match)
		{
			if ( first )
			{
				for(it=0; it<theLength; it++)
				{
					theCommand[it]=serialRead(_socket);
					#if _3G_debug_mode>1
						USB.print(F("Command answer1.1: "));
						USB.print(char(theCommand[it]));
						USB.print(F(" "));
						USB.println(theCommand[it],HEX);
					#endif
					delay(20);
				}
				first=0;
			}
			it=0;
		
			if ( serialAvailable(_socket))
			{
				theSame=true;
				for(it=0; it<theLength ; it++)
				{
					if(theCommand[it] != expectedAnswer[it])
					{
						theSame= false;
						break;
					}
				}
				if( theSame )
				{
					match=1;
					free(theCommand);
					return 1;
				}
				else
				{
					for(it=0; it<theLength-1 ; it++)
					{
						theCommand[it]=theCommand[it+1];
					}
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer1: "));
						USB.println(theCommand);
					#endif
				}
			}
		}
	}
	
	free(theCommand);
	
	if ( match )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//functions with two answers
uint8_t Wasp3G::sendCommand2(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2){	
    return sendCommand2(theText, expectedAnswer1, expectedAnswer2, DEFAULT_TIMEOUT, 0);
}

uint8_t Wasp3G::sendCommand2(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2, int MAX_TIMEOUT, int sendOnce){
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;
	
    int timeout = 0;

    int length=sprintf(theCommand, "AT%s\r\n", theText); 
	
	#if _3G_debug_mode>0
		USB.print(F("Sending command with 2 answers: "));
		USB.print(theCommand);
	#endif

	// try sending the command
	// wait for serial response
    timeout = 0;
    serialFlush(_socket);
    while(!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
	{
        if (!sendOnce || !timeout)
		{
            printString(theCommand, _socket);
        }
        delay(DELAY_ON_SEND);
        timeout++;
    };

	free(theCommand);
	
    int answer= waitForData( expectedAnswer1, expectedAnswer2, MAX_TIMEOUT, timeout, 0);
	
    #if _3G_debug_mode>0
		USB.print(F("Answer: "));
		USB.println(answer, DEC);
	#endif
	
    return answer;
}

uint8_t Wasp3G::waitForData(const char* expectedAnswer1, const char* expectedAnswer2, int MAX_TIMEOUT, int timeout, int seconds){
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;
	
	for (int i = 0; i < 100; i++)
	{
		theCommand[i] = '\0';
	}

	int theLength1 = 0;
	int theLength2 = 0;
	int minLength;
	int maxLength;
	int it=0;
	bool theSame=false;	
	uint8_t first=1;
	int cont=0;
	int cont2=0;
	char aux;
	boolean ok;
	
	// Gets the maximum length and the minimum length of the 2 strings
	theLength1=strlen(expectedAnswer1);
	minLength=theLength1;
	maxLength=theLength1;
	
	theLength2=strlen(expectedAnswer2);
	if(minLength>theLength2)
	{
		minLength=theLength2;
	}
	if(maxLength<theLength2)
	{
		maxLength=theLength2;	
	}	
		
	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}
	
	while (timeout < MAX_TIMEOUT)
	{
		while (!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
		{
			timeout++;
			delay(10);
		}
		
		while (serialAvailable(_socket))
		{
			if ( first == 1 )	// Get data from serial port until 'minLength'
			{
				for (it = 0; it <= minLength; it++)
				{
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer2.1: "));
						USB.print(char(theCommand[it]));
						USB.print(F(" "));
						USB.println(theCommand[it],HEX);
					#endif
				}
				first=2;
			}
			else if (first == 2)	// Get data from serial port increasing the length of 'theCommand' from minLength to maxLength
			{
				if (serialAvailable(_socket))
				{
					minLength++;
					it=minLength;
					theCommand[minLength]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer2.2: "));
						USB.print(char(theCommand[it]));
						USB.print(F(" "));
						USB.println(theCommand[it],HEX);
					#endif
				}
				if (minLength == maxLength)
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
						theCommand[it]=theCommand[it+1];
					}
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer2: "));
						USB.println(theCommand);
					#endif
				}
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
			
			if (strstr(theCommand, expectedAnswer1) != NULL)
			{
				if ((expectedAnswer1 == ERROR_CME)||(expectedAnswer1 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 1;
			}
			
			  
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer2) != NULL)
			{
				if ((expectedAnswer2 == ERROR_CME)||(expectedAnswer2 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 2;
			}
  			
		}
	}
	
	free(theCommand);
	
	return 0;
}

// 3 answers
uint8_t Wasp3G::sendCommand3(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, int MAX_TIMEOUT, int sendOnce){
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;
	
    int timeout = 0;

    int length=sprintf(theCommand, "AT%s\r\n", theText);
	#if _3G_debug_mode>0
		USB.print(F("sending command with 3 answers: "));
		USB.print(theCommand);
	#endif
    

	// try sending the command
	// wait for serial response
    timeout = 0;
    serialFlush(_socket);
    while(!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
	{
        if (!sendOnce || !timeout)
		{
            printString(theCommand, _socket);
        }
        delay(DELAY_ON_SEND);
        timeout++;
    };
	
	free(theCommand);

    int answer= waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer3, MAX_TIMEOUT, timeout, 0);
	
    #if _3G_debug_mode>0
		USB.print(F("Answer: "));
		USB.println(answer, DEC);
	#endif
	    
    return answer;
}

uint8_t Wasp3G::waitForData(const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, int MAX_TIMEOUT, int timeout, int seconds){
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;
	
	uint8_t minLength;
	uint8_t maxLength;
	uint8_t theLength1;
	uint8_t theLength2;
	uint8_t theLength3;
	uint8_t it=0;
	bool theSame=false;	
	uint8_t first=1;
	uint8_t cont=0;
	uint8_t cont2=0;
	char aux;

	boolean ok;
	
	for (it = 0; it < 100; it++) // Initializes 'theCommand' string
	{
		theCommand[it] = '\0';
	}

	// Gets the maximum length and the minimum length of the 3 strings
	theLength1=strlen(expectedAnswer1);
	minLength=theLength1;
	maxLength=theLength1;
	
	theLength2=strlen(expectedAnswer2);
	if(minLength>theLength2)
	{
		minLength=theLength2;
	}
	if(maxLength<theLength2)
	{
		maxLength=theLength2;	
	}
	
	theLength3=strlen(expectedAnswer3);
	if(minLength>theLength3)
	{
		minLength=theLength3;
	}
	if(maxLength<theLength3)
	{
		maxLength=theLength3;	
	}
	
	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}
	
	while(timeout < MAX_TIMEOUT)
	{
		while (!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
		{
			timeout++;
			delay(10);
		}
		
		while (serialAvailable(_socket))
		{
			if ( first == 1 )	// Get data from serial port until 'minLength'
			{
				for (it = 0; it < minLength; it++)
				{
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer3.1: "));
						USB.print(char(theCommand[it]));
						USB.print(F(" "));
						USB.println(theCommand[it],HEX);
					#endif
				}
				first=2;
			}
			else if (first == 2)	// Get data from serial port increasing the length of 'theCommand' from minLength to maxLength
			{
				if (serialAvailable(_socket))
				{					
					it=minLength;
					theCommand[minLength]=serialRead(_socket);
					minLength++;
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer3.2: "));
						USB.print(char(theCommand[it]));
						USB.print(F(" "));
						USB.println(theCommand[it],HEX);
					#endif
				}
				if (minLength > maxLength)
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
						theCommand[it]=theCommand[it+1];
					}
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer3.3: "));
						USB.println(theCommand);
					#endif
				}
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
  
			if (strstr(theCommand, expectedAnswer1) != NULL)
			{
				if ((expectedAnswer1 == ERROR_CME)||(expectedAnswer1 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 1;
			}
			
			
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer2) != NULL)
			{

				if((expectedAnswer2 == ERROR_CME) || (expectedAnswer2 == ERROR_CMS) || (expectedAnswer2 == ERROR_IP))
				{
					#if _3G_debug_mode>0
						USB.print(F("special error"));
					#endif
					while (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					
					// Gets the length of the data string
					do{	
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if _3G_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 2;			
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer3) != NULL)
			{
				if((expectedAnswer3 == ERROR_CME) || (expectedAnswer3 == ERROR_CMS) || (expectedAnswer3 == ERROR_IP))
				{
					#if _3G_debug_mode>0
						USB.print(F("special error"));
					#endif
					while(serialRead(_socket)!=' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if _3G_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 3;

			}
			
			cont=0;
			cont2=0;
			ok=false;
  			
		}
	}
	
	free(theCommand);
	
	return 0;
}

//4 answers
uint8_t Wasp3G::sendCommand4(const char* theText,  const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, const char* expectedAnswer4, int MAX_TIMEOUT, int sendOnce) {
	
	
	char* theCommand = (char*) calloc(100,sizeof(char));
	if( theCommand==NULL ) return -1;
		
    int timeout = 0;

    int length=sprintf(theCommand, "AT%s\r\n", theText);
	
	#if _3G_debug_mode>0
		USB.print(F("send command with 4 answers: "));
		USB.print(theCommand);
	#endif
    

	// try sending the command
	// wait for serial response
    timeout = 0;
    serialFlush(_socket);
    while(!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
	{
        if (!sendOnce || !timeout)
		{
            printString(theCommand,_socket);
        }
        delay(DELAY_ON_SEND);
        timeout++;
    };

	free(theCommand);
	
    int answer= waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer3, expectedAnswer4, MAX_TIMEOUT, timeout, 0);
	
    #if _3G_debug_mode>0
		USB.print(F("Answer: "));
		USB.println(answer, DEC);
	#endif
	    
    return answer;
}

uint8_t Wasp3G::waitForData(const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, const char* expectedAnswer4, int MAX_TIMEOUT, int timeout, int seconds) {

	char* theCommand = (char*) calloc(100,sizeof(char));
	if ( theCommand == NULL )
	{
		return -1;
	}
	
	uint8_t minLength;
	uint8_t maxLength;
	uint8_t theLength1;
	uint8_t theLength2;
	uint8_t theLength3;
	uint8_t theLength4;
	uint8_t it=0;
	bool theSame=false;	
	uint8_t first=1;
	
	for (it = 0; it < 100; it++)
	{
		theCommand[it] = '\0';
	}
	
	uint8_t cont=0;
	uint8_t cont2=0;
	char aux;

	theLength1=strlen(expectedAnswer1);
	minLength=theLength1;
	maxLength=theLength1;
	
	theLength2=strlen(expectedAnswer2);
	if(minLength>theLength2)
	{
		minLength=theLength2;
	}
	if(maxLength<theLength2)
	{
		maxLength=theLength2;
	}
	
	theLength3=strlen(expectedAnswer3);
	if(minLength>theLength3)
	{
		minLength=theLength3;
	}
	if(maxLength<theLength3)
	{
		maxLength=theLength3;	
	}
	
	theLength3=strlen(expectedAnswer4);
	if (minLength>theLength4)
	{
		minLength=theLength4;	
	}
	if (maxLength<theLength4)
	{
		maxLength=theLength4;	
	}
	
	// if there is a heating time, then wait to see if you got
	// any data from the serial port
	while (seconds > 0)
	{
		delay(1000);
		seconds--;
	}
	while (timeout < MAX_TIMEOUT)
	{
		while (!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
		{
			timeout++;
			delay(10);
		}
		
		while ( serialAvailable(_socket))
		{
			if ( first == 1 )	// Get data from serial port until 'minLength'
			{
				for (it=0; it < minLength; it++)
				{
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer4.1: "));
						USB.print(char(theCommand[it]));
						USB.print(F(" "));
						USB.println(theCommand[it],HEX);
					#endif
				}
				first=2;
			}
			else if (first == 2)	// Get data from serial port increasing the length of theCommand from minLength to maxLength
			{
				if (serialAvailable(_socket))
				{
					minLength++;
					it=minLength;
					theCommand[minLength]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer4.2: "));
						USB.print(char(theCommand[it]));
						USB.print(F(" "));
						USB.println(theCommand[it],HEX);
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
					for (it=0; it <= maxLength ; it++)
					{
						theCommand[it]=theCommand[it+1];
					}
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						USB.print(F("Command answer4: "));
						USB.println(theCommand);
					#endif
				}
			}
			
			cont=0;
			cont2=0;
			boolean ok=false;

			if (strstr(theCommand, expectedAnswer1) != NULL)
			{
				if ((expectedAnswer1 == ERROR_CME)||(expectedAnswer1 == ERROR_CMS))
				{
					#if GPRS_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if GPRS_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 1;
			}

  
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer2) != NULL)
			{
	
				if ((expectedAnswer2 == ERROR_CME) || (expectedAnswer2 == ERROR_CMS) || (expectedAnswer2 == ERROR_IP))
				{
					#if _3G_debug_mode>0
						USB.print(F("special error"));
					#endif
					while (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if _3G_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 2;
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
			if (strstr(theCommand, expectedAnswer3) != NULL)
			{
				if ((expectedAnswer3 == ERROR_CME) || (expectedAnswer3 == ERROR_CMS) || (expectedAnswer3 == ERROR_IP))
				{
					#if _3G_debug_mode>0
						USB.print(F("special error"));
					#endif
					while (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if _3G_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				free(theCommand);
				return 3;
			}
			
			cont=0;
			cont2=0;
			ok=false;
			
			
  			if (strstr(theCommand, expectedAnswer4) != NULL)
			{
				if ((expectedAnswer4 == ERROR_CME)||(expectedAnswer4 == ERROR_CMS) || (expectedAnswer4 == ERROR_IP))
				{
					#if _3G_debug_mode>0
						USB.print(F("special error"));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					// Gets the length of the data string
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if _3G_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}	
				free(theCommand);
				return 4;
			}
  			
		}
	}
	free(theCommand);
	return 0;
}


// Public Methods //////////////////////////////////////////////////////////////

//Power functions
/* ON(void) - opens UART1 and powers the SIM5218 module
 *
 * It opens UART1 and powers the SIM5218 module
 *
 * Returns '1' on success , '0' if error and '-2' if error with CME error response.
*/
uint8_t Wasp3G::ON(){
	detachInterrupt(RXD1_PIN);
	detachInterrupt(TXD1_PIN);
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
	
	#if CAMERA_FUSE
		pinMode(VH_PIN,OUTPUT); // Configures pins for IR cut filter and LED light
		pinMode(VL_PIN,OUTPUT);
		pinMode(FILTER_ENABLE,OUTPUT);
		pinMode(POWER_LED,OUTPUT);
		pinMode(POWER_LED2,OUTPUT);
		digitalWrite(VH_PIN,HIGH);
		digitalWrite(VL_PIN,HIGH);
		digitalWrite(FILTER_ENABLE,HIGH);
		digitalWrite(POWER_LED,LOW);
		digitalWrite(POWER_LED2,LOW);
		pinMode(GPS_PW,OUTPUT);
		digitalWrite(GPS_PW,LOW);
	#endif
	
	#if _3G_debug_mode==1
		USB.println(F("Debug mode 1"));
	#endif
	#if _3G_debug_mode==2
		USB.println(F("Debug mode 2"));
	#endif
	

	return(setMode(_3G_ON));
}

/* begin(void) - initialize 3G module
 *
 * This function powers up the 3G module and open Serial Port at velocity selected by the user
 * By default, it will be at 115200bps
 *
 * Returns nothing
*/
void Wasp3G::begin(){
	Utils.setMuxSocket1();
	beginSerial(_baudRate, _socket);
}

/* close(void) - closes UART used by SIM5218 module
 *
 * This function closes UART used by SIM5218 module
 *
 * Returns nothing
*/
void Wasp3G::close(){
	closeSerial(_socket);
	Utils.setMux(MUX_TO_LOW, MUX_TO_LOW);
}

/* OFF(void) - closes UART1 and powers off the SIM5218 module
 *
 * This function closes UART1 and powers off the SIM5218 module
 *
 * Returns '1' on success and '0' if error
*/
uint8_t Wasp3G::OFF(){
	
	uint8_t answer;
	
    answer=setMode(_3G_POWER_OFF);
	
	close();
	
	if (RTC.isON == 2)
	{
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
	
	return(answer);
}

/* setMode(uint8_t) - Sets 3G Power Mode
 *
 * This function selects the active power mode among: ON, FULL, MINIMUM, OFFLINE and OFF.
 * SIM5218 will enter SLEEP mode automatically.
 *
 * It does not close the serial port, only sends the proper command to 3G module and send the power pulse.
 *
 * Returns '1' on success , '0' if error and '-2' if error with CME error response.
*/
uint8_t Wasp3G::setMode(uint8_t pwrMode){
	
	int8_t answer=0;
	uint8_t counter, global_counter;
	
	switch(pwrMode)
	{		
		case _3G_ON:
			
			if (_pwrMode == _3G_SLEEP)
			{
				begin();
			}

			pinMode(GPRS_PW, OUTPUT);
			digitalWrite(GPRS_PW, LOW);
			delay(200);
			digitalWrite(GPRS_PW, HIGH);
			getIfReady();
			#if _3G_debug_mode>0
				USB.print(F("Module status: "));
				USB.println(ready,DEC);
			#endif
			global_counter = 3;
			counter = 20;
			while ((ready == 0) && (global_counter > 0))
			{
				delay(500);
				getIfReady();
				#if _3G_debug_mode>0
					USB.print(F("Module status: "));
					USB.println(ready,DEC);
				#endif
				counter--;
				if (counter == 0)
				{
					#if _3G_debug_mode>0
						USB.println(F("Retry start"));
					#endif
					digitalWrite(GPRS_PW, LOW);
					delay(3000);
					digitalWrite(GPRS_PW, HIGH);
					counter = 20;
					global_counter--;
				}
			}
			
			if (global_counter != 0)
			{			
				// For all versions
				// Enables numeric error codes:
				sendCommand1("+CMEE=1",OK_RESPONSE);
				// Disables command echoes:
				sendCommand1("E0",OK_RESPONSE);
				
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[0])));
				answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			
				if (PWR.getBatteryLevel() < 20)
				{	
					USB.println(F("********************"));
					USB.println(F("Danger! Low battery!"));
					USB.println(F("********************"));
					answer = 3;
				}
			}
			else
			{
				answer = 0;
			}
			break;

		case _3G_FULL:
			if (_pwrMode == _3G_SLEEP)
			{
				#if _3G_debug_mode>0
					USB.println(F("Reactivating UART"));
				#endif
				begin();
			}
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[0])));
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			break;
			
		case _3G_RF_OFF:
			if (_pwrMode == _3G_SLEEP)
			{
				#if _3G_debug_mode>0
					USB.println(F("Reactivating UART"));
				#endif
				begin();
			}
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[1])));
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			break;

		case _3G_MINIMUM:
			if (_pwrMode == _3G_SLEEP)
			{
				#if _3G_debug_mode>0
					USB.println(F("Reactivating UART"));
				#endif
				begin();
			}
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[2])));
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			break;
			
		case _3G_SLEEP:
			//answer=sendCommand2(POWER_MIN, OK_RESPONSE, ERROR_CME);
			//close();
			
			closeSerial(_socket);
			answer = 1;
			break;
		
		case _3G_POWER_OFF:

			digitalWrite(GPRS_PW, LOW);
			delay(1000);
			if (sendCommand1("", OK_RESPONSE, 10, 0) == 0)
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
	}
	else if (answer > 1)
	{
		return -answer;
	}
	
	return answer;
}

/* getMode(void) - Gets 3G Power Mode
 *
 * This function gets the actual 3G Power Mode. Possible values are ON, FULL, MINIMUM, OFFLINE and OFF.
 *
 * Returns the power mode
*/
uint8_t	Wasp3G::getMode(){
	return	_pwrMode;
}

/* check(void) - Checks if 3G is connected to the network
 *
 * This function checks if 3G module is connected to the network. If not, it has no sense working with 3G.
 *
 * Returns '1' when connected and '0' if not
*/
int8_t Wasp3G::check(uint16_t time){
	
	unsigned long previous;
	int8_t answer;
	
	previous = millis();
	
	do{	
		// Sends the command and waits for the answer (0,1 for home network and 0,5 for roaming)
		answer = sendCommand2("+CREG?", "+CREG: 0,1", "+CREG: 0,5");
	}while ((answer == 0) && ((millis() - previous) < (time * 1000)));
	
	if ((answer == 0) || ((millis() - previous) > (time * 1000)))
	{
		return 0;
	}
	
	return 1;
}

/* setTime() - Sets time and date to 3G module from RTC
*
* Returns '1' on success , '0' if error and '-2' if error with CME error response.
*/
uint8_t Wasp3G::setTime(){
	
	bool RTC_ant=false;
	int8_t answer;
	
	RTC.ON();
	
	if (RTC.isON == 0) // Checks if the RTC is on
	{
		RTC_ant = true;
		RTC.ON();
	}
		
	RTC.getTime(); //Gets time from RTC
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[4])));
	sprintf( buffer_3G, "%s\"%02u/%02u/%02u,%02u:%02u:%02u+01\"", str_aux1, RTC.year, RTC.month, RTC.date, RTC.hour, RTC.minute, RTC.second);

	if (RTC_ant) // Powers off the RTC if before it was off
	{
		RTC.OFF();
	}
	
	answer = sendCommand2( buffer_3G, OK_RESPONSE, ERROR);
	
	if (answer == 2)
	{
		return -answer;
	}
	else
	{
		return answer;
	}
}

//SIM functions
/* setPIN(const char*) - sets PIN to the SIM
 *
 * This function sets the specified PIN to the SIM
 *
 * Returns '1' on success, '0' or '-3' if error and '-2' if error with CME code
*/
int8_t	Wasp3G::setPIN(const char* pin){
	
	int8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[12])));
	sprintf(buffer_3G, "%s%s", str_aux1, pin);
	answer=sendCommand3(buffer_3G, OK_RESPONSE, ERROR_CME, ERROR, 1000, 0);
	
	if (answer > 1)
	{
		return -answer;
	}
	
	return answer;
}

/* changePIN(const char*, const char*) - changes PIN number to the SIM
 *
 * This function changes the PIN number to the SIM
 *
 * Returns '1' on success, '0' if error and -1 if CME code are available
*/
uint8_t Wasp3G::changePIN(const char* old_pin, const char* new_pin){

	uint8_t answer=0;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[12])));
	sprintf(buffer_3G, "%s\"%s\",\"%s\"", str_aux1, old_pin, new_pin);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
	
	if (answer == 1)
	{
		return 1;
	}
	else if (answer == 2)
	{
		return -1;
	}
	
	return 0;
	
}

/* getIMEI() - gets the IMEI from the 3G module
 *
 * This function gets the IMEI from the SIM card. It stores the IMEI into 'IMEI' variable.
 *
 * Returns '1' on success and '0' if error
*/
int8_t Wasp3G::getIMEI(){

	int8_t answer,counter;
	unsigned long previous;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[13])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[14])));
	answer=sendCommand2(str_aux1, str_aux2, ERROR);
	
	if (answer == 1)
	{
		counter=0;
		do{
			previous=millis();
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) <= 2000));
			buffer_3G[counter]=serialRead(_socket);
			if ((buffer_3G[counter] != '\r') && (buffer_3G[counter] != '\n'))
			{
				counter++;
			}
		}while ((buffer_3G[counter] != '\r') && ((millis()-previous) <= 2000));
		
		if (buffer_3G[counter] == '\r')
		{
			buffer_3G[counter]='\0';
			return 1;
		}			
	}
	
	return 0;
		
}

/* getIMSI() - gets the IMSI from the SIM card
 *
 * This function gets the IMSI from the SIM card. It stores the IMSI into 'IMSI' variable.
 *
 * Returns '1' on success and '0' if error
*/
int8_t Wasp3G::getIMSI(){

	unsigned long previous=millis();
	int8_t counter=0;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[15])));
	sendCommand1(str_aux1, "\r\n");
	previous=millis();
	counter=0;
	do{
		previous=millis();
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000));
		buffer_3G[counter]=serialRead(_socket);
		if ((buffer_3G[counter] != '\r') && (buffer_3G[counter] != '\n'))
		{
			counter++;
		}
	}while ((((buffer_3G[counter] != '\r') && (buffer_3G[counter] != '\n')) || (counter == 0)) && ((millis()-previous) < 3000));
		
	if (buffer_3G[counter] == '\r')
	{
		buffer_3G[counter]='\0';
		return 1;
	}			
		
	return 0;
}



/* manageIncomingData() - manage incoming data from serial port, executing proper functions to store received data
 *
 * This function manages incoming data from serial port, executing proper functions to store received data
 *
 * Returns '1' for call, '2' for SMS, '3' for IP data and '0' for error or not data
*/
//Devuelve en buffer_3G
// Llamada --> Número de telefono; 
// SMS --> Indice del SMS
// IP --> Datos recibidos. IP_dir -->Dirección IP y puerto

int8_t	Wasp3G::manageIncomingData(){

	uint8_t a = 0; // counter and auxiliar variable
	unsigned long previous = 0;
	// waits for incoming data
	previous = millis();
	while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 20000));
	
	// reads data from input buffer
	previous = millis();
	while ( (millis()-previous) < 2000 )
	{
		while( (serialAvailable(_socket) != 0) && ((millis() - previous) < 2000) )
		{
			if (a < BUFFER_SIZE)
			{
				buffer_3G[a] = serialRead(_socket);
				#if _3G_debug_mode>0
					USB.print(char(buffer_3G[a]));
				#endif
				a++;
			}
			else
			{
				serialRead(_socket);
			}
		}
	}
	buffer_3G[a] = '\0';

	if (a > 0) // this if is conditionated by the fuses selected in Wasp3G.h
	{
		a = 0;
#if GSM_FUSE&&IP_FUSE	
		if (parse(buffer_3G, "+CLIP"))
		{
			readCall();
			a = 1;
		}
		else if (parse(buffer_3G, "+CMTI"))
		{
			a = incomingSMS();
			if(a != 0)
			{
				a = readSMS(a);
				a = 2;
			}
			else
			{
				a = 0;
			}
		}
		else if (parse(buffer_3G, "RECV FROM"))
		{
			readIPdata();
			a = 3;
		}
#endif
#if GSM_FUSE&&(~IP_FUSE)
		if (parse(buffer_3G, "+CLIP"))
		{
			readCall();
			a = 1;
		}
		else if (parse(buffer_3G, "+CMTI"))
		{
			a = incomingSMS();
			if(a != 0)
			{
				readSMS(a);
				a = 2;
			}
			else
			{
				a = 0;
			}
		}
#endif
#if (~GSM_FUSE)&&IP_FUSE
		if (parse(buffer_3G, "RECV FROM"))
		{
			readIPdata();
			a = 3;
		}
#endif
	}
	else
	{
		a = 0;
	}
	
	return a;
}

//GSM functions
#if GSM_FUSE
//Call functions
/* makeCall(const char*) - makes a call to the seleted telephone number
 *
 * This function makes a call to the given telephone number.
 *
 * Returns '1' on success, '0' if error and '-2' if no carrier
*/
int8_t Wasp3G::makeCall(const char* tlfNumber){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[0])));
	sprintf(buffer_3G, "%s%s;", str_aux1, tlfNumber);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, "NO CARRIER");
	
	if (answer == 2)
	{
		return -2;
	}
	
	return answer;	
}

/* makelostCall(const char*, uint8_t) - makes a lost call to the seleted telephone number
 *
 * This function makes a call to the given telephone number and its duration is specified by the other input.
 * After 'timeCall' seconds, hang the call up.
 *
 * Returns '1' on success, '0' if error and '-2' if no carrier
*/
int8_t Wasp3G::makeLostCall(const char* tlfNumber, uint8_t timeCall){

	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[0])));
	sprintf(buffer_3G, "%s%s;", str_aux1, tlfNumber);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, "NO CARRIER");
	
	if (answer == 1)
	{
		for (int a=0; a < timeCall ; a++)
		{
			delay(1000);
		}
		hangUp();
		return 1;
	}
	else if (answer == 2)
	{
		return -2;	
	}
	
	return answer;
}

/* setInfoIncomingCall() - set the info shown when an incoming call is received
 *
 * This function sets the info shown when an incoming call is received
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
 */
int8_t	Wasp3G::setInfoIncomingCall(){
	uint8_t answer=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[1])));
	answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
	
	if (answer == 2)
	{
		return -2;
	}
	
	return answer;
}

/* readCall(const char*) - set in 'buffer_3G' variable the tlf number of the incoming call
 *
 * This function sets in 'buffer_3G' variable the tlf number of the incoming call
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * Returns '1' on success and '0' if error
*/
int8_t	Wasp3G::readCall(){
	uint8_t a=0;
	uint8_t b=0;
	
	while ( (buffer_3G[a] != '"') && (a < 45) )
	{
		a++;
	}
	a++;
	if (a >= 45)
	{
		return 0;
	}
	while ( (buffer_3G[a] != '"') && (a < 45) && (b < 15) )
	{
		buffer_3G[b]=buffer_3G[a];
		a++;
		b++;
	}
    if ( b >= 15 )
	{
		buffer_3G[b-1]='\0';
	}
    else
	{
		buffer_3G[b]='\0';
	}
	return 1;
}

/* hangUp() - hangs the call up
 *
 * This function hangs all the active calls up.
 *
 * Returns '1' on success and '0' if error
*/
int8_t Wasp3G::hangUp(){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[2])));
	return (sendCommand1(str_aux1, OK_RESPONSE));

}

/* autoAnswer(uint8_t) - enables or disables the auto-answer function of the module
 *
 * This function enables or disables the auto-answer function of the module.
 *
 * If 'rings' is '0' disable auto answer.
 *
 * Returns '1' on success and '0' if error
*/
int8_t Wasp3G::autoAnswer(uint8_t rings){

	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[3])));
	sprintf(buffer_3G, "%s%s", str_aux1, rings);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* answerCall() - Answers an incoming call
 *
 * This function answers an incoming call
 *
 * Returns '1' on success, '0' if error and '-2' if there isn't a incoming call
*/
int8_t Wasp3G::answerCall(){
	
	uint8_t answer=0;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[4])));
	answer=sendCommand3(str_aux1, "BEGIN", "CONNECT", "NO CARRIER", 2000, 0);
	
	if (answer == 3)
	{
		return -2;
	}
	else if ((answer == 2) || (answer == 1))
	{
		return 1;
	}
	
	return 0;
}

/* generateTone(uint8_t) - Generates a DTMF tone
 *
 * This function generates a DTMF tone 
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::generateTone(uint8_t tone){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[5])));
	sprintf(buffer_3G, "%s%d", str_aux1, tone);
	return sendCommand1(buffer_3G, OK_RESPONSE);
}

/* ringerLevel(uint8_t) - Controls the ringer level of the loudspeaker
 *
 * This function controls the ringer level of the loudspeaker. 
 *
 * 'level' values: '0' for mute and '1' to '5' for volume level
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::ringerLevel(uint8_t level){
	
	uint8_t answer=0;
	
	if (level == 0)	// If level is '0' enables the silent mode
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[6])));
		sprintf(buffer_3G, "%s1", str_aux1);
		return sendCommand1(buffer_3G, OK_RESPONSE);
	}
	else // If level isn't '0' disables the silent mode and set the volume level
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[6])));
		sprintf(buffer_3G, "%s0", str_aux1);
		answer=sendCommand1(buffer_3G, OK_RESPONSE);
		if (answer == 1)
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[7])));
			sprintf(buffer_3G, "%s%d", str_aux1, level-1);
			return sendCommand1(buffer_3G, OK_RESPONSE);
		}
	}
	
	return 0;
}

/* setCLIPresentation(uint8_t) - Enables or disables the presentation of the incoming call 
 *
 * This function enables or disables the presentation of the incoming call
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
*/
int8_t Wasp3G::setCLIPresentation(uint8_t mode){
	
	int8_t answer=0;	
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[8])));
	sprintf(buffer_3G, "%s%u", str_aux1, mode);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
	
	if (answer == 2)
	{
		return -2;
	}
	return answer;
	
}

/* setCLIRestriction(uint8_t) - Restricts or enables the presentation of the CLI to the called party when originating a call.
 *
 * This function restricts or enables the presentation of the CLI to the called party when originating a call.
 *
 * Allowed modes DEFAULT_CLIR='0', INVOKE_CLIR='1' or SUPPRESS_CLIR='2'
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
*/
int8_t Wasp3G::setCLIRestriction(uint8_t mode){
	
	int8_t answer=0;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[9])));
	sprintf(buffer_3G, "%s%u", str_aux1, mode);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
	
	if (answer == 2)
	{
		return -2;
	}
	return answer;
	
}

/* getPhoneStatus() - Gets the phone activity status
 *
 *This function gets the phone activity status
 *
 *Return '0' for error, '1'= Ready, '2'= Unknown,'3'= Ringing, '4'= Call in progress
*/
int8_t Wasp3G::getPhoneActStatus(){
	
	int8_t answer=0;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[10])));
	answer=sendCommand1(str_aux1, "+CPAS: ");
	
	if (answer == 1)
	{
		answer=serialRead(_socket)-0x30;
		if (answer == 0)
		{
			answer=1;
		}
	}	
	return answer;
}

// SMS functions
/* setTextModeSMS() - set the text mode to the sms
 *
 * This function sets the text mode to the sms
 *
 * Returns '1' on success and '0' if error
 */
int8_t Wasp3G::setTextModeSMS(){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[11])));
	return (sendCommand1(str_aux1, OK_RESPONSE));
}

/* sendSMS(const char*, const char*) - sends an SMS to the specified number
 *
 * This function sends an SMS to the specified number.
 *
 *  Returns '1' on success,'0' if error and -2 if error with CMS error code available
*/
int8_t Wasp3G::sendSMS(const char* smsText, const char* tlfNumber){
	
	int8_t answer=0;

	setTextModeSMS();
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[12])));	
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, tlfNumber);
	
	answer=sendCommand2(buffer_3G, ">", ERROR_CMS);
	
	if (answer == 2)
	{
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	
	printString(smsText, _socket);
	printByte(0x1A, _socket);
	
	answer=waitForData( OK_RESPONSE, 10000, 0, 0);
	
	return answer;
}

/* setInfoIncomingSMS() - set the info shown when an incoming SMS is received
 *
 * This function sets the info shown when an incoming SMS is received
 *
 * Returns '1' on success, '0' if error, '-2' if error with CMS error code, '-3' if error setting the memory and '-4' if error setting the memory with CMS error code.
 */
int8_t Wasp3G::setInfoIncomingSMS(){
	
	uint8_t answer=0;
	
	setTextModeSMS();
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[13])));
	answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CMS);	
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[16])));
	sprintf(buffer_3G, "%s\"SM\",\"SM\",\"SM\"", str_aux1);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[17])));
	answer=sendCommand2(buffer_3G, str_aux1, ERROR_CMS);	
	if (answer == 0)
	{
		return -3;
	}
	else if (answer == 2)
	{
		return -4;
	}
	
	return 1;	
}

/* readSMS() - set in 'tlfIN' and 'sms' variables the tlf number and text of the incoming SMS
 *
 * This function sets in 'tlfIN' and 'buffer_3G' variables the tlf number and text of the incoming SMS
 *
 * Returns '1' on success and '0' if error
*/
int8_t Wasp3G::readSMS(uint8_t index){
	
	int8_t answer = 0;
	unsigned long previous;
	int counter = 0;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[14])));
	sprintf(buffer_3G, "%s%d", str_aux1, index-1);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[15])));
	answer = sendCommand2(buffer_3G, str_aux1, ERROR_CMS);
	
	if (answer == 1)
	{
		counter = 0;
		previous = millis();
		
		// reads up to the sender phone number
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000));
			if (serialRead(_socket) == '"'){
				counter++;
			}
		}while ((counter < 3) && ((millis() - previous) < 2000));
		
		// stores in 'tlfNumber' the sender phone number
		#if _3G_debug_mode>0
			USB.println(F("Phone number"));
		#endif
		counter = 0;		
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000));
			tlfNumber[counter] = serialRead(_socket);
			#if _3G_debug_mode>0
				USB.print(char(tlfNumber[counter]));
			#endif
			counter++;
		}while ((tlfNumber[counter-1] != '"') && ((millis() - previous) < 2000));		
		tlfNumber[counter-1] = '\0';
		
		// reads up to the message text
		counter = 0;		
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000));
			buffer_3G[0] = serialRead(_socket);
		}while ((buffer_3G[0] != '\n') && ((millis() - previous) < 2000));
		
		// stores the message text in 'buffer_3G'
		#if _3G_debug_mode>0
			USB.println(F(""));
			USB.println(F("SMS body"));
		#endif
		counter = 0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000));
			buffer_3G[counter] = serialRead(_socket);
			#if _3G_debug_mode>0
				USB.print(char(buffer_3G[counter]));
			#endif
			counter++;
		}while ((parse(buffer_3G, "OK\r\n") == 0) && ((millis() - previous) < 2000));
		buffer_3G[counter-6] = '\0';
		#if _3G_debug_mode>0
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

/* getTotalSMS(uint8_t ) - Gets the number of total SMS stored in the SIM
 *
 * This function gets the number of total SMS stored in the SIM
 *
 * Returns the number of SMS, '-1' if error or '-2' if error with CMS error code
*/
int8_t Wasp3G::getTotalSMS(){

	int8_t answer, count;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[16])));
	sprintf(buffer_3G, "%s\"SM\",\"SM\",\"SM\"", str_aux1);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[17])));
	answer=sendCommand2(buffer_3G, str_aux1, ERROR_CMS);
	
	if (answer == 1)
	{
		count=serialRead(_socket);
		answer=0;	
		
		// Gets the number of SMS in the memory
		do{
			answer*=10;
			answer+=count-0x30;
			count=serialRead(_socket);
		}while (count != ',');
		
		return answer;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	return -1;
}

/* deleteSMS(uint8_t ) - deletes a sms in the memory
 *
 * This function deletes a sms in the memory selected by sms_index
 *
 * Returns '1' on success, '0' if error and '-2' if error with CMS error code
*/
int8_t Wasp3G::deleteSMS(uint8_t sms_index){

	int8_t answer;
    
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[18])));
	sprintf(buffer_3G, "%s%u", str_aux1, sms_index);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CMS);

	if (answer == 1)
	{
		return 1;
	}
	else if (answer == 2)
	{
		return -2;
	}
	return 0;
}

/* incomingSMS(uint8_t ) - Gets the index of the incoming SMS
 *
 * This function gets the index of the incoming SMS
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * Returns the index of SMS, '0' if error
*/
int8_t Wasp3G::incomingSMS(){

	unsigned long previous;	
	int8_t aux, answer;
	int count;
	
	count = 0;	
	previous = millis();
	
	while((buffer_3G[count] != '\0') && (buffer_3G[count] != ',') && ((millis() - previous) < 1000))
	{
		count++;
	}
	
	if (((millis() - previous) < 1000) && (buffer_3G[count] != '\0'))
	{
		count++;
		answer = 0;	
		
		// Gets the number of SMS in the memory
		do{
			answer *= 10;
			answer += buffer_3G[count]-0x30;
			count++;
		}while (buffer_3G[count] != 0x0D);
		
		return answer;
	}	
	return 0;
}

#endif

//Camera functions
#if CAMERA_FUSE

/* startCamera(void) - initializes the camera connected to 3G module
 *
 * Returns '1' on success , '0' if error, '-2' if camera not detected, '-3' if camera is already started.
*/
int8_t Wasp3G::startCamera(){	
	
	int8_t answer;
	
	PWR.setSensorPower(SENS_3V3, SENS_ON); // Powers analog circuit of the camera
	selectFilter(1); // Enables IR cut filter
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[0])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[26])));
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[27])));
	answer=sendCommand3(str_aux1, OK_RESPONSE, str_aux2, str_aux3, 1000, 0);
	
	if (answer > 1)
	{
		return -answer;
	}
	
	return answer;
}

/* stopCamera(void) -stops the camera connected to 3G module
 *
 * Returns '1' on success , '0' if error, '-2' if camera not started
*/
int8_t Wasp3G::stopCamera(){	
	
	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[1])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));
	answer=sendCommand2(str_aux1, OK_RESPONSE, str_aux2, 1000, 0);
	
	if (answer > 1)
	{
		return -answer;
	}
	
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	
	return answer;
}

/* takePicture(void) - takes a picture and saves it.
 * 
 * 'buffer_3G' contains the picture name.
 *
 * Returns '1' on success, '0' if error, '-2' if camera not started,
 * '-3' if camera is in invalid state,'-4' if there isn't memory enough.
*/
int8_t Wasp3G::takePicture(){

	int8_t answer;
	int8_t count=2;	
	unsigned long previous;
	
	digitalWrite(FILTER_ENABLE, LOW);
	delay(500);	
	
	// Takes the picture	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[16])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[30])));
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[29])));
	strcpy_P(str_aux4, (char*)pgm_read_word(&(table_CAMERA[27])));
	strcpy_P(str_aux5, (char*)pgm_read_word(&(table_CAMERA[28])));
	//answer=sendCommand4(CAM_TAKE_PIC, OK_RESPONSE, CAM_NO_START, CAM_INVALID_STATE, CAM_NO_MEM, 200, 0);
	answer=sendCommand4(str_aux1, str_aux2, str_aux3, str_aux4, str_aux5, 200, 0);

	digitalWrite(FILTER_ENABLE, HIGH);
	
	/*if (answer > 1)
	{
		return -answer;
	}
	else if (answer == 0)
	{
		return 0;
	}
	return 1;

	// Saves the picture
	answer=sendCommand3(CAM_SAVE_PIC, CAM_EP, CAM_NO_START, CAM_INVALID_STATE, 200, 0);*/
	
	count=0;
	if(answer==1) // If answer is OK gets the name of the video and saves it in 'buffer_3G'
	{
		previous=millis();
		do{
			while (serialAvailable(_socket) == 0 );
			buffer_3G[count]=serialRead(_socket);
			count++;
		}while ((buffer_3G[count-1] != '\r') && ((millis()-previous) < 1000));
		buffer_3G[count-1] = '\0';
		return 1;
	}
	
	if (answer > 1)
	{
		return -answer;
	}
	else if (answer == 0)
	{
		return 0;
	}

}

/* startVideo() - Starts video capture
 * 
 *'buffer_3G' contains the picture name.
 *
 * Returns '1' on success , '0' if error, '-2' if camera not started,
 * '-3' if camera is in invalid state, '4' if there isn't memory enough
*/
int8_t Wasp3G::startVideo(){

	int8_t answer;
	uint8_t count;
	unsigned long previous;
	
	//autoLight();
	digitalWrite(FILTER_ENABLE, LOW);
	delay(200);
	
	// Starts capture video:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[20])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[31])));
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[29])));
	strcpy_P(str_aux4, (char*)pgm_read_word(&(table_CAMERA[27])));
	strcpy_P(str_aux5, (char*)pgm_read_word(&(table_CAMERA[28])));
	answer=sendCommand4(str_aux1, str_aux2, str_aux3, str_aux4, str_aux5, 1000, 0);
	
	count=0;
	if (answer == 1) // If answer is OK gets the name of the video and saves it in 'buffer_3G'
	{
		previous=millis();
		do{
			while (serialAvailable(_socket) == 0 );
			buffer_3G[count]=serialRead(_socket);
			count++;
		}while ((buffer_3G[count-1] != '\r') && ((millis()-previous) < 1000));
		buffer_3G[count-1] = '\0';
		return 1;
	}
	else if (answer > 1)
	{
		digitalWrite(FILTER_ENABLE, HIGH);		
		return -answer;
	}
	
	return 0;

}

/* pauseVideo() - Pauses video capture
 *
 * Returns '1' on success , '0' if error, '-2' if camera not started, '-3' if camera is in invalid state
*/
int8_t Wasp3G::pauseVideo(){
	
	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[21])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[27])));
	answer=sendCommand3(str_aux1, OK_RESPONSE, str_aux2, str_aux3, 1000, 0);
	
	if (answer > 1)
	{
		return -answer;
	}
	
	digitalWrite(FILTER_ENABLE, HIGH);
	
	return answer;
}

/* resumeVideo() - Resumes video capture
 *
 * Returns '1' on success , '0' if error, '-2' if camera not started, '-3' if camera is in invalid state
*/
int8_t Wasp3G::resumeVideo(){
	
	int8_t answer;
	
	digitalWrite(FILTER_ENABLE, LOW);
	delay(200);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[22])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[27])));
	answer=sendCommand3(str_aux1, OK_RESPONSE, str_aux2, str_aux3, 1000, 0);
	
	if (answer > 1)
	{
		digitalWrite(FILTER_ENABLE, HIGH);
		
		return -answer;
	}
	
	return answer;
}

/* stopVideo() - Stops video capture
 *
 * Returns '1' on success , '0' if error, '-2' if camera not started, '-3' if camera is in invalid state
*/
int8_t Wasp3G::stopVideo(){
	
	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[23])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[27])));
	answer=sendCommand3(str_aux1, OK_RESPONSE, str_aux2, str_aux3, 1000, 0);
	
	if (answer > 1)
	{
		return -answer;
	}
	
	digitalWrite(FILTER_ENABLE, HIGH);
	
	return answer;
}

/* cameraRotation(const char*) - Sets the camera rotation
 * 
 * Allowed values: "0" degrees, "90" degrees, "180" degrees and "270" degrees
 *
 * Returns '1' on success , '0' if error,'-2' if camera not started and '-3' if camera is in invalid state
*/
int8_t Wasp3G::cameraRotation(const char* rotation){
	
	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[11])));
	sprintf(buffer_3G, "%s%s", str_aux1, rotation);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[29])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[27])));
	answer=sendCommand3(buffer_3G, OK_RESPONSE, str_aux1, str_aux2, 1000, 0);
	
	if (answer > 1)
	{
		return -answer;
	}
	
	return answer;

}

/* cameraResolution(uint8_t) - Sets camera resolution
 * 
 * '0' for STAMP, '1' for QQVGA, '2' for QCIF, '3' for QVGA, '4' for CIF, '5' for VGA and '6' for XGA
 *
 * Returns '1' on success , '0' if error, '-2' if camera not detected and '-3' if camera not started
*/
int8_t Wasp3G::cameraResolution(uint8_t resolution){
	
	int8_t answer;
	
	switch(resolution)
	{
		case 0:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[3])));
			break;
		case 1:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[4])));
			break;
		case 2:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[5])));
			break;
		case 3:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[6])));
			break;
		case 4:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[7])));
			break;
		case 5:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[8])));
			break;
		case 6:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[9])));
			break;
		default:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[10])));
			break;
	}
	
	sprintf(buffer_3G, "%s%s", str_aux1, str_aux2);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[26])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));
	answer=sendCommand3(buffer_3G, OK_RESPONSE, str_aux1, str_aux2, 1000, 0);
	
	if (answer > 1)
	{
		return -answer;
	}
	
	return answer;

}

/* cameraFPS(uint8_t) - Sets FPS
 * 
 * Sets the Frames Per Second: '0' for 7.5 fps, '1' for 10 fps and '2' for 15 fps
 *
 * Returns '1' on success , '0' if error,'-2' if camera not started, '-3' if camera is in invalid state
*/
int8_t Wasp3G::cameraFPS(uint8_t fps){

	int8_t answer;
	uint8_t count;
	
	
	// Sets the frames per second
	count = 5;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[10])));
	sprintf(buffer_3G, "%s%u", str_aux1, fps);
	
	do{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[29])));
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[27])));
		answer = sendCommand3(buffer_3G, OK_RESPONSE, str_aux1, str_aux2, 1000, 0);
		if (answer == 2)
		{
			startCamera();
		}
		count--;
	}while ((answer == 2) && (count != 0));
	
	if (answer > 1)
	{
		return -answer;
	}
	
	return answer;
}

/* cameraBrightness(uint8_t) - Sets camera brightness
 * 
 * Allowed values: 0 to 6 (0 is the lowest, 6 is the highest)
 *
 * Returns '1' on success , '0' if error,'-2' if camera not started, '-3' if camera is in invalid state
*/
int8_t Wasp3G::cameraBrightness(uint8_t mode){
	
	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[14])));
	sprintf(buffer_3G, "%s%u", str_aux1, mode);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[29])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[27])));
	answer=sendCommand3(buffer_3G, OK_RESPONSE, str_aux1, str_aux2, 10, 0);

	if (answer != 1)
	{
		return -answer;
	}
	
	return answer;

}

/* pictureName(const char*) - sets picture name format
 * 
 * The length max for name is 20. 'name' is only a part of the whole name; the whole name is 'name'xxxx.  
 *
 * Returns '1' on success and '0' if error
*/
int8_t Wasp3G::pictureName(const char* name){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[18])));
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, name);

	return (sendCommand1(buffer_3G, OK_RESPONSE));
}

/* pictureTimeStamp(uint8_t) - adds date frame on the picture.
 * 
 * The function activates or deactivates to add date frame on the picture
 *
 * Returns '1' on success and '0' if error
*/
int8_t Wasp3G::pictureTimeStamp(uint8_t state){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[19])));
	sprintf(buffer_3G, "%s%d", str_aux1, state);

	return (sendCommand1(buffer_3G, OK_RESPONSE));

}
 
/* autoLevel(void) - Rotates the camera to take a not rotated picture
 *
 * This function reads the accelerometer and rorates the camera in the correct position
 *
 * Returns '1' if success, '0' if error, '-2' if error with the accelerometer 
 * and '-3'  if error with rotation function
*/
int8_t Wasp3G::autoLevel(void){

	int x_acc,y_acc;
	
	ACC.ON();
	// a little delay
	delay(50);
	
	if (ACC.check() == 0x32)
	{	 
		x_acc = ACC.getX();
		y_acc = ACC.getY();
		
		#if _3G_debug_mode>0
			USB.print(F("X value: "));
			USB.println(x_acc, DEC);
			USB.print(F("Y value: "));
			USB.println(y_acc, DEC);
		#endif
		
		ACC.OFF();
		
		if (abs(x_acc) > abs(y_acc))
		{
			if (x_acc >= 0)
			{
				if (cameraRotation("270") == 1)
				{
					return 1;
				}
				else
				{
					return -3;
				}
			}
			else
			{
				if (cameraRotation("90") == 1)
				{
					return 1;
				}
				else
				{
					return -3;
				}
			}
		
		}
		else 
		{
			if (y_acc >= 0)
			{
				if (cameraRotation("180") == 1)
				{
					return 1;
				}
				else
				{
					return -3;
				}
			}
			else
			{
				if (cameraRotation("0") == 1)
				{
					return 1;
				}
				else
				{
					return -3;
				}
			}
		}
	}
	else
	{
		ACC.OFF();
		return -2;
	}
	
	return 0;
	
}

/* powerIRLED(int8_t) - Powers the IR LEDs of the Video Camera Sensor Board
 * This function powers the IR LEDs of the Video Camera Sensor Board
 *
 * The input parameter is needed: '0' powers off all LEDs, '1' powers on block 1, '2' powers on block 2 and '3'powers all LEDs
 *
 * Returns nothing
*/
void Wasp3G::powerIRLED(int8_t blockIR){

	switch (blockIR){
		case 0:
			digitalWrite(POWER_LED, LOW);
			digitalWrite(POWER_LED2, LOW);
			break;
		case 1:
			digitalWrite(POWER_LED, HIGH);
			digitalWrite(POWER_LED2, LOW);
			break;
		case 2:
			digitalWrite(POWER_LED, LOW);
			digitalWrite(POWER_LED2, HIGH);
			break;
		case 3:
			digitalWrite(POWER_LED, HIGH);
			digitalWrite(POWER_LED2, HIGH);
			break;	
	}

}

/* autoLight(void) - Reads the value of a LDR sensor, turn on/off the IR LEDs and selects the IR filter position
 *
 * This function reads the value of a LDR sensor, turn on/off the IR LEDs and selects the IR filter position.
 * Threshold values are defined in Wasp3G_constants.h
 *
 * Returns nothing
*/
void Wasp3G::autoLight(void){

	int aux=analogRead(SENS_LDR);
	
	aux=analogRead(SENS_LDR);	
	
	#if _3G_debug_mode>0
		USB.print(F("LDR value: "));
		USB.println(aux,DEC);
	#endif
	
	if ((aux > THRESHOLD_LIGHT_2) && (THRESHOLD_LIGHT_1 > aux))
	{	
		#if _3G_debug_mode>0
			USB.println(F("Level 1"));
		#endif
		selectFilter(0);
		powerIRLED(1);
	}
	else if (aux < THRESHOLD_LIGHT_2)
	{
		#if _3G_debug_mode>0
			USB.println(F("Level 2"));
		#endif
		selectFilter(0);
		powerIRLED(3);
	}
	else
	{
		
		aux=analogRead(SENS_IR);
		aux=analogRead(SENS_IR);
		#if _3G_debug_mode>0
			USB.print(F("IR value: "));
			USB.println(aux,DEC);
		#endif
		
		if (THRESHOLD_IR < aux)
		{
			selectFilter(1);
			#if _3G_debug_mode>0
				USB.println(F("Level 0. IR filter disabled"));
			#endif
		}
		else
		{
			selectFilter(0);
			#if _3G_debug_mode>0
				USB.println(F("Level 0. IR filter enabled"));
			#endif
		}
		powerIRLED(0);
	}	
}

/*selectFilter(int8_t) - select a filter for the lens
 *
 * 'filter': '0' enables IR cut filter, '1' disables IR cut filter
 *
 * Returns nothing
*/
void Wasp3G::selectFilter(int8_t filter){

	if (filter == 1) // Enables IR cut filter
	{
		digitalWrite(VH_PIN, LOW);
		digitalWrite(VL_PIN, HIGH);
	}
	else if (filter == 0) // Disables IR cut filter
	{
		digitalWrite(VH_PIN, HIGH);
		digitalWrite(VL_PIN, LOW);
	}
}

/*enablePIRInterrupt() - Enables the interrupt generated by the PIR
 *
 * Returns nothing
*/
void Wasp3G::enablePIRInterrupt(void){

	// Powers off the mux of UART1 to enters in sleep mode:
	close();
	
	// Powers on the PIR
	pinMode(GPS_PW,OUTPUT);
	digitalWrite(GPS_PW,HIGH);
	pinMode(PIR_3G_PIN_MON,INPUT);
	delay(3000);
	
	// Waits for PIR
	while (digitalRead(PIR_3G_PIN_MON) == 1);
	delay(1000);
	enableInterrupts(PIR_3G_INT);
	intFlag &= ~(PIR_3G_INT);
}

/*disablePIRInterrupt(int8_t) - Disables the interrupt generated by the PIR
 *
 * This function disables the interrupt generated by the PIR and activates/deactivates the PIR.
 *
 * Returns nothing
*/
void Wasp3G::disablePIRInterrupt(int8_t PIRstate){

	
	disableInterrupts(PIR_3G_INT);
	
	begin();
	
	if (PIRstate == 1)
	{
		pinMode(PIR_3G_PIN_MON,OUTPUT);
		digitalWrite(PIR_3G_PIN_MON,LOW);
	}
	else
	{
		digitalWrite(GPS_PW,LOW);
		pinMode(PIR_3G_PIN_MON,OUTPUT);
		digitalWrite(PIR_3G_PIN_MON,LOW);
	}
	
	intFlag &= ~(PIR_3G_INT);
	//while (getIfReady() == 0);
    Utils.setMuxSocket1();
	ready=1;
	//while (ready == 0);
}
 
/* makeVideoCall(const char*, int8_t) - Makes a videocall
 *
 * This function makes a videocall
 *
 * Returns '1' if success, '0' if error, '-1' if error connecting to the other party, '-2' if error with setup or the other party hangs the call 
 * '-3'  if error connecting the videocall and '-4' if error recording the call (videocall is active)
*/
int8_t Wasp3G::makeVideoCall(const char* phone_number, int8_t record){

	int answer;
	
	PWR.setSensorPower(SENS_3V3, SENS_ON);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[32])));
	sprintf(buffer_3G, "%s%s", str_aux1, phone_number);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[37])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[41])));
	answer = sendCommand2(buffer_3G, str_aux1, str_aux2);
	if (answer != 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));
		sendCommand1(str_aux1, OK_RESPONSE);
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return 0;
	}
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[38])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[41])));
	answer = waitForData(str_aux1, str_aux2, 3000, 0, 0);
	if (answer == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));
		sendCommand1(str_aux1, OK_RESPONSE);
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return -1;
	}
	else if (answer == 2)
	{
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return -1;
	}
	
	answer = waitForData(V_SETUP, V_END, 3000, 0, 0);
	if (answer == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));
		sendCommand1(str_aux1, OK_RESPONSE);
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return -2;
	}
	else if (answer == 2)
	{
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return -2;
	}
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[40])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[41])));	
	answer = waitForData(str_aux1, str_aux2, 3000, 0, 0);
	if (answer == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));
		sendCommand1(str_aux1, OK_RESPONSE);
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return -3;
	}
	else if (answer == 2)
	{
		return -3;
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[35])));
	sprintf(buffer_3G, "%s%d", str_aux1, record);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[37])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[41])));	
	answer = sendCommand2(buffer_3G, str_aux1, str_aux2);
	if (answer != 0)
	{
		return -4;
	}
	
	
	return 1;
}

/* hangVideoCall() - Hangs a videocall
 *
 * This function hangs a videocall
 *
 * Returns '1' if success, '0' if error
*/
int8_t Wasp3G::hangVideoCall(){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));
	if (sendCommand1(str_aux1, OK_RESPONSE) != 1)
	{
		return 0;
	}
		
	return 1;
}

/* VideoCallQuality(int8_t) - Sets the video quality 
 *
 * This function sets the video quality. 5 for high quality image or 15 for high motion profile.
 *
 * Returns '1' if success, '0' if error
*/
int8_t Wasp3G::VideoCallQuality(int8_t VideoQuality){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[36])));
	sprintf(buffer_3G, "%s%d", str_aux1, VideoQuality);
	if (sendCommand2(buffer_3G, OK_RESPONSE, ERROR) != 1)
	{
		return 0;
	}
		
	return 1;
}

/* VideoCallDMTF(const char*) - Sends DMTF tones
 *
 * This function sends DMTF tones
 *
 * Returns '1' if success, '0' if error
*/
int8_t Wasp3G::VideoCallDMTF(const char* DMTF_str){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[34])));
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, DMTF_str);
	if (sendCommand2(buffer_3G, OK_RESPONSE, ERROR) != 1)
	{
		return 0;
	}
		
	return 1;
}

#endif

//FTP functions
#if FTP_FUSE

/* configureFTP(const char*, const char*, const char*, const char*, uint8_t, const char*) - Configures the connection to the FTP server
 *
 * Configures the module with server name, port, user name, password, transmission type (ASCII or binary) and server mode (active or pasive)
 *
 * Returns '1' on success,'-2' if error setting the connection parameters (APN), '-3' if error setting the FTP server ('-13' if CME error available),
 * '-4' if error setting the FTP port ('-14' if CME error available), '-5' if error setting the FTP mode ('-15' if CME error available),
 * '-6' if error setting the FTP type ('-16' if CME error available), '-7' if error setting the user name ('-17' if CME error available),
 * '-8' if error setting the FTP password ('-18' if CME error available),
*/
int8_t Wasp3G::configureFTP(const char* server, const char* port, const char* user_name, const char* password, uint8_t mode, const char* type){
	
	int8_t answer;
	int8_t count;
	
	// Sets connection parameters (apn, user_name, password)
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));
	sprintf(buffer_3G, "%s1,\"IP\",\"%s\"", str_aux1, _3G_APN);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return -2;
	}
	
// Sets username and password	
	#ifdef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s1,\"%s\",\"%s\"", str_aux1, _3G_PASSW, _3G_LOGIN);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif
	
	// Sets username and password	
	#ifndef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s0", str_aux1);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif
	
		
	// Sets FTP server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[0])));
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, server);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count>0));
	if (count == 0)
	{
		if (answer == 2)
		{
			return -13;
		}
		else
		{
			return -3;
		}
	}
	
	// Sets FTP port
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[1])));
	sprintf(buffer_3G, "%s%s", str_aux1, port);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count>0));
	if (count == 0)
	{
		if(answer==2)
		{
			return -14;
		}
		else
		{
			return -4;
		}
	}
	
	// Sets FTP mode
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[2])));
	sprintf(buffer_3G, "%s%u", str_aux1, mode);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (count == 0)
	{
		if (answer == 2)
		{
			return -15;
		}
		else 
		{
			return -5;
		}
	}
	
	// Sets FTP type
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[3])));
	sprintf(buffer_3G, "%s%s", str_aux1, type);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (count == 0)
	{
		if (answer == 2)
		{
			return -16;
		}
		else
		{
			return -6;
		}
	}
	
	// Sets FTP user name
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[4])));
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, user_name);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (count ==  0)
	{
		if (answer == 2)
		{
			return -17;
		}
		else
		{
			return -7;
		}
	}
	
	// Sets FTP password
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[5])));
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, password);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (count == 0)
	{
		if (answer == 2) 
		{
			return -18;
		}
		else 
		{
			return -8;
		}
	}
	
	return 1;
	
}

/* uploadFile(uint8_t, const char*) - Uploads a file from 3G board to FTP server
 *
 * Origin values allowed:  0 – current directory, 1 – “C:/Picture” directory, 2 – “C:/Video” directory, 3 – “C:/VideoCall” directory,
 * 4 – “D:/Picture” directory, 5 – “D:/Video” directory, 6 – “D:/VideoCall” directory, 7 – “C:/Audio” directory, 8 – “D:/Audio” directory
 *
 * max_time is the total time in seconds to upload the file from the server
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME code (FTP error) and '-3' if error getting the file of the size to upload.
*/
int8_t Wasp3G::uploadFile(uint8_t origin, const char* destination_path){

	uint8_t answer;
	uint8_t count;
	unsigned long previous;
	long file_size;
	
	// first get the file size to calculates a aproximated upload time
	switch (origin)
	{
		case 1:
			goRoot(0);
			cd("Picture");
			break;
		case 2:
			goRoot(0);
			cd("Video");
			break;
		case 3:
			goRoot(0);
			cd("VideoCall");
			break;
		case 4:
			goRoot(1);
			cd("Picture");
			break;
		case 5:
			goRoot(1);
			cd("Video");
			break;
		case 6:
			goRoot(1);
			cd("VideoCall");
			break;
		case 7:
			goRoot(0);
			cd("Audio");
			break;
		case 8:
			goRoot(1);
			cd("Audio");
			break;
	}
	if ((strchr(destination_path, '/')) == NULL)
	{
		file_size = getFileSize(destination_path);
	}
	else
	{
		file_size = getFileSize(strchr(destination_path, '/'));
	}
	
	if (file_size == -2)
	{
		return -3;
	}
	
// First restart TCP/UDP connection:
	count=10;
	
	if (check3Gconnection() == 1) 
	{	
		// Dettachs 3G:
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[9])));
		do{
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			count--;
		}while ((count != 0) && (answer != 1));
		if (answer == 0)
		{	
			return -2;
		}
		else if (answer == 2)
		{
			return -10;
		}
	}
	
	// Now attaches connection:
	count=10;	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[8])));
	do{
		answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((count != 0) && (answer != 1));
	if (answer == 0)
	{	
		return -3;
	}
	else if (answer == 2)
	{
		return -11;
	}
	
	// Waits for connection:
	previous=millis();
	while ((check3Gconnection() != 1) && ((millis()-previous) < 30000))
	{
		delay(2000);
	}
	if ((millis() - previous) > 30000)
	{
		return -4;
	}

	
	// Send the file and selects the origin location
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[10])));
	sprintf(buffer_3G, "%s\"%s\",%u", str_aux1, destination_path, origin);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[11])));
	count = 3;
	do{
		answer=sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR, (file_size / 10) + 1000, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	
	
	if (count == 0)
	{
		if (answer == 2)	// If CME error code is available returns -2
		{
			return -2;
		}
		else
		{
			return 0;		// Error without code
		}
	}
	else
	{
		previous = millis();
		count = serialRead(_socket);	
		answer = 0;	
		
		// Gets the answer (a number in ASCII), if the number is 0 the transfer is OK, if is a number, it is an FTP error code
		do{
			answer *= 10;
			answer += count-0x30;
			count = serialRead(_socket);
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < (file_size / 10)));
		}while ((count != '\r') && ((millis() - previous) < (file_size / 10)));
		
		if (answer != 0)
		{
			CME_CMS_code = answer;
			return -2;
		}
	}
	
	return 1;
	
}

/* downloadFile(const char*, uint8_t, int) - Downloads a file from FTP server to 3G board
 *
 * Destination values allowed:  0 – current directory, 1 – “C:/Picture” directory, 2 – “C:/Video” directory, 3 – “C:/VideoCall” directory,
 * 4 – “D:/Picture” directory, 5 – “D:/Video” directory, 6 – “D:/VideoCall” directory, 7 – “C:/Audio” directory, 8 – “D:/Audio” directory
 *
 * max_time is the total time in seconds to download the file from the server
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME code (FTP error)
*/
int8_t Wasp3G::downloadFile(const char* origin_path, uint8_t destination, uint16_t max_time){

	uint8_t answer;
	uint8_t count;
		
	
	// Request the file and selects the destination location
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[6])));
	if (strchr(origin_path, '/') == strrchr(origin_path, '/'))
	{
		sprintf(buffer_3G, "%s\"%s\",%u", str_aux1, origin_path + 1, destination);	
	}
	else
	{
		sprintf(buffer_3G, "%s\"%s\",%u", str_aux1, origin_path, destination);	
	}
	
	count=3;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));
	do{
		answer=sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR, max_time*100, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	
	if(count == 0)
	{
		if (answer == 2)	// If CME error code is available returns -2
		{
			return -2;
		}
		else
		{
			return 0;		// Error without code
		}
	}
	else
	{
		count = serialRead(_socket);	
		answer = 0;	
		
		// Gets the answer (a number in ASCII), if the number is 0 the transfer is OK, if is a number, it is an FTP error code
		do{
			answer *= 10;
			answer += count - 0x30;
			count = serialRead(_socket);
			while(serialAvailable(_socket) == 0);
		}while (count != '\r');
		
		if(answer != 0)
		{
			CME_CMS_code = answer;
			return -2;
		}
	}
	
	return 1;
	
}

/* uploadData(const char*, const char*) - Uploads data from Waspmote to FTP server
 *
 * This function uploads data from Waspmote to FTP server
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME code (FTP error), '-3' if error getting file size from SD
*/
int8_t Wasp3G::uploadData(const char* SD_file, const char* FTP_destination_path){

	uint8_t answer;
	uint16_t count;
	long file_size;
	
	//Sends the command to send data	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[12])));
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, FTP_destination_path);
		
	count=3;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[13])));
	do{
		answer=sendCommand2(buffer_3G, str_aux1, ERROR_CME, 3000, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	
	if (count == 0)
	{
		if (answer == 2)	//If CME error code is available returns 2
		{
			return -2;
		}
		else
		{
			return 0;		//Error without code
		}
	}
	
	// Sends data trought SOCKET:
	else
	{	
		SD.ON();
		file_size = SD.getFileSize(SD_file);
		if (file_size == -1)
		{
			#if _3G_debug_mode>0
				USB.print(F("Error reading SD file size"));
			#endif 
			// Sends <CTRL+Z>:
			count=3;
			#if _3G_debug_mode>0
				USB.print(F("Sends CTRL+Z"));
			#endif
			printByte(0x1A, _socket);
			do{
				answer=waitForData(OK_RESPONSE, ERROR_CME, 1000, 0, 0);
				count--;
			}while ((answer != 1) && (count > 0));
			SD.OFF();
			return -3;
		}
		else
		{
			#if _3G_debug_mode>0
				USB.print(F("file size: "));
				USB.println(file_size,DEC);
			#endif
			count=0;
			do{
				if (file_size >= 250)
				{
					strncpy(buffer_3G, SD.cat(SD_file, count, 250), 250);
					buffer_3G[250]='\0';
					count+=250;
				}
				else
				{
					strncpy(buffer_3G, SD.cat(SD_file, count, (file_size - count)), (file_size - count));
					count=file_size;
					buffer_3G[count]='\0';
				}
				printString(buffer_3G,_socket);
				
				#if _3G_debug_mode>0
					USB.print(F("sended bytes: "));
					USB.println(count,DEC);
				#endif
			}while (count < file_size);
			
			SD.OFF();
			
			// Sends <CTRL+Z>:
			count=3;
			#if _3G_debug_mode>0
				USB.print(F("Sends CTRL+Z"));
			#endif
			printByte(0x1A, _socket);
			do{
				answer=waitForData(OK_RESPONSE, ERROR_CME, 1000, 0, 0);
				count--;
			}while ((answer != 1) && (count > 0));
			
			if (count == 0)
			{
				if (answer == 2)	// If CME error code is available returns 2
				{
					return -2;
				}
				else
				{
					return 0;		// Error without code
				}
			}
		}
	}
	
	return 1;
	
}

/* downloadData(const char*, const char*) - Downloads data from FTP server to Waspmote
 *
 * This function downloads data to Waspmote from FTP server
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME code (FTP error) and '-3' if error sending the file from 3G module to Waspmote's SD
*/
int8_t Wasp3G::downloadData(const char* FTP_file, const char* SD_destination_path, uint16_t max_time){

	uint8_t answer=1;
	uint16_t count, file_size;
	
	// Waspmote can't manage the incoming packets of 1KB from the 3G module
	// First downloads the file to the 3G module
	
	answer = downloadFile( FTP_file, 0, max_time);
	
	if (answer == 1)
	{
		//if the file have been downloaded correctly, it will be transferred to Waspmote SD
		if (strrchr(FTP_file,'/') == NULL)
		{
			answer = getXModemFile(FTP_file, SD_destination_path);
			del(FTP_file);
		}
		else
		{
			answer = getXModemFile((strrchr(FTP_file,'/')+1), SD_destination_path);
			//once the file is transferred, it deletes from the 3G module
			del(strrchr(FTP_file,'/')+1);
		}
		
		if (answer != 1)
		{
			return -3;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return answer;
	}
}



/* loginFPTS(const char*, uint16_t, const char*, const char*, uint8_t, const char*) - Acquires the SSL stack and logs into the FTPS server
 *
 * Acquires the SSL stack and logs into the FTPS server
 *
 * Returns '1' on success,'-2' if error setting the connection parameters (APN), '-3' if error acquiring the SSL stack, '-4' error login into the server,
 * '-5' if timeout when logs in
*/
int8_t Wasp3G::loginFPTS(const char* server, uint16_t port, const char* user_name, const char* password){
	
	int8_t answer;
	int8_t count;
	
	// Sets connection parameters (apn, user_name, password)
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));
	sprintf(buffer_3G, "%s1,\"IP\",\"%s\"", str_aux1, _3G_APN);
	count = 5;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return -2;
	}
	
// Sets username and password	
	#ifdef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s1,\"%s\",\"%s\"", str_aux1, _3G_PASSW, _3G_LOGIN);
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif
	
	// Sets username and password	
	#ifndef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s0", str_aux1);
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif
	
	// Releases old SSL stack if there is
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[15])));
	sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	
	// Acquires SSL stack
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[14])));
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return -3;
	}

	// Logs into the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[16])));
	sprintf(buffer_3G, "%s=\"%s\",%u,\"%s\",\"%s\"", str_aux1, server, port, user_name, password);
	answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
	if (answer == 2)
	{
		return -4;
	}
	else if (answer == 0)
	{
		return -5;
	}
	
	return 1;
	
}

/* uploadFileSecure(uint8_t, const char*) - Uploads a file from 3G board to FTPS server
 *
 * Origin values allowed:  0 – current directory, 1 – “C:/Picture” directory, 2 – “C:/Video” directory, 3 – “C:/VideoCall” directory,
 * 4 – “D:/Picture” directory, 5 – “D:/Video” directory, 6 – “D:/VideoCall” directory, 7 – “C:/Audio” directory, 8 – “D:/Audio” directory
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME code (FTPS error) and '-3' if error getting the file of the size to upload.
*/
int8_t Wasp3G::uploadFileSecure(uint8_t origin, const char* destination_path){

	uint8_t answer;
	uint8_t count;
	unsigned long previous;
	long file_size;
	
	// first get the file size to calculates a aproximated upload time
	switch (origin)
	{
		case 1:
			goRoot(0);
			cd("Picture");
			break;
		case 2:
			goRoot(0);
			cd("Video");
			break;
		case 3:
			goRoot(0);
			cd("VideoCall");
			break;
		case 4:
			goRoot(1);
			cd("Picture");
			break;
		case 5:
			goRoot(1);
			cd("Video");
			break;
		case 6:
			goRoot(1);
			cd("VideoCall");
			break;
		case 7:
			goRoot(0);
			cd("Audio");
			break;
		case 8:
			goRoot(1);
			cd("Audio");
			break;
		default:
			break;
	}
	if ((strchr(destination_path, '/')) == NULL)
	{
		file_size = getFileSize(destination_path);
	}
	else
	{
		file_size = getFileSize(strchr(destination_path, '/'));
	}
	
	if (file_size == -2)
	{
		return -3;
	}
	
	// Send the file and selects the origin location
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[22])));
	sprintf(buffer_3G, "%s\"%s\",%u", str_aux1, destination_path, origin);
		
	count = 3;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[23])));
	do{
		answer = sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR, (file_size / 10) + 1000, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	
	
	if (count == 0)
	{
		if (answer == 2)	// If CME error code is available returns -2
		{
			return -2;
		}
		else
		{
			return 0;		// Error without code
		}
	}
	else
	{
		previous = millis();
		count = serialRead(_socket);	
		answer = 0;	
		
		// Gets the answer (a number in ASCII), if the number is 0 the transfer is OK, if is a number, it is an FTP error code
		do{
			answer *= 10;
			answer += count - 0x30;
			count = serialRead(_socket);
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < (file_size / 10)));
		}while ((count != '\r') && ((millis() - previous) < (file_size / 10)));
		
		if (answer != 0)
		{
			CME_CMS_code = answer;
			return -2;
		}
	}
	
	return 1;
	
}

/* downloadFileSecure(const char*, uint8_t, int) - Downloads a file from FTPS server to 3G board
 *
 * Destination values allowed:  0 – current directory, 1 – “C:/Picture” directory, 2 – “C:/Video” directory, 3 – “C:/VideoCall” directory,
 * 4 – “D:/Picture” directory, 5 – “D:/Video” directory, 6 – “D:/VideoCall” directory, 7 – “C:/Audio” directory, 8 – “D:/Audio” directory
 *
 * max_time is the total time in seconds to download the file from the server
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME code (FTPS error)
*/
int8_t Wasp3G::downloadFileSecure(const char* origin_path, uint8_t destination, uint16_t max_time){

	uint8_t answer;
	uint8_t count;
		
	// Request the file and selects the destination location
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[18])));
	sprintf(buffer_3G, "%s\"%s\",%u", str_aux1, origin_path, destination);
	
	count=3;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[19])));
	do{
		answer=sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR, max_time*100, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	
	if(count == 0)
	{
		if (answer == 2)	// If CME error code is available returns -2
		{
			return -2;
		}
		else
		{
			return 0;		// Error without code
		}
	}
	else
	{
		count = serialRead(_socket);	
		answer = 0;	
		
		// Gets the answer (a number in ASCII), if the number is 0 the transfer is OK, if is a number, it is an FTPS error code
		do{
			answer *= 10;
			answer += count - 0x30;
			count = serialRead(_socket);
			while(serialAvailable(_socket) == 0);
		}while (count != '\r');
		
		if(answer != 0)
		{
			CME_CMS_code = answer;
			return -2;
		}
	}
	
	return 1;
	
}

/* uploadDataSecure(const char*, const char*) - Uploads data from Waspmote to FTPS server
 *
 * This function uploads data from Waspmote to FTPS server
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME code (FTPS error), '-3' if error getting file size from SD
*/
int8_t Wasp3G::uploadDataSecure(const char* SD_file, const char* FTP_destination_path){

	uint8_t answer;
	uint16_t count;
	long file_size;
	
	//Sends the command to send data
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[24])));
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, FTP_destination_path);
		
	count=3;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[25])));
	do{
		answer=sendCommand2(buffer_3G, str_aux1, ERROR_CME, 3000, 0);
		count--;
	}while ((answer != 1) && (count > 0));
	
	if (count == 0)
	{
		if (answer == 2)	//If CME error code is available returns 2
		{
			return -2;
		}
		else
		{
			return 0;		//Error without code
		}
	}
	
	// Sends data trought SOCKET:
	else
	{	
		SD.ON();
		file_size = SD.getFileSize(SD_file);
		if (file_size == -1)
		{
			#if _3G_debug_mode>0
				USB.print(F("Error reading SD file size"));
			#endif// Sends <CTRL+Z>:
			count = 3;
			#if _3G_debug_mode>0
			USB.print(F("Sends CTRL+Z"));
			#endif
			printByte(0x1A, _socket);
			do{
				answer = waitForData(OK_RESPONSE, ERROR_CME, 1000, 0, 0);
				count--;
			}while ((answer != 1) && (count > 0));
			SD.OFF();
			return -3;
		}
		else
		{
			#if _3G_debug_mode>0
				USB.print(F("file size: "));
				USB.println(file_size,DEC);
			#endif
			count = 0;
			do{
				if (file_size >= 250)
				{
					strncpy(buffer_3G, SD.cat(SD_file, count, 250), 250);
					buffer_3G[250] = '\0';
					count += 250;
				}
				else
				{
					strncpy(buffer_3G, SD.cat(SD_file, count, (file_size - count)), (file_size - count));
					count = file_size;
				}
				printString(buffer_3G,_socket);
				
				#if _3G_debug_mode>0
					USB.print(F("sended bytes: "));
					USB.println(count,DEC);
				#endif
			}while (count < file_size);
			
			SD.OFF();
			
			// Sends <CTRL+Z>:
			count = 3;
			#if _3G_debug_mode>0
				USB.print(F("Sends CTRL+Z"));
			#endif
			printByte(0x1A, _socket);
			do{
				answer = waitForData(OK_RESPONSE, ERROR_CME, 1000, 0, 0);
				count--;
			}while ((answer != 1) && (count > 0));
			
			if (count == 0)
			{
				if (answer == 2)	// If CME error code is available returns 2
				{
					return -2;
				}
				else
				{
					return 0;		// Error without code
				}
			}
		}
	}
	
	return 1;
	
}

/* downloadDataSecure(const char*, const char*) - Downloads data from FTP server to Waspmote
 *
 * This function downloads data to Waspmote from FTP server
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME code (FTP error) and '-3' if error sending the file from 3G module to Waspmote's SD
*/
int8_t Wasp3G::downloadDataSecure(const char* FTP_file, const char* SD_destination_path, uint16_t max_time){

	uint8_t answer;
	uint16_t count, file_size;
	
	// Waspmote can't manage the incoming packets of 1KB from the 3G module
	// First downloads the file to the 3G module
	
	answer = downloadFile( FTP_file, 0, max_time);
	
	if (answer == 1)
	{
		//if the file have been downloaded correctly, it will be transferred to Waspmote SD
		answer = getXModemFile((strrchr(FTP_file,'/')+1), SD_destination_path);
		//once the file is transferred, it deletes from the 3G module
		del(strrchr(FTP_file,'/')+1);
		
		if (answer != 1)
		{
			return -3;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return answer;
	}
}

/* logoutFPTS() - Logs out the FTPS server and releases the SSL stack
 *
 * Logs out the FTPS server and releases the SSL stack
 *
 * Returns '1' on success,'-2' if error logging out of the server and '-3' if error releasing the SSL stack
*/
int8_t Wasp3G::logoutFPTS(){
	
	int8_t answer;

	// Logs out of the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[17])));
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return -2;
	}
	
	// Releases SSL stack
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[15])));
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return -3;
	}
	
	return 1;	
}


#endif

//SMTP and POP3 functions
#if MAIL_FUSE

/* setSMTPserver(const char*, uint16_t, const char* , const char*) - Sets the SMTP server, port, username and password
 *
 * This function sets the SMTP server, port, username and password
 *
 * Returns '1' on success, '0' if error setting username and password and '-1' if error setting server and port
*/
int8_t Wasp3G::setSMTPserver(const char* server, uint16_t port, const char* username, const char* password){

	uint8_t answer=0;

	// Sets the SMTP server address and port
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[0])));
	sprintf(buffer_3G, "%s\"%s\",%d", str_aux1, server, port);
	answer=sendCommand1(buffer_3G, OK_RESPONSE);	
	if (answer == 0)
	{
		return -1;
	}
	
	// Sets the SMTP username and password
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[1])));
	sprintf(buffer_3G, "%s1,\"%s\",\"%s\"", str_aux1, username, password);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPserver(const char*, uint16_t) - Sets the SMTP server and port
 *
 * This function sets the SMTP server and port
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPserver(const char* server, uint16_t port){
	
	uint8_t answer;
	
	// Sets the SMTP server address and port
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[0])));
	sprintf(buffer_3G, "%s\"%s\",%d", str_aux1, server, port);
	answer=sendCommand1(buffer_3G, OK_RESPONSE);	
	if (answer == 0)
	{
		return 0;
	}
	
	// Sets the SMTP username and password
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[1])));
	sprintf(buffer_3G, "%s0", str_aux1);
	return (sendCommand1(buffer_3G, OK_RESPONSE));
	
}

/* setSMTPfrom( const char*, const char*) - Sets sender address and name
 *
 * This function sets sender address and name
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPfrom( const char* mail_address, const char* name){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[2])));
	sprintf(buffer_3G, "%s\"%s\",\"%s\"", str_aux1, mail_address, name);
	return (sendCommand1(buffer_3G, OK_RESPONSE));
	
}

/* setSMTPrecipient(uint8_t, uint8_t, const char*, const char*) - Sets recipient address and name (TO/CC/BCC)
 *
 * This function sets recipient address and name (TO/CC/BCC)
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPrecipient(uint8_t kind, uint8_t index, const char* mail_address, const char* name){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[3])));
	sprintf(buffer_3G, "%s%d,%d,\"%s\",\"%s\"", str_aux1, kind, index, mail_address, name);
	return (sendCommand1(buffer_3G, OK_RESPONSE));
	
}

/* setSMTPsubject( const char*) - Sets the subject of the email
 *
 * This function sets the subject of the email
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPsubject( const char* subject){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[4])));
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, subject);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPbody( const char*) - Sets the body of the email
 *
 * This function sets the body of the email
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPbody( const char* body){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[5])));
	sprintf(buffer_3G, "%s\"%s\"", str_aux1, body);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPattach( uint8_t, const char*) - Add attachments to the email
 *
 * This function adds attachments to the email
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPattach( uint8_t index, const char* file){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[6])));
	sprintf(buffer_3G, "%s%d,\"%s\"", str_aux1, index, file);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPsend() - Sends the email
 *
 * This function sends the email
 *
 * Returns '1' on success, '0' if error setting the apn, '-3' if error setting the apn with cme error code available
 * and '-2' error sendig the email
*/
int8_t Wasp3G::setSMTPsend(){
	
	int8_t answer, count;
	
	// Sets APN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));
	sprintf(buffer_3G, "%s1,\"IP\",\"%s\"", str_aux1, _3G_APN);
	count = 10;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return 0;
	}	
	
	// Sets username and password	
	#ifdef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s1,\"%s\",\"%s\"", str_aux1, _3G_PASSW, _3G_LOGIN);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif
	
	// Sets username and password	
	#ifndef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s0", str_aux1);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif
		
	// Sends the email
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[7])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[8])));
	answer = sendCommand2(str_aux1, str_aux2, ERROR, 12000, 0);
	if ((answer == 0) || (answer == 2))
	{	
		return -2;
	}
	
	return 1;

}


/* setPOP3server(const char*, uint16_t, const char* , const char*) - Sets the POP3 server, port, username and password
 *
 * This function sets the POP3 server, port, username and password and configures the apn
 *
 * Returns '1' on success, '0' if error setting the apn, '-3' if error setting the apn with cme error code available
 * and '-2' error setting the parameters of POP3 server
*/
int8_t Wasp3G::setPOP3server(const char* server, uint16_t port, const char* username, const char* password){
	
	int8_t answer, count;
	
	// Sets APN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));
	sprintf(buffer_3G, "%s1,\"IP\",\"%s\"", str_aux1, _3G_APN);
	count = 10;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return 0;
	}	
	
	// Sets username and password	
	#ifdef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s1,\"%s\",\"%s\"", str_aux1, _3G_PASSW, _3G_LOGIN);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif
	
	// Sets username and password	
	#ifndef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s0", str_aux1);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif
	
	// Sets the POP3 server, port, username and password
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[9])));
	sprintf(buffer_3G, "%s=\"%s\",\"%s\",\"%s\",%d", str_aux1, server, username, password, port);
	answer = sendCommand1(buffer_3G, OK_RESPONSE);
	if (answer == 0)
	{
		return -2;
	}
	
	return 1;
	
}

/* getPOP3list() - Gets the total number of emails
 *
 * This function Gets the total number of emails
 *
 * Returns the total number of emails, '-2' if error logging in the POP3 server and '-3' if error getting the e-mail number
*/
int Wasp3G::getPOP3list(){
	
	int8_t answer;
	unsigned long previous;
	int x, count;
	
	// Logs into the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[10])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
	answer = sendCommand2(str_aux1, str_aux2, ERROR, 3000, 0);	
	if ((answer == 0) || (answer == 2))
	{
		return -1;
	}	
	
	// Slow baudrate to manage the data
	changeBaudrate(4800);
	getIfReady();
	
	// Request the list of emails
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[12])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[13])));
	answer = sendCommand1(str_aux1, str_aux2);	
	if (answer == 1)
	{
		previous = millis();
		x = 0;
		count = 0;
		do{	
			buffer_3G[2] = serialRead(_socket);
			if (buffer_3G[2] != -1)
			{
				buffer_3G[0] = buffer_3G[1];
				buffer_3G[1] = buffer_3G[2];
				if (buffer_3G[2] == '\r')
				{
					count++;
				}
			}
		}while (((buffer_3G[2] != 'K') && (buffer_3G[0] != 'O')) && ((millis() - previous) < 30000));
		
		// Restores the baudrate
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));
		sprintf(buffer_3G, "%s%ld", str_aux1, _baudRate);
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		if (answer == 2)
		{
			return -4;
		}
		else if (answer == 1) // If the command is executed by the 3G module, changes the Wasmote baudrate
		{
			beginSerial(_baudRate, _socket);
		}
		getIfReady();
				
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
		sendCommand1(str_aux1, str_aux2);
		
		return count;
	}	
	
	// Restores the baudrate
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));
	sprintf(buffer_3G, "%s%ld", str_aux1, _baudRate);
	answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
	if (answer == 2)
	{
		return -4;
	}
	else if (answer == 1) // If the command is executed by the 3G module, changes the Wasmote baudrate
	{
		beginSerial(_baudRate, _socket);
	}
	getIfReady();
		
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
	sendCommand1(str_aux1, str_aux2);
	
	return -3;
	
}

/* getPOP3header(uint8_t) - Gets the header of the e-mail specified in index
 *
 * This function gets the header of the e-mail specified in index and returns it in 'buffer_3G'.
 *
 * Returns '1' on success, '-1' if error logging in the POP3 server and '-2' if error getting the header of the e-mail
*/
int8_t Wasp3G::getPOP3header(uint8_t index){
	
	int8_t answer, count;
	unsigned long previous;
	int x;
	char aux_str[15];
	
	// Logs into the server	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[10])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
	answer = sendCommand2(str_aux1, str_aux2, ERROR, 3000, 0);	
	if ((answer == 0) || (answer == 2))
	{
		return -1;
	}	
	
	// Slow baudrate to manage the data
	changeBaudrate(4800);
	getIfReady();
	
	// Request the header of the email
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[14])));
	sprintf( buffer_3G, "%s%d", str_aux1, index);
	answer=sendCommand1(buffer_3G, "From:");	
	if (answer == 1)
	{
		buffer_3G[0]='\0';
		strcmp(buffer_3G, "From:");
		x=0;
		previous=millis();
		
		do{
			buffer_3G[x]=serialRead(_socket);
			if (buffer_3G[x] != -1)
			{
				x++;
			}
		}while (((buffer_3G[x-1] != 'K') && (buffer_3G[x-2] != 'O')) && ((millis()-previous) < 30000) && (x < BUFFER_SIZE));
		
		buffer_3G[x-4]='\0';
		
		// Restores the baudrate
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));
		sprintf(aux_str, "%s%ld", str_aux1, _baudRate);
		answer = sendCommand2(aux_str, OK_RESPONSE, ERROR);
		if (answer == 2)
		{
			return -3;
		}
		else if (answer == 1) // If the command is executed by the 3G module, changes the Wasmote baudrate
		{
			beginSerial(_baudRate, _socket);
		}
		getIfReady();
		
		
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
		sendCommand1(str_aux1, str_aux2);
		
		return 1;
	}	
	
	// Restores the baudrate
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));
	sprintf(aux_str, "%s%ld", str_aux1, _baudRate);
	answer = sendCommand2(aux_str, OK_RESPONSE, ERROR);
	if (answer == 2)
	{
		return -3;
	}
	else if (answer == 1) // If the command is executed by the 3G module, changes the Wasmote baudrate
	{
		beginSerial(_baudRate, _socket);
	}
	getIfReady();
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
	sendCommand1(str_aux1, str_aux2);
	
	return -2;
	
}

/* getPOP3mail(uint8_t) - Gets the e-mail specified in index
 *
 * This function gets the e-mail specified in index
 *
 * Returns '1' on success, '-1' if error logging in the POP3 server and '-2' getting the e-mail
*/
int8_t Wasp3G::getPOP3mail(uint8_t index){
	
	int8_t answer, count;
	unsigned long previous;
	int x;
		
	// Logs into the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[10])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
	answer = sendCommand2(str_aux1, str_aux2, ERROR, 3000, 0);	
	if ((answer == 0) || (answer == 2))
	{
		return -1;
	}	
		
	// Request the email
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[15])));
	sprintf(buffer_3G, "%s%d,1", str_aux1, index);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[17])));
	answer = sendCommand1(buffer_3G, str_aux1);	
	if (answer == 1)
	{
		x = 0;
		serialRead(_socket);
		serialRead(_socket);
		previous = millis();
		do{
			//while ((serialAvailable(_socket) <= 20) && ((millis()-previous) < 10000));
			buffer_3G[x] = serialRead(_socket);
			if (buffer_3G[x] != 0xFF)
			{				
				x++;
			}
		}while ((buffer_3G[x-1] != '\r') && ((millis()-previous) < 30000) && (x < BUFFER_SIZE));
		
		buffer_3G[x-1] = '\0';
		
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
		sendCommand1(str_aux1, str_aux2);
		
		return 1;
	}
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
	sendCommand1(str_aux1, str_aux2);
	
	return -2;	
}

/* deletePOP3mail(uint8_t) - Marks an e-mail to delete from POP3 server
 *
 * This function marks an e-mail to delete from POP3 server when logs out
 *
 * Returns '1' on success, '-1' if error logging in the POP3 server and '-2' if error deleting the e-mail
*/
int8_t Wasp3G::deletePOP3mail(uint8_t index){
	
	int8_t answer, count;
	unsigned long previous;
	int x;
	
	// Logs into the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[10])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
	answer = sendCommand2(str_aux1, str_aux2, ERROR, 3000, 0);	
	if ((answer == 0) || (answer == 2))
	{
		return -1;
	}	
	
	// Request the header of the email
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[16])));
	sprintf( buffer_3G, "%s%d", str_aux1, index);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[17])));
	answer=sendCommand2(buffer_3G, str_aux1, ERROR);	
	if (answer == 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
		sendCommand1(str_aux1, str_aux2);
		return 1;
	}	
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));
	sendCommand1(str_aux1, str_aux2);
	return -2;
	
}

#endif

//HTTP functions
#if HTTP_FUSE
/* readURL(const char*, uint16_t, uint16_t , const char*) - Sends a request to a HTTP url and get an answer
 *
 * This function sends a request to a HTTP url and get an answer. The answer is stored in 'buffer_3G'
 *
 * Returns '1' on success, '-1' if error setting APN, username and password, '-2' if error opening a HTTP session, '-3' if error receiving data or timeout waiting data,
 * '-4' if error changing the baudrate (data received is OK), '-5' if unknown error for HTTP, '-6' if HTTP task is busy, '-7' if fail to resolve server address,
 * '-8' if HTTP timeout, '-9' if fail to transfer data, '-10' if memory error, '-11' if invalid parameter, '-12' if network error,
 * '-15' if error setting APN, username and password with CME_error code available and '-16' if error opening a HTTP session with CME_error code available
*/
int16_t Wasp3G::readURL(const char* url, uint16_t port, const char* HTTP_request){
	
	int8_t answer, header;
	int16_t HTTP_data, count;
	char aux, command[15];
	unsigned long previous;
	
	// Sets APN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));
	sprintf(buffer_3G, "%s1,\"IP\",\"%s\"", str_aux1, _3G_APN);
	count = 5;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return -1;
	}	
	
	// Sets username and password	
	#ifdef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s1,\"%s\",\"%s\"", str_aux1, _3G_PASSW, _3G_LOGIN);
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 0)
	{
		return -1;
	}
	else if (answer == 2)
	{
		return -15;
	}
	#endif
	
	// Sets username and password	
	#ifndef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s0", str_aux1);
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 0)
	{
		return -1;
	}
	else if (answer == 2)
	{
		return -15;
	}
	#endif
	
	for ( count = 0; count < BUFFER_SIZE; count++)
	{
		buffer_3G[count] = '\0';
	}
	
	changeBaudrate(2400);
	getIfReady();
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[0])));
	sprintf(buffer_3G, "%s\"%s\",%d", str_aux1, url, port);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[1])));
	answer = sendCommand2(buffer_3G, str_aux1, ERROR_CME, 2000, 0);
	if (answer == 0)
	{
		changeBaudrate(_baudRate);
		return -2;
	}
	else if (answer == 2)
	{
		changeBaudrate(_baudRate);
		return -16;
	}

	//serialFlush(_socket);
	printString(HTTP_request, _socket);
	printByte(0x1A, _socket);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[2])));
	answer = waitForData(str_aux1, ERROR, 6000, 0, 0);	
	if (answer != 1)
	{
		changeBaudrate(_baudRate);
		return -3;
	}
		
	count = 0;
	aux = serialRead(_socket);
	while (aux == 'D')
	{	// Data received
	
		serialRead(_socket);	// A
		serialRead(_socket);	// T
		serialRead(_socket);	// A
		serialRead(_socket);	// ,
		
		HTTP_data = 0;
		aux = serialRead(_socket);
		// Gets the length of the first data string
		do{
			HTTP_data *= 10;
			HTTP_data += aux - 0x30;
			aux = serialRead(_socket);
		}while (aux != '\r');
		
		serialRead(_socket); // Skips '\n'
		
		// Reads the incoming bytes
		previous = millis();
		
		#if _3G_debug_mode>0
			USB.print(F("HTTP data: "));
			USB.println(HTTP_data, DEC);
		#endif
		
		do{
			aux = serialRead(_socket);
			if (aux != -1)
			{	
				if (count < BUFFER_SIZE)
				{
					buffer_3G[count] = aux;
					count++;
				}
				HTTP_data--;
			}	
			else
			{
				delay(1);
			}
		}while ((HTTP_data > 0) && ((millis() - previous) < 10000));
		
		#if _3G_debug_mode>0
			USB.print(F("Count remainder: "));
			USB.println(HTTP_data, DEC);
		#endif
		
		// Waits for new data or the end of the request
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[2])));
		answer = waitForData(str_aux1, ERROR, 2000, 0, 0);
		if (answer == 1)
		{
			aux = serialRead(_socket);
		}
		else
		{	
			aux = 0;
		}
	}
	
	if (aux == '0')
	{
		// No more data
		buffer_3G[count - 1] = '\0';

		// Changes to default baudrate
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));
		sprintf(command, "%s%ld", str_aux1, _baudRate);
		answer=sendCommand2(command, OK_RESPONSE, ERROR);	
		if (answer == 2)
		{
			return -4;
		}
		else if (answer == 1) // If the command is executed by the 3G module, changes the Wasmote baudrate
		{
			beginSerial(_baudRate, _socket);
		}
		
		return 1;
	}
	else if (aux == 0)
	{
		// Error answer received or timeout waiting data
		return 	-3;
	}
	else
	{
		// Error code received
		HTTP_data = 0;
		do{
			HTTP_data *= 10;
			HTTP_data += aux - 0x30;
			aux = serialRead(_socket);
		}while (aux != '\r');
		
		#if _3G_debug_mode>0
			USB.print(F("HTTP error: "));
			USB.println(HTTP_data, DEC);
		#endif
		
		HTTP_data -= 215;
		
		changeBaudrate(_baudRate);
		
		return -HTTP_data;
	}
}

/* readURLS(const char*, uint16_t, uint16_t , const char*) - Sends a request to a HTTPS url and get an answer
 *
 * This function sends a request to a HTTPS url and get an answer. The answer is stored in 'buffer_3G'
 *
 * Returns '1' on success, '-1' if unknown error, '-2' if 3G module is busy, '-3' if server closed, '-4' if timeout,
 * '-5' if transfer failed, '-6' if memory error, '-7' if invalid parameter, '-8' if network error, '-10' if error setting APN, username and password
 * '-11' if error acquiring HTTPS protocol stack, '-12' if error opening a HTTPS session, '-13' if error changing baudrate, 
 * '-14' if error storing HTTPS request in the output buffer, '-15' if error sending the HTTPS request to the url, '-16' if error with the receive command,
 * '-17' if error closing the session (data received is OK), '-18' if error releasing the SSL stack (data received is OK), 
 * '-19' if error changing the baudrate (data received is OK), '-20' if error receiving data or timeout waiting data and
 * '-25' if error setting username and password with CME_error code available
*/
int8_t Wasp3G::readURLS(const char* url, uint16_t port, const char* HTTPS_request){
	
	int8_t answer;
	int HTTPS_data, count;
	char command[15], aux;
	unsigned long previous;
	
	// Sets APN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));
	sprintf(buffer_3G, "%s1,\"IP\",\"%s\"", str_aux1, _3G_APN);
	count = 5;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return -10;
	}	
	
	// Sets username and password	
	#ifdef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s1,\"%s\",\"%s\"", str_aux1, _3G_PASSW, _3G_LOGIN);
	count = 5;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 0)
	{	
		return -10;
	}
	else if (answer == 2)
	{
		return -25;
	}
	#endif
	
	// Sets username and password	
	#ifndef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s0", str_aux1);
	count = 5;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 0)
	{	
		return -10;
	}
	else if (answer == 2)
	{
		return -25;
	}
	#endif
	
	for ( count = 0; count < BUFFER_SIZE; count++)
	{
		buffer_3G[count] = '\0';
	}
	
	// Release other SSL stacks and close session
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));
	sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));
	sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[3])));
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return -11;
	}
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[5])));
	sprintf(buffer_3G, "%s=\"%s\",%d", str_aux1, url, port);
	answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR, 2000, 0);
	if (answer != 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		return -12;
	}
	
	answer = changeBaudrate(2400);
	if (answer != 1)
	{
		return -13;
	}
	getIfReady();
	
	// Stores HTTPS data in the output buffer
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[7])));
	sprintf(buffer_3G, "%s=%d", str_aux1, strlen(HTTPS_request));
	answer = sendCommand2(buffer_3G, "\r\n>", ERROR, 2000,  0);
	if (answer != 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		changeBaudrate(_baudRate);
		return -14;
	}
	
	printString(HTTPS_request,_socket);
	answer = waitForData(OK_RESPONSE, ERROR, 200, 0, 0);
	if (answer != 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		changeBaudrate(_baudRate);
		return -14;
	}
	
	// Sends the data of the buffer
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[7])));
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		changeBaudrate(_baudRate);
		return -15;
	}
	
	// Receives data
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[8])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_HTTP[9])));
	answer = sendCommand2(str_aux1, str_aux2, ERROR);
	if (answer != 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		changeBaudrate(_baudRate);
		return -16;
	}	
	
	count = 0;
	aux = serialRead(_socket);
	while (aux == 'D')
	{	// Data received
	
		serialRead(_socket);	// A
		serialRead(_socket);	// T
		serialRead(_socket);	// A
		serialRead(_socket);	// ,
		
		HTTPS_data = 0;
		aux=serialRead(_socket);
		// Gets the length of the first data string
		do{
			
			HTTPS_data *= 10;
			HTTPS_data += aux - 0x30;
			aux = serialRead(_socket);
		}while (aux != '\r');
		
		serialRead(_socket); // Skips '\n'
		
		// Reads the incoming bytes
		previous = millis();
		
		#if _3G_debug_mode>0
			USB.print(F("HTTPS data: "));
			USB.println(HTTPS_data, DEC);
		#endif
		
		do{
			aux = serialRead(_socket);
			if (aux != -1)
			{	
				if (count < BUFFER_SIZE)
				{
					buffer_3G[count] = aux;
					count++;
				}
				HTTPS_data--;
			}	
			else
			{
				delay(1);
			}
		}while ((HTTPS_data > 0) && ((millis() - previous) < 10000));
		
		#if _3G_debug_mode>0
			USB.print(F("Count remainder: "));
			USB.println(HTTPS_data, DEC);
		#endif
		
		// Waits for new data or the end of the request
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[9])));
		answer = waitForData(str_aux1, ERROR, 2000, 0, 0);
		if (answer == 1)
		{
			aux = serialRead(_socket);
		}
		else
		{
			aux = 0;
		}
	}
	
	if (aux == '0')
	{
		// No more data
		buffer_3G[count - 1] = '\0';
		
		// Closes connection and release the SSL stack		
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));
		answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		if (answer != 1)
		{
			changeBaudrate(_baudRate);
			return -17;
		}
		
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));
		answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		if (answer != 1)
		{
			changeBaudrate(_baudRate);
			return -18;
		}
		
		// Changes to default baudrate
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));
		sprintf(command, "%s%ld", str_aux1, _baudRate);
		answer = sendCommand2(command, OK_RESPONSE, ERROR);	
		if (answer == 2)
		{
			changeBaudrate(_baudRate);
			return -19;
		}
		else if (answer == 1) // If the command is executed by the 3G module, changes the Wasmote baudrate
		{
			beginSerial(_baudRate, _socket);
		}
		
		return 1;
	}
	else if (aux == 0)
	{
		// Error answer received or timeout waiting data
		return 	-20;
	}
	else
	{
		// Error code received		
		HTTPS_data = 0;		
		do{
			HTTPS_data *= 10;
			HTTPS_data += aux - 0x30;
			aux = serialRead(_socket);
		}while (aux != '\r');
		
		#if _3G_debug_mode>0
			USB.print(F("HTTPS error: "));
			USB.println(HTTPS_data, DEC);
		#endif
		
		// Closes connection, release the SSL stack and changes the baudrate
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		changeBaudrate(_baudRate);
		
		return -HTTPS_data;
	}
}
#endif

//GPS function
#if GPS_FUSE

/*startGPS() - Starts GPS in stand-alone mode
 *
 * This function starts the GPS in stand-alone mode
 *
 * Returns '1' if success, '0' if error, '-4' if error starting the GPS
*/
int8_t Wasp3G::startGPS(){
	return startGPS( 1, "", "");
}	
	
/*startGPS(int8_t, const char*, const char*) - Starts and configures the GPS
 *
 * This function starts and configures (if needs) the GPS.
 *
 * 'mode': '1' for stand-alone mode, '2' for UE-based mode and '3' for UE-assisted mode
 *
 * Returns '1' if success, '0' if error, '-2' if error setting the apn, '-3' if error setting GPS server and port,
 * '-4' if error starting the GPS, '-5' if AGPS data are not available
*/
int8_t Wasp3G::startGPS(int8_t mode, const char* GPS_url, const char* GPS_port){
	
	int8_t answer;
	uint8_t count=0;
	
	if (mode == 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[0])));
		sprintf(buffer_3G, "%s%d", str_aux1, mode);
	}
	else
	{
		// Sets APN
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));
		sprintf(buffer_3G, "%s1,\"IP\",\"%s\"", str_aux1, _3G_APN);
		count = 5;
		do{
			answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
			count--;
		}while ((answer != 1) && (count  > 0));
		if (count == 0)
		{
			return -2;
		}	
		
		// Sets username and password	
		#ifdef _3G_PASSW && _3G_LOGIN
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
		sprintf(buffer_3G, "%s1,\"%s\",\"%s\"", str_aux1, _3G_PASSW, _3G_LOGIN);
		count = 5;
		do{
			answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
			count--;
		}while ((answer != 1) && (count  > 0));
		if (answer == 0)
		{	
			return -2;
		}
		else if (answer == 2)
		{
			return -2;
		}
		#endif
		
		// Sets username and password	
		#ifndef _3G_PASSW && _3G_LOGIN
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
		sprintf(buffer_3G, "%s0", str_aux1);
		count = 5;
		do{
			answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
			count--;
		}while ((answer != 1) && (count  > 0));
		if (answer == 0)
		{	
			return -2;
		}
		else if (answer == 2)
		{
			return -2;
		}
		#endif
		
		// Sets the GPS server and port:
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[4])));
		sprintf(buffer_3G, "%s\"%s:%s\"", str_aux1, GPS_url, GPS_port);
		count=10;
		do{
			answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
			count--;
		}while ((answer != 1) && (count  > 0));
		if (count == 0)
		{
			return -3;
		}
		
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[0])));
		sprintf(buffer_3G, "%s%d", str_aux1, mode);
	}
	
	// Starts the GPS:
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
			return -4;
	}
	
	// If GPS mode is assisted GPS, waits for string of GPS data:
	if (mode == 3)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[5])));
		if (waitForData(str_aux1, 6000, 0, 0) == 1) //If there are data, stores it in 'buffer_3G'
		{
			count=0;
			do{
				buffer_3G[count]=serialRead(_socket);
				count++;
			}while (serialAvailable(_socket) != 0);
			buffer_3G[count]='\0';
		}
		else
		{
			return -5;
		}
	}
		
	return 1;
}

/*startGPScold() - Starts and configures the GPScold start GPS session
 *
 * This function starts and configures (if needs) the GPS.
 *
 * Returns '1' if success, '0' if error
*/
int8_t Wasp3G::startGPScold(){
	
	// Starts the GPS:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[1])));
	return sendCommand1(str_aux1, OK_RESPONSE);
}

/*startGPShot() - Starts and configures the GPScold start GPS session
 *
 * This function starts and configures (if needs) the GPS.
 *
 * Returns '1' if success, '0' if error
*/
int8_t Wasp3G::startGPShot(){
	
	// Starts the GPS:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[2])));
	return sendCommand1(str_aux1, OK_RESPONSE);

}

/*stopGPS() - Stops the GPS
 *
 * This function stops the GPS
 *
 * Returns '1' if success and '0' if error
*/
int8_t Wasp3G::stopGPS(){
	
	int8_t answer;

	// Stops the GPS:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[3])));
	answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR);

	if (answer == 1)
	{
			return answer;
	}
		
	return 0;
}

/*getGPSinfo() - gets info for GPS if it's available
 *
 * This function gets info for GPS if it's available
 *
 * Returns '1' if success, '-2' if info it's not available and '0' if error
*/
int8_t Wasp3G::getGPSinfo(){
	
	int8_t answer;
	uint8_t count=0, count2;
	unsigned long previous;
			
	// Starts the GPS:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[6])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_GPS[7])));
	answer=sendCommand1(str_aux1, str_aux2);

	if (answer != 1)
	{
			return -2;
	}
	
	// Gets GPS string
	count=0;	
	previous=millis();
	buffer_3G[0]='\0';
	do{
		while ((serialAvailable == 0) && ((millis()-previous) < 5000));
		buffer_3G[count]=serialRead(_socket);
		count++;
	}while ((buffer_3G[count-1] != '\r') && ((millis()-previous) < 5000));
	buffer_3G[count] = '\0';
	
	if (buffer_3G[0] == ',') // if there aren't data available
	{
		return -2;
	}
	else if (buffer_3G[0] == '\0') // if there aren't data
	{
		return 0;
	}
	else // Parses the GPS string
	{
		latitude[0]=' ';
		latitude[1]='\0';
		strcat(latitude,strtok(buffer_3G, ",")); // Gets latitude
		if (strcmp("N",strtok(NULL, ",")) == 0) // add '+' for north and '-' for south
		{
			latitude[0]='+';
		}
		else
		{
			latitude[0]='-';
		}
		longitude[0]=' ';
		longitude[1]='\0';
		strcat(longitude,strtok(NULL, ",")); // Gets longitude
		if (strcmp("W",strtok(NULL, ",")) == 0) // add '-' for west and '+' for east
		{
			longitude[0]='-';
		}
		else
		{
			longitude[0]='+';
		}
		strcpy(date,strtok(NULL, ",")); // Gets date
		strcpy(UTC_time,strtok(NULL, ",")); // Gets UTC time
		strcpy(altitude,strtok(NULL, ",")); // Gets altitude
		strcpy(speedOG,strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
		strcpy(course,strtok(NULL, ",")); // Gets course
	}
	
	return 1;
}

/*enableAutoGPS() - Enables to start GPS automatic when module power on
 *
 * This function enables to start GPS automatic when module power on
 *
 * Returns '1' if success, '0' if error
*/
int8_t Wasp3G::enableAutoGPS(){
	
	// Enables the auto GPS:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[8])));
	return sendCommand1(str_aux1, OK_RESPONSE);
}

/*disableAutoGPS() - Disables to start GPS automatic when module power on
 *
 * This function disables to start GPS automatic when module power on
 *
 * Returns '1' if success, '0' if error
*/
int8_t Wasp3G::disableAutoGPS(){
	
	// Disables the auto GPS:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[9])));
	return sendCommand1(str_aux1, OK_RESPONSE);
}

/* convert2Degrees ( input ) - performs the conversion from input 
 * parameters in  DD°MM.mmm’ notation to DD.dddddd° notation. 
 * 
 * Sign '+' is set for positive latitudes/longitudes (North, East)
 * Sign '-' is set for negative latitudes/longitudes (South, West)
 * 
 * parameter: 'input' is a string indicating the latitude/longitude in 
 * DDmm.mmmm' notation for latitude and DDDmm.mmmm' notation for longitude
 * parameter: 'indicator' is a char indicating 'N' for North, 'S' for South, 'E'
 * for East and 'W' for West
 * Returns: a float indicating the latitude in DD.dddddd° notation
 *  
 */
float Wasp3G::convert2Degrees(char* input){
	// final latitude expresed in degrees
	float degrees;
	float minutes;
	
	//auxiliar variable
	char aux[10];
	
	// check if 'indicator' is a valid input
	if ( input[5] == '.' && input[6] == '.' )
	{
		// invalid indicator
		return 0;
	}	
	
	// get 'degrees' from input parameter
	if (input[5] == '.')
	{
		//latitude format: DDmm.mmmm'
		aux[0]=input[1];
		aux[1]=input[2];
		aux[2]='\0';
	}
	else
	{
		//longitude format: DDDmm.mmmm'
		aux[0]=input[1];
		aux[1]=input[2];
		aux[2]=input[3];
		aux[3]='\0';
	}
	
	// convert string to integer and add it to final float variable
	degrees=atoi(aux);
	
	// get 'minutes' from input parameter 
	if (input[5] == '.')
	{
		//latitude format: DDmm.mmmm'
		for ( int i=0; i<9; i++ )
		{
			aux[i]=input[i+3];
		}
		aux[7]='\0';
	}
	else
	{
		//latitude format: DDmm.mmmm'
		for ( int i=0; i<9; i++ )
		{
			aux[i]=input[i+4];
		}
		aux[7]='\0';
	}	
	
	// convert string to integer and add it to final float variable
	minutes=atof(aux);
	
	// add minutes to degrees 
	degrees=degrees+minutes/60;
	
	if (input[0] == '-')
	{
		degrees*=-1.0;
	}
		
	return degrees;
	
}

#endif

//TCP/UDP functions
#if IP_FUSE

/* configureTCP_UDP() - Configures 3G connection with login, password and some other parameters to use TCP or UDP connections in non-transparent mode
 *
 * This function creates a 3G connection with the carrier server to get access to the internet
 *
 * Returns '1' on success, '-2' if error dettaching the connection, '-10' if error dettaching the connection with CME code available,
 * '-3' if error attaching the connection, '-11' if error attaching the connection with CME code available,
 * '-4' if waiting time for connection have expired, '-5' if error setting the APN,
 * '-6' if error setting the user name and the password, '-12' if error setting the user name and the password with CME code available, 
 * and '-7' if error configurating IP parameters
*/
int8_t Wasp3G::configureTCP_UDP(){
	return (configureTCP_UDP(0));
}

/* configureTCP_UDP(int8_t) - Configures 3G connection with login, password and some other parameters to use TCP or UDP connections
 *
 * This function creates a 3G connection with the carrier server to get access to the internet
 *
 * Returns '1' on success, '-2' if error dettaching the connection, '-10' if error dettaching the connection with CME code available,
 * '-3' if error attaching the connection, '-11' if error attaching the connection with CME code available,
 * '-4' if waiting time for connection have expired, '-5' if error setting the APN,
 * '-6' if error setting the user name and the password, '-12' if error setting the user name and the password with CME code available, 
 * and '-7' if error configurating IP parameters
*/
int8_t Wasp3G::configureTCP_UDP(int8_t app_mode){
	
	unsigned long previous = millis();
	uint8_t answer=0;
	uint8_t count;
	uint8_t state;
		
	// First restart TCP/UDP connection:
	count=10;
	
	if (check3Gconnection() == 1) 
	{	
		// Dettachs 3G:
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[9])));
		do{
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			count--;
		}while ((count != 0) && (answer != 1));
		if (answer == 0)
		{	
			return -2;
		}
		else if (answer == 2)
		{
			return -10;
		}
	}
	
	// Now attaches connection:
	count=10;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[8])));
	do{
		answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((count != 0) && (answer != 1));
	if (answer == 0)
	{	
		return -3;
	}
	else if (answer == 2)
	{
		return -11;
	}
	
	// Waits for connection:
	previous=millis();
	while ((check3Gconnection() != 1) && (millis()-previous < 30000));
	if (millis()-previous > 30000)
	{
		return -4;
	}
	
	// Sets APN:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));
	sprintf(buffer_3G, "%s1,\"IP\",\"%s\"", str_aux1, _3G_APN);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return -5;
	}	
	
	// Sets username and password	
	#ifdef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s1,\"%s\",\"%s\"", str_aux1, _3G_PASSW, _3G_LOGIN);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif
	
	// Sets username and password	
	#ifndef _3G_PASSW && _3G_LOGIN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));
	sprintf(buffer_3G, "%s0", str_aux1);
	count=10;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 2)
	{	
		return -2;
	}
	else if (answer == 0)
	{
		return 0;
	}
	#endif

	#if _3G_debug_mode>0
		USB.print(F("IP Flag: "));
		USB.println(IP_flags,BIN);
	#endif
	
	// Configures answers and retries
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[18])));
	sprintf(buffer_3G, "%s%d,%d,1,0,1", str_aux1, RETRIES, DELAY_SEND);
	//sprintf(buffer_3G, "%s%d,%d,1,1,1", str_aux1, RETRIES, DELAY_SEND);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
	
	if ((answer == 0) || (answer == 2))
	{	
		return -7;
	}	
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[2])));
	sprintf(buffer_3G, "%s%d", str_aux1, app_mode);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
	
	if ((answer == 0) || (answer == 2))
	{	
		return -8;
	}
	
	IP_flags &= 0xFE;
	if (app_mode == 1)
	{
		IP_flags |= 0x01;
	}
	
	#if _3G_debug_mode>0
		USB.print(F("IP Flag: "));
		USB.println(IP_flags,BIN);
	#endif
	
	return 1;
	
}

/* closeSocket() - Closes all sockets opened.
 *
 * This function closes all sockets opened.
 *
 * Returns '1' on success, '0' if error and '-2' if error with IP error code available 
*/
int8_t Wasp3G::closeSocket(){
	
	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[1])));
	answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_IP);
	
	if (answer == 2)
	{	
		return -2;
	}
	return answer;
}

/* createSocket(uint8_t) - Configures the 3G module to use multi client mode or UDP client and opens the network
 *
 * This function configures the 3G module to use multi client mode or UDP client and opens the network
 *
 * Returns '1' on success, '-2' if error opening the network, '-4' if error opening the network with CME error code available,
 * '-5' if error opening the network with IP error code available, '-3' if error opening the TCP connection or starting the TCP server
 * and '-6' if error opening the TCP connection or starting the TCP server with IP error code
*/
int8_t Wasp3G::createSocket(uint8_t mode){
	return( createSocket(mode, "", 0));
}

/* createSocket(uint8_t, uint16_t) - Configures the 3G module to use the TCP server and opens the network
 *
 * This function configures the 3G module to use the TCP server and opens the network
 *
 * Returns '1' on success, '-2' if error opening the network, '-4' if error opening the network with CME error code available,
 * '-5' if error opening the network with IP error code available, '-3' if error opening the TCP connection or starting the TCP server
 * and '-6' if error opening the TCP connection or starting the TCP server with IP error code
*/
int8_t Wasp3G::createSocket(uint8_t mode, uint16_t port){
	return( createSocket(mode, "", port));
}

/* createSocket(uint8_t, const char*, uint16_t) - Configures the 3G module for TCP and UDP and opens the network
 *
 * This function configures the 3G module for TCP and UDP and opens the network
 *
 * Returns '1' on success, '-2' if error opening the network, '-4' if error opening the network with CME error code available,
 * '-5' if error opening the network with IP error code available, '-3' if error opening the TCP connection or starting the TCP server
 * and '-6' if error opening the TCP connection or starting the TCP server with IP error code
*/
int8_t Wasp3G::createSocket(uint8_t mode, const char* ip, uint16_t port){
	
	int answer, count;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[0])));
	switch (mode)
	{
		// TCP client, single connection mode
		case 0:
			sprintf(buffer_3G, "%s\"TCP\",0,0", str_aux1);
			break;
			
		// UDP client, single connection mode
		case 1:
			sprintf(buffer_3G, "%s\"UDP\",0,0", str_aux1);
			break;
			
		// TCP server
		case 2:
			sprintf(buffer_3G, "%s\"TCP\",%u", str_aux1, port);
			break;
			
		// Multiple connection mode
		case 3:
			sprintf(buffer_3G, "%s,,1", str_aux1);
			break;
	}

	count=10;
	do{
		answer=sendCommand3(buffer_3G, OK_RESPONSE, ERROR_CME, ERROR_IP, 1000, 0);
		count--;
	}while ((count != 0) && (answer != 1));

	
	if (answer == 3)
	{
		return -5;
	}
	else if (answer == 2)
	{	
		return -4;
	}
	else if (answer == 0)
	{
		return -2;
	}
	
	if (mode == 3)
	{	
		IP_flags &= 0xF9;
		IP_flags |= 0x06;
	}
	else
	{
		IP_flags &= 0xF9;
		IP_flags |= 0x04;
	}
	
	#if _3G_debug_mode>0
		USB.print(F("Flag 2: "));
		USB.println(IP_flags,BIN);
	#endif
	
	switch (mode)
	{
		// TCP client, single connection mode
		case 0:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[5])));
			sprintf(buffer_3G, "%s\"%s\",%u", str_aux1, ip, port);
			
			if ((IP_flags & 0x01) == 0)
			{
				count=10;
				do{
					answer=sendCommand3(buffer_3G, "Connect ok", ERROR_CME, ERROR_IP, 2000, 0);
					count--;
				}while ((count != 0) && (answer != 1));
			}
			else
			{
				count=10;
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[21])));
				do{
					answer=sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR_IP, 2000, 0);
					count--;
				}while ((count != 0) && (answer != 1));
			}
			break;
			
		// Start up the TCP server
		case 2:
			count=10;
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[8])));
			do{
				answer=sendCommand3(str_aux1, OK_RESPONSE, ERROR_IP, ERROR, 1000, 0);
				count--;
			}while ((count != 0) && (answer != 1));
			break;
	}
	
	if (answer == 2)
	{	
		return -6;
	}
	else if (answer != 1)
	{	
		return -3;
	}
	
	return 1;
	
}

/* createMultiSocket(uint8_t, uint16_t) - Opens a UDP port to listen in multi client mode
 *
 * This function opens a UDP port to listen 
 *
 * Returns '1' on success, '0' if error, '-2' if not configured in multi client mode, '-3' if network is closed,
 * '-4' error opening the connection with CME error code available and '-5' error opening the connection with IP error code available
*/
int8_t Wasp3G::createMultiSocket(uint8_t n_link, uint16_t local_port){
	return (createMultiSocket(n_link, "", local_port));
}

/* createMultiSocket(uint8_t, const char*, uint16_t) - creates a TCP/IP connection to the specified IP and PORT in multi client mode
 *
 * This function creates a TCP/IP connection to the specified IP and PORT in multi client mode
 *
 * Returns '1' on success, '0' if error, '-2' if not configured in multi client mode, '-3' if network is closed,
 * '-4' error opening the connection with CME error code available and '-5' error opening the connection with IP error code available
*/
int8_t Wasp3G::createMultiSocket(uint8_t n_link, const char* serverIP, uint16_t server_port){
	
	int8_t answer, count;
	
	// Checks the connection mode and the network status flags:
	if ((IP_flags & 0x02) != 2)
	{
		return -2;
	}
	
	if ((IP_flags & 0x04) != 4)
	{
		return -3;
	}
	
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[9])));
	if (serverIP[0] == '\0')
	{
		// UDP connections
		sprintf(buffer_3G, "%s%d,\"UDP\",,,%u", str_aux1, n_link,server_port);
	}
	else
	{
		// TCP connections
		sprintf(buffer_3G, "%s%d,\"TCP\",\"%s\",%u", str_aux1, n_link, serverIP, server_port);
	}
	
	count=10;
	do{
		answer=sendCommand3(buffer_3G, OK_RESPONSE, ERROR_CME, ERROR_IP, 1000, 0);
		count--;
	}while ((count != 0) && (answer != 1));
	
	if (answer == 2)
	{	
		return -4;
	}
	else if (answer == 3)
	{	
		return -5;
	}
	else if (answer == 0)
	{
		return 0;
	}
	
	return 1;
	
}

/* sendData(const char*) - Sends the data througth a socket (TCP in single connection)
 *
 * This function sends the data througth a socket
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME error code available and '-3' if error with IP error code available
*/
int8_t Wasp3G::sendData(const char* data){
	return (sendData( 0, (uint8_t*)data, "", 0, strlen(data)));
}

/* sendData(uint8_t, const char*) - Sends the data througth a socket (TCP in multiple connection)
 *
 * This function sends the data througth a socket
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME error code available and '-3' if error with IP error code available
*/
int8_t Wasp3G::sendData(uint8_t n_link, const char* data){
	return (sendData( n_link, (uint8_t*)data, "", 0, strlen(data)));
}

/* sendData( const char*, const char*, uint16_t) - Sends the data througth a socket (UDP in single connection)
 *
 * This function sends the data througth a socket
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME error code available and '-3' if error with IP error code available
*/
int8_t Wasp3G::sendData(const char* data, const char* ip, uint16_t port){
	return (sendData( 0, (uint8_t*)data, ip, port, strlen(data)));
}

/* sendData(uint8_t, const char*, const char*, uint16_t) - Sends the data througth a socket (UDP in multiple connection)
 *
 * This function sends the data througth a socket
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME error code available and '-3' if error with IP error code available
*/
int8_t Wasp3G::sendData(uint8_t n_link, const char* data, const char* ip, uint16_t port){
	return (sendData( 0, (uint8_t*)data, ip, port, strlen(data)));
}

/* sendData(const char*) - Sends the data througth a socket (TCP in single connection with data length include)
 *
 * This function sends the data througth a socket
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME error code available and '-3' if error with IP error code available
*/
int8_t Wasp3G::sendData(uint8_t* data, int16_t length){
	return (sendData( 0, data, "", 0, length));
}

/* sendData(uint8_t, const char*) - Sends the data througth a socket (TCP in multiple connection with data length include)
 *
 * This function sends the data througth a socket
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME error code available and '-3' if error with IP error code available
*/
int8_t Wasp3G::sendData(uint8_t n_link, uint8_t* data, int16_t length){
	return (sendData( n_link, data, "", 0, length));
}

/* sendData( const char*, const char*, uint16_t) - Sends the data througth a socket (UDP in single connection with data length include)
 *
 * This function sends the data througth a socket
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME error code available and '-3' if error with IP error code available
*/
int8_t Wasp3G::sendData(uint8_t* data, const char* ip, uint16_t port, int16_t length){
	return (sendData( 0, data, ip, port, length));
}

/* sendData(uint8_t, const char*, const char*, uint16_t) - Sends the data througth a socket (base function)
 *
 * This function sends the data througth a socket
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME error code available and '-3' if error with IP error code available
*/
int8_t Wasp3G::sendData(uint8_t n_link, uint8_t* data, const char* ip, uint16_t port, int16_t length){

	int8_t answer;
	uint16_t counter;
	
	if (IP_flags & 0x02)
	{
		// Multiple connection mode
		if (port == 0)
		{
			// TCP link
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[10])));
			sprintf(buffer_3G, "%s%d,%d", str_aux1, n_link, length);
			answer = sendCommand3(buffer_3G, "\r\n>", ERROR_CME, ERROR_IP, 2000, 0);
			if (answer == 1)
			{	
				#if _3G_debug_mode>1	
					USB.println(F("Sending data (multiple connection - TCP)..."));
				#endif
				for (counter = 0; counter < length; counter++)
				{
					printByte(data[counter],_socket);
					#if _3G_debug_mode>1	
						USB.print(data[counter], HEX);
						USB.print(" ");
					#endif	
				}
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[12])));
				answer = waitForData(str_aux1, DEFAULT_TIMEOUT, 0, 0);
				#if _3G_debug_mode>0	
					USB.print(F("Answer for send: "));
					USB.println(answer, DEC);
				#endif
			}
		}
		else
		{
			// UDP link
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[10])));
			sprintf(buffer_3G, "%s%d,%d,\"%s\",%u", str_aux1, n_link, length, ip, port);
			answer = sendCommand3(buffer_3G, "\r\n>", ERROR_CME, ERROR_IP, 2000, 0);
			if (answer == 1)
			{	
				#if _3G_debug_mode>1	
					USB.println(F("Sending data (multiple connection - UDP)..."));
				#endif
				for (counter = 0; counter < length; counter++)
				{
					printByte(data[counter],_socket);
					#if _3G_debug_mode>1	
						USB.print(data[counter], HEX);
						USB.print(" ");
					#endif	
				}
				answer = waitForData(OK_RESPONSE, DEFAULT_TIMEOUT, 0, 0);
				#if _3G_debug_mode>0	
					USB.print(F("Answer for send: "));
					USB.println(answer, DEC);
				#endif
			}
			
		}
		
		if (answer == 3)
		{
			return -3;
		}
		else if (answer == 2)
		{
			return -2;
		}
		else if (answer == 0)
		{
			return 0;
		}
	}
	else
	{
		// Single connection mode
		if (port == 0)
		{
			// TCP link
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[6])));
			sprintf(buffer_3G, "%s%d", str_aux1, length);
			answer = sendCommand2(buffer_3G, "\r\n>", ERROR_IP);
			if (answer == 1)
			{	
				#if _3G_debug_mode>1	
					USB.println(F("Sending data (single connection - TCP)..."));
				#endif
				for (counter = 0; counter < length; counter++)
				{
					printByte(data[counter],_socket);
					#if _3G_debug_mode>1	
						USB.print(data[counter], HEX);
						USB.print(" ");
					#endif	
				}
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[12])));
				answer = waitForData(str_aux1, DEFAULT_TIMEOUT, 0, 0);
				#if _3G_debug_mode>0	
					USB.print(F("Answer for send: "));
					USB.println(answer, DEC);
				#endif
			}
		}
		else
		{
			// UDP link
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[7])));
			sprintf(buffer_3G, "%s%d,\"%s\",%u", str_aux1, length, ip, port);
			answer = sendCommand2(buffer_3G, "\r\n>", ERROR_IP);
			if (answer == 1)
			{		
				#if _3G_debug_mode>1	
					USB.println(F("Sending data (single connection - UDP)..."));
				#endif	
				for (counter = 0; counter < length; counter++)
				{
					printByte(data[counter],_socket);
					#if _3G_debug_mode>1	
						USB.print(data[counter], HEX);
						USB.print(" ");
					#endif	
				}
				answer = waitForData(OK_RESPONSE, DEFAULT_TIMEOUT, 0, 0);
				#if _3G_debug_mode>0	
					USB.print(F("Answer for send: "));
					USB.println(answer, DEC);
				#endif
			}
		}
		
		if (answer == 2)
		{
			return -3;
		}
		else if (answer == 0)
		{
			return 0;
		}
	}	
	
	return 1;
}

/* closeMultiSocket(uint8_t) - Closes a socket opened with createMultiSocket in multi client mode
 *
 * This function closes a socket opened with createMultiSocket in multi client mode
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME error code available and '-3' if error with IP error code available
*/
int8_t Wasp3G::closeMultiSocket(uint8_t n_link){
	
	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[11])));
	sprintf(buffer_3G, "%s%d", str_aux1, n_link);
	answer=sendCommand3(buffer_3G, OK_RESPONSE, ERROR_CME, ERROR_IP, 1000, 0);
	
	if (answer == 3)
	{
		return -3;
	}
	else if (answer == 2)
	{
		return -2;
	}
	
	return answer;
	
}

/* readIPdata() - Manages the IP data from the 3G module
 *
 * This function manages the IP data from the 3G module
 *
 * Stores the IP address from the sender in IP_dir and the data in 'buffer_3G'
 *
 * Returns '1' on success, '0' if error and '-2' if error with CME error code available
*/
int16_t Wasp3G::readIPdata(){

	int counter;
	int16_t data_length = 0;
	int8_t answer;
	
	
	#if _3G_debug_mode>0
		USB.print(F("Inside readIPdata: "));
		USB.println(IP_dir);
	#endif	
	// Checks if there is the IP address and port:
	if (parse(buffer_3G, "RECV FROM:"))
	{
		counter = strchr(buffer_3G, ':') - buffer_3G;
		answer = 0;
		counter++;
		do{
			IP_dir[answer] = buffer_3G[counter + answer];
			answer++;
		}while ((buffer_3G[counter+answer] != 0x0D) && (answer < 22));
		IP_dir[answer] = '\0';
		#if _3G_debug_mode>0
			USB.print(F("Data from: "));
			USB.println(IP_dir);
		#endif
	}
	
	// Checks if there is the data length header:
	if (parse(buffer_3G, "+IPD"))
	{
		counter=strchr(buffer_3G, '+') - buffer_3G;
		answer=0;
		counter += 4;
		do{
			data_length *= 10;
			data_length += buffer_3G[counter+answer] - 0x30;
			answer++;
		}while ((buffer_3G[counter+answer] != '\r') && (answer < 6));
		#if _3G_debug_mode>0
			USB.print(F("Data length: "));
			USB.println(data_length, DEC);
		#endif
	}
	else if (parse(buffer_3G, "+RECEIVE,"))
	{
		counter=strchr(buffer_3G, '+') - buffer_3G;
		answer=0;
		counter += 9;
		n_connection=buffer_3G[counter];
		#if _3G_debug_mode>0
			USB.print(F("No of connection: "));
			USB.println(char(n_connection));
		#endif
		serialRead(_socket);
		counter += 2;
		
		do{
			data_length *= 10;
			data_length += buffer_3G[counter+answer] - 0x30;
			answer++;
		}while ((buffer_3G[counter+answer] != ':') && (answer < 6));
		#if _3G_debug_mode>0
			USB.print(F("Data length: "));
			USB.println(data_length, DEC);
		#endif
		counter += 1;
	}
	else
	{			
		#if _3G_debug_mode>0
			USB.println(F("No data length header!!"));
		#endif
		return -2;
	}
	
	// Gets the data and stores in buffer_3G:
	counter+=2;
	if (data_length != 0)
	{
		strncpy(buffer_3G, buffer_3G + counter + answer, data_length);
		buffer_3G[data_length] = '\0';
		
	}
	
	return data_length;

}

/* listClients() - Lists the clients connected to the module
 *
 * This function lists the clients connected to the module
 *
 * Stores the number of connection, IP address and port from the client in 'buffer_3G'. Each line is a different client.
 *
 * Returns '1' on success, '0' if error and '-2' if error with IP error code available
*/
int8_t Wasp3G::listClients(){

	int counter;
	int8_t answer;
	unsigned long previous;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[14])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[15])));
	answer=sendCommand2(str_aux1, str_aux2, ERROR_IP);
	
	buffer_3G[0] = '\0';
	
	if (answer == 2)
	{
		return -2;
	}
	else if (answer == 1)
	{
		previous=millis();
		counter=0;
		answer=1;
		do{
			previous=millis();
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000));
			buffer_3G[counter]=serialRead(_socket);
			counter++;
			if (buffer_3G[counter-1] == '\n')
			{
				answer=waitForData(str_aux2, OK_RESPONSE, DEFAULT_TIMEOUT, 0, 0);
			}
		}while ((answer == 1) && ((millis()-previous) < 3000));
		buffer_3G[counter]='\0';
	}
	
	return answer;

}

/* openClient(uint8_t) - Opens the connection from a client to the module
 *
 * This function opens the connection from a client to the module
 *
 * Returns '1' on success, '0' if error and '-2' if error with IP error code available
*/
int8_t Wasp3G::openClient(uint8_t n_client){

	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[16])));
	sprintf(buffer_3G, "%s%u", str_aux1, n_client);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_IP);
	
	if (answer == 2)
	{
		return -2;
	}
	
	return answer;

}

/* closeClient(uint8_t) - Closes a client connected to the module
 *
 * This function closes a client connected to the module
 *
 * Returns '1' on success, '0' if error and '-2' if error with IP error code available
*/
int8_t Wasp3G::closeClient(uint8_t n_client){

	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[17])));
	sprintf(buffer_3G, "%s%u", str_aux1, n_client);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR_IP);
	
	if (answer == 2)
	{
		return -2;
	}
	
	return answer;

}

/* getIP() - Gets the IP address assigned to the module
 *
 * This function gets the IP address assigned to the module and stores it in 'buffer_3G'.
 *
 * Returns '1' on success, '0' if error and -2 if error with IP error code available
*/
int8_t Wasp3G::getIP(){

	int counter;
	int8_t answer;
	unsigned long previous;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[3])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[4])));
	answer = sendCommand2(str_aux1, str_aux2, ERROR_IP);
	
	if (answer == 2)
	{
		return -2;
	}
	
	if (answer == 1)
	{
		previous = millis();
		counter = 0;
		do{
			previous = millis();
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000));
			buffer_3G[counter] = serialRead(_socket);
			counter++;
		}while ((buffer_3G[counter-1] != '\r') && ((millis()-previous) < 3000));
		buffer_3G[counter] = '\0';
	}	
	
	return answer;
}

/* QueryDomainfromIP(const char*) - Queries the domain name from IP address.
 *
 * This function queries the domain name from IP address and stores it in 'buffer_3G'.
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::QueryDomainfromIP(const char* ip){

	int counter;
	int8_t answer;
	unsigned long previous;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[20])));
	sprintf(buffer_3G, "%s=\"%s\"", str_aux1, ip);	
	answer = sendCommand2(buffer_3G, str_aux1, ERROR);
	
	if (answer == 1)
	{	
		serialRead(_socket);
		serialRead(_socket);
		
		if (serialRead(_socket) == '1')
		{
			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000));
			}while ((serialRead(_socket) != '"') && ((millis() - previous) < 1000));
			 
			previous = millis();
			counter = 0;
			do{
				previous = millis();
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000));
				buffer_3G[counter] = serialRead(_socket);
				counter++;
			}while ((buffer_3G[counter-1] != '"') && ((millis() - previous) < 1000));
			buffer_3G[counter-1] = '\0';
			
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

/* QueryIPfromDomain(const char*) - Queries the IP from domain name address.
 *
 * This function queries the IP address from domain name and stores it in 'buffer_3G'.
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::QueryIPfromDomain(const char* domain){

	int counter;
	int8_t answer;
	unsigned long previous;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[19])));
	sprintf(buffer_3G, "%s=\"%s\"", str_aux1, domain);	
	answer=sendCommand2(buffer_3G, str_aux1, ERROR);
	
	if (answer == 1)
	{	
		serialRead(_socket);
		serialRead(_socket);
		
		if (serialRead(_socket) == '1')
		{
			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000));
			}while ((serialRead(_socket) != '"') && ((millis() - previous) < 1000));
			
			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000));
			}while ((serialRead(_socket) != '"') && ((millis() - previous) < 1000));
			
			
			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000));
			}while ((serialRead(_socket) != '"') && ((millis() - previous) < 1000));
			 
			previous = millis();
			counter = 0;
			do{
				previous = millis();
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000));
				buffer_3G[counter] = serialRead(_socket);
				counter++;
			}while ((buffer_3G[counter-1] != '"') && ((millis() - previous) < 1000));
			buffer_3G[counter-1] = '\0';
			
			return 1;
			
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
}

/*switchtoDataMode() - switchs from command mode to data mode
 *
 * This function switchs from command mode to data modes
 *
 * Returns '1' on success, '0' if error and '-2' if connection is not successfully resumed
*/
int8_t Wasp3G::switchtoDataMode(){
	
	uint8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[21])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[22])));
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_IP[23])));
	answer = sendCommand2(str_aux1, str_aux2, str_aux3);

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
int8_t Wasp3G::switchtoCommandMode(){

	uint8_t answer;
	
	delay(1000);	//waits one second after the last data send
	printByte('+', _socket);
	printByte('+', _socket);
	printByte('+', _socket);
	answer = waitForData(OK_RESPONSE, 500, 0, 0);
	
	if (answer != 1)
	{
		return 0;
	}
	return 1;
}

#endif


//XMODEM functions
/* getXmodemFile(const char* , const char*) - Gets a file from 3G/GPRS Board and stores it in Waspmote
 *
 * This function gets a file from 3G/GPRS Board and stores it in Waspmote with Xmodem protocol
 *
 * Returns '1' if succes, '0' if error, '-2' if error going to root directory in Waspmote's SD, '-3' if error creating the file in Waspmote,
 * '-4' if error if file not exist in 3G/GPRS module and '-5' if error getting the file
*/
int8_t Wasp3G::getXModemFile(const char* origin, const char* destiny){

	int aux;
	uint8_t checksum, error_counter=0;
	unsigned long previous;
	long file_size;
	
	// Enables microSD card on Waspmote:
	SD.ON();
	
	// First goes to the main directory:
	if (SD.goRoot() != 1)
	{
		SD.OFF();
		return -2;
	}
	
	// Then creates the file into the SD of Waspmote:
	#if _3G_debug_mode>0
		USB.print(F("Origin: "));
		USB.println(origin);
		USB.print(F("Destiny: "));
		USB.println(destiny);
	#endif
	
	aux = SD.create(destiny);
	if (aux == 2)
	{
		SD.OFF();
		return -3;
	}
	
	// Gets the file size
	file_size = getFileSize(origin);
	
	// Sends AT command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[50])));
	sprintf(buffer_3G,"%s=\"%s\"",str_aux1, origin);
	aux=sendCommand2(buffer_3G,OK_RESPONSE,"FILE NOT EXISTING");
	
	if (aux == 0 || aux == 2)
	{		
		SD.OFF();
		if (aux == 2)
		{		
			return -4;
		}
		return 0;
	}
	else
	{
		// Cleans input buffer:
		while (serialAvailable(_socket) != 0)
		{
			serialRead(_socket);
		}
		
		// Starts the transmission and gets the data:
		serialWrite(0x15, _socket);
		do{
			aux=0;
			previous=millis();

			while ((serialAvailable(_socket) < 134) && ((millis()-previous) <= 3000));
			for(int x=0; x < 135; x++){
				buffer_3G[x]=serialRead(_socket);
			}
			
			#if _3G_debug_mode>0
				if (buffer_3G[1] == 0)
				{
					USB.println(F("*******************************"));
				}
				USB.print(F("Header value: "));
				USB.print(buffer_3G[0],DEC);
				USB.print(F("\tPacket numbers: "));
				USB.print(buffer_3G[1],DEC);
				USB.print(F(";  "));
				USB.print(buffer_3G[2],DEC);
				USB.print(F("\tChecksum value: "));
				USB.printHex(buffer_3G[131]);
			#endif
			checksum=buffer_3G[131];
			
			// If data isn't an EOT saves data in SD file
			if (buffer_3G[0] != 0x04)
			{
				
				for (int x=0; x < 128; x++)
				{
					buffer_3G[x]=buffer_3G[x+3];
				}
				buffer_3G[128]='\0';
				#if _3G_debug_mode>0	
					USB.print(F("\tGenerated checksum: "));
					USB.printHex(getXModemCheckSum((uint8_t*)buffer_3G));
				#endif
				
				
				// Cleans the input buffer
				while (serialAvailable(_socket) != 0)
				{
					serialRead(_socket);
				}
				
				
				// Checks the checksum byte
				if(checksum == getXModemCheckSum((uint8_t*)buffer_3G))
				{	
					#if _3G_debug_mode>0
						USB.print(F("\tChecksum correct"));
					#endif
					
					// Stores the data into the SD card
					if (file_size < 128)
					{
						// Last data packet
						aux = 126;
						while ((buffer_3G[aux] == 0x1A) && (aux > 0))
						{
							aux--;
						}
						SD.writeSD(destiny, (uint8_t*)buffer_3G, SD.getFileSize(destiny), aux+1);
					}
					else
					{
						SD.writeSD(destiny, (uint8_t*)buffer_3G, SD.getFileSize(destiny), 128);
						file_size -= 128;
					}
					
					error_counter = 0;
					serialWrite(0x06,_socket);
				}
				else
				{
					error_counter++;
					serialWrite(0x15,_socket);
					#if _3G_debug_mode>0
						USB.println(F("\tChecksum error"));
						USB.print(F("Error counter: "));
						USB.println(error_counter, DEC);
					#endif
				}
					
				#if _3G_debug_mode>0
					USB.print(F("\tSize: "));
					USB.println(SD.getFileSize(destiny), DEC);
				#endif
				
				#if _3G_debug_mode>1	
					USB.print(F("Data field: "));
					for (int x=0; x <128; x++)
					{
						USB.printHex(buffer_3G[x]);
						USB.print(F(" "));
					}
					USB.println(F(""));
				#endif	
				
				buffer_3G[0] = 0x00;
			}
			else
			{
				#if _3G_debug_mode>0
					USB.println(F("EOF"));
				#endif
				serialWrite(0x06,_socket);
			}
		}while ((buffer_3G[0] != 0x04) && (error_counter < 10));
		
		if (error_counter < 10)
		{
				aux = SD.getFileSize(destiny);
				
		}
	}
	
	SD.OFF();
	
	if (error_counter >= 10)
	{
		return -5;
	}
	else
	{	
		return 1;
	}
}

//File system functions
/* goRoot(uint8_t) - It goes to the root of the desired unit (0 for C internal memory and 1 for the microSD card)
 *
 * This function changes the unit and goes to the root of the desired unit (0 for C internal memory and 1 for the microSD card)
 *
 * Returns '1' if succes, '-2' if error changing the unit or '0' if error going to the root
*/
int8_t Wasp3G::goRoot(uint8_t unit){
	
	int8_t answer;
	int x;
	unsigned long previous;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[16])));
	if (unit == 0) // selects internal memory (C: unit)
	{
		sprintf(buffer_3G, "%sC:", str_aux1);
	}	
	else if (unit == 1) // selects microSD memory (D: unit)
	{
		sprintf(buffer_3G, "%sD:", str_aux1);
	}
	
	// first changes to the desired unit
	answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
	
	if (answer == 1)
	{
		do{
			// then goes to the root
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[17])));
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[18])));
			answer = sendCommand2(str_aux1, str_aux2, ERROR);
			if (answer == 1)
			{
				previous = millis();
				x = 0;
				do{
					while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000));
					buffer_3G[0] = serialRead(_socket);
					if (buffer_3G[0] == '/')
					{
						x++;
					}
				}while ((buffer_3G[0] != '\r') && ((millis()-previous) < 3000));
				
				#if _3G_debug_mode>0
					USB.print(F("Directory level: "));
					USB.println(x, DEC);
				#endif
			}
			else
			{
				return 0;
			}
		}while (x > 1);
		
		return 1;
	}
	else
	{
		return -2;
	}
	
	
}

/* cd(const char*) - It changes the directory in the actual unit
 *
 * This function changes the directory in the actual unit
 *
 * Returns '1' if success and '0' if error
*/
int8_t Wasp3G::cd(const char* path){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[16])));
	sprintf(buffer_3G, "%s%s", str_aux1, path);
	
	if (sendCommand2(buffer_3G, OK_RESPONSE, ERROR) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* getFileSize(const char*) - Gets the size of a given file in the current directory
 *
 * This function changes the directory in the current directory
 *
 * Returns the file_size if success and '-2' if error
*/
long Wasp3G::getFileSize(const char* filename){

	long file_size=0, previous;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[19])));
	sprintf(buffer_3G, "%s%s", str_aux1, filename);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[20])));
	if (sendCommand2(buffer_3G, str_aux1, ERROR))
	{
		previous = millis();
		// waits for data available
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000));
		buffer_3G[0] = serialRead(_socket);
		
		// Gets the file size
		do{
			file_size *= 10;
			file_size += buffer_3G[0] - 0x30;
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000));
			buffer_3G[0] = serialRead(_socket);
		}while ((buffer_3G[0] != ',') && ((millis()-previous) < 3000));
		
		#if _3G_debug_mode>0
			USB.print(F("File size: "));
			USB.println(file_size, DEC);
		#endif
			
		return file_size;
	}
	else
	{
		return -2;
	}
}

/* del(const char*) - Deletes a file in the current directory
 *
 * This function deletes a file in the current directory
 *
 * Returns '1' if success and '0' if error
*/
int8_t Wasp3G::del(const char* filename){
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[21])));
	sprintf(buffer_3G, "%s%s", str_aux1, filename);
	if (sendCommand2(buffer_3G, OK_RESPONSE, ERROR) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* isSD() - Checks if microSD card is available
 *
 * This function checks if microSD card is available
 *
 * Returns '1' if is present and '0' if not
*/
int8_t Wasp3G::isSD(){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[22])));
	sprintf(buffer_3G, "%s?", str_aux1);
	return sendCommand1(buffer_3G, OK_RESPONSE);
}

/* ls(int8_t ) - Stores in 'buffer_3G' a list of subdirectories and files in the current directory 
 *
 * This function stores in 'buffer_3G' a list of subdirectories and files in the current directory
 *
 * The parameter 'type' select the kind of list: '0' list both subdirectories and files, '1' list subdirectories only and '2' list files only
 *
 * Returns '1' if success, '2' if no files or subdirectories and '0' if error
*/ 
int8_t Wasp3G::ls(int8_t type){

	unsigned long previous;
	int counter=0, answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[23])));
	sprintf(buffer_3G, "%s=%d", str_aux1, type);
	answer = sendCommand3( buffer_3G, str_aux1, OK_RESPONSE, ERROR, 1000, 0);
	if (answer == 1)
	{
		previous=millis();
		counter = 0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000));
			buffer_3G[counter] = serialRead(_socket);
			#if _3G_debug_mode>1
				USB.print(buffer_3G[counter]);
			#endif
			counter++;		
		}while ((counter < BUFFER_SIZE) && !((buffer_3G[counter-2] == 'O') && (buffer_3G[counter-1] == 'K')) && ((millis()-previous) < 3000));
		
		if ((buffer_3G[counter-2] == 'O') && (buffer_3G[counter-1] == 'K'))
		{
			buffer_3G[counter-6] = '\0';
		}
		else
		{
			buffer_3G[counter-1] = '\0';
		}
		
		return 1;
	}
	else if (answer == 2)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}


//Miscelaneus functions
/* getRSSI() - Gets RSSI level
 *
 * This function gets the RSSI level
 *
 * Returns the value in -dBm or '0' if error
*/
int8_t Wasp3G::getRSSI(){

	int8_t answer, count;
	unsigned long previous;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[24])));
	answer = sendCommand2(str_aux1, str_aux1, ERROR);
	
	if (answer == 1)
	{
		// if the commands answer with +CSQ: reads the value and convert it
		previous = millis();
		serialRead(_socket);
		serialRead(_socket);
		answer = 0;
		count = serialRead(_socket);
		do{
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 1000));
			answer *= 10;
			answer += count-0x30;
			count = serialRead(_socket);
 		}while ((count != ',') && ((millis()-previous) < 1000));
		
		#if _3G_debug_mode>0
			USB.print(F("Raw RSSI: "));
			USB.println(answer, DEC);
		#endif
		
		// converts the answer from the command to dBm
		switch(answer)
		{
			case 0:
				answer = -113;
				break;
			case 1:
				answer = -111;
				break;
			case 31:
				answer = 0;
				break;
			default:
				answer = (answer * 2) - 109;
		}
		
		return answer;
	}
	else
	{
		return 0;
	}
}

/* getCellsysInfo() - Gets cell system information. Only in GSM
 *
 * This function gets cell system information. 
 *
 * Information is stored in 'buffer_3G'
 *
 * Returns '1' on success, '0' if error, '-1' if timeout and '-2' if error restoring the baudrate (data are valid)
*/
int8_t Wasp3G::getCellsysInfo(){

	int8_t answer;
	int x;
	unsigned long previous;
	char command[15];
	
	// reduces the baudrate
	changeBaudrate(4800);
	getIfReady();	
	
	buffer_3G[0] = '\0';
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[34])));
	answer = sendCommand1(str_aux1, str_aux1);

	if (answer == 1)
	{
		x = 0;
		serialRead(_socket); // skips ':'
		previous = millis();
		do{
			do{
				// reads from socket 1
				buffer_3G[x] = serialRead(_socket);
				if (buffer_3G[x] != -1)
				{	
					x++;
				}	
				else
				{
					delay(1);
				}
			}while ((buffer_3G[x-1] != '\r') && ((millis() - previous) < 5000));
			
			if ((millis() - previous) < 5000)
			{
				// no timeout, waits for the next line or for the OK
				answer = waitForData(OK_RESPONSE, str_aux1, 500, 0, 0);
			}
			else
			{
				// timeout
				answer = -1;
			}
			serialRead(_socket); // skips ':'
			buffer_3G[x] = '\r'; // next line
			x++;
			buffer_3G[x] = '\n';
			x++;			
			
		}while (answer == 2);
		buffer_3G[x-3] = '\0';
		
	}
	
	// Changes to default baudrate
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));
	sprintf(command, "%s%ld", str_aux1, _baudRate);
	x = sendCommand2(command, OK_RESPONSE, ERROR);	
	if (x == 2)
	{
		return -4;
	}
	else if (x == 1) // If the command is executed by the 3G module, changes the Wasmote's baudrate
	{
		beginSerial(_baudRate, _socket);
	}
		
	return answer;
}

/* getCellchannel() - Gets cell channel information. Only during a GSM call
 *
 * This function gets cell channel information. 
 *
 * Information is stored in 'buffer_3G'
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::getCellchannel(){

	int8_t answer;
	int x;
	unsigned long previous;
	
	buffer_3G[0] = '\0';
	
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[35])));
	answer = sendCommand1(str_aux1, str_aux1);

	if (answer == 1)
	{
		serialRead(_socket); // skips ':'
		serialRead(_socket); // skips ' '
		x = 0;
		previous = millis();
		do{
			// reads from socket 1
			buffer_3G[x] = serialRead(_socket);
			if (buffer_3G[x] != -1)
			{	
				x++;
			}	
			else
			{
				delay(1);
			}
		}while (!((buffer_3G[x-1] == 'K') && (buffer_3G[x-2] == 'O')) && ((millis() - previous) < 5000));
		buffer_3G[x-4] = '\0';
	}
	
	return answer;
}

/* getCellradioparam() - Gets serving cell radio parameters. Only during a GSM call
 *
 * This function gets serving cell radio parameters.
 *
 * Information is stored in 'buffer_3G'.
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::getCellradioparam(){

	int8_t answer;
	int x;
	unsigned long previous;
	
	buffer_3G[0] = '\0';
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[36])));
	answer = sendCommand1(str_aux1, str_aux1);

	if (answer == 1)
	{
		serialRead(_socket); // skips ':'
		serialRead(_socket); // skips ' '
		x = 0;
		previous = millis();
		do{			
			// reads from socket 1
			buffer_3G[x] = serialRead(_socket);
			if (buffer_3G[x] != -1)
			{	
				x++;
			}	
			else
			{
				delay(1);
			}
		}while (!((buffer_3G[x-1] == 'K') && (buffer_3G[x-2] == 'O')) && ((millis() - previous) < 5000));
		buffer_3G[x-4] = '\0';
	}
	
	return answer;
}

/* setPreferedServiceDomain() - Sets preferred service domain selection
 *
 * This function sets network system mode preference.
 *
 * Allows '0' for CS Only, '1' for PS Only and '2' for CS + PS
 *
 * Returns '1' if success and '0' if error
*/
int8_t Wasp3G::setPreferedServiceDomain(uint8_t mode){
		
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[29])));
	sprintf(buffer_3G, "%s=%d", str_aux1, mode);
	// Sends the command:
	return (sendCommand1(buffer_3G, OK_RESPONSE));
}

/* scanNetworkchannels() - Scans the network band channels specified 
 *
 * This function scans the network band channels specified. 
 *
 * The input parameter 'mode' set the verbose response or only numeric data
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::scanNetworkchannels(int chn_start, int chn_end, bool mode){

	int8_t answer, x;
	unsigned long previous;
	
	if (mode == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[39])));
		sprintf(buffer_3G, "%s=%d,%d", str_aux1, chn_start, chn_end);
	}
	else
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[40])));
		sprintf(buffer_3G, "%s=%d,%d", str_aux1, chn_start, chn_end);	
	}
	// Sends the command:
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[41])));
	answer=sendCommand1(buffer_3G, str_aux1, 1000, 0);

	if (answer == 1)
	{
		x = 0;
		previous = millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000));
			buffer_3G[x] = serialRead(_socket);
			x++;
		}while ((buffer_3G[x-1] != 'N') && ((millis() - previous) < 10000) && (x < BUFFER_SIZE));
		buffer_3G[x-3] = '\0';
	}
	
	return answer;
}

/* getUEsysInfo() - Inquire UE system information
 *
 * This function inquires UE system information. 
 *
 * Information are stored in 'buffer_3G' it's different from 2G or 3G
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::getUEsysInfo(){

	int8_t answer, x;
	unsigned long previous;
	
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[30])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[31])));
	answer=sendCommand1(str_aux1, str_aux2);

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000));
			buffer_3G[x]=serialRead(_socket);
			x++;
		}while ((buffer_3G[x-1] != '\r') && ((millis() - previous) < 5000));
		buffer_3G[x-1]='\0';
	}
	
	return answer;
}

/* showsNetworkMode() - Shows network system mode
 *
 * This function shows network system mode.
 *
 * Returns '0' if error, '-1' if error with CME error code available, '1'for no service,
 *     '2' for GSM, '3' for GPRS, '4' for EGPRS (EDGE), '5' for WCDMA,
 *    '6' for HSDPA only, '7' for HSUPA only and '8' for HSPA (HSDPA and HSUPA)
*/
int8_t Wasp3G::showsNetworkMode(){

	int8_t answer;
	
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[32])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[33])));
	answer=sendCommand2(str_aux1, str_aux2, ERROR_CME);

	if (answer == 2)
	{
		return -2;
	}
	else if (answer == 1)
	{
		serialRead(_socket);
		serialRead(_socket);
		return (serialRead(_socket)-0x2F);	
	}
	
	return answer;
}

/* WCDMAsysInfo() - Shows the mobile phone system information in WCDMA
 *
 * This function shows the mobile phone system information in WCDMA.
 *
 * Information are stored in 'buffer_3G'.
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::WCDMAsysInfo(){

	int8_t answer, x;
	unsigned long previous;
	
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[37])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[38])));
	answer=sendCommand1(str_aux1, str_aux2);

	if (answer == 1)
	{
		// Gets info from active cell:
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000));
			buffer_3G[x]=serialRead(_socket);
			x++;
		}while ((buffer_3G[x-1] != '\n') && ((millis() - previous) < 5000));
		
		waitForData(str_aux2, 2, 0, 0);
		
		// Gets info from sync neighbor cell
		
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000));
			buffer_3G[x]=serialRead(_socket);
			x++;
		}while ((buffer_3G[x-1] != '\n') && ((millis() - previous) < 5000));
		
		waitForData(str_aux2, 2, 0, 0);
		
		// Gets info from async neighbor cell
		
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000));
			buffer_3G[x]=serialRead(_socket);
			x++;
		}while ((buffer_3G[x-1] != '\n') && ((millis() - previous) < 5000));
		buffer_3G[x-1]='\0';
	}
	
	return answer;
}

/* setNetworkMode() - Sets network system mode preference
 *
 * This function sets network system mode preference.
 *
 * Allows '0' for automatic, '1' for GSM only and '2' for WCDMA only
 *
 * Returns '1' if success and '0' if error
*/
int8_t Wasp3G::setNetworkMode(uint8_t mode){
		
	// Selects the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[26])));
	switch (mode)
	{
		case 0:
			sprintf(buffer_3G, "%s=2", str_aux1);
			break;
		case 1:
			sprintf(buffer_3G, "%s=13", str_aux1);
			break;
		case 2:
			sprintf(buffer_3G, "%s=14", str_aux1);
			break;
	}
	
	// Sends the command:
	return (sendCommand1(buffer_3G, OK_RESPONSE));
}

/* setNetworkBand(int, int, int) - Sets the band preference.
 *
 * This function sets the band preference.
 *
 * Returns '1' if success and '0' if error
*/
int8_t Wasp3G::setNetworkBand(int high_zone, int mid_zone, int low_zone){
	
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[27])));
	sprintf(buffer_3G, "%s=0x%04X0000%04X%04X", str_aux1, high_zone, mid_zone, low_zone);
	return (sendCommand1(buffer_3G, OK_RESPONSE));
}

/* modeAcquisitionsOrder(uint8_t) - Sets the preferences for order of acquisitions 
 *
 * This function sets the preferences for order of acquisitions 
 *
 * Allows '0' for automatic,'1' GSM,WCDMA and '2' for WCDMA,GSM
 *
 * Returns '1' if success and '0' if error
*/
int8_t Wasp3G::modeAcquisitionsOrder(uint8_t mode){
	
	// Selects the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[28])));
	sprintf(buffer_3G, "%s=%d", str_aux1, mode);
	// Sends the command:
	return (sendCommand1(buffer_3G, OK_RESPONSE));
}

/* selectStorage(uint8_t) - Selects the storage location
 *
 * This function selects the storage location
 *
 * Returns '1' on success, '0' or '-2' if error
*/
int8_t Wasp3G::selectStorage(uint8_t destination){
	
	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[42])));
	sprintf(buffer_3G, "%s%d", str_aux1, destination);
	
	// Sends the command:
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);

	if (answer == 2)
	{
			return -2;
	}
	
	return answer;
}

/* changeBaudrate(long) - Changes the baudrate between Waspmote and 3G module
 *
 * This function changes the baudrate between Waspmote and 3G module
 *
 * Returns '1' on success, '0' or '-2' if error
*/
int8_t Wasp3G::changeBaudrate(long baudrate){
	
	int8_t answer;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));
	sprintf(buffer_3G, "%s%ld", str_aux1, baudrate);
	
	// Sends the command:
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);

	if (answer == 2)
	{
			return -2;
	}
	else if (answer == 1) // If the command is executed by the 3G module, changes the Wasmote baudrate
	{
		beginSerial(baudrate, _socket);
	}
	
	return answer;
}

/* sendATCommand(ATcommand) - sends any command to 3G module
 *
 * This function sends any command to 3G module
 *
 * It stores in 'buffer_3G' the answer returned by the 3G module
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::sendATCommand(const char* ATcommand){
	return sendATCommand(ATcommand, DEFAULT_TIMEOUT, 0);
}

/* sendATCommand(ATcommand) - sends any command to 3G module
 *
 * This function sends any command to 3G module
 *
 * It stores in 'buffer_3G' the answer returned by the 3G module
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::sendATCommand(const char* ATcommand, int MAX_TIMEOUT, int sendOnce){
	
	int timeout=0;
	uint16_t i=0;
	
	// Cleans 'buffer_3G':
	for (i = 0; i < BUFFER_SIZE; i++)
	{
		buffer_3G[i] = '\0';
	}
	
	i=0;
	
	sprintf(buffer_3G, "AT%s%c%c", ATcommand,'\r','\n');

	serialFlush(_socket);

	// Sends the command to the 3G module:
	while(!serialAvailable(_socket) && (timeout < MAX_TIMEOUT))
	{
		if (!sendOnce || !timeout)
		{
			printString(buffer_3G,_socket);
		}
		delay(DELAY_ON_SEND);
		timeout++;
	};
	
	timeout = 0;
	// Waits and reads the answer from the 3G module:	
	while ( timeout < 10 )
	{
		while ((!serialAvailable(_socket)) && (timeout < 10))
		{
			timeout++;
			delay(1000);
		}
		while ( serialAvailable(_socket) && (timeout < 10))
		{
			buffer_3G[i] = serialRead(_socket);
			#if _3G_debug_mode>0
				USB.print(char(buffer_3G[i]));
			#endif
			delay(20);
			i++;
			timeout=0;
			if (i >= BUFFER_SIZE)
			{
				timeout=10;
			}
		}
	}
	
	buffer_3G[i]='\0';
	
	if (i < 5) 
	{
		return 0;
	}
	return 1;
	
}

/* selectAudioOutput(uint8_t) - Selects speaker or loudspeaker output for calls
 *
 * This function selects speaker (0) or loudspeaker (1) output for calls
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::selectAudioOutput(uint8_t output){
		
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[44])));
	sprintf(buffer_3G, "%s%d", str_aux1, ((output * 2) + 1));
	return sendCommand1(buffer_3G, OK_RESPONSE);
}

/* micGain(uint8_t) - Controls the gain level of the microphone
 *
 * This function controls the gain level of the microphone.
 *
 * This function only can be used into a call
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::micGain(uint8_t gain){
	
	char command[10];
	uint8_t answer=0;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[45])));
	if (gain == 0)	// If gain is '0' enables the mute of the microphone
	{
		
		sprintf(buffer_3G, "%s1", str_aux1);
		return sendCommand1(buffer_3G, OK_RESPONSE);
	}
	else // If gain isn't '0' disables the mute and set the gain level
	{
		sprintf(buffer_3G, "%s0", str_aux1);
		answer=sendCommand1(buffer_3G, OK_RESPONSE);
		if (answer == 1)
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[46])));
			sprintf(buffer_3G, "%s%d", str_aux1, gain-1);
			return sendCommand1(buffer_3G, OK_RESPONSE);
		}
	}
	
	return 0;
}

/* loudspeakerLevel(uint8_t) - Sets loudspeaker volume 
 *
 * This function sets loudspeaker volume level between 0-5
 *
 * 'volume' values: '0' for mute and '1' to '5' for volume level 
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::loudspeakerLevel(uint8_t volume){

	uint8_t answer=0;
	
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[48])));
	if (volume == 0)	// If volume is '0' enables the silent mode
	{		
		sprintf(buffer_3G, "%s1", str_aux1);
		return sendCommand1(buffer_3G, OK_RESPONSE);
	}
	else // If volume isn't '0' disables the silent mode and set the volume level
	{
		sprintf(buffer_3G, "%s0", str_aux1);
		answer=sendCommand1(buffer_3G, OK_RESPONSE);
		if (answer == 1)
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[49])));
			sprintf(buffer_3G, "%s%d", str_aux1, volume-1);
			return sendCommand1(buffer_3G, OK_RESPONSE);
		}
	}
	
	return 0;
}

/* whoamI() - Gets the model of the module
 *
 * This function gets the model of the module and saves it in 'buffer_GPRS'
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::whoamI(){
	int8_t answer, x;
	unsigned long previous;
	
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[51])));
	answer=sendCommand1(str_aux1, "\r\n");

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000));
			buffer_3G[x]=serialRead(_socket);
			x++;
		}while ((buffer_3G[x-1] != '\r') && ((millis() - previous) < 5000));
		buffer_3G[x-1]='\0';
	}
	
	return answer;

}

/* firmware_version() - Gets the firmware version of the module
 *
 * This function gets the firmware version of the module and saves it in 'buffer_GPRS'
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::firmware_version(){
	int8_t answer, x;
	unsigned long previous;
	
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[52])));
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[53])));
	answer=sendCommand1(str_aux1, str_aux2);

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000));
			buffer_3G[x]=serialRead(_socket);
			x++;
		}while ((buffer_3G[x-1] != '\r') && ((millis() - previous) < 5000));
		buffer_3G[x-1]='\0';
	}
	
	return answer;

}

/* show_APN() - Shows the apn, login and password constants
 *
 * This function shows the apn, login and password constants
 *
 * Returns nothing
*/
void Wasp3G::show_APN(){
	// APN parameters depends on SIM
	USB.print(F("APN: "));
	USB.println(_3G_APN);
	USB.print(F("LOGIN: "));
	USB.println(_3G_LOGIN);
	USB.print(F("PASSWORD: "));
	USB.println(_3G_PASSW);

}

#if TRANSMISSION_FUSE
/* sendFiletoMeshlium(char*, char*, char*) - Sends a picture or a video to Meshlium
 *
 * This function sends a picture or a video to Meshlium
 *
 * Return '1' if success, '-2' if error getting the size of the file in the 3G/GPRS module, '-3' if time out sending the INITIAL frame, 
 * '-4' if error sending the INITIAL frame to Meshlium, '-5' if NACK received from Meshlium in the INITIAL frame, '-6' if error getting the file from the 3G/GPRS module,
 * '-7' if error sending the file to Meshlium and also error sending the END frame, '-8' if error sending the file to Meshlium, '-9' if error sending the END frame
*/
int8_t Wasp3G::sendFiletoMeshlium(char* origin_path, char* destiny_name, char* MAC_address){

	char frame[100];
	int aux;
	uint8_t checksum, error_counter;
	unsigned long previous;
	long file_size;
	
	
	uint16_t total_packets, packet_counter = 0;
	uint8_t counter = 0, send_counter;
	
	// Gets the file size
	file_size = getFileSize(origin_path);
	
	if (file_size == -2)
	{	
		return -2;
	}
	
	total_packets = (file_size / 128) * 2;
	
	if (file_size > total_packets*64)
	{
		total_packets = total_packets +2;
	}
	
	#ifdef WaspXBeeDM_h
		#if _3G_debug_mode>0
			USB.println(F("DigiMesh radio"));
		#endif
		xbeeDM.ON();
	#endif
	#ifdef WaspXBeeZB_h
		#if _3G_debug_mode>0
			USB.println(F("ZigBee radio"));
		#endif
		xbeeZB.ON();
		delay(10000);
	#endif
	#ifdef WaspXBee802_h
		#if _3G_debug_mode>0
			USB.println(F("802.15.4 radio"));
		#endif
		xbee802.ON();
		xbee802.flush();
	#endif
		
	delay(5000);
	
	// Assemble the INITIAL frame	
	sprintf(frame,"<=>0%lu#%s#%d#", _serial_id, destiny_name, total_packets);
	frame[3] = INITIAL_PACKET;
	
	#if _3G_debug_mode>0
		USB.print(F("Frame: "));
		USB.println(frame);
	#endif
	
	// Sends the frame and waits for ACK or NACK
	counter = SENDING_RETRIES;
	do{
		aux = sendPacket((uint8_t*)frame, strlen(frame), MAC_address, 1);
		delay(1);
		counter--;
	} while ((counter > 0 ) && (!(aux == 1) || (aux == 2)));
	
	if (aux == 0)
	{	// Time out 
	
		#ifdef WaspXBeeDM_h
			xbeeDM.OFF();
		#endif
		#ifdef WaspXBeeZB_h
			xbeeZB.OFF();
		#endif
		#ifdef WaspXBee802_h
			xbee802.OFF();
		#endif
		return -3;
	}
	else if (aux == -2)
	{	// Error sending the packet
		#ifdef WaspXBeeDM_h
			xbeeDM.OFF();
		#endif
		#ifdef WaspXBeeZB_h
			xbeeZB.OFF();
		#endif
		#ifdef WaspXBee802_h
			xbee802.OFF();
		#endif
		return -4;
	}
	else if (aux == 2)
	{	// NACK received 
		#ifdef WaspXBeeDM_h
			xbeeDM.OFF();
		#endif
		#ifdef WaspXBeeZB_h
			xbeeZB.OFF();
		#endif
		#ifdef WaspXBee802_h
			xbee802.OFF();
		#endif
		return -5;
	}
	
	
	// Sends AT command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[50])));
	sprintf(frame, "%s=\"%s\"", str_aux1, origin_path);
	aux = sendCommand2(frame, OK_RESPONSE, "FILE NOT EXISTING");
	
	if (aux == 0 || aux == 2)
	{
		// Assemble the END frame	
		frame[0] = '<';
		frame[1] = '=';
		frame[2] = '>';
		frame[3] = END_PACKET;	
		frame[4] = session_ID;	
		frame[5] = 0x18;	
	
		counter = SENDING_RETRIES;
		do{
			aux = sendPacket((uint8_t*)frame, 6, MAC_address, 0);
			delay(10);
			counter--;
		} while ((counter > 0 ) && (!(aux == 1) || (aux == 2)));
		
		#ifdef WaspXBeeDM_h
			xbeeDM.OFF();
		#endif
		#ifdef WaspXBeeZB_h
			xbeeZB.OFF();
		#endif
		#ifdef WaspXBee802_h
			xbee802.OFF();
		#endif
		return -6;
	}
	else
	{	
		// Cleans input buffer:
		while (serialAvailable(_socket) != 0)
		{
			serialRead(_socket);
		}
		
		// Starts the transmission and gets the data:
		serialWrite(0x15, _socket);
		error_counter = 0;
		do{
			aux=0;
			previous=millis();

			while ((serialAvailable(_socket) < 134) && ((millis()-previous) <= 3000));
			for(int x=0; x < 135; x++){
				buffer_3G[x] = serialRead(_socket);
			}
			
			#if _3G_debug_mode>0
				if (buffer_3G[1] == 0)
				{
					USB.println(F("*******************************"));
				}
				USB.print(F("Header value: "));
				USB.print(buffer_3G[0],DEC);
				USB.print(F("\tPacket numbers: "));
				USB.print(buffer_3G[1],DEC);
				USB.print(F(";  "));
				USB.print(buffer_3G[2],DEC);
				USB.print(F("\tChecksum value: "));
				USB.printHex(buffer_3G[131]);
			#endif
			checksum=buffer_3G[131];
			
			// If data isn't an EOT saves data in SD file
			if (buffer_3G[0] != 0x04)
			{
				
				for (int x=0; x < 128; x++)
				{
					buffer_3G[x]=buffer_3G[x+3];
				}
				buffer_3G[128]='\0';
				#if _3G_debug_mode>0	
					USB.print(F("\tGenerated checksum: "));
					USB.printHex(getXModemCheckSum((uint8_t*)buffer_3G));
				#endif
				
				
				// Cleans the input buffer
				while (serialAvailable(_socket) != 0)
				{
					serialRead(_socket);
				}
				
				
				// Checks the checksum byte
				if(checksum == getXModemCheckSum((uint8_t*)buffer_3G))
				{	
					send_counter = SENDING_RETRIES;
					
					do{
						#if _3G_debug_mode>0
							USB.println(F("\tChecksum correct"));
						#endif
						
						// sends the first data packet
						// assembles the frame
						frame[0] = '<';
						frame[1] = '=';
						frame[2] = '>';
						frame[3] = DATA_PACKET;
						frame[4] = session_ID;
						memcpy(frame + 5, &packet_counter, 2);
						memcpy(frame + 7, buffer_3G, 64);
						
						// sends the frame
						delay(1);
						counter = SENDING_RETRIES;
						do{
							aux = sendPacket((uint8_t*)frame, 71, MAC_address, 1);
							#if _3G_debug_mode>0
								USB.print(F("Paquete impar. Respuesta: "));
								USB.println(aux, DEC);
							#endif
							delay(10);
							counter--;
						} while ((counter > 0 ) && (aux != 1));	
						
						if (aux == 1)
						{
							packet_counter++;
							// sends the second data packet
							// assembles the frame
							frame[0] = '<';
							frame[1] = '=';
							frame[2] = '>';
							frame[3] = DATA_PACKET;
							frame[4] = session_ID;
							memcpy(frame + 5, &packet_counter, 2);
							memcpy(frame + 7, buffer_3G + 64, 64);
							
							// sends the frame
							counter = SENDING_RETRIES;
							delay(1);
							do{
								aux = sendPacket((uint8_t*)frame, 71, MAC_address, 1);
								#if _3G_debug_mode>0
									USB.print(F("Paquete par. Respuesta: "));	
									USB.println(aux, DEC);
								#endif
								delay(10);
								counter--;
							} while ((counter > 0 ) && (aux != 1));
							
							if ((aux == 0) || (aux == -2) || (aux == 2)) // Timeout or error sending the frame
							{
								error_counter = 10;
							}
							else if (aux == 1)
							{
								// second frame has been sent
								packet_counter++;
							}
						}
						else if ((aux == 0) || (aux == -2) || (aux == 2)) // Timeout or error sending the frame
						{
							error_counter = 10;
						}
						#if _3G_debug_mode>0
							USB.print(F("/////////////////////////////////////////////////////"));	
							USB.print(F("aux:"));	
							USB.println(aux, DEC);	
							USB.print(F("error_counter:"));	
							USB.println(error_counter, DEC);	
							USB.print(F("send_counter:"));	
							USB.println(send_counter, DEC);
						#endif
						
						
					}while ((aux != 1) && (error_counter < 10) && (send_counter > 0));
					
					#if _3G_debug_mode>1	
						USB.print(F("Data field: "));
						for (int x=0; x <128; x++)
						{
							USB.print(buffer_3G[x], HEX);
							USB.print(F(" "));
						}
						USB.println(F(""));
					#endif
					
					//error_counter = 0;
					serialWrite(0x06,_socket);
				}
				else
				{
					#if _3G_debug_mode>1
						USB.println(F("\tChecksum error"));
					#endif
					error_counter++;
					serialWrite(0x15,_socket);
				}
				
				buffer_3G[0] = 0x00;
			}
			else
			{
				#if _3G_debug_mode>0
					USB.println(F("EOF"));
				#endif
				serialWrite(0x06,_socket);
			}
		}while ((buffer_3G[0] != 0x04) && (error_counter < 10));

	}
	
	if (error_counter >= 10)
	{
		frame[0] = '<';
		frame[1] = '=';
		frame[2] = '>';
		frame[3] = END_PACKET;
		frame[4] = session_ID;
		frame[5] = 0x18;
		
		// sends the frame
		delay(1);
		counter = SENDING_RETRIES;
		do{
			aux = sendPacket((uint8_t*)frame, 6, MAC_address, 0);
			delay(10);
			counter--;
		} while ((counter > 0 ) && (aux != 1));
		
		#ifdef WaspXBeeDM_h
			xbeeDM.OFF();
		#endif
		#ifdef WaspXBeeZB_h
			xbeeZB.OFF();
		#endif
		#ifdef WaspXBee802_h
			xbee802.OFF();
		#endif
		
		if (aux == -2) // Timeout or error sending the frame
		{
			return -7;
		}
		
		return -8;
	}
	else
	{	
		frame[0] = '<';
		frame[1] = '=';
		frame[2] = '>';
		frame[3] = END_PACKET;
		frame[4] = session_ID;
		frame[5] = 0x04;
		
		// sends the frame
		delay(1);
		counter = SENDING_RETRIES;
		do{
			aux = sendPacket((uint8_t*)frame, 6, MAC_address, 0);
			delay(10);
			counter--;
		} while ((counter > 0 ) && (aux != 1));
		
		#ifdef WaspXBeeDM_h
			xbeeDM.OFF();
		#endif
		#ifdef WaspXBeeZB_h
			xbeeZB.OFF();
		#endif
		#ifdef WaspXBee802_h
			xbee802.OFF();
		#endif
		
		if (aux == -2) // Timeout or error sending the frame
		{
			return -9;
		}
		
		return 1;
	}
}

/*sendPacket(uint8_t*, uint16_t, char*, uint8_t) - Sends a packet to Meshlium
 *
 * This function sends a packet to Meshlium
 *
 * Returns '1' if ACK received, '2' if NACK received, '0' if timeout and '-2' if error sending the packet
*/
int8_t Wasp3G::sendPacket(uint8_t* frame, uint16_t frame_length, char* MAC_destiny, uint8_t wait_for_answer){

	unsigned long previous;
	int8_t answer;

	
	#if _3G_debug_mode>0
		USB.println(F("***************************"));
		USB.print(F("Sending frame to: "));
		USB.println(MAC_destiny);
		USB.print(F("Data length: "));
		USB.println(frame_length, DEC);
		USB.print(F("Session ID in HEX: "));
		USB.printHex(frame[4]);
		USB.print(F("Packet number in HEX: "));
		USB.printHex(frame[6]);
		USB.printHex(frame[5]);
		USB.println(F(""));
	#endif

	// create packet to send
	packetXBee* packet; 
	
    // set packet to send:
    packet=(packetXBee*) calloc(1,sizeof(packetXBee)); // memory allocation
	
	if (packet == NULL)
	{
		return -1;
	}
    packet->mode=BROADCAST; // set Unicast mode

	#ifdef WaspXBeeDM_h
		// sets Destination parameters
		xbeeDM.setDestinationParams(packet, MAC_destiny, frame, frame_length); 
		// send data
		xbeeDM.sendXBee(packet);

		//free memory
		free(packet);
		packet=NULL; 
			
		// Check TX flag
		if( xbeeDM.error_TX != 0 )
		{
			#if _3G_debug_mode>0
				USB.println(F("error_TX"));
			#endif
			return -2;
		}
		
		//Now, waits for ACK or NACK for meshlium
		previous = millis();
		
		answer = 0;
		if (wait_for_answer == 0){
			return 1;	
		}
		else
		{
			do{
				// check available data in RX buffer
				if( xbeeDM.available() > 0 ) 
				{
					// parse information
					xbeeDM.treatData(); 

					// check RX flag after 'treatData'
					if( !xbeeDM.error_RX ) 
					{
						// check available packets
						while( xbeeDM.pos > 0 )
						{
							#if _3G_debug_mode>0
								USB.print(F("Data received: "));
								USB.print(xbeeDM.packet_finished[xbeeDM.pos-1]->data[0], HEX);
								USB.print(F(" "));
								USB.print(xbeeDM.packet_finished[xbeeDM.pos-1]->data[1], HEX);
								USB.print(F(" "));
								USB.print(xbeeDM.packet_finished[xbeeDM.pos-1]->data[2], HEX);
								USB.print(F(" "));
								USB.print(xbeeDM.packet_finished[xbeeDM.pos-1]->data[3], HEX);
								USB.print(F(" "));
								USB.print(xbeeDM.packet_finished[xbeeDM.pos-1]->data[4], HEX);
								USB.print(F(" "));
								USB.println(xbeeDM.packet_finished[xbeeDM.pos-1]->data[5], HEX);
							#endif
							
							// checks if its a frame packet
							if ((xbeeDM.packet_finished[xbeeDM.pos-1]->data[0] == '<') && (xbeeDM.packet_finished[xbeeDM.pos-1]->data[1] == '=') && (xbeeDM.packet_finished[xbeeDM.pos-1]->data[2] == '>'))
							{
								#if _3G_debug_mode>0
									USB.println(F("Frame received"));
								#endif
								//checks the kind of data packet
								if ((xbeeDM.packet_finished[xbeeDM.pos-1]->data[3] == ID_PACKET) && (frame[3] == INITIAL_PACKET)) 
								{
									#if _3G_debug_mode>0
										USB.println(F("INITIAL frame"));
									#endif
									// gets the ID for the session
									session_ID = xbeeDM.packet_finished[xbeeDM.pos-1]->data[4];
									#if _3G_debug_mode>0
										USB.print(F("Session ID: "));
										USB.println(session_ID, HEX);
									#endif
									
									if (xbeeDM.packet_finished[xbeeDM.pos-1]->data[5] == ACK_ASCII)
									{
										answer = 1;
										#if _3G_debug_mode>0
											USB.println(F("ACK received"));
										#endif
									}
									else if (xbeeDM.packet_finished[xbeeDM.pos-1]->data[5] == NACK_ASCII)
									{
										answer = 2;
										#if _3G_debug_mode>0
											USB.println(F("NACK received"));
										#endif
									}
									else 
									{
										answer = 0;
										#if _3G_debug_mode>0
											USB.println(F("Nothing useful received"));
										#endif
									}
									
								}
								else if (xbeeDM.packet_finished[xbeeDM.pos-1]->data[3] == ACK_PACKET) 
								{
									#if _3G_debug_mode>0
										USB.println(F("ACK/NACK frame"));
									#endif
									//check the ID of the packet
									if (xbeeDM.packet_finished[xbeeDM.pos-1]->data[4] == session_ID)
									{
										#if _3G_debug_mode>0
											USB.print(F("Session ID: "));
											USB.println(session_ID, HEX);
										#endif
										if (xbeeDM.packet_finished[xbeeDM.pos-1]->data[5] == ACK_ASCII)
										{
											answer = 1;
											#if _3G_debug_mode>0
												USB.println(F("ACK received"));
											#endif
										}
										else if (xbeeDM.packet_finished[xbeeDM.pos-1]->data[5] == NACK_ASCII)
										{
											answer = 2;
											#if _3G_debug_mode>0
												USB.println(F("NACK received"));
											#endif
										}
										else 
										{
											answer = 0;
											#if _3G_debug_mode>0
												USB.println(F("Nothing useful received"));
											#endif
										}
									}
								}
							}

							// free memory
							free(xbeeDM.packet_finished[xbeeDM.pos-1]);
							xbeeDM.packet_finished[xbeeDM.pos-1] = NULL; 

							// decrement the received packet counter
							xbeeDM.pos--; 
						}
					}
				}
			} while ((answer == 0) && ((millis() - previous) < 5000) && (wait_for_answer == 1));
		}
	#endif

	#ifdef WaspXBeeZB_h
		// sets Destination parameters
		xbeeZB.setDestinationParams(packet, MAC_destiny, frame, frame_length); 
		// send data
		xbeeZB.sendXBee(packet);

		//free memory
		free(packet);
		packet=NULL; 
			
		// Check TX flag
		if( xbeeZB.error_TX != 0 )
		{
			#if _3G_debug_mode>0
				USB.println(F("error_TX"));
			#endif
			return -2;
		}
		
		//Now, waits for ACK or NACK for meshlium
		previous = millis();
		
		answer = 0;
		if (wait_for_answer == 0){
			return 1;	
		}
		else
		{
			do{
				// check available data in RX buffer
				if( xbeeZB.available() > 0 ) 
				{
					// parse information
					xbeeZB.treatData(); 

					// check RX flag after 'treatData'
					if( !xbeeZB.error_RX ) 
					{
						// check available packets
						while( xbeeZB.pos > 0 )
						{
							#if _3G_debug_mode>0
								USB.print(F("Data received: "));
								USB.print(xbeeZB.packet_finished[xbeeZB.pos-1]->data[0], HEX);
								USB.print(F(" "));
								USB.print(xbeeZB.packet_finished[xbeeZB.pos-1]->data[1], HEX);
								USB.print(F(" "));
								USB.print(xbeeZB.packet_finished[xbeeZB.pos-1]->data[2], HEX);
								USB.print(F(" "));
								USB.print(xbeeZB.packet_finished[xbeeZB.pos-1]->data[3], HEX);
								USB.print(F(" "));
								USB.print(xbeeZB.packet_finished[xbeeZB.pos-1]->data[4], HEX);
								USB.print(F(" "));
								USB.println(xbeeZB.packet_finished[xbeeZB.pos-1]->data[5], HEX);
							#endif
							
							// checks if its a frame packet
							if ((xbeeZB.packet_finished[xbeeZB.pos-1]->data[0] == '<') && (xbeeZB.packet_finished[xbeeZB.pos-1]->data[1] == '=') && (xbeeZB.packet_finished[xbeeZB.pos-1]->data[2] == '>'))
							{
								#if _3G_debug_mode>0
									USB.println(F("Frame received"));
								#endif
								//checks the kind of data packet
								if ((xbeeZB.packet_finished[xbeeZB.pos-1]->data[3] == ID_PACKET) && (frame[3] == INITIAL_PACKET)) 
								{
									#if _3G_debug_mode>0
										USB.println(F("INITIAL frame"));
									#endif
									// gets the ID for the session
									session_ID = xbeeZB.packet_finished[xbeeZB.pos-1]->data[4];
									#if _3G_debug_mode>0
										USB.print(F("Session ID: "));
										USB.println(session_ID, HEX);
									#endif
									
									if (xbeeZB.packet_finished[xbeeZB.pos-1]->data[5] == ACK_ASCII)
									{
										answer = 1;
										#if _3G_debug_mode>0
											USB.println(F("ACK received"));
										#endif
									}
									else if (xbeeZB.packet_finished[xbeeZB.pos-1]->data[5] == NACK_ASCII)
									{
										answer = 2;
										#if _3G_debug_mode>0
											USB.println(F("NACK received"));
										#endif
									}
									else 
									{
										answer = 0;
										#if _3G_debug_mode>0
											USB.println(F("Nothing useful received"));
										#endif
									}
									
								}
								else if (xbeeZB.packet_finished[xbeeZB.pos-1]->data[3] == ACK_PACKET) 
								{
									#if _3G_debug_mode>0
										USB.println(F("ACK/NACK frame"));
									#endif
									//check the ID of the packet
									if (xbeeZB.packet_finished[xbeeZB.pos-1]->data[4] == session_ID)
									{
										#if _3G_debug_mode>0
											USB.print(F("Session ID: "));
											USB.println(session_ID, HEX);
										#endif
										if (xbeeZB.packet_finished[xbeeZB.pos-1]->data[5] == ACK_ASCII)
										{
											answer = 1;
											#if _3G_debug_mode>0
												USB.println(F("ACK received"));
											#endif
										}
										else if (xbeeZB.packet_finished[xbeeZB.pos-1]->data[5] == NACK_ASCII)
										{
											answer = 2;
											#if _3G_debug_mode>0
												USB.println(F("NACK received"));
											#endif
										}
										else 
										{
											answer = 0;
											#if _3G_debug_mode>0
												USB.println(F("Nothing useful received"));
											#endif
										}
									}
								}
							}

							// free memory
							free(xbeeZB.packet_finished[xbeeZB.pos-1]);
							xbeeZB.packet_finished[xbeeZB.pos-1] = NULL; 

							// decrement the received packet counter
							xbeeZB.pos--; 
						}
					}
				}
			} while ((answer == 0) && ((millis() - previous) < 5000) && (wait_for_answer == 1));
		}
	#endif
	
	#ifdef WaspXBee802_h
		// sets Destination parameters
		xbee802.setDestinationParams(packet, MAC_destiny, frame, frame_length, MAC_TYPE);
		// send data
		xbee802.sendXBee(packet);
	
		//free memory
		free(packet);
		packet=NULL; 
		
		// Check TX flag
		if( xbee802.error_TX != 0 )
		{
			#if _3G_debug_mode>0
				USB.println(F("error_TX"));
			#endif
			return -2;
		}
		
		
		//Now, waits for ACK or NACK for meshlium
		previous = millis();
		answer = 0;
		if (wait_for_answer == 0){
			return 1;	
		}
		else
		{
			do{
				// check available data in RX buffer
				if( xbee802.available() > 0 ) 
				{
					// parse information
					xbee802.treatData(); 

					// check RX flag after 'treatData'
					if( !xbee802.error_RX ) 
					{
						// check available packets
						while( xbee802.pos > 0 )
						{
							#if _3G_debug_mode>0
								USB.print(F("Data received: "));
								USB.print(xbee802.packet_finished[xbee802.pos-1]->data[0], HEX);
								USB.print(F(" "));
								USB.print(xbee802.packet_finished[xbee802.pos-1]->data[1], HEX);
								USB.print(F(" "));
								USB.print(xbee802.packet_finished[xbee802.pos-1]->data[2], HEX);
								USB.print(F(" "));
								USB.print(xbee802.packet_finished[xbee802.pos-1]->data[3], HEX);
								USB.print(F(" "));
								USB.print(xbee802.packet_finished[xbee802.pos-1]->data[4], HEX);
								USB.print(F(" "));
								USB.println(xbee802.packet_finished[xbee802.pos-1]->data[5], HEX);
							#endif
							
							// checks if its a frame packet
							if ((xbee802.packet_finished[xbee802.pos-1]->data[0] == '<') && (xbee802.packet_finished[xbee802.pos-1]->data[1] == '=') && (xbee802.packet_finished[xbee802.pos-1]->data[2] == '>'))
							{
								#if _3G_debug_mode>0
									USB.println(F("Frame received"));
								#endif
								//checks the kind of data packet
								if ((xbee802.packet_finished[xbee802.pos-1]->data[3] == ID_PACKET) && (frame[3] == INITIAL_PACKET)) 
								{
									#if _3G_debug_mode>0
										USB.println(F("INITIAL frame"));
									#endif
									// gets the ID for the session
									session_ID = xbee802.packet_finished[xbee802.pos-1]->data[4];
									#if _3G_debug_mode>0
										USB.print(F("Session ID: "));
										USB.println(session_ID, HEX);
									#endif
									
									if (xbee802.packet_finished[xbee802.pos-1]->data[5] == ACK_ASCII)
									{
										answer = 1;
										#if _3G_debug_mode>0
											USB.println(F("ACK received"));
										#endif
									}
									else if (xbee802.packet_finished[xbee802.pos-1]->data[5] == NACK_ASCII)
									{
										answer = 2;
										#if _3G_debug_mode>0
											USB.println(F("NACK received"));
										#endif
									}
									else 
									{
										answer = 0;
										#if _3G_debug_mode>0
											USB.println(F("Nothing useful received"));
										#endif
									}
									
								}
								else if (xbee802.packet_finished[xbee802.pos-1]->data[3] == ACK_PACKET) 
								{
									#if _3G_debug_mode>0
										USB.println(F("ACK/NACK frame"));
									#endif
									//check the ID of the packet
									if (xbee802.packet_finished[xbee802.pos-1]->data[4] == session_ID)
									{
										#if _3G_debug_mode>0
											USB.print(F("Session ID: "));
											USB.println(session_ID, HEX);
										#endif
										if (xbee802.packet_finished[xbee802.pos-1]->data[5] == ACK_ASCII)
										{
											answer = 1;
											#if _3G_debug_mode>0
												USB.println(F("ACK received"));
											#endif
										}
										else if (xbee802.packet_finished[xbee802.pos-1]->data[5] == NACK_ASCII)
										{
											answer = 2;
											#if _3G_debug_mode>0
												USB.println(F("NACK received"));
											#endif
										}
										else 
										{
											answer = 0;
											#if _3G_debug_mode>0
												USB.println(F("Nothing useful received"));
											#endif
										}
									}
								}
							}

							// free memory
							free(xbee802.packet_finished[xbee802.pos-1]);
							xbee802.packet_finished[xbee802.pos-1] = NULL; 

							// decrement the received packet counter
							xbee802.pos--; 
						}
					}
					else
					{
						#if _3G_debug_mode>0
							USB.print(F("Error_RX:"));
							USB.println(xbee802.error_RX, DEC);
						#endif
					}
				}
			} while ((answer == 0) && ((millis() - previous) < 5000) && (wait_for_answer == 1));
		}
	#endif
	
    return answer;
	
	
}

#ifdef WaspWIFI_h
/* sendFiletoWiFiFTP(char*, char*, char*, uint16_t, uint8_t, char*, char*, uint8_t, char*, char*) - Uploads a file to a FTP using the WiFi connection
 *
 * This function uploads a file to a FTP using the WiFi connection. It does all steps.
 
 * Return '1' if success, '-2' if error setting the connection options, '-3' if error setting the DHCP options
 * '-4' if error setting FTP parameters, '-5' if error setting authentification key, '-6' if error setting the join mode
 * '-7' if error joining to the Wi-Fi network, '-8' if error opening the FTP session and '-9' if error uploading the file
*/
int8_t Wasp3G::sendFiletoWiFiFTP(char* origin_path, char* destiny_name, char* FTP_server, uint16_t FTP_port, uint8_t FTP_mode, char* FTP_username, char* FTP_password, uint8_t auth_type, char* auth_key, char* SSID){
    
	int8_t answer;
	getXModemFile(origin_path,destiny_name); 
	// Switch on the WIFI module on the desired socket.
	WIFI.ON(SOCKET0);
		// 1. Configure the transport protocol (UDP, TCP, FTP, HTTP...)
	answer = WIFI.setConnectionOptions(CLIENT_SERVER);
	if (answer == 1)
	{
		// 2. Configure the way the modules will resolve the IP address.
		answer =WIFI.setDHCPoptions(DHCP_ON);
		if (answer == 1)
		{
			// 3.0 Sets the server IP address, ports and FTP mode
			answer =WIFI.setFTP(FTP_server,FTP_port,FTP_mode,20);
			if (answer == 1)
			{
				// 3.1 Sets the server account with the username and password
				answer = WIFI.openFTP( FTP_username, FTP_password); 
				if (answer == 1)
				{
					// 4. Configure how to connect the AP
					answer = WIFI.setAuthKey(auth_type,auth_key); 
					if (answer == 1)
					{
						answer = WIFI.setJoinMode(MANUAL);
						if (answer == 1)
						{
							answer = WIFI.join(SSID);
							if (answer == 1)
							{
								answer = WIFI.uploadFile(origin_path, destiny_name, ".");
								if (answer == 1)
								{
									answer = 1;
								}
								else
								{
									answer = -9;
								}
							}
							else
							{
								answer = -8;
							}
						}
						else
						{
							answer = -7;
						}
					}
					else
					{
						answer = -6;
					}
				}
				else
				{
					answer = -5;
				}
			}
			else
			{
				answer = -4;
			}
		}
		else
		{
			answer = -3;
		}
	}
	else
	{
		answer = -2;
	}
	     
     // Exit and power off the module. 
     WIFI.OFF();
	 
	 return answer;
}
#endif

/* sendFileto3GFTP(uint8_t, const char*, const char*r, const char*, uint8_t, const char*, const char*) - Uploads a file to a FTP server
 *
 * This function uploads a file to a FTP server. It does all steps
 *
 * Origin values allowed:  0 – current directory, 1 – “C:/Picture” directory, 2 – “C:/Video” directory, 3 – “C:/VideoCall” directory,
 * 4 – “D:/Picture” directory, 5 – “D:/Video” directory, 6 – “D:/VideoCall” directory, 7 – “C:/Audio” directory, 8 – “D:/Audio” directory
 *
 * Return '1' on success,'-2' if error setting the connection parameters (APN), '-3' if error setting the FTP server ('-13' if CME error available),
 * '-4' if error setting the FTP port ('-14' if CME error available), '-5' if error setting the FTP mode ('-15' if CME error available),
 * '-6' if error setting the FTP type ('-16' if CME error available), '-7' if error setting the user name ('-17' if CME error available),
 * '-8' if error setting the FTP password ('-18' if CME error available), '-20' if error uploading the file, '-22' if error with CME code (FTP error) and 
 * '-23' if error getting the file of the size to upload.
 */
int8_t Wasp3G::sendFileto3GFTP(uint8_t origin, const char* destination_path, const char* FTP_server, const char* FTP_port, uint8_t FTP_mode, const char* FTP_username, const char* FTP_password){

	int8_t answer;
	
	answer = configureFTP(FTP_server, FTP_port, FTP_username, FTP_password, FTP_mode, "I");
	if (answer == 1)
	{
		answer = uploadFile( origin, destination_path);
		if (answer == 1)
		{
			return 1;
		}
		else
		{
			return answer - 20;
		}
	}
	else
	{
		return answer;
	}
}


/* sendFileto3Gemail(char*, uint16_t, char*, char* , char*, char*, char*, char*, char*, char*, char*) - Sends a file attached into an email
 *
 * This function sends a file attached into an email. It does all steps to send the email
 *
 * Return '1' if success, '0' if error setting username and password, '-1' if error setting server and port, '-2' if error setting sender address and name,
 * '-3' if error setting recipient address and name, '-4' if error setting subject, '-5' if error setting the body, '-6' if error attaching the file 
 * and '-7' if error sending the email
*/
int8_t Wasp3G::sendFileto3Gemail(char* SMTP_server, uint16_t SMTP_port, char* STMP_account, char* STMP_password, char* sender_address, char* sender_name, char* recipient_address, char* recipient_name, char* subject, char* body, char* picture_name){

	int8_t answer;
	
	answer = setSMTPserver(SMTP_server, SMTP_port, STMP_account, STMP_password);
	if (answer == 1)
	{
		if (_3G.setSMTPfrom(sender_address, sender_name))
		{
			if (_3G.setSMTPrecipient(0, 0, recipient_address, recipient_name))
			{
				if (_3G.setSMTPsubject( subject))
				{
					if (_3G.setSMTPbody( body))
					{   
						if (setSMTPattach( 1, picture_name) == 1)
						{
							if ( setSMTPsend() == 1)
							{                            
								return 1;
							}
							else
							{
								return -7;
							}
						}
						else
						{
							return -6;
						}
					}
					else
					{
						return -5;
					} 
				}
				else
				{
					return -4;
				}  
			}
			else
			{
				return -3;
			}  
		}
		else
		{
			return -2;
		}  
	}
	else
	{
		return answer;
	}
}

#endif


//*******************************************************************************
//			OTA over 3G
//*******************************************************************************
#if OTA_FUSE
/* requestOTA(const char*, const char*, const char*, const char*) - It downloads a new OTA file if OTA is necessary
 *
 * This function downloads a new OTA file if OTA is necessary
 *
 * Returns '1' on success,'-2' if error setting the connection parameters (APN), '-3' if error setting the FTP server ('-13' if CME error available),
 * '-4' if error setting the FTP port ('-14' if CME error available), '-5' if error setting the FTP mode ('-15' if CME error available),
 * '-6' if error setting the FTP type ('-16' if CME error available), '-7' if error setting the user name ('-17' if CME error available),
 * '-8' if error setting the FTP password ('-18' if CME error available), '-19' if error downloading the OTA version file,
 * '-21' if error with CME code (FTP error) downloading the OTA version file, '-22' if error sending the OTA version file from 3G module to Waspmote's SD,
 * '-23' if there isn't FILE tag, '-24' if there isn't PATH tag, '-25' if there isn't VERSION tag, '-26' if OTA is not necessary, 
 * '-27' if OTA files are the same program version,'-28' if error downloading the OTA file, '-31' if error with CME code (FTP error) downloading the OTA file
 *  and '-32' if error sending the OTA file from 3G module to Waspmote's SD.
*/
int8_t Wasp3G::requestOTA(const char* FTP_server, const char* FTP_port, const char* FTP_username, const char* FTP_password){

	int8_t answer;
	char aux_ver[4];
	uint8_t version;
	char* str_pointer;
	char aux_name[8];
	char programID[8];
	char* path = (char*) calloc(60, sizeof(char));
	if ( path == NULL )
	{
		return -1;
	}
	
	
	SD.ON();
	SD.goRoot();
	SD.del(OTA_ver_file);
	SD.OFF();
	answer = configureFTP( FTP_server, FTP_port, FTP_username, FTP_password, 1, "I");
	if (answer == 1)
	{	
		
		answer = downloadData(OTA_ver_file, OTA_ver_file, 180);
		if (answer == 1)
		{
			
			SD.ON();
			SD.goRoot();
			
			// Reads the file
			strcpy(buffer_3G, SD.cat(OTA_ver_file, 0, BUFFER_SIZE));

			// Searchs the file name
			str_pointer = strstr(buffer_3G, "FILE:");
			if (str_pointer != NULL)
			{	
				strncpy(aux_name, strchr(buffer_3G, ':') + 1, 7);
				aux_name[7] = '\0';
				
				#if _3G_debug_mode>0
					USB.print(F("OTA file: "));
					USB.println(aux_name);	
				#endif
				// Searchs the file name
				str_pointer = strstr(buffer_3G, "PATH:");
				if (str_pointer != NULL)
				{
					strncpy(path, strchr(str_pointer, ':') + 1, strchr(str_pointer, '\n') - (strchr(str_pointer, ':')));
					
					path[strchr(path, '\n') - path] = '\0';
					
					#if _3G_debug_mode>0
						USB.print(F("File path: "));
						USB.println(path);
					#endif
					//strcat(path,"/");
					strcat(path,aux_name);
					
					str_pointer = strstr(buffer_3G, "VERSION:");
					
					if (str_pointer != NULL)
					{
					
						strncpy(aux_ver, strchr(str_pointer, ':') + 1, strchr(str_pointer, '\n') - (strchr(str_pointer, ':')));					
						aux_ver[strchr(aux_ver, '\n') - aux_ver] = '\0';
						
						version = atoi(aux_ver);
						
						#if _3G_debug_mode>0
							USB.print(F("Version: "));
							USB.println(version, DEC);
						#endif
						
						SD.del(aux_name);
		
						if (strcmp(aux_name, NO_OTA) != 0)
						{
							Utils.getProgramID(programID);
							// check if the program have a new version or if it is a different code
							if (((strcmp(aux_name, programID) == 0) && (version > Utils.getProgramVersion())) || (strcmp(aux_name, programID) != 0))
							{		
								delay(10000);
								answer = downloadData(path, aux_name, 180);
								if (answer == 1)
								{
									_3G.OFF();
									
									Utils.loadOTA(aux_name, version);

									free(path);
									return 1;
								}
								else
								{
									SD.OFF();
									free(path);
									return answer - 28;
								}
							}
							else
							{
								#if _3G_debug_mode>0
									USB.println(F("Same program version, no OTA required"));
								#endif
								SD.OFF();
								free(path);
								return -27;
							}
								
						}
						else
						{
							
							#if _3G_debug_mode>0
								USB.println(F("No OTA"));
							#endif
							SD.OFF();
							free(path);
							return -26;
						}
						
						
					}
					else
					{
						SD.OFF();
						free(path);
						return -25;
					}
				}
				else
				{
					SD.OFF();
					free(path);
					return -24;
				}	
			}
			else
			{
				SD.OFF();
				free(path);
				return -23;
			}
		}
		else
		{
			free(path);
			return answer - 19;
		}
	}
	else
	{	
		free(path);
		return answer;
	}

}

#endif
// Preinstantiate Objects //////////////////////////////////////////////////////

Wasp3G _3G = Wasp3G();
