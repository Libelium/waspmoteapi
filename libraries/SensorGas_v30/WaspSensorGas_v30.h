/*! \file WaspSensorGas_v30.h
 *  \brief Library for managing the Gas Sensor Board v30
 *   
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 * 
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *  Version:			3.0
 *  Design:				David Gascón
 *  Implementation:		Ahmad Saad
*/

 /*! \def WaspSensorGas_h
    \brief The library flag
    
  */
#ifndef WaspSensorGas_v30_h
#define WaspSensorGas_v30_h

//**********************************************************************
// Includes
//********************************************************************** 
#include <inttypes.h>

// TSL2561 Sensor for reading luxes value
#include "TSL2561.h"
// BME280 library for reading temperature, humidity and pressure values
#include "BME280.h"
// Ultrasound library for readign distance
#include "UltrasoundSensor.h"

//**********************************************************************
// DEFINES OF CALIBRATION POINTS
//**********************************************************************
#define POINT_1		0x00
#define POINT_2		0x01
#define POINT_3		0x02
#define POINT_4		0x03
#define POINT_5		0x04
#define POINT_6		0x05
#define POINT_7		0x06
#define POINT_8		0x07
#define POINT_9		0x08
#define POINT_10	0x09

//**********************************************************************
// DEFINES FOR POWER CONTROL DIGITAL PINS
//**********************************************************************
#define SOCKET2_ON_PIN			DIGITAL7
#define SOCKET3_ON_PIN			DIGITAL6
#define SOCKET4_ON_PIN			DIGITAL5
#define SOCKET5_ON_PIN			DIGITAL4
#define SOCKET6_ON_PIN			DIGITAL3
#define SOCKET7_ON_PIN			DIGITAL2
#define SOCKET4_CONTROL_PIN		DIGITAL8

//**********************************************************************
// DEFINES FOR MULTIPLEXER CONTROL
//**********************************************************************
#define A2		19		// ANALOG6
#define A1		17		// ANALOG4
#define A0		15		// ANALOG2
#define EN	DIGITAL1	// ENABLE MULTIPLEXOR

//**********************************************************************
// DEFINES FOR DIGIPOT ADDRESSES
//**********************************************************************
#define GAIN_DIGIPOT_ADDRESS		I2C_ADDRESS_GASES_DIGIPOT3
#define SOCKET3_DIGIPOT_ADDRESS		I2C_ADDRESS_GASES_DIGIPOT3
#define SOCKET4_DIGIPOT_ADDRESS		I2C_ADDRESS_GASES_DIGIPOT1
#define SOCKET5_DIGIPOT_ADDRESS		I2C_ADDRESS_GASES_DIGIPOT2
#define SOCKET6_DIGIPOT_ADDRESS		I2C_ADDRESS_GASES_DIGIPOT1
#define SOCKET7_DIGIPOT_ADDRESS		I2C_ADDRESS_GASES_DIGIPOT2

// ENABLE I2C ISOLATOR
#define I2C_PIN_OE		14

//**********************************************************************
// SENSOR STATE
//**********************************************************************
#define ON_STATE	0x01
#define OFF_STATE	0x00
#define MAX_POINTS	10		// MAX calibration points
#define ANALOG_REFERENCE 2.56
#define SOCKET7_SUPPLY	5.0
#define SOCKET6_SUPPLY	5.0
#define SOCKET5_SUPPLY	2.5
#define SOCKET3_SUPPLY	1.8
#define SOCKET4_SUPPLY	5.0

#define SOCKET3_POTENTIOMETER	0x00
#define SOCKET4_POTENTIOMETER	0x00
#define SOCKET5_POTENTIOMETER	0x10
#define SOCKET6_POTENTIOMETER	0x10
#define SOCKET7_POTENTIOMETER	0x00


//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages 
 */
#define DEBUG_GASES		0
#define PRINT_GASES(str)		USB.print(F("[GASES] ")); USB.print(str);
#define PRINT_GASES_VAL(val)	USB.print(float(val));
#define PRINTLN_GASES(str)		USB.print(F("[GASES] ")); USB.println(str);
#define PRINTLN_GASES_VAL(val)	USB.println(float(val));

class GasSensorClass 
{
	//******************************************************************		
	// Public methods of the class
	//******************************************************************
	public: 
		
		// Class constructor
		GasSensorClass();
		//Power Control
		void ON();
		void OFF();
		
		// Atributes of the class
		int state;
		float gain;
		float loadResistor;
		float Ro;
		uint8_t socket;
		
		// Public methos of the class
		float readVoltage();
		float getPPM();
		float getResistance();
		
		float getTemperature();
		float getHumidity();
		float getPressure();
		float getLuxes(uint8_t);
		float getDistance();

		float readConcentration(float);
		float getConcentration(float input);
		
		int setCalibrationPoints();
		int setCalibrationPoints(float calValues[], float calConcentrations[], uint8_t numPoints_);
		int saveCalibrationPoints(float calValues[], float calConcentrations[], uint8_t numPoints_);

		// Arrays for point to point calibration
		float values[MAX_POINTS]; 
		float concentrations[MAX_POINTS];
		uint8_t numPoints;
		
	//******************************************************************
	// Protected methods of the class
	//******************************************************************
	protected: 

		// Configure the gain of the amplifier stage
		void setAmplifier(uint8_t address, float value);
		// Configure the load resistance
		void setResistor(uint8_t address, float value, int pot);

	//******************************************************************
	// Private methods of the class
	//******************************************************************

	private:

		// Configures the ANALOG MULTIPLEXER for each socket
		void setMUX();
};

//**********************************************************************
// O2Sensor Class derives directly from the GasSensor Class
// In the SOCKET1, only this sensor can be connected
//**********************************************************************
class O2SensorClass : public GasSensorClass 
{
	public:

		// Class constructors
		O2SensorClass();
		O2SensorClass(uint8_t);
		O2SensorClass(uint8_t, float);
		
		//Power Control
		void ON();
		void OFF();
		
		// Public methods for getting sensor values
		float readConcentration();
		float readVoltage();
		
		// Configure the calibration line
		void setCalibrationPoints(float calVoltages[], float calConcentrations[]);
		
	private:

		// Configures the ANALOG MULTIPLEXER for SOCKET1
		void setMUX();
		// Private atributes of the class
		float slope;
};

//**********************************************************************
// SOCKET2 Class for managing  the CO2 Sensor
//**********************************************************************
class CO2SensorClass : public GasSensorClass 
{
	public: 

		// Class constrcutors
		CO2SensorClass();
		CO2SensorClass(uint8_t);
		CO2SensorClass(uint8_t, uint8_t);

		//Power Control
		void ON();
		void OFF();
		
		// Public methods for getting sensor values
		float readVoltage();
		float readConcentration();
		int setCalibrationPoints();
		int setCalibrationPoints(float calValues[], float calConcentrations[], uint8_t numPoints_);
		
	private:

		// Configures the ANALOG MULTIPLEXER for SOCKET2
		void setMUX();
};

//**********************************************************************
// SOCKET3 Class for managing NO2 Sensor
// 1v8 heather sensors
//**********************************************************************
class socket3Class : public GasSensorClass 
{
	public: 
		// Class constrcutors
		socket3Class();
		socket3Class(float, float);
		
		//Power Control
		void ON();
		void OFF();
		
		// Public methods for getting sensor values
		float readVoltage();
		float readResistance(float);
		float readConcentration(float);
		
		float readResistance();
		float readConcentration();
		
	private: 
		// Configures the ANALOG MULTIPLEXER for SOCKET3
		void setMUX();
};

class NO2SensorClass : public socket3Class 
{	
	public:
		NO2SensorClass();
		NO2SensorClass(uint8_t);
		NO2SensorClass(uint8_t, float, float);
		
	private:
	
};

//**********************************************************************
// SOCKET4 Class for managing CO Sensor and NH3 Sensor
// Pulse reading sensor
//**********************************************************************
class socket4Class : public GasSensorClass
{	
	public:
		// Class constructors
		socket4Class();
		socket4Class(float, float);
		float readVoltage();
		
		//Power Control
		void ON();
		void OFF();

	protected: 
		// Configures the ANALOG MULTIPLEXER for SOCKET4
		void setMUX();
};

class COSensorClass : public socket4Class 
{
	public:

		// Class constructors
		COSensorClass();
		COSensorClass(uint8_t);
		COSensorClass(uint8_t, float, float);

		// Public methods for getting sensor values
		float readResistance(float);
		float readConcentration(float);
		float readVoltage();
		
		float readResistance();
		float readConcentration();
};

class NH3SensorClass : public socket4Class 
{
	public:
		
		NH3SensorClass();
		NH3SensorClass(uint8_t);
		NH3SensorClass(uint8_t, float, float);
		
		// Public methods for getting sensor values
		float readResistance(float);
		float readConcentration(float);
		float readVoltage();
		
		float readResistance();
		float readConcentration();
};

//**********************************************************************
// SOCKET5 Class for managing VOC and O3 Sensors
// 2v5 heater sensors
//**********************************************************************
class socket5Class : public GasSensorClass 
{
	public: 

		// Class constrcutors
		socket5Class();
		socket5Class(float, float);
		
		//Power Control
		void ON();
		void OFF();
		
		// Public methods for getting sensor values
		float readVoltage();
		float readResistance(float input);
		float readConcentration(float);
		
		float readResistance();
		float readConcentration();

	private: 

		// Configures the ANALOG MULTIPLEXER for SOCKET5
		void setMUX();
	
};

class O3SensorClass : public socket5Class
{
	public:

		O3SensorClass();
		O3SensorClass(uint8_t);
		O3SensorClass(uint8_t, float, float);
};

class VOCSensorClass : public socket5Class
{
	public: 

		VOCSensorClass();
		VOCSensorClass(uint8_t);
		VOCSensorClass(uint8_t, float, float);
	
};

//**********************************************************************
// SOCKET6 Class for managing CH4, API, APII, SV and LPG Sensors
// 5V heating sensors
//**********************************************************************
class sockets5VClass : public GasSensorClass
{
	public:

		// Class constrcutors
		sockets5VClass();
		sockets5VClass(uint8_t);
		sockets5VClass(uint8_t, float , float);
		
		//Power Control
		void ON();
		void OFF();
		
		// Public methods for getting sensor values
		float readVoltage();
		
		float readResistance();
		float readResistance(float);
		
		float readConcentration();
		float readConcentration(float);

	private:

		// Configures the ANALOG MULTIPLEXER for SOCKET6
		void setMUX();
};

class CH4SensorClass : public sockets5VClass
{
	public:

		CH4SensorClass();
		CH4SensorClass(uint8_t);
		CH4SensorClass(uint8_t, float, float);	
};

class APSensorClass : public sockets5VClass
{
	public:

		APSensorClass();
		APSensorClass(uint8_t);
		APSensorClass(uint8_t, float, float);
};

class LPGSensorClass : public sockets5VClass 
{
	public:

		LPGSensorClass();
		LPGSensorClass(uint8_t);
		LPGSensorClass(uint8_t, float, float);
};


class SVSensorClass : public sockets5VClass
{
	public:

		SVSensorClass();
		SVSensorClass(uint8_t);
		SVSensorClass(uint8_t, float, float);
};

extern GasSensorClass Gases;

#endif

