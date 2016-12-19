/*
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
 *  Version:		3.1
 *  Design:			David Gascón
 *  Implementation: Alejandro Gállego, Ahmad Saad
 */
 

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspSensorCities_PRO.h"
  
// Constructors ///////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorCitiesPRO::WaspSensorCitiesPRO()
{	
	pinMode(SCP_I2C_MAIN_EN, OUTPUT);	// I2C main pin
	
	pinMode(SCP_PWR_SOCKET_1, OUTPUT);	// PWR pin socket 1
	pinMode(SCP_PWR_SOCKET_2, OUTPUT);	// PWR pin socket 2
	pinMode(SCP_PWR_SOCKET_3, OUTPUT);	// PWR pin socket 3
	pinMode(SCP_PWR_SOCKET_4, OUTPUT);	// PWR pin socket 4
	pinMode(SCP_PWR_SOCKET_5, OUTPUT);	// PWR pin socket 5

	
	digitalWrite(SCP_I2C_MAIN_EN, LOW);	// I2C main pin
	
	digitalWrite(SCP_PWR_SOCKET_1, LOW);	// PWR pin socket 1
	digitalWrite(SCP_PWR_SOCKET_2, LOW);	// PWR pin socket 2
	digitalWrite(SCP_PWR_SOCKET_3, LOW);	// PWR pin socket 3
	digitalWrite(SCP_PWR_SOCKET_4, LOW);	// PWR pin socket 4
	digitalWrite(SCP_PWR_SOCKET_5, LOW);	// PWR pin socket 5
	
	// update Waspmote Control Register
	WaspRegisterSensor |= REG_CITIES_PRO;
	pwrCitiesPRORegister = 0;
	pwrGasPRORegister = 0;
}

// Private Methods ////////////////////////////////////////////////////////


// Public Methods //////////////////////////////////////////////////////////////

/*	Turns ON the sensor/socket
 *	Parameters:	socket_sensor:	SOCKET_1
 *								SOCKET_2
 * 								SOCKET_3
 * 								SOCKET_4
 * 								SOCKET_5
 * 								SOCKET_A
 * 								SOCKET_B
 * 								SOCKET_C
 * 								SOCKET_E
 * 								SOCKET_F
 *  Return:	void
 */
void WaspSensorCitiesPRO::ON(uint8_t socket_sensor)
{
	
	// Power on 3V3 and/or 5V if necessary	
	if ((WaspRegister & REG_3V3) == 0)
	{
		#if CITIES_PRO_DEBUG>0
			USB.println(F("SCP.3V3 to ON"));
		#endif
		PWR.setSensorPower(SENS_3V3, SENS_ON);
		digitalWrite(SCP_I2C_MAIN_EN, HIGH);	// I2C main pin
	}

	switch(socket_sensor)
	{
		case SOCKET_1:
		case SOCKET_C:
			digitalWrite(SCP_PWR_SOCKET_1, HIGH);
			
			// Set the flags
			pwrCitiesPRORegister |= 0x01;
			break;
			
		case SOCKET_2:
		case SOCKET_E:
			digitalWrite(SCP_PWR_SOCKET_2, HIGH);
			
			// Set the flags
			pwrCitiesPRORegister |= 0x02;
			break;
			
		case SOCKET_3:
		case SOCKET_F:
			digitalWrite(SCP_PWR_SOCKET_3, HIGH);
			
			// Set the flags
			pwrCitiesPRORegister |= 0x04;
			break;
			
		case SOCKET_4:
		case SOCKET_A:
			digitalWrite(SCP_PWR_SOCKET_4, HIGH);
			
			// Set the flags
			pwrCitiesPRORegister |= 0x08;
			break;
			
		case SOCKET_5:
		case SOCKET_B:
			digitalWrite(SCP_PWR_SOCKET_5, HIGH);
			
			// Set the flags
			pwrCitiesPRORegister |= 0x10;
			break;

	}
	
	#if CITIES_PRO_DEBUG>1
		USB.print(F("SCP.pwrCitiesPRORegister="));
		USB.println(pwrCitiesPRORegister, BIN);
		USB.print(F("SCP.pwrGasPRORegister="));
		USB.println(pwrGasPRORegister, BIN);
	#endif	
	
}

/*	Turns OFF the sensor/socket
 *	Parameters:	socket_sensor:	SOCKET_1
 *								SOCKET_2
 * 								SOCKET_3
 * 								SOCKET_4
 * 								SOCKET_5
 * 								SOCKET_A
 * 								SOCKET_B
 * 								SOCKET_C
 * 								SOCKET_E
 * 								SOCKET_F
 *  Return:	void
 */
void WaspSensorCitiesPRO::OFF(uint8_t socket_sensor)
{
	uint8_t mask;
	
	switch(socket_sensor)
	{	

		case SOCKET_1:
		case SOCKET_C:
			digitalWrite(SCP_PWR_SOCKET_1, LOW);
			
			// Set the flags
			pwrCitiesPRORegister &= 0xFE;
			break;
			
		case SOCKET_2:
		case SOCKET_E:
			digitalWrite(SCP_PWR_SOCKET_2, LOW);
			
			// Set the flags
			pwrCitiesPRORegister &= 0xFD;
			break;
			
		case SOCKET_3:
		case SOCKET_F:
			digitalWrite(SCP_PWR_SOCKET_3, LOW);
			
			// Set the flags
			pwrCitiesPRORegister &= 0xFB;
			break;
			
		case SOCKET_4:
		case SOCKET_A:
			digitalWrite(SCP_PWR_SOCKET_4, LOW);
			
			// Set the flags
			pwrCitiesPRORegister &= 0xF7;
			break;
			
		case SOCKET_5:
		case SOCKET_B:
			digitalWrite(SCP_PWR_SOCKET_5, LOW);
			
			// Set the flags
			pwrCitiesPRORegister &= 0xEF;
			break;

	}	
	#if CITIES_PRO_DEBUG>1
		USB.print(F("SCP.pwrCitiesPRORegister="));
		USB.println(pwrCitiesPRORegister, BIN);
		USB.print(F("SCP.pwrGasPRORegister="));
		USB.println(pwrGasPRORegister, BIN);
	#endif	
	
	// Check I2C isolator
	if ((pwrCitiesPRORegister == 0) && ((pwrGasPRORegister & 0xFE) == 0))
	{
		// Disable I2C isolator
		digitalWrite(SCP_I2C_MAIN_EN, LOW);
	}
	
	if ((pwrGasPRORegister == 0x00) && 
		(pwrCitiesPRORegister == 0x00) && 
		((WaspRegister & REG_3V3) != 0))
	{					
		#if CITIES_PRO_DEBUG>0
			USB.println(F("SCP.3V3 to OFF"));
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



