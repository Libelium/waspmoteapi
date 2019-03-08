/*! \file OPC_N2.h
    \brief Library for managing the OPC_N2

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
    Implementation:	Marcos Yarza, Alejandro Gállego

*/

/*! \def OPC_N2_h
    \brief The library flag

 */
#ifndef OPC_N2_h
#define OPC_N2_h

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <inttypes.h>
#include <avr/pgmspace.h>

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

// CS pin for the sensor
#define DUST_SENSOR_CS DIGITAL2
#define DUST_SENSOR_POWER DIGITAL1

#define OPC_N2_DEBUG 0
// #define OPC_N2_DEBUG 1

// define print message
#define PRINT_OPC_N2(str)	USB.print(F("[OPC_N2] ")); USB.print(str);

#define OPC_N2_SPI_MODE		0
#define OPC_N2_UART_MODE	1

/// Sensor commands /////////////////////////////////////////////////////////////////
// COMMAND: Set digital pot
const uint8_t SET_DIGITAL_POT PROGMEM = 0x03;
const uint8_t DIGITAL_POT_ON PROGMEM = 0x00;
const uint8_t DIGITAL_POT_OFF PROGMEM = 0x01;


// UNUSED COMMANDS
const uint8_t DIGITAL_POT_SET_LASER_PWR PROGMEM = 0x42;
const uint8_t DIGITAL_POT_SET_FAN_PWR PROGMEM = 0x42;

// COMMAND: Read information string
const uint8_t READ_INFO_STRING PROGMEM = 0x3F;

// COMMAND: Read configuration variables
const uint8_t READ_CONFIG_VAR PROGMEM = 0x3C;

// UNUSED COMMAND
const uint8_t WRITE_CONFIG_VAR PROGMEM = 0x3A;

// COMMAND: Read histogram
const uint8_t READ_HISTOGRAM PROGMEM = 0x30;				// It will reset the histogram too

// UNUSED COMMAND
const uint8_t SAVE_CONFIG PROGMEM = 0x43;

// COMMAND: Read sensor status
const uint8_t CHECK_STATUS PROGMEM = 0xCF;
const uint8_t CHECK_STATUS_READY PROGMEM = 0xF3;



extern volatile uint8_t	pwrGasPRORegister;

/******************************************************************************
 * Class
 ******************************************************************************/

//! WaspOPC_N2 Class
/*!
	WaspOPC_N2 Class defines all the variables and functions used to manage OPC N2 particle sensosr
 */
class WaspOPC_N2 : public WaspUART
{

	/// private methods //////////////////////////
	private:

	#define SENSOR_DUST_UART_SIZE 110
	uint8_t class_buffer[SENSOR_DUST_UART_SIZE];

	//! Variable : status variable from the OPC-N2 module
    /*!
	 * 1 if the sensor is powered and 0 if not
     */
	uint8_t isON;

	//! Variable : working mode
    /*!
	 * 0 if the sensor uses SPI, 1 if uses UART
     */
	bool _mode;

	//! This function checks if the OPC-N2 sensor is ready
	/*!
	\return		0 if not ready
				1 if  ready
	*/
	uint8_t checkStatus();


	//! This function inits the SPI bus to use with OPC-N2 module
	/*!
	\return		nothing
	*/
	void configSPI();


	/// public methods and attributes //////////////////////////
	public:

	/// Variables /////////////////////////////////////////////////////////////

	//! Variable : _binBoundaryValues
    /*!
     */
	uint16_t _binBoundaryValues[15];

	//! Variable : _binParticleVolume
    /*!
     */
	float _binParticleVolume[16];

	//! Variable : _binParticleDensity
    /*!
     */
	float _binParticleDensity[16];

	//! Variable : _binSampleVolumeWeight
    /*!
     */
	float _binSampleVolumeWeight[16];

	//! Variable : _gain
    /*!
	 * Gain Scaling Coefficient
     */
	float _gain;

	//! Variable : _sample
    /*!
	 * Sample Flow Rate
     */
	float _sample;

	//! Variable : _laserDAC
    /*!
	 * Laser DAC value
     */
	uint8_t _laserDAC;

	//! Variable :_fanDAC
    /*!
	 * Fan DAC value
     */
	uint8_t _fanDAC;

	//! Variable : _bin
    /*!
	 * Amount of particles of each bin
     */
	uint32_t _bin[16];

	//! Variable : _temp. This sensor is not available inside the sensor yet
    /*!
	 * Temperature value in Celsius degrees
     */
	float _temp;

	//! Variable : _pressure. This sensor is not available inside the sensor yet
    /*!
	 * Pressure value in Pascals
     */
	float _pressure;

	//! Variable : _periodCount
    /*!
	 * Measure of the histogram's actual sampling period. It is recorded as a
	 * number of 12MHz clock cycles.
     */
	uint32_t _periodCount;

	//! Variable : _bin1_MToF
    /*!
	 * average amount of time that particles sized in the stated bin took to
	 * cross the OPS's laser beam. Each value is in us multiplied by 3.
     */
	uint8_t _bin1_MToF;

	//! Variable : _bin3_MToF
    /*!
	 * average amount of time that particles sized in the stated bin took to
	 * cross the OPS's laser beam. Each value is in us multiplied by 3.
     */
	uint8_t _bin3_MToF;

	//! Variable : _bin5_MToF
    /*!
	 * average amount of time that particles sized in the stated bin took to
	 * cross the OPS's laser beam. Each value is in us multiplied by 3.
     */
	uint8_t _bin5_MToF;

	//! Variable : _bin7_MToF
    /*!
	 * average amount of time that particles sized in the stated bin took to
	 * cross the OPS's laser beam. Each value is in us multiplied by 3.
     */
	uint8_t _bin7_MToF;

	//! Variable : _PM1
    /*!
	 * PM 1 in µg/m3
     */
	float _PM1;

	//! Variable : _PM2_5
    /*!
	 * PM 2'5 in µg/m3
     */
	float _PM2_5;

	//! Variable : _PM10
    /*!
	 * PM 10 in µg/m3
     */
	float _PM10;


	WaspOPC_N2();

	/// Funtions ///////////////////////////////////////////////////////////////
	//! This function opens UART port and powers the sensor
	/*!
	\return		0 if the sensor doesn't init correctly
				1 if init OK
	*/
	uint8_t ON();

	//! This function opens desired communication port and powers the sensor
    /*!
	 *
	\param	bool com_mode: 0 if the sensor uses SPI, 1 if uses UART
	\return		0 if the sensor doesn't init correctly
				1 if init OK
	*/
	uint8_t ON(bool com_mode);

	//! This function closes SPI port and powers OFF the sensor
	/*!
	\return		0 if the sensor doesn't power off correctly
				1 if powers off correctly
	*/
	uint8_t OFF();

	//! This function closes SPI port and powers OFF the sensor
	/*!
	\return		0 if the sensor doesn't power off correctly
				1 if powers off correctly
	*/
	uint8_t OFF_UART();

	//! This function reads the information string from OPC-N2 sensor
	/*!
	\param	char* buffer: string pointer to store the information data
	\return		1 if OK
				-1 if error sending the command
	*/
	int8_t getInfoString(char* buffer);

	//! This function switchs the fan and the laser ON or OFF
	/*!
	\param	uint8_t mode: DIGITAL_POT_ON or DIGITAL_POT_OFF
	\return		1 if OK
				-1 if error sending the command
				-2 if error receiving data
	*/
	int8_t setDigitalPot(uint8_t mode);

	/*! This function reads the histogram from OPC-N2 sensor module.
	 * It will reset the histogram too. Next variables will be updated:
	 * 				_bin[16]
	 * 				_temp
	 * 				_pressure
	 * 				_periodCount
	 * 				_bin1_MToF
	 * 				_bin3_MToF
	 * 				_bin5_MToF
	 * 				_bin7_MToF
	 * 				_PM1
	 * 				_PM2_5
	 * 				_PM10
	 */
	/*!
	\return		1 if OK
				-1 if error sending the command
				-2 if error receiving data (CRC)
	*/
	int8_t getHistogramData();

	/*! This function reads configuration data from OPC-N2 sensor module.
	 * The next variables will be updated:
	 * 		_binBoundaryValues[15]
	 * 		_binParticleVolume[16]
	 * 		_binParticleDensity[16]
	 * 		_binSampleVolumeWeight[16]
	 * 		_gain
	 * 		_sample
	 * 		_laserDAC
	 * 		_fanDAC
	 */
	/*!
	\return		1 if OK
				-1 if error sending the command
	*/
	int8_t getConfigVar();

	/*! This function gets PM values (PM1, PM2_5 and PM10)
	 * Next variables will be updated:
	 * 				_bin[16]
	 * 				_temp
	 * 				_pressure
	 * 				_periodCount
	 * 				_bin1_MToF
	 * 				_bin3_MToF
	 * 				_bin5_MToF
	 * 				_bin7_MToF
	 * 				_PM1
	 * 				_PM2_5
	 * 				_PM10
	 */
	/*!
	\param	uint32_t timeSample: time sampling the air in milliseconds
	\return		1 if OK
				-1 if error sending the command digital pot on
				-2 if error receiving data
				-3 if error sending the command read histogram
				-4 if error receiving data
				-5 if error sending the command read histogram
				-6 if error receiving data
				-7 if error sending the command digital pot off
				-8 if error receiving data
	*/
	int8_t getPM(uint32_t timeSample);

		/*! This function gets PM values (PM1, PM2_5 and PM10)
	 * Next variables will be updated:
	 * 				_bin[16]
	 * 				_temp
	 * 				_pressure
	 * 				_periodCount
	 * 				_bin1_MToF
	 * 				_bin3_MToF
	 * 				_bin5_MToF
	 * 				_bin7_MToF
	 * 				_PM1
	 * 				_PM2_5
	 * 				_PM10
	 */
	/*!
	\param	uint32_t waitSample: time with the fan on without sampling the air in milliseconds
	\param	uint32_t timeSample: time sampling the air in milliseconds
	\return		1 if OK
				-1 if error sending the command digital pot on
				-2 if error receiving data
				-3 if error sending the command read histogram
				-4 if error receiving data
				-5 if error sending the command read histogram
				-6 if error receiving data
				-7 if error sending the command digital pot off
				-8 if error receiving data
	*/
	int8_t getPM(uint32_t waitSample, uint32_t timeSample);

};

extern WaspOPC_N2 OPC_N2;

#endif
