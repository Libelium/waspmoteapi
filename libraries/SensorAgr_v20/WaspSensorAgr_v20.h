/*! \file WaspSensorAgr_v20.h
    \brief Library for managing the Agriculture Sensor Board v2.0
    
    Copyright (C) 2013 Libelium Comunicaciones Distribuidas S.L.
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
  
    Version:		1.0
    Design:			David Gascón
    Implementation:	Alberto Bielsa, Manuel Calahorra, Yuri Carmona

 */

 /*! \def WaspSensorAgr_v20_h
    \brief The library flag
    
  */
#ifndef WaspSensorAgr_v20_h
#define WaspSensorAgr_v20_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>
#include <WaspConstants.h>


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def SENS_AGR_PLUVIOMETER
    \brief Sensor types. Pluviometer sensor in this case (two sensors may be connected to this socket)
    
 */
/*! \def SENS_AGR_ANEMOMETER
    \brief Sensor types. Anemometer sensor in this case
    
 */
/*! \def SENS_AGR_WATERMARK_1
    \brief Sensor types. Watermark sensor in this case
    
 */
/*! \def SENS_AGR_WATERMARK_2
    \brief Sensor types. Watermark sensor in this case
    
 */
/*! \def SENS_AGR_WATERMARK_3
    \brief Sensor types. Watermark sensor in this case
    
 */
/*! \def SENS_AGR_VANE
    \brief Sensor types. Vane sensor in this case
    
 */
/*! \def SENS_AGR_DENDROMETER
    \brief Sensor types. Dendrometer sensor in this case
    
 */
/*! \def SENS_AGR_PT1000
    \brief Sensor types. PT1000 sensor in this case 
    
 */
/*! \def SENS_AGR_LEAF_WETNESS
    \brief Sensor types. Leaf wetness sensor in this case
    
 */
/*! \def SENS_AGR_TEMPERATURE
    \brief Sensor types. Temperature sensor in this case 
    
 */
/*! \def SENS_AGR_HUMIDITY
    \brief Sensor types. Humidity sensor in this case 
    
 */
/*! \def SENS_AGR_RADIATION
    \brief Sensor types. Sun radiation sensor in this case (two sensors may be connected to this socket)
    
 */
/*! \def SENS_AGR_SENSIRION
    \brief Sensor types. Sensirion sensor in this case (two sensors may be connected to this socket)
    
 */
/*! \def SENS_AGR_PRESSURE
    \brief Sensor types. Pressure sensor in this case
    
 */

/*! \def SENS_AGR_LDR
    \brief Sensor types. Pressure sensor in this case
    
 */

/*! \def SENS_AGR_TEMP_DS18B20
    \brief Sensor types. Pressure sensor in this case
    
 */

#define	SENS_AGR_PLUVIOMETER		16
#define	SENS_AGR_ANEMOMETER 		1
#define	SENS_AGR_WATERMARK_1		2
#define	SENS_AGR_WATERMARK_2		4
#define	SENS_AGR_WATERMARK_3		8
#define	SENS_AGR_VANE				0
#define	SENS_AGR_DENDROMETER		32
#define	SENS_AGR_PT1000				64
#define	SENS_AGR_LEAF_WETNESS		128
#define	SENS_AGR_TEMPERATURE		256
#define	SENS_AGR_HUMIDITY			512
#define	SENS_AGR_RADIATION			1024
#define	SENS_AGR_SENSIRION			2048
#define	SENS_AGR_PRESSURE			4096
#define	SENS_AGR_LDR				8192
#define	SENS_AGR_TEMP_DS18B20		16384

/*! \def SENS_SWITCH_1
    \brief Switches for powering the sensors
    
 */
/*! \def SENS_SWITCH_2
    \brief Switches for powering the sensors
    
 */
/*! \def SENS_SWITCH_3
    \brief Switches for powering the sensors
    
 */
/*! \def SENS_SWITCH_4
    \brief Switches for powering the sensors
    
 */
/*! \def SENS_MUX_SEL
    \brief Sensor multiplexer selector
    
 */
#define	SENS_SWITCH_1	DIGITAL7
#define	SENS_SWITCH_2	DIGITAL1
#define	SENS_SWITCH_3	ANA0
#define	SENS_SWITCH_4	DIGITAL5
#define SENS_MUX_SEL	DIGITAL3


/*! \def SENS_CLK
    \brief Sensirion CLK pin
    
 */
/*! \def SENS_DATA
    \brief Sensirion CLK data
    
 */
/*! \def SENS_PREC_HIGH
    \brief Sensirion High Precision
    
 */
/*! \def SENS_PREC_LOW
    \brief Sensirion Low Precision
    
 */
/*! \def SENSIRION_TEMP
    \brief Sensirion Temperature
    
 */
/*! \def SENSIRION_HUM
    \brief Sensirion Humidity
    
 */
#define SENS_CLK	DIGITAL8
#define SENS_DATA	DIGITAL6
#define SENS_PREC_HIGH	1
#define SENS_PREC_LOW	0
#define SENSIRION_TEMP	0
#define SENSIRION_HUM	1


/*! \def SENS_AGR_VANE_N
    \brief Vane : North Direction
    
 */
/*! \def SENS_AGR_VANE_NNE
    \brief Vane : North-NorthEast Direction
    
 */
/*! \def SENS_AGR_VANE_NE
    \brief Vane : NorthEast Direction
    
 */
/*! \def SENS_AGR_VANE_ENE
    \brief Vane : East-NorthEast Direction
    
 */
/*! \def SENS_AGR_VANE_E
    \brief Vane : East Direction
    
 */
/*! \def SENS_AGR_VANE_ESE
    \brief Vane : East-SouthEast Direction
    
 */
/*! \def SENS_AGR_VANE_SE
    \brief Vane : SouthEast Direction
    
 */
/*! \def SENS_AGR_VANE_SSE
    \brief Vane : South-SouthEast Direction
    
 */
/*! \def SENS_AGR_VANE_S
    \brief Vane : South Direction
    
 */
/*! \def SENS_AGR_VANE_SSW
    \brief Vane : South-SouthWest Direction
    
 */
/*! \def SENS_AGR_VANE_SW
    \brief Vane : SouthWest Direction
    
 */
/*! \def SENS_AGR_VANE_WSW
    \brief Vane : West-SouthWest Direction
    
 */
/*! \def SENS_AGR_VANE_W
    \brief Vane : West Direction
    
 */
/*! \def SENS_AGR_VANE_WNW
    \brief Vane : West-Northwest Direction
    
 */
/*! \def SENS_AGR_VANE_NW
    \brief Vane : NorthWest Direction
    
 */
/*! \def SENS_AGR_VANE_NNW
    \brief Vane : North-NorthWest Direction
    
 */
#define SENS_AGR_VANE_N		0
#define SENS_AGR_VANE_NNE	1
#define SENS_AGR_VANE_NE	2
#define SENS_AGR_VANE_ENE	3
#define SENS_AGR_VANE_E		4
#define SENS_AGR_VANE_ESE	5
#define SENS_AGR_VANE_SE	6
#define SENS_AGR_VANE_SSE	7
#define SENS_AGR_VANE_S		8
#define SENS_AGR_VANE_SSW	9
#define SENS_AGR_VANE_SW	10
#define SENS_AGR_VANE_WSW	11
#define SENS_AGR_VANE_W		12
#define SENS_AGR_VANE_WNW	13
#define SENS_AGR_VANE_NW	14
#define SENS_AGR_VANE_NNW	15


/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspSensorAgrV20 Class
/*!
	WaspSensorAgrV20 Class defines all the variables and functions used for managing the Agriculture Sensor Board
 */
class WaspSensorAgr_v20
{
	private:
	
	//! It reads from the dendrometer
  	/*!
	\return the value returned by the sensor
	 */
	float readDendrometer(void);

	//! It reads from the PT1000
  	/*!
	\return the value returned by the sensor
	 */
	float readPT1000(void);

	//! It reads from the radiation sensors
  	/*!
	\return the value returned by the sensor
	 */
	float readRadiation(void);
			
	//! It reads from the Watermark
  	/*!
	\param uint8_t sens : the Watermark on use
	\return the value returned by the sensor
	 */
	float readWatermark(uint8_t sens);
			
	//! It reads from the sensirion
  	/*!
	\param uint8_t parameter : TEMPERATURE or HUMIDITY
	\return the value returned by the sensor
	 */
	float readSensirion(uint8_t parameter);
	
	//! It reads from the pluviometer
  	/*!
	\return the value returned by the sensor
	 */
	uint16_t readPluviometer(void);

	//! It reads from the anemometer
  	/*!
	\return the value returned by the sensor
	 */
	float readAnemometer(void);

	
	//! It converts data
  	/*!
	\param byte data_input : the data to convert
	\param uint8_t type : temperature(1) or dendrometer(0)
	\return the value converted
	 */
	float conversion(byte data_input[3], uint8_t type);
	
	//! It converts pressure
  	/*!
	\param int readValue : the data to convert
	\return the value converted
	 */	
	float pressureConversion(int readValue);
	
	//! It converts leaf wetness
  	/*!
	\param int readValue : the data to convert
	\return the value converted
	 */	
	float lwsConversion(int readValue);
	
	//! It gets the direction of the wind
  	/*!
	\param float vane : the voltage got from the vane
	\return nothing
	 */	
	void getVaneDirection(float vane);
	
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
	
	//! It converts the humidity returned by sencera
  	/*!
	\param int readValue : value returned by sencera
	\return the converted value
	 */
	float senceraConversion(int readValue);
	
	//! It converts the temperature returned by mcp
  	/*!
	\param int readValue : value returned by mcp
	\return the converted value
	 */
 	float mcpConversion(int readValue);

	public:
	
	//! Variable : specifies the wind direction
  	/*!
   	*/
	uint8_t vaneDirection;
	
	//! class constructor
  	/*!
	It initializes the different digital pins
	\param void
	\return void
	 */
	WaspSensorAgr_v20();
	
	//! Turns ON the board
  	/*!
	\param void
	\return void
	 */
	void ON(void);
	
	//! Turns OFF the board
  	/*!
	\param void
	\return void
	 */
	void OFF(void);
	
	//! It sets board power mode, setting ON/OFF 3v3 and 5V switches
  	/*!
	\param uint8_t mode : SENS_ON or SENS_OFF
	\return error
	 */
	int8_t setBoardMode(uint8_t mode);
	
	//! It sets ON/OFF the different sensor switches
  	/*!
	\param uint8_t mode : SENS_ON or SENS_OFF
	\param uint16_t sensor : the sensor to set ON/OFF
	\return error
	 */
	int8_t setSensorMode(uint8_t mode, uint16_t sensor);
	
	//! It reads the value measured by the sensor
  	/*!
	\param uint16_t sensor : the sensor to read the value from
	\return the value measured by the sensor (range [0-3.3] Volts)
	 */
	float readValue(uint16_t sensor);
	
	//! It reads the value measured by the sensor
  	/*!
	\param uint16_t sensor : the sensor to read the value from
	\param uint8_t type : the type to read
	\return the value measured by the sensor (range [0-3.3] Volts)
	 */
	float readValue(uint16_t sensor, uint8_t type);
		
	
	//! It sleeps Waspmote enabling the switches required for the agriculture board
  	/*!
	\param const char* time2wake : string that indicates the time to wake up. It looks like "dd:hh:mm:ss"
	\param uint8_t offset : RTC_OFFSET or RTC_ABSOLUTE
	\param uint8_t mode : RTC_ALM1_MODE1, RTC_ALM1_MODE2, RTC_ALM1_MODE3, RTC_ALM1_MODE4 or RTC_ALM1_MODE5
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF or SOCKET0_OFF
	\return void
	 */
	void sleepAgr(const char* time2wake, uint8_t offset, uint8_t mode, uint8_t option);

	//! It sleeps Waspmote enabling the switches required for the Agriculture Board
  	/*!
	\param const char* time2wake : string that indicates the time to wake up. It looks like "dd:hh:mm:ss"
	\param uint8_t offset : RTC_OFFSET or RTC_ABSOLUTE
	\param uint8_t mode : RTC_ALM1_MODE1, RTC_ALM1_MODE2, RTC_ALM1_MODE3, RTC_ALM1_MODE4 or RTC_ALM1_MODE5
	\param uint8_t option : ALL_ON, ALL_OFF, SENS_OFF or SOCKET0_OFF
	\param uint8_t agr_interrupt : specifies the sensor we are enabling before going sleep (Anemometer and Pluviometer)
	\return void
	 */
	void sleepAgr(const char* time2wake, uint8_t offset, uint8_t mode, uint8_t option, uint8_t agr_interrupt);

	//! It enables the pluviometer interruption
    	/*!
	\param void
	\return void
	 */
	void attachPluvioInt(void);
	
	//! It disables the pluviometer interruption
  	/*!
	\param void
	\return void
	 */
	void detachPluvioInt(void);
	
	
	//! It reads the DS1820 temperature sensor
  	/*!
	\param void
	\return void
	 */
	float readTempDS1820();
	
	
};

extern WaspSensorAgr_v20 SensorAgrv20;

#endif

