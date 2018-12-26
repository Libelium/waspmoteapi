/*! 
 * @file 	WaspSigfox.h
 * @author	Libelium Comunicaciones Distribuidas S.L.
 * @version	3.4
 * @brief 	Library for managing Sigfox modules TD1207 & TD1508
 * 
 * Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
 * http://www.libelium.com
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
 
#ifndef WaspSigfox_h
#define WaspSigfox_h

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <inttypes.h>
#include <WaspUART.h>


/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

//! DEBUG_SIGFOX
/*! Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_SIGFOX	0


// define print message
#define PRINT_SIGFOX(str)	USB.print(F("[Sigfox] ")); USB.print(str);


//! UART baudrate
#define SIGFOX_RATE 9600

//! ATcommands responses
static char SIGFOX_AT_OK[] 	= "OK";
static char SIGFOX_AT_ERROR[] 	= "ERROR";
static char SIGFOX_AT_EOL[] 	= "\r\n";
static char SIGFOX_AT_HEADER[] = "AT$";
static char SIGFOX_AT_HEADER_SLASH[] = "AT/";

//! Maximum LAN packet size
static int SIGFOX_LAN_MAX_PAYLOAD = 17;
	

/*! @enum AnswersTypes
 * API answer messages
 */
enum AnswersTypes
{
	SIGFOX_ANSWER_OK = 0,
	SIGFOX_ANSWER_ERROR = 1,
	SIGFOX_NO_ANSWER = 2,
};


/*! @enum CommandTypes
 * Command types
 */
enum CommandTypes
{
	SIGFOX_CMD_SET  = 1, 	// AT$<cmd>=<value>
	SIGFOX_CMD_READ = 2, 	// AT$<cmd>?
	SIGFOX_CMD_DISPLAY = 3, // AT/<cmd>?
};

/*! @enum RegionTypes
 */
enum RegionTypes
{
	SIGFOX_REGION_UNKNOWN 	= 0,
	SIGFOX_REGION_ETSI 		= 1,
	SIGFOX_REGION_FCC 		= 2,
	SIGFOX_REGION_ARIB 		= 3,
};

/******************************************************************************
 * Class
 *****************************************************************************/

/*! @class WaspSigFox
 * WaspSigFox Class defines all the variables and functions used to manage 
 * TD1207 modules
 */
class WaspSigfox : public WaspUART
{
	  
	private:
	
		#define RADIO_SIGFOX_UART_SIZE 100
		uint8_t class_buffer[RADIO_SIGFOX_UART_SIZE];
	
		// private attributes
		char _command[100];
		
		// private methods
		void generator(uint8_t type, int n, const char *cmdCode, ...);		
		uint32_t parseHexValue();	
		uint8_t parseUint8Value();
		uint32_t parseUint32Value();

	public:
		uint8_t _power;					/*!< Sigfox tx power (in dBm)	*/		
		uint32_t _id;					/*!< Sigfox module id			*/	
		char _firmware[10];				/*!< Module firmware version	*/	
		uint32_t _address;				/*!< LAN address				*/	 
		uint32_t _mask;					/*!< Mask address				*/		
		uint32_t _frequency;			/*!< Frequency					*/	
		int _powerLAN;					/*!< LAN tx power (in dBm)		*/	
		char _packet[35];				/*!< LAN packet structure		*/	
		uint8_t _region;				/*!< actual region of the module*/	
		char _macroChannelBitmask[25];	/*!< Macro channel bitmask		*/	
		uint8_t _macroChannel;			/*!< Macro channel 				*/	
		int32_t _downFreqOffset;		/*!< Downlink Frequency Offset	*/	
		
		//! class constructor
		WaspSigfox()
		{
			// assign class pointer to UART buffer
			_buffer = class_buffer;
			_bufferSize = RADIO_SIGFOX_UART_SIZE;	
		};
		
		// Switch on/off functions
		uint8_t ON(uint8_t socket);	
		uint8_t OFF(uint8_t socket);	
		uint8_t check();
		
		// Sigfox functions
		uint8_t getID();
		uint8_t send(char* data);
		uint8_t send(uint8_t* data, uint16_t length);
		uint8_t sendACK(char* data);
		uint8_t sendACK(uint8_t* data, uint16_t length);		
		uint8_t testTransmit(uint16_t count, uint16_t period, int channel);
		uint8_t showFirmware();
		uint8_t setPower(uint8_t power);
		uint8_t getPower();	
		uint8_t sendKeepAlive();
		uint8_t sendKeepAlive(uint8_t period);
		uint8_t continuosWave(uint32_t freq, bool enable);
		
		uint8_t saveSettings();
		uint8_t factorySettings();
		uint8_t defaultConfiguration();
		
		// LAN
		uint8_t setAddressLAN(uint32_t naddress);
		uint8_t getAddressLAN();	
		uint8_t setMask(uint32_t naddress);		
		uint8_t getMask();	
		uint8_t setFrequency(uint32_t frec);
		uint8_t getFrequency();
		uint8_t setPowerLAN(int power);
		uint8_t getPowerLAN();
		uint8_t parsePacketLAN();
		uint8_t sendLAN(uint8_t* data, uint16_t length);		
		uint8_t sendLAN(char* data);	
		uint8_t receive(uint32_t wait);
		void showPacket();
		uint8_t disableRX();	
		uint8_t setMultiPacket();	
		uint8_t getMultiPacket(uint32_t time);	
		uint8_t getRegion();
		
		// FCC functions
		uint8_t setMacroChannelBitmask(char* bitmask);
		uint8_t getMacroChannelBitmask();
		uint8_t setMacroChannel(uint8_t config);
		uint8_t getMacroChannel();
		uint8_t setDownFreqOffset(int32_t offset);
		uint8_t getDownFreqOffset();
		
		// Radio configuration region functions
		uint8_t setRegionRC4();
		uint8_t setRegionRC2();
};

//! Define the object
extern WaspSigfox Sigfox;


#endif
