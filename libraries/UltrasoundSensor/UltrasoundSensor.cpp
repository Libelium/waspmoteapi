/*
 *  Library for managing the MB7040 and MB1202 sensors
 * 
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.0
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
	
	uint8_t HByte, LByte;
	uint16_t range;
	uint32_t tempo;
	
	delay(200);
	
	if( !Wire.isON ) Wire.begin();
	
	Wire.beginTransmission(I2C_ADDRESS_MB7040_MB1202);
    Wire.send(MB7040_MB1202_RANGE_READING);        
	Wire.endTransmission();
	
	delay(100); //It is best to allow 100ms between readings to allow for proper acoustic dissipation. 
	
	// Reads the measured distance	
	Wire.requestFrom(I2C_ADDRESS_MB7040_MB1202,0x02);
	tempo = millis();
	while((Wire.available() < 2) && ((millis() - tempo) < MB7040_MB1202_I2C_READ_TIMEOUT))
	{
		if (millis() < tempo) tempo = millis();	//to avoid millis overflow
	}
	
	if (Wire.available() == 2)
	{
		HByte = Wire.receive();
		LByte = Wire.receive();
		Wire.endTransmission();
	
		range = ((uint16_t)HByte * 256) + LByte;
		if (range >= 800)
		{
			range = 9000;			
		}
		
	}
	else
	{
		range = 10000;
	}	
	
	
	return range;	
}


// Preinstantiate Objects //////////////////////////////////////////////////////

UltrasoundSensor Ultrasound = UltrasoundSensor();
