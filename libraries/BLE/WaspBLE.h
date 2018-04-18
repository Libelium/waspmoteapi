/*! \file WaspBLE.h
    \briefLibrary for managing the Bluetooth low energy BLE112

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
    Implementation:	Javier Siscart

*/

/*! \def WaspBLE_h
    \brief The library flag

 */
#ifndef WaspBLE_h
#define WaspBLE_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
/* Debug mode. Possible values are:
 * 0 = no debug messages will be printed
 * 1 = some debug messages will be printed
 * 2 = All messages of internal communication will be printed
 */
#define BLE_DEBUG 0

#define PRINT_BLE(str)	USB.print(F("[BLE] ")); USB.print(str);

// Comment this line to avoid using EEPROM with this library
#define ENABLE_EEPROM_SAVING	1

// General constants
// Default baudrate
#define BT_BLUEGIGA_RATE	115200
//	BLuetooth Sleep pin for SOCKET0. Same as XBEE_SLEEP
#define	BLE_SLEEP	47
//max packet size allowed by the protocol
#define MAX_PACKET_SIZE 65
// time to be waiting a module init answer. 2 seconds default
//#define INIT_TIMEOUT 2000
// time to be waiting module answer. 20 millisecods default
#define ANSWER_TIMEOUT 20
// Default scanning time when not specified.
#define DEFAULT_SCAN_TIME						30
// range from 0 to 15, equivalent to power from -23 to +3 dBm
#define TX_POWER_MAX 15
// EEPROM address to save the last scan results.
#define SCAN_EEPROM_START_ADDRESS			1024
#define SCAN_EEPROM_LIMIT_ADDRESS			1823
#define SCAN_END							0xF0

////////////////////////////
// Bluegiga definitions
////////////////////////////
// GAP Discover Mode
const uint8_t BLE_GAP_DISCOVER_LIMITED = 							0;
const uint8_t BLE_GAP_DISCOVER_GENERIC = 							1;
const uint8_t BLE_GAP_DISCOVER_OBSERVATION = 						2;

// GAP Discoverable mode
const uint8_t BLE_GAP_NON_DISCOVERABLE =							0;
const uint8_t BLE_GAP_LIMITED_DISCOVERABLE = 						1;
const uint8_t BLE_GAP_GENERAL_DISCOVERABLE = 						2;
const uint8_t BLE_GAP_BROADCAST = 									3;
const uint8_t BLE_GAP_USER_DATA = 									4;
const uint8_t BLE_GAP_ENHANCED_BROADCASTING = 						128;

// GAP Connectable mode
const uint8_t BLE_GAP_NON_CONNECTABLE = 							0;
const uint8_t BLE_GAP_DIRECTED_CONNECTABLE = 						1;
const uint8_t BLE_GAP_UNDIRECTED_CONNECTABLE = 					2;
//const uint8_t BLE_GAP_SCANNABLE_CONNECTABLE                       3;

// GAP advertisement policy
const uint8_t BLE_GAP_ADV_POLICY_ALL = 							0;
const uint8_t BLE_GAP_ADV_POLICY_WHITELIST_SCAN = 					1;
const uint8_t BLE_GAP_ADV_POLICY_WHITELIST_CONNECT = 				2;
const uint8_t BLE_GAP_ADV_POLICY_WHITELIST_ALL = 					3;

// GAP scan policy
const uint8_t BLE_GAP_SCAN_POLICY_ALL = 							0;
const uint8_t BLE_GAP_SCAN_POLICY_WHITELIST = 						1;

// Scan active or passive
const uint8_t BLE_PASSIVE_SCANNING = 								0;
const uint8_t BLE_ACTIVE_SCANNING = 								1;

// mac filtering: scan_duplicate_filtering
const uint8_t BLE_MAC_FILTER_DISABLED = 							0;
const uint8_t BLE_MAC_FILTER_ENABLED = 							1;

// Bluetooth address types
const uint8_t BLE_GAP_ADDRESS_TYPE_PUBLIC = 						0;
const uint8_t BLE_GAP_ADDRESS_TYPE_RANDOM = 						1;

// Setting adv or scan response data
const uint8_t BLE_GAP_ADVERTISEMENT = 								0;
const uint8_t BLE_GAP_SCAN_RESPONSE = 								1;

// Enable/disable bonding
const uint8_t BLE_DISABLE_BONDING = 								0;
const uint8_t BLE_ENABLE_BONDING = 								1;

// Enable/disable MITM
const uint8_t BLE_DISABLE_MITM = 									0;
const uint8_t BLE_ENABLE_MITM = 									1;

// Enables indicate write operation
const uint8_t BLE_INDICATE_ENABLED = 								1;
const uint8_t BLE_INDICATE_DISABLED = 								0;

// Event list.
// System events
const uint8_t BLE_EVENT_SYSTEM_BOOT =							  	1;
const uint8_t BLE_EVENT_SYSTEM_DEBUG =							  	2;
const uint8_t BLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_RX =			  	3;
const uint8_t BLE_EVENT_SYSTEM_ENDPOINT_WATERMARK_TX =			  	4;
const uint8_t BLE_EVENT_SYSTEM_SCRIPT_FAILURE =				  	5;
const uint8_t BLE_EVENT_SYSTEM_NO_LICENSE_KEY =				  	6;
// Persistent store events
const uint8_t BLE_EVENT_FLASH_PS_KEY =								7;
// Attribute database events
const uint8_t BLE_EVENT_ATTRIBUTES_VALUE =							8;
const uint8_t BLE_EVENT_ATTRIBUTES_USER_READ_REQUEST =				9;
const uint8_t BLE_EVENT_ATTRIBUTES_STATUS =						10;
// Connection
const uint8_t BLE_EVENT_CONNECTION_STATUS =						11;
const uint8_t BLE_EVENT_CONNECTION_VERSION_IND =					12;
const uint8_t BLE_EVENT_CONNECTION_FEATURE_IND	 =					13;
const uint8_t BLE_EVENT_CONNECTION_RAW_RX =						14;
const uint8_t BLE_EVENT_CONNECTION_DISCONNECTED =					15;
// Attribute cliente events
const uint8_t BLE_EVENT_ATTCLIENT_INDICATED =						16;
const uint8_t BLE_EVENT_ATTCLIENT_PROCEDURE_COMPLETED =			17;
const uint8_t BLE_EVENT_ATTCLIENT_GROUP_FOUND =					18;
const uint8_t BLE_EVENT_ATTCLIENT_ATTRIBUTE_FOUND =				19;
const uint8_t BLE_EVENT_ATTCLIENT_FIND_INFORMATION_FOUND =			20;
const uint8_t BLE_EVENT_ATTCLIENT_ATTRIBUTE_VALUE =				21;
const uint8_t BLE_EVENT_ATTCLIENT_READ_MULTIPLE_RESPONSE =			22;
// Security manager events
const uint8_t BLE_EVENT_SM_SMP_DATA =								23;
const uint8_t BLE_EVENT_SM_BONDING_FAIL =							24;
const uint8_t BLE_EVENT_SM_PASSKEY_DISPLAY =						25;
const uint8_t BLE_EVENT_SM_PASSKEY_REQUEST	 =						26;
const uint8_t BLE_EVENT_SM_BOND_STATUS	 =							27;
// Gerneric access profile events.
const uint8_t BLE_EVENT_GAP_SCAN_RESPONSE =						28;
const uint8_t BLE_EVENT_GAP_MODE_CHANGED =							29;
// Hardware events
const uint8_t BLE_EVENT_HARDWARE_IO_PORT_STATUS =					30;
const uint8_t BLE_EVENT_HARDWARE_SOFT_TIMER =						31;
const uint8_t BLE_EVENT_HARDWARE_ADC_RESULT =						32;



// Struct to save a BLE device and its related data.
struct discoveredDevice
{
	uint8_t mac[6];
	int8_t rssi;
	uint8_t friendlyName[31];
	uint8_t advData[33];
};


/******************************************************************************
 * Class
 ******************************************************************************/
class WaspBLE
{
	/// private methods //////////////////////////
	private:

    //! Variable : Baudrate used to communicate with the Bluetooth module. By default, it is 115200bps
    	/*!
	*/
	uint32_t _baudrateBT;

	//! Variable : UART used by the Bluetooth module
    	/*!
	 */
	uint8_t _uartBT;

	//! Variable : Variable to store answer for a command
    	/*!
	*/
	uint8_t answer[MAX_PACKET_SIZE];

 	//! Variable : Variable to store device addresses in scanning functions
    	/*!
	*/
    uint8_t previousMAC[6];

	//! Variable : General access profile discover mode
    	/*!
	*/
	uint8_t GAP_discover_mode;

	//! Variable : General access profile discoverable mode
    	/*!
	*/
	uint8_t GAP_discoverable_mode;

	//! Variable : Stores General access profile connectable mode
    	/*!
	*/
	uint8_t GAP_connectable_mode;

	//! Variable : Defines at what intervals scanner is started
    	/*!
	*/
	uint8_t scan_interval;

	//! Variable : How long to scan at each scan interval
    	/*!
	*/
	uint8_t scan_window;

	//! Variable : Stores scan policy
    	/*!
	*/
	uint8_t scan_policy;

	//! Variable : Stores advertisement policy
    	/*!
	*/
	uint8_t adv_policy;

	//! Variable : Global to see if active or passive scan is taking process. 0 passive, 1 active.
    	/*!
	*/
	uint8_t active;

	//! Variable : Global to see if dupplicate advertisers are filtered or not.
    	/*!
	*/
	uint8_t scan_duplicate_filtering;

	//! Variable : Global to store TX power
    	/*!
	*/
	uint8_t TXPower;

	//! Variable : maximum advertisement interval
    	/*!
	*/
	uint8_t adv_interval_max;

	//! Variable : minimum advertisement interval
    	/*!
	*/
	uint8_t adv_interval_min;

	//! Variable : Used to identify which of the three advertisement channels are used
    	/*!
	*/
	uint8_t adv_channels;

	//! Variable : Used to select between scan response or advertisement response.
    	/*!
	*/
	uint8_t set_scanrsp;	///FIX!! necessary???

	//! Variable : store last written position of eeprom when saving a scan
    	/*!
	*/
	int scanIndex;

	//! Initializes some variables and module parameters
    	/*!
    \param
    \return Return 1 if OK, 0 if no communication, 2 if errir seting TX power, 3 error if seting MAC filter, 4 if setting GAP mode.
	 */
	uint8_t init();

	//! Sends a binary command to the BLE module by UART interface
    	/*!
    \param uint8_t LL: payload length, low bits.
    \param uint8_t CID: command class ID
    \param uint8_t CMD: Command ID
    \param uint8_t * PL: payload
    \return return 1 if command > 128 bytes; 0 otherwise.
	 */
	uint16_t sendCommand(uint8_t LL, uint8_t CID, uint8_t CMD, uint8_t * PL);

	//! Reads and stores module answer. The module last about 300 milliseconds to answer a command.
    	/*!
    \param uint8_t answerLength: length of expected answer
    \return return error code. 0 if OK, error code otherwise.
	 */
	uint16_t readCommandAnswer(uint8_t answerLength, uint8_t ExpectedErrCode);

	//! parses a scan response event, saving each device data field separately.
    	/*!
    \param uint8_t friendlyName: used to save friendly name. 0 if not used, 1 otherwise.
    \return return 0 if not an ble_evt_gap_scan_response, 2 if EEPROM limit reached (only if EEPROM saving is valid), 1 otherwise
	 */
	uint8_t parseScanEvent(uint8_t friendlyName);

	//! save discovered device on EEPROM
    	/*!
    \param
    \return return 0 if limit reached. 1 otherwise.
	 */
	#ifdef ENABLE_EEPROM_SAVING
	uint16_t saveDevice(uint8_t nameFlag);
	#endif

	//! looks into advertisement data and saves the friendly name of the device.
    	/*!
    \param
    \return 0 if name not found, 1 if complete name found, 2 if shortened name found.
	 */
	uint8_t parseName();

	//! Makes an inquiry to discover specific device by its Mac.
    	/*!
    \param uint8_t * Mac: Mac address of the device to be found
    \param uint8_t maxTime: Time to be looking for this device
    \param int8_t TXPower: TX power used during the scan
    \return '0' if not found. '1' if found, error code otherwise.
	 */
	uint16_t scanDevice(uint8_t* Mac, uint32_t maxTime, uint8_t TXPower);


	/// public methods //////////////////////////
    public:

    //! Variable : Struct to save a BLE device and its data.
    	/*!
	*/
    discoveredDevice BLEDev;

    //! Variable : own mac address
    	/*!
	*/
	char my_bd_addr[13];

    //! Variable : stores error code received from the module.
    	/*!
	*/
    uint16_t errorCode;

    //! Variable : stores number of discovered devices.
    	/*!
	*/
    int16_t numberOfDevices;

	/// FIX! Not used yet
	//! Variable : // 0 = advertiser, 1 = scanner, 2 = Master, 3 = slave;
    	/*!
	*/
	uint8_t deviceRole;

    //! Variable : Handler used for the connection
    	/*!
	*/
	uint8_t connection_handle;

	//! Variable: Auxiliary buffer to save data when an attribute is read/written.
    	/*!
    */
	uint8_t attributeValue[MAX_PACKET_SIZE];

	//! Variable : Variable to store a module event
    	/*!
	*/
    uint8_t event[MAX_PACKET_SIZE];

	//! class constructor
  	/*!
	It does nothing
	\param void
	\return void
	*/
	WaspBLE();

	//! It opens the UART and powers the module
    	/*!
    \param
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
    \param
    \return void
	 */
	void OFF();

	//! Set TX power.
    	/*!
    \param uint8_t power: Power can be a value between 0 and 15 which give the real TX power from -23 to +3dBm
    \return return 0 if OK, 1 if error. this command does not return error code.
	 */
	uint16_t setTXPower(uint8_t power);

	//! sends software reset command to the module. Resets in normal mode
    	/*!
    \param
    \return  '1' if reset OK, '0' if no answer from module.
	 */
	uint8_t reset();

	/// Scanning functions //////////////////////////////////

	//! Makes an inquiry to discover specific device by its Mac.
    	/*!
    \param char* Mac: Mac address of the device to be found
    \return '0' if not found. '1' if found, error code otherwise.
	 */
	uint16_t scanDevice(char * Mac);

	//! Makes an inquiry to discover specific device by its Mac.
    	/*!
    \param char* Mac: Mac address of the device to be found
    \param uint8_t maxTime: Time to be looking for this device
    \param uint8_t TXPower: TX power used during the scan
    \return '0' if not found. '1' if found, error code otherwise.
	 */
	uint16_t scanDevice(char* Mac, uint32_t maxTime, uint8_t TXPower);

	//! Scans network to find other BLE modules.
    	/*!
    \param uint8_t time: Time to be looking for this device
    \param int8_t TXPower: TX power used during the scan
    \return return 0 if scan OK, errorCode if error.
	 */
	uint16_t scanNetwork(uint8_t time, uint8_t TXPower);

	//! Scans network to find other BLE modules.
    	/*!
    \param uint8_t time: Time to be looking for this device
    \return return 0 if scan OK, errorCode if error.
	 */
	uint16_t scanNetwork(uint8_t time);

	//! Scans network till find specified number of devices.
    	/*!
    \param int16_t MaxDevices: Number of devices to be found before stop scanning.
    \param int8_t power: TX power used during the scan
    \return return errorCode
	 */
	uint16_t scanNetworkLimited(int16_t MaxDevices, uint8_t power);

	//! Scans network till find specified number of devices.
    	/*!
    \param int16_t MaxDevices: Number of devices to be found before stop scanning.
    \return return errorCode
	 */
	uint16_t scanNetworkLimited(int16_t MaxDevices);

	//! Cancels a scan procedure.
    	/*!
    \param
    \return  return 0 if OK, err code otherwise.
	 */
	uint16_t scanNetworkCancel();

	//! Scans network to find other BLE modules, including friendly name. Uses active scanning.
    	/*!
    \param uint8_t time: Time to be looking for devices
    \param int8_t TXPower: TX power used during the scan
    \return
	 */
	uint8_t scanNetworkName(uint8_t time, uint8_t TXPower);

	//! Scans network to find other BLE modules, including friendly name. Uses active scanning.
    	/*!
    \param uint8_t time: Time to be looking for devices
    \return return error code in any case.
	 */
	uint8_t scanNetworkName(uint8_t time);

	//! This function configures the discover mode. Default observation mode.
    	/*!
    \param uint8_t discover: discover mode; Limited, generic, observation
    \return return 0 if ok, error code otherwise.
	 */
	uint16_t setDiscoverMode(uint8_t discover);

	//! This functions configures the discoverability mode. default general discoverable mode.
    	/*!
    \param uint8_t discoverable: discoverabillity mode; non discoverable, limited, general, broadcast.
    \return return 0 if ok, error code otherwise.
	 */
	uint16_t setDiscoverableMode(uint8_t discoverable);

	//! This functions configures the connectability mode. default directed conectable mode.
    	/*!
    \param uint8_t connectable: connectable mode; Non connectable, direct connectable, indirect connectable, scannable non connectable.
    \return return 0 if ok, error code otherwise.
	 */
	uint16_t setConnectableMode(uint8_t connectable);

	//! This function ends the current procedure, like a scan.
    	/*!
    \param
    \return return error code in any case
	 */
	uint16_t endProcedure();

	//! This function sets advertisement parameters
    	/*!
    \param uint16_t adv_min: minimum advertisement interval. units of 625 us. range 0x20 to 0x4000.
    \param uint16_t adv_max: maximum adversisement interval. units of 625 us. range 0x20 to 0x4000.
    \param uint8_t adv_ch: bitmask to set which advertisements channels are used.
    \return return error code.
	 */
	uint16_t setAdvParameters(uint16_t adv_min, uint16_t adv_max, uint8_t adv_ch);

	//! Set Advertisement scan Response data
    	/*!
    \param set_scanrsp: advertisement data type; 0 sets advertisement data. 1 sets scan response data.
    \param adv_data: data to send
    \return return 1 if data is truncated, error code otherwise.
	 */
	uint16_t setAdvData(uint8_t set_scanrsp, char* adv_data);

	//! Set Advertisement scan Response data
    	/*!
    \param set_scanrsp: advertisement data type; 0 sets advertisement data. 1 sets scan response data.
    \param adv_data: data to send
    \param adv_data_length: length of adv data.
    \return return 1 if data is truncated, error code otherwise.
	 */
	uint16_t setAdvData(uint8_t set_scanrsp, uint8_t* adv_data, uint8_t adv_data_length);

	//! This function sets scanning parameters
    	/*!
    \param uint16_t scan_interval: default 75 (46.875ms)
    \param uint16_t scan_win: default 50 (31.250 ms)
    \param scanning: 1 = use active scanning; 0 = use passive scanning.
    \return return 0 if ok, error code otherwise.
	 */
	uint16_t setScanningParameters(uint16_t scan_interval, uint16_t scan_window, uint8_t scanning);

	//! This function sets scanning parameters
    	/*!
    \param uint8_t active: 1 = use active scanning; 0 = use passive scanning.
    \return
	 */
	uint16_t setScanningParameters(uint8_t active);

	//! Return current scanning parameters
    	/*!
    \param
    \return returns current scanning parameters: GAP Mode, scan_interval,
	scan_window, active/passive, scan_duplicate_filtering, TX_POWER
	 */
	void  getScanningParameters();

	//! Set scan, connection, and advertising filtering parameters, based on the whitelist
    	/*!
    \param uint8_t Scan Policy: 0 = gap_scan_policy_all; 1 = gap_scan_policy_whitelist
    \param uint8_t Advertising policy: 0 = gap_adv_policy_all ; 1 = gap_adv_policy_whitelist_scan ; 2 = gap_adv_policy_whitelist_connect; 3 = gap_adv_policy_whitelist_all;
	\param uint8_t scan Duplicate filtering: 0 = do not filter; 1 = filter duplicates.
    \return return 0 if OK, error code otherwise.
	 */
	uint16_t setFiltering(uint8_t scan_pol, uint8_t adv_pol, uint8_t scan_duplicate_filter);

	//! Set advertising filtering parameters, based on the whitelist
    	/*!
    \param uint8_t scan Duplicate filtering: 0 = do not filter; 1 = filter duplicates.
    \return return 0 if OK, error code otherwise.
	 */
	uint16_t setFiltering(uint8_t scan_duplicate_filtering);

	//! Reads the internal Temperature sensor of the BLE112. Not calibrated. +-10ªC accuracy.
    	/*!
    \param
    \return return temperature if ok, 0 if error reading.
	 */
	float getTemp();

	//! Reads the internal ADC of the BLE112. Waits for ADC event before exit.
    	/*!
    \param uint8_t input: Selects the ADC input
    \param uint8_t decimation: Resolution of the ADC
    \param uint8_t reference selection.
    \return ADC value (bigEndian) if OK. 0 error or ADC event not found.
	 */
	int16_t ADCRead(uint8_t input, uint8_t decimation, uint8_t reference_selection);

	//! Returns the BLE module MAC address
    	/*!
    \param
    \return Returns the BLE module MAC address
	 */
	char * getOwnMac();

	//! print last scan saved on EEPROM by USB.
    	/*!
    \param
    \return return number of devices printed.
	 */
	uint8_t printInquiry();

	//! similar to AT -> OK
    	/*!
    \param
    \return  return 1 if ok, 0 if no response
	 */
	uint8_t sayHello();

	//!  Define the remote devices allowed to establish a connection.
    	/*!
    \param char * BLEAdrress: MAC of the remote module
    \return : return error code
	 */
	uint16_t whiteListAppend(char * BLEAddress);

	//! Delete all entries of the white list at once.  Do not use this command while advertising or while being connected.
	  	/*!
    \param
    \return 1 if ok, o if error
	 */
	uint8_t whiteListClear();

	//! Remove an entry from the running white list.
    	/*!
    \param char * BLEAdrress: MAC of the remote module
    \return 0 if OK, errorCode otherwise.
	 */
	uint16_t whiteListRemove(char * BLEAddress);


	/// Connection functions ////////////////

	//! This function will start direct connection establishment procedure to a dedicated BLE device.
    	/*!
    \param char BLEAddress: address of BLE device to connect.
    \param uint16_t con_interval_min: Minimum connection interval (units of 1.25ms)
    \param uint16_t con_interval_max: Maximum connection interval (units of 1.25ms)
    \param uint16_t timeout: Supervision timeout (units of 10ms)
    \param uint16_t latency: Slave latency. Defines how many connections intervals a slave may skip.
    \return return 0 if invalid parameters, 1 if connection is successful, error code if error sending conenctDirect command, event identification number otherwise.
	 */
	uint16_t connectDirect(char * BLEAddress, uint16_t conn_interval_min, uint16_t conn_interval_max, uint16_t timeout, uint16_t latency);

	//! This function will start direct connection establishment procedure to a dedicated BLE device.
    	/*!
    \param char BLEAddress: address of BLE device to connect.
    \return return 0 if invalid parameters, 1 if connection is successful, error code otherwise.
	 */
	uint16_t connectDirect(char * BLEAddress);

	//! This function disconnects an active connection
    	/*!
    \param connection: connection handle.
    \return  return 1 if connection handle is not right. error code if error sending command. event identifier if disconnection event not found. 0 if ok.
	 */
	uint16_t disconnect(uint8_t connection);

	//! get RSSI of the given link.
    	/*!
    \param uint8_t connection: handler of the connection
    \return return 0 if error, rssi otherwise.
	 */
	int8_t getRSSI(uint8_t connection);

	//! Disables wake up pin of the BLE module (disables UART interface)
     	/*! allowing module low power modes.
    \param
    \return void
	 */
	 void sleep();

	 //! Enables Wakeup pin (enables AURT interface) and wake up BLE from low power modes
    	/*!
    \param
    \return return 1 if wake up OK (event found), 0 if no event found, event identification number otherwise.
	 */
	uint8_t wakeUp();

	//!  wait for specified time for an event.
    	/*!
    \param unsigned long time: time to be waiting for event
    \return return 0 if no event found,  event identification number otherwise.
	*/
	uint8_t waitEvent(unsigned long time);

	 //! Variable: stores last ADC read value
    	/*!
    \param
    \return
	 */
	int16_t ADCValue;

	//!   Reads and stores module answer. By default read max allowed bytes if possible
    	/*!
    \param
    \return return error code. 0 if OK, error code otherwise.
	 */
	uint16_t readCommandAnswer();

	//!   Sends a custom command to the BLE module. Packet mode is mandatory.
    	/*!
    \param uint8_t * customCommand: command to be sent to the BLE module. It must be in packet mode.
    \param uint8_t length: length of the command to be sent.
    \return return 1 if command exceeds maximum length. 0 otherwise.
	 */
	uint16_t sendCommand(uint8_t * customCommand, uint8_t length);

	//!   Sends a custom command to the BLE module. Packet mode is mandatory.
    	/*!
    \param char * customCommand: command to be sent to the BLE module. It must be in packet mode.
    \return return 1 if command exceeds maximum length. 0 otherwise.
	 */
	uint16_t sendCommand(char * customCommand);

	//!   Start encryption form the given connection
    	/*!
    \param uint8_t handle: connection handle
    \return return error code. 0 if OK, error code otherwise.
	 */
	uint16_t encryptConnection(uint8_t handle);

	//!   Start encryption form the given connection
    	/*!
    \param uint8_t handle: connection handle
    \param uint8_t bondable: enable or disable bonding
    \return return error code. 0 if OK, error code otherwise.
	 */
	uint16_t encryptConnection(uint8_t handle, uint8_t bondable);

	//!   Sets device to bondable mode
    	/*!
    \param uint8_t bondable: enable or disable bonding
    \return return 1 if ok, 0 therwise
	 */
	uint16_t setBondableMode(uint8_t bondable);

	//!  Enters the passkey required for Man-in-the-Middle pairing.
    	/*!
    \param uint8_t handle: connection handle
    \param uint32_t passkey: key.
    \return return error code. 0 if OK, error code otherwise.
	 */
	uint16_t setKey(uint8_t handle, uint32_t passkey);

	//!   deletes all devices bonded
    	/*!
      \return return error code. 0 if OK, error code otherwise.
	 */
	uint16_t deleteBonding();

	//!  return number of bonded devices. maximum of 8
    	/*!
    \return return number of bonded devices. maximum of 8
	 */
	uint16_t getBonding();

	//!  Configures security manager
    	/*!
    \param uint8_t mitm:Man-in-the-middle protection.
    \param uint8_t min_key_size: Minimum key size in bytes. range 7-16
    \param uint8_t io_cap: I/O capabilities See: SMP IO Capabilities
    \return 0 if ok, 1 otherwise
	 */
	uint16_t setSecurityParameters(uint8_t mitm, uint8_t min_key_size, uint8_t io_cap);

	//!   read an attribute from the local database of the BLE device.
    	/*!
    \param uint16_t handle: attribute handler
    \param uint16_t offset: offset
     \return return error code. 0 if OK, error code otherwise.
	 */
	uint16_t readLocalAttribute(uint16_t handle, uint16_t offset);

	//!   read an attribute from the local database of the BLE device (default offset=0).
    	/*!
    \param uint16_t handle: attribute handler
    \return return error code. 0 if OK, error code otherwise.
	 */
	uint16_t readLocalAttribute(uint16_t handle);

	//!   write local attribute to the local GATT database of the BLE device
    	/*!
    \param uint16_t handle: attribute handler
    \param char * data: data to write in the attribute

     \return return 0 if OK, 1 if write ok and indicated ok, error code if error writting, event identification number if other event found
	 */
	uint16_t writeLocalAttribute(uint16_t handle, char * data);

	//!   write local attribute to the local GATT database of the BLE device
    	/*!
    \param uint16_t handle: attribute handler
    \param uint8_t indicate: enables /disable indicate process.
    \param char * data: data to write in the attribute
    \return return 0 if OK, 1 if write ok and indicated ok, error code if error writting, event identification number if other event found
	 */
	uint16_t writeLocalAttribute(uint16_t handle, uint8_t indicate, char * data);

	//!   write local attribute to the local GATT database of the BLE device
    	/*!
    \param uint16_t handle: attribute handler
    \param uint8_t * data: data to write in the attribute
    \param uint8_t length: data length
     \return return 0 if OK, 1 if write ok and indicated ok, error code if error writting, event identification number if other event found
	 */
	uint16_t writeLocalAttribute(uint16_t handle, uint8_t * data, uint8_t length);

	//!   write local attribute of the BLE device, indicate enabled
    	/*!
    \param uint16_t handle: attribute handler
    \param uint8_t indicate: enables /disable indicate process.
    \param uint8_t * data
    \param uint8_t length: data length
     \return return error code. 0 if OK, error code otherwise.
	 */
	uint16_t writeLocalAttribute(uint16_t handle, uint8_t indicate, uint8_t * data, uint8_t length);

	//!   read an attribute from a remote BLE device
    	/*!
    \param uint8_t handle: connection handler
    \param uint16_t handle: attribute handler
     \return return error Code. 0 if OK, 1 if event value not found, error code if error sending command. Event identification number otherwise.
	 */
	uint16_t attributeRead(uint8_t connection_handle, uint16_t att_handle);

	 //!  write an attribute from a remote BLE device
    	/*!
    \param uint8_t handle: connection handler
    \param uint16_t handle: attribute handler
    \param char * data: data to be written
    \return return errorCode in any case. 0 means success. event identification number if write procedure completed event not received.
	 */
	uint16_t attributeWrite(uint8_t connection, uint16_t atthandle, char * data);

	//!  write an attribute from a remote BLE device
    	/*!
    \param uint8_t handle: connection handler
    \param uint16_t handle: attribute handler
    \param uint8_t * data: data to be written
    \param uint8_t length: data length
    \return return errorCode in any case. 0 means success. event identification number if write procedure completed event not received.
	 */
	uint16_t attributeWrite(uint8_t connection, uint16_t atthandle, uint8_t * data, uint8_t length);

	 //!  identify event saved on event buffer.
    	/*!
    \return return event identification number accordint to next list.
	 */
	uint8_t parseEvent();

	//!  get the current status of the BLE module
    	/*!
    \return 255 if status not received, connection status otherwise.
	 */
	uint8_t getStatus(uint8_t connection);

};

extern WaspBLE BLE;
#endif
