/*!	\file WaspSensorXtr.cpp
	\brief Library for managing the Xtreme sensor boards

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
	Implementation: Victor Boria, Javier Siscart

*/

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif


#include "WaspSensorXtr.h"



/// Command table ////////////////////////////////////////////

const char string_00[] PROGMEM = "";
const char string_01[] PROGMEM = "";
const char string_02[] PROGMEM = "";
const char string_03[] PROGMEM = "";
const char string_04[] PROGMEM = "";
const char string_05[] PROGMEM = "";
const char string_06[] PROGMEM = "WARNING - Redefinition of sensor socket detected";
const char string_07[] PROGMEM = "WARNING - The following sensor can not work in the defined socket: ";
const char string_08[] PROGMEM = "sensor not detected";
const char string_09[] PROGMEM = "invalid data";
const char string_10[] PROGMEM = "socket (!): ";
const char string_11[] PROGMEM = "WARNING - Not possible to turn on two sensors at the same time: ";
const char string_12[] PROGMEM = "%c %s %s %c %s %s %s %s %s %s";							//GMX100 frame format
const char string_13[] PROGMEM = "%c %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX101 frame format
const char string_14[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX200 frame format
const char string_15[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %s %s %s"; //GMX240 frame format
const char string_16[] PROGMEM = "%c %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX300 frame format
const char string_17[] PROGMEM = "%c %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX301 frame format
const char string_18[] PROGMEM = "%c %s %s %s %d %s %s %s %s %s %c %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX400 frame format
const char string_19[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX500 frame format
const char string_20[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX501 frame format
const char string_21[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %d %s %s %s %d %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX531 GMX541 GMX551 frame format
const char string_22[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX550 frame format
const char string_23[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX600 frame format
const char string_24[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX200 + GPS frame format
const char string_25[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX240 + GPS frame format
const char string_26[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX500 + GPS frame format
const char string_27[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX501 + GPS frame format
const char string_28[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX531 GMX541 GMX551 + GPS frame format
const char string_29[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX550 + GPS frame format
const char string_30[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX600 + GPS frame format


const char* const table_xtr[] PROGMEM =
{
	string_00,
	string_01,
	string_02,
	string_03,
	string_04,
	string_05,
	string_06,
	string_07,
	string_08,
	string_09,
	string_10,
	string_11,
	string_12,
	string_13,
	string_14,
	string_15,
	string_16,
	string_17,
	string_18,
	string_19,
	string_20,
	string_21,
	string_22,
	string_23,
	string_24,
	string_25,
	string_26,
	string_27,
	string_28,
	string_29,
	string_30

};


//! class constructor
WaspSensorXtr::WaspSensorXtr()
{
	// Update Waspmote Control Register
	WaspRegisterSensor |= REG_XTR;

	// init variables
	// SW_XTR MUX -> done in main.cpp
	//pinMode(MUX_EN, OUTPUT);
	//digitalWrite(MUX_EN, LOW);

	// pin configuration
	pinMode(MUX_A, OUTPUT);
	pinMode(MUX_B, OUTPUT);
	digitalWrite(MUX_A, LOW);
	digitalWrite(MUX_B, LOW);

	// 3v3 pins of adgs
	pinMode(_3V3_SOCKETA, OUTPUT);
	digitalWrite(_3V3_SOCKETA, LOW);
	pinMode(_3V3_SOCKETB, OUTPUT);
	digitalWrite(_3V3_SOCKETB, LOW);
	pinMode(_3V3_SOCKETD, OUTPUT);
	digitalWrite(_3V3_SOCKETD, LOW);
	pinMode(_3V3_SOCKETE, OUTPUT);
	digitalWrite(_3V3_SOCKETE, LOW);

	// DC DC
	pinMode(SW_12V, OUTPUT);
	digitalWrite(SW_12V, LOW);

	// I2C isolators
	pinMode(EXPAN_ISO_EN, OUTPUT);
	digitalWrite(EXPAN_ISO_EN, LOW);
	pinMode(I2C_SOCKETA_EN, OUTPUT);
	digitalWrite(I2C_SOCKETA_EN, LOW);
	pinMode(I2C_SOCKETD_EN, OUTPUT);
	digitalWrite(I2C_SOCKETD_EN, LOW);

	// SPI isolator
	pinMode(SPI_ISO_EN, OUTPUT);
	digitalWrite(SPI_ISO_EN, LOW);


	// State registers
	socketRegister = 0;
	stateRegister12v = 0;
	redefinedSocket = 0;

	bmeIsolatorEnabledSocketA = 0;
	bmeIsolatorEnabledSocketD = 0;
	luxesIsolatorEnabledSocketA = 0;
	luxesIsolatorEnabledSocketD = 0;
	ultrasoundIsolatorEnabledSocketA = 0;
	ultrasoundIsolatorEnabledSocketD = 0;
}


// Private Methods /////////////////////////////////////////////////////////////





// Public Methods //////////////////////////////////////////////////////////////

/*!
	\brief Turns ON the Xtreme board
	\param void
	\return void
*/
void WaspSensorXtr::ON()
{
	ON(REG_5V & REG_3V3);
}



/*!
	\brief Turns ON the Xtreme board
	\param power select between 5V, 3V3 or both
	\return void
*/
void WaspSensorXtr::ON(uint8_t power)
{
	switch (power)
	{
		case REG_5V:
			PWR.setSensorPower(SENS_5V, SENS_ON);
			break;

		case REG_3V3:
			PWR.setSensorPower(SENS_3V3, SENS_ON);
			break;

		case (REG_5V & REG_3V3):
			PWR.setSensorPower(SENS_3V3, SENS_ON);
			PWR.setSensorPower(SENS_5V, SENS_ON);
			break;

		default:
			break;
	}
}

/*!
	\brief Turns OFF the Agriculture Xtreme board
	\param void
	\return void
*/
void WaspSensorXtr::OFF()
{
	//Only turn OFF 3V3 if every 12V register if OFF
	//3V3 is neccessary for 3v3 socket selecter pin expasor
	if (((WaspRegister & REG_3V3) != 0) && SensorXtr.stateRegister12v == 0)
	{
#if DEBUG_XTR == 2
		PRINTLN_XTR(F("3V3 OFF"));
#endif
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}
	if ((WaspRegister & REG_5V) != 0)
	{
#if DEBUG_XTR == 2
		PRINTLN_XTR(F("5V OFF"));
#endif
		PWR.setSensorPower(SENS_5V, SENS_OFF);
	}

}



/*!
	\brief Manages the 3v3 power supplies of Agriculture Xtreme board
	\param socket socket to be powered
	\param state desired state of the selected power supply
	\return void
*/
void WaspSensorXtr::set3v3(uint8_t socket, uint8_t _state)
{

	if (_state == SWITCH_ON)
	{
		switch (socket)
		{
			case XTR_SOCKET_A:
				digitalWrite(_3V3_SOCKETA, HIGH);
				break;

			case XTR_SOCKET_B:
				digitalWrite(_3V3_SOCKETB, HIGH);
				break;

			case XTR_SOCKET_D:
				digitalWrite(_3V3_SOCKETD, HIGH);
				break;

			case XTR_SOCKET_E:
				digitalWrite(_3V3_SOCKETE, HIGH);
				break;

			default:
				break;
		}
	}
	else
	{
		switch (socket)
		{
			case XTR_SOCKET_A:
				digitalWrite(_3V3_SOCKETA, LOW);
				break;

			case XTR_SOCKET_B:
				digitalWrite(_3V3_SOCKETB, LOW);
				break;

			case XTR_SOCKET_D:
				digitalWrite(_3V3_SOCKETD, LOW);
				break;

			case XTR_SOCKET_E:
				digitalWrite(_3V3_SOCKETE, LOW);
				break;

			default:
				break;
		}
	}

}

/*!
	\brief Manages the 12v power supplies of Agriculture Xtreme board
	\param state desired state
	\return void
*/
void WaspSensorXtr::set12v(uint8_t socket, uint8_t _state)
{
	MCP23008 mcp;	// object to manage internal circuitry

	// enable I2C in pin expansor enabling isolator
	digitalWrite(EXPAN_ISO_EN, HIGH);
	delay(10);

	// enable DC-DC
	digitalWrite(SW_12V, HIGH);

	// Pin expander modes
	mcp.pinMode(XTR_SOCKET_A, OUTPUT);
	mcp.pinMode(XTR_SOCKET_B, OUTPUT);
	mcp.pinMode(XTR_SOCKET_C, OUTPUT);
	mcp.pinMode(XTR_SOCKET_D, OUTPUT);
	mcp.pinMode(XTR_SOCKET_E, OUTPUT);
	mcp.pinMode(XTR_SOCKET_F, OUTPUT);
	mcp.pinMode(MCP_GP1, INPUT);
	mcp.pinMode(MCP_GP1, INPUT);

	// update SensorXtr.stateRegister12v
	if (_state == SWITCH_ON)
	{
		//SensorXtr.stateRegister12v update
		bitSet(SensorXtr.stateRegister12v, socket);
	}
	else
	{
		//SensorXtr.stateRegister12v update
		bitClear(SensorXtr.stateRegister12v, socket);
	}

	// update every pin in expander
	for (int i = 2; i < 8; i++)
	{
		bool bit_state = bitRead(SensorXtr.stateRegister12v, i);
		mcp.digitalWrite(i, bit_state);
	}

	// if all 12v supplies are ON print warning to avoid overcurrents.
	if (SensorXtr.stateRegister12v >= 0b11111100)
	{
		PRINTLN_XTR(F("WARNING - Possible overcurrent, 12V is ON in all the sockets"));
	}

	//If every 12V register if OFF, then turn OFF DC-DC
	if (SensorXtr.stateRegister12v == 0)
	{
#if DEBUG_XTR == 2
		PRINTLN_XTR(F("12V OFF"));
#endif
		// disable DC-DC
		digitalWrite(SW_12V, LOW);
		delay(10);
	}

	// disable I2C in pin expansor disabling isolator
	digitalWrite(EXPAN_ISO_EN, LOW);
	delay(10);

}

/*!
	\brief Controls the on board multiplexor acording to socket selected
		OUT - socket - INPUT (A,B)
		Y0		- Data B -	(0,0)
		Y1		- Data C -	(1,0)
		Y2		- Data D -	(0,1)
		Y3		- Data A -	(1,1)
	\return void
*/
void WaspSensorXtr::setMux(uint8_t socket, uint8_t _state)
{
	if (_state == ENABLED)
	{
		// enable mux
		digitalWrite(MUX_EN, LOW);

		// set multiplexor according socket and turn on power if necessary
		switch (socket)
		{
			case XTR_SOCKET_A:
				digitalWrite(MUX_A, HIGH);
				digitalWrite(MUX_B, HIGH);
				break;

			case XTR_SOCKET_B:
				digitalWrite(MUX_A, LOW);
				digitalWrite(MUX_B, LOW);
				break;

			case XTR_SOCKET_C:
				digitalWrite(MUX_A, HIGH);
				digitalWrite(MUX_B, LOW);
				break;

			case XTR_SOCKET_D:
				digitalWrite(MUX_A, LOW);
				digitalWrite(MUX_B, HIGH);
				break;

			default:
				break;
		}
	}
	else
	{
		// enable mux
		digitalWrite(MUX_EN, HIGH);
	}

	delay(10);
}

/*!
	\brief Read the EEPROM memory serial number
	\param void
	\return 1 if OK, 0 otherwise.
*/
uint32_t WaspSensorXtr::readBoardSerialNumber()
{
	uint8_t manufacturer_code = 0;
	uint8_t device_code = 0;

	memset(boardSerialNumber, 0x00, sizeof(boardSerialNumber));

	uint8_t flag3v3 = 0;

	if ((WaspRegister & REG_3V3) == 0)
	{
		flag3v3 = 1;
		PWR.setSensorPower(SENS_3V3, SENS_ON);
	}

	// Enable EEPROM memory
	pinMode(EXPAN_ISO_EN, OUTPUT);
	digitalWrite(EXPAN_ISO_EN, HIGH);
	delay(100);

	I2C.begin();
	if (I2C.scan(xtr_eeprom_address) == 0)
	{
		// Reading manufacturer code (should be 0x29)
		I2C.read(xtr_eeprom_address, manufacturer_code_address, &manufacturer_code, 1);

		// Reading device code (should be 0x41)
		I2C.read(xtr_eeprom_address, device_code_address, &device_code, 1);

		if ((manufacturer_code == 0x29) && (device_code == 0x41))
		{
			I2C.read(xtr_eeprom_address, serial_number_address, boardSerialNumber, 4);

			// Disable EEPROM memory
			digitalWrite(EXPAN_ISO_EN, LOW);
			if (flag3v3)
			{
				PWR.setSensorPower(SENS_3V3, SENS_OFF);
			}

			return 1;
		}
	}

	// If here, there was an error while reading
	// Disable EEPROM memory
	digitalWrite(EXPAN_ISO_EN, LOW);
	if (flag3v3)
	{
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}

	return 0;
}


/*!
	\brief Write the I2C EEPROM
	\param void
	\return 0 if OK, otherwise error.
*/
uint8_t WaspSensorXtr::writeEEPROM(uint8_t address, uint8_t value)
{
	uint8_t flag3v3 = 0;

	// reserved addresses below 0x50
	if ( address >= 0x50 )
	{
		if ((WaspRegister & REG_3V3) == 0)
		{
			flag3v3 = 1;
			PWR.setSensorPower(SENS_3V3, SENS_ON);
		}

		// Enable EEPROM memory
		pinMode(EXPAN_ISO_EN, OUTPUT);
		digitalWrite(EXPAN_ISO_EN, HIGH);
		delay(100);

		I2C.begin();
		if (I2C.scan(xtr_eeprom_address) == 0)
		{
			int rv = I2C.write(xtr_eeprom_address, address, value);

			digitalWrite(EXPAN_ISO_EN, LOW);
			if (flag3v3) {
				PWR.setSensorPower(SENS_3V3, SENS_OFF);
			}
			return rv;
		}
	}

	digitalWrite(EXPAN_ISO_EN, LOW);
	if (flag3v3) {
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}
	return 1;
}

/*!
	\brief Read the I2C EEPROM
	\param void
	\return data if OK, otherwise -1.
*/
int8_t WaspSensorXtr::readEEPROM(uint8_t address)
{
	uint8_t flag3v3 = 0;

	if ((WaspRegister & REG_3V3) == 0)
	{
		flag3v3 = 1;
		PWR.setSensorPower(SENS_3V3, SENS_ON);
	}

	// Enable EEPROM memory
	pinMode(EXPAN_ISO_EN, OUTPUT);
	digitalWrite(EXPAN_ISO_EN, HIGH);
	delay(100);

	I2C.begin();
	if (I2C.scan(xtr_eeprom_address) == 0)
	{
		uint8_t rdata = 0;
		I2C.read(xtr_eeprom_address, address, &rdata, 1);

		digitalWrite(EXPAN_ISO_EN, LOW);
		if (flag3v3) {
			PWR.setSensorPower(SENS_3V3, SENS_OFF);
		}
		return rdata;
	}

	digitalWrite(EXPAN_ISO_EN, LOW);
	if (flag3v3) {
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}
	return -1;
}




//******************************************************************************
// 5TE Sensor Class functions
//******************************************************************************


/*!
	\brief 5TE Class constructor
	\param socket selected socket for sensor
*/
Decagon_5TE::Decagon_5TE(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_5TE::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_E) || (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("5TE"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(300);

#if DEBUG_XTR == 2
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Decagon_5TE::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();
}

/*!
	\brief Reads the sensor data
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_5TE::read()
{
	SensorXtr.setMux(socket, ENABLED);

	// Initialize variables
	sensor5TE.dielectricPermittivity = 0;
	sensor5TE.electricalConductivity = 0;
	sensor5TE.temperature = 0;
	float parameter4_dummy = -1000;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		response = sdi12SensorXtr.readMeasures(	_5TE,
												sensor5TE.sensorSerialNumber,
												sensor5TE.dielectricPermittivity,
												sensor5TE.electricalConductivity,
												sensor5TE.temperature,
												parameter4_dummy);

		if ((sensor5TE.dielectricPermittivity != 0)
		|| (sensor5TE.electricalConductivity != 0)
		|| (sensor5TE.temperature != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	SensorXtr.setMux(socket, DISABLED);
	return response;
}

/*!
	\brief Reads the sensor serial number
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_5TE::readSerialNumber()
{
	return read();
}

//******************************************************************************
// 5TM Sensor Class functions
//******************************************************************************


/*!
	\brief 5TM Class constructor
	\param socket selected socket for sensor
*/
Decagon_5TM::Decagon_5TM(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_5TM::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_E) || (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("5TM"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(300);

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Decagon_5TM::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_5TM::read()
{
	SensorXtr.setMux(socket, ENABLED);

	// Initialize variables
	sensor5TM.dielectricPermittivity = 0;
	sensor5TM.temperature = 0;
	float parameter3_dummy = -1000;
	float parameter4_dummy = -1000;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		response = sdi12SensorXtr.readMeasures(	_5TM,
												sensor5TM.sensorSerialNumber,
												sensor5TM.dielectricPermittivity,
												sensor5TM.temperature,
												parameter3_dummy,
												parameter4_dummy);

		if ((sensor5TM.dielectricPermittivity != 0)
				|| (sensor5TM.temperature != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	SensorXtr.setMux(socket, DISABLED);
	return response;
}

/*!
	\brief Reads the sensor serial number
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_5TM::readSerialNumber()
{
	return read();
}

//******************************************************************************
// GS3 Sensor Class functions
//******************************************************************************

/*!
	\brief GS3 Class constructor
	\param socket selected socket for sensor
*/
Decagon_GS3::Decagon_GS3(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_GS3::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_E) || (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("GS3"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(300);

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Decagon_GS3::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_GS3::read()
{
	SensorXtr.setMux(socket, ENABLED);

	// Initialize variables
	sensorGS3.dielectricPermittivity = 0;
	sensorGS3.electricalConductivity = 0;
	sensorGS3.temperature = 0;
	float parameter4_dummy = -1000;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{

		response = sdi12SensorXtr.readMeasures(	GS3,
												sensorGS3.sensorSerialNumber,
												sensorGS3.dielectricPermittivity,
												sensorGS3.temperature,
												sensorGS3.electricalConductivity,
												parameter4_dummy);

		if ((sensorGS3.dielectricPermittivity != 0)
				|| (sensorGS3.temperature != 0)
				|| (sensorGS3.electricalConductivity != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	SensorXtr.setMux(socket, DISABLED);
	return response;
}

/*!
	\brief Reads the sensor serial number
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_GS3::readSerialNumber()
{
	return read();
}


//******************************************************************************
// VP4 Sensor Class functions
//******************************************************************************

/*!
	\brief VP4 Class constructor
	\param socket selected socket for sensor
*/

Decagon_VP4::Decagon_VP4(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_VP4::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_E) || (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("VP4"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(800);

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Decagon_VP4::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_VP4::read()
{
	SensorXtr.setMux(socket, ENABLED);

	// Initialize variables
	sensorVP4.vaporPressure = 0;
	sensorVP4.temperature = 0;
	sensorVP4.relativeHumidity = 0;
	sensorVP4.atmosphericPressure = 0;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{

		response = sdi12SensorXtr.readMeasures(	VP4,
												sensorVP4.sensorSerialNumber,
												sensorVP4.vaporPressure,
												sensorVP4.temperature,
												sensorVP4.relativeHumidity,
												sensorVP4.atmosphericPressure);


		if ((sensorVP4.vaporPressure != 0)
		|| (sensorVP4.temperature != 0)
		|| (sensorVP4.relativeHumidity != 0)
		|| (sensorVP4.atmosphericPressure != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	SensorXtr.setMux(socket, DISABLED);
	return response;
}

/*!
	\brief Reads the sensor serial number
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_VP4::readSerialNumber()
{
	return read();
}

//******************************************************************************
// MPS6 Sensor Class functions
//******************************************************************************

/*!
	\brief MPS6 Class constructor
	\param socket selected socket for sensor
*/
Decagon_MPS6::Decagon_MPS6(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_MPS6::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_E) || (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("MPS6"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(300);

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Decagon_MPS6::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_MPS6::read()
{
	SensorXtr.setMux(socket, ENABLED);

	// Initialize variables
	sensorMPS6.waterPotential = 0;
	sensorMPS6.temperature = 0;
	float parameter3_dummy = -1000;
	float parameter4_dummy = -1000;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		response = sdi12SensorXtr.readMeasures(	MPS6,
												sensorMPS6.sensorSerialNumber,
												sensorMPS6.waterPotential,
												sensorMPS6.temperature,
												parameter3_dummy,
												parameter4_dummy);

		if ((sensorMPS6.waterPotential != 0)
				|| (sensorMPS6.temperature != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	SensorXtr.setMux(socket, DISABLED);
	return response;
}

/*!
	\brief Reads the sensor serial number
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Decagon_MPS6::readSerialNumber()
{
	return read();
}

//******************************************************************************
// SO-411 Sensor Class functions
//******************************************************************************


/*!
	\brief SO411 Class constructor
	\param socket selected socket for sensor
*/
Apogee_SO411::Apogee_SO411(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}

}


/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SO411::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_E) || (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("SO-411"));

		return 0;
	}


	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(300);

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Apogee_SO411::OFF()
{
	//Turn off the sensor and the heater
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SO411::read()
{
	SensorXtr.setMux(socket, ENABLED);

	// Initialize variables
	sensorSO411.calibratedOxygen = 0;
	sensorSO411.bodyTemperature = 0;
	sensorSO411.milliVolts = 0;
	float parameter4_dummy = -1000;
	memset(sensorSO411.sensorSerialNumber, 0x00, sizeof(sensorSO411.sensorSerialNumber));

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		response = sdi12SensorXtr.readMeasures(	SO411,
												sensorSO411.sensorSerialNumber,
												sensorSO411.calibratedOxygen,
												sensorSO411.bodyTemperature,
												sensorSO411.milliVolts,
												parameter4_dummy);

		if ((sensorSO411.calibratedOxygen != 0)
		|| (sensorSO411.bodyTemperature != 0)
		|| (sensorSO411.milliVolts != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	SensorXtr.setMux(socket, DISABLED);
	return response;
}

/*!
	\brief Reads the sensor serial number
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SO411::readSerialNumber()
{
	return read();
}

//******************************************************************************
// SI-411 Sensor Class functions
//******************************************************************************


/*!
	\brief SI411 Class constructor
	\param socket selected socket for sensor
*/
Apogee_SI411::Apogee_SI411(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}

}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SI411::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_E) || (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("SI-411"));

		return 0;
	}


	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(300);

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Apogee_SI411::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SI411::read()
{
	SensorXtr.setMux(socket, ENABLED);

	// Initialize variables
	sensorSI411.targetTemperature = 0;
	float parameter2_dummy = -1000;
	float parameter3_dummy = -1000;
	float parameter4_dummy = -1000;
	memset(sensorSI411.sensorSerialNumber, 0x00, sizeof(sensorSI411.sensorSerialNumber));

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		response = sdi12SensorXtr.readMeasures(	SI411,
												sensorSI411.sensorSerialNumber,
												sensorSI411.targetTemperature,
												parameter2_dummy,
												parameter3_dummy,
												parameter4_dummy);

		if ((sensorSI411.sensorSerialNumber[0] != 0)
		|| (sensorSI411.targetTemperature != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;

	}

	SensorXtr.setMux(socket, DISABLED);
	return response;
}


/*!
	\brief Reads the sensor serial number
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SI411::readSerialNumber()
{
	return read();
}



//******************************************************************************
// SF-421 Sensor Class functions
//******************************************************************************


/*!
	\brief SF421 Class constructor
	\param socket selected socket for sensor
*/
Apogee_SF421::Apogee_SF421(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}

}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SF421::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_E) || (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("SF-421"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(300);

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Apogee_SF421::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SF421::read()
{
	SensorXtr.setMux(socket, ENABLED);

	// Initialize variables
	sensorSF421.budTemperature = 0;
	sensorSF421.leafTemperature = 0;
	float parameter3_dummy = 0;
	float parameter4_dummy = -1000;
	memset(sensorSF421.sensorSerialNumber, 0x00, sizeof(sensorSF421.sensorSerialNumber));

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		response = sdi12SensorXtr.readMeasures(	SF421,
												sensorSF421.sensorSerialNumber,
												sensorSF421.budTemperature,
												sensorSF421.leafTemperature,
												parameter3_dummy,
												parameter4_dummy);



		if ((sensorSF421.sensorSerialNumber[0] != 0)
		|| (sensorSF421.budTemperature != 0)
		|| (sensorSF421.leafTemperature != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	SensorXtr.setMux(socket, DISABLED);
	return response;
}


/*!
	\brief Reads the sensor serial number
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SF421::readSerialNumber()
{
	return read();
}

//******************************************************************************
// Leaf Wetness Sensor Class functions
//******************************************************************************

/*!
	\brief leafWetness Class constructor
	\param socket selected socket for sensor
*/
leafWetness::leafWetness()
{
	// store sensor location
	socket = XTR_SOCKET_B;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}

}

/*!
	\brief Turns on the sensor
	\param void
	\return void
*/
void leafWetness::ON()
{
	if (SensorXtr.redefinedSocket == 1)
	{
		char message[50];
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	SensorXtr.ON(REG_3V3);
	SensorXtr.set3v3(XTR_SOCKET_B, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(10);

}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void leafWetness::OFF()
{
	SensorXtr.set3v3(XTR_SOCKET_B, SWITCH_OFF);
	SensorXtr.OFF();

}


/*!
	\brief Reads the leaf wetness sensor
	\param void
	\return return 0 if sensor not present or invalid data. 1 Otherwise.
*/
uint8_t leafWetness::read()
{
	LTC ltc;			// object to manage ADC

	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	delay(10);

	// ADC setup
	ltc.begin();

	// necessary for the sensor
	delay(10);

	ltc.readADC(ADC_CH3);
	wetness = ltc.readADC(ADC_CH3);

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor
#if DEBUG_XTR == 1
	PRINT_XTR(F("wetness: "));
	USB.printFloat(wetness, 5);
	USB.println();
#endif

	// MAX sensor value us 1.1V, if powered at 3V3. Not present if greater values.
	if ((wetness == 0) || (wetness > 1.1 ))
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

//******************************************************************************
// Dendrometer Sensor Class functions
//******************************************************************************


/*!
	\brief dendrometer Class constructor 1
	\param socket selected socket for sensor
*/
dendrometer::dendrometer()
{
	dendrometer(DENDRO_DD);
}

/*!
	\brief dendrometer Class constructor 2
	\param socket selected socket for sensor
*/
dendrometer::dendrometer(uint8_t type)
{
	dendroType = type;
	diameter = 0;
	dendroRef = 0;
	dendroGrowth = 0;

	// store sensor location
	socket = XTR_SOCKET_C;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}


/*!
	\brief Turns on the sensor
	\param void
	\return void
*/
void dendrometer::ON()
{

	if (SensorXtr.redefinedSocket == 1)
	{
		char message[50];
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}



	SensorXtr.ON(REG_3V3);

	//neccessary delay after powering the sensor
	delay(10);
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void dendrometer::OFF()
{
	SensorXtr.OFF();
}



/*!
	\brief reads the dendrometer sensor and converts its value into mm
	\param void
	\return 1 if ok, 0 if something fails
*/
float dendrometer::read(void)
{
	LTC ltc;			// object to manage ADC

	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();

	// necessary for the sensor
	delay(10);

	ltc.readADC(ADC_CH5);
	diameter = ltc.readADC(ADC_CH5);

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor in volts
#if DEBUG_XTR == 2
	PRINT_XTR(F("dendro (V): "));
	USB.printFloat(diameter, 5);
	USB.println();
#endif

	// Conversion to mm according type
	diameter = (diameter * dendroType) / 3;

	// check value of the sensor in mm
#if DEBUG_XTR == 1
	PRINT_XTR(F("diameter (mm): "));
	USB.printFloat(diameter, 5);
	USB.println();
#endif

	// No way to check if sensor missing. -2000 if value out of range or ADC fail.
	if (diameter <= 0)
	{
		// measure out of range, greater than 15mm or negative
		return 0;
	}
	else
	{
		return 1;
	}

}


/*!
	\brief Sets reference value to measure dendrometer growth
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t dendrometer::setReference(void)
{
	if (read() == 1)
	{
		dendroRef = diameter;
		return 1;
	}
	else
	{
		return 0;
	}
}


/*!
	\brief Compare current dendrometer value with reference
	\param void
	\return 1 if ok, 0 if something fails
*/

float dendrometer::readGrowth(void)
{
	if (read() == 1)
	{
		dendroGrowth = diameter - dendroRef;
		return 1;
	}
	else
	{
		return 0;
	}
}


//******************************************************************************
// GMX-240 Weather station Sensor Class functions
//******************************************************************************


/*!
	\brief weatherStation Class constructor
	\param socket selected socket for sensor
*/
weatherStation::weatherStation()
{
	socket = XTR_SOCKET_E;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return void
*/
void weatherStation::ON()
{
	if (SensorXtr.redefinedSocket == 1)
	{
		char message[50];
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	Utils.setMuxAux2();
	beginSerial(19200, 1);
	serialFlush(1);

	SensorXtr.ON(REG_3V3);

	//Enable RS-485 chip on (shared with 3v3 pin)
	SensorXtr.set3v3(socket, SWITCH_ON);
	SensorXtr.set12v(socket, SWITCH_ON);

	const uint16_t BUFFER_SIZE = 500;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0x00, sizeof(buffer));
	bool exitWhile = 0;
	uint16_t i = 0;
	unsigned long previous = millis();

	//Capture buffer
	while (((millis() - previous) < 10000) && exitWhile == 0)
	{
		if (serialAvailable(1) > 0)
		{
			//Avoid storing 0x00 in our buffer string
			char buffer_temp = serialRead(1);
			if (buffer_temp != 0x00)
			{
				buffer[i] = buffer_temp;
				i++;
			}
			if (strstr(buffer, "<END OF STARTUP MESSAGE>") != NULL)
			{
				exitWhile = 1;
			}
			if (i == BUFFER_SIZE)
			{
				exitWhile = 1;
			}
		}

		//avoid millis overflow problem after approximately 50 days
		if ( millis() < previous ) previous = millis();
	}

#if DEBUG_XTR > 1
	USB.print(F("WS RX:"));
	USB.println(buffer);
#endif

	if (strstr(buffer, "GMX100") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX100 found"));
#endif

		stationModel = WS_GMX100;
	}
	else if (strstr(buffer, "GMX101") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX101 found"));
#endif

		stationModel = WS_GMX101;
	}
	else if (strstr(buffer, "GMX200") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX200 found"));
#endif

		stationModel = WS_GMX200;
	}
	else if (strstr(buffer, "GMX240") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX240 found"));
#endif

		stationModel = WS_GMX240;
	}
	else if (strstr(buffer, "GMX300") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX300 found"));
#endif

		stationModel = WS_GMX300;
	}
	else if (strstr(buffer, "GMX301") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX301 found"));
#endif

		stationModel = WS_GMX301;
	}
	else if (strstr(buffer, "GMX400") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX400 found"));
#endif

		stationModel = WS_GMX400;
	}
	else if (strstr(buffer, "GMX500") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX500 found"));
#endif

		stationModel = WS_GMX500;
	}
	else if (strstr(buffer, "GMX501") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX501 found"));
#endif

		stationModel = WS_GMX501;
	}
	else if (strstr(buffer, "GMX531") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX531 found"));
#endif

		stationModel = WS_GMX531;
	}
	else if (strstr(buffer, "GMX541") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX541 found"));
#endif

		stationModel = WS_GMX541;
	}
	else if (strstr(buffer, "GMX550") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX550 found"));
#endif

		stationModel = WS_GMX550;
	}
	else if (strstr(buffer, "GMX551") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX551 found"));
#endif

		stationModel = WS_GMX551;
	}
	else if (strstr(buffer, "GMX600") != NULL)
	{
#if DEBUG_XTR > 1
		PRINTLN_XTR(F("GMX600 found"));
#endif

		stationModel = WS_GMX600;
	}


	//neccessary delay for a first good read
	delay(100);
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void weatherStation::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();
}

/*!
	\brief enable/disable gps
	\param gps option
	\return void
*/
void weatherStation::GPS(uint8_t option)
{
	gps = option;
}

/*!
	\brief Enters commands to weather station
	\param str
	\return 1 if ok, 0 if something fails
*/
uint8_t weatherStation::sendCommand(char* str)
{
	const uint16_t BUFFER_SIZE = 200;
	char buffer_ws_raw[BUFFER_SIZE];
	memset(buffer_ws_raw, 0x00, sizeof(buffer_ws_raw));
	bool exitWhile = 0;
	bool dataFrameFound = 0;
	uint16_t i = 0;
	unsigned long previous = millis();


	//Configure UART
	Utils.setMuxAux2();
	beginSerial(19200, 1);
	serialFlush(1);
	delay(5);


	//Clean serial buffer
	while (serialAvailable(1) > 0)
	{
		serialRead(1);
	}

	// Enter to SETUP MODE
	printString("\r", 1);
	delay(20);

	printString("*", 1);
	printString("\r", 1);
#if DEBUG_XTR > 1
	USB.print(F("WS TX:"));
	USB.println(F("*"));

	USB.print(F("WS RX:"));
#endif

	//Capture buffer
	while (((millis() - previous) < 8000) && (exitWhile == 0) && (dataFrameFound == 0))
	{
		if (serialAvailable(1) > 0)
		{
			char buffer_temp = serialRead(1);
#if DEBUG_XTR > 1
			USB.print(buffer_temp);
#endif

			buffer_ws_raw[i] = buffer_temp;
			i++;

			//> found
			if (buffer_ws_raw[i - 1] == '>')
			{
				dataFrameFound = 1;
			}

			if (i - 1 == BUFFER_SIZE)
			{
				exitWhile = 1;
			}
		}

		//avoid millis overflow problem after approximately 50 days
		if ( millis() < previous ) previous = millis();
	}

	if (dataFrameFound == 0)
	{
		return 0;
	}

	memset(buffer_ws_raw, 0x00, sizeof(buffer_ws_raw));
	strcpy(buffer_ws_raw, str);

#if DEBUG_XTR > 1
	USB.print(F("WS TX:"));
#endif


	printString("\r", 1);
	delay(20);
	for (int j = 0; j < strlen(buffer_ws_raw); j++)
	{
		printByte(buffer_ws_raw[j], 1);
#if DEBUG_XTR > 1
		USB.print(buffer_ws_raw[j]);
#endif
		delay(20);
	}


	//Clean serial buffer
	while (serialAvailable(1) > 0)
	{
		serialRead(1);
	}
	printString("\r", 1);
#if DEBUG_XTR > 1
	USB.println();
#endif

	memset(buffer_ws_raw, 0x00, sizeof(buffer_ws_raw));
	exitWhile = 0;
	dataFrameFound = 0;
	i = 0;
	previous = millis();

	//Capture buffer
	while (((millis() - previous) < 1000) && (exitWhile == 0) && (dataFrameFound == 0))
	{
		if (serialAvailable(1) > 0)
		{
			//Avoid storing 0x00 in our buffer string or 0x02 STX (Start of Text)
			char buffer_temp = serialRead(1);

			if ((buffer_temp != 0x00) && (buffer_temp != 0x02))
			{

				buffer_ws_raw[i] = buffer_temp;
				i++;
			}
			//ETX (End of Text) found
			if (buffer_ws_raw[i - 1] == 0x03)
			{
				buffer_ws_raw[i - 1] = 0x00;
				dataFrameFound = 1;
			}

			if (i - 1 == BUFFER_SIZE)
			{
				exitWhile = 1;
			}
		}
		//avoid millis overflow problem after approximately 50 days
		if ( millis() < previous ) previous = millis();

	}

#if DEBUG_XTR > 1
	USB.print("WS RX:");
	USB.println(buffer_ws_raw);
#endif


	// Exit from SETUP MODE
#if DEBUG_XTR > 1
	USB.println("WS TX:EXIT");
#endif


	printString("\r", 1);
	delay(20);

	printString("E", 1); delay(20);
	printString("X", 1); delay(20);
	printString("I", 1); delay(20);
	printString("T", 1); delay(20);
	printString("\r", 1);
	delay(20);

	//Clean serial buffer
	while (serialAvailable(1) > 0)
	{
		serialRead(1);
	}

	return 1;
}



/*!
	\brief Reads the weather Station sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t weatherStation::read()
{
	const uint16_t BUFFER_SIZE = 250;
	char buffer_ws_raw[BUFFER_SIZE];
	memset(buffer_ws_raw, 0x00, sizeof(buffer_ws_raw));
	bool exitWhile = 0;
	bool dataFrameFound = 0;
	bool dataFrameParsed = 0;
	uint16_t i = 0;
	unsigned long previous = millis();
	char buffer_table[150];
	memset(buffer_table, 0x00, sizeof(buffer_table));

	// Initialize vector variables
	gmx.windDirection = 0;
	gmx.correctedWindDirection = 0;
	gmx.avgWindDirection = 0;
	gmx.windSpeed = 0;
	gmx.avgWindSpeed = 0;
	gmx.avgWindGustDirection = 0;
	gmx.avgWindGustSpeed = 0;
	gmx.avgCorrectedWindDirection = 0;
	strcpy(gmx.windSensorStatus, "0");
	gmx.precipTotal = 0;
	gmx.precipIntensity = 0;
	gmx.precipStatus = 0;
	gmx.compass = 0;
	gmx.xTilt = 0;
	gmx.yTilt = 0;
	gmx.zOrient = 0;
	strcpy(gmx.timestamp, "0");
	gmx.supplyVoltage = 0;
	strcpy(gmx.status, "0");
	gmx.solarRadiation = 0;
	gmx.sunshineHours = 0;
	strcpy(gmx.sunriseTime, "0");
	strcpy(gmx.solarNoonTime, "0");
	strcpy(gmx.sunsetTime, "0");
	strcpy(gmx.sunPosition, "0");
	strcpy(gmx.twilightCivil, "0");
	strcpy(gmx.twilightNautical, "0");
	strcpy(gmx.twilightAstronom, "0");
	gmx.pressure = 0;
	gmx.pressureSeaLevel = 0;
	gmx.pressureStation = 0;
	gmx.relativeHumidity = 0;
	gmx.temperature = 0;
	gmx.dewpoint = 0;
	gmx.absoluteHumidity = 0;
	gmx.airDensity = 0;
	gmx.wetBulbTemperature = 0;
	gmx.windChill = 0;
	gmx.heatIndex = 0;
#ifdef GMX_GPS_OPTION
	gmx.gpsCorrectedSpeed = 0;
	gmx.gpsAvgCorrectedSpeed = 0;
	gmx.gpsCorrectedGustSpeed = 0;
	gmx.gpsCorrectedGustDirection = 0;
	strcpy(gmx.gpsLocation, "0");
	gmx.gpsHeading = 0;
	gmx.gpsSpeed = 0;
	strcpy(gmx.gpsStatus, "0");
#endif

	// Create and initialize local variables
	char node_letter_local = 0;
	char windSpeed_local[7];
	char avgWindSpeed_local[7];
	char avgWindGustSpeed_local[7];
	char precipTotal_local[10];
	char precipIntensity_local[8];
	char precipStatus_local = 'N';
	char xTilt_local[4];
	char yTilt_local[4];
	char zOrient_local[3];
	char supplyVoltage_local[6];
	char sunshineHours_local[5];
	char pressure_local[7];
	char pressureSeaLevel_local[7];
	char pressureStation_local[7];
	char temperature_local[6];
	char dewpoint_local[7];
	char absoluteHumidity_local[6];
	char airDensity_local[3];
	char wetBulbTemperature_local[7];
	char windChill_local[5];
#ifdef GMX_GPS_OPTION
	char gpsCorrectedSpeed_local[7];
	char gpsAvgCorrectedSpeed_local[7];
	char gpsCorrectedGustSpeed_local[7];
	char gpsSpeed_local[8];
#endif

	strcpy(windSpeed_local, "0");
	strcpy(avgWindSpeed_local, "0");
	strcpy(avgWindGustSpeed_local, "0");
	strcpy(precipTotal_local, "0");
	strcpy(precipIntensity_local, "0");
	strcpy(xTilt_local, "0");
	strcpy(yTilt_local, "0");
	strcpy(zOrient_local, "0");
	strcpy(supplyVoltage_local, "0");
	strcpy(sunshineHours_local, "0");
	strcpy(pressure_local, "0");
	strcpy(pressureSeaLevel_local, "0");
	strcpy(pressureStation_local, "0");
	strcpy(temperature_local, "0");
	strcpy(dewpoint_local, "0");
	strcpy(absoluteHumidity_local, "0");
	strcpy(airDensity_local, "0");
	strcpy(wetBulbTemperature_local, "0");
	strcpy(windChill_local, "0");
#if GMX_GPS_OPTION > 1
	strcpy(gpsCorrectedSpeed_local, "0");
	strcpy(gpsAvgCorrectedSpeed_local, "0");
	strcpy(gpsCorrectedGustSpeed_local, "0");
	strcpy(gpsSpeed_local, "0");
#endif


	//Configure UART
	Utils.setMuxAux2();
	beginSerial(19200, 1);
	serialFlush(1);
	delay(5);

	//Clean serial buffer
	while (serialAvailable(1) > 0)
	{
		serialRead(1);
	}

	//Send command asking for data (previously "?Q" required)
	printString("Q", 1);
#if DEBUG_XTR > 1
	USB.print(F("WS TX:"));
	USB.println(F("Q"));
#endif

	//Capture buffer
	while (((millis() - previous) < 8000) && (exitWhile == 0) && (dataFrameFound == 0))
	{
		if (serialAvailable(1) > 0)
		{
			//Avoid storing 0x00 in our buffer string or 0x02 STX (Start of Text)
			char buffer_temp = serialRead(1);
			if ((buffer_temp != 0x00) && (buffer_temp != 0x02))
			{
				//Change ',' for ' ' (whitespace character) for better parsing
				if (buffer_temp != ',')
				{
					buffer_ws_raw[i] = buffer_temp;
				}
				else
				{
					buffer_ws_raw[i] = ' ';
				}
				i++;
			}
			//ETX (End of Text) found
			if (buffer_ws_raw[i - 1] == 0x03)
			{
				buffer_ws_raw[i - 1] = 0x00;
				dataFrameFound = 1;
			}

			if (i - 1 == BUFFER_SIZE)
			{
				exitWhile = 1;
			}
		}

		//avoid millis overflow problem after approximately 50 days
		if ( millis() < previous ) previous = millis();
	}

	//Snippet for simulating a weather station connected
	//dataFrameFound = 1;

	//GMX240 example frame
	//stationModel = WS_GMX240;
	//strcpy(buffer_ws_raw, "Q 044 000.02 013 145 001.45 145 015.15 131 0000 00000.080 000.080 Y 010 +52 +33 +1 2018-06-11T10:59:20.6 +12.0 0000");

	//GMX100 example frame
	//stationModel = WS_GMX100;
	//strcpy(buffer_ws_raw, "Q 00000.080 000.080 Y +26 -56 +1 2018-06-12T16:31:11.1 +12.0 00000");

	//GMX101 example frame
	//stationModel = WS_GMX101;
	//Q 0001 01.20 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +32 -17 +1 2017-01-20T11:46:01.3 +05.0 0000
	
	//GMX541 example frame
	//stationModel = WS_GMX541;
	//strcpy(buffer_ws_raw, "Q 264 000.05 052 000 000.00 000 000.00 000 0100 00000.000 000.000 N 148 1001.4 1001.4 1001.4 047 +025.2 +013.4 11.18 0006 00.00  +026 1.2 +017.9 06:49 11:47 16:46 153:+26 17:16 17:49 18:22 +03 -82 +1 2018-11-13T10:06:56.5 +11.8 0000");
	
	
#if DEBUG_XTR > 1
	USB.print(F("WS RX:"));
	USB.println(buffer_ws_raw);
#endif

	if (dataFrameFound && stationModel == WS_GMX100)
	{
		//Frame is like:
		//"Q 00000.080 000.080 Y +26 -56 +1 2018-06-12T16:31:11.1 +12.0 0000"

		//"%c %s %s %c %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[12])));
		sscanf (buffer_ws_raw, buffer_table,
						&node_letter_local,
						precipTotal_local,
						precipIntensity_local,
						&precipStatus_local,
						xTilt_local,
						yTilt_local,
						zOrient_local,
						gmx.timestamp,
						supplyVoltage_local,
						gmx.status);

		dataFrameParsed = 1;
	}
	else if (dataFrameFound && stationModel == WS_GMX101)
	{
		//Frame is like:
		//"Q 0001 01.20 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +32 -17 +1 2017-01-20T11:46:01.3 +05.0 0000"

		//"%c %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[13])));
		sscanf (buffer_ws_raw, buffer_table,
						&node_letter_local,
						gmx.solarRadiation,
						sunshineHours_local,
						gmx.sunriseTime,
						gmx.solarNoonTime,
						gmx.sunsetTime,
						gmx.sunPosition,
						gmx.twilightCivil,
						gmx.twilightNautical,
						gmx.twilightAstronom,
						xTilt_local,
						yTilt_local,
						zOrient_local,
						gmx.timestamp,
						supplyVoltage_local,
						gmx.status);

		dataFrameParsed = 1;
	}
	else if (dataFrameFound && stationModel == WS_GMX200)
	{
		if (!gps)
		{
			//Frame is like:
			//"Q 048 000.02 106 000 000.00 000 000.00 000 0100 058 07:58 12:08 16:19 143:+09 16:57 17:39 18:19 00 +00 +1 2018-01-16T09:29:31.1 +05.0 0000"

			//"%c %d %s %d %d %s %d %s %d %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[14])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							&gmx.compass,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status);

			dataFrameParsed = 1;
		}
#if GMX_GPS_OPTION > 1
		else
		{
			//Frame is like:
			//"Q 048 000.02 106 000 000.00 000 000.00 000 0100 058 07:58 12:08 16:19 143:+09 16:57 17:39 18:19 00 +00 +1 2018-01-16T09:29:31.1 +05.0 0000
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"

			//"%c %d %s %d %d %s %d %s %d %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[24])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							&gmx.compass,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status,
							gpsCorrectedSpeed_local,
							gpsAvgCorrectedSpeed_local,
							gpsCorrectedGustSpeed_local,
							&gmx.gpsCorrectedGustDirection,
							gmx.gpsLocation,
							&gmx.gpsHeading,
							gpsSpeed_local,
							gmx.gpsStatus);

			dataFrameParsed = 1;

		}
#endif
	}
	else if (dataFrameFound && stationModel == WS_GMX240)
	{
		if (!gps)
		{
			//Frame is like:
			//"Q 044 000.02 013 145 001.45 145 015.15 131 0000 00000.080 000.080 Y 010 +52 +33 +1 2018-06-11T10:59:20.6 +12.0 0000"

			//"%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[15])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							precipTotal_local,
							precipIntensity_local,
							&precipStatus_local,
							&gmx.compass,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status);

			dataFrameParsed = 1;
		}
#if GMX_GPS_OPTION > 1
		else
		{
			//Frame is like:
			//"Q 044 000.02 013 145 001.45 145 015.15 131 0000 00000.080 000.080 Y 010 +52 +33 +1 2018-06-11T10:59:20.6 +12.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"

			//"%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[25])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							precipTotal_local,
							precipIntensity_local,
							&precipStatus_local,
							&gmx.compass,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status,
							gpsCorrectedSpeed_local,
							gpsAvgCorrectedSpeed_local,
							gpsCorrectedGustSpeed_local,
							&gmx.gpsCorrectedGustDirection,
							gmx.gpsLocation,
							&gmx.gpsHeading,
							gpsSpeed_local,
							gmx.gpsStatus);

			dataFrameParsed = 1;
		}
#endif

	}
	else if (dataFrameFound && stationModel == WS_GMX300)
	{
		//Frame is like:
		//"Q 0999.5 0999.5 0999.5 040 +023.3 +009.1 08.45 1.2 +015.1 07:58 12:08 16:19 162:+15 16:57 17:39 18:19 +00 +01 +1
		// 2018-01-16T10:55:38.5 +05.1 0000"

		//"%c %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[16])));
		sscanf (buffer_ws_raw, buffer_table,
						&node_letter_local,
						pressure_local,
						pressureSeaLevel_local,
						pressureStation_local,
						&gmx.relativeHumidity,
						temperature_local,
						dewpoint_local,
						absoluteHumidity_local,
						airDensity_local,
						wetBulbTemperature_local,
						gmx.sunriseTime,
						gmx.solarNoonTime,
						gmx.sunsetTime,
						gmx.sunPosition,
						gmx.twilightCivil,
						gmx.twilightNautical,
						gmx.twilightAstronom,
						xTilt_local,
						yTilt_local,
						zOrient_local,
						gmx.timestamp,
						supplyVoltage_local,
						gmx.status);

		dataFrameParsed = 1;
	}
	else if (dataFrameFound && stationModel == WS_GMX301)
	{
		//Frame is like:
		//"Q 0999.4 0999.4 0999.4 040 +023.3 +009.0 08.41 2155 00.00 1.2 +015.0 07:58 12:08 16:19 163:+15 16:57 17:39 18:19 +00 +00 +1
		// 2018-01-16T10:58:40.7 +05.1 0000"

		//"%c %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[17])));
		sscanf (buffer_ws_raw, buffer_table,
						&node_letter_local,
						pressure_local,
						pressureSeaLevel_local,
						pressureStation_local,
						&gmx.relativeHumidity,
						temperature_local,
						dewpoint_local,
						absoluteHumidity_local,
						gmx.solarRadiation,
						sunshineHours_local,
						airDensity_local,
						wetBulbTemperature_local,
						gmx.sunriseTime,
						gmx.solarNoonTime,
						gmx.sunsetTime,
						gmx.sunPosition,
						gmx.twilightCivil,
						gmx.twilightNautical,
						gmx.twilightAstronom,
						xTilt_local,
						yTilt_local,
						zOrient_local,
						gmx.timestamp,
						supplyVoltage_local,
						gmx.status);

		dataFrameParsed = 1;
	}
	else if (dataFrameFound && stationModel == WS_GMX400)
	{
		//Frame is like:
		//"Q 0999.3 0999.3 0999.3 041 +023.2 +009.3 08.61 00000.000 000.000 N 1.2 +015.1 07:58 12:08 16:19 165:+16 16:57 17:39 18:19 +00 +00 +1
		// 2018-01-16T11:09:24.0 +05.1 0000"

		//"%c %s %s %s %d %s %s %s %s %s %c %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[18])));
		sscanf (buffer_ws_raw, buffer_table,
						&node_letter_local,
						pressure_local,
						pressureSeaLevel_local,
						pressureStation_local,
						&gmx.relativeHumidity,
						temperature_local,
						dewpoint_local,
						absoluteHumidity_local,
						precipTotal_local,
						precipIntensity_local,
						&precipStatus_local,
						airDensity_local,
						wetBulbTemperature_local,
						gmx.sunriseTime,
						gmx.solarNoonTime,
						gmx.sunsetTime,
						gmx.sunPosition,
						gmx.twilightCivil,
						gmx.twilightNautical,
						gmx.twilightAstronom,
						xTilt_local,
						yTilt_local,
						zOrient_local,
						gmx.timestamp,
						supplyVoltage_local,
						gmx.status);

		dataFrameParsed = 1;
	}
	else if (dataFrameFound && stationModel == WS_GMX500)
	{
		if (!gps)
		{
			//Frame is like:
			//"Q 056 000.04 115 000 000.00 000 000.00 000 0100 0999.2 0999.2 0999.2 041 +023.2 +009.2 08.56 059 1.2 +015.1 07:58 12:08 16:19 166:+16
			// 16:57 17:39 18:19 +00 +01 +1 2018-01-16T11:13:19.5 +05.0 0000"

			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[19])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							&gmx.compass,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status);

			dataFrameParsed = 1;
		}
#if GMX_GPS_OPTION > 1
		else
		{
			//Frame is like:
			//"Q 056 000.04 115 000 000.00 000 000.00 000 0100 0999.2 0999.2 0999.2 041 +023.2 +009.2 08.56 059 1.2 +015.1 07:58 12:08 16:19 166:+16
			// 16:57 17:39 18:19 +00 +01 +1 2018-01-16T11:13:19.5 +05.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"

			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[26])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							&gmx.compass,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status,
							gpsCorrectedSpeed_local,
							gpsAvgCorrectedSpeed_local,
							gpsCorrectedGustSpeed_local,
							&gmx.gpsCorrectedGustDirection,
							gmx.gpsLocation,
							&gmx.gpsHeading,
							gpsSpeed_local,
							gmx.gpsStatus);

			dataFrameParsed = 1;

		}
#endif
	}
	else if (dataFrameFound && stationModel == WS_GMX501)
	{
		if (!gps)
		{
			//Frame is like:
			//"Q,003,000.02,062,000,000.00,000,000.00,000,0100,0999.3,0999.3,0999.3,041,+023.3,+009.3,08.61,059,0001,00.00,,,1.2,+015.2,07:58,12:08,16:19,161:+15,16:57,17:39,18:19,+00,+00,+1,,2018-01-16T10:50:19.2,+05.0,0000"
			// faltan los datos de radiacion en el frame de ejemplo

			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[20])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							&gmx.compass,
							gmx.solarRadiation,
							sunshineHours_local,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status);

			dataFrameParsed = 1;
		}
#if GMX_GPS_OPTION > 1
		else
		{
			//Frame is like:
			//"Q,003,000.02,062,000,000.00,000,000.00,000,0100,0999.3,0999.3,0999.3,041,+023.3,+009.3,08.61,059,0001,00.00,,,1.2,+015.2,07:58,12:08,16:19,161:+15,16:57,17:39,18:19,+00,+00,+1,,2018-01-16T10:50:19.2,+05.0,0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"
			// faltan los datos de radiacion en el frame de ejemplo

			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[27])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							&gmx.compass,
							gmx.solarRadiation,
							sunshineHours_local,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status,
							gpsCorrectedSpeed_local,
							gpsAvgCorrectedSpeed_local,
							gpsCorrectedGustSpeed_local,
							&gmx.gpsCorrectedGustDirection,
							gmx.gpsLocation,
							&gmx.gpsHeading,
							gpsSpeed_local,
							gmx.gpsStatus);

			dataFrameParsed = 1;
		}
#endif
	}
	else if (dataFrameFound && (stationModel == WS_GMX531 || stationModel == WS_GMX541 || stationModel == WS_GMX551))
	{
		if (!gps)
		{
			//Frame is like:
			
			//"Q 264 000.05 052 000 000.00 000 000.00 000 0100 00000.000 000.000 N 148 1001.4 1001.4 1001.4 047 +025.2 +013.4 11.18 0006 00.00  +026 1.2 +017.9 06:49 11:47 16:46 153:+26 17:16 17:49 18:22 +03 -82 +1 2018-11-13T10:06:56.5 +11.8 0000"
			//"%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %d %s %s %s %d %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[21])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							precipTotal_local,
							precipIntensity_local,
							&precipStatus_local,
							&gmx.compass,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							gmx.solarRadiation,
							sunshineHours_local,
							windChill_local,
							gmx.heatIndex,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status);

			dataFrameParsed = 1;
		}
#if GMX_GPS_OPTION > 1
		else
		{
			//Frame is like:
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 00000.200 000.200 N 042 0001 01.20
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"

			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[28])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							precipTotal_local,
							precipIntensity_local,
							&precipStatus_local,
							&gmx.compass,
							gmx.solarRadiation,
							sunshineHours_local,
							windChill_local,
							gmx.heatIndex,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status,
							gpsCorrectedSpeed_local,
							gpsAvgCorrectedSpeed_local,
							gpsCorrectedGustSpeed_local,
							&gmx.gpsCorrectedGustDirection,
							gmx.gpsLocation,
							&gmx.gpsHeading,
							gpsSpeed_local,
							gmx.gpsStatus);

			dataFrameParsed = 1;
		}
#endif
	}
	else if (dataFrameFound && stationModel == WS_GMX550)
	{
		if (!gps)
		{
			//Frame is like:
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 00000.200 000.200 N 042
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"

			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[22])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							precipTotal_local,
							precipIntensity_local,
							&precipStatus_local,
							&gmx.compass,
							windChill_local,
							gmx.heatIndex,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status);

			dataFrameParsed = 1;
		}
#if GMX_GPS_OPTION > 1
		else
		{
			//Frame is like:
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 00000.200 000.200 N 042
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"

			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[29])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							precipTotal_local,
							precipIntensity_local,
							&precipStatus_local,
							&gmx.compass,
							windChill_local,
							gmx.heatIndex,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status,
							gpsCorrectedSpeed_local,
							gpsAvgCorrectedSpeed_local,
							gpsCorrectedGustSpeed_local,
							&gmx.gpsCorrectedGustDirection,
							gmx.gpsLocation,
							&gmx.gpsHeading,
							gpsSpeed_local,
							gmx.gpsStatus);

			dataFrameParsed = 1;
		}
#endif
	}
	else if (dataFrameFound && stationModel == WS_GMX600)
	{
		if (!gps)
		{
			//Frame is like:
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 042
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"

			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[23])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							&gmx.compass,
							windChill_local,
							gmx.heatIndex,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status);

			dataFrameParsed = 1;
		}
#if GMX_GPS_OPTION > 1
		else
		{
			//Frame is like:
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 042
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"

			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_xtr[30])));
			sscanf (buffer_ws_raw, buffer_table,
							&node_letter_local,
							&gmx.windDirection,
							windSpeed_local,
							&gmx.correctedWindDirection,
							&gmx.avgWindDirection,
							avgWindSpeed_local,
							&gmx.avgWindGustDirection,
							avgWindGustSpeed_local,
							&gmx.avgCorrectedWindDirection,
							gmx.windSensorStatus,
							pressure_local,
							pressureSeaLevel_local,
							pressureStation_local,
							&gmx.relativeHumidity,
							temperature_local,
							dewpoint_local,
							absoluteHumidity_local,
							&gmx.compass,
							windChill_local,
							gmx.heatIndex,
							airDensity_local,
							wetBulbTemperature_local,
							gmx.sunriseTime,
							gmx.solarNoonTime,
							gmx.sunsetTime,
							gmx.sunPosition,
							gmx.twilightCivil,
							gmx.twilightNautical,
							gmx.twilightAstronom,
							xTilt_local,
							yTilt_local,
							zOrient_local,
							gmx.timestamp,
							supplyVoltage_local,
							gmx.status,
							gpsCorrectedSpeed_local,
							gpsAvgCorrectedSpeed_local,
							gpsCorrectedGustSpeed_local,
							&gmx.gpsCorrectedGustDirection,
							gmx.gpsLocation,
							&gmx.gpsHeading,
							gpsSpeed_local,
							gmx.gpsStatus);

			dataFrameParsed = 1;
		}
#endif
	}




	if (dataFrameParsed == 1)
	{
		if (precipStatus_local == 'Y')
		{
			gmx.precipStatus = 1;
		}
		else
		{
			gmx.precipStatus = 0;
		}

		gmx.windSpeed = atof (windSpeed_local);
		gmx.avgWindSpeed = atof (avgWindSpeed_local);
		gmx.avgWindGustSpeed = atof (avgWindGustSpeed_local);
		gmx.precipTotal = atof (precipTotal_local);
		gmx.precipIntensity = atof (precipIntensity_local);
		gmx.xTilt = atof (xTilt_local);
		gmx.yTilt = atof (yTilt_local);
		gmx.zOrient = atof (zOrient_local);
		gmx.supplyVoltage = atof (supplyVoltage_local);
		gmx.sunshineHours = atof (sunshineHours_local);
		gmx.pressure = atof (pressure_local);
		gmx.pressureSeaLevel = atof (pressureSeaLevel_local);
		gmx.pressureStation = atof (pressureStation_local);
		gmx.temperature = atof (temperature_local);
		gmx.dewpoint = atof (dewpoint_local);
		gmx.absoluteHumidity = atof (absoluteHumidity_local);
		gmx.airDensity = atof (airDensity_local);
		gmx.wetBulbTemperature = atof (wetBulbTemperature_local);
		gmx.windChill = atof (windChill_local);
#ifdef GMX_GPS_OPTION
		gmx.gpsCorrectedSpeed_ = atof (gpsCorrectedSpeed_local);
		gmx.gpsAvgCorrectedSpeed = atof (gpsAvgCorrectedSpeed_local);
		gmx.gpsCorrectedGustSpeed = atof (gpsCorrectedGustSpeed_local);
		gmx.gpsSpeed = atof (gpsSpeed_local);
#endif

		return 1;
	}
	else
	{
		return 0;
	}
}


//******************************************************************************
// BME Sensor Class functions
//******************************************************************************

/*!
	\brief BME Class constructor
	\param socket selected socket for sensor
*/
bme::bme(uint8_t _socket)
{
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}


/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t bme::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_B)
			|| (socket == XTR_SOCKET_C)
			|| (socket == XTR_SOCKET_E)
			|| (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("BME280"));

		return 0;
	}

	SensorXtr.ON(REG_3V3);
	SensorXtr.set3v3(socket, SWITCH_ON);

	// switch ON I2C isolator Enable, detect if other sensor is already enabled
	if (socket == XTR_SOCKET_A && SensorXtr.bmeIsolatorEnabledSocketD == 0)
	{
		digitalWrite(I2C_SOCKETA_EN, HIGH);
		SensorXtr.bmeIsolatorEnabledSocketA = 1;
	}
	else if (socket == XTR_SOCKET_A && SensorXtr.bmeIsolatorEnabledSocketD == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[11])));
		PRINT_XTR(message);
		USB.println(F("BME280"));
		return 0;
	}
	else if (socket == XTR_SOCKET_D && SensorXtr.bmeIsolatorEnabledSocketA == 0)
	{
		digitalWrite(I2C_SOCKETD_EN, HIGH);
		SensorXtr.bmeIsolatorEnabledSocketD = 1;
	}
	else if (socket == XTR_SOCKET_D && SensorXtr.bmeIsolatorEnabledSocketA == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[11])));
		PRINT_XTR(message);
		USB.println(F("BME280"));
		return 0;
	}
	//neccessary delay after powering the sensor
	delay(10);

	// init BME
	BME.ON();

	return 1;
}



/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void bme::OFF()
{
	// switch OFF I2C isolator Enable
	if (socket == XTR_SOCKET_A)
	{
		digitalWrite(I2C_SOCKETA_EN, LOW);
		SensorXtr.bmeIsolatorEnabledSocketA = 0;
	}
	if (socket == XTR_SOCKET_D)
	{
		digitalWrite(I2C_SOCKETD_EN, LOW);
		SensorXtr.bmeIsolatorEnabledSocketD = 0;
	}

	SensorXtr.set3v3(socket, SWITCH_OFF);
	SensorXtr.OFF();

	// switch off delay for better preformance before
	// entering sleep mode after calling this function
	delay(100);
}


/*!
	\brief Read BME temperature value
	\param void
	\return temperature value
*/
float bme::getTemperature()
{
	float value = 0;

	value = BME.getTemperature(BME280_OVERSAMP_1X, 0);

#if DEBUG_XTR>0
	PRINT_XTR(F("Temperature:"));
	USB.println(value);
	PRINT_XTR(F("BME280_OVERSAMP_1X"));
	USB.println(BME280_OVERSAMP_1X);
#endif

	return value;
}

/*!
	\brief Read BME humidity value
	\param void
	\return humidity value
*/
float bme::getHumidity()
{
	float value = 0;

	// read the humidity from the BME280 Sensor
	value = BME.getHumidity(BME280_OVERSAMP_1X);
#if DEBUG_XTR>0
	PRINT_XTR(F("Humidity:"));
	USB.println(value);
	PRINT_XTR(F("BME280_OVERSAMP_1X"));
	USB.println(BME280_OVERSAMP_1X);
#endif

	return value;
}

/*!
	\brief Read BME pressure value
	\param void
	\return pressure value
*/
float bme::getPressure()
{
	float value = 0;

	// read the pressure from the BME280 Sensor
	value = BME.getPressure(BME280_OVERSAMP_1X, 0);
#if DEBUG_XTR>0
	PRINT_XTR(F("Pressure:"));
	USB.println(value);
	PRINT_XTR(F("BME280_OVERSAMP_1X"));
	USB.println(BME280_OVERSAMP_1X);
#endif

	return value;
}



//******************************************************************************
// Ultrasound Sensor Class functions
//******************************************************************************


/*!
	\brief Ultrasound Class constructor
	\param socket selected socket for sensor
*/
ultrasound::ultrasound(uint8_t _socket)
{
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}



/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t ultrasound::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_B)
			|| (socket == XTR_SOCKET_C)
			|| (socket == XTR_SOCKET_E)
			|| (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("Ultrasound"));

		return 0;
	}

	SensorXtr.ON(REG_3V3);
	SensorXtr.set3v3(socket, SWITCH_ON);

	// switch ON I2C isolator Enable, detect if other sensor is already enabled
	if (socket == XTR_SOCKET_A && SensorXtr.ultrasoundIsolatorEnabledSocketD == 0)
	{
		digitalWrite(I2C_SOCKETA_EN, HIGH);
		SensorXtr.ultrasoundIsolatorEnabledSocketA = 1;
	}
	else if (socket == XTR_SOCKET_A && SensorXtr.ultrasoundIsolatorEnabledSocketD == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[11])));
		PRINT_XTR(message);
		USB.println(F("ultrasound"));
		return 0;
	}
	else if (socket == XTR_SOCKET_D && SensorXtr.ultrasoundIsolatorEnabledSocketA == 0)
	{
		digitalWrite(I2C_SOCKETD_EN, HIGH);
		SensorXtr.ultrasoundIsolatorEnabledSocketD = 1;
	}
	else if (socket == XTR_SOCKET_D && SensorXtr.ultrasoundIsolatorEnabledSocketA == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[11])));
		PRINT_XTR(message);
		USB.println(F("ultrasound"));
		return 0;
	}


	//neccessary delay after powering the sensor
	delay(200);

	return 1;
}



/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void ultrasound::OFF()
{
	// switch OFF I2C isolator Enable
	if (socket == XTR_SOCKET_A)
	{
		digitalWrite(I2C_SOCKETA_EN, LOW);
		SensorXtr.ultrasoundIsolatorEnabledSocketA = 0;
	}
	if (socket == XTR_SOCKET_D)
	{
		digitalWrite(I2C_SOCKETD_EN, LOW);
		SensorXtr.ultrasoundIsolatorEnabledSocketD = 0;
	}

	SensorXtr.set3v3(socket, SWITCH_OFF);
	SensorXtr.OFF();

	// switch off delay for better preformance before
	// entering sleep mode after calling this function
	delay(100);
}


/*!
	\brief Performs a distance measurement
	\param void
	\return distance in cm.
			9000 if error reading the distance
			10000 if error reading the sensor
*/
uint16_t ultrasound::getDistance()
{
	return Ultrasound.getDistance();
}




//******************************************************************************
// Luxes Sensor Class functions
//******************************************************************************

/*!
	\brief Luxes Class constructor
	\param socket selected socket for sensor
*/
luxes::luxes(uint8_t _socket)
{
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}


/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t luxes::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_B)
			|| (socket == XTR_SOCKET_C)
			|| (socket == XTR_SOCKET_E)
			|| (socket == XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("Luxes"));

		return 0;
	}


	SensorXtr.ON(REG_3V3);
	SensorXtr.set3v3(socket, SWITCH_ON);

	// switch ON I2C isolator Enable, detect if other sensor is already enabled
	if (socket == XTR_SOCKET_A && SensorXtr.luxesIsolatorEnabledSocketD == 0)
	{
		digitalWrite(I2C_SOCKETA_EN, HIGH);
		SensorXtr.luxesIsolatorEnabledSocketA = 1;
	}
	else if (socket == XTR_SOCKET_A && SensorXtr.luxesIsolatorEnabledSocketD == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[11])));
		PRINT_XTR(message);
		USB.println(F("luxes"));
		return 0;
	}
	else if (socket == XTR_SOCKET_D && SensorXtr.luxesIsolatorEnabledSocketA == 0)
	{
		digitalWrite(I2C_SOCKETD_EN, HIGH);
		SensorXtr.luxesIsolatorEnabledSocketD = 1;
	}
	else if (socket == XTR_SOCKET_D && SensorXtr.luxesIsolatorEnabledSocketA == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[11])));
		PRINT_XTR(message);
		USB.println(F("luxes"));
		return 0;
	}


	//neccessary delay after powering the sensor
	delay(100);

	// init luxes sensor
	TSL.ON();

	return 1;
}


/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void luxes::OFF()
{
	// switch OFF I2C isolator Enable
	if (socket == XTR_SOCKET_A)
	{
		digitalWrite(I2C_SOCKETA_EN, LOW);
		SensorXtr.luxesIsolatorEnabledSocketA = 0;
	}
	if (socket == XTR_SOCKET_D)
	{
		digitalWrite(I2C_SOCKETD_EN, LOW);
		SensorXtr.luxesIsolatorEnabledSocketD = 0;
	}

	SensorXtr.set3v3(socket, SWITCH_OFF);
	SensorXtr.OFF();

	// switch off delay for better preformance before
	// entering sleep mode after calling this function
	delay(100);
}


/*!
	\brief Performs a luminosity measurement
	\param void
	\return luxes if ok, -1 if error
*/
uint32_t luxes::getLuminosity()
{
	uint8_t error;
	uint8_t retries = 3;

	do
	{
		// get luminosity
		error = TSL.getLuminosity();

		if (error == 0)
		{
			return TSL.lux;
		}
		retries--;
		I2C.recover();
	}
	while (retries > 0);

	return (uint32_t) - 1;
}


//******************************************************************************
// 4-20mA Sensor Class functions
//******************************************************************************

/*!
	\brief 4-20mA Class constructor
	\param socket selected socket for sensor
*/
_4_20mA::_4_20mA(uint8_t _socket)
{
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t _4_20mA::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_A)
			|| (socket == XTR_SOCKET_C)
			|| (socket == XTR_SOCKET_D)
			|| (socket == XTR_SOCKET_E))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("4-20mA"));

		return 0;
	}

	SensorXtr.ON(REG_3V3);
	SensorXtr.set12v(socket, SWITCH_ON);

	//neccessary delay after powering the sensor
	delay(10);

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void _4_20mA::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();
}


/*!
	\brief Reads the 4-20mA sensor
	\param void
	\return 0 if invalid data. Current value Otherwise.
*/
float _4_20mA::read()
{
	LTC ltc;			// object to manage ADC

	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();


	// necessary for the sensor
	delay(10);

	if (socket == XTR_SOCKET_F)
	{
		ltc.readADC(ADC_CH1);
		current = ltc.readADC(ADC_CH1);
	}
	else if (socket == XTR_SOCKET_B)
	{
		ltc.readADC(ADC_CH0);
		current = ltc.readADC(ADC_CH0);
	}
	else
	{
#if DEBUG_XTR == 1
		PRINT_XTR(F("wrong 4.20 socket "));
		USB.println(socket, DEC);
#endif
		return 0;
	}

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

#if DEBUG_XTR == 1
	PRINT_XTR(F("4.20: "));
	USB.printFloat(current, 4);
	USB.println();
#endif

	if ((current < 0) || (current > 5 ))
	{
#if DEBUG_XTR == 1
		PRINTLN_XTR(F("Unknown 4.20 error"));
#endif
		return 0;
	}
	else
	{
		return current;
	}

}


//******************************************************************************
// SU-100 Sensor Class functions
//******************************************************************************

/*!
	\brief SU100 Class constructor
	\param socket selected socket for sensor
*/

Apogee_SU100::Apogee_SU100(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}

}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SU100::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_A)
			|| (socket == XTR_SOCKET_D))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("SU100"));

		return 0;
	}

	SensorXtr.ON(REG_3V3);


	// necessary for POR of the ADC
	delay(10);

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Apogee_SU100::OFF()
{
	SensorXtr.OFF();
}



/*!
	\brief reads the SU100 sensor and converts its value into umol·m-2·s-1
	\param void
	\return 0 if invalid data. Measure otherwise
*/

float Apogee_SU100::read(void)
{
	// object to manage ADC
	LTC ltc;

	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();

	if (socket == XTR_SOCKET_B)
	{
		ltc.readADC(ADC_CH3);
		radiationVoltage = ltc.readADC(ADC_CH3);
	}
	if (socket == XTR_SOCKET_C)
	{
		ltc.readADC(ADC_CH5);
		radiationVoltage = ltc.readADC(ADC_CH5);
	}
	if (socket == XTR_SOCKET_E)
	{
		ltc.readADC(ADC_CH4);
		radiationVoltage = ltc.readADC(ADC_CH4);
	}
	if (socket == XTR_SOCKET_F)
	{
		ltc.readADC(ADC_CH2);
		radiationVoltage = ltc.readADC(ADC_CH2);
	}

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor in volts
#if DEBUG_XTR == 2
	PRINT_XTR(F("radiation (V): "));
	USB.printFloat(radiationVoltage, 5);
	USB.println();
#endif

	// Conversion from voltage into umol·m-2·s-1
	radiation = radiationVoltage / 0.0002;

	// check value of the sensor in mm
#if DEBUG_XTR == 1
	PRINT_XTR(F("radiation (umol*m-2*s-1): "));
	USB.printFloat(radiation, 5);
	USB.println();
#endif

	// No way to check if sensor missing.
	if (radiation <= 0)
	{
		// measure out of range
		return 0;
	}
	else
	{
		return radiation;
	}

}


//******************************************************************************
// SQ-110 Sensor Class functions
//******************************************************************************

/*!
	\brief SQ110 Class constructor
	\param socket selected socket for sensor
*/
Apogee_SQ110::Apogee_SQ110(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}

}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SQ110::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_A)
			|| (socket == XTR_SOCKET_D))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("SQ110"));

		return 0;
	}

	SensorXtr.ON(REG_3V3);

	// necessary for POR of the ADC
	delay(10);

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Apogee_SQ110::OFF()
{
	SensorXtr.OFF();
}



/*!
	\brief reads the SU100 sensor and converts its value into umol·m-2·s-1
	\param void
	\return 0 if invalid data. Measure otherwise
*/
float Apogee_SQ110::read(void)
{
	// object to manage ADC
	LTC ltc;

	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();

	if (socket == XTR_SOCKET_B)
	{
		ltc.readADC(ADC_CH3);
		radiationVoltage = ltc.readADC(ADC_CH3);
	}
	if (socket == XTR_SOCKET_C)
	{
		ltc.readADC(ADC_CH5);
		radiationVoltage = ltc.readADC(ADC_CH5);
	}
	if (socket == XTR_SOCKET_E)
	{
		ltc.readADC(ADC_CH4);
		radiationVoltage = ltc.readADC(ADC_CH4);
	}
	if (socket == XTR_SOCKET_F)
	{
		ltc.readADC(ADC_CH2);
		radiationVoltage = ltc.readADC(ADC_CH2);
	}

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor in volts
#if DEBUG_XTR == 2
	PRINT_XTR(F("radiation (V): "));
	USB.printFloat(radiationVoltage, 5);
	USB.println();
#endif

	// Conversion from voltage into umol·m-2·s-1
	radiation = radiationVoltage / 0.0002;

	// check value of the sensor in mm
#if DEBUG_XTR == 1
	PRINT_XTR(F("radiation (umol*m-2*s-1): "));
	USB.printFloat(radiation, 5);
	USB.println();
#endif

	// No way to check if sensor missing.
	if (radiation <= 0)
	{
		// measure out of range
		return 0;
	}
	else
	{
		return radiation;
	}

}


//******************************************************************************
// SP-510 Sensor Class functions
//******************************************************************************

/*!
	\brief SP510 Class constructor
	\param socket selected socket for sensor
*/
Apogee_SP510::Apogee_SP510(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}

}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Apogee_SP510::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if ((socket == XTR_SOCKET_A)
			|| (socket == XTR_SOCKET_D))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("SP510"));

		return 0;
	}

	SensorXtr.ON(REG_3V3);

	//Turn on the heater
	SensorXtr.set12v(socket, SWITCH_ON);

	// necessary for POR of the ADC
	delay(10);

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Apogee_SP510::OFF()
{
	//Turn off the heater
	SensorXtr.set12v(socket, SWITCH_OFF);
	SensorXtr.OFF();
}


/*!
	\brief reads the SU100 sensor and converts its value into umol·m-2·s-1
	\param void
	\return 0 if invalid data. Measure otherwise.
*/
float Apogee_SP510::read(void)
{
	// object to manage ADC
	LTC ltc;

	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();

	if (socket == XTR_SOCKET_B)
	{
		ltc.readADC(ADC_CH3);
		radiationVoltage = ltc.readADC(ADC_CH3);
	}
	if (socket == XTR_SOCKET_C)
	{
		ltc.readADC(ADC_CH5);
		radiationVoltage = ltc.readADC(ADC_CH5);
	}
	if (socket == XTR_SOCKET_E)
	{
		ltc.readADC(ADC_CH4);
		radiationVoltage = ltc.readADC(ADC_CH4);
	}
	if (socket == XTR_SOCKET_F)
	{
		ltc.readADC(ADC_CH2);
		radiationVoltage = ltc.readADC(ADC_CH2);
	}

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor in volts
#if DEBUG_XTR == 2
	PRINT_XTR(F("radiation (V): "));
	USB.printFloat(radiationVoltage, 5);
	USB.println();
#endif

	// Conversion from voltage into W*m-2
	radiation = radiationVoltage * 17.543;

	// check value of the sensor in mm
#if DEBUG_XTR == 1
	PRINT_XTR(F("radiation (W*m-2): "));
	USB.printFloat(radiation, 5);
	USB.println();
#endif

	// No way to check if sensor missing.
	if (radiation <= 0)
	{
		// measure out of range
		return 0;
	}
	else
	{
		return radiation;
	}

}

/*!
	\brief Turns on and off the heater of the sensor
	\param ON or OFF
	\return void
*/
void Apogee_SP510::heater(uint8_t state)
{
	SensorXtr.ON(REG_3V3);
	SensorXtr.set12v(socket, state);
}




/*******************************************************************************
	Smart Water Xtreme
 ******************************************************************************/


/*	OPTOD: Class constructor
		Parameters: void
		Return: void
*/
Aqualabo_OPTOD::Aqualabo_OPTOD(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_OPTOD::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if (socket == XTR_SOCKET_F)
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("OPTOD"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_ON);

		//Set modbus address and modbus waiting time acording to sensor
		modbusSensorsXtr.setParametersBySensor(OPTOD);
	}
	//The rest of the sockets use SDI-12
	else
	{
		//neccessary delay after powering the sensor
		delay(1000);
	}

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Aqualabo_OPTOD::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_OFF);
	}
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return void
*/
uint8_t Aqualabo_OPTOD::read()
{
	// Initialize variables
	sensorOPTOD.temperature = 0;
	sensorOPTOD.oxygenSAT = 0;
	sensorOPTOD.oxygenMGL = 0;
	sensorOPTOD.oxygenPPM = 0;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{

		//Socket E is the only with RS-485
		if (socket == XTR_SOCKET_E)
		{
			response = modbusSensorsXtr.readMeasures(	sensorOPTOD.temperature,
														sensorOPTOD.oxygenSAT,
														sensorOPTOD.oxygenMGL,
														sensorOPTOD.oxygenPPM);
		}
		//The rest of the sockets use SDI-12
		else
		{
			SensorXtr.setMux(socket, ENABLED);

			memset(sensorOPTOD.sensorSerialNumber, 0x00, sizeof(sensorOPTOD.sensorSerialNumber));

			response = sdi12SensorXtr.readMeasures(	OPTOD,
													sensorOPTOD.sensorSerialNumber,
													sensorOPTOD.temperature,
													sensorOPTOD.oxygenSAT,
													sensorOPTOD.oxygenMGL,
													sensorOPTOD.oxygenPPM);
																									
			SensorXtr.setMux(socket, DISABLED);
		}

		if ((sensorOPTOD.temperature != 0)
		|| (sensorOPTOD.oxygenSAT != 0)
		|| (sensorOPTOD.oxygenMGL != 0)
		|| (sensorOPTOD.oxygenPPM != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	return response;
}


/* readSerialNumber: Gets the serial number of the sensor
	parameters: void
	return: 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_OPTOD::readSerialNumber()
{
	memset(sensorOPTOD.sensorSerialNumber, 0x00, sizeof(sensorOPTOD.sensorSerialNumber));

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		uint8_t response = modbusSensorsXtr.readSerialNumber(sensorOPTOD.sensorSerialNumber);
	}
	//The rest of the sockets use SDI-12
	else
	{
		return read();
	}
}



/*	PHEHT: Class constructor
		Parameters: void
		Return: void
*/
Aqualabo_PHEHT::Aqualabo_PHEHT(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_PHEHT::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if (socket == XTR_SOCKET_F)
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("PHEHT"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_ON);

		//Set modbus address and modbus waiting time acording to sensor
		modbusSensorsXtr.setParametersBySensor(PHEHT);
	}
	//The rest of the sockets use SDI-12
	else
	{
		//neccessary delay after powering the sensor for SDI-12
		delay(1000);
	}

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Aqualabo_PHEHT::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_OFF);
	}
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_PHEHT::read()
{
	// Initialize variables
	sensorPHEHT.temperature = 0;
	sensorPHEHT.pH = 0;
	sensorPHEHT.redox = 0;
	sensorPHEHT.pHMV = 0;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		//Socket E is the only with RS-485
		if (socket == XTR_SOCKET_E)
		{
			response = modbusSensorsXtr.readMeasures(	sensorPHEHT.temperature,
														sensorPHEHT.pH,
														sensorPHEHT.redox,
														sensorPHEHT.pHMV);
		}
		//The rest of the sockets use SDI-12
		else
		{
			SensorXtr.setMux(socket, ENABLED);

			memset(sensorPHEHT.sensorSerialNumber, 0x00, sizeof(sensorPHEHT.sensorSerialNumber));

			response = sdi12SensorXtr.readMeasures(	PHEHT,
													sensorPHEHT.sensorSerialNumber,
													sensorPHEHT.temperature,
													sensorPHEHT.pH,
													sensorPHEHT.redox,
													sensorPHEHT.pHMV);

			SensorXtr.setMux(socket, DISABLED);
		}

		if ((sensorPHEHT.temperature != 0)
				|| (sensorPHEHT.pH != 0)
				|| (sensorPHEHT.redox != 0)
				|| (sensorPHEHT.pHMV != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}


	return response;
}


/* readSerialNumber: Gets the serial number of the sensor
	parameters: void
	return: 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_PHEHT::readSerialNumber()
{
	memset(sensorPHEHT.sensorSerialNumber, 0x00, sizeof(sensorPHEHT.sensorSerialNumber));

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		uint8_t response = modbusSensorsXtr.readSerialNumber(sensorPHEHT.sensorSerialNumber);
	}
	//The rest of the sockets use SDI-12
	else
	{
		return read();
	}
}





/*	C4E: Class constructor
		Parameters: void
		Return: void
*/
Aqualabo_C4E::Aqualabo_C4E(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_C4E::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if (socket == XTR_SOCKET_F)
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("C4E"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_ON);

		//Set modbus address and modbus waiting time acording to sensor
		modbusSensorsXtr.setParametersBySensor(C4E);
	}
	//The rest of the sockets use SDI-12
	else
	{
		//neccessary delay after powering the sensor
		delay(500);
	}
#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Aqualabo_C4E::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_OFF);
	}
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return void
*/
uint8_t Aqualabo_C4E::read()
{
	// Initialize variables
	sensorC4E.temperature = 0;
	sensorC4E.conductivity = 0;
	sensorC4E.salinity = 0;
	sensorC4E.totalDissolvedSolids = 0;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		//Socket E is the only with RS-485
		if (socket == XTR_SOCKET_E)
		{
			response = modbusSensorsXtr.readMeasures(	sensorC4E.temperature,
														sensorC4E.conductivity,
														sensorC4E.conductivity,
														sensorC4E.totalDissolvedSolids);
		}
		//The rest of the sockets use SDI-12
		else
		{
			SensorXtr.setMux(socket, ENABLED);

			response = sdi12SensorXtr.readMeasures(	C4E,
													sensorC4E.sensorSerialNumber,
													sensorC4E.temperature,
													sensorC4E.conductivity,
													sensorC4E.salinity,
													sensorC4E.totalDissolvedSolids);

			SensorXtr.setMux(socket, DISABLED);
		}

		if ((sensorC4E.temperature != 0)
		|| (sensorC4E.conductivity != 0)
		|| (sensorC4E.salinity != 0)
		|| (sensorC4E.totalDissolvedSolids != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	return response;
}


/* readSerialNumber: Gets the serial number of the sensor
	parameters: void
	return: 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_C4E::readSerialNumber()
{
	memset(sensorC4E.sensorSerialNumber, 0x00, sizeof(sensorC4E.sensorSerialNumber));

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		uint8_t response = modbusSensorsXtr.readSerialNumber(sensorC4E.sensorSerialNumber);
	}
	//The rest of the sockets use SDI-12
	else
	{
		return read();
	}
}



/*	NTU: Class constructor
		Parameters: void
		Return: void
*/
Aqualabo_NTU::Aqualabo_NTU(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_NTU::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if (socket == XTR_SOCKET_F)
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("NTU"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_ON);

		//Set modbus address and modbus waiting time acording to sensor
		modbusSensorsXtr.setParametersBySensor(NTU);
	}
	//The rest of the sockets use SDI-12
	else
	{
		//neccessary delay after powering the sensor for SDI-12
		delay(1000);
	}

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Aqualabo_NTU::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_OFF);
	}
	SensorXtr.OFF();
}




/*!
	\brief Reads the sensor data
	\param void
	\return 0 is OK, 1 if error
*/
uint8_t Aqualabo_NTU::read()
{
	// Initialize variables
	sensorNTU.temperature = 0;
	sensorNTU.turbidityNTU = 0;
	float parameter3_dummy = 0; //turbidityFNU is always equal to turbidityNTU
	sensorNTU.turbidityMGL = 0;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		//Socket E is the only with RS-485
		if (socket == XTR_SOCKET_E)
		{
			response = modbusSensorsXtr.readMeasures(	sensorNTU.temperature,
														sensorNTU.turbidityNTU,
														parameter3_dummy,
														sensorNTU.turbidityMGL);
		}
		//The rest of the sockets use SDI-12
		else
		{
			SensorXtr.setMux(socket, ENABLED);

			response = sdi12SensorXtr.readMeasures(	NTU,
													sensorNTU.sensorSerialNumber,
													sensorNTU.temperature,
													sensorNTU.turbidityNTU,
													parameter3_dummy,
													sensorNTU.turbidityMGL);

			SensorXtr.setMux(socket, DISABLED);

		}

		if ((sensorNTU.temperature != 0)
		|| (sensorNTU.turbidityNTU != 0)
		|| (parameter3_dummy != 0)
		|| (sensorNTU.turbidityMGL != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	return response;
}

/* readSerialNumber: Gets the serial number of the sensor
	parameters: void
	return: 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_NTU::readSerialNumber()
{
	memset(sensorNTU.sensorSerialNumber, 0x00, sizeof(sensorNTU.sensorSerialNumber));

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		uint8_t response = modbusSensorsXtr.readSerialNumber(sensorNTU.sensorSerialNumber);
	}
	//The rest of the sockets use SDI-12
	else
	{
		return read();
	}
}




/*	CTZN: Class constructor
		Parameters: void
		Return: void
*/
Aqualabo_CTZN::Aqualabo_CTZN(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_CTZN::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if (socket == XTR_SOCKET_F)
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("CTZN"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_ON);

		//Set modbus address and modbus waiting time acording to sensor
		modbusSensorsXtr.setParametersBySensor(CTZN);
	}
	//The rest of the sockets use SDI-12
	else
	{
		//neccessary delay after powering the sensor
		delay(1000);
	}
#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Aqualabo_CTZN::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_OFF);
	}
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return void
*/
uint8_t Aqualabo_CTZN::read()
{
	// Initialize variables
	sensorCTZN.temperature = 0;
	sensorCTZN.conductivity = 0;
	sensorCTZN.salinity = 0;
	sensorCTZN.conductivityNotCompensated = 0;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{
		//Socket E is the only with RS-485
		if (socket == XTR_SOCKET_E)
		{
			response = modbusSensorsXtr.readMeasures(	sensorCTZN.temperature,
														sensorCTZN.conductivity,
														sensorCTZN.salinity,
														sensorCTZN.conductivityNotCompensated);
		}
		//The rest of the sockets use SDI-12
		else
		{
			SensorXtr.setMux(socket, ENABLED);

			response = sdi12SensorXtr.readMeasures(	CTZN,
													sensorCTZN.sensorSerialNumber,
													sensorCTZN.temperature,
													sensorCTZN.conductivity,
													sensorCTZN.salinity,
													sensorCTZN.conductivityNotCompensated);

			SensorXtr.setMux(socket, DISABLED);

		}

		if ((sensorCTZN.temperature != 0)
		|| (sensorCTZN.conductivity != 0)
		|| (sensorCTZN.salinity != 0)
		|| (sensorCTZN.conductivityNotCompensated != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}
	return response;
}


/* readSerialNumber: Gets the serial number of the sensor
	parameters: void
	return: 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_CTZN::readSerialNumber()
{
	memset(sensorCTZN.sensorSerialNumber, 0x00, sizeof(sensorCTZN.sensorSerialNumber));

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		uint8_t response = modbusSensorsXtr.readSerialNumber(sensorCTZN.sensorSerialNumber);
	}
	//The rest of the sockets use SDI-12
	else
	{
		return read();
	}
}



/*	MES5: Class constructor
		Parameters: void
		Return: void
*/
Aqualabo_MES5::Aqualabo_MES5(uint8_t _socket)
{
	// store sensor location
	socket = _socket;

	if (bitRead(SensorXtr.socketRegister, socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		SensorXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(SensorXtr.socketRegister, socket);
	}
}

/*!
	\brief Turns on the sensor
	\param void
	\return 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_MES5::ON()
{
	char message[70];

	if (SensorXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[6])));
		PRINTLN_XTR(message);
	}

	if (socket == XTR_SOCKET_F)
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_xtr[7])));
		PRINT_XTR(message);
		USB.println(F("MES5"));

		return 0;
	}

	SensorXtr.ON(); //SDI12 needs both 3v3 and 5v
	SensorXtr.set12v(socket, SWITCH_ON);

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_ON);

		//Set modbus address and modbus waiting time acording to sensor
		modbusSensorsXtr.setParametersBySensor(MES5);
	}
	//The rest of the sockets use SDI-12
	else
	{
		//neccessary delay after powering the sensor
		delay(1000);
	}

#if DEBUG_XTR == 2
	//"socket (!): "
	strcpy_P(message, (char*)pgm_read_word(&(table_xtr[10])));
	PRINT_XTR(message);
	USB.println(socket, DEC);
#endif

	return 1;
}

/*!
	\brief Turns off the sensor
	\param void
	\return void
*/
void Aqualabo_MES5::OFF()
{
	SensorXtr.set12v(socket, SWITCH_OFF);
	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		//Enable RS-485 chip on (shared with 3v3 pin)
		SensorXtr.set3v3(socket, SWITCH_OFF);
	}
	SensorXtr.OFF();

}

/*!
	\brief Reads the sensor data
	\param void
	\return void
*/
uint8_t Aqualabo_MES5::read()
{
	// Initialize variables
	sensorMES5.temperature = 0;
	sensorMES5.sludgeBlanket = 0;
	sensorMES5.suspendedSolids = 0;
	sensorMES5.turbidityFAU = 0;

	uint8_t response = 0;
	uint8_t validMeasure = 0;
	uint8_t retries = 0;

	while ((validMeasure == 0) && (retries < 3))
	{

		//Socket E is the only with RS-485
		if (socket == XTR_SOCKET_E)
		{
			response = modbusSensorsXtr.readMeasures(	sensorMES5.temperature,
														sensorMES5.sludgeBlanket,
														sensorMES5.suspendedSolids,
														sensorMES5.turbidityFAU);
		}
		//The rest of the sockets use SDI-12
		else
		{
			SensorXtr.setMux(socket, ENABLED);

			response = sdi12SensorXtr.readMeasures(	MES5,
													sensorMES5.sensorSerialNumber,
													sensorMES5.temperature,
													sensorMES5.sludgeBlanket,
													sensorMES5.suspendedSolids,
													sensorMES5.turbidityFAU);

			SensorXtr.setMux(socket, DISABLED);
		}

		if ((sensorMES5.temperature != 0)
		|| (sensorMES5.sludgeBlanket != 0)
		|| (sensorMES5.suspendedSolids != 0)
		|| (sensorMES5.turbidityFAU != 0))
		{
			validMeasure = 1;
		}
		else
		{
			delay(1000);
		}
		retries++;
	}

	return response;
}



/* readSerialNumber: Gets the serial number of the sensor
	parameters: void
	return: 1 if ok, 0 if something fails
*/
uint8_t Aqualabo_MES5::readSerialNumber()
{
	memset(sensorMES5.sensorSerialNumber, 0x00, sizeof(sensorMES5.sensorSerialNumber));

	//Socket E is the only with RS-485
	if (socket == XTR_SOCKET_E)
	{
		uint8_t response = modbusSensorsXtr.readSerialNumber(sensorMES5.sensorSerialNumber);
	}
	//The rest of the sockets use SDI-12
	else
	{
		return read();
	}
}



//! class constructor
WaspSensorWaterXtr::WaspSensorWaterXtr()
{
}

/*!
	\brief Configure the sensor
	\param void
	\return 0 if ok, 1 if error
*/
uint8_t WaspSensorWaterXtr::init()
{
	return modbusSensorsXtr.initSensor();
}

/*!
	\brief Configure the sensor
	\param void
	\return 0 if ok, 1 if error
*/
uint8_t WaspSensorWaterXtr::init(uint8_t range)
{
	return modbusSensorsXtr.initSensor(range);
}


/*!
	\brief Configure the sensor
	\param void
	\return 0 if ok, 1 if error
*/
uint8_t WaspSensorWaterXtr::init(uint8_t range, uint8_t avg)
{
	return modbusSensorsXtr.initSensor(range, avg);
}

/*!
	\brief calibrates sensor
	\param void
	\return 0 if ok, 1 if error
*/
uint8_t WaspSensorWaterXtr::calibrate(uint8_t sensor, uint8_t parameter, uint8_t step, float value)
{
	return modbusSensorsXtr.calibrate(sensor, parameter, step, value);
}



/*!
	\brief Fill Operators Name
	\param void
	\return 0 if ok, 1 if error
*/
void WaspSensorWaterXtr::fillOperatorsName(char* name)
{
	memset(modbusSensorsXtr.calibrationOperatorsName, 0x00, sizeof(modbusSensorsXtr.calibrationOperatorsName));
	strcpy(modbusSensorsXtr.calibrationOperatorsName, name);
}


/*!
	\brief Fill Operators Name
	\param void
	\return 0 if ok, 1 if error
*/
void WaspSensorWaterXtr::fillCalibrationDate(char* date)
{
	memset(modbusSensorsXtr.calibrationDate, 0x00, sizeof(modbusSensorsXtr.calibrationDate));
	strcpy(modbusSensorsXtr.calibrationDate, date);
}

/*!
	\brief restore to factory calibration
	\param void
	\return 0 if ok, 1 if error
*/
uint8_t WaspSensorWaterXtr::restoreToFactoryCalibration(uint8_t parameter)
{
	return modbusSensorsXtr.restoreToFactoryCalibration(parameter);
}

/*!
	\brief neccessary to do this if exiting during a calibration without considering anything
	\param void
	\return 0 if ok, 1 if error
*/
uint8_t WaspSensorWaterXtr::resetTemporaryCalibrationData(uint8_t returnAvgTo1)
{
	return modbusSensorsXtr.resetTemporaryCalibrationData(returnAvgTo1);
}


/*!
	\brief menu assisted calibration process
	\param sensorType and parameter
	\return void
*/
void Aqualabo_OPTOD::calibrationProcess(uint8_t parameter)
{
	const uint8_t inputSize = 100;
	char input[inputSize];
	uint8_t response = 0;
	float offset = 0;
	float slope = 0;

	printBigLine();
	USB.println(F("MENU ASSISTED CALIBRATION PROCESS"));
	USB.println(F("OPTOD sensor"));

	if (parameter == TEMPERATURE)
	{
		USB.println(F("Temperature parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nFor this process it is advisable to use a reference temperature sensor."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0*C is recommended (Sensor fully immersed in an ice/water bath)"));
		USB.println(F("Example: 0.350"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(OPTOD, TEMPERATURE, STEP_1, NULL);

			offset = atof(input);

			printLine();
			USB.print(F("2. Set sensor at selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F("*C."));
			USB.println(F("Wait some minutes until the measure stabilizes."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorOPTOD.temperature, 2);
					USB.println(F("*C"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(OPTOD, TEMPERATURE, STEP_2, offset);

				printLine();
				USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
				USB.println(F("25*C is recommended (Sensor fully immersed in a bath heated at 25*C)"));
				USB.println(F("Example: 25.140"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("4. Immerse the sensor in water at your selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F("*C."));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorOPTOD.temperature, 2);
							USB.println(F("*C"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(OPTOD, TEMPERATURE, STEP_3, slope);

						printLine();
						USB.println(F("5. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("6.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						calibrate(OPTOD, TEMPERATURE, STEP_4, NULL);

						printLine();

						USB.println(F("Calibration successfully finished!"));
					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

	if (parameter == OXYGEN)
	{
		uint8_t calibrationMethod = 0;

		USB.println(F("Oxygen parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nYou can choose between one or two-point calibration method. At the end of the"));
		USB.println(F("process the results of the calibration will be stored in the FLASH memory of the"));
		USB.println(F("sensor for future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit."));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert '1' for one point calibration or '2' for two point calibration method"));
		USB.println(F("and press Enter."));
		USB.println(F("Example: 1"));
		USB.print(F("> "));

		serialClean();
		while ((find((uint8_t*)input, strlen(input), "1") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
			&& (find((uint8_t*)input, strlen(input), "2") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
		{

			getData(input, inputSize);

		}

		USB.println(input);

		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(OPTOD, OXYGEN, STEP_1, NULL);
			
			calibrationMethod = atoi(input);

			//only slope
			if (calibrationMethod == 1)
			{
				USB.println(F("One point calibration method selected"));

				slope = 100;

				printLine();
				USB.println(F("2. Set sensor at standart slope: 100%"));
				USB.println(F("Wait some minutes until the measure stabilizes."));
				USB.println(F("Then insert 'N' for Next step and press Enter."));

				serialClean();
				memset(input, 0x00, sizeof(input));

				uint16_t j = 300;
				while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
					&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
				{
					j++;
					if (j >= 300)
					{
						j = 0;

						read();
						USB.println();
						USB.printFloat(sensorOPTOD.oxygenSAT, 2);
						USB.println(F(" %"));
						USB.print(F("> "));
					}

					getData(input, inputSize);
					delay(10);
				}

				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{
					//In step 3 user select calibration standard 2 (slope)
					//This step must be done after stabilizing and measuring in water with
					//the selected value
					calibrate(OPTOD, OXYGEN, STEP_3, slope);

					printLine();
					USB.println(F("3. In order to validate the calibration some data is required."));
					USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
					USB.print(F("> "));

					serialClean();
					while (getData(input, inputSize) == 0);

					char calibrationOperatorsName_temp[17];
					memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
					strcpy(calibrationOperatorsName_temp, input);


					for (int k = strlen(input); k < 16; k++)
					{
						calibrationOperatorsName_temp[k] = ' ';
					}

					USB.println(calibrationOperatorsName_temp);
					fillOperatorsName(calibrationOperatorsName_temp);

					printLine();
					USB.println(F("4.Please insert calibration date."));


					int year;
					int month;
					int day;
					int hour;
					int minute;

					char calibrationDate_temp[17];
					memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
					/////////////////////////////////
					//	YEAR
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert year [yy] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					year = atoi(input);
					USB.println(year);


					/////////////////////////////////
					//	MONTH
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert month [mm] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					month = atoi(input);
					USB.println(month);


					/////////////////////////////////
					//	DAY
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert day [dd] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					day = atoi(input);
					USB.println(day);


					/////////////////////////////////
					//	HOUR
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert Hour [HH] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					hour = atoi(input);
					USB.println(hour);

					/////////////////////////////////
					//	MINUTE
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert minute [MM] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					minute = atoi(input);
					USB.println(minute);


					/////////////////////////////////
					//	create buffer
					/////////////////////////////////
					sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
									minute,
									hour,
									day,
									month,
									year );


					calibrationDate_temp[12] = ' ';
					calibrationDate_temp[13] = ' ';
					calibrationDate_temp[14] = ' ';
					calibrationDate_temp[15] = ' ';

					//USB.println(calibrationDate_temp);

					fillCalibrationDate(calibrationDate_temp);


					//In step 4 user validates the entire calibration entering operator's name and date
					calibrate(OPTOD, OXYGEN, STEP_4, NULL);

					printLine();

					USB.println(F("Calibration successfully finished!"));
				}


			}

			if (calibrationMethod == 2)
			{
				USB.println(F("Two point calibration method selected"));

				printLine();
				USB.println(F("2. Set sensor at standard offset: 0%"));
				USB.println(F("Wait some minutes until the measure stabilizes."));
				USB.println(F("Then insert 'N' for Next step and press Enter."));

				offset = 0;

				serialClean();
				memset(input, 0x00, sizeof(input) );
				uint16_t j = 300;
				while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
							&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
				{
					j++;
					if (j >= 300)
					{
						j = 0;

						read();
						USB.println();
						USB.printFloat(sensorOPTOD.oxygenSAT, 2);
						USB.println(F(" %"));
						USB.print(F("> "));
					}

					getData(input, inputSize);
					delay(10);
				}

				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{
					//In step 2 user select calibration standard 1 (offset)
					//This step must be done after stabilizing and measuring in water with
					//the selected value using readMeasures function previosly
					calibrate(OPTOD, OXYGEN, STEP_2, offset);


					slope = 100;

					printLine();
					USB.println(F("5. Set sensor at standart slope: 100%"));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();
					memset(input, 0x00, sizeof(input));

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorOPTOD.oxygenSAT, 2);
							USB.println(F(" %"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(OPTOD, OXYGEN, STEP_3, slope);

						printLine();
						USB.println(F("6. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("7.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						calibrate(OPTOD, OXYGEN, STEP_4, NULL);

						printLine();

						USB.println(F("Calibration successfully finished!"));
					}

				}
			}


		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}
}

/*!
	\brief menu assisted calibration process
	\param sensorType and parameter
	\return void
*/
void Aqualabo_PHEHT::calibrationProcess(uint8_t parameter)
{
	const uint8_t inputSize = 100;
	char input[inputSize];
	uint8_t response = 0;
	float offset = 0;
	float slope = 0;

	printBigLine();
	USB.println(F("MENU ASSISTED CALIBRATION PROCESS"));
	USB.println(F("PHEHT sensor"));

	if (parameter == TEMPERATURE)
	{
		USB.println(F("Temperature parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nFor this process it is advisable to use a reference temperature sensor."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0*C is recommended (Sensor fully immersed in an ice/water bath)"));
		USB.println(F("Example: 0.350"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(PHEHT, TEMPERATURE, STEP_1, NULL);

			offset = atof(input);

			printLine();
			USB.print(F("2. Set sensor at selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F("*C."));
			USB.println(F("Wait some minutes until the measure stabilizes."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorPHEHT.temperature, 2);
					USB.println(F("*C"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(PHEHT, TEMPERATURE, STEP_2, offset);

				printLine();
				USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
				USB.println(F("25*C is recommended (Sensor fully immersed in a bath heated at 25*C)"));
				USB.println(F("Example: 25.140"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("4. Immerse the sensor in water at your selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F("*C."));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorPHEHT.temperature, 2);
							USB.println(F("*C"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(PHEHT, TEMPERATURE, STEP_3, slope);

						printLine();
						USB.println(F("5. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("6.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						calibrate(PHEHT, TEMPERATURE, STEP_4, NULL);

						printLine();

						USB.println(F("Calibration successfully finished!"));
					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

	if (parameter == PH)
	{
		uint8_t calibrationMethod = 0;
		
		USB.println(F("pH parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nYou can choose between two or three-point calibration method."));
		USB.println(F("At the end of the process the results of the calibration will be "));
		USB.println(F("stored in the FLASH memory of the sensor for future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		
		USB.println(F("1. Insert '2' for two point calibration or '3' for three point calibration method"));
		USB.println(F("and press Enter."));
		USB.println(F("Example: 3"));
		USB.print(F("> "));

		serialClean();
		while ((find((uint8_t*)input, strlen(input), "2") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
			&& (find((uint8_t*)input, strlen(input), "3") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
		{

			getData(input, inputSize);

		}

		USB.println(input);

		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			calibrationMethod = atoi(input);

			
			if (calibrationMethod == 2)
			{
				USB.println(F("Two point calibration method selected"));
				
				USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
				USB.println(F("Example: 4"));
				USB.print(F("> "));


				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{
					//In step 1 we reset temporary calibration data and indicate the range (no range)
					calibrate(PHEHT, PH, STEP_1, NULL);

					offset = atof(input);

					printLine();
					USB.print(F("2. Place the sensor at selected offset: pH "));
					USB.printFloat(offset, 4);
					USB.println(F(""));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Observing the offset in this step will help you assess whether calibration"));
					USB.println(F("is necessary or not, depending on the precision required in your application."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();
					memset(input, 0x00, sizeof(input) );
					uint16_t j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorPHEHT.pH, 2);
							USB.println(F(""));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 2 user select calibration standard 1 (offset)
						//This step must be done after stabilizing and measuring in water with
						//the selected value using readMeasures function previosly
						calibrate(PHEHT, PH, STEP_2, offset);

						printLine();
						USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
						USB.println(F("Example: 7"));
						USB.print(F("> "));

						serialClean();
						while ( getData(input, inputSize) == 0 );
						USB.println(input);
						if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
						{
							//Exit discarding changes
							exitCalibration();
						}
						else
						{

							slope = atof(input);

							printLine();
							USB.print(F("4. Place the sensor at selected slope: pH "));
							USB.printFloat(slope, 4);
							USB.println(F(""));
							USB.println(F("Wait some minutes until the measure stabilizes."));
							USB.println(F("Then insert 'N' for Next step and press Enter."));

							serialClean();

							j = 300;
							while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
										&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
							{
								j++;
								if (j >= 300)
								{
									j = 0;

									read();
									USB.println();
									USB.printFloat(sensorPHEHT.pH, 2);
									USB.println(F(""));
									USB.print(F("> "));
								}

								getData(input, inputSize);
								delay(10);
							}

							USB.println(input);
							if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
							{
								//Exit discarding changes
								exitCalibration();
							}
							else
							{
								//In step 3 user select calibration standard 2 (slope)
								//This step must be done after stabilizing and measuring in water with
								//the selected value
								calibrate(PHEHT, PH, STEP_3, slope);

								printLine();
								USB.println(F("5. In order to validate the calibration some data is required."));
								USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
								USB.print(F("> "));

								serialClean();
								while (getData(input, inputSize) == 0);

								char calibrationOperatorsName_temp[17];
								memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
								strcpy(calibrationOperatorsName_temp, input);


								for (int k = strlen(input); k < 16; k++)
								{
									calibrationOperatorsName_temp[k] = ' ';
								}

								USB.println(calibrationOperatorsName_temp);
								fillOperatorsName(calibrationOperatorsName_temp);

								printLine();
								USB.println(F("6.Please insert calibration date."));


								int year;
								int month;
								int day;
								int hour;
								int minute;

								char calibrationDate_temp[17];
								memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
								/////////////////////////////////
								//	YEAR
								/////////////////////////////////
								serialClean();
								do
								{
									USB.println("Insert year [yy] and press Enter.");
									USB.print(F("> "));
								}
								while ( getDate(input, inputSize, 2) != true );

								year = atoi(input);
								USB.println(year);


								/////////////////////////////////
								//	MONTH
								/////////////////////////////////
								serialClean();
								do
								{
									USB.println("Insert month [mm] and press Enter.");
									USB.print(F("> "));
								}
								while ( getDate(input, inputSize, 2) != true );

								month = atoi(input);
								USB.println(month);


								/////////////////////////////////
								//	DAY
								/////////////////////////////////
								serialClean();
								do
								{
									USB.println("Insert day [dd] and press Enter.");
									USB.print(F("> "));
								}
								while ( getDate(input, inputSize, 2) != true );

								day = atoi(input);
								USB.println(day);


								/////////////////////////////////
								//	HOUR
								/////////////////////////////////
								serialClean();
								do
								{
									USB.println("Insert Hour [HH] and press Enter.");
									USB.print(F("> "));
								}
								while ( getDate(input, inputSize, 2) != true );

								hour = atoi(input);
								USB.println(hour);

								/////////////////////////////////
								//	MINUTE
								/////////////////////////////////
								serialClean();
								do
								{
									USB.println("Insert minute [MM] and press Enter.");
									USB.print(F("> "));
								}
								while ( getDate(input, inputSize, 2) != true );

								minute = atoi(input);
								USB.println(minute);


								/////////////////////////////////
								//	create buffer
								/////////////////////////////////
								sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
												minute,
												hour,
												day,
												month,
												year );


								calibrationDate_temp[12] = ' ';
								calibrationDate_temp[13] = ' ';
								calibrationDate_temp[14] = ' ';
								calibrationDate_temp[15] = ' ';

								//USB.println(calibrationDate_temp);

								fillCalibrationDate(calibrationDate_temp);


								//In step 4 user validates the entire calibration entering operator's name and date
								calibrate(PHEHT, PH, STEP_4, NULL);

								printLine();

								USB.println(F("Calibration successfully finished!"));
							}
						}
					}
				}
			}
		
			
			
			if (calibrationMethod == 3)
			{
				USB.println(F("Three point calibration method selected"));
				
				USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
				USB.println(F("Example: 4"));
				USB.print(F("> "));


				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{
					//In step 1 we reset temporary calibration data and indicate the range (no range)
					calibrate(PHEHT, PH, STEP_1, NULL);

					offset = atof(input);

					printLine();
					USB.print(F("2. Place the sensor at selected offset: pH "));
					USB.printFloat(offset, 4);
					USB.println(F(""));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Observing the offset in this step will help you assess whether calibration"));
					USB.println(F("is necessary or not, depending on the precision required in your application."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();
					memset(input, 0x00, sizeof(input) );
					uint16_t j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorPHEHT.pH, 2);
							USB.println(F(""));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 2 user select calibration standard 1 (offset)
						//This step must be done after stabilizing and measuring in water with
						//the selected value using readMeasures function previosly
						calibrate(PHEHT, PH, STEP_2, offset);

						printLine();
						USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
						USB.println(F("Example: 7"));
						USB.print(F("> "));

						serialClean();
						while ( getData(input, inputSize) == 0 );
						USB.println(input);
						if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
						{
							//Exit discarding changes
							exitCalibration();
						}
						else
						{

							slope = atof(input);

							printLine();
							USB.print(F("4. Place the sensor at selected slope: pH "));
							USB.printFloat(slope, 4);
							USB.println(F(""));
							USB.println(F("Wait some minutes until the measure stabilizes."));
							USB.println(F("Then insert 'N' for Next step and press Enter."));

							serialClean();

							j = 300;
							while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
										&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
							{
								j++;
								if (j >= 300)
								{
									j = 0;

									read();
									USB.println();
									USB.printFloat(sensorPHEHT.pH, 2);
									USB.println(F(""));
									USB.print(F("> "));
								}

								getData(input, inputSize);
								delay(10);
							}

							USB.println(input);
							if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
							{
								//Exit discarding changes
								exitCalibration();
							}
							else
							{
								//In step 3 user select calibration standard 2 (slope)
								//This step must be done after stabilizing and measuring in water with
								//the selected value
								calibrate(PHEHT, PH, STEP_3, slope);
								
								printLine();
								
								USB.println(F("5. Insert the third calibration standart value and press Enter."));
								USB.println(F("Example: 9"));
								USB.print(F("> "));

								serialClean();
								while ( getData(input, inputSize) == 0 );
								USB.println(input);
								if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
								{
									//Exit discarding changes
									exitCalibration();
								}
								else
								{

									slope = atof(input);

									printLine();
									USB.print(F("6. Place the sensor at selected slope: pH "));
									USB.printFloat(slope, 4);
									USB.println(F(""));
									USB.println(F("Wait some minutes until the measure stabilizes."));
									USB.println(F("Then insert 'N' for Next step and press Enter."));

									serialClean();

									j = 300;
									while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
												&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
									{
										j++;
										if (j >= 300)
										{
											j = 0;

											read();
											USB.println();
											USB.printFloat(sensorPHEHT.pH, 2);
											USB.println(F(""));
											USB.print(F("> "));
										}

										getData(input, inputSize);
										delay(10);
									}

									USB.println(input);
									if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
									{
										//Exit discarding changes
										exitCalibration();
									}
									else
									{
										//In step 3 user select calibration standard 2 (slope)
										//This step must be done after stabilizing and measuring in water with
										//the selected value
										calibrate(PHEHT, PH, STEP_3B, slope);


										printLine();
										USB.println(F("7. In order to validate the calibration some data is required."));
										USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
										USB.print(F("> "));

										serialClean();
										while (getData(input, inputSize) == 0);

										char calibrationOperatorsName_temp[17];
										memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
										strcpy(calibrationOperatorsName_temp, input);


										for (int k = strlen(input); k < 16; k++)
										{
											calibrationOperatorsName_temp[k] = ' ';
										}

										USB.println(calibrationOperatorsName_temp);
										fillOperatorsName(calibrationOperatorsName_temp);

										printLine();
										USB.println(F("8.Please insert calibration date."));


										int year;
										int month;
										int day;
										int hour;
										int minute;

										char calibrationDate_temp[17];
										memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
										/////////////////////////////////
										//	YEAR
										/////////////////////////////////
										serialClean();
										do
										{
											USB.println("Insert year [yy] and press Enter.");
											USB.print(F("> "));
										}
										while ( getDate(input, inputSize, 2) != true );

										year = atoi(input);
										USB.println(year);


										/////////////////////////////////
										//	MONTH
										/////////////////////////////////
										serialClean();
										do
										{
											USB.println("Insert month [mm] and press Enter.");
											USB.print(F("> "));
										}
										while ( getDate(input, inputSize, 2) != true );

										month = atoi(input);
										USB.println(month);


										/////////////////////////////////
										//	DAY
										/////////////////////////////////
										serialClean();
										do
										{
											USB.println("Insert day [dd] and press Enter.");
											USB.print(F("> "));
										}
										while ( getDate(input, inputSize, 2) != true );

										day = atoi(input);
										USB.println(day);


										/////////////////////////////////
										//	HOUR
										/////////////////////////////////
										serialClean();
										do
										{
											USB.println("Insert Hour [HH] and press Enter.");
											USB.print(F("> "));
										}
										while ( getDate(input, inputSize, 2) != true );

										hour = atoi(input);
										USB.println(hour);

										/////////////////////////////////
										//	MINUTE
										/////////////////////////////////
										serialClean();
										do
										{
											USB.println("Insert minute [MM] and press Enter.");
											USB.print(F("> "));
										}
										while ( getDate(input, inputSize, 2) != true );

										minute = atoi(input);
										USB.println(minute);


										/////////////////////////////////
										//	create buffer
										/////////////////////////////////
										sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
														minute,
														hour,
														day,
														month,
														year );


										calibrationDate_temp[12] = ' ';
										calibrationDate_temp[13] = ' ';
										calibrationDate_temp[14] = ' ';
										calibrationDate_temp[15] = ' ';

										//USB.println(calibrationDate_temp);

										fillCalibrationDate(calibrationDate_temp);


										//In step 4 user validates the entire calibration entering operator's name and date
										calibrate(PHEHT, PH, STEP_4, NULL);

										printLine();

										USB.println(F("Calibration successfully finished!"));
									}
								}
							}
						}
					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

	if (parameter == REDOX)
	{
		USB.println(F("Redox parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();

		//In step 1 we reset temporary calibration data and indicate the range (no range)
		calibrate(PHEHT, REDOX, STEP_1, NULL);
		
		//offset is not used in this particular sensor parameter
		offset = 0;

		USB.println(F("1. Place the sensor at standard offset: 0 mV"));
		USB.println(F("Wait some minutes until the measure stabilizes."));
		USB.println(F("Observing the offset in this step will help you assess whether calibration"));
		USB.println(F("is necessary or not, depending on the precision required in your application."));
		USB.println(F("Then insert 'N' for Next step and press Enter."));

		serialClean();
		memset(input, 0x00, sizeof(input) );
		uint16_t j = 300;
		while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
			&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
		{
			j++;
			if (j >= 300)
			{
				j = 0;

				read();
				USB.println();
				USB.printFloat(sensorPHEHT.redox, 2);
				USB.println(F(" mV"));
				USB.print(F("> "));
			}

			getData(input, inputSize);
			delay(10);
		}

		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibrationAndStopElectronicZero();
		}
		else
		{
			//In step 2 user select calibration standard 1 (offset)
			//This step must be done after stabilizing and measuring in water with
			//the selected value using readMeasures function previosly
			calibrate(PHEHT, REDOX, STEP_2, offset);

			printLine();
			USB.println(F("2. Insert the second calibration standart value (slope) and press Enter."));
			USB.println(F("240 mV is recommended)"));
			USB.println(F("Example: 240"));
			USB.print(F("> "));

			serialClean();
			while ( getData(input, inputSize) == 0 );
			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibrationAndStopElectronicZero();
			}
			else
			{

				slope = atof(input);

				printLine();
				USB.print(F("3. Place the sensor at selected slope: "));
				USB.printFloat(slope, 4);
				USB.println(F(" mV"));
				USB.println(F("Wait some minutes until the measure stabilizes."));
				USB.println(F("Then insert 'N' for Next step and press Enter."));

				serialClean();

				j = 300;
				while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
							&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
				{
					j++;
					if (j >= 300)
					{
						j = 0;

						read();
						USB.println();
						USB.printFloat(sensorPHEHT.redox, 2);
						USB.println(F(" mV"));
						USB.print(F("> "));
					}

					getData(input, inputSize);
					delay(10);
				}

				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibrationAndStopElectronicZero();
				}
				else
				{
					//In step 3 user select calibration standard 2 (slope)
					//This step must be done after stabilizing and measuring in water with
					//the selected value
					calibrate(PHEHT, REDOX, STEP_3, slope);

					printLine();
					USB.println(F("4. In order to validate the calibration some data is required."));
					USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
					USB.print(F("> "));

					serialClean();
					while (getData(input, inputSize) == 0);

					char calibrationOperatorsName_temp[17];
					memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
					strcpy(calibrationOperatorsName_temp, input);


					for (int k = strlen(input); k < 16; k++)
					{
						calibrationOperatorsName_temp[k] = ' ';
					}

					USB.println(calibrationOperatorsName_temp);
					fillOperatorsName(calibrationOperatorsName_temp);

					printLine();
					USB.println(F("5.Please insert calibration date."));


					int year;
					int month;
					int day;
					int hour;
					int minute;

					char calibrationDate_temp[17];
					memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
					/////////////////////////////////
					//	YEAR
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert year [yy] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					year = atoi(input);
					USB.println(year);


					/////////////////////////////////
					//	MONTH
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert month [mm] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					month = atoi(input);
					USB.println(month);


					/////////////////////////////////
					//	DAY
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert day [dd] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					day = atoi(input);
					USB.println(day);


					/////////////////////////////////
					//	HOUR
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert Hour [HH] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					hour = atoi(input);
					USB.println(hour);

					/////////////////////////////////
					//	MINUTE
					/////////////////////////////////
					serialClean();
					do
					{
						USB.println("Insert minute [MM] and press Enter.");
						USB.print(F("> "));
					}
					while ( getDate(input, inputSize, 2) != true );

					minute = atoi(input);
					USB.println(minute);


					/////////////////////////////////
					//	create buffer
					/////////////////////////////////
					sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
									minute,
									hour,
									day,
									month,
									year );


					calibrationDate_temp[12] = ' ';
					calibrationDate_temp[13] = ' ';
					calibrationDate_temp[14] = ' ';
					calibrationDate_temp[15] = ' ';

					//USB.println(calibrationDate_temp);

					fillCalibrationDate(calibrationDate_temp);


					//In step 4 user validates the entire calibration entering operator's name and date
					calibrate(PHEHT, REDOX, STEP_4, NULL);

					printLine();

					USB.println(F("Calibration successfully finished!"));
				}
			}
		}

		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

}

/*!
	\brief menu assisted calibration process
	\param sensorType and parameter
	\return void
*/
void Aqualabo_C4E::calibrationProcess(uint8_t parameter)
{
	const uint8_t inputSize = 100;
	char input[inputSize];
	uint8_t response = 0;
	float offset = 0;
	float slope = 0;

	printBigLine();
	USB.println(F("MENU ASSISTED CALIBRATION PROCESS"));
	USB.println(F("C4E sensor"));

	if (parameter == TEMPERATURE)
	{
		USB.println(F("Temperature parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nFor this process it is advisable to use a reference temperature sensor."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0*C is recommended (Sensor fully immersed in an ice/water bath)"));
		USB.println(F("Example: 0.350"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(C4E, TEMPERATURE, STEP_1, NULL);

			offset = atof(input);

			printLine();
			USB.print(F("2. Set sensor at selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F("*C."));
			USB.println(F("Wait some minutes until the measure stabilizes."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorC4E.temperature, 2);
					USB.println(F("*C"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(C4E, TEMPERATURE, STEP_2, offset);

				printLine();
				USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
				USB.println(F("25*C is recommended (Sensor fully immersed in a bath heated at 25*C)"));
				USB.println(F("Example: 25.140"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("4. Immerse the sensor in water at your selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F("*C."));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorC4E.temperature, 2);
							USB.println(F("*C"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(C4E, TEMPERATURE, STEP_3, slope);

						printLine();
						USB.println(F("5. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("6.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						calibrate(C4E, TEMPERATURE, STEP_4, NULL);

						printLine();

						USB.println(F("Calibration successfully finished!"));
					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}


	if (parameter == CONDUCTIVITY)
	{
		uint8_t range = 0;

		USB.println(F("Conductivity parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nWith this process only one range will be calibrated, if desired, carry out"));
		USB.println(F("this process for each range to be calibrated a maximum of 4 times."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the range to be calibrated from the 4 available ranges and press Enter:"));
		USB.println(F("1 for Range 1 (0 / 200 uS/cm)"));
		USB.println(F("2 for Range 2 (0 / 2000 uS/cm)"));
		USB.println(F("3 for Range 3 (0 / 20 mS/cm)"));
		USB.println(F("4 for Range 4 (0 / 200 mS/cm)"));
		USB.println(F("Example: 2"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );

		range = atoi(input);
		USB.println(range, DEC);

		//!*************************************************************
		//! Name: init(uint8_t range)
		//!
		//! Note: Only works in Socket E
		//!
		//! Description: Initializes the sensor. It's necessary to initialize the sensor
		//! once in each code (in setup) before using it, since some parameters are
		//! configured and initial information is extracted from the sensor
		//!
		//! Param: range (Range for NTU measure)
		//!				select from: RANGE_AUTOMATIC, RANGE_1, RANGE_2, RANGE_3, RANGE_4 (see guide for more info)
		//!
		//! Returns: 0 is OK, 1 if error
		//!*************************************************************
		response = init(range);
		if (response)
		{
			USB.println(F("Error initializing the sensor. \r\nCheck the sensor and restart the code."));
		}



		printLine();
		USB.println(F("2. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0 uS/cm is recommended (sensor exposed to the air)"));
		USB.println(F("Example: 0"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range
			calibrate(C4E, PARAMETER_1, STEP_1, (float)range);

			offset = atof(input);

			printLine();
			USB.print(F("3. Immerse the sensor in a solution at your selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F(" uS/cm."));
			USB.println(F("Wait some minutes until the measure stabilizes.."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorC4E.conductivity, 2);
					USB.println(F(" uS/cm"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(C4E, PARAMETER_1, STEP_2, offset);

				printLine();
				USB.println(F("4. Insert the second calibration standart value (slope) and press Enter."));
				USB.print(F("A solution recommended for your selected range is "));
				switch (range)
				{
					case RANGE_1:
						USB.print(F("84"));
						break;

					case RANGE_2:
						USB.print(F("1413"));
						break;

					case RANGE_3:
						USB.print(F("12880"));
						break;

					case RANGE_4:
						USB.print(F("111800"));
						break;
				}
				USB.println(F(" uS/cm."));
				USB.println(F("Example: 1413"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("5. Immerse the sensor in a solution at your selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F(" uS/cm."));
					USB.println(F("Wait some minutes until the measure stabilizes.."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorC4E.conductivity, 2);
							USB.println(F(" uS/cm"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(C4E, PARAMETER_1, STEP_3, slope);

						printLine();
						USB.println(F("6. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("7.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						if (calibrate(C4E, PARAMETER_1, STEP_4, NULL) == 0)
						{
							printLine();
							USB.println(F("Calibration successfully finished!"));
						}
						else
						{
							printLine();
							USB.println(F("Error in calibration validation"));
						}

					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

}


/*!
	\brief menu assisted calibration process
	\param sensorType and parameter
	\return void
*/
void Aqualabo_NTU::calibrationProcess(uint8_t parameter)
{
	const uint8_t inputSize = 100;
	char input[inputSize];
	uint8_t response = 0;
	float offset = 0;
	float slope = 0;

	printBigLine();
	USB.println(F("MENU ASSISTED CALIBRATION PROCESS"));
	USB.println(F("NTU sensor"));

	if (parameter == TEMPERATURE)
	{
		USB.println(F("Temperature parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nFor this process it is advisable to use a reference temperature sensor."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0*C is recommended (Sensor fully immersed in an ice/water bath)"));
		USB.println(F("Example: 0.350"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(NTU, TEMPERATURE, STEP_1, NULL);

			offset = atof(input);

			printLine();
			USB.print(F("2. Set sensor at selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F("*C."));
			USB.println(F("Wait some minutes until the measure stabilizes."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorNTU.temperature, 2);
					USB.println(F("*C"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(NTU, TEMPERATURE, STEP_2, offset);

				printLine();
				USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
				USB.println(F("25*C is recommended (Sensor fully immersed in a bath heated at 25*C)"));
				USB.println(F("Example: 25.140"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("4. Immerse the sensor in water at your selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F("*C."));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorNTU.temperature, 2);
							USB.println(F("*C"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(NTU, TEMPERATURE, STEP_3, slope);

						printLine();
						USB.println(F("5. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("6.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						calibrate(NTU, TEMPERATURE, STEP_4, NULL);

						printLine();

						USB.println(F("Calibration successfully finished!"));
					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

	if (parameter == NTU_TURBIDITY)
	{
		uint8_t range = 0;

		USB.println(F("NTU turbidity parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nFor this process it is necessary to use NTU calibration solutions."));
		USB.println(F("\r\nWith this process only one range will be calibrated, if desired, carry out"));
		USB.println(F("this process for each range to be calibrated a maximum of 4 times."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the range to be calibrated from the 4 available ranges:"));
		USB.println(F("1 for Range 1 (0 / 50 NTU)"));
		USB.println(F("2 for Range 2 (0 / 200 NTU)"));
		USB.println(F("3 for Range 3 (0 / 1000 NTU)"));
		USB.println(F("4 for Range 4 (0 / 4000 NTU)"));
		USB.println(F("Example: 2"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );

		range = atoi(input);
		USB.println(range, DEC);

		//!*************************************************************
		//! Name: init(uint8_t range)
		//!
		//! Note: Only works in Socket E
		//!
		//! Description: Initializes the sensor. It's necessary to initialize the sensor
		//! once in each code (in setup) before using it, since some parameters are
		//! configured and initial information is extracted from the sensor
		//!
		//! Param: range (Range for NTU measure)
		//!				select from: RANGE_AUTOMATIC, RANGE_1, RANGE_2, RANGE_3, RANGE_4 (see guide for more info)
		//!
		//! Returns: 0 is OK, 1 if error
		//!*************************************************************
		response = init(range);
		if (response)
		{
			USB.println(F("Error initializing the sensor. \r\nCheck the sensor and restart the code."));
		}



		printLine();
		USB.println(F("2. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0 NTU is recommended (demineralised water)"));
		USB.println(F("Example: 0"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range
			calibrate(NTU, PARAMETER_1, STEP_1, (float)range);

			offset = atof(input);

			printLine();
			USB.print(F("3. Immerse the sensor in a solution at your selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F(" NTU."));
			USB.println(F("Wait some minutes until the measure stabilizes.."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorNTU.turbidityNTU, 4);
					USB.println(F(" NTU"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(NTU, PARAMETER_1, STEP_2, offset);

				printLine();
				USB.println(F("4. Insert the second calibration standart value (slope) and press Enter."));
				USB.println(F("A solution with concentration matching the middle of the measurement range"));
				USB.print(F("is recommended. For your selected range is "));
				switch (range)
				{
					case RANGE_1:
						USB.print(F("25"));
						break;

					case RANGE_2:
						USB.print(F("100"));
						break;

					case RANGE_3:
						USB.print(F("500"));
						break;

					case RANGE_4:
						USB.print(F("2000"));
						break;
				}
				USB.println(F(" NTU."));
				USB.println(F("Example: 2000"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("5. Immerse the sensor in a solution at your selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F(" NTU."));
					USB.println(F("Wait some minutes until the measure stabilizes.."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorNTU.turbidityNTU, 4);
							USB.println(F(" NTU"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(NTU, PARAMETER_1, STEP_3, slope);

						printLine();
						USB.println(F("6. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("7.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						if (calibrate(NTU, PARAMETER_1, STEP_4, NULL) == 0)
						{
							printLine();
							USB.println(F("Calibration successfully finished!"));
						}
						else
						{
							printLine();
							USB.println(F("Error in calibration validation"));
						}

					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

}


/*!
	\brief menu assisted calibration process
	\param sensorType and parameter
	\return void
*/
void Aqualabo_CTZN::calibrationProcess(uint8_t parameter)
{
	const uint8_t inputSize = 100;
	char input[inputSize];
	uint8_t response = 0;
	float offset = 0;
	float slope = 0;

	printBigLine();
	USB.println(F("MENU ASSISTED CALIBRATION PROCESS"));
	USB.println(F("CTZN sensor"));

	if (parameter == TEMPERATURE)
	{
		USB.println(F("Temperature parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nFor this process it is advisable to use a reference temperature sensor."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0*C is recommended (Sensor fully immersed in an ice/water bath)"));
		USB.println(F("Example: 0.350"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(CTZN, TEMPERATURE, STEP_1, NULL);

			offset = atof(input);

			printLine();
			USB.print(F("2. Set sensor at selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F("*C."));
			USB.println(F("Wait some minutes until the measure stabilizes."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorCTZN.temperature, 2);
					USB.println(F("*C"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(CTZN, TEMPERATURE, STEP_2, offset);

				printLine();
				USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
				USB.println(F("25*C is recommended (Sensor fully immersed in a bath heated at 25*C)"));
				USB.println(F("Example: 25.140"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("4. Immerse the sensor in water at your selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F("*C."));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorCTZN.temperature, 2);
							USB.println(F("*C"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(CTZN, TEMPERATURE, STEP_3, slope);

						printLine();
						USB.println(F("5. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("6.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						calibrate(CTZN, TEMPERATURE, STEP_4, NULL);

						printLine();

						USB.println(F("Calibration successfully finished!"));
					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

	if (parameter == CONDUCTIVITY)
	{
		USB.println(F("Conductivity parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0 mS/cm is recommended (sensor exposed to the air)"));
		USB.println(F("Example: 0"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(CTZN, PARAMETER_1, STEP_1, NULL);

			offset = atof(input);

			printLine();
			USB.print(F("2. Place the sensor at selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F(" mS/cm."));
			USB.println(F("Wait some minutes until the measure stabilizes."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorCTZN.conductivity, 2);
					USB.println(F(" mS/cm"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(CTZN, PARAMETER_1, STEP_2, offset);

				printLine();
				USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
				USB.println(F("20 mS/cm is recommended"));
				USB.println(F("Example: 20"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("4. Place the sensor at selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F(" mS/cm."));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorCTZN.conductivity, 2);
							USB.println(F(" mS/cm"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(CTZN, PARAMETER_1, STEP_3, slope);

						printLine();
						USB.println(F("5. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("6.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						calibrate(CTZN, PARAMETER_1, STEP_4, NULL);

						printLine();

						USB.println(F("Calibration successfully finished!"));
					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

}


/*!
	\brief menu assisted calibration process
	\param sensorType and parameter
	\return void
*/
void Aqualabo_MES5::calibrationProcess(uint8_t parameter)
{
	const uint8_t inputSize = 100;
	char input[inputSize];
	uint8_t response = 0;
	float offset = 0;
	float slope = 0;

	printBigLine();
	USB.println(F("MENU ASSISTED CALIBRATION PROCESS"));
	USB.println(F("MES5 sensor"));

	if (parameter == TEMPERATURE)
	{
		USB.println(F("Temperature parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nFor this process it is advisable to use a reference temperature sensor."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0*C is recommended (Sensor fully immersed in an ice/water bath)"));
		USB.println(F("Example: 0.350"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(MES5, TEMPERATURE, STEP_1, NULL);

			offset = atof(input);

			printLine();
			USB.print(F("2. Set sensor at selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F("*C."));
			USB.println(F("Wait some minutes until the measure stabilizes."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorMES5.temperature, 2);
					USB.println(F("*C"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(MES5, TEMPERATURE, STEP_2, offset);

				printLine();
				USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
				USB.println(F("25*C is recommended (Sensor fully immersed in a bath heated at 25*C)"));
				USB.println(F("Example: 25.140"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("4. Immerse the sensor in water at your selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F("*C."));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorMES5.temperature, 2);
							USB.println(F("*C"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(MES5, TEMPERATURE, STEP_3, slope);

						printLine();
						USB.println(F("5. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("6.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						calibrate(MES5, TEMPERATURE, STEP_4, NULL);

						printLine();

						USB.println(F("Calibration successfully finished!"));
					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

	if (parameter == SLUDGE_BLANKET)
	{
		USB.println(F("Sludge blanket parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a one point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the calibration standart value you will use (offset) and press Enter."));
		USB.println(F("100% is recommended"));
		USB.println(F("Example: 100"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(MES5, PARAMETER_1, STEP_1, NULL);

			offset = atof(input);

			printLine();
			USB.print(F("2. Set sensor at selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F(" %"));
			USB.println(F("Wait some minutes until the measure stabilizes."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorMES5.sludgeBlanket, 2);
					USB.println(F(" %"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(MES5, PARAMETER_1, STEP_2, offset);



				printLine();
				USB.println(F("3. In order to validate the calibration some data is required."));
				USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
				USB.print(F("> "));

				serialClean();
				while (getData(input, inputSize) == 0);

				char calibrationOperatorsName_temp[17];
				memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
				strcpy(calibrationOperatorsName_temp, input);


				for (int k = strlen(input); k < 16; k++)
				{
					calibrationOperatorsName_temp[k] = ' ';
				}

				USB.println(calibrationOperatorsName_temp);
				fillOperatorsName(calibrationOperatorsName_temp);

				printLine();
				USB.println(F("4.Please insert calibration date."));


				int year;
				int month;
				int day;
				int hour;
				int minute;

				char calibrationDate_temp[17];
				memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
				/////////////////////////////////
				//	YEAR
				/////////////////////////////////
				serialClean();
				do
				{
					USB.println("Insert year [yy] and press Enter.");
					USB.print(F("> "));
				}
				while ( getDate(input, inputSize, 2) != true );

				year = atoi(input);
				USB.println(year);


				/////////////////////////////////
				//	MONTH
				/////////////////////////////////
				serialClean();
				do
				{
					USB.println("Insert month [mm] and press Enter.");
					USB.print(F("> "));
				}
				while ( getDate(input, inputSize, 2) != true );

				month = atoi(input);
				USB.println(month);


				/////////////////////////////////
				//	DAY
				/////////////////////////////////
				serialClean();
				do
				{
					USB.println("Insert day [dd] and press Enter.");
					USB.print(F("> "));
				}
				while ( getDate(input, inputSize, 2) != true );

				day = atoi(input);
				USB.println(day);


				/////////////////////////////////
				//	HOUR
				/////////////////////////////////
				serialClean();
				do
				{
					USB.println("Insert Hour [HH] and press Enter.");
					USB.print(F("> "));
				}
				while ( getDate(input, inputSize, 2) != true );

				hour = atoi(input);
				USB.println(hour);

				/////////////////////////////////
				//	MINUTE
				/////////////////////////////////
				serialClean();
				do
				{
					USB.println("Insert minute [MM] and press Enter.");
					USB.print(F("> "));
				}
				while ( getDate(input, inputSize, 2) != true );

				minute = atoi(input);
				USB.println(minute);


				/////////////////////////////////
				//	create buffer
				/////////////////////////////////
				sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
								minute,
								hour,
								day,
								month,
								year );


				calibrationDate_temp[12] = ' ';
				calibrationDate_temp[13] = ' ';
				calibrationDate_temp[14] = ' ';
				calibrationDate_temp[15] = ' ';

				//USB.println(calibrationDate_temp);

				fillCalibrationDate(calibrationDate_temp);


				//In step 4 user validates the entire calibration entering operator's name and date
				calibrate(MES5, PARAMETER_1, STEP_4, NULL);

				printLine();

				USB.println(F("Calibration successfully finished!"));
			}


		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

	if (parameter == FAU_TURBIDITY)
	{
		USB.println(F("FAU turbidity parameter"));
		printBigLine();
		USB.println(F("0. Introduction:"));
		USB.println(F("\r\nThis is a two-point calibration method. At the end of the process the results"));
		USB.println(F("of the calibration will be stored in the FLASH memory of the sensor for"));
		USB.println(F("future uses."));
		USB.println(F("\r\nThe sensor is calibrated ex works, meaning that no calibration is required"));
		USB.println(F("before initial startup. During operation the sensor should be calibrated if the"));
		USB.println(F("measured values begin to drift."));
		USB.println(F("\r\nRinse the sensor in clean water and dry it with a soft cloth or an absorbent"));
		USB.println(F("paper before each calibration."));
		USB.println(F("\r\nTo exit the calibration without considering anything please insert 'Q' to Quit"));
		USB.println(F("and press Enter."));
		printLine();
		USB.println(F("1. Insert the first calibration standart value you will use (offset) and press Enter."));
		USB.println(F("0 FAU is recommended"));
		USB.println(F("Example: 0"));
		USB.print(F("> "));


		serialClean();
		while ( getData(input, inputSize) == 0 );
		USB.println(input);
		if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
		{
			//Exit discarding changes
			exitCalibration();
		}
		else
		{
			//In step 1 we reset temporary calibration data and indicate the range (no range)
			calibrate(MES5, PARAMETER_3, STEP_1, NULL);

			offset = atof(input);

			printLine();
			USB.print(F("2. Set sensor at selected offset: "));
			USB.printFloat(offset, 4);
			USB.println(F(" FAU."));
			USB.println(F("Wait some minutes until the measure stabilizes."));
			USB.println(F("Observing the offset in this step will help you assess whether calibration"));
			USB.println(F("is necessary or not, depending on the precision required in your application."));
			USB.println(F("Then insert 'N' for Next step and press Enter."));

			serialClean();
			memset(input, 0x00, sizeof(input) );
			uint16_t j = 300;
			while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
						&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
			{
				j++;
				if (j >= 300)
				{
					j = 0;

					read();
					USB.println();
					USB.printFloat(sensorMES5.turbidityFAU, 2);
					USB.println(F(" FAU"));
					USB.print(F("> "));
				}

				getData(input, inputSize);
				delay(10);
			}

			USB.println(input);
			if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
			{
				//Exit discarding changes
				exitCalibration();
			}
			else
			{
				//In step 2 user select calibration standard 1 (offset)
				//This step must be done after stabilizing and measuring in water with
				//the selected value using readMeasures function previosly
				calibrate(MES5, PARAMETER_3, STEP_2, offset);

				printLine();
				USB.println(F("3. Insert the second calibration standart value (slope) and press Enter."));
				USB.println(F("2000 FAU is recommended"));
				USB.println(F("Example: 2000"));
				USB.print(F("> "));

				serialClean();
				while ( getData(input, inputSize) == 0 );
				USB.println(input);
				if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
				{
					//Exit discarding changes
					exitCalibration();
				}
				else
				{

					slope = atof(input);

					printLine();
					USB.print(F("4. Immerse the sensor in water at your selected slope: "));
					USB.printFloat(slope, 4);
					USB.println(F(" FAU."));
					USB.println(F("Wait some minutes until the measure stabilizes."));
					USB.println(F("Then insert 'N' for Next step and press Enter."));

					serialClean();

					j = 300;
					while ((find((uint8_t*)input, strlen(input), "N") != 1) && (find((uint8_t*)input, strlen(input), "Q") != 1)
								&& (find((uint8_t*)input, strlen(input), "n") != 1) && (find((uint8_t*)input, strlen(input), "q") != 1))
					{
						j++;
						if (j >= 300)
						{
							j = 0;

							read();
							USB.println();
							USB.printFloat(sensorMES5.turbidityFAU, 2);
							USB.println(F(" FAU"));
							USB.print(F("> "));
						}

						getData(input, inputSize);
						delay(10);
					}

					USB.println(input);
					if ((find((uint8_t*)input, strlen(input), "Q") == 1) || (find((uint8_t*)input, strlen(input), "q") == 1))
					{
						//Exit discarding changes
						exitCalibration();
					}
					else
					{
						//In step 3 user select calibration standard 2 (slope)
						//This step must be done after stabilizing and measuring in water with
						//the selected value
						calibrate(MES5, PARAMETER_3, STEP_3, slope);

						printLine();
						USB.println(F("5. In order to validate the calibration some data is required."));
						USB.println(F("Please insert operator's name (up to 16 letters) and press Enter."));
						USB.print(F("> "));

						serialClean();
						while (getData(input, inputSize) == 0);

						char calibrationOperatorsName_temp[17];
						memset(calibrationOperatorsName_temp, 0x00, sizeof(calibrationOperatorsName_temp));
						strcpy(calibrationOperatorsName_temp, input);


						for (int k = strlen(input); k < 16; k++)
						{
							calibrationOperatorsName_temp[k] = ' ';
						}

						USB.println(calibrationOperatorsName_temp);
						fillOperatorsName(calibrationOperatorsName_temp);

						printLine();
						USB.println(F("6.Please insert calibration date."));


						int year;
						int month;
						int day;
						int hour;
						int minute;

						char calibrationDate_temp[17];
						memset(calibrationDate_temp, 0x00, sizeof(calibrationDate_temp));
						/////////////////////////////////
						//	YEAR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert year [yy] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						year = atoi(input);
						USB.println(year);


						/////////////////////////////////
						//	MONTH
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert month [mm] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						month = atoi(input);
						USB.println(month);


						/////////////////////////////////
						//	DAY
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert day [dd] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						day = atoi(input);
						USB.println(day);


						/////////////////////////////////
						//	HOUR
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert Hour [HH] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						hour = atoi(input);
						USB.println(hour);

						/////////////////////////////////
						//	MINUTE
						/////////////////////////////////
						serialClean();
						do
						{
							USB.println("Insert minute [MM] and press Enter.");
							USB.print(F("> "));
						}
						while ( getDate(input, inputSize, 2) != true );

						minute = atoi(input);
						USB.println(minute);


						/////////////////////////////////
						//	create buffer
						/////////////////////////////////
						sprintf(calibrationDate_temp, "%02u%02u%02u%02u20%02u",
										minute,
										hour,
										day,
										month,
										year );


						calibrationDate_temp[12] = ' ';
						calibrationDate_temp[13] = ' ';
						calibrationDate_temp[14] = ' ';
						calibrationDate_temp[15] = ' ';

						//USB.println(calibrationDate_temp);

						fillCalibrationDate(calibrationDate_temp);


						//In step 4 user validates the entire calibration entering operator's name and date
						calibrate(MES5, PARAMETER_3, STEP_4, NULL);

						printLine();

						USB.println(F("Calibration successfully finished!"));
					}
				}
			}
		}
		printLine();
		USB.println(F("End of calibration process"));
		printBigLine();
	}

}

void WaspSensorWaterXtr::exitCalibration()
{
	printLine();
	USB.println(F("Exiting the calibration without considering anything"));
	resetTemporaryCalibrationData(RETURN_AVG_TO_1);
}

void WaspSensorWaterXtr::exitCalibrationAndStopElectronicZero()
{
	printLine();
	USB.println(F("Exiting the calibration without considering anything"));
	resetTemporaryCalibrationData(RETURN_AVG_TO_1_AND_STOP_ELECTRONIC_ZERO);
}


void WaspSensorWaterXtr::printLine()
{
	USB.println(F("\r\n****************\r\n"));
}

void WaspSensorWaterXtr::printBigLine()
{
	USB.println(F("\r\n*********************************************\r\n"));
}


uint8_t WaspSensorWaterXtr::getData(char* _input , uint8_t _inputSize)
{
	memset(_input, 0x00, _inputSize);
	uint8_t i = 0;

	if (USB.available() > 0)
	{
		while (USB.available() > 0)
		{
			_input[i] = USB.read();
			//USB.print("READ:");
			//USB.println(input[i]);
			if ((_input[i] == '\r') || (_input[i] == '\n') )
			{
				_input[i] = 0x00;
			}
			else
			{
				i++;
			}
			delay(10);
		}
	}
	return i;
}

boolean WaspSensorWaterXtr::getDate(char* input, uint8_t inputSize, int numBytes)
{
	memset(input, 0x00, inputSize);
	int i = 0;
	USB.flush();
	int nRead = 0;

	while (!USB.available());

	while (USB.available() > 0)
	{
		input[i] = USB.read();

		if ( (input[i] == '\r') || (input[i] == '\n') )
		{
			input[i] = 0x00;
		}
		else
		{
			i++;
		}
	}

	nRead = i;

	if (nRead != numBytes)
	{
		USB.print(F("must write "));
		USB.print(numBytes, DEC);
		USB.print(F(" characters. Read "));
		USB.print(nRead, DEC);
		USB.println(F(" bytes"));
		return false;
	}
	else
	{
		input[i] = '\0';
		return true;
	}

}

void WaspSensorWaterXtr::serialClean()
{
	while (USB.available() > 0)
	{
		USB.read();
	};
}

/*

	name: find
	@param	uint8_t* buffer: pointer to buffer to be scanned
	@param uint16_t length: actual length of buffer
	@param char* pattern: pattern to find
	@return	'0' not found,
				'1' pattern found

*/
bool WaspSensorWaterXtr::find( uint8_t* buffer, uint16_t length, char* pattern)
{
	int result;

	if ( length >= strlen(pattern) )
	{
		for (uint16_t i = 0; i <= length - strlen(pattern); i++)
		{
			result = memcmp( &buffer[i], pattern, strlen(pattern) );

			if ( result == 0 )
			{
				return true;
			}
		}
	}

	return false;
}







// Preinstantiate Objects //////////////////////////////////////////////////////

WaspSensorXtr SensorXtr = WaspSensorXtr();

//WaspSensorWaterXtr SmartWaterXtr = WaspSensorWaterXtr();

////////////////////////////////////////////////////////////////////////////////
