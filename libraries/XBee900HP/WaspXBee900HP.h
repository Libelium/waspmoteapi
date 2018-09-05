/*! \file WaspXBee900HP.h
    \brief Library for managing XBee 900 HP modules
    
    Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		3.0
    Design:			David Gascón
    Implementation:	Yuri Carmona
 */
 
#ifndef WaspXBee900HP_h
#define WaspXBee900HP_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <WConstants.h>
#include <WaspXBeeCore.h>
#include <inttypes.h>

/******************************************************************************
 * Definitions
 ******************************************************************************/

//! Transmit Options
#define TO_DIGIMESH				0xC0	// (only 200k firmware)
#define TO_POINT_TO_MULTIPOINT 	0x40


/******************************************************************************
 * Class
 ******************************************************************************/

//! WaspXBee900HP Class
/*!
	WaspXBee900 Class defines all the variables and functions used to manage 
	XBee 900MHz modules. It inherits from 'WaspXBeeCore' class 
	the necessary functions, variables and definitions
 */
class WaspXBee900HP : public WaspXBeeCore
{
  
public:

	//! class constructor
  	/*!	It does nothing
	\param void
	\return void
	 */
	WaspXBee900HP()
	{
		// clear library buffers
		memset( nodeID, 0x00, sizeof(nodeID) );
		memset( linkKey, 0x00, sizeof(linkKey) );
	};

	
	/////////////////////////////   Methods  ///////////////////////////////////	
	
	//! It initializes the necessary variables
  	/*!	It initalizes all the necessary variables
	\param uint8_t uart_used : specifies the UART to be used: SOCKET0 or SOCKET1
	\return void
	 */
	void init(	uint8_t uart_used	);

	//! It gets the REceived Error Count
  	/*! This count is incremented whenever a packet is received which contained 
  	 * integrity errors of some sort. Once the number reaches 0xFFFF, further 
  	 * events will not be counted. The counter can be reset to any 16-bit value 
  	 * by appending a hexadecimal parameter to the command.  
  	 * 
  	 * It stores in global 'errorsRF' variable the number of times the RF 
  	 * receiver detected a CRC or length error
	\return '0' on success, '1' otherwise
	 */
	uint8_t getRFerrors();
	
	//! It gets Good Packets Received 
  	/*! This count is incremented whenever a good frame with a valid MAC header 
  	 * is received on the RF interface. Once the number reaches 0xFFFF, further 
  	 * events will not be counted. The counter can be reset to any 16-bit value 
  	 * by appending a hexadecimal parameter to the command. 
  	 * It stores in global '_goodPackets' variable the number of good frames with 
  	 * valid MAC headers that are received on the RF interface
	\return '0' on success, '1' otherwise
	 */
	uint8_t getGoodPackets();	

	
	//! It gets the Transmission Errors (AT+TR)
  	/*! This count is incremented whenever a MAC transmission attempt exhausts 
  	 * all MAC retries without ever receiving a MAC acknowledgment message from 
  	 * the destination node. Once the number reaches 0xFFFF, further events will 
  	 * not be counted. The counter can be reset to any 16-bit value by appending 
  	 * a hexadecimal parameter to the command. 
  	 * The value is stored in '_transmisionErrors' variable
	\return '0' on success, '1' otherwise
	 */
	uint8_t getTransmisionErrors();
			
	
	//! It gets the available frequencies (AT+AF)
  	/*!	This read only command can be queried to return a bitfield of the 
  	 * frequencies that are available in the module’s region of operation
  	 * This command returns a bitfield. Each bit corresponds to a physical 
  	 * channel. Channels are spaced 400 kHz apart:
  	 * 	Bit 0 – 902.400 MHZ
  	 * 	Bit 1 – 902.800 MHZ
  	 * 		...
  	 * 	Bit 31 – 914.800 MHZ
  	 * 		...
  	 * 	Bit 63 – 927.600 MHZ
  	 * 
  	 * Range: 
  	 * 		0x1FFFFFF to 0x00FFFFFFFFFFFFFFFF
  	 * 
  	 * Default:
  	 * 		USA/Canada: 0x00FFFFFFFFFFFFFFFF (channels 0 – 63)
  	 * 		Australia: 0x00FFFFFFFE00000000 (channels 33 – 63)
  	 * 		Brazil: 0x00FFFFFFFE00000FFF	(channels 0-11, 33 – 63)
  	 * 		Singapore: 0x00FFE00000000000
  	 * 
  	 * The value read from the module is stored in _availableFreq
	\return '0' on success, '1' otherwise
	 */
	uint8_t getAvailableFreq();
	
	
	//! It allows channels to be selectively enabled or disabled (AT+CM)
	/*! This is useful to avoid using frequencies that experience unacceptable 
	 * levels of RF interference.
	 * This command is a bitfield. Each bit in the bitfield corresponds to a 
	 * frequency as defined in the Available Frequencies (AF) command. When a 
	 * bit in the Channel Mask and the corresponding bit in the Available 
	 * Frequencies are both set to 1 then that physical channel may be chosen by 
	 * the module as an active channel for communication.
	 *
	 * Range: 
	 * 		0x1FFFFFF to 0x00FFFFFFFFFFFFFFFF
	 * Default:
	 * 		0xFFFFFFFFFFF7FFFF  (Channel 19: 910.000MHZ is disabled by default)
	\parameter uint32_t mask: new mask value to be set
	\return '0' on success, '1' otherwise
	 */
	uint8_t setChannelMask( uint8_t mask[8] );	
	uint8_t getChannelMask();	
	
	
	//! It gets the Minimum Frequency Count (AT+MF)
  	/*! This read only command can be queried to determine the minimum number 
  	 * of channels that must be enabled with the CM command for proper operation 
  	 * in the modules region of operation.
  	 * Range:
  	 * 		1 to 50
  	 * Default:
  	 * 		USA/Canada:  25
  	 * 		Australia: 25
  	 * 		Brazil: 25
  	 * 		Singapore: 11
  	 * 	
	\return '0' on success, '1' otherwise
	 */
	uint8_t getMinFreqCount();
	
	
	//! It set/gets the Preamble ID (AT+HP)
  	/*!	The preamble ID for which module communicates. Only modules with 
  	 * matching preamble IDs can communicate with each other. Different preamble 
  	 * IDs minimize interference between multiple sets of modules operating in 
  	 * the same vicinity. When receiving a packet this is checked before the 
  	 * network ID, as it is encoded in the preamble, and the network ID is 
  	 * encoded in the MAC header. 
  	 * The value set/get is stored in _preambleID attribute
  	 * Range:	0 to 7
  	 * Default:	0
	\return '0' on success, '1' otherwise
	 */
	uint8_t setPreambleID( uint8_t preambleID );
	uint8_t getPreambleID();
	
	
	
	//! It set/gets the Transmit Options (AT+TO)
  	/*!	This command defines transmission options for all packets originating 
  	 * from this radio. These options can be overridden on a packet-by-packet 
  	 * basis by using the TxOptions field of the API TxRequest frames.
  	 * The value set/get is stored in _transmitOptions attribute
  	 * Bitmap:
  	 * 		Bit 6,7: Delivery Method -> b'00  <invalid option>
  	 * 									b'01 - Point-Multipoint
  	 * 									b’11 - DigiMesh (N/A on 10k product)
  	 * 		Bit 5: reserved
  	 * 		Bit 4: reserved
  	 * 		Bit 3: Trace Route 	-> Enable a Trace Route on all DigiMesh API packets
  	 * 		Bit 2: NACK 		-> Enable a NACK messages on all DigiMesh API packets
  	 * 		Bit 1: Disable RD 	-> Disable Route Discovery on all DigiMesh unicasts
  	 * 		Bit 0: Disable ACK 	-> Disable acknowledgments on all unicasts
  	 * Default:	
  	 * 		0x40 (10k firmware)
  	 * 		0xC0 (200k firmware)  
  	 * 		
	\return '0' on success, '1' otherwise
	 */
	uint8_t setTransmitOptions( uint8_t newTransmitOption );
	uint8_t getTransmitOptions();
	
	
	//! It sends a packet to other XBee modules
  	/*!
    \param struct packetXBee* packet : the function gets the needed information 
			to send the packet from it
    \return '0' on success, '1' otherwise
    */
	uint8_t sendXBeePriv(struct packetXBee* packet);		
		
		
	//! It sets/gets Network Hops (AT+NH)
  	/*! The maximum number of hops expected to be seen in a network route. This 
  	 * value doesn't limit the number of hops allowed, but it is used to 
  	 * calculate timeouts waiting for network acknowledgments
    \param uint8_t nhops: parameter to set
    \return '0' on success, '1' otherwise
    */
	uint8_t setNetworkHops(uint8_t nhops);
	uint8_t getNetworkHops();
	
		
	//! It sets/gets the Network Delay Slots (AT+NN)
  	/*! Set or read the maximum random number of network delay slots before 
  	 * rebroadcasting a network packet
	\param uint8_t dslots: range [0-0x0A]
	\return '0' on success, '1' otherwise
	 */
	uint8_t setNetworkDelaySlots(uint8_t dslots);
	uint8_t getNetworkDelaySlots();
	
	
	//! It sets/gets Mesh Unicast Retries (AT+MR)
  	/*! The maximum number of network packet delivery attempts. If MR is 
  	 * non-zero, packets sent will request a network acknowledgment, and can be 
  	 * resent up to MR+1 times if no acknowledgments are received. We recommend 
  	 * setting this value to 1. If this parameter is set to 0, then network ACKs 
  	 * are disabled. Routes can be found initially, but will never be repaired 
  	 * if a route fails. 
	\remarks supported in the 200k variant only.
	\param uint8_t mesh : the maximum number of network packet delivery attempts 
			(range [0-7])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setMeshNetworkRetries(uint8_t mesh);
	uint8_t getMeshNetworkRetries();
	
	
	//!It sets/gets teh Unicast Mac Retries (AT+RR)
	/*! The maximum number of MAC level packet delivery attempts for unicasts. 
	 * If RR is non-zero packets sent from the radio will request an 
	 * acknowledgment, and can be resent up to RR times if no acknowledgments 
	 * are received.
    \param uint8_t retry: the number of retries to be set (0 to 7)
    \return '0' on success, '1' otherwise
    */
	uint8_t setRetries(uint8_t retry);
	uint8_t getRetries();	
	

	///////////////////////////// Attributes ///////////////////////////////////
	
	//! Variable: the number of times the RF receiver detected a CRC or length error
	uint16_t _errorsRF;
	
	//! Variable: the number of good frames with valid MAC headers that are 
	//! received on the RF interface
	uint16_t _goodPackets;

	//! Variable: the number of MAC frames that exhaust MAC retries without 
	//! ever receiving a MAC acknowledgement message from the adjacent node
	uint16_t _transmisionErrors;
	
	//! Variable: frequencies that are available in the module’s region of 
	//! operation
	uint8_t _availableFreq[8];
	
	//! Variable: Channel mask
	uint8_t _channelMask[8];
	
	//! Variable: Minimum Frequency Count
	uint8_t _minFreqCount;
	
	//! Variable: Minimum Frequency Count
	uint8_t _preambleID;
	
	//! Variable: Transmit Options
	uint8_t _transmitOptions;
	
	//! Variable : the maximum number of hops expected to be seen in a network 
	//! route (range [1-0xFF])
	uint8_t _networkHops;	
	
	//! Variable : the maximum random number of network delay slots before 
	//! rebroadcasting a network packet (range [0-0x0A])
	uint8_t _netDelaySlots;
	
	//! Variable : the maximum number of network packet delivery attempts (range [0-7])
	uint8_t _meshNetRetries;
	
  	/*! Variable : the maximum number of MAC level packet deliveryn attempts for 
  	 * unicasts.
	 */
	uint8_t _retries;
	
	
};


// define the extern object (it is defined in cpp)
extern WaspXBee900HP	xbee900HP;

#endif
