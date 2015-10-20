/*! \file TurbiditySensor.h
	\brief Library for managing the Smart Water Turbidity Sensor Board

	Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
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

	Version:		1.2
	Design:		David Gascón
	Implementation:	Ahmad Saad
*/


#ifndef TurbditySensor_h
#define TurbditySensor_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <inttypes.h>

/////////////////////////////////////////////////////////////////////////////
// Include the neccesary libraries.
// The turbidity sensor uses RS-485 Modbus communication
/////////////////////////////////////////////////////////////////////////////

#include "../RS485/Wasp485.h"
#include "../ModbusMaster485/ModbusMaster485.h"

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
#define DISABLED			0x0000
#define TURB_MEAS_STATUS	0x0065
#define NEW_MEAS_REG		0x0001
#define TEMP_NEW_MEAS		0x0001
#define TURB_NEW_MEAS		0x0002

// Registers
#define OFFSET_0			0x0001
#define TEMP_25				0x0002

// This address will be configured as a first step 
#define SENSOR_ADDRESS		0x0001
#define DEFAULT_ADDRESS 	0x0000

// Debug mode define
#define DEBUG_MODE 0

// FilterSamples should  be an odd number, no smaller than 3
#define filterSamples   11


/******************************************************************************
 * Class
 ******************************************************************************/
 
//! Turbidity Sensor Class
/*!
	This Class defines all the variables and functions used for
	managing the Turbidity Sensor
 */
class turbiditySensorClass
{
	public: 
		
		// Public functions
		turbiditySensorClass();
		char ON();
		void OFF();
		uint8_t readTurbidity();
		float getTurbidity();

	private:
	
		// Sensor management functions
		uint8_t readTemperature();
		void readCompensationTemperature(uint16_t _register);
		void startMeasurment(uint8_t parameter);
		void typeMeasurementConfiguration(uint16_t address, uint16_t config);
		void resetSensor();
		void average(uint8_t average);
		int configureSensorAddress(uint8_t address);
		void clearBuffer();
		void writeCalibrationValue(uint16_t address, float value);
		float getTemperature();

		// For Mdobus management
		ModbusMaster485 sensor;
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
