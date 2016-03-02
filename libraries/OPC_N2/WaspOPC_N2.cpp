/*
 *  Library for managing the Particle sensor OPC-N2 from Alphasense
 * 
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.3
 *  Design:			David Gascón
 *  Implementation:	Marcos Yarza, Alejandro Gállego
 */
  

/******************************************************************************
 * Includes
 ******************************************************************************/

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspOPC_N2.h"


/******************************************************************************
 * Constructors
 ******************************************************************************/

WaspOPC_N2::WaspOPC_N2()
{
	// update Waspmote Control Register
	WaspRegister |= REG_DUST_GASES_PRO;
	
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
	_pressure = 0.0;
	_periodCount = 0;
	_PM1 = 0.0;
	_PM2_5 = 0.0;
	_PM10 = 0.0;
	
	pwrGasPRORegister = 0;
}


/******************************************************************************
 * PRIVATE FUNCTIONS                                                          *
 ******************************************************************************/

/* Function: 	This function checks if the OPC-N2 sensor is ready
 *
 * Returns 0 if not ready, 1 if  ready
*/
uint8_t WaspOPC_N2::checkStatus()
{	
	uint8_t error = 0;
	uint8_t val = 0;
	uint16_t times = 0;
	
	#if OPC_N2_DEBUG>0
		USB.print(F("OPC-N2: Check status..."));
	#endif
	
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
			#if OPC_N2_DEBUG>0
		USB.println(F("ready"));
	#endif
	}
	else
	{	
		error = 0;
		#if OPC_N2_DEBUG>0
		USB.println(F("not ready"));
		#endif
		
	}
	
	SPI.setSPISlave(ALL_DESELECTED);
	
	return error;
}

/* Function: 	This function inits the SPI bus to use with OPC-N2 module
 *
 * Returns nothing
*/
void WaspOPC_N2::configSPI()
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

/* Function: 	This function opens SPI port and powers the sensor
 *
 * Returns 		0 if the sensor doesn't init correctly
 * 				1 if init OK
*/
uint8_t WaspOPC_N2::ON()
{
	
	uint8_t error = 0;
	
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
		#if OPC_N2_DEBUG>0
			USB.println(F("OPC-N2.3V3 to ON"));
		#endif
		PWR.setSensorPower(SENS_3V3, SENS_ON);
	}
	delay(1000);
	
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
uint8_t WaspOPC_N2::OFF()
{	
	
	uint8_t error = 0;
	#if OPC_N2_DEBUG>0
		USB.print(F("OPC-N2.Turning off sensor,"));
	#endif
	// Stopping SPI port	
	SPI.isDustSensor = false;
	SPI.setSPISlave(ALL_DESELECTED);
	pinMode(DUST_SENSOR_CS,INPUT);
	SPI.close();
	
	digitalWrite(DUST_SENSOR_POWER,LOW);
	
	if (( pwrGasPRORegister == 0x01) || ( pwrGasPRORegister == 0x0))
	{			
		#if OPC_N2_DEBUG>0			
			USB.println(F("3V3 off"));
		#endif
		PWR.setSensorPower(SENS_3V3, SENS_OFF);		
	}
	#if OPC_N2_DEBUG>0		
	else
	{
		USB.println(F("3V3 NOT off"));
	}
	#endif
	
		
	if((digitalRead(DUST_SENSOR_CS) == HIGH) && (digitalRead(DUST_SENSOR_POWER) == LOW))
	{
		error = 1;		
		pwrGasPRORegister &= 0xFE;
	}
	isON = 0;
		
	
	return error;
}

/* Function: 	This function reads the information string from OPC-N2 sensor 
 * 				module. 
 * Parameters:	buffer: string pointer to store the information data
 * Returns: 	1 if OK
 *				-1 if error sending the command
*/
int8_t WaspOPC_N2::getInfoString(char* buffer)
{ 
	
	uint8_t error = 0;
	uint8_t val = 0;
	uint16_t times = 0;
	
	
	#if OPC_N2_DEBUG>0
		USB.println(F("OPC-N2.Reading information string"));
	#endif
	
	SPI.setSPISlave(DUST_SENSOR_SELECT);
	delayMicroseconds(100);
	while((val != CHECK_STATUS_READY) && (times<100))
	{ 
		val = SPI.transfer(READ_INFO_STRING);
		times++;
		delay(30);
	}
	
	if (times >= 100)
	{
		return -1;
	}	
	
	// At least 1.7 ms between command byte and following byte
	delay(2);
	
	for(int i = 0; i < 58; i++)
	{
		buffer[i] = SPI.transfer(READ_INFO_STRING);
		delayMicroseconds(8);
		
	}
	
	buffer[58] = '\0';
	
	error = 1;
	
	#if OPC_N2_DEBUG>0
		for(int i = 0; i < 58; i++)
		{
			USB.print(buffer[i],HEX);
			USB.print(" ");
		}
		USB.println("");
	#endif
		
	// Release the bus
	SPI.setSPISlave(ALL_DESELECTED);
	return error;
}

/* Function: 	This function switchs the fan and the laser ON or OFF
 * Parameters:	mode: DIGITAL_POT_ON or DIGITAL_POT_OFF
 * Returns 		1 if ok
 *				-1 if error sending the command
 * 				-2 if error receiving data
*/
int8_t WaspOPC_N2::setDigitalPot(uint8_t mode)
{	
	int8_t error = 0;
	uint8_t val = 0;
	uint16_t times = 0;
	
	#if OPC_N2_DEBUG>0
		USB.print(F("OPC-N2.Setting digital pot"));
	#endif
		
	uint8_t command[2];
	uint8_t command_answer[2];
	
	command[0] = SET_DIGITAL_POT;
	command[1] = mode;
	
	delay(100);
	SPI.setSPISlave(DUST_SENSOR_SELECT);
	delayMicroseconds(2);
	
	command_answer[0] = 0;
	command_answer[1] = 0;
	
	while(	((command_answer[0] != CHECK_STATUS_READY) || 
			(command_answer[1] != SET_DIGITAL_POT)) &&
			(times<20))
	{
		command_answer[0] = SPI.transfer(command[0]); 
		delay(2);
		command_answer[1] = SPI.transfer(command[1]); 
		delay(10);
		times++;
	}
	
	if (times >= 20 )
	{
		#if OPC_N2_DEBUG>0
			USB.println(F("...failed. Communication error."));
		#endif
		error = -1;
	}
	else
	{
		#if OPC_N2_DEBUG>0
			USB.println(F("...done."));
		#endif
		error = 1;
	}

	
	return error;
}

/* Function: 	This function reads the histogram from OPC-N2 sensor module. 
 * 	It will reset the histogram too. Next variables will be updated:
 * 				_bin[16]
 * 				_temp
 * 				_temp_float
 * 				_pressure
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
int8_t WaspOPC_N2::getHistogramData()
{
	uint8_t error = 1;
	uint8_t val = 0;
	uint16_t times = 0;
	uint16_t crc = 0;
	uint16_t crc_bin = 0;
	
	uint32_t aux_val;
	byte histogramString[62];	
	
	#if OPC_N2_DEBUG>0
		USB.print(F("OPC-N2.Getting histogram data"));
	#endif
	error = 1;
	delay(100);

	SPI.setSPISlave(DUST_SENSOR_SELECT);
	// Read histogram data
	while((val != CHECK_STATUS_READY) && (times < 100))
	{ 
		val = SPI.transfer(READ_HISTOGRAM);
		delay(10);
		times++;
		if (val != CHECK_STATUS_READY)	
		{
			SPI.setSPISlave(ALL_DESELECTED);
			delay(100);
			SPI.setSPISlave(DUST_SENSOR_SELECT);
			
		}
		
	}
	
	if (times >= 100)
	{
		#if OPC_N2_DEBUG>0
			USB.println(F("...failed. Communication error."));
		#endif
		error = -1;
	}
		
	
		
	for(int i = 0; i < 62; i++)
	{
		delayMicroseconds(8);     
		histogramString[i] = SPI.transfer(0x30);
	}

	SPI.setSPISlave(ALL_DESELECTED);
			
	crc = (histogramString[49] * 256) + histogramString[48];
	crc_bin=0;
	for (int i = 0; i<16; i++)
	{
		_bin[i] = 0;
		_bin[i] = (_bin[i] << 8) | histogramString[2*i+1];
		_bin[i] = (_bin[i] << 8) | histogramString[2*i];
		crc_bin += _bin[i];
	}
	
	
	if (crc_bin != crc)
	{		
		#if OPC_N2_DEBUG>0
			USB.println(F("...CRC NOK"));
			USB.print(F("CRC bin: "));
			USB.print(crc_bin, DEC);
			USB.print(F(" || CRC : "));
			USB.println(crc, DEC);
		#endif
			
		error = -2;
	}
	
	#if OPC_N2_DEBUG>0
		USB.println(F("...Done"));
	#endif
	
	
	_bin1_MToF = histogramString[32];
	_bin3_MToF = histogramString[33];
	_bin5_MToF = histogramString[34];
	_bin7_MToF = histogramString[35];
	
	aux_val = *(uint32_t *)&histogramString[36];
	_temp = aux_val / 10.0;
	aux_val = *(uint32_t *)&histogramString[40];
	_pressure = aux_val;
	_periodCount = *(uint32_t *)&histogramString[44];
	
	
	_PM1 = *(float *)&histogramString[50];
	_PM2_5 = *(float *)&histogramString[54];
	_PM10 = *(float *)&histogramString[58];

	return error;
}

/* Function: 	This function reads configuration data from OPC-N2 sensor module.
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
int8_t WaspOPC_N2::getConfigVar()
{
	uint8_t error = 0;
	uint8_t val = 0;
	uint16_t times = 0;
	uint16_t crc = 0;
	uint16_t crc_bin = 0;
	
	byte aux_buffer[4];
	
	
	
	#if OPC_N2_DEBUG>0
		USB.print(F("OPC-N2.Getting config variables"));
	#endif
	
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
		#if OPC_N2_DEBUG>0
			USB.println(F("...failed. Communication error."));
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
	
	#if OPC_N2_DEBUG>0
		USB.println(F("...Done"));
	#endif
		
	return error;
}

/* Function: 	This function gets PM values (PM1, PM2_5 and PM10)
 * The next variables will be updated:
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
int8_t WaspOPC_N2::getPM(uint32_t timeSample)
{
	

	return getPM(0, timeSample);
	
}

/* Function: 	This function gets PM values (PM1, PM2_5 and PM10)
 * The next variables will be updated:
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
int8_t WaspOPC_N2::getPM(uint32_t waitSample, uint32_t timeSample)
{
	uint8_t error = 0;
	
	#if OPC_N2_DEBUG>0
		USB.println(F("OPC-N2.Getting PM with fan on"));
	#endif
	
	for (int i = 0; i < 15; i++)
	{
		_bin[i] = 0;
	}
	
	_temp = 0.0;
	_pressure = 0.0;
	_periodCount = 0;
	_PM1 = 0.0;
	_PM2_5 = 0.0;
	_PM10 = 0.0;	 
		configSPI();
	error = checkStatus();
	
	// Set digital pot ON
	delay(100);
	error = setDigitalPot(DIGITAL_POT_ON);
	if (error != 1)
	{
		return error;
	}
		
	// Reset the histogram
	delay(waitSample + 500);
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
		for (int i = 0; i < 15; i++)
		{
			_bin[i] = 0;
		}
		
		_temp = 0.0;
		_pressure = 0.0;
		_periodCount = 0;
		_PM1 = 0.0;
		_PM2_5 = 0.0;
		_PM10 = 0.0;
		
		return error - 4;
	}
	
	// Set digital pot OFF
	delay(100);
	error = setDigitalPot(DIGITAL_POT_OFF);
	if (error != 1)
	{
		return error - 6;
	}
	
	return error;
}

/// Preinstantiate Objects /////////////////////////////////////////////////////
WaspOPC_N2 OPC_N2 = WaspOPC_N2();
