/*! \file WaspSensorEvent_v20.h
    \brief Library for managing the Event Sensor Board V2.0
    
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


 /*! \def WaspSensorEvent_v20_h
    \brief The library flag
    
  */
#ifndef WaspSensorEvent_v20_h
#define WaspSensorEvent_v20_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>


/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
 
/*! \def SENS_SOCKET4
    \brief Sensor sockets. Socket number 4 in this case
    
*/
/*! \def SENS_SOCKET3
    \brief Sensor sockets. Socket number 3 in this case
    
 */
/*! \def SENS_SOCKET6
    \brief Sensor sockets. Socket number 6 in this case
    
 */
/*! \def SENS_SOCKET5
    \brief Sensor sockets. Socket number 5 in this case
    
 */
/*! \def SENS_SOCKET1
    \brief Sensor sockets. Socket number 1 in this case
    
 */
/*! \def SENS_SOCKET2
    \brief Sensor sockets. Socket number 2 in this case
    
 */
/*! \def SENS_SOCKET7
    \brief Sensor sockets. Socket number 7 in this case
    
 */
/*! \def SENS_SOCKET8
    \brief Sensor sockets. Socket number 8 in this case
    
 */
#define	SENS_SOCKET4		1
#define	SENS_SOCKET3		2
#define	SENS_SOCKET6		4
#define	SENS_SOCKET5		8
#define	SENS_SOCKET1		16
#define	SENS_SOCKET2		32
#define	SENS_SOCKET7		64
#define	SENS_SOCKET8		128

/*! \def SENS_SENSIRION_DATA
    \brief Sensirion data pin
 */
/*! \def SENS_SENSIRION_DATA
    \brief Sensirion clock pin
 */
#define SENS_SENSIRION_DATA	19
#define SENS_SENSIRION_CLK	20
/*! \def SENS_PREC_HIGH
    \brief Sensirion High Precision
 */
/*! \def SENS_PREC_LOW
    \brief Sensirion Low Precision
 */
#define SENS_PREC_HIGH	1
#define SENS_PREC_LOW	0

/*! \def SENSIRION_TEMP
    \brief Sensirion Temperature Reading
 */
/*! \def SENSIRION_HUM
    \brief Sensirion Humidity Reading
 */
#define SENSIRION_TEMP		0
#define SENSIRION_HUM		1



/*! \def SENS_RESISTIVE
    \brief Sensor sockets. Socket number 6 in this case
    
 */
/*! \def SENS_FS100
    \brief Sensor sockets. Socket number 5 in this case
    
 */
/*! \def SENS_FS200A
    \brief Sensor sockets. Socket number 1 in this case
    
 */
/*! \def SENS_FS400
    \brief Sensor sockets. Socket number 2 in this case
    
 */
/*! \def SENS_TEMPERATURE
    \brief Sensor sockets. Socket number 7 in this case
    
 */
/*! \def SENS_HUMIDITY
    \brief Sensor sockets. Socket number 8 in this case
    
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
#define	SENS_RESISTIVE		0
#define	SENS_FLOW_FS100		1
#define	SENS_FLOW_FS200		2
#define	SENS_FLOW_FS400		3
#define	SENS_TEMPERATURE	4
#define	SENS_HUMIDITY		5
#define SENS_SENSIRION		6
#define SENS_FLOW_YFS401	7
#define SENS_FLOW_FS300		8
#define SENS_FLOW_YFG1		9

/******************************************************************************
 * Class
 ******************************************************************************/
 
 //! WaspSensorEventV20 Class
/*!
	WaspSensorEventV20 Class defines all the variables and functions used for managing the Events Sensor Board V2.0
 */
class WaspSensorEvent_v20
{
	private:
	
	bool _intEnabled;
	

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
    
	//! It sets the Digipot0 threshold
  	/*!
	\param uint8_t address : digipo0 address
	\param uint8_t value : threshold
	\return void
   	*/
	void setDigipot0(uint8_t address, float value);
	
	//! It sets the Digipot1 threshold
  	/*!
	\param uint8_t address : digipo1 address
	\param uint8_t value : threshold
	\return void
	 */
	void setDigipot1(uint8_t address, float value);

	//! It reads the corresponding flow sensor and returns the flow
	//! value (litres / min)
  	/*!
	\param uint8_t model : the model of flow sensor
	\return the value converted
	 */	
	float flowReading(uint8_t model);


	public:

	//! Variable : specifies the sensor that has generated the interruption
  	/*!
	It specifies the socket that has generated the interruption, activating the 
	corresponding flag position using the 'SENS_SOCKETX' definitions 
	(X range [1-8])
	\sa SENS_SOCKET4, SENS_SOCKET3, SENS_SOCKET6, SENS_SOCKET5, SENS_SOCKET1, 
	SENS_SOCKET2, SENS_SOCKET7, SENS_SOCKET8
		 _______________________________________________
		|     |     |     |     |     |     |     |     |
		| S_8 | S_7 | S_2 | S_1 | S_5 | S_6 | S_3 | S_4 |
		|_____|_____|_____|_____|_____|_____|_____|_____|
   	*/
	uint8_t	intFlag;

	//! class constructor
  	/*!
		It initializes the different digital pins
	\param void
	\return void
	 */
	WaspSensorEvent_v20();

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
	\return error
	 */
	int8_t 	setBoardMode(uint8_t mode);
	
	//! It sets threshold configuring digipots
  	/*!
	\param uint8_t sensor : specifies the socket to set the threshold to ('SENS_SOCKETX')
	\param float threshold : the threshold to set (0-3.3V)
	\return error
	 */
	int8_t	setThreshold(uint8_t sensor, float threshold);
	
	//! It reads the value measured by the sensor
  	/*!
	\param uint8_t sensor : specifies the socket ('SENS_SOCKETX')
	\return the value read in volts
	 */
	float 	readValue(uint8_t sensor);

	//! It reads the value measured by the sensor and converts the value
  	/*!
	\param uint8_t sensor : specifies the socket ('SENS_SOCKETX')
	\param uint8_t type : specifies the type of sensor connected
	\return the value read 
	 */
	float	readValue(uint8_t sensor, uint8_t type);

	
	//! It attaches the interruption
  	/*!
	\param void
	\return void
	 */
	void	attachInt(void);
	
	//! It detaches the interruption
  	/*!
	\param void
	\return void
	 */
	void	detachInt(void);
	
	//! It loads the parallel shift register to check the sensor that has generated the interruption
  	/*!
	\param void
	\return the flag to check the sensor that has generated the interruption
	 */
	uint8_t	loadInt(void);
};

extern WaspSensorEvent_v20 SensorEventv20;

#endif

