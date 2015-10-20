/*
 *  Library for managing the MCP3421 ADC
 * 
 *  Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.1
 *  Design:			David Gascón
 *  Implementation:	Alejandro Gállego
 */

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif


#include <MCP3421.h>

// Constructors ////////////////////////////////////////////////////////////////
MCP3421::MCP3421(){

}

/* Function:	This function performs a conversion with the desired parameters
 * Parameters:	resolution: resolution value for ADC conversion
 * 					MCP3421_RES_12_BIT or MCP3421_LOW_RES
 * 					MCP3421_RES_14_BIT or MCP3421_MEDIUM_RES
 * 					MCP3421_RES_16_BIT or MCP3421_HIGH_RES
 * 					MCP3421_RES_18_BIT or MCP3421_ULTRA_HIGH_RES
 *  			gain: gain setting for ADC
 * 					MCP3421_GAIN_1
 * 					MCP3421_GAIN_2
 * 					MCP3421_GAIN_4
 * 					MCP3421_GAIN_8
 * 				conversion: MCP3421_RAW or MCP3421_VOLTS
 * Return: 		measure in milliVolts or raw
 */
float MCP3421::readADC(uint8_t resolution, uint8_t gain, uint8_t conversion ){

	
	uint8_t config_reg, val1, val2, val3;
	float value;
	
	unsigned long tempo;	
	
	long aux_val;
	
	if( !Wire.I2C_ON ) Wire.begin();

	// Primero se manda la orden de conversion
	Wire.beginTransmission(I2C_ADDRESS_GASPRO_MCP3421);   
	
	config_reg = 128 + (resolution * 4) + gain;
	Wire.send(config_reg);  // start from address theAddress
	Wire.endTransmission();


	// START READING
	switch (resolution)
	{
		case MCP3421_RES_12_BIT:
			delay(6);
			//Leer 3 bytes ( 2 de datos + configuracion)
			Wire.requestFrom(I2C_ADDRESS_GASPRO_MCP3421, 0x03);
			tempo = millis();
			while((Wire.available() < 3) && ((millis() - tempo) < MCP3421_I2C_READ_TIMEOUT))
			{
				if (millis() < tempo) tempo = millis();	//to avoid millis overflow
			}
			
			if (Wire.available() == 3)
			{
				val1 = Wire.receive();
				val2 = Wire.receive();
				value = val1*256 + val2;
				config_reg = Wire.receive();
				Wire.endTransmission();
				
				if (conversion == MCP3421_VOLTS)
				{
					value /= pow(2, gain);
				}
			}
			else
			{
				value = -10000;
			}
			
			break;
			
		case MCP3421_RES_14_BIT:
			delay(18);
			//Leer 3 bytes ( 2 de datos + configuracion)
			Wire.requestFrom(I2C_ADDRESS_GASPRO_MCP3421, 0x03);			
			tempo = millis();
			while((Wire.available() < 3) && ((millis() - tempo) < MCP3421_I2C_READ_TIMEOUT))
			{
				if (millis() < tempo) tempo = millis();	//to avoid millis overflow
			}
			
			if (Wire.available() == 3)
			{
				val1 = Wire.receive();
				val2 = Wire.receive();
				value = val1*256 + val2;
				config_reg = Wire.receive();
				Wire.endTransmission();
			
				if (conversion == MCP3421_VOLTS)
				{
					value /= 4;
					value /= pow(2, gain);
				}
			}
			else
			{
				value = -10000;
			}
			
			break;
			
		case MCP3421_RES_16_BIT:
			delay(68);
			//Leer 3 bytes ( 2 de datos + configuracion)
			Wire.requestFrom(I2C_ADDRESS_GASPRO_MCP3421, 0x03);		
			tempo = millis();
			while((Wire.available() < 3) && ((millis() - tempo) < MCP3421_I2C_READ_TIMEOUT))
			{
				if (millis() < tempo) tempo = millis();	//to avoid millis overflow
			}
			
			if (Wire.available() == 3)
			{
				val1 = Wire.receive();
				val2 = Wire.receive();
				value = val1*256 + val2;
				config_reg = Wire.receive();
				Wire.endTransmission();
			
				if (conversion == MCP3421_VOLTS)
				{
					value /= 16;
					value /= pow(2, gain);
				}
			}
			else
			{
				value = -10000;
			}
			
			break;
			
		case MCP3421_RES_18_BIT:
			delay(300);
			//Leer 3 bytes ( 3 de datos + configuracion)
			Wire.requestFrom(I2C_ADDRESS_GASPRO_MCP3421, 0x04);				
			tempo = millis();
			while((Wire.available() < 4) && ((millis() - tempo) < MCP3421_I2C_READ_TIMEOUT))
			{
				if (millis() < tempo) tempo = millis();	//to avoid millis overflow
			}
			
			if (Wire.available() == 4)
			{				
				val1 = Wire.receive();
				val2 = Wire.receive();
				val3 = Wire.receive();
				config_reg = Wire.receive();
				Wire.endTransmission();
				
				if (val1 & B00000010)
				{
					aux_val = 0xFF000000 + ( (long(val1) << 16) & 0x00FF0000)  + ( (long(val2) << 8) & 0x0000FF00) + (val3 & 0x000000FF);
					value = float(aux_val);
				}
				else 
				{
					aux_val = ( (long(val1) << 16) & 0x00FF0000)  + ( (long(val2) << 8) & 0x0000FF00) + (val3 & 0x000000FF);
					value = float(aux_val);
				}
			
				if (conversion == MCP3421_VOLTS)
				{
					value /= 64;
					value /= pow(2, gain);
				}
			}
			else
			{
				value = -10000;
			}			
			break;
		
	}
	

	
	return value;	
}


// Preinstantiate Objects //////////////////////////////////////////////////////

MCP3421 MCP = MCP3421();
