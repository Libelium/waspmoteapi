/*! \file currentLoop.cpp

	\brief Library for managing the 4-20mA Board
	Copyright (C) 2017 Libelium Comunicaciones Distribuidas S.L.
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

	Version:		3.1
	Implementation:	Ahmad Saad
*/

/***********************************************************************
 * Includes
 ***********************************************************************/
#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif

#include "currentLoop.h"


/***********************************************************************
 * Class contructors
 ***********************************************************************/
 
//!*************************************************************
//!	Name:	currentLoop
//!	Description: Constructor of the class
//!************************************************************* 
currentLoop::currentLoop() {}

 
/***********************************************************************
 * Methods of the Class
 ***********************************************************************/
 
//!*************************************************************
//!	Name:	ON(uint8_t powerSupply)									
//!	Description: Powers ON the 4-20mA supply 5V or 12V.			
//!	Param : powerSupply: the power supply to switch ON.			
//!	Returns: "1" if no error, "0" if error							
//!*************************************************************
uint8_t currentLoop::ON(uint8_t powerSupply)
{
	if (powerSupply == SUPPLY12V) {
		pinMode(DIGITAL5, OUTPUT);
		delay(1000);
		digitalWrite(DIGITAL5, LOW);
		delay(1000);
	} else	if (powerSupply == SUPPLY5V) {
		PWR.setSensorPower(SENS_5V,SENS_ON); 
	} else {
		return 0;
	}
	
	return 1;
}


//!*************************************************************
//!	Name:	OFF(uint8_t powerSupply)													
//!	Description: Powers OFF the 4-20mA supply 5V or 12V.
//!	Param : uint8_t powerSupply: the power supply to switch OFF.
//!	Returns: "1" if no error, "0" if error						
//!*************************************************************
uint8_t currentLoop::OFF(uint8_t powerSupply)
{
	if (powerSupply == SUPPLY12V) {
		pinMode(DIGITAL5, OUTPUT);
		digitalWrite(DIGITAL5, HIGH);
		delay(1000);
	} else	if (powerSupply == SUPPLY5V) {
		PWR.setSensorPower(SENS_5V,SENS_OFF); 
	} else {
		return 0;
	}
	
	return 1;
}


//!*************************************************************
//!	Name:	readChannel(uint8_t channel)
//!	Description: Get the sensor value in integer format.
//!	Param : uint8_t channel: the channel to read.	
//!	Returns: int with the value read (0-1023)
//!*************************************************************	
int currentLoop::readChannel(uint8_t channel)
{
	_analogValue = 0;
	uint8_t readings = 100;
	
	if ((channel == SOCKET_A) || (channel == CHANNEL1)) 
	{
		channel = ANALOG1;
	} 
	else if ((channel == SOCKET_B) || (channel == CHANNEL2))
	{
		channel = ANALOG2;
	}
	
	else if ((channel == SOCKET_C) || (channel == CHANNEL3))
	{
		channel = ANALOG5;
	}
	else if ((channel == SOCKET_D) || (channel == CHANNEL4))
	{
		channel = ANALOG6;
	}	
		
	for (int i = 0; i < readings ; i ++){
		_analogValue = _analogValue + analogRead(channel);
	} 
		
	return _analogValue / readings;
}


//!*************************************************************
//!	Name:	readVoltage(uint8_t channel)
//!	Description: Get the sensor value as a voltage in Volts.
//!	Param : uint8_t channel: the channel to read.
//!	Returns: the voltage value read (0 - 3V3)
//!*************************************************************
float currentLoop::readVoltage(uint8_t channel)
{
	return (readChannel(channel) * 3.3 / 1023.0);
}


//!*************************************************************
//!	Name:	readCurrent(uint8_t channel)
//!	Description: Get the sensor value as a current in mA. 
//!	Param : uint8_t channel: the channel to read.					
//!	Returns: the current value read (4-20mA).
//!*************************************************************
float currentLoop::readCurrent(uint8_t channel)
{
	return (readVoltage(channel) / 165.0 * 1000);
}


//!*************************************************************
//!	Name:	readCurrent(uint8_t channel, float offSet)
//!	Description: Get the sensor value as a current in mA. 
//!	Param : uint8_t channel: the channel to read.
//!	        float offSet: correction offSet. 
//!	Returns: the current value read (4-20mA).
//!*************************************************************
float currentLoop::readCurrent(uint8_t channel, float offSet)
{
	return ((readVoltage(channel) / 165.0 * 1000) - offSet);
}


//!*************************************************************
//!	Name:	isConnected(uint8_t channel)
//!	Description: It checks if the current loop is well connected
//!	Param : the channel to read.			
//!	Returns: "0" if no connected, "1" if connected.
//!*************************************************************
uint8_t currentLoop::isConnected(uint8_t channel)
{
	if (readVoltage(channel) < 0.6)
		return 0;
	else
		return 1;
}


currentLoop currentLoopBoard = currentLoop();


