/*! \file WaspSensorCitiesPRO.h
    \brief Library for managing the Smart Cities PRO Sensor Board
    
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
  
    Version:		3.1
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


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
#define SCP_PWR_SOCKET_1	ANA2
#define SCP_PWR_SOCKET_2	DIGITAL5
#define SCP_PWR_SOCKET_3	ANA5
#define SCP_PWR_SOCKET_4	ANA6
#define SCP_PWR_SOCKET_5	ANA1
#define SCP_I2C_MAIN_EN		ANA0


//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages 
 */
#define DEBUG_CITIES_PRO		1

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
	WaspSensorCitiesPRO Class defines all the variables and functions used for managing the Smart Cities PRO Sensor Board
 */
class WaspSensorCitiesPRO
{
	private:

	public:

	//! class constructor
  	/*!
		It initializes the different digital pins
	\param void
	\return void
	 */
	WaspSensorCitiesPRO();
	
	
	//! Turns ON the sensor/socket
  	/*!
	\param uint8_t socket_sensor:	SENS_CITIES_PRO_NOISE
									SENS_CITIES_PRO_POLI1
									SENS_CITIES_PRO_GAS1
									SENS_CITIES_PRO_DUST
									SENS_CITIES_PRO_POLI2
									SENS_CITIES_PRO_GAS2
	\return void
	 */
	void ON(uint8_t socket_sensor);
	
	
	//! Turns OFF the sensor/socket
  	/*!
	\param uint8_t socket_sensor:	SENS_CITIES_PRO_NOISE
									SENS_CITIES_PRO_POLI1
									SENS_CITIES_PRO_GAS1
									SENS_CITIES_PRO_DUST
									SENS_CITIES_PRO_POLI2
									SENS_CITIES_PRO_GAS2
	\return void
	 */
	void OFF(uint8_t socket_sensor);	

};

extern WaspSensorCitiesPRO SensorCitiesPRO;

#endif


#ifndef NOISESENSOR_H

#define FAST_MODE	0x00
#define SLOW_MODE	0x01

class noiseSensor : WaspUART
{
	
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
		
	private:
	
};

extern noiseSensor noise;

#endif

