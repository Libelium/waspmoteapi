/*
 *  Library for managing the MB7040 and MB1202 sensors
 * 
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		3.1
 *  Design:			David Gascón
 *  Implementation:	Alejandro Gállego
 */

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif


#include <UltrasoundSensor.h>


/* Function:	This function performs a distance measurement
 * Return: 		distance in cm.
 * 				9000 if error reading the distance
 * 				10000 if error reading the sensor
 */
uint16_t UltrasoundSensor::getDistance()
{
	
	union l {
		uint16_t distance;
		uint8_t data[2];
	}measure;
	
	uint32_t tempo;

	// init I2C bus
	I2C.begin();
	
	// send command
	I2C.write(I2C_ADDRESS_MB7040_MB1202, MB7040_MB1202_RANGE_READING, 1);
	
	delay(100); //It is best to allow 100ms between readings to allow for proper acoustic dissipation. 
	
	// Reads the measured distance	
	I2C.read(I2C_ADDRESS_MB7040_MB1202,measure.data,2);
	
	uint8_t aux;
	aux = measure.data[0];
	measure.data[0] = measure.data[1];
	measure.data[1] = aux;
	
	return measure.distance;	
}


// Preinstantiate Objects //////////////////////////////////////////////////////

UltrasoundSensor Ultrasound = UltrasoundSensor();
