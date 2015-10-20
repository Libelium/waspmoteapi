/*
 *  Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
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
		
	digitalWrite(DIGITAL0,LOW);
	digitalWrite(DIGITAL2,LOW);
	digitalWrite(DIGITAL3,LOW);
	digitalWrite(DIGITAL4,LOW);
	digitalWrite(DIGITAL6,LOW);
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(DIGITAL8,LOW);
		
	// init power supply to OFF state
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	
	// update Waspmote Control Register
	WaspRegister |= REG_EVENTS;
	
	// init interruption attribute flag 
	_intEnabled = false;
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
		case	SENS_ON :	// update I2C flag
							Wire.isBoard = true;
							// switch on the power supplies
							PWR.setSensorPower(SENS_3V3, SENS_ON);
							// Sets RTC on to enable I2C
							if(!RTC.isON) RTC.setMode(RTC_ON, RTC_I2C_MODE);
							break;
							
		case	SENS_OFF:	// update I2C flag
							Wire.isBoard = false;
							// switch on the power supplies
							PWR.setSensorPower(SENS_3V3, SENS_OFF);
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
		case	SENS_SOCKET1	:	setDigipot1(I2C_ADDRESS_EVENTS_DIGIPOT1,threshold);
									break;
		case	SENS_SOCKET2	:	setDigipot0(I2C_ADDRESS_EVENTS_DIGIPOT1,threshold);
									break;
		case	SENS_SOCKET3	:	setDigipot0(I2C_ADDRESS_EVENTS_DIGIPOT2,threshold);
									break;
		case	SENS_SOCKET4	:	setDigipot1(I2C_ADDRESS_EVENTS_DIGIPOT2,threshold);
									break;
		case	SENS_SOCKET5	:	setDigipot0(I2C_ADDRESS_EVENTS_DIGIPOT3,threshold);
									break;
		case	SENS_SOCKET6	:	setDigipot1(I2C_ADDRESS_EVENTS_DIGIPOT3,threshold);
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
	// variable to read sensors
	int aux = 0;
	
	// get actual interruption state flag
	bool isEnabled = _intEnabled;
	
	// disable interruption
	detachInt();
	
	switch( sensor )
	{
		case	SENS_SOCKET1	:	aux = analogRead(ANALOG1);
									break;
		case	SENS_SOCKET2	:	aux = analogRead(ANALOG2);
									break;
		case	SENS_SOCKET3	:	aux = analogRead(ANALOG4);
									break;
		case	SENS_SOCKET4	:	aux = analogRead(ANALOG3);
									break;
		case	SENS_SOCKET5	:	aux = analogRead(ANALOG6);
									break;
		case	SENS_SOCKET6	:	aux = analogRead(ANALOG7);
									break;
		case	SENS_SOCKET7	:	aux = digitalRead(DIGITAL5);	
									// re-enable interruption if needed
									if( isEnabled == true )
									{										
										delay(50);
										attachInt();
									}
									return aux;
									break;
		case	SENS_SOCKET8	:	aux = analogRead(ANALOG5);
									break;
		default					:	aux = -1;
	}
	
	// re-enable interruption if needed
	if( isEnabled == true )
	{	
		delay(50);
		attachInt();
	}
	
	if( aux == -1 )
	{
		return (float)-1.0;
	}
	
	// perform conversion
	float value = ((float)aux * 3.3)/1023.0;
	
	return	value;
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
		case 	SENS_FLOW_FS200	:	
		case 	SENS_FLOW_FS400	:	
		case 	SENS_FLOW_YFS401 :	
		case 	SENS_FLOW_FS300	:	
		case 	SENS_FLOW_YFG1	:	aux = flowReading(type);
									break;
		case 	SENS_TEMPERATURE:	if(sensor == SENS_SENSIRION)
									{
										aux = readSensirion(SENSIRION_TEMP);
									} else
									{
										aux = readValue(sensor);
										aux = ( aux - 0.5 )* 100;
									}
									break;
		case 	SENS_HUMIDITY	:	if(sensor == SENS_SENSIRION)
									{
										aux = readSensirion(SENSIRION_HUM);
									} else
									{
										aux = readValue(sensor);
										aux = aux * 100 / 3;
									}
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
	_intEnabled = true;
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
	_intEnabled = false;
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
 * 						- SENS_FLOW_YFS401 : Selects YFS401 flow sensor
 * 						- SENS_FLOW_FS300 : Selects FS300 flow sensor 
 * 						- SENS_FLOW_YFG1 : Selects YFG1 flow sensor
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
	  if( millis() < start )
	  {
		  value = 0;
		  start = millis();
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

		case SENS_FLOW_YFS401	:	flow = float(value) / 96;
									break;

		case SENS_FLOW_FS300	:	flow = float(value) / 5.5;
									break;

		case SENS_FLOW_YFG1		:	flow = float(value) / 1.85;
									break;

		default 				:	flow = -1.0;
									break;
	}

	return flow;
}


/*	readSensirion: reads the temperature or humidity value from the Sensirion
 * 				   digital temperature and humidity sensor
 *	Parameters: uint8_t parameter
 * 						- SENS_TEMPERATURE
 * 						- SENS_HUMIDITY
 *  Return:	float value : temperature (ºC) or humidity (%RH) value
 * 						  out of range values if connection problem
 * 
 */
float WaspSensorEvent_v20::readSensirion(uint8_t parameter)
{
	int ack = 0;
	int val_read = 0;
	int ack2, ack3, i = 0;
	long a = 0;
	long b = 0;
	
	const byte HUMIDITY = B00000101;
	const byte TEMPERATURE = B00000011;
	
	

	if( parameter==SENSIRION_TEMP ) parameter=TEMPERATURE;
	else if( parameter==SENSIRION_HUM ) parameter=HUMIDITY;
		
  //************************************* 
  // First Transmission cycle (START)
  
	pinMode(SENS_SENSIRION_DATA,  OUTPUT);
	pinMode(SENS_SENSIRION_CLK, OUTPUT);
	digitalWrite(SENS_SENSIRION_DATA,  HIGH);
	digitalWrite(SENS_SENSIRION_CLK, HIGH);
	delayMicroseconds(1);
	digitalWrite(SENS_SENSIRION_DATA,  LOW);
	digitalWrite(SENS_SENSIRION_CLK, LOW);
	delayMicroseconds(1);
	digitalWrite(SENS_SENSIRION_CLK, HIGH);
	digitalWrite(SENS_SENSIRION_DATA,  HIGH);
	delayMicroseconds(1);
	digitalWrite(SENS_SENSIRION_CLK, LOW);

  //***************************************
  // Write the command (3 first bits: always 000, last five bits: command)

	//parameter: B00000011 for temperature and B00000101 for humidity
	shiftOut(SENS_SENSIRION_DATA, SENS_SENSIRION_CLK, MSBFIRST, parameter);  
	digitalWrite(SENS_SENSIRION_CLK, HIGH);
	pinMode(SENS_SENSIRION_DATA, INPUT);
	digitalWrite(SENS_SENSIRION_DATA, HIGH);

	a = millis();
	ack = digitalRead(SENS_SENSIRION_DATA);
	while((ack == HIGH)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_SENSIRION_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}

	digitalWrite(SENS_SENSIRION_CLK, LOW);

	a = millis();
	ack = digitalRead(SENS_SENSIRION_DATA);
	while((ack == LOW)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_SENSIRION_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}
  
  //****************************************
  //Wait for a complete conversion
  
	ack = digitalRead(SENS_SENSIRION_DATA);
	a = millis();
	while((ack == HIGH)&&((millis()-a)<400))
	{
		ack = digitalRead(SENS_SENSIRION_DATA);
	}
 
  //*****************************************
  //Read the 8 most significative bits

	a = millis();
	for(int i = 0; i < 8; i++)
	{
		digitalWrite(SENS_SENSIRION_CLK, HIGH);
		val_read = (val_read * 2) + digitalRead(SENS_SENSIRION_DATA);
		digitalWrite(SENS_SENSIRION_CLK, LOW);
	}
  
	ack = digitalRead(SENS_SENSIRION_DATA);
	a = millis();
	while((ack == LOW)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_SENSIRION_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}
  
  //****************************************
  //ACK from the  microcontroller
	pinMode(SENS_SENSIRION_DATA, OUTPUT);
	digitalWrite(SENS_SENSIRION_DATA, LOW);
	delayMicroseconds(1);
	digitalWrite(SENS_SENSIRION_CLK, HIGH);
	delayMicroseconds(400);
	digitalWrite(SENS_SENSIRION_CLK, LOW);
	pinMode(SENS_SENSIRION_DATA, INPUT);
	digitalWrite(SENS_SENSIRION_DATA, HIGH);
   
  //***************************************
  //Read the 8 least significative bits
	a = millis();
	for(int i = 0; i < 8; i++)
	{
		digitalWrite(SENS_SENSIRION_CLK, HIGH);
		val_read = val_read * 2 + digitalRead(SENS_SENSIRION_DATA);
		digitalWrite(SENS_SENSIRION_CLK, LOW);
	}
	b = millis()-a;

  
  //**************************************
  //CRC not taken into account
  
	pinMode(SENS_SENSIRION_DATA, OUTPUT);
	digitalWrite(SENS_SENSIRION_DATA, HIGH);
	digitalWrite(SENS_SENSIRION_CLK, HIGH);
	delayMicroseconds(400);
	digitalWrite(SENS_SENSIRION_CLK, LOW);
	
	digitalWrite(SENS_SENSIRION_DATA, LOW);
  
	if( parameter==TEMPERATURE ) return temperatureConversion(val_read,SENS_PREC_HIGH);
	else if( parameter==HUMIDITY ) return humidityConversion(val_read,SENS_PREC_HIGH);
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

/*	temperatureConversion: converts the value read from the Sensirion into a
 * 						   temperature value
 *	Parameters:	int readValue : value read from the Sensirion
 * 				int precision : format at which the sensor was read
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
float WaspSensorEvent_v20::temperatureConversion(int readValue, int precision)
{
	float temperature = 0;
	float d1 = -39.7;
	float d2 = 0;
	
	float aux=0;
  
	switch(precision)
	{
		case SENS_PREC_HIGH:    d2 = 0.01;
					temperature = d1 + (d2 * float(readValue));
					break;    
		case SENS_PREC_LOW:     d2 = 0.04;
					temperature = d1 + (d2 * float(readValue));
					break;
	}
  
	return(temperature);
}
/*	humidityConversion: converts the value read from the Sensirion into a
 * 						humidity value
 *	Parameters:	int readValue : value read from the Sensirion
 * 				int precision : format at which the sensor was read
 *  Return:		float value : humidity measured by the sensor in %RH
 *  
 */
float WaspSensorEvent_v20::humidityConversion(int readValue, int precision)
{
	float humidity = 0;
	float c1 = -2.0468;
	float c2 = 0;
	float c3 = 0;
  
	switch(precision)
	{
		case SENS_PREC_HIGH	:	c2 = 0.0367;
								c3 = -1.5955e-6;
								humidity = c1 + (c2 * float(readValue)) 
										   + (c3 * float(readValue) * float(readValue));
								break;

		case SENS_PREC_LOW	:	c2 = 0.5872;
								c3 = -4.0845e-4;
								humidity = c1 + (c2 * float(readValue))
										   + (c3 * float(readValue) * float(readValue));
								break;
		default			  	:	;
	}
  
	//in case of saturation
	if( humidity > 99.0 )
	{
		humidity = 100.0;
	}
	
	return(humidity);
}
WaspSensorEvent_v20 SensorEventv20=WaspSensorEvent_v20();
