/*! \file LMP91000.h
    \brief Library for managing the LMP91000 AFE 
    
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
#define LMP91000_MODEC_REG_PWR_MODE_2_LEAD_GALVANIC			1
#define LMP91000_MODEC_REG_PWR_MODE_STAND_BY				2
#define LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPEROMETRIC		3
#define LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_OFF			6
#define LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_ON				7
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
		
		void OFF();
		
		uint8_t check();
		uint8_t lock_reg();
		uint8_t unlock_reg();
		
		float getRgain();
		float getInternalZero();
		
		uint8_t setRgain(uint8_t );		
		uint8_t setInternalZero(uint8_t);
		
		uint16_t getRefSource();
		uint8_t setRefSource(uint8_t);
		
		uint8_t getTIAConReg();
		uint8_t getRefConReg();
		uint8_t getModeReg();
		uint8_t setTIAConReg(uint8_t , uint8_t );
		uint8_t setRefConReg(uint8_t , uint8_t , uint8_t , uint8_t);
		uint8_t setModeReg(uint8_t , uint8_t);
};

extern LMP91000 LMP;

#endif
