/*! \file TSL2561.h
    \brief Library for managing the TSL2561 sensor (luxes accuracy)

    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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

    Version:		3.2
    Design:			David Gascón
    Implementation:	Alejandro Gállego

*/

/*! \def TSL2561_h
    \brief The library flag

*/
#ifndef TSL2561_h
#define TSL2561_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>

/*! Possible values:
 * 	0: No debug mode enabled
 * 	1: debug 1
 * 	2: debug 2
 */
#define TSL2561_DEBUG 0
// #define TSL2561_DEBUG 1
// #define TSL2561_DEBUG 2

#define PRINT_LUX(str)	USB.print(F("[LUX] ")); USB.print(str);



//! Sensor Specific constants
// LUX auxiliary definitions
#define TSL2561_FULLSPECTRUM 			0 // channel 0
#define TSL2561_INFRARED 				1 // channel 1
#define TSL2561_VISIBLE 				2 // channel 0 - channel 1

#define TSL2561_LOW_RES					0
#define TSL2561_MED_RES					1
#define TSL2561_HIGH_RES				2

#define TSL2561_GAIN_1					0
#define TSL2561_GAIN_16					1


/// Register address
#define TSL2561_CONTROL_REG				(uint8_t)0x00
#define TSL2561_TIMING_REG				(uint8_t)0x01
#define TSL2561_THRESHHOLDL_LOW_REG		(uint8_t)0x02
#define TSL2561_THRESHHOLDL_HIGH_REG	(uint8_t)0x03
#define TSL2561_THRESHHOLDH_LOW_REG		(uint8_t)0x04
#define TSL2561_THRESHHOLDH_HIGH_REG	(uint8_t)0x05
#define TSL2561_INTERRUPT_REG			(uint8_t)0x06
#define TSL2561_CRC_REG					(uint8_t)0x08
#define TSL2561_CHIP_ID_REG				(uint8_t)0x0A
#define TSL2561_CHAN0_LOW_REG			(uint8_t)0x0C
#define TSL2561_CHAN0_HIGH_REG			(uint8_t)0x0D
#define TSL2561_CHAN1_LOW_REG			(uint8_t)0x0E
#define TSL2561_CHAN1_HIGH_REG			(uint8_t)0x0F

/// ID Register
#define TSL2561_CHIP_ID_REG_CHIP_ID		0x0A





// Lux calculations
#define TSL2561_READBIT           		(0x01)
#define TSL2561_COMMAND_BIT       		(0x80)    // Must be 1
#define TSL2561_CLEAR_BIT         		(0x40)    // Clears any pending interrupt (write 1 to clear)
#define TSL2561_WORD_BIT          		(0x20)    // 1 = read/write word (rather than byte)
#define TSL2561_BLOCK_BIT         		(0x10)    // 1 = using block read/write
#define TSL2561_CONTROL_POWERON   		(0x03)
#define TSL2561_CONTROL_POWEROFF  		(0x00)
#define TSL2561_LUX_LUXSCALE      		(14)      // Scale by 2^14
#define TSL2561_LUX_RATIOSCALE    		(9)       // Scale ratio by 2^9
#define TSL2561_LUX_CHSCALE       		(10)      // Scale channel values by 2^10
#define TSL2561_LUX_CHSCALE_TINT0 		(0x7517)  // 322/11 * 2^TSL2561_LUX_CHSCALE
#define TSL2561_LUX_CHSCALE_TINT1 		(0x0FE7)  // 322/81 * 2^TSL2561_LUX_CHSCALE

//Values
#define TSL2561_LUX_K1T           		(0x0040)  // 0.125 * 2^RATIO_SCALE
#define TSL2561_LUX_B1T           		(0x01f2)  // 0.0304 * 2^LUX_SCALE
#define TSL2561_LUX_M1T           		(0x01be)  // 0.0272 * 2^LUX_SCALE
#define TSL2561_LUX_K2T           		(0x0080)  // 0.250 * 2^RATIO_SCALE
#define TSL2561_LUX_B2T           		(0x0214)  // 0.0325 * 2^LUX_SCALE
#define TSL2561_LUX_M2T           		(0x02d1)  // 0.0440 * 2^LUX_SCALE
#define TSL2561_LUX_K3T           		(0x00c0)  // 0.375 * 2^RATIO_SCALE
#define TSL2561_LUX_B3T           		(0x023f)  // 0.0351 * 2^LUX_SCALE
#define TSL2561_LUX_M3T           		(0x037b)  // 0.0544 * 2^LUX_SCALE
#define TSL2561_LUX_K4T           		(0x0100)  // 0.50 * 2^RATIO_SCALE
#define TSL2561_LUX_B4T           		(0x0270)  // 0.0381 * 2^LUX_SCALE
#define TSL2561_LUX_M4T           		(0x03fe)  // 0.0624 * 2^LUX_SCALE
#define TSL2561_LUX_K5T           		(0x0138)  // 0.61 * 2^RATIO_SCALE
#define TSL2561_LUX_B5T           		(0x016f)  // 0.0224 * 2^LUX_SCALE
#define TSL2561_LUX_M5T           		(0x01fc)  // 0.0310 * 2^LUX_SCALE
#define TSL2561_LUX_K6T           		(0x019a)  // 0.80 * 2^RATIO_SCALE
#define TSL2561_LUX_B6T           		(0x00d2)  // 0.0128 * 2^LUX_SCALE
#define TSL2561_LUX_M6T           		(0x00fb)  // 0.0153 * 2^LUX_SCALE
#define TSL2561_LUX_K7T           		(0x029a)  // 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B7T           		(0x0018)  // 0.00146 * 2^LUX_SCALE
#define TSL2561_LUX_M7T           		(0x0012)  // 0.00112 * 2^LUX_SCALE
#define TSL2561_LUX_K8T           		(0x029a)  // 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B8T           		(0x0000)  // 0.000 * 2^LUX_SCALE
#define TSL2561_LUX_M8T           		(0x0000)  // 0.000 * 2^LUX_SCALE

#define OUTDOOR		0
#define INDOOR		1

// Lux auxiliary data
typedef enum
{
  TSL2561_INTEGRATIONTIME_13MS      = 0x00,    // 13.7ms, fast but low resolution
  TSL2561_INTEGRATIONTIME_101MS     = 0x01,    // 101ms, medium resolution and speed
  TSL2561_INTEGRATIONTIME_402MS     = 0x02     // 402ms, 16-bit data but slowest conversions
}
tsl2561IntegrationTime_t;

// Lux auxiliary data
typedef enum
{
  TSL2561_GAIN_0X                   = 0x00,    // No gain, use in bright light to avoid sensor saturation
  TSL2561_GAIN_16X                  = 0x10,    // 16x gain, use in low light to boost sensitivity
}
tsl2561Gain_t;

/******************************************************************************
 * Class
 ******************************************************************************/

//! TSL2561 Class
/*!
	TSL2561 Class defines all the variables and functions used to manage TSL2561 sensor
 */
class TSL2561
{
	private:

	//! Variable : aux variable for Lux sensor
    	/*!
	*/
	tsl2561IntegrationTime_t _integration;

	//! Variable : Gain for the Lux sensor
    	/*!
	*/
	tsl2561Gain_t _gain;

	//! Variable : stores lux sensor state
    	/*!
	*/
	boolean _initialized;

	//! Enables lux sensor
  	/*!
	\param void

	\return void
	 */
	void enable(void);

	//! Disables lux sensor
  	/*!
	\param void

	\return void
	 */
	void disable(void);

	//! Calculate luxes measured by lux sensor
  	/*!
	\param ch0: channel 0
	\param ch1: channel 1
	\return nothing
	 */
	void calculateLux();

	//! Configures luxes sensor
  	/*!
	\param integration:

	\return void
	 */
	void setTiming(tsl2561IntegrationTime_t integration);

	//! Sets Lux sensor gain
  	/*!
	\param gain: gain to be set

	\return
	 */
	void setGain(tsl2561Gain_t gain);

	//! Reads lux sensor
  	/*!
	\param

	\return lux
	 */
	int8_t getFullLuminosity ();



	boolean checkID();

	public:

	// Constructors
	TSL2561();


	//! Variable : value measured in luxes
    	/*!
	*/
	uint32_t lux;


	uint16_t ir, full, visible;


	//! Turn on the sensor and preconfigurates it
  	/*!
	\param void
	\return luxes
	 */
	boolean ON(void);

	int8_t getLuminosity();
	int8_t getLuminosity(uint8_t res);
	int8_t getLuminosity(uint8_t res, bool gain);

};


extern TSL2561 TSL;

#endif
