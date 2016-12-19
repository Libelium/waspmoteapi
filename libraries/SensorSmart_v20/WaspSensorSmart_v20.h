/*! \file WaspSensorSmart_v20.h
    \brief Library for managing the Smart Metering Sensor Board
    
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
    Implementation:	Alberto Bielsa, Manuel Calahorra

 */


 /*! \def WaspSensorSmart_v20_h
    \brief The library flag
    
  */
#ifndef WaspSensorSmart_v20_h
#define WaspSensorSmart_v20_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

/*! \def SENS_SMART_CURRENT
    \brief Sensor types. Current sensor
    
 */
/*! \def SENS_SMART_LCELLS
    \brief Sensor types. Load Cells sensor
    
 */
/*! \def SENS_SMART_LDR
    \brief Sensor types. LDR sensor
    
 */
/*! \def SENS_SMART_TEMPERATURE
    \brief Sensor types. Temperature sensor
    
 */
/*! \def SENS_SMART_HUMIDITY
    \brief Sensor types. Humidity sensor
    
 */
/*! \def SENS_SMART_US_3V3
    \brief Sensor types. 3,3V Ultrasound Sensor
    
 */
/*! \def SENS_SMART_FLOW_3V3
    \brief Sensor types. 3,3V Flow sensor
    
 */
/*! \def SENS_SMART_US_5V
    \brief Sensor types. 5V Ultrasound Sensor
    
 */
/*! \def SENS_SMART_FLOW_5V
    \brief Sensor types. 5V Flow sensor
    
 */
/*! \def SENS_SMART_TEMP_DS18B20
    \brief Sensor types. DS18B20 temperature sensor
    
 */
#define	SENS_SMART_LDR			2
#define	SENS_SMART_DFS_3V3		4
#define	SENS_SMART_DFS_5V		8
#define	SENS_SMART_LCELLS_5V	16
#define	SENS_SMART_CURRENT		32
#define	SENS_SMART_LCELLS_10V	64
#define	SENS_SMART_TEMPERATURE	256
#define	SENS_SMART_HUMIDITY		512
#define	SENS_SMART_US_3V3		2048
#define	SENS_SMART_FLOW_3V3		4096
#define	SENS_SMART_US_5V		8192
#define	SENS_SMART_FLOW_5V		16384
#define	SENS_SMART_TEMP_DS18B20	32768

/*! \def SENS_US_WRA1
    \brief Specifies the WRA1 as ultrasound sensor in use
    
 */
/*! \def SENS_US_EZ0
    \brief Specifies the EZ0 as ultrasound sensor in use

 */
#define SENS_US_WRA1	1
#define SENS_US_EZ0		2


/*! \def SENS_FLOW_FS100
    \brief Specifies the FS100 as flow sensor in use
    
 */
/*! \def SENS_FLOW_FS200
    \brief Specifies the FS200 as flow sensor in use
    
 */
/*! \def SENS_FLOW_FS400
    \brief Specifies the FS400 as flow sensor in use
    
 */
/*! \def SENS_FLOW_YFS401
    \brief Specifies the YFS401 as flow sensor in use
    
 */
/*! \def SENS_FLOW_FS300
    \brief Specifies the FS300 as flow sensor in use
    
 */
/*! \def SENS_FLOW_YFG1
    \brief Specifies the YFG1 as flow sensor in use
    
 */
#define SENS_FLOW_FS100		1
#define SENS_FLOW_FS200		2
#define SENS_FLOW_FS400		4
#define SENS_FLOW_YFS401	8
#define SENS_FLOW_FS300		16
#define SENS_FLOW_YFG1		32


/******************************************************************************
 * Class
 ******************************************************************************/
 
 //! WaspSensorSmart_v20 Class
/*!
	WaspSensorSmart_v20 Class defines all the variables and functions used for
	managing the Smart Metering Sensor Board
 */
class WaspSensorSmart_v20
{
	private:
	
	//! It reads the DS1820 temperature sensor
  	/*!
	\param void
	\return void
	 */
	float readTempDS1820();
 
	//! It converts the analog read value into volts
  	/*!
	\param int readValue : the data to convert
	\return the value converted
	 */	
	float ldrConversion(int readValue);

	//! It reads the corresponding socket and converts the analog read value
	//! into volts
  	/*!
	\param int socket : the socket to read
	\return the value read and converted
	 */	
	float ldReading(uint16_t socket);

	//! It converts the analog read value into volts
  	/*!
	\param int readValue : the data to convert
	\return the value converted
	 */	
	float lcellConversion(int readValue);

	//! It converts the analog read value into current (ampers)
  	/*!
	\param int readValue : the data to convert
	\return the value converted
	 */	
	float currentConversion(int readValue);

	//! It converts the analog read value into temperature (ºC)
  	/*!
	\param int readValue : the data to convert
	\return the value converted
	 */	
	float temperatureConversion(int readValue);

	//! It converts the analog read value into humidity (%RH)
  	/*!
	\param int readValue : the data to convert
	\return the value converted
	 */	
	float humidityConversion(int readValue);

	//! It reads the corresponding socket and returns the distance value (cm)
  	/*!
	\param uint16_t socket : the socket to be read
	\param uint8_t model : the model of ultrasound sensor
	\return the value converted
	 */	
	float ultrasoundConversion(uint16_t socket, uint8_t model);

	//! It reads the corresponding socket and returns the flow
	//! value (litres / min)
  	/*!
	\param uint16_t socket : the socket to be read
	\param uint8_t model : the model of flow sensor
	\return the value converted
	 */	
	float flowReading(int socket, uint8_t model);

	public:

	//! class constructor
  	/*!
		It initializes the different digital pins
	\param void
	\return void
	 */
	WaspSensorSmart_v20();

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

	//! It sets ON/OFF the 3V3/5V switches
  	/*!
	\param uint8_t mode : SENS_ON or SENS_OFF
	\return int8_8 : error
	 */
	int8_t setBoardMode(uint8_t mode);
	
	
	//! It sets ON/OFF the different sensor switches
  	/*!
	\param uint8_t mode : SENS_ON or SENS_OFF
	\param uint16_t sensor : the sensor to set ON/OFF
	\return int8_t error
	 */
	int8_t setSensorMode(uint8_t mode, uint16_t sensor);
	
	//! It reads the value measured by the sensor
  	/*!
	\param uint16_t sensor : 	specifies the socket to set the threshold
								to ('SENS_SMART_X')
	\return the value read 
	 */
	float readValue(uint16_t sensor);

	//! It reads the value measured by the sensor
  	/*!
	\param uint16_t sensor 	: 	specifies the socket to set the threshold
								to ('SENS_SMART_X')
	\param uint8_t type 	: 	specifies the model of the sensor to be read for
								ultrasound or flow sensors
	\return the value read 
	 */
	float readValue(uint16_t sensor, uint8_t type);
	
};

extern WaspSensorSmart_v20 SensorSmartv20;

#endif

