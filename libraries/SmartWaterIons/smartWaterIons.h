/*
 *  Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
   
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		1.1
 *  Design:			Ahmad Saad
 */

 
#ifndef smartWaterIons_h
#define smartWaterIons_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>
#include <utility/ADC7705.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

#define SOCKETA 		1
#define SOCKETB			2
#define SOCKETC 		3
#define SOCKETD			4
 
#define SOCKET1 		1
#define SOCKET2			2
#define SOCKET3 		3
#define SOCKET4			4
#define MAX_POINTS		20
 
//**************************************************************************************************
//  Smart Water Board Class 
//**************************************************************************************************

/***********************************************************************
 * This class is for managing the Smart Water Ions Board 
 ***********************************************************************/
class WaspSensorSWIons
{
	public:
		//! Class constructor
		WaspSensorSWIons();
		//! Turns ON the board
		void ON(void);
		//! Turns OFF the board
		void OFF(void);
};

// Object for managing the methods of the class
extern WaspSensorSWIons SWIonsBoard;

#endif


//**************************************************************************************************
//  Ion Sensor Class 
//**************************************************************************************************
/***********************************************************************
 * This is the general class witch derive the other classes
 ***********************************************************************/
#ifndef IONSENSORCLASS_H
#define IONSENSORCLASS_H


// From this class will derive the rest of the clasess
class ionSensorClass
{
	public:
	
		// Void class constructor
		ionSensorClass();
		// Class constructor with socket specification 
		ionSensorClass(uint8_t socket);
		// Read ADC function
		float read();
	
		// These are specific functions for ions sensors
		// The ions sensors can be connected in any SOCKET
		void setCalibrationPoints (	const float calVoltages[],
									const float calConcentrations[],
									uint8_t numPoints );
		
		// Returns the ion concentration in ppm's
		float calculateConcentration(float input);
		
		int pointToPointCalibration(float calVoltages[],
									float calConcentrations[],  
									uint8_t numPoints_);
									
		float calculateConcentrationP2P(float input);

		
		// These are specific functions for pH sensor
		// The pH sensor can be connected in any SOCKET
		float pHConversion(float input, float temp);
		void setpHCalibrationPoints(float	_calibration_point_10,
									float	_calibration_point_7,
									float	_calibration_point_4,
									float	_calibration_temperature);
									
		
		
	private: 
	
		// These variables are used to calculate the concentacion in ppm's
		float slope;
		float intersection;
		
		//	Calibration points for pH sensor
		float calibration_point_10;
		float calibration_point_7;
		float calibration_point_4;
		float calibration_temperature;
		
		// Socket used by the class
		uint8_t _mySocket;
		
		// Arrays for point to point calibration
		float voltages[MAX_POINTS]; 
		float concentrations[MAX_POINTS];
		uint8_t numPoints;
};
	
#endif
	


//**************************************************************************************************
// Temperature Sensor class 
//**************************************************************************************************
#ifndef PT1000_h
#define PT1000_h

class pt1000Class
{
	public:

		pt1000Class();
		float read(void);
};

#endif


//**************************************************************************************************
// SOCKET1 Class 
//**************************************************************************************************
#ifndef SOCKET1_H
#define SOCKET1_H

// This class derivate from ionSensorClass
class socket1Class : public ionSensorClass
{
	public:

		socket1Class();
		float read();
};

#endif




//**************************************************************************************************
// SOCKET2 Class 
//**************************************************************************************************
#ifndef SOCKET2_H
#define SOCKET2_H

// This class derivate from ionSensorClass
class socket2Class : public ionSensorClass
{	
	public:

		socket2Class();
		float read();
};

#endif


//**************************************************************************************************
// SOCKET3 Class 
//**************************************************************************************************
#ifndef SOCKET3_H
#define SOCKET3_H

// This class derivate from ionSensorClass
class socket3Class : public ionSensorClass
{
	public:

		socket3Class();
		float read();
};

#endif

//**************************************************************************************************
// SOCKET4 Class 
//**************************************************************************************************
#ifndef SOCKET4_H
#define SOCKET4_H

// This class derivate from ionSensorClass
class socket4Class : public ionSensorClass
{
	public:

		socket4Class();
		float read();
};

#endif

