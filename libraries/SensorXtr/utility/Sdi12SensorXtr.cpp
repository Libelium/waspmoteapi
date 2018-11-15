/*!	\file Sdi12SensorXtr.cpp
	\brief Library for managing SDI-12 in Xtreme boards

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
	Implementation: Victor Boria

*/


#include "Sdi12SensorXtr.h"


#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif


const char string_00[] PROGMEM = "I!";	// SDI-12 info
const char string_01[] PROGMEM = "M!";	// SDI-12 measurement
const char string_02[] PROGMEM = "D0!";	// SDI-12 data
const char string_03[] PROGMEM = "Ab!";	// SDI-12 change address
const char string_04[] PROGMEM = "?!";	// SDI-12 address query
const char string_05[] PROGMEM = "?I!";	// SDI-12 info


const char* const table_sdi12[] PROGMEM =
{
	string_00,
	string_01,
	string_02,
	string_03,
	string_04,
	string_05
};


//! class constructor
Sdi12SensorXtr::Sdi12SensorXtr()
{
	
}


//******************************************************************************
// SDI-12 functions
//******************************************************************************


/*!
 * \brief detects if SDI12 sensor is present
 * \param sensorName SDI-12 senor name
 * \return return 0 if not, 1 if present.
 */
uint8_t Sdi12SensorXtr::isSensor(uint8_t sensorName, char *sensorSerialNumber)
{
	char sensorModel[7];
	char sensorVersion[4];
	char command[6];
	
	// clear variables
	memset(sensorModel, 0x00, sizeof(sensorModel));
	memset(sensorVersion, 0x00, sizeof(sensorVersion));
	
	// check if sensor is present. Copy command from flash memory and send it.
	strcpy_P(command, (char*)pgm_read_word(&(table_sdi12[5])));
	sdi12.sendCommand(command, strlen(command));
	
	sdi12.readCommandAnswer(33, LISTEN_TIME);
	
	//necessary delay
	delay(30);
	
	/* readMeasures answer
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
			sensorVersion[i] = sdi12.read();
			//sdi12.read();
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
				sensorSerialNumber[i] = byte_buffer;
			}
			// add end of string
			sensorSerialNumber[i+1] = 0x00;
		}
	}
	
	char sensorNameStr[7]; 
	memset(sensorNameStr, 0x00, sizeof(sensorNameStr));
	
	char sensorNameAuxStr[7]; 
	memset(sensorNameAuxStr, 0x00, sizeof(sensorNameAuxStr));
	strncpy(sensorNameAuxStr, "AUX", 3);
	
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
			strncpy(sensorNameStr, "VP-4", 4);
			break;
			
		case MPS6:
			strncpy(sensorNameStr, "MPS-6", 5);
			memset(sensorNameAuxStr, 0x00, sizeof(sensorNameAuxStr));
			strncpy(sensorNameAuxStr, "TER21", 5); //Sensor name change in nov 2018
			break;
			
		case SO411:
			strncpy(sensorNameStr, "SO-411", 6);
			break;
			
		case SI411:
			strncpy(sensorNameStr, "SI-411", 6);
			break;
			
		case SF421:
			strncpy(sensorNameStr, "SF-421", 6);
			break;

		case C4E:
			strncpy(sensorNameStr, "C4E", 3);
			break;
		
		case CTZN:
			strncpy(sensorNameStr, "CTZ-T", 5);
			break;
		
		case MES5:
			strncpy(sensorNameStr, "Turb", 4);
			break;
		
		case OPTOD:
			strncpy(sensorNameStr, "ODO", 3);
			break;
		
		case PHEHT:
			strncpy(sensorNameStr, "pH/EH", 5);
			break;
		
		case NTU:
			strncpy(sensorNameStr, "Nep/T", 5);
			break;
		
		default:
			break;
	}
    
    #if DEBUG_XTR_SDI > 0
    PRINT_XTR_SDI(F("sensorModel:"));
    USB.println(sensorModel);
    PRINT_XTR_SDI(F("sensorVersion:"));
    USB.println(sensorVersion);
    PRINT_XTR_SDI(F("sensorNameStr:"));
    USB.println(sensorNameStr);
    PRINT_XTR_SDI(F("sensorNameAuxStr:"));
    USB.println(sensorNameAuxStr);
    #endif

	//Compare if the Model field returned by the sensor is equal to sensorName
	if(strncmp(sensorModel, sensorNameStr,strlen(sensorNameStr)) == 0)
	{
		return 1;
	}
	else
	{
		//Compare if the Model field returned by the sensor is equal to sensorNameAuxStr
		if(strncmp(sensorModel, sensorNameAuxStr,strlen(sensorNameAuxStr)) == 0)
		{
			return 1;
		}
		else
		{
			if (sensorModel[0] == 0x00)
			{
				#if DEBUG_XTR_SDI > 0
					char message[20];
					//"sensor not detected"
					strcpy_P(message, (char*)pgm_read_word(&(table_sdi12[8]))); 
					PRINTLN_XTR_SDI(message);
				#endif
			}
			else 
			{
				#if DEBUG_XTR_SDI > 0
					PRINT_XTR_SDI(F("other sensor: "));
					USB.println(sensorModel);
				#endif
			}

			return 0;
		}
	}
}

/*!
 * \brief send measurement command to the SDI-12 sensor to start measuring
 * \param void
 * \return return 0 if invalid answer. 1 if ok.
 */
uint8_t Sdi12SensorXtr::startSensor()
{
	char aux[3];
	char command[6];
	char numberOfMeasures = 0;
	char timeToNextMeasure_string[4];
	
	memset(timeToNextMeasure_string, 0x00, sizeof(timeToNextMeasure_string));
	
	// build command with address
	strcpy_P(aux, (char*)pgm_read_word(&(table_sdi12[1])));

	sprintf(command, "%c%s", address, aux);
	sdi12.sendCommand(command, strlen(command));
	sdi12.readCommandAnswer(5, LISTEN_TIME);
	
	//necessary delay
	delay(30);
	
	// readMeasures answer
	if (sdi12.available() >= 5)
	{
		// skip sensor address
		sdi12.read();

		// Measurement data will be available after specified time
		timeToNextMeasure_string[0] = sdi12.read();
		timeToNextMeasure_string[1] = sdi12.read();
		timeToNextMeasure_string[2] = sdi12.read();
		
		timeToNextMeasure = atoi(timeToNextMeasure_string);
		// Number of values returned
		numberOfMeasures = sdi12.read();
	}
	else
	{
		//invalid data
		#if DEBUG_XTR_SDI > 0
			char message[20];
			//"invalid data"
			strcpy_P(message, (char*)pgm_read_word(&(table_sdi12[9]))); 
			PRINT_XTR_SDI(message);
		#endif
		return 0;
	}

	#if DEBUG_XTR_SDI > 1
		PRINT_XTR_SDI(F("timeToNextMeasure:"));
		USB.println(timeToNextMeasure, DEC);
		PRINT_XTR_SDI(F("numberOfMeasures:"));
		USB.println(numberOfMeasures);
	#endif

	return 1;
}




 /*!
 * \brief Reads and readMeasuress the data of the SDI-12 sensor 
 * \param sensorType selected SDI-12 sensor type
 * \return 0 if sensor not present or invalid data. 1 Otherwise.
 */
uint8_t Sdi12SensorXtr::readMeasures(uint8_t sensorType, char *sensorSerialNumber, float &parameter1, float &parameter2, float &parameter3, float &parameter4)
{
	char command[6];
	
	// READING
	char measures[50];
	char aux[4];
	uint8_t i = 0;
	
	uint8_t numberFields = 4;
	
	if(parameter4 == -1000)
	{
		numberFields = 3;
		
		if(parameter3 == -1000)
		{
			numberFields = 2;
			
			if(parameter2 == -1000)
			{
				numberFields = 1;
			}
		}
	}
	
	memset(aux, 0x00, sizeof(aux));

	//check if correct SDI-12 sensor connected   
	if (isSensor(sensorType, sensorSerialNumber) == 0)
	{
		memset(sensorSerialNumber, 0x00, sizeof(sensorSerialNumber));
		sdi12.setState(DISABLED);
		return 0;
	}

	if (startSensor() == 0)
	{
		sdi12.setState(DISABLED);
		return 0;
	}

	// now wait timeToNextMeasure till data is ready + aditional delay
	delay(timeToNextMeasure*1000);
	
	// send data command aD0!. Build command with address
	strcpy_P(aux, (char*)pgm_read_word(&(table_sdi12[2])));
	snprintf(command, sizeof(command), "%c%s", address, aux);
	
	sdi12.sendCommand(command, strlen(command));
	sdi12.readCommandAnswer(30, LISTEN_TIME);
	
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
	
	
	// PARSING
	i = 0;
	uint8_t counter = 0;
	
	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	
	uint8_t len = strlen(measures);

	char stringParameter1[20];
	char stringParameter2[20];
	char stringParameter3[20];
	char stringParameter4[20];
	
	//Empty the arrays
	memset(stringParameter1, 0x00, sizeof(stringParameter1));
	memset(stringParameter2, 0x00, sizeof(stringParameter2));
	memset(stringParameter3, 0x00, sizeof(stringParameter3));
	memset(stringParameter4, 0x00, sizeof(stringParameter4));

	//if invalid data, return 0.
	if (len == 0)
	{
		return 0;
	}

	while((counter <= numberFields) && (i <= len))
	{
		if ((measures[i] == '+') || (measures[i] == '-'))
		{
			counter++;
		}
		switch (counter)
		{
			case 1:
				stringParameter1[a] = measures[i];
				a++;
				break;

			case 2:
				stringParameter2[b] = measures[i];
				b++;
				break;

			case 3:
				stringParameter3[c] = measures[i];
				c++;
				break;
			
			case 4:
				stringParameter4[d] = measures[i];
				d++;
				break;
				
			default: 
				break;
		}
		i++;
	}

	//add eof to strings
	stringParameter1[a] = '\0';
	stringParameter2[b] = '\0';
	stringParameter3[c] = '\0';
	stringParameter4[d] = '\0';
	
	// Convert strings to float values
	parameter1 = atof(stringParameter1);
	parameter2 = atof(stringParameter2);
	parameter3 = atof(stringParameter3);
	parameter4 = atof(stringParameter4);


	#if DEBUG_XTR_SDI > 0
		PRINT_XTR_SDI(F("measures:"));
		USB.println(measures);
		PRINT_XTR_SDI(F("Parameter 1:"));
		USB.println(parameter1);
		PRINT_XTR_SDI(F("Parameter 2:"));
		USB.println(parameter2);
		PRINT_XTR_SDI(F("Parameter 3:"));
		USB.println(parameter3);
		PRINT_XTR_SDI(F("Parameter 4:"));
		USB.println(parameter4);
	#endif

	// If every value have been readMeasuresd, return 1.
	if (counter != numberFields)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

// Preinstantiate Objects //////////////////////////////////////////////////////

Sdi12SensorXtr	sdi12SensorXtr = Sdi12SensorXtr();

