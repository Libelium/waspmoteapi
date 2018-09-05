/*
 *  Library for managing the LMP91000 AFE 
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

#include <LMP91000.h>

// Constructor ///////////////////////////////////////////////////////////////
LMP91000::LMP91000(){}

/* Function: 	This function checks if the LMP91000 can is ready
 * Returns: 	1 if ready, 0 if not ready
*/
uint8_t LMP91000::check()
{
	uint8_t status;
	uint8_t answer;

	answer = I2C.readBit(	I2C_ADDRESS_GASPRO_LMP91000, 
							LMP91000_STATUS_REG, 
							&status, 
							LMP91000_STATUS_REG_STATUS__POS);
	
	if ((answer != 0) || (status == 0))
	{
		return 0;
	}
	
	return 1;
}

/* Function: 	This function sets the LMP91000 to deep sleep mode and shorts
 *				 the FET
 * Returns: 	nothing
*/
void LMP91000::OFF()
{
	setModeReg(	LMP91000_MODEC_REG_FET_SHORTED,
				LMP91000_MODEC_REG_PWR_MODE_DEEP_SLEEP);
}

/* Function: 	This function sets to 1 the lock bit from lock register
 * Returns: 	1 if OK, -1 if error
*/
uint8_t LMP91000::lock_reg()
{
	uint8_t answer;
		
	answer = I2C.writeBit(I2C_ADDRESS_GASPRO_LMP91000, LMP91000_LOCK_REG, LMP91000_LOCK_REG_LOCK, LMP91000_LOCK_REG_LOCK__POS);
	
	return answer;
}

/* Function: 	This function sets to 0 the lock bit from lock register
 * Returns: 	1 if OK, -1 if error
*/
uint8_t LMP91000::unlock_reg()
{	
	uint8_t answer;
	
	answer = I2C.writeBit(	I2C_ADDRESS_GASPRO_LMP91000, LMP91000_LOCK_REG, LMP91000_LOCK_REG_UNLOCK, LMP91000_LOCK_REG_LOCK__POS);
	
	return answer;
}

/* Function: 	This function reads the Rgain selected
 * Returns: 	0 for external resistor
 *				1 for 2K75 resistor
 *				2 for 3K5 resistor
 *				3 for 7K resistor
 *				4 for 14K resistor
 *				5 for 35K resistor
 *				6 for 120K resistor
 *				7 for 350K resistor
 *				-1 if error
*/
float LMP91000::getRgain()
{
	uint8_t answer = 0;
	uint8_t r_gain;

	answer = I2C.readBits(	I2C_ADDRESS_GASPRO_LMP91000, 
							LMP91000_TIAC_REG,
							&r_gain,
							LMP91000_TIAC_REG_REF_R_GAIN__POS,
							LMP91000_TIAC_REG_REF_R_GAIN__LEN);
	if (answer == 0)
	{	
		switch (r_gain)
		{
			case 0:
				return 1000;
			case 1:
				return 2.750;
			case 2:
				return 3.500;
			case 3:
				return 7.0;
			case 4:
				return 14.0;
			case 5:
				return 35.0;
			case 6:
				return 120.0;
			case 7:
				return 350.0;
			default:
				return 0;
		}
	}

	return answer;
}

/* Function: 	This function sets the resistor for the transimpedance stage
 * Parameters:	R_gain: 
 * 					LMP91000_TIAC_REG_REF_R_GAIN_EXT
 * 					LMP91000_TIAC_REG_REF_R_GAIN_2K75
 * 					LMP91000_TIAC_REG_REF_R_GAIN_3K5
 * 					LMP91000_TIAC_REG_REF_R_GAIN_7K
 * 					LMP91000_TIAC_REG_REF_R_GAIN_14K
 * 					LMP91000_TIAC_REG_REF_R_GAIN_35K
 * 					LMP91000_TIAC_REG_REF_R_GAIN_120K
 * 					LMP91000_TIAC_REG_REF_R_GAIN_350K
 * Returns: 	1 if OK, -1 if error
*/
uint8_t LMP91000::setRgain(uint8_t R_gain)
{
	return I2C.writeBits(I2C_ADDRESS_GASPRO_LMP91000, LMP91000_TIAC_REG, R_gain, LMP91000_TIAC_REG_REF_R_GAIN__POS, LMP91000_TIAC_REG_REF_R_GAIN__LEN);
}

/* Function: 	This function reads the internal zero selection
 * Returns: 	0 for 20% of Vref
 *				1 for 50% of Vref
 *				2 for 67% of Vref
 *				3 for bypassed
 * 				-1 if error
*/
float LMP91000::getInternalZero()
{
	uint8_t answer = 0;	
	uint8_t internal_zero;
	float V_ref = getRefSource();

	answer = I2C.readBits(	I2C_ADDRESS_GASPRO_LMP91000,
							LMP91000_REFC_REG,
							&internal_zero,
							LMP91000_REFC_REG_REF_INT_Z__POS,
							LMP91000_REFC_REG_REF_INT_Z__LEN);
	if (answer == 0)
	{
		switch (internal_zero)
		{
			case 0:
				V_ref *= 0.2;
				break;
			case 1:
				V_ref *= 0.5;
				break;
			case 2:
				V_ref *= 0.67;
				break;
			case 3:
				V_ref *= 1;
				break;
		}
		
		return V_ref;
	}
	
	return answer;
}

/* Function: 	This function sets the internal zero voltage from reference 
 * 				source
 * Parameters:	InternalZeroPercentaje: 
 * 					LMP91000_REFC_REG_REF_INT_Z_20
 * 					LMP91000_REFC_REG_REF_INT_Z_50
 * 					LMP91000_REFC_REG_REF_INT_Z_67
 * 					LMP91000_REFC_REG_REF_INT_Z_BYPASSED
 * Returns: 	1 if OK, -1 if error
*/
uint8_t LMP91000::setInternalZero(uint8_t InternalZeroPercentaje)
{

	return I2C.writeBits(I2C_ADDRESS_GASPRO_LMP91000, LMP91000_REFC_REG, InternalZeroPercentaje, LMP91000_REFC_REG_REF_INT_Z__POS, LMP91000_REFC_REG_REF_INT_Z__LEN);
}

/* Function: 	This function reads the reference source selection
 * Returns: 	0 for internal Vref
 *				1 for external Vref
 * 				-1 if error
*/
uint16_t LMP91000::getRefSource()
{
	uint8_t answer = 0;
	uint8_t ref_source;
			
	answer = I2C.readBit(	I2C_ADDRESS_GASPRO_LMP91000,
							LMP91000_REFC_REG,
							&ref_source,
							LMP91000_REFC_REG_REF_SOURCE__POS);
	if (answer == 0)
	{
		// Gets the Vref
		switch (ref_source)
		{
			case 0:
				return 3300;
			case 1:
				return 2048;
		}
	}
	
	return answer;
}

/* Function: 	This function sets the reference voltage source
 * Parameters:	ReferenceSource: internal or external
 * 					LMP91000_REFC_REG_REF_SOURCE_INTERNAL_REF
 * 					LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF
 * Returns: 	1 if OK, -1 if error
*/
uint8_t LMP91000::setRefSource(uint8_t ReferenceSource)
{
	return I2C.writeBit(I2C_ADDRESS_GASPRO_LMP91000, LMP91000_REFC_REG, ReferenceSource, LMP91000_REFC_REG_REF_SOURCE__POS);
}

/* Function: 	This function reads the TIA control register
 * Returns: 	The TIA control reg or 255 if error
*/
uint8_t LMP91000::getTIAConReg()
{
	uint8_t buffer;
	uint8_t answer = 0;
	uint16_t size = 1;

	answer = I2C.read(I2C_ADDRESS_GASPRO_LMP91000, (uint8_t)LMP91000_TIAC_REG, &buffer, size);
	
	if (answer == 0)
	{	
		return buffer;
	}
	
	return answer;
}

/* Function: 	This function reads the reference control register
 * Returns: 	The reference control reg or 255 if error
*/
uint8_t LMP91000::getRefConReg()
{
	uint8_t buffer = 0;
	uint8_t answer = 0;
	
	answer = I2C.read(I2C_ADDRESS_GASPRO_LMP91000, (uint8_t)LMP91000_REFC_REG, &buffer, 1);
	
	if (answer == 0)
	{	
		return buffer;
	}
	
	return answer;
}

/* Function: 	This function reads the mode control register
 * Returns: 	The mode control reg or 255 if error
*/
uint8_t LMP91000::getModeReg()
{
	uint8_t buffer = 0;
	uint8_t answer = 0;
	
	answer = I2C.read(	I2C_ADDRESS_GASPRO_LMP91000, (uint8_t)LMP91000_MODEC_REG, &buffer, 1);
	
	if (answer == 0)
	{	
		return buffer;
	}
	
	return answer;
}

/* Function: 	This function sets the TIA control register
 * Parameters:	R_gain: gain resistor for the transimpedance amplifier
 * 					LMP91000_TIAC_REG_REF_R_GAIN_EXT
 * 					LMP91000_TIAC_REG_REF_R_GAIN_2K75
 * 					LMP91000_TIAC_REG_REF_R_GAIN_3K5
 * 					LMP91000_TIAC_REG_REF_R_GAIN_7K
 * 					LMP91000_TIAC_REG_REF_R_GAIN_14K
 * 					LMP91000_TIAC_REG_REF_R_GAIN_35K
 * 					LMP91000_TIAC_REG_REF_R_GAIN_120K
 * 					LMP91000_TIAC_REG_REF_R_GAIN_350K
 * 				R_load:	load resistor for the sensor
 * 					LMP91000_TIAC_REG_REF_R_LOAD_10R
 * 					LMP91000_TIAC_REG_REF_R_LOAD_33R
 * 					LMP91000_TIAC_REG_REF_R_LOAD_50R
 * 					LMP91000_TIAC_REG_REF_R_LOAD_100R
 * Returns: 	1
*/
uint8_t LMP91000::setTIAConReg(uint8_t R_gain, uint8_t R_load)
{
	uint8_t TIA_con;	
	
	TIA_con = (R_gain * 4) + R_load;
	
	unlock_reg();
	
	return I2C.write(	I2C_ADDRESS_GASPRO_LMP91000, (uint8_t)LMP91000_TIAC_REG, &TIA_con, 1);
}

/* Function: 	This function sets the reference control register
 * Parameters:	ref_source: voltage reference source
 * 					LMP91000_REFC_REG_REF_SOURCE_INTERNAL_REF
 * 					LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF
 * 				int_zero:	internal zero percentage from reference source
 * 					LMP91000_REFC_REG_REF_INT_Z_20
 * 					LMP91000_REFC_REG_REF_INT_Z_50
 * 					LMP91000_REFC_REG_REF_INT_Z_67
 * 					LMP91000_REFC_REG_REF_INT_Z_BYPASSED
 * 				BIAS_perc:	bias percentage from reference source
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_0
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_1
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_2
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_4
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_6
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_8
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_10
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_12
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_14
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_16
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_18
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_20
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_22
 * 					LMP91000_REFC_REG_REF_BIAS_PERC_24
 * 				BIAS_sign:	polarity for bias voltage
 * 					LMP91000_REFC_REG_REF_POLARITY_NEGATIVE
 * 					LMP91000_REFC_REG_REF_POLARITY_POSITIVE
 * Returns: 	1
*/
uint8_t LMP91000::setRefConReg(uint8_t ref_source, uint8_t int_zero, uint8_t BIAS_perc, uint8_t BIAS_sign)
{
	uint8_t ref_con;
		
	ref_con = (128 * ref_source) + (int_zero * 32) + (BIAS_sign * 16) + BIAS_perc;
		
	unlock_reg();

	return I2C.write(	I2C_ADDRESS_GASPRO_LMP91000, (uint8_t)LMP91000_REFC_REG, &ref_con, 1);
}

/* Function: 	This function sets the mode control register
 * Parameters:	FET_short: enables or disables de shorting FET
 * 					LMP91000_MODEC_REG_FET_NOT_SHORTED
 * 					LMP91000_MODEC_REG_FET_SHORTED
 * 				op_mode:	working mode
 * 					LMP91000_MODEC_REG_PWR_MODE_DEEP_SLEEP
 * 					LMP91000_MODEC_REG_PWR_MODE_2_LEAD_GALVANIC
 * 					LMP91000_MODEC_REG_PWR_MODE_STAND_BY
 * 					LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPERIOMETRIC
 * 					LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_OFF
 * 					LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_ON
 * 					LMP91000_MODEC_REG_PWR_MODE_NO_CHANGE
 * Returns: 	1
*/
uint8_t LMP91000::setModeReg(uint8_t FET_short, uint8_t op_mode)
{
	uint8_t mode_con;
	
	mode_con = (128 * FET_short) + op_mode;
	
	unlock_reg();
	
	return I2C.write(I2C_ADDRESS_GASPRO_LMP91000, (uint8_t)LMP91000_MODEC_REG, &mode_con, 1);
}

// Preinstantiate Objects //////////////////////////////////////////////////////
LMP91000 LMP = LMP91000();

