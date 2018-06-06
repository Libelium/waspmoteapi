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
 *  Version:		3.1
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, Manuel Calahorra
 */
 
#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "WaspSensorPrototyping_v20.h"



// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorPrototyping_v20::WaspSensorPrototyping_v20()
{	
	// init power supply to OFF state
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	
	// update Waspmote Control Register
	WaspRegisterSensor |= REG_PROTOTYPING;
}

// Public Methods //////////////////////////////////////////////////////////////

/*	ON: Calls the setBoardMode function to turn on the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorPrototyping_v20::ON(void)
{
	setBoardMode(SENS_ON);
}

/*	OFF: Calls the setBoardMode function to turn off the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorPrototyping_v20::OFF(void)
{
	setBoardMode(SENS_OFF);
}

/*	setBoardMode: Sets the board mode indicated
 *	Parameters:	uint8_t mode 
 * 						- SENS_ON : turn on the board
 * 						- SENS_OFF : turn off the board
 *  Return:		uint8_t error
 * 						- 1 : success / no error detected
 * 						- 0 : wrong mode introduced
 */
int8_t	WaspSensorPrototyping_v20::setBoardMode(uint8_t mode)
{
	switch( mode )
	{
		case	SENS_ON :	// switch on the power supplies
							PWR.setSensorPower(SENS_3V3, SENS_ON);
							PWR.setSensorPower(SENS_5V, SENS_ON);
							// Sets RTC on to enable I2C
							if(!RTC.isON) RTC.setMode(RTC_ON, RTC_I2C_MODE);
							break;
		case	SENS_OFF:	// switch off the power supplies
							PWR.setSensorPower(SENS_3V3, SENS_OFF);
							PWR.setSensorPower(SENS_5V, SENS_OFF);
							break;
		default			:	return 0;
	}
	
	return 1;
}

/*	readADC: reads the analog to digital converter on the board through the I2C
 *	Parameters: void
 *  Return:	float value : voltage measured by the ADC, between -4.5V and 4.5V
 */
float	WaspSensorPrototyping_v20::readADC(void)
{
	uint8_t data[2] = {0, 0};
	float val_def;
	uint16_t val;
    uint8_t error;

	I2C.begin();
	
	delay(100);
	
    I2C.begin();
    error = I2C.read((uint8_t)B0010100, data, 2);	

	val = int(data[0])*256 + int(data[1]);
	val_def = ((float)val - 32769.0)*9.0;
	val_def = val_def/65535;

	return val_def;
}

/*	readAnalogSensor: reads the indicated pin and converts its value into volts
 *	Parameters:	uint8_t pin : pin to be read, from ANALOG1 to ANALOG7
 *  Return:		float value : voltage read in the pin in volts
 * 							  -1 if an incorrect pin was selected
 */
float WaspSensorPrototyping_v20::readAnalogSensor(uint8_t pin)
{
	uint16_t read_val;
	float def_val;

	if ( (pin >= ANALOG1) && (pin <= ANALOG7) )
	{
		read_val = analogRead(pin);
		read_val = analogRead(pin);
		def_val = (read_val*3.3)/1023;
		return def_val;
	}
	else	return -1;
}


WaspSensorPrototyping_v20 SensorProtov20=WaspSensorPrototyping_v20();
