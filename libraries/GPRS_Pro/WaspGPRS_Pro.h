/*! \file WaspGPRS_Pro.h
    \brief Library for managing the SIM900 module
    
    Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.0

    Design:		David Gascón

    Implementation:	Alejandro Gállego

*/

 /*! \def WaspGPRS_Pro_h
    \brief The library flag
    
  */
#ifndef WaspGPRS_Pro_h
#define WaspGPRS_Pro_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>
#include "WaspGPRS_Proconstants.h"

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/


/*! \def GPRS_PRO_ON
    \brief Working mode. ON in this case
 */
#define GPRS_PRO_ON         0

/*! \def GPRS_PRO_FULL
    \brief Working mode. Full functionality
 */
#define GPRS_PRO_FULL         1

/*! \def GPRS_PRO_RF_OFF
    \brief Working mode. The RF part of the module will not work
 */
#define GPRS_PRO_RF_OFF      2

/*! \def GPRS_PRO_MIN
    \brief Working mode. minimum functionality
 */
#define GPRS_PRO_MIN	 3

/*! \def GPRS_PRO_SLEEP
    \brief Working mode. sleep mode
 */
#define GPRS_PRO_SLEEP	 4

/*! \def GPRS_PRO_POWER_OFF
    \brief Working mode. Powers off the voltage of the module
 */
#define GPRS_PRO_POWER_OFF	5

/*! \def ENABLE
 */
#define	ENABLE	1

/*! \def DISABLE
 */
#define	DISABLE	0


/*! \def NORMAL_MODE
    \brief Alert Sound Mode. Normal mode
 */
#define	NORMAL_MODE	0

/*! \def SILENT_MODE
    \brief Alert Sound Mode. Silent mode (all sounds from ME are prevented)
 */
#define	SILENT_MODE	1


/*! \def LEVEL_OFF
    \brief Ringer mode. OFF in this case
 */
#define LEVEL_OFF 0

/*! \def LEVEL_LOW
    \brief Ringer mode. Low level in this case
 */
#define LEVEL_LOW 1

/*! \def LEVEL_MEDIUM
    \brief Ringer mode. Medium level in this case
 */
#define LEVEL_MEDIUM 2

/*! \def LEVEL_HIGH
    \brief Ringer mode. High level in this case
 */
#define LEVEL_HIGH 3

/*! \def LEVEL_CRESCENDO
    \brief Ringer mode. Crescendo in this case
 */
#define LEVEL_CRESCENDO 4



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

/*! \def GPRS_PRO_RATE
    \brief SIM900 Baud Rate
 */
#define	GPRS_PRO_RATE	57600

/*! \def DELAY_ON_SEND
    \brief Constants for AT commands. Delay after every sending attempt in this case
 */
#define DELAY_ON_SEND 250

/*! \def DEFAULT_TIMEOUT
    \brief Constants for AT commands. Default attempts to try in this case (steps of 10ms)
 */
#define DEFAULT_TIMEOUT 1000

/*! \def SEND_ONCE
    \brief Constants for AT commands. Sending only once in this case
 */
#define SEND_ONCE 1

/*! \def PORT_USED
    \brief Constants for AT commands. Port used in AT commands functions in this case
 */
#define PORT_USED  1



/*! \def SINGLE_CONNECTION
    \brief Configures the module to use single connection mode
 */
#define	SINGLE_CONNECTION 0

/*! \def MULTI_CONNECTION
    \brief Configures the module to use multiple connection mode
 */
#define	MULTI_CONNECTION 1

/*! \def UDP_CLIENT
    \brief When opening a socket, it can be opened as client or server. Client in this case
 */
#define	UDP_CLIENT	0

/*! \def TCP_CLIENT
    \brief When opening a socket, it can be opened as client or server. Client in this case
 */
#define	TCP_CLIENT	1

/*! \def TCP_SERVER
    \brief When opening a socket, it can be opened as client or server. Server in this case
 */
#define	TCP_SERVER	2

/*! \def UDP_EXTENDED
    \brief When opening a socket, it can be opened as client or server. Client for extended UDP in this case
 */
#define	UDP_EXTENDED	3



/*! \def NON_TRANSPARENT
    \brief When opening a socket, it can be opened in non transparent mode or transparent mode. Non transparent in this chase
 */
#define	NON_TRANSPARENT 0

/*! \def TRANSPARENT
    \brief When opening a socket, it can be opened in non transparent mode or transparent mode. Transparent in this chase
 */
#define	TRANSPARENT 1



/*! \def GPRS_DATA_LENGTH
    \brief Maximum data length expressed as a string
 */
#define GPRS_DATA_LENGTH "100"

/*! \def GPRS_DATA_LENGTH_U
    \brief Maximum data length expressed as an integer
 */
#define	GPRS_DATA_LENGTH_U 100

/*! \def GPRS_MAX_DATA
    \brief Maximum data length 
 */
#define	GPRS_MAX_DATA	100

/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspGPRS_Pro Class
/*!
	WaspGPRS Class defines all the variables and functions used to manage GPRS module
 */
class WaspGPRS_Pro
{
	private:
		
	
	//! Variable : stores if the module is ready or not (1:not ready, 0:ready)
    	/*!
	 */
	uint8_t not_ready;
	
	//! Variable : stores the IP mode connection (1:multiple, 0:single)
    	/*!
	 */
	uint8_t IP_mode;
	
	
	

#if IP_FUSE
	//! Gets IP direction when configure a TCP/UDP profiles
	/*!
	\param void
	\return '1' on success, '0' if error. It stores IP direction in 'IP_direction'
	*/
	uint8_t getIP();
	
	
	//! It checks if GPRS connection is OK
    /*!
	\param void
	\return '1' IP INITIAL,'2' IP START,'3' IP CONFIG, '4' IP GPRSACT, '5' IP STATUS, '6' TCP CONNECTING/UDP CONNECTING/SERVER LISTENING, 
	'7' CONNECT OK, '8' TCP CLOSING/UDP CLOSING, '9' TCP CLOSED/UDP CLOSED, '10' PDP DEACT, '0' if error
	 */
	uint8_t checkIPstatus();
#endif	
	
	//! Parses 'data_expected' into 'data' string
	/*!
	\param char* data : string of data  
	\param char* data_expected : string of data to find
	\return '1' if data_expected is in data, '0' if not.
	*/
	uint8_t parse(const char* data,const char* data_expected);

	//! It gets if GPRS module is ready or not
    /*!
	\return nothing. It changes the value of 'not_ready'
	 */
	void getIfReady();	
	
	//! It checks if GPRS connection is OK
    /*!
	\param void
	\return '1' on success, '0' if error
	 */
	uint8_t checkGPRS();
		
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer : string expected to be answered by the module
	\return '1' on success, '0' if error
	 */	
	uint8_t sendCommand1(const char* theText, const char* expectedAnswer1);
	
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* endOfCommand : string to send to the module
	\param char* expectedAnswer : string expected to be answered by the module
	\param int MAX_TIMEOUT : specifies the maximum timeout	
	\param int sendOnce : specifies if the data is sent once	
	\return '1' if expectedAnswer has been detected, '0' if not detected
	 */
	uint8_t sendCommand1(const char* theText, const char* expectedAnswer, int MAX_TIMEOUT, int sendOnce);
	
	//! It waits for data from the module
    /*!
	\param char* expectedAnswer : string expected to be answered by the module
	\param int MAX_TIMEOUT : specifies the maximum timeout	
	\param int timeout : specifies the timeout
	\param int seconds : specifies the number of seconds to wait before listening to the module
	\return '1' if expectedAnswer has been detected, '0' if not detected
	 */
	uint8_t waitForData(const char* expectedAnswer, int MAX_TIMEOUT, int timeout, int seconds);
	
	//!functions with two answers
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* endOfCommand : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param char* expectedAnswer2 : string expected to be answered by the module
	\param int sendOnce : specifies if the data is sent once	
	\return '1' if expectedAnswer1 has been detected, '2' if expectedAnswer2, '0' if not detected
	 */
	uint8_t sendCommand2(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2);
	
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* endOfCommand : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param char* expectedAnswer2 : string expected to be answered by the module
	\param int MAX_TIMEOUT : specifies the maximum timeout	
	\param int sendOnce : specifies if the data is sent once	
	\return '1' if expectedAnswer1 has been detected, '2' if expectedAnswer2 has been detected, '0' if not detected
	 */
	uint8_t sendCommand2(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2, int MAX_TIMEOUT, int sendOnce);
	
	//! It waits for data from the module
    /*!
	\param char* expectedAnswer1 : string 1 expected to be answered by the module
	\param char* expectedAnswer2 : string 2 expected to be answered by the module
	\param int MAX_TIMEOUT : specifies the maximum timeout	
	\param int timeout : specifies the timeout
	\param int seconds : specifies the number of seconds to wait before listening to the module
	\return '1' if expectedAnswer1 has been detected, '2' if expectedAnswer2 has been detected, '0' if not detected
	 */
	uint8_t waitForData(const char* expectedAnswer1, const char* expectedAnswer2, int MAX_TIMEOUT, int timeout, int seconds);
	
	//!functions with three answers
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param char* expectedAnswer2 : string expected to be answered by the module
	\param char* expectedAnswer3 : string expected to be answered by the module
	\param int MAX_TIMEOUT : specifies the maximum timeout	
	\param int sendOnce : specifies if the data is sent once	
	\return '1' if expectedAnswer1 has been detected, '2' if expectedAnswer2 has been detected,
		'3' if expectedAnswer3 has been detected,'0' if not detected
	 */
	uint8_t sendCommand3(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, int MAX_TIMEOUT, int sendOnce);
	
	//! It waits for data from the module
    /*!
	\param char* expectedAnswer1 : string 1 expected to be answered by the module
	\param char* expectedAnswer2 : string 2 expected to be answered by the module
	\param char* expectedAnswer3 : string 3 expected to be answered by the module
	\param int MAX_TIMEOUT : specifies the maximum timeout	
	\param int timeout : specifies the timeout
	\param int seconds : specifies the number of seconds to wait before listening to the module
	\return '1' if expectedAnswer1 has been detected, '2' if expectedAnswer2 has been detected,
		'3' if expectedAnswer3 has been detected,'0' if not detected
	 */
	uint8_t waitForData(const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, int MAX_TIMEOUT, int timeout, int seconds);
	
	//!functions with four answers
	//! It sends an AT command to the module
    /*!
	\param char* theText : string to send to the module
	\param char* expectedAnswer1 : string expected to be answered by the module
	\param char* expectedAnswer2 : string expected to be answered by the module
	\param char* expectedAnswer3 : string expected to be answered by the module
	\param char* expectedAnswer4 : string expected to be answered by the module
	\param int MAX_TIMEOUT : specifies the maximum timeout	
	\param int sendOnce : specifies if the data is sent once	
	\return '1' if expectedAnswer1 has been detected, '2' if expectedAnswer2 has been detected,
		'3' if expectedAnswer3 has been detected, '4' if expectedAnswer4 has been detected, '0' if not detected
	 */
	uint8_t sendCommand4(const char* theText, const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, const char* expectedAnswer4, int MAX_TIMEOUT, int sendOnce);
	
	//! It waits for data from the module
    /*!
	\param char* expectedAnswer1 : string 1 expected to be answered by the module
	\param char* expectedAnswer2 : string 2 expected to be answered by the module
	\param char* expectedAnswer3 : string 3 expected to be answered by the module
	\param char* expectedAnswer4 : string 3 expected to be answered by the module
	\param int MAX_TIMEOUT : specifies the maximum timeout	
	\param int timeout : specifies the timeout
	\param int seconds : specifies the number of seconds to wait before listening to the module	
	\return '1' if expectedAnswer1 has been detected, '2' if expectedAnswer2 has been detected,
		'3' if expectedAnswer3 has been detected, '4' if expectedAnswer4 has been detected, '0' if not detected
	 */
	uint8_t waitForData(const char* expectedAnswer1, const char* expectedAnswer2, const char* expectedAnswer3, const char* expectedAnswer4, int MAX_TIMEOUT, int timeout, int seconds);
	
	
#if FTP_FUSE	
    //! It sends data via FTP
    /*!
    \param char* file : path within SD card to find the file to upload
    \param char* path : path in the FTP server where store the file
    \return '1' on success, '0' if error, '-1' if no memory
    */
	int8_t sendDataFTP(const char* file, const char* path);
	
    //! It reads data via FTP
    /*!
    \param char* file : path in the FTP server where find the file to download
    \param char* path : path within SD card to store the file to download
	\return '1' on success, '0' if error, '-1' if no memory
	 */
	int8_t readDataFTP(const char* file, const char* path);

	//! It reads the size of a file into the FTP server
    /*!
    \param char* path : path within SD card to store the file to download
	\return size or '-1' if error
	 */
	long getfilesizeFTP(const char* path);
#endif

	//! It closes at opened connection for FTP or HTTP
	/*! This function closes a GPRS connection with the carrier server to get access to the HTTP and FTP applications
	\param uint8_t n_conf : number of the profile (1-3)
	\return '1' on success, '0' if error and '-2' error with CME error code available
	 */
	int8_t closeGPRS_HTTP_FTP_connection(uint8_t n_conf);

	int8_t closeHTTP();
	
	public:
	
	//! Variable : struct that stores the format and the name of the operators
	struct operators{
		uint8_t format;
		char operator_name[15];
	}operators_list[5];
		
	//! Variable : status flag, used to see if there was an error while communicating with the module
    /*!
	Possible values are : GPRS_ERROR_POWER, GPRS_ERROR_CALL, GPRS_ERROR_HANG, GPRS_ERROR_SMS, GPRS_ERROR_PIN, GPRS_ERROR_CALLINFO, GPRS_ERROR_SMSINFO, GPRS_ERROR_CONF, GPRS_ERROR_PATTERN, GPRS_ERROR_TIMER, GPRS_ERROR_PROFILE, GPRS_ERROR_SOCKET, GPRS_ERROR_CHECK, GPRS_ERROR_CLOSE
     */
	int   flag;
	
	//! Variable : last call or SMS received telephone number
    /*!
	It stores telephone numbers with country code if it appears
	*/
	char tlfIN[15];
	
	//! Variable : baud rate used to communicate with the GPRS module
    /*!
	By default, it is 57600bps
	*/
	long _baudRate;
	
	//! Variable : power mode
    /*!
	Possible values are: GPRS_PRO_ON, GPRS_PRO_FULL, GPRS_PRO_RF_OFF, GPRS_PRO_MIN, GPRS_PRO_SLEEP, GPRS_PRO_OFF
	*/
	uint8_t _pwrMode;
	
	//! Variable : UART used by the GPRS module
    /*!
	GPRS module is connected to the UART1
	*/
	uint8_t	_socket;
	
	//! Variable : last SMS text received
    /*!
	It stores up to 100bytes from the last SMS received
	*/
	char sms[100];
	
	//! Variable : socket ID
    /*!
	It stores the ID of the last socket opened
	*/
	uint8_t socket_ID[4];
	
	//! Variable : amount of data read from an URL or from a socket
	uint16_t data_read;
	
	//! Variable : Cell ID number
	char cellID[5];
      
	//! Variable : RSSI value
	int RSSI;
	
	//! Variable : Last sms received index
	char sms_index[4];
	        
    //! Variable : IP direction
	char IP_dir[16];  
	
	//! Variable : IP application mode
	/*!
	'0'= non transparent mode, '1'= transparent mode
	*/
	uint8_t IP_app_mode; 	
			
	//! Variable : Stores CME or CMS error code
    int CME_CMS_code;
	
	//! Variable : Stores CME or CMS error code
    int FTP_error_code;
        
    //! Variable : specifies if the GPRS modules is connected to the network (1:connected ; 0:connected)
    uint8_t connected;
	
	char buffer_GPRS[256];
	
    //! class constructor
    /*!
	It initializes some variables
	\param void
	\return void
    */ 
	WaspGPRS_Pro();
    
	//! It opens UART1 and powers the SIM900 module
    /*!
	\param void
	\return void
	\sa close(), begin()
     */ 
	void ON();
		
	//! It closes UART1 and powers off the SIM900 module
    /*!
	\param void
	\return void
	\sa close(), begin()
	 */ 
	void OFF();
		
	//! It opens UART and sets multiplexer properly
    /*!
	\param void
	\return void
	 */ 
	void begin();
		
	//! It closes UART and sets multiplexer properly
    /*!
	\param void
	\return void
	*/ 
	void close();
		
	//! It sets Power Mode
    /*!
	\param uint8_t pwrMode : the desired power mode (GPRS_PRO_ON, GPRS_PRO_FULL, GPRS_PRO_RF_OFF, GPRS_PRO_MIN, GPRS_PRO_SLEEP, GPRS_PRO_POWER_OFF)
	\return '1' on success, '0' if error and '-2' if error with CME error code available
	 */
	int8_t setMode(uint8_t pwrMode);
		
	//! It gets Power Mode
    /*!
	\param void
	\return the power mode (GPRS_PRO_ON, GPRS_PRO_FULL, GPRS_PRO_RF_OFF, GPRS_PRO_MIN, GPRS_PRO_SLEEP, GPRS_PRO_POWER_OFF)
	 */
	uint8_t getMode();
		
	//! Sets time and date to GPRS_Pro module from RTC
	/*!
	\param void
	\return '1' on success , '0' or '-2' if error
	*/
	uint8_t setTime();
	
	//! It checks if GPRS is connected to the network
    /*!
	\param void
	\return '1' if connected, '0' if not
	*/
	int8_t check();
		
	//! It sets PIN
    /*!
	\param const char* PIN : the SIM's PIN
	\return '1' on success, '0' if error and '-2' if CME error code available
	*/
	int8_t setPIN(const char* pin);
	
	//! changes PIN number to the SIM
    /*!
	\param const char* old_pin : the old SIM's PIN
	\param const char* new_pin : the new SIM's PIN
	\return Returns '1' on success, '0' if error and '-2' if CME error code available
	*/
	int8_t changePIN(const char* old_pin, const char* new_pin);
	
	//! It gets the IMSI from the SIM card
    /*!
    It stores the IMSI into 'buffer_GPRS' variable.
	\return '1' if connected, '0' if not
	*/
    int8_t getIMSI();
	
    //! It gets the IMEI from the SIM card
    /*!
    It stores the IMEI into 'buffer_GPRS' variable.
	\return '1' if connected, '0' if not
	 */
    int8_t getIMEI();
	
	
#if GSM_FUSE	
	//! It makes a call to the specified number
    /*!
	\param const char* tlfNumber : telephone number to call. It must be a telephone number with 9 digits.
	\return '1' on success, '0' if error
	 */
	int8_t makeCall(const char* tlfNumber);
	
	//! It makes a lost call to the specified number
    /*!
	\param const char* tlfNumber : telephone number to call. It must be a telephone number with 9 digits.
	\param uint8_t timeCall : time the module is calling (in seconds)
	\return '1' on success, '0' if error
	 */
	int8_t makeLostCall(const char* tlfNumber, uint8_t timeCall);
	
	//! It sets the info shown when an incoming call is received
    	/*!
	\param void
	\return '1' on success, '0' if error and '-2' if error with CME error code available
	 */
	int8_t	setInfoIncomingCall();
	
	//! It stores in 'tlfIN' variable the telephone number of the incoming call
    /*!
	\param char* data : data returned by the module when a call is being received
	\return '1' on success, '0' if error
	 */
	uint8_t	readCall(const char* data);
	
	//! It hangs all the active calls up
    /*!
	\return '1' on success, '0' if error
	 */
	uint8_t hangUp();
	
	//! It sets the monitor speaker loudness
    /*!
	\param uint8_t volume : volume level between 0 and 9
	\return '1' on success, '0' if error
	 */
	uint8_t setMonitorVolume(uint8_t volume);
	
	//! It sets the monitor speaker mode
    /*!
	\param uint8_t mode : speaker mode between 0 and 9
	\return '1' on success, '0' if error
	 */
	uint8_t setMonitorMode(uint8_t mode);
	
	//! It enables or disables the presentation of the incoming call
    /*!
	\param uint8_t mode : ENABLE or DISABLE
	\return '1' on success, '0' if error
	 */
	uint8_t setCLIPresentation(uint8_t mode);
	
	//! It restricts or enables the presentation of the CLI to the called party when originating a call.
    /*!
	\param uint8_t mode : DEFAULT_CLIR, INVOKE_CLIR or SUPPRESS_CLIR
	\return '1' on success, '0' if error
	 */
	uint8_t setCLIRestriction(uint8_t mode);
	
	//! It gets the phone activity status
    /*!
	\param void
	\return '1' on success, '0' if error
	 */
	uint8_t getPhoneActStatus();
	
	//! It sets loudspeaker volume
    /*!
	\param uint8_t volume : volume level between 0 and 100
	\return '1' on success, '0' if error and '-2' if error with CME error code available
	 */
	uint8_t setLoudspeakerLevel(uint8_t volume);
	
	//! It sets the monitor speaker loudness
    /*!
	\param uint8_t mode : SILENT_MODE
	\return '1' on success, '0' if error setting the sound mode, '-2' if error setting the sound mode with CME error code available,
		'-3' if error setting the sound type, '-4' if error setting the sound type with CME error code available,
		'-5' if error setting the ring level, '-6' if error setting the ring level with CME error code available,
	 */
	uint8_t setCallAlert(uint8_t mode);

	//! It sets the monitor speaker loudness
    /*!
	\param uint8_t mode : NORMAL_MODE or SILENT_MODE
	\param uint8_t sound_type : number for various melodies
	\param uint8_t ring_level : LEVEL_OFF, LEVEL_LOW, LEVEL_MEDIUM, LEVEL_HIGH or LEVEL_CRESCENDO
	\return '1' on success, '0' if error setting the sound mode, '-2' if error setting the sound mode with CME error code available,
		'-3' if error setting the sound type, '-4' if error setting the sound type with CME error code available,
		'-5' if error setting the ring level, '-6' if error setting the ring level with CME error code available,
	 */
	uint8_t setCallAlert(uint8_t mode,uint8_t sound_type, uint8_t ring_level);
	
	//! It sets the monitor speaker loudness
    /*!
	\param uint8_t mute_mode : ENABLE or DISALBE
	\return '1' on success, '0' if error, '-2' if error with CME error code available
	 */
	uint8_t setMute(uint8_t mute_mode);
	
	
	//! It sets 'text mode' for sending SMS
    /*!
	\param void
	\return '1' on success, '0' if error
	 */
	uint8_t setTextModeSMS();
	
	//! It sends a SMS to the specified number
    /*!
	\param const char* smsText : SMS text (up to 80bytes)
	\param const char* tlfNumber : telephone number to send the SMS. It must be a telephone number with 9 digits.
	\return '1' on success,'0' if error, '-2' if error sending the SMS 
		and '-3' if error sending the SMS with CMS error code available
	 */
	int8_t sendSMS(const char* smsText, const char* tlfNumber);
	
	//! It sets the info shown when an incoming SMS is received
    	/*!
	\param void
	\return '1' on success, '0' if error
	 */
	uint8_t setInfoIncomingSMS();
	
	//! It stores in 'tlfIN' and 'sms' variables the telephone number and the text of the incoming SMS. It stores in 'sms_index' variable the last sms received index
    /*!
	\param char* data : data returned by the module when an SMS is received
	\return '1' on success, '0' if error, '-1' if no memory
	 */
	int8_t readSMS(const char* data);
	
	//! It gets the number of total SMS stored in the SIM
    /*!	
	\return the number of SMS or '-2' if error
	 */
	uint8_t getTotalSMS();	

	//! It deletes a sms in the memory selected by sms_index
    /*!
	\param int sms_index : index of the sms to delete
	\return '1' on success, '0' if error and '-2' if error with CMS error code available
	 */	
	uint8_t deleteSMS(uint8_t sms_index);	
#endif	
	
	
	//! It manages incoming data from serial port, executing proper functions to store received data
	/*!
	\param void
	\return '1' on success, '0' if error, '-1' if no memory
	 */
	int8_t	manageIncomingData();
	
	//! Resumes the connection and switches back from Command mode to data mode
	/*!
	\param void
	\return '1' on success, '0' if error ,'2' if connection is not successfully resumed
	 */
	int8_t switchtoDataMode();
	
	//! Switch From Data Mode Or PPP Online Mode To Command Mode
	/*!
	\param void
	\return '1' on success, '0' if error
	 */
	int8_t switchtoCommandMode();	
	
	//! It sends any command to the GPRS module
    /*!
	\param char* ATcommand : the command to send to the GPRS module
	\return '1' on success, '0' if error
	 */
	int8_t sendCommand(const char* ATcommand);
		
	//! It configures GPRS connection with login, password and some other parameters for use with HTTP and FTP functions
    /*!	It takes the configuration parameters from 'WaspGPRSconstants.h' file
	\param uint8_t n_conf : number of the profile (1-3)
	\return '1' on success, '0' if error and '-2' if error setting the type of internet connection, 
		'-3' if error setting the apn, '-4' if error setting the user name, '-5' if error setting the password
		and '-6' if error saving the configuration
	 */
	int8_t configureGPRS_HTTP_FTP(uint8_t n_conf);
		
#if FTP_FUSE
	//! It uploads a file to a FTP server
    /*!
	\param const char* file : path within SD card to find the file to upload
    \param const char* path : path in the FTP server where store the file
	\param const char* user : login to connect to the ftp server
	\param const char* passw : password to connect to the ftp server
	\param const char* ftp_server : ftp server
	\param uint8_t ftp_port : ftp server port
	\param uint8_t n_conf : number of HTTP/FTP profile
	\return '1' on success and '0' if error opening connection with the GPRS provider, '-2' if error getting the IP address
		'-3' if error setting the FTP/HTTP ID, '-4' if error setting the FTP mode, '-5' if error setting the FTP type,
		'-6' if error setting the FTP server, '-7' if error setting the FTP port, '-8' if error setting the user name,
		'-9' if error setting the password, '-10' if error starting the SD, '-11' if error taking the file size in the SD,
		'-13' if error setting the file name in the FTP server, '-14' if error setting the path of the file in the FTP server
		'-15' if error opening the FTP session, '-16' if error when request to send data, '-17' error sending data to the FTP,
		'-18' if error waiting for send more data, '-20' if error closing the FTP session, '-21' setting the file name in the FTP to get the file size
		'-22' setting the path in the FTP to get the file size, '-23' if error getting the file size
		'-41' if error setting the FTP/HTTP ID with CME error code available, '-42' if error setting the FTP mode with CME error code available,
		'-43' if error setting the FTP type with CME error code available, '-44' if error setting the FTP server with CME error code available,
		'-45' if error setting the FTP port with CME error code available, '-46' if error setting the user name with CME error code available,
		'-47' if error setting the password with CME error code available, '-48' if error starting the SD with CME error code available,
		'-49' if error taking the file size in the SD with CME error code available, '-48' if error setting the file name in the FTP server with CME error code available,
		'-49' if error setting the path of the file in the FTP server with CME error code available, '-50' if error opening the FTP session with CME error code available,
		'-51' if error closing the FTP session with CME error code available, '-53' setting the file name in the FTP to get the file size with CME error code available,
		'-54' setting the path in the FTP to get the file size with CME error code available, '-55' if error getting the file size with CME error code available
	 */
	int8_t uploadFile(const char* file, const char* path, const char* user, const char* passw, const char* ftp_server, const char* ftp_port, uint8_t n_conf);
	
	//! It downloads a file from a FTP server
    /*!
	\param const char* file : path in the FTP server where find the file to download
    \param const char* path : path within SD card to store the file to download
	\param const char* user : login to connect to the ftp server
	\param const char* passw : password to connect to the ftp server
	\param const char* ftp_server : ftp server
	\param uint8_t ftp_port : ftp server port
	\param uint8_t n_conf : number of HTTP/FTP profile
	\return '1' on success and '0' if error opening connection with the GPRS provider, '-2' if error getting the IP address
		'-3' if error setting the FTP/HTTP ID, '-4' if error setting the FTP mode, '-5' if error setting the FTP type,
		'-6' if error setting the FTP server, '-7' if error setting the FTP port, '-8' if error setting the user name,
		'-9' if error setting the password, '-12' if error setting the file name in the FTP server, 
		'-13' if error setting the path of the file in the FTP server, '-14' if error opening the FTP session,
		'-15' if error starting the SD, '-16' if error creating the file, '-17' error requesting data to the FTP,
		'-18' if error saving data into the SD, '-19' if error requesting more data to the FTP, '-21' setting the file name in the FTP to get the file size
		'-22' setting the path in the FTP to get the file size, '-23' if error getting the file size
		'-41' if error setting the FTP/HTTP ID with CME error code available, '-42' if error setting the FTP mode with CME error code available,
		'-43' if error setting the FTP type with CME error code available, '-44' if error setting the FTP server with CME error code available,
		'-45' if error setting the FTP port with CME error code available, '-46' if error setting the user name with CME error code available,
		'-47' if error setting the password with CME error code available, '-48' if error setting the file name in the FTP server with CME error code available,
		'-49' if error setting the path of the file in the FTP server with CME error code available, '-50' if error opening the FTP session with CME error code available,
		'-51' if error requesting data to the FTP with CME error code available, '-52' if error requesting more data to the FTP with CME error code available,
		'-53' setting the file name in the FTP to get the file size with CME error code available,
		'-54' setting the path in the FTP to get the file size with CME error code available, '-55' if error getting the file size with CME error code available
	 */
	int8_t downloadFile(const char* file, const char* path, const char* user, const char* passw, const char* ftp_server, const char* ftp_port, uint8_t n_conf);
#endif	
	
#if HTTP_FUSE
	//! It accesses to the specified URL and stores the info read in 'data_URL' variable
    /*!
	It stores in 'buffer_GPRS' variable up to 255 bytes
	\param const char* url : the URL to get the information from
	\param uint8_t n_conf : number of HTTP/FTP profile
	\return '1' on success and '0' if error, '-2' if error opening the connection,'-3' if error getting the IP address,
		'-4' if error initializing the HTTP service, '-10' if error initializing the HTTP service with CME error code available,
		'-5' if error setting CID the HTTP service, '-11' if error setting CID the HTTP service with CME error code available,
		'-6' if error setting the url the HTTP service, '-12' if error setting the url the HTTP service with CME error code available,
		'-7' if error setting the url the HTTP service, '-13' if error setting the url the HTTP service with CME error code available,
		'-8' if error getting data from url, '-14' if error getting data from url with CME error code available,
		'-9' if error closing the HTTP service, '-15' if error closing the HTTP service with CME error code available,
	 */
	int8_t readURL(const char* url, uint8_t n_conf);
	int8_t readURL(const char* url, uint8_t* data, int length, uint8_t n_conf);
#endif
	
	//! It gets the currently selected operator from network
    /*! It stores it in operator_name
	\param void
	\return '1' on success, '0' if error and '-2' if CME error code available
	 */
	int8_t getcurrentOperator();
	
	//! It gets the currently available operators from network
    /*! It stores it in operator_list
	\param void
	\return '1' on success, '0' if error
	 */
	int8_t getAvailableOperators();
	
	//! It sets the monitor speaker loudness
    /*!
	\param uint8_t index : index in the list from 0 to 4
	\param uint8_t format: format of the operator names
	\param uint8_t preferred_operator : operator name
	\return '1' on success, '0' if error and '-2' if CME error code available
	 */
	int8_t setPreferredOperator(int index, uint8_t format, const char* preferred_operator);
	
	//! It gets info from the cell where the modules is connected
    /*!	It stores in 'RSSI' and 'cellID' variables the RSSI and the Cell ID
	\return '1' on success, '0' if error and '-2' if CME error code available
	 */
	int8_t getCellInfo();
	
	
#if IP_FUSE	
	//! It configures GPRS connection with login, password and some other parameters for use with TCP or UDP connections
    /*!
	It takes the configuration parameters from 'WaspGPRSconstants.h' file
	\param uint8_t mode : MULTI_CONNECTION
	\return '1' on success, '0' if error, '-2' if error dettaching the GPRS connection, 
		'-3' if error attaching the GPRS connection, '-4' if error setting the application mode,
		'-5' if error setting the connection mode, '-6' if error establishing the connection with the GPRS provider, 
		'-15' if error dettaching the GPRS connection with CME error code available, 
		'-16' if error attaching the GPRS connection with CME error code available.
	 */
	int8_t configureGPRS_TCP_UDP(uint8_t mode_connection);
	
	//! It configures GPRS connection with login, password and some other parameters for use with TCP or UDP connections
    /*!
	It takes the configuration parameters from 'WaspGPRSconstants.h' file
	\param uint8_t mode_connection : SINGLE_CONNECTION 
	\param uint8_t app_mode : TRANSPARENT mode or NON_TRANSPARENT mode
	\return '1' on success, '0' if error, '-2' if error dettaching the GPRS connection, 
		'-3' if error attaching the GPRS connection, '-4' if error setting the application mode,
		'-5' if error setting the connection mode, '-6' if error establishing the connection with the GPRS provider, 
		'-15' if error dettaching the GPRS connection with CME error code available, 
		'-16' if error attaching the GPRS connection with CME error code available.
	 */
	int8_t configureGPRS_TCP_UDP(uint8_t mode_connection, uint8_t app_mode);
	
	//! It sets the number of the internal port for TCP or UDP connections
    /*!
	\param const char* mode : TCP or UDP
	\param uint16_t port : PORT number
	\return '1' on success, '0' if error
	 */
	uint8_t setLocalPort(const char* mode, uint16_t port);

	//! It saves the configuration into the internal NVRAM of the GPRS module
    /*!
	\param void
	\return '1' on success, '0' if error
	 */
	uint8_t saveGPRS_TCP_UDPconfiguration();
	
	//! It creates a TCP/IP connection to the specified IP and PORT
    /*!
	\param uint8_t working_mode :  TCP_SERVER
	\param const char* port : the PORT to open a socket to
	\return '1' on success, '0' if error setting the connection, 
		'-2' if error setting the connection with CME error code available
		and '-3' if time out waiting the connection
	 */
	int8_t createSocket( uint8_t working_mode, const char* port);
	
	//! It creates a TCP/IP connection to the specified IP and PORT
    /*!
	\param uint8_t working_mode : TCP_CLIENT, UDP_CLIENT or UDP_EXTENDED
	\param const char* ip : the IP to open a socket to
	\param const char* port : the PORT to open a socket to
	\return '1' on success, '0' if error setting the connection, 
		'-2' if error setting the connection with CME error code available
		and '-3' if time out waiting the connection
	 */
	int8_t createSocket( uint8_t working_mode, const char* ip,const char* port);
	
	//! It creates a TCP/IP connection to the specified IP and PORT
    /*!
	\param uint8_t working_mode : TCP_CLIENT, UDP_CLIENT or UDP_EXTENDED
	\param uint8_t n_connection : number of the connection id to use (0-7)
	\param const char* ip : the IP to open a socket to
	\param const char* port : the PORT to open a socket to	
	\return '1' on success, '0' if error setting the connection, 
		'-2' if error setting the connection with CME error code available
		and '-3' if time out waiting the connection
	 */
	int8_t createSocket( uint8_t working_mode, uint8_t n_connection, const char* ip, const char* port);
	
	//! It sends 'data' to the specified 'socket'
    /*!
	\param const char* data : the data to send to the socket
	\return '1' on success, '0' if error waiting the response of the module,
		'-2' if error with CME error code available
		'-3' if no feedback detected and '-4' if the send fails
	*/	
	int8_t sendData(const char* data);	
	
	//! It sends 'data' to the specified 'socket'
    /*!
	\param const char* data : the data to send to the socket
	\param uint8_t n_connection: the connection's number
	\return '1' on success, '0' if error waiting the response of the module,
		'-2' if error with CME error code available
		'-3' if no feedback detected and '-4' if the send fails
	*/	
	int8_t sendData(const char* data, uint8_t n_connection);
	
	//! It sends 'data' to the specified 'socket'
    /*!
	\param uint8_t* data : the data to send to the socket
	\param int length : the length of the data for send to the socket
	\return '1' on success, '0' if error waiting the response of the module,
		'-2' if error with CME error code available
		'-3' if no feedback detected and '-4' if the send fails
	*/	
	int8_t sendData(uint8_t* data, int length);
	
	//! It sends 'data' to the specified 'socket'
    /*!
	\param uint8_t* data : the data to send to the socket
	\param int length : the length of the data for send to the socket
	\param uint8_t n_connection: the connection's number
	\return '1' on success, '0' if error waiting the response of the module,
		'-2' if error with CME error code available
		'-3' if no feedback detected and '-4' if the send fails
	*/	
	int8_t sendData(uint8_t* data, int length, uint8_t n_connection);
	
	//! Gets data receive from a TCP or UDP connection and stores it in 'buffer_GPRS'
    /*!
	\param char* dataIN : string of data with TCP/UDP info
	\return '1' on success, '0' if error
	 */
	int8_t readIPData(char* dataIN);
	
	//! It closes TCP/IP connection
    /*!
	\param void
	\return '1' on success, '0' if error
	 */
	int8_t closeSocket();
	
	//! It closes TCP/IP connection
    /*!
	\param uint8_t n_connection: the connection's number
	\return '1' on success, '0' if error
	 */
	int8_t closeSocket(uint8_t n_connection);

	//! It enables/disables to close the connection quickly
    /*!
	\param uint8_t mode: ENABLE or DISABLE
	\return '1' on success, '0' if error
	 */
	int8_t QuickcloseSocket(uint8_t mode);
	
	//! It gets the IP direction from a URL using DNS servers
    /*! It stores the direccion in 'buffer_GPRS'
	\param const char* IP_query : URL to obtain te IP direction
	\return '1' on success, '0' if error
	 */
	uint8_t getIPfromDNS(const char* IP_query);
	
	//! It adds an IP head at the beginning of a package received
    /*! 
	\param uint8_t on_off : ENABLE or DISABLE
	\return '1' on success, '0' if error
	 */	
	int8_t IPHeader(uint8_t on_off);
	
	//! It sets a timer when module is sending data
    /*! 
	\param uint8_t mode : ENABLE or DISABLE
	\return '1' on success, '0' if error
	 */	
	int8_t SetAutoSendingTimer(uint8_t mode);
	
	//! It sets a timer when module is sending data
    /*! 
	\param uint8_t mode : ENABLE or DISABLE
	\param uint8_t time : time in seconds from 0 to 100
	\return '1' on success, '0' if error
	 */
	int8_t SetAutoSendingTimer(uint8_t mode, uint8_t time);
	
	//! It enables or disables to show remote IP address and port when received data
    /*! 
	\param uint8_t on_off : ENABLE or DISABLE
	\return '1' on success, '0' if error
	 */
	int8_t ShowRemoteIP(uint8_t on_off);
	
	//! It enables or disables to show transfer protocol in IP head when received data
    /*! 
	\param uint8_t on_off : ENABLE or DISABLE
	\return '1' on success, '0' if error
	 */
	int8_t ShowProtocolHeader(uint8_t on_off);
	
	//! It enables or disables to discard input AT data in TCP data send
    /*! 
	\param uint8_t on_off : ENABLE or DISABLE
	\return '1' on success, '0' if error
	 */
	int8_t DiscardInputATData(uint8_t on_off);
	
	//! It enables or disables to get data manually from a TCP or UDP connection
    /*! 
	\param uint8_t on_off : ENABLE or DISABLE
	\return '1' on success, '0' if error
	 */
	int8_t SetDataManually(uint8_t on_off);
	
	//! It enables or disables to get data manually from a TCP or UDP connection
    /*! 
	\param uint8_t on_off : ENABLE or DISABLE
	\param uint8_t id : id connection number
	\return '1' on success, '0' if error
	*/
	int8_t SetDataManually(uint8_t on_off, uint8_t id);
	
	//! It gets data manually from a TCP or UDP connection
    /*! 
	\param uint16_t data_length : the legth of the data to get
	\return '1' on success, '0' if error
	 */
	int8_t GetDataManually(uint16_t data_length);
	
	//! It gets data manually from a TCP or UDP connection
    /*! 
	\param uint16_t data_length : the legth of the data to get
	\param uint8_t id : id connection number
	\return '1' on success, '0' if error
	 */
	int8_t GetDataManually(uint16_t data_length, uint8_t id);
#endif
	
	//! It sets the directions of DNS servers from GPRS_Proconstants.h
    /*!
	\return '1' on success, '0' if error and '-2' if CME error code available
	 */	
	uint8_t setDNS();
	
	//! It sets the direction of DNS server
    /*!
	\param const char* DNS_dir1 : DNS server direction
	\return '1' on success, '0' if error and '-2' if CME error code available
	 */
	uint8_t setDNS(const char* DNS_dir);
	
	//! It sets the directions of DNS servers
    /*!
	\param const char* DNS_dir1 : DNS server direction
	\param const char* DNS_dir2 : DNS server direction
	\return '1' on success, '0' if error and '-2' if CME error code available
	 */
	uint8_t setDNS(const char* DNS_dir1, const char* DNS_dir2);
};

extern WaspGPRS_Pro GPRS_Pro;

#endif
