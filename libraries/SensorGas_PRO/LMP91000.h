/*! \file LMP91000.h
    \brief Library for managing the LMP91000 AFE 
    
    Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.2
    Design:			David Gascón
    Implementation:	Alejandro Gállego

*/

/*! \def LMP91000_h
    \brief The library flag
    
 */
#ifndef LMP91000_h
#define LMP91000_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>

#define LMP_DEBUG 0


// REGISTER TABLE
#define LMP91000_STATUS_REG	0x00
#define LMP91000_LOCK_REG		0x01
#define LMP91000_TIAC_REG		0x10
#define LMP91000_REFC_REG		0x11
#define LMP91000_MODEC_REG		0x12

// STATUS REGISTER
#define LMP91000_STATUS_REG_STATUS__POS	0

// LOCK REGISTER
#define LMP91000_LOCK_REG_LOCK__POS	0
#define LMP91000_LOCK_REG_UNLOCK		0
#define LMP91000_LOCK_REG_LOCK			1

// TIA CONTROL REGISTER
#define LMP91000_TIAC_REG_REF_R_GAIN__POS		2
#define LMP91000_TIAC_REG_REF_R_GAIN__LEN		3

#define LMP91000_TIAC_REG_REF_R_GAIN_EXT		0
#define LMP91000_TIAC_REG_REF_R_GAIN_2K75		1
#define LMP91000_TIAC_REG_REF_R_GAIN_3K5		2
#define LMP91000_TIAC_REG_REF_R_GAIN_7K		3
#define LMP91000_TIAC_REG_REF_R_GAIN_14K		4
#define LMP91000_TIAC_REG_REF_R_GAIN_35K		5
#define LMP91000_TIAC_REG_REF_R_GAIN_120K		6
#define LMP91000_TIAC_REG_REF_R_GAIN_350K		7
#define LMP91000_GAIN_0		0
#define LMP91000_GAIN_1		1
#define LMP91000_GAIN_2		2
#define LMP91000_GAIN_3		3
#define LMP91000_GAIN_4		4
#define LMP91000_GAIN_5		5
#define LMP91000_GAIN_6		6
#define LMP91000_GAIN_7		7


#define LMP91000_TIAC_REG_REF_R_LOAD__POS		0
#define LMP91000_TIAC_REG_REF_R_LOAD__LEN		2

#define LMP91000_TIAC_REG_REF_R_LOAD_10R		0
#define LMP91000_TIAC_REG_REF_R_LOAD_33R		1
#define LMP91000_TIAC_REG_REF_R_LOAD_50R		2
#define LMP91000_TIAC_REG_REF_R_LOAD_100R		3


// REFERENCE CONTROL REGISTER
#define LMP91000_REFC_REG_REF_SOURCE__POS			7

#define LMP91000_REFC_REG_REF_SOURCE_INTERNAL_REF	0
#define LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF	1


#define LMP91000_REFC_REG_REF_INT_Z__POS		5
#define LMP91000_REFC_REG_REF_INT_Z__LEN		2

#define LMP91000_REFC_REG_REF_INT_Z_20			0
#define LMP91000_REFC_REG_REF_INT_Z_50			1
#define LMP91000_REFC_REG_REF_INT_Z_67			2
#define LMP91000_REFC_REG_REF_INT_Z_BYPASSED		3


#define LMP91000_REFC_REG_REF_POLARITY__POS		7

#define LMP91000_REFC_REG_REF_POLARITY_NEGATIVE	0
#define LMP91000_REFC_REG_REF_POLARITY_POSITIVE	1


#define LMP91000_REFC_REG_REF_BIAS__POS		0
#define LMP91000_REFC_REG_REF_BIAS__LEN		4

#define LMP91000_REFC_REG_REF_BIAS_PERC_0 		0
#define LMP91000_REFC_REG_REF_BIAS_PERC_1 		1
#define LMP91000_REFC_REG_REF_BIAS_PERC_2 		2
#define LMP91000_REFC_REG_REF_BIAS_PERC_4 		3
#define LMP91000_REFC_REG_REF_BIAS_PERC_6 		4
#define LMP91000_REFC_REG_REF_BIAS_PERC_8 		5
#define LMP91000_REFC_REG_REF_BIAS_PERC_10		6
#define LMP91000_REFC_REG_REF_BIAS_PERC_12		7
#define LMP91000_REFC_REG_REF_BIAS_PERC_14		8
#define LMP91000_REFC_REG_REF_BIAS_PERC_16		9
#define LMP91000_REFC_REG_REF_BIAS_PERC_18		10
#define LMP91000_REFC_REG_REF_BIAS_PERC_20		11
#define LMP91000_REFC_REG_REF_BIAS_PERC_22		12
#define LMP91000_REFC_REG_REF_BIAS_PERC_24		13


// MODE CONTROL REGISTER
#define LMP91000_MODEC_REG_FET__POS				7

#define LMP91000_MODEC_REG_FET_NOT_SHORTED		0
#define LMP91000_MODEC_REG_FET_SHORTED			1


#define LMP91000_MODEC_REG_PWR_MODE__POS					0
#define LMP91000_MODEC_REG_PWR_MODE__LEN					3

#define LMP91000_MODEC_REG_PWR_MODE_DEEP_SLEEP				0
#define LMP91000_MODEC_REG_PWR_MODE_2_LEAD_GALVANIC		1
#define LMP91000_MODEC_REG_PWR_MODE_STAND_BY				2
#define LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPERIOMETRIC	3
#define LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_OFF			6
#define LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_ON			7
#define LMP91000_MODEC_REG_PWR_MODE_NO_CHANGE				8


#define AFE_DEEP_SLEEP		0
#define AFE_STAND_BY		2
#define AFE_AMPERIOMETRIC	3


/******************************************************************************
 * Class
 ******************************************************************************/
 
//! LMP91000 Class
/*!
	LMP91000 Class defines all the variables and functions used to manage LMP91000 
 */
class LMP91000
{
	private:

	public:

	LMP91000();
	
	//! This function checks if the LMP91000 can is ready
	/*!
	\return		1 if ready, 0 if not ready
	*/
	bool check();	

	//! This function sets the LMP91000 to deep sleep mode and shorts the FET
	/*!
	\return		nothing
	*/
	void OFF();
	
	//! This function sets to 1 the lock bit from lock register
	/*!
	\return		1 if OK, -1 if error
	*/
	int8_t lock_reg();
	
	//! This function sets to 0 the lock bit from lock register
	/*!
	\return		1 if OK, -1 if error
	*/
	int8_t unlock_reg();
	
	//! This function reads the Rgain selected
	/*!
	\return		0 for external resistor
				1 for 2K75 resistor
				2 for 3K5 resistor
				3 for 7K resistor
				4 for 14K resistor
				5 for 35K resistor
				6 for 120K resistor
				7 for 350K resistor
				-1 if error
	*/
	int8_t getRgain();
	
	//! This function sets the resistor for the transimpedance stage
	/*!
	\param uint8_t R_gain: LMP91000_TIAC_REG_REF_R_GAIN_EXT
					LMP91000_TIAC_REG_REF_R_GAIN_2K75
					LMP91000_TIAC_REG_REF_R_GAIN_3K5
 					LMP91000_TIAC_REG_REF_R_GAIN_7K
					LMP91000_TIAC_REG_REF_R_GAIN_14K
					LMP91000_TIAC_REG_REF_R_GAIN_35K
					LMP91000_TIAC_REG_REF_R_GAIN_120K
					LMP91000_TIAC_REG_REF_R_GAIN_350K
	\return		1 if OK
				-1 if error
	*/
	int8_t setRgain(uint8_t R_gain);
	
	//! This function reads the internal zero selection
	/*!
	\return		0 for 20% of Vref
				1 for 50% of Vref
				2 for 67% of Vref
				3 for bypassed
				-1 if error
	*/
	int8_t getInternalZero();
	
	//! This function sets the internal zero voltage from reference source
	/*!
	\param uint8_t InternalZeroPercentaje: LMP91000_REFC_REG_REF_INT_Z_20
					LMP91000_REFC_REG_REF_INT_Z_50
					LMP91000_REFC_REG_REF_INT_Z_67
					LMP91000_REFC_REG_REF_INT_Z_BYPASSED
	\return		1 if OK
				-1 if error
	*/
	int8_t setInternalZero(uint8_t InternalZeroPercentaje);
	
	//! This function reads the reference source selection
	/*!
	\return		0 for internal Vref
				1 for external Vref
				-1 if error
	*/
	int8_t getRefSource();
	
	//! This function sets the reference voltage source
	/*!
	\param uint8_t ReferenceSource: LMP91000_REFC_REG_REF_SOURCE_INTERNAL_REF
					LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF
	\return		1 if OK
				-1 if error
	*/
	int8_t setRefSource(uint8_t ReferenceSource);

	//! This function reads the TIA control register
	/*!
	\return		The TIA control reg or 255 if error
	*/
	uint8_t getTIAConReg();

	//! This function reads the reference control register
	/*!
	\return		The reference control reg or 255 if error
	*/
	uint8_t getRefConReg();

	//! This function reads the mode control register
	/*!
	\return		The mode control reg or 255 if error
	*/
	uint8_t getModeReg();

	//! This function sets the TIA control register
	/*!
	\param uint8_t R_gain: gain resistor for the transimpedance amplifier
						LMP91000_TIAC_REG_REF_R_GAIN_EXT
						LMP91000_TIAC_REG_REF_R_GAIN_2K75
						LMP91000_TIAC_REG_REF_R_GAIN_3K5
						LMP91000_TIAC_REG_REF_R_GAIN_7K
						LMP91000_TIAC_REG_REF_R_GAIN_14K
						LMP91000_TIAC_REG_REF_R_GAIN_35K
						LMP91000_TIAC_REG_REF_R_GAIN_120K
						LMP91000_TIAC_REG_REF_R_GAIN_350K
	\param uint8_t R_load: load resistor for the sensor
						LMP91000_TIAC_REG_REF_R_LOAD_10R
						LMP91000_TIAC_REG_REF_R_LOAD_33R
						LMP91000_TIAC_REG_REF_R_LOAD_50R
						LMP91000_TIAC_REG_REF_R_LOAD_100R
	\return		1
	*/
	int8_t setTIAConReg(uint8_t R_gain, uint8_t R_load);
	
	//! This function sets the reference control register
	/*!
	\param uint8_t ref_source: voltage reference source
						LMP91000_REFC_REG_REF_SOURCE_INTERNAL_REF
						LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF
	\param uint8_t int_zero: internal zero percentage from reference source
						LMP91000_REFC_REG_REF_INT_Z_20
						LMP91000_REFC_REG_REF_INT_Z_50
						LMP91000_REFC_REG_REF_INT_Z_67
						LMP91000_REFC_REG_REF_INT_Z_BYPASSED
	\param uint8_t BIAS_perc: bias percentage from reference source
						LMP91000_REFC_REG_REF_BIAS_PERC_0
						LMP91000_REFC_REG_REF_BIAS_PERC_1
						LMP91000_REFC_REG_REF_BIAS_PERC_2
						LMP91000_REFC_REG_REF_BIAS_PERC_4
						LMP91000_REFC_REG_REF_BIAS_PERC_6
						LMP91000_REFC_REG_REF_BIAS_PERC_8
						LMP91000_REFC_REG_REF_BIAS_PERC_10
						LMP91000_REFC_REG_REF_BIAS_PERC_12
						LMP91000_REFC_REG_REF_BIAS_PERC_14
						LMP91000_REFC_REG_REF_BIAS_PERC_16
						LMP91000_REFC_REG_REF_BIAS_PERC_18
						LMP91000_REFC_REG_REF_BIAS_PERC_20
						LMP91000_REFC_REG_REF_BIAS_PERC_22
						LMP91000_REFC_REG_REF_BIAS_PERC_24
	\param uint8_t BIAS_sign: polarity for bias voltage
						LMP91000_REFC_REG_REF_POLARITY_NEGATIVE
						LMP91000_REFC_REG_REF_POLARITY_POSITIVE
	\return		1
	*/
	int8_t setRefConReg(uint8_t ref_source, uint8_t int_zero, uint8_t BIAS_perc, uint8_t BIAS_sign);
	
	//! This function sets the mode control register
	/*!
	\param uint8_t FET_short: enables or disables de shorting FET
						LMP91000_MODEC_REG_FET_NOT_SHORTED
						LMP91000_MODEC_REG_FET_SHORTED
	\param uint8_t op_mode:	working mode
						LMP91000_MODEC_REG_PWR_MODE_DEEP_SLEEP
						LMP91000_MODEC_REG_PWR_MODE_2_LEAD_GALVANIC
						LMP91000_MODEC_REG_PWR_MODE_STAND_BY
						LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPERIOMETRIC
						LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_OFF
						LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_ON
						LMP91000_MODEC_REG_PWR_MODE_NO_CHANGE
	\return		1
	*/
	int8_t setModeReg(uint8_t FET_short, uint8_t op_mode);
	
};

extern LMP91000 LMP;

#endif
