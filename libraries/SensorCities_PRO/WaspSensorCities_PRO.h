/*! \file WaspSensorCitiesPRO.h
    \brief Library for managing the Smart Cities PRO Sensor Board

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

    Version:		3.5
    Design:			David Gascón
    Implementation:	Alejandro Gállego, Ahmad Saad

 */


 /*! \def WaspSensorCitiesPRO_h
    \brief The library flag

  */
#ifndef WaspSensorCitiesPRO_h
#define WaspSensorCitiesPRO_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>
#include <WaspConstants.h>
#include <BME280.h>
#include <UltrasoundSensor.h>
#include <TSL2561.h>

#ifndef WaspSensorGas_Pro_h
#include <WaspSensorGas_Pro.h>
#endif

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
// I2C pins (sockets prepared for I2C connection)
#define SCP_I2C_MAIN_EN		ANA0 		// GP_I2C_MAIN_EN
#define SCP_I2C_SOCKET_1_C	DIGITAL4	// GP_I2C_SOCKET_1_C
#define SCP_I2C_SOCKET_3_F	DIGITAL8	// GP_I2C_SOCKET_3_F
#define SCP_I2C_SOCKET_5_B	ANA3		// GP_I2C_SOCKET_5_B

// PWR pins (sockets prepared for I2C connection)
#define SCP_PWR_SOCKET_1_C	DIGITAL3	// GP_PWR_SOCKET_1_C
#define SCP_PWR_SOCKET_3_F	DIGITAL7	// GP_PWR_SOCKET_3_F
#define SCP_PWR_SOCKET_5_B	ANA4		// GP_PWR_SOCKET_5_B

// PWR pins (to give power supply to socket)
#define SCP_PWR_3V3_SOCKET_1_C	ANA2
#define SCP_PWR_3V3_SOCKET_2_E	DIGITAL5
#define SCP_PWR_3V3_SOCKET_3_F	ANA5
#define SCP_PWR_3V3_SOCKET_4_A	ANA6
#define SCP_PWR_3V3_SOCKET_5_B	ANA1



//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_CITIES_PRO		0

#define PRINT_CITIES_PRO(str)			USB.print(F("[CITIES_PRO] ")); USB.print(str);
#define PRINT_CITIES_PRO_VAL(val)		USB.print(float(val));
#define PRINTLN_CITIES_PRO(str)			USB.print(F("[CITIES_PRO] ")); USB.println(str);
#define PRINTLN_CITIES_PRO_VAL(val)		USB.println(float(val));


extern volatile uint8_t	pwrCitiesPRORegister;
extern volatile uint8_t	pwrGasPRORegister;

/******************************************************************************
 * Class
 ******************************************************************************/

//! WaspSensorCitiesPRO Class
/*!
	WaspSensorCitiesPRO Class defines all the variables and functions used for
	managing the Smart Cities PRO Sensor Board
 */
class WaspSensorCitiesPRO
{

private:

public:

	WaspSensorCitiesPRO();

	void ON(uint8_t socket_sensor);
	void OFF(uint8_t socket_sensor);

};

extern WaspSensorCitiesPRO SensorCitiesPRO;

#endif




/******************************************************************************
 * Class
 ******************************************************************************/
#ifndef NOISESENSOR_H

#define FAST_MODE	0x00
#define SLOW_MODE	0x01

class noiseSensor : public WaspUART
{
	private:
		#define SENSOR_NOISE_UART_SIZE 20
		uint8_t class_buffer[SENSOR_NOISE_UART_SIZE];
		
	public:		

		// Constructor
		noiseSensor();
		// Sound Pressure Level with A-Weighting
		float SPLA;
		// Get a new measure of SPLA
		uint8_t getSPLA();
		// Get a new measure of SPLA with SLOW or FAST configuration
		uint8_t getSPLA(uint8_t);
		// Configure the UART for communicating with the sensor
		void configure();

};

extern noiseSensor noise;

#endif




/******************************************************************************
 * Class
 ******************************************************************************/
#ifndef BME_CITIES_SENSOR_H

class bmeCitiesSensor: WaspSensorCitiesPRO
{
	private:
	public:

		uint8_t _socket;

		// Constructor
		bmeCitiesSensor(uint8_t socket);

		void ON();
		void OFF();

		float getTemperature();
		float getHumidity();
		float getPressure();
};


#endif



/******************************************************************************
 * Class
 ******************************************************************************/
#ifndef ULTRASOUND_CITIES_SENSOR_H

class ultrasoundCitiesSensor: WaspSensorCitiesPRO
{
	private:
	public:

		uint8_t _socket;

		// Constructor
		ultrasoundCitiesSensor(uint8_t socket);

		void ON();
		void OFF();
		uint16_t getDistance();
};


#endif



/******************************************************************************
 * Class
 ******************************************************************************/
#ifndef LUXES_CITIES_SENSOR_H

class luxesCitiesSensor: WaspSensorCitiesPRO
{
	private:
	public:

		uint8_t _socket;

		// Constructor
		luxesCitiesSensor(uint8_t socket);

		void ON();
		void OFF();
		uint32_t getLuminosity();
    uint32_t getLuminosity(bool gain);
		uint32_t getLuminosity(bool gain, uint8_t res);
};


#endif
