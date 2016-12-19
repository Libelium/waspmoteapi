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
 *  Version:		3.0
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, Manuel Calahorra
 */
 

#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "WaspSensorParking.h"

// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorParking::WaspSensorParking()
{
	pinMode(DIGITAL7,OUTPUT);
	pinMode(DIGITAL6,OUTPUT);
	pinMode(DIGITAL5,OUTPUT);
	pinMode(DIGITAL4,OUTPUT);
	pinMode(DIGITAL3,OUTPUT);
	pinMode(DIGITAL2,OUTPUT);
	pinMode(DIGITAL1,OUTPUT);
	pinMode(16,OUTPUT);
	pinMode(17,OUTPUT);
	pinMode(19,OUTPUT);
	
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(DIGITAL6,LOW);
	digitalWrite(DIGITAL5,LOW);
	digitalWrite(DIGITAL4,LOW);
	digitalWrite(DIGITAL3,LOW);
	digitalWrite(DIGITAL2,LOW);
	digitalWrite(DIGITAL1,LOW);
	digitalWrite(16,LOW);
	digitalWrite(17,LOW);
	digitalWrite(19,LOW);	
	
	// init power supply to OFF state
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	PWR.setSensorPower(SENS_5V, SENS_OFF);
		
	// update Waspmote Control Register
	WaspRegisterSensor |= REG_PARKING;
}

// Public Methods //////////////////////////////////////////////////////////////

/*	ON: Calls the setBoardMode function to turn on the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorParking::ON(void)
{
	setBoardMode(SENS_ON);
}

/*	OFF: Calls the setBoardMode function to turn off the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorParking::OFF(void)
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
int8_t	WaspSensorParking::setBoardMode(uint8_t mode)
{
	switch( mode )
	{
		case	SENS_ON	:	// switch on the power supply
							PWR.setSensorPower(SENS_5V, SENS_ON);
							break;
		case	SENS_OFF:	// switch on the power supply
							PWR.setSensorPower(SENS_5V, SENS_OFF);
							break;
		default			:	return 0;
	}
	
	return 1;
}

/*	calibration: calibrates the empty state of the parking lot completing the
 * 				 reference values for temperature and magnetic field in initialX,
 * 				 initialY, initialZ and initialTand the initial compensation indexes
 * 				 in variables indexX, indexY and indexZ
 *	Parameters:	void
 *  Return:		void
 * 	
 */
void	WaspSensorParking::calibration(void)
{
	uint16_t val_x = 0;
	uint16_t val_y = 0;
	uint16_t val_z = 0;  
	int temp = 0;
	int temper = 0;
	float temp2 = 0.0;
	  
	for(int i=0; i<8; i++)
	{
		readParkingSetReset();
		val_x+=valueX;
		val_y+=valueY;
		val_z+=valueZ;  
		delay(500);  
	}
	  
	initialX = val_x/8;
	initialY = val_y/8;
	initialZ = val_z/8;

	temper = 0;  
	temp = 0;
	analogRead(SENS_PARKING_T);
	delay(1);
	for(int i=0; i<8; i++)
	{
		temper=analogRead(SENS_PARKING_T);  
		delay(100);
		temp2 = ((float(temper) * 3300 / 1023) - 500) / 10;
		temper = int(temp2);
		temp = temp + temper;
	}

	temp2 = float(temp)/8;
	 
	temp = int(temp2);

	initialT = temp;
	  
	indexX = coefX2*temp*temp + coefX*temp + constX;
	indexY = coefY2*temp*temp + coefY*temp + constY;
	indexZ = coefZ2*temp*temp + coefZ*temp + constZ;

}

/*	loadReference: It loads the coefficients of the approximation for temperature
 * 				   dependance from the EEPROM in variables coefX2, coefY2, coefZ2,
 * 				   coefX, coefY, coefZ, constX, constY and constZ
 *	Parameters:	void
 *  Return:		void
 * 	
 */
void	WaspSensorParking::loadReference(void)
{
	int address;

	address = PARKING_ADDRESS_COEFX2;
	coefX2 = eeprom_read_float((float*)(address));
	address = PARKING_ADDRESS_COEFY2;
	coefY2 = eeprom_read_float((float*)(address));
	address = PARKING_ADDRESS_COEFZ2;
	coefZ2 = eeprom_read_float((float*)(address));
	address = PARKING_ADDRESS_COEFX;
	coefX = eeprom_read_float((float*)(address));
	address = PARKING_ADDRESS_COEFY;
	coefY = eeprom_read_float((float*)(address));
	address = PARKING_ADDRESS_COEFZ;
	coefZ = eeprom_read_float((float*)(address));
	address = PARKING_ADDRESS_CONSTX;
	constX = eeprom_read_float((float*)(address));
	address = PARKING_ADDRESS_CONSTY;
	constY = eeprom_read_float((float*)(address));
	address = PARKING_ADDRESS_CONSTZ;
	constZ = eeprom_read_float((float*)(address));
}

/*	calculateReference: It calculates the reference for each axis in function of
 * 						the initial values (initialX, initialY and initialZ), the
 * 						compensation coefficeints (coefX2, coefY2, coefZ2, coefX,
 * 						coefY, coefZ, constX, constY and constZ) and current
 * 						temperature and stores them in variables referenceX,
 * 						referenceY and referenceZ
 * 	Parameters: int temperature : temperature read at which the mote currrently is
 *  Return:		void
 * 
 */
void	WaspSensorParking::calculateReference(int temperature)
{
	referenceX = int((float(initialX) / indexX) *
					( coefX2*temperature*temperature + coefX*temperature + constX ));
	referenceY = int((float(initialY) / indexY) *
					( coefY2*temperature*temperature + coefY*temperature + constY ));
	referenceZ = int((float(initialZ) / indexZ) * 
					( coefZ2*temperature*temperature + coefZ*temperature + constZ ));
}

/*	readTemperature: It reads the output voltage of the temperature sensor and
 * 					 returns temperature in Celsius degree
 * 	Parameters:	void
 *  Return:		int value : the temperature value read from the sensor
 * 
 */
int	WaspSensorParking::readTemperature(void)
{
	int temp = 0;
	int temper = 0;
	float temp2 = 0.0;
	analogRead(SENS_PARKING_T);
	for(int i=0; i<8; i++)
	{
		temper=analogRead(SENS_PARKING_T);  
		delay(10);
		temp2 = ((float(temper) * 3300 / 1023) - 500) / 10;
		temper = int(temp2);
		temp = temp + temper;
	}

	temp2 = float(temp)/8;
	 
	temp = int(temp2);

	return temp;

}

/*	readParking: It reads the magnetic field sensors and returns the values read
 * 				 in variables valueX, valueY and valueZ
 *	Parameters:	void
 *  Return:		void
 * 	
 */
void	WaspSensorParking::readParking(void)
{
	analogRead(SENS_PARKING_X);
	delay(1);
	valueX = analogRead(SENS_PARKING_X);
	analogRead(SENS_PARKING_Y);
	delay(1);
	valueY = analogRead(SENS_PARKING_Y);
	analogRead(SENS_PARKING_Z);
	delay(1);
	valueZ = analogRead(SENS_PARKING_Z);
}

/*	readParkingSetReset: It applies a set and reset pulse to the magnetic field
 * 						 sensors and reads them, returning the values read in
 * 						 variables valueX, valueY and valueZ
 *	Parameters:	void
 *  Return:		void
 * 	
 */
void	WaspSensorParking::readParkingSetReset(void)
{
	digitalWrite(PARKING_SET_RESET_Y,HIGH);
	digitalWrite(PARKING_SET_RESET_X,HIGH);
	delay(100);
	digitalWrite(PARKING_SET_RESET_Y,LOW);
	digitalWrite(PARKING_SET_RESET_X,LOW);
	analogRead(SENS_PARKING_X);
	delay(10);
	valueX = analogRead(SENS_PARKING_X);
	analogRead(SENS_PARKING_Y);
	delay(1);
	valueY = analogRead(SENS_PARKING_Y);
	delay(100);
	digitalWrite(PARKING_SET_RESET_Z,HIGH);
	delay(100);
	digitalWrite(PARKING_SET_RESET_Z,LOW);
	analogRead(SENS_PARKING_Z);
	delay(10);
	valueZ = analogRead(SENS_PARKING_Z);
}

/*	estimateState: It uses the values in variables valueX, valueY, valueZ,
 * 				   referenceX, referenceY and referenceZ to estimate the
 * 				   state of the parking lot
 *	Parameters:	void
 *  Return:		boolean state : state of the lot
 * 								0 empty
 * 								1 occupied
 * 	
 */
boolean	WaspSensorParking::estimateState(void)
{
	boolean status;

	if( (abs((valueX-referenceX))>=PARKING_THRESHOLD) || (abs((valueY-referenceY))>=PARKING_THRESHOLD) || (abs((valueZ-referenceZ))>=PARKING_THRESHOLD) ) status = PARKING_OCCUPIED;
	else status = PARKING_EMPTY;

	return status;
}


// Private Methods //////////////////////////////////////////////////////////////


WaspSensorParking SensorParking=WaspSensorParking();
