/*! \file UltrasoundSensor.h
    \brief Library for managing the MB7040 and MB1202 sensors
    
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
    Implementation:	Alejandro Gállego

*/

/*! \def UltrasoundSensor_h
    \brief The library flag
    
 */
#ifndef UltrasoundSensor_h
#define UltrasoundSensor_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>



/******************************************************************************
 * Defines
 ******************************************************************************/
 
#define MB7040_MB1202_I2C_READ_TIMEOUT	100

// Command to take a single reading
#define MB7040_MB1202_RANGE_READING		0x51


/******************************************************************************
 * Class
 ******************************************************************************/
 
//! UltrasoundSensor Class
/*!
	UltrasoundSensor Class defines all the variables and functions used to manage MB7040 and MB1202 sensors
 */
class UltrasoundSensor
{
	public:
	
	//! This function performs a distance measurement
	/*!	
	\return		0 to 735: distance in cm.
				9000 if error reading the distance
				10000 if error reading the sensor
	*/
	uint16_t getDistance();
	
};

extern UltrasoundSensor Ultrasound;

#endif
