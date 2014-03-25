/*! \file WaspSensorGas_v20.h
    \brief Library for managing the Gas Sensor Board
    
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

    Design:		David Gascón

    Implementation:	Alberto Bielsa, Manuel Calahorra

*/

 /*! \def WaspSensorGas_v20_h
    \brief The library flag
    
  */
#ifndef WaspSensorGas_v20_h
#define WaspSensorGas_v20_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include <inttypes.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/
 
/*! \def SENS_TEMPERATURE
    \brief Sensor types. Temperature sensor in this case    
 */
/*! \def SENS_HUMIDITY
    \brief Sensor types. Humidity sensor in this case    
 */
/*! \def SENS_PRESSURE
    \brief Sensor types. Pressure sensor in this case    
 */
/*! \def SENS_CO2
    \brief Sensor types. CO2 sensor in this case    
 */
/*! \def SENS_O2
    \brief Sensor types. O2 sensor in this case    
 */
/*! \def SENS_SOCKET2A
    \brief Sensor types. Socket2A sensor in this case (many sensors can be connected
		   to this socket)    
 */
/*! \def SENS_SOCKET2B
    \brief Sensor types. Socket2A sensor in this case (NO2, O3 or VOC sensors can
		   be connected to this socket)    
 */
/*! \def SENS_SOCKET3A
    \brief Sensor types. Socket3A sensor in this case (many sensors can be connected
		   to this socket)    
 */
/*! \def SENS_SOCKET3B
    \brief Sensor types. Socket3B sensor in this case (many sensors can be connected
		   to this socket)    
 */
/*! \def SENS_SOCKET3C
    \brief Sensor types. Socket3C sensor in this case (many sensors can be connected
		   to this socket)    
 */
/*! \def SENS_SOCKET4A
    \brief Sensor types. Socket4A sensor in this case (many sensors can be connected
		   to this socket)    
 */
/*! \def SENS_SOCKET4C
    \brief Sensor types. Socket4C sensor in this case (many sensors can be connected
		   to this socket)
    
 */
#define	SENS_TEMPERATURE	0
#define	SENS_HUMIDITY		1
#define	SENS_PRESSURE		2
#define	SENS_CO2			4
#define	SENS_O2				8
#define	SENS_SOCKET2A		16
#define	SENS_SOCKET2B		32
#define	SENS_SOCKET3A		64
#define	SENS_SOCKET3CO		128
#define	SENS_SOCKET3NH3		256
#define	SENS_SOCKET3B		4096
#define	SENS_SOCKET4A		512
#define	SENS_SOCKET4CO		1024
#define	SENS_SOCKET4NH3		2048


/*! \def NO2_ON
    \brief NO2 sensor powered
    
 */
/*! \def NO2_OFF
    \brief NO2 sensor unpowered
    
 */
#define NO2_ON			1
#define NO2_OFF			0


/*! \def SENS_AMPLI1
    \brief Sensor amplifiers and resistors. Amplifier1 in this case
    
 */
/*! \def SENS_AMPLI2
    \brief Sensor amplifiers and resistors. Amplifier2 in this case
    
 */
/*! \def SENS_AMPLI3
    \brief Sensor amplifiers and resistors. Amplifier3 in this case
    
 */
/*! \def SENS_AMPLI4
    \brief Sensor amplifiers and resistors. Amplifier4 in this case
    
 */
/*! \def SENS_R1
    \brief Sensor amplifiers and resistors. Resistor1 in this case
    
 */
/*! \def SENS_R2
    \brief Sensor amplifiers and resistors. Resistor2 in this case
    
 */
/*! \def SENS_R3
    \brief Sensor amplifiers and resistors. Resistor3 in this case
    
 */
#define	SENS_AMPLI1	0
#define	SENS_AMPLI2	1
#define	SENS_AMPLI3	2
#define	SENS_AMPLI4	4
#define	SENS_R1		8
#define	SENS_R2		16
#define	SENS_R3		32



/******************************************************************************
 * Class
 ******************************************************************************/
 
//! WaspSensorGasV20 Class
/*!
	WaspSensorGasV20 Class defines all the variables and functions used for managing
	the Gas Sensor Board
 */
class WaspSensorGas_v20
{
	private:

	//! It denotes whether the NO2 sensor is ON or not
 	uint8_t NO2_state;
    	
	//! It configures the sensor resistors
  	/*!
	\param uint8_t ampli : the amplifier to configure
	\param float resistor : the value to set the resistor to
	\return void
	 */
	void configureResistor(uint8_t ampli, float resistor);
	
	//! It sets the resistor value
  	/*!
	\param uint8_t address : the resistor address
	\param float value : the value to set the resistor to
	\return void
	 */
	void setResistor(uint8_t address, float value);
	
	//! It configures the corresponding amplifier	
  	/*!
	\param uint8_t ampli : the amplifier to set
	\param uint8_t gain : the gain to set
	\return void
	 */
	void configureAmplifier(uint8_t ampli, uint8_t gain);
	
	//! It sets the value of the gain
  	/*!
	\param uint8_t address : the amplifier address
	\param uint8_t value : the value to set the amplifier to
	\return void
	 */
	void setAmplifier(uint8_t address, uint8_t value);
	
	//! It sends a pulse to read the sensor value
  	/*!
	\param uint16_t sensor : the sensor to read the value from
	\return the value returned by the sensor
	 */
	uint16_t pulse(uint16_t sensor);
	
	//! It converts pressure
  	/*!
	\param int readValue : the data to convert
	\return the value converted
	 */	
	float pressureConversion(int readValue);
	
	//! It converts the temperature returned by mcp
  	/*!
	\param int readValue : value returned by mcp
	\return the converted value
	 */
 	float mcpConversion(int readValue);
	
	//! It converts the humidity returned by sencera
  	/*!
	\param int readValue : value returned by sencera
	\return the converted value
	 */
	float senceraConversion(int readValue);
	
	
	public:
	
	//! class constructor
  	/*!
		It initializes the different digital pins
	\param void
	\return void
	 */
	WaspSensorGas_v20();
	
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
	
	//! It configures the amplifier gain in the different sensors
  	/*!
	\param uint16_t sensor : the sensor to configure 
	\param uint8_t gain : the gain to set (range [1-101])
	\return error
	 */
	int8_t configureSensor(uint16_t sensor, uint8_t gain);
	
	//! It configures the amplifier gain and load resistor in the different sensors
  	/*!
	\param uint16_t sensor : the sensor to configure
	\param uint8_t gain : the gain to set (range [1-101])
	\param float resistor : the load resistor to set (range [0-100] in KOhms)
	\return error
	 */
	int8_t configureSensor(uint16_t sensor, uint8_t gain, float resistor);
	
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
	
	//! It calculates the sensor resistance in function of the voltage read, the
	//! gain and load resistance set and the socket selected
  	/*!
	\param uint16_t sensor : the sensor that has been read
	\param float value : the sensor to read the value from
	\param float load : the sensor to read the value from
	\param uint8_t gain : the sensor to read the value from
	\return the resistance of the sensor as a float
	 */
	float calculateResistance(uint16_t sensor, float value, uint8_t gain, float load);
	
	//! It calculates the gas concentration from the sensor resistance 
	//! using the calibration parameters of the sensor
  	/*!
	\param float calibrationConcentration : the gas concentrations in calibration
	\param float calibrationOutput : the sensor output in each calibration point
	\param float inputValue : the resistance of the sensor measured
	\return the gas concentration
	 */
	float calculateConcentration(	int calibrationConcentration[3],
									float calibrationOutput[3],
									float inputValue);
};

extern WaspSensorGas_v20 SensorGasv20;

#endif

