/*! \file currentLoop.h

	\brief Library for managing the 4-20mA
	Copyright (C) 2017 Libelium Comunicaciones Distribuidas S.L.
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

	Version:		3.1
	Implementation:	Ahmad Saad
*/

#ifndef currentLoop_h
#define currentLoop_h

/***********************************************************************
 * Includes
 ***********************************************************************/
#include <inttypes.h>

/***********************************************************************
* Configuration Selection
************************************************************************/	
#define CHANNEL1 0x01 //ANALOG1
#define CHANNEL2 0x02 //ANALOG2
#define CHANNEL3 0x03 //ANALOG5
#define CHANNEL4 0x04 //ANALOG6

#define SUPPLY12V 12
#define SUPPLY5V 5


/***********************************************************************
 * Class
 **********************************************************************/
class currentLoop{

	public:
	
		//! The constructor of the class
		currentLoop();
		
		//! Powers ON the 4-20mA supply 5V or 12V
		uint8_t ON(uint8_t powerSupply);
		
		//! Powers OFF the 4-20mA supply 5V or 12V
		uint8_t OFF(uint8_t powerSupply);
		
		//! Get the sensor value in integer format
		int readChannel(uint8_t channel);
		
		//! Get the sensor value as a voltage in Volts
		float	readVoltage(uint8_t channel);
		
		//! Get the sensor value as a current in mA
		float readCurrent(uint8_t channel);

		//! Get the sensor value as a current in mA and introduce 
		//! a correction offSet factor. 
		float readCurrent(uint8_t channel, float offSet);

		//! It checks if the current loop is well connected
		uint8_t isConnected(uint8_t channel);
		
	private:
	
		//! This variable stores the last value read from th ADC
		long _analogValue;

};

extern currentLoop currentLoopBoard;

#endif
