/*
 *  Copyright (C) 2009 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		0.8
 *  Design:		David Gascón
 *  Implementation:	Alberto Bielsa, David Cuartielles
 */
 

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspSensorEvent_v20.h"

// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorEvent_v20::WaspSensorEvent_v20()
{
	pinMode(DIGITAL0,OUTPUT);
	pinMode(DIGITAL1,INPUT);
	pinMode(DIGITAL2,OUTPUT);
	pinMode(DIGITAL3,OUTPUT);
	pinMode(DIGITAL4,OUTPUT);
	pinMode(DIGITAL5,INPUT);
	pinMode(DIGITAL6,OUTPUT);
	pinMode(DIGITAL7,OUTPUT);
	pinMode(DIGITAL8,OUTPUT);
	pinMode(SENS_PW_3V3,OUTPUT);
		
	digitalWrite(DIGITAL0,LOW);
	digitalWrite(DIGITAL2,LOW);
	digitalWrite(DIGITAL3,LOW);
	digitalWrite(DIGITAL4,LOW);
	digitalWrite(DIGITAL6,LOW);
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(DIGITAL8,LOW);
	digitalWrite(SENS_PW_3V3,LOW);
}

// Public Methods //////////////////////////////////////////////////////////////

/*	ON: Calls the setBoardMode function to turn on the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorEvent_v20::ON(void)
{
	setBoardMode(SENS_ON);
}

/*	OFF: Calls the setBoardMode function to turn off the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorEvent_v20::OFF(void)
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
int8_t	WaspSensorEvent_v20::setBoardMode(uint8_t mode)
{
	switch( mode )
	{
		case	SENS_ON :	digitalWrite(SENS_PW_3V3,HIGH);
							// Sets RTC on to enable I2C
							if(!RTC.isON) RTC.setMode(RTC_ON, RTC_I2C_MODE);
							break;
		case	SENS_OFF:	digitalWrite(SENS_PW_3V3,LOW);
							break;
		default 		: 	return 0;
	}
	
	return 1;
}


/* setThreshold: Sets interruption threshold configuring the corresponding digipot
 *	Parameters:	uint8_t sensor 
 * 						- SENS_SOCKET1
 * 						- SENS_SOCKET2
 * 						- SENS_SOCKET3
 * 						- SENS_SOCKET4
 * 						- SENS_SOCKET5
 * 						- SENS_SOCKET6
 * 			  : float threshold : interruption threshold of the sensor between 0
 * 								  and 3.3V
 *  Return:		uint8_t error
 * 						- 1 : success / no error detected
 * 						- -1 : wrong socket introduced
 * 						- -2 : wrong threshold introduced
 * 
 */
int8_t	WaspSensorEvent_v20::setThreshold(uint8_t sensor, float threshold) 
{
	if( ( threshold < 0 ) || ( threshold > 3.3 ) )
	{
		return -2;
	}
	
	switch( sensor )
	{
		case	SENS_SOCKET1	:	setDigipot1(B0101000,threshold);
									break;
		case	SENS_SOCKET2	:	setDigipot0(B0101000,threshold);
									break;
		case	SENS_SOCKET3	:	setDigipot0(B0101100,threshold);
									break;
		case	SENS_SOCKET4	:	setDigipot1(B0101100,threshold);
									break;
		case	SENS_SOCKET5	:	setDigipot0(B0101010,threshold);
									break;
		case	SENS_SOCKET6	:	setDigipot1(B0101010,threshold);
									break;
		default					:	return -1;
	}
	
	return 1;	
}

/*	readValue: Reads the analog to digital converter input indicated of the given
 * 			   sensor socket and converts the value into voltage
 *	Parameters:	uint16_t sensor
 * 						- SENS_SOCKET1
 * 						- SENS_SOCKET2
 * 						- SENS_SOCKET3
 * 						- SENS_SOCKET4
 * 						- SENS_SOCKET5
 * 						- SENS_SOCKET6
 * 						- SENS_SOCKET7
 * 						- SENS_SOCKET8
 *  Return:		float value : voltage read at the sensor output
 * 							  -1.0 for error in sensor type selection
 * 
 */
float	WaspSensorEvent_v20::readValue(uint8_t sensor)
{
	uint16_t aux=0;
	switch( sensor )
	{
		case	SENS_SOCKET1	:	aux=analogRead(ANALOG1);
									break;
		case	SENS_SOCKET2	:	aux=analogRead(ANALOG2);
									break;
		case	SENS_SOCKET3	:	aux=analogRead(ANALOG4);
									break;
		case	SENS_SOCKET4	:	aux=analogRead(ANALOG3);
									break;
		case	SENS_SOCKET5	:	aux=analogRead(ANALOG6);
									break;
		case	SENS_SOCKET6	:	aux=analogRead(ANALOG7);
									break;
		case	SENS_SOCKET7	:	aux=digitalRead(DIGITAL5);
									return aux;
									break;
		case	SENS_SOCKET8	:	aux=analogRead(ANALOG5);
									break;
		default					:	return -1.0;
	}
	return	(aux*3.3)/1023;
}

/*	readValue: Reads the analog to digital converter input indicated of the given
 * 			   sensor socket and converts the value into voltage
 *	Parameters:	uint16_t sensor
 * 						- SENS_SOCKET1
 * 						- SENS_SOCKET2
 * 						- SENS_SOCKET3
 * 						- SENS_SOCKET4
 * 						- SENS_SOCKET5
 * 						- SENS_SOCKET6
 * 						- SENS_SOCKET7
 * 						- SENS_SOCKET8
 * 				uint16_t parameter
 * 						- SENS_RESISTIVE
 * 						- SENS_FS100
 * 						- SENS_FS200A
 * 						- SENS_FS400
 * 						- SENS_TEMPERATURE
 * 						- SENS_HUMIDITY
 *  Return:		float value : converted value of the sensor
 * 							  -1000.0 for error in sensor type selection
 * 
 */
float	WaspSensorEvent_v20::readValue(uint8_t sensor, uint8_t type)
{
	float aux = 0;
	
	switch (type)
	{
		case 	SENS_RESISTIVE	:	aux = readValue(sensor);
									switch ( sensor )
									{
										case	SENS_SOCKET1	:	aux = ( ( 3.3 / aux ) - 1 ) * 560;
																	break;
										case	SENS_SOCKET2	:	aux = ( ( 3.3 / aux ) - 1 ) * 100;
																	break;
										case	SENS_SOCKET3	:	aux = ( ( 3.3 / aux ) - 1 ) * 10;
																	break;
										default					:	return -1000.0;
									}
									break;
		case 	SENS_FLOW_FS100	:	
		case 	SENS_FLOW_FS200 :	
		case 	SENS_FLOW_FS400	:	aux = flowReading(type);
									break;
		case 	SENS_TEMPERATURE:	aux = readValue(sensor);
									aux = ( aux - 0.5 )* 100;
									break;
		case 	SENS_HUMIDITY	:	aux = readValue(sensor);
									aux = aux * 100 / 3;
									break;
		default					:	aux = readValue(sensor);
									break;			
	}
	
	return aux;
}


/* attacInt: It attaches sensors board interruption, setting three-state buffer
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorEvent_v20::attachInt(void) 
{
	digitalWrite(SENS_INT_ENABLE,HIGH); 
	enableInterrupts(SENS_INT);
}


/* detachInt: It detaches sensor board interruption, unsetting three-state buffer
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorEvent_v20::detachInt(void) 
{
	digitalWrite(SENS_INT_ENABLE,LOW); 
	disableInterrupts(SENS_INT);
}


/* loadInt: Loads shift register through parallel input to check the sensor
 * 			that generates the interruption updating 'intFlag'
 *	Parameters:	void
 *  Return:		uint8_t loadInt : as long as updating the 'intFlag' variable, it
 * 								  returns the same value as a uint8_t
 * 
 */
uint8_t	WaspSensorEvent_v20::loadInt(void) 
{
	uint8_t aux=0;
	
	intFlag=0;
	
	delay(1);
	digitalWrite(SENS_INT_ENABLE, LOW);  
	delay(10);
	digitalWrite(SENS_INT_CLK_INH, LOW);
	delay(1);

	if(digitalRead(SENS_INT_DO)) intFlag |= 1;
	delay(2);

	digitalWrite(SENS_INT_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_DO)) intFlag |= 2;
	delay(1);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);

	digitalWrite(SENS_INT_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_DO)) intFlag |= 4;
	delay(1);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);

	digitalWrite(SENS_INT_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_DO)) intFlag |= 8;
	delay(1);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);

	digitalWrite(SENS_INT_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_DO)) intFlag |= 16;
	delay(1);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
      
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_DO)) intFlag |= 32;
	delay(1);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
      
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_DO)) intFlag |= 64;
	delay(1);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);

	digitalWrite(SENS_INT_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_DO)) intFlag |= 128;
	delay(1);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
	
	delay(200);
	digitalWrite(SENS_INT_ENABLE, HIGH);
	digitalWrite(SENS_INT_CLK_INH, HIGH);
	
	
	
	if( intFlag & 16) aux |= 0x01;
	if( intFlag & 32) aux |= 0x02;
	if( intFlag & 2) aux |= 0x04;
	if( intFlag & 1) aux |= 0x08;
	if( intFlag & 8) aux |= 0x10;
	if( intFlag & 4) aux |= 0x20;
	if( intFlag & 64) aux |= 0x40;
	if( intFlag & 128) aux |= 0x80;
	
	return aux;
}

// Private Methods //////////////////////////////////////////////////////////////


/*	flowReading: reads the analog to digital converter input indicated
 * 						   in socket and converts the value into distance in
 * 						   function of the sensor selected in mode
 *	Parameters:	uint16_t socket : digital input to be read
 * 				uint8_t model
 * 						- SENS_FLOW_FS100 : Selects FS100A flow sensor
 * 						- SENS_FLOW_FS200 : Selects FS200A flow sensor 
 * 						- SENS_FLOW_FS400 : Selects FS400A flow sensor
 *
 *  Return:		float flow : flow measured by the sensor in litres/minute
 * 							 -1.0 for error in sensor type selection
 * 
 */
 float WaspSensorEvent_v20::flowReading(uint8_t model)
{
	float flow = 0.0;
	int value = 0;
	long start = 0;
	int previous_reading = 0;
	int reading = 0;
	start = millis();
	while((millis()-start)<=1000)
	{
	  previous_reading = reading;
	  reading = digitalRead(18);
	  
	  if((previous_reading == 1)&&(reading == 0))
	  {
	    value++;
	  }
	}
	delay(100);


	switch(model)
	{
		case SENS_FLOW_FS100	:	flow = float(value) / 65;
									break;

		case SENS_FLOW_FS200	:	flow = float(value) / 7.5;
									break;

		case SENS_FLOW_FS400	:	flow = float(value) / 6.5;
									break;

		default 				:	flow = -1.0;
									break;
	}

	return flow;
}


/*	setResistor: calculates the resistor value in function of the entered threshold
 * 				 and sets the digipot for B digipots
 *	Parameters:	uint8_t address : I2C address of the digipot
 *  			float value : load resistor value selected
 * 	Return: 	void
 * 
 */
void WaspSensorEvent_v20::setDigipot1(uint8_t address, float value)
{

	float thres=0.0;
	uint8_t threshold=0;
		
	thres=(3.3-value);
	thres *=128;
	thres /=3.3;
	threshold = (uint8_t) thres;
	if( !Wire.I2C_ON ) Wire.begin();
	delay(100);
	Wire.beginTransmission(address);
	Wire.send(B00010000);
	Wire.send(threshold);
	Wire.endTransmission();
	if( Wire.I2C_ON && !ACC.isON && RTC.isON!=1){
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
}

/*	setResistor: calculates the resistor value in function of the entered threshold
 * 				 and sets the digipot for A digipots
 *	Parameters:	uint8_t address : I2C address of the digipot
 *  			float value : load resistor value selected
 * 	Return: 	void
 * 
 */
void WaspSensorEvent_v20::setDigipot0(uint8_t address, float value)
{
	float thres=0.0;
	uint8_t threshold=0;
		
	thres=(3.3-value);
	thres *=128;
	thres /=3.3;
	threshold = (uint8_t) thres;
	if( !Wire.I2C_ON ) Wire.begin();
	delay(100);
	Wire.beginTransmission(address);
	Wire.send(B00000000);
	Wire.send(threshold);
	Wire.endTransmission();
	if( Wire.I2C_ON && !ACC.isON && RTC.isON!=1){
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
}

WaspSensorEvent_v20 SensorEventv20=WaspSensorEvent_v20();
