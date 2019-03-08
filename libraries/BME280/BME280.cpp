/*
 *  Library for managing the BME280 sensor
 *
 *  Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.2
 *  Design:			David Gascón
 *  Implementation:	Alejandro Gállego
 */

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif

#include <BME280.h>


// Constructors ////////////////////////////////////////////////////////////////
BME280::BME280()
{
}

/// PRIVATE FUNCTIONS
/// INTERNAL COMPENSATION FUNCTIONS
/* Function: 	This function compensates the temperature with the calibration data
 * Parameters:	uncompensated_temp: uncompensated temperature value
 * Returns: 	compensated temperature in ºC
*/
float BME280::compensateTemp(long uncompensated_temp)
{

	long var1, var2;

	#if BME280_DEBUG>0
		PRINT_BME(F("BME280.Compensate temperature\n"));
	#endif
	#if BME280_DEBUG>1
		PRINT_BME(F("BME280.Uncompensated temp: 0x"));
		USB.println(uncompensated_temp, HEX);
	#endif

	var1 = ((((uncompensated_temp >> 3) - ((long)dig_T1 << 1))) * ((long)dig_T2)) >> 11;
	var2 = (((((uncompensated_temp >> 4) - ((long)dig_T1)) * ((uncompensated_temp >> 4) - ((long)dig_T1))) >> 12) * ((long)dig_T3)) >> 14;
	t_fine = var1 + var2;
	var1 = ((t_fine * 5 + 128) >> 8);

	return (float(var1) / 100);

}

/* Function: 	This function compensates the pressure with the calibration data
 * Parameters:	uncompensated_pres: uncompensated pressure value
 * Returns: 	compensated pressure in Pascals
*/
float BME280::compensatePres(long uncompensated_pres)
{

	long long var1, var2, p;

	#if BME280_DEBUG>0
		PRINT_BME(F("BME280.Compensate pressure\n"));
	#endif
	#if BME280_DEBUG>1
		PRINT_BME(F("BME280.Uncompensated pres: 0x"));
		USB.println(uncompensated_pres, HEX);
	#endif

	var1 = ((long long)t_fine) - 128000;
	var2 = var1 * var1 * (long long)dig_P6;
	var2 = var2 + ((var1 * (long long)dig_P5) << 17);
	var2 = var2 + (((long long)dig_P4) << 35);
	var1 = ((var1 * var1 * (long long)dig_P3) >> 8) + ((var1 * (long long)dig_P2) << 12);
	var1 = (((((long long)1) << 47) + var1)) * ((long long)dig_P1) >> 33;

	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}

	p = 1048576 - uncompensated_pres;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = (((long long)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	var2 = (((long long)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((long long)dig_P7) << 4);

	return (uint32_t)p;

}

/* Function: 	This function compensates the humidity with the calibration data
 * Parameters:	uncompensated_hum: uncompensated humidity value
 * Returns: 	compensated humidity in %RH
*/
float BME280::compensateHum(long uncompensated_hum)
{

	long v_x1_u32r;

	#if BME280_DEBUG>0
		PRINT_BME(F("BME280.Compensate humidity\n"));
	#endif
	#if BME280_DEBUG>1
		PRINT_BME(F("BME280.Uncompensated hum: 0x"));
		USB.println(uncompensated_hum, HEX);
	#endif

	v_x1_u32r = (t_fine - ((long)76800));
	v_x1_u32r = (((((uncompensated_hum << 14) - (((long)dig_H4) << 20) - (((long)dig_H5) * v_x1_u32r)) + ((long)16384)) >> 15) * (((((((v_x1_u32r * ((long)dig_H6)) >> 10) * (((v_x1_u32r * ((long)dig_H3)) >> 11) + ((long)32768))) >> 10) + ((long)2097152)) *	((long)dig_H2) + 8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((long)dig_H1)) >> 4));

	if (v_x1_u32r < 0)
	{
		v_x1_u32r = 0;
	}

	if (v_x1_u32r > 419430400)
	{
		v_x1_u32r = 419430400;
	}


	return (v_x1_u32r >> 12);


}

/// PUBLIC FUNCTIONS
/// POWER AND CONFIGURATION FUNCTIONS

/* Function: 	This function checks if the module is accesible via I2C and
 * 				reads the calibration registers
 * Returns: 	1 if is OK, 0 if not
*/
int8_t BME280::ON()
{
	if ((WaspRegister & REG_3V3) == 0)
	{
		PWR.setSensorPower(SENS_3V3, SENS_ON);
		#if BME280_DEBUG>0
			PRINT_BME(F("BME280.3V3 to ON \n"));
		#endif
	}
	
	I2C.begin();
	
	delay(100);

	// Check if the sensor is accesible
	if (checkID() == 1)
	{
		// Read the calibration registers
		readCalibration();
		return 1;
	}

	return 0;
}

/* Function: 	This function checks if the module is accesible via I2C
 * Returns: 	1 if is accesible, 0 if not
*/
int8_t BME280::checkID()
{
	uint8_t valueID;


	#if BME280_DEBUG>0
		PRINT_BME(F("BME280.Checking ID..."));
	#endif
	I2C.read(I2C_ADDRESS_GASPRO_BME280, BME280_CHIP_ID_REG, &valueID, 1);
	if (valueID == BME280_CHIP_ID_REG_CHIP_ID)
	{
		#if BME280_DEBUG>0
			PRINT_BME(F("OK\n"));
		#endif
		return 1;
	}

	#if BME280_DEBUG>0
		PRINT_BME(F("error\n"));
	#endif
	return 0;

}

/* Function: 	This function reads the calibration registers
 * Returns: 	Nothing
*/
void BME280::readCalibration()
{
	uint8_t buffer[4];

	#if BME280_DEBUG>0
		PRINT_BME(F("BME280.Reading calibration regs...\n"));
	#endif

	// dig_T1
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_T1_LSB_REG, buffer, 2);
	dig_T1 = (uint16_t(buffer[1]) << 8) + buffer[0];

	// dig_T2
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_T2_LSB_REG, buffer, 2);
	dig_T2 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_T3
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_T3_LSB_REG, buffer, 2);
	dig_T3 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_P1
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_P1_LSB_REG, buffer, 2);
	dig_P1 = (uint16_t(buffer[1]) << 8) + buffer[0];

	// dig_P2
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_P2_LSB_REG, buffer, 2);
	dig_P2 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_P3
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_P3_LSB_REG, buffer, 2);
	dig_P3 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_P4
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_P4_LSB_REG, buffer, 2);
	dig_P4 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_P5
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_P5_LSB_REG, buffer, 2);
	dig_P5 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_P6
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_P6_LSB_REG, buffer, 2);
	dig_P6 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_P7
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_P7_LSB_REG, buffer, 2);
	dig_P7 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_P8
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_P8_LSB_REG, buffer, 2);
	dig_P8 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_P9
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_P9_LSB_REG, buffer, 2);
	dig_P9 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_H1
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_H1_REG, &dig_H1, 1);
	
	// dig_H2
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_H2_LSB_REG, buffer, 2);
	dig_H2 = (int16_t(buffer[1]) << 8) + buffer[0];

	// dig_H3
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_H3_REG, &dig_H3, 1);
	
	// dig_H4 and dig_H5
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_H4_MSB_REG, buffer, 3);
	dig_H4 = (int16_t(buffer[0]) << 4) + (buffer[1] & 0x0F);

	dig_H5 = (int16_t(buffer[2]) << 4) + (buffer[1] >> 4);

	// dig_H6
	I2C.read( I2C_ADDRESS_GASPRO_BME280, BME280_DIG_H6_REG,  buffer, 1);
	dig_H6 = buffer[0];

}

/* Function: 	This function shows the calibration variables
 * Returns: 	Nothing
*/
void BME280::showCalibration()
{

	USB.println(F("Calibration values for BME280"));
	USB.print(F("T1:\t0x"));
	USB.printHex(dig_T1);
	USB.print(F("\t\t"));
	USB.println(dig_T1, DEC);
	USB.print(F("T2:\t0x"));
	USB.printHex(dig_T2);
	USB.print(F("\t\t"));
	USB.println(dig_T2, DEC);
	USB.print(F("T3:\t0x"));
	USB.printHex(dig_T3);
	USB.print(F("\t\t"));
	USB.println(dig_T3, DEC);


	USB.print(F("P1:\t0x"));
	USB.printHex(dig_P1);
	USB.print(F("\t\t"));
	USB.println(dig_P1, DEC);
	USB.print(F("P2:\t0x"));
	USB.printHex(dig_P2);
	USB.print(F("\t\t"));
	USB.println(dig_P2, DEC);
	USB.print(F("P3:\t0x"));
	USB.printHex(dig_P3);
	USB.print(F("\t\t"));
	USB.println(dig_P3, DEC);
	USB.print(F("P4:\t0x"));
	USB.printHex(dig_P4);
	USB.print(F("\t\t"));
	USB.println(dig_P4, DEC);
	USB.print(F("P5:\t0x"));
	USB.printHex(dig_P5);
	USB.print(F("\t\t"));
	USB.println(dig_P5, DEC);
	USB.print(F("P6:\t0x"));
	USB.printHex(dig_P6);
	USB.print(F("\t\t"));
	USB.println(dig_P6, DEC);
	USB.print(F("P7:\t0x"));
	USB.printHex(dig_P7);
	USB.print(F("\t\t"));
	USB.println(dig_P7, DEC);
	USB.print(F("P8:\t0x"));
	USB.printHex(dig_P8);
	USB.print(F("\t\t"));
	USB.println(dig_P8, DEC);
	USB.print(F("P9:\t0x"));
	USB.printHex(dig_P9);
	USB.print(F("\t\t"));
	USB.println(dig_P9, DEC);


	USB.print(F("H1:\t0x"));
	USB.printHex(dig_H1);
	USB.print(F("\t\t"));
	USB.println(dig_H1, DEC);
	USB.print(F("H2:\t0x"));
	USB.printHex(dig_H2);
	USB.print(F("\t\t"));
	USB.println(dig_H2, DEC);
	USB.print(F("H3:\t0x"));
	USB.printHex(dig_H3);
	USB.print(F("\t\t"));
	USB.println(dig_H3, DEC);
	USB.print(F("H4:\t0x"));
	USB.printHex(dig_H4);
	USB.print(F("\t\t"));
	USB.println(dig_H4, DEC);
	USB.print(F("H5:\t0x"));
	USB.printHex(dig_H5);
	USB.print(F("\t\t"));
	USB.println(dig_H5, DEC);
	USB.print(F("H6:\t0x"));
	USB.printHex(dig_H6);
	USB.print(F("\t\t"));
	USB.println(dig_H6, DEC);
}

/// MEASURE FUNCTIONS
/* Function: 	This function reads temperature and compensate it
 * Parameters:	over_sample_value:	oversamples value for the sensor
 * 					- BME280_OVERSAMP_SKIPPED
 * 					- BME280_OVERSAMP_1X
 * 					- BME280_OVERSAMP_2X
 * 					- BME280_OVERSAMP_4X
 * 					- BME280_OVERSAMP_8X
 * 					- BME280_OVERSAMP_16X
 * 				filter_value: filter value for the sensor
 * 					- BME280_FILTER_COEFF_OFF
 * 					- BME280_FILTER_COEFF_2
 * 					- BME280_FILTER_COEFF_4
 * 					- BME280_FILTER_COEFF_8
 * 					- BME280_FILTER_COEFF_16
 * Returns: 	The temperature in ºC
 *				-1000 if comunication error
 *				-1001 if conversion timeout
*/
float BME280::getTemperature(uint8_t over_sample_value, uint8_t filter_value)
{
	uint8_t buffer[3];
	long uncompensated_temp;
	float temp;
	float meassure_time, meassure_max_time;

	#if BME280_DEBUG>0
		PRINT_BME(F("BME280.Read temperature\n"));
	#endif

	// Checks communication
	if (checkID() != 1)
	{
		return -1000;
	}



	//************************************************************************
	// Configuration of the sensor
	// Unselect humidity meassure
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CTRL_HUMIDITY_REG,
				BME280_OVERSAMP_SKIPPED,
				BME280_CTRL_HUMIDITY_REG_OVERSAM_HUMIDITY__POS,
				BME280_CTRL_HUMIDITY_REG_OVERSAM_HUMIDITY__LEN);

	// Unselect pressure meassure
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CTRL_MEAS_REG,
				BME280_OVERSAMP_SKIPPED,
				BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__POS,
				BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__LEN);

	// Select temperature meassure
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CTRL_MEAS_REG,
				over_sample_value,
				BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__POS,
				BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__LEN);
    
	
	// Configure IIR filter	
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CONFIG_REG,
				BME280_FILTER_COEFF_OFF,
				BME280_CONFIG_REG_FILTER__POS,
				BME280_CONFIG_REG_FILTER__LEN);


	//************************************************************************
	// Meassuring
	// Selects forced mode
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CTRL_MEAS_REG,
				BME280_FORCED_MODE,
				BME280_CTRL_MEAS_REG_POWER_MODE__POS,
				BME280_CTRL_MEAS_REG_POWER_MODE__LEN);

	meassure_time = 1 + (2 * (1 << (over_sample_value - 1)));
	meassure_max_time = 1.25 + (2.3 * (1 << (over_sample_value - 1)));

	#if BME280_DEBUG>1
		PRINT_BME(F("BME280.meassure_time: "));
		USB.println(meassure_time);
		PRINT_BME(F("BME280.meassure_max_time: "));
		USB.println(meassure_max_time);
	#endif

	delay(int(meassure_time) + 1);

	// Check if the meassure is completed
	I2C.readBit(I2C_ADDRESS_GASPRO_BME280, BME280_STAT_REG, buffer, BME280_STAT_REG_MEASURING__POS);
	if (buffer[0] == 1)
	{
		// Wait up to meassure_max_time
		delay(int(meassure_max_time - meassure_time) + 1);
		// Check if the meassure is completed
		I2C.readBit(I2C_ADDRESS_GASPRO_BME280, BME280_STAT_REG, buffer, BME280_STAT_REG_MEASURING__POS);
		if (buffer[0] == 1)
		{
			return -1001;
		}
	}


	//************************************************************************
	// Read data and compensate it
	
	I2C.read(I2C_ADDRESS_GASPRO_BME280, BME280_TEMPERATURE_MSB_REG, buffer, 3);
	uncompensated_temp = (long(buffer[0]) << 16) + (long(buffer[1]) << 8) + long(buffer[2]);
	uncompensated_temp >>= 4;
	temp = compensateTemp(uncompensated_temp);

    return temp;

}

/* Function: 	This function reads pressure and compensate it
 * Parameters:	over_sample_value:	oversamples value for the sensor
 * 					- BME280_OVERSAMP_SKIPPED
 * 					- BME280_OVERSAMP_1X
 * 					- BME280_OVERSAMP_2X
 * 					- BME280_OVERSAMP_4X
 * 					- BME280_OVERSAMP_8X
 * 					- BME280_OVERSAMP_16X
 * 				filter_value: filter value for the sensor
 * 					- BME280_FILTER_COEFF_OFF
 * 					- BME280_FILTER_COEFF_2
 * 					- BME280_FILTER_COEFF_4
 * 					- BME280_FILTER_COEFF_8
 * 					- BME280_FILTER_COEFF_16
 * Returns: 	The pressure in Pascals
 *				-1000 if comunication error
 *				-1001 if conversion timeout
*/
float BME280::getPressure(uint8_t over_sample_value, uint8_t filter_value)
{
	uint8_t buffer[3];
	long uncompensated_pres;
	long uncompensated_temp;
	float pressure;
	float meassure_time, meassure_max_time;


	#if BME280_DEBUG>0
		PRINT_BME(F("BME280.Read pressure\n"));
	#endif

	// Checks communication
	if (checkID() != 1)
	{
		return -1000;
	}

	// Unselect humidity meassure
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CTRL_HUMIDITY_REG,
				BME280_OVERSAMP_SKIPPED,
				BME280_CTRL_HUMIDITY_REG_OVERSAM_HUMIDITY__POS,
				BME280_CTRL_HUMIDITY_REG_OVERSAM_HUMIDITY__LEN);

	// Select pressure meassure
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CTRL_MEAS_REG,
				over_sample_value,
				BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__POS,
				BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__LEN);
	
	// Select temperature meassure 
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CTRL_MEAS_REG,
				over_sample_value,
				BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__POS,
				BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__LEN);
    
	
	// Configure IIR filter	
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CONFIG_REG,
				BME280_FILTER_COEFF_OFF,
				BME280_CONFIG_REG_FILTER__POS,
				BME280_CONFIG_REG_FILTER__LEN);

	// Select forced mode
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
				BME280_CTRL_MEAS_REG,
				BME280_FORCED_MODE,
				BME280_CTRL_MEAS_REG_POWER_MODE__POS,
				BME280_CTRL_MEAS_REG_POWER_MODE__LEN);


	meassure_time = 1 + (2 * (1 << (over_sample_value - 1))) + (2 * (1 << (over_sample_value - 1)) + 0.5);
	meassure_max_time = 1.25 + (2.3 * (1 << (over_sample_value - 1))) + (2.3 * (1 << (over_sample_value - 1)) + 0.575);

	#if BME280_DEBUG>1
		PRINT_BME(F("BME280.meassure_time: "));
		USB.println(meassure_time);
		PRINT_BME(F("BME280.meassure_max_time: "));
		USB.println(meassure_max_time);
	#endif

	delay(int(meassure_time) + 1);

	// Check if the meassure is completed
	I2C.readBit(I2C_ADDRESS_GASPRO_BME280, BME280_STAT_REG, buffer, BME280_STAT_REG_MEASURING__POS);
	if (buffer[0] == 1)
	{
		// Wait up to meassure_max_time
		delay(int(meassure_max_time - meassure_time) + 1);
		// Check if the meassure is completed
		I2C.readBit(I2C_ADDRESS_GASPRO_BME280, BME280_STAT_REG, buffer, BME280_STAT_REG_MEASURING__POS);
		if (buffer[0] == 1)
		{
			return -1001;
		}
	}
	
	I2C.read(I2C_ADDRESS_GASPRO_BME280, BME280_TEMPERATURE_MSB_REG, buffer, 3);
	uncompensated_temp = (long(buffer[0]) << 16) + (long(buffer[1]) << 8) + long(buffer[2]);
	uncompensated_temp >>= 4;
	compensateTemp( uncompensated_temp);
	
	I2C.read(I2C_ADDRESS_GASPRO_BME280, BME280_PRESSURE_MSB_REG, buffer, 3);
	uncompensated_pres = (long(buffer[0]) << 16) + (long(buffer[1]) << 8) + long(buffer[2]);
	uncompensated_pres >>= 4;
	pressure = compensatePres(uncompensated_pres);

	// compensatePres returns pressure in Q24.8 format
	pressure /= 256;
    return pressure;

}

/* Function: 	This function reads humidity and compensate it
 * Parameters:	filter_value: oversamples value for the sensor
 * 					- BME280_OVERSAMP_SKIPPED
 * 					- BME280_OVERSAMP_1X
 * 					- BME280_OVERSAMP_2X
 * 					- BME280_OVERSAMP_4X
 * 					- BME280_OVERSAMP_8X
 * 					- BME280_OVERSAMP_16X
 * Returns: 	The humidity in %RH
 *				-1000 if comunication error
 *				-1001 if conversion timeout
*/
float BME280::getHumidity(uint8_t over_sample_value)
{
	uint8_t buffer[3];
	long uncompensated_hum;
	long uncompensated_temp;
	float humidity;
	float meassure_time, meassure_max_time;

	#if BME280_DEBUG>0
		PRINT_BME(F("BME280.Read humidity\n"));
	#endif

	// Checks communication
	if (checkID() != 1)
	{
		return -1000;
	}

	// Select humidity meassure
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
					BME280_CTRL_HUMIDITY_REG,
					over_sample_value,
					BME280_CTRL_HUMIDITY_REG_OVERSAM_HUMIDITY__POS,
					BME280_CTRL_HUMIDITY_REG_OVERSAM_HUMIDITY__LEN);

	// Unselect pressure meassure
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
					BME280_CTRL_MEAS_REG,
					BME280_OVERSAMP_SKIPPED,
					BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__POS,
					BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__LEN);
	
	// Select temperature meassure 
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
					BME280_CTRL_MEAS_REG,
					over_sample_value,
					BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__POS,
					BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__LEN);
    
	
	// Configure IIR filter	
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
					BME280_CONFIG_REG,
					BME280_FILTER_COEFF_OFF,
					BME280_CONFIG_REG_FILTER__POS,
					BME280_CONFIG_REG_FILTER__LEN);

	// Select forced mode
	I2C.writeBits(	I2C_ADDRESS_GASPRO_BME280, 
					BME280_CTRL_MEAS_REG,
					BME280_FORCED_MODE,
					BME280_CTRL_MEAS_REG_POWER_MODE__POS,
					BME280_CTRL_MEAS_REG_POWER_MODE__LEN);

	meassure_time = 1 + (2 * (1 << (over_sample_value - 1))) + (2 * (1 << (over_sample_value - 1)) + 0.5);
	meassure_max_time = 1.25 + (2.3 * (1 << (over_sample_value - 1))) + (2.3 * (1 << (over_sample_value - 1)) + 0.575);

	#if BME280_DEBUG>1
		PRINT_BME(F("BME280.meassure_time: "));
		USB.println(meassure_time);
		PRINT_BME(F("BME280.meassure_max_time: "));
		USB.println(meassure_max_time);
	#endif

	delay(int(meassure_time) + 1);

	// Check if the meassure is completed
	I2C.readBit(I2C_ADDRESS_GASPRO_BME280, BME280_STAT_REG, buffer, BME280_STAT_REG_MEASURING__POS);
	if (buffer[0] == 1)
	{
		// Wait up to meassure_max_time
		delay(int(meassure_max_time - meassure_time) + 1);
		// Check if the meassure is completed
		I2C.readBit(I2C_ADDRESS_GASPRO_BME280, BME280_STAT_REG, buffer, BME280_STAT_REG_MEASURING__POS);
		if (buffer[0] == 1)
		{
			return -1001;
		}
	}
	
	I2C.read(I2C_ADDRESS_GASPRO_BME280, BME280_TEMPERATURE_MSB_REG, buffer, 3);
	uncompensated_temp = (long(buffer[0]) << 16) + (long(buffer[1]) << 8) + long(buffer[2]);
	uncompensated_temp >>= 4;
	compensateTemp(uncompensated_temp);
	
	I2C.read(I2C_ADDRESS_GASPRO_BME280, BME280_HUMIDITY_MSB_REG, buffer, 2);
	uncompensated_hum = (long(buffer[0]) << 8) + long(buffer[1]);
	humidity = compensateHum(uncompensated_hum);

	// compensateHum returns pressure in Q22.10 format
	humidity /= 1024;
    return humidity;

}

// Preinstantiate Objects //////////////////////////////////////////////////////
BME280 BME = BME280();
