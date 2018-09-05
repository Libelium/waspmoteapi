/*
 *  Library for managing the TSL2561 sensor (luxes accuray)
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
 *  Version:		3.3
 *  Design:			David Gascón
 *  Implementation:	Alejandro Gállego
 */

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif

#include <TSL2561.h>


// Constructors ////////////////////////////////////////////////////////////////
TSL2561::TSL2561()
{
  _initialized = false;
  _integration = TSL2561_INTEGRATIONTIME_402MS;
  _gain = TSL2561_GAIN_0X;
}

/// PRIVATE FUNCTIONS



boolean TSL2561::checkID()
{
	uint8_t valueID;


	#if TSL2561_DEBUG>0
		PRINT_LUX(F("TSL2561.Checking ID..."));
	#endif
	I2C.read(I2C_ADDRESS_TSL2561, TSL2561_CHIP_ID_REG, &valueID,1);
	if (valueID == TSL2561_CHIP_ID_REG_CHIP_ID)
	{
		#if TSL2561_DEBUG>0
			PRINT_LUX(F("OK\n"));
		#endif
		return 1;
	}

	#if TSL2561_DEBUG>0
		PRINT_LUX(F("error\n"));
	#endif
	return 0;


}


/*
 Function:
 Returns:
 Parameters:
 Values:
*/
void TSL2561::enable(void)
{
  #if TSL2561_DEBUG>0
		PRINT_LUX(F("TSL2561.Enabling lux sensor\n"));
	#endif
	I2C.write	(	I2C_ADDRESS_TSL2561, 
					TSL2561_COMMAND_BIT | TSL2561_CONTROL_REG,
					TSL2561_CONTROL_POWERON);

	delay(100);
}

/*
 Function:
 Returns:
 Parameters:
 Values:
*/
void TSL2561::disable(void)
{
  	#if TSL2561_DEBUG>0
		PRINT_LUX(F("TSL2561.Disabling lux sensor\n"));
	#endif
	I2C.write	(	I2C_ADDRESS_TSL2561, 
					TSL2561_COMMAND_BIT | TSL2561_CONTROL_REG,
					TSL2561_CONTROL_POWEROFF);

	delay(100);
}

/*
 Function:
 Returns:
 Parameters:
 Values:
*/
void TSL2561::setGain(tsl2561Gain_t gain)
{
	enable();

	#if TSL2561_DEBUG>0
		PRINT_LUX(F("TSL2561.Setting gain to "));
		USB.println(gain, DEC);
	#endif

	_gain = gain;
  
	I2C.write	(	I2C_ADDRESS_TSL2561, 
					TSL2561_COMMAND_BIT | TSL2561_TIMING_REG,
					_integration | _gain);

	disable();
}

/*
 Function:
 Returns:
 Parameters:
 Values:
*/
void TSL2561::setTiming(tsl2561IntegrationTime_t integration)
{

	enable();

	#if TSL2561_DEBUG>0
		PRINT_LUX(F("TSL2561.Setting integration time to "));
		USB.println(integration, DEC);
	#endif

	_integration = integration;

	I2C.write	(	I2C_ADDRESS_TSL2561, 
					TSL2561_COMMAND_BIT | TSL2561_TIMING_REG,
					_integration | _gain);

	disable();
}


/*
 Function:
 Returns:
 Parameters:
 Values:
*/
void TSL2561::calculateLux()
{
	unsigned long chScale;
	unsigned long channel1;
	unsigned long channel0;

	switch (_integration)
	{
		case TSL2561_INTEGRATIONTIME_13MS:
			chScale = TSL2561_LUX_CHSCALE_TINT0;
			break;

		case TSL2561_INTEGRATIONTIME_101MS:
			chScale = TSL2561_LUX_CHSCALE_TINT1;
			break;

		default: // No scaling ... integration time = 402ms
			chScale = (1 << TSL2561_LUX_CHSCALE);
			break;
	}

	// Scale for gain (1x or 16x)
	if (!_gain)
	{
		chScale = chScale << 4;
	}

	// scale the channel values
	channel0 = (full * chScale) >> TSL2561_LUX_CHSCALE;
	channel1 = (ir * chScale) >> TSL2561_LUX_CHSCALE;

	// find the ratio of the channel values (Channel1/Channel0)
	unsigned long ratio1 = 0;
	if (channel0 != 0)
	{
		ratio1 = (channel1 << (TSL2561_LUX_RATIOSCALE+1)) / channel0;
	}

	// round the ratio value
	unsigned long ratio = (ratio1 + 1) >> 1;

	unsigned int b, m;

	if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1T))
	{
		b = TSL2561_LUX_B1T;
		m = TSL2561_LUX_M1T;
	}
	else if (ratio <= TSL2561_LUX_K2T)
	{
		b = TSL2561_LUX_B2T;
		m = TSL2561_LUX_M2T;
	}
	else if (ratio <= TSL2561_LUX_K3T)
	{
		b = TSL2561_LUX_B3T;
		m = TSL2561_LUX_M3T;
	}
	else if (ratio <= TSL2561_LUX_K4T)
	{
		b = TSL2561_LUX_B4T;
		m = TSL2561_LUX_M4T;
	}
	else if (ratio <= TSL2561_LUX_K5T)
	{
		b = TSL2561_LUX_B5T;
		m = TSL2561_LUX_M5T;
	}
	else if (ratio <= TSL2561_LUX_K6T)
	{
		b = TSL2561_LUX_B6T;
		m = TSL2561_LUX_M6T;
	}
	else if (ratio <= TSL2561_LUX_K7T)
	{
		b = TSL2561_LUX_B7T;
		m = TSL2561_LUX_M7T;
	}
	else if (ratio > TSL2561_LUX_K8T)
	{
		b = TSL2561_LUX_B8T;
		m = TSL2561_LUX_M8T;
	}

	unsigned long temp;
	temp = ((channel0 * b) - (channel1 * m));

	// do not allow negative lux value
	if (temp < 0)
	{
		temp = 0;
	}

	// round lsb (2^(LUX_SCALE-1))
	temp += (1 << (TSL2561_LUX_LUXSCALE-1));

	// strip off fractional portion
	lux = temp >> TSL2561_LUX_LUXSCALE;

}

/*
 Function:
 Returns:
 Parameters:
 Values:
*/
int8_t TSL2561::getFullLuminosity ()
{
	int8_t error;
	uint8_t aux_buffer[4];

	// Enable the device by setting the control bit to 0x03
	enable();

	// Wait x ms for ADC to complete
	switch (_integration)
	{
		case TSL2561_INTEGRATIONTIME_13MS:
			delay(14);
			break;

		case TSL2561_INTEGRATIONTIME_101MS:
			delay(105);
			break;

		default:
			delay(420);
			break;
	}

	error = I2C.read(	I2C_ADDRESS_TSL2561,
					(uint8_t)(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_CHAN0_LOW_REG),
					aux_buffer,
					4);

	full = ((uint16_t) aux_buffer[1] << 8) | (uint16_t) aux_buffer[0];
	ir = ((uint16_t) aux_buffer[3] << 8) | (uint16_t) aux_buffer[2];

  #if TSL2561_DEBUG>0
    uint32_t x = (((uint32_t)ir << 16) | (uint32_t)full );
    PRINT_LUX("Full luminosity: ");
    USB.println(x, DEC);
  #endif

	disable();

	return error;
}

/// PUBLIC FUNCTIONS
/// POWER AND CONFIGURATION FUNCTIONS

/*
 Function:
 Returns:
 Parameters:
 Values:
*/
boolean TSL2561::ON(void) 
{	
	I2C.begin();
	
	delay(100);

	if (checkID() == 0)
	{
		return 1;
	}

	_initialized = true;

	// Set default integration time and gain
	setTiming(_integration);
	setGain(_gain);

	delay(400);

	return 0;
}

int8_t TSL2561::getLuminosity()
{
	return getLuminosity( TSL2561_HIGH_RES, TSL2561_GAIN_1);
}

int8_t TSL2561::getLuminosity(uint8_t res)
{
	return getLuminosity( res, TSL2561_GAIN_1);

}

int8_t TSL2561::getLuminosity(uint8_t res, bool gain)
{
	int8_t error;

	if (gain == 0)
	{
		setGain(TSL2561_GAIN_0X);
	}
	else
	{
		setGain(TSL2561_GAIN_16X);
	}
	setTiming((tsl2561IntegrationTime_t)res);

	// Reads both channels of the sensor
	error = getFullLuminosity();
	if ( error != 0)
	{
		return error;
	}

	visible = full - ir;

	// Calculta the luxes value
	calculateLux();

	return 0;

}


// Preinstantiate Objects //////////////////////////////////////////////////////
TSL2561 TSL = TSL2561();
