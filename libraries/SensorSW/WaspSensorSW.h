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
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:		2.2
 *  Design:			Ahmad Saad
 */

 
#ifndef WaspSensorSW_h
#define WaspSensorSW_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>
#include <utility/ADC.h>
#include <utility/filter.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

#define	SENS_SW_DO				2
#define	SENS_SW_COND			3
#define	SENS_SW_PH				4
#define	SENS_SW_ORP				5
#define	SENS_SW_DI				6


// Calibration values of the conductivity sensor
#define	SW_COND_CAL_01		0.0271
#define	SW_COND_CAL_02		0.0365
#define	SW_COND_CAL_03		0.0478
#define	SW_COND_CAL_04		0.0676
#define	SW_COND_CAL_05		0.1151
#define	SW_COND_CAL_06		0.1997
#define	SW_COND_CAL_07		0.3190
#define	SW_COND_CAL_08		0.3698
#define	SW_COND_CAL_09		0.5047
#define	SW_COND_CAL_10		0.5990
#define	SW_COND_CAL_11		0.6860
#define	SW_COND_CAL_12		0.7642
#define	SW_COND_CAL_13		0.8694
#define	SW_COND_CAL_14		0.8754
#define	SW_COND_CAL_15		0.9076
#define	SW_COND_CAL_16		0.9931

#define FILTER_SAMPLES 7

#define TEMP_CHANNEL 	0
#define DO_CHANNEL 		2
#define PH_CHANNEL 		3
#define ORP_CHANNEL 	4
#define DI_CHANNEL 		5
#define COND_CHANNEL 	7

#define pH_SOCKET 3
#define ORP_SOCKET 2
#define DI_SOCKET 1
 
//**************************************************************************************************
//  Smart Water Board Class 
//**************************************************************************************************
class WaspSensorSW
{
	public:
		//! Class constructor
		WaspSensorSW();
		//! Turns ON the board
		void ON(void);
		//! Turns OFF the board
		void OFF(void);

		friend class pHClass;
		friend class conductivityClass;
		friend class ORPClass;
		friend class DOClass;
		friend class DIClass;

	private:
		
		//! Read from the ADC
		float getMeasure(uint8_t, uint8_t);		
		

		
};

extern WaspSensorSW SensorSW;

#endif



//**************************************************************************************************
// Temperature sensor class 
//**************************************************************************************************
#ifndef PT1000_h
#define PT1000_h

class pt1000Class
{
	public:

		pt1000Class();
		float readTemperature(void);
};

#endif


//**************************************************************************************************
// pH sensor class 
//**************************************************************************************************
#ifndef pHsensor_h
#define pHsensor_h

class pHClass
{
	public:

		pHClass();
		pHClass(uint8_t);

		
		float readpH();
		float pHConversion(float input);
		float pHConversion(float input, float temp);
		void setCalibrationPoints(	float	_calibration_point_10,
									float	_calibration_point_7,
									float	_calibration_point_4,
									float	_calibration_temperature);

	private:

		uint8_t pHChannel;
		uint8_t pHSwitch;
		
		float calibration_point_10;
		float calibration_point_7;
		float calibration_point_4;
		float calibration_temperature;
};

#endif



//**************************************************************************************************
// Conductivity sensor class 
//**************************************************************************************************
#ifndef Conductivity_h
#define Conductivity_h

class conductivityClass
{
	public:

		conductivityClass();
		float readConductivity();
		float conductivityConversion(float input);

		void setCalibrationPoints(	float _point_1_conductivity, float _point_1_calibration,
									float _point_2_conductivity, float _point_2_calibration);


	private:

		float resistanceConversion(float input);

		float point_1_cond;
		float point_1_cal;
		float point_2_cond;
		float point_2_cal;
};

#endif


//**************************************************************************************************
// ORP sensor class 
//**************************************************************************************************
#ifndef ORP_h
#define ORP_h

class ORPClass
{
	public:

		ORPClass();
		ORPClass(uint8_t);
		
		float readORP();

	private:

		uint8_t ORPChannel;
		uint8_t ORPSwitch;

};

#endif

//**************************************************************************************************
// DO sensor class 
//**************************************************************************************************
#ifndef DO_h
#define DO_h

class DOClass
{
	public:

		DOClass(){};
		float readDO();
		float DOConversion(float input);

		void setCalibrationPoints(float _air_calibration, float _zero_calibration);

	private:

		float zero_calibration;
		float air_calibration;
};

#endif


//**************************************************************************************************
// DI sensor class 
//**************************************************************************************************
#ifndef DI_h
#define DI_h

class DIClass
{
	public:

		DIClass();
		DIClass(uint8_t);
		float readDI();
		void setCalibrationPoints(float calibrationValues[]);
		
		void setCalibrationPoints(	float calVoltages[], 
									float calConcentrations[],  
									uint8_t numPoints);

		float calculateConcentration(float input);

	private:

		uint8_t DIChannel;
		uint8_t DISwitch;

		float slope;
		float intersection;
		
};

#endif
