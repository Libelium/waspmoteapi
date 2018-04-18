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

#include <Wasp3G.h>

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
const char MUTE_SPEAKER[]		PROGMEM	= "+VMUTE=";		//48
const char LVL_SPEAKER[]		PROGMEM	= "+CLVL=";			//49
const char XMODEM_RECEIVE[]		PROGMEM	= "+CTXFILE";		//50

const char AT_WHO_AM_I[]		PROGMEM	= "+CGMM";			//51
const char FIRMWARE_VER[]		PROGMEM	= "+CGMR";			//52
const char FIRMWARE_VER_R[]		PROGMEM	= "+CGMR: ";		//53
const char CHECK[]				PROGMEM = "+CREG?";			//54
const char CHECK_RES[]			PROGMEM = "+CREG: 0,";		//55
const char ROAMING[]			PROGMEM = "+CREG: 0,5";		//56

//Constants for manageIncomingData
const char INCOMING_CALL[]		PROGMEM = "+CLIP";			//57
const char INCOMING_SMS[]		PROGMEM = "+CMTI";			//58


const char CHANGE_PIN[]			PROGMEM = "+CPWD=";			//59
const char XMODEM_SEND[]		PROGMEM = "+CRXFILE=";		//60

const char CHECK_GPRS[]			PROGMEM = "+CGREG?";		//61
const char CHECK_GPRS_RES[]		PROGMEM = "+CGREG: 0,";		//62

const char GET_TIME[]			PROGMEM	= "+CCLK?";			//63
const char GET_TIME_RES[]		PROGMEM	= "+CCLK: ";		//64


const char* const  table_MISC[] PROGMEM =
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
	CHECK,					//54
	CHECK_RES,				//55
	ROAMING,				//56

	//manageIncomingData
	INCOMING_CALL,			//57
	INCOMING_SMS,			//58

	CHANGE_PIN,				//59

	XMODEM_SEND,			//60

	CHECK_GPRS,				//61
	CHECK_GPRS_RES,			//62

	GET_TIME,				//63
	GET_TIME_RES,			//64
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

const char NO_CARRIER[]		PROGMEM = "NO CARRIER";		//19
const char BEGIN[]			PROGMEM = "BEGIN";			//20
const char CONNECT[]		PROGMEM = "CONNECT";		//21

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

const unsigned long FTP_TIMEOUT = 120000;
const unsigned long TRANSFER_BASE_TIME = 30000;

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
const char FTP_LIST_RES[]			PROGMEM	= "+CFTPLIST: DATA,";	//27
const char FTP_LIST_END[]			PROGMEM	= "+CFTPLIST: 0";		//28


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
	FTP_LIST_END,			//28
};
#endif

//SMTP and POP3 constants
#if MAIL_FUSE

const unsigned long SMTP_TIMEOUT = 120000;
const unsigned long POP3_TIMEOUT = 30000;

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
const char POP3_IN[]		PROGMEM	= "+POP3IN";		//10
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


const unsigned long HTTP_TIMEOUT = 45000;		// Timeout for HTTP and HTTPS functions in miliseconds
const unsigned long HTTP_CONF_TIMEOUT = 15000;	// Timeout for HTTP and HTTPS functions in miliseconds

const char HTTP_ACT[] 		PROGMEM	= "+CHTTPACT=";				//0
const char HTTP_ACT_REQ[]	PROGMEM	= "+CHTTPACT: REQUEST";		//1
const char HTTP_ACT_DATA[]	PROGMEM	= "+CHTTPACT: ";			//2

const char HTTPS_START[]	PROGMEM	= "+CHTTPSSTART";			//3
const char HTTPS_STOP[]		PROGMEM	= "+CHTTPSSTOP";			//4
const char HTTPS_OPEN[]		PROGMEM	= "+CHTTPSOPSE";			//5
const char HTTPS_CLOSE[]	PROGMEM	= "+CHTTPSCLSE";			//6
const char HTTPS_SEND[]		PROGMEM	= "+CHTTPSSEND";			//7
const char HTTPS_RCV[]		PROGMEM	= "+CHTTPSRECV";			//8
const char HTTPS_DATA[]		PROGMEM	= "+CHTTPSRECV: ";			//9
const char HTTPS_EVENT[]	PROGMEM	= "+CHTTPS: RECV EVENT";	//10

const char HTTP_GET[]		PROGMEM	= "GET /getpost_frame_parser.php?frame=";					//11
const char HTTP_POST[]		PROGMEM	= "POST /getpost_frame_parser.php";							//12
const char HTTP_FRAME_1[]	PROGMEM	= " HTTP/1.1\r\nHost: ";									//13
const char HTTP_FRAME_2[]	PROGMEM	= "\r\nContent-Type: application/x-www-form-urlencoded";	//14
const char HTTP_FRAME_3[]	PROGMEM	= "\r\nContent-Length: ";									//15
const char HTTP_END_GET[]	PROGMEM	= "0\r\n\r\n";												//16
const char HTTP_END_POST[]	PROGMEM	= "\r\n\r\nframe=";											//17

const char HTP_SERVER[]		PROGMEM	= "+CHTPSERV=";		//18
const char HTP_UPDATE[]		PROGMEM	= "+CHTPUPDATE";	//19
const char HTP_UPDATE_RES[]	PROGMEM	= "+CHTPUPDATE: ";	//20



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
	HTTPS_EVENT,	//10

	HTTP_GET,		//11
	HTTP_POST,		//12
	HTTP_FRAME_1,	//13
	HTTP_FRAME_2,	//14
	HTTP_FRAME_3,	//15
	HTTP_END_GET,	//16
	HTTP_END_POST,	//17

	HTP_SERVER,	//18
	HTP_UPDATE,	//19
	HTP_UPDATE_RES,	//20
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

const unsigned long IP_TIMEOUT = 30000;

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

const char INCOMING_IP[]		PROGMEM = "RECV FROM:";		//24
const char IP_DATA_SINGLE[]		PROGMEM = "+IPD";			//25
const char IP_DATA_MULTI[]		PROGMEM = "+RECEIVE,";		//26


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
	INCOMING_IP,			//24
	IP_DATA_SINGLE,			//25
	IP_DATA_MULTI,			//26

};
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

	memset(_apn, '\0', sizeof(_apn));
	memset(_apn_login, '\0', sizeof(_apn_login));
	memset(_apn_password, '\0', sizeof(_apn_password));
	strncpy(_apn, _3G_APN, min(sizeof(_apn), strlen(_3G_APN)));
	strncpy(_apn_login, _3G_LOGIN, min(sizeof(_apn_login), strlen(_3G_LOGIN)));
	strncpy(_apn_password, _3G_PASSW, min(sizeof(_apn_password), strlen(_3G_PASSW)));

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
	answer=waitForData("OK", 1000, millis(), 0);
	if(answer == 1)
	{
		ready=1;
	}
	else
	{
		ready=0;
	}
}

/* check3Gconnection(void) - Checks if 3G is connected to the data network
 *
 * This function checks if 3G module is connected to the network. If not, it has no sense working with 3G.
 *
 * Returns '1' when connected,
 * '0' if not registered and the module is not currently searching a new operator,
 * '-1' if error
 * '-2' if not registered, but the module is currently searching a new operator,
 * '-3' if registration denied
 * and '-4' if the state is unknown
*/
int8_t Wasp3G::check3Gconnection(unsigned long time){

	unsigned long previous;
	int8_t answer;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[61])));	//CHECK_GPRS
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[62])));	//CHECK_GPRS_RES

	previous = millis();

	do{
		// Sends the command and waits for the answer (0,1 for home network and 0,5 for roaming)
		answer = sendCommand1(str_aux1, str_aux2, 3000, 1);

		if (answer == 1)
		{
			answer = serialRead(_socket) - 0x30;
		}
		else
		{
			answer = -1;
		}
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while (((answer == 2) || (answer == 4) || (answer == 0) || (answer == -1)) && ((millis() - previous) < (time * 1000)));

	#if _3G_debug_mode>0
		PRINT_3G(F("Network status: "));
		USB.println(answer, DEC);
	#endif

	if (((answer != 1) && (answer != 5) && (answer != -1)) || ((millis() - previous) > (time * 1000)))
	{
		return -answer;
	}
	else if (answer == -1)
	{
		return -1;
	}

	return 1;
}

/* check3Gattach() - checks if 3G connection is attached or not
 *
 * This function checks if 3G connection is  attached or not
 *
 * Returns '1' if attached, '2' if not attached and '0' if error
*/
uint8_t Wasp3G::check3Gattach(){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[5])));	//AT_3G_CHECK
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[6])));	//AT_3G_CHECK_ON
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_MISC[7])));	//AT_3G_CHECK_OFF
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

/*
 * This	function calculates the	CRC used by the	XMODEM/CRC Protocol
 * The first argument is a pointer to the message block.
 * The second argument is the number of	bytes in the message block.
 * The function	returns	an integer which contains the CRC.
 * The low order 16 bits are the coefficients of the CRC.
 */
uint16_t Wasp3G::sendXModemCheckSum(char* ptr){

    uint16_t  crc= 0;
    char i;
	int count=128;
    while (--count >= 0)
    {
        crc = crc ^ (int) *ptr++ << 8;
        i = 8;
        do
        {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while(--i);
    }
    return (crc);
}


#if HTTP_FUSE

/* initHTTP() - Configures the operator parameters
 *
 * This function configures the operator parameters
 *
 * Returns:
 * '1' on success
 * '-1' if error setting APN, username and password,
 * '-3' if error receiving data or timeout waiting data
 * '-15' if error setting APN, username and password with CME_error code available
*/
int8_t Wasp3G::initHTTP()
{
	int8_t answer;
	int16_t count;

	// Sets APN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));	//_3G_CON
	snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"IP\",\"%s\"", str_aux1, _apn);
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
	if (strlen(_apn_login) == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
	}
	else
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"%s\",\"%s\"", str_aux1, _apn_password, _apn_login);
	}
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

	return 1;

}

/* sendHTTPrequest(const char*,	uint16_t,uint8_t*,int,uint8_t) - Sends the HTTP request to the server
 *
 * This function sends the HTTP request to the server
 *
 * Returns:
 * '1' on success
 * '-2' if error opening a HTTP session
 * '-3' if error receiving data or timeout waiting data
 * '-16' if error opening a HTTP session with CME_error code available
*/
int8_t Wasp3G::sendHTTPrequest(		const char* url,
									uint16_t port,
									uint8_t* data,
									uint16_t length,
									uint8_t method )
{

	int8_t answer;
	char aux_conv[3];
	memset( aux_conv, 0x00, sizeof(aux_conv) );

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[0])));	//HTTP_ACT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%u", str_aux1, url, port);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[1])));	//HTTP_ACT_REQ
	answer = sendCommand2(buffer_3G, str_aux1, ERROR_CME, HTTP_TIMEOUT, SEND_ONCE);
	if (answer == 0)
	{
		return -2;
	}
	else if (answer == 2)
	{
		return -16;
	}

	// Sends the request with the frame to the server

	switch(method)
	{
		case GET:
			// GET /getpost_frame_parser.php?frame=
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[11])));	//HTTP_GET
			printString(str_aux3, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(str_aux3);
			#endif

			for (uint16_t x=0 ; x < length; x++)
			{
				Utils.hex2str(&data[x], aux_conv, 1);
				printByte(aux_conv[0], _socket);
				printByte(aux_conv[1], _socket);
				#if _3G_debug_mode>0
					USB.print(aux_conv[0]);
					USB.print(aux_conv[1]);
				#endif
			}

			//  HTTP/1.1\r\nHost:
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[13])));	//HTTP_FRAME_1
			printString(str_aux3, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(str_aux3);
			#endif

			printString(url, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(url);
			#endif

			// \r\nContent-Length:
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[15])));	//HTTP_FRAME_3
			printString(str_aux3, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(str_aux3);
			#endif

			// 0\r\n\r\n
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[16])));	//HTTP_END_GET
			printString(str_aux3, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(str_aux3);
			#endif

			break;

		case POST:
			// POST /getpost_frame_parser.php
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[12])));	//HTTP_POST
			printString(str_aux3, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(str_aux3);
			#endif

			//  HTTP/1.1\r\nHost:
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[13])));	//HTTP_FRAME_1
			printString(str_aux3, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(str_aux3);
			#endif

			printString(url, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(url);
			#endif

			// \r\nContent-Type: application/x-www-form-urlencoded
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[14])));	//HTTP_FRAME_2
			printString(str_aux3, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(str_aux3);
			#endif

			// \r\nContent-Length:
			strcpy_P(str_aux3, (char*)pgm_read_word(&(table_HTTP[15])));	//HTTP_FRAME_3
			printString(str_aux3, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(str_aux3);
			#endif

			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[17])));	//HTTP_END_POST
			sprintf(str_aux3, "%d%s", (length * 2) + 6, str_aux1);
			printString(str_aux3, _socket);
			#if _3G_debug_mode>0
				PRINT_3G(str_aux3);
			#endif

			for (uint16_t x=0 ; x < length; x++)
			{
				Utils.hex2str(&data[x], aux_conv, 1);
				printByte(aux_conv[0], _socket);
				printByte(aux_conv[1], _socket);
				#if _3G_debug_mode>0
					USB.print(aux_conv[0]);
					USB.print(aux_conv[1]);
				#endif
			}

			break;

		default:
			break;
	}



	printByte(0x1A, _socket);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[2])));	//HTTP_ACT_DATA
	answer = waitForData(str_aux1, ERROR, HTTP_TIMEOUT, millis(), 0);
	if (answer != 1)
	{
		return -3;
	}

	return 1;

}

/* readHTTPresponse(int8_t) - Reads the response from the server
 *
 * This function reads the response from the server
 *
 * Returns:
 * '1' on success
 * '-3' if error receiving data or timeout waiting data
 * '-4' if error changing the baudrate (data received is OK)
 * '-17' if url response its not OK  (HTTP code 200)
 * '-18' if content-length field not found
 * '-19' if data field not found
*/
int8_t Wasp3G::readHTTPresponse(int8_t parse)
{
	int8_t answer;
	int16_t HTTP_data, count;
	char aux;
	unsigned long previous;
	char* aux_ptr;
	uint8_t len;


	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);

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
			PRINT_3G(F("HTTP data: "));
			USB.println(HTTP_data, DEC);
		#endif

		do{
			aux = serialRead(_socket);
			if (aux != -1)
			{
				if (count < _3G_BUFFER_SIZE)
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

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((HTTP_data > 0) && ((millis() - previous) < 10000));

		#if _3G_debug_mode>0
			PRINT_3G(F("Count remainder: "));
			USB.println(HTTP_data, DEC);
		#endif

		// Waits for new data or the end of the request
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[2])));	//HTTP_ACT_DATA
		answer = waitForData(str_aux1, ERROR, HTTP_TIMEOUT, millis(), 0);
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
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));	//CHANGE_BAUDRATE
		snprintf(str_aux2, sizeof(str_aux2), "%s%ld", str_aux1, _baudRate);
		answer=sendCommand2(str_aux2, OK_RESPONSE, ERROR);
		if (answer == 2)
		{
			return -4;
		}
		else if (answer == 1) // If the command is executed by the 3G module, changes the Waspmote baudrate
		{
			beginSerial(_baudRate, _socket);
		}

		if(parse == 1)
		{
			//EXTRAAAAA, parseo de la info. Quita cabecera y deja sólo datos
			// checks if the response is OK
			if (strstr(buffer_3G, "200 ok") == NULL)
			{
				// url response its not OK
				return -17;
			}

			// finds the data length
			aux_ptr = strstr(buffer_3G, "content-length: ");
			if (aux_ptr == NULL)
			{
				// content-length field not found
				return -18;
			}

			aux_ptr += strlen("content-length: ");

			strncpy(str_aux1, aux_ptr, strchr(aux_ptr, '\r') - aux_ptr);
			sscanf(str_aux1, "%d", &len);
			aux_ptr = strstr(buffer_3G, "\r\n\r\n");
			if (aux_ptr == NULL)
			{
				// data field not found
				return -19;
			}
			aux_ptr = aux_ptr + 4;

			strncpy(buffer_3G, aux_ptr, len);

			buffer_3G[len] = '\0';

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
			PRINT_3G(F("HTTP error: "));
			USB.println(HTTP_data, DEC);
		#endif

		HTTP_data -= 215;

		changeBaudrate(_baudRate);

		return -HTTP_data;
	}
}

#endif

// AT Comands ///////////////////////////////////////////////////////////////////


//functions with one answer
uint8_t Wasp3G::sendCommand1( const char* theText,
							  const char* expectedAnswer1)
{
    return sendCommand1(theText, expectedAnswer1, DEFAULT_TIMEOUT, SEND_DEFAULT);
}

uint8_t Wasp3G::sendCommand1(	const char* theText,
								const char* expectedAnswer1,
								unsigned long max_timeout,
								int num_tries)
{
    unsigned long timeout = 0;

	#if _3G_debug_mode>0
		PRINT_3G(F("Send command with 1 answer: "));
		USB.print(F("AT"));
		USB.println(theText);
	#endif

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

    int answer= waitForData( expectedAnswer1, expectedAnswer1, expectedAnswer1, expectedAnswer1, max_timeout, timeout, 0, 1);

	#if _3G_debug_mode>0
		PRINT_3G(F("Answer: "));
		USB.println(answer, DEC);
	#endif

    return answer;
}

//functions with two answers
uint8_t Wasp3G::sendCommand2(	const char* theText,
								const char* expectedAnswer1,
								const char* expectedAnswer2)
{
    return sendCommand2(theText, expectedAnswer1, expectedAnswer2, DEFAULT_TIMEOUT, SEND_DEFAULT);
}

uint8_t Wasp3G::sendCommand2(	const char* theText,
								const char* expectedAnswer1,
								const char* expectedAnswer2,
								unsigned long max_timeout,
								int num_tries)
{
    unsigned long timeout = 0;

    #if _3G_debug_mode>0
	    PRINT_3G(F("Send command with 2 answers: "));
	    USB.print(F("AT"));
	    USB.println(theText);
    #endif

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

    int answer= waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer2, expectedAnswer2, max_timeout, timeout, 0, 2);

    #if _3G_debug_mode>0
	    PRINT_3G(F("Answer: "));
	    USB.println(answer, DEC);
    #endif

    return answer;
}

//function with three answers
uint8_t Wasp3G::sendCommand3(	const char* theText,
								const char* expectedAnswer1,
								const char* expectedAnswer2,
								const char* expectedAnswer3,
								unsigned long max_timeout,
								int num_tries)
{
    unsigned long timeout = 0;

	#if _3G_debug_mode>0
		PRINT_3G(F("Send command with 3 answers: "));
		USB.print(F("AT"));
		USB.println(theText);
	#endif

	// try sending the command
	// wait for serial response
    timeout = millis();
    serialFlush(_socket);
	while (serialAvailable(_socket) > 0)
	{
		serialRead(_socket);
	}
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

    int answer= waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer3, expectedAnswer3, max_timeout, timeout, 0, 3);

	#if _3G_debug_mode>0
		PRINT_3G(F("Answer: "));
		USB.println(answer, DEC);
	#endif

    return answer;
}

//function with four answers
uint8_t Wasp3G::sendCommand4(	const char* theText,
								const char* expectedAnswer1,
								const char* expectedAnswer2,
								const char* expectedAnswer3,
								const char* expectedAnswer4,
								unsigned long max_timeout,
								int num_tries)
{
    unsigned long timeout = 0;

	#if _3G_debug_mode>0
		PRINT_3G(F("Send command with 4 answers: "));
		USB.print(F("AT"));
		USB.println(theText);
	#endif

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

    int answer= waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer3, expectedAnswer4, max_timeout, timeout, 0, 4);

	#if _3G_debug_mode>0
		PRINT_3G(F("Answer: "));
		USB.println(answer, DEC);
	#endif

    return answer;
}

//function to wait an specific answer
uint8_t Wasp3G::waitForData(	const char* expectedAnswer1,
								unsigned long max_timeout,
								unsigned long timeout,
								int seconds)
{
	return (waitForData( expectedAnswer1, expectedAnswer1, expectedAnswer1, expectedAnswer1, max_timeout, timeout, 0, 1));
}

uint8_t Wasp3G::waitForData(	const char* expectedAnswer1,
								const char* expectedAnswer2,
								unsigned long max_timeout,
								unsigned long timeout,
								int seconds)
{
	return (waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer2, expectedAnswer2, max_timeout, timeout, 0, 1));
}

uint8_t Wasp3G::waitForData(	const char* expectedAnswer1,
								const char* expectedAnswer2,
								const char* expectedAnswer3,
								unsigned long max_timeout,
								unsigned long timeout,
								int seconds)
{
	return (waitForData( expectedAnswer1, expectedAnswer2, expectedAnswer3, expectedAnswer3, max_timeout, timeout, 0, 1));
}

uint8_t Wasp3G::waitForData(	const char* expectedAnswer1,
								const char* expectedAnswer2,
								const char* expectedAnswer3,
								const char* expectedAnswer4,
								unsigned long max_timeout,
								unsigned long timeout,
								int seconds,
								int n_answers)
{
	char theCommand[100];

	memset(theCommand, '\0', sizeof(theCommand));

	int theLength = 0;
	int minLength;
	int maxLength;
	int it=0;
	uint8_t first=1;
	char aux;


	// Gets the maximum length and the minimum length of the all strings
	theLength=strlen(expectedAnswer1);
	minLength=theLength;
	maxLength=theLength;

	if (n_answers > 1)
	{
		theLength=strlen(expectedAnswer2);
		if(minLength>theLength)
		{
			minLength=theLength;
		}
		if(maxLength<theLength)
		{
			maxLength=theLength;
		}
	}
	if (n_answers > 2)
	{
		theLength=strlen(expectedAnswer3);
		if(minLength>theLength)
		{
			minLength=theLength;
		}
		if(maxLength<theLength)
		{
			maxLength=theLength;
		}
	}
	if (n_answers > 3)
	{
		theLength=strlen(expectedAnswer4);
		if(minLength>theLength)
		{
			minLength=theLength;
		}
		if(maxLength<theLength)
		{
			maxLength=theLength;
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
				for (it = 0; it < minLength; it++)
				{
					theCommand[it] = serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						PRINT_3G(F("Command answer1: "));
						USB.println(theCommand);
						PRINT_3G(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
				if ((n_answers > 1) && (minLength < maxLength))
				{
					first = 2;
				}
				else
				{
					first = 0;
				}
			}
			else if (first == 2)	// Gets data from serial port increasing the length of 'theCommand' from minLength to maxLength
			{
				if (serialAvailable(_socket))
				{
					it=minLength;
					minLength++;
					theCommand[it]=serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						PRINT_3G(F("Command answer2: "));
						USB.println(theCommand);
						PRINT_3G(F("Length: "));
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
					theCommand[it-1] = serialRead(_socket);
					delay(20);
					#if _3G_debug_mode>1
						PRINT_3G(F("Command answer3: "));
						USB.println(theCommand);
						PRINT_3G(F("Length: "));
						USB.println(strlen(theCommand), DEC);
					#endif
				}
			}

			if (strstr(theCommand, expectedAnswer1) != NULL)
			{
				if ((strcmp(expectedAnswer1, ERROR_CME) == 0) || (strcmp(expectedAnswer1, ERROR_CMS) == 0))
				{
					#if _3G_debug_mode>0
						PRINT_3G(F("special error "));
					#endif
					while (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);

					do{ // Gets the length of the data string
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if _3G_debug_mode>0
						USB.println(CME_CMS_code,DEC);
					#endif
				}
				return 1;
			}

			if ((strstr(theCommand, expectedAnswer2) != NULL) && (n_answers > 1))
			{
				if ((strcmp(expectedAnswer2, ERROR_CME) == 0) || (strcmp(expectedAnswer2, ERROR_CMS) == 0))
				{
					#if _3G_debug_mode>0
						PRINT_3G(F("special error "));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if _3G_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				return 2;
			}

			if ((strstr(theCommand, expectedAnswer3) != NULL) && (n_answers > 2))
			{
				if ((strcmp(expectedAnswer3, ERROR_CME) == 0) || (strcmp(expectedAnswer3, ERROR_CMS) == 0))
				{
					#if _3G_debug_mode>0
						PRINT_3G(F("special error "));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if _3G_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				return 3;
			}

			if ((strstr(theCommand, expectedAnswer4) != NULL) && (n_answers > 3))
			{
				if ((strcmp(expectedAnswer4, ERROR_CME) == 0) || (strcmp(expectedAnswer4, ERROR_CMS) == 0))
				{
					#if _3G_debug_mode>0
						PRINT_3G(F("special error "));
					#endif
					while  (serialRead(_socket) != ' ');
					CME_CMS_code=0;
					aux=serialRead(_socket);
					do{
						CME_CMS_code*=10;
						CME_CMS_code+=aux-0x30;
						aux=serialRead(_socket);
					}while (aux != '\r');
					#if _3G_debug_mode>0
						USB.println(CME_CMS_code, DEC);
					#endif
				}
				return 4;
			}

		}

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < timeout) timeout = millis();
	}

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
		PRINT_3G(F("Debug mode 1\n"));
	#endif
	#if _3G_debug_mode==2
		PRINT_3G(F("Debug mode 2\n"));
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
	_baudRate=_3G_RATE;
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
	Utils.setMux(LOW, LOW);
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
	uint8_t battery_level;
	uint8_t counter, global_counter;

	switch(pwrMode)
	{
		case _3G_ON:

			battery_level = PWR.getBatteryLevel();

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
				PRINT_3G(F("Module status: "));
				USB.println(ready,DEC);
			#endif
			global_counter = 3;
			counter = 15;
			while ((ready == 0) && (global_counter > 0))
			{
				delay(500);
				getIfReady();
				#if _3G_debug_mode>0
					PRINT_3G(F("Module status: "));
					USB.println(ready,DEC);
				#endif
				counter--;
				if (counter == 0)
				{
					#if _3G_debug_mode>0
						PRINT_3G(F("Retry start\n"));
					#endif
					digitalWrite(GPRS_PW, LOW);
					delay(3000);
					digitalWrite(GPRS_PW, HIGH);
					counter = 15;
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

				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[0])));	//POWER_FULL
				answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);

				if (battery_level < 30)
				{
					PRINT_3G(F("********************\n"));
					PRINT_3G(F("Danger! Low battery!\n"));
					PRINT_3G(F("********************\n"));
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
					PRINT_3G(F("Reactivating UART\n"));
				#endif
				begin();
			}
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[0])));	//POWER_FULL
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			break;

		case _3G_RF_OFF:
			if (_pwrMode == _3G_SLEEP)
			{
				#if _3G_debug_mode>0
					PRINT_3G(F("Reactivating UART\n"));
				#endif
				begin();
			}
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[1])));	//POWER_RF_OFF
			answer=sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
			break;

		case _3G_MINIMUM:
			if (_pwrMode == _3G_SLEEP)
			{
				#if _3G_debug_mode>0
					PRINT_3G(F("Reactivating UART\n"));
				#endif
				begin();
			}
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[2])));	//POWER_MIN
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
			getIfReady();
			if (ready == 0)
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
 * Returns '1' when connected,
 * '0' if not registered and the module is not currently searching a new operator,
 * '-2' if not registered, but the module is currently searching a new operator,
 * '-3' if registration denied
 * and '-4' if the state is unknown
*/
int8_t Wasp3G::check(unsigned long time){

	unsigned long previous;
	int8_t answer;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[54])));	//CHECK
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[55])));	//CHECK_RES

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

	#if _3G_debug_mode>0
		PRINT_3G(F("Network status: "));
		USB.println(answer, DEC);
	#endif

	if (((answer != 1) && (answer != 5)) || ((millis() - previous) > (time * 1000)))
	{
		return -answer;
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[4])));	//SET_TIME
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%02u/%02u/%02u,%02u:%02u:%02u+00\"", str_aux1, RTC.year, RTC.month, RTC.date, RTC.hour, RTC.minute, RTC.second);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[12])));	//SET_PIN
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s", str_aux1, pin);
	answer=sendCommand3(buffer_3G, OK_RESPONSE, ERROR_CME, ERROR, 2000, SEND_ONCE);

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

	uint8_t answer = 0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[59])));	//CHANGE_PIN
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"SC\",\"%s\",\"%s\"", str_aux1, old_pin, new_pin);
	answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);

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

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[13])));	//GET_IMEI
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[14])));	//GET_IMEI_R
	answer=sendCommand2(str_aux1, str_aux2, ERROR);

	if (answer == 1)
	{
		counter=0;
		previous = millis();
		do{
			// Waits for data
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) <= 2000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}

			}
			buffer_3G[counter]=serialRead(_socket);
			if ((buffer_3G[counter] != '\r') && (buffer_3G[counter] != '\n'))
			{
				counter++;
			}

			if (millis() < previous)
			{
				previous = millis();
			}
		}while ((buffer_3G[counter] != '\r') && ((millis()-previous) <= 2000));

		if (buffer_3G[counter] == '\r')
		{
			buffer_3G[counter] = '\0';
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

	unsigned long previous;
	int8_t counter=0;

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[15])));	//GET_IMSI
	sendCommand1(str_aux1, "\r\n");
	previous = millis();
	counter = 0;
	do{
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
		{
			if (millis() < previous)
			{
				previous = millis();
			}
		}
		buffer_3G[counter] = serialRead(_socket);

		if ((buffer_3G[counter] != '\r') && (buffer_3G[counter] != '\n'))
		{
			counter++;
		}

		if (millis() < previous)
		{
			previous = millis();
		}
	}while ((((buffer_3G[counter] != '\r') && (buffer_3G[counter] != '\n')) || (counter == 0)) && ((millis()-previous) < 3000));

	if (buffer_3G[counter] == '\r')
	{
		buffer_3G[counter] = '\0';
		return 1;
	}

	return 0;
}


/* manageIncomingData() - manage incoming data from serial port, executing proper functions to store received data
 *
 * This function manages incoming data from serial port, executing proper functions to store received data
 *
 * Returns '1' for call, '2' for SMS, '3' for IP data and '0' for error or not data
 * Returns in buffer_3G
 * Incoming call --> phone number
 * SMS --> SMS index
 * IP --> Data received. IP_dir -->IP addess and port
*/
int8_t	Wasp3G::manageIncomingData(){
	return manageIncomingData(20000);
}
int8_t	Wasp3G::manageIncomingData(unsigned long waiting_time){

	int16_t a;		 //counter and auxiliar variable
	unsigned long previous = 0;

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	a=0;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[57])));	//INCOMING_CALL
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[58])));	//INCOMING_SMS

	#if IP_FUSE==1
		strcpy_P(str_aux3, (char*)pgm_read_word(&(table_IP[24])));		//INCOMING_IP
	#endif
	// Wait for data
	serialFlush(_socket);
	previous = millis();
  #if _3G_debug_mode>0
    PRINT_3G(F(""));
  #endif
	while (((millis()-previous) < waiting_time) && (a < _3G_BUFFER_SIZE) && (a >= 0))
	{
		if (serialAvailable(_socket) != 0)
		{
			buffer_3G[a] = serialRead(_socket);	// Reads a byte
			#if _3G_debug_mode>0
				USB.print(char(buffer_3G[a]));
			#endif
			a++;

			// Check the received data
			if ((strstr(buffer_3G, str_aux1)) != NULL)
			{
				#if _3G_debug_mode>0
					PRINT_3G(F("\nIncoming call\n"));
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
			else if ((strstr(buffer_3G, str_aux2)) != NULL)
			{
				#if _3G_debug_mode>0
					PRINT_3G(F("\nIncoming SMS\n"));
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
			else if ((strstr(buffer_3G, str_aux3)) != NULL)
			{
				#if _3G_debug_mode>0
					PRINT_3G(F("\nIncoming IP data\n"));
				#endif

				a = readIPdata();
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[0])));		//CALL
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s;", str_aux1, tlfNumber);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[19])));	//NO_CARRIER
	answer = sendCommand2(buffer_3G, OK_RESPONSE, str_aux1);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[0])));		//CALL
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s;", str_aux1, tlfNumber);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[19])));	//NO_CARRIER
	answer = sendCommand2(buffer_3G, OK_RESPONSE, str_aux1);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[1])));		//LINE_ID
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
	uint8_t a = 0;
	unsigned long previous;

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);

	previous = millis();

	// Reads up to the phone number
	do{
		while (!serialAvailable(_socket) && ((millis()-previous) < 2000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}

		buffer_3G[0] = serialRead(_socket);	// Reads a byte

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((buffer_3G[0] != '"') && ((millis() - previous) < 2000));

	if ((millis() - previous) > 2000)
	{
		return 0;
	}

	// Stores in buffer_3G the phone number
	#if _3G_debug_mode>0
		PRINT_3G(F("Phone number: "));
	#endif
	previous = millis();
  #if _3G_debug_mode>0
    PRINT_3G("");
  #endif
	do{
		while (!serialAvailable(_socket) && ((millis()-previous) < 2000))
		{
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();
		}

		buffer_3G[a] = serialRead(_socket);	// Reads a byte
		#if _3G_debug_mode>0
			USB.print(char(buffer_3G[a]));
		#endif
		a++;
		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((buffer_3G[a-1] != '"') && ((millis() - previous) < 2000));

	buffer_3G[a - 1] = '\0';

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
int8_t Wasp3G::hangUp(){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[2])));		//HANG_CALL
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


	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[3])));		//AUTO_ANSWER
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, rings);
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[4])));		//CALL_ASNWER
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_GSM[19])));	//NO_CARRIER
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_GSM[20])));	//BEGIN
	strcpy_P(str_aux4, (char*)pgm_read_word(&(table_GSM[21])));	//CONNECT
	answer = sendCommand3(str_aux1, str_aux2, str_aux3, str_aux4, 4000, SEND_ONCE);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[5])));		//TONE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, tone);
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
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[6])));		//MUTE_RINGER
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1", str_aux1);
		return sendCommand1(buffer_3G, OK_RESPONSE);
	}
	else // If level isn't '0' disables the silent mode and set the volume level
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[6])));		//MUTE_RINGER
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
		answer=sendCommand1(buffer_3G, OK_RESPONSE);
		if (answer == 1)
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[7])));		//LVL_RINGER
			snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, level-1);
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[8])));		//LINE_ID_PRES
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%u", str_aux1, mode);
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[9])));		//LINE_ID_REST
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%u", str_aux1, mode);
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[10])));	//PHONE_ACT
	snprintf(str_aux2, sizeof(str_aux2), "%s: ", str_aux1);
	answer = sendCommand1(str_aux1, str_aux2);

	if (answer == 1)
	{
		answer = serialRead(_socket) - 0x30;
		if (answer == 0)
		{
			answer = 1;
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[11])));	//SMS_MODE
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[12])));	//SEND_SMS
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, tlfNumber);

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

	answer = waitForData( OK_RESPONSE, 10000, millis(), 0);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[13])));	//SMS_INFO
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR_CMS);
	if (answer == 0)
	{
		return 0;
	}
	else if (answer == 2)
	{
		return -2;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[16])));	//SMS_MEMORY
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"SM\",\"SM\",\"SM\"", str_aux1);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[17])));	//SMS_MEMORY_R
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[14])));	//SMS_READ
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, index-1);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[15])));	//SMS_READ_R
	answer = sendCommand2(buffer_3G, str_aux1, ERROR_CMS);

	if (answer == 1)
	{
		counter = 0;
		previous = millis();

		// reads up to the sender phone number
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			if (serialRead(_socket) == '"'){
				counter++;
			}

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((counter < 3) && ((millis() - previous) < 2000));

		// stores in 'tlfNumber' the sender phone number
		#if _3G_debug_mode>0
			PRINT_3G(F("Phone number\n"));
		#endif
		counter = 0;
    #if _3G_debug_mode>0
      PRINT_3G("");
    #endif
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			tlfNumber[counter] = serialRead(_socket);
			#if _3G_debug_mode>0
				USB.print(char(tlfNumber[counter]));
			#endif
			counter++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((tlfNumber[counter-1] != '"') && ((millis() - previous) < 2000));
		tlfNumber[counter-1] = '\0';

		// reads up to the message text
		counter = 0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}

			buffer_3G[0] = serialRead(_socket);

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[0] != '\n') && ((millis() - previous) < 2000));

		// stores the message text in 'buffer_3G'
		#if _3G_debug_mode>0
			USB.println();
			PRINT_3G(F("SMS body\n"));
      PRINT_3G(F(""));
		#endif
		counter = 0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 2000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[counter] = serialRead(_socket);
			#if _3G_debug_mode>0
				USB.print(char(buffer_3G[counter]));
			#endif
			counter++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((strstr(buffer_3G, "OK\r\n") == NULL) && ((millis() - previous) < 2000) && (counter < _3G_BUFFER_SIZE));
		buffer_3G[counter-6] = '\0';
		#if _3G_debug_mode>0
			USB.println();
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[16])));	//SMS_MEMORY
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"SM\",\"SM\",\"SM\"", str_aux1);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[17])));	//SMS_MEMORY_R
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GSM[18])));	//SMS_DELETE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%u", str_aux1, sms_index - 1);
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

/* incomingSMS() - Gets the index of the incoming SMS
 *
 * This function gets the index of the incoming SMS
 *
 * This function should be executed only inside 'manageIncomingData' function.
 *
 * Returns the index of SMS, '0' if error
*/
int8_t Wasp3G::incomingSMS(){

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
		buffer_3G[count] = serialRead(_socket);
		count++;

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();
	}while ((buffer_3G[count-1] != '\r') && ((millis() - previous) < 1000) && (count < _3G_BUFFER_SIZE));

	buffer_3G[count-1] = '\0';

	count = atoi(buffer_3G);
	//index 0 --> 1
	count++;

	#if _3G_debug_mode>0
		PRINT_3G(F("SMS index: "));
		USB.println(count, DEC);
	#endif

	if ((millis() - previous) > 1200)
	{
		return 0;
	}

	return count;
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[0])));		//CAM_START
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[26])));		//CAM_NO_SENSOR
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[27])));		//CAM_INVALID_STATE
	answer=sendCommand3(str_aux1, OK_RESPONSE, str_aux2, str_aux3, 5000, SEND_ONCE);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[1])));		//CAM_STOP
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
	answer=sendCommand2(str_aux1, OK_RESPONSE, str_aux2, 5000, SEND_ONCE);

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
	int8_t count;
	unsigned long previous;

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);

	digitalWrite(FILTER_ENABLE, LOW);
	delay(500);

	// Takes the picture
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[16])));		//CAM_TAKE_PIC
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[30])));		//CAM_EP
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
	strcpy_P(str_aux4, (char*)pgm_read_word(&(table_CAMERA[27])));		//CAM_INVALID_STATE
	strcpy_P(str_aux5, (char*)pgm_read_word(&(table_CAMERA[28])));		//CAM_NO_MEM

	answer = sendCommand4(str_aux1, str_aux2, str_aux3, str_aux4, str_aux5, 10000, SEND_ONCE);

	digitalWrite(FILTER_ENABLE, HIGH);

	count = 0;
	if(answer == 1) // If answer is OK gets the name of the video and saves it in 'buffer_3G'
	{
		previous = millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 1000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[count] = serialRead(_socket);
			count++;

			if (millis() < previous)
			{
				previous = millis();
			}
		}while ((buffer_3G[count-1] != '\r') && ((millis()-previous) < 1000));
		buffer_3G[count-1] = '\0';

		// Waits the OK response
		waitForData(OK_RESPONSE, DEFAULT_TIMEOUT, millis(), 0);

		return 1;
	}

	if (answer > 1)
	{
		return -answer;
	}

	return 0;

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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[20])));		//CAM_START_VIDEO
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[31])));		//CAM_EV
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
	strcpy_P(str_aux4, (char*)pgm_read_word(&(table_CAMERA[27])));		//CAM_INVALID_STATE
	strcpy_P(str_aux5, (char*)pgm_read_word(&(table_CAMERA[28])));		//CAM_NO_MEM
	answer=sendCommand4(str_aux1, str_aux2, str_aux3, str_aux4, str_aux5, 5000, SEND_ONCE);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[21])));		//CAM_PAUSE_VIDEO
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[27])));		//CAM_INVALID_STATE
	answer=sendCommand3(str_aux1, OK_RESPONSE, str_aux2, str_aux3, 2000, SEND_ONCE);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[22])));		//CAM_RESUME_VIDEO
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[27])));		//CAM_INVALID_STATE
	answer=sendCommand3(str_aux1, OK_RESPONSE, str_aux2, str_aux3, 2000, SEND_ONCE);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[23])));		//CAM_STOP_VIDEO
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
	strcpy_P(str_aux3, (char*)pgm_read_word(&(table_CAMERA[27])));		//CAM_INVALID_STATE
	answer=sendCommand3(str_aux1, OK_RESPONSE, str_aux2, str_aux3, 1000, SEND_ONCE);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[11])));		//CAM_ROT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s", str_aux1, rotation);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[27])));		//CAM_INVALID_STATE
	answer=sendCommand3(buffer_3G, OK_RESPONSE, str_aux1, str_aux2, 1000, SEND_ONCE);

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
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));	//CAM_DIM
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[3])));	//RES_STAMP
			break;
		case 1:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));	//CAM_DIM
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[4])));	//RES_QQVGA
			break;
		case 2:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));	//CAM_DIM
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[5])));	//RES_QCIF
			break;
		case 3:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));	//CAM_DIM
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[6])));	//RES_QVGA
			break;
		case 4:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));	//CAM_DIM
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[7])));	//RES_CIF
			break;
		case 5:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));	//CAM_DIM
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[8])));	//RES_VGA
			break;
		case 6:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));	//CAM_DIM
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[9])));	//RES_XGA
			break;
		default:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[2])));	//CAM_DIM
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[6])));	//RES_QVGA
			break;
	}

	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s", str_aux1, str_aux2);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[26])));		//CAM_NO_SENSOR
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
	answer=sendCommand3(buffer_3G, OK_RESPONSE, str_aux1, str_aux2, 2000, SEND_ONCE);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[10])));		//CAM_FPS
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%u", str_aux1, fps);

	do{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[27])));		//CAM_INVALID_STATE
		answer = sendCommand3(buffer_3G, OK_RESPONSE, str_aux1, str_aux2, 2000, SEND_ONCE);
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[14])));		//CAM_BRIGHT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%u", str_aux1, mode);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[29])));		//CAM_NO_START
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[27])));		//CAM_INVALID_STATE
	answer=sendCommand3(buffer_3G, OK_RESPONSE, str_aux1, str_aux2, 2000, SEND_ONCE);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[18])));		//CAM_NAME_PIC
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, name);

	return (sendCommand1(buffer_3G, OK_RESPONSE));
}

/* pictureTimeStamp(uint8_t) - adds date frame on the picture.
 *
 * The function activates or deactivates to add date frame on the picture
 *
 * Returns '1' on success and '0' if error
*/
int8_t Wasp3G::pictureTimeStamp(uint8_t state){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[19])));		//CAM_TIME_STAMP
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, state);

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
			PRINT_3G(F("X value: "));
			USB.println(x_acc, DEC);
			PRINT_3G(F("Y value: "));
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
		PRINT_3G(F("LDR value: "));
		USB.println(aux,DEC);
	#endif

	if ((aux > THRESHOLD_LIGHT_2) && (THRESHOLD_LIGHT_1 > aux))
	{
		#if _3G_debug_mode>0
			PRINT_3G(F("Level 1\n"));
		#endif
		selectFilter(0);
		powerIRLED(1);
	}
	else if (aux < THRESHOLD_LIGHT_2)
	{
		#if _3G_debug_mode>0
			PRINT_3G(F("Level 2\n"));
		#endif
		selectFilter(0);
		powerIRLED(3);
	}
	else
	{

		aux=analogRead(SENS_IR);
		aux=analogRead(SENS_IR);
		#if _3G_debug_mode>0
			PRINT_3G(F("IR value: "));
			USB.println(aux,DEC);
		#endif

		if (THRESHOLD_IR < aux)
		{
			selectFilter(1);
			#if _3G_debug_mode>0
				PRINT_3G(F("Level 0. IR filter disabled\n"));
			#endif
		}
		else
		{
			selectFilter(0);
			#if _3G_debug_mode>0
				PRINT_3G(F("Level 0. IR filter enabled\n"));
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

	//intFlag &= ~(PIR_3G_INT);
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[32])));		//V_CALL_START
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s", str_aux1, phone_number);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[37])));		//V_ACCEPTED
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[41])));		//V_END
	answer = sendCommand2(buffer_3G, str_aux1, str_aux2);
	if (answer != 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));		//V_CALL_END
		sendCommand1(str_aux1, OK_RESPONSE);
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return 0;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[38])));		//V_RECV
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[41])));		//V_END
	answer = waitForData(str_aux1, str_aux2, 30000, millis(), 0);
	if (answer == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));		//V_CALL_END
		sendCommand1(str_aux1, OK_RESPONSE);
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return -1;
	}
	else if (answer == 2)
	{
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return -1;
	}

	answer = waitForData(V_SETUP, V_END, 30000, millis(), 0);
	if (answer == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));		//V_CALL_END
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
	answer = waitForData(str_aux1, str_aux2, 30000, 0, 0);
	if (answer == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));		//V_CALL_END
		sendCommand1(str_aux1, OK_RESPONSE);
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		return -3;
	}
	else if (answer == 2)
	{
		return -3;
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[35])));		//V_RECORD
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, record);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[37])));		//V_ACCEPTED
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_CAMERA[41])));		//V_END
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[33])));		//V_CALL_END
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[36])));		//V_QUALITY
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, VideoQuality);
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_CAMERA[34])));		//V_DMTF
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, DMTF_str);
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
 * Returns '1' on success,
 * '-2' if error setting the connection parameters (APN)
 * '-3' if error setting the FTP server ('-13' if CME error available),
 * '-4' if error setting the FTP port ('-14' if CME error available)
 * '-5' if error setting the FTP mode ('-15' if CME error available),
 * '-6' if error setting the FTP type ('-16' if CME error available)
 * '-7' if error setting the user name ('-17' if CME error available),
 * '-8' if error setting the FTP password ('-18' if CME error available),
*/
int8_t Wasp3G::configureFTP(const char* server,
							const char* port,
							const char* user_name,
							const char* password,
							uint8_t mode,
							const char* type)
{

	int8_t answer;
	int8_t count;

	// Sets connection parameters (apn, user_name, password)
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));	//_3G_CON
	snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"IP\",\"%s\"", str_aux1, _apn);
	count = 10;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return -2;
	}

	// Sets username and password
	if (strlen(_apn_login) == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
	}
	else
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"%s\",\"%s\"", str_aux1, _apn_password, _apn_login);
	}
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 0)
	{
		return -2;
	}
	else if (answer == 2)
	{
		return 0;
	}

	// Sets FTP server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[0])));		//FTP_SERVER
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, server);
	count = 10;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[1])));		//FTP_PORT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s", str_aux1, port);
	count = 10;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count > 0));
	if (count == 0)
	{
		if(answer == 2)
		{
			return -14;
		}
		else
		{
			return -4;
		}
	}

	// Sets FTP mode
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[2])));		//FTP_MODE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%u", str_aux1, mode);
	count = 10;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[3])));		//FTP_TYPE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s", str_aux1, type);
	count = 10;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[4])));		//FTP_UN
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, user_name);
	count = 10;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[5])));		//FTP_UN
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, password);
	count = 10;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
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
 * Origin values allowed:  	0 – current directory,
 * 							1 – “C:/Picture” directory,
 * 							2 – “C:/Video” directory,
 * 							3 – “C:/VideoCall” directory,
 * 							4 – “D:/Picture” directory,
 * 							5 – “D:/Video” directory,
 * 							6 – “D:/VideoCall” directory,
 * 							7 – “C:/Audio” directory,
 * 							8 – “D:/Audio” directory
 *
 * Returns '1' on success,
 * '0' if error,
 * '-2' if error with CME code (FTP error)
 * '-3' if error getting the file of the size to upload.
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

	// Then, restart 3G+GPS connection:
	count = 10;

	if (check3Gattach() == 1)
	{
		// Dettachs 3G:
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[9])));	//AT_3G_ATT_OFF
		do{
			answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
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
	count = 10;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[8])));	//AT_3G_ATT_ON
	do{
		answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR_CME);
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
	previous = millis();
	while ((check3Gattach() != 1) && ((millis()-previous) < 30000))
	{
		delay(2000);
		if (millis() < previous)
		{
			previous = millis();
		}
	}
	if ((millis() - previous) > 30000)
	{
		return -4;
	}


	answer = check3Gconnection(90);

	if (answer != 1)
	{
		return 0;
	}

	// Send the file and selects the origin location
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[10])));	//FTP_PUT_FILE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%u", str_aux1, destination_path, origin);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[11])));	//FTP_PUT_FILE_RES
	count = 3;
	do{
		answer = sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR, (file_size / 10) + 10000, SEND_ONCE);
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
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < (file_size / 10)))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}

			if (millis() < previous)
			{
				previous = millis();
			}

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
 * Destination values allowed:	0 – current directory
 * 								1 – “C:/Picture” directory
 * 								2 – “C:/Video” directory
 * 								3 – “C:/VideoCall” directory
 * 								4 – “D:/Picture” directory
 * 								5 – “D:/Video” directory
 * 								6 – “D:/VideoCall” directory
 * 								7 – “C:/Audio” directory
 * 								8 – “D:/Audio” directory
 *
 * max_time is the total time in seconds to download the file from the server
 *
 * Returns '1' on success, '0' if error, '-2' if error with CME code (FTP error)
*/
int8_t Wasp3G::downloadFile(const char* origin_path, uint8_t destination, unsigned long max_time){

	uint8_t answer;
	uint8_t count;

	answer = check3Gconnection(90);

	if (answer != 1)
	{
		return -3;
	}


	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	// Request the file and selects the destination location
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[6])));		//FTP_GET_FILE
	if (strchr(origin_path, '/') == strrchr(origin_path, '/'))
	{
		snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%u", str_aux1, origin_path + 1, destination);
	}
	else
	{
		snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%u", str_aux1, origin_path, destination);
	}

	count = 3;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[7])));		//FTP_GET_FILE_RES
	do{
		delay(10000);
		answer = sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR, max_time*1000, SEND_ONCE);
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
 * Returns '1' on success
 * '0' if error
 * '-2' if error with CME code (FTP error)
 * '-3' if error getting file size from SD
*/
int8_t Wasp3G::uploadData(const char* SD_file, const char* FTP_destination_path){

	int8_t answer;
	int i;
	unsigned long previous, file_time;

	answer = sendXModemFile(SD_file, strrchr(FTP_destination_path, '/') + 1);

	SD.ON();
	file_time = SD.getFileSize(SD_file) + TRANSFER_BASE_TIME;
	SD.OFF();

	#if _3G_debug_mode>0
		PRINT_3G("Max upload time: ");
		USB.println(file_time, DEC);
	#endif

	if (answer == 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[10])));	//FTP_PUT_FILE
		snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",0", str_aux1, FTP_destination_path);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[11])));	//FTP_PUT_FILE_RES
		answer = sendCommand2(buffer_3G, str_aux1, ERROR_CME, file_time, SEND_ONCE);

		previous = millis();

		if (answer == 1)
		{
			//Reads the FTP code
			i = 0;
			do{
				while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
				{
					if (millis() < previous)
					{
						previous = millis();
					}
				}
				buffer_3G[i] = serialRead(_socket);
				i++;

				if (millis() < previous)
				{
					previous = millis();
				}
			}while ((buffer_3G[i-1] != '\r') && ((millis()-previous) < 3000));

			buffer_3G[i-1] = '\0';
			i = atoi(buffer_3G);

			del(strrchr(FTP_destination_path, '/') + 1);

			if (i == 0)
			{
				return 1;
			}
			else
			{
				return (190 - i);
			}

		}

	}

	return answer;

}

/* downloadData(const char*, const char*) - Downloads data from FTP server to Waspmote
 *
 * This function downloads data to Waspmote from FTP server
 *
 * Returns '1' on success
 * '0' if error
 * '-2' if error with CME code (FTP error)
 * '-3' if error sending the file from 3G module to Waspmote's SD
*/
int8_t Wasp3G::downloadData(const char* FTP_file, const char* SD_destination_path){

	uint8_t answer=1;
	unsigned long file_time;

	//Gets the file size from the FTP
	file_time = getFTPsize(FTP_file);

	if (long(file_time) == -1)
	{
		file_time = TRANSFER_BASE_TIME;
	}
	else
	{
		file_time += TRANSFER_BASE_TIME;
	}

	// Waspmote can't manage the incoming packets of 1KB from the 3G module
	// First downloads the file to the 3G module

	#if _3G_debug_mode>0
		PRINT_3G("Max download time: ");
		USB.println(file_time, DEC);
	#endif

	answer = downloadFile( FTP_file, 0, file_time);

	if (answer == 1)
	{
		//if the file have been downloaded correctly, it will be transferred to Waspmote SD
		if (strrchr(FTP_file, '/') == NULL)
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

/* getFTPsize(const char*) - Gets the file size from an FTP server
 *
 * This function connects to an FTP server and gets the size of a file
 *
 * Returns the size of the file
 * '-1' if error with CME code (FTP error)
*/
unsigned long Wasp3G::getFTPsize(const char* FTP_file)
{
	int8_t answer;
	uint16_t i, j;
	unsigned long previous;

	answer = check3Gconnection(90);

	if (answer != 1)
	{
		return -2;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[26])));	//FTP_LIST
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=\"%s\"", str_aux1, FTP_file);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[27])));	//FTP_LIST_RES
	answer = sendCommand2(buffer_3G, str_aux1, ERROR_CME, FTP_TIMEOUT, SEND_ONCE);
	previous = millis();

	memset( buffer_3G, '\0', _3G_BUFFER_SIZE);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[28])));	//FTP_LIST_END
	if (answer == 1)
	{
		//First, reads the number of incoming bytes
		i = 0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[i] = serialRead(_socket);
			i++;

			if (millis() < previous)
			{
				previous = millis();
			}
		}while ((buffer_3G[i-1] != '\r') && ((millis()-previous) < 3000));

		buffer_3G[i-1] = '\0';
		j = atoi(buffer_3G);

		//Then reads the bytes
		serialRead(_socket);
		i = 0;
		do{
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[i] = serialRead(_socket);
			i++;

			if (millis() < previous)
			{
				previous = millis();
			}
		}while ((i < j) && ((millis()-previous) < 3000));

		buffer_3G[i] = '\0';

		// Parses the string getting the file size
		strtok(buffer_3G, " ");
		strtok(NULL, " ");
		strtok(NULL, " ");
		strtok(NULL, " ");
		strcpy(buffer_3G,strtok(NULL, " "));

		// Waits for the en string
		waitForData(str_aux1, ERROR_CME, FTP_TIMEOUT, millis(), 0);
		// Converts from the string to a long value
		return atol(buffer_3G);
	}

	return -1;
}

/* loginFPTS(const char*, uint16_t, const char*, const char*, uint8_t, const char*) - Acquires the SSL stack and logs into the FTPS server
 *
 * Acquires the SSL stack and logs into the FTPS server
 *
 * Returns '1' on success
 * '-2' if error setting the connection parameters (APN)
 * '-3' if error acquiring the SSL stack
 * '-4' error login into the server,
 * '-5' if timeout when logs in
*/
int8_t Wasp3G::loginFPTS(const char* server, uint16_t port, const char* user_name, const char* password){

	int8_t answer;
	int8_t count;

	// Sets connection parameters (apn, user_name, password)
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));	//_3G_CON
	snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"IP\",\"%s\"", str_aux1, _apn);
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
	if (strlen(_apn_login) == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
	}
	else
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"%s\",\"%s\"", str_aux1, _apn_password, _apn_login);
	}
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 0)
	{
		return -2;
	}
	else if (answer == 2)
	{
		return 0;
	}

	// Releases old SSL stack if there is
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[15])));	//RELEASE_SSL_STACK
	sendCommand2(str_aux1, OK_RESPONSE, ERROR);

	// Acquires SSL stack
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[14])));	//ACQUIRE_SSL_STACK
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return -3;
	}

	// Logs into the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[16])));	//FTPS_LOGIN
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=\"%s\",%u,\"%s\",\"%s\"", str_aux1, server, port, user_name, password);
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[22])));	//FTPS_PUT_FILE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%u", str_aux1, destination_path, origin);

	count = 3;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[23])));	//FTPS_PUT_FILE_RES
	do{
		answer = sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR, (file_size / 10) + 1000, SEND_ONCE);
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[18])));	//FTPS_GET_FILE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%u", str_aux1, origin_path, destination);

	count=3;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[19])));	//FTPS_GET_FILE_RES
	do{
		answer=sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR, max_time*100, SEND_ONCE);
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
 * Returns '1' on success
 * '0' if error
 * '-2' if error with CME code (FTPS error)
 * '-3' if error getting file size from SD
*/
int8_t Wasp3G::uploadDataSecure(const char* SD_file, const char* FTP_destination_path){

	uint8_t answer;
	uint16_t count;
	long file_size;

	//Sends the command to send data
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[24])));	//FTPS_PUT_FILE_SIO
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, FTP_destination_path);

	count=3;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[25])));	//FTPS_PUT_FILE_RES_SIO
	do{
		answer=sendCommand2(buffer_3G, str_aux1, ERROR_CME, 30000, SEND_ONCE);
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
				PRINT_3G(F("Error reading SD file size\n"));
			#endif// Sends <CTRL+Z>:
			count = 3;
			#if _3G_debug_mode>0
			PRINT_3G(F("Sends CTRL+Z\n"));
			#endif
			printByte(0x1A, _socket);
			do{
				answer = waitForData(OK_RESPONSE, ERROR_CME, 10000, millis(), 0);
				count--;
			}while ((answer != 1) && (count > 0));
			SD.OFF();
			return -3;
		}
		else
		{
			#if _3G_debug_mode>0
				PRINT_3G(F("file size: "));
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
					PRINT_3G(F("bytes sent : "));
					USB.println(count,DEC);
				#endif
			}while (count < file_size);

			SD.OFF();

			// Sends <CTRL+Z>:
			count = 3;
			#if _3G_debug_mode>0
				PRINT_3G(F("Sends CTRL+Z\n"));
			#endif
			printByte(0x1A, _socket);
			do{
				answer = waitForData(OK_RESPONSE, ERROR_CME, 10000, millis(), 0);
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
 * Returns '1' on success
 * '0' if error
 * '-2' if error with CME code (FTP error)
 * '-3' if error sending the file from 3G module to Waspmote's SD
*/
int8_t Wasp3G::downloadDataSecure(const char* FTP_file, const char* SD_destination_path, uint16_t max_time){

	uint8_t answer;

	// Waspmote can't manage the incoming packets of 1KB from the 3G module
	// First downloads the file to the 3G module

	answer = downloadFileSecure( FTP_file, 0, max_time);

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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[17])));	//FTPS_LOGOUT
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return -2;
	}

	// Releases SSL stack
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_FTP[15])));	//RELEASE_SSL_STACK
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

	uint8_t answer;

	// Sets the SMTP server address and port
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[0])));	//SMTP_SERVER
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%d", str_aux1, server, port);
	answer = sendCommand1(buffer_3G, OK_RESPONSE);
	if (answer == 0)
	{
		return -1;
	}

	// Sets the SMTP username and password
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[1])));	//SMTP_AUTH
	snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"%s\",\"%s\"", str_aux1, username, password);
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[0])));	//SMTP_SERVER
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%d", str_aux1, server, port);
	answer = sendCommand1(buffer_3G, OK_RESPONSE);
	if (answer == 0)
	{
		return 0;
	}

	// Sets the SMTP username and password
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[1])));	//SMTP_AUTH
	snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPfrom( const char*, const char*) - Sets sender address and name
 *
 * This function sets sender address and name
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPfrom( const char* mail_address, const char* name){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[2])));	//SMTP_FROM
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",\"%s\"", str_aux1, mail_address, name);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPrecipient(uint8_t, uint8_t, const char*, const char*) - Sets recipient address and name (TO/CC/BCC)
 *
 * This function sets recipient address and name (TO/CC/BCC)
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPrecipient(uint8_t kind, uint8_t index, const char* mail_address, const char* name){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[3])));	//SMTP_RCPT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,%d,\"%s\",\"%s\"", str_aux1, kind, index, mail_address, name);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPsubject( const char*) - Sets the subject of the email
 *
 * This function sets the subject of the email
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPsubject( const char* subject){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[4])));	//SMTP_SUBJECT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, subject);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPbody( const char*) - Sets the body of the email
 *
 * This function sets the body of the email
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPbody( const char* body){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[5])));	//SMTP_BODY
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, body);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPattach( uint8_t, const char*) - Add attachments to the email
 *
 * This function adds attachments to the email
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::setSMTPattach( uint8_t index, const char* file){

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[6])));	//SMTP_ATTACH
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,\"%s\"", str_aux1, index, file);
	return (sendCommand1(buffer_3G, OK_RESPONSE));

}

/* setSMTPsend() - Sends the email
 *
 * This function sends the email
 *
 * Returns '1' on success,
 * '0' if error setting the apn,
 * '-2' error sendig the email
 * '-3' if error setting the apn with cme error code available
*/
int8_t Wasp3G::setSMTPsend(){

	int8_t answer, count;

	// Sets APN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));	//_3G_CON
	snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"IP\",\"%s\"", str_aux1, _apn);
	count = 3;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return 0;
	}

	// Sets username and password
	if (strlen(_apn_login) == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
	}
	else
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"%s\",\"%s\"", str_aux1, _apn_password, _apn_login);
	}
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 0)
	{
		return -2;
	}
	else if (answer == 2)
	{
		return 0;
	}

	// Sends the email
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[7])));	//SMTP_SEND
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[8])));	//SMTP_SEND_R
	answer = sendCommand2(str_aux1, str_aux2, ERROR, SMTP_TIMEOUT, SEND_ONCE);
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
 * Returns '1' on success,
 * '0' if error setting the apn,
 * '-2' error setting the parameters of POP3 server
 * '-3' if error setting the apn with cme error code available
*/
int8_t Wasp3G::setPOP3server(const char* server, uint16_t port, const char* username, const char* password){

	int8_t answer, count;

	// Sets APN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));	//_3G_CON
	snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"IP\",\"%s\"", str_aux1, _apn);
	count = 3;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return 0;
	}

	// Sets username and password
	if (strlen(_apn_login) == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
	}
	else
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"%s\",\"%s\"", str_aux1, _apn_password, _apn_login);
	}
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 0)
	{
		return -2;
	}
	else if (answer == 2)
	{
		return 0;
	}

	// Sets the POP3 server, port, username and password
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[9])));	//POP3_SERVER
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=\"%s\",\"%s\",\"%s\",%d", str_aux1, server, username, password, port);
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
 * Returns the total number of emails,
 * '-2' if error logging in the POP3 server
 * '-3' if error getting the e-mail number
*/
int Wasp3G::getPOP3list(){

	int8_t answer;
	unsigned long previous;
	int count;

	// Logs into the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[10])));	//POP3_IN
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	answer = sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);
	if ((answer == 0) || (answer == 2))
	{
		return -1;
	}

	// Slow baudrate to manage the data
	changeBaudrate(4800);
	getIfReady();

	// Request the list of emails
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[12])));	//POP3_LIST
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[13])));	//POP3_LIST_R
	answer = sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);
	if (answer == 1)
	{
		previous = millis();
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

			if (millis() < previous)
			{
				previous = millis();
			}

		}while (((buffer_3G[2] != 'K') && (buffer_3G[0] != 'O')) && ((millis() - previous) < 30000));

		// Restores the baudrate
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));	//CHANGE_BAUDRATE
		snprintf(buffer_3G, sizeof(buffer_3G), "%s%ld", str_aux1, _baudRate);
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

		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));	//POP3_OUT
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
		sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);

		return count;
	}

	// Restores the baudrate
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));	//CHANGE_BAUDRATE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%ld", str_aux1, _baudRate);
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));	//POP3_OUT
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);

	return -3;

}

/* getPOP3header(uint8_t) - Gets the header of the e-mail specified in index
 *
 * This function gets the header of the e-mail specified in index and returns it in 'buffer_3G'.
 *
 * Returns '1' on success, '-1' if error logging in the POP3 server
 * and '-2' if error getting the header of the e-mail
*/
int8_t Wasp3G::getPOP3header(uint8_t index){

	int8_t answer;
	unsigned long previous;
	int x;

	// Logs into the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[10])));	//POP3_IN
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	answer = sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);
	if ((answer == 0) || (answer == 2))
	{
		return -1;
	}

	// Slow baudrate to manage the data
	changeBaudrate(4800);
	getIfReady();

	// Request the header of the email
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[14])));	//POP3_HEADER
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, index);
	answer=sendCommand1(buffer_3G, "From:");
	if (answer == 1)
	{
		memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
		x=0;
    #if _3G_debug_mode>0
      PRINT_3G(F(""));
    #endif
		previous=millis();

		do{
			buffer_3G[x] = serialRead(_socket);
			if (buffer_3G[x] != -1)
			{
				#if _3G_debug_mode>0
					USB.print(char(buffer_3G[x]));
					x++;
				#endif
			}

			if (millis() < previous)
			{
				previous = millis();
			}

		}while (((buffer_3G[x-1] != 'K') && (buffer_3G[x-2] != 'O'))
					&& ((millis()-previous) < POP3_TIMEOUT)
					&& (x < _3G_BUFFER_SIZE));

		buffer_3G[x-4]='\0';

		// Restores the baudrate
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));	//CHANGE_BAUDRATE
		snprintf(str_aux2, sizeof(str_aux2), "%s%ld", str_aux1, _baudRate);
		answer = sendCommand2(str_aux2, OK_RESPONSE, ERROR);
		if (answer == 2)
		{
			return -3;
		}
		else if (answer == 1) // If the command is executed by the 3G module, changes the Wasmote baudrate
		{
			beginSerial(_baudRate, _socket);
		}
		getIfReady();


		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));	//POP3_OUT
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
		sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);

		return 1;
	}

	// Restores the baudrate
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));	//CHANGE_BAUDRATE
	snprintf(str_aux2, sizeof(str_aux2), "%s%ld", str_aux1, _baudRate);
	answer = sendCommand2(str_aux2, OK_RESPONSE, ERROR);
	if (answer == 2)
	{
		return -3;
	}
	else if (answer == 1) // If the command is executed by the 3G module, changes the Wasmote baudrate
	{
		beginSerial(_baudRate, _socket);
	}
	getIfReady();

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));	//POP3_OUT
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);

	return -2;

}

/* getPOP3mail(uint8_t) - Gets the e-mail specified in index
 *
 * This function gets the e-mail specified in index
 *
 * Returns '1' on success, '-1' if error logging in the POP3 server and '-2' getting the e-mail
*/
int8_t Wasp3G::getPOP3mail(uint8_t index){

	int8_t answer;
	unsigned long previous;
	int x;

	// Logs into the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[10])));	//POP3_IN
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	answer = sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);
	if ((answer == 0) || (answer == 2))
	{
		return -1;
	}

	// Request the email
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[15])));	//POP3_GET
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,1", str_aux1, index);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	answer = sendCommand2(buffer_3G, str_aux1, ERROR, POP3_TIMEOUT, SEND_ONCE);
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

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[x-1] != '\r')
					&& ((millis()-previous) < POP3_TIMEOUT)
					&& (x < _3G_BUFFER_SIZE));

		buffer_3G[x-1] = '\0';

		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));	//POP3_OUT
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
		sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);

		return 1;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));	//POP3_OUT
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);

	return -2;
}

/* deletePOP3mail(uint8_t) - Marks an e-mail to delete from POP3 server
 *
 * This function marks an e-mail to delete from POP3 server when logs out
 *
 * Returns '1' on success, '-1' if error logging in the POP3 server and '-2' if error deleting the e-mail
*/
int8_t Wasp3G::deletePOP3mail(uint8_t index){

	int8_t answer;

	// Logs into the server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[10])));	//POP3_IN
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	answer = sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);
	if ((answer == 0) || (answer == 2))
	{
		return -1;
	}

	// Request the header of the email
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[16])));	//POP3_DEL
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, index);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	answer = sendCommand2(buffer_3G, str_aux1, ERROR);
	if (answer == 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));	//POP3_OUT
		strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
		sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);
		return 1;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MAIL[11])));	//POP3_OUT
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MAIL[17])));	//POP3_SUCCESS
	sendCommand2(str_aux1, str_aux2, ERROR, POP3_TIMEOUT, SEND_ONCE);
	return -2;

}

#endif

//HTTP functions
#if HTTP_FUSE

/* readURL(const char*, uint16_t, uint16_t , const char*) - Sends a request to a HTTP url and get an answer
 *
 * This function sends a request to a HTTP url and get an answer. The answer is stored in 'buffer_3G'
 *
 * Returns '1' on success,
 * '0' if no connection,
 * '-1' if error setting APN, username and password,
 * '-2' if error opening a HTTP session,
 * '-3' if error receiving data or timeout waiting data,
 * '-4' if error changing the baudrate (data received is OK),
 * '-5' if unknown error for HTTP,
 * '-6' if HTTP task is busy,
 * '-7' if fail to resolve server address,
 * '-8' if HTTP timeout,
 * '-9' if fail to transfer data,
 * '-10' if memory error,
 * '-11' if invalid parameter,
 * '-12' if network error,
 * '-15' if error setting APN, username and password with CME_error code available
 * '-16' if error opening a HTTP session with CME_error code available
 * '-20' if error checking the connection
*/
int16_t Wasp3G::readURL(const char* url, uint16_t port, const char* HTTP_request){
	return readURL( url, port, HTTP_request, 0);
}

/* readURL(const char*, uint16_t, uint16_t , const char*, bool) - Sends a request to a HTTP url and get an answer
 *
 * This function sends a request to a HTTP url and get an answer. The answer is stored in 'buffer_3G'
 *
 * Returns '1' on success,
 * '0' if no connection
 * '-1' if error setting APN, username and password,
 * '-2' if error opening a HTTP session,
 * '-3' if error receiving data or timeout waiting data,
 * '-4' if error changing the baudrate (data received is OK),
 * '-5' if unknown error for HTTP,
 * '-6' if HTTP task is busy,
 * '-7' if fail to resolve server address,
 * '-8' if HTTP timeout,
 * '-9' if fail to transfer data,
 * '-10' if memory error,
 * '-11' if invalid parameter,
 * '-12' if network error,
 * '-15' if error setting APN, username and password with CME_error code available
 * '-16' if error opening a HTTP session with CME_error code available
 * '-20' if error checking the connection
*/
int16_t Wasp3G::readURL(const char* url, uint16_t port, const char* HTTP_request, bool parse){

	int16_t answer;

	// Checks the connection
	answer = check3Gconnection(90);
	if ((answer != 1) && (answer != -1))
	{
		return 0;
	}
	else if (answer == -1)
	{
		return -20;
	}

	// Configures the operator parameters
	answer = initHTTP();
	if (answer != 1)
	{
		return answer;
	}

	// Reduces the baudrate to allows manage all data from the 3G module
	changeBaudrate(2400);
	getIfReady();

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	delay(1000);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[0])));	//HTTP_ACT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%u", str_aux1, url, port);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[1])));	//HTTP_ACT_REQ
	answer = sendCommand2(buffer_3G, str_aux1, ERROR_CME, HTTP_TIMEOUT, SEND_ONCE);
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
	delay(1000);
	for (uint16_t x=0 ; x < strlen(HTTP_request);x++)
	{
		printByte(HTTP_request[x], _socket);
	}
	delay(1000);
	printByte(0x1A, _socket);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[2])));	//HTTP_ACT_DATA
	answer = waitForData(str_aux1, ERROR, HTTP_TIMEOUT, millis(), 0);
	if (answer != 1)
	{
		changeBaudrate(_baudRate);
		return -3;
	}

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);

	// Reads the response from the server ('0' header and answer, '1' only answer from Meshlium)
	return readHTTPresponse(parse);
}

/* setTimebyURL - Sets the time of Waspmote's RTC getting the time from an HTP server
 *
 * This function sets the time of Waspmote's RTC getting the time from an HTP server
 *
 * Returns '1' on success,
 * '0' if no connection
 * '-1' if error setting APN, username and password,
 * '-2' if error checking the connection
 * '-3' if error adding the HTP server
 * '-4' if error reading the time from 3G's RTC
 * '-5' HTP Unknown error
 * '-6' HTP Wrong parameter
 * '-7' HTP Wrong date and time calculated
 * '-8' HTP Network error
 * '-15' if error setting APN, username and password with CME_error code available
*/
int16_t Wasp3G::setTimebyURL(const char* htp_server, uint16_t htp_port){

	int16_t answer;
	char aux_str[20];
	uint8_t year, month, date, day_week, hour, minute, second;
	int8_t timezone;
	bool RTC_ant=false;

	uint16_t count=0;
	unsigned long previous;

	// Checks the connection
	answer = check3Gconnection(90);
	if ((answer != 1) && (answer != -1))
	{
		return 0;
	}
	else if (answer == -1)
	{
		return -2;
	}

	// Configures the operator parameters
	answer = initHTTP();
	if (answer != 1)
	{
		return answer - 4;
	}


	// ADD the HTP server
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[18])));	//"+CHTPSERV="
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"ADD\",\"%s\",%u,1", str_aux1, htp_server, htp_port);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
	if (answer != 1)
	{
		return -3;
	}

	// Updating date and time using HTP protocol
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[19])));	//"+CHTPUPDATE"
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_HTTP[20])));	//"+CHTPUPDATE: "
	answer=sendCommand2(str_aux1, str_aux2, ERROR);
	if (answer != 1)
	{
		return answer;
	}
	delay(100);
	answer = serialRead(_socket) - 0x30;
	if (answer != 0)
	{
		#if _3G_debug_mode>0
			PRINT_3G(F("Error HTP: "));
			USB.println(answer, DEC);
		#endif
		return answer;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[63])));	//"+CCLK?"
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[64])));	//"+CCLK:"
	answer=sendCommand2(str_aux1, str_aux2, ERROR);
	if (answer != 1)
	{
		return -4;
	}

		count = 0;
	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	previous = millis();
	do{
		while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000))
		{
			if (millis() < previous)
			{
				previous = millis();
			}
		}
		buffer_3G[count]=serialRead(_socket);
		count++;

		if (millis() < previous)
		{
			previous = millis();
		}

	}while ((buffer_3G[count-1] != '\r') && ((millis() - previous) < 5000) && (count < _3G_BUFFER_SIZE));

	year = ((buffer_3G[1] - 0x30) * 10) + (buffer_3G[2] - 0x30);
	month = ((buffer_3G[4] - 0x30) * 10) + (buffer_3G[5] - 0x30);
	date = ((buffer_3G[7] - 0x30) * 10) + (buffer_3G[8] - 0x30);
	hour = ((buffer_3G[10] - 0x30) * 10) + (buffer_3G[11] - 0x30);
	minute = ((buffer_3G[13] - 0x30) * 10) + (buffer_3G[14] - 0x30);
	second = ((buffer_3G[16] - 0x30) * 10) + (buffer_3G[17] - 0x30);
	timezone = (((buffer_3G[19] - 0x30) * 10) + (buffer_3G[20] - 0x30)) / 4;
	if(buffer_3G[18] == '-')
	{
		timezone *= -1;
 	}

	#if _3G_debug_mode>0
		PRINT_3G(F("year "));
		USB.print(year, DEC);
		USB.print(F("; month "));
		USB.print(month, DEC);
		USB.print(F("; date "));
		USB.println(date, DEC);
		PRINT_3G(F("hour "));
		USB.print(hour, DEC);
		USB.print(F("; minute "));
		USB.print(minute, DEC);
		USB.print(F("; second "));
		USB.print(second, DEC);
		USB.print(F("; timezone "));
		USB.println((timezone), DEC);
	#endif

	if (timezone >= 0)
	{
		if(hour >= timezone)
		{
			hour = hour - timezone;
		}
		else
		{
			hour = hour - timezone + 24;
		}
	}
	else
	{
		if((hour - timezone) > 23)
		{
			hour = hour - timezone - 24;
		}
		else
		{
			hour = hour - timezone;
		}

	}

	if (RTC.isON == 0) // Checks if the RTC is on
	{
		RTC_ant = true;
		RTC.ON();
	}

	// Stes the RTC time
	RTC.setTime(year, month, date, RTC.dow(year, month, date), hour, minute, second); //Gets time from RTC

	if (RTC_ant == 1) // Powers off the RTC if before it was off
	{
		RTC.OFF();
	}

	return 1;


}

/* setTimebyMeshlium - Sets the time of Waspmote's RTC getting the time from Meshlium
 *
 * This function sets the time of Waspmote's RTC getting the time from Meshlium
 *
 * Returns '1' on success,
 * '0' if no connection
 * '-1' if error setting APN, username and password,
 * '-2' if error opening a HTTP session,
 * '-3' if error receiving data or timeout waiting data,
 * '-4' if error changing the baudrate (data received is OK),
 * '-5' if unknown error for HTTP,
 * '-6' if HTTP task is busy,
 * '-7' if fail to resolve server address,
 * '-8' if HTTP timeout,
 * '-9' if fail to transfer data,
 * '-10' if memory error,
 * '-11' if invalid parameter,
 * '-12' if network error,
 * '-15' if error setting APN, username and password with CME_error code available
 * '-16' if error opening a HTTP session with CME_error code available
 * '-17' if url response its not OK  (HTTP code 200)
 * '-18' if content-length field not found
 * '-19' if data field not found
 * '-20' if error checking the connection
*/
int16_t Wasp3G::setTimebyMeshlium(const char* url, uint16_t port){
	int16_t answer;
	char frame_data[50];
	char MID[17];
	uint8_t year, month, date, day_week, hour, minute, second;
	bool RTC_ant=false;
	char time_zone[6];

	memset(frame_data, '\0', sizeof(frame_data));
	memset(MID, '\0', sizeof(MID));

	// read mote ID from EEPROM memory
	for(int i=0 ; i<16 ; i++ )
	{
		MID[i]=Utils.readEEPROM(i+EEPROM_FRAME_MOTEID);
	}
	MID[16]='\0';

	// Generates a frame
	snprintf(frame_data,
				sizeof(frame_data),
				"<=>%c0#%02x%02x%02x%02x#%s#0#",
				155,
				_serial_id[4],
				_serial_id[5],
				_serial_id[6],
				_serial_id[7],
				MID);

	answer = sendHTTPframe( url, port, (uint8_t*) frame_data, strlen(frame_data), GET, 1);
	// gets URL from the solicited URL
	if ( answer == 1)
	{
		year = ((buffer_3G[2] - 0x30) * 10) + (buffer_3G[3] - 0x30);
		month = ((buffer_3G[4] - 0x30) * 10) + (buffer_3G[5] - 0x30);
		date = ((buffer_3G[6] - 0x30) * 10) + (buffer_3G[7] - 0x30);
		hour = ((buffer_3G[8] - 0x30) * 10) + (buffer_3G[9] - 0x30);
		minute = ((buffer_3G[10] - 0x30) * 10) + (buffer_3G[11] - 0x30);
		second = ((buffer_3G[12] - 0x30) * 10) + (buffer_3G[13] - 0x30);
		memset(time_zone, '\0', sizeof(time_zone));
		strncpy(time_zone, buffer_3G+14,5);

		#if _3G_debug_mode>0
			PRINT_3G(F("year "));
			USB.print(year, DEC);
			USB.print(F("; month "));
			USB.print(month, DEC);
			USB.print(F("; date "));
			USB.println(date, DEC);
			PRINT_3G(F("hour "));
			USB.print(hour, DEC);
			USB.print(F("; minute "));
			USB.print(minute, DEC);
			USB.print(F("; second "));
			USB.print(second, DEC);
			USB.print(F("; time zone "));
			USB.println(time_zone);
		#endif

		if (RTC.isON == 0) // Checks if the RTC is on
		{
			RTC_ant = true;
			RTC.ON();
		}

		// Sets the RTC time
		RTC.setTime(year, month, date, RTC.dow(year, month, date), hour, minute, second); //Gets time from RTC

		if (RTC_ant == 1) // Powers off the RTC if before it was off
		{
			RTC.OFF();
		}

		// Sets the RTC of the 3G too
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[4])));	//SET_TIME
		snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%02u/%02u/%02u,%02u:%02u:%02u+00\"", str_aux1, RTC.year, RTC.month, RTC.date, RTC.hour, RTC.minute, RTC.second);
		answer = sendCommand2( buffer_3G, OK_RESPONSE, ERROR);

		memset(buffer_3G, '\0', sizeof(buffer_3G));
		strncpy(buffer_3G, time_zone, 5);

		if (answer == 2)
		{
			return -21;
		}

		return 1;
	}

	return answer;


}

/* sendHTTPframe(const char*, uint16_t, uint16_t , const char*) - Sends a frame to Meshlium
 *
 * This function sends a frame to Meshlium and get an answer. The answer is stored in 'buffer_3G'
 *
 * Returns '1' on success,
 * '0' if no connection
 * '-1' if error setting APN, username and password,
 * '-2' if error opening a HTTP session,
 * '-3' if error receiving data or timeout waiting data,
 * '-4' if error changing the baudrate (data received is OK),
 * '-5' if unknown error for HTTP,
 * '-6' if HTTP task is busy,
 * '-7' if fail to resolve server address,
 * '-8' if HTTP timeout,
 * '-9' if fail to transfer data,
 * '-10' if memory error,
 * '-11' if invalid parameter,
 * '-12' if network error,
 * '-15' if error setting APN, username and password with CME_error code available
 * '-16' if error opening a HTTP session with CME_error code available
 * '-17' if url response its not OK  (HTTP code 200)
 * '-18' if content-length field not found
 * '-19' if data field not found
 * '-20' if error checking the connection
*/
int16_t Wasp3G::sendHTTPframe(const char* url, uint16_t port, uint8_t* data, int length, uint8_t method){
	return sendHTTPframe( url, port, data, length, method, 0);
}

/* sendHTTPframe(const char*, uint16_t, uint16_t , const char*) - Sends a frame to Meshlium
 *
 * This function sends a frame to Meshlium and get an answer. The answer is stored in 'buffer_3G'
 *
 * Returns '1' on success,
 * '0' if no connection
 * '-1' if error setting APN, username and password,
 * '-2' if error opening a HTTP session,
 * '-3' if error receiving data or timeout waiting data,
 * '-4' if error changing the baudrate (data received is OK),
 * '-5' if unknown error for HTTP,
 * '-6' if HTTP task is busy,
 * '-7' if fail to resolve server address,
 * '-8' if HTTP timeout,
 * '-9' if fail to transfer data,
 * '-10' if memory error,
 * '-11' if invalid parameter,
 * '-12' if network error,
 * '-15' if error setting APN, username and password with CME_error code available
 * '-16' if error opening a HTTP session with CME_error code available
 * '-17' if url response its not OK  (HTTP code 200)
 * '-18' if content-length field not found
 * '-19' if data field not found
 * '-20' if error checking the connection
*/
int16_t Wasp3G::sendHTTPframe(const char* url, uint16_t port, uint8_t* data, int length, uint8_t method, uint8_t parse){

	int16_t answer;

	// Checks the connection
	answer = check3Gconnection(90);
	if ((answer != 1) && (answer != -1))
	{
		return 0;
	}
	else if (answer == -1)
	{
		return -20;
	}

	// Configures the operator parameters
	answer = initHTTP();
	if (answer != 1)
	{
		return answer;
	}

	// Reduces the baudrate to allows manage all data from the 3G module
	changeBaudrate(2400);
	getIfReady();

	delay(1000);

	// Sends the HTTP request to the server
	answer = sendHTTPrequest(url, port, data, length, method);
	if (answer != 1)
	{
		changeBaudrate(_baudRate);
		return answer;
	}

	// Reads the response from the server ('0' header and answer, '1' only answer from Meshlium)
	return readHTTPresponse(parse);
}

/* readURLS(const char*, uint16_t, uint16_t , const char*) - Sends a request to a HTTPS url and get an answer
 *
 * This function sends a request to a HTTPS url and get an answer. The answer is stored in 'buffer_3G'
 *
 * Returns '1' on success,
 * '-1' if unknown error,
 * '-2' if 3G module is busy,
 * '-3' if server closed,
 * '-4' if timeout,
 * '-5' if transfer failed,
 * '-6' if memory error,
 * '-7' if invalid parameter,
 * '-8' if network error,
 * '-10' if error setting APN, username and password
 * '-11' if error acquiring HTTPS protocol stack,
 * '-12' if error opening a HTTPS session,
 * '-13' if error changing baudrate,
 * '-14' if error storing HTTPS request in the output buffer,
 * '-15' if error sending the HTTPS request to the url,
 * '-16' if error with the receive command,
 * '-17' if error closing the session (data received is OK),
 * '-18' if error releasing the SSL stack (data received is OK),
 * '-19' if error changing the baudrate (data received is OK),
 * '-20' if error receiving data or timeout waiting data
 * '-25' if error setting username and password with CME_error code available
 * '-31' HTTPS error code: unknown error
 * '-32' HTTPS error code: busy
 * '-33' HTTPS error code: server closed
 * '-34' HTTPS error code: timeout
 * '-35' HTTPS error code: transfer failed
 * '-36' HTTPS error code: memory error
 * '-37' HTTPS error code: invalid parameter
 * '-38' HTTPS error code: network error
*/
int8_t Wasp3G::readURLS(const char* url, uint16_t port, const char* HTTPS_request){

	int8_t answer;
	int HTTPS_data, count;
	char command[15], aux;
	unsigned long previous;

	// Sets APN
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));	//_3G_CON
	snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"IP\",\"%s\"", str_aux1, _apn);
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
	if (strlen(_apn_login) == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
	}
	else
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"%s\",\"%s\"", str_aux1, _apn_password, _apn_login);
	}
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
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

	// Release other SSL stacks and close session
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));	//HTTPS_CLOSE
	sendCommand2(str_aux1, OK_RESPONSE, ERROR);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));	//HTTPS_STOP
	sendCommand2(str_aux1, OK_RESPONSE, ERROR);

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[3])));	//HTTPS_START
	answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR, HTTP_CONF_TIMEOUT, SEND_ONCE);
	if (answer != 1)
	{
		return -11;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[5])));	// HTTPS_OPEN
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=\"%s\",%u", str_aux1, url, port);
	answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR, HTTP_TIMEOUT, SEND_ONCE);
	if (answer != 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));	// HTTPS_STOP
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		return -12;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[7])));	//HTTPS_SEND
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=%d", str_aux1, strlen(HTTPS_request));
	answer = sendCommand2(buffer_3G, "\r\n>", ERROR, HTTP_CONF_TIMEOUT,  SEND_ONCE);
	if (answer != 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));	// HTTPS_CLOSE
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));	// HTTPS_STOP
		sendCommand2(str_aux1, OK_RESPONSE, ERROR);
		return -14;
	}

	//printString(HTTPS_request,_socket);
	for (uint16_t x=0 ; x < strlen(HTTPS_request);x++)
	{
		//printHex(HTTP_request[x], _socket);
		printByte(HTTPS_request[x], _socket);
	}
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

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);

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
			PRINT_3G(F("HTTPS data: "));
			USB.println(HTTPS_data, DEC);
		#endif

		do{
			aux = serialRead(_socket);
			if (aux != -1)
			{
				if (count < _3G_BUFFER_SIZE)
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

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((HTTPS_data > 0) && ((millis() - previous) < 20000));

		#if _3G_debug_mode>0
			PRINT_3G(F("Count remainder: "));
			USB.println(HTTPS_data, DEC);
		#endif

		// Waits for new data or the end of the request
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[9])));	//HTTPS_DATA
		answer = waitForData(str_aux1, ERROR, HTTP_TIMEOUT, millis(), 0);
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
		buffer_3G[count] = '\0';

		// Closes connection and release the SSL stack
		delay(1000);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));	//HTTPS_CLOSE
		answer = sendCommand2(str_aux1, OK_RESPONSE, ERROR, HTTP_TIMEOUT,  SEND_ONCE);
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
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));	//CHANGE_BAUDRATE
		snprintf(command, sizeof(command), "%s%ld", str_aux1, _baudRate);
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
			PRINT_3G(F("HTTPS error: "));
			USB.println(HTTPS_data, DEC);
		#endif

		// Closes connection, release the SSL stack and changes the baudrate
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[6])));	//HTTPS_CLOSE
		sendCommand2(str_aux1, OK_RESPONSE, ERROR, HTTP_CONF_TIMEOUT,  SEND_ONCE);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_HTTP[4])));	//HTTPS_STOP
		sendCommand2(str_aux1, OK_RESPONSE, ERROR, HTTP_CONF_TIMEOUT,  SEND_ONCE);
		changeBaudrate(_baudRate);

		return -HTTPS_data - 30;
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
 * Returns '1' if success,
 * '0' if error,
 * '-2' if error setting the apn,
 * '-3' if error setting GPS server and port,
 * '-4' if error starting the GPS,
 * '-5' if AGPS data are not available
*/
int8_t Wasp3G::startGPS(int8_t mode, const char* GPS_url, const char* GPS_port){

	int8_t answer;
	uint8_t count=0;

	if (mode == 1)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[0])));		//START_GPS
		snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, mode);
	}
	else
	{
		// Sets APN
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));	//_3G_CON
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"IP\",\"%s\"", str_aux1, _apn);
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
		if (strlen(_apn_login) == 0)
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
			snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
		}
		else
		{
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
			snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"%s\",\"%s\"", str_aux1, _apn_password, _apn_login);
		}
		count = 5;
		do{
			answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
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

		// Sets the GPS server and port:
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[4])));		//GPS_SERVER
		snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s:%s\"", str_aux1, GPS_url, GPS_port);
		count=10;
		do{
			answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
			count--;
		}while ((answer != 1) && (count  > 0));
		if (count == 0)
		{
			return -3;
		}

		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[0])));		//START_GPS
		snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, mode);
	}

	// Starts the GPS:
	answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR, 45000, SEND_ONCE);

	if (answer != 1)
	{
			return -4;
	}

	// If GPS mode is assisted GPS, waits for string of GPS data:
	if (mode == 3)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[5])));		//A_GPS_INFO
		if (waitForData(str_aux1, 60000, millis(), 0) == 1) 	//If there are data, stores it in 'buffer_3G'
		{
			count=0;
			do{
				buffer_3G[count]=serialRead(_socket);
				count++;
			}while ((serialAvailable(_socket) != 0) && (count < _3G_BUFFER_SIZE));
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[1])));		//START_GPS_COLD
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[2])));		//START_GPS_HOT
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[3])));		//STOP_GPS
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
	uint8_t count=0;
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
	count = 0;
	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	previous = millis();
	do{
		while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000))
		{
			if (millis() < previous)
			{
				previous = millis();
			}
		}
		buffer_3G[count]=serialRead(_socket);
		count++;

		if (millis() < previous)
		{
			previous = millis();
		}

	}while ((buffer_3G[count-1] != '\r') && ((millis() - previous) < 5000) && (count < _3G_BUFFER_SIZE));
	buffer_3G[count] = '\0';

	#if _3G_debug_mode>0
		PRINT_3G(F("GPS raw data: "));
		USB.println(buffer_3G);
	#endif

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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[8])));		//ENABLE_AUTO_GPS
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_GPS[9])));		//DISABLE_AUTO_GPS
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

/*setTimebyGPS(unsigned long , bool ) - Sets the time of Waspmote's RTC getting the time from GPS
 *
 * This function sets the time of Waspmote's RTC getting the time from GPS
 *
 * Returns '1' if success,
 * '-1' if error starting the GPS module
 * '-2' if timeout waiting for GPS data
 * '-3' if error setting the RTC time of the 3G module
*/
int8_t Wasp3G::setTimebyGPS(unsigned long waiting_time, bool state){

	int8_t answer;
	unsigned long previous;
	uint8_t year, month, day, day_week, hour, minute, second;
	bool RTC_ant=false;

	// If state is '1', the GPS is started. '0' if not
	if (state == 0)
	{
		answer = startGPS();

		if (answer != 1)
		{
			// error starting the GPS module
			return -1;
		}
	}

	previous = millis();

	do{
		answer = getGPSinfo();

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous)
		{
			previous = millis();
		}

	}while(((millis() - previous) < (waiting_time * 1000)) && (answer != 1));

	//Stops the GPS module
	if (state == 0)
	{
		stopGPS();
	}

	if ((millis() - previous) > waiting_time * 1000)
	{
		//Timeout waiting for GPS data
		return -2;
	}

	#if _3G_debug_mode>0
		PRINT_3G(F("Date: "));
		USB.println(date);
		PRINT_3G(F("UTC_time: "));
		USB.println(UTC_time);
	#endif

	day = ((date[0] - 0x30) * 10) + (date[1] - 0x30);
	month = ((date[2] - 0x30) * 10) + (date[3] - 0x30);
	year = ((date[4] - 0x30) * 10) + (date[5] - 0x30);
	hour = ((UTC_time[0] - 0x30) * 10) + (UTC_time[1] - 0x30);
	minute = ((UTC_time[2] - 0x30) * 10) + (UTC_time[3] - 0x30);
	second = ((UTC_time[4] - 0x30) * 10) + (UTC_time[5] - 0x30);

	#if _3G_debug_mode>0
		PRINT_3G(F("year "));
		USB.print(year, DEC);
		USB.print(F("; month "));
		USB.print(month, DEC);
		USB.print(F("; day "));
		USB.println(day, DEC);
		PRINT_3G(F("hour "));
		USB.print(hour, DEC);
		USB.print(F("; minute "));
		USB.print(minute, DEC);
		USB.print(F("; second "));
		USB.println(second, DEC);
	#endif

	if (RTC.isON == 0) // Checks if the RTC is on
	{
		RTC_ant = true;
		RTC.ON();
	}

	// Stes the RTC time
	RTC.setTime(year, month, day, RTC.dow(year, month, day), hour, minute, second); //Gets time from RTC

	if (RTC_ant == 1) // Powers off the RTC if before it was off
	{
		RTC.OFF();
	}

	// Sets the RTC of the 3G too
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[4])));	//SET_TIME
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%02u/%02u/%02u,%02u:%02u:%02u+00\"", str_aux1, RTC.year, RTC.month, RTC.date, RTC.hour, RTC.minute, RTC.second);
	answer = sendCommand2( buffer_3G, OK_RESPONSE, ERROR);

	if (answer != 1)
	{
		//Error setting the RTC time of the 3G module
		return -3;
	}

	return 1;

}
#endif

//TCP/UDP functions
#if IP_FUSE

/* configureTCP_UDP(int8_t) - Configures 3G connection with login, password and some other parameters to use TCP or UDP connections
 *
 * This function creates a 3G connection with the carrier server to get access to the internet
 *
 * Returns '1' on success,
 * '-2' if error dettaching the connection,
 * '-10' if error dettaching the connection with CME code available,
 * '-3' if error attaching the connection,
 * '-11' if error attaching the connection with CME code available,
 * '-4' if waiting time for connection have expired,
 * '-5' if error setting the APN,
 * '-6' if error setting the user name and the password,
 * '-12' if error setting the user name and the password with CME code available,
 * and '-7' if error configurating IP parameters
*/
int8_t Wasp3G::configureTCP_UDP(){

	unsigned long previous = millis();
	uint8_t answer=0;
	uint8_t count;

	// First restart TCP/UDP connection:
	count = 5;

	if (check3Gattach() == 1)
	{
		// Dettachs 3G:
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[9])));	//AT_3G_ATT_OFF
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
	count = 5;
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[8])));	//AT_3G_ATT_ON
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
	while ((check3Gattach() != 1) && ((millis()-previous) < 30000))
	{
		if (millis() < previous)
		{
			previous = millis();
		}
	}

	if (millis()-previous > 30000)
	{
		return -4;
	}

	// Sets APN:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[10])));	//_3G_CON
	snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"IP\",\"%s\"", str_aux1, _apn);
	count = 5;
	do{
		answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (count == 0)
	{
		return -5;
	}

	// Sets username and password
	if (strlen(_apn_login) == 0)
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
	}
	else
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[11])));	//_3G_AUTH
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1,\"%s\",\"%s\"", str_aux1, _apn_password, _apn_login);
	}
	count = 5;
	do{
		answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_CME);
		count--;
	}while ((answer != 1) && (count  > 0));
	if (answer == 0)
	{
		return -2;
	}
	else if (answer == 2)
	{
		return -0;
	}

	#if _3G_debug_mode>0
		PRINT_3G(F("IP Flag: "));
		USB.println(IP_flags,BIN);
	#endif

	// Configures answers and retries
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[18])));		//CONFIGURE_IP
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,%d,1,0,1", str_aux1, RETRIES, DELAY_SEND);
	//snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,%d,1,1,1", str_aux1, RETRIES, DELAY_SEND);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);

	if ((answer == 0) || (answer == 2))
	{
		return -7;
	}

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[2])));	//IP_APP_MODE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
	answer=sendCommand2(buffer_3G, OK_RESPONSE, ERROR);

	if ((answer == 0) || (answer == 2))
	{
		return -8;
	}

	IP_flags &= 0xFE;

	#if _3G_debug_mode>0
		PRINT_3G(F("IP Flag: "));
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[1])));	//IP_CLOSE
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[0])));	//IP_OPEN
	switch (mode)
	{
		// TCP client, single connection mode
		case 0:
			snprintf(buffer_3G, sizeof(buffer_3G), "%s\"TCP\",0,0", str_aux1);
			break;

		// UDP client, single connection mode
		case 1:
			snprintf(buffer_3G, sizeof(buffer_3G), "%s\"UDP\",0,0", str_aux1);
			break;

		// TCP server
		case 2:
			snprintf(buffer_3G, sizeof(buffer_3G), "%s\"TCP\",%u", str_aux1, port);
			break;

		// Multiple connection mode
		case 3:
			snprintf(buffer_3G, sizeof(buffer_3G), "%s,,1", str_aux1);
			break;
	}

	count = 3;
	do{
		answer = sendCommand3(buffer_3G, OK_RESPONSE, ERROR_CME, ERROR_IP, IP_TIMEOUT, SEND_ONCE);
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
		PRINT_3G(F("Flag 2: "));
		USB.println(IP_flags,BIN);
	#endif

	switch (mode)
	{
		// TCP client, single connection mode
		case 0:
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[5])));	//TCP_CONNECT
			snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\",%u", str_aux1, ip, port);

			if ((IP_flags & 0x01) == 0)
			{
				count=10;
				do{
					answer=sendCommand3(buffer_3G, "Connect ok", ERROR_CME, ERROR_IP, IP_TIMEOUT, SEND_ONCE);
					count--;
				}while ((count != 0) && (answer != 1));
			}
			else
			{
				count=10;
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[21])));	//IPDATAMODE
				do{
					answer=sendCommand3(buffer_3G, str_aux1, ERROR_CME, ERROR_IP, IP_TIMEOUT, SEND_ONCE);
					count--;
				}while ((count != 0) && (answer != 1));
			}
			break;

		// Start up the TCP server
		case 2:
			count=10;
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[8])));	//IP_SERVER
			do{
				answer=sendCommand3(str_aux1, OK_RESPONSE, ERROR_IP, ERROR, IP_TIMEOUT, SEND_ONCE);
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


	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[9])));	//MULTI_OPEN
	if (serverIP[0] == '\0')
	{
		// UDP connections
		snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,\"UDP\",,,%u", str_aux1, n_link,server_port);
	}
	else
	{
		// TCP connections
		snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,\"TCP\",\"%s\",%u", str_aux1, n_link, serverIP, server_port);
	}

	count = 3;
	do{
		answer = sendCommand3(buffer_3G, OK_RESPONSE, ERROR_CME, ERROR_IP, 10000, SEND_DEFAULT);
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
	int16_t counter;

	if (IP_flags & 0x02)
	{
		// Multiple connection mode
		if (port == 0)
		{
			// TCP link
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[10])));		//MULTI_SEND
			snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,%d", str_aux1, n_link, length);
			answer = sendCommand3(buffer_3G, "\r\n>", ERROR_CME, ERROR_IP, 20000, SEND_DEFAULT);
			if (answer == 1)
			{
				#if _3G_debug_mode>1
					PRINT_3G(F("Sending data (multiple connection - TCP)...\n"));
          PRINT_3G(F(""));
				#endif
				for (counter = 0; counter < length; counter++)
				{
					printByte(data[counter],_socket);
					#if _3G_debug_mode>1
						USB.print(data[counter], HEX);
						USB.print(" ");
					#endif
				}
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[12])));		//TCP_SEND_OK
				answer = waitForData(str_aux1, DEFAULT_TIMEOUT, millis(), 0);
				#if _3G_debug_mode>0
					PRINT_3G(F("Answer for send: "));
					USB.println(answer, DEC);
				#endif
			}
		}
		else
		{
			// UDP link
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[10])));		//MULTI_SEND
			snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,%d,\"%s\",%u", str_aux1, n_link, length, ip, port);
			answer = sendCommand3(buffer_3G, "\r\n>", ERROR_CME, ERROR_IP, 20000, SEND_DEFAULT);
			if (answer == 1)
			{
				#if _3G_debug_mode>1
					PRINT_3G(F("Sending data (multiple connection - UDP)...\n"));
          PRINT_3G(F(""));
				#endif

				for (counter = 0; counter < length; counter++)
				{
					printByte(data[counter],_socket);
					#if _3G_debug_mode>1
						USB.print(data[counter], HEX);
						USB.print(" ");
					#endif
				}
        USB.println();
				answer = waitForData(OK_RESPONSE, DEFAULT_TIMEOUT, millis(), 0);
				#if _3G_debug_mode>0
					PRINT_3G(F("Answer for send: "));
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
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[6])));		//TCP_SEND
			snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, length);
			answer = sendCommand2(buffer_3G, "\r\n>", ERROR_IP);
			if (answer == 1)
			{
				#if _3G_debug_mode>1
					PRINT_3G(F("Sending data (single connection - TCP)...\n"));
          PRINT_3G(F(""));
				#endif

				for (counter = 0; counter < length; counter++)
				{
					printByte(data[counter],_socket);
					#if _3G_debug_mode>1
						USB.print(data[counter], HEX);
						USB.print(" ");
					#endif
				}
        USB.println();
				strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[12])));		//TCP_SEND_OK
				answer = waitForData(str_aux1, DEFAULT_TIMEOUT, millis(), 0);
				#if _3G_debug_mode>0
					PRINT_3G(F("Answer for send: "));
					USB.println(answer, DEC);
				#endif
			}
		}
		else
		{
			// UDP link
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[7])));		//UDP_SEND
			snprintf(buffer_3G, sizeof(buffer_3G), "%s%d,\"%s\",%u", str_aux1, length, ip, port);
			answer = sendCommand2(buffer_3G, "\r\n>", ERROR_IP);
			if (answer == 1)
			{
				#if _3G_debug_mode>1
					PRINT_3G(F("Sending data (single connection - UDP)...\n"));
          PRINT_3G(F(""));
				#endif

				for (counter = 0; counter < length; counter++)
				{
					printByte(data[counter],_socket);
					#if _3G_debug_mode>1
						USB.print(data[counter], HEX);
						USB.print(" ");
					#endif
				}
        USB.println();
				answer = waitForData(OK_RESPONSE, DEFAULT_TIMEOUT, millis(), 0);
				#if _3G_debug_mode>0
					PRINT_3G(F("Answer for send: "));
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[11])));		//MULTI_CLOSE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, n_link);
	answer=sendCommand3(buffer_3G, OK_RESPONSE, ERROR_CME, ERROR_IP, 10000, SEND_DEFAULT);

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

	uint16_t i;
	uint16_t data_length = 0;
	int8_t answer;
	unsigned long previous;


	#if _3G_debug_mode>0
		PRINT_3G(F("Inside readIPdata\n"));
	#endif

	memset(IP_dir, '\0', sizeof(IP_dir));

	//Reads the IP address of the incoming connection
	answer = 0;
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

		IP_dir[i] = serialRead(_socket);
		i++;

		// Condition to avoid an overflow (DO NOT REMOVE)
		if( millis() < previous) previous = millis();

	}while ((IP_dir[i-1] != 0x0D) && ((millis() - previous) < 1000) && (i < sizeof(IP_dir)));

	IP_dir[i-1] = '\0';

	if ((millis() - previous) > 1000)
	{
		return 0;
	}

	#if _3G_debug_mode>0
		PRINT_3G(F("Data from: "));
		USB.println(IP_dir);
	#endif


	// Checks if there is the data length header:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[25])));		//IP_DATA_SINGLE
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[26])));		//IP_DATA_MULTI
	answer = waitForData(str_aux1, str_aux2, 2000, millis(), 0);
	if (answer == 1)
	{
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

			str_aux1[i] = serialRead(_socket);
			i++;

			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();

		}while ((str_aux1[i-1] != 0x0D) && ((millis() - previous) < 1000) && (i < sizeof(str_aux1)));
		str_aux1[i-1] = '\0';
		data_length = atoi(str_aux1);

		#if _3G_debug_mode>0
			PRINT_3G(F("Data length: "));
			USB.println(data_length, DEC);
		#endif
	}
	else if (answer == 2)
	{

		n_connection = serialRead(_socket);
		#if _3G_debug_mode>0
			PRINT_3G(F("No of connection: "));
			USB.println(char(n_connection));
		#endif

		serialRead(_socket); //Skips ','

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

			str_aux1[i] = serialRead(_socket);
			i++;

			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();

		}while ((str_aux1[i-1] != 0x0D) && ((millis() - previous) < 1000) && (i > sizeof(str_aux1)));
		str_aux1[i-1] = '\0';
		data_length = atoi(str_aux1);

		#if _3G_debug_mode>0
			PRINT_3G(F("Data length: "));
			USB.println(data_length, DEC);
		#endif

	}
	else
	{
		#if _3G_debug_mode>0
			PRINT_3G(F("No data length header!!\n"));
		#endif
		return -2;
	}

	// Gets the data and stores in buffer_3G:
	serialRead(_socket); //Skips '\n'

	if (data_length != 0)
	{
		memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
		i = 0;
		while ((data_length > i) && ((millis() - previous) < 30000) && (i < _3G_BUFFER_SIZE)){
			while((serialAvailable(_socket) == 0) && ((millis() - previous) < 30000))
			{
				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous)
				{
					previous = millis();
				}

				delay(10);
			}

			buffer_3G[i] = serialRead(_socket);
			i++;

			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous) previous = millis();

		}

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[14])));		//SERVER_LIST
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[15])));		//SERVER_LIST_R
	answer = sendCommand2(str_aux1, str_aux2, ERROR_IP);

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);

	if (answer == 2)
	{
		return -2;
	}
	else if (answer == 1)
	{
		previous = millis();
		counter=0;
		answer=1;
		do{
			previous = millis();
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000)){

				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[counter] = serialRead(_socket);
			counter++;
			if (buffer_3G[counter-1] == '\n')
			{
				answer = waitForData(str_aux2, OK_RESPONSE, DEFAULT_TIMEOUT, millis(), 0);
			}

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((answer == 1) && ((millis()-previous) < 3000) && (counter < _3G_BUFFER_SIZE));
		buffer_3G[counter] = '\0';
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[16])));		//SERVER_OPEN_CLIENT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%u", str_aux1, n_client);
	answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR_IP);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[17])));		//SERVER_CLOSE_CLIENT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%u", str_aux1, n_client);
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[3])));		//GET_IP
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_IP[4])));		//GET_IP_R
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
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[counter] = serialRead(_socket);
			counter++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[counter-1] != '\r') && ((millis()-previous) < 3000) && (counter < _3G_BUFFER_SIZE));
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

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[20])));		//DOMFROMIP
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=\"%s\"", str_aux1, ip);
	answer = sendCommand2(buffer_3G, str_aux1, ERROR);

	if (answer == 1)
	{
		serialRead(_socket);
		serialRead(_socket);

		if (serialRead(_socket) == '1')
		{
			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
				{
					if (millis() < previous)
					{
						previous = millis();
					}
				}

				if (millis() < previous)
				{
					previous = millis();
				}
			}while ((serialRead(_socket) != '"') && ((millis() - previous) < 1000));

			previous = millis();
			counter = 0;
			do{
				previous = millis();
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
				{
					if (millis() < previous)
					{
						previous = millis();
					}
				}
				buffer_3G[counter] = serialRead(_socket);
				counter++;

				if (millis() < previous)
				{
					previous = millis();
				}

			}while ((buffer_3G[counter-1] != '"') && ((millis() - previous) < 1000) && (counter < _3G_BUFFER_SIZE));
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

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_IP[19])));		//IPFROMDOM
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=\"%s\"", str_aux1, domain);
	answer=sendCommand2(buffer_3G, str_aux1, ERROR);

	if (answer == 1)
	{
		serialRead(_socket);
		serialRead(_socket);

		if (serialRead(_socket) == '1')
		{
			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
				{
					if (millis() < previous)
					{
						previous = millis();
					}
				}

				if (millis() < previous)
				{
					previous = millis();
				}

			}while ((serialRead(_socket) != '"') && ((millis() - previous) < 1000));

			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
				{
					if (millis() < previous)
					{
						previous = millis();
					}
				}

				if (millis() < previous)
				{
					previous = millis();
				}

			}while ((serialRead(_socket) != '"') && ((millis() - previous) < 1000));


			previous = millis();
			do{
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
				{
					if (millis() < previous)
					{
						previous = millis();
					}
				}

				if (millis() < previous)
				{
					previous = millis();
				}

			}while ((serialRead(_socket) != '"') && ((millis() - previous) < 1000));

			previous = millis();
			counter = 0;
			do{
				previous = millis();
				while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 1000))
				{
					if (millis() < previous)
					{
						previous = millis();
					}
				}
				buffer_3G[counter] = serialRead(_socket);
				counter++;

				if (millis() < previous)
				{
					previous = millis();
				}

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

#endif

//XMODEM functions
/* getXmodemFile(const char* , const char*) - Gets a file from 3G+GPS Board and stores it in Waspmote
 *
 * This function gets a file from 3G+GPS Board and stores it in Waspmote with Xmodem protocol
 *
 * Returns: '1' if succes,
 * '0' if error,
 * '-2' if error going to root directory in Waspmote's SD,
 * '-3' if error creating the file in Waspmote,
 * '-4' if error if the file doesn't exist in 3G+GPS module
 * '-5' if error getting the file
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
		PRINT_3G(F("Origin: "));
		USB.println(origin);
		PRINT_3G(F("Destiny: "));
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[50])));	//XMODEM_RECEIVE
	snprintf(buffer_3G, sizeof(buffer_3G),"%s=\"%s\"",str_aux1, origin);
	aux=sendCommand2(buffer_3G, OK_RESPONSE, "FILE NOT EXISTING");

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
			previous = millis();

			while ((serialAvailable(_socket) < 134) && ((millis()-previous) <= 3000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}

			for(int x=0; x < 135; x++){
				buffer_3G[x]=serialRead(_socket);
			}

			#if _3G_debug_mode>0
				if (buffer_3G[1] == 0)
				{
					PRINT_3G(F("*******************************\n"));
				}
				PRINT_3G(F("Header value: "));
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
						PRINT_3G(F("Error counter: "));
						USB.println(error_counter, DEC);
					#endif
				}

				#if _3G_debug_mode>0
					PRINT_3G(F("\tSize: "));
					USB.println(SD.getFileSize(destiny), DEC);
				#endif

				#if _3G_debug_mode>1
					PRINT_3G(F("Data field: "));
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
					PRINT_3G(F("EOF\n"));
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

	return 1;
}

/* sendXModemFile(const char* , const char*) - Sends a file from Waspmote and stores it in 3G+GPS Board
 *
 * This function gets a file from 3G+GPS Board and stores it in Waspmote with Xmodem protocol
 *
 * Returns: '1' if succes,
 * '0' if error,
 * '-2' if error sending de data
 * '-4' if error going to root directory in Waspmote's SD,
 * '-5' if error reading the size of the file,
 * '-6' if error opnening the file
 * '-7' if error reading the file
*/
int8_t Wasp3G::sendXModemFile(const char* origin, const char* destiny){

	int aux;
	uint8_t error_counter = 10, packet_counter = 1, answer;
	long file_size, bytes_sent = 0;
	uint16_t crc;

	SdFile file;

	// Enables microSD card on Waspmote:
	SD.ON();

	// First goes to the main directory:
	if (SD.goRoot() != 1)
	{
		SD.OFF();
		return -4;
	}

	#if _3G_debug_mode>0
		PRINT_3G(F("Origin: "));
		USB.println(origin);
		PRINT_3G(F("Destiny: "));
		USB.println(destiny);
	#endif

	file_size = SD.getFileSize(origin);
	if (file_size == -1)
	{

		#if _3G_debug_mode>0
			PRINT_3G(F("Error reading SD file size\n"));
		#endif

		SD.OFF();
		return -5;
	}
	else
	{
		#if _3G_debug_mode>0
			PRINT_3G(F("file size: "));
			USB.println(file_size,DEC);
		#endif

		if(!SD.openFile((char*)origin, &file, O_RDONLY))
		{
			// SD error
			#if _3G_debug_mode>0
				PRINT_3G(F("Error: opening file\n"));
			#endif
			SD.OFF();
			return -6;
		}

		// set pointer to the beginning of the file
		if(!file.seekSet(0))
		{
			// SD error
			#if _3G_debug_mode>0
				PRINT_3G(F("Error: setting initial offset in file\n"));
			#endif
			SD.OFF();
			return -7;
		}
	}

	// Sends AT command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[60])));	//XMODEM_SEND
	snprintf(buffer_3G, sizeof(buffer_3G), "%s\"%s\"", str_aux1, destiny);
	answer = sendCommand3(buffer_3G, "C", ERROR, "FILE IS EXISTING", 20000, SEND_ONCE);

	if (answer == 1)
	{
		do{
			//Assamble the Xmodem packet
			buffer_3G[0] = 0x01;
			buffer_3G[1] = packet_counter;
			buffer_3G[2] = 0xFF - packet_counter;

			aux = file.read(buffer_3G + 3, 128);
			if (aux == -1)
			{
				// SD error
				#if _3G_debug_mode>0
					PRINT_3G(F("Error: reading the file\n"));
				#endif

			}
			else if (aux < 128)
			{
				memset((&buffer_3G[3]) + aux, 0x1A, 128 - aux);
			}

			crc = sendXModemCheckSum(buffer_3G + 3);
			buffer_3G[131] = char((0xFF00 & crc)>>8);
			buffer_3G[132] = char(0x00FF & crc);
			buffer_3G[133] = 0x00;

			#if _3G_debug_mode>0
				PRINT_3G(F("Header value: "));
				USB.print(buffer_3G[0],DEC);
				USB.print(F("\tPacket numbers: "));
				USB.print(buffer_3G[1],DEC);
				USB.print(F("\t"));
				USB.print(buffer_3G[2],DEC);
				USB.print(F("\tChecksum value: "));
				USB.printHex(buffer_3G[131]);
				USB.printHex(buffer_3G[132]);
				USB.print(F("\tBytes sent: "));
				USB.print(bytes_sent + aux,DEC);
				USB.println(F(""));
			#endif

      #if _3G_debug_mode>1
        PRINT_3G(F(""));
      #endif

			for (uint8_t i = 0; i < 134; i++)
			{
				printByte(buffer_3G[i], _socket);
				#if _3G_debug_mode>1
					USB.printHex(buffer_3G[i]);
				#endif
			}
			#if _3G_debug_mode>1
				USB.println();
			#endif

			//Waits the answer from the module
			str_aux1[0] = XMODEM_ACK;
			str_aux1[1] = '\0';
			str_aux2[0] = XMODEM_NAK;
			str_aux2[1] = '\0';
			answer = waitForData(str_aux1, str_aux2, "C", 10000, millis(), 0);

			switch (answer)
			{
				case 1:
					bytes_sent += aux;
					packet_counter++;
					break;

				case 2:
				case 3:
					// set pointer to the beginning of the file
					if(!file.seekSet(bytes_sent - 1))
					{
						// SD error
						#if _3G_debug_mode>0
							PRINT_3G(F("Error: setting offset in file\n"));
						#endif

						bytes_sent = file_size;
					}
					error_counter--;
					break;
				default:
					// set pointer to the beginning of the file
					if(!file.seekSet(bytes_sent - 1))
					{
						// SD error
						#if _3G_debug_mode>0
							PRINT_3G(F("Error: setting offset in file\n"));
						#endif

						bytes_sent = file_size;
					}
					answer = 4;
					error_counter--;
					break;
			}
		}while((bytes_sent < file_size) && (error_counter > 0));

		SD.OFF();

		printByte(XMODEM_EOT, _socket);

		if (answer != 1)
		{
			return -answer;
		}

		return 1;
	}

	return 0;
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[16])));	//CHANGE_DIR
	if (unit == 0) // selects internal memory (C: unit)
	{
		snprintf(buffer_3G, sizeof(buffer_3G), "%sC:", str_aux1);
	}
	else if (unit == 1) // selects microSD memory (D: unit)
	{
		snprintf(buffer_3G, sizeof(buffer_3G), "%sD:", str_aux1);
	}

	// first changes to the desired unit
	answer = sendCommand2(buffer_3G, OK_RESPONSE, ERROR);

	if (answer == 1)
	{
		do{
			// then goes to the root
			strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[17])));	//CHANGE_DIR_BACK
			strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[18])));	//CHANGE_DIR_R
			answer = sendCommand2(str_aux1, str_aux2, ERROR);
			if (answer == 1)
			{
				previous = millis();
				x = 0;
				do{
					while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
					{
						if (millis() < previous)
						{
							previous = millis();
						}
					}
					buffer_3G[0] = serialRead(_socket);
					if (buffer_3G[0] == '/')
					{
						x++;
					}

					if (millis() < previous)
					{
						previous = millis();
					}

				}while ((buffer_3G[0] != '\r') && ((millis()-previous) < 3000));

				#if _3G_debug_mode>0
					PRINT_3G(F("Directory level: "));
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[16])));	//CHANGE_DIR
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s", str_aux1, path);

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

	long file_size=0;
	unsigned long previous;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[19])));	//FILE_ATTRIB
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s", str_aux1, filename);
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[20])));	//FILE_ATTRIB_R
	if (sendCommand2(buffer_3G, str_aux1, ERROR))
	{
		previous = millis();
		// waits for data available
		while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
		{
			if (millis() < previous)
			{
				previous = millis();
			}
		}
		buffer_3G[0] = serialRead(_socket);

		// Gets the file size
		do{
			file_size *= 10;
			file_size += buffer_3G[0] - 0x30;
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}

			buffer_3G[0] = serialRead(_socket);

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[0] != ',') && ((millis()-previous) < 3000));

		#if _3G_debug_mode>0
			PRINT_3G(F("File size: "));
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[21])));	//DEL_FILE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%s", str_aux1, filename);
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
	snprintf(buffer_3G, sizeof(buffer_3G), "%s?", str_aux1);
	return sendCommand1(buffer_3G, OK_RESPONSE);
}

/* ls(int8_t ) - Stores in 'buffer_3G' a list of subdirectories and files in the current directory
 *
 * This function stores in 'buffer_3G' a list of subdirectories and files in the current directory
 *
 * The parameter 'type' select the kind of list: '0' list both subdirectories and files,
 * 		'1' list subdirectories only and '2' list files only
 *
 * Returns '1' if success, '2' if no files or subdirectories and '0' if error
*/
int8_t Wasp3G::ls(int8_t type){

	unsigned long previous;
	int counter=0, answer;

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[23])));	//LIST_DIR
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=%d", str_aux1, type);
	answer = sendCommand3( buffer_3G, str_aux1, OK_RESPONSE, ERROR, 10000, SEND_DEFAULT);
	if (answer == 1)
	{
		previous=millis();
		counter = 0;
    #if _3G_debug_mode>1
      PRINT_3G(F(""));
    #endif
		do{
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 3000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[counter] = serialRead(_socket);
			#if _3G_debug_mode>1
				USB.print(buffer_3G[counter]);
			#endif
			counter++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((counter < _3G_BUFFER_SIZE)
				&& !((buffer_3G[counter-2] == 'O') && (buffer_3G[counter-1] == 'K'))
				&& ((millis()-previous) < 3000));

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[24])));	//GET_RSSI
	answer = sendCommand2(str_aux1, str_aux1, ERROR);

	if (answer == 1)
	{
		// if the command answers with +CSQ: reads the value
		previous = millis();
		serialRead(_socket);
		serialRead(_socket);
		answer = 0;
		count = serialRead(_socket);
		do{
			while ((serialAvailable(_socket) == 0) && ((millis()-previous) < 1000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			answer *= 10;
			answer += count-0x30;
			count = serialRead(_socket);

			if (millis() < previous)
			{
				previous = millis();
			}

 		}while ((count != ',') && ((millis()-previous) < 1000));

		#if _3G_debug_mode>0
			PRINT_3G(F("Raw RSSI: "));
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
			case 33:
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
 * Returns '1' on success,
 * '0' if error,
 * '-1' if timeout
 * '-2' if error restoring the baudrate (data are valid)
*/
int8_t Wasp3G::getCellsysInfo(){

	int8_t answer;
	int x;
	unsigned long previous;
	char command[15];

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);

	// reduces the baudrate
	changeBaudrate(4800);
	getIfReady();

	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[34])));		//CELL_SYS_INFO
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

				if (millis() < previous)
				{
					previous = millis();
				}

			}while ((buffer_3G[x-1] != '\r')
				&& ((millis() - previous) < 5000)
				&& (x < _3G_BUFFER_SIZE));

			if ((millis() - previous) < 5000)
			{
				// no timeout, waits for the next line or for the OK
				answer = waitForData(OK_RESPONSE, str_aux1, 5000, millis(), 0);
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));	//CHANGE_BAUDRATE
	snprintf(command, sizeof(command), "%s%ld", str_aux1, _baudRate);
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

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);

	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[35])));	//CELL_CHN_INFO
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

			if (millis() < previous)
			{
				previous = millis();
			}

		}while (!((buffer_3G[x-1] == 'K')
			&& (buffer_3G[x-2] == 'O'))
			&& ((millis() - previous) < 5000)
			&& (x < _3G_BUFFER_SIZE));
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

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[36])));	//CELL_RADIO_PARAM
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
			if ((buffer_3G[x] != -1) &&  (x < _3G_BUFFER_SIZE))
			{
				x++;
			}
			else
			{
				delay(1);
			}

			if (millis() < previous)
			{
				previous = millis();
			}

		}while (!((buffer_3G[x-1] == 'K')
			&& (buffer_3G[x-2] == 'O'))
			&& ((millis() - previous) < 5000));
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[29])));	//PREF_SERV_DOM
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=%d", str_aux1, mode);
	// Sends the command:
	return (sendCommand1(buffer_3G, OK_RESPONSE));
}

/* scanNetworkchannels() - Scans the network band channels specified
 *
 * This function scans the network band channels specified. Only in GSM
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
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[39])));	//CHN_SCAN_STR
		snprintf(buffer_3G, sizeof(buffer_3G), "%s=%d,%d", str_aux1, chn_start, chn_end);
	}
	else
	{
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[40])));	//CHN_SCAN_NUM
		snprintf(buffer_3G, sizeof(buffer_3G), "%s=%d,%d", str_aux1, chn_start, chn_end);
	}
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[41])));	//NET_START_SCAN
	answer=sendCommand1(buffer_3G, str_aux1, 20000, 0);

	if (answer == 1)
	{
		x = 0;
		previous = millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[x] = serialRead(_socket);
			x++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[x-1] != 'N')
			&& ((millis() - previous) < 10000)
			&& (x < _3G_BUFFER_SIZE));

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

	int8_t x;
	uint8_t answer=0;
	unsigned long previous;

	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[30])));	//INQ_UE_SYS
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[31])));	//INQ_UE_SYS_R
	answer=sendCommand1(str_aux1, str_aux2);

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[x]=serialRead(_socket);
			x++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[x-1] != '\r')
			&& ((millis() - previous) < 5000)
			&& (x < _3G_BUFFER_SIZE));

		buffer_3G[x-1]='\0';
	}

	return answer;
}

/* showsNetworkMode() - Shows network system mode
 *
 * This function shows network system mode.
 *
 * Returns '0' if error,
 * '-1' if error with CME error code available,
 * '1'for no service,
 * '2' for GSM,
 * '3' for GPRS,
 * '4' for EGPRS (EDGE),
 * '5' for WCDMA,
 * '6' for HSDPA only,
 * '7' for HSUPA only
 * '8' for HSPA (HSDPA and HSUPA)
*/
int8_t Wasp3G::showsNetworkMode(){

	int8_t answer;

	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[32])));	//NETWORK_MODE
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[33])));	//NETWORK_MODE_R
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

	memset(buffer_3G, '\0', _3G_BUFFER_SIZE);
	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[37])));	//CELL_SET_SYS_INFO
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[38])));	//CELL_SET_SYS_INFO_R
	answer=sendCommand1(str_aux1, str_aux2);

	if (answer == 1)
	{
		// Gets info from active cell:
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[x]=serialRead(_socket);
			x++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[x-1] != '\n')
			&& ((millis() - previous) < 10000)
			&& (x < _3G_BUFFER_SIZE));

		waitForData(str_aux2, 2000, millis(), 0);

		// Gets info from sync neighbor cell

		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[x]=serialRead(_socket);
			x++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[x-1] != '\n') && ((millis() - previous) < 10000));

		waitForData(str_aux2, 2000, millis(), 0);

		// Gets info from async neighbor cell

		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 10000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[x]=serialRead(_socket);
			x++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[x-1] != '\n')
			&& ((millis() - previous) < 10000)
			&& (x < _3G_BUFFER_SIZE));

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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[26])));	//PREF_MODE
	switch (mode)
	{
		case 0:
			snprintf(buffer_3G, sizeof(buffer_3G), "%s=2", str_aux1);
			break;
		case 1:
			snprintf(buffer_3G, sizeof(buffer_3G), "%s=13", str_aux1);
			break;
		case 2:
			snprintf(buffer_3G, sizeof(buffer_3G), "%s=14", str_aux1);
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[27])));	//PREF_BAND
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=0x%04X0000%04X%04X", str_aux1, high_zone, mid_zone, low_zone);
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
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[28])));	//ACQ_ORDER
	snprintf(buffer_3G, sizeof(buffer_3G), "%s=%d", str_aux1, mode);
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
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, destination);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[43])));	//CHANGE_BAUDRATE
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%ld", str_aux1, baudrate);

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
uint8_t Wasp3G::sendATCommand(const char* ATcommand){

	unsigned long timeout;
	uint16_t i;

	// Cleans 'buffer_3G':
	memset (buffer_3G, '\0', _3G_BUFFER_SIZE);

	i = 0;

	snprintf(buffer_3G, sizeof(buffer_3G), "AT%s%c%c", ATcommand,'\r','\n');

	serialFlush(_socket);

	// Sends the command to the 3G module:
	printString(buffer_3G,_socket);

	timeout = millis();
	// Waits and reads the answer from the 3G module:
	while ( (millis() - timeout) < 10000 )
	{
		while ((!serialAvailable(_socket)) && ((millis() - timeout) < 10000))
		{
			delay(100);
			if (millis() < timeout)
			{
				timeout = millis();
			}
		}
    #if _3G_debug_mode>0
      PRINT_3G(F(""));
    #endif
		while ( serialAvailable(_socket) && ((millis() - timeout) < 10000))
		{
			buffer_3G[i] = serialRead(_socket);
			#if _3G_debug_mode>0
				USB.print(char(buffer_3G[i]));
			#endif
			delay(20);

			if (i < _3G_BUFFER_SIZE)
			{
				i++;
			}
			else
			{
				timeout = millis() + 10000;
			}

			if (millis() < timeout)
			{
				timeout = millis();
			}
		}
	}

	buffer_3G[i]='\0';

	if (i < 2)
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[44])));	//AUDIO_OUT
	snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, ((output * 2) + 1));
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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[45])));	//MUTE_MIC
	if (gain == 0)	// If gain is '0' enables the mute of the microphone
	{

		snprintf(buffer_3G, sizeof(buffer_3G), "%s1", str_aux1);
		return sendCommand1(buffer_3G, OK_RESPONSE);
	}
	else // If gain isn't '0' disables the mute and set the gain level
	{
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
		sendCommand1(buffer_3G, OK_RESPONSE);

		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[46])));	//GAIN_MIC
		snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, gain-1);
		return sendCommand1(buffer_3G, OK_RESPONSE);

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

	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[48])));	//MUTE_SPEAKER
	if (volume == 0)	// If volume is '0' enables the silent mode
	{
		snprintf(buffer_3G, sizeof(buffer_3G), "%s1", str_aux1);
		return sendCommand1(buffer_3G, OK_RESPONSE);
	}
	else // If volume isn't '0' disables the silent mode and set the volume level
	{
		snprintf(buffer_3G, sizeof(buffer_3G), "%s0", str_aux1);
		sendCommand2(buffer_3G, OK_RESPONSE, ERROR);
		strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[49])));	//LVL_SPEAKER
		snprintf(buffer_3G, sizeof(buffer_3G), "%s%d", str_aux1, volume-1);
		return sendCommand1(buffer_3G, OK_RESPONSE);
	}

	return 0;
}

/* whoamI() - Gets the model of the module
 *
 * This function gets the model of the module and saves it in 'buffer_3G'
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::whoamI(){
	int8_t answer, x;
	unsigned long previous;

	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[51])));	//AT_WHO_AM_I
	answer=sendCommand1(str_aux1, "\r\n");

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[x]=serialRead(_socket);
			x++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[x-1] != '\r') && ((millis() - previous) < 5000));
		buffer_3G[x-1]='\0';
	}

	return answer;

}

/* firmware_version() - Gets the firmware version of the module
 *
 * This function gets the firmware version of the module and saves it in 'buffer_3G'
 *
 * Returns '1' on success, '0' if error
*/
int8_t Wasp3G::firmware_version(){
	int8_t answer, x;
	unsigned long previous;

	// Sends the command:
	strcpy_P(str_aux1, (char*)pgm_read_word(&(table_MISC[52])));	//FIRMWARE_VER
	strcpy_P(str_aux2, (char*)pgm_read_word(&(table_MISC[53])));	//FIRMWARE_VER_R
	answer=sendCommand1(str_aux1, str_aux2);

	if (answer == 1)
	{
		x=0;
		previous=millis();
		do{
			while ((serialAvailable(_socket) == 0) && ((millis() - previous) < 5000))
			{
				if (millis() < previous)
				{
					previous = millis();
				}
			}
			buffer_3G[x]=serialRead(_socket);
			x++;

			if (millis() < previous)
			{
				previous = millis();
			}

		}while ((buffer_3G[x-1] != '\r') && ((millis() - previous) < 5000));
		buffer_3G[x-1]='\0';
	}

	return answer;

}

/* set_APN(char*) - Sets the apn from operator
 * This function sets the apn from operator
 * Returns nothing
*/
void Wasp3G::set_APN( char* apn){

	set_APN( apn, NULL, NULL);
}

/* set_APN(char*, char*, char*) - Sets the apn, login and password from operator
 *
 * This function sets the apn, login and password from operator
 *
 * Returns nothing
*/
void Wasp3G::set_APN( char* apn, char* login, char* password){

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
void Wasp3G::show_APN(){
	// APN parameters depends on SIM
	PRINT_3G(F("APN: "));
	USB.println(_apn);
	PRINT_3G(F("LOGIN: "));
	USB.println(_apn_login);
	PRINT_3G(F("PASSWORD: "));
	USB.println(_apn_password);
}

#if TRANSMISSION_FUSE

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
 * Returns '1' on success,
 * '-2' if error setting the connection parameters (APN),
 * '-3' if error setting the FTP server ('-13' if CME error available),
 * '-4' if error setting the FTP port ('-14' if CME error available),
 * '-5' if error setting the FTP mode ('-15' if CME error available),
 * '-6' if error setting the FTP type ('-16' if CME error available),
 * '-7' if error setting the user name ('-17' if CME error available),
 * '-8' if error setting the FTP password ('-18' if CME error available),
 * '-19' if error downloading the OTA version file,
 * '-21' if error with CME code (FTP error) downloading the OTA version file,
 * '-22' if error sending the OTA version file from 3G module to Waspmote's SD,
 * '-23' if there isn't FILE tag,
 * '-24' if there isn't PATH tag,
 * '-25' if there isn't VERSION tag,
 * '-26' if OTA is not necessary,
 * '-27' if OTA files are the same program version,
 * '-28' if error downloading the OTA file,
 * '-31' if error with CME code (FTP error) downloading the OTA file
 *  and '-32' if error sending the OTA file from 3G module to Waspmote's SD.
*/
int8_t Wasp3G::requestOTA(const char* FTP_server, const char* FTP_port, const char* FTP_username, const char* FTP_password){

	int8_t answer;
	char aux_ver[4];
	uint8_t version;
	char* str_pointer;
	char aux_name[8];
	char programID[8];
	char path[60];

//	memset(path, 0x00, strlen(path));
	//memset(aux_name, 0x00, strlen(aux_name));

	SD.ON();
	SD.goRoot();
	SD.del(OTA_ver_file);
	SD.OFF();
	answer = configureFTP( FTP_server, FTP_port, FTP_username, FTP_password, 1, "I");
	if (answer == 1)
	{

		answer = downloadData(OTA_ver_file, OTA_ver_file);
		if (answer == 1)
		{

			SD.ON();
			SD.goRoot();

			// Reads the file
			strcpy(buffer_3G, SD.cat(OTA_ver_file, 0, _3G_BUFFER_SIZE));

			// Searchs the file name
			str_pointer = strstr(buffer_3G, "FILE:");
			if (str_pointer != NULL)
			{
				strncpy(aux_name, strchr(buffer_3G, ':') + 1, 7);
				aux_name[7] = '\0';

				#if _3G_debug_mode>0
					PRINT_3G(F("OTA file: "));
					USB.println(aux_name);
				#endif
				// Searchs the file name
				str_pointer = strstr(buffer_3G, "PATH:");
				if (str_pointer != NULL)
				{
					strncpy(path, strchr(str_pointer, ':') + 1, strchr(str_pointer, '\n') - (strchr(str_pointer, ':')));

					path[strchr(path, '\n') - path] = '\0';

					#if _3G_debug_mode>0
						PRINT_3G(F("File path: "));
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
							PRINT_3G(F("Version: "));
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
								PRINT_3G("Downloading OTA file\n");
								#if _3G_debug_mode>0
									PRINT_3G(F("File to download: "));
									USB.println(path);
									PRINT_3G(F("File to save: "));
									USB.println(aux_name);
								#endif
								answer = downloadData(path, aux_name);
								if (answer == 1)
								{
									_3G.OFF();

									Utils.loadOTA(aux_name, version);

									return 1;
								}
								else
								{
									SD.OFF();
									return answer - 28;
								}
							}
							else
							{
								#if _3G_debug_mode>0
									PRINT_3G(F("Same program version, no OTA required\n"));
								#endif
								SD.OFF();
								return -27;
							}

						}
						else
						{

							#if _3G_debug_mode>0
								PRINT_3G(F("No OTA\n"));
							#endif
							SD.OFF();
							return -26;
						}


					}
					else
					{
						SD.OFF();
						return -25;
					}
				}
				else
				{
					SD.OFF();
					return -24;
				}
			}
			else
			{
				SD.OFF();
				return -23;
			}
		}
		else
		{
			return answer - 19;
		}
	}
	else
	{
		return answer;
	}

}

#endif
// Preinstantiate Objects //////////////////////////////////////////////////////

Wasp3G _3G = Wasp3G();
