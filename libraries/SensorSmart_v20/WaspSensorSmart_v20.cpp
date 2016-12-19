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
 *  Implementation:	Alberto Bielsa, David Cuartielles
 */
 

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspSensorSmart_v20.h"


// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorSmart_v20::WaspSensorSmart_v20()
{
	pinMode(DIGITAL1,INPUT);
	pinMode(DIGITAL2,INPUT);
	pinMode(DIGITAL3,OUTPUT);
	pinMode(DIGITAL4,OUTPUT);
	pinMode(DIGITAL5,OUTPUT);
	pinMode(DIGITAL6,OUTPUT);
	pinMode(DIGITAL7,OUTPUT);
	pinMode(DIGITAL8,OUTPUT);

	digitalWrite(DIGITAL3,HIGH);
	digitalWrite(DIGITAL4,HIGH);
	digitalWrite(DIGITAL5,LOW);
	digitalWrite(DIGITAL6,LOW);
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(DIGITAL8,LOW);
	
	// init power supply to OFF state
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	
	// update Waspmote Control Register
	WaspRegisterSensor |= REG_METERING;
}

// Public Methods //////////////////////////////////////////////////////////////

/*	ON: Calls the setBoardMode function to turn on the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorSmart_v20::ON(void)
{
	setBoardMode(SENS_ON);
}

/*	OFF: Calls the setBoardMode function to turn off the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorSmart_v20::OFF(void)
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
int8_t	WaspSensorSmart_v20::setBoardMode(uint8_t mode)
{
	switch( mode )
	{
		case	SENS_ON 	:	// update I2C flag
								Wire.isBoard = true;
								// switch on the power supplies
								PWR.setSensorPower(SENS_3V3, SENS_ON);
								PWR.setSensorPower(SENS_5V, SENS_ON);
								// Sets RTC on to enable I2C
								if(!RTC.isON) RTC.setMode(RTC_ON, RTC_I2C_MODE);
								break;
								
		case	SENS_OFF	:	// update I2C flag
								Wire.isBoard = false;
								// switch off the power supplies
								PWR.setSensorPower(SENS_3V3, SENS_OFF);
								PWR.setSensorPower(SENS_5V, SENS_OFF);
								break;
		default				:	return 0;
	}
	return 1;
}

/*	setSensorMode: Turns on or off the specified sensor
 *	Parameters:	uint8_t mode 
 * 						- SENS_ON : turn on the sensor
 * 						- SENS_OFF : turn off the sensor
 * 				uint16_t sensor
 * 						- SENS_SMART_LDR : luminosity sensor
 * 						- SENS_SMART_FLOW_5V : flow sensor at 5V socket
 * 						- SENS_SMART_LCELLS_5V : load cell
 * 						- SENS_SMART_LCELLS_10V : load cell
 * 						- SENS_SMART_CURRENT : current clamp
 * 						- SENS_SMART_TEMPERATURE : temperature sensor
 * 						- SENS_SMART_HUMIDITY : humidity sensor
 * 						- SENS_SMART_US_3V3 : ultrasound sensor at 3.3V socket
 * 						- SENS_SMART_FLOW_3V3 : flow sensor at 3.3V socket
 * 						- SENS_SMART_US_5V : ultrasound sensor at 5V socket
 * 						- SENS_SMART_DFS_3V3 : foil sensor at 3.3V socket
 * 						- SENS_SMART_DFS_5V : foil sensor at 5V socket
 *  Return:		uint8_t error
 * 						- 1 : success / no error detected
 * 						- 0 : wrong mode introduced
 * 						- -1 : wrong sensor introduced
 * 
 */
int8_t	WaspSensorSmart_v20::setSensorMode(uint8_t mode, uint16_t sensor)
{
	if( mode==SENS_ON )
	{
		switch( sensor )
		{
			case	SENS_SMART_LDR			:	digitalWrite(DIGITAL8,HIGH);
												break;
			case	SENS_SMART_FLOW_5V		:	digitalWrite(DIGITAL6,HIGH);
												break;
			case	SENS_SMART_LCELLS_5V	:	digitalWrite(DIGITAL3,LOW);
												break;
			case	SENS_SMART_LCELLS_10V	:	digitalWrite(DIGITAL4,LOW);
												break;
			case	SENS_SMART_CURRENT		:	digitalWrite(DIGITAL5,HIGH);
												break;
			case	SENS_SMART_TEMPERATURE	:	digitalWrite(DIGITAL8,HIGH);
												break;
			case	SENS_SMART_HUMIDITY		:	digitalWrite(DIGITAL8,HIGH);
												break;
			case	SENS_SMART_US_3V3		:	digitalWrite(DIGITAL7,HIGH);
												break;
			case	SENS_SMART_DFS_3V3		:	digitalWrite(DIGITAL7,HIGH);
												break;
			case	SENS_SMART_FLOW_3V3		:	digitalWrite(DIGITAL6,HIGH);
												break;
			case	SENS_SMART_US_5V		:	digitalWrite(DIGITAL7,HIGH);
												break;
			case	SENS_SMART_DFS_5V		:	digitalWrite(DIGITAL7,HIGH);
												break;
			case	SENS_SMART_TEMP_DS18B20	:	digitalWrite(DIGITAL8,HIGH);
												break;
			default							:	return -1;
		}
	} else if( mode==SENS_OFF )
	{
		switch( sensor )
		{
			case	SENS_SMART_LDR			:	digitalWrite(DIGITAL8,LOW);
												break;
			case	SENS_SMART_FLOW_5V		:	digitalWrite(DIGITAL6,LOW);
												break;
			case	SENS_SMART_LCELLS_5V	:	digitalWrite(DIGITAL3,HIGH);
												break;
			case	SENS_SMART_LCELLS_10V	:	digitalWrite(DIGITAL4,HIGH);
												break;
			case	SENS_SMART_CURRENT		:	digitalWrite(DIGITAL5,LOW);
												break;
			case	SENS_SMART_TEMPERATURE	:	digitalWrite(DIGITAL8,LOW);
												break;
			case	SENS_SMART_HUMIDITY		:	digitalWrite(DIGITAL8,LOW);
												break;
			case	SENS_SMART_US_3V3		:	digitalWrite(DIGITAL7,LOW);
												break;
			case	SENS_SMART_DFS_3V3		:	digitalWrite(DIGITAL7,LOW);
												break;
			case	SENS_SMART_FLOW_3V3		:	digitalWrite(DIGITAL6,LOW);
												break;
			case	SENS_SMART_US_5V		:	digitalWrite(DIGITAL7,LOW);
												break;
			case	SENS_SMART_DFS_5V		:	digitalWrite(DIGITAL7,LOW);
												break;
			case	SENS_SMART_TEMP_DS18B20	:	digitalWrite(DIGITAL8,LOW);
												break;
			default							:	return -1;
		}
	} else return 0;
	
	return 1;
}


/*	readValue: Calls the readValue function with no type specified
 *	Parameters:	uint16_t sensor
 * 						- SENS_SMART_LDR : luminosity sensor
 * 						- SENS_SMART_LCELLS_5V : load cell
 * 						- SENS_SMART_LCELLS_10V : load cell
 * 						- SENS_SMART_CURRENT : current clamp
 * 						- SENS_SMART_TEMPERATURE : temperature sensor
 * 						- SENS_SMART_HUMIDITY : humidity sensor
 * 						- SENS_SMART_DFS_3V3 : foil sensor at 3.3V socket
 * 						- SENS_SMART_DFS_5V : foil sensor at 5V socket
 *  Return:		float value : value read from the sensor
 * 
 */
float	WaspSensorSmart_v20::readValue(uint16_t sensor)
{
	return readValue(sensor, 0);
}

/*	readValue: 	Reads the specified sensor, including the type if it is a flow
 * 				or ultrasound sensor
 *	Parameters:	uint16_t sensor
 * 						- SENS_SMART_LDR : luminosity sensor
 * 						- SENS_SMART_FLOW_5V : flow sensor at 5V socket
 * 						- SENS_SMART_LCELLS_10V : load cell
 * 						- SENS_SMART_LCELLS_5V : load cell
 * 						- SENS_SMART_CURRENT : current clamp
 * 						- SENS_SMART_TEMPERATURE : temperature sensor
 * 						- SENS_SMART_HUMIDITY : humidity sensor
 * 						- SENS_SMART_US_3V3 : ultrasound sensor at 3.3V socket
 * 						- SENS_SMART_FLOW_3V3 : flow sensor at 3.3V socket
 * 						- SENS_SMART_US_5B : ultrasound sensor at 5V socket
 *						- SENS_SMART_TEMP_DS18B20 : Temperature DS18B20 sensor (only P&S)
 * 				uint8_t type
 * 						- SENS_US_WRA1 : Selects WRA1 ultrasound sensor
 * 						- SENS_US_EZO : Selects EZ0 ultrasound sensor
 * 						- SENS_FLOW_FS100A : Selects FS100A flow sensor
 * 						- SENS_FLOW_FS200A : Selects FS200A flow sensor 
 * 						- SENS_FLOW_FS400A : Selects FS400A flow sensor
 * 						
 *  Return:		float value : value read from the sensor
 * 
 */
float	WaspSensorSmart_v20::readValue(uint16_t sensor, uint8_t type)
{
	int aux=0;
	float value = 0.0;
	
	switch( sensor )
	{
		case SENS_SMART_LDR			:	aux = analogRead(ANALOG5);
										value = ldrConversion(aux);
										break;
		case SENS_SMART_FLOW_5V		:	value = flowReading(DIGITAL1, type);
										break;
		case SENS_SMART_LCELLS_5V	:	aux = analogRead(ANALOG6);
										value = lcellConversion(aux);
										break;
		case SENS_SMART_LCELLS_10V	:	aux = analogRead(ANALOG6);
										value = lcellConversion(aux);
										break;
		case SENS_SMART_CURRENT		:	aux = analogRead(ANALOG1);
										value = currentConversion(aux);
										break;
		case SENS_SMART_TEMPERATURE	:	aux = analogRead(ANALOG4);
										value = temperatureConversion(aux);
										break;
		case SENS_SMART_HUMIDITY	:	aux = analogRead(ANALOG7);
										value = humidityConversion(aux);
										break;
		case SENS_SMART_US_3V3		:	value = ultrasoundConversion(ANALOG3, type);
										break;
		case SENS_SMART_DFS_3V3		:	value = ldReading(ANALOG3);
										break;
		case SENS_SMART_FLOW_3V3	:	value = flowReading(DIGITAL2, type);
										break;
		case SENS_SMART_US_5V		:	value = ultrasoundConversion(ANALOG2, type);
										break;
		case SENS_SMART_DFS_5V		:	value = ldReading(ANALOG2);
										break;
		case SENS_SMART_TEMP_DS18B20:	value=readTempDS1820();
										break;
		default						:	;
	}

	return value;
}



// Private Methods //////////////////////////////////////////////////////////////

/* readTempDS1820() - reads the DS1820 temperature sensor
 *
 * It reads the DS1820 temperature sensor
 */
float WaspSensorSmart_v20::readTempDS1820()
{
	// Select analog 4 as pin to be used
	// 'false' input means that no 3v3 power supply is managed
	// So, the Sensor Board and the sensor switch must be 
	// powered on prior using this function
	return	Utils.readTempDS1820( 17, false );
}
 
/*	ldrConversion: converts the value read at the analog to digital converter
 * 				   into a voltage
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : voltage in the LDR sensor load resistor
 * 
 */
 float WaspSensorSmart_v20::ldrConversion(int readValue)
{
	float ldr = 0;
   
	ldr = float(readValue) * 3.3 / 1023;
      
	return(ldr);
}

/*	ldReading: converts the value read at the analog to digital converter at 
 *	 			the input indicated into a voltage
 *	Parameters:	uint16_t socket : 	input of the analog-to-digital converter to 
 * 									be read
 *  Return:		float value : voltage read in the input indicated by socket
 * 
 */
 float WaspSensorSmart_v20::ldReading(uint16_t socket)
{
	int aux = 0;
	float ld = 0;
   
	aux = analogRead(socket);
   
	if (socket == ANALOG3)
	{
		ld = float(aux) * 3.3 / 1023;
	} else if (socket == ANALOG2)
	{
		ld = float(aux) * 5.5 / 1023;
	}
      
	return(ld);
}

/*	lcellConversion: converts the value read at the analog to digital converter
 *	 				  corresponding to the load cell into a voltage
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : voltage read in the input indicated by socket
 * 
 */
 float WaspSensorSmart_v20::lcellConversion(int readValue)
{
	float lcell = 0;
   
	lcell = float(readValue) * 3.3 / 1023;
      
	return(lcell);
}

/*	currentConversion: converts the value read at the analog to digital converter
 *	 				  corresponding to the current clamp into a current value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : current measured by the clamp in Amperes
 * 
 */
 float WaspSensorSmart_v20::currentConversion(int readValue)
{
	float analog_value = 0;
	float current = 0;
   
	analog_value = float(readValue) * 3.3 / 1023;

	// make conversion depending on the voltage level
	if (analog_value <= 0.1)
	{
		current = analog_value * 38.88;
	}
    if (analog_value > 0.1)
    { 
		current = analog_value * 37.116 ;
	}
      
	return(current);
}

/*	temperatureConversion: converts the value read at the analog to digital
 * 						   converter corresponding to the temperature sensor
 * 						   into a temperature value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
 float WaspSensorSmart_v20::temperatureConversion(int readValue)
{
	float temperature = 0;
   
	temperature = float(readValue) * 3300 / 1023;
   
	temperature = (temperature - 500) / 10;
   
	return(temperature);   
}

/*	humidityConversion: converts the value read at the analog to digital
 * 						 converter corresponding to the humidity sensor
 * 						 into a humidity value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : humidity measured by the sensor in %RH
 * 
 */
 float WaspSensorSmart_v20::humidityConversion(int readValue)
{
	float humidity = 0;
   
	humidity = float(readValue) * 5500 / 1023;
   
	humidity = (humidity - 800) / 31;
   
	return(humidity);
   
}

/*	ultrasoundConversion: reads the analog to digital converter input indicated
 * 						   in socket and converts the value into distance in
 * 						   function of the sensor selected in mode
 *	Parameters:	uint16_t socket : input of the analog-to-digital converter to 
 * 								  be read
 * 				uint8_t model
 * 						- SENS_US_WRA1 : Selects WRA1 ultrasound sensor
 * 						- SENS_US_EZO : Selects EZ0 ultrasound sensor
 *  Return:		float distance : distance measured by the ultrasound sensor in m
 * 								 -1.0 for error in sensor type selection
 * 
 */
 float WaspSensorSmart_v20::ultrasoundConversion(uint16_t socket, uint8_t model)
{
	float distance = 0;
   
	distance = float(analogRead(socket)) * 3300 / 1023;

	switch( model )
	{
		case	SENS_US_WRA1	:	if ( socket == ANALOG3 )
									{
										distance = distance / 3.2;
									} else
									{
										distance = distance / 1.77;
									}
									break;

		case	SENS_US_EZ0		:	if ( socket == ANALOG3 )
									{
										distance = distance / 2.52;
									} else
									{
										distance = distance / 2.31;
									}
									break;
		default					:	distance = -1.0;
									break;
	}

	return(distance);
   
}

/*	flowReading: reads the analog to digital converter input indicated
 * 						   in socket and converts the value into a flow value in
 * 						   function of the sensor selected in mode
 *	Parameters:	uint16_t socket : digital input to be read
 * 				uint8_t model
 * 						- SENS_FLOW_FS100A : Selects FS100A flow sensor
 * 						- SENS_FLOW_FS200A : Selects FS200A flow sensor 
 * 						- SENS_FLOW_FS400A : Selects FS400A flow sensor
 * 						- SENS_FLOW_YFS401 : Selects YFS401 flow sensor
 * 						- SENS_FLOW_FS300 : Selects FS300 flow sensor 
 * 						- SENS_FLOW_YFG1 : Selects YFG1 flow sensor
 *
 *  Return:		float flow : flow measured by the sensor in liters/minute
 * 							 -1.0 for error in sensor type selection
 * 
 */
 float WaspSensorSmart_v20::flowReading(int socket, uint8_t model)
{
	float flow = 0.0;
	int value = 0;
	long start = 0;
	int previous_reading = 0;
	int reading = 0;
	
	// Measure flow sensor pulses during 1 second, to obtain pulses per second.
	start = millis();
	while( (millis() - start) <= 1000 )
	{
		previous_reading = reading;
		reading = digitalRead(socket);
		
		if((previous_reading == 1) && (reading == 0))
		{
		value++;
		}
		
		// to avoid millis overflow
		if (millis() < start) start = millis();	
	}
	
	delay(100);

	/* Now calculate the liters per minute magnitude, depending on the flow sensor used.
	 * Example:  Flow sensor FS200A has 450 pulses/liter, so:
	 * 
	 * flow [liters/minute] = value [pulses/second] / (450 [pulses / liter] / 60 )
	 * 
	 * flow = value / (450/60) = value / 7.5
	 * 
	 * Note: FS100A has 3900 pulses/liter. FS400 has 390 pulses/liter
	 */
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

		case SENS_FLOW_FS300	:	flow = float(value) / 5.4;
									break;

		case SENS_FLOW_YFG1		:	flow = float(value) / 1.85;
									break;

		default 				:	flow = -1.0;
									break;
	}

	return flow;
}

WaspSensorSmart_v20 SensorSmartv20=WaspSensorSmart_v20();
