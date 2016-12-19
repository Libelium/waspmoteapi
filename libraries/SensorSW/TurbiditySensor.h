/*! \file TurbiditySensor.h
	\brief Library for managing the Smart Water Turbidity Sensor

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

	Version:			3.1
	Design:				David Gascón
	Implementation:		Ahmad Saad
*/


#ifndef TurbditySensor_h
#define TurbditySensor_h

/*****************************************************************************
* Includes
******************************************************************************/
#include <inttypes.h>

/////////////////////////////////////////////////////////////////////////////
// Include the neccesary libraries.
/////////////////////////////////////////////////////////////////////////////

#include "ModbusMaster.h"
/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

// Some sensor Registers
#define ADDRESS_REG			0x00A3
#define TEMP_VALUE_REG		0x0053
#define TURB_VALUE_REG		0x0055  
#define RESET_REG			0x0002
#define COMP_TEMP_REG		0x005D
#define TEMP_MEAS_STATUS	0x0064
#define TEMP_COEF_REG		0x014C
#define TEMP_CAL1_REG		0x0200
#define TEMP_CAL2_REG		0x0202
#define OPER_NAME_REG		0x027E
#define DATE_TEMP_REG		0x0286
#define TEMP_TYPE_CON		0x00A5
#define TURB_TYPE_CON		0x00A6
#define AVRG_PARA_REG		0x00AA
#define TURB_MEAS_STATUS	0x0065
#define NEW_MEAS_REG		0x0001
#define TEMP_NEW_MEAS		0x0001
#define TURB_NEW_MEAS		0x0002

// Registers
#define OFFSET_0			0x0001
#define TEMP_25				0x0002

// Turbidity ON/OFF control Pin
#define PWR_TURBIDITY	17

// This address will be configured as a first step 
#define SENSOR_ADDRESS		0x0001
#define DEFAULT_ADDRESS 	0x0000

// FilterSamples should be an odd number, no smaller than 3
#define filterSamples	7

//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages 
 */
#define DEBUG_TURBIDITY	0

#define PRINT_TURBIDITY(str)		USB.print(F("[TURBIDITY] ")); USB.print(str);
#define PRINT_TURBIDITY_VAL(val)	USB.print(val, BIN);

#define PRINTLN_TURBIDITY(str)		USB.print(F("[TURBIDITY] ")); USB.println(str);
#define PRINTLN_TURBIDITY_VAL(val)	USB.println(val, BIN);

/******************************************************************************
 * Class
 ******************************************************************************/
 
//! Turbidity Sensor Class
/*!
	This Class defines all the variables and functions used for
	managing the Turbidity Sensor
 */
class turbidityClass
{
	public: 
		
		// Public functions
		turbidityClass();
		turbidityClass(uint8_t);

		uint8_t ON();
		void OFF();
		uint8_t readTurbidity();
		float getTurbidity();
		
		uint8_t readTemperature();
		float getTemperature();

	private:
	
		// Sensor management functions
		void readCompensationTemperature(uint16_t _register);
		uint8_t startMeasurment(uint8_t parameter);
		uint8_t typeMeasurementConfiguration(uint16_t address, uint16_t config);
		uint8_t resetSensor();
		uint8_t average(uint8_t average);
		uint8_t configureSensorAddress(uint8_t address);
		void clearBuffer();
		void writeCalibrationValue(uint16_t address, float value);
		
		uint8_t init();

		// For Mdobus management
		ModbusMaster sensor;
		// Sensor variables
		float temperature;
		float turbidity;
		
		// Filter function
		long digitalSmooth(int rawIn, int *sensSmoothArray);
		// array for holding raw sensor values for sensor1
		int sensSmoothArray1 [filterSamples];   
		// Variables for sensor1 data
		int rawData1, smoothData1;  

};

#endif
