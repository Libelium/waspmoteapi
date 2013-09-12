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
 *  Version:		0.13
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, Manuel Calahorra, Yuri Carmona, Jorge Casanova
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
	
	TSL2561(TSL2561_ADDR_FLOAT);

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
			case	SENS_AMBIENT_LUX	:		digitalWrite(SENS_AMBIENT_LUX_PWR,HIGH);
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
			case	SENS_AMBIENT_LUX	:		digitalWrite(SENS_AMBIENT_LUX_PWR,LOW);
												break;
			default							:	return -1;
		}
	} else return 0;
	
	return 1;
}

float WaspSensorAmbient::readSensirionTemperature(void)
{
	float temperature;
	
	temperature = readSensirion(SENS_AMBIENT_TEMPERATURE);
	
	return temperature;
}

float WaspSensorAmbient::readSensirionHumidity(void)
{
	float humidity;
	
	humidity = readSensirion(SENS_AMBIENT_HUMIDITY);
	
	return humidity;
	
}

float WaspSensorAmbient::readLDR(void)
{
	float luminosity;
	int aux;

	aux = analogRead(ANALOG6);
	luminosity = 3.3*aux/1023;

	return luminosity;
}


// Public Methods //////////////////////////////////////////////////////////////


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
	int ack2, ack3, i = 0;
	long a = 0;
	long b = 0;
	
	const byte HUMIDITY = B00000101;
	const byte TEMPERATURE = B00000011;
	
	

	if( parameter==SENS_AMBIENT_TEMPERATURE ) parameter=TEMPERATURE;
	else if( parameter==SENS_AMBIENT_HUMIDITY ) parameter=HUMIDITY;
		
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
	b = millis()-a;

  
  //**************************************
  //CRC not taken into account
  
	pinMode(SENS_AMBIENT_SENSIRION_DATA, OUTPUT);
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA, HIGH);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, HIGH);
	delayMicroseconds(400);
	digitalWrite(SENS_AMBIENT_SENSIRION_CLK, LOW);
	
	digitalWrite(SENS_AMBIENT_SENSIRION_DATA, LOW);
  
	if( parameter==TEMPERATURE ) return temperatureConversion(val_read,SENS_PREC_HIGH);
	else if( parameter==HUMIDITY ) return humidityConversion(val_read,SENS_PREC_HIGH);
} 

/*	temperatureConversion: converts the value read from the Sensirion into a
 * 						   temperature value
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
  
	//in case of saturation
	if( humidity > 99.0 )
	{
		humidity = 100.0;
	}
	
	return(humidity);
}

/*	LUXConversion: converts the value read from the LUX Sensor into a
 * 						   LUX value
 *	Parameters:	int readValue : value read from the Sensirion
 * 				int precision : format at which the sensor was read
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
float WaspSensorAmbient::TSL2561(uint8_t addr) {
  _addr = addr;
  _initialized = false;
  _integration = TSL2561_INTEGRATIONTIME_13MS;
  _gain = TSL2561_GAIN_16X;

  // we cant do wire initialization till later, because we havent loaded Wire yet
}

boolean WaspSensorAmbient::begin(void) {
  Wire.begin();

 // Initialise I2C
  Wire.beginTransmission(_addr);
#if ARDUINO >= 100
  Wire.write(TSL2561_REGISTER_ID);
#else
  Wire.send(TSL2561_REGISTER_ID);
#endif
  Wire.endTransmission();
  Wire.requestFrom(_addr, 1);
#if ARDUINO >= 100
  int x = Wire.read();
#else
  int x = Wire.receive();
#endif
  //Serial.print("0x"); Serial.println(x, HEX);
  if (x & 0x0A ) {
    //Serial.println("Found TSL2561");
  } else {
    return false;
  }
  _initialized = true;

  // Set default integration time and gain
  setTiming(_integration);
  setGain(_gain);
  // Note: by default, the device is in power down mode on bootup
  disable();

  return true;
}

void WaspSensorAmbient::enable(void)
{
  if (!_initialized) begin();

  // Enable the device by setting the control bit to 0x03
  write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_CONTROL_POWERON);
  delay(100);
}

void WaspSensorAmbient::disable(void)
{
  if (!_initialized) begin();

  // Disable the device by setting the control bit to 0x03
  write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_CONTROL_POWEROFF);
}


void WaspSensorAmbient::setGain(tsl2561Gain_t gain) {
  if (!_initialized) begin();

  enable();
  _gain = gain;
  write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, _integration | _gain);  
  disable();
}

void WaspSensorAmbient::setTiming(tsl2561IntegrationTime_t integration)
{
  if (!_initialized) begin();

  enable();
  _integration = integration;
  write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, _integration | _gain);  
  disable();
}

uint32_t WaspSensorAmbient::calculateLux(uint16_t ch0, uint16_t ch1)
{
  unsigned long chScale;
  unsigned long channel1;
  unsigned long channel0;

  switch (_integration)
  {
    case TSL2561_INTEGRATIONTIME_13MS:
      chScale = TSL2561_LUX_CHSCALE_TINT0;
      break;
    case TSL2561_INTEGRATIONTIME_101MS:
      chScale = TSL2561_LUX_CHSCALE_TINT1;
      break;
    default: // No scaling ... integration time = 402ms
      chScale = (1 << TSL2561_LUX_CHSCALE);
      break;
  }

  // Scale for gain (1x or 16x)
  if (!_gain) chScale = chScale << 4;

  // scale the channel values
  channel0 = (ch0 * chScale) >> TSL2561_LUX_CHSCALE;
  channel1 = (ch1 * chScale) >> TSL2561_LUX_CHSCALE;

  // find the ratio of the channel values (Channel1/Channel0)
  unsigned long ratio1 = 0;
  if (channel0 != 0) ratio1 = (channel1 << (TSL2561_LUX_RATIOSCALE+1)) / channel0;

  // round the ratio value
  unsigned long ratio = (ratio1 + 1) >> 1;

  unsigned int b, m;

#ifdef TSL2561_PACKAGE_CS
  if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1C))
    {b=TSL2561_LUX_B1C; m=TSL2561_LUX_M1C;}
  else if (ratio <= TSL2561_LUX_K2C)
    {b=TSL2561_LUX_B2C; m=TSL2561_LUX_M2C;}
  else if (ratio <= TSL2561_LUX_K3C)
    {b=TSL2561_LUX_B3C; m=TSL2561_LUX_M3C;}
  else if (ratio <= TSL2561_LUX_K4C)
    {b=TSL2561_LUX_B4C; m=TSL2561_LUX_M4C;}
  else if (ratio <= TSL2561_LUX_K5C)
    {b=TSL2561_LUX_B5C; m=TSL2561_LUX_M5C;}
  else if (ratio <= TSL2561_LUX_K6C)
    {b=TSL2561_LUX_B6C; m=TSL2561_LUX_M6C;}
  else if (ratio <= TSL2561_LUX_K7C)
    {b=TSL2561_LUX_B7C; m=TSL2561_LUX_M7C;}
  else if (ratio > TSL2561_LUX_K8C)
    {b=TSL2561_LUX_B8C; m=TSL2561_LUX_M8C;}
#else
  if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1T))
    {b=TSL2561_LUX_B1T; m=TSL2561_LUX_M1T;}
  else if (ratio <= TSL2561_LUX_K2T)
    {b=TSL2561_LUX_B2T; m=TSL2561_LUX_M2T;}
  else if (ratio <= TSL2561_LUX_K3T)
    {b=TSL2561_LUX_B3T; m=TSL2561_LUX_M3T;}
  else if (ratio <= TSL2561_LUX_K4T)
    {b=TSL2561_LUX_B4T; m=TSL2561_LUX_M4T;}
  else if (ratio <= TSL2561_LUX_K5T)
    {b=TSL2561_LUX_B5T; m=TSL2561_LUX_M5T;}
  else if (ratio <= TSL2561_LUX_K6T)
    {b=TSL2561_LUX_B6T; m=TSL2561_LUX_M6T;}
  else if (ratio <= TSL2561_LUX_K7T)
    {b=TSL2561_LUX_B7T; m=TSL2561_LUX_M7T;}
  else if (ratio > TSL2561_LUX_K8T)
    {b=TSL2561_LUX_B8T; m=TSL2561_LUX_M8T;}
#endif

  unsigned long temp;
  temp = ((channel0 * b) - (channel1 * m));

  // do not allow negative lux value
  if (temp < 0) temp = 0;

  // round lsb (2^(LUX_SCALE-1))
  temp += (1 << (TSL2561_LUX_LUXSCALE-1));

  // strip off fractional portion
  uint32_t lux = temp >> TSL2561_LUX_LUXSCALE;

  // Signal I2C had no errors
  return lux;
}

uint32_t WaspSensorAmbient::getFullLuminosity (void)
{
  if (!_initialized) begin();

  // Enable the device by setting the control bit to 0x03
  enable();

  // Wait x ms for ADC to complete
  switch (_integration)
  {
    case TSL2561_INTEGRATIONTIME_13MS:
      delay(14);
      break;
    case TSL2561_INTEGRATIONTIME_101MS:
      delay(102);
      break;
    default:
      delay(400);
      break;
  }

  uint32_t x;
  x = read16(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN1_LOW);
  x <<= 16;
  x |= read16(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN0_LOW);

  disable();

  return x;
}
uint16_t WaspSensorAmbient::getLuminosity (uint8_t channel) {

  uint32_t x = getFullLuminosity();

  if (channel == 0) {
    // Reads two byte value from channel 0 (visible + infrared)
    return (x & 0xFFFF);
  } else if (channel == 1) {
    // Reads two byte value from channel 1 (infrared)
    return (x >> 16);
  } else if (channel == 2) {
    // Reads all and subtracts out just the visible!
    return ( (x & 0xFFFF) - (x >> 16));
  }
  
  // unknown channel!
  return 0;
}


uint16_t WaspSensorAmbient::read16(uint8_t reg)
{
  uint16_t x; uint16_t t;

  Wire.beginTransmission(_addr);
#if ARDUINO >= 100
  Wire.write(reg);
#else
  Wire.send(reg);
#endif
  Wire.endTransmission();

  Wire.requestFrom(_addr, 2);
#if ARDUINO >= 100
  t = Wire.read();
  x = Wire.read();
#else
  t = Wire.receive();
  x = Wire.receive();
#endif
  x <<= 8;
  x |= t;
  return x;
}



void WaspSensorAmbient::write8 (uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(_addr);
#if ARDUINO >= 100
  Wire.write(reg);
  Wire.write(value);
#else
  Wire.send(reg);
  Wire.send(value);
#endif
  Wire.endTransmission();
}

/*	LUXConversion: converts the value read from the LUX Sensor into a
 * 						   LUX value
 *	Parameters:	int readValue : value read from the Sensirion
 * 				int precision : format at which the sensor was read
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
float WaspSensorAmbient::readLUXbright()
{
  setGain(TSL2561_GAIN_0X);         		// set no gain (for bright situtations)
  setTiming(TSL2561_INTEGRATIONTIME_13MS);  // shortest integration time (bright light)
  uint32_t lum = getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  return calculateLux(full, ir);
}

float WaspSensorAmbient::readLUXmedium()
{ 
  setGain(TSL2561_GAIN_16X);         		// set no gain (for bright situtations)
  setTiming(TSL2561_INTEGRATIONTIME_101MS); // shortest integration time (bright light)
  uint32_t lum = getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  return calculateLux(full, ir);
}

float WaspSensorAmbient::readLUXdim()
{
  setGain(TSL2561_GAIN_16X);        		 // set no gain (for bright situtations)
  setTiming(TSL2561_INTEGRATIONTIME_402MS);  // shortest integration time (bright light)
  uint32_t lum = getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  return calculateLux(full, ir);
}

  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparions you want!
float WaspSensorAmbient::readLUMINOSITYbright()
{
  setGain(TSL2561_GAIN_0X);         		// set no gain (for bright situtations)
  setTiming(TSL2561_INTEGRATIONTIME_13MS);  // shortest integration time (bright light)
  uint32_t lum = getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  USB.print("IR: "); USB.print(ir);   USB.print("\t");
  USB.print("Full: "); USB.print(full);   USB.print("\t");
  USB.print("Visible: "); USB.print(full - ir);   USB.print("\t");
  USB.print("Lux: "); USB.println(calculateLux(full, ir));
}

float WaspSensorAmbient::readLUMINOSITYmedium()
{
  setGain(TSL2561_GAIN_16X);         		// set no gain (for bright situtations)
  setTiming(TSL2561_INTEGRATIONTIME_101MS); // shortest integration time (bright light)
  uint32_t lum = getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  USB.print("IR: "); USB.print(ir);   USB.print("\t");
  USB.print("Full: "); USB.print(full);   USB.print("\t");
  USB.print("Visible: "); USB.print(full - ir);   USB.print("\t");
  USB.print("Lux: "); USB.println(calculateLux(full, ir));
}

float WaspSensorAmbient::readLUMINOSITYdim()
{
  setGain(TSL2561_GAIN_16X);         		// set no gain (for bright situtations)
  setTiming(TSL2561_INTEGRATIONTIME_402MS); // shortest integration time (bright light)
  uint32_t lum = getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  USB.print("IR: "); USB.print(ir);   USB.print("\t");
  USB.print("Full: "); USB.print(full);   USB.print("\t");
  USB.print("Visible: "); USB.print(full - ir);   USB.print("\t");
  USB.print("Lux: "); USB.println(calculateLux(full, ir));
}

WaspSensorAmbient SensorAmbient=WaspSensorAmbient();
