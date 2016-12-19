/*! \file WaspXBee900.h
    \brief Library for managing 900MHz modules
    
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
 
/*! \def WaspXBeeDM_h
    \brief The library flag
    
 */
#ifndef WaspXBee900_h
#define WaspXBee900_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <WConstants.h>
#include "WaspXBeeCore.h"
#include <inttypes.h>


/******************************************************************************
 * Class
 ******************************************************************************/

//! WaspXBee900 Class
/*!
	WaspXBee900 Class defines all the variables and functions used to manage 
	XBee 900MHz modules. It inherits from 'WaspXBeeCore' class 
	the necessary functions, variables and definitions
 */
class WaspXBee900 : public WaspXBeeCore
{
  
public:
	  
	//! class constructor
  	/*!
	It does nothing
	\param void
	\return void
	 */
	WaspXBee900()
	{
		// clear library buffers
		memset( nodeID, 0x00, sizeof(nodeID) );
		memset( linkKey, 0x00, sizeof(linkKey) );
	};

	
	//! It initializes the necessary variables
  	/*!
	It initalizes all the necessary variables
	\param uint8_t uart_used : specifies the UART where the data are sent to,
			(SOCKET0 or SOCKET1)
	\return void
	 */
	void init(	uint8_t uart_used	);
	
	//! It gets the number of times the RF receiver detected a CRC or length error
  	/*!
	It stores in global 'errorsRF' variable the number of times the RF receiver 
	detected a CRC or length error
	\return '0' on success, '1' otherwise
	 */
	uint8_t getRFerrors();
	
	//! It gets the number of good frames with valid MAC headers that are 
	//! received on the RF interface
  	/*!
	It stores in global 'goodPackets' variable the number of good frames 
	with valid MAC headers that are received on the RF interface
	\return '0' on success, '1' otherwise
	 */
	uint8_t getGoodPackets();
	
	//! It gets the DBM level of the designated channel
  	/*!
	It stores in global 'channelRSSI' variable the number of retries
	\param uint8_t channel : the channel where to get the DBM level (depends on 
			the XBee module)
	\return '0' on success, '1' otherwise
	 */
	uint8_t getChannelRSSI(uint8_t channel);
	
	//! It gets the number of MAC frames that exhaust MAC retries without ever 
	//! receiving a MAC acknowledgement message from the adjacent node
  	/*!
	It stores in global 'transmisionErrors' variable the number of MAC frames 
	that exhaust MAC retries without ever receiving a MAC acknowledgement
	message from the adjacent node
	\return '0' on success, '1' otherwise
	 */
	uint8_t getTransmisionErrors();
		
	//! It gets module temperature in Celsius. Negatives temperatures can be returned
  	/*!
	It stores in global 'temperature' variable module temperature in Celsius
	\return '0' on success, '1' otherwise
	 */
	uint8_t getTemperature();
	
	//! It gets the voltage on the Vcc pin
  	/*!
		It stores in global 'supplyVoltage' variable the voltage on the Vcc pin
	\return '0' on success, '1' otherwise
	 */
	uint8_t getSupplyVoltage();
	
	//! It restores module parameters to compiled defaults
  	/*!
	\return '0' on success, '1' otherwise
	 */
	uint8_t restoreCompiled();

	//! It sends a packet to other XBee modules
  	/*!
    \param struct packetXBee* packet : the function gets the needed information 
			to send the packet from it
    \return '0' on success, '1' otherwise
    */
	uint8_t sendXBeePriv(struct packetXBee* packet);		
		

		
	
	//! Variable : the number of times the RF receiver detected a CRC or length error
  	/*!
	 */
	uint8_t errorsRF[2];
	
	//! Variable : the number of good frames with valid MAC headers that are 
	//! received on the RF interface
  	/*!
	 */
	uint8_t goodPackets[2];
	
	//! Variable : the DBM level of the designated channel
  	/*!
	 */
	uint8_t channelRSSI;

	//! Variable : the number of MAC frames that exhaust MAC retries without 
	//! ever receiving a MAC acknowledgement message from the adjacent node
  	/*!
	 */
	uint8_t transmisionErrors[2];
	
	//! Variable : the maximum number of hops expected to be seen in a network 
	//! route (range [1-0xFF])
  	/*!
	 */
	uint8_t networkHops;
	
	//! Variable : the maximum random number of network delay slots before 
	//! rebroadcasting a network packet (range [0-0x0A])
  	/*!
	 */
	uint8_t netDelaySlots;
	
	//! Variable : the maximum number of route discovery retries allowed to 
	//! find a path to the destination node (range [0-0x0A])
  	/*!
	 */
	uint8_t netRouteRequest;
	
	//! Variable : the maximum number of network packet delivery attempts (range [0-7])
  	/*!
	 */
	uint8_t meshNetRetries;
	
	//! Variable : module temperature in Celsius
  	/*!
	 */
	uint8_t temperature[2];
	
	//! Variable : the voltage on the Vcc pin
  	/*!
	 */
	uint8_t supplyVoltage[2];
};

extern WaspXBee900	xbee900;

#endif
