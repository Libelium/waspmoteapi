/*
 *  Library for managing the Particle sensor PM from Alphasense
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
 *  Version:		1.0
 *  Design:			David Gascón
 *  Implementation:	Isabel Burillo
 */


/******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspPM.h"


/******************************************************************************
 * Constructors
 ******************************************************************************/

WaspPM::WaspPM()
{
	// update Waspmote Control Register
	WaspRegisterSensor |= REG_DUST_GASES_PRO;

	pinMode(DUST_SENSOR_CS,OUTPUT);
	digitalWrite(DUST_SENSOR_CS,HIGH);
	pinMode(DUST_SENSOR_POWER,OUTPUT);
	digitalWrite(DUST_SENSOR_POWER,LOW);


	for (int i = 0; i < 15; i++)
	{
		_binParticleVolume[i] = 0.0;
		_binParticleDensity[i] = 0.0;;
		_binSampleVolumeWeight[i] = 0.0;
		_bin[i] = 0;
	}
	for (int i = 0; i < 14; i++)
	{
		_binBoundaryValues[i] = 0;
	}

	_gain = 0;
	_sample = 0;
	_laserDAC = 0;
	_fanDAC = 0;

	_temp = 0.0;
	_hum = 0.0;
	_periodCount = 0;
	_PM1 = 0.0;
	_PM2_5 = 0.0;
	_PM10 = 0.0;
  _tempN2 = 0.0;
  _pressureN2 = 0.0;

	pwrGasPRORegister = 0;

  // assign class pointer to UART buffer
  _buffer = class_buffer;
  _bufferSize = SENSOR_DUST_UART_SIZE;
}


/******************************************************************************
 * PRIVATE FUNCTIONS                                                          *
 ******************************************************************************/

/* Function: 	This function checks if the PM sensor is ready
 *
 * Returns 0 if not ready, 1 if  ready
*/
uint8_t WaspPM::checkStatus()
{
	uint8_t error = 0;
	uint8_t val = 0;
	uint16_t times = 0;

	#if PM_DEBUG>0
		PRINT_PM(F("PM: Check status...\n"));
	#endif

	if(_mode == PM_SPI_MODE)
	{
		SPI.setSPISlave(ALL_DESELECTED);
		SPI.setSPISlave(DUST_SENSOR_SELECT);
		delayMicroseconds(2);
		while((val != CHECK_STATUS_READY)&&(times<100))
		{
			val = SPI.transfer(CHECK_STATUS);
			times++;
			delay(50);
		}
		if (times<99)
		{

			error = 1;
			#if PM_DEBUG>0
				PRINT_PM(F("ready\n"));
			#endif
		}
		else
		{
			error = 0;
			#if PM_DEBUG>0
				PRINT_PM(F("not ready\n"));
			#endif

		}

		SPI.setSPISlave(ALL_DESELECTED);
	}
	else
	{
		times = 5;
		do{
			error = sendCommand("AT\r", "OK",3000);
			times--;
		}while((times > 0) && (error != 1));

		if (error == 1)
		{
			#if PM_DEBUG>0
				PRINT_PM(F("ready\n"));
			#endif
		}
		else
		{
			#if PM_DEBUG>0
				PRINT_PM(F("not ready\n"));
			#endif

		}
	}

	return error;
}


/* Function: 	This function inits the SPI bus to use with PM module
 *
 * Returns nothing
*/
void WaspPM::configSPI()
{
	// Starting SPI port
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setClockDivider(SPI_CLOCK_DIV32);
	SPI.setDataMode(SPI_MODE1);
	SPI.setSPISlave(ALL_DESELECTED);


}

/******************************************************************************
 * PUBLIC FUNCTIONS
 ******************************************************************************/

uint8_t WaspPM::ON()
{
	return ON(PM_UART_MODE);
}
/* Function: 	This function opens SPI port and powers the sensor
 *
 * Returns 		0 if the sensor doesn't init correctly
 * 				1 if init OK
*/
uint8_t WaspPM::ON(bool com_mode)
{

	uint8_t error = 0;

	_mode = com_mode;
	#if PM_DEBUG>0
		if(_mode == PM_SPI_MODE)
		{
			PRINT_PM(F("PM.SPI Mode\n"));
		}
		else
		{
			PRINT_PM(F("PM.UART Mode\n"));
		}
	#endif

	if (_mode == PM_SPI_MODE)
	{

		pinMode(DUST_SENSOR_CS,OUTPUT);
		digitalWrite(DUST_SENSOR_CS,HIGH);
		delay(1000);


		pinMode(DUST_SENSOR_POWER,OUTPUT);
		digitalWrite(DUST_SENSOR_POWER,LOW);
		delay(1000);

		digitalWrite(DUST_SENSOR_POWER,HIGH);
		delay(1000);

		// update SPI flag
		SPI.isDustSensor = true;

		configSPI();

		delay(1000);
		if ((WaspRegister & REG_3V3) == 0)
		{
			#if PM_DEBUG>0
				PRINT_PM(F("PM.3V3 to ON\n"));
			#endif
			PWR.setSensorPower(SENS_3V3, SENS_ON);
		}
		delay(2000);
	}
	else
	{
		pinMode(DUST_SENSOR_POWER,OUTPUT);

		digitalWrite(DUST_SENSOR_POWER,HIGH);
// 		delay(15000);
		delay(5000);
		_baudrate = 9600;
		_uart = 1;
		beginUART();
		Utils.setMuxAux2();
	}

	error = checkStatus();

	if (error == 0)
	{
		OFF();
		pwrGasPRORegister &= 0xFE;
		isON = 0;
	}
	else
	{
		pwrGasPRORegister |= 0x01;
		isON = 1;
	}
	delay(2000);

	return error;

}

/* Function: 	This function closes SPI port and powers OFF the sensor
 *
 * Returns 		0 if the sensor doesn't power off correctly
 * 				1 if powers off correctly
*/
uint8_t WaspPM::OFF()
{

	uint8_t error = 0;

	if (_mode == PM_SPI_MODE)
	{
		#if PM_DEBUG>0
			PRINT_PM(F("PM.Turning off sensor,\n"));
		#endif
		// Stopping SPI port
		SPI.isDustSensor = false;
		SPI.setSPISlave(ALL_DESELECTED);
		pinMode(DUST_SENSOR_CS,INPUT);
		SPI.close();

		digitalWrite(DUST_SENSOR_POWER,LOW);

		if (( pwrGasPRORegister == 0x01) || ( pwrGasPRORegister == 0x0))
		{
			#if PM_DEBUG>0
				PRINT_PM(F("3V3 off\n"));
			#endif
			PWR.setSensorPower(SENS_3V3, SENS_OFF);
		}
		#if PM_DEBUG>0
		else
		{
			PRINT_PM(F("3V3 NOT off\n"));
		}
		#endif


		if((digitalRead(DUST_SENSOR_CS) == HIGH) && (digitalRead(DUST_SENSOR_POWER) == LOW))
		{
			error = 1;
			pwrGasPRORegister &= 0xFE;
		}
		isON = 0;
	}
	else
	{
		#if PM_DEBUG>0
			PRINT_PM(F("PM.Turning off sensor\n"));
		#endif

		closeSerial(1);

		digitalWrite(DUST_SENSOR_POWER,LOW);

		error = 1;
		pwrGasPRORegister &= 0xFE;
		isON = 0;
	}


	return error;
}

/* Function: 	This function reads the information string from PM sensor
 * 				module.
 * Parameters:	buffer: string pointer to store the information data
 * Returns: 	1 if OK
 *				-1 if error sending the command
*/
int8_t WaspPM::getInfoString(char* buffer)
{

	uint8_t error = 0;
	uint8_t val = 0;
	uint16_t times = 0;


	#if PM_DEBUG>0
		PRINT_PM(F("PM.Reading information string\n"));
	#endif

	if (_mode == PM_SPI_MODE)
	{

		SPI.setSPISlave(DUST_SENSOR_SELECT);
		delayMicroseconds(100);
		while((val != CHECK_STATUS_READY) && (times<100))
		{
			val = SPI.transfer(READ_INFO_STRING);
			times++;
			delay(1);
		}

		if (times >= 100)
		{
			return -1;
		}

		// At least 1.7 ms between command byte and following byte
		delay(10);

		for(int i = 0; i < 58; i++)
		{
      delayMicroseconds(10);
			buffer[i] = SPI.transfer(READ_INFO_STRING);

		}

		buffer[58] = '\0';

		error = 1;

		#if PM_DEBUG>0
      PRINT_PM(F(""));
			for(int i = 0; i < 58; i++)
			{
				USB.print(buffer[i],HEX);
				USB.print(" ");
			}
			USB.println("");
		#endif

		// Release the bus
		SPI.setSPISlave(ALL_DESELECTED);
	}
	else
	{
		char command[10];
		uint32_t waitTime;

		#if PM_DEBUG>0
			PRINT_PM(F("PM.Getting PM with fan on\n"));
		#endif

		memset(command, '\0', sizeof(command));
		snprintf(	command, sizeof(command), "AT$101\r");

		beginSerial(9600, 1);
		Utils.setMuxAux2();
		delay(100);

		error = sendCommand(command, "$101", "ERROR", 2000);
		if( error != 1)
		{
			return -11;
		}

		error = waitFor("OK", 2000);
		if( error != 1)
		{
			return -12;
		}
		#if PM_DEBUG>0
			PRINT_PM(F("PM.String received: "));
			USB.println((char*) _buffer);
		#endif

		memset(buffer, '\0', 60);
		strncpy(buffer, (char*)_buffer+1, 60);

	}

	return error;
}

/* Function: 	This function switchs the fan and the laser ON or OFF
 * Parameters:	mode: DIGITAL_POT_ON or DIGITAL_POT_OFF
 * Returns 		1 if ok
 *				-1 if error sending the command
 * 				-2 if error receiving data
*/
int8_t WaspPM::setDigitalPot(uint8_t mode)
{
	int8_t error = 0;
	uint8_t val = 0;
	uint16_t times = 0;

	#if PM_DEBUG>0
		PRINT_PM(F("PM.Setting digital pot\n"));
	#endif

	if(_mode == PM_UART_MODE)
	{
		#if PM_DEBUG>0
			PRINT_PM(F("... not supported in UART_MODE\n"));
		#endif
		return  -3;
	}

	uint8_t command[2];
	uint8_t command_answer[2];

	command[0] = SET_DIGITAL_POT;
	command[1] = mode;

	delay(100);
	SPI.setSPISlave(DUST_SENSOR_SELECT);
	delayMicroseconds(100);

	command_answer[0] = 0;
	command_answer[1] = 0;

	while(	(command_answer[0] != CHECK_STATUS_READY) && (times<20))
	{
    delay(10);
		command_answer[0] = SPI.transfer(command[0]);
		times++;
	}
	if (times >= 20 )
	{
		#if PM_DEBUG>0
			PRINT_PM(F("...failed. Communication error.\n"));
		#endif
		error = -1;
	}
	else
	{
    command_answer[1] = SPI.transfer(command[1]);
		#if PM_DEBUG>0
			PRINT_PM(F("...done.\n"));
		#endif
		error = 1;
	}

	return error;
}

/* Function: 	This function reads the histogram from PM sensor module.
 * 	It will reset the histogram too. Next variables will be updated:
 * 				_bin[24]
 * 				_binL[16]
 * 				_binH[8]
 * 				_temp
 * 				_temp_float
 * 				_hum
 * 				_periodCount
 * 				_bin1_MToF
 * 				_bin3_MToF
 * 				_bin5_MToF
 * 				_bin7_MToF
 * 				_PM1
 * 				_PM2_5
 * 				_PM10
 * Returns: 	1 if OK
 *				-1 if error sending the command
 * 				-2 if error receiving data (CRC)
*/
int8_t WaspPM::getHistogramData()
{
	uint8_t error = 1;
	uint8_t val = 0;
	uint16_t times = 0;
	//uint16_t crc = 0;
	uint16_t crc_bin = 0;

	uint16_t aux_val;
	byte histogramString[86];

	#if PM_DEBUG>0
		PRINT_PM(F("PM.Getting histogram data\n"));
	#endif

	if (_mode == PM_SPI_MODE)
	{

		error = 1;
		delay(100);

		SPI.setSPISlave(DUST_SENSOR_SELECT);
    //delayMicroseconds(100);
		// Read histogram data
		while((val != CHECK_STATUS_READY) && (times < 40))
		{
      if (times == 20)
      {
        delay(3000);
        // delay(1000);
        // SPI.setSPISlave(ALL_DESELECTED);
        // delay(1000);
        // SPI.setSPISlave(DUST_SENSOR_SELECT);

      }
      delay(1);
			val = SPI.transfer(READ_HISTOGRAM);
			times++;


		}

		if (times >= 40)
		{
			#if PM_DEBUG>0
				PRINT_PM(F("...failed. Communication error.\n"));
			#endif
			error = -1;
		}



		for(int i = 0; i < 86; i++)
		{
			delayMicroseconds(10);
			histogramString[i] = SPI.transfer(0x30);
		}

		SPI.setSPISlave(ALL_DESELECTED);

    // for(int i = 0; i < 86; i++)
    // {
    //   USB.print(i,DEC);
    //   USB.print(": ");
    //   USB.println(histogramString[i], DEC);
    // }


    // calculate checksum
		crc_bin = (histogramString[85] * 256) + histogramString[84];

    unsigned char _bit;
    unsigned int crc = 0xFFFF;
    unsigned char byteCtr;

		for (byteCtr = 0; byteCtr<84; byteCtr++)
		{
      crc ^=(unsigned int)histogramString[byteCtr];
      for(_bit=0; _bit<8; _bit++)
      {
        if(crc & 1){
          crc >>= 1;
          crc ^=  0xA001;
        }
        else{
          crc >>= 1;
        }
      }
		}

		if (crc_bin != crc)
		{
			#if PM_DEBUG>0
				PRINT_PM(F("...CRC NOK\n"));
				PRINT_PM(F("CRC bin: "));
				USB.print(crc_bin, DEC);
				USB.print(F(" || CRC : "));
				USB.println(crc, DEC);
			#endif

			error = -2;
		}

		#if PM_DEBUG>0
			PRINT_PM(F("...Done\n"));
		#endif

    int j = 0;
    for (int i=0; i<48; i+=2)
    {
      _bin[j] = *(uint16_t *)&histogramString[i];
      //_bin[j] = (unsigned int *)&histogramString[i];
      j++;
    }
    memcpy(_binL, _bin, 32);
    memcpy(_binH, &_bin[32], 16);


		_bin1_MToF = histogramString[48];
		_bin3_MToF = histogramString[49];
		_bin5_MToF = histogramString[50];
		_bin7_MToF = histogramString[51];

    // calculate temperature
	  aux_val = ((uint16_t)histogramString[57])*256 + histogramString[56];
		_temp = -45.0+((175.0*aux_val)/65535.0);

    // calculate humidity
		aux_val = ((uint16_t)histogramString[59])*256 + histogramString[58];
		_hum = 100.0*aux_val/65535.0;

    // calculate particle matter
		_PM1 = *(float *)&histogramString[60];
		_PM2_5 = *(float *)&histogramString[64];
		_PM10 = *(float *)&histogramString[68];
	}
	else
	{
		char command[10];
		uint32_t waitTime;

		#if PM_DEBUG>0
			PRINT_PM(F("PM.Getting PM with fan on\n"));
		#endif

		for (int i = 0; i < 24; i++)
		{
			_bin[i] = 0;
		}
    for (int i = 0; i < 16; i++)
    {
      _binL[i] = 0;
    }
    for (int i = 0; i < 8; i++)
    {
      _binH[i] = 0;
    }

		_temp = 0.0;
		_hum = 0.0;
		_periodCount = 0;
		_PM1 = 0.0;
		_PM2_5 = 0.0;
		_PM10 = 0.0;

		memset(command, '\0', sizeof(command));
		snprintf(	command, sizeof(command), "AT$201\r");

		beginSerial(9600, 1);
		Utils.setMuxAux2();
		delay(100);

		error = sendCommand(command, "$201", "ERROR", 2000);
		if( error != 1)
		{
			return -11;
		}

		error = waitFor("OK", 2000);
		if( error != 1)
		{
			return -12;
		}
		#if PM_DEBUG>0
			PRINT_PM(F("PM.String received: "));
			USB.println((char*) _buffer);
		#endif

    // count "," to know if the UART adapter board is v1 or v2
    uint8_t count = 0;
    for(int i; i<SENSOR_DUST_UART_SIZE; i++){
      if(strncmp((char*)_buffer[i],",",1)==0) {
        count ++;
      }
    }

    // UART adpter board firmware version v1
    if(count<26){

      #if PM_DEBUG>0
        PRINT_PM(F("UART adapter board firmware version v1\n"));
      #endif

      _PM1 = strtod(strtok((char*)_buffer+1, ","), NULL);
      _PM2_5 = strtod(strtok(NULL, ","), NULL);
      _PM10 = strtod(strtok(NULL, ","), NULL);

      for (uint8_t i = 0; i < 16; i++)
      {
        _bin[i] = atoi(strtok(NULL, ","));
      }

      _bin1_MToF = atoi(strtok(NULL, ","));
      _bin3_MToF = atoi(strtok(NULL, ","));
      _bin5_MToF = atoi(strtok(NULL, ","));
      _bin7_MToF = atoi(strtok(NULL, ","));

      _tempN2 = strtod(strtok(NULL, ","), NULL);
      _pressureN2 = strtod(strtok(NULL, ","), NULL);
      _periodCount = atol(strtok(NULL, "\r"));
    }
    else{ // UART adpter board firmware version v2

      #if PM_DEBUG>0
        PRINT_PM(F("UART adapter board firmware version v2\n"));
      #endif

  		_PM1 = strtod(strtok((char*)_buffer+1, ","), NULL);
  		_PM2_5 = strtod(strtok(NULL, ","), NULL);
  		_PM10 = strtod(strtok(NULL, ","), NULL);

  		for (uint8_t i = 0; i < 24; i++)
  		{
  			_bin[i] = atoi(strtok(NULL, ","));
  		}

  		_bin1_MToF = atoi(strtok(NULL, ","));
  		_bin3_MToF = atoi(strtok(NULL, ","));
  		_bin5_MToF = atoi(strtok(NULL, ","));
  		_bin7_MToF = atoi(strtok(NULL, ","));

  		_temp = strtod(strtok(NULL, ","), NULL);
  		_hum = strtod(strtok(NULL, ","), NULL);
      _periodCount = atol(strtok(NULL, ","));
      _opcModel = atoi(strtok(NULL, "\r"));
    }
    memcpy(_binL, _bin, 32);
    memcpy(_binH, &_bin[32], 16);
	}

	return error;
}

/* Function: 	This function reads configuration data from PM sensor module.
 * The next variables will be updated:
 * 				_binBoundaryValues[15]
 * 				_binParticleVolume[16]
 * 				_binParticleDensity[16]
 * 				_binSampleVolumeWeight[16]
 * 				_gain
 * 				_sample
 * 				_laserDAC
 * 				_fanDAC
 * Returns: 	1 if OK
 *				-1 if error sending the command
*/
int8_t WaspPM::getConfigVar()
{
	uint8_t error = 0;
	uint8_t val = 0;
	uint16_t times = 0;
	uint16_t crc = 0;
	uint16_t crc_bin = 0;

	byte aux_buffer[4];



	#if PM_DEBUG>0
		PRINT_PM(F("PM.Getting config variables"));
	#endif

	if(_mode == PM_UART_MODE)
	{
		#if PM_DEBUG>0
			PRINT_PM(F("... not supported in UART_MODE\n"));
		#endif
		return  -3;
	}

	delay(100);
	SPI.setSPISlave(DUST_SENSOR_SELECT);

	// Read histogram data
	while((val != CHECK_STATUS_READY) && (times < 100))
	{
		val = SPI.transfer(READ_CONFIG_VAR);
		times++;
		delay(1);
	}

	if (times >= 100)
	{
		#if PM_DEBUG>0
			PRINT_PM(F("...failed. Communication error.\n"));
		#endif
		return -1;
	}

	error = 1;

	// Bin Boundaries values (BB0 - BB14). It are unsigned 16bit integer values.
	for(int i = 0; i < 15; i++)
	{
		delayMicroseconds(8);
		val = SPI.transfer(0x3C);
		_binBoundaryValues[i] = 0;
		_binBoundaryValues[i] = val;
		delayMicroseconds(8);
		val = SPI.transfer(0x3C);
		_binBoundaryValues[i] = _binBoundaryValues[i] | (val << 8);
	}

	SPI.transfer(0x3C);
	SPI.transfer(0x3C);

	// Bin Particle Volumes (BPV0 - BPV15) are real number variables
	for(int i = 0; i < 16; i++)
	{
		delayMicroseconds(8);
		aux_buffer[0] = SPI.transfer(0x3C);
		delayMicroseconds(8);
		aux_buffer[1] = SPI.transfer(0x3C);
		delayMicroseconds(8);
		aux_buffer[2] = SPI.transfer(0x3C);
		delayMicroseconds(8);
		aux_buffer[3] = SPI.transfer(0x3C);
		_binParticleVolume[i] = *(float *)&aux_buffer[0];
	}

	// Bin Particle Densities (BPD0 - BPD15) are real number variables
	for(int i = 0; i < 16; i++)
	{
		delayMicroseconds(8);
		aux_buffer[0] = SPI.transfer(0x3C);
		delayMicroseconds(8);
		aux_buffer[1] = SPI.transfer(0x3C);
		delayMicroseconds(8);
		aux_buffer[2] = SPI.transfer(0x3C);
		delayMicroseconds(8);
		aux_buffer[3] = SPI.transfer(0x3C);
		_binParticleDensity[i] = *(float *)&aux_buffer[0];
	}

	// Bin Sample Volume Weightings (BSVW0 - BSVW15) are real number variables
	for(int i = 0; i < 16; i++)
	{
		delayMicroseconds(8);
		aux_buffer[0] = SPI.transfer(0x3C);
		delayMicroseconds(8);
		aux_buffer[1] = SPI.transfer(0x3C);
		delayMicroseconds(8);
		aux_buffer[2] = SPI.transfer(0x3C);
		delayMicroseconds(8);
		aux_buffer[3] = SPI.transfer(0x3C);
		_binSampleVolumeWeight[i] = *(float *)&aux_buffer[0];
	}

	// Gain Scaling Coefficient (GSC) is real number variable
	delayMicroseconds(8);
	aux_buffer[0] = SPI.transfer(0x3C);
	delayMicroseconds(8);
	aux_buffer[1] = SPI.transfer(0x3C);
	delayMicroseconds(8);
	aux_buffer[2] = SPI.transfer(0x3C);
	delayMicroseconds(8);
	aux_buffer[3] = SPI.transfer(0x3C);
	_gain = *(float *)&aux_buffer[0];


	// Sample Flow Rate (SFR) is real number variable
	delayMicroseconds(8);
	aux_buffer[0] = SPI.transfer(0x3C);
	delayMicroseconds(8);
	aux_buffer[1] = SPI.transfer(0x3C);
	delayMicroseconds(8);
	aux_buffer[2] = SPI.transfer(0x3C);
	delayMicroseconds(8);
	aux_buffer[3] = SPI.transfer(0x3C);
	_sample = *(float *)&aux_buffer[0];



	delayMicroseconds(8);
	_laserDAC = SPI.transfer(0x3C);
	delayMicroseconds(8);
	_fanDAC = SPI.transfer(0x3C);

	// Read 22 spare bytes
	for(int i = 0; i < 22; i++)
	{
		delayMicroseconds(8);
		SPI.transfer(0x3C);
	}

	SPI.setSPISlave(ALL_DESELECTED);

	#if PM_DEBUG>0
		PRINT_PM(F("...Done\n"));
	#endif

	return error;
}

/* Function: 	This function gets PM values (PM1, PM2_5 and PM10)
 * The next variables will be updated:
 * 				_bin[24]
 * 				_binL[16]
 * 				_binH[8]
 * 				_temp
 * 				_hum
 * 				_periodCount
 * 				_bin1_MToF
 * 				_bin3_MToF
 * 				_bin5_MToF
 * 				_bin7_MToF
 * 				_PM1
 * 				_PM2_5
 * 				_PM10
 * Parameters:	timeSample: desired time to sample in milliseconds
 * Returns: 	1 if OK
 * 				-1 if error sending the command digital pot on
 *				-2 if error receiving data
 * 				-3 if error sending the command read histogram
 *				-4 if error receiving data
 * 				-5 if error sending the command read histogram
 *				-6 if error receiving data
 * 				-7 if error sending the command digital pot off
 *				-8 if error receiving data
*/
int8_t WaspPM::getPM(uint32_t timeSample)
{
	return getPM(0, timeSample);
}

/* Function: 	This function gets PM values (PM1, PM2_5 and PM10)
 * The next variables will be updated:
 * 				_bin[24]
 * 				_binL[16]
 * 				_binH[8]
 * 				_temp
 * 				_hum
 * 				_periodCount
 * 				_bin1_MToF
 * 				_bin3_MToF
 * 				_bin5_MToF
 * 				_bin7_MToF
 * 				_PM1
 * 				_PM2_5
 * 				_PM10
 * Parameters:	waitSample: waiting time before to sample in milliseconds
 * 				timeSample: desired time to sample in milliseconds
 * Returns: 	1 if OK
 * 				-1 if error sending the command digital pot on
 *				-2 if error receiving data
 * 				-3 if error sending the command read histogram
 *				-4 if error receiving data
 * 				-5 if error sending the command read histogram
 *				-6 if error receiving data
 * 				-7 if error sending the command digital pot off
 *				-8 if error receiving data
*/
int8_t WaspPM::getPM(uint32_t waitSample, uint32_t timeSample)
{
	uint8_t error = 0;
	char* pointer1;
	char* pointer2;

	if (_mode == PM_SPI_MODE)
	{

		#if PM_DEBUG>0
			PRINT_PM(F("PM.Getting PM with fan on\n"));
		#endif

		for (int i = 0; i < 24; i++)
		{
			_bin[i] = 0;
		}
    for (int i = 0; i < 16; i++)
    {
      _binL[i] = 0;
    }
    for (int i = 0; i < 8; i++)
    {
      _binH[i] = 0;
    }

		_temp = 0.0;
		_hum = 0.0;
		_periodCount = 0;
		_PM1 = 0.0;
		_PM2_5 = 0.0;
		_PM10 = 0.0;
			configSPI();
		error = checkStatus();
    if (error != 1)
    {
      return error;
    }

		// Set digital pot ON
		delay(100);
		error = setDigitalPot(DIGITAL_POT_ON_FAN);
		if (error != 1)
		{
			return error;
		}
    delay(1000);
    error = setDigitalPot(DIGITAL_POT_ON_LASER);
    if (error != 1)
    {
      return error;
    }

		// // Reset the histogram
		delay(waitSample + 600);
		error = getHistogramData();
		if (error != 1)
		{
			return error - 2;
		}

		// Desired delay
		delay(timeSample);

		// Read the histogram
		error = getHistogramData();
		if (error != 1)
		{
			for (int i = 0; i < 24; i++)
			{
				_bin[i] = 0;
			}
      for (int i = 0; i < 16; i++)
      {
        _binL[i] = 0;
      }
      for (int i = 0; i < 8; i++)
      {
        _binH[i] = 0;
      }

			_temp = 0.0;
			_hum = 0.0;
			_periodCount = 0;
			_PM1 = 0.0;
			_PM2_5 = 0.0;
			_PM10 = 0.0;

			return error - 4;
		}

		// Set digital pot OFF
		delay(100);
		error = setDigitalPot(DIGITAL_POT_OFF_FAN);
		if (error != 1)
		{
			return error - 6;
		}
    delay(1000);
    error = setDigitalPot(DIGITAL_POT_OFF_LASER);
    if (error != 1)
    {
      return error - 6;
    }

	}
	else
	{
		char command[23];
		uint32_t waitTime;

		#if PM_DEBUG>0
			PRINT_PM(F("PM.Getting PM with fan on\n"));
		#endif

		for (int i = 0; i < 24; i++)
		{
			_bin[i] = 0;
		}
    for (int i = 0; i < 16; i++)
    {
      _binL[i] = 0;
    }
    for (int i = 0; i < 8; i++)
    {
      _binH[i] = 0;
    }
		_temp = 0.0;
		_hum = 0.0;
		_periodCount = 0;
		_PM1 = 0.0;
		_PM2_5 = 0.0;
		_PM10 = 0.0;
    _tempN2 = 0.0;
    _pressureN2 = 0.0;


		memset(command, '\0', sizeof(command));
		snprintf(	command, sizeof(command), "AT$200=%lu,%lu,2\r",
					waitSample, timeSample);
		waitTime = waitSample + timeSample + 8000;

		beginSerial(9600, 1);
		Utils.setMuxAux2();
		delay(100);

		error = sendCommand(command, "$200", "ERROR", waitTime);
		if( error != 1)
		{
      #if PM_DEBUG>0
        PRINT_PM(F(""));
        USB.println((char*) _buffer);
      #endif
			return -11;
		}

		error = waitFor("OK", 2000);
		if( error != 1)
		{
			return -12;
		}
		#if PM_DEBUG>0
			PRINT_PM(F("PM.String received: "));
			USB.println((char*) _buffer);
		#endif

    // count "," to know if the UART adapter board is v1 or v2
    uint8_t count = 0;
    for(int i=0; i<SENSOR_DUST_UART_SIZE; i++){
      // if(strncmp((char*)_buffer[i],",",1)==0) {
      //   count ++;
      // }
      if(_buffer[i]==',') {
        count ++;
      }
    }

    // UART adpter board firmware version v1
    if(count<26){

      #if PM_DEBUG>0
        PRINT_PM(F("UART adapter board firmware version v1\n"));
      #endif

      _PM1 = strtod(strtok((char*)_buffer+1, ","), NULL);
      _PM2_5 = strtod(strtok(NULL, ","), NULL);
      _PM10 = strtod(strtok(NULL, ","), NULL);

      for (uint8_t i = 0; i < 16; i++)
      {
        _bin[i] = atoi(strtok(NULL, ","));
      }

      _bin1_MToF = atoi(strtok(NULL, ","));
      _bin3_MToF = atoi(strtok(NULL, ","));
      _bin5_MToF = atoi(strtok(NULL, ","));
      _bin7_MToF = atoi(strtok(NULL, ","));

      _tempN2 = strtod(strtok(NULL, ","), NULL);
      _pressureN2 = strtod(strtok(NULL, ","), NULL);
      _periodCount = atol(strtok(NULL, "\r"));
      _opcModel = 0x32;
    }
    else{ // UART adpter board firmware version v2

      #if PM_DEBUG>0
        PRINT_PM(F("UART adapter board firmware version v2\n"));
      #endif

  		_PM1 = strtod(strtok((char*)_buffer+1, ","), NULL);
  		_PM2_5 = strtod(strtok(NULL, ","), NULL);
  		_PM10 = strtod(strtok(NULL, ","), NULL);

  		for (uint8_t i = 0; i < 24; i++)
  		{
  			_bin[i] = atoi(strtok(NULL, ","));
  		}

  		_bin1_MToF = atoi(strtok(NULL, ","));
  		_bin3_MToF = atoi(strtok(NULL, ","));
  		_bin5_MToF = atoi(strtok(NULL, ","));
  		_bin7_MToF = atoi(strtok(NULL, ","));

  		_temp = strtod(strtok(NULL, ","), NULL);
  		_hum = strtod(strtok(NULL, ","), NULL);
  		_periodCount = atol(strtok(NULL, ","));
      _opcModel = atoi(strtok(NULL, "\r"));
    }
    memcpy(_binL, _bin, 32);
    memcpy(_binH, &_bin[16], 16);
	}



	return error;
}

/* Function: 	This function reads the serial number from PM sensor.
 * Parameters:	buffer: string pointer to store the information data
 * Returns: 	1 if OK
 *				-1 if error sending the command
*/
int8_t WaspPM::readSerialNumber(char* buffer)
{

	uint8_t error = 0;
	uint8_t val = 0;
	uint16_t times = 0;


	#if PM_DEBUG>0
		PRINT_PM(F("PM.Reading serial number\n"));
	#endif

	if (_mode == PM_SPI_MODE)
	{

		SPI.setSPISlave(DUST_SENSOR_SELECT);
		delayMicroseconds(100);
		while((val != CHECK_STATUS_READY) && (times<100))
		{
			val = SPI.transfer(READ_SERIAL_NUMBER);
			times++;
			delay(1);
		}

		if (times >= 100)
		{
			return -1;
		}

		// At least 1.7 ms between command byte and following byte
		delay(10);

		for(int i = 0; i < 60; i++)
		{
      delayMicroseconds(10);
			buffer[i] = SPI.transfer(READ_SERIAL_NUMBER);
		}

		buffer[60] = '\0';

		error = 1;

		#if PM_DEBUG>0
      PRINT_PM(F(""));
			for(int i = 0; i < 60; i++)
			{
				USB.print(buffer[i],HEX);
				USB.print(" ");
			}
			USB.println("");
		#endif

		// Release the bus
		SPI.setSPISlave(ALL_DESELECTED);
	}
	else
	{
		char command[10];
		uint32_t waitTime;

		memset(command, '\0', sizeof(command));
		snprintf(	command, sizeof(command), "AT$102\r");

		beginSerial(9600, 1);
		Utils.setMuxAux2();
		delay(100);

		error = sendCommand(command, "$102", "ERROR", 2000);
		if( error != 1)
		{
			return -11;
		}

		error = waitFor("OK", 2000);
		if( error != 1)
		{
			return -12;
		}
		#if PM_DEBUG>0
			PRINT_PM(F("PM. Serial number: "));
			USB.println((char*) _buffer);
		#endif

		memset(buffer, '\0', 60);
		strncpy(buffer, (char*)_buffer+1, 60);

	}

	return error;
}

/// Preinstantiate Objects /////////////////////////////////////////////////////
WaspPM PM = WaspPM();
