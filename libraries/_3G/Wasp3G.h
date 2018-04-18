/*! \file Wasp3G.h
    \brief Library for managing the SIM5218 module

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

    Version:		3.2
    Design:			David Gascón
    Implementation:	Alejandro Gállego

*/

 /*! \def Wasp3G_h
    \brief The library flag

  */
#ifndef Wasp3G_h
#define Wasp3G_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>

//#include <WaspWIFI.h>

//!Module fuses
#define GSM_FUSE	1		//Call and SMS related functions and constants
#define CAMERA_FUSE	0		//Camera related functions and constants
#define FTP_FUSE	1		//FTP related functions and constants
#define MAIL_FUSE	1		//SMTP and POP3 related functions and constants
#define HTTP_FUSE	1		//HTTP and HTTPS related functions and constants
#define GPS_FUSE	1		//GPS related functions and constants
#define IP_FUSE		1		//TCP and UDP related functions and constants
#define TRANSMISSION_FUSE	1

#define OTA_FUSE	1		//TCP and UDP related functions and constants

#define _3G_debug_mode	0
#define PRINT_3G(str)	USB.print(F("[3G] ")); USB.print(str);

#define _3G_BUFFER_SIZE 512

#define	_3G_APN "apn"
#define	_3G_LOGIN "login"		//comment this line if you don't need login
#define	_3G_PASSW "password"	//comment this line if you don't need password

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/


/*! \def _3G_ON
    \brief Working mode. Power ON in this case
 */
#define	 _3G_ON	1

/*! \def _3G_FULL
    \brief Working mode. Full functionality in this case
 */
#define	 _3G_FULL	2

/*! \def _3G_MINIMUM
    \brief Working mode. Minimum functionality (RF and SIM are OFF) in this case
 */
#define	 _3G_MINIMUM	3

/*! \def _3G_RF_OFF
    \brief Working mode. RF circuits are off in this case
 */
#define	 _3G_RF_OFF		4

/*! \def _3G_SLEEP
    \brief Working mode. RF and SIM are OFF and the module enters in sleep mode
 */
#define	 _3G_SLEEP 		5

/*! \def _3G_POWER_OFF
    \brief Working mode. Power OFF in this case
 */
#define	_3G_POWER_OFF	0


/*! \def _3G_RATE
    \brief SIM5218 Baud Rate
 */
#define	_3G_RATE	115200

/*! \def DELAY_ON_SEND
    \brief Constants for AT commands. Delay after every sending attempt in this case
 */
#define DELAY_ON_SEND 250

/*! \def DEFAULT_TIMEOUT
    \brief Constants for AT commands. Default attempts to try in this case.
 */
#define DEFAULT_TIMEOUT 10000

/*! \def SEND_ONCE
    \brief Constants for AT commands. Sending only once in this case
 */
#define SEND_ONCE 1

/*! \def SEND_DEFAULT
    \brief Constants for AT commands. Sending 10 times in this case
 */
#define SEND_DEFAULT 10

/*! \def PORT_USED
    \brief Constants for AT commands. Port used in AT commands functions in this case
 */
#define PORT_USED  1



/*! \def UDP_CLIENT
    \brief When opening a socket, it can be opened as client or server. Client in this case
 */
#define	UDP_CLIENT	1

/*! \def TCP_CLIENT
    \brief When opening a socket, it can be opened as client or server. Client in this case
 */
#define	TCP_CLIENT	0

/*! \def TCP_SERVER
    \brief When opening a socket, it can be opened as client or server. Server in this case
 */
#define	TCP_SERVER	2

/*! \def MULTI_CONNECTION
    \brief Configures the module to use multiple connection mode
 */
#define	MULTI_CONNECTION 3

/*! \def ENABLE
 */
#define	ENABLE	1

/*! \def DISABLE
 */
#define	DISABLE	0

/*! \def DEFAULT_CLIR
    \brief CLIR mode. Presentation indicator is used according to the subscription of the CLIR service
 */
#define	DEFAULT_CLIR	0

/*! \def SUPPRESS_CLIR
    \brief CLIR mode. CLIR supression
 */
#define	SUPPRESS_CLIR	1

/*! \def INVOKE_CLIR
    \brief CLIR mode. CLIR invocation
 */
#define	INVOKE_CLIR	2

/*! \def GET
 */
#define	GET 0

/*! \def POST
 */
#define	POST 1


#define	AT_COMMAND	"AT"
#define OK_RESPONSE "OK"

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

//Xmodem constants
#define XMODEM_ACK		0x06
#define XMODEM_NAK		0x15
#define XMODEM_SOH		0x01
#define XMODEM_EOT		0x04
#define XMODEM_CAN		0x18




/******************************************************************************
 * Class
 ******************************************************************************/

//! Wasp3G Class
/*!
	Wasp3G Class defines all the variables and functions used to manage GPRS module
 */
class Wasp3G
{
	private:

	//! Variable : stores if the module is ready or not (0:not ready, 1:ready)
   uint8_t ready;

	//! Variables: aux strings that store commands and answer extracted from flash memory
	char str_aux1[20];
	char str_aux2[20];
	char str_aux3[60];
	char str_aux4[20];
	char str_aux5[20];

   	//! Variables: strings that store _apn, _apn_login and _apn_password from operator
	char _apn[20], _apn_login[20], _apn_password[20];


	//! It gets if GPRS module is ready or not
    /*!
	\return nothing. It changes the value of 'ready'
	 */
	void getIfReady();



	int8_t check3Gconnection(unsigned long time);

	//! It checks if 3G connection is attached or not
    /*!
	\param void
	\return '1' on success, '0' if error
	 */
	uint8_t check3Gattach();

	uint8_t getXModemCheckSum(uint8_t* data);

	uint16_t sendXModemCheckSum(char* ptr);

	#if HTTP_FUSE
		//! It configures the operator parameters
		/*!
		\return  '1' on success
			'-1' if error setting APN, username and password,
			'-3' if error receiving data or timeout waiting data
			'-15' if error setting APN, username and password with CME_error code available
		*/
		int8_t initHTTP();

		//! It sends the HTTP request to the server
		/*!
		\param const char* url : url or IP address of the server
		\param uint16_t port : server port
		\param uint8_t* data : frame data to send
		\param int length : length of the frame
		\param uint8_t method : GET or POST
		\return  '1' on success
			'-2' if error opening a HTTP session
			'-3' if error receiving data or timeout waiting data
			'-16' if error opening a HTTP session with CME_error code available
		*/
		int8_t sendHTTPrequest(	const char* url,
								uint16_t port,
								uint8_t* data,
								uint16_t length,
								uint8_t method );

		//! It reads the response from the server
		/*!
		\param int8_t parse : '0' header and answer, '1' only answer from Meshlium
		\return  '1' on success
			'-3' if error receiving data or timeout waiting data
			'-4' if error changing the baudrate (data received is OK)
			'-17' if url response its not OK  (HTTP code 200)
			'-18' if content-length field not found
			'-19' if data field not found
		*/
		int8_t readHTTPresponse(int8_t parse);
	#endif

	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\return  '1' if expectedAnswer1 was found and '0' if no answer was found
	 */
	uint8_t sendCommand1( const char* theText, const char* expectedAnswer1);

	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout
	\param int sendOnce : specifies if the data is sent once
	\return  '1' if expectedAnswer1 was found and '0' if no answer was found
	 */
	uint8_t sendCommand1(	const char* theText, const char* expectedAnswer1,
							unsigned long MAX_TIMEOUT, int sendOnce);

	//functions with two answers
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param char* expectedAnswer2 : string expected to be answered by the module
	\return  '1' if expectedAnswer1 was found, '2' if expectedAnswer2 was found
		and '0' if no answer was found
	 */
	uint8_t sendCommand2(	const char* theText,
							const char* expectedAnswer1,
							const char* expectedAnswer2);

	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param char* expectedAnswer2 : string expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout
	\param int sendOnce : specifies if the data is sent once
	\return  '1' if expectedAnswer1 was found, '2' if expectedAnswer2 was found
		and '0' if no answer was found
	 */
	uint8_t sendCommand2(	const char* theText,
							const char* expectedAnswer1,
							const char* expectedAnswer2,
							unsigned long MAX_TIMEOUT,
							int sendOnce);

	//function with three answers
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param char* expectedAnswer2 : string expected to be answered by the module
	\param char* expectedAnswer3 : string expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout
	\param int sendOnce : specifies if the data is sent once
	\return  '1' if expectedAnswer1 was found, '2' if expectedAnswer2 was found,
		'3' if expectedAnswer2 was found and '0' if no answer was found
	 */
	uint8_t sendCommand3(	const char* theText,
							const char* expectedAnswer1,
							const char* expectedAnswer2,
							const char* expectedAnswer3,
							unsigned long MAX_TIMEOUT,
							int sendOnce);

	//function with four answers
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param char* expectedAnswer2 : string expected to be answered by the module
	\param char* expectedAnswer3 : string expected to be answered by the module
	\param char* expectedAnswer4 : string expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout
	\param int sendOnce : specifies if the data is sent once
	\return  '1' if expectedAnswer1 was found, '2' if expectedAnswer2 was found,
		'3' if expectedAnswer2 was found, '4' if expectedAnswer2 was found and
		'0' if no answer was found
	 */
	uint8_t sendCommand4(	const char* theText,
							const char* expectedAnswer1,
							const char* expectedAnswer2,
							const char* expectedAnswer3,
							const char* expectedAnswer4,
							unsigned long MAX_TIMEOUT,
							int sendOnce);


	//! It waits for data from the module
    /*!
	\param char* expectedAnswer1 : string 1 expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout
	\param unsigned long timeout : specifies the timeout
	\param int seconds : specifies the number of seconds to wait before listening to the module
	\return '1' if expectedAnswer1 was found and '0' if no answer was found
	 */
	uint8_t waitForData(	const char* expectedAnswer1,
							unsigned long MAX_TIMEOUT,
							unsigned long timeout,
							int seconds);

	//! It waits for data from the module
    /*!
	\param char* expectedAnswer1 : string 1 expected to be answered by the module
	\param char* expectedAnswer2 : string 2 expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout
	\param unsigned long timeout : specifies the timeout
	\param int seconds : specifies the number of seconds to wait before listening to the module
	\return '1' if expectedAnswer1 was found, '2' if expectedAnswer2 was found
		and '0' if no answer was found
	 */
	uint8_t waitForData(	const char* expectedAnswer1,
							const char* expectedAnswer2,
							unsigned long MAX_TIMEOUT,
							unsigned long timeout,
							int seconds);

	//! It waits for data from the module
    /*!
	\param char* expectedAnswer1 : string 1 expected to be answered by the module
	\param char* expectedAnswer2 : string 2 expected to be answered by the module
	\param char* expectedAnswer3 : string 3 expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout
	\param unsigned long timeout : specifies the timeout
	\param int seconds : specifies the number of seconds to wait before listening to the module
	\return '1' if expectedAnswer1 was found, '2' if expectedAnswer2 was found,
		'3' if expectedAnswer2 was found and '0' if no answer was found
	 */
	uint8_t waitForData(	const char* expectedAnswer1,
							const char* expectedAnswer2,
							const char* expectedAnswer3,
							unsigned long MAX_TIMEOUT,
							unsigned long timeout,
							int seconds);
	//! It waits for data from the module
    /*!
	\param char* expectedAnswer1 : string 1 expected to be answered by the module
	\param char* expectedAnswer2 : string 2 expected to be answered by the module
	\param char* expectedAnswer3 : string 3 expected to be answered by the module
	\param char* expectedAnswer4 : string 3 expected to be answered by the module
	\param unsigned long MAX_TIMEOUT : specifies the maximum timeout
	\param unsigned long timeout : specifies the timeout
	\param int seconds : specifies the number of seconds to wait before listening to the module
	\return '1' if expectedAnswer1 was found, '2' if expectedAnswer2 was found,
		'3' if expectedAnswer2 was found, '4' if expectedAnswer2 was found and
		'0' if no answer was found
	 */
	uint8_t waitForData(	const char* expectedAnswer1,
							const char* expectedAnswer2,
							const char* expectedAnswer3,
							const char* expectedAnswer4,
							unsigned long MAX_TIMEOUT,
							unsigned long timeout,
							int seconds,
							int n_answers);





	public:

	//! Variable : power mode
    /*!
	Possible values are: _3G_ON, _3G_FULL, _3G_MINIMUM, _3G_OFFLINE and _3G_OFF;
	*/
	uint8_t _pwrMode;

	 //! Variable : SOCKET used by the 3G module
    /*!
	3G module is connected to the SOCKET1
	*/
	uint8_t	_socket;

	uint32_t  _baudRate;

	//! Variable : IP direction
	char IP_dir[22]; // XXX.XXX.XXX.XXX:XXXXX
	char n_connection;
	char tlfNumber[16];

	//! Variable :
	/*!
	bit 0 => '0'= normal mode, '1'= transparent mode
	bit 1 => '0'= single connection, '1'= multiple connection
	bit 2 => '0'= net close, '1'= net open
	bit 3 => '0'= client, '1'= server
	*/
	uint8_t IP_flags;

	//! Variable : Stores CME or CMS error code
    uint16_t CME_CMS_code;

	//! Variable :
    char buffer_3G[_3G_BUFFER_SIZE];

	//!Variables for GPS
	#if GPS_FUSE

		char latitude[13]; // +/- ddmm.mmmmmm. d=degrees, m=minutes
		char longitude[14]; // +/- dddmm.mmmmmm. d=degrees, m=minutes
		char date[7]; // ddmmyy
		char UTC_time[9]; // hhmmss.s
		char altitude[10];
		char speedOG[6]; // Speed Over Ground. Unit is knots.
		char course[6];

	#endif

	 //! class constructor
    /*!
	It initializes some variables
	\param void
	\return void
    */
	Wasp3G();

	//!*****************************************************************
	//! Power functions
	//! It opens SOCKET1 and powers the SIM5218 module
    /*!
	\param void
	\return '1' on success, '0' if error and '2' if error with CME error response.
	\sa close(), begin()
     */
	uint8_t ON();


	//! It closes SOCKET1 and powers off the SIM5218 module
    /*!
	\param void
	\return '1' on success and '0' if error
	\sa close(), begin()
	 */
	uint8_t OFF();


	//! It opens SOCKET and sets multiplexer properly
    /*!
	\param void
	\return void
	 */
	void begin();


	//! It closes SOCKET and sets multiplexer properly
    /*!
	\param void
	\return void
	*/
	void close();


	//! It sets Power Mode
    /*!
	\param uint8_t pwrMode : the desired power mode (_3G_ON, _3G_FULL, _3G_MINIMUM, _3G_OFFLINE and _3G_OFF)
	\return '1' on success, '0' if error  and '-2' if error with CME error response.
	 */
	uint8_t setMode(uint8_t pwrMode);


	//! It gets Power Mode
    /*!
	\param void
	\return the power mode (_3G_ON, _3G_FULL, _3G_MINIMUM, _3G_OFFLINE and _3G_OFF)
	 */
	uint8_t getMode();

	//! It checks if 3G is connected to the network
    /*!
	\param uint8_t time: time to wait
	\return Returns '1' when connected,
		'0' if not registered and the module is not currently searching a new operator,
		'-2' if not registered, but the module is currently searching a new operator,
		'-3' if registration denied
		and '-4' if the state is unknown
	 */
	int8_t check(unsigned long time);

		//! Sets time and date to 3G module from RTC
	/*!
	\return '1' on success , '0' or '-2' if error
	*/
	uint8_t setTime();

	//! It sets PIN
    /*!
	\param const char* PIN : the SIM's PIN
	\return '1' on success, '0' if error
	*/
	int8_t	setPIN(const char* pin);

	//! changes PIN number to the SIM
    /*!
	\param const char* old_pin : the old SIM's PIN
	\param const char* new_pin : the new SIM's PIN
	\return '1' on success, '0' if error and -1 if CME code are available
	*/
	uint8_t changePIN(const char* old_pin, const char* new_pin);

	//! It gets the IMSI from the SIM card
    /*!
    It stores the IMSI into 'buffer_3G' variable.
	\return '1' if connected, '0' if not
	*/
    int8_t getIMSI();

    //! It gets the IMEI from the 3G module
    /*!
    It stores the IMEI into 'buffer_3G' variable.
	\return '1' if succes, '0' if not
	 */
    int8_t getIMEI();



	int8_t	manageIncomingData();

	int8_t	manageIncomingData(unsigned long waiting_time);


	//!*****************************************************************
	//! GSM functions
	#if GSM_FUSE
	//! It makes a call to the specified number
    /*!
	\param const char* tlfNumber : telephone number to call. It must be a telephone number with 9 digits.
	\return '1' on success, '0' if error and '-2' if no carrier
	 */
	int8_t makeCall(const char* tlfNumber);

	//! It makes a lost call to the specified number
    /*!
	\param const char* tlfNumber : telephone number to call. It must be a telephone number with 9 digits.
	\param uint8_t timeCall : time the module is calling (in seconds)
	\return '1' on success, '0' if error and '-2' if no carrier
	 */
	int8_t makeLostCall(const char* tlfNumber, uint8_t timeCall);

	//! It sets the info shown when an incoming call is received
    	/*!
	\param void
	\return '1' on success, '0' if error and '-2' if error with CME error code available
	 */
	int8_t	setInfoIncomingCall();

	//! It stores in 'buffer_3G' variable the telephone number of the incoming call
    /*!
	\param char* data : data returned by the module when a call is being received
	\return '1' on success, '0' if error
	 */
	int8_t	readCall();

	//! It hangs all the active calls up
    /*!
	\return '1' on success, '0' if error
	 */
	int8_t hangUp();

	//! Enables or disables the auto-answer function of the module
    /*!
	\param uint8_t rings : '0' disable and '1' to '255' for rings of wait before answer
	\return '1' on success, '0' if error
	 */
	int8_t	autoAnswer(uint8_t rings);

	//! Answers an incoming call
    /*!
	\return '1' on success, '0' if error
	 */
	int8_t	answerCall();

	//!  Generates a DTMF tone
    /*!
	\param uint8_t tone : '0' - Stop the sound tone, '1' - DTMF tone for 1 key, duration 100ms,
		'2' - DTMF tone for 2 key, duration 100ms, '3' - DTMF tone for 3 key, duration 100ms,
		'4' - DTMF tone for 4 key, duration 100ms, '5' - DTMF tone for 5 key, duration 100ms,
		'6' - DTMF tone for 6 key, duration 100ms, '7' - DTMF tone for 7 key, duration 100ms,
		'8' - DTMF tone for 8 key, duration 100ms, '9' - DTMF tone for 9 key, duration 100ms,
		'10' - DTMF tone for 0 key, duration 100ms, '11' - DTMF tone for A key, duration 100ms,
		'12' - DTMF tone for B key, duration 100ms, '13' - DTMF tone for C key, duration 100ms,
		'14' - DTMF tone for D key, duration 100ms, '15' - DTMF tone for # key, duration 100ms,
		'16' - DTMF tone for * key, duration 100ms, '17' - Subscriber busy sound, duration always,
		'18' - Congestion sound, duration always, '19' - Error information sound, duration 1330*3ms,
		'20' - Number unobtainable sound, duration 1330*3ms, '21' - Authentication failure sound, duration 1330*3ms,
		'22' - Radio path acknowledgement sound, duration 700*1ms, '23' - Radio path not available sound, duration 400*4ms,
		'24' - CEPT call waiting sound, duration 4000*2ms, '25' - CEPT ringing sound, duration always,
		'26' - CEPT dial tone, duration always
	\return '1' on success, '0' if error
	 */
	int8_t	generateTone(uint8_t tone);

	//! Controls the ringer level of the loudspeaker
    /*!
	\param uint8_t level : '0' for mute and '1' to '5' for volume level
	\return '1' on success, '0' if error
	 */
	int8_t ringerLevel(uint8_t level);

	//! It enables or disables the presentation of the incoming call
    /*!
	\param uint8_t mode : ENABLE or DISABLE
	\return '1' on success, '0' if error and '-2' if error with CME error code available
	 */
	int8_t setCLIPresentation(uint8_t mode);

	//! It restricts or enables the presentation of the CLI to the called party when originating a call.
    /*!
	\param uint8_t mode : DEFAULT_CLIR, INVOKE_CLIR or SUPPRESS_CLIR
	\return '1' on success, '0' if error and '-2' if error with CME error code available
	 */
	int8_t setCLIRestriction(uint8_t mode);

	//! It gets the phone activity status
    /*!
	\param void
	\return '0' for error, '1'= Ready, '2'= Unknown,'3'= Ringing, '4'= Call in progress
	 */
	int8_t getPhoneActStatus();

	//! It sets 'text mode' for sending SMS
    /*!
	\param void
	\return '1' on success, '0' if error
	 */
	int8_t setTextModeSMS();

	//! It sends a SMS to the specified number
    /*!
	\param const char* smsText : SMS text (up to 160 bytes)
	\param const char* tlfNumber : telephone number to call. It must be a telephone number with 9 digits.
	\return '1' on success, '0' if error and -2 if error with CMS error code available
	 */
	int8_t sendSMS(const char* smsText, const char* tlfNumber);

	//! It sets the info shown when an incoming SMS is received
	/*!
	\param void
	\return '1' on success, '0' if error, '-2' if error with CMS error code,
		'-3' if error setting the memory and '-4' if error setting the memory with CMS error code.
	 */
	int8_t setInfoIncomingSMS();

	//! It stores in 'tlfIN' and 'sms' variables the telephone number and the text of the incoming SMS. It stores in 'sms_index' variable the last sms received index
    /*!
	\param char* data : data returned by the module when an SMS is received
	\return '1' on success, '0' if error, '-1' if no memory
	 */
	int8_t readSMS(uint8_t index);

	//! It gets the number of total SMS stored in the SIM
    /*!
	\return the number of SMS, '-1' if error or '-2' if error with CMS error code
	 */
	int8_t getTotalSMS();

	//! It deletes a sms in the memory selected by sms_index
    /*!
	\param int sms_index : index of the sms to delete
	\return '1' on success, '0' if error and '-2' if error with CMS error code
	 */
	int8_t deleteSMS(uint8_t sms_index);

	//! It gets the index of the incoming SMS
    /*!
	\return the index of SMS, '0' if error
	 */
	int8_t incomingSMS();

	#endif

	//!*****************************************************************
	//! Camera functions
	#if CAMERA_FUSE
	//! Initializes the camera
    /*!
	\param void
	\return Returns '1' on success,
		'0' if error,
		'-2' if camera not detected,
		'-3' if camera is already started.
	 */
	int8_t startCamera();

	//! Stops the camera
    /*!
	\param void
	\return Returns '1' on success,
		'0' if error,
		'-2' if camera not started
	 */
	int8_t stopCamera();

	//! Take a picture and saves it.
	/*!
	\param uint8_t location: '0' from module location, '1' from 3G SD location
	\return Returns '1' on success,
		'0' if error,
		'2' error setting the store location,
		'3' if camera not detected,
		'4' if camera not started,
		'5' if camera is in invalid state,
		'6' if there isn't memory enough
		Buffer_3G contains the picture name.
	 */
	int8_t takePicture();

	//! Starts video capture
	/*!
	\return Returns '1' on success ,
		'0' if error,
		'-2' if camera not started,
		'-3' if camera is in invalid state,
		'4' if there isn't memory enough
	 */
	int8_t startVideo();

	//! Pauses video capture
	/*!
	\return '1' on success,
		'0' if error,
		'-2' if camera not started,
		'-3' if camera is in invalid state
	 */
	int8_t pauseVideo();

	//! Resumes video capture
	/*!
	\return '1' on success,
		'0' if error,
		'-2' if camera not started,
		'-3' if camera is in invalid state
	 */
	int8_t resumeVideo();

	//! Stops video capture
	/*!
	\return Returns '1' on success,
		'0' if error,
		'-2' if camera not started,
		'-3' if camera is in invalid state
	 */
	int8_t stopVideo();

	//! Configures the analog camera capturer
	/*!
	\param uint8_t video_mode: '0' for PAL, '1' for NTSC
	\return Returns '1' on success and '0' if error
	 */
	int8_t analogCameraConfig(uint8_t video_mode,uint8_t video_channel);

	//! Sets the camera rotation
	/*!
	\param const char* rotation: "0" degrees, "90" degrees, "180" degrees and "270" degrees
	\return Returns '1' on success,
		'0' if error,
		'-2' if camera not started
		'-3' if camera is in invalid state
	 */
	int8_t cameraRotation(const char* rotation);

	//!  Sets camera brightness
	/*!
	\param uint8_t mode: 0 to 6 (0 is the lowest, 6 is the highest)
	\return Returns '1' on success,
		'0' if error,
		'-2' if camera not started,
		'-3' if camera is in invalid state
	 */
	int8_t cameraBrightness(uint8_t mode);

	//!  Sets camera resolution
	/*!
	\param uint8_t resolution: '0' for STAMP,
								'1' for QQVGA,
								'2' for QCIF,
								'3' for QVGA,
								'4' for CIF,
								'5' for VGA
								'6' for XGA
	\return '1' on success,
		'0' if error,
		'-2' if camera not detected
		'-3' if camera not started
	 */
	int8_t cameraResolution(uint8_t resolution);

	//!  Sets FPS
	/*!
	\param uint8_t fps:	'0' for 7.5 fps, '1' for 10 fps and '2' for 15 fps
	\return '1' on success,
		'0' if error,
		'-2' if camera not started,
		'-3' if camera is in invalid state
	 */
	int8_t cameraFPS(uint8_t fps);

	//!  Sets picture name format
	/*!
	\param const char* name: string with the name format for the pictures
	\return '1' on success and '0' if error
	 */
	int8_t pictureName(const char* name);

	//! Adds date frame on the picture.
	/*!
	\param uint8_t state: '0' for disable and '1' for enable
	\return '1' on success and '0' if error
	*/
	int8_t pictureTimeStamp(uint8_t state);


	int8_t autoLevel(void);

	//! Powers the IR LEDs of the Video Camera Sensor Board
	/*!
	\param uint8_t blockIR:	'0' powers off all LEDs,
							'1' powers on block 1,
							'2' powers on block 2
							'3'powers all LEDs
	\return nothing
	*/
	void powerIRLED(int8_t blockIR);

	//!  Reads the value of a LDR sensor, turn on/off the IR LEDs and selects the IR filter position
	/*!
	\return nothing
	 */
	void autoLight(void);

	//!  Selects a filter for the lens
	/*!
	\param int8_t filter: '1' enables IR cut filter, '0' disables IR cut filter
	\return nothing
	 */
	void selectFilter(int8_t filter);

	void enablePIRInterrupt(void);

	void disablePIRInterrupt(int8_t PIRstate);

	//!  Makes a videocall
	/*!
	\param const char* phone_number: number to call
	\param int8_t record:	'0' not record video,
							'1' only record far-end video,
							'2' only record near-end video
							'3' record both far-end and near-end
	\return '1' if success,
		'0' if error,
		'-1' if error connecting to the other party,
		'-2' if error with setup or the other party hangs the call,
		'-3'  if error connecting the videocall
		'-4' if error recording the call (videocall is active)
	 */
	int8_t makeVideoCall(const char* phone_number, int8_t record);

	//!  Hangs a videocall
	/*!
	\return '1' on success and '0' if error
	 */
	int8_t hangVideoCall();

	//!  Sets the video quality
	/*!
	\param int8_t VideoQuality: 5 for high quality image or 15 for high motion profile
	\return '1' on success and '0' if error
	 */
	int8_t VideoCallQuality(int8_t VideoQuality);

	//!  Sends DMTF tones
	/*!
	\param const char* DMTF_str: string with the DMTF tones. The maximal length of DTMF string is 127.
	\return '1' on success and '0' if error
	 */
	int8_t VideoCallDMTF(const char* DMTF_str);

	#endif

	//!*****************************************************************
	//!FTP functions
	#if FTP_FUSE

	//! Configures the connection to the FTP server
	/*!
	\param const char* server: string with the server domain or IP
	\param const char* port:string with the FTP port
	\param const char* user_name:string with the user name
	\param const char* password:string with the FTP password
	\param uint8_t mode:FTP mode (active or passive)
	\param const char* type:string with the FTP type (ASCII or Binary)
	\return '1' on success,
		'-2' if error setting the connection parameters (APN),
		'-3' if error setting the FTP server ('-13' if CME error available),
		'-4' if error setting the FTP port ('-14' if CME error available),
		'-5' if error setting the FTP mode ('-15' if CME error available),
		'-6' if error setting the FTP type ('-16' if CME error available),
		'-7' if error setting the user name ('-17' if CME error available)
		'-8' if error setting the FTP password ('-18' if CME error available)
	 */
	int8_t configureFTP(	const char* server,
							const char* port,
							const char* user_name,
							const char* password,
							uint8_t mode,
							const char* type);

	//!  Uploads a file from 3G board to FTP server
	/*!
	\param const char* destination_path: path in the FTP server where uploads the file
	\param uint8_t origin: The directory to where is file .
		0 – current directory,
		1 – “C:/Picture” directory,
		2 – “C:/Video” directory,
		3 – “C:/VideoCall” directory,
		4 – “D:/Picture” directory,
		5 – “D:/Video” directory,
		6 – “D:/VideoCall” directory,
		7 – “C:/Audio” directory,
		8 – “D:/Audio” directory
	\return '1' on success,
		'0' if error,
		'-2' if error with CME code (FTP errors)
	 */
	int8_t uploadFile(uint8_t origin, const char* destination_path);

	//!  Downloads a file from FTP server to 3G board
	/*!
	\param const char* origin_path: path in the FTP server where the file to download is located
	\param uint8_t destination: The directory to save the downloaded file . 0 – current directory,
		1 – “C:/Picture” directory,
		2 – “C:/Video” directory,
		3 – “C:/VideoCall” directory,
		4 – “D:/Picture” directory,
		5 – “D:/Video” directory,
		6 – “D:/VideoCall” directory,
		7 – “C:/Audio” directory,
		8 – “D:/Audio” directory
	\param uint16_t max_time: value of time out in secods to donwload the file
	\return '1' on success,
		'0' if error,
		'-2' if error with CME code (FTP errors)
		'-3' if error getting the file of the size to upload
	 */
	int8_t downloadFile(const char* origin_path, uint8_t destination, unsigned long max_time);

	//!  Uploads a file from Waspmote to FTP server
	/*!
	\param const char* SD_file: path in the Waspmote's SD with the file
	\param const char* destination_path: path in the FTP server where uploads the file
	\return '1' on success,
		'0' if error,
		'-2' if error with CME code (FTP error)
		'-3' if error getting ile size from SD
	 */
	int8_t uploadData(const char* SD_file, const char* destination_path);

	//!  Downloads a file to Waspmote from FTP server
	/*!
	\param const char* FTP_file: path in the FTP server with the file
	\param const char* destination_path: path in the Waspmote's SD where uploads the file
	\return '1' on success,
		'0' if error,
		'-2' if error with CME code (FTP error)
		'-3' if error sending the file from 3G module to Waspmote SD
	 */
	int8_t downloadData(const char* FTP_file, const char* destination_path);

	//!  Gets the file size from an FTP server
	/*!
	\param const char* FTP_file: path in the FTP server with the file
	\return the size of the file or '-1' if error with CME code (FTP error)
	 */
	unsigned long getFTPsize(const char* FTP_file);

	//! Acquires the SSL stack and logs into the FTPS server
	/*!
	\param const char* server: string with the server domain or IP
	\param uint16_t port: string with the FTP port
	\param const char* user_name: string with the user name
	\param const char* password: string with the FTP password
	\return '1' on success,
		'-2' if error setting the connection parameters (APN),
		'-3' if error acquiring the SSL stack,
		'-4' error login into the server,
		'-5' if timeout when logs in
	 */
	int8_t loginFPTS(	const char* server,
						uint16_t port,
						const char* user_name,
						const char* password);

	//!  Uploads a file from 3G board to FTP server
	/*!
	\param const char* destination_path: path in the FTP server where uploads the file
	\param uint8_t origin: The directory to where is file .
		0 – current directory,
		1 – “C:/Picture” directory,
		2 – “C:/Video” directory,
		3 – “C:/VideoCall” directory,
		4 – “D:/Picture” directory,
		5 – “D:/Video” directory,
		6 – “D:/VideoCall” directory,
		7 – “C:/Audio” directory,
		8 – “D:/Audio” directory
	\return '1' on success, '0' if error, '-2' if error with CME code (FTP errors)
	 */
	int8_t uploadFileSecure(uint8_t origin, const char* destination_path);

	//!  Downloads a file from FTP server to 3G board
	/*!
	\param const char* origin_path: path in the FTP server where the file to download is located
	\param uint8_t destination: The directory to save the downloaded file .
		0 – current directory,
		1 – “C:/Picture” directory,
		2 – “C:/Video” directory,
		3 – “C:/VideoCall” directory,
		4 – “D:/Picture” directory,
		5 – “D:/Video” directory,
		6 – “D:/VideoCall” directory,
		7 – “C:/Audio” directory,
		8 – “D:/Audio” directory
	\return '1' on success,
		'0' if error,
		'-2' if error with CME code (FTP errors)
		'-3' if error getting the file of the size to upload
	 */
	int8_t downloadFileSecure(const char* origin_path, uint8_t destination, uint16_t max_time);

	//!  Uploads a file from Waspmote to FTP server
	/*!
	\param const char* SD_file: path in the Waspmote's SD with the file
	\param const char* destination_path: path in the FTP server where uploads the file
	\return '1' on success,
		'0' if error,
		'-2' if error with CME code (FTP error)
		'-3' if error getting ile size from SD
	 */
	int8_t uploadDataSecure(const char* SD_file, const char* destination_path);

	//!  Downloads a file to Waspmote from FTP server
	/*!
	\param const char* FTP_file: path in the FTP server with the file
	\param const char* destination_path: path in the Waspmote's SD where uploads the file
	\return '1' on success,
		'0' if error,
		'-2' if error with CME code (FTP error)
		'-3' if error sending the file from 3G module to Waspmote SD
	 */
	int8_t downloadDataSecure(const char* FTP_file, const char* destination_path, uint16_t max_time);

	//! Logs out the FTPS server and releases the SSL stack
	/*!
	\return '1' on success,
		'-2' if error logging out of the server
		'-3' if error releasing the SSL stack
	*/
	int8_t logoutFPTS();
	#endif

	//!*****************************************************************
	//!SMTP and POP3 functions
	#if MAIL_FUSE

	//! Sets the SMTP server, port, username and password
	/*!
	\param const char* server: string with the server domain or IP
	\param uint16_t port:string with the SMTP port
	\param const char* username: string with the username
	\param const char* password: string with the password
	\return '1' on success, '0' if error setting username and password
		and '-1' if error setting server and port
	 */
	int8_t setSMTPserver(const char* server, uint16_t port, const char* username, const char* password);

	//! Sets the SMTP server and port
	/*!
	\param const char* server: string with the server domain or IP
	\param uint16_t port:string with the FTP port
	\return '1' on success, '0'  if error setting server and port
	 */
	int8_t setSMTPserver(const char* server, uint16_t port);

	//! Sets sender address and name
	/*!
	\param const char* mail_address: string with the sender mail address
	\param const char* name:string with the sender name
	\return '1' on success, '0'  if error
	 */
	int8_t setSMTPfrom( const char* mail_address, const char* name);

	//! Sets recipient address and name (TO/CC/BCC)
	/*!
	\param uint8_t kind: '0' TO (normal recipient), '1' CC (carbon Copy recipient),
		'2' BCC (blind Carbon Copy recipient)
	\param uint8_t index: from 0 to 4
	\param const char* mail_address: string with the mail address
	\param const char* name:string with the recipient name
	\return '1' on success, '0'  if error
	 */
	int8_t setSMTPrecipient(uint8_t kind, uint8_t index, const char* mail_address, const char* name);

	//! Sets the subject of the email
	/*!
	\param const char* subject: string with the subject of the email
	\return '1' on success, '0'  if error
	 */
	int8_t setSMTPsubject( const char* subject);

	//! Sets the body of the email
	/*!
	\param const char* subject: string with the body of the email
	\return '1' on success, '0'  if error
	 */
	int8_t setSMTPbody( const char* body);

	//! Add attachments to the email
	/*!
	\param uint8_t index: index of the attachment from 1 to 10
	\param uint8_t file: name of a file which is under current directory
	\return '1' on success, '0'  if error
	 */
	int8_t setSMTPattach( uint8_t index, const char* file);

	//! Sends the email
	/*!
	\return '1' on success, '0' if error setting the apn, '-3' if error setting the apn with cme error code available
		and '-2' error sendig the email
	 */
	int8_t setSMTPsend();


	//! Sets the POP3 server, port, username and password
	/*!
	\param const char* server: string with the server domain or IP
	\param uint16_t port: POP3 port
	\param const char* username: string with the username
	\param const char* password: string with the password
	\return '1' on success, '0' if error setting the apn, '-3' if error setting the apn with cme error code available
		and '-2' error setting the parameters of POP3 server
	 */
	int8_t setPOP3server(const char* server, uint16_t port, const char* username, const char* password);

	//! Gets the e-mail number and total size
	/*!
	\return the total number of emails, '-2' if error logging in the POP3 server
		and '-3' if error getting the e-mail number
	 */
	int getPOP3list();

	//! Gets the header of the e-mail specified in index and returns it in 'buffer_3G'
	/*!
	\param uint8_t index: index of the e-mail
	\return '1' on success, '-1' if error logging in the POP3 server
		and '-2' if error getting the header of the e-mail
	 */
	int8_t getPOP3header(uint8_t index);

	//! Gets the e-mail specified in index
	/*!
	\param uint8_t index: index of the e-mail
	\return '1' on success, '-1' if error logging in the POP3 server
		and '-2' getting the e-mail
	 */
	int8_t getPOP3mail(uint8_t index);

	//! Marks an e-mail to delete from POP3 server
	/*!
	\param uint8_t index: index of the e-mail
	\return '1' on success, '-1' if error logging in the POP3 server
		and '-2' if error deleting the e-mail
	 */
	int8_t deletePOP3mail(uint8_t index);

	#endif

	//!*****************************************************************
	//!HTTP and HTTPS functions
	#if HTTP_FUSE

	//! Sends a request to a HTTP url and get an answer. The answer is stored in 'buffer_3G'
	/*!
	\param const char* url: server to send the HTTP request. "www.http_server.com"
	\param uint16_t port: number of the connection port
	\param const char* HTTP_request: request to send to the HTTP server
	\return '1' on success
		'0' if no connection
		'-1' if error setting APN, username and password
		'-2' if error opening a HTTP session
		'-3' if error receiving data or timeout waiting data
		'-4' if error changing the baudrate (data received is OK)
		'-5' if unknown error for HTTP
		'-6' if HTTP task is busy
		'-7' if fail to resolve server address
		'-8' if HTTP timeout
		'-9' if fail to transfer data
		'-10' if memory error
		'-11' if invalid parameter
		'-12' if network error
		'-15' if error setting APN, username and password with CME_error code available
		'-16' if error opening a HTTP session with CME_error code available
		'-20' if error checking the connection
	*/
	int16_t readURL(const char* url, uint16_t port, const char* HTTP_request);

	//! Sends a request to a HTTP url and get an answer. The answer is stored in 'buffer_3G'
	/*!
	\param const char* url: server to send the HTTP request. "www.http_server.com"
	\param uint16_t port: number of the connection port
	\param const char* HTTP_request: request to send to the HTTP server
	\return '1' on success
		'0' if no connection
		'-1' if error setting APN, username and password
		'-2' if error opening a HTTP session
		'-3' if error receiving data or timeout waiting data
		'-4' if error changing the baudrate (data received is OK)
		'-5' if unknown error for HTTP
		'-6' if HTTP task is busy
		'-7' if fail to resolve server address
		'-8' if HTTP timeout
		'-9' if fail to transfer data
		'-10' if memory error
		'-11' if invalid parameter
		'-12' if network error
		'-15' if error setting APN, username and password with CME_error code available
		'-16' if error opening a HTTP session with CME_error code available
		'-17' if url response its not OK (HTTP code 200)
		'-18' if content-length field not found
		'-19' if data field not found
		'-20' if error checking the connection
	*/
	int16_t readURL(const char* url, uint16_t port, const char* HTTP_request, bool parse);

	//! Sets the time of Waspmote's RTC getting the time from an HTP server
	/*!
	\return '1' on success
		'0' if no connection
		'-1' if error setting APN, username and password,
		'-2' if error checking the connection
		'-3' if error adding the HTP server
		'-4' if error reading the time from 3G's RTC
		'-5' HTP Unknown error
		'-6' HTP Wrong parameter
		'-7' HTP Wrong date and time calculated
		'-8' HTP Network error
		'-15' if error setting APN, username and password with CME_error code available
	*/
	int16_t setTimebyURL(const char* htp_server, uint16_t htp_port);

	//! Sets the time of Waspmote's RTC getting the time from Meshlium
	/*!
	\param const char* url : url or IP address of the server
	\param uint16_t port : server port
	\return '1' on success,
		'0' if no connection
		'-1' if error setting APN, username and password,
		'-2' if error opening a HTTP session,
		'-3' if error receiving data or timeout waiting data,
		'-4' if error changing the baudrate (data received is OK),
		'-5' if unknown error for HTTP,
		'-6' if HTTP task is busy,
		'-7' if fail to resolve server address,
		'-8' if HTTP timeout,
		'-9' if fail to transfer data,
		'-10' if memory error,
		'-11' if invalid parameter,
		'-12' if network error,
		'-15' if error setting APN, username and password with CME_error code available
		'-16' if error opening a HTTP session with CME_error code available
		'-17' if url response its not OK (HTTP code 200)
		'-18' if content-length field not found
		'-19' if data field not found
		'-20' if error checking the connection

	*/
	int16_t setTimebyMeshlium(const char* url, uint16_t port);

	//! Sends a frame to Meshlium and get an answer. The answer is stored in 'buffer_3G'
	/*!
	\param const char* url : url or IP address of the server
	\param uint16_t port : server port
	\param uint8_t* data : frame data to send
	\param int length : length of the frame
	\param uint8_t method : GET or POST
	\return '1' on success,
		'0' if no connection
		'-1' if error setting APN, username and password,
		'-2' if error opening a HTTP session,
		'-3' if error receiving data or timeout waiting data,
		'-4' if error changing the baudrate (data received is OK),
		'-5' if unknown error for HTTP,
		'-6' if HTTP task is busy,
		'-7' if fail to resolve server address,
		'-8' if HTTP timeout,
		'-9' if fail to transfer data,
		'-10' if memory error,
		'-11' if invalid parameter,
		'-12' if network error,
		'-15' if error setting APN, username and password with CME_error code available
		'-16' if error opening a HTTP session with CME_error code available
		'-17' if url response its not OK (HTTP code 200)
		'-18' if content-length field not found
		'-19' if data field not found
		'-20' if error checking the connection
	*/
	int16_t sendHTTPframe(const char* url, uint16_t port, uint8_t* data, int length, uint8_t method );

	//! Sends a frame to Meshlium and get an answer. The answer is stored in 'buffer_3G'
	/*!
	\param const char* url : url or IP address of the server
	\param uint16_t port : server port
	\param uint8_t* data : frame data to send
	\param int length : length of the frame
	\param uint8_t method : GET or POST
	\param uint8_t parse : '1' parses the answer for the Meshlium and '0' for raw data
	\return '1' on success
		'0' if no connection
		'-1' if error setting APN, username and password
		'-2' if error opening a HTTP session
		'-3' if error receiving data or timeout waiting data
		'-4' if error changing the baudrate (data received is OK)
		'-5' if unknown error for HTTP
		'-6' if HTTP task is busy
		'-7' if fail to resolve server address
		'-8' if HTTP timeout
		'-9' if fail to transfer data
		'-10' if memory error
		'-11' if invalid parameter
		'-12' if network error
		'-15' if error setting APN, username and password with CME_error code available
		'-16' if error opening a HTTP session with CME_error code available
		'-17' if url response its not OK (HTTP code 200)
		'-18' if content-length field not found
		'-19' if data field not found
		'-20' if error checking the connection
	*/
	int16_t sendHTTPframe(const char* url, uint16_t port, uint8_t* data, int length, uint8_t method, uint8_t parse );

	//! Sends a request to a HTTPS url and get an answer. The answer is stored in 'buffer_3G'
	/*!
	\param const char* url: server to send the HTTPS request. "www.https_server.com"
	\param uint16_t port: number of the connection port
	\param const char* HTTPS_request: request to send to the HTTPS server
	\return '1' on success,
		'-1' if unknown error,
		'-2' if 3G module is busy,
		'-3' if server closed,
		'-4' if timeout,
		'-5' if transfer failed,
		'-6' if memory error,
		'-7' if invalid parameter,
		'-8' if network error,
		'-10' if error setting APN, username and password
		'-11' if error acquiring HTTPS protocol stack,
		'-12' if error opening a HTTPS session,
		'-13' if error changing baudrate,
		'-14' if error storing HTTPS request in the output buffer,
		'-15' if error sending the HTTPS request to the url,
		'-16' if error with the receive command,
		'-17' if error closing the session (data received is OK),
		'-18' if error releasing the SSL stack (data received is OK),
		'-19' if error changing the baudrate (data received is OK),
		'-20' if error receiving data or timeout waiting data and
		'-25' if error setting username and password with CME_error code available
		'-31' HTTPS error code: unknown error
		'-32' HTTPS error code: busy
		'-33' HTTPS error code: server closed
		'-34' HTTPS error code: timeout
		'-35' HTTPS error code: transfer failed
		'-36' HTTPS error code: memory error
		'-37' HTTPS error code: invalid parameter
		'-38' HTTPS error code: network error
	*/
	int8_t readURLS(const char* url, uint16_t port, const char* HTTPS_request);
	#endif

	//!*****************************************************************
	//!GPS functions
	#if GPS_FUSE

	//! Starts GPS in stand-alone mode
	/*!
	\return '1' if success, '0' if error, '-4' if error starting the GPS
	 */
	int8_t startGPS();

	//! Starts and configures the GPS
	/*!
	\param uint8_t mode:	'1' for stand-alone mode,
							'2' for UE-based mode
							'3' for UE-assisted mode
	\param const char* GPS_url: string with the server domain or IP
	\param const char* GPS_port:string with the FTP port
	\return '1' if success,
			'0' if error,
			'-2' if error setting the apn,
			'-3' if error setting GPS server and port,
			'-4' if error starting the GPS,
			'-5' if AGPS data are not available
	 */
	int8_t startGPS(int8_t mode, const char* GPS_url, const char* GPS_port);

	int8_t startGPScold();

	int8_t startGPShot();

	//! Stops the GPS
	/*!
	\return '1' if success and '0' if error
	 */
	int8_t stopGPS();

	//! Gets info for GPS if it's available
	/*!
	\return '1' if success, '-2' if info it's not available and '0' if error
	 */
	int8_t getGPSinfo();

	//! Enables to start GPS automatic when module power on
	/*!
	\return '1' if success, '0' if error
	*/
	int8_t enableAutoGPS();

	//! Disables to start GPS automatic when module power on
	/*!
	\return '1' if success, '0' if error
	*/
	int8_t disableAutoGPS();

	float convert2Degrees(char* input);

	//! Sets the time of Waspmote's RTC getting the time from GPS
	/*!
	\param unsigned long waiting_time:	waiting time for fix the GPS satellites
	\param bool state: state of the GPS engine:'1', the GPS engine is stopped
												'0', the GPS engine is started
	\return '1' if success,
			'-1' if error starting the GPS module
			'-2' if timeout waiting for GPS data
			'-3' if error setting the RTC time of the 3G module
	 */
	int8_t setTimebyGPS(unsigned long waiting_time, bool state);

	#endif

	//!*****************************************************************
	//!TCP/UDP functions
	#if IP_FUSE

	//! It configures 3G connection with login, password and some other parameters to use TCP or UDP connections in non-transparent mode
    /*!
	It takes the configuration parameters from 'Wasp3G.cpp' file
	\return '1' on success, '-2' if error dettaching the connection, '-10' if error dettaching the connection with CME code available,
		'-3' if error attaching the connection, '-11' if error attaching the connection with CME code available,
		'-4' if waiting time for connection have expired, '-5' if error setting the APN,
		'-6' if error setting the user name and the password, '-12' if error setting the user name and the password with CME code available,
		and '-7' if error configurating IP parameters
	 */
	int8_t configureTCP_UDP();



	//! It closes all sockets opened
    /*!
	\return '1' on success, '0' if error and '-2' if error with IP error code available
	 */
	int8_t closeSocket();

	//! It configures the 3G module to use multi client mode or UDP client and opens the network
    /*!
	\param uint8_t mode :  MULTI_CONNECTION or UDP_CLIENT
	\return '1' on success, '-2' if error opening the network,
		'-3' if error opening the network with CME error code available
		'-4' if error opening the network with IP error code available
		'-5' if error opening the TCP connection or starting the TCP server
		and '-6' if error opening the TCP connection or starting the TCP server with IP error code available
	*/
	int8_t createSocket(uint8_t mode);

	//! It configures the 3G module to use the TCP server and opens the network
    /*!
	\param uint8_t mode : TCP_SERVER
	\param const char* port : the PORT to open a socket to
	\return '1' on success, '-2' if error opening the network,
		'-3' if error opening the network with CME error code available
		'-4' if error opening the network with IP error code available
		'-5' if error opening the TCP connection or starting the TCP server
		and '-6' if error opening the TCP connection or starting the TCP server with IP error code available
	*/
	int8_t createSocket(uint8_t mode, uint16_t port);

	//! It configures the 3G module for TCP and UDP and opens the network
    /*!
	\param uint8_t mode : TCP_CLIENT, UDP_CLIENT, TCP_SERVER or MULTI_CONNECTION
	\param const char* ip : the IP to open a socket to
	\param const char* port : the PORT to open a socket to
	\return '1' on success, '-2' if error opening the network,
		'-3' if error opening the network with CME error code available
		'-4' if error opening the network with IP error code available
		'-5' if error opening the TCP connection or starting the TCP server
		and '-6' if error opening the TCP connection or starting the TCP server with IP error code available
	*/
	int8_t createSocket(uint8_t mode, const char* ip, uint16_t port);

	//! It opens a UDP port to listen in multi client mode
    /*!
	\param uint8_t n_link : number of the connection (0-9)
	\param uint16_t local_port : the local port for listen
	\return '1' on success, '0' if error, '-2' if not configured in multi client mode,
		'-3' if network is closed, '-4' error opening the connection with CME error code available
		and '-5' error opening the connection with IP error code available
	*/
	int8_t createMultiSocket(uint8_t n_link, uint16_t local_port);

	//! It creates a TCP/IP connection to the specified IP and PORT in multi client mode
    /*!
	\param uint8_t n_link : number of the connection (0-9)
	\param const char* serverIP : the server IP
	\param uint16_t server_port : the server port
	\return '1' on success, '0' if error, '-2' if not configured in multi client mode,
		'-3' if network is closed, '-4' error opening the connection with CME error code available
		and '-5' error opening the connection with IP error code available
	*/
	int8_t createMultiSocket(uint8_t n_link, const char* serverIP, uint16_t server_port);

	//! It sends the data througth a socket (TCP in single connection)
    /*!
	\param const char* data : the data to send
	\return '1' on success, '0' if error, '-2' if error with CME error code available
		and '-3' if error with IP error code available
	*/
	int8_t sendData(const char* data);

	//! It sends the data througth a socket (TCP in multiple connection)
    /*!
	\param uint8_t n_link : number of the connection (0-9)
	\param const char* data : the data to send
	\return '1' on success, '0' if error, '-2' if error with CME error code available
		and '-3' if error with IP error code available
	*/
	int8_t sendData(uint8_t n_link, const char* data);

	//! It sends the data througth a socket (UDP in single connection)
    /*!
	\param const char* data : the data to send
	\param const char* ip : the server's IP
	\param uint16_t port : the server port
	\return '1' on success, '0' if error, '-2' if error with CME error code available
		and '-3' if error with IP error code available
	*/
	int8_t sendData(const char* data, const char* ip, uint16_t port);

	int8_t sendData(uint8_t n_link, const char* data, const char* ip, uint16_t port);

	//! It sends the data througth a socket (TCP in single connection with data length include)
    /*!
	\param const char* data : the data to send
	\return '1' on success, '0' if error, '-2' if error with CME error code available
		and '-3' if error with IP error code available
	*/
	int8_t sendData(uint8_t* data, int16_t length);

	//! It sends the data througth a socket (TCP in multiple connection with data length include)
    /*!
	\param uint8_t n_link : number of the connection (0-9)
	\param const char* data : the data to send
	\return '1' on success, '0' if error, '-2' if error with CME error code available
		and '-3' if error with IP error code available
	*/
	int8_t sendData(uint8_t n_link, uint8_t* data, int16_t length);

	//! It sends the data througth a socket (UDP in single connection with data length include)
    /*!
	\param const char* data : the data to send
	\param const char* ip : the server's IP
	\param uint16_t port : the server port
	\return '1' on success, '0' if error, '-2' if error with CME error code available
		and '-3' if error with IP error code available
	*/
	int8_t sendData(uint8_t* data, const char* ip, uint16_t port, int16_t length);

	//! It sends the data througth a socket (base function)
    /*!
	\param uint8_t n_link : number of the connection (0-9)
	\param const char* data : the data to send
	\param const char* ip : the server's IP
	\param uint16_t port : the server port
	\return '1' on success, '0' if error, '-2' if error with CME error code available
		and '-3' if error with IP error code available
	*/
	int8_t sendData(uint8_t n_link, uint8_t* data, const char* ip, uint16_t port, int16_t length);

	//! It closes a socket opened with createMultiSocket in multi client mode
    /*!
	\param uint8_t n_link : number of the connection (0-9)
	\return '1' on success, '0' if error, '-2' if error with CME error code available
		and  '-3' if error with IP error code available
	*/
	int8_t closeMultiSocket(uint8_t n_link);

	//! It manages the IP data from the 3G module. Stores the IP address from the sender in IP_dir and the data in 'buffer_3G'.
    /*!
	\return '1' on success, '0' if error and '-2' if error with CME error code available
	*/
	int16_t readIPdata();

	//! It lists the clients connected to the module
    /*!
	\return '1' on success, '0' if error and '-2' if error with IP error code available
	*/
	int8_t listClients();

	//! It opens the connection from a client to the module
    /*!
	\param uint8_t n_client: number of the client
	\return '1' on success, '0' if error and '-2' if error with IP error code available
	*/
	int8_t openClient(uint8_t n_client);

	//! It closes a client connected to the module
    /*!
	\param uint8_t n_client: number of the client connected to the module
	\return '1' on success, '0' if error and '-2' if error with IP error code available
	*/
	int8_t closeClient(uint8_t n_client);

	//! It gets the IP address assigned to the module and stores it in 'buffer_3G'
    /*!
	\return '1' on success, '0' if error and -2 if error with IP error code available
	*/
	int8_t getIP();

	//! It queries the domain name from IP address and stores it in 'buffer_3G'
    /*!
	\param const char* ip: IP address for query the domain name
	\return '1' on success, '0' if error
	*/
	int8_t QueryDomainfromIP(const char* ip);

	//! It queries the IP address from domain name and stores it in 'buffer_3G'
    /*!
	\param const char* domain: domain name for query the IP
	\return '1' on success, '0' if error
	*/
	int8_t QueryIPfromDomain(const char* domain);

	#endif

	//!*****************************************************************
	//! Xmodem functions

		//! It gets a file from 3G/GPRS Board and stores it in Waspmote
    /*!
	\param const char* origin: the name of the file in the 3G/GPRS module
	\param const char* destiny: the path of the file to store the file
	\return '1' if succes, '0' if error, '-2' if error going to root directory in Waspmote's SD, '-3' if error creating the file in Waspmote,
		-4' if error if file not exist in 3G/GPRS module and '-5' if error getting the file
	*/
	int8_t getXModemFile(const char* origin, const char* destiny);

	//! It sends a file from Waspmote and stores it in 3G/GPRS Board
    /*!
	\param const char* origin: the name of the file in the SD
	\param const char* destiny: the path of the file to store the file
	\return '1' if succes,
		'0' if error,
		'-2' if error sending de data
		'-4' if error going to root directory in Waspmote's SD,
		'-5' if error reading the size of the file,
		'-6' if error opnening the file
		'-7' if error reading the file
	*/
	int8_t sendXModemFile(const char* origin, const char* destiny);

	//!*****************************************************************
	//! File system functions

	//! It goes to the root of the desired unit (0 for C internal memory and 1 for the microSD card)
	/*!
	\param uint8_t unit: selects the unit to work, 0 for C internal memory and 1 for the microSD card
	\return '1' if succes, '-2' if error changing the unit or '0' if error going to the root
	*/
	int8_t goRoot(uint8_t unit);

	//! It changes the directory in the actual unit
	/*!
	\param const char* path: directory in the actual unit
	\return  '1' if success and '0' if error
	*/
	int8_t cd(const char* path);

	//! Gets the size of a given file name in the current directory
	/*!
	\param const char* filename: the name of the file to get the size
	\return  the file_size if success and '-2' if error
	*/
	long getFileSize(const char* filename);

	//! Deletes a file in the current directory
	/*!
	\param const char* filename: the name of the file to delete
	\return '1' if success and '0' if error
	*/
	int8_t del(const char* filename);

	//!  Checks if microSD card is available
	/*!
	\return  '1' if is present and '0' if not
	*/
	int8_t isSD();

	//!  Stores in 'buffer_3G' a list of subdirectories and files in the current directory
	/*!
	\param uint8_t type: select the kind of list; '0' list both subdirectories and files,
		'1' list subdirectories only and '2' list files only
	\return '1' if success, '2' if no files or subdirectories and '0' if error
	*/
	int8_t ls(int8_t type);


	//!*****************************************************************
	//! Various functions

	//! Gets RSSI level
    /*!
	\return the value in -dBm or '0' if error
	 */
	int8_t getRSSI();

	//! Gets cell system information. Only in GSM. Information is stored in 'buffer_3G'
    /*!
	\return '1' on success, '0' if error, '-1' if timeout and '-2' if error restoring the baudrate (data are valid)
	 */
	int8_t getCellsysInfo();

	//! Gets cell channel information. Only during a GSM call. Information is stored in 'buffer_3G'
    /*!
	\return '1' on success, '0' if error
	 */
	int8_t getCellchannel();

	//! Gets serving cell radio parameters. Only during a GSM call. Information is stored in 'buffer_3G'
    /*!
	\return '1' on success, '0' if error
	 */
	int8_t getCellradioparam();

	//! Sets preferred service domain selection
	/*!
	\param uint8_t mode: '0' for CS Only, '1' for PS Only and '2' for CS + PS
	\return '1' on success, '0' if error
	*/
	int8_t setPreferedServiceDomain(uint8_t mode);

	//! Scans the network band channels specified
	/*!
	\param int chn_start: starting channel
	\param int chn_end: ending channel
	\param bool mode: output type. '0' verbose response, '1' only numeric data
	\return '1' on success, '0' if error
	*/
	int8_t scanNetworkchannels(int chn_start, int chn_end, bool mode);

	//! It inquires UE system information. Information is stored in 'buffer_3G'
    /*!
	\return '1' on success, '0' if error
	 */
	int8_t getUEsysInfo();

	//! It shows network system mode.
    /*!
	\return '0' if error, '-1' if error with CME error code available, '1'for no service,
		'2' for GSM, '3' for GPRS, '4' for EGPRS (EDGE), '5' for WCDMA,
		'6' for HSDPA only, '7' for HSUPA only and '8' for HSPA (HSDPA and HSUPA)
	 */
	int8_t showsNetworkMode();

	//! It shows the mobile phone system information in WCDMA.
    /*!
	\return '1' on success, '0' if error
	 */
	int8_t WCDMAsysInfo();

	//! It sets network system mode preference.
    /*!
	\param uint8_t mode : '0' for automatic, '1' for GSM only and '2' for WCDMA only
	\return '1' on success, '0' if error
	 */
	int8_t setNetworkMode(uint8_t mode);

	//! Sets the band preference.
    /*!
	\param int high_band: '128' for GSM_DCS_1800, '256' for GSM_EGSM_900 and '512' for GSM_PGSM_900
	\param int mid_band: '1' for GSM_450, '2' for GSM_480, '4' for GSM_750, '8' for GSM_850, '16' for GSM_RGSM_900, '32' for GSM_PCS_1900,
		'64' for WCDMA_IMT_2000, '128' for WCDMA_PCS_1900, '256' for WCDMA_III_1700, '512' for WCDMA_IV_1700, '1024' for WCDMA_850 and
		'2048' for WCDMA_800.
	\param int low_band: '1' for WCDMA_VII_2600, '2' for WCDMA_VIII_900 and '4' for WCDMA_IX_1700
	\return '1' if success and '0' if error
*/
	int8_t setNetworkBand(int high_band, int mid_band, int low_band);

	//! It sets the preferences for order of acquisitions
    /*!
	\param uint8_t mode : '0' for automatic,'1' GSM,WCDMA and '2' for WCDMA,GSM
	\return '1' on success, '0' if error
	 */
	int8_t modeAcquisitionsOrder(uint8_t mode);

	//! It selects the storage location
    /*!
	\param uint8_t destination : '0' for 3G module and '1' for SD of 3G module
	\return '1' on success, '0' or '-2' if error
	 */
	int8_t selectStorage(uint8_t destination);

	//! It changes the baudrate between Waspmote and 3G module
    /*!
	\param long baudrate : new baudrate
	\return '1' on success, '0' or '-2' if error
	 */
	int8_t changeBaudrate(long baudrate);

	//! It sends any AT command to the 3G module
    /*!
	\param char* ATcommand : the command to send to the 3G module
	\return '1' on success, '0' if error. The answer is stored into 'buffer_3G'
	 */
	uint8_t sendATCommand(const char* ATcommand);

	//! Selects speaker or loudspeaker output for calls
    /*!
	\param uint8_t output : '0' for speaker and '1' for loudspeaker
	\return '1' on success, '0' if error
	 */
	int8_t	selectAudioOutput(uint8_t output);

	//! Controls the gain level of the microphone
	//! Mute only can be used into a call
    /*!
	\param uint8_t gain : '0' for mute and '1' to '16' for gain level
	\return '1' on success, '0' if error
	 */
	int8_t micGain(uint8_t gain);

	//! Sets loudspeaker volume
    /*!
	\param uint8_t level: '0' for mute and '1' to '5' for volume level
	\return '1' on success, '0' if error
	 */
	int8_t loudspeakerLevel(uint8_t volume);

	//! It gets the model of the module and saves it in 'buffer_GPRS'
    /*!
	\return '1' on success, '0' if error
	 */
	int8_t whoamI();

	//! It gets the firmware version of the module and saves it in 'buffer_GPRS'
    /*!
	\return '1' on success, '0' if error
	 */
	int8_t firmware_version();

	//! Sets the apn from operator
    /*!
	\param char* apn: apn from operator
	\return nothing
	 */
	void set_APN( char* apn);

	//! Sets the apn, login and password from operator
    /*!
	\param char* apn: apn from operator
	\param char* login: login from operator
	\param char* password: password from operator
	\return nothing
	 */
	void set_APN( char* apn, char* login, char* password);

	//! It shows the apn, login and password constants
    /*!
	\return '1' on success, '0' if error
	 */
	void show_APN();

	#if TRANSMISSION_FUSE

	//! Uploads a file to a FTP using the WiFi connection
    /*!
	\param char* origin_path: the name of the file in the 3G/GPRS module
	\param char* destiny_name: the path of the file to store the file
	\param char* FTP_server: string with the server domain or IP
	\param uint16_t FTP_port: FTP port
	\param uint8_t FTP_mode: FTP mode (active or passive)
	\param char* FTP_username: string with the user name
	\param char* FTP_password: string with the FTP password
	\param uint8_t auth_type: secure mode of the WiFi network
	\param char* auth_key: string with the authentication key of the WiFi network
	\param char* SSID: string with the SSID of the WiFi network
	\return '1' if success, '-2' if error setting the connection options, '-3' if error setting the DHCP options
		'-4' if error setting FTP parameters, '-5' if error setting authentification key, '-6' if error setting the join mode
		'-7' if error joining to the Wi-Fi network, '-8' if error opening the FTP session and '-9' if error uploading the file
	*/
	int8_t sendFiletoWiFiFTP(char* origin_path, char* destiny_name, char* FTP_server, uint16_t FTP_port, uint8_t FTP_mode, char* FTP_username, char* FTP_password, uint8_t auth_type, char* auth_key, char* SSID);

	//! Uploads a file to a FTP server
    /*!
	\param uint8_t origin: The directory to where is file . 0 – current directory, 1 – “C:/Picture” directory, 2 – “C:/Video” directory,
		3 – “C:/VideoCall” directory, 4 – “D:/Picture” directory, 5 – “D:/Video” directory, 6 – “D:/VideoCall” directory, 7 – “C:/Audio” directory,
		8 – “D:/Audio” directory
	\param const char* destination_path: the path of the file to store the file
	\param const char* FTP_server: string with the server domain or IP
	\param const char* FTP_port:string with the FTP port
	\param uint8_t FTP_mode:FTP mode (active or passive)
	\param const char* FTP_username:string with the user name
	\param const char* FTP_password:string with the FTP password
	\return '1' on success,'-2' if error setting the connection parameters (APN), '-3' if error setting the FTP server ('-13' if CME error available),
		'-4' if error setting the FTP port ('-14' if CME error available), '-5' if error setting the FTP mode ('-15' if CME error available),
		'-6' if error setting the FTP type ('-16' if CME error available), '-7' if error setting the user name ('-17' if CME error available),
		'-8' if error setting the FTP password ('-18' if CME error available), '-20' if error uploading the file, '-22' if error with CME code (FTP error) and
		'-23' if error getting the file of the size to upload.
	*/
	int8_t sendFileto3GFTP(uint8_t origin, const char* destination_path, const char* FTP_server, const char* FTP_port, uint8_t FTP_mode, const char* FTP_username, const char* FTP_password);

	//! Sends a file attached into an email
    /*!
	\param const char* SMTP_server: string with the server domain or IP
	\param uint16_t SMTP_port:string with the SMTP port
	\param const char* STMP_account: string with the username
	\param const char* STMP_password: string with the password
	\param const char* sender_address: string with the sender mail address
	\param const char* sender_name:string with the sender name
	\param const char* recipient_address: string with the mail address
	\param const char* recipient_name:string with the recipient name
	\param const char* subject: string with the body of the email
	\param const char* body: string with the subject of the email
	\param uint8_t index: index of the attachment from 1 to 10
	\param uint8_t picture_name: name of a file which is under current directory
	\return  '1' if success, '0' if error setting username and password, '-1' if error setting server and port, '-2' if error setting sender address and name,
		'-3' if error setting recipient address and name, '-4' if error setting subject, '-5' if error setting the body, '-6' if error attaching the file
		and '-7' if error sending the email
	*/
	int8_t sendFileto3Gemail(char* SMTP_server, uint16_t SMTP_port, char* STMP_account, char* STMP_password, char* sender_address, char* sender_name, char* recipient_address, char* recipient_name, char* subject, char* body, char* picture_name);

	#endif

	#if OTA_FUSE
	//! It downloads a new OTA file if OTA is necessary
    /*!
	\param const char* FTP_server: string with the server domain or IP
	\param const char* FTP_port:string with the FTP port
	\param const char* FTP_username:string with the user name
	\param const char* FTP_password:string with the FTP password
	\return '1' on success,'-2' if error setting the connection parameters (APN), '-3' if error setting the FTP server ('-13' if CME error available),
		'-4' if error setting the FTP port ('-14' if CME error available), '-5' if error setting the FTP mode ('-15' if CME error available),
		'-6' if error setting the FTP type ('-16' if CME error available), '-7' if error setting the user name ('-17' if CME error available),
		'-8' if error setting the FTP password ('-18' if CME error available), '-19' if error downloading the OTA version file,
		'-21' if error with CME code (FTP error) downloading the OTA version file, '-22' if error sending the OTA version file from 3G module to Waspmote's SD,
		'-23' if there isn't FILE tag, '-24' if there isn't PATH tag, '-25' if there isn't VERSION tag, '-26' if OTA is not necessary,
		'-27' if OTA files are the same program version,'-28' if error downloading the OTA file, '-31' if error with CME code (FTP error) downloading the OTA file
		and '-32' if error sending the OTA file from 3G module to Waspmote's SD.
	*/
	int8_t requestOTA(const char* FTP_server, const char* FTP_port, const char* FTP_username, const char* FTP_password);
	#endif
};

extern Wasp3G _3G;

#endif
