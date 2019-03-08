/*! \file WaspSensorAgr_v30.h
    \brief Library for managing the Agriculture Sensor Board v2.0

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

 /*! \def WaspSensorAgr_v30_h
    \brief The library flag
  */
#ifndef WaspSensorAgr_v30_h
#define WaspSensorAgr_v30_h
/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>
#include <WaspConstants.h>
#include <avr/pgmspace.h>
#include "UltrasoundSensor.h"
#include "TSL2561.h"
//**********************************************************************
// DEBUG MODES
//**********************************************************************

/*! Possible values:
 * 	0: No debug mode enabled
 * 	1: debug 1
 * 	2: debug 2
 */
#define DEBUG_AGR 0

// define print message
#define PRINT_AGR(str)	USB.print(F("[AGR] ")); USB.print(str);


//**********************************************************************
// DEFINES INPUTS INPUTS
//**********************************************************************
#define WATERMARK_DIR_A 			DIGITAL8
#define RADIATION_ON 				DIGITAL7
#define WATERMARK_DIR_B				DIGITAL6
#define DEN_PT1000_ON				DIGITAL5
#define I2C_PIN_OE 					DIGITAL3
#define ANEMOMETER_DATA				DIGITAL2
#define WATERMARK_ON				DIGITAL1
#define LEAF_WETNESS_ON				ANA6
#define WATERMARK_DATA				ANA5
#define WIND_VANE_DATA				ANA4
#define PLUVIO_DATA					ANA3
#define LEAF_WETNESS_DATA			ANA2
#define WEATHER_STATION_ON			ANA0
#define	SENS_AGR_PLUVIOMETER		16
/*
#define	SENS_AGR_ANEMOMETER 		1
#define	SENS_AGR_WATERMARK_1		2
#define	SENS_AGR_WATERMARK_2		4
#define	SENS_AGR_WATERMARK_3		8
#define	SENS_AGR_VANE				0
#define	SENS_AGR_DENDROMETER		32
#define	SENS_AGR_PT1000				64
#define	SENS_AGR_LEAF_WETNESS		128
#define	SENS_AGR_TEMPERATURE		256
#define	SENS_AGR_HUMIDITY			512
#define	SENS_AGR_RADIATION			1024
#define	SENS_AGR_SENSIRION			2048
#define	SENS_AGR_PRESSURE			4096
#define	SENS_AGR_LDR				8192
#define	SENS_AGR_TEMP_DS18B20		16384
* /

//**********************************************************************
// DEFINES WIND VANE DIRECTIONS
//**********************************************************************
/*! \def SENS_AGR_VANE_N
    \brief Vane : North Direction
 */
/*! \def SENS_AGR_VANE_NNE
    \brief Vane : North-NorthEast Direction
 */
/*! \def SENS_AGR_VANE_NE
    \brief Vane : NorthEast Direction
 */
/*! \def SENS_AGR_VANE_ENE
    \brief Vane : East-NorthEast Direction
 */
/*! \def SENS_AGR_VANE_E
    \brief Vane : East Direction
 */
/*! \def SENS_AGR_VANE_ESE
    \brief Vane : East-SouthEast Direction
 */
/*! \def SENS_AGR_VANE_SE
    \brief Vane : SouthEast Direction
 */
/*! \def SENS_AGR_VANE_SSE
    \brief Vane : South-SouthEast Direction
 */
/*! \def SENS_AGR_VANE_S
    \brief Vane : South Direction
 */
/*! \def SENS_AGR_VANE_SSW
    \brief Vane : South-SouthWest Direction
 */
/*! \def SENS_AGR_VANE_SW
    \brief Vane : SouthWest Direction
 */
/*! \def SENS_AGR_VANE_WSW
    \brief Vane : West-SouthWest Direction
 */
/*! \def SENS_AGR_VANE_W
    \brief Vane : West Direction
 */
/*! \def SENS_AGR_VANE_WNW
    \brief Vane : West-Northwest Direction
 */
/*! \def SENS_AGR_VANE_NW
    \brief Vane : NorthWest Direction
 */
/*! \def SENS_AGR_VANE_NNW
    \brief Vane : North-NorthWest Direction
 */
#define SENS_AGR_VANE_E			0
#define SENS_AGR_VANE_ENE		1
#define SENS_AGR_VANE_NE		2
#define SENS_AGR_VANE_NNE		3
#define SENS_AGR_VANE_N			4
#define SENS_AGR_VANE_NNW		5
#define SENS_AGR_VANE_NW		6
#define SENS_AGR_VANE_WNW		7
#define SENS_AGR_VANE_W			8
#define SENS_AGR_VANE_WSW		9
#define SENS_AGR_VANE_SW		10
#define SENS_AGR_VANE_SSW		11
#define SENS_AGR_VANE_S			12
#define SENS_AGR_VANE_SSE		13
#define SENS_AGR_VANE_SE		14
#define SENS_AGR_VANE_ESE		15

//**********************************************************************
// DEFINES INPUTS INPUTS
//**********************************************************************
#define	SENS_SA_WATERMARK		17
#define	SENS_SA_PT1000			18
#define	SENS_SA_DENDROMETER		19
#define	SENS_SA_LW				20
#define	SENS_SA_APG				21
#define	SENS_SA_DENDROMETER		22
#define	SENS_SA_LW				23
#define	SENS_SA_APG				24
#define	SENS_SA_WDV				25
#define	SENS_SA_ANE				26
#define	SENS_SA_PLV				27
#define	SENS_SA_DD				28
#define	SENS_SA_DF				29
#define	SENS_SA_DC3				30
#define	SENS_SA_DC2				31
//**********************************************************************
//DECLARE VARS
//**********************************************************************
	struct pluviometer_st
	{
		uint8_t		month;
		uint8_t		day;
		uint16_t	pulses;
	};
//**************************************************************************************************
//  Smart Agriculture Board Class
//**************************************************************************************************
class WaspSensorAgr_v30
{
	public:
		//! Class constructor
		WaspSensorAgr_v30();
		//! Turns ON the board
		void ON(void);
		//! Turns OFF the board
		void OFF(void);
		float getTemperature();
		float getHumidity();
		float getPressure();
		uint16_t getDistance();
		uint32_t getLuxes();
		uint32_t getLuxes(bool gain);
		uint32_t getLuxes(bool gain, uint8_t res);	
		void sleepAgr(const char*, uint8_t, uint8_t, uint8_t);
		void sleepAgr(const char*, uint8_t, uint8_t, uint8_t, uint8_t);
		friend class watermarkClass;
		friend class leafWetnessClass;
		friend class ds18b20Class;
		friend class pt1000Class;
		friend class dendrometerClass;
		friend class radiationClass;
		friend class weatherStationClass;
	private:

	protected:
		float conversion(byte[], uint8_t);
};
extern WaspSensorAgr_v30 Agriculture;
#endif

//**************************************************************************************************
// watermark class
//**************************************************************************************************
#ifndef watermarkClass_h
#define watermarkClass_h

class watermarkClass
{
	public:
		watermarkClass(uint8_t);
		float readWatermark();
	private:
		uint8_t _watermarkSocket;
};
#endif

//**************************************************************************************************
// Leaf Wetness class
//**************************************************************************************************
#ifndef leafWetnessClass_h
#define leafWetnessClass_h

class leafWetnessClass
{
	public:
		leafWetnessClass();
		float getLeafWetness();
};

#endif

//**************************************************************************************************
// DS18B20 class
//**************************************************************************************************
#ifndef ds18b20Class_h
#define ds18b20Class_h

class ds18b20Class
{
	public:
		ds18b20Class();
		float readDS18b20();
};
#endif

//**************************************************************************************************
// PT1000 class
//**************************************************************************************************
#ifndef pt1000Class_h
#define pt1000Class_h

class pt1000Class : public WaspSensorAgr_v30
{
	public:
		pt1000Class();
		float readPT1000();
};
#endif
//**************************************************************************************************
// Dendrometer sensor class
//**************************************************************************************************
#ifndef dendrometerClass_h
#define dendrometerClass_h

class dendrometerClass : public WaspSensorAgr_v30
{
	public:
		dendrometerClass();
		dendrometerClass(uint8_t type);
		float readDendrometer();
		float readGrowth();
		void setReference(void);
		uint8_t _dendro;
		float _reference;
};
#endif
//**************************************************************************************************
// Radiation class
//**************************************************************************************************
#ifndef radiationClass_h
#define radiationClass_h

class radiationClass
{
	public:
		radiationClass();
		float readRadiation();
};
#endif
//**************************************************************************************************
// Weather Station class
//**************************************************************************************************
#ifndef weatherStationClass_h
#define weatherStationClass_h

class weatherStationClass : public WaspSensorAgr_v30
{
	public:
		weatherStationClass();
		float readAnemometer();
		void getVaneFiltered(void);
		uint8_t readVaneDirection();
		float readPluviometerHour();
		float readPluviometerCurrent();
		float readPluviometerDay();
		uint16_t readPluviometer(void);
		float readPluviometer(uint8_t, int);
		uint8_t vaneDirection;
		void attachPluvioInt(void);
		void detachPluvioInt(void);
		void storePulse();
		float gustWind;
		pluviometer_st plv_array[24];
		void getVaneDirection(float);
};
#endif
