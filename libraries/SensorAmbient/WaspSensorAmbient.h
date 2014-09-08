/*! \file WaspSensorAmbient.h
    \brief Library for environmental Sensors
    
    Copyright (C) 2014 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.1
    Design:			David Gascón
    Implementation:	Alberto Bielsa, Manuel Calahorra, Yuri Carmona, Jorge Casanova, Javier Siscart
     
    Based on K. Townsend Library.
 */

 /*! \def WaspSensorAmbient.h
    \brief The library flag
    
  */
#ifndef WaspSensorAmbient_h
#define WaspSensorAmbient_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>
#include <WaspConstants.h>


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def AMBIENT_DEBUG
    \brief Debug mode definition. Comment this line to disable debug mode. Uncomment to enable. 
 */
#define SENS_AMBIENT_DEBUG

// Pin out definition
#define SENS_AMBIENT_SENSIRION_PWR		15
#define SENS_AMBIENT_SENSIRION_DATA	17
#define SENS_AMBIENT_LDR_OUT			ANALOG6
#define SENS_AMBIENT_SENSIRION_CLK		DIGITAL2
#define SENS_AMBIENT_LDR_PWR			DIGITAL4
#define SENS_AMBIENT_SENSIRION_GND		DIGITAL6
#define SENS_AMBIENT_LDR_GND			DIGITAL8
#define SENS_AMBIENT_LUX_PWR			SENS_PW_3V3

/*! \def SENS_AMBIENT_TEMPERATURE
    \brief Sensirion temperature
 */
/*! \def SENS_AMBIENT_HUMIDITY
    \brief Sensirion humidity
 */
 /*! \def SENS_LDR
    \brief LDR sensor
 */
 /*! \def SENS_LUX
    \brief Lux sensor
 */
#define SENS_AMBIENT_TEMPERATURE		1
#define SENS_AMBIENT_HUMIDITY			2
#define SENS_AMBIENT_LDR				4
#define SENS_AMBIENT_LUX				8

/*! \def SENS_PREC_HIGH
    \brief Sensirion High Precision
 */
/*! \def SENS_PREC_LOW
    \brief Sensirion Low Precision
 */
#define SENS_PREC_HIGH					1
#define SENS_PREC_LOW					0

// LUX auxiliary definitions
#ifndef _TSL2561_H_
#define _TSL2561_H_
#define TSL2561_VISIBLE 				2 // channel 0 - channel 1
#define TSL2561_INFRARED 				1 // channel 1
#define TSL2561_FULLSPECTRUM 			0 // channel 0
//i2c address
#define TSL2561_ADDR_FLOAT 			0x39
// Lux calculations
#define TSL2561_PACKAGE_T_FN_CL
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

// Lux auxiliary data
enum
{
  TSL2561_REGISTER_CONTROL          = 0x00,
  TSL2561_REGISTER_TIMING           = 0x01,
  TSL2561_REGISTER_THRESHHOLDL_LOW  = 0x02,
  TSL2561_REGISTER_THRESHHOLDL_HIGH = 0x03,
  TSL2561_REGISTER_THRESHHOLDH_LOW  = 0x04,
  TSL2561_REGISTER_THRESHHOLDH_HIGH = 0x05,
  TSL2561_REGISTER_INTERRUPT        = 0x06,
  TSL2561_REGISTER_CRC              = 0x08,
  TSL2561_REGISTER_ID               = 0x0A,
  TSL2561_REGISTER_CHAN0_LOW        = 0x0C,
  TSL2561_REGISTER_CHAN0_HIGH       = 0x0D,
  TSL2561_REGISTER_CHAN1_LOW        = 0x0E,
  TSL2561_REGISTER_CHAN1_HIGH       = 0x0F
};

// Lux auxiliary data
typedef enum
{
  TSL2561_INTEGRATIONTIME_13MS      = 0x00,    // 13.7ms
  TSL2561_INTEGRATIONTIME_101MS     = 0x01,    // 101ms
  TSL2561_INTEGRATIONTIME_402MS     = 0x02     // 402ms
}
tsl2561IntegrationTime_t;

// Lux auxiliary data
typedef enum
{
  TSL2561_GAIN_0X                   = 0x00,    // No gain
  TSL2561_GAIN_16X                  = 0x10,    // 16x gain
}
tsl2561Gain_t;

#endif	// end of lux definitions

/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspSensorAmbient Class
/*!
	WaspSensorAmbient Class defines all the variables and functions used for managing
	the Ambient Sensors
 */
class WaspSensorAmbient
{
	private:
	
	//! Variable : Lux sensor address
    	/*!
	*/
	int8_t _addr;
	
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
	
	//! It reads from the sensirion
  	/*!
	\param uint8_t parameter : TEMPERATURE or HUMIDITY
	\return the value returned by the sensor
	 */
	float readSensirion(uint8_t parameter);
	
	//! It converts the temperature returned by sensirion
  	/*!
	\param int readValue : value returned by sensirion
	\param int precision : precission bits
	\return the converted value
	 */	
	float temperatureConversion(int readValue, int precision);
	
	//! It converts the humidity returned by sensirion
  	/*!
	\param int readValue : value returned by sensirion
	\param int precision : precission bits
	\return the converted value
	 */
	float humidityConversion(int readValue, int precision);
	
	
	//! It reads the Sensirion temperature value
  	/*!
	\return the value returned by the sensor
	 */
	float readSensirionTemperature(void);

	//! It reads the Sensirion humidity value
  	/*!
	\return the value returned by the sensor
	 */
	float readSensirionHumidity(void);

	//! It reads the LDR
  	/*!
	\return the value returned by the sensor
	 */
	float readLDR(void);
	
	//! It reads the Lux Sensor
  	/*!
	\return the value returned by the sensor
	 */	
	boolean begin(void);
	
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
	
	//! Write a register of Lux sensor
  	/*!
	\param r: register to write
	\param v: value to write
	
	\return void
	 */
	void write8(uint8_t r, uint8_t v);
	
	//! REad a lux sensor reguster
  	/*!
	\param reg: register to be read
	
	\return register value
	 */
	uint16_t read16(uint8_t reg);
	
	//! Calculate luxes measured by lux sensor
  	/*!
	\param ch0: channel 0
	\param ch1: channel 1
	\return luxes
	 */
	uint32_t calculateLux(uint16_t ch0, uint16_t ch1);
	
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
	
	//! Reads the lux sensor
  	/*!
	\param channel: sellects lux ssensor channel
	
	\return lux
	 */
	uint16_t getLuminosity (uint8_t channel);
	
	//! Reads lux sensor
  	/*!
	\param 
	
	\return lux
	 */
	uint32_t getFullLuminosity ();
	
	//! Initialize aux variables of Lux sensor
  	/*!
	\param addr: lux sensor address
	
	\return void
	 */
	void TSL2561(uint8_t addr);
	
	
	public:
	
	//! class constructor
  	/*!
	It initializes the different digital pins
	\param void
	\return void
	 */
	WaspSensorAmbient();
	
	//! It sets ON/OFF the different sensor switches
  	/*!
	\param uint8_t mode : SENS_ON or SENS_OFF
	\param uint16_t sensor : the sensor to set ON/OFF
	\return error
	 */
	int8_t setSensorMode(uint8_t mode, uint16_t sensor);


	//! Reads the corresponding sensor
  	/*!
	\param uint16_t sensor : the sensor to be read
	\return error
	 */
	float readValue(uint8_t sensor);

	//! Read Luxes in bright environments (outdoors)
  	/*!
	\param void
	
	\return luxes
	 */
	float readLUXbright(void);
	
	//! Read Luxes in medium light environments 
  	/*!
	\param void
	
	\return luxes
	 */
	float readLUXmedium(void);
	
	//! Read Luxes in low light environments 
  	/*!
	\param void
	
	\return luxes
	 */
	float readLUXdim(void);
	
	//! Read Luxes and calculate other parameters in bright environments
  	/*!
	\param void
	
	\return lux
	 */
	float readLUMINOSITYbright(void);
	
	//!  Read Luxes and calculate other parameters in medium light environments 
  	/*!
	\param void
	
	\return luxes
	 */
	float readLUMINOSITYmedium(void);
	
	//!  Read Luxes and calculate other parameters in low light environments 
  	/*!
	\param void
	
	\return luxes
	 */
	float readLUMINOSITYdim(void);

};

extern WaspSensorAmbient SensorAmbient;

#endif

