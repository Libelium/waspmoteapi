/*! \file WaspXBeeCore.h
    \brief Library for managing the XBee modules

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
    Implementation:	Alberto Bielsa, Yuri Carmona

 */

/*! \def WaspXBeeCore_h
    \brief The library flag

 */
#ifndef WaspXBeeCore_h
#define WaspXBeeCore_h


/******************************************************************************
 * Includes
 ******************************************************************************/

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "WConstants.h"
#include "WaspUSB.h"
#include "pins_waspmote.h"
#include "WaspConstants.h"
#include <inttypes.h>

// SD Utilities
#include <WaspSD.h>



/******************************************************************************
 * Definitions
 ******************************************************************************/

//Different protocols used in the libraries
#define XBEE_802_15_4 	1
#define	ZIGBEE 			2
#define	DIGIMESH 		3
#define XBEE_900 		4
#define XBEE_868 		5
#define XBEE_900HP 		6
#define XBEE_868LP 		7


//Different modes
#define UNICAST 	0
#define BROADCAST 	1
#define CLUSTER 	2

//Different RX frame types
#define _16B 		0 //only for XBee-802.15.4
#define _64B 		1 //only for XBee-802.15.4
#define NORMAL_RX 	2 // Receive packet --> AO=0
#define EXPLICIT_RX	3 // Explicit RX Indicator --> AO=1

//Different Max Sizes Used in Libraries
#define MAX_DATA			300
#define	MAX_PARSE			300
#define	MAX_BROTHERS		5
#define MAX_FINISH_PACKETS	5

//Differents addressing types
#define	MY_TYPE		0
#define	MAC_TYPE	1

//Variable for debugging
#define	DEBUG_XBEE	0

#define PRINT_XBEE(str)	USB.print(F("[XBEE] ")); USB.print(str);
#define PRINTLN_XBEE(str)	USB.print(F("[XBEE] ")); USB.println(str);

// Replacement Policy
#define	XBEE_LIFO	0
#define	XBEE_FIFO	1
#define	XBEE_OUT	2


/******************* 802.15.4 **************************/

//Awake Time
#define AWAKE_TIME_802_15_4_H		0x13
#define AWAKE_TIME_802_15_4_L		0x88

//Sleep Time
#define SLEEP_TIME_802_15_4_H		0x00
#define SLEEP_TIME_802_15_4_L		0x00

//Scan Time
#define SCAN_TIME_802_15_4			0x19

//Scan Channels
#define SCAN_CHANNELS_802_15_4_H	0x1F
#define SCAN_CHANNELS_802_15_4_L	0xFE

//Encryption Mode
#define ENCRYPT_MODE_802_15_4		0x00

//Power Level
#define POWER_LEVEL_802_15_4		0x04

//Time RSSI
#define TIME_RSSI_802_15_4			0x28

//Sleep Options
#define	SLEEP_OPTIONS_802_15_4		0x00



/******************* ZB **************************/

//Awake Time
#define AWAKE_TIME_ZIGBEE_H		0x13
#define AWAKE_TIME_ZIGBEE_L		0x88

//Sleep Time
#define SLEEP_TIME_ZIGBEE_H		0x00
#define SLEEP_TIME_ZIGBEE_L		0x20

//Scan Time
#define	SCAN_TIME_ZIGBEE		0x3C

//Scan Channels
#define SCAN_CHANNELS_ZIGBEE_H	0x3F
#define SCAN_CHANNELS_ZIGBEE_L	0xFF

//Time Energy Channel
#define TIME_ENERGY_CHANNEL_ZIGBEE	0x03

//Encryption Mode
#define ENCRYPT_MODE_ZIGBEE		0x00

//Power Level
#define POWER_LEVEL_ZIGBEE		0x04

//Time RSSI
#define TIME_RSSI_ZIGBEE		0x28

//Sleep Options
#define	SLEEP_OPTIONS_ZIGBEE	0x00




/******************* DM **************************/

//Awake Time
#define AWAKE_TIME_DIGIMESH_H	0x00
#define AWAKE_TIME_DIGIMESH_M	0x07
#define AWAKE_TIME_DIGIMESH_L	0xD0

//Sleep Time
#define SLEEP_TIME_DIGIMESH_H	0x00
#define SLEEP_TIME_DIGIMESH_M	0x00
#define SLEEP_TIME_DIGIMESH_L	0xC8

//Scan Time
#define SCAN_TIME_DIGIMESH_H	0x00
#define SCAN_TIME_DIGIMESH_L	0x82

//Encryption Mode
#define ENCRYPT_MODE_DIGIMESH	0x00

//Power Level
#define POWER_LEVEL_DIGIMESH	0x04

//Time RSSI
#define TIME_RSSI_DIGIMESH		0x20

//Sleep Options
#define	SLEEP_OPTIONS_DIGIMESH	0x00




/******************* OTAP **************************/
#define	BOOT_LIST			"BOOT.TXT"
#define	delay_start			1
#define	delay_end			3000
#define	MAX_OTA_RETRIES		3
#define	OTA_TIMEOUT			10000 //milliseconds

// OTA frame types
#define DELETE_FRAME 			0x78
#define CHECK_NEW_PROG_FRAME 	0x79
#define NEW_FIRM_RECEIVED_FRAME 0x7A
#define NEW_FIRM_PACKET_FRAME 	0x7B
#define NEW_FIRM_END_FRAME 		0x7C
#define UPLOAD_FIRM_FRAME 		0x7D
#define REQUEST_ID_FRAME 		0x7E
#define REQUEST_BOOT_FRAME 		0x7F



/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

//! Structure : used for storing the information returned by other nodes when a
//! Node Discovery is performed
/*!
 */
struct Node
{
	//! Structure Variable : 16b Network Address
	/*!
 	*/
	uint8_t MY[2];

	//! Structure Variable : 32b Lower Mac Source
	/*!
	 */
	uint8_t SH[4];

	//! Structure Variable : 32b Higher Mac Source
	/*!
	 */
	uint8_t SL[4];

	//! Structure Variable : Node Identifier
	/*!
	 */
	char NI[21];

	//! Structure Variable : Parent 16b Network Address (ZigBee)
	/*!
	 */
	uint8_t PMY[2];

	//! Structure Variable : Device Type: 0=End 1=Router 2=Coord (ZigBee)
	/*!
	 */
	uint8_t DT;

	//! Structure Variable : Status: Reserved (ZigBee)
	/*!
	 */
	uint8_t ST;

	//! Structure Variable : Profile ID (ZigBee)
	/*!
	 */
	uint8_t PID[2];

	//! Structure Variable : Manufacturer ID (ZigBee)
	/*!
	 */
	uint8_t MID[2];

	//! Structure Variable : Receive Signal Strength Indicator
	/*!
	 */
	uint8_t RSSI;
};

//! Structure : used for storing the information needed to send or receive a
//! packet, such as the addresses and data
/*!
 */
struct packetXBee
{
  private:
  public:
  /************ IN ***********/
	//! Structure Variable : 32b Lower Mac Destination
	/*!
 	*/
	uint8_t macDL[4];

	//! Structure Variable : 32b Higher Mac Destination
	/*!
	 */
	uint8_t macDH[4];

	//! Structure Variable : Sending Mode:
	//! 0=UNICAST ; 1=BROADCAST ; 2=CLUSTER
	/*!
	 */
	uint8_t mode;

	//! Structure Variable : Address Type -> 0=16B ; 1=64B
	/*! Only available for XBee-802.15.4 in order to specify what sort of
	 *  addressing has been used: 16-b or 64-b addressing
	 */
	uint8_t address_type;

	//! Structure Variable : 16b Network Address Destination
	/*!
	 */
	uint8_t naD[2];

	//! Structure Variable : Data. All the data here, even when it is > payload
	/*!
	 */
	char data[MAX_DATA];

	//! Structure Variable : Real data length.
	/*!
	 */
	uint16_t data_length;

	//! Structure Variable : Source Endpoint (ZigBee)
	/*!
	 */
	uint8_t SD;

	//! Structure Variable : Destination Endpoint (ZigBee)
	/*!
	 */
	uint8_t DE;

	//! Structure Variable : Cluster Identifier (ZigBee)
	/*!
	 */
	uint8_t CID[2];

	//! Structure Variable : Profile Identifier (ZigBee)
	/*!
	 */
	uint8_t PID[2];

	//! Structure Variable : Specifies if Network Address is known:
	//! 0=unknown net address ; 1=known net address
	/*!
	 */
	uint8_t MY_known;

	//! Structure Variable : Sending options (depends on the XBee module)
	/*!
	 */
	uint8_t opt;


	/******** APLICATION *******/

	//! Structure Variable : 32b Lower Mac Source
	/*!
	 */
	uint8_t macSL[4];

	//! Structure Variable : 32b Higher Mac Source
	/*!
	 */
	uint8_t macSH[4];

	//! Structure Variable : 16b Network Address Source
	/*!
	 */
	uint8_t naS[2];

	//! Structure Variable : Receive Signal Strength Indicator
	/*!
	 */
	uint8_t RSSI;

	//! Structure Variable : Address Source Type
	/*! Only available for XBee-802.15.4 in order to specify what sort of
	 *  addressing has been used: 16-b or 64-b addressing
	 */
	uint8_t address_typeS;

	//! Structure Variable : Specifies the time when the first fragment of the
	//! packet was received
	/*!
	 */
	long time;


	/******** OUT **************/

	//! Structure Variable : Delivery Status
	/*!
	 */
	uint8_t deliv_status;

	//! Structure Variable : Discovery Status
	/*!
	 */
	uint8_t discov_status;

	//! Structure Variable : Network Address where the packet has been set
	/*!
	 */
	uint8_t true_naD[2];

	//! Structure Variable : Retries needed to send the packet
	/*!
	 */
	uint8_t retries;
};





//! Structure : used to store information about a new firmware
/*!
 */
struct firmware_struct
{
private:
public:

	//! Structure Variable : New firmware ID
	/*!
	 */
	char ID[33];

	//! Structure Variable : New firmware Date
	/*!
	 */
	char DATE[13];

	//! Structure Variable : New firmware MAC where it was sent
	/*!
	 */
	uint8_t mac_programming[8];

	//! Structure Variable : Number of packets received
	/*!
	 */
	uint16_t packets_received;

	//! Structure Variable : Time in which last OTA packet arrived
	/*!
	 */
	unsigned long	time_arrived;

	//! Structure Variable : New firmware ID
	/*!
	 */
	char name_file[10];

	//! Structure Variable : Number of packet just received
	/*!
	 */
	uint8_t data_count_packet;

	//! Structure Variable : Number of packet received before
	/*!
	 */
	uint8_t data_count_packet_ant;

	//! Structure Variable : Specifies if a packet has been lost
	/*!
	 */
	uint8_t paq_disordered;

	//! Structure Variable : Specifies if the function new_firmware_received
	//! has been executed previously
	/*!
	 */
	uint8_t already_init;

	//! Structure Variable : channel to set after re-programming
	/*!
	 */
	uint8_t channel;

	//! Structure Variable : Auth-key to set after re-programming
	/*!
	 */
	char authkey[8];

	//! Structure Variable : Encryption-key to set after re-programming
	/*!
	 */
	char encryptionkey[16];

	//! Structure Variable : Encryption mode to set after re-programming
	/*!
	 */
	uint8_t encryptionMode;

	//! Structure Variable : multicast type
	//! (0:802.15.4 - 1:DigiMesh/ZB - 2:868/900)
	/*!
	 */
	uint8_t multi_type;
};




//! Structure : header_t
/*! Special frame header for OTA packets
 */
struct header_t
{
	uint8_t start[3]; // <=>
	uint8_t type;	  // frame type
};


//! Structure : delete_firm_t
/*! Special frame structure for OTA packets
 */
struct delete_firm_t
{
	header_t header;
	uint8_t authkey[8];
	uint8_t pid[7];
};



//! Structure : new_firm_received_t
/*!
 */
struct new_firm_received_t
{
	header_t header;
	uint8_t authkey[8];
	uint8_t pid[7];
	uint8_t date[12];
	union
	{
		uint8_t channel; // 802.15.4 multicast /DM
		uint8_t new_authkey[8];	// DM/ZB multicast
		struct	// 868/900 multicast
		{
			uint8_t encryptionkey[16];
			uint8_t new_encryptionkey[16];
		};
	};
};


//! Structure : new_firm_packet_t
/*!
 */
struct new_firm_packet_t
{
	header_t header;
	uint8_t counter;
	uint8_t data[100];
};


//! Structure : new_firm_end_t
/*!
 */
struct new_firm_end_t
{
	header_t header;
	char numPackets[4];
};



//! Structure : upload_firm_t
/*!
 */
struct upload_firm_t
{
	header_t header;
	uint8_t authkey[8];
	uint8_t pid[7];
};


//! Structure : request_id_t
/*!
 */
struct request_id_t
{
	header_t header;
	uint8_t authkey[8];
};


//! Structure : request_boot_t
/*!
 */
struct request_boot_t
{
	header_t header;
	uint8_t authkey[8];
};




//! Structure : rxPacket80_t
/*! This structure defines the XBee API frames related to RX data.
 * The Frame type for this sort frames is 0x80.
 */
struct rxPacket80_t
{
	uint8_t 	start;
	uint16_t 	length;
	uint8_t 	frameType;
	uint8_t 	macS[8];
	uint8_t 	rssi;
	uint8_t 	options;
	uint8_t		data[100];
	uint8_t		checksum;
};

//! Structure : rxPacket81_t
/*! This structure defines the XBee API frames related to RX data.
 * The Frame type for this sort frames is 0x81.
 */
struct rxPacket81_t
{
	uint8_t 	start;
	uint16_t 	length;
	uint8_t 	frameType;
	uint8_t 	naS[2];
	uint8_t 	rssi;
	uint8_t 	options;
	uint8_t		data[100];
	uint8_t		checksum;
};

//! Structure : rxPacket90_t
/*! This structure defines the XBee API frames related to RX data.
 * The Frame type for this sort frames is 0x90.
 */
struct rxPacket90_t
{
	uint8_t 	start;
	uint16_t 	length;
	uint8_t 	frameType;
	uint8_t 	macS[8];
	uint8_t 	reserved[2];
	uint8_t 	options;
	uint8_t		data[100];
	uint8_t		checksum;
};

//! Structure : rxPacket91_t
/*! This structure defines the XBee API frames related to RX data.
 * The Frame type for this sort frames is 0x91.
 */
struct rxPacket91_t
{
	uint8_t 	start;
	uint16_t 	length;
	uint8_t 	frameType;
	uint8_t 	macS[8];
	uint8_t 	reserved[2];
	uint8_t 	srcEndPoint;
	uint8_t 	dstEndPoint;
	uint16_t 	clusterID;
	uint16_t 	profileID;
	uint8_t 	options;
	uint8_t		data[100];
	uint8_t		checksum;
};

extern volatile uint8_t _boot_version;
extern volatile uint16_t WaspRegister;
extern volatile uint16_t WaspRegisterSensor;



/******************************************************************************
 * Class
 ******************************************************************************/

 //! WaspXBeeCore Class
/*!
	WaspXBeeCore Class defines all the variables and functions used for managing
	the XBee modules. In this library, all the common functions are defined to
	be used in the other XBee libraries
 */
class WaspXBeeCore
{

private:

	//! Variable : firm_file is used for OTA new firmware file
	/*!
	*/
	SdFile firm_file;

	//! Variable : boot_file is used for OTA boot.txt file
	/*!
	*/
	SdFile boot_file;

public:

	//! Class constructor
	/*! Initializes buffers
	  \param void
	  \return void
	 */
	WaspXBeeCore()
	{
		// set the default maximum number of retries to '3'
		_send_retries = 3;

		// update WaspRegister for SPI interferences in Waspv15
		WaspRegister |= REG_XBEE_SOCKET0;
	}

	//! It initalizes all necessary variables including its parent's variables
	virtual void init(	uint8_t uart_used );

	//! It gets the own lower 32b MAC
  	/*!
    It stores in global 'sourceMacLow' variable the own lower 32b MAC
    \return '0' on success, '1' otherwise
     */
    uint8_t getOwnMacLow();

	//! It gets the own higher 32b MAC
  	/*!
    It stores in global 'sourceMacHigh' variable the own higher 32b MAC
    \return '0' on success, '1' otherwise
     */
    uint8_t getOwnMacHigh();

	//! It gets the own MAC
  	/*!
    It stores in global 'sourceMacHigh' and 'sourceMacLow' variables the 64b MAC
    \return '0' on success, '1' otherwise
     */
    uint8_t getOwnMac();

	//! It sets the own 16b Network Address
  	/*!
    \param uint8_t NA_H : higher Network Address byte (range [0x00-0xFF])
    \param uint8_t NA_L : lower Network Address byte (range [0x00-0xFF])
    \return '0' on success, '1' otherwise
     */
    uint8_t setOwnNetAddress(uint8_t* NA);
    uint8_t setOwnNetAddress(uint8_t NA_H, uint8_t NA_L);
    uint8_t setOwnNetAddress(char* NA);

	//! It gets the 16b Network Address
  	/*!
    It stores in global 'sourceNA' the 16b Network Address
    \return '0' on success, '1' otherwise
     */
    uint8_t getOwnNetAddress();

	//! It sets the baudrate
  	/*!
    \param uint8_t baud_rate : the baudrate to set the XBee to (range [0-5])
    \return '0' on success, '1' otherwise
     */
    uint8_t setBaudrate(uint8_t baud_rate);

	//! It sets API enabled or disabled
  	/*!
    \param uint8_t api_value : the API mode (range [0-2])
    \return '0' on success, '1' otherwise
     */
    uint8_t setAPI(uint8_t api_value);

	//! It sets API options
  	/*!
    \param uint8_t api_options : the API options (range [0-1])
    \return '0' on success, '1' otherwise
     */
    uint8_t setAPIoptions(uint8_t api_options);

	//! It sets the PAN ID
  	/*!
    \param uint8_t* PANID : the PAN ID (64b - ZigBee ; 16b - Other protocols)
    \return '0' on success, '1' otherwise
     */
    uint8_t setPAN(uint8_t* PANID);

	//! It gets the PAN ID
  	/*!
    It stores in global 'PAN_ID' the PAN ID
    \return '0' on success, '1' otherwise
     */
    uint8_t getPAN();

	//! It sets the sleep mode
  	/*!
    \param uint8_t sleep : the sleep mode (range [0-5])
    \return '0' on success, '1' otherwise
     */
    uint8_t setSleepMode(uint8_t sleep);

	//! It gets the sleep mode
  	/*!
    It stores in global 'sleepMode' the sleep mode
    \return '0' on success, '1' otherwise
     */
    uint8_t getSleepMode();

	//! It sets the time awake before sleeping
  	/*!
    \param uint8_t* awake : the time awake before sleeping (range depends on the XBee module)
    \return '0' on success, '1' otherwise
     */
    uint8_t setAwakeTime(uint8_t* awake);

	//! It sets time the module is slept
  	/*!
    \param uint8_t* sleep : the module is slept (range depends on the XBee module)
    \return '0' on success, '1' otherwise
     */
    uint8_t setSleepTime(uint8_t* sleep);

	//! It sets the channel frequency where module is working on
  	/*!
    \param uint8_t _channel : the channel frequency where module is working on (range depends on the XBee module)
    \return '0' on success, '1' otherwise
     */
    uint8_t setChannel(uint8_t _channel);

	//! It gets the channel frequency where module is working on
  	/*!
    It stores in global 'channel' the channel frequency where module is working on
    \return '0' on success, '1' otherwise
     */
    uint8_t getChannel();

	//! It sets the Node Identifier
  	/*!
    \param char* node : the NI must be a 20 character max string
    \return '0' on success, '1' otherwise
     */
    uint8_t setNodeIdentifier(const char* node);

	//! It gets the Node Identifier
  	/*!
    It stores in global 'nodeID' the Node Identifier
    \return '0' on success, '1' otherwise
     */
    uint8_t getNodeIdentifier();

	//! It scans for brothers in the same channel and same PAN ID
  	/*!
    It stores the given info (SH,SL,MY,RSSI,NI) in global array "scannedBrothers" variable
    It stores in global "totalScannedBrothers" the number of found brothers
    \return '0' on success, '1' otherwise
     */
    uint8_t scanNetwork();

	//! It scans for a brother in the same channel and same PAN ID
  	/*!
    It stores the given info (SH,SL,MY,RSSI,NI) in global array "scannedBrothers" variable
    It stores in global "totalScannedBrothers" the number of found brothers
    \param char* node : 20-byte max string containing NI of the node to search
    \return '0' on success, '1' otherwise
     */
    uint8_t scanNetwork(const char* node);

	//! It sets the time the Node Discovery is scanning
  	/*!
    \param uint8_t* time : the time the Node Discovery is scanning (range [0x01-0xFC])
    \return '0' on success, '1' otherwise
     */
    uint8_t setScanningTime(uint8_t* time);

	//! It gets the time the Node Discovery is scanning
  	/*!
    It stores in global 'scanTime' the time the Node Discovery is scanning
    \return '0' on success, '1' otherwise
     */
    uint8_t getScanningTime();

	//! It sets the options for the network discovery command
  	/*!
    \param uint8_t options : the options for the network discovery command (range [0x00-0x03])
    \return '0' on success, '1' otherwise
     */
    uint8_t setDiscoveryOptions(uint8_t options);

	//! It gets the options for the network discovery command
  	/*!
    It stores in global 'discoveryOptions' the options for the network discovery command
    \return '0' on success, '1' otherwise
     */
    uint8_t getDiscoveryOptions();

	//! It performs a quick search of a specific node.
  	/*!
    It stores the destination address given by AT+DN command to the 'address'
    parameter
    \param char* node : 20-byte max string containing NI of the node to search
    \param uint8_t* address : variable where address is stored
    \return '0' on success, '1' otherwise
     */
    uint8_t nodeSearch(const char* node, uint8_t* address);

	//! It sets the list of channels to scan when performing an energy scan
  	/*!
    \param uint8_t channel_H : higher channel list byte (range [0x00-0xFF])
    \param uint8_t channel_L : lower channel list byte (range [0x00-0xFF])
    \return '0' on success, '1' otherwise
     */
    uint8_t setScanningChannels(uint8_t channel_H, uint8_t channel_L);

	//! It gets the list of channels to scan when performing an energy scan
  	/*!
    It stores in global 'scanChannels' the list of channels to scan when performing an energy scan
    \return '0' on success, '1' otherwise
     */
    uint8_t getScanningChannels();

	//! It sets the time the Energy Scan will be performed
  	/*!
    It stores the energy on each channel in global 'energyChannel' variable. The
    actual scan time on each channel is measured as Time = [(2 ^ED) * 15.36] ms
    \param uint8_t duration : time the energy scan will be performed (range [0-6])
    \return '0' on success, '1' otherwise
     */
    uint8_t setDurationEnergyChannels(uint8_t duration);

	//! It gets the time the Energy Scan will be performed
  	/*!
    It stores in global 'timeEnergyChannel' the time the Energy Scan will be performed
    \return '0' on success, '1' otherwise
     */
    uint8_t getDurationEnergyChannels();

	//! It sets the link key to use in the 128b AES algorithm
  	/*!
    \param char* key : the 128-bit AES encryption key (range [0-0xFFFFFFFFFFFFFFFF])
    \return '0' on success, '1' otherwise
     */
    uint8_t setLinkKey(const char* key);

	//! It sets the encryption mode ON/OFF
  	/*!
    \param uint8_t mode : the encryption mode (range [0-1])
    \return '0' on success, '1' otherwise
     */
    uint8_t setEncryptionMode(uint8_t mode);

	//! It gets the encryption mode ON/OFF
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t getEncryptionMode();

	//! It sets the power level at which RF module transmits
  	/*!
    \param uint8_t mode : power level at which RF module transmits (depends on the XBee module - range [0-4])
    \return '0' on success, '1' otherwise
     */
    uint8_t setPowerLevel(uint8_t value);

    //! It gets the power level at which RF module transmits
  	/*!
    \return '0' on success, '1' otherwise, '2' if command not executed
     */
    uint8_t getPowerLevel();

	//! It gets the Received Signal Strength Indicator
  	/*!
    It stores in global 'valueRSSI' the Received Signal Strength Indicator
    \return '0' on success, '1' otherwise
     */
    uint8_t getRSSI();

	//! It gets the Hardware Version
  	/*!
    It stores in global 'hardVersion' the Hardware Version
    \return '0' on success, '1' otherwise
     */
    uint8_t getHardVersion();

	//! It gets the Software Version
  	/*!
    It stores in global 'softVersion' the Software Version
    \return '0' on success, '1' otherwise
     */
    uint8_t getSoftVersion();

	//! It sets the RSSI time
  	/*!
    \param uint8_t time : amount of time to do the PWM (range [0x00-0xFF])
    \return '0' on success, '1' otherwise
     */
    uint8_t setRSSItime(uint8_t time);

	//! It gets the RSSI time
  	/*!
    It stores in global 'timeRSSI' the RSSI time
    \return '0' on success, '1' otherwise
    */
    uint8_t getRSSItime();

	//! It writes the parameters changed into non-volatil memory, being applied
	//! when the XBee is set OFF
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t writeValues();

	//! It writes the parameters changed into non-volatil memory and applies
	//! them immediately
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t applyChanges();

	//! It resets the XBee firmware
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t reset();

	//! It resets the XBee parameters to factory defaults
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t resetDefaults();

	//! It sets the sleep options
  	/*!
    \param uint8_t soption : the sleep options (range depends on the XBee module)
    \return '0' on success, '1' otherwise
     */
    uint8_t setSleepOptions(uint8_t soption);

	//! It gets the sleep options
  	/*!
    It stores in global 'sleepOptions' the sleep options
    \return '0' on success, '1' otherwise
     */
    uint8_t getSleepOptions();

 	//! It gets the low destination address (AT+DL) when a scan is performed
  	/*!
    \return '0' on success, '-1','1' or '2' otherwise
     */
    uint8_t getDestinationAddress(uint8_t* naD);

	//! It sends a packet to others XBee modules
  	/*!
    \param struct packetXBee* packet : it is filled with the information needed
		to be able to send the packet
    \return '0' on success, '1' otherwise
     */
    uint8_t sendXBee(struct packetXBee* packet);

	//! It sends a packet from one XBee to another XBee in API mode
	/*! This function performs application-level retries.
	 * 	This function is only used for 64-bit addressing.
    \param char* macAddress : destination MAC address
    \param char* data : data to be sent (as string)
    \return '0' on success, '1' error
     */
    uint8_t send( char* macAddress, char* data );

    //! It sends a packet from one XBee to another XBee in API mode
	/*! This function performs application-level retries.
	 * 	This function is only used for 64-bit addressing.
    \param char* macAddress : destination MAC address
    \param uint8_t* pointer : pointer to buffer of data to be sent
    \param uint16_t length  : length of the buffer
    \return '0' on success, '1' error
     */
	uint8_t send( char* macAddress, uint8_t* pointer, uint16_t length );

	//! It sends a packet from one XBee to another XBee in API mode
	uint8_t send( uint8_t* macAddress, char* data );
	uint8_t send( uint8_t* macAddress, uint8_t* pointer, uint16_t length );

	//! It sets the maximum number of application-level retries to be done
	void setSendingRetries(uint8_t num);

	//! It treats the data from XBee UART
  	/*!
    \return '0' on success, '1' otherwise
    */
    int8_t treatData();

    //! This function receives a new xbee data packet
  	/*! If OK, the result is stored in _payload and _length
    \param uint32_t timeout : ms to wait until time-out before a packet arrives
    \return
		'6' --> ERROR: Error escaping character within payload bytes
		'5' --> ERROR: Error escaping character in checksum byte
		'4' --> ERROR: Checksum is not correct
		'3' --> ERROR: Checksum byte is not available
		'2' --> ERROR: Frame Type is not valid
		'1' --> ERROR: timeout when receiving answer
		'0' --> OK: The command has been executed with no errors
     */
    int8_t receivePacketTimeout( uint32_t timeout);

    //! It sets the RTC settings with Meshlium timestamp configuration
	/*!  This function sends a special Frame to Meshlium (Meshlium's MAC address
	 * must be indicated as input), and then Meshlium returns an answer with the
	 * timestamp. This function parses the info and sets the RTC Time and Date.
	 */
    uint8_t setRTCfromMeshlium(char* address);

	//! The user introduces an AT command within a string and the function
	//! executes it without knowing its meaning
  	/*!
    \param char* atcommand : the command to execute. It must finish with a '#'
    \return '0' on success, '1' otherwise
     */
    uint8_t sendCommandAT(const char *atcommand);

	//! It connects XBee, activating switch and opens the UART0
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t ON();

    //! It connects XBee, activating switch and opens the selected UART
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t ON(uint8_t uart_used);

	//! It disconnects XBee, switching it off and closing the UART
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t OFF();

	//! It sets the XBee to sleep, asserting PIN 9
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t sleep();

	//! It wakes up the XBee, de-asserting PIN 9
  	/*!
    \return '0' on success, '1' otherwise
     */
    uint8_t wake();


    //! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param uint8_t* address : the receiver MAC
    \param char* data : the data to send
    \return '1' on success
     */
    int8_t setDestinationParams(	packetXBee* paq,
									uint8_t* address,
									const char* data);

	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param uint8_t* address : the receiver MAC
    \param char* data : the data to send
    \param uint8_t type : origin identification type (using this function call,
			it only can be used MAC_TYPE)
    \return '1' on success
     */
    int8_t setDestinationParams(	packetXBee* paq,
									uint8_t* address,
									const char* data,
									uint8_t type	);



	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param char* address : the receiver MAC
    \param char* data : the data to send
    \return '1' on success
     */
    int8_t setDestinationParams(	packetXBee* paq,
									const char* address,
									const char* data	);


	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param char* address : the receiver MAC
    \param char* data : the data to send
    \param uint8_t type : origin identification type: MAC_TYPE or MY_TYPE
    \return '1' on success
     */
    int8_t setDestinationParams(	packetXBee* paq,
									const char* address,
									const char* data,
									uint8_t type	);

	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param uint8_t* address : the receiver MAC
    \param uint8_t* data : the data to send
    \param int length : length of the data field
    \return '1' on success
     */
	int8_t setDestinationParams(	packetXBee* paq,
									uint8_t* address,
									uint8_t* data,
									uint16_t length	);


	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param uint8_t* address : the receiver MAC
    \param uint8_t* data : the data to send
    \param int length : length of the data field
    \param uint8_t type : origin identification type: MAC_TYPE or MY_TYPE
    \return '1' on success
     */
	int8_t setDestinationParams(	packetXBee* paq,
									uint8_t* address,
									uint8_t* data,
									uint16_t length,
									uint8_t type	);


	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param char* address : the receiver MAC
    \param uint8_t* data : the data to send
    \param int length : length of the data field
    \return '1' on success
     */
	int8_t setDestinationParams(	packetXBee* paq,
									const char* address,
									uint8_t* data,
									uint16_t length	);

	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param char* address : the receiver MAC
    \param uint8_t* data : the data to send
    \param int length : length of the data field
    \param uint8_t type : origin identification type: MAC_TYPE or MY_TYPE
    \return '1' on success
     */
	int8_t setDestinationParams(	packetXBee* paq,
									const char* address,
									uint8_t* data,
									uint16_t length,
									uint8_t type	);

	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param uint8_t* address : the receiver MAC
    \param int data : the data to send
    \return '1' on success
     */
    int8_t setDestinationParams(	packetXBee* paq,
									uint8_t* address,
									int data	);

	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param uint8_t* address : the receiver MAC
    \param int data : the data to send
    \param uint8_t type : origin identification type (using this function call,
			it only can be used MAC_TYPE)
    \return '1' on success
     */
    int8_t setDestinationParams(	packetXBee* paq,
									uint8_t* address,
									int data,
									uint8_t type	);

	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param char* address : the receiver MAC
    \param int data : the data to send
    \return '1' on success
     */
    int8_t setDestinationParams(	packetXBee* paq,
									const char* address,
									int data	);

	//! It sets the destination parameters, such as the receiver address and
	//! the data to send
  	/*!
    \param packetXBee* paq : a packetXBee structure where some parameters should
			have been filled before calling this function. After this call, this
			structure is filled with the corresponding address and data
    \param char* address : the receiver MAC
    \param int data : the data to send
    \param uint8_t type : origin identification type: MAC_TYPE or MY_TYPE
    \return '1' on success
     */
    int8_t setDestinationParams(	packetXBee* paq,
									const char* address,
									int data,
									uint8_t type	);


	//! It clears the variable 'command'
  	/*!
     */
    void clearCommand();

	//! It checks the new firmware upgrade
  	/*!
	\return void
	 */
	void checkNewProgram();

	//! It checks if timeout is up while sending program packets
  	/*!
	\return '1':Timeout is up.  '0':The function was executed with no errors
	 */
	uint8_t checkOtapTimeout();

	//! It checks if there is available data in selected UART
  	/*!
	\return number of available bytes.
	 */
	uint8_t available();

	//! It clears the UART buffer
  	/*!
	\param void
	\return void
	 */
	void flush();



	/// Attributes /////////////////////////////////////////////////////////////

	//! Variable : it stores if the XBee module is ON or OFF (0-1)
	/*!
	 */
	uint8_t XBee_ON;

	//! Variable : 32b Lower Mac Source
	/*!
	 */
	uint8_t sourceMacLow[4];

	//! Variable : 32b Higher Mac Source
	/*!
	 */
   	uint8_t sourceMacHigh[4];

	//! Variable : 16b Network Address
	/*!
	 */
   	uint8_t sourceNA[2];

	//! Variable : Baudrate, speed used to communicate with the XBee module (0-5)
	/*!
	 */
    uint8_t baudrate;

	//! Variable : Api value selected (0-2)
	/*!
	 */
    uint8_t apiValue;

	//! Variable : 64b PAN ID
	/*!
	 */
	uint8_t PAN_ID[8];

	//! Variable : Current Sleep Mode (0-5)
	/*!
	 */
	uint8_t sleepMode;

	//! Variable : array for storing the packets received completely
	/*!
	 */
	packetXBee *packet_finished[MAX_FINISH_PACKETS];

	//! Variable : real number of complete received packets
	/*!
	 */
	uint8_t totalPacketsReceived;

	//! Variable : indicates the position in 'packet_finished' array of each packet
	/*!
	 */
	uint8_t	pos;

	//! Variable : array for storing the information answered by the nodes when
	//! a Node Discovery is performe
	/*!
	 */
	Node scannedBrothers[MAX_BROTHERS];

	//! Variable : number of brothers found
	/*!
	 */
	int8_t totalScannedBrothers;

	//! Variable : time to be idle before start sleeping
	/*!
	 */
	uint8_t awakeTime[3];

	//! Variable : Cyclic sleeping time
	/*!
	 */
	uint8_t sleepTime[3];

	//! Variable : Channel frequency where the module is currently working on
	/*!
	 */
	uint8_t channel;

	//! Variable : Node Identifier
	/*!
	 */
	char nodeID[20];

	//! Variable : time meanwhile the Node Discovery is scanning
	/*!
	 */
	uint8_t scanTime[2];

	//! Variable : options for the network discovery command
	/*!
	 */
    uint8_t discoveryOptions;

	//! Variable : list of channels to scan when performing an energy scan
	/*!
	 */
	uint8_t scanChannels[2];

	//! Variable : energy found on each channel
	/*!
	 */
	uint8_t energyChannel[20];

	//! Variable : time the Energy Scan is going to be performed
	/*!
	 */
	uint8_t timeEnergyChannel;

	//! Variable : 128b AES Link key
	/*!
	 */
	char linkKey[17];

	//! Variable : encryption mode (ON/OFF) (0-1)
	/*!
	 */
	uint8_t encryptMode;

	//! Variable : power level at which the RF transmits
	/*!
	 */
	uint8_t powerLevel;

	//! Variable : time meanwhile the PWM output is active after receiving a packet
	/*!
	 */
	uint8_t timeRSSI;

	//! Variable : software Version
	/*!
	 */
	uint8_t softVersion[4];

	//! Variable : hardware Version
	/*!
	 */
	uint8_t hardVersion[2];

	//! Variable : received Signal Strength Indicator
	/*!
	 */
	uint8_t valueRSSI[2];

	//! Variable : sleep Options
	/*!
	 */
	uint8_t sleepOptions;

	//! Variable : Answer received after executing "sendCommandAT" function
	/*!
	 */
    uint8_t commandAT[100];

	//! Variable : It stores the last Modem Status indication received
	/*!
	 */
	uint8_t modem_status;

	//! Variable : It specifies the replacement ploicty to implement (FIFO, LIFO or OUT)
	/*!
	 */
	uint8_t replacementPolicy;

	//! Variable : It stores if the last call to an AT command has generated an error
	/*!
	 */
	int8_t error_AT;

	//! Variable : It stores if the last received packet has generated an error
	/*!
	 */
	int8_t error_RX;

	//! Variable : It stores if the last sent packet has generated an error
	/*!
	 */
	int8_t error_TX;

	//! Variable : specifies the firmware information
  	/*!
	 */
	firmware_struct firm_info;

	//! Variable : specifies if the re-programming process is running
  	/*!
	 */
	uint8_t programming_ON;

	//! Variable : buffer for a received data packet
  	/*!
	 */
	uint8_t 	_payload[MAX_DATA];

	//! Variable : specifies the number of bytes in _payload
  	/*!
	 */
	uint16_t 	_length;

	//! Variable : specifies the source MAC Adddress when a packet is received
  	/*!
	 */
	uint8_t 	_srcMAC[8];

	//! Variable : specifies the source Network Adddress when a packet is received
  	/*!
	 */
	uint8_t 	_srcNA[2];

	//! Variable : specifies the RSSI received in the last packet
  	/*!
	 */
	int 	_rssi;

	//! Variable : specifies the maximum number of retries to be done
  	/*! If the sending process fails, up to _send_retries are done
	 */
	uint8_t _send_retries;

protected:


	//! It reads a packet from other XBee module
  	/*! It should be called when data is available from the XBee. If the
  	available data is not a packet it will handle it and will return the
  	appropriate message
    \return '0' on success, '1' when error, '-1' when no memory is available
    */
    int8_t readXBee(uint8_t* data);

	//! It sends a packet to other XBee modules
  	/*!
      \param struct packetXBee* packet : the function gets the needed information to send the packet from it
      \return '0' on success, '1' otherwise
         */
    virtual uint8_t sendXBeePriv(struct packetXBee* packet);

	//! It generates the API frame to send to the XBee module
  	/*!
      \param const char* data : the string that contains part of the API frame
      \param uint8_t param : input parameter to set using the AT command
      \return void
         */
      void gen_data(const char* data, uint8_t param);

	//! It generates the API frame to send to the XBee module
  	/*!
      \param const char* data : the string that contains part of the API frame
      \return void
         */
      void gen_data(const char* data);

	//! It generates the API frame to send to the XBee module
  	/*!
      \param const char* data : the string that contains part of the API frame
      \param uint8_t param1 : higher part of the input parameter to set using the AT command
      \param uint8_t param2 : lower part of the input parameter to set using the AT command
      \return void
         */
      void gen_data(const char* data, uint8_t param1, uint8_t param2);

	//! It generates the API frame to send to the XBee module
  	/*!
      \param const char* data : the string that contains part of the API frame
      \param uint8_t* param : input parameter to set using the AT command
      \return void
         */
      void gen_data(const char* data, uint8_t* param);

	//! It generates the API frame to send to the XBee module
  	/*!
      \param const char* data : the string that contains part of the API frame
      \param char* param : input parameter to set using the AT command
      \return void
         */
      void gen_data(const char* data, const char* param);

	//! It generates the checksum API frame to send to the XBee module
  	/*!
      \param const char* data : the string that contains part of the API frame
      \return the checksum generated
         */
      uint8_t gen_checksum(const char* data);

	//! It sends the API frame stored in 'command' variable to the XBee module
  	/*!
      \param const char* data : the string that contains part of the API frame
      \return '0' if no error, '1' if error
         */
      uint8_t gen_send(const char* data);

	//! It generates the API frame when a TX is done
  	/*!
  	This function is used to generate the XBee data payload, which is composed
  	by the Application header and the final data field.
    \param struct packetXBee* _packet : packet for storing the data to send
    \param uint8_t* TX_array : array for storing the data
    \param uint8_t start_pos: start position
    */
    void genDataPayload(	struct packetXBee* _packet,
							uint8_t* TX_array,
							uint8_t start_pos	);

	//! It generates the frame using eschaped characters
  	/*!
      \param struct packetXBee* _packet : packet for storing the data to send
      \param uint8_t* TX_array : array for storing the data
      \param uint8_t &protect: variable used for storing if some protected character
      \param uint8_t type: variable used for knowing the frame length
         */
      void gen_frame_ap2(struct packetXBee* _packet, uint8_t* TX_array, uint8_t &protect, uint8_t type);

	//! It parses the answer received by the XBee module, calling the appropriate function
  	/*!
      \param uint8_t* frame : an array that contains the API frame that is expected to receive answer from if it is an AT command
      \return '0' if no error, '1' if error
         */
      int8_t parse_message(uint8_t* frame);

	//! It generates the correct API frame from an eschaped one
  	/*!
	\param uint8_t* data_in : the string that contains the eschaped API frame AT command
	\param uint16_t end : the end of the frame
	\param uint16_t start : the start of the frame
	\return '0' if no error, '1' if error
	*/
    void des_esc(uint8_t* data_in, uint16_t end, uint16_t start);

	//! It generates the correct API frame from a non-eschaped one
  	/*! This function is used by gen_send function which sends the correct escaped
  	frame to the XBee module.
    \param uint8_t* TX : pointer to the array where the correct escaped frame
		is stored
    \param uint8_t* data : pointer to the actual non-escaped frame
    \param int* final_length : pointer where the final frame length is stored
	\return void
	*/
    void gen_escaped_frame(	uint8_t* TX,
							uint8_t* data,
							int* final_length);

	//! It parses the AT command answer received by the XBee module
  	/*!
      \param uint8_t* data_in : the string that contains the eschaped API frame AT command
      \param uint8_t* frame : an array that contains the API frame that is expected to receive answer from if it is an AT command
      \param uint16_t end : the end of the frame
      \param uint16_t start : the start of the frame
      \return '0' if no error, '1' if error
         */
      uint8_t atCommandResponse(uint8_t* data_in, uint8_t* frame, uint16_t end, uint16_t start);

	//! It parses the Modem Status message received by the XBee module
  	/*!
      \param uint8_t* data_in : the string that contains the eschaped API frame AT command
      \param uint16_t end : the end of the frame
      \param uint16_t start : the start of the frame
      \return '0' if no error, '1' if error
         */
      uint8_t modemStatusResponse(uint8_t* data_in, uint16_t end, uint16_t start);

	//! It parses the TX Status message received by the 802.15.4 XBee module
  	/*!This function is used only for 802.15.4 protocol
      \param uint8_t* ByteIN : array to store the received answer
      \return '0' if no error, '1' if error
         */
      uint8_t txStatusResponse();

	//! It parses the ZB TX Status message received by the XBee module
  	/*!This function is used for all protocols, but the 802.15.4
      \param uint8_t* ByteIN : array to store the received answer
      \return '0' if no error, '1' if error
         */
      uint8_t txZBStatusResponse();

	//! It parses the RX Data message received by the XBee module
  	/*!
      \param uint8_t* data_in : the string that contains the eschaped API frame AT command
      \param uint16_t end : the end of the frame
      \param uint16_t start : the start of the frame
      \return '0' if no error, '1' if error
         */
      int8_t rxData(uint8_t* data_in, uint16_t end, uint16_t start);

	//! It parses the ND message received by the XBee module
  	/*!
	It stores in 'scannedBrothers' variable the data extracted from the answer
	 */
	void treatScan();

	//! It checks the checksum is good
  	/*!
    \param uint8_t* data_in : the string that contains the eschaped API frame AT command
    \param uint16_t end : the end of the frame
	\param uint16_t start : the start of the frame
	\return '0' if no error, '1' if error
	*/
	uint8_t checkChecksum(uint8_t* data_in, uint16_t end, uint16_t start);

	//! It gets the TX frame checksum
  	/*!
    \param uint8_t* TX : the pointer to the generated frame which checksum has
    to be calculated
	\return calculated checksum
	*/
	uint8_t getChecksum(uint8_t* TX);


	//! It gets the next index where store the finished packet
  	/*!
        \return the index where store the packet
         */
        uint8_t getFinishIndex();

	//! It clears the finished packets array
  	/*!
         */
        void clearFinishArray();

	//! It gets the index in 'packet_finished' where store the new packet, according to a FIFO policy
  	/*!
        \return the index where store the packet
         */
        uint8_t getIndexFIFO();

	//! It gets the index in 'packet_finished' where store the new packet, according to a LIFO policy
  	/*!
        \return the index where store the packet
         */
        uint8_t getIndexLIFO();


	//! It receives the first packet of a new firmware
  	/*!
	\return 1 if error, 0 otherwise
	 */
	uint8_t new_firmware_received();

	//! It receives the data packets of a new firmware
  	/*!
	\return void
	 */
	void new_firmware_packets();

	//! It receives the last packet of a new firmware
  	/*!
	\return void
	 */
	void new_firmware_end();

	//! It uploads the new firmware
  	/*!
	\return void
	 */
	void upload_firmware();

	//! It answers the ID requested
  	/*!
	\return void
	 */
	void request_ID();

	//! It answers the boot list file
  	/*!
	\return void
	 */
	void request_bootlist();

	//! It deletes the firmware required
  	/*!
	\return void
	 */
	void delete_firmware();

	//! It sets the previous configuration in multicast transmissions
  	/*!
	\return void
	 */
	void setMulticastConf();

	//! Variable : protocol used (depends on de the XBee module)
  	/*!
	 */
	uint8_t protocol;

	//! Variable : it stores the UART where the dara are sent to (UART0 or UART1)
	/*!
	 */
	uint8_t uart;

	//! Variable : internal variable used to store the data length
  	/*!
	 */
   	uint16_t data_length;

	//! Variable : it stores the data received in each frame
  	/*!
	 */
   	uint8_t data[50];

	//! Variable : internal counter
  	/*!
	 */
	uint16_t it;

	//! Variable : address type
  	/*! It can be:
  	 * 	 _16B --> for 16-Bit address RX frames (only XBee-802.15.4 protocol)
  	 * 	 _64B --> for 64-bit address RX frames (only XBee-802.15.4 protocol)
  	 * 	 NORMAL_RX --> for normal RX frames (for all XBee protocols but 802.15.4)
  	 * 	 EXPLICIT_RX --> for explicit RX indicator frames (for all XBee protocols but 802.15.4)
	 */
	uint8_t rxFrameType;

	//! Variable : array to store the AT commands
  	/*!
	 */
	uint8_t command[30];

	//! Variable : index data to make a packet from many different data
  	/*! This variable is used to fill different data arguments as DATA_OFFSET
  	 * when calling setDestinationParams function
	 */
	uint16_t data_ind;

	//! Variable : delivery packet status
  	/*!
	 */
	uint8_t delivery_status;

	//! Variable : discovery process status
  	/*!
	 */
	uint8_t discovery_status;

	//! Variable : true 16b Network Address where the packet has been sent
  	/*!
	 */
	uint8_t true_naD[2];

	//! Variable : retries done during the sending
  	/*!
	 */
	uint8_t retries_sending;

	//! Variable : flag to indicate if a frame was truncated
  	/*!
	 */
	uint8_t frameNext;

	//! Variable : specifies if APS encryption is enabled or disabled
  	/*!
	 */
	uint8_t apsEncryption;

	//! Variable : object to the SD card
  	/*!
	 */
	Sd2Card card;

	//! Variable : flag to indicate sd card is on
  	/*!
	 */
	uint8_t sd_on;
};


#endif
