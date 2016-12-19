/*! \file WaspSensorPrototyping_v20.h
    \brief Library for managing the Prototyping v2.0 Sensor Board
    
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
    Implementation:	Alberto Bielsa, Manuel Calahorra

 */
 
/*! \def WaspSensorPrototyping_v20_h
    \brief The library flag
    
 */
#ifndef WaspSensorPrototyping_v20_h
#define WaspSensorPrototyping_v20_h


/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
 

/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspSensorPrototyping Class
/*!
	WaspSensorPrototyping Class defines all the variables and functions used for
	managing the Prototyping Sensor Board
 */
class WaspSensorPrototyping_v20
{
	private:
	
	public:
		
		//! class constructor
  		/*!
			It initializes the different digital pins
		\param void
		\return void
	 	*/
		WaspSensorPrototyping_v20();
		
		//! Turns ON the board
  		/*!
		\param void
		\return void
	 	*/
		void 	ON(void);

		//! Turns OFF the board
  		/*!
		\param void
		\return void
	 	*/
		void 	OFF(void);

		//! It sets board power mode, setting ON/OFF 3v3 and 5V switches
  		/*!
		\param uint8_t mode : SENS_ON or SENS_OFF
		\return int8_t error
	 	*/
		int8_t 	setBoardMode(uint8_t mode);
		
		//! It reads the Analogic-to-Digital Converter
  		/*!
		\param void
		\return the value returned by the conversor
		 */
		float	readADC(void);
		
		//! It reads an analog sensor and returns its measured value in Volts
  		/*!
		\param uint8_t pin : specifies the analog pin where the sensor is connected
		\return the measured value in Volts (range [0-3.3] Volts)
		 */
		float	readAnalogSensor(uint8_t pin);
};

extern WaspSensorPrototyping_v20 SensorProtov20;

#endif
