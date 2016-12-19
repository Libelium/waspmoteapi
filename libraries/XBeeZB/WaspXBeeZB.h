/*! \file WaspXBeeZB.h
    \brief Library for managing XBee ZigBee modules
    
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
    Implementation:	Alberto Bielsa, Yuri Carmona

 */
 
/*! \def WaspXBeeZB_h
    \brief The library flag
    
 */
#ifndef WaspXBeeZB_h
#define WaspXBeeZB_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include <WConstants.h>
#include "WaspXBeeCore.h"


/******************************************************************************
 * Class
 ******************************************************************************/

//! WaspXBeeZB Class
/*!
WaspXBeeZB Class defines all the variables and functions used to manage XBee 
ZigBee modules. It inherits from 'WaspXBeeCore' class the necessary functions, 
variables and definitions
 */
class WaspXBeeZB : public WaspXBeeCore
{
 
public:
	  
	//! class constructor
  	/*!
	It does nothing
	\param void
	\return void
	 */
	WaspXBeeZB()
    {
		// clear library buffers
		memset( nodeID, 0x00, sizeof(nodeID) );
		memset( linkKey, 0x00, sizeof(linkKey) );
	};
	
	/// Methods ////////////////////////////////////////////////////////////////
	
	//! It initializes the necessary variables
  	/*!
	It initalizes all the necessary variables
	\param uint8_t protocol_used : specifies the protocol used in the XBee 
			module (depends on the XBee module)
	\param uint8_t uart_used : specifies the UART where the data are sent to (0-1)
	\return void
	 */
	void init(	uint8_t uart_used	);
	
	
	//! It resets the network
  	/*!
	\param uint8_t reset : specifies the reset to do (0: reset the node network 
			interface || 1: reset the entirely network)
	\return '0' on success, '1' otherwise
	 */
	uint8_t resetNetwork(uint8_t reset);
	
	//! It gets the 16b parent´s network address
  	/*!
		It stores in global 'parentNA' variable the 16b parent´s network address
	\return '0' on success, '1' otherwise
	 */
	uint8_t getParentNetworkAddress();
	
	//! It gets the number of children which can still connect to the current device
  	/*!
	It stores in global 'remainingChildren' variable the number of children 
	which can still connect to the current device
	\return '0' on success, '1' otherwise
	 */
	uint8_t getRemainingChildren();
	
	//! It sets the current device type
  	/*!
	\param uint8_t* type : the current device type (range [0-0xFFFFFFFF])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setDeviceType(uint8_t* type);
	
	//! It gets the current device type
  	/*!
		It stores in global 'deviceType' variable the current device type
	\return '0' on success, '1' otherwise
	 */
	uint8_t getDeviceType();
	
	//! It gets the bytes that can be used in the payload
  	/*!
		It stores in global 'maxPayloadBytes' variable the bytes that can be used in the payload
	\return '0' on success, '1' otherwise
	 */
	uint8_t getPayloadBytes();
	
	//! It gets the 64-bit Operating Extended PAN ID
  	/*!
	It stores in global 'operating64PAN' variable the 64-bit Operating PAN ID
	\return '0' on success, '1' otherwise
	 */
	uint8_t getOperating64PAN();
	
	//! It gets the 16-bit Operating PAN ID
  	/*!
	It stores in global 'operating16PAN' variable the 16-bit Operating PAN ID
	\return '0' on success, '1' otherwise
	 */
	uint8_t getOperating16PAN();
	
	//! It sets the maximum hops limit
  	/*!
	\param uint8_t type : the maximum hops limit (range [0x00-0xFF])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setMaxUnicastHops(uint8_t hops);
	
	//! It gets the maximum hop limits
  	/*!
	It stores in global 'maxUnicastHops' variable the maximum hop limits
	\return '0' on success, '1' otherwise
	 */
	uint8_t getMaxUnicastHops();
	
	//! It sets the maximum number of hops for each broadcast data transmission
  	/*!
	\param uint8_t bhops : the maximum number of hops for each broadcast data transmission (range [0x00-0x20])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setMaxBroadcastHops(uint8_t bhops);
	
	//! It gets the maximum number of hops for each broadcast data transmission
  	/*!
	It stores in global 'maxBroadcastHops' variable the maximum number of hops for each broadcast data transmission
	\return '0' on success, '1' otherwise
	 */
	uint8_t getMaxBroadcastHops();
	
	//! It sets the ZigBee Stack profile
  	/*!
	\param uint8_t profile : the ZigBee Stack profile (range [0-2])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setStackProfile(uint8_t profile);
	
	//! It gets the ZigBee Stack profile
  	/*!
	It stores in global 'stackProfile' variable the ZigBee Stack profile
	\return '0' on success, '1' otherwise
	 */
	uint8_t getStackProfile();
	
	//! It sets the number of Sleep Periods to not assert XBee pin
  	/*!
	\param uint8_t* periods : the number of Sleep Periods to not assert XBee pin (range [0x20-0xAF0])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setPeriodSleep(uint8_t* periods);
	
	//! It sets the time that a Coordinator/Router allows nodes to join
  	/*! This function sets the NJ parameter. Range: 0 - 0xFF [x 1 sec]. 
  	Default: 0xFF
  	\param uint8_t time : the time that a Coordinator/Router allows nodes to join 
	\return '0' on success, '1' otherwise
	 */
	uint8_t setJoinTime(uint8_t time);
	
	//! It gets the time that a Coordinator/Router allows nodes to join
  	/*!
	It stores in global 'joinTime' variable the time that a Coordinator/Router allows nodes to join
	\return '0' on success, '1' otherwise
	 */
	uint8_t getJoinTime();
	
	//! It sets the channel verification parameter (JV parameter)
  	/*!
	\param uint8_t time : the channel verification parameter (range [0-1])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setChannelVerification(uint8_t verif);
	
	//! It gets the channel verification parameter (JV parameter)
  	/*!
	It stores in global 'channelVerification' variable the channel verification parameter
	\return '0' on success, '1' otherwise
	 */
	uint8_t getChannelVerification();
	
	//! It sets the join notification setting
  	/*!
	\param uint8_t notif : the join notification setting (range [0-1])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setJoinNotification(uint8_t notif);
	
	//! It gets the join notification setting
  	/*!
	It stores in global 'joinNotification' variable the join notification setting
	\return '0' on success, '1' otherwise
	 */
	uint8_t getJoinNotification();
	
	//! It sets the time between consecutive aggregate route broadcast messages
  	/*!
	\param uint8_t anotif : the time between consecutive aggregate route broadcast messages (range [0x00-0xFF])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setAggregateNotification(uint8_t anotif);
	
	//! It gets the time between consecutive aggregate route broadcast messages
  	/*!
	It stores in global 'aggregateNotification' variable the time between consecutive aggregate route broadcast messages
	\return '0' on success, '1' otherwise
	 */
	uint8_t getAggregateNotification();
	
	//! It gets information regarding last node join request
  	/*!
	It stores in global 'associationIndication' variable information regarding last node join request
	\return '0' on success, '1' otherwise
	 */
	uint8_t getAssociationIndication();
	
	//! It sets options for encryption
  	/*!
	\param uint8_t eoptions : options for encryption (range [0-2])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setEncryptionOptions(uint8_t eoptions);
	
	//! It gets options for encryption
  	/*!
	It stores in global 'encrypOptions' variable options for encryption
	\return '0' on success, '1' otherwise
	 */
	uint8_t getEncryptionOptions();
	
	//! It sets the 128-bit AES encryption key
  	/*!
	\param char* key : the 128-bit AES encryption key (range [0-0xFFFFFFFFFFFFFFFF])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setNetworkKey(const char* key);
	
	//! It sets the power mode of the device
  	/*!
	\param uint8_t power : the power mode of the device (range [0-1])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setPowerMode(uint8_t power);
	
	//! It gets the power mode of the device
  	/*!
	It stores in global 'powerMode' variable the power mode of the device
	\return '0' on success, '1' otherwise
	 */
	uint8_t getPowerMode();
	
	//! It gets the voltage on the Vcc pin
  	/*!
	It stores in global 'supplyVoltage' variable the voltage on the Vcc pin
	\return '0' on success, '1' otherwise
	 */
	uint8_t getSupplyVoltage();
	
	//! It sets the Application Layer Encryption
  	/*!
	\param uint8_t mode : enables or disables this encryption mode (XBEE_ON or XBEE_OFF)
	\return '0' on success, '1' otherwise
	 */
	uint8_t setAPSencryption(uint8_t mode);
	
	//! It sends a packet to other XBee modules
  	/*!
    \param struct packetXBee* packet : the function gets the needed information 
			to send the packet from it
    \return '0' on success, '1' otherwise
    */
	uint8_t sendXBeePriv(struct packetXBee* packet);
	
	//! It sets MY_Known flag to '1' and sets the destination network address 
	//! to the packet to be sent.
  	/*!
    \param struct packetXBee* paq :  This is the packet to be set
    \param const char* address : pointer to the destination address
    \return void
    */
	void setKnownDestination(packetXBee* paq, const char* address);
	
	//! It sets MY_Known flag to '1' and sets the destination network address 
	//! to the packet to be sent.
  	/*!
    \param struct packetXBee* paq :  This is the packet to be set
    \param const char* address : pointer to the destination address
    \return void
    */
	void setKnownDestination(packetXBee* paq, uint8_t* address);
	
	//! 
	uint8_t setCoordinator(uint8_t input);
	//! 
	uint8_t getCoordinator();
	
	
	/// Variables /////////////////////////////////////////////////////////////
	
	//! Variable : the 16b parent´s network address
	uint8_t parentNA[2];
	
	//! Variable : the number of children which can still connect to the current device
	uint8_t remainingChildren;
	
	//! Variable : the current device type
	uint8_t deviceType[4];
	
	//! Variable : the bytes that can be used in the payload
	uint8_t maxPayloadBytes[2];
	
	//! Variable : the operating 64-bit PAN ID
	uint8_t operating64PAN[8];
	
	//! Variable : the operating 16-bit PAN ID
	uint8_t operating16PAN[2];
	
	//! Variable : the maximum hops limit (range [0x00-0xFF])
	uint8_t maxUnicastHops; 
	
	//! Variable : the maximum number of hops for each broadcast data transmission (range [0x00-0x20])
	uint8_t maxBroadcastHops;
	
	//! Variable : the ZigBee Stack profile (range [0-2])
	uint8_t stackProfile;
	
	//! Variable : the number of Sleep Periods to not assert XBee pin
	uint8_t periodSleep[2];
	
	//! Variable : the time that a Coordinator/Router allows nodes to join (range [0x00-0xFF])
	uint8_t joinTime; 
	
	//! Variable : the channel verification parameter (range [0-1])
	uint8_t channelVerification;
	
	//! Variable : the join notification setting (range [0-1])
	uint8_t joinNotification;
	
	//! Variable : the time between consecutive aggregate route broadcast messages (range [0x00-0xFF])
	uint8_t aggregateNotification;
	
	//! Variable : information regarding last node join request
	uint8_t associationIndication;
	
	//! Variable : options for encryption (range [0-2])
	uint8_t encryptOptions;
	
	//! Variable : the 128-bit AES encryption key (range [0-0xFFFFFFFFFFFFFFFF])
	uint8_t networkKey[16];
	
	//! Variable : the power mode of the device (range [0-1])
	uint8_t powerMode;
	
	//! Variable : the voltage on the Vcc pin
	uint8_t supplyVoltage[2];	
	
	//! Variable : if this device is a coordinator (1) or not (0)
	uint8_t coordinatorEnable; 
};

extern WaspXBeeZB	xbeeZB;

#endif
