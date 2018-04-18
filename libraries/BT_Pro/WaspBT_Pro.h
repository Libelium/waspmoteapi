/*
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		3.1
 *  Design:			David Gascón
 *  Implementation:	Javier Siscart
 */

#ifndef WaspBT_Pro_h
#define WaspBT_Pro_h

/*********************************************************************
 * Includes
 *********************************************************************/

#include <inttypes.h>

/*********************************************************************
 * Definitions & Declarations
 *********************************************************************/

/***********OPERATION MODES************/
// Uncomment to enable debug mode
// #define DEBUG_MODE

#define PRINT_BT(str)	USB.print(F("[BT_Pro] ")); USB.print(str);

// uncomment to enable date and time in each device
#define ENABLE_DATE_AND_TIME

// uncomment to enable friendly name features
#define ENABLE_FRIENDLY_NAME

// General constants
#define BT_BLUEGIGA_RATE	115200		// Default baudrate

#define DEFAULT_MAX_INQUIRY_RESULTS	250
#define RX_BUFFER	64
#define BLOCK_SIZE 	32					// Bytes per block used reading UART
#define BLOCK_MAC_SIZE	17				// Bytes per block used to parse Macs
#define COMMAND_SIZE	40
#define BT_NODE_ID_ADDR 1024				// EEPROM address where node ID is stored.
#define ERRORSD1			"err1"		// Error writting.
#define ERRORSD2			"err2"		// Error creating.
#define ERRORSD3			"err3"		// Error deleting.

// File name definitions
#define INQFILE 			"DEVICES.TXT"


//TX power levels allowed for WT12
#define TX_POWER_0	-27		//-27dBm; minimum value
#define TX_POWER_1	-22
#define TX_POWER_2	-17
#define TX_POWER_3	-12
#define TX_POWER_4	-7
#define TX_POWER_5	-2
#define TX_POWER_6	3
#define TX_POWER_DEFAULT_WT12	3	//default factory value
#define TX_POWER_MAX_WT12	3	// maximum value


/*********************************************************************
 * Class
 *********************************************************************/

//! WaspBT_Pro Class
/*!
	WaspBT_Pro Class defines all the variables and functions used for managing the Bluetooth Board
 */
class WaspBT_Pro
{
	private:

	//! Variable : Integer used as counter
    	/*!
	 */
	uint16_t i;

	//! Variable : Integer used to store TX power. seven defined TX power leves. txPower = 0 for minimum power and txPower = 6 for maximum.
		/*!
	 */
	int8_t txPower;

	//! Variable : MAC address
    	/*!
	 */
	char mac_address[BLOCK_MAC_SIZE+1];

	//! Variable : Class of device
    	/*!
	 */
	char CoD[7];

	//! Variable : RSSI
    	/*!
	 */
	char RSSI[4];
    //! Variable : Class. Used for classification.
    	/*!
	 */
	char devClass[2];

	//! Variable : Array for storing the data received from the module
    	/*!
	 */
	uint8_t commandAnswer[RX_BUFFER];

	//! Variable : Array for storing command to be sent to the module.
    	/*!
	 */
	char theCommand[COMMAND_SIZE];

	//! Variable : Baudrate used to communicate with the Bluetooth module. By default, it is 115200bps
    	/*!
	*/
	uint32_t _baudrateBT;

	//! Variable : UART used by the Bluetooth module
    	/*!
	 */
	uint8_t	_uartBT;

	//! Variable : Stores identifier address.
    	/*!
	*/
	int  mem_addr;

	//! Variable : Stores waspmote identifier (8 char length).
    	/*!
	 */
	char identifier[9];

	//! Initializes some parameters of bluetooth module
    	/*!
    \return '1' on success, '0' configuration failed, '-1' erasing SD files failed, '-2' creating SD files failed, '-3' SD card not present
	 */
	int8_t init();

	//! It looks for specific text in module answer.
    	/*!
    \param uint8_t* data: data where string is contained.
    \param const char* expectedAnswer: string to be found.
    \return returns '0' if the string is not found or position of the expected answer.
	 */
	uint16_t lookForAnswer(uint8_t* data, const char* expectedAnswer);

	//! It looks for specific text in module answer.
    	/*!
    \param char* data: data where string is contained.
    \param const char* expectedAnswer: string to be found.
    \return returns '0' if the string is not found or position of the expected answer.
	 */
	uint16_t lookForAnswer(char* data, const char* expectedAnswer);

	//! Sends a command to bluetooth module.
    	/*!
    \param const char* theText: Command to send.
    */
	void sendCommand(const char* theText);

	//! Sends a command to bluetooth module.
    	/*!
    \param uint8_t * theCommand: Command to send.
    \param uint16_t length: command length
    */
	void sendCommand(uint8_t * theCommand, uint16_t length);

	//! Reads command answer and saves it.
    	/*!
	 */
	void readCommandAnswer();

	//! Changes Inquiry TX radio power.
    	/*!
     \param int8_t power: power: TX power value.
	 */
	void changeInquiryPower(int8_t power);
#ifdef ENABLE_FRIENDLY_NAME
	//! Looks for friendly names. NOTE: Inquiring with friendly names is avery slow process. Setting timeout (in milliseconds) the process can be aborted.
    	/*!
    \return Returns: '1' on success, '0' otherwise
	 */
	uint8_t parseNames();
#endif

	//! Saves Mac, CoD and RSSI of a discovered device.
    	/*!
    \param char* block: array which contains inquiry data.
    \return '1' on success, '0' otherwise
	 */
	uint8_t parseBlock(char* block);

	//! Reads UART while inquiry is being answered.
    	/*!
    \param long inquiryTime: wait for module answer during this time.
    \param uint16_t MAX_DEVICES: Maximum number of devices to discover.
    \param bool name: Enables friendly name scan.
    \param bool limited: Enables limited scan.
    \return '1' on success, '0' error parsing block, '-1' error parsing names, '-2' maybe device lost, '-3' error writting SD
	 */
	int8_t waitInquiryAnswer(unsigned long inquiryTime, uint16_t MAX_DEVICES, bool name, bool limited);

#ifdef ENABLE_DATE_AND_TIME
	//! Reads nodeID from EEPROM and Date from RTC. Writes them into INQFILE.
    	/*!
    \return '1' on success, '0' otherwise
	 */
	uint8_t getSetDateID();
#endif

	//! Parses module answer trying to find specified MAC, stops inquiry when mac is found. if dewvice is found, saved on position 0.
    	/*!
    \param long inquiryTime: wait for module answer during this time.
    \param char* mac: mac of desired device.
    \return Returs 1 if found. 0 if not found.
	 */
	bool  waitScanDeviceAnswer(unsigned long inquiryTime, char* mac);

	//! Sets time to be waiting for inquiry answer.
    	/*!
    \param uint16_t time:  time of inquiry in seconds. It is multiplied according to manufacturer.
    \return Returns wait time in milliseconds
	 */
	uint16_t setInquiryTime(uint16_t time);

	//! It cancels currently inquiry.
    	/*!
	 */
	void scanNetworkCancel();

	//! Erases corresponding files on SD.
    	/*!
    \return '1' on success, '0' otherwise
	 */
	uint8_t eraseSDFiles();

	//! Creates necessary files on SD.
    	/*!
    \return '1' on success, '0' otherwise
	 */
	uint8_t createSDFiles();


#ifdef DEBUG_MODE
	//! Test purposes only.
    	/*!
	 */
	void printBuffer();

	//! Test purposes only.
    	/*!
	 */
	void printBuffer2();

#endif

	public:

	//! class constructor
  	/*!
	  It does nothing
	  \param void
	  \return void
	 */
	WaspBT_Pro();

	//! Variable : Stores number of lines of devices file before inquiry
    	/*!
	 */
	uint32_t numLinesBefore;	// should be private

	//! Variable : Stores number of lines of devices file after inquiry.
    	/*!
	 */
	uint32_t numLinesAfter;		// should be private

	//! Variable : Stores number of discovered devices during an inquiry
    	/*!
	 */
	uint16_t numberOfDevices;

	//! Variable : Variable to know if module is in data or command mode
    	/*!
    	0 = data mode, 1 = command mode
	 */
	uint8_t commandMode;

	//! Variable : Variable to store number of active connections.
    	/*!
	 */
	//
	uint8_t activeConnections;

	//! Variable : Variable to store RSSI of a transparent link.
    	/*!
	 */
	//
	char linkRSSI[4];

	//! Variable : Variable to store the own name
    /*!
	 */
	char friendlyName[24];


	//! It opens the UART and powers the module
    	/*!
    \return '1' os success, '0' error reset, '-1' error init
	 */
	int8_t ON();

	//! It opens the UART and powers the module
    	/*!
    \param uint8_t UartMode: UartMode should be 0 for SOCKET0 and 1 for SOCKET1
    \return '1' os success, '0' error reset, '-1' error init
	 */
	int8_t ON(uint8_t UartMode);

	//! It closes the UART and powers off the module
    	/*!
	 */
	void OFF();

	//! Turns bluetotoh module into sleep mode.
    	/*!
	 */
	void sleep();

	//! Wakes up Bluetotoh module from Sleep mode.
    	/*!
    \return '1' on success, '0' otherwise
	 */
	uint8_t wakeUp();

	//! It resets the module
    	/*!
    \return '1' on success, '0' otherwise
	 */
	uint8_t reset();

	//! Reads Bluetooth Node Identifier
    	/*!
    \return Bluetooth node identifier stored in EEPROM
	 */
	char * getNodeID();

	//! Saves Bluetooth Node indentifier into EEPROM
    	/*!
    \param char* ID: Bluetootn Node identifier. It must be 8 char length
	 */
	void setNodeID(char * ID);

	//! Gets own bluetooth module Mac address.
    	/*!
    \return Own mac Address of bluetooth module.
	 */
	char * getOwnMac();

	//! Gets own Bluetooth module friendly name.
    	/*!
    \return public name of bluetooth device. Max length manually limited to 20 characters. Hardware allows til 256 chars.
	 */
	char * getOwnName();

	//! Sets Bluetooth module friendly name. * * Spaces are not allowed.
    	/*!
    \param char* publicName: Visible name of bluetooth device. Use short names without spaces
    \return '1' on success, '0' otherwise
	*/
	uint8_t setOwnName(char * publicName);

	//! Reads temperature from internal module sensor. Internal sensor is not accurante and refreshing rate is not too high.
    	/*!
    \return Temperature
	 */
	long getTemp();

	//! It scans looking for devices.
    	/*!
    \param uint8_t time: Inquiry time.
    \param int8_t power: Allowed TX power levels
    \return returns number of devices found.
    */
	int8_t scanNetwork(uint8_t time, int8_t power);

#ifdef ENABLE_FRIENDLY_NAME
	//! It scans looking for devices, including friendly name.
		/*!
    \param uint8_t time: Inquiry time.
    \param int8_t power: Allowed TX power levels
    \return returns number of devices found.
    */
	int8_t scanNetworkName(uint8_t time, int8_t power);
#endif

	//! It scans network and stops when finds "MAX_DEVICES".
		/*!
    \param uint16_t MAX_DEVICES: Maximum number of devices to find.
    \param int8_t power: Allowed TX power levels
    \return Returns number of devices found.
    */
	int8_t scanNetworkLimited(uint16_t MAX_DEVICES, int8_t power);

	//! It scans looking for devices showing RSSI
		/*!
    \param char* Mac: Mac of device to discover
    \param uint8_t maxTime: Maximum time searching device
    \param int8_t power: Allowed TX power levels
    \return '0' if not found. '1' if found
    */
	int16_t scanDevice(char* Mac, uint8_t maxTime, int8_t power);


	//! Prints data of last inquiry. Function for debugging purposes only. This function becomes slows after some time.
		/*!
    \return '1' on success, '0' otherwise
    */
	uint8_t printInquiry();


	//! Creates a transparent connection with other bluetooth module using serial port profile
		/*!
    \param char* mac: device mac address to be connected
    \return '1' on success. '0' otherwise
    */
	uint8_t createConnection(char * mac);

	//! Removes a transparent connection
		/*!
    \param
    \return '1' on success. '0' otherwise
    */
	uint8_t removeConnection();

	//! Sends data trough a transparent connection with other bluetooth module using serial port profile
		/*!
    \param char* data: data to be sent
    \return '1' on success. '0' otherwise
    */
	uint8_t sendData(char *data);

	//! Sends data trough a transparent connection with other bluetooth module using serial port profile
	/*! length is defined by an input parameter
    \param char* data: data to be sent
    \return '1' on success. '0' otherwise
    */
	uint8_t sendData(uint8_t* data, uint16_t length);

	//! Enters command mode of bluetooth module
		/*!
    \param char* Mac: Mac of device to discover
    \return '1' on success. '0' otherwise
    */
	uint8_t enterCommandMode();

	//! Switches from command mode to data mode
		/*!
    \param char* Mac: Mac of device to discover
    \return '1' on success. '0' otherwise
    */
	uint8_t returnToDataMode();


	//!  Checks if there are active conenctions. Maximun connections are 7
		/*!
    \return 0-7 number of active connections, -1 error entering command mode.
    */
	int8_t checkActiveConnections();

	//!  Updates the Receiver Signal Strength Indication of the variable linkRSSI
		/*!
	\return '1' if RSSI obtained, '0' if no connections, '-1' if error in command mode, '-2' if link not active.
    */
	uint8_t getRSSI();

	//!  Updates the Receiver Signal Strength Indication of the variable linkRSSI of the link given as a parameter
		/*!
	\param uint8_t linkID: link ID of the connection
    \return '1' if RSSI obtained, '0' if no connections, '-1' if error in command mode, '-2' if link not active.
    */
	uint8_t getRSSI(uint8_t linkID);

	//!  Pair with other module, with default pin code 123456. It has a timeout
    //!  of 20 seconds. Note: the AUTH event can be enabled to see when a device is trying to pair.
		/*!
	\param char* macAddress: Mac address of the device to pair.
    \return '1' if pairing ok, '0' otherwise.
    */
	uint8_t pair(char* macAddress);

	//!  Pair with other module, specifying Pin code. It has a timeout
    //!  of 20 seconds. Note: the AUTH event can be enabled to see when a device is trying to pair.
		/*!
	\param char* macAddress: Mac address of the device to pair.
	\param char  * pincode: PIN code for pairing process
    \return '1' if pairing ok, '0' otherwise.
    */
	uint8_t pair(char* macAddress, char * pinCode);

	//!  removes al paired devices
		/*!
	\param void
    \return void
    */
	void removePairedDevices();

	//!  removes all paired devices. mac address must not have capital leters:
	//! ok    --> "00:1a:f0:90:b3:c8"
	//! wrong --> "00:1A:F0:90:B3:C8"
		/*!
	\param char * deviceMac: mac of device to check.
    \return returns '1' if pared, '0' otherwise
    */
	uint8_t isPaired(char * deviceMac);

};
extern WaspBT_Pro BT_Pro;
#endif
