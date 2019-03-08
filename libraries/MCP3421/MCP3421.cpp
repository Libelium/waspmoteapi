/*
 *  Library for managing the MCP3421 ADC
 *
 *  Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		4.1
 *  Design:			David Gascón
 *  Implementation:	Ahmad Saad & Alejandro Gállego
 */

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif


#include <MCP3421.h>

// Constructors ////////////////////////////////////////////////////////////////
MCP3421::MCP3421(){}


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
float MCP3421::readADC(uint8_t resolution, uint8_t gain)
{
	return readADC(I2C_ADDRESS_GASPRO_MCP3421_A1, resolution, gain);
}

/* Function:	This function performs a conversion with the desired parameters
 * Parameters:	ADC_addr: I2C address for the ADC
 * 				resolution: resolution value for ADC conversion
 * 					MCP3421_RES_12_BIT or MCP3421_LOW_RES
 * 					MCP3421_RES_14_BIT or MCP3421_MEDIUM_RES
 * 					MCP3421_RES_16_BIT or MCP3421_HIGH_RES
 * 					MCP3421_RES_18_BIT or MCP3421_ULTRA_HIGH_RES
 *  			gain: gain setting for ADC
 * 					MCP3421_GAIN_1
 * 					MCP3421_GAIN_2
 * 					MCP3421_GAIN_4
 * 					MCP3421_GAIN_8
 * Return: 		measure in milliVolts
 */
float MCP3421::readADC(uint8_t adc_address, uint8_t resolution, uint8_t gain)
{
	uint8_t tx_bufferI2C[10];
	uint8_t rx_bufferI2C[10];
	uint8_t result;

	double value = -1000.0;

	tx_bufferI2C[0] = 0x80 +(resolution * 4) + gain;

	I2C.begin();
	I2C.write(adc_address, tx_bufferI2C, 1);
	delay(50);

	// START READING
	switch (resolution)
	{
		case MCP3421_RES_12_BIT:
		case MCP3421_RES_14_BIT:
		case MCP3421_RES_16_BIT:

			delay(10);

			result = I2C.read(adc_address, rx_bufferI2C, 3);

			if (result == 0)
			{
				value = rx_bufferI2C[0] * 256 + rx_bufferI2C[1];

				if (resolution == MCP3421_RES_12_BIT)
				{
					value /= pow(2, gain);
				}
				else if (resolution == MCP3421_RES_14_BIT)
				{
					value /= 4;
					value /= pow(2, gain);
				}
				else 
				{
					// value = MAX_VAL * (Vin / Vref(mV)) = 32768 * (Vin / 2048) => Vin = value / 16
					value /= 16;
					value /= pow(2, gain);
				}
			}
			else
			{
				value = -10000.0;
			}
		break;

		case MCP3421_RES_18_BIT:

			delay(300);

			result = I2C.read(adc_address, rx_bufferI2C, 4);

			#if DEBUG_MCP3421 > 0
				PRINTHEX_MCP3421(" | HG: ", rx_bufferI2C[0]);
				PRINTHEX_MCP3421(" | MD: ", rx_bufferI2C[1]);
				PRINTHEX_MCP3421(" | LW: ", rx_bufferI2C[2]);
			#endif

			if (result == 0)
			{
				value = ((long(rx_bufferI2C[0]) << 16) & 0x00010000)  + ( (long(rx_bufferI2C[1]) << 8) & 0x0000FF00) + (long(rx_bufferI2C[2]) & 0x000000FF);

				if ((rx_bufferI2C[0] & 0x02) != 0)
				{
					value = -(131072 - value);
				}

				value = float(value / 64.0 );
				value = value / pow(2, gain);
			}
			else
			{
				value = -10000.0;
			}
		break;
	}

	return value;
}


// Preinstantiate Objects //////////////////////////////////////////////////////
MCP3421 MCP = MCP3421();
