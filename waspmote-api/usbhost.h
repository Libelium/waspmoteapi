/*! \file WaspUtils.h
    \brief Library containing useful general functions
    
    Copyright (C) 2009 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		0.12

    Design:		

    Implementation:	

*/
  
/* MAX3421E-based USB Host Library header file */



#ifndef _USBHOST_H_
#define _USBHOST_H_  


/******************************************************************************
 * Includes
 ******************************************************************************/
 
//#include "max3421e.h"
//#include "usb_ch9.h"


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

static uint8_t vbusState;

/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspUtils Class
/*!
	WaspUtils Class defines all the variables and functions used to set LEDs, multiplexor and useful general functions
 */
class MAX3421e
{
  private:

  public:
  	MAX3421e();
	void regWr( uint8_t reg, uint8_t data );
	void regWrAS( uint8_t reg, uint8_t data );
	uint8_t* bytesWr( uint8_t reg, uint8_t nbytes, uint8_t* data_p );
	uint8_t regRd( uint8_t reg );
	uint8_t regRdAS( uint8_t reg );
	uint8_t* bytesRd( uint8_t reg, uint8_t nbytes, uint8_t* data_p );
	uint16_t reset();
	void Spi_Init();
	void Host();
	void Device();
	uint8_t getVbusState( void );
	void busprobe();	
	uint8_t IntHandler();
	uint8_t Task();
};

#endif //_USBHOST_H_
