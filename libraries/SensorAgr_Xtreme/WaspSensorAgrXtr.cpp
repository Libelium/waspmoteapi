/*!	\file WaspSensorAgrXtr.cpp
	\brief Library for managing the Smart Agriculture Extreme sensor board

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

	Version:		3.1
	Design:			David Gascón
	Implementation: Javier Siscart, Víctor Boria

 */

#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif


#include "WaspSensorAgrXtr.h"



/// Command table ////////////////////////////////////////////

const char string_00[] PROGMEM = "I!";	// SDI-12 info
const char string_01[] PROGMEM = "M!";	// SDI-12 measurement
const char string_02[] PROGMEM = "D0!";	// SDI-12 data
const char string_03[] PROGMEM = "Ab!";	// SDI-12 change address
const char string_04[] PROGMEM = "?!";	// SDI-12 address query
const char string_05[] PROGMEM = "?I!";	// SDI-12 info
const char string_06[] PROGMEM = "WARNING - Redefinition of sensor socket detected";
const char string_07[] PROGMEM = "WARNING - The following sensor can not work in the defined socket:";
const char string_08[] PROGMEM = "sensor not detected";
const char string_09[] PROGMEM = "invalid data";
const char string_10[] PROGMEM = "socket (!): ";
const char string_11[] PROGMEM = "WARNING - Not possible to turn ON two sensors at the same time:";
const char string_12[] PROGMEM = "%c %s %s %c %s %s %s %s %s %s"; 								//GMX100 frame format
const char string_13[] PROGMEM = "%c %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX101 frame format
const char string_14[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX200 frame format
const char string_15[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %s %s %s"; //GMX240 frame format
const char string_16[] PROGMEM = "%c %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX300 frame format
const char string_17[] PROGMEM = "%c %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX301 frame format
const char string_18[] PROGMEM = "%c %s %s %s %d %s %s %s %s %s %c %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX400 frame format
const char string_19[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX500 frame format
const char string_20[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX501 frame format
const char string_21[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX531 GMX541 GMX551 frame format
const char string_22[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX550 frame format
const char string_23[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"; //GMX600 frame format

const char string_24[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX200 + GPS frame format
const char string_25[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX240 + GPS frame format
const char string_26[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX500 + GPS frame format
const char string_27[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX501 + GPS frame format
const char string_28[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX531 GMX541 GMX551 + GPS frame format
const char string_29[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX550 + GPS frame format
const char string_30[] PROGMEM = "%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"; //GMX600 + GPS frame format


const char* const table_agrxtr[] PROGMEM =
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
WaspSensorAgrXtr::WaspSensorAgrXtr()
{
	// init variables

	// AGR_XTR MUX
	pinMode(MUX_EN, OUTPUT);
	digitalWrite(MUX_EN, LOW); 

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
	pinMode(SPI_ISO_EN, OUTPUT);
	digitalWrite(SPI_ISO_EN, LOW);

	// Update Waspmote Control Register
	WaspRegisterSensor |= REG_AGR_XTR;
	
	// State registers
	//AgricultureXtr.socketRegister = 0;
	//AgricultureXtr._12vStateRegister = 0;
	//AgricultureXtr.redefinedSocket = 0;
	
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
 * \brief Turns ON the Agriculture Xtreme board
 * \param void
 * \return void
 */
void WaspSensorAgrXtr::ON()
{
	ON(REG_5V & REG_3V3);
}



/*!
 * \brief Turns ON the Agriculture Xtreme board
 * \param power select between 5V, 3V3 or both
 * \return void
 */
 void WaspSensorAgrXtr::ON(uint8_t power)
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
 * \brief Turns OFF the Agriculture Xtreme board
 * \param void
 * \return void
 */
void WaspSensorAgrXtr::OFF()
{
	//Only turn OFF 3V3 if every 12V register if OFF
	//3V3 is neccessary for 3v3 socket selecter pin expasor
	if (((WaspRegister & REG_3V3) != 0) && AgricultureXtr._12vStateRegister == 0)
	{
		#if DEBUG_AGR_XTR == 2
			PRINTLN_AGR_XTR(F("3V3 OFF"));
		#endif
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}
	if ((WaspRegister & REG_5V) != 0)
	{
		#if DEBUG_AGR_XTR == 2
			PRINTLN_AGR_XTR(F("5V OFF"));
		#endif
		PWR.setSensorPower(SENS_5V, SENS_OFF);
	}

}



/*!
 * \brief Manages the 3v3 power supplies of Agriculture Xtreme board
 * \param socket socket to be powered
 * \param state desired state of the selected power supply
 * \return void
 */
 void WaspSensorAgrXtr::set3v3(uint8_t socket, uint8_t state)
 {

 	if (state == _3V3_ON)
 	{
 		switch (socket)
 		{
 			case AGR_XTR_SOCKET_A:
				digitalWrite(_3V3_SOCKETA, HIGH);
 				break;

 			case AGR_XTR_SOCKET_B:
				digitalWrite(_3V3_SOCKETB, HIGH);
 				break;

 			case AGR_XTR_SOCKET_D:
				digitalWrite(_3V3_SOCKETD, HIGH);
 				break;

 			case AGR_XTR_SOCKET_E:
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
 			case AGR_XTR_SOCKET_A:
				digitalWrite(_3V3_SOCKETA, LOW);
 				break;

 			case AGR_XTR_SOCKET_B:
				digitalWrite(_3V3_SOCKETB, LOW);
 				break;

 			case AGR_XTR_SOCKET_D:
				digitalWrite(_3V3_SOCKETD, LOW);
 				break;

			case AGR_XTR_SOCKET_E:
				digitalWrite(_3V3_SOCKETE, LOW);
				break;

 			default:
				break;
 		}
 	}

 }

 /*!
 * \brief Manages the 12v power supplies of Agriculture Xtreme board
 * \param state desired state 
 * \return void
 */
void WaspSensorAgrXtr::set12v(uint8_t state)
{
	// enable I2C in pin expansor enabling isolator
	digitalWrite(EXPAN_ISO_EN, HIGH);
	delay(10);
	
	// enable DC-DC
	digitalWrite(SW_12V, HIGH);

	// Pin expander modes
	mcp.pinMode(AGR_XTR_SOCKET_A, OUTPUT);
	mcp.pinMode(AGR_XTR_SOCKET_B, OUTPUT);
	mcp.pinMode(AGR_XTR_SOCKET_C, OUTPUT);
	mcp.pinMode(AGR_XTR_SOCKET_D, OUTPUT);
	mcp.pinMode(AGR_XTR_SOCKET_E, OUTPUT);
	mcp.pinMode(AGR_XTR_SOCKET_F, OUTPUT);
	mcp.pinMode(MCP_GP1, INPUT);
	mcp.pinMode(MCP_GP1, INPUT);
	
	// update _12vStateRegister
	if (state == _12V_ON)
	{
		//_12vStateRegister update
		bitSet(AgricultureXtr._12vStateRegister, _socket);
	}
	else
	{
		//_12vStateRegister update
		bitClear(AgricultureXtr._12vStateRegister, _socket); 
	}
	
	// update every pin in expander
	for(int i=2; i<8; i++)
	{
		bool bit_state = bitRead(AgricultureXtr._12vStateRegister, i);
		mcp.digitalWrite(i, bit_state);
	}

	// if all 12v supplies are ON print warning to avoid overcurrents.
	if(AgricultureXtr._12vStateRegister >= 0b11111100)
	{
		PRINTLN_AGR_XTR(F("WARNING - Possible overcurrent, 12V is ON in all the sockets"));
	}
	
	//If every 12V register if OFF, then turn OFF DC-DC
	if(AgricultureXtr._12vStateRegister == 0)
	{
		#if DEBUG_AGR_XTR == 2
			PRINTLN_AGR_XTR(F("12V OFF"));
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
 * \brief Controls the on board multiplexor acording to _socket selected
 		OUT 	- SOCKET - INPUT (A,B)
		Y0 		- Data B -	(0,0)
		Y1 		- Data C -	(1,0)
		Y2 		- Data D -	(0,1)
		Y3 		- Data A -	(1,1)
 * \return void
 */
void WaspSensorAgrXtr::setMux()
{
	// enable mux
	digitalWrite(MUX_EN, LOW);

	// set multiplexor according socket and turn on power if necessary
	switch (_socket)
	{
		case AGR_XTR_SOCKET_A:
			digitalWrite(MUX_A, HIGH);
			digitalWrite(MUX_B, HIGH);
			break;

		case AGR_XTR_SOCKET_B:
			digitalWrite(MUX_A, LOW);
			digitalWrite(MUX_B, LOW);
			break;

		case AGR_XTR_SOCKET_C:
			digitalWrite(MUX_A, HIGH);
			digitalWrite(MUX_B, LOW);
			break;

		case AGR_XTR_SOCKET_D:
			digitalWrite(MUX_A, LOW);
			digitalWrite(MUX_B, HIGH);
			break;

		default:
			break;
	}
	
	delay(10);

}

/*!
 * \brief Read the EEPROM memory serial number
 * \param void
 * \return 1 if OK, 0 otherwise.
 */
uint8_t WaspSensorAgrXtr::readSerialNumber()
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
	if (I2C.scan(agr_xtr_eeprom_address) == 0)
	{
		// Reading manufacturer code (should be 0x29)
		I2C.read(agr_xtr_eeprom_address, manufacturer_code_address, &manufacturer_code, 1);
		
		// Reading device code (should be 0x41)
		I2C.read(agr_xtr_eeprom_address, device_code_address, &device_code, 1);
		
		if ((manufacturer_code == 0x29) && (device_code == 0x41))
		{
			I2C.read(agr_xtr_eeprom_address, serial_number_address, boardSerialNumber, 4);
			
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
 * \brief Write the I2C EEPROM
 * \param void
 * \return 0 if OK, otherwise error.
 */
uint8_t WaspSensorAgrXtr::writeEEPROM(uint8_t address, uint8_t value)
{	
	uint8_t flag3v3 = 0;
	
	// reserved addresses below 0x50
	if( address >= 0x50 ) 
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
		if (I2C.scan(agr_xtr_eeprom_address) == 0)
		{
			int rv = I2C.write(agr_xtr_eeprom_address, address, value);
			
			digitalWrite(EXPAN_ISO_EN, LOW);
			if (flag3v3){
				PWR.setSensorPower(SENS_3V3, SENS_OFF);
			}
			return rv;
		}
	}
	
	digitalWrite(EXPAN_ISO_EN, LOW);
	if (flag3v3){
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}
	return 1;
}

/*!
 * \brief Read the I2C EEPROM
 * \param void
 * \return data if OK, otherwise -1.
 */
int8_t WaspSensorAgrXtr::readEEPROM(uint8_t address)
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
	if (I2C.scan(agr_xtr_eeprom_address) == 0)
	{
		uint8_t rdata = 0;
		I2C.read(agr_xtr_eeprom_address, address, &rdata, 1);
		
		digitalWrite(EXPAN_ISO_EN, LOW);
		if (flag3v3){
			PWR.setSensorPower(SENS_3V3, SENS_OFF);
		}
		return rdata;
	}
	
	digitalWrite(EXPAN_ISO_EN, LOW);
	if (flag3v3){
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
	}
	return -1;
}

//******************************************************************************
// SDI-12 functions
//******************************************************************************


/*!
 * \brief detects if SDI12 sensor is present
 * \param sensorName SDI-12 senor name
 * \return return 0 if not, 1 if present.
 */
uint8_t WaspSensorAgrXtr::isSensor(uint8_t sensorName)
{
	// clear variables
	memset(sensorModel, 0x00, sizeof(sensorModel));
	memset(sensorVersion, 0x00, sizeof(sensorVersion));
	memset(AgricultureXtr.sensorSerialNumber, 0x00, sizeof(AgricultureXtr.sensorSerialNumber));
	
	// check if sensor is present. Copy command from flash memory and send it.
	strcpy_P(command, (char*)pgm_read_word(&(table_agrxtr[5])));
	sdi12.sendCommand(command, strlen(command));
	
	sdi12.readCommandAnswer(33,LISTEN_TIME);
	
	//necessary delay
	delay(30);
	
	/* parse answer
	* SENSOR ADDRESS | SDI12 SUPPORT | VENDOR | MODEL | VERSION | SERIAL |
	*/
	if (sdi12.available() >= 20)
	{

		address = sdi12.read();

		// discard two bytes
		sdi12.read();
		sdi12.read();

		// SDI12 SUPPORT model
		for(uint8_t i = 0;i < 8; i++)
		{
			sdi12.read();
		}

		// sensor model
		for(uint8_t i = 0;i < 6; i++)
		{
			sensorModel[i] = sdi12.read();
		}
		
		// sensor version
		for(uint8_t i = 0;i < 3; i++)
		{
			AgricultureXtr.sensorVersion[i] = sdi12.read();
		}

		// sensor serial number
		for(uint8_t i = 0;i < 13; i++)
		{
			char byte_buffer = sdi12.read();
			//13 is carriage return, end of serial number
			if (byte_buffer == 13) 
			{	
				break;
			}
			else
			{
				AgricultureXtr.sensorSerialNumber[i] = byte_buffer;
			}
		}
	}
	
	char sensorNameStr[7]; 
	memset(sensorNameStr, 0x00, sizeof(sensorNameStr));
	
	switch (sensorName)
	{
		case _5TE:
			strncpy(sensorNameStr, "5TE", 3);
			break;
			
		case _5TM:
			strncpy(sensorNameStr, "5TM", 3);
			break;
			
		case GS3:
			strncpy(sensorNameStr, "GS3", 3);
			break;
			
		case VP4:
			strncpy(sensorNameStr, "VP-4", 3);
			break;
			
		case MPS6:
			strncpy(sensorNameStr, "MPS-6", 3);
			break;
			
		case SO411:
			strncpy(sensorNameStr, "SO-411", 3);
			break;
			
		case SI411:
			strncpy(sensorNameStr, "SI-411", 3);
			break;
			
		case SF421:
			strncpy(sensorNameStr, "SF-421", 3);
			break;
			
		default:
			break;
	}

	//Compare if the Model field returned by the sensor is equal to sensorName
	if(strncmp(sensorModel, sensorNameStr,strlen(sensorNameStr)) == 0)
	{
		return 1;
	}
	else
	{
		if (sensorModel[0] == 0x00)
		{
			#if DEBUG_AGR_XTR == 1
				char message[20];
				//"sensor not detected"
				strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[8]))); 
				PRINTLN_AGR_XTR(message);
			#endif
		}
		else 
		{
			#if DEBUG_AGR_XTR == 1
				PRINT_AGR_XTR(F("other sensor: "));
				USB.println(sensorModel);
			#endif
		}

		return 0;
	}
}

/*!
 * \brief send measurement command to the SDI-12 sensor to start measuring
 * \param void
 * \return return 0 if invalid answer. 1 if ok.
 */
uint8_t WaspSensorAgrXtr::startSensor()
{
	char aux[3];
	memset(timeToNextMeasure, 0x00, sizeof(timeToNextMeasure));
	
	// build command with address
	strcpy_P(aux, (char*)pgm_read_word(&(table_agrxtr[1])));

	sprintf(command, "%c%s", address, aux);
	sdi12.sendCommand(command, strlen(command));
	sdi12.readCommandAnswer(5,LISTEN_TIME);
	
	//necessary delay
	delay(30);
	
	// parse answer
	if (sdi12.available() >= 5)
	{
		// skip sensor address
		sdi12.read();

		// Measurement data will be available after specified time
		timeToNextMeasure[0] = sdi12.read();
		timeToNextMeasure[1] = sdi12.read();
		timeToNextMeasure[2] = sdi12.read();

		// Number of values returned
		numberOfMeasures = sdi12.read();
	}
	else
	{
		//invalid data
		#if DEBUG_AGR_XTR == 1
			char message[20];
			//"invalid data"
			strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[9]))); 
			PRINT_AGR_XTR(message);
		#endif
		return 0;
	}

	#if DEBUG_AGR_XTR == 2
		PRINT_AGR_XTR(F("time:"));
		USB.println(timeToNextMeasure);
		PRINT_AGR_XTR(F("N measures:"));
		USB.println(numberOfMeasures);
	#endif

	return 1;
}

 /*!
 * \brief Reads the data of the SDI-12 sensor and stores it in a buffer
 * \param sensorType selected SDI-12 sensor type
 * \return 0 if sensor not present or invalid data. 1 Otherwise.
 */
uint8_t WaspSensorAgrXtr::read(uint8_t sensorType)
{
	char aux[4];
	uint8_t i = 0;
	
	memset(aux, 0x00, sizeof(aux));

	//check if decagon connected
	if (isSensor(sensorType) == 0)
	{
		sdi12.setState(DISABLED);

		// disable mux
		digitalWrite(MUX_EN, HIGH);			
		return 0;
	}

	if (startSensor() == 0)
	{
		sdi12.setState(DISABLED);

		// disable mux
		digitalWrite(MUX_EN, HIGH);			
		return 0;
	}

	// now wait timeToNextMeasure till data is ready + aditional delay
	uint8_t time = atoi(timeToNextMeasure);
	
	delay(time*1000);
	
	// send data command aD0!. Build command with address
	strcpy_P(aux, (char*)pgm_read_word(&(table_agrxtr[2])));
	snprintf(command, sizeof(command), "%c%s", address, aux);
	
	sdi12.sendCommand(command, strlen(command));
	sdi12.readCommandAnswer(30,LISTEN_TIME);
	
	// clear measures array
	memset(measures, 0x00, sizeof(measures));
	
	// store the reading in measures buffer
	if (sdi12.available() > 7) 
	{
		//skip address because it is not possible to connect more than one SDI-12 sensor at the same time
		sdi12.read();
		
		while (sdi12.available() && (i < 30))
		{
			measures[i] = sdi12.read();
			if (measures[i] == NULL) break;
			i++;
		}	
	}
	
	sdi12.setState(DISABLED);

	// disable mux
	digitalWrite(MUX_EN, HIGH);
	
	return 1;
}


//******************************************************************************
// 5TE Sensor Class functions
//******************************************************************************


/*!
 * \brief 5TE Class constructor
 * \param socket selected socket for sensor
 */
Decagon_5TE::Decagon_5TE(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_5TE::ON()
{
	char message[70];
	
	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}
	
	if((_socket == AGR_XTR_SOCKET_E) || (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("5TE"));
		
		return 0;
	}
	
	super::ON();	//SDI12 needs both 3v3 and 5v
	set12v(_12V_ON);
	
	//neccessary delay after powering the sensor
	delay(300);
	
	#if DEBUG_AGR_XTR == 2
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[10]))); 
		PRINT_AGR_XTR(message);
		USB.println(_socket, DEC);
	#endif
	
	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Decagon_5TE::OFF()
{
	set12v(_12V_OFF);
	super::OFF();
}

/*!
 * \brief Reads the sensor data
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_5TE::read()
{
	setMux();
	
	// Initialize variables
	sensor5TE.dielectricPermittivity = 0;
	sensor5TE.electricalConductivity = 0;
	sensor5TE.temperature = 0;
	
	if (super::read(_5TE) == 1)
	{
		return parse5TE();		
	}
	else
	{
		return 0;
	}
}


/*!
 * \brief Parses the values measured from the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_5TE::parse5TE()
{

	uint8_t i = 0;
	uint8_t counter = 0;
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t len = strlen(measures);

	char dielectricPermittivity[20];
	char electricalConductivity[20];
	char temperature[20];

	//Empty the arrays
	memset(temperature, 0x00, sizeof(temperature));
	memset(dielectricPermittivity, 0x00, sizeof(dielectricPermittivity));
	memset(electricalConductivity, 0x00, sizeof(electricalConductivity));

	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter < 3) || (i <= len))
	{
		if ((measures[i] == '+') || (measures[i] == '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1:
				dielectricPermittivity[a] = measures[i];
				a++;
				break;

			case 2:
				electricalConductivity[b] = measures[i];
				b++;
				break;

			case 3:
				temperature[c] = measures[i];
				c++;
				break;

			default: 
				break;
		}
		i++;
	}

	//add eof to strings
	dielectricPermittivity[a] = '\0';
	electricalConductivity[b] = '\0';
	temperature[c] = '\0';

	// Convert strings to float values
	sensor5TE.dielectricPermittivity = atof(dielectricPermittivity);
	sensor5TE.electricalConductivity = atof(electricalConductivity);
	sensor5TE.temperature = atof(temperature);

	#if DEBUG_AGR_XTR == 1
		PRINT_AGR_XTR(F("Measures:"));
		USB.print(measures);
		PRINT_AGR_XTR(F("Permittivity:"));
		USB.println(sensor5TE.dielectricPermittivity);
		PRINT_AGR_XTR(F("Conductivity:"));
		USB.println(sensor5TE.electricalConductivity);
		PRINT_AGR_XTR(F("Temp:"));
		USB.println(sensor5TE.temperature);
	#endif

	// If three values have been parsed, return 1.
	if (counter != 3)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}


//******************************************************************************
// 5TM Sensor Class functions
//******************************************************************************


/*!
 * \brief 5TM Class constructor
 * \param socket selected socket for sensor
 */
Decagon_5TM::Decagon_5TM(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_5TM::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_E) || (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("5TM"));

		return 0;
	}

	super::ON();	//SDI12 needs both 3v3 and 5v
	set12v(_12V_ON);

	//neccessary delay after powering the sensor
	delay(300);
	
	#if DEBUG_AGR_XTR == 2
		//"socket (!): "
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[10]))); 
		PRINT_AGR_XTR(message);
		USB.println(_socket, DEC);
	#endif

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Decagon_5TM::OFF()
{
	set12v(_12V_OFF);
	super::OFF();

}

/*!
 * \brief Reads the sensor data
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_5TM::read()
{
	
	setMux();
	
	// Initialize variables
	sensor5TM.dielectricPermittivity = 0;
	sensor5TM.temperature = 0;
	
	if (super::read(_5TM) == 1)
	{
		return parse5TM();		
	}
	else
	{
		return 0;
	}
}


/*!
 * \brief Parses the values measured from the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_5TM::parse5TM()
{

	uint8_t i = 0;
	uint8_t counter = 0;
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t len = strlen(measures);

	//! Variable: Array to store measured Volumetric Water conductivity in m3/m3
	char dielectricPermittivity[20];

	//! Variable: Array to store measured temperature in ºC
	char temperature[20];

	//Empty the arrays
	memset(dielectricPermittivity, 0x00, sizeof(dielectricPermittivity));
	memset(temperature, 0x00, sizeof(temperature));


	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter < 2) || (i<=len))
	{
		if ((measures[i]== '+') || (measures[i]== '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1:
				dielectricPermittivity[a] = measures[i];
				a++;
				break;

			case 2:
				temperature[b] = measures[i];
				b++;
				break;

			default:
				break;
		}
		i++;
	}

	//add eof to strings
	dielectricPermittivity[a] = '\0';
	temperature[b] = '\0';

	// Convert strings to float values
	sensor5TM.dielectricPermittivity = atof(dielectricPermittivity);
	sensor5TM.temperature = atof(temperature);

	#if DEBUG_AGR_XTR == 1
		PRINT_AGR_XTR(F("Measures:"));
		USB.print(measures);
		PRINT_AGR_XTR(F("Permittivity:"));
		USB.println(sensor5TM.dielectricPermittivity);
		PRINT_AGR_XTR(F("Temp:"));
		USB.println(sensor5TM.temperature);
	#endif

	// If three values have been parsed, return 1.
	if (counter != 2)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

//******************************************************************************
// GS3 Sensor Class functions
//******************************************************************************

/*!
 * \brief GS3 Class constructor
 * \param socket selected socket for sensor
 */
Decagon_GS3::Decagon_GS3(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_GS3::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_E) || (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("GS3"));

		return 0;
	}

	super::ON();	//SDI12 needs both 3v3 and 5v
	set12v(_12V_ON);

	//neccessary delay after powering the sensor
	delay(300);
	
	#if DEBUG_AGR_XTR == 2
		//"socket (!): "
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[10]))); 
		PRINT_AGR_XTR(message);
		USB.println(_socket, DEC);
	#endif

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Decagon_GS3::OFF()
{
	set12v(_12V_OFF);
	super::OFF();

}

/*!
 * \brief Reads the sensor data
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_GS3::read()
{

	setMux();
	
	// Initialize variables
	sensorGS3.dielectricPermittivity = 0;
	sensorGS3.electricalConductivity = 0;
	sensorGS3.temperature = 0;

	if (super::read(GS3) == 1)
	{
		return parseGS3();		
	}
	else
	{
		return 0;
	}

}


/*!
 * \brief Parses the values measured from the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_GS3::parseGS3()
{

	uint8_t i = 0;
	uint8_t counter = 0;
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t len = strlen(measures);

	//! Variable: Array to store measured Volumetric Water conductivity in m3/m3
	char dielectricPermittivity[20];

	//! Variable: Array to store measured electrical conductivity in μS/cm
	char electricalConductivity[20];

	//! Variable: Array to store measured temperature in ºC
	char temperature[20];

	//Empty the arrays
	memset(temperature, 0x00, sizeof(temperature));
	memset(dielectricPermittivity, 0x00, sizeof(dielectricPermittivity));
	memset(electricalConductivity, 0x00, sizeof(electricalConductivity));

	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter < 3) || (i<=len))
	{
		if ((measures[i]== '+') || (measures[i]== '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1: 
				dielectricPermittivity[a] = measures[i];
				a++;
				break;

			case 2:
				temperature[b] = measures[i];
				b++;
				break;

			case 3:
				electricalConductivity[c] = measures[i];
				c++;
				break;

			default: 
				break;
		}
		i++;
	}

	//add eof to strings
	dielectricPermittivity[a] = '\0';
	temperature[b] = '\0';
	electricalConductivity[c] = '\0';


	// Convert strings to float values
	sensorGS3.dielectricPermittivity = atof(dielectricPermittivity);
	sensorGS3.electricalConductivity = atof(electricalConductivity);
	sensorGS3.temperature = atof(temperature);

	#if DEBUG_AGR_XTR == 1
		PRINT_AGR_XTR(F("Measures:"));
		USB.print(measures);
		PRINT_AGR_XTR(F("Permittivity:"));
		USB.println(sensorGS3.dielectricPermittivity);
		PRINT_AGR_XTR(F("Conductivity:"));
		USB.println(sensorGS3.electricalConductivity);
		PRINT_AGR_XTR(F("Temp:"));
		USB.println(sensorGS3.temperature);
	#endif

	// If three values have been parsed, return 1.
	if (counter != 3)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}


//******************************************************************************
// VP4 Sensor Class functions
//******************************************************************************

/*!
 * \brief VP4 Class constructor
 * \param socket selected socket for sensor
 */

Decagon_VP4::Decagon_VP4(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_VP4::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_E) || (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("VP4"));

		return 0;
	}

	super::ON();	//SDI12 needs both 3v3 and 5v
	set12v(_12V_ON);

	//neccessary delay after powering the sensor
	delay(800);
	
	#if DEBUG_AGR_XTR == 2
		//"socket (!): "
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[10]))); 
		PRINT_AGR_XTR(message);
		USB.println(_socket, DEC);
	#endif

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Decagon_VP4::OFF()
{
	set12v(_12V_OFF);
	super::OFF();

}

/*!
 * \brief Reads the sensor data
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_VP4::read()
{

	setMux();
	
	// Initialize variables
	sensorVP4.vaporPressure = 0;
	sensorVP4.temperature = 0;
	sensorVP4.relativeHumidity = 0;
	sensorVP4.atmosphericPressure = 0;
	
	if (super::read(VP4) == 1)
	{
		return parseVP4();		
	}
	else
	{
		return 0;
	}
}


/*!
 * \brief Parses the values measured from the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_VP4::parseVP4()
{

	uint8_t i = 0;
	uint8_t counter = 0;
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint8_t len = strlen(measures);

	//! Variable: Array to store measured Vapor Pressure in kPa
	char vaporPressure[20];

	//! Variable: Array to store measured temperature in ºC
	char temperature[20];

	//! Variable: store measured Relative Humidity in %
	char relativeHumidity[20];

	//! Variable: store measured Atmospheric Pressure in kPa
	char atmosphericPressure[20];

	//Empty the data arrays
	memset(vaporPressure, 0x00, sizeof(vaporPressure));
	memset(temperature, 0x00, sizeof(temperature));
	memset(relativeHumidity, 0x00, sizeof(relativeHumidity));
	memset(atmosphericPressure, 0x00, sizeof(atmosphericPressure));


	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter < 4) || (i<=len))
	{
		if ((measures[i]== '+') || (measures[i]== '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1: 
				vaporPressure[a] = measures[i];
				a++;
				break;

			case 2: 
				temperature[b] = measures[i];
				b++;
				break;

			case 3: 
				relativeHumidity[c] = measures[i];
				c++;
				break;

			case 4:
				atmosphericPressure[d] = measures[i];
				d++;
				break;

			default:
				break;
		}
		i++;
	}

	//add eof to strings
	vaporPressure[a] = '\0';
	temperature[b] = '\0';
	relativeHumidity[c] = '\0';
	atmosphericPressure[d] = '\0';

	// Convert strings to float values
	sensorVP4.vaporPressure = atof(vaporPressure);
	sensorVP4.temperature = atof(temperature);
	sensorVP4.relativeHumidity = atof(relativeHumidity)*100;
	sensorVP4.atmosphericPressure = atof(atmosphericPressure);

	#if DEBUG_AGR_XTR == 1
		PRINT_AGR_XTR(F("Measures:"));
		USB.print(measures);
		PRINT_AGR_XTR(F("Vapor Pressure:"));
		USB.println(sensorVP4.vaporPressure);
		PRINT_AGR_XTR(F("Temperature:"));
		USB.println(sensorVP4.temperature);
		PRINT_AGR_XTR(F("Relative Humidity:"));
		USB.println(sensorVP4.relativeHumidity);
		PRINT_AGR_XTR(F("Atmospheric Pressure:"));
		USB.println(sensorVP4.atmosphericPressure);
	#endif

	// If four values have been parsed, return 1.
	if (counter != 4)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

//******************************************************************************
// MPS6 Sensor Class functions
//******************************************************************************

/*!
 * \brief MPS6 Class constructor
 * \param socket selected socket for sensor
 */
Decagon_MPS6::Decagon_MPS6(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_MPS6::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_E) || (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("MPS6"));

		return 0;
	}

	super::ON();	//SDI12 needs both 3v3 and 5v
	set12v(_12V_ON);

	//neccessary delay after powering the sensor
	delay(300);
	
	#if DEBUG_AGR_XTR == 2
		//"socket (!): "
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[10]))); 
		PRINT_AGR_XTR(message);
		USB.println(_socket, DEC);
	#endif

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Decagon_MPS6::OFF()
{
	set12v(_12V_OFF);
	super::OFF();

}

/*!
 * \brief Reads the sensor data
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_MPS6::read()
{

	setMux();
	
	// Initialize variables
	sensorMPS6.waterPotential = 0;
	sensorMPS6.temperature = 0;
	
	if (super::read(MPS6) == 1)
	{
		return parseMPS6();		
	}
	else
	{
		return 0;
	}
}


/*!
 * \brief Parses the values measured from the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Decagon_MPS6::parseMPS6()
{

	uint8_t i = 0;
	uint8_t counter = 0;
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t len = strlen(measures);

	//! Variable: Array to store measured Vapor Pressure in kPa
	char waterPotential[20];

	//! Variable: Array to store measured temperature in ºC
	char temperature[20];


	//Empty the data arrays
	memset(waterPotential, 0x00, sizeof(waterPotential));
	memset(temperature, 0x00, sizeof(temperature));

	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter < 2) || (i<=len))
	{
		if ((measures[i]== '+') || (measures[i]== '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1:
				waterPotential[a] = measures[i];
				a++;
				break;

			case 2:
				temperature[b] = measures[i];
				b++;
				break;


			default:
				break;
		}
		i++;
	}

	//add eof to strings
	waterPotential[a] = '\0';
	temperature[b] = '\0';

	// Convert strings to float values
	sensorMPS6.waterPotential = atof(waterPotential);
	sensorMPS6.temperature = atof(temperature);


	#if DEBUG_AGR_XTR == 1
		PRINT_AGR_XTR(F("Measures:"));
		USB.print(measures);
		PRINT_AGR_XTR(F("Water Potential:"));
		USB.println(sensorMPS6.waterPotential);
		PRINT_AGR_XTR(F("Temperature:"));
		USB.println(sensorMPS6.temperature);
	#endif

	// If four values have been parsed, return 1.
	if (counter != 2)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}


//******************************************************************************
// SO-411 Sensor Class functions
//******************************************************************************


/*!
 * \brief SO411 Class constructor
 * \param socket selected socket for sensor
 */
Apogee_SO411::Apogee_SO411(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}

}


/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SO411::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_E) || (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("SO-411"));

		return 0;
	}


	super::ON();	//SDI12 needs both 3v3 and 5v
	set12v(_12V_ON);

	//neccessary delay after powering the sensor
	delay(300);
	
	#if DEBUG_AGR_XTR == 2
		//"socket (!): "
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[10]))); 
		PRINT_AGR_XTR(message);
		USB.println(_socket, DEC);
	#endif

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Apogee_SO411::OFF()
{
	//Turn off the sensor and the heater
	set12v(_12V_OFF);
	super::OFF();

}

/*!
 * \brief Reads the sensor data
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SO411::read()
{

	setMux();
	
	// Initialize variables
	sensorSO411.calibratedOxygen = 0;
	sensorSO411.bodyTemperature = 0;
	sensorSO411.milliVolts = 0;

	if (super::read(SO411) == 1)
	{
		return parseSO411();		
	}
	else
	{
		return 0;
	}

}


/*!
 * \brief Parses the values measured from the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SO411::parseSO411()
{

	uint8_t i = 0;
	uint8_t counter = 0;
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t len = strlen(measures);

	//! Variable: Array to store measured calibrated Oxygen
	char calibratedOxygen[20];

	//! Variable: Array to store measured body Temperature
	char bodyTemperature[20];

	//! Variable: Array to store measured milliVolts
	char milliVolts[20];

	//Empty the arrays
	memset(milliVolts, 0x00, sizeof(milliVolts));
	memset(calibratedOxygen, 0x00, sizeof(calibratedOxygen));
	memset(bodyTemperature, 0x00, sizeof(bodyTemperature));

	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter < 3) || (i<=len))
	{
		if ((measures[i]== '+') || (measures[i]== '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1: 
				calibratedOxygen[a] = measures[i];
				a++;
				break;

			case 2: 
				milliVolts[b] = measures[i];
				b++;
				break;

			case 3: 
				bodyTemperature[c] =  measures[i];
				c++;
				break;

			default: 
				break;
		}
		i++;
	}

	//add eof to strings
	calibratedOxygen[a] = '\0';
	milliVolts[b] = '\0';
	bodyTemperature[c] = '\0';


	// Convert strings to float values
	sensorSO411.calibratedOxygen = atof(calibratedOxygen);
	sensorSO411.bodyTemperature = atof(bodyTemperature);
	sensorSO411.milliVolts = atof(milliVolts);

	#if DEBUG_AGR_XTR == 1
		PRINT_AGR_XTR(F("Measures:"));
		USB.print(measures);
		PRINT_AGR_XTR(F("Calibrated Oxygen:"));
		USB.println(sensorSO411.calibratedOxygen);
		PRINT_AGR_XTR(F("Body Temperature:"));
		USB.println(sensorSO411.bodyTemperature);
		PRINT_AGR_XTR(F("MilliVolts:"));
		USB.println(sensorSO411.milliVolts);
	#endif

	// If three values have been parsed, return 1.
	if (counter != 3)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}


//******************************************************************************
// SI-411 Sensor Class functions
//******************************************************************************


/*!
 * \brief SI411 Class constructor
 * \param socket selected socket for sensor
 */
Apogee_SI411::Apogee_SI411(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}

}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SI411::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_E) || (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("SI-411"));

		return 0;
	}


	super::ON();	//SDI12 needs both 3v3 and 5v
	set12v(_12V_ON);
	
	//neccessary delay after powering the sensor
	delay(300);
	
	#if DEBUG_AGR_XTR == 2
		//"socket (!): "
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[10]))); 
		PRINT_AGR_XTR(message);
		USB.println(_socket, DEC);
	#endif

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Apogee_SI411::OFF()
{
	set12v(_12V_OFF);
	super::OFF();

}

/*!
 * \brief Reads the sensor data
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SI411::read()
{

	setMux();

	// Initialize variables
	sensorSI411.targetTemperature = 0;
	
	if (super::read(SI411) == 1)
	{
		return parseSI411();		
	}
	else
	{
		return 0;
	}

}



/*!
 * \brief Parses the values measured from the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SI411::parseSI411()
{

	uint8_t i = 0;
	uint8_t counter = 0;
	uint8_t a = 0;
	uint8_t len = strlen(measures);

	//! Variable: Array to store measured Target Temperature in ºC
	char targetTemperature[20];

	//Empty the data arrays
	memset(targetTemperature, 0x00, sizeof(targetTemperature));

	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while(i <= len)
	{

		if ((measures[i]== '+') || (measures[i]== '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1: 
				targetTemperature[a] = measures[i];
				a++;
				break;

			default:
				break;
		}
		i++;

	}

	//add eof to strings
	targetTemperature[a] = '\0';


	// Convert strings to float values
	sensorSI411.targetTemperature = atof(targetTemperature);


	#if DEBUG_AGR_XTR == 1
		PRINT_AGR_XTR(F("measures:"));
		USB.print(measures);
		PRINT_AGR_XTR(F("Target Temperature:"));
		USB.println(sensorSI411.targetTemperature);

	#endif

	// If one value have been parsed, return 1.
	if (targetTemperature[0] == NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}


//******************************************************************************
// SF-421 Sensor Class functions
//******************************************************************************


/*!
 * \brief SF421 Class constructor
 * \param socket selected socket for sensor
 */
Apogee_SF421::Apogee_SF421(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}

}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SF421::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_E) || (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("SF-421"));

		return 0;
	}

	super::ON();	//SDI12 needs both 3v3 and 5v
	set12v(_12V_ON);

	//neccessary delay after powering the sensor
	delay(300);

	#if DEBUG_AGR_XTR == 2
		//"socket (!): "
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[10]))); 
		PRINT_AGR_XTR(message);
		USB.println(_socket, DEC);
	#endif

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Apogee_SF421::OFF()
{
	set12v(_12V_OFF);
	super::OFF();

}

/*!
 * \brief Reads the sensor data
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SF421::read()
{

	setMux();
	
	// Initialize variables
	sensorSF421.budTemperature = 0;
	sensorSF421.leafTemperature = 0;
	
	if (super::read(SF421) == 1)
	{
		return parseSF421();		
	}
	else
	{
		return 0;
	}

}


/*!
 * \brief Parses the values measured from the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SF421::parseSF421()
{
	uint8_t i = 0;
	uint8_t counter = 0;
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t len = strlen(measures);

	//! Variable: Array to store measured Target Temperature in ºC
	char budTemperature[20];
	char leafTemperature[20];

	//Empty the data arrays
	memset(budTemperature, 0x00, sizeof(budTemperature));
	memset(leafTemperature, 0x00, sizeof(leafTemperature));

	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter < 2) || (i<=len))
	{

		if ((measures[i]== '+') || (measures[i]== '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1:
				budTemperature[a] = measures[i];
				a++;
				break;

			case 2:
				leafTemperature[b] = measures[i];
				b++;
				break;

			default:
				break;
		}

		i++;
	}

	//add eof to strings
	budTemperature[a] = '\0';
	leafTemperature[b] = '\0';

	// Convert strings to float values
	sensorSF421.budTemperature = atof(budTemperature);
	sensorSF421.leafTemperature = atof(leafTemperature);

	#if DEBUG_AGR_XTR == 1
		PRINT_AGR_XTR(F("measures:"));
		USB.print(measures);
		PRINT_AGR_XTR(F("Bud Temperature:"));
		USB.println(sensorSF421.budTemperature);
		PRINT_AGR_XTR(F("Leaf Temperature:"));
		USB.println(sensorSF421.leafTemperature);

	#endif

	// If one value have been parsed, return 1.
	if (counter != 2)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}


//******************************************************************************
// Leaf Wetness Sensor Class functions
//******************************************************************************

/*!
 * \brief leafWetness Class constructor
 * \param socket selected socket for sensor
 */
leafWetness::leafWetness()
{	
	// store sensor location
	_socket = AGR_XTR_SOCKET_B;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}

}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return void
 */
void leafWetness::ON()
{
	if(AgricultureXtr.redefinedSocket == 1)
	{
		char message[50];
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	super::ON(REG_3V3);
	set3v3(AGR_XTR_SOCKET_B, _3V3_ON);

	//neccessary delay after powering the sensor
	delay(10);
	
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void leafWetness::OFF()
{
	set3v3(AGR_XTR_SOCKET_B, _3V3_OFF);
	super::OFF();

}


/*!
 * \brief Reads the leaf wetness sensor
 * \param void
 * \return return 0 if sensor not present or invalid data. 1 Otherwise.
 */
uint8_t leafWetness::read()
{

	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	delay(10);

	// ADC setup
	ltc.begin();

	// necessary for the sensor
	delay(10);

	wetness = ltc.readADC(ADC_CH3);

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor
	#if DEBUG_AGR_XTR == 1
	PRINT_AGR_XTR(F("wetness: "));
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
 * \brief dendrometer Class constructor 1
 * \param socket selected socket for sensor
 */
dendrometer::dendrometer()
{
	dendrometer(DENDRO_DD);
}

/*!
 * \brief dendrometer Class constructor 2
 * \param socket selected socket for sensor
 */
dendrometer::dendrometer(uint8_t type)
{
	dendroType = type;
	diameter = 0;
	dendroRef = 0;
	dendroGrowth = 0;

	// store sensor location
	_socket = AGR_XTR_SOCKET_C;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}


/*!
 * \brief Turns on the sensor
 * \param void
 * \return void
 */
void dendrometer::ON()
{

	if(AgricultureXtr.redefinedSocket == 1)
	{
		char message[50];
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}



	super::ON(REG_3V3);

	//neccessary delay after powering the sensor
	delay(10);
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void dendrometer::OFF()
{	
	super::OFF();
}



/*!
 * \brief reads the dendrometer sensor and converts its value into mm
 * \param void
 * \return 1 if ok, 0 if something fails
 */
float dendrometer::read(void)
{
	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();

	// necessary for the sensor
	delay(10);

	diameter = ltc.readADC(ADC_CH5);

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor in volts
	#if DEBUG_AGR_XTR == 2
	PRINT_AGR_XTR(F("dendro (V): "));
	USB.printFloat(diameter, 5);
	USB.println();
	#endif

	// Conversion to mm according type
	diameter = (diameter * dendroType) / 3;

	// check value of the sensor in mm
	#if DEBUG_AGR_XTR == 1
	PRINT_AGR_XTR(F("diameter (mm): "));
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
 * \brief Sets reference value to measure dendrometer growth
 * \param void
 * \return 1 if ok, 0 if something fails
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
 * \brief Compare current dendrometer value with reference
 * \param void
 * \return 1 if ok, 0 if something fails
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
 * \brief weatherStation Class constructor
 * \param socket selected socket for sensor
 */
weatherStation::weatherStation()
{
	_socket = AGR_XTR_SOCKET_E;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return void
 */
void weatherStation::ON()
{
	if(AgricultureXtr.redefinedSocket == 1)
	{
		char message[50];
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	Utils.setMuxAux2();
	beginSerial(19200, 1);
	serialFlush(1);
	
	super::ON(REG_3V3);
	//Enable RS-485 chip on (shared with 3v3 pin)
	set3v3(_socket, _3V3_ON);
	set12v(_12V_ON);

	const uint16_t BUFFER_SIZE = 300;
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
			if(strstr(buffer, "<END OF STARTUP MESSAGE>") != NULL)
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
	
	#if DEBUG_AGR_XTR == 2
	USB.print(F("WS RX:"));
	USB.println(buffer);
	#endif
	
	if(strstr(buffer, "GMX100") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX100 found"));
		#endif
		
		stationModel = WS_GMX100;
	}
	else if(strstr(buffer, "GMX101") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX101 found"));
		#endif
		
		stationModel = WS_GMX101;
	}
	else if(strstr(buffer, "GMX200") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX200 found"));
		#endif
		
		stationModel = WS_GMX200;
	}
	else if(strstr(buffer, "GMX240") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX240 found"));
		#endif
		
		stationModel = WS_GMX240;
	}
	else if(strstr(buffer, "GMX300") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX300 found"));
		#endif
		
		stationModel = WS_GMX300;
	}
	else if(strstr(buffer, "GMX301") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX301 found"));
		#endif
		
		stationModel = WS_GMX301;
	}
	else if(strstr(buffer, "GMX400") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX400 found"));
		#endif
		
		stationModel = WS_GMX400;
	}
	else if(strstr(buffer, "GMX500") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX500 found"));
		#endif
		
		stationModel = WS_GMX500;
	}
	else if(strstr(buffer, "GMX501") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX501 found"));
		#endif
		
		stationModel = WS_GMX501;
	}
	else if(strstr(buffer, "GMX531") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX531 found"));
		#endif
		
		stationModel = WS_GMX531;
	}
	else if(strstr(buffer, "GMX541") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX541 found"));
		#endif
		
		stationModel = WS_GMX541;
	}
	else if(strstr(buffer, "GMX550") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX550 found"));
		#endif
		
		stationModel = WS_GMX550;
	}
	else if(strstr(buffer, "GMX551") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX551 found"));
		#endif
		
		stationModel = WS_GMX551;
	}
	else if(strstr(buffer, "GMX600") != NULL)
	{
		#if DEBUG_AGR_XTR == 2
		PRINTLN_AGR_XTR(F("GMX600 found"));
		#endif
		
		stationModel = WS_GMX600;
	}
	
	
	//neccessary delay for a first good read
	delay(100);
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void weatherStation::OFF()
{
	set12v(_12V_OFF);
	super::OFF();
}

/*!
 * \brief enable/disable gps
 * \param gps option
 * \return void
 */
void weatherStation::GPS(uint8_t option)
{
	gps = option;
}

/*!
 * \brief Reads the weather Station sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t weatherStation::sendCommand(char* str)
{
	const uint16_t BUFFER_SIZE = 130;
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
	
	
	printString(str, 1);
	#if DEBUG_AGR_XTR == 2
	USB.print(F("WS TX:"));
	USB.println(str);
	
	USB.print(F("WS RX:"));
	#endif
	
		//Capture buffer
	while (((millis() - previous) < 8000) && (exitWhile == 0) && (dataFrameFound == 0))
	{
		if (serialAvailable(1) > 0)
		{
			//Avoid storing 0x00 in our buffer string or 0x02 STX (Start of Text)
			char buffer_temp = serialRead(1);
			#if DEBUG_AGR_XTR == 2
			USB.print(buffer_temp);
			//USB.print(".");
			#endif
			if ((buffer_temp != 0x00) && (buffer_temp != 0x02))
			{
				//Change ',' for ' ' (whitespace character) for better parsing
				if(buffer_temp != ',')
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
			if (buffer_ws_raw[i-1] == 0x03)
			{
				buffer_ws_raw[i-1] = 0x00;
				dataFrameFound = 1;
			}
			
			if (i-1 == BUFFER_SIZE)
			{
				exitWhile = 1;
			}
		}

		//avoid millis overflow problem after approximately 50 days
		if ( millis() < previous ) previous = millis();
	}
	
	#if DEBUG_AGR_XTR == 2
	USB.println();
	#endif
	
	/*
	#if DEBUG_AGR_XTR == 2
	USB.print(F("WS RX:"));
	USB.println(buffer_ws_raw);
	#endif
	*/
}

/*!
 * \brief Reads the weather Station sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t weatherStation::read()
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
	
	//Send command asking for data (previously "?Q" required)
	printString("Q", 1);
	#if DEBUG_AGR_XTR == 2
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
				if(buffer_temp != ',')
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
			if (buffer_ws_raw[i-1] == 0x03)
			{
				buffer_ws_raw[i-1] = 0x00;
				dataFrameFound = 1;
			}
			
			if (i-1 == BUFFER_SIZE)
			{
				exitWhile = 1;
			}
		}

		//avoid millis overflow problem after approximately 50 days
		if ( millis() < previous ) previous = millis();
	}
	
	#if DEBUG_AGR_XTR == 2
	USB.print(F("WS RX:"));
	USB.println(buffer_ws_raw);
	#endif
	
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
	
	
	char buffer_table[150];
	memset(buffer_table, 0x00, sizeof(buffer_table));
	
	if(dataFrameFound && stationModel == WS_GMX100)
	{
		//Frame is like: 
		//"Q 00000.080 000.080 Y +26 -56 +1 2018-06-12T16:31:11.1 +12.0 0000"
		
		//"%c %s %s %c %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[12])));
		sscanf (buffer_ws_raw, buffer_table,
		&gmx240.node_letter,
		gmx240.precipitation_total,
		gmx240.precipitation_intensity,
		&gmx240.precipitation_status,
		gmx240.x_tilt,
		gmx240.y_tilt,
		gmx240.z_orient,
		gmx240.timestamp,
		gmx240.supply_voltage,
		gmx240.status);
		
		return 1;
	}
	else if(dataFrameFound && stationModel == WS_GMX101)
	{
		//Frame is like: 
		//"Q 0001 01.20 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +32 -17 +1 2017-01-20T11:46:01.3 +05.0 0000"
		
		//"%c %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[13])));
		sscanf (buffer_ws_raw, buffer_table,
		&gmx240.node_letter,
		gmx240.solar_radiation,
		gmx240.sunshine_hours,
		gmx240.sunrise_time,
		gmx240.solar_noon_time,
		gmx240.sunset_time,
		gmx240.position_of_sun,
		gmx240.twilight_civil,
		gmx240.twilight_nautical,
		gmx240.twilight_astronomical,
		gmx240.x_tilt,
		gmx240.y_tilt,
		gmx240.z_orient,
		gmx240.timestamp,
		gmx240.supply_voltage,
		gmx240.status);
		
		return 1;
	}
	else if(dataFrameFound && stationModel == WS_GMX200)
	{
		if (!gps){
			//Frame is like: 
			//"Q 048 000.02 106 000 000.00 000 000.00 000 0100 058 07:58 12:08 16:19 143:+09 16:57 17:39 18:19 00 +00 +1 2018-01-16T09:29:31.1 +05.0 0000"
			
			//"%c %d %s %d %d %s %d %s %d %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[14])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			&gmx240.compass,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status);
			
			return 1;
		}
		else{
			//Frame is like: 
			//"Q 048 000.02 106 000 000.00 000 000.00 000 0100 058 07:58 12:08 16:19 143:+09 16:57 17:39 18:19 00 +00 +1 2018-01-16T09:29:31.1 +05.0 0000
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"
			
			//"%c %d %s %d %d %s %d %s %d %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[24])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			&gmx240.compass,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status,
			gmx240.gps_corrected_speed,
			gmx240.gps_average_corrected_speed,
			gmx240.gps_corrected_gust_speed,
			&gmx240.gps_corrected_gust_direction,
			gmx240.gps_location,
			&gmx240.gps_heading,
			gmx240.gps_speed,
			gmx240.gps_status);
			
			return 1;
			
		}
	}
	else if(dataFrameFound && stationModel == WS_GMX240)
	{
		if (!gps){
			//Frame is like: 
			//"Q 044 000.02 013 145 001.45 145 015.15 131 0000 00000.080 000.080 Y 010 +52 +33 +1 2018-06-11T10:59:20.6 +12.0 0000"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[15])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.precipitation_total,
			gmx240.precipitation_intensity,
			&gmx240.precipitation_status,
			&gmx240.compass,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status);
			
			return 1;
		}
		else{
			//Frame is like: 
			//"Q 044 000.02 013 145 001.45 145 015.15 131 0000 00000.080 000.080 Y 010 +52 +33 +1 2018-06-11T10:59:20.6 +12.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %c %d %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[25])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.precipitation_total,
			gmx240.precipitation_intensity,
			&gmx240.precipitation_status,
			&gmx240.compass,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status,
			gmx240.gps_corrected_speed,
			gmx240.gps_average_corrected_speed,
			gmx240.gps_corrected_gust_speed,
			&gmx240.gps_corrected_gust_direction,
			gmx240.gps_location,
			&gmx240.gps_heading,
			gmx240.gps_speed,
			gmx240.gps_status);
			
			return 1;
		}
		
	}
	else if(dataFrameFound && stationModel == WS_GMX300)
	{
		//Frame is like: 
		//"Q 0999.5 0999.5 0999.5 040 +023.3 +009.1 08.45 1.2 +015.1 07:58 12:08 16:19 162:+15 16:57 17:39 18:19 +00 +01 +1 
		// 2018-01-16T10:55:38.5 +05.1 0000"
		
		//"%c %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[16])));
		sscanf (buffer_ws_raw, buffer_table,
		&gmx240.node_letter,
		gmx240.pressure,
		gmx240.pressure_sea_level,
		gmx240.pressure_station,
		&gmx240.relative_humidity,
		gmx240.temperature,
		gmx240.dewpoint,
		gmx240.absolute_humidity,
		gmx240.air_density,
		gmx240.wet_build_temperature,
		gmx240.sunrise_time,
		gmx240.solar_noon_time,
		gmx240.sunset_time,
		gmx240.position_of_sun,
		gmx240.twilight_civil,
		gmx240.twilight_nautical,
		gmx240.twilight_astronomical,
		gmx240.x_tilt,
		gmx240.y_tilt,
		gmx240.z_orient,
		gmx240.timestamp,
		gmx240.supply_voltage,
		gmx240.status);
		
		return 1;
	}
	else if(dataFrameFound && stationModel == WS_GMX301)
	{
		//Frame is like: 
		//"Q 0999.4 0999.4 0999.4 040 +023.3 +009.0 08.41 2155 00.00 1.2 +015.0 07:58 12:08 16:19 163:+15 16:57 17:39 18:19 +00 +00 +1 
		// 2018-01-16T10:58:40.7 +05.1 0000"
		
		//"%c %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[17])));
		sscanf (buffer_ws_raw, buffer_table,
		&gmx240.node_letter,
		gmx240.pressure,
		gmx240.pressure_sea_level,
		gmx240.pressure_station,
		&gmx240.relative_humidity,
		gmx240.temperature,
		gmx240.dewpoint,
		gmx240.absolute_humidity,
		gmx240.solar_radiation,
		gmx240.sunshine_hours,
		gmx240.air_density,
		gmx240.wet_build_temperature,
		gmx240.sunrise_time,
		gmx240.solar_noon_time,
		gmx240.sunset_time,
		gmx240.position_of_sun,
		gmx240.twilight_civil,
		gmx240.twilight_nautical,
		gmx240.twilight_astronomical,
		gmx240.x_tilt,
		gmx240.y_tilt,
		gmx240.z_orient,
		gmx240.timestamp,
		gmx240.supply_voltage,
		gmx240.status);
		
		return 1;
	}
	else if(dataFrameFound && stationModel == WS_GMX400)
	{
		//Frame is like: 
		//"Q 0999.3 0999.3 0999.3 041 +023.2 +009.3 08.61 00000.000 000.000 N 1.2 +015.1 07:58 12:08 16:19 165:+16 16:57 17:39 18:19 +00 +00 +1 
		// 2018-01-16T11:09:24.0 +05.1 0000"
		
		//"%c %s %s %s %d %s %s %s %s %s %c %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
		strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[18])));
		sscanf (buffer_ws_raw, buffer_table,
		&gmx240.node_letter,
		gmx240.pressure,
		gmx240.pressure_sea_level,
		gmx240.pressure_station,
		&gmx240.relative_humidity,
		gmx240.temperature,
		gmx240.dewpoint,
		gmx240.absolute_humidity,
		gmx240.precipitation_total,
		gmx240.precipitation_intensity,
		&gmx240.precipitation_status,
		gmx240.air_density,
		gmx240.wet_build_temperature,
		gmx240.sunrise_time,
		gmx240.solar_noon_time,
		gmx240.sunset_time,
		gmx240.position_of_sun,
		gmx240.twilight_civil,
		gmx240.twilight_nautical,
		gmx240.twilight_astronomical,
		gmx240.x_tilt,
		gmx240.y_tilt,
		gmx240.z_orient,
		gmx240.timestamp,
		gmx240.supply_voltage,
		gmx240.status);
		
		return 1;
	}
	else if(dataFrameFound && stationModel == WS_GMX500)
	{
		if(!gps){
			//Frame is like: 
			//"Q 056 000.04 115 000 000.00 000 000.00 000 0100 0999.2 0999.2 0999.2 041 +023.2 +009.2 08.56 059 1.2 +015.1 07:58 12:08 16:19 166:+16 
			// 16:57 17:39 18:19 +00 +01 +1 2018-01-16T11:13:19.5 +05.0 0000"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[19])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			&gmx240.compass,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status);
			
			return 1;
		}
		else{
			//Frame is like: 
			//"Q 056 000.04 115 000 000.00 000 000.00 000 0100 0999.2 0999.2 0999.2 041 +023.2 +009.2 08.56 059 1.2 +015.1 07:58 12:08 16:19 166:+16 
			// 16:57 17:39 18:19 +00 +01 +1 2018-01-16T11:13:19.5 +05.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[26])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			&gmx240.compass,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status,
			gmx240.gps_corrected_speed,
			gmx240.gps_average_corrected_speed,
			gmx240.gps_corrected_gust_speed,
			&gmx240.gps_corrected_gust_direction,
			gmx240.gps_location,
			&gmx240.gps_heading,
			gmx240.gps_speed,
			gmx240.gps_status);
			
			return 1;
			
		}
	}
	else if(dataFrameFound && stationModel == WS_GMX501)
	{
		if (!gps){
			//Frame is like: 
			//"Q,003,000.02,062,000,000.00,000,000.00,000,0100,0999.3,0999.3,0999.3,041,+023.3,+009.3,08.61,059,0001,00.00,,,1.2,+015.2,07:58,12:08,16:19,161:+15,16:57,17:39,18:19,+00,+00,+1,,2018-01-16T10:50:19.2,+05.0,0000"
			// faltan los datos de radiacion en el frame de ejemplo
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[20])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			&gmx240.compass,
			gmx240.solar_radiation,
			gmx240.sunshine_hours,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status);
			
			return 1;
		}
		else{
			//Frame is like: 
			//"Q,003,000.02,062,000,000.00,000,000.00,000,0100,0999.3,0999.3,0999.3,041,+023.3,+009.3,08.61,059,0001,00.00,,,1.2,+015.2,07:58,12:08,16:19,161:+15,16:57,17:39,18:19,+00,+00,+1,,2018-01-16T10:50:19.2,+05.0,0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"
			// faltan los datos de radiacion en el frame de ejemplo
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[27])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			&gmx240.compass,
			gmx240.solar_radiation,
			gmx240.sunshine_hours,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status,
			gmx240.gps_corrected_speed,
			gmx240.gps_average_corrected_speed,
			gmx240.gps_corrected_gust_speed,
			&gmx240.gps_corrected_gust_direction,
			gmx240.gps_location,
			&gmx240.gps_heading,
			gmx240.gps_speed,
			gmx240.gps_status);
			
			return 1;
		}
	}
	else if(dataFrameFound && (stationModel == WS_GMX531 || stationModel == WS_GMX541 || stationModel == WS_GMX551))
	{
		if(!gps){
			//Frame is like: 
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 00000.200 000.200 N 042 0001 01.20 
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[21])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			gmx240.precipitation_total,
			gmx240.precipitation_intensity,
			&gmx240.precipitation_status,
			&gmx240.compass,
			gmx240.solar_radiation,
			gmx240.sunshine_hours,
			gmx240.wind_chill,
			gmx240.heat_index,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status);
			
			return 1;
		}
		else{
			//Frame is like: 
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 00000.200 000.200 N 042 0001 01.20 
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[28])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			gmx240.precipitation_total,
			gmx240.precipitation_intensity,
			&gmx240.precipitation_status,
			&gmx240.compass,
			gmx240.solar_radiation,
			gmx240.sunshine_hours,
			gmx240.wind_chill,
			gmx240.heat_index,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status,
			gmx240.gps_corrected_speed,
			gmx240.gps_average_corrected_speed,
			gmx240.gps_corrected_gust_speed,
			&gmx240.gps_corrected_gust_direction,
			gmx240.gps_location,
			&gmx240.gps_heading,
			gmx240.gps_speed,
			gmx240.gps_status);
			
			return 1;
		}
	}
	else if(dataFrameFound && stationModel == WS_GMX550)
	{
		if(!gps){
			//Frame is like: 
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 00000.200 000.200 N 042
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[22])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			gmx240.precipitation_total,
			gmx240.precipitation_intensity,
			&gmx240.precipitation_status,
			&gmx240.compass,
			gmx240.wind_chill,
			gmx240.heat_index,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status);
			
			return 1;
		}
		else{
			//Frame is like: 
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 00000.200 000.200 N 042
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %s %s %c %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[29])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			gmx240.precipitation_total,
			gmx240.precipitation_intensity,
			&gmx240.precipitation_status,
			&gmx240.compass,
			gmx240.wind_chill,
			gmx240.heat_index,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status,
			gmx240.gps_corrected_speed,
			gmx240.gps_average_corrected_speed,
			gmx240.gps_corrected_gust_speed,
			&gmx240.gps_corrected_gust_direction,
			gmx240.gps_location,
			&gmx240.gps_heading,
			gmx240.gps_speed,
			gmx240.gps_status);
			
			return 1;
		}
	}
	else if(dataFrameFound && stationModel == WS_GMX600)
	{
		if(!gps){
			//Frame is like: 
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 042
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[23])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			&gmx240.compass,
			gmx240.wind_chill,
			gmx240.heat_index,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status);
			
			return 1;
		}
		else{
			//Frame is like: 
			//"Q 269 000.03 311 000 000.00 000 000.00 000 0100 1032.5 1032.5 1032.5 028 +023.0 +003.8 05.90 042
			// +028 +028 1.2 +012.8 07:54 12:10 16:25 174:+18 17:03 17:45 18:24 +12 -14 +1 2017-01-20T11:46:01.3 +05.0 0000"
			// 000.56 000.00 000.00 000 +50.763328:-001.540155:-0002.70 242 000.58 010C"
			
			//"%c %d %s %d %d %s %d %s %d %s %s %s %s %d %s %s %s %d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %d %s %d %s %s"
			strcpy_P((char*)buffer_table, (char*)pgm_read_word(&(table_agrxtr[30])));
			sscanf (buffer_ws_raw, buffer_table,
			&gmx240.node_letter,
			&gmx240.wind_direction,
			gmx240.wind_speed,
			&gmx240.corrected_wind_direction,
			&gmx240.average_wind_direction,
			gmx240.average_wind_speed,
			&gmx240.average_wind_gust_direction,
			gmx240.average_wind_gust_speed,
			&gmx240.average_corrected_wind_direction,
			gmx240.wind_sensor_status,
			gmx240.pressure,
			gmx240.pressure_sea_level,
			gmx240.pressure_station,
			&gmx240.relative_humidity,
			gmx240.temperature,
			gmx240.dewpoint,
			gmx240.absolute_humidity,
			&gmx240.compass,
			gmx240.wind_chill,
			gmx240.heat_index,
			gmx240.air_density,
			gmx240.wet_build_temperature,
			gmx240.sunrise_time,
			gmx240.solar_noon_time,
			gmx240.sunset_time,
			gmx240.position_of_sun,
			gmx240.twilight_civil,
			gmx240.twilight_nautical,
			gmx240.twilight_astronomical,
			gmx240.x_tilt,
			gmx240.y_tilt,
			gmx240.z_orient,
			gmx240.timestamp,
			gmx240.supply_voltage,
			gmx240.status,
			gmx240.gps_corrected_speed,
			gmx240.gps_average_corrected_speed,
			gmx240.gps_corrected_gust_speed,
			&gmx240.gps_corrected_gust_direction,
			gmx240.gps_location,
			&gmx240.gps_heading,
			gmx240.gps_speed,
			gmx240.gps_status);
			
			return 1;			
		}
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
 * \brief BME Class constructor
 * \param socket selected socket for sensor
 */
bme::bme(uint8_t socket)
{
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}


/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t bme::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_B) 
	|| (_socket == AGR_XTR_SOCKET_C)
	|| (_socket == AGR_XTR_SOCKET_E)
	|| (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("BME280"));

		return 0;
	}

	super::ON(REG_3V3);
	set3v3(_socket, _3V3_ON);

	// switch ON I2C isolator Enable, detect if other sensor is already enabled
	if(_socket == AGR_XTR_SOCKET_A && AgricultureXtr.bmeIsolatorEnabledSocketD == 0)
	{
		digitalWrite(I2C_SOCKETA_EN, HIGH);
		AgricultureXtr.bmeIsolatorEnabledSocketA = 1;
	}
	else if(_socket == AGR_XTR_SOCKET_A && AgricultureXtr.bmeIsolatorEnabledSocketD == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[11]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("BME280"));
		return 0;
	}
	else if(_socket == AGR_XTR_SOCKET_D && AgricultureXtr.bmeIsolatorEnabledSocketA == 0)
	{
		digitalWrite(I2C_SOCKETD_EN, HIGH);
		AgricultureXtr.bmeIsolatorEnabledSocketD = 1;
	}
	else if(_socket == AGR_XTR_SOCKET_D && AgricultureXtr.bmeIsolatorEnabledSocketA == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[11]))); 
		PRINT_AGR_XTR(message);
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
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void bme::OFF()
{
	// switch OFF I2C isolator Enable
	if(_socket == AGR_XTR_SOCKET_A)
	{
		digitalWrite(I2C_SOCKETA_EN, LOW);
		AgricultureXtr.bmeIsolatorEnabledSocketA = 0;
	}
	if(_socket == AGR_XTR_SOCKET_D)
	{
		digitalWrite(I2C_SOCKETD_EN, LOW);
		AgricultureXtr.bmeIsolatorEnabledSocketD = 0;
	}

	set3v3(_socket, _3V3_OFF);
	super::OFF();

	// switch off delay for better preformance before
	// entering sleep mode after calling this function
	delay(100);
}


/*!
 * \brief Read BME temperature value
 * \param void
 * \return temperature value
 */
float bme::getTemperature()
{
	float value = 0;

	value = BME.getTemperature(BME280_OVERSAMP_1X, 0);

	#if DEBUG_AGR_XTR>0
		PRINT_AGR_XTR(F("Temperature:"));
		USB.println(value);
		PRINT_AGR_XTR(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);
	#endif

	return value;
}

/*!
 * \brief Read BME humidity value
 * \param void
 * \return humidity value
 */
float bme::getHumidity()
{
	float value = 0;

	// read the humidity from the BME280 Sensor
	value = BME.getHumidity(BME280_OVERSAMP_1X);
	#if DEBUG_AGR_XTR>0
		PRINT_AGR_XTR(F("Humidity:"));
		USB.println(value);
		PRINT_AGR_XTR(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);
	#endif

	return value;
}

/*!
 * \brief Read BME pressure value
 * \param void
 * \return pressure value
 */
float bme::getPressure()
{
	float value = 0;

	// read the pressure from the BME280 Sensor
	value = BME.getPressure(BME280_OVERSAMP_1X, 0);
	#if DEBUG_AGR_XTR>0
		PRINT_AGR_XTR(F("Pressure:"));
		USB.println(value);
		PRINT_AGR_XTR(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);
	#endif

	return value;
}



//******************************************************************************
// Ultrasound Sensor Class functions
//******************************************************************************


/*!
 * \brief Ultrasound Class constructor
 * \param socket selected socket for sensor
 */
ultrasound::ultrasound(uint8_t socket)
{
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}



/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t ultrasound::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_B) 
	|| (_socket == AGR_XTR_SOCKET_C)
	|| (_socket == AGR_XTR_SOCKET_E)
	|| (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("Ultrasound"));

		return 0;
	}

	super::ON(REG_3V3);
	set3v3(_socket, _3V3_ON);

	// switch ON I2C isolator Enable, detect if other sensor is already enabled
	if(_socket == AGR_XTR_SOCKET_A && AgricultureXtr.ultrasoundIsolatorEnabledSocketD == 0)
	{
		digitalWrite(I2C_SOCKETA_EN, HIGH);
		AgricultureXtr.ultrasoundIsolatorEnabledSocketA = 1;
	}
	else if(_socket == AGR_XTR_SOCKET_A && AgricultureXtr.ultrasoundIsolatorEnabledSocketD == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[11]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("ultrasound"));
		return 0;
	}
	else if(_socket == AGR_XTR_SOCKET_D && AgricultureXtr.ultrasoundIsolatorEnabledSocketA == 0)
	{
		digitalWrite(I2C_SOCKETD_EN, HIGH);
		AgricultureXtr.ultrasoundIsolatorEnabledSocketD = 1;
	}
	else if(_socket == AGR_XTR_SOCKET_D && AgricultureXtr.ultrasoundIsolatorEnabledSocketA == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[11]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("ultrasound"));
		return 0;
	}

	
	//neccessary delay after powering the sensor
	delay(200);
	
	return 1;
}



/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void ultrasound::OFF()
{
	// switch OFF I2C isolator Enable
	if(_socket == AGR_XTR_SOCKET_A)
	{
		digitalWrite(I2C_SOCKETA_EN, LOW);
		AgricultureXtr.ultrasoundIsolatorEnabledSocketA = 0;
	}
	if(_socket == AGR_XTR_SOCKET_D)
	{
		digitalWrite(I2C_SOCKETD_EN, LOW);
		AgricultureXtr.ultrasoundIsolatorEnabledSocketD = 0;
	}

	set3v3(_socket, _3V3_OFF);
	super::OFF();

	// switch off delay for better preformance before
	// entering sleep mode after calling this function
	delay(100);
}


/*!
 * \brief Performs a distance measurement
 * \param void
 * \return distance in cm.
 *		9000 if error reading the distance
 *		10000 if error reading the sensor
 */
uint16_t ultrasound::getDistance()
{
	return Ultrasound.getDistance();
}




//******************************************************************************
// Luxes Sensor Class functions
//******************************************************************************

/*!
 * \brief Luxes Class constructor
 * \param socket selected socket for sensor
 */
luxes::luxes(uint8_t socket)
{
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}


/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t luxes::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_B) 
	|| (_socket == AGR_XTR_SOCKET_C)
	|| (_socket == AGR_XTR_SOCKET_E)
	|| (_socket == AGR_XTR_SOCKET_F))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("Luxes"));

		return 0;
	}


	super::ON(REG_3V3);
	set3v3(_socket, _3V3_ON);

	// switch ON I2C isolator Enable, detect if other sensor is already enabled
	if(_socket == AGR_XTR_SOCKET_A && AgricultureXtr.luxesIsolatorEnabledSocketD == 0)
	{
		digitalWrite(I2C_SOCKETA_EN, HIGH);
		AgricultureXtr.luxesIsolatorEnabledSocketA = 1;
	}
	else if(_socket == AGR_XTR_SOCKET_A && AgricultureXtr.luxesIsolatorEnabledSocketD == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[11]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("luxes"));
		return 0;
	}
	else if(_socket == AGR_XTR_SOCKET_D && AgricultureXtr.luxesIsolatorEnabledSocketA == 0)
	{
		digitalWrite(I2C_SOCKETD_EN, HIGH);
		AgricultureXtr.luxesIsolatorEnabledSocketD = 1;
	}
	else if(_socket == AGR_XTR_SOCKET_D && AgricultureXtr.luxesIsolatorEnabledSocketA == 1)
	{
		char message[70];
		memset(message, 0x00, sizeof(message));
		//"WARNING - Not possible to turn ON two sensors at the same time:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[11]))); 
		PRINT_AGR_XTR(message);
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
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void luxes::OFF()
{
	// switch OFF I2C isolator Enable
	if(_socket == AGR_XTR_SOCKET_A)
	{
		digitalWrite(I2C_SOCKETA_EN, LOW);
		AgricultureXtr.luxesIsolatorEnabledSocketA = 0;
	}
	if(_socket == AGR_XTR_SOCKET_D)
	{
		digitalWrite(I2C_SOCKETD_EN, LOW);
		AgricultureXtr.luxesIsolatorEnabledSocketD = 0;
	}

	set3v3(_socket, _3V3_OFF);
	super::OFF();

	// switch off delay for better preformance before
	// entering sleep mode after calling this function
	delay(100);
}


/*!
 * \brief Performs a luminosity measurement
 * \param void
 * \return luxes if ok, -1 if error
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
	while(retries > 0);

	return (uint32_t)-1;
}


//******************************************************************************
// 4-20mA Sensor Class functions
//******************************************************************************

/*!
 * \brief 4-20mA Class constructor
 * \param socket selected socket for sensor
 */
_4_20mA::_4_20mA(uint8_t socket)
{
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}
}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t _4_20mA::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_A) 
	|| (_socket == AGR_XTR_SOCKET_C)
	|| (_socket == AGR_XTR_SOCKET_D)
	|| (_socket == AGR_XTR_SOCKET_E))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("4-20mA"));

		return 0;
	}

	super::ON(REG_3V3);
	set12v(_12V_ON);

	//neccessary delay after powering the sensor
	delay(10);
	
	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void _4_20mA::OFF()
{
	set12v(_12V_OFF);
	super::OFF();
}


/*!
 * \brief Reads the 4-20mA sensor
 * \param void
 * \return 0 if invalid data. Current value Otherwise.
 */
float _4_20mA::read()
{

	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();


	// necessary for the sensor
	delay(10);

	if (_socket == AGR_XTR_SOCKET_F)	
	{
		current = ltc.readADC(ADC_CH1);
	}
	else if (_socket == AGR_XTR_SOCKET_B)
	{
		current = ltc.readADC(ADC_CH0);
	}
	else
	{
		#if DEBUG_AGR_XTR == 1
		PRINT_AGR_XTR(F("wrong 4.20 socket "));
		USB.println(_socket, DEC);
		#endif
		return 0;
	}	

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	#if DEBUG_AGR_XTR == 1
	PRINT_AGR_XTR(F("4.20: "));
	USB.printFloat(current, 4);
	USB.println();
	#endif

	if ((current < 0) || (current > 5 ))
	{
		#if DEBUG_AGR_XTR == 1
		PRINTLN_AGR_XTR(F("Unknown 4.20 error"));
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
 * \brief SU100 Class constructor
 * \param socket selected socket for sensor
 */

Apogee_SU100::Apogee_SU100(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}

}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SU100::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_A) 
	|| (_socket == AGR_XTR_SOCKET_D))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("SU100"));

		return 0;
	}

	super::ON(REG_3V3);


	// necessary for POR of the ADC
	delay(10);

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Apogee_SU100::OFF()
{	
	super::OFF();
}



/*!
 * \brief reads the SU100 sensor and converts its value into umol·m-2·s-1
 * \param void
 * \return 0 if invalid data. Measure otherwise
 */

float Apogee_SU100::read(void)
{
	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();

	if(_socket == AGR_XTR_SOCKET_B)
	{
		radiationVoltage = ltc.readADC(ADC_CH3);
	}
	if(_socket == AGR_XTR_SOCKET_C)
	{
		radiationVoltage = ltc.readADC(ADC_CH5);
	}
	if(_socket == AGR_XTR_SOCKET_E)
	{
		radiationVoltage = ltc.readADC(ADC_CH4);
	}
	if(_socket == AGR_XTR_SOCKET_F)
	{
		radiationVoltage = ltc.readADC(ADC_CH2);
	}

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor in volts
	#if DEBUG_AGR_XTR == 2
	PRINT_AGR_XTR(F("radiation (V): "));
	USB.printFloat(radiationVoltage, 5);
	USB.println();
	#endif

	// Conversion from voltage into umol·m-2·s-1
	radiation = radiationVoltage / 0.0002;

	// check value of the sensor in mm
	#if DEBUG_AGR_XTR == 1
	PRINT_AGR_XTR(F("radiation (umol*m-2*s-1): "));
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
 * \brief SQ110 Class constructor
 * \param socket selected socket for sensor
 */
Apogee_SQ110::Apogee_SQ110(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}

}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SQ110::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_A) 
	|| (_socket == AGR_XTR_SOCKET_D))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("SQ110"));

		return 0;
	}

	super::ON(REG_3V3);


	// necessary for POR of the ADC
	delay(10);

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Apogee_SQ110::OFF()
{	
	super::OFF();
}



/*!
 * \brief reads the SU100 sensor and converts its value into umol·m-2·s-1
 * \param void
 * \return 0 if invalid data. Measure otherwise
 */
float Apogee_SQ110::read(void)
{
	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();

	if(_socket == AGR_XTR_SOCKET_B)
	{
		radiationVoltage = ltc.readADC(ADC_CH3);
	}
	if(_socket == AGR_XTR_SOCKET_C)
	{
		radiationVoltage = ltc.readADC(ADC_CH5);
	}
	if(_socket == AGR_XTR_SOCKET_E)
	{
		radiationVoltage = ltc.readADC(ADC_CH4);
	}
	if(_socket == AGR_XTR_SOCKET_F)
	{
		radiationVoltage = ltc.readADC(ADC_CH2);
	}

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor in volts
	#if DEBUG_AGR_XTR == 2
	PRINT_AGR_XTR(F("radiation (V): "));
	USB.printFloat(radiationVoltage, 5);
	USB.println();
	#endif

	// Conversion from voltage into umol·m-2·s-1
	radiation = radiationVoltage / 0.0002;

	// check value of the sensor in mm
	#if DEBUG_AGR_XTR == 1
	PRINT_AGR_XTR(F("radiation (umol*m-2*s-1): "));
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
 * \brief SP510 Class constructor
 * \param socket selected socket for sensor
 */
Apogee_SP510::Apogee_SP510(uint8_t socket)
{
	// store sensor location
	_socket = socket;

	if(bitRead(AgricultureXtr.socketRegister, _socket) == 1)
	{
		//Redefinition of socket by two sensors detected
		AgricultureXtr.redefinedSocket = 1;
	}
	else
	{
		bitSet(AgricultureXtr.socketRegister, _socket); 
	}

}

/*!
 * \brief Turns on the sensor
 * \param void
 * \return 1 if ok, 0 if something fails
 */
uint8_t Apogee_SP510::ON()
{
	char message[70];

	if(AgricultureXtr.redefinedSocket == 1)
	{
		//"WARNING: Redefinition of sensor socket detected"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[6]))); 
		PRINTLN_AGR_XTR(message);
	}

	if((_socket == AGR_XTR_SOCKET_A) 
	|| (_socket == AGR_XTR_SOCKET_D))
	{
		//"WARNING - The following sensor can not work in the defined socket:"
		strcpy_P(message, (char*)pgm_read_word(&(table_agrxtr[7]))); 
		PRINT_AGR_XTR(message);
		USB.println(F("SP510"));

		return 0;
	}

	super::ON(REG_3V3);
	
	//Turn on the heater
	set12v(_12V_ON);
	
	// necessary for POR of the ADC
	delay(10);

	return 1;
}

/*!
 * \brief Turns off the sensor
 * \param void
 * \return void
 */
void Apogee_SP510::OFF()
{	
	//Turn off the heater
	set12v(_12V_OFF);
	
	super::OFF();
}


/*!
 * \brief reads the SU100 sensor and converts its value into umol·m-2·s-1
 * \param void
 * \return 0 if invalid data. Measure otherwise.
 */
float Apogee_SP510::read(void)
{
	//Enable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, HIGH);

	// ADC setup
	ltc.begin();

	if(_socket == AGR_XTR_SOCKET_B)
	{
		radiationVoltage = ltc.readADC(ADC_CH3);
	}
	if(_socket == AGR_XTR_SOCKET_C)
	{
		radiationVoltage = ltc.readADC(ADC_CH5);
	}
	if(_socket == AGR_XTR_SOCKET_E)
	{
		radiationVoltage = ltc.readADC(ADC_CH4);
	}
	if(_socket == AGR_XTR_SOCKET_F)
	{
		radiationVoltage = ltc.readADC(ADC_CH2);
	}

	//Disable SPI isolator for using the ADC
	digitalWrite(SPI_ISO_EN, LOW);

	// check value of the sensor in volts
	#if DEBUG_AGR_XTR == 2
	PRINT_AGR_XTR(F("radiation (V): "));
	USB.printFloat(radiationVoltage, 5);
	USB.println();
	#endif

	// Conversion from voltage into W*m-2
	radiation = radiationVoltage * 17.543;

	// check value of the sensor in mm
	#if DEBUG_AGR_XTR == 1
	PRINT_AGR_XTR(F("radiation (W*m-2): "));
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
 * \brief Turns on and off the heater of the sensor
 * \param _12V_ON or _12V_OFF
 * \return void
 */
void Apogee_SP510::heater(uint8_t state)
{	
	super::ON(REG_3V3);
	set12v(state);
}





// Preinstantiate Objects //////////////////////////////////////////////////////

WaspSensorAgrXtr	AgricultureXtr = WaspSensorAgrXtr();

////////////////////////////////////////////////////////////////////////////////
