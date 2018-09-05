/*! \file WaspXBee802.h
    \brief Library for managing XBee 802.15.4 modules
    
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
 
/*! \def WaspXBee802_h
    \brief The library flag
    
 */
#ifndef WaspXBee802_h
#define WaspXBee802_h

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

//! WaspXBee802 Class
/*!
	WaspXBee802 Class defines all the variables and functions used to manage 
	XBee 802.15.4 modules. It inherits from 'WaspXBeeCore' class the necessary 
	functions, variables and definitions
 */
class WaspXBee802 : public WaspXBeeCore
{
  
public:
	  
	//! class constructor
  	/*!
	It does nothing
	\param void
	\return void
  	 */ 
    WaspXBee802()
    {
		// clear library buffers
		memset( nodeID, 0x00, sizeof(nodeID) );
		memset( linkKey, 0x00, sizeof(linkKey) );
	};
	
	//! It initializes the necessary variables
  	/*!
	It initalizes all the necessary variables
	\param uint8_t protocol_used : specifies the protocol used in the XBee module 
			(depends on the XBee module)
	\param uint8_t uart_used : specifies the UART where the data are sent to (0-1)
	\return void
	 */
	void init( uint8_t uart_used );
	
	//! It sets the maximum number of retries to execute in addition to the	
	//! three retries defined in the 802.15.4 protocol
  	/*!
	\param uint8_t retry : specifies the number of retries to set (range [0-6])
	\return '0' on success, '1' otherwise
	 */
    uint8_t setRetries(uint8_t retry);
	
	//! It gets the maximum number of retries to execute in addition to the	
	//! three retries defined in the 802.15.4 protocol
  	/*!
	It stores in global 'retries' variable the number of retries
	\return '0' on success, '1' otherwise
	 */
    uint8_t getRetries();
	
	//! It sets the minimun value of the back-off exponent in CSMA/CA
  	/*!
	\param uint8_t exponent : specifies the value of the back-off exponent in 
			CSMA/CA (range [0-3]) 
	\return '0' on success, '1' otherwise
	 */
    uint8_t setDelaySlots(uint8_t exponent);
	
	//! It gets the minimun value of the back-off exponent in CSMA/CA
  	/*!
	It stores in global 'delaySlots' variable the minimun value of the back-off 
	exponent in CSMA/CA
	\return '0' on success, '1' otherwise
	 */
    uint8_t getDelaySlots();
	
	//! It sets the MAC mode
  	/*!
	\param uint8_t mac : specifies the MAC mode (range [0-3]) 
	\return '0' on success, '1' otherwise
	 */
    uint8_t setMacMode(uint8_t mac);
	
	//! It gets the MAC mode
  	/*!
	It stores in global 'macMode' variable the MAC mode
	\return '0' on success, '1' otherwise
	 */
    uint8_t getMacMode();
	
	//! It sets the CA threshold in the CCA process to detect energy on the channel
  	/*!
	\param uint8_t threshold : specifies the CA threshold in the CCA process to 
			detect energy on the channel (range [0x00-0x50]) 
	\return '0' on success, '1' otherwise
	 */
    uint8_t setEnergyThreshold(uint8_t threshold);
	
	//! It gets the Energy Threshold used in the CCA process
  	/*!
	It stores in global 'energyThreshold' variable the Energy Threshold used in 
	the CCA process
	\return '0' on success, '1' otherwise
	 */
    uint8_t getEnergyThreshold();
	
	//! It gets the number of times too much energy has been found on the channel
  	/*!
	It stores in global 'counterCCA' variable the number of times too much 
	energy has been found on the channel
	\return '0' on success, '1' otherwise
	 */
    uint8_t getCCAcounter();
	
	//! It resets the CCA counter
  	/*!
	\param void
	\return '0' on success, '1' otherwise
	 */
    uint8_t resetCCAcounter();
	
	//! It gets the number of times there has been an ACK failure
  	/*!
	It stores in global 'counterACK' variable the number of times there has been 
	an ACK failure
	\return '0' on success, '1' otherwise
	 */
    uint8_t getACKcounter();
	
	//! It resets the ACK counter
  	/*!
	\param void
	\return '0' on success, '1' otherwise
	 */
    uint8_t resetACKcounter();
    
    //! It sends a packet to other XBee modules
  	/*!
    \param struct packetXBee* packet : the function gets the needed information 
			to send the packet from it
    \return '0' on success, '1' otherwise
    */
	uint8_t sendXBeePriv(struct packetXBee* packet);
	

	/// Variables /////////////////////////////////////////////////////////////

	//! Variable : number of retries to execute in addition to the three retries 
	//! defined in the 802.15.4 protocol (range [0-6])
  	/*!
   	*/
    uint8_t retries;
	
	//! Variable : the minimun value of the back-off exponent in CSMA/CA (range [0-3])
  	/*!
	 */
    uint8_t delaySlots;
	
	//! Variable : the MAC mode(range [0-3]) 
  	/*!
	 */
    uint8_t macMode;
	
	//! Variable : the CA threshold in the CCA process to detect energy on the 
	//! channel (range [0x00-0x50]) 
  	/*!
	 */
    uint8_t energyThreshold;
	
	//! Variable : the number of times too much energy has been found on the channel
  	/*!
	 */
    uint8_t counterCCA[2];
	
	//! Variable : the number of times there has been an ACK failure
  	/*!
	 */
    uint8_t counterACK[2];


private:

	//! Variable : internal counter
  	/*!
	 */
    uint8_t counter;
};

extern WaspXBee802	xbee802;

#endif
