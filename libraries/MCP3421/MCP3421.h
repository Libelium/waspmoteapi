/*! \file MCP3421.h
    \brief Library for managing the MCP3421 ADC
    
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

/*! \def MCP3421_h
    \brief The library flag
    
 */
#ifndef MCP3421_h
#define MCP3421_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>


//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_MCP3421		0

#define PRINT_MCP3421(str)			USB.print(F("[MCP3421] ")); USB.print(str);
#define PRINTHEX_MCP3421(str, val)	USB.print(F(str));	USB.printHex(val);

#define MCP3421_I2C_READ_TIMEOUT	100

// resolution value for ADC conversion
#define MCP3421_RES_12_BIT		0
#define MCP3421_RES_14_BIT		1
#define MCP3421_RES_16_BIT		2
#define MCP3421_RES_18_BIT		3

#define MCP3421_LOW_RES			0
#define MCP3421_MEDIUM_RES			1
#define MCP3421_HIGH_RES			2
#define MCP3421_ULTRA_HIGH_RES		3

// gain setting for ADC
#define MCP3421_GAIN_1			0
#define MCP3421_GAIN_2			1
#define MCP3421_GAIN_4			2
#define MCP3421_GAIN_8			3

// conversion 
#define MCP3421_RAW			0
#define MCP3421_VOLTS			1


#define I2C_ADDRESS_GASPRO_MCP3421_A0   0x68
#define I2C_ADDRESS_GASPRO_MCP3421_A1   0x69
#define I2C_ADDRESS_GASPRO_MCP3421_A2   0x6A

/******************************************************************************
 * Class
 ******************************************************************************/
 
//! MCP3421 Class
/*!
	MCP3421 Class defines all the variables and functions used to manage ADC module
 */
class MCP3421
{
	private:
	
	public:
	
	MCP3421();

	/*!
	\param uint8_t resolution: resolution value for ADC conversion
						MCP3421_RES_12_BIT or MCP3421_LOW_RES
						MCP3421_RES_14_BIT or MCP3421_MEDIUM_RES
						MCP3421_RES_16_BIT or MCP3421_HIGH_RES
						MCP3421_RES_18_BIT or MCP3421_ULTRA_HIGH_RES
	\param uint8_t gain: gain setting for ADC
						MCP3421_GAIN_1
						MCP3421_GAIN_2
						MCP3421_GAIN_4
						MCP3421_GAIN_8
	\param uint8_t conversion: returns the raw value or converted to millivolts
						MCP3421_RAW
						MCP3421_VOLTS
	\return		measure in milliVolts or raw
	*/
	float readADC(uint8_t resolution, uint8_t gain);
	
	/*!
	\param uint8_t ADC_addr: I2C address for the ADC
	\param uint8_t resolution: resolution value for ADC conversion
						MCP3421_RES_12_BIT or MCP3421_LOW_RES
						MCP3421_RES_14_BIT or MCP3421_MEDIUM_RES
						MCP3421_RES_16_BIT or MCP3421_HIGH_RES
						MCP3421_RES_18_BIT or MCP3421_ULTRA_HIGH_RES
	\param uint8_t gain: gain setting for ADC
						MCP3421_GAIN_1
						MCP3421_GAIN_2
						MCP3421_GAIN_4
						MCP3421_GAIN_8
	\param uint8_t conversion: returns the raw value or converted to millivolts
						MCP3421_RAW
						MCP3421_VOLTS
	\return		measure in milliVolts or raw
	*/
	float readADC(uint8_t adc_addr, uint8_t resolution, uint8_t gain);
	
};

extern MCP3421 MCP;

#endif
