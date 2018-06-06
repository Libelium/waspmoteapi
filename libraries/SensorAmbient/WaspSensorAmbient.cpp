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
 *  Version:		3.4
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, Manuel Calahorra, Yuri Carmona, Jorge Casanova, Javier Siscart
 *
 * 	Based on K. Townsend Library.
 *
 */

#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "WaspSensorAmbient.h"

// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 *
 */
WaspSensorAmbient::WaspSensorAmbient()
{
	pinMode(SENS_AMBIENT_LDR_PWR, OUTPUT);
	pinMode(SENS_AMBIENT_SENSIRION_PWR,OUTPUT);
	pinMode(SENS_AMBIENT_SENSIRION_GND,OUTPUT);
	pinMode(SENS_AMBIENT_SENSIRION_CLK,OUTPUT);
	pinMode(SENS_AMBIENT_SENSIRION_DATA, OUTPUT);
	pinMode(SENS_AMBIENT_LDR_GND, OUTPUT);

	digitalWrite(SENS_AMBIENT_LDR_PWR,LOW);
	digitalWrite(SENS_AMBIENT_SENSIRION_PWR,LOW);
	digitalWrite(SENS_AMBIENT_SENSIRION_GND,LOW);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK,LOW);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA,LOW);
	digitalWrite(SENS_AMBIENT_LDR_GND,LOW);

	WaspRegisterSensor |= REG_AMBIENT;
}

// Private Methods //////////////////////////////////////////////////////////////


/*
 Function: Read the sensirion temperature
 Returns: float temperature in ºC
 Parameters:
 Values:
*/
float WaspSensorAmbient::readSensirionTemperature(void)
{
	float temperature;

	temperature = readSensirion(SENS_AMBIENT_TEMPERATURE);

	return temperature;
}

/*
 Function: Read the sensirion humidity
 Returns: float humidity value
 Parameters:
 Values:
*/
float WaspSensorAmbient::readSensirionHumidity(void)
{
	float humidity;

	humidity = readSensirion(SENS_AMBIENT_HUMIDITY);

	return humidity;

}

/*
 Function: Read the LDR sensor
 Returns: Return luminosity in Volts
 Parameters:
 Values:
*/
float WaspSensorAmbient::readLDR(void)
{
	float luminosity;
	int aux;

	// LDR is powered at 3V3 with a 10K pull down. The ADC is 10 bits
	aux = analogRead(ANALOG6);
	luminosity = 3.3*aux/1023;

	// The conversion to R (Ohms) would be R = (3V3/V) -1) * 10K

	return luminosity;
}

/*	readSensirion: reads the temperature or humidity value from the Sensirion
 * 				   digital temperature and humidity sensor
 *	Parameters: uint8_t parameter
 * 						- SENS_AMBIENT_TEMPERATURE
 * 						- SENS_AMBIENT_HUMIDITY
 *  Return:	float value : temperature (ºC) or humidity (%RH) value
 * 						  out of range values if connection problem
 *
 */
float WaspSensorAmbient::readSensirion(uint8_t parameter)
{
	int ack = 0;
	int val_read = 0;
	unsigned long a = 0;

	const byte HUMIDITY = B00000101;
	const byte TEMPERATURE = B00000011;


	if( parameter==SENS_AMBIENT_TEMPERATURE )
	{
		parameter=TEMPERATURE;
	}
	else if( parameter==SENS_AMBIENT_HUMIDITY )
	{
		parameter=HUMIDITY;
	}
	else return 0;

	//*************************************
	// First Transmission cycle (START)

	pinMode(SENS_AMBIENT_SENSIRION_DATA,  OUTPUT);
	pinMode(SENS_AMBIENT_SENSIRION_CLK, OUTPUT);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA,  HIGH);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, HIGH);
	delayMicroseconds(1);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA,  LOW);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, LOW);
	delayMicroseconds(1);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, HIGH);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA,  HIGH);
	delayMicroseconds(1);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, LOW);

	//***************************************
	// Write the command (3 first bits: always 000, last five bits: command)

	//parameter: B00000011 for temperature and B00000101 for humidity
	shiftOut(SENS_AMBIENT_SENSIRION_DATA, SENS_AMBIENT_SENSIRION_CLK, MSBFIRST, parameter);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, HIGH);
	pinMode(SENS_AMBIENT_SENSIRION_DATA, INPUT);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA, HIGH);

	a = millis();
	ack = digitalRead(SENS_AMBIENT_SENSIRION_DATA);
	while((ack == HIGH)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_AMBIENT_SENSIRION_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}

	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, LOW);

	a = millis();
	ack = digitalRead(SENS_AMBIENT_SENSIRION_DATA);
	while((ack == LOW)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_AMBIENT_SENSIRION_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}

	//****************************************
	//Wait for a complete conversion

	ack = digitalRead(SENS_AMBIENT_SENSIRION_DATA);
	a = millis();
	while((ack == HIGH)&&((millis()-a)<400))
	{
		ack = digitalRead(SENS_AMBIENT_SENSIRION_DATA);
	}

	//*****************************************
	//Read the 8 most significative bits

	a = millis();
	for(int i = 0; i < 8; i++)
	{
		digitalWrite(SENS_AMBIENT_SENSIRION_CLK, HIGH);
		val_read = (val_read * 2) + digitalRead(SENS_AMBIENT_SENSIRION_DATA);
		digitalWrite(SENS_AMBIENT_SENSIRION_CLK, LOW);
	}

	ack = digitalRead(SENS_AMBIENT_SENSIRION_DATA);
	a = millis();
	while((ack == LOW)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_AMBIENT_SENSIRION_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}

	//****************************************
	//ACK from the  microcontroller
	pinMode(SENS_AMBIENT_SENSIRION_DATA, OUTPUT);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA, LOW);
	delayMicroseconds(1);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, HIGH);
	delayMicroseconds(400);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, LOW);
	pinMode(SENS_AMBIENT_SENSIRION_DATA, INPUT);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA, HIGH);

	//***************************************
	//Read the 8 least significative bits
	a = millis();
	for(int i = 0; i < 8; i++)
	{
		digitalWrite(SENS_AMBIENT_SENSIRION_CLK, HIGH);
		val_read = val_read * 2 + digitalRead(SENS_AMBIENT_SENSIRION_DATA);
		digitalWrite(SENS_AMBIENT_SENSIRION_CLK, LOW);
	}


	//**************************************
	//CRC not taken into account
	pinMode(SENS_AMBIENT_SENSIRION_DATA, OUTPUT);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA, HIGH);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, HIGH);
	delayMicroseconds(400);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, LOW);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA, LOW);

	if( parameter==TEMPERATURE )
	{
		return temperatureConversion(val_read,SENS_PREC_HIGH);
	}
	else if( parameter==HUMIDITY )
	{
		return humidityConversion(val_read,SENS_PREC_HIGH);
	}
	else return 0;
}

/*	temperatureConversion: converts the value read from the Sensirion into a
 * 						   temperature value in ºC
 *	Parameters:	int readValue : value read from the Sensirion
 * 				int precision : format at which the sensor was read
 *  Return:		float value : temperature measured by the sensor in ºC
 *
 */
float WaspSensorAmbient::temperatureConversion(int readValue, int precision)
{
	float temperature = 0;
	float d1 = -39.7;
	float d2 = 0;

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
float WaspSensorAmbient::humidityConversion(int readValue, int precision)
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

	// in case of saturation
	if( humidity > 99.0 )
	{
		humidity = 100.0;
	}

	return(humidity);
}



// Public Methods //////////////////////////////////////////////////////////////

/*	setSensorMode: It sets ON/OFF the different sensor switches
 *	Parameters:	uint8_t mode
 * 						- SENS_ON : turn on the sensor
 * 						- SENS_OFF : turn off the sensor
 * 				uint16_t sensor
 * 							- SENS_AMBIENT_TEMPERATURE : Temperature Sensor
 * 							- SENS_AMBIENT_HUMIDITY : Humidity Sensor
 * 							- SENS_AMBIENT_LDR : Luminosity Sensor
 *  Return:		int8_t error
 * 						1 : success
 * 						0 : wrong mode selected
 * 						-1: wrong sensor selected
 *
 */
int8_t	WaspSensorAmbient::setSensorMode(uint8_t mode, uint16_t sensor)
{
	if( mode==SENS_ON )
	{
		switch( sensor )
		{
			case	SENS_AMBIENT_LDR		:	digitalWrite(SENS_AMBIENT_LDR_PWR,HIGH);
												break;
			case	SENS_AMBIENT_TEMPERATURE:	digitalWrite(SENS_AMBIENT_SENSIRION_PWR,HIGH);
												break;
			case	SENS_AMBIENT_HUMIDITY	:	digitalWrite(SENS_AMBIENT_SENSIRION_PWR,HIGH);
												break;								
			case	SENS_AMBIENT_LUX		:	// switch on the power supplies
												PWR.setSensorPower(SENS_3V3, SENS_ON);
												break;
			default						:	return -1;
		}
	} else if( mode==SENS_OFF )
	{
		switch( sensor )
		{
			case	SENS_AMBIENT_LDR		:	digitalWrite(SENS_AMBIENT_LDR_PWR,LOW);
												break;
			case	SENS_AMBIENT_TEMPERATURE:	digitalWrite(SENS_AMBIENT_SENSIRION_PWR,LOW);
												break;
			case	SENS_AMBIENT_HUMIDITY	:	digitalWrite(SENS_AMBIENT_SENSIRION_PWR,LOW);
												break;
			case	SENS_AMBIENT_LUX	:		// switch off the power supplies
												PWR.setSensorPower(SENS_3V3, SENS_OFF);
												break;
			default							:	return -1;
		}
	} else return 0;

	return 1;
}

/*	readValue: read the corresponding sensor.
 *
 *	Parameters:	uint16_t sensor
 * 						- SENS_AMBIENT_TEMPERATURE
 * 						- SENS_AMBIENT_HUMIDITY
 * 						- SENS_AMBIENT_LDR
 * 						- SENS_AMBIENT_LUX
 *  Return:		float value : value of the read sensor.
 *
 */
float	WaspSensorAmbient::readValue(uint8_t sensor)
{
	float aux=0;
	switch( sensor )
	{
		case	SENS_AMBIENT_TEMPERATURE	:	aux = readSensirionTemperature();
		break;

		case	SENS_AMBIENT_HUMIDITY		:	aux = readSensirionHumidity();
		break;

		case	SENS_AMBIENT_LDR			:	aux = readLDR();
		break;

		case	SENS_AMBIENT_LUX			:	aux = TSL.getLuminosity(TSL2561_HIGH_RES, TSL2561_GAIN_1);
		break;

		default							:	return -1.0;
	}

	return	aux;
}





/*	getTemperature:
 *
 */
float WaspSensorAmbient::getTemperature()
{
	float value = 0;

	setSensorMode(SENS_ON, SENS_AMBIENT_TEMPERATURE);
	delay(100);
	value = readValue(SENS_AMBIENT_TEMPERATURE);
	setSensorMode(SENS_OFF, SENS_AMBIENT_TEMPERATURE);

	return value;
}



/*	getHumidity:
 *
 */
float WaspSensorAmbient::getHumidity()
{
	float value = 0;

	setSensorMode(SENS_ON, SENS_AMBIENT_HUMIDITY);
	delay(100);
	value = readValue(SENS_AMBIENT_HUMIDITY);
	setSensorMode(SENS_OFF, SENS_AMBIENT_HUMIDITY);

	return value;
}


/*	getLuminosity:
 *
 */
float WaspSensorAmbient::getLuminosity()
{
	float value = 0;

	setSensorMode(SENS_ON, SENS_AMBIENT_LDR);
	// dummy reading
	readValue(SENS_AMBIENT_LDR);
	value = readValue(SENS_AMBIENT_LDR);
	setSensorMode(SENS_OFF, SENS_AMBIENT_LDR);

	return value;
}

/*!
 * @brief 	This function performs a lux measurement
 * @return 	luxes if ok
 * 			-1 if error
 */
uint32_t WaspSensorAmbient::getLuxes()
{
  return getLuxes(TSL2561_GAIN_1, TSL2561_HIGH_RES);

}

/*!
 * @brief 	This function performs a lux measurement
 * @return 	luxes if ok
 * 			-1 if error
 */
uint32_t WaspSensorAmbient::getLuxes(bool gain)
{
  return getLuxes(gain, TSL2561_HIGH_RES);
}


/*!
 * @brief 	This function performs a lux measurement
 * @param   Gain: INDOOR, OUTDOOR
 *          Resolution: TSL2561_HIGH_RES, TSL2561_MED_RES, TSL2561_LOW_RES
 * @return 	luxes if ok
 * 			    -1 if error
 */
uint32_t WaspSensorAmbient::getLuxes(bool gain, uint8_t res)
{
	uint8_t error;
	
	// switch on the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_ON);
	TSL.ON();

	error = TSL.getLuminosity(res, gain);

	// switch off the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_OFF);

	if (error == 0)
	{
		return TSL.lux;
	}
	else{
		return (uint32_t)-1;
	}
}



/*	getTemperatureBME: get temperature from BME280 sensor
 *
 */
float WaspSensorAmbient::getTemperatureBME()
{
	float value = 0;

	// switch on the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_ON);

	// Configure the BME280 Sensor (Temperature, Humidity and Pressure)
	BME.ON();
	delay(100);

	value = BME.getTemperature(BME280_OVERSAMP_1X, 0);
	delay(100);

	// switch off the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_OFF);

	// Read the temperature from the BME280 Sensor
	return value;
}



/*	getPressureBME: get pressure from BME280 sensor
 *
 */
float WaspSensorAmbient::getPressureBME()
{
	float value = 0;

	// switch on the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_ON);

	//Configure the BME280 Sensor (Temperature, Humidity and Pressure)
	BME.ON();
	delay(100);

	// Read the pressure from the BME280 Sensor
	value = BME.getPressure(BME280_OVERSAMP_1X, 0);
	delay(100);

	// switch off the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_OFF);

	// Read the temperature from the BME280 Sensor
	return value;
}



/*	getHumidityBME: get humidity from BME280 sensor
 *
 */
float WaspSensorAmbient::getHumidityBME()
{
	float value = 0;

	// switch on the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_ON);

	//Configure the BME280 Sensor (Temperature, Humidity and Pressure)
	BME.ON();
	delay(100);

	// Read the humidity from the BME280 Sensor
	value = BME.getHumidity(BME280_OVERSAMP_1X);
	
	delay(100);		

	// switch off the power supplies
	PWR.setSensorPower(SENS_3V3, SENS_OFF);

	// Read the temperature from the BME280 Sensor
	return value;
}


WaspSensorAmbient SensorAmbient=WaspSensorAmbient();
