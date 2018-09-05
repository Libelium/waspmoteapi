/*! \file TurbiditySensor.cpp
	\brief Library for managing the Smart Water Turbidity Sensor

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

	Version:			4.1
	Design:				David Gascón
	Implementation:		Ahmad Saad & Luis Miguel Marti
*/


/***********************************************************************
 * Includes
 ***********************************************************************/
#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "TurbiditySensor.h"

/***********************************************************************
 * Class contructors
 ***********************************************************************/
turbidityClass::turbidityClass()
{
	_sensorAddress = DEFAULT_ADDRESS;
}


/***********************************************************************
 * Class contructors
 ***********************************************************************/
turbidityClass::turbidityClass(uint8_t address)
{
	// The sensor comes from factory with a default address
	// This direction can be changed using the function configureSensorAddress
	_sensorAddress = address;
}

/***********************************************************************
 * Methods of the Class
 ***********************************************************************/

//!*************************************************************
//!	Name:	ON()
//!	Description: Powers and configures the turbidity sensor
//!	Param : void
//!	Returns: "0" if no error, "-1" if error
//!*************************************************************
uint8_t turbidityClass::ON()
{

	uint8_t result;

	delay(10);

	if (_boot_version < 'H')
	{
		sensor = ModbusMaster(RS485_COM, _sensorAddress);

		// The sensor uses 9600 bps speed communication
		sensor.begin(9600);

		// Switch ON the power supply
		PWR.setSensorPower(SENS_5V, SENS_ON);
		delay(100);
		WaspRegister |= REG_RS485;

		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Sensor configured in Waspmote v12"));
		#endif
	}
	else
	{
		sensor = ModbusMaster(RS232_COM, _sensorAddress);

		// The sensor uses 9600 bps speed communication
		sensor.begin(9600, 1);

		// set Auxiliar1 socket
		Utils.setMuxAux1();

		// Switch ON the power supply
		PWR.setSensorPower(SENS_5V, SENS_ON);
		WaspRegister |= REG_SOCKET1;

		// Turbidity Sensor ON
		pinMode(PWR_TURBIDITY, OUTPUT);
		digitalWrite(PWR_TURBIDITY, HIGH);
		delay(100);

		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Sensor configured in Waspmote v15"));
		#endif
	}

	delay(1000);

	return result;
}


//!*************************************************************
//!	Name:	OFF()
//!	Description: Powers OFF the turbidity sensor
//!	Param : void
//!	Returns: void
//!*************************************************************
void turbidityClass::OFF()
{
	if (_boot_version >= 'H')
	{
		// Turbidity Sensor OFF
		pinMode(PWR_TURBIDITY, OUTPUT);
		digitalWrite(PWR_TURBIDITY, LOW);
	}
}


//!*************************************************************
//!	Name:	getTurbidity()
//!	Description: Returns the stored value of the turbidity
//!	Param : void
//!	Returns: The turbidity value
//!*************************************************************
float turbidityClass::getTurbidity()
{
	uint8_t status = -1;
	uint8_t retries = 0;

	sensor.setTransmitBuffer(1, 0x00);
	sensor.setTransmitBuffer(0, 0x1F);

	delay(100);

	while ((status !=0) && (retries < 5))
	{

		delay(50);
		retries++;
		status =  sensor.writeMultipleRegisters(NEW_MEAS_REG, 0x01);

		#if DEBUG_TURBIDITY > 0
			PRINT_TURBIDITY(F("STATUS: "));
			PRINTLN_TURBIDITY_VAL(status);
		#endif
	}

	// Important delay
	delay(1000);


	if (status == 0)
	{
		status = -1;
		retries = 0;

		while ((status !=0) && (retries < 10))
		{
			status = sensor.readHoldingRegisters(MEASUREMENT_STATUS, 0x0B);
			retries++;
		}

		if (status == 0)
		{
			foo.ints[0] = sensor.getResponseBuffer(4);
			foo.ints[1] = sensor.getResponseBuffer(3);

			_turbidityNTU = foo.toFloat;
		}
		else
		{
			// If no response from the slave, print an error message.
			#if DEBUG_TURBIDITY > 0
				PRINTLN_TURBIDITY(F("Communication error reading parameters"));
			#endif
		}
	}
	else
	{
		// If no response from the slave, print an error message.
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication error (Writing Multiple Registers)"));
		#endif

		//if readTurbidity function fails return -1000
		return -1000.0;
	}

	sensor.clearResponseBuffer();

	// negative values aren't usefull so return zeros
	// if sensor returns zeros (negative values) is might be badly placed
	if (_turbidityNTU<0.0)
	{
		_turbidityNTU = 0.0;
	}

	return _turbidityNTU;
}


//!*************************************************************
//!	Name:	getConcentration()
//!	Description: Returns the stored value of the turbidity
//!	Param : void
//!	Returns: The turbidity value
//!*************************************************************
float turbidityClass::getConcentration()
{
	uint8_t status = -1;
	uint8_t retries = 0;

	sensor.setTransmitBuffer(1, 0x00);
	sensor.setTransmitBuffer(0, 0x1F);

	while ((status !=0) && (retries < 5))
	{

		delay(10);
		retries++;
		status =  sensor.writeMultipleRegisters(NEW_MEAS_REG, _sensorAddress);

		#if DEBUG_TURBIDITY > 0
			PRINT_TURBIDITY(F("STATUS: "));
			PRINTLN_TURBIDITY_VAL(status);
		#endif
	}

	// Important delay
	delay(1000);


	if (status == 0)
	{
		status = -1;
		retries = 0;

		while ((status !=0) && (retries < 10))
		{
			status = sensor.readHoldingRegisters(MEASUREMENT_STATUS, 0x0B);
			retries++;
		}

		if (status == 0)
		{
			foo.ints[0] = sensor.getResponseBuffer(8);
			foo.ints[1] = sensor.getResponseBuffer(7);

			_turbidityMGL = foo.toFloat;
		}
		else
		{
			// If no response from the slave, print an error message.
			#if DEBUG_TURBIDITY > 0
				PRINTLN_TURBIDITY(F("Communication error reading parameters"));
			#endif
		}
	}
	else
	{
		// If no response from the slave, print an error message.
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication error (Writing Multiple Registers)"));
		#endif

		//if readTurbidity function fails return -1000
		return -1000.0;
	}

	sensor.clearResponseBuffer();

	// negative values aren't usefull so return zeros
	// if sensor returns zeros (negative values) is might be badly placed
	if (_turbidityMGL<0.0)
	{
		_turbidityMGL = 0.0;
	}

	return _turbidityMGL;
}


//!*************************************************************
//!	Name:	getConcentration()
//!	Description: Returns the stored value of the turbidity
//!	Param : void
//!	Returns: The turbidity value
//!*************************************************************
float turbidityClass::getValues()
{
	uint8_t status = -1;
	uint8_t retries = 0;

	sensor.setTransmitBuffer(1, 0x00);
	sensor.setTransmitBuffer(0, 0x1F);

	while ((status !=0) && (retries < 5))
	{

		delay(10);
		retries++;
		status =  sensor.writeMultipleRegisters(NEW_MEAS_REG, _sensorAddress);

		#if DEBUG_TURBIDITY > 0
			PRINT_TURBIDITY(F("STATUS: "));
			PRINTLN_TURBIDITY_VAL(status);
		#endif
	}

	// Important delay
	delay(1000);


	if (status == 0)
	{
		status = -1;
		retries = 0;

		while ((status !=0) && (retries < 10))
		{
			status = sensor.readHoldingRegisters(MEASUREMENT_STATUS, 0x0B);
			retries++;
		}

		if (status == 0)
		{
			foo.ints[0] = sensor.getResponseBuffer(2);
			foo.ints[1] = sensor.getResponseBuffer(1);

			_temperature = foo.toFloat;

			foo.ints[0] = sensor.getResponseBuffer(4);
			foo.ints[1] = sensor.getResponseBuffer(3);

			_turbidityNTU = foo.toFloat;

			foo.ints[0] = sensor.getResponseBuffer(8);
			foo.ints[1] = sensor.getResponseBuffer(7);

			_turbidityMGL = foo.toFloat;
		}
		else
		{
			// If no response from the slave, print an error message.
			#if DEBUG_TURBIDITY > 0
				PRINTLN_TURBIDITY(F("Communication error reading parameters"));
			#endif
		}
	}
	else
	{
		// If no response from the slave, print an error message.
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication error (Writing Multiple Registers)"));
		#endif

		return 1;
	}

	sensor.clearResponseBuffer();

	// negative values aren't usefull so return zeros
	// if sensor returns zeros (negative values) is might be badly placed
	if (_temperature<0.0)
	{
		_temperature = 0.0;
		return 1;
	}

	if (_turbidityNTU<0.0)
	{
		_turbidityNTU = 0.0;
		return 1;
	}

	if (_turbidityMGL<0.0)
	{
		_turbidityMGL = 0.0;
		return 1;
	}

	return 0;
}


//!*************************************************************
//!	Name:	getTemperature()
//!	Description: Returns the value of the temperature
//!	Param : void
//!	Returns: The temperature value
//!*************************************************************
float turbidityClass::getTemperature()
{
	uint8_t status = -1;
	uint8_t retries = 0;

	sensor.setTransmitBuffer(1, 0x00);
	sensor.setTransmitBuffer(0, 0x1F);

	while ((status !=0) && (retries < 5))
	{

		delay(10);
		retries++;
		status =  sensor.writeMultipleRegisters(NEW_MEAS_REG, 0x01);

		#if DEBUG_TURBIDITY > 0
			PRINT_TURBIDITY(F("STATUS: "));
			PRINTLN_TURBIDITY_VAL(status);
		#endif
	}

	// Important delay
	delay(1000);


	if (status == 0)
	{
		status = -1;
		retries = 0;

		while ((status !=0) && (retries < 10))
		{
			status = sensor.readHoldingRegisters(MEASUREMENT_STATUS, 0x0B);
			retries++;
		}

		if (status == 0)
		{
			foo.ints[0] = sensor.getResponseBuffer(2);
			foo.ints[1] = sensor.getResponseBuffer(1);

			_temperature = foo.toFloat;
		}
		else
		{
			// If no response from the slave, print an error message.
			#if DEBUG_TURBIDITY > 0
				PRINTLN_TURBIDITY(F("Communication error reading parameters"));
			#endif
		}
	}
	else
	{
		// If no response from the slave, print an error message.
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication error (Writing Multiple Registers)"));
		#endif

		//if readTurbidity function fails return -1000
		return -1000.0;
	}

	sensor.clearResponseBuffer();

	// negative values aren't usefull so return zeros
	// if sensor returns zeros (negative values) is might be badly placed
	if (_temperature<0.0)
	{
		_temperature = 0.0;
	}

	return _temperature;
}


//!*************************************************************
//!	Name:	getInfo()
//!	Description: Gets the information of the sensor
//!	Param : void
//!	Returns: "0" if no error, "-1" if error
//!*************************************************************
uint8_t turbidityClass::getSerialNumber()
{
	uint8_t result = sensor.readHoldingRegisters(SERIAL_NUMBER_REG, 16);
	uint8_t j = 0;

	if (result == 0)
	{

		for (int i=0; i<8; i++)
		{
			serialNum[j++] = sensor.getResponseBuffer(i) & 0xFF;
			serialNum[j++] = sensor.getResponseBuffer(i) >>8 & 0xFF;
		}
	}
	else
	{
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Error! No response from slave"));
		#endif
	}

	return result;
}

//!*************************************************************
//!	Name:	average()
//!	Description: Configure the average value
//!	Param : void
//!	Returns: void
//!*************************************************************
uint8_t turbidityClass::average(uint8_t avg)
{
	uint8_t status = -1;
	uint8_t retries = 0;

	if (avg > 50) avg = 50;

	sensor.setTransmitBuffer(1, 0x00);
	sensor.setTransmitBuffer(0, avg);

	while ((status !=0) && (retries < 5))
	{
		status = sensor.writeMultipleRegisters(AVRG_PARA_REG, _sensorAddress);

		delay(10);
		retries++;
	}

	// Check that the direction has been well written
	if (status == 0)
	{
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Average configured..."));
		#endif
		return 0;
	}
	else

	{
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication Error. Average not configured."));
		#endif
		return 1;
	}
}


//!*************************************************************
//!	Name:	configureSensorAddress()
//!	Description: Configure the address of the sensor
//!	Param : address: the address to configure
//!	Returns: void
//!*************************************************************
uint8_t turbidityClass::configureSensorAddress(uint8_t address)
{
	uint8_t result = -1;
	uint8_t retries = 0;

	sensor.setTransmitBuffer(1, 0x00);
	sensor.setTransmitBuffer(0, address);

	while ((result !=0) && (retries < 5))
	{
		retries ++;
		// Asign the address to the sensor
		result = sensor.writeMultipleRegisters(ADDRESS_REG, _sensorAddress);
		delay(50);
	}

	if (result == 0)
	{
		#if DEBUG_TURBIDITY > 0
			// If no response from the slave, print an error message
			PRINTLN_TURBIDITY(F("Address well configured"));
		#endif

		// Save the new slave address
		_sensorAddress = address;
		// Use the new address of the sensor
		sensor.setSlaveAddress(_sensorAddress);

		return 0;
	}
	else
	{
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication Error. Address not configured."));
		#endif

		return 1;
	}

	sensor.clearResponseBuffer();
}


//!*************************************************************
//!	Name:	clearBuffer()
//!	Description: Flushes the buffers.
//!	Param : void
//!	Returns: void
//!*************************************************************
void turbidityClass::clearBuffer()
{
	// Clear Response Buffer
	sensor.clearResponseBuffer();
	sensor.clearTransmitBuffer();
	delay(10);
}
