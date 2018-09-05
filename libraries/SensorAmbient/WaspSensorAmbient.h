/*! \file WaspSensorAmbient.h
    \brief Library for environmental Sensors

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

// TSL2561 Sensor for reading luxes value
#include "TSL2561.h"
#include "BME280.h"


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

 /*! Possible values:
  * 	0: No debug mode enabled
  */
#define SENS_AMBIENT_DEBUG 0

#define PRINT_AMBIENT(str)	USB.print(F("[AMBIENT] ")); USB.print(str);


// Pin out definition
#define SENS_AMBIENT_SENSIRION_PWR		15
#define SENS_AMBIENT_SENSIRION_DATA		17
#define SENS_AMBIENT_LDR_OUT			ANALOG6
#define SENS_AMBIENT_SENSIRION_CLK		DIGITAL2
#define SENS_AMBIENT_LDR_PWR			DIGITAL4
#define SENS_AMBIENT_SENSIRION_GND		DIGITAL6
#define SENS_AMBIENT_LDR_GND			DIGITAL8

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

	//! Read temperature sensor
	float getTemperature();

	//! Read humidity sensor
	float getHumidity();

	//! Read LDR sensor (luminosity)
	float getLuminosity();

	//! Read Luxes sensor
	uint32_t getLuxes();
	uint32_t getLuxes(bool gain);
	uint32_t getLuxes(bool gain, uint8_t res);

	//! Read BME Temperature
	float getTemperatureBME();
	//! Read BME Humidity
	float getHumidityBME();
	//! Read BME Pressure
	float getPressureBME();

};

extern WaspSensorAmbient SensorAmbient;

#endif
