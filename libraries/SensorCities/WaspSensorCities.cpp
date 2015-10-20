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
 *  Design:			David Gascón
 *  Implementation: Manuel Calahorra
 */
 

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspSensorCities.h"
  
// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorCities::WaspSensorCities()
{
	pinMode(DIGITAL1,OUTPUT);
	pinMode(DIGITAL2,OUTPUT);
	pinMode(DIGITAL3,INPUT);
	pinMode(DIGITAL4,OUTPUT);
	pinMode(DIGITAL5,OUTPUT);
	pinMode(DIGITAL6,OUTPUT);
	pinMode(DIGITAL7,OUTPUT);
	pinMode(DIGITAL8,OUTPUT);
	pinMode(14,INPUT);
	pinMode(15,OUTPUT);
	pinMode(16,INPUT);
	pinMode(17,INPUT);
	pinMode(18,INPUT);
	pinMode(19,INPUT);
	pinMode(20,INPUT);

	digitalWrite(DIGITAL1,LOW);
	digitalWrite(DIGITAL2,LOW);
	digitalWrite(DIGITAL4,LOW);
	digitalWrite(DIGITAL5,LOW);
	digitalWrite(DIGITAL6,LOW);
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(DIGITAL8,LOW);
	digitalWrite(15,LOW);	
	
	// init power supply to OFF state
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	
	// update Waspmote Control Register
	WaspRegister |= REG_CITIES_V15;
}

// Public Methods //////////////////////////////////////////////////////////////

/*	ON: Calls the setBoardMode function to turn on the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorCities::ON(void)
{
	setBoardMode(SENS_ON);
}

/*	OFF: Calls the setBoardMode function to turn off the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorCities::OFF(void)
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
int8_t	WaspSensorCities::setBoardMode(uint8_t mode)
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
							break;
		case	SENS_OFF:	// update I2C flag
							Wire.isBoard = false;
							// switch off the power supplies
							PWR.setSensorPower(SENS_3V3, SENS_OFF);
							PWR.setSensorPower(SENS_5V, SENS_OFF);
							break;
		default			:	return 0;
	}
	
	return 1;
}

/* setAudioGain: Sets resistance of the digipots which control the gain of the
 * 				 noise sensor circuitry
 * Parameters:	float value1 : gain of the input stage between 1 and 101
 * 			 	float value2 : gain of the input stage between 1.056 and 5.0
 * 
 * Returns void
 */
void WaspSensorCities::setAudioGain(uint8_t value1, float value2)
{
	uint8_t ampli=0;
	float auxiliar = 0.0;

	// Set gain values
	gain1 = value1;
	gain2 = value2;

	// value1 range: from 1 to 101
	if(value1 > 101)
		value1 = 101;
	else if(value1 < 1)
		value1 = 1;

	value1--;
	ampli=(uint8_t) 128-(128/100)*value1;

	if( !Wire.I2C_ON ) Wire.begin();
	delay(100);
	Wire.beginTransmission(I2C_ADDRESS_CITIES_AUDIO_GAIN);
	Wire.send(B00000000);
	Wire.send(ampli);
	Wire.endTransmission();	

	// value2 range: from 1.056 to 5.0
	if(value2 > 5.0)
		value2 = 5.0;
	else if(value2 < 1.056)
		value2 = 1.056;

	auxiliar = 5.6 / (value2-1.0);

	ampli=(uint8_t) 128-(128/100)*auxiliar;

	Wire.beginTransmission(I2C_ADDRESS_CITIES_AUDIO_GAIN);
	Wire.send(B00010000);
	Wire.send(ampli);
	Wire.endTransmission();

	if( Wire.I2C_ON && !ACC.isON && RTC.isON!=1){
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
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
int8_t	WaspSensorCities::setThreshold(uint16_t sensor, float threshold) 
{
	if( ( threshold < 0 ) || ( threshold > 3.3 ) )
	{
		return -2;
	}
	
	switch( sensor )
	{
		case SENS_CITIES_DUST			:	setDigipot0(I2C_ADDRESS_SENS_CITIES_DUST,threshold);
			 								break;
		case SENS_CITIES_LD				:	setDigipot1(I2C_ADDRESS_CITIES_LD,threshold);
			 								break;
		case SENS_CITIES_AUDIO			:	setDigipot1(I2C_ADDRESS_CITIES_AUDIO,threshold);
			 								break;
		case SENS_CITIES_HUMIDITY		:	setDigipot0(I2C_ADDRESS_CITIES_HUMIDITY,threshold);
			 								break;
		case SENS_CITIES_TEMPERATURE	:	setDigipot1(I2C_ADDRESS_CITIES_TEMPERATURE,threshold);
			 								break;
		case SENS_CITIES_ULTRASOUND_5V	:	setDigipot0(I2C_ADDRESS_CITIES_ULTRA_5V,threshold);
			 								break;
		case SENS_CITIES_ULTRASOUND_3V3	:	setDigipot1(I2C_ADDRESS_CITIES_ULTRA_3V3,threshold);
			 								break;
		case SENS_CITIES_LDR			:	setDigipot0(I2C_ADDRESS_CITIES_LDR,threshold);
			 								break;
		case SENS_CITIES_CD				:	setDigipot0(I2C_ADDRESS_CITIES_CD,threshold);
			 								break;
		case SENS_CITIES_CP				:	setDigipot0(I2C_ADDRESS_CITIES_CP,threshold);
											break;
		default						:	return -1;
	}
	
	return 1;
}

/*	setSensorMode: It sets ON/OFF the different sensor switches
 *	Parameters:	uint8_t mode 
 * 						- SENS_ON : turn on the sensor
 * 						- SENS_OFF : turn off the sensor
 * 				uint16_t sensor
 * 							- SENS_CITIES_DUST : Dust Sensor
 * 							- SENS_CITIES_LD : Linear Displacement Sensor
 * 							- SENS_CITIES_AUDIO : Noise Sensor
 * 							- SENS_CITIES_HUMIDITY : Humidity Sensor
 * 							- SENS_CITIES_TEMPERATURE : Temperature Sensor
 * 							- SENS_CITIES_ULTRASOUND : Ultrasound Sensor
 * 							- SENS_CITIES_LDR : Luminosity Sensor
 *	 						- SENS_CITIES_CD : Crack detection Sensor
 * 							- SENS_CITIES_CP : Crack propagation Sensor
 *  Return:		int8_t error
 * 						1 : success
 * 						0 : wrong mode selected
 * 						-1: wrong sensor selected
 * 
 */
int8_t	WaspSensorCities::setSensorMode(uint8_t mode, uint16_t sensor)
{
	if( mode==SENS_ON )
	{
		switch( sensor )
		{
			case	SENS_CITIES_DUST			:	digitalWrite(DIGITAL2,HIGH);
													break;
			case	SENS_CITIES_LD				:	digitalWrite(DIGITAL1,HIGH);
													break;
			case	SENS_CITIES_AUDIO			:	digitalWrite(DIGITAL6,HIGH);
													//Set amplifiers gain
													setAudioGain(49,1.89);
													break;
			case	SENS_CITIES_HUMIDITY		:	digitalWrite(DIGITAL2,HIGH);
													break;
			case	SENS_CITIES_TEMPERATURE		:	digitalWrite(DIGITAL2,HIGH);
													break;
			case	SENS_CITIES_ULTRASOUND_5V	:	digitalWrite(DIGITAL2,HIGH);
													break;
			case	SENS_CITIES_ULTRASOUND_3V3	:	digitalWrite(DIGITAL2,HIGH);
													break;
			case	SENS_CITIES_LDR				:	digitalWrite(DIGITAL2,HIGH);
													break;
			case	SENS_CITIES_CD				:	digitalWrite(DIGITAL2,HIGH);
													break;
			case	SENS_CITIES_CP				:	digitalWrite(DIGITAL2,HIGH);
													break;
			case	SENS_CITIES_TEMP_DS18B20	:	digitalWrite(DIGITAL2,HIGH);
													break;
			default								:	return -1;
		}
	} else if( mode==SENS_OFF )
	{
		switch( sensor )
		{
			case	SENS_CITIES_DUST			:	digitalWrite(DIGITAL2,LOW);
													break;
			case	SENS_CITIES_LD				:	digitalWrite(DIGITAL1,LOW);
													break;
			case	SENS_CITIES_AUDIO			:	digitalWrite(DIGITAL6,LOW);
													break;
			case	SENS_CITIES_HUMIDITY		:	digitalWrite(DIGITAL2,LOW);
													break;
			case	SENS_CITIES_TEMPERATURE		:	digitalWrite(DIGITAL2,LOW);
													break;
			case	SENS_CITIES_ULTRASOUND_5V	:	digitalWrite(DIGITAL2,LOW);
													break;
			case	SENS_CITIES_ULTRASOUND_3V3	:	digitalWrite(DIGITAL2,LOW);
													break;
			case	SENS_CITIES_LDR				:	digitalWrite(DIGITAL2,LOW);
													break;
			case	SENS_CITIES_CD				:	digitalWrite(DIGITAL2,LOW);
													break;
			case	SENS_CITIES_CP				:	digitalWrite(DIGITAL2,LOW);
													break;
			case	SENS_CITIES_TEMP_DS18B20	:	digitalWrite(DIGITAL2,LOW);
													break;
			default								:	return -1;
		}
	} else return 0;
	
	return 1;
}

/*	readValue: Reads the analog to digital converter input indicated of the given
 * 			   sensor socket and converts the value into the proper units
 *	Parameters:	uint16_t sensor
 * 							- SENS_CITIES_DUST : Dust Sensor
 * 							- SENS_CITIES_LD : Linear Displacement Sensor
 * 							- SENS_CITIES_AUDIO : Noise Sensor
 * 							- SENS_CITIES_HUMIDITY : Humidity Sensor
 * 							- SENS_CITIES_TEMPERATURE : Temperature Sensor
 * 							- SENS_CITIES_ULTRASOUND : Ultrasound Sensor
 * 							- SENS_CITIES_LDR : Luminosity Sensor
 *	 						- SENS_CITIES_CD : Crack detection Sensor
 * 							- SENS_CITIES_CP : Crack propagation Sensor
 *  Return:		float value : value read at the sensor output or load resistor
 * 							  converted to the proper units
 * 
 */
float	WaspSensorCities::readValue(uint16_t sensor)
{
	return readValue(sensor, 0);
}

/*	readValue: Reads the analog to digital converter input indicated of the given
 * 			   sensor socket and converts the value into the proper units
 *	Parameters:	uint16_t sensor
 * 							- SENS_CITIES_DUST : Dust Sensor
 * 							- SENS_CITIES_LD : Linear Displacement Sensor
 * 							- SENS_CITIES_AUDIO : Noise Sensor
 * 							- SENS_CITIES_HUMIDITY : Humidity Sensor
 * 							- SENS_CITIES_TEMPERATURE : Temperature Sensor
 * 							- SENS_CITIES_ULTRASOUND : Ultrasound Sensor
 * 							- SENS_CITIES_LDR : Luminosity Sensor
 *	 						- SENS_CITIES_CD : Crack detection Sensor
 * 							- SENS_CITIES_CP : Crack propagation Sensor
 * 				uint8_t type
 * 							- SENS_US_WRA1	:	Selects ultrasounds WRA1 sensor
 * 							- SENS_US_EZ0	:	Selects ultrasounds EZ0 sensor
 *  Return:		float value : value read at the sensor output or load resistor
 * 							  converted to the proper units
 * 
 */
float	WaspSensorCities::readValue(uint16_t sensor, uint8_t type)
{
	int aux=0;
	float value = 0.0;
	
	switch( sensor )
	{
		case	SENS_CITIES_DUST			:	aux = analogRead(ANALOG1);
												value = dustConversion(aux);
												break;
		case	SENS_CITIES_LD				:	aux = analogRead(ANALOG7);
												value = ldConversion(aux);
												break;
		case	SENS_CITIES_AUDIO			:	// Measure noise for a second
												value=0;
												for(int g=0;g<1000;g++){
													value += analogRead(ANALOG6);
													delay(1);
												}
												value = value / 1000;  
												value = audioConversion(value);
												break;
		case	SENS_CITIES_HUMIDITY		:	aux = analogRead(ANALOG3);
												value = humidityConversion(aux);
												break;
		case	SENS_CITIES_TEMPERATURE		:	aux = analogRead(ANALOG4);
												value = temperatureConversion(aux);
												break;
		case	SENS_CITIES_ULTRASOUND_3V3	:	value = ultrasoundConversion(ANALOG4, type);
												break;
		case	SENS_CITIES_ULTRASOUND_5V	:	value = ultrasoundConversion(ANALOG3, type);
												break;
		case	SENS_CITIES_LDR				:	aux = analogRead(ANALOG5);
												value = ldrConversion(aux);
												break;
		case	SENS_CITIES_CD				:	aux = analogRead(ANALOG5);
												value = aux;
												break;
		case	SENS_CITIES_CP				:	aux = analogRead(ANALOG5);
												value = aux;
												break;
		case	SENS_CITIES_TEMP_DS18B20	:	value=readTempDS1820();
												break;
		default								:	;
	}
	
	return value;
}


/* attacInt: It attaches sensors board interruption, setting three-state buffer
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorCities::attachInt() 
{
	digitalWrite(SENS_INT_CITIES_ENABLE,HIGH); 
	enableInterrupts(SENS_INT);
}


/* detachInt: It detaches sensor board interruption, unsetting three-state buffer
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorCities::detachInt() 
{
	digitalWrite(SENS_INT_CITIES_ENABLE,LOW); 
	disableInterrupts(SENS_INT);
}


/* loadInt: Loads shift register through parallel input to check the sensor
 * 			that generates the interruption updating 'intFlag'
 *	Parameters:	void
 *  Return:		uint8_t loadInt : as long as updating the 'intFlag' variable, it
 * 								  returns the same value as a uint8_t
 * 
 */
uint8_t	WaspSensorCities::loadInt() 
{		
	intFlag=0;
	
	delay(1);
	digitalWrite(SENS_INT_CITIES_ENABLE, LOW);
	delay(10);
	digitalWrite(SENS_INT_CITIES_CLK_INH, LOW);
	delay(1);

	if(digitalRead(SENS_INT_CITIES_DO)) intFlag |= SENS_CITIES_HUMIDITY;
	delay(2);

	digitalWrite(SENS_INT_CITIES_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_CITIES_DO)) intFlag |= 2; // empty: not mounted
	delay(1);
	digitalWrite(SENS_INT_CITIES_CLK_REG, LOW);
	delay(2);

	digitalWrite(SENS_INT_CITIES_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_CITIES_DO)) intFlag |= 4; // empty: connected to ground
	delay(1);
	digitalWrite(SENS_INT_CITIES_CLK_REG, LOW);
	delay(2);

	digitalWrite(SENS_INT_CITIES_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_CITIES_DO)) intFlag |= SENS_CITIES_DUST;
	delay(1);
	digitalWrite(SENS_INT_CITIES_CLK_REG, LOW);
	delay(2);

	digitalWrite(SENS_INT_CITIES_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_CITIES_DO)) intFlag |= SENS_CITIES_AUDIO;
	delay(1);
	digitalWrite(SENS_INT_CITIES_CLK_REG, LOW);
	delay(2);
      
	digitalWrite(SENS_INT_CITIES_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_CITIES_DO)) intFlag |= SENS_CITIES_LDR;
	delay(1);
	digitalWrite(SENS_INT_CITIES_CLK_REG, LOW);
	delay(2);
      
	digitalWrite(SENS_INT_CITIES_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_CITIES_DO)) intFlag |= SENS_CITIES_LD;
	delay(1);
	digitalWrite(SENS_INT_CITIES_CLK_REG, LOW);
	delay(2);

	digitalWrite(SENS_INT_CITIES_CLK_REG, HIGH);
	delay(1);
	if(digitalRead(SENS_INT_CITIES_DO)) intFlag |= SENS_CITIES_TEMPERATURE;
	delay(1);
	digitalWrite(SENS_INT_CITIES_CLK_REG, LOW);
	delay(2);
	
	delay(200);
	digitalWrite(SENS_INT_CITIES_ENABLE, HIGH);
	digitalWrite(SENS_INT_CITIES_CLK_INH, HIGH);
	
	return intFlag;
}

// Private Methods //////////////////////////////////////////////////////////////


/* readTempDS1820() - reads the DS1820 temperature sensor
 *
 * It reads the DS1820 temperature sensor
 */
float WaspSensorCities::readTempDS1820()
{
	// Select analog 4 as pin to be used
	// 'false' input means that no 3v3 power supply is managed
	// So, the Sensor Board and the sensor switch must be 
	// powered on prior using this function
	return 	Utils.readTempDS1820( 17, false );
}



/*	setResistor: calculates the resistor value in function of the entered threshold
 * 				 and sets the digipot for B digipots
 *	Parameters:	uint8_t address : I2C address of the digipot
 *  			float value : load resistor value selected
 * 	Return: 	void
 * 
 */
void WaspSensorCities::setDigipot1(uint8_t address, float value)
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
void WaspSensorCities::setDigipot0(uint8_t address, float value)
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


/* dustConversion: converts the value read for the dust sensor from voltage into
 * 				   dust concentration in mg/m³
 * Parameters: readValue : value read from AD converter (expressed in bits)
 * Return:	 float audio : dust concentration in mg/m³
 *
 */ float WaspSensorCities::dustConversion(int readValue)
{
	float dust = 0;
   
  	dust = ((float) readValue/310-0.0)/5;
   
	return(dust);
}

/*	ldConversion: converts the value read at the analog to digital converter
 * 				  into a distance value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : distance marked by the sensor in mm
 * 
 */
float WaspSensorCities::ldConversion(int readValue)
{
	float ld = 0;
   
	ld = float(readValue) * 11 / (1023);
      
	return(ld);
}

/* audioConversion: converts audio value read from ANALOG6. It sets the gain for
 * 					 the audio amplifier. Get LookUpTable values stored in
 * 					 EEPROM[256-277] and make the conversion from bits to dBSPLAs
 * 
 * Parameters: readValue : value read from AD converter (expressed in bits)
 * Return:	 float audio : sound level in dBSPLAs (range from 50 to 100)
 *
 */ 
float WaspSensorCities::audioConversion(int readValue)
{
	float audio = 0;	
	uint8_t low,high=0;
	int LUT[11];

	// Read EEPROM calibration parameters
	for(int i=0;i<11;i++)
	{    
		high=Utils.readEEPROM(SENS_NOISE_ADDRESS+i*2); 
		low=Utils.readEEPROM(SENS_NOISE_ADDRESS+i*2+1);    

		LUT[i]=high*256+low;		
	}	

	if(readValue<LUT[0]) audio=50.0;
	else if(readValue<LUT[1]) audio=50.0+5.0*(readValue-LUT[0])/(LUT[1]-LUT[0]);
	else if(readValue<LUT[2]) audio=55.0+5.0*(readValue-LUT[1])/(LUT[2]-LUT[1]);
	else if(readValue<LUT[3]) audio=60.0+5.0*(readValue-LUT[2])/(LUT[3]-LUT[2]);
	else if(readValue<LUT[4]) audio=65.0+5.0*(readValue-LUT[3])/(LUT[4]-LUT[3]);
	else if(readValue<LUT[5]) audio=70.0+5.0*(readValue-LUT[4])/(LUT[5]-LUT[4]);
	else if(readValue<LUT[6]) audio=75.0+5.0*(readValue-LUT[5])/(LUT[6]-LUT[5]);
	else if(readValue<LUT[7]) audio=80.0+5.0*(readValue-LUT[6])/(LUT[7]-LUT[6]);
	else if(readValue<LUT[8]) audio=85.0+5.0*(readValue-LUT[7])/(LUT[8]-LUT[7]);
	else if(readValue<LUT[9]) audio=90.0+5.0*(readValue-LUT[8])/(LUT[9]-LUT[8]);
	else if(readValue<LUT[10]) audio=95.0+5.0*(readValue-LUT[9])/(LUT[10]-LUT[9]);
	else audio=100.0; 

	return(audio);
}

/*	ldrConversion: converts the value read at the analog to digital converter
 * 				   into a voltage
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : voltage in the LDR sensor load resistor
 * 
 */
float WaspSensorCities::ldrConversion(int readValue)
{
	float ldr = 0;
   
	ldr = (float(readValue)*100/1023);
      
	return(ldr);
}

/*	temperatureConversion: converts the value read at the analog to digital
 * 						   converter corresponding to the temperature sensor
 * 						   into a temperature value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
float WaspSensorCities::temperatureConversion(int readValue)
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
float WaspSensorCities::humidityConversion(int readValue)
{
	float humidity = 0;
   
	humidity = float(readValue) * 5000 / 1023;
   
	humidity = (humidity - 800) / 31;
   
	return(humidity);
   
}

/*	ultrasoundConversion: converts the value read at the analog to digital converter
 * 						  into a distance in m
 *	Parameters:	uint16_t readValue : value read from the ADC input
 *  Return:		float distance : distance measured by the ultrasound sensor in m
 * 								 -1.0 for error in sensor type selection
 * 
 */
float WaspSensorCities::ultrasoundConversion(uint16_t socket, uint8_t model)
{
	float distance = 0;
   
	distance = float(analogRead(socket)) * 3300 / 1023;

	switch( model )
	{
		case	SENS_US_WRA1	:	if ( socket == ANALOG4 )
									{
										distance = distance / 3.2;
									} else
									{
										distance = distance / 1.77;
									}
									break;

		case	SENS_US_EZ0		:	if ( socket == ANALOG4 )
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


WaspSensorCities SensorCities=WaspSensorCities();
