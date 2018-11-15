/*! \file Sdi12SensorXtr.h
	\brief Library for managing SDI-12 in Xtreme boards

	Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
	http://www.libelium.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 2.1 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.	If not, see <http://www.gnu.org/licenses/>.

	Version:		3.0
	Design:			David Gascón
	Implementation: Victor Boria

 */

#ifndef Sdi12SensorXtr_h
#define Sdi12SensorXtr_h

#include <SDI12.h>


/*!
 * \def DEBUG_XTR_SDI
 * \brief Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */

#define DEBUG_XTR_SDI		0
#define PRINT_XTR_SDI(str)		USB.print(F("[XTR-SDI] ")); USB.print(str);
#define PRINTLN_XTR_SDI(str)	USB.print(F("[XTR-SDI] ")); USB.println(str);


// Supported sensors with Xtreme boards
#define _5TE				1
#define GS3					2
#define VP4					3
#define MPS6				4 //Name change to TEROS21 in nov 2018
#define SO411				5
#define SI411				6
#define _5TM				7
#define SF421				8
#define C4E					9
#define CTZN				10
#define MES5				11
#define OPTOD				12
#define PHEHT				13
#define NTU					14

/*!
 * \class Sdi12SensorXtr
 * \brief class for SDI12 sensors in Xtreme boards
 */
class Sdi12SensorXtr
{
	public:
		//! Constructor
		Sdi12SensorXtr();
		
		//object to manage SDI12 communications
		WaspSDI12 sdi12;

		uint8_t readMeasures(	uint8_t sensorType,
						char *sensorSerialNumber,
						float &parameter1, 
						float &parameter2, 
						float &parameter3, 
						float &parameter4);
		
		char address;
		uint8_t timeToNextMeasure;
		
 	private:
		uint8_t isSensor(uint8_t sensorName, char *sensorSerialNumber);
	 	uint8_t startSensor();
};

// object to manage SDI-12 sensor in Xtreme boards
extern Sdi12SensorXtr sdi12SensorXtr;

#endif
