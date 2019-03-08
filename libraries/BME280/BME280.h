/*! \file BME280.h
    \brief Library for managing the BME280 sensor

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

    Version:		3.2
    Design:			David Gascón
    Implementation:	Alejandro Gállego

*/

/*! \def BME280_h
    \brief The library flag

*/
#ifndef BME280_h
#define BME280_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>

#define BME280_DEBUG 0

// define print message
#define PRINT_BME(str)	USB.print(F("[BME] ")); USB.print(str);


//! Sensor Specific constants
#define BME280_SLEEP_MODE				0x00
#define BME280_FORCED_MODE				0x01
#define BME280_NORMAL_MODE				0x03
#define BME280_SOFT_RESET_CODE			0xB6


#define BME280_STANDBY_TIME_1_MS		0x00
#define BME280_STANDBY_TIME_63_MS		0x01
#define BME280_STANDBY_TIME_125_MS		0x02
#define BME280_STANDBY_TIME_250_MS		0x03
#define BME280_STANDBY_TIME_500_MS		0x04
#define BME280_STANDBY_TIME_1000_MS		0x05
#define BME280_STANDBY_TIME_10_MS		0x06
#define BME280_STANDBY_TIME_20_MS		0x07

/// Oversampling constants (ctrl_hum_reg and ctrl_meas_reg)
#define BME280_OVERSAMP_SKIPPED			0x00
#define BME280_OVERSAMP_1X				0x01
#define BME280_OVERSAMP_2X				0x02
#define BME280_OVERSAMP_4X				0x03
#define BME280_OVERSAMP_8X				0x04
#define BME280_OVERSAMP_16X				0x05

/// Filter constants
#define BME280_FILTER_COEFF_OFF					0x00
#define BME280_FILTER_COEFF_2					0x01
#define BME280_FILTER_COEFF_4					0x02
#define BME280_FILTER_COEFF_8					0x03
#define BME280_FILTER_COEFF_16					0x04

/// Register address
/*calibration registers */
#define BME280_DIG_T1_LSB_REG			(uint8_t)0x88
#define BME280_DIG_T1_MSB_REG			(uint8_t)0x89
#define BME280_DIG_T2_LSB_REG			(uint8_t)0x8A
#define BME280_DIG_T2_MSB_REG			(uint8_t)0x8B
#define BME280_DIG_T3_LSB_REG			(uint8_t)0x8C
#define BME280_DIG_T3_MSB_REG			(uint8_t)0x8D
#define BME280_DIG_P1_LSB_REG			(uint8_t)0x8E
#define BME280_DIG_P1_MSB_REG			(uint8_t)0x8F
#define BME280_DIG_P2_LSB_REG			(uint8_t)0x90
#define BME280_DIG_P2_MSB_REG			(uint8_t)0x91
#define BME280_DIG_P3_LSB_REG			(uint8_t)0x92
#define BME280_DIG_P3_MSB_REG			(uint8_t)0x93
#define BME280_DIG_P4_LSB_REG			(uint8_t)0x94
#define BME280_DIG_P4_MSB_REG			(uint8_t)0x95
#define BME280_DIG_P5_LSB_REG			(uint8_t)0x96
#define BME280_DIG_P5_MSB_REG			(uint8_t)0x97
#define BME280_DIG_P6_LSB_REG			(uint8_t)0x98
#define BME280_DIG_P6_MSB_REG			(uint8_t)0x99
#define BME280_DIG_P7_LSB_REG			(uint8_t)0x9A
#define BME280_DIG_P7_MSB_REG			(uint8_t)0x9B
#define BME280_DIG_P8_LSB_REG			(uint8_t)0x9C
#define BME280_DIG_P8_MSB_REG			(uint8_t)0x9D
#define BME280_DIG_P9_LSB_REG			(uint8_t)0x9E
#define BME280_DIG_P9_MSB_REG			(uint8_t)0x9F
										
#define BME280_DIG_H1_REG				(uint8_t)0xA1

#define BME280_DIG_H2_LSB_REG			(uint8_t)0xE1
#define BME280_DIG_H2_MSB_REG			(uint8_t)0xE2
#define BME280_DIG_H3_REG				(uint8_t)0xE3
#define BME280_DIG_H4_MSB_REG			(uint8_t)0xE4
#define BME280_DIG_H5_LSB_H4_LSB_REG	(uint8_t)0xE5
#define BME280_DIG_H5_MSB_REG			(uint8_t)0xE6
#define BME280_DIG_H6_REG				(uint8_t)0xE7
										
										
#define BME280_CHIP_ID_REG				(uint8_t)0xD0	// Chip ID Register
#define BME280_RST_REG					(uint8_t)0xE0	// Softreset Register
#define BME280_STAT_REG					(uint8_t)0xF3	// Status Register
#define BME280_CTRL_MEAS_REG			(uint8_t)0xF4	// Ctrl Measure Register
#define BME280_CTRL_HUMIDITY_REG		(uint8_t)0xF2	// Ctrl Humidity Register
#define BME280_CONFIG_REG				(uint8_t)0xF5	// Configuration Register
#define BME280_PRESSURE_MSB_REG			(uint8_t)0xF7	// Pressure MSB Register
#define BME280_PRESSURE_LSB_REG			(uint8_t)0xF8	// Pressure LSB Register
#define BME280_PRESSURE_XLSB_REG		(uint8_t)0xF9	// Pressure XLSB Register
#define BME280_TEMPERATURE_MSB_REG		(uint8_t)0xFA	// Temperature MSB Reg
#define BME280_TEMPERATURE_LSB_REG		(uint8_t)0xFB	// Temperature LSB Reg
#define BME280_TEMPERATURE_XLSB_REG		(uint8_t)0xFC	// Temperature XLSB Reg
#define BME280_HUMIDITY_MSB_REG			(uint8_t)0xFD	// Humidity MSB Reg
#define BME280_HUMIDITY_LSB_REG			(uint8_t)0xFE	// Humidity LSB Reg



/// ID Register
#define BME280_CHIP_ID_REG_CHIP_ID		0x60

/// Status Register
#define BME280_STAT_REG_MEASURING__POS		3
#define BME280_STAT_REG_MEASURING__MSK		0x08
#define BME280_STAT_REG_MEASURING__LEN		1

#define BME280_STAT_REG_IM_UPDATE__POS		0
#define BME280_STAT_REG_IM_UPDATE__MSK		0x01
#define BME280_STAT_REG_IM_UPDATE__LEN		1

/// Control Measurement Register
#define BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__POS		5
#define BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__MSK		0xE0
#define BME280_CTRL_MEAS_REG_OVERSAMP_TEMPERATURE__LEN		3

#define BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__POS		2
#define BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__MSK		0x1C
#define BME280_CTRL_MEAS_REG_OVERSAMP_PRESSURE__LEN		3

#define BME280_CTRL_MEAS_REG_POWER_MODE__POS				0
#define BME280_CTRL_MEAS_REG_POWER_MODE__MSK				0x03
#define BME280_CTRL_MEAS_REG_POWER_MODE__LEN				2

/// Control Humidity Register
#define BME280_CTRL_HUMIDITY_REG_OVERSAM_HUMIDITY__POS		0
#define BME280_CTRL_HUMIDITY_REG_OVERSAM_HUMIDITY__MSK		0x07
#define BME280_CTRL_HUMIDITY_REG_OVERSAM_HUMIDITY__LEN		3

/// Configuration Register
#define BME280_CONFIG_REG_TSB__POS				5
#define BME280_CONFIG_REG_TSB__MSK				0xE0
#define BME280_CONFIG_REG_TSB__LEN				3

#define BME280_CONFIG_REG_FILTER__POS			2
#define BME280_CONFIG_REG_FILTER__MSK			0x1C
#define BME280_CONFIG_REG_FILTER__LEN			3

#define BME280_CONFIG_REG_SPI3_ENABLE__POS		0
#define BME280_CONFIG_REG_SPI3_ENABLE__MSK		0x01
#define BME280_CONFIG_REG_SPI3_ENABLE__LEN		1

/// Data Register
#define BME280_PRESSURE_XLSB_REG_DATA__POS			4
#define BME280_PRESSURE_XLSB_REG_DATA__MSK			0xF0
#define BME280_PRESSURE_XLSB_REG_DATA__LEN			4

#define BME280_TEMPERATURE_XLSB_REG_DATA__POS		4
#define BME280_TEMPERATURE_XLSB_REG_DATA__MSK		0xF0
#define BME280_TEMPERATURE_XLSB_REG_DATA__LEN		4


/******************************************************************************
 * Class
 ******************************************************************************/

//! BME280 Class
/*!
	BME280 Class defines all the variables and functions used to manage BME280 sensor
 */
class BME280
{
	private:

	/// Calibration variables
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;

	uint8_t  dig_H1;
	int16_t dig_H2;
	uint8_t  dig_H3;
	int16_t dig_H4;
	int16_t dig_H5;
	int8_t  dig_H6;

	int32_t t_fine;

	/// INTERNAL COMPENSATION FUNCTIONS
	//! This function compensates the temperature with the calibration data
	/*!
	\param	long uncompensated_temp: uncompensated temperature value
	\return		compensated temperature in ºC
	*/
	float compensateTemp(long uncompensated_temp);

	//! This function compensates the pressure with the calibration data
	/*!
	\param	long uncompensated_pres: uncompensated pressure value
	\return		compensated pressure in Pascals
	*/
	float compensatePres(long uncompensated_pres);

	//! This function compensates the humidity with the calibration data
	/*!
	\param	long uncompensated_hum: uncompensated humidity value
	\return		compensated humidity in %RH
	*/
	float compensateHum(long uncompensated_hum);


	public:

	// Constructors
	BME280();

	/// POWER AND CONFIGURATION FUNCTIONS
	//! This function checks if the module is accesible via I2C and
	//! reads the calibration registers
	/*!
	\return		1 if is OK, 0 if not
	*/
	int8_t ON();

	//! This function checks if the module is accesible via I2C
	/*!
	\return		1 if is accesible, 0 if not
	*/
	int8_t checkID();

	//! This function reads the calibration registers
	/*!
	\return	 	nothing
	*/
	void readCalibration();

	//! This function shows the calibration variables
	/*!
	\return		nothing
	*/
	void showCalibration();

	/// MEASURE FUNCTIONS
	//! This function reads temperature and compensate it
	/*!
	\param	uint8_t over_sample_value: oversamples value for the sensor
					- BME280_OVERSAMP_SKIPPED
					- BME280_OVERSAMP_1X
					- BME280_OVERSAMP_2X
					- BME280_OVERSAMP_4X
					- BME280_OVERSAMP_8X
					- BME280_OVERSAMP_16X
	\param	uint8_t filter_value: filter value for the sensor
					- BME280_FILTER_COEFF_OFF
					- BME280_FILTER_COEFF_2
					- BME280_FILTER_COEFF_4
					- BME280_FILTER_COEFF_8
					- BME280_FILTER_COEFF_16
	\return		The temperature in ºC
				-1000 if comunication error
				-1001 if conversion timeout
	*/
	float getTemperature(uint8_t over_sample_value, uint8_t filter_value);

	//! This function reads pressure and compensate it
	/*!
	\param	uint8_t over_sample_value: oversamples value for the sensor
					- BME280_OVERSAMP_SKIPPED
					- BME280_OVERSAMP_1X
					- BME280_OVERSAMP_2X
					- BME280_OVERSAMP_4X
					- BME280_OVERSAMP_8X
					- BME280_OVERSAMP_16X
	\param	uint8_t filter_value: filter value for the sensor
					- BME280_FILTER_COEFF_OFF
					- BME280_FILTER_COEFF_2
					- BME280_FILTER_COEFF_4
					- BME280_FILTER_COEFF_8
					- BME280_FILTER_COEFF_16
	\return		The pressure in Pascals
				-1000 if comunication error
				-1001 if conversion timeout
	*/
	float getPressure(uint8_t over_sample_value, uint8_t filter_value);

	//! This function reads humidity and compensate it
	/*!
	\param	uint8_t over_sample_value: oversamples value for the sensor
					- BME280_OVERSAMP_SKIPPED
					- BME280_OVERSAMP_1X
					- BME280_OVERSAMP_2X
					- BME280_OVERSAMP_4X
					- BME280_OVERSAMP_8X
					- BME280_OVERSAMP_16X
	\return		The humidity in %RH
				-1000 if comunication error
				-1001 if conversion timeout
	*/
	float getHumidity(uint8_t over_sample_value);



};


extern BME280 BME;

#endif
