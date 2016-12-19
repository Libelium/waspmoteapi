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
 *  Implementation:	Alberto Bielsa, Manuel Calahorra, Yuri Carmona
 */


#ifndef __WPROGRAM_H__
#include <WaspClasses.h>
#endif

#include "WaspSensorAgr_v20.h"

// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorAgr_v20::WaspSensorAgr_v20()
{	
	pinMode(DIGITAL8,OUTPUT);
	pinMode(DIGITAL7,OUTPUT);
	pinMode(DIGITAL6,OUTPUT);
	pinMode(DIGITAL5,OUTPUT);
	pinMode(DIGITAL4,INPUT);
	pinMode(DIGITAL3,OUTPUT);
	pinMode(DIGITAL2,INPUT);	
	pinMode(DIGITAL1,OUTPUT);	
	pinMode(ANA0,OUTPUT);
	pinMode(15, INPUT);
	pinMode(17, INPUT);
	pinMode(19, INPUT);
	
	digitalWrite(DIGITAL8,LOW);
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(DIGITAL6,LOW);
	digitalWrite(DIGITAL5,LOW);
	digitalWrite(DIGITAL3,LOW);
	digitalWrite(DIGITAL1,LOW);
	digitalWrite(ANA0,LOW);
		
	// init power supply to OFF state
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	
	// clear array
	memset( plv_array, 0x00, sizeof(plv_array) );	
	
	// update Waspmote Control Register
	WaspRegisterSensor |= REG_AGRICULTURE;
}

// Public Methods //////////////////////////////////////////////////////////////

/*	ON: Calls the setBoardMode function to turn on the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::ON(void)
{
	setBoardMode(SENS_ON);	
}

/*	OFF: Calls the setBoardMode function to turn off the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::OFF(void)
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
int8_t	WaspSensorAgr_v20::setBoardMode(uint8_t mode)
{
	
	switch( mode )
	{
		case	SENS_ON :	// update I2C flag
							Wire.isBoard = true;
							// switch on the power supplies
							PWR.setSensorPower(SENS_3V3, SENS_ON);
							PWR.setSensorPower(SENS_5V, SENS_ON);
							// Sets RTC on to enable I2C
							if(!RTC.isON) RTC.setMode(RTC_ON, RTC_I2C_MODE);
							digitalWrite(DIGITAL5,HIGH);
							break;
							
		case	SENS_OFF:	// update I2C flag
							Wire.isBoard = false;
							// switch off the power supplies
							PWR.setSensorPower(SENS_3V3, SENS_OFF);
							PWR.setSensorPower(SENS_5V, SENS_OFF);
							digitalWrite(DIGITAL5,LOW);
							break;
		default			:	return 0;
	}
	
	return 1;
}

/*	setSensorMode: It sets ON/OFF the different sensor switches
 *	Parameters:	uint8_t mode 
 * 						- SENS_ON : turn on the sensor
 * 						- SENS_OFF : turn off the sensor
 * 				uint16_t sensor
 * 							- SENS_AGR_PRESSURE : Atmospheric Pressure Sensor
 * 							- SENS_AGR_WATERMARK1 : Soil Moisture 1 Sensor
 * 							- SENS_AGR_WATERMARK2 : Soil Moisture 2 Sensor
 * 							- SENS_AGR_WATERMARK3 : Soil Moisture 3 Sensor
 * 							- SENS_AGR_ANEMOMETER : Weather Station Sensor
 * 							- SENS_AGR_VANE : Weather Station Sensor
 * 							- SENS_AGR_DENDROMETER : Trunk diameter Sensor
 *	 						- SENS_AGR_PT100 : Soil temperature Sensor
 * 							- SENS_AGR_LEAF_WETNESS : Leaf wetness Sensor
 * 							- SENS_AGR_TEMPERATURE : Temperature Sensor
 * 							- SENS_AGR_HUMIDITY : Humidity Sensor
 * 							- SENS_AGR_RADIATION : Solar radiation Sensor
 * 							- SENS_AGR_SENSIRION : Humidity and temperature Sensor
 * 							- SENS_AGR_LDR : Luminosity Sensor
 * 							- SENS_AGR_TEMP_DS18B20 : Temperature DS18B20 sensor (Only P&S!)
 *  Return:		int8_t error
 * 						1 : success
 * 						0 : wrong mode selected
 * 						-1: wrong sensor selected
 * 
 */
int8_t	WaspSensorAgr_v20::setSensorMode(uint8_t mode, uint16_t sensor)
{	
	if( mode==SENS_ON )
	{
		switch( sensor )
		{
			case	SENS_AGR_PRESSURE	:	digitalWrite(SENS_SWITCH_1,HIGH);
											break;
			case	SENS_AGR_WATERMARK_1:	digitalWrite(SENS_SWITCH_2,HIGH);
											break;
			case	SENS_AGR_WATERMARK_2:	digitalWrite(SENS_SWITCH_2,HIGH);
											break;
			case	SENS_AGR_WATERMARK_3:	digitalWrite(SENS_SWITCH_2,HIGH);
											break;				
			case	SENS_AGR_ANEMOMETER	:	digitalWrite(SENS_SWITCH_3,HIGH);
											break;
			case	SENS_AGR_VANE		:	digitalWrite(SENS_SWITCH_3,HIGH);
											break;
			case	SENS_AGR_DENDROMETER:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			case	SENS_AGR_PT1000		:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			case	SENS_AGR_LEAF_WETNESS:	digitalWrite(SENS_SWITCH_4,HIGH);
											digitalWrite(SENS_MUX_SEL,HIGH);
											break;
			case	SENS_AGR_TEMPERATURE:	digitalWrite(SENS_SWITCH_4,HIGH);
											digitalWrite(SENS_MUX_SEL,HIGH);
											break;
			case	SENS_AGR_HUMIDITY	:	digitalWrite(SENS_SWITCH_4,HIGH);
											digitalWrite(SENS_MUX_SEL,HIGH);
											break;
			case	SENS_AGR_RADIATION	:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			case	SENS_AGR_SENSIRION	:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			case	SENS_AGR_LDR		:	digitalWrite(SENS_SWITCH_4,HIGH);
											break;
			case	SENS_AGR_TEMP_DS18B20:	digitalWrite(SENS_SWITCH_4,HIGH);
											digitalWrite(SENS_MUX_SEL,HIGH);
											break;
			default						:	return -1;
		}
	} else if( mode==SENS_OFF )
	{
		switch( sensor )
		{
			case	SENS_AGR_PRESSURE	:	digitalWrite(SENS_SWITCH_1,LOW);
											break;
			case	SENS_AGR_WATERMARK_1:	digitalWrite(SENS_SWITCH_2,LOW);
											break;
			case	SENS_AGR_WATERMARK_2:	digitalWrite(SENS_SWITCH_2,LOW);
											break;
			case	SENS_AGR_WATERMARK_3:	digitalWrite(SENS_SWITCH_2,LOW);
											break;				
			case	SENS_AGR_ANEMOMETER	:	digitalWrite(SENS_SWITCH_3,LOW);
											break;
			case	SENS_AGR_VANE		:	digitalWrite(SENS_SWITCH_3,LOW);
											break;
			case	SENS_AGR_DENDROMETER:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_PT1000		:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_LEAF_WETNESS:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_TEMPERATURE:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_HUMIDITY	:	digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_RADIATION:		digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_SENSIRION:		digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_LDR:			digitalWrite(SENS_SWITCH_4,LOW);
											break;
			case	SENS_AGR_TEMP_DS18B20:  digitalWrite(SENS_SWITCH_4,LOW);
											break;
			default						:	return -1;
		}
	} else return 0;
	
	return 1;
}

/*	readValue: Calls the readValue function with no type specified
 *	Parameters:	uint16_t sensor
 * 							- SENS_AGR_PRESSURE : Atmospheric Pressure Sensor
 * 							- SENS_AGR_WATERMARK1 : Soil Moisture 1 Sensor
 * 							- SENS_AGR_WATERMARK2 : Soil Moisture 2 Sensor
 * 							- SENS_AGR_WATERMARK3 : Soil Moisture 3 Sensor
 * 							- SENS_AGR_ANEMOMETER : Anemometer Sensor
 * 							- SENS_AGR_VANE : Vane Sensor
 * 							- SENS_AGR_PLUVIOMETER : Pluviometer Sensor
 * 							- SENS_AGR_DENDROMETER : Trunk diameter Sensor
 *	 						- SENS_AGR_PT100 : Soil temperature Sensor
 * 							- SENS_AGR_LEAF_WETNESS : Leaf wetness Sensor
 * 							- SENS_AGR_TEMPERATURE : Temperature Sensor
 * 							- SENS_AGR_HUMIDITY : Humidity Sensor
 * 							- SENS_AGR_RADIATION : Solar radiation Sensor
 * 							- SENS_AGR_LDR : Luminosity Sensor
 * 							- SENS_AGR_TEMP_DS18B20 : Temperature DS18B20 sensor (only P&S!)
 *  Return:		float value : value read from the sensor
 * 
 */
float	WaspSensorAgr_v20::readValue(uint16_t sensor)
{
	return readValue(sensor,0);
}

/*	readValue: Reads the analog to digital converter input indicated of the given
 * 			   sensor socket and converts the value into the proper units
 *	Parameters:	uint16_t sensor
 * 							- SENS_AGR_PRESSURE : Atmospheric Pressure Sensor
 * 							- SENS_AGR_WATERMARK1 : Soil Moisture 1 Sensor
 * 							- SENS_AGR_WATERMARK2 : Soil Moisture 2 Sensor
 * 							- SENS_AGR_WATERMARK3 : Soil Moisture 3 Sensor
 * 							- SENS_AGR_ANEMOMETER : Anemometer Sensor
 * 							- SENS_AGR_VANE : Vane Sensor
 * 							- SENS_AGR_PLUVIOMETER : Pluviometer Sensor
 * 							- SENS_AGR_DENDROMETER : Trunk diameter Sensor
 *	 						- SENS_AGR_PT100 : Soil temperature Sensor
 * 							- SENS_AGR_LEAF_WETNESS : Leaf wetness Sensor
 * 							- SENS_AGR_TEMPERATURE : Temperature Sensor
 * 							- SENS_AGR_HUMIDITY : Humidity Sensor
 * 							- SENS_AGR_RADIATION : Solar radiation Sensor
 * 							- SENS_AGR_SENSIRION : Humidity and temperature Sensor
 * 							- SENS_AGR_LDR : Luminosity Sensor
 * 							- SENS_AGR_TEMP_DS18B20 : Temperature DS18B20 sensor (only P&S!)
 *  Return:		float value : value read from the sensor
 * 
 */
float	WaspSensorAgr_v20::readValue(uint16_t sensor, uint8_t type)
{
	float aux=0;
	uint16_t aux2=0;
 	
	switch( sensor )
	{
		case	SENS_AGR_PRESSURE	:	aux2=analogRead(ANALOG3);
										aux=pressureConversion(aux2); // KPa
										break;
		case	SENS_AGR_WATERMARK_1:	digitalWrite(SENS_MUX_SEL,LOW);
										aux=readWatermark(SENS_AGR_WATERMARK_1);
										// 50Hz - 200cbar || 10KHz - 0cbar
										digitalWrite(SENS_MUX_SEL,HIGH);
										break;
		case	SENS_AGR_WATERMARK_2:	digitalWrite(SENS_MUX_SEL,LOW);
										aux=readWatermark(SENS_AGR_WATERMARK_2);
										// 50Hz - 200cbar || 10KHz - 0cbar
										digitalWrite(SENS_MUX_SEL,HIGH);
										break;
		case	SENS_AGR_WATERMARK_3:	digitalWrite(SENS_MUX_SEL,LOW);
										aux=readWatermark(SENS_AGR_WATERMARK_3);
										// 50Hz - 200cbar || 10KHz - 0cbar
										digitalWrite(SENS_MUX_SEL,HIGH);
										break;
		case	SENS_AGR_ANEMOMETER	:	aux=readAnemometer();
										break;
		case	SENS_AGR_VANE		:	aux2=analogRead(ANALOG5);
										aux=(aux2*3.3)/1023; // Volts
										getVaneDirection(aux); // Direction
										break;
		case	SENS_AGR_DENDROMETER:	aux=readDendrometer(); //mm
										break;
		case	SENS_AGR_PT1000		:	aux=readPT1000(); // º Celsius
										break;
		case	SENS_AGR_LEAF_WETNESS:	aux2=analogRead(ANALOG6);
										aux=lwsConversion(aux2); // %Hum
										break;
		case	SENS_AGR_TEMPERATURE:	aux2=analogRead(ANALOG4);
										aux=mcpConversion(aux2); // ºCelsius
										break;
		case	SENS_AGR_HUMIDITY	:	aux2=analogRead(ANALOG2);
										aux=senceraConversion(aux2); // %Hum
										break;
		case	SENS_AGR_RADIATION	:	aux=readRadiation(); //Volts
										break;
		case	SENS_AGR_SENSIRION	:	if( type==SENSIRION_TEMP )
										{
											aux=readSensirion(SENSIRION_TEMP); 
											// ºCelsius
										} else if( type==SENSIRION_HUM )
										{
											aux=readSensirion(SENSIRION_HUM);
											// %Hum
										}
										break;
		case	SENS_AGR_PLUVIOMETER:	aux2=readPluviometer();
										aux=float(aux2) * 0.2794 * 20; // mm/min
										break;	
		case	SENS_AGR_LDR		:	aux2=analogRead(ANALOG7);
										aux=float(aux2*3.3) / 1023;
										break;	
		case	SENS_AGR_TEMP_DS18B20:	aux=readTempDS1820();
										break;	
		
		default						:	;
	}
	
	return	aux;
}


/*  attacPluvioInt: It attaches the pluviometer interruptions
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::attachPluvioInt(void) 
{
		enableInterrupts(PLV_INT);
}


/*  detachPluvioInt: It detaches the pluviometer interruptions
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::detachPluvioInt(void) 
{
	disableInterrupts(PLV_INT);
}

/*  sleepAgr: Calls the sleepAgr without agriculture interruptions
 *	Parameters:	const char*	time2wake
 * 				uint8_t offset
 * 				uint8_t mode
 * 				uint8_t option
 * 
 * 				See deepSleep function in PWR library			
 * 
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::sleepAgr(const char*	time2wake,
									uint8_t offset,
									uint8_t mode,
									uint8_t option)
{
	sleepAgr(time2wake, offset, mode, option, 0);
}

/*  sleepAgr: sleep function to turn off the sensors without disabling the board
 *	Parameters:	const char*	time2wake
 * 				uint8_t offset
 * 				uint8_t mode
 * 				uint8_t option
 * 
 * 				See deepSleep function in PWR library			
 * 
 *  Return:		void
 * 
 */
void	WaspSensorAgr_v20::sleepAgr(const char* time2wake,
									uint8_t offset, 
									uint8_t mode, 
									uint8_t option, 
									uint8_t agr_interrupt)
{
	// Set RTC alarme to wake up from Sleep Power Down Mode
	uint8_t retries=0;	
	
	// Switch off both multiplexers in UART_0 and UART_1
    Utils.muxOFF();
    
    // mandatory delay to wait for MUX_RX stabilization
	delay(100);	
    
	// set the XBee monitorization pin to zero
	pinMode(XBEE_MON,OUTPUT);
	digitalWrite(XBEE_MON,LOW);

	// set RTC alarm to wake up at specified time
	RTC.ON();
	RTC.setAlarm1(time2wake,offset,mode);
	RTC.OFF();
	
	// switch off sensors power supply
	digitalWrite(SENS_SWITCH_1, LOW);
	digitalWrite(SENS_SWITCH_2, LOW);
	digitalWrite(SENS_SWITCH_4, LOW);
	digitalWrite(SENS_MUX_SEL, LOW);
	digitalWrite(SENS_DATA, LOW);
	digitalWrite(SENS_SWITCH_3, LOW);
	
	// switches off depending on the option selected
	PWR.switchesOFF(option);

	// enable PLV interruption if selected
	if (agr_interrupt & SENS_AGR_PLUVIOMETER)
	{
		enableInterrupts(PLV_INT);
	}
	
	// make sure interruption pin is LOW before entering a low power state
	// if not the interruption will never come
	while(digitalRead(MUX_RX)==HIGH)
	{
		// clear all detected interruption signals
		delay(1);
		PWR.clearInterruptionPin();
		retries++;
		if(retries>10)
		{
			return (void)0;
		}
	}

	// set sleep mode
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_mode();
	sleep_disable();
	
	// in the case SENS_OFF was an option is mandatory to turn on the
	// sensor boards before setting up the I2C bus
	PWR.switchesON(option);

	// Switch on the RTC and clear the alarm signals	
	// Disable RTC interruption after waking up 
	// Except if the pluviometer interruption has woken-up the device. Then it
	// is supposed to enter sleep mode in a few seconds
	if( !(intFlag & PLV_INT) )
	{
		RTC.ON();		
		RTC.disableAlarm1();
		RTC.clearAlarmFlag();
		RTC.OFF();
	}
	
	// Keep sensor supply powered down if selected
	if( option & SENS_OFF )
	{
		// switch off the power supplies
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		PWR.setSensorPower(SENS_5V, SENS_OFF);
	}
		
}


// Private Methods //////////////////////////////////////////////////////////////

/*	readDendrometer: reads the analog to digital converter input to which is
 * 					 connected the dendrometer through the I2C and converts its
 * 					 value into mm
 *	Parameters: void
 *  Return:	float value : trunk diameter read by the dendrometer in mm
 * 
 */
float WaspSensorAgr_v20::readDendrometer(void)
{
	const byte dendro_channel = B10100001;
	byte data_dendro[3] = {0,0,0};
	float value_dendro = 0;
	
	if (!Wire.isON) 
	{
		Wire.begin();
	}
	delay(300);
  
	Wire.beginTransmission(I2C_ADDRESS_AGR_DENDROMETER);
	Wire.send(dendro_channel);
	Wire.send(B01010101);
	Wire.endTransmission();

	delay(300);
  
	Wire.requestFrom(I2C_ADDRESS_AGR_DENDROMETER, 3);
  
	int i=0;
	while (Wire.available())
	{
		data_dendro[i]=Wire.receive();
		i++;
	}
	
	if (Wire.isON && !ACC.isON && RTC.isON!=1)
	{
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
  
	return value_dendro = conversion(data_dendro,0);
}

/*	readAnemometer: reads the number of anemometer pulses during three seconds
 * 					and turns the value into speed (km/h)
 *	Parameters: void
 *  Return:	float value : wind speed (km/h)
 * 
 */
float WaspSensorAgr_v20::readAnemometer(void)
{
	int reading_anemometer = 0;
	int previous_reading_anemometer = 0;
	int value_anemometer = 0;
	float wind_speed = 0;
	unsigned long start_anemometer=0;
	unsigned long previous_pulse=0;
	unsigned long pulse_duration=1000000; // set to large value
	unsigned long new_pulse_duration=0;
	const unsigned long MEAS_TIME = 3000; // ms

	value_anemometer = 0;
	start_anemometer = millis();
	previous_pulse = millis();
	while( (millis()-start_anemometer) <= MEAS_TIME )
	{
		previous_reading_anemometer = reading_anemometer;
		reading_anemometer = digitalRead(DIGITAL2);
    
		// check falling edge
		if((previous_reading_anemometer == 1)&&(reading_anemometer == 0))
		{
			// increment pulse counter
			value_anemometer++;
			
			// get new pulse elapsed time
			new_pulse_duration = millis()-previous_pulse;
			// update pulse instant time				
			previous_pulse = millis();

			// update pulse duration in the case is the lowest 
			if( new_pulse_duration < pulse_duration )
			{
				pulse_duration = new_pulse_duration;
			}
			
		}
		//avoid millis overflow problem
		if( millis() < start_anemometer ) start_anemometer=millis(); 
	}
	delay(100);
	
	// calculate average wind speed
	wind_speed = value_anemometer * 2.4 / (MEAS_TIME/1000);
	
	// calculate gust of wind 2.4Km/h per second
	gustWind = 2.4 / ((float)pulse_duration/1000);
  
	return wind_speed;
}

/*	readPT1000: reads the analog to digital converter input to which is connected
 * 				the	PT1000 sensor through the I2C and converts its value into
 * 				temperature (ºC)
 *	Parameters: void
 *  Return:	float value : temperature in Celsius (ºC)
 * 
 */
float WaspSensorAgr_v20::readPT1000(void)
{	
	const byte pt1000_channel = B10100000;
	byte data_pt1000[3] = {0,0,0};
	float value_pt1000 = 0;
	
	if (!Wire.isON) 
	{
		Wire.begin();
	}
	delay(300);

	Wire.beginTransmission(I2C_ADDRESS_AGR_PT1000);
	Wire.send(pt1000_channel);
	Wire.send(B01010101);
	Wire.endTransmission();
  
	delay(300);
  
	Wire.requestFrom(I2C_ADDRESS_AGR_PT1000, 3);

	int k=0;
	while (Wire.available())
	{
		data_pt1000[k]=Wire.receive();
		k++;
	}

	if (Wire.isON && !ACC.isON && RTC.isON!=1)
	{
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
	return value_pt1000 = conversion(data_pt1000,1);  
}

/*	readRadiation: reads the analog to digital converter to which is connected the
 * 				   solar radiation sensor through the I2C and converts its value
 * 				   into voltage
 *	Parameters: void
 *  Return:	float value : solar radiation in volts
 * 
 */
float WaspSensorAgr_v20::readRadiation(void)
{
	byte data_apogee[2] = {0,0};
	long val = 0;
	float val_def = 0;

	if (!Wire.isON)
	{
		Wire.begin();
	}
  
	delay(150);

	Wire.requestFrom(I2C_ADDRESS_AGR_RADIATION, 2);
  
	int i = 0;
	while (Wire.available())
	{
		data_apogee[i] = Wire.receive();
		i++;
	}
  
	if (Wire.isON && !ACC.isON && RTC.isON!=1)
	{
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
 
	val = long(data_apogee[1]) + long(data_apogee[0])*256;
    
	val_def = (val - 32769)*9;
	return val_def = val_def/65535;
}

/*	readWatermark: reads the frequency of the adaptation circuit of the Watermark
 * 				   sensor indicated in sens
 *	Parameters: uint8_t sens
 * 						- SENS_AGR_WATERMARK_1
 * 						- SENS_AGR_WATERMARK_2
 * 						- SENS_AGR_WATERMARK_3
 *  Return:	float value : watermark circuit frequency
 * 						  -1 if wrong sensor selected
 * 
 */
float WaspSensorAgr_v20::readWatermark(uint8_t sens)
{
	uint8_t pin=0;
	int value_watermark = 0;
	int previous_value_watermark = 0;
	int counter_watermark = 0;
	unsigned long start = 0;
	float freq = 0;
	
	pinMode(15, INPUT);
	pinMode(17, INPUT);
	pinMode(19, INPUT);
    
 	digitalWrite(SENS_MUX_SEL,LOW);
	
	switch( sens )
	{
		case SENS_AGR_WATERMARK_1	:	pin=15;
										break;
		case SENS_AGR_WATERMARK_2	:	pin=19;
										break;
		case SENS_AGR_WATERMARK_3	:	pin=17;
										break;
		default						:	return -1.0;
	}
 	
	counter_watermark = 0;
	start = millis();
	while(counter_watermark < 2000)
	{
		previous_value_watermark = value_watermark;
		value_watermark = digitalRead(pin);
    
		if((previous_value_watermark ==1)&&(value_watermark == 0))
		{
			counter_watermark++;
		}
	}
  
	return freq = 2000000 / float((millis() - start));
}

/*	readSensirion: reads the temperature or humidity value from the Sensirion
 * 				   digital temperature and humidity sensor
 *	Parameters: uint8_t parameter
 * 						- SENSIRION_TEMP
 * 						- SENSIRION_HUM
 *  Return:	float value : temperature (ºC) or humidity (%RH) value
 * 						  out of range values if connection problem
 * 
 */
float WaspSensorAgr_v20::readSensirion(uint8_t parameter)
{
	int ack = 0;
	int val_read = 0;
	unsigned long a = 0;	
	
	const byte HUMIDITY = B00000101;
	const byte TEMPERATURE = B00000011;
	
	

	if( parameter==SENSIRION_TEMP ) parameter=TEMPERATURE;
	else if( parameter==SENSIRION_HUM ) parameter=HUMIDITY;
		
  //************************************* 
  // First Transmission cycle (START)
  
	pinMode(SENS_DATA,  OUTPUT);
	pinMode(SENS_CLK, OUTPUT);
	digitalWrite(SENS_DATA,  HIGH);
	digitalWrite(SENS_CLK, HIGH);
	delayMicroseconds(1);
	digitalWrite(SENS_DATA,  LOW);
	digitalWrite(SENS_CLK, LOW);
	delayMicroseconds(1);
	digitalWrite(SENS_CLK, HIGH);
	digitalWrite(SENS_DATA,  HIGH);
	delayMicroseconds(1);
	digitalWrite(SENS_CLK, LOW);

  //***************************************
  // Write the command (3 first bits: always 000, last five bits: command)

	//parameter: B00000011 for temperature and B00000101 for humidity
	shiftOut(SENS_DATA, SENS_CLK, MSBFIRST, parameter);  
	digitalWrite(SENS_CLK, HIGH);
	pinMode(SENS_DATA, INPUT);

	a = millis();
	ack = digitalRead(SENS_DATA);
	while((ack == HIGH)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}

	digitalWrite(SENS_CLK, LOW);

	a = millis();
	ack = digitalRead(SENS_DATA);
	while((ack == LOW)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}
  
  //****************************************
  //Wait for a complete conversion
  
	ack = digitalRead(SENS_DATA);
	a = millis();
	while((ack == HIGH)&&((millis()-a)<400))
	{
		ack = digitalRead(SENS_DATA);
	}
 
  //*****************************************
  //Read the 8 most significative bits

	a = millis();
	for(int i = 0; i < 8; i++)
	{
		digitalWrite(SENS_CLK, HIGH);
		val_read = (val_read * 2) + digitalRead(SENS_DATA);
		digitalWrite(SENS_CLK, LOW);
	}
  
	ack = digitalRead(SENS_DATA);
	a = millis();
	while((ack == LOW)&&((millis()-a)<10))
	{
		ack = digitalRead(SENS_DATA);
		if (millis() < a) a = millis();	//to avoid millis overflow
	}
  
  //****************************************
  //ACK from the  microcontroller
	pinMode(SENS_DATA, OUTPUT);
	digitalWrite(SENS_DATA, LOW);
	delayMicroseconds(1);
	digitalWrite(SENS_CLK, HIGH);
	delayMicroseconds(400);
	digitalWrite(SENS_CLK, LOW);
	pinMode(SENS_DATA, INPUT);
   
  //***************************************
  //Read the 8 least significative bits
	a = millis();
	for(int i = 0; i < 8; i++)
	{
		digitalWrite(SENS_CLK, HIGH);
		val_read = val_read * 2 + digitalRead(SENS_DATA);
		digitalWrite(SENS_CLK, LOW);
	}
	
  
  //**************************************
  //CRC not taken into account
  
	pinMode(SENS_DATA, OUTPUT);
	digitalWrite(SENS_DATA, HIGH);
	digitalWrite(SENS_CLK, HIGH);
	delayMicroseconds(400);
	digitalWrite(SENS_CLK, LOW);
	
	digitalWrite(SENS_DATA, LOW);
  
	if( parameter==TEMPERATURE ) return temperatureConversion(val_read,SENS_PREC_HIGH);
	else if( parameter==HUMIDITY ) return humidityConversion(val_read,SENS_PREC_HIGH);
	
	return 0;
} 

/*	temperatureConversion: converts the value read from the Sensirion into a
 * 						   temperature value
 *	Parameters:	int readValue : value read from the Sensirion
 * 				int precision : format at which the sensor was read
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
float WaspSensorAgr_v20::temperatureConversion(int readValue, int precision)
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
float WaspSensorAgr_v20::humidityConversion(int readValue, int precision)
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



/*	readPluviometerHour 
 * 
 * It calculates the rain fall during the previous hour before actual slot.
 * 
 * For example: It is 13.30 pm. Then this function calculates the rain fall for 
 * the whole previous slot. It is said to be the rainfall from 12pm to 13pm
 * 
 */
float WaspSensorAgr_v20::readPluviometerHour()
{
	// Introduce one hour time as '1' hour and '1' hour-offset
	return 	readPluviometer(1, 1);
}


/*	readPluviometerCurrent 
 * 
 * It calculates the rain fall during the current hour slot.
 * 
 * For example: It is 13.30 pm. Then this function calculates the rain fall for 
 * this hour slot. It is said to be the rainfall from 13pm to 13.30pm
 * 
 */
float WaspSensorAgr_v20::readPluviometerCurrent()
{
	// Introduce one hour time as '1' hour and '0' hour-offset
	return 	readPluviometer(1, 0);
}

/*	readPluviometerDay 
 * 
 * It calculates the rain fall during the last day
 * 
 */
float WaspSensorAgr_v20::readPluviometerDay()
{
	// Introduce one day time as '24' hour
	return 	readPluviometer(24, 1);
}


/*	readPluviometer: reads the number of pluviometer pulses during the indicated 
 * 					time and turns the value into mm of rain per indicated time
 *	Parameters: 'time' indicates the amount of time (in seconds) to calculate 
 *  the rain fall. For example, one hour would be 3600 seconds.
 *  Return:	float value : precipitations (mm)
 * 
 */
float WaspSensorAgr_v20::readPluviometer( uint8_t numHours, int offset)
{	
	// Variable to store the precipitations value
	float precipitations = 0.0;	// mm
	float pluviometerCounter = 0.0;	// number of pulses
	int counter = (int)numHours;
	
	// switch on RTC and get Date
	RTC.ON();
	RTC.getTime();
	
	// calculate rain fall:
	
	// firstly, from RTC.hour down to 24h
	for(int i = (int)RTC.hour-offset; i>=0 ; i--)
	{
		// decrease counter variable
		counter--;
		
		// check hours counter
		if( counter < 0 ) break;		
		
		// check correct Date
		if( (plv_array[i].day   == RTC.date) &&
			(plv_array[i].month == RTC.month) )
		{			
			// add number of pulses for each valid slot
			pluviometerCounter += plv_array[i].pulses;
		}		
	}
	
	// secondly, from 24h down to RTC.hour	
	for(int i = 23; i>=RTC.hour ; i--)
	{
		// decrease counter variable
		counter--;
		
		// check hours counter
		if( counter < 0 ) break;	
		
		// get epoch reference to actual Date
		unsigned long epoch = RTC.getEpochTime(RTC.year,RTC.month,RTC.date,0,0,0);
		// substract one day
		epoch -= SECS_PER_DAY;
		timestamp_t 	tm;
		RTC.breakTimeAbsolute( epoch, &tm);		
		
		// check correct Date
		if( (plv_array[i].day   == tm.date) &&
			(plv_array[i].month == tm.month) )
		{				
			// add number of pulses for each valid slot
			pluviometerCounter += plv_array[i].pulses;
		}
		
	}
	
	// calculate precipitation (mm) for indicated time period
	precipitations = pluviometerCounter * 0.2794; 
	
	return precipitations;	
}


/*	readPluviometer: reads the number of anemometer pulses during three seconds
 * 					 and turns the value into mm of rain
 *	Parameters: void
 *  Return:	float value : precipitations (mm)
 * 
 */
uint16_t WaspSensorAgr_v20::readPluviometer()
{
	int reading_pluviometer = 0;
	int previous_reading_pluviometer = 0;
	int value_pluviometer = 0;
	unsigned long start_pluviometer=0;

	value_pluviometer = 0;
	start_pluviometer = millis();
	while((millis()-start_pluviometer)<=3000)
	{
		previous_reading_pluviometer = reading_pluviometer;
		reading_pluviometer = digitalRead(DIGITAL4);
    
		if((previous_reading_pluviometer == 1)&&(reading_pluviometer == 0))
		{
			value_pluviometer++;
		}
		//avoid millis overflow problem
		if( millis() < start_pluviometer) start_pluviometer=millis();
	}
	delay(100);
  
	return value_pluviometer;
}


/*	storePulse: 
 * 
 * This function increments the number of pulses inside the pluviometer array 
 * in the corresponding index of 'plv_array' 
 * 
 */
void WaspSensorAgr_v20::storePulse()
{
	// switch on RTC and get actual time
	RTC.ON();
	RTC.getTime();
	uint16_t MAX_NUMBER_PULSES = 65535;
	
	// check if array slot must be initialized or not
	if( (plv_array[RTC.hour].day   == RTC.date) &&
		(plv_array[RTC.hour].month == RTC.month) )
	{
		// increment number of pulses
		if( plv_array[RTC.hour].pulses < MAX_NUMBER_PULSES )
		{
			plv_array[RTC.hour].pulses++;
		}
	}
	else
	{
		// store new date for this slot
		plv_array[RTC.hour].day = RTC.date;
		plv_array[RTC.hour].month = RTC.month;
		plv_array[RTC.hour].pulses = 0;
		// increment number of pulses
		if( plv_array[RTC.hour].pulses < MAX_NUMBER_PULSES )
		{
			plv_array[RTC.hour].pulses++;
		}
	}	
}



/*	conversion: converts the value read from the PT1000 and dendrometer ADC into
 * 				the units of the sensor
 *	Parameters: byte data_input[3] : three bytes from the ADC conversion
 * 				uint8_t type : 1 for PT1000 reading, 0 for dendrometer reading
 *  Return:	float value : temperature (ºC) or diameter (mm) in function of the sensor
 * 
 */
float WaspSensorAgr_v20::conversion(byte data_input[3], uint8_t type)
{
	long val = 0;
	float val_def = 0;
	int signo = 0;
	int overflow = 0;
	float Vcc = 3.3;
	float R1           = 1005.0; 
	float R2           = 1005.0;
	float R3           = 1005.0;
	float Rx           = 0.0;
	float tempPt       = 0.0;
	float equis        = 0.0;
  
	signo = int(data_input[0] >> 7);
	overflow = int((data_input[0] >> 6)&B00000001);

	val = long((data_input[2] >> 6)&B00000011) + long(data_input[1])*4 
		  + long((data_input[0])&B00111111)*1024;

  
	if (signo == 1)
	{
		if (overflow == 1)
		{
      //OVERFLOW High
			val_def = 2;
		}
		else
		{
			val_def = val*1.5;
			val_def = val_def/65535;
		}
	}
	else
	{
		if (overflow == 0)
		{
      //OVERFLOW LOW
			val_def = -2;
		}
		else
		{
			val_def = -(65535 - val)*1.5;
			val_def = val_def/65535;
		}
	}

	if( type==1 ){
		Rx = (Vcc*R2*R3 + val_def*R3*(R1+R2)) / (Vcc*R1 - val_def*(R1+R2));
		equis = (Rx - 1001.52) / 1351.99;
		Rx = equis * 1494.46 + 996.04;
		tempPt = (Rx-1000)/3.9083;
		return(tempPt);
	}
	else if( type==0) return ( (val_def * 11000)/1000.0 );
	
	return 0;
}



/*	pressureConversion: converts the value read at the analog to digital
 * 						converter corresponding to the atmospheric pressure
 * 						sensor into a pressure value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : temperature measured by the sensor in kilopascals
 * 
 */float WaspSensorAgr_v20::pressureConversion(int readValue)
{
	float pressure = 0;   
	
	//  datasheet: Vout=Vs(0.009*P-0.95) --> P= (Vout+0.4845)/0.0459
		
	// sensor output (mV) . Range 200 - 4800mV
	pressure = ((float(readValue) * 3300.0) / 1023.0) / 0.6;
	 
	// Obtain kPa. 
	// 0.208 is an offset to fix a 5Kpa deviation. 
	pressure = ((((pressure/1000)+0.208)+0.4845)/0.0459);
   
	return(pressure);
}



/*	lwsConversion: converts the value read at the analog to digital	converter
 * 				   input corresponding to the leaf wetness sensor into a percentage
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : wetness measured by the sensor in %RH
 * 
 */
float WaspSensorAgr_v20::lwsConversion(int readValue)
{
	float lws = 0;
   
	//This sensor has a range between 1-3.3 V
	//So that the ADC reads values between 310-1023
	//The next formula can be extracted by linearizing with two points
	// (x1 , y1) = (310, 100 %)
	// (x2 , y2) = (1023, 0  %)
	// (y-y1)/(y2-y1) = (x-x1)/(x2-x1)
	
	if (float (readValue)>310.0)
	{
		lws=(1023.0*100.0/713.0)-(100.0/713.0)*readValue;
	} 
	else
	{
		lws=100.0;
	}
	
	return(lws);
   
}
 
/*	getVaneDirection: stores in the vaneDirection variable the orientation of the
 * 					  vane calculated from the voltage read at its output
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		void
 * 
 */
void WaspSensorAgr_v20::getVaneDirection(float vane)
{
	if( vane<0.25 ) vaneDirection=SENS_AGR_VANE_ESE;
	else if( vane>=0.25 && vane<0.28 ) vaneDirection=SENS_AGR_VANE_ENE;
	else if( vane>=0.28 && vane<0.35 ) vaneDirection=SENS_AGR_VANE_E;
	else if( vane>=0.35 && vane<0.5 ) vaneDirection=SENS_AGR_VANE_SSE;
	else if( vane>=0.5 && vane<0.65 ) vaneDirection=SENS_AGR_VANE_SE;
	else if( vane>=0.65 && vane<0.85 ) vaneDirection=SENS_AGR_VANE_SSW;
	else if( vane>=0.85 && vane<1.1 ) vaneDirection=SENS_AGR_VANE_S;
	else if( vane>=1.1 && vane<1.38 ) vaneDirection=SENS_AGR_VANE_NNE;
	else if( vane>=1.38 && vane<1.6 ) vaneDirection=SENS_AGR_VANE_NE;
	else if( vane>=1.6 && vane<1.96 ) vaneDirection=SENS_AGR_VANE_WSW;
	else if( vane>=1.96 && vane<2.15 ) vaneDirection=SENS_AGR_VANE_SW;
	else if( vane>=2.15 && vane<2.35 ) vaneDirection=SENS_AGR_VANE_NNW;
	else if( vane>=2.35 && vane<2.6 ) vaneDirection=SENS_AGR_VANE_N;
	else if( vane>=2.6 && vane<2.75 ) vaneDirection=SENS_AGR_VANE_WNW;
	else if( vane>=2.75 && vane<2.95 ) vaneDirection=SENS_AGR_VANE_NW;
	else if( vane>=2.95 ) vaneDirection=SENS_AGR_VANE_W;
}

 
/*	getVaneFiltred: stores in the vaneDirection variable the orientation of the
 * 					vane calculated from the voltage read at its output. The 
 * 					measurement is performed doing the mean of several values.				
 *	
 *  Return:		void
 *  Remarks: http://en.wikipedia.org/wiki/Mean_of_circular_quantities
 * 
 */
void WaspSensorAgr_v20::getVaneFiltered()
{
	int NUM_SAMPLES=20;	
	int SAMPLING_TIME=100; // ms
	int aux;
	float sample[NUM_SAMPLES];
	float vanes[NUM_SAMPLES];
	
	for( int i=0 ; i<NUM_SAMPLES; i++ )
	{
		aux = analogRead(ANALOG5); //read bits 0-1023
		sample[i] = (aux*3.3)/1023; // Volts
		getVaneDirection(sample[i]); // in vane direction
		vanes[i] = vaneDirection;
		delay(SAMPLING_TIME);
	}
	
	// Mean filter
	float mean=0;
	int conversion=0;
	float senos=0.0;
	float cosenos=0.0;
	
	// translate to radians 
	for( int i=0 ; i<NUM_SAMPLES; i++ )
	{
		vanes[i] = vanes[i]*2*PI/16;
	}
	
	// get the summatory of both sine y cosine of all measurements
	for( int i=0 ; i<NUM_SAMPLES; i++ )
	{
		senos += sin(vanes[i]);
		cosenos += cos(vanes[i]);
	}
	
	// perform the mean of angles
	mean = atan2(senos/NUM_SAMPLES, cosenos/NUM_SAMPLES);	
	
	// negative radians: if range is betwen [-PI to 0] translate it: [PI to 2PI]
	if(mean<0) 
	{
		mean *= -1;
		mean = (PI-mean)+PI;
	}
	
	// Translate it to the values given in the API
	conversion = (int)round( 16*mean/(2*PI) );
	
	// in case of 2*PI, set to 0
	if(conversion == 16) 
	{
		conversion=0;
	}
	
	// update variable
	vaneDirection = conversion;
	
}

/*	senceraConversion: converts the value read at the analog to digital
 * 					   converter corresponding to the humidity sensor
 * 					   into a humidity value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : humidity measured by the sensor in %RH
 * 
 */
float WaspSensorAgr_v20::senceraConversion(int readValue)
{
	float humidity = 0.0;   
	
    humidity = (float(readValue) * 3300.0 / 1023.0)/0.6; //sensor output (mV)
	humidity = (humidity - 800) / 31; // %hum
   
	return(humidity);
   
}
 
/*	mcpConversion: converts the value read at the analog to digital converter
 * 				   corresponding to the temperature sensor into a temperature value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
float WaspSensorAgr_v20::mcpConversion(int readValue)
{
	float temperature = 0;
   
	temperature = float(readValue) * 3300 / 1023; //sensor output (mV)
   
	temperature = (temperature - 500) / 10; 
   
	return(temperature);
   
}


/* readTempDS1820() - reads the DS1820 temperature sensor
 *
 * It reads the DS1820 temperature sensor
 */
float WaspSensorAgr_v20::readTempDS1820()
{
	// Select analog 4 as pin to be used
	// 'false' input means that no 3v3 power supply is managed
	// So, the Sensor Board and the sensor switch must be 
	// powered on prior using this function
	return 	Utils.readTempDS1820( 17, false );
}







WaspSensorAgr_v20 SensorAgrv20=WaspSensorAgr_v20();
