/*! \file WaspSensorEvent_v30.h
    \brief Library for managing the Events Sensor Board

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

    Version:		3.4
    Design:			David Gascón
    Implementation:	Carlos Bello

*/

 /*! \def WaspSensorGas_h
    \brief The library flag

  */
#ifndef WaspSensorEvent_v30_h
#define WaspSensorEvent_v30_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>
#include "UltrasoundSensor.h"
#include <TSL2561.h>
//**********************************************************************
// DEBUG MODES
//**********************************************************************

/*! Possible values:
 * 	0: No debug mode enabled
 * 	1: debug 1
 * 	2: debug 2
 */
#define DEBUG_EVN 0

// define print message
#define PRINT_EVENT(str)	USB.print(F("[EVENT] ")); USB.print(str);


//**********************************************************************
// DEFINES INPUTS INPUTS
//**********************************************************************
#define FLOW_B				DIGITAL5
#define I2C_PIN_OE 			ANA5
#define PULS_A		 		ANA6
#define PULS_C				ANA4
#define PULS_D				ANA3
#define PULS_E				ANA2
#define PULS_F				ANA0
// Event Sensor Board
#define	SENS_INT_PIN_MON 	DIGITAL2  	// PA2
#define	SENS_INT_CLK_REG	DIGITAL7	// PC4
#define	SENS_INT_DO			DIGITAL1	// PE3
#define	SENS_INT_ENABLE		DIGITAL8	// PC5
#define	SENS_INT_CLK_INH	DIGITAL3	// PA4
#define SENS_INT_FLOW_EN	DIGITAL4
//**********************************************************************
// DEFINES FLOW SENSORS
//**********************************************************************
#define	SENS_FLOW_FS100		1
#define	SENS_FLOW_FS200		2
#define	SENS_FLOW_FS400		3
#define SENS_FLOW_YFS401	4
#define SENS_FLOW_FS300		5
#define SENS_FLOW_YFG1		6


//**************************************************************************************************
//  Smart Agriculture Board Class
//**************************************************************************************************
class WaspSensorEvent_v30
{
	public:

		WaspSensorEvent_v30();
		void ON(void);
		void OFF(void);
		void attachInt();
		void detachInt();
		uint8_t	readInput(uint8_t);
		void loadInt();
		float getTemperature();
		float getHumidity();
		float getPressure();
		uint16_t getDistance();
    uint32_t getLuxes();
    uint32_t getLuxes(bool gain);
		uint32_t getLuxes(bool gain, uint8_t res);
		friend class relayClass;
		friend class flowClass;
		friend class hallSensorClass;
		friend class pirSensorClass;
		friend class liquidLevelClass;
		friend class liquidPresenceClass;
		bool _intEnabled;

		// Interruption Inputs Vars
		bool input1Flag;
		bool input2Flag;
		bool input3Flag;
		bool input4Flag;
		bool input6Flag;
		bool flowFlag;
};
extern WaspSensorEvent_v30 Events;
#endif

//**************************************************************************************************
// Hall Effect class
//**************************************************************************************************
#ifndef hallSensorClass_h
#define hallSensorClass_h

class hallSensorClass : public WaspSensorEvent_v30
{
	public:
		hallSensorClass(uint8_t);
		uint8_t read();
		uint8_t readHallSensor();
		bool getInt();
	private:
		uint8_t hallEffectSocket;
};
#endif

//**************************************************************************************************
// PIR Sensor class
//**************************************************************************************************
#ifndef pirSensorClass_h
#define pirSensorClass_h

class pirSensorClass : public WaspSensorEvent_v30
{
	public:
		pirSensorClass(uint8_t);
		uint8_t read();
		uint8_t readPirSensor();
		bool getInt();
	private:
		uint8_t pirSensorSocket;
};
#endif

//**************************************************************************************************
// Liquid Level Class
//**************************************************************************************************
#ifndef liquidLevelClass_h
#define liquidLevelClass_h

class liquidLevelClass : public WaspSensorEvent_v30
{
	public:
		liquidLevelClass(uint8_t);
		uint8_t read();
		uint8_t readliquidLevel();
		bool getInt();
	private:
		uint8_t liquidLevelSocket;
};
#endif

//**************************************************************************************************
// Liquid Presence Sensor Class
//**************************************************************************************************
#ifndef liquidPresenceClass_h
#define liquidPresenceClass_h

class liquidPresenceClass : public WaspSensorEvent_v30
{
	public:
		liquidPresenceClass(uint8_t);
		uint8_t read();
		uint8_t readliquidPresence();
		float readVoltage();
		float readResistance(float volts);
		bool getInt();
	private:
		uint8_t liquidPresenceSocket;
};
#endif
//**************************************************************************************************
// Relay class
//**************************************************************************************************
#ifndef relayClass_h
#define relayClass_h

class relayClass : public WaspSensorEvent_v30
{
	public:
		relayClass();
		uint8_t read();
		uint8_t readInRel();
		void relayON();
		void relayOFF();
		bool getInt();
};
#endif

//**************************************************************************************************
// flowReadingClass class
//**************************************************************************************************
#ifndef flowClass_h
#define flowClass_h

class flowClass : public WaspSensorEvent_v30
{
	public:
		flowClass(uint8_t);
		float flowReading();
		float read();
		bool getInt();
		void enableFlowInt();
		void disableFlowInt();
	private:
		uint8_t _model;
};
#endif
