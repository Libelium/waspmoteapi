/*
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
 *  Version:		3.7
 *  Design:			David Gascón
 *  Implementation: Alejandro Gállego, Ahmad Saad
 */


#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspSensorCities_PRO.h"

// Constructors ///////////////////////////////////////////////////////////

/*!
 * @brief It initializes the different digital pins
 * @param void
 * @return void
 */
WaspSensorCitiesPRO::WaspSensorCitiesPRO()
{
	// I2C main pin
	pinMode(SCP_I2C_MAIN_EN, OUTPUT);
	digitalWrite(SCP_I2C_MAIN_EN, LOW);

	// switch off socket 3v3/i2c isolators
	pinMode(SCP_PWR_3V3_SOCKET_1_C, OUTPUT);
	pinMode(SCP_PWR_3V3_SOCKET_2_E, OUTPUT);
	pinMode(SCP_PWR_3V3_SOCKET_3_F, OUTPUT);
	pinMode(SCP_PWR_3V3_SOCKET_4_A, OUTPUT);
	pinMode(SCP_PWR_3V3_SOCKET_5_B, OUTPUT);
	digitalWrite(SCP_PWR_3V3_SOCKET_1_C, LOW);
	digitalWrite(SCP_PWR_3V3_SOCKET_2_E, LOW);
	digitalWrite(SCP_PWR_3V3_SOCKET_3_F, LOW);
	digitalWrite(SCP_PWR_3V3_SOCKET_4_A, LOW);
	digitalWrite(SCP_PWR_3V3_SOCKET_5_B, LOW);

	// disable probe i2c lines
	pinMode(SCP_I2C_SOCKET_1_C, OUTPUT);
	pinMode(SCP_I2C_SOCKET_3_F, OUTPUT);
	pinMode(SCP_I2C_SOCKET_5_B, OUTPUT);
	digitalWrite(SCP_I2C_SOCKET_1_C, LOW);
	digitalWrite(SCP_I2C_SOCKET_3_F, LOW);
	digitalWrite(SCP_I2C_SOCKET_5_B, LOW);

	// switch off all probe power lines
	pinMode(SCP_PWR_SOCKET_1_C, OUTPUT);
	pinMode(SCP_PWR_SOCKET_3_F, OUTPUT);
	pinMode(SCP_PWR_SOCKET_5_B, OUTPUT);
	digitalWrite(SCP_PWR_SOCKET_1_C, HIGH);
	digitalWrite(SCP_PWR_SOCKET_3_F, HIGH);
	digitalWrite(SCP_PWR_SOCKET_5_B, HIGH);

	// update Waspmote Control Register
	WaspRegisterSensor |= REG_CITIES_PRO;
	pwrCitiesPRORegister = 0;
	pwrGasPRORegister = 0;
}

// Private Methods ////////////////////////////////////////////////////////


// Public Methods //////////////////////////////////////////////////////////////


/*!
 * @brief Turns ON the sensor/socket
 * @param uint8_t socket_sensor:
 * 		@arg SOCKET_1
 * 		@arg SOCKET_2
 * 		@arg SOCKET_3
 * 		@arg SOCKET_4
 * 		@arg SOCKET_5
 * 		@arg SOCKET_A
 * 		@arg SOCKET_B
 * 		@arg SOCKET_C
 * 		@arg SOCKET_E
 * 		@arg SOCKET_F
 * @return void
 */
void WaspSensorCitiesPRO::ON(uint8_t socket_sensor)
{
	// Power on 3V3 and/or 5V if necessary
	if ((WaspRegister & REG_3V3) == 0)
	{
		#if DEBUG_CITIES_PRO>0
			PRINTLN_CITIES_PRO(F("3V3 to ON"));
		#endif
		PWR.setSensorPower(SENS_3V3, SENS_ON);
		digitalWrite(SCP_I2C_MAIN_EN, HIGH);	// I2C main pin
	}

	switch(socket_sensor)
	{
		case SOCKET_1:
		case SOCKET_C:
			pwrCitiesPRORegister |= (1 << 0x01);
			digitalWrite(SCP_PWR_3V3_SOCKET_1_C, HIGH);
			break;

		case SOCKET_2:
		case SOCKET_E:
			pwrCitiesPRORegister |= (1 << 0x02);
			digitalWrite(SCP_PWR_3V3_SOCKET_2_E, HIGH);
			break;

		case SOCKET_3:
		case SOCKET_F:
			pwrCitiesPRORegister |= (1 << 0x03);
			digitalWrite(SCP_PWR_3V3_SOCKET_3_F, HIGH);
			break;

		case SOCKET_4:
		case SOCKET_A:
			pwrCitiesPRORegister |= (1 << 0x04);
			digitalWrite(SCP_PWR_3V3_SOCKET_4_A, HIGH);
			break;

		case SOCKET_5:
		case SOCKET_B:
			pwrCitiesPRORegister |= (1 << 0x05);
			digitalWrite(SCP_PWR_3V3_SOCKET_5_B, HIGH);
			break;

		default:
			break;
	}

	#if DEBUG_CITIES_PRO>1
		PRINT_CITIES_PRO(F("pwrCitiesPRORegister="));
		USB.println(pwrCitiesPRORegister, BIN);
		PRINT_CITIES_PRO(F("pwrGasPRORegister="));
		USB.println(pwrGasPRORegister, BIN);
	#endif

}

/*!
 * @brief Turns OFF the sensor/socket
 * @param uint8_t socket_sensor:
 * 		@arg SOCKET_1
 * 		@arg SOCKET_2
 * 		@arg SOCKET_3
 * 		@arg SOCKET_4
 * 		@arg SOCKET_5
 * 		@arg SOCKET_A
 * 		@arg SOCKET_B
 * 		@arg SOCKET_C
 * 		@arg SOCKET_E
 * 		@arg SOCKET_F
 * @return void
 */
void WaspSensorCitiesPRO::OFF(uint8_t socket_sensor)
{
	uint8_t mask;

	// Check I2C isolator
	if ((pwrCitiesPRORegister == 0) && ((pwrGasPRORegister & 0xFE) == 0))
	{
		// Disable I2C isolator
		digitalWrite(SCP_I2C_MAIN_EN, LOW);
	}

	switch(socket_sensor)
	{

		case SOCKET_1:
		case SOCKET_C:
			digitalWrite(SCP_PWR_3V3_SOCKET_1_C, LOW);

			// Set the flags
			pwrCitiesPRORegister &= ~(1 << 0x01);
			break;

		case SOCKET_2:
		case SOCKET_E:
			digitalWrite(SCP_PWR_3V3_SOCKET_2_E, LOW);

			// Set the flags
			pwrCitiesPRORegister &= ~(1 << 0x02);
			break;

		case SOCKET_3:
		case SOCKET_F:
			digitalWrite(SCP_PWR_3V3_SOCKET_3_F, LOW);

			// Set the flags
			pwrCitiesPRORegister &= ~(1 << 0x03);
			break;

		case SOCKET_4:
		case SOCKET_A:
			digitalWrite(SCP_PWR_3V3_SOCKET_4_A, LOW);

			// Set the flags
			pwrCitiesPRORegister &= ~(1 << 0x04);
			break;

		case SOCKET_5:
		case SOCKET_B:
			digitalWrite(SCP_PWR_3V3_SOCKET_5_B, LOW);

			// Set the flags
			pwrCitiesPRORegister &= ~(1 << 0x05);
			break;

		default:
			break;
	}
	#if DEBUG_CITIES_PRO>1
		PRINT_CITIES_PRO(F("pwrCitiesPRORegister="));
		USB.println(pwrCitiesPRORegister, BIN);
		PRINT_CITIES_PRO(F("pwrGasPRORegister="));
		USB.println(pwrGasPRORegister, BIN);
	#endif

	if ((pwrGasPRORegister == 0x00) &&
		(pwrCitiesPRORegister == 0x00) &&
		((WaspRegister & REG_3V3) != 0))
	{
		#if DEBUG_CITIES_PRO>0
			PRINTLN_CITIES_PRO(F("3V3 to OFF"));
		#endif
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}
}

WaspSensorCitiesPRO SensorCitiesPRO=WaspSensorCitiesPRO();


//************************************************************************************
// Noise Sensor Class functions
//************************************************************************************

/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
noiseSensor::noiseSensor()
{
	// store the UART to be used
	_uart = 0x01;
	_baudrate = 115200;
	_def_delay = 50;
	
	// assign class pointer to UART buffer
	_buffer = class_buffer;
	_bufferSize = SENSOR_NOISE_UART_SIZE;
}


/*!
 * @brief	Get a new measure of SPLA
 * @param
 * @return	uint8_t: Status of the last communication
 */
uint8_t noiseSensor::getSPLA(void)
{
	getSPLA(FAST_MODE);
}


/*!
 * @brief	Get a new measure of SPLA
 * @param
 * @return	uint8_t: Status of the last communication
 */
uint8_t noiseSensor::getSPLA(uint8_t mode)
{
	uint8_t status;

	if (mode == SLOW_MODE)
	{
		// Send command for getting a new measure
		status = sendCommand("ATSLOW", "OK", 5000);
	}
	else
	{
		// Send command for getting a new measure
		status = sendCommand("ATFAST", "OK", 5000);
	}

	// Request 8 bytes from the UART buffer
	readBuffer(7, 1);

	if (status == 0)
	{
		#if DEBUG_CITIES_PRO > 0
			PRINTLN_CITIES_PRO(F("Timeout: No response from the Noise Sensor"));
		#endif

		return -1;
	}
	else
	{
		status = parseFloat(&SPLA, "\r\n");

		if (status == 0)
		{
			#if DEBUG_CITIES_PRO > 1
				PRINTLN_CITIES_PRO(F("Successful communication. Value stored in SPLA variable."));
				PRINTLN_CITIES_PRO(F("Value Stored in SPLA: "));
				PRINTLN_CITIES_PRO_VAL(SPLA);
			#endif

			return status;
		}
		else
		{
			#if DEBUG_CITIES_PRO > 0
				PRINTLN_CITIES_PRO(F("Wrong response. Can't read data."));
			#endif
		}

		return status;
	}
}


/*!
 * @brief	Configure the UART for communicating with the sensor
 * @param 	void
 * @return	void
 */
void noiseSensor::configure()
{
	// open mcu uart
	beginUART();
	// set Auxiliar1 socket
	Utils.setMuxAux1();
	// flush uart
	serialFlush(_uart);
}

// Instance of the class
noiseSensor noise = noiseSensor();






//******************************************************************************
// BME Sensor Class functions
//******************************************************************************

/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
bmeCitiesSensor::bmeCitiesSensor(uint8_t socket)
{
	_socket = socket;
}



/*!
 * @brief	switch on the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void bmeCitiesSensor::ON()
{
	WaspSensorCitiesPRO::ON(_socket);

	// switch ON I2C
	digitalWrite(SCP_I2C_MAIN_EN, HIGH);

	// init BME
	BME.ON();
}



/*!
 * @brief	switch off the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void bmeCitiesSensor::OFF()
{
	WaspSensorCitiesPRO::OFF(_socket);
	delay(100);
}


/*!
 *  @brief Read BME temperature value
 *  @return	temperature value
 *
 */
float bmeCitiesSensor::getTemperature()
{
	float value = 0;
	uint8_t error;
	uint8_t retries;

	// switch ON I2C
	digitalWrite(SCP_I2C_MAIN_EN, HIGH);

	///////////////////////////////////////////////////////////////////
	// configure the BME280 Sensor (Temperature, Humidity and Pressure)
	///////////////////////////////////////////////////////////////////
	retries = 3;
	do
	{
		error = BME.ON();
		retries--;

		if (error != 1)
		{
			I2C.recover();
		}
	} while ((error != 1) && (retries > 0));

	delay(100);

	///////////////////////////////////////////////////////////////////
	// read temperature	from the BME280 Sensor
	///////////////////////////////////////////////////////////////////
	retries = 3;
	do
	{
		value = BME.getTemperature(BME280_OVERSAMP_1X, 0);
		retries--;

		if (value == -1000.0)
		{
			I2C.recover();
		}
	} while ((value != -1000.0) && (retries > 0));

	#if DEBUG_CITIES_PRO>0
		PRINT_CITIES_PRO(F("Temperature:"));
		USB.println(value);
		PRINT_CITIES_PRO(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);
	#endif

	delay(100);

	return value;
}


/*!
 *  @brief Read BME humidity value
 *  @return	humidity value
 *
 */
float bmeCitiesSensor::getHumidity()
{
	float value = 0;
	uint8_t error;
	uint8_t retries;

	// switch ON I2C
	digitalWrite(SCP_I2C_MAIN_EN, HIGH);

	///////////////////////////////////////////////////////////////////
	// configure the BME280 Sensor (Temperature, Humidity and Pressure)
	///////////////////////////////////////////////////////////////////
	retries = 3;
	do
	{
		error = BME.ON();
		retries--;

		if (error != 1)
		{
			I2C.recover();
		}
	} while ((error != 1) && (retries > 0));

	delay(100);

	///////////////////////////////////////////////////////////////////
	// read the humidity from the BME280 Sensor
	///////////////////////////////////////////////////////////////////
	retries = 3;
	do
	{
		value = BME.getHumidity(BME280_OVERSAMP_1X);
		retries--;

		if (value == -1000.0)
		{
			I2C.recover();
		}
	} while ((value != -1000.0) && (retries > 0));

	#if DEBUG_CITIES_PRO>0
		PRINT_CITIES_PRO(F("Humidity:"));
		USB.println(value);
		PRINT_CITIES_PRO(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);
	#endif
	delay(100);

	return value;
}


/*!
 *  @brief Read BME pressure value
 *  @return	pressure value
 *
 */
float bmeCitiesSensor::getPressure()
{
	float value = 0;
	uint8_t error;
	uint8_t retries;

	// switch ON I2C
	digitalWrite(SCP_I2C_MAIN_EN, HIGH);

	///////////////////////////////////////////////////////////////////
	// configure the BME280 Sensor (Temperature, Humidity and Pressure)
	///////////////////////////////////////////////////////////////////
	retries = 3;
	do
	{
		error = BME.ON();
		retries--;

		if (error != 1)
		{
			I2C.recover();
		}
	} while ((error != 1) && (retries > 0));

	delay(100);

	///////////////////////////////////////////////////////////////////
	// read the pressure from the BME280 Sensor
	///////////////////////////////////////////////////////////////////
	retries = 3;
	do
	{
		value = BME.getPressure(BME280_OVERSAMP_1X, 0);
		retries--;

		if (value == -1000.0)
		{
			I2C.recover();
		}
	} while ((value != -1000.0) && (retries > 0));


	#if DEBUG_CITIES_PRO>0
		PRINT_CITIES_PRO(F("Pressure:"));
		USB.println(value);
		PRINT_CITIES_PRO(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);
	#endif

	delay(100);

	return value;
}






//******************************************************************************
// Ultrasound Sensor Class functions
//******************************************************************************

/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
ultrasoundCitiesSensor::ultrasoundCitiesSensor(uint8_t socket)
{
	_socket = socket;
}



/*!
 * @brief	switch on the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void ultrasoundCitiesSensor::ON()
{
	WaspSensorCitiesPRO::ON(_socket);
	delay(500);
}



/*!
 * @brief	switch off the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void ultrasoundCitiesSensor::OFF()
{
	WaspSensorCitiesPRO::OFF(_socket);
	delay(100);
}


/*!
 * @brief 	This function performs a distance measurement
 * @return 	distance in cm.
 * 		  	9000 if error reading the distance
 * 			10000 if error reading the sensor
 */
uint16_t ultrasoundCitiesSensor::getDistance()
{
	return Ultrasound.getDistance();
}






//******************************************************************************
// Luxes Sensor Class functions
//******************************************************************************

/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
luxesCitiesSensor::luxesCitiesSensor(uint8_t socket)
{
	_socket = socket;
}



/*!
 * @brief	switch on the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void luxesCitiesSensor::ON()
{
	WaspSensorCitiesPRO::ON(_socket);
	delay(100);

	// init luxes sensor
	TSL.ON();
}



/*!
 * @brief	switch off the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void luxesCitiesSensor::OFF()
{
	WaspSensorCitiesPRO::OFF(_socket);

	// switch off delay for better preformance before
	// entering sleep mode after calling this function
	delay(100);
}


/*!
 * @brief 	This function performs a luxes measurement
 * @return 	luxes if ok
 * 			-1 if error
 */
uint32_t luxesCitiesSensor::getLuminosity()
{
  return getLuminosity(TSL2561_GAIN_1, TSL2561_HIGH_RES);
}

/*!
 * @brief 	This function performs a luxes measurement
 * @return 	luxes if ok
 * 			-1 if error
 */
uint32_t luxesCitiesSensor::getLuminosity(bool gain)
{
  return getLuminosity(gain, TSL2561_HIGH_RES);
}

/*!
 * @brief 	This function performs a luxes measurement
 * @param   Resolution. Available options: TSL2561_HIGH_RES,
 *          TSL2561_MED_RES, TSL2561_LOW_RES
 * @return 	luxes if ok
 * 			-1 if error
 */
uint32_t luxesCitiesSensor::getLuminosity(bool gain, uint8_t res)
{
	uint8_t error;
	uint8_t retries = 3;

	do
	{
		// get luminosity
		error = TSL.getLuminosity(res, gain);

		if (error == 0)
		{
			return TSL.lux;
		}
		retries--;
		I2C.recover();
	}
	while(retries > 0);

	return (uint32_t)-1;
}
