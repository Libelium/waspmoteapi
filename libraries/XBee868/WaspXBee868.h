/*! \file WaspXBee868.h
    \brief Library for managing XBee 868MHz modules
    
    Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
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

/*! \def WaspXBee868_h
    \brief The library flag
    
 */
#ifndef WaspXBee868_h
#define WaspXBee868_h

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

//! WaspXBee868 Class
/*!
	WaspXBee868 Class defines all the variables and functions used to manage 
	XBee 868 modules. It inherits from 'WaspXBeeCore' class the necessary 
	functions, variables and definitions
 */
class WaspXBee868 : public WaspXBeeCore
{
 
public:
	
	//! class constructor
  	/*!
	  It does nothing
	  \param void
	  \return void
	 */
	WaspXBee868()
	{
		// clear library buffers
		memset( nodeID, 0x00, sizeof(nodeID) );
		memset( linkKey, 0x00, sizeof(linkKey) );
	};

	
	//! It initializes the necessary variables
  	/*!
	It initalizes all the necessary variables
	\param uint8_t uart_used : specifies the UART where the data are sent to 
			(UART0 or UART1)
	\return void
	 */
	void init( uint8_t uart_used );
	
	//! It gets the number of times the RF receiver detected a CRC or length error
  	/*!
	It stores in global 'errorsRF' variable the number of times the RF 
	receiver detected a CRC or length error
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
	It stores in global 'channelRSSI' variable the DBM level of the designated 
	channel
	\param uint8_t channel : the channel where to get the DBM level (range [0-11])
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
	
	//! It gets the current device type
  	/*!
		It stores in global 'deviceType' variable the current device type
	\return '0' on success, '1' otherwise
	 */
	uint8_t getDeviceType();
	
	//! It gets the bytes that can be used in the payload
  	/*!
	It stores in global 'maxPayloadBytes' variable the bytes that can be used 
	in the payload
	\return '0' on success, '1' otherwise
	 */
	uint8_t getPayloadBytes();
	
	//! It sets the number of additional broadcast retransmissions
  	/*!
	\param uint8_t mtrans : specifies the number of additional broadcast 
			retransmissions (range [0x00-0x0F])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setMultipleBroadcast(uint8_t mtrans);
	
	//! It gets the number of additional broadcast retransmissions
  	/*!
	It stores in global 'multipleBroadcast' variable the number of additional
	broadcast retransmissions
	\return '0' on success, '1' otherwise
	 */
	uint8_t getMultipleBroadcast();
	
	//! It sets the number of retries than can be sent for a given unicast RF packet
  	/*!
	\param uint8_t macretries : specifies the number of retries than can be 
			sent for a given unicast RF packet (range [0x00-0x0F])
	\return '0' on success, '1' otherwise
	 */
	uint8_t setMacRetries(uint8_t macretries);
	
	//! It gets the number of retries than can be sent for a given unicast RF packet
  	/*!
	It stores in global 'macRetries' variable the number of retries than can be 
	sent for a given unicast RF packet
	\return '0' on success, '1' otherwise
	 */
	uint8_t getMacRetries();
	
	//! It gets the % it has been used of available Duty Cycle
  	/*!
	It stores in global 'dutyCycle' variable the % it has been used of
	available Duty Cycle
	\return '0' on success, '1' otherwise
	 */
	uint8_t getDutyCycle();
	
	//! It gets the reason for the last module reset
  	/*!
	It stores in global 'resetReason' variable the reason for the last module reset
	\return '0' on success, '1' otherwise
	 */
	uint8_t getResetReason();
	
	//! It gets the number of failed ACK retries
  	/*!
		It stores in global 'ACKerrors' variable the number of failed ACK retries
	\return '0' on success, '1' otherwise
	 */
	uint8_t getACKerrors();
	
	//! It sends a packet to other XBee modules
  	/*!
    \param struct packetXBee* packet : the function gets the needed information 
			to send the packet from it
    \return '0' on success, '1' otherwise
    */
	uint8_t sendXBeePriv(struct packetXBee* packet);
	
	
	/// Variables /////////////////////////////////////////////////////////////
	
	//! Variable : the number of failed ACK retries
  	/*!
	 */
	uint8_t ACKerrors[2];
	
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
	
	//! Variable : module temperature in Celsius. Negatives temperatures can be returned
  	/*!
	 */
	uint8_t temperature[2];
	
	//! Variable : Voltage on the Vcc pin
  	/*!
	 */
	uint8_t supplyVoltage[2];
	
	//! Variable : Max payload to be used for transmission
  	/*!
	 */
	uint8_t maxPayloadBytes[2];
	
	//! Variable : the current device type
  	/*!
	 */
	uint8_t deviceType[4];
	
	//! Variable : the number of additional broadcast retransmissions (range [0x00-0x0F])
  	/*!
	 */
	uint8_t multipleBroadcast;
	
	//! Variable : the number of retries than can be sent for a given unicast 
	//! RF packet (range [0x00-0x0F])
  	/*!
	 */
	uint8_t macRetries;
	
	//! Variable : the % it has been used of available Duty Cycle
  	/*!
	 */
	uint8_t dutyCycle;
	
	//! Variable : Reason for the last module reset
  	/*!
	 */
	uint8_t resetReason;
};

extern WaspXBee868	xbee868;

#endif
