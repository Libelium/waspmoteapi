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
 *  Implementation:	Carlos Bello
 */
#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

// BME280 library for reading temperature, humidity and pressure values
#include "BME280.h"
#include "Wire.h"
#include "WaspConstants.h"
#include "WaspSensorAgr_v30.h"
#include "UltrasoundSensor.h"
#include <TSL2561.h>

//**********************************************************************
// AGRICULTURE SENSOR BOARD CLASS
//**********************************************************************
//!*********************************************************************
//!	Name:	WaspSensorAgr_v30()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*********************************************************************
WaspSensorAgr_v30::WaspSensorAgr_v30()
{	
	// init power supply to OFF state
	PWR.setSensorPower(SENS_3V3, SENS_OFF);	
	// clear array
	//memset( plv_array, 0x00, sizeof(plv_array) );	
}

//!*********************************************************************
//!	Name:	ON()										
//!	Description: Switch ON the power supply and configure the I/O pins		
//!	Param : void														
//!	Returns: void							
//!*********************************************************************
void WaspSensorAgr_v30::ON() {
	// Configure pins
	pinMode(DIGITAL0,OUTPUT);	//E4 PWM2 RESERVED
	pinMode(DIGITAL1,OUTPUT);	//WATERMARK POWER ON
	pinMode(DIGITAL2,INPUT);	//ANEMOMETER SIGNAL INPUT
	pinMode(DIGITAL3,OUTPUT);	//I2C MAIN PIN
	pinMode(DIGITAL5,OUTPUT);	//DENTROMETER AND PT1000 POWER ON
	pinMode(DIGITAL6,OUTPUT);	//ADDRESS B WATERMARK
	pinMode(DIGITAL7,OUTPUT);	//RADIATION POWER ON
	pinMode(DIGITAL8,OUTPUT);	//ADDRESS A WATERMARK

	pinMode(ANA0,OUTPUT);		//WEATHER STATION POWER ON
	pinMode(ANA1,OUTPUT);		//NO USE
	pinMode(ANA3,INPUT);		//PLUVIOMETER DATA
	pinMode(ANA5,INPUT);		//WATERMARK DATA
	pinMode(ANA6,OUTPUT);		//LEAF WETNESS POWER ON	
	delay(10);
	//I2C ISOLATOR PIN ENABLE
	pinMode(I2C_PIN_OE, OUTPUT);
	digitalWrite(I2C_PIN_OE, LOW);
	// Switch ON 3V3 for supplying the board
	PWR.setSensorPower(SENS_3V3, SENS_ON);
	
    if (_boot_version < 'H')
    {
        USB.println(F("\n***************  WARNING *******************"));
        USB.println(F("This example is valid only for Waspmote v15."));
        USB.println(F("Your Waspmote version is v12."));
        USB.println(F("*******************************************"));
		return (void)0; 
    }    	   
}

//!*********************************************************************
//!	Name:	OFF()										
//!	Description: Switch OFF the power supply	
//!	Param : void														
//!	Returns: void							
//!*********************************************************************
void WaspSensorAgr_v30::OFF(){ 
	digitalWrite(DIGITAL0,LOW);	
	digitalWrite(DIGITAL4,LOW);
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(ANA0,LOW);
	digitalWrite(ANA1,LOW);
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);
	// Switch OFF 3V3
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	delay(100);
}
/*	conversion: converts the value read from the PT1000 and dendrometer ADC into
 * 				the units of the sensor
 *	Parameters: byte data_input[3] : three bytes from the ADC conversion
 * 				uint8_t type : 1 for PT1000 reading, 0 for dendrometer reading
 *  Return:	float value : temperature (ºC) or diameter (mm) in function of the sensor
 * 
 */
float WaspSensorAgr_v30::conversion(byte data_input[3], uint8_t type)
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
 
void	WaspSensorAgr_v30::sleepAgr(const char*	time2wake,
									uint8_t offset,
									uint8_t mode,
									uint8_t option)
{
	#if DEBUG_AGR > 0
	PRINT_AGR(F("sleepAgr function:\r\n"));	
	#endif	
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
 
void	WaspSensorAgr_v30::sleepAgr(const char* time2wake,
									uint8_t offset, 
									uint8_t mode, 
									uint8_t option, 
									uint8_t agr_interrupt)
{
	#if DEBUG_AGR > 0
	PRINT_AGR(F("sleepAgr interrupt function:\r\n"));	
	#endif	
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
	digitalWrite(DIGITAL0,LOW);	
	digitalWrite(DIGITAL2,LOW);
	digitalWrite(DIGITAL3,LOW);
	digitalWrite(DIGITAL4,LOW);
	digitalWrite(DIGITAL6,LOW);
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(ANA0,LOW);
	digitalWrite(ANA1,LOW);
	digitalWrite(ANA2,LOW);
	digitalWrite(ANA3,LOW);
	digitalWrite(ANA4,LOW);
	digitalWrite(ANA5,LOW);
	
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

//!*********************************************************************
//!	Name:	getTemperature()										
//!	Description: Gets the temperature from the BME280 sensor
//!	Param : void														
//!	Returns: float: temperature value read		
//!*********************************************************************
float WaspSensorAgr_v30::getTemperature() {
	float value = 0;
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	//Configure the BME280 Sensor (Temperature, Humidity and Pressure)
	BME.ON();
	delay(100);	
	value = BME.getTemperature(BME280_OVERSAMP_1X, 0);
	#if DEBUG_AGR==1
		PRINT_AGR(F("getTemperature:"));
		USB.println(value);		
	#endif
		
	#if DEBUG_AGR==2
		PRINT_AGR(F("getTemperature:"));
		USB.println(value);	
		PRINT_AGR(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);			
	#endif 	
	delay(100);
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);
	
	// Read the temperature from the BME280 Sensor
	return value;
}

//!*********************************************************************
//!	Name:	getHumidity()										
//!	Description: Gets the Humidity from the BME280 sensor	
//!	Param : void														
//!	Returns: float: humidity value read						
//!*********************************************************************
float WaspSensorAgr_v30::getHumidity() {
	float value = 0;
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	//Configure the BME280 Sensor (Temperature, Humidity and Pressure)
	BME.ON();
	delay(100);	
	// Read the humidity from the BME280 Sensor
	value = BME.getHumidity(BME280_OVERSAMP_1X);
	#if DEBUG_AGR==1
		PRINT_AGR(F("getHumidity:"));
		USB.println(value);		
	#endif
		
	#if DEBUG_AGR==2
		PRINT_AGR(F("getHumidity:"));
		USB.println(value);	
		PRINT_AGR(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);	
	#endif    	
	delay(100);
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);
	// Read the temperature from the BME280 Sensor	
	return value;
}

//!*********************************************************************
//!	Name:	getPressure()										
//!	Description: Gets the Pressure from the BME280 sensor
//!	Param : void														
//!	Returns:  float: pressure value read								
//!*********************************************************************
float WaspSensorAgr_v30::getPressure() {
	float value = 0;
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	//Configure the BME280 Sensor (Temperature, Humidity and Pressure)
	BME.ON();
	delay(100);	
	// Read the pressure from the BME280 Sensor
	value = BME.getPressure(BME280_OVERSAMP_1X, 0);
	delay(100);
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);
	#if DEBUG_AGR==1
		PRINT_AGR(F("getPressure:"));
		USB.println(value);		
	#endif
		
	#if DEBUG_AGR==2
		PRINT_AGR(F("getPressure:"));
		USB.println(value);	
		PRINT_AGR(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);	
	#endif  	
	// Read the temperature from the BME280 Sensor	
	return value;	
}

//!*********************************************************************
//!	Name:	getDistance()										
//!	Description: Gets distance from Ultrasound Sensor
//!	Param : void														
//!	Returns:  float: distance value read								
//!*********************************************************************
uint16_t WaspSensorAgr_v30::getDistance(){
	uint16_t value;
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	delay(100);	
	value = Ultrasound.getDistance();
	delay(100);
	
	#if DEBUG_AGR > 0
		PRINT_AGR(F("getDistance function: "));
		USB.println(value);
	#endif		
	
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);	
	return value;
}

//!*********************************************************************
//!	Name:	getLuxes()										
//!	Description: Gets luxes from TSL2561
//!	Param : gain ( OUTDOOR OR INDOOR)														
//!	Returns:  float: luxes value read								
//!*********************************************************************
uint32_t WaspSensorAgr_v30::getLuxes(uint8_t gain){
	uint32_t value;
	TSL.ON();
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	delay(100);
	switch (gain)
	{
		case OUTDOOR:
			TSL.getLuminosity(TSL2561_HIGH_RES, TSL2561_GAIN_1); 	
		break;
		
		case INDOOR:
			TSL.getLuminosity(TSL2561_HIGH_RES, TSL2561_GAIN_16); 	
		break;
	}
	#if DEBUG_AGR >= 1
	PRINT_AGR(F("getLuxes function: "));
	USB.println(value);
	#endif		
	value = TSL.lux;
	delay(100);
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);	
	return value;
}

// Preinstantiate Objects //////////////////////////////////////////////////////
WaspSensorAgr_v30 Agriculture = WaspSensorAgr_v30();



/*	
 * Class constructor
 * 
 */
watermarkClass::watermarkClass(uint8_t socket)
{
	_watermarkSocket = socket;
}

/*	readWatermark: reads the frequency of the adaptation circuit of the Watermark
 * 				   sensor indicated in sens
 *  Return:	float value : watermark circuit frequency
 * 						  -1 if wrong sensor selected
 * 
 */
float watermarkClass::readWatermark()
{
	int value = 0;
	int previous_value = 0;
	int counter = 0;
	float freq = 0;
	
	// switch on
    digitalWrite(WATERMARK_ON,HIGH);
 
	switch (_watermarkSocket)
	{
		case SOCKET_1:
		case SOCKET_B:
		    digitalWrite(WATERMARK_DIR_A,LOW);
		    digitalWrite(WATERMARK_DIR_B,LOW);
		break;
		case SOCKET_2:
		case SOCKET_E:
			digitalWrite(WATERMARK_DIR_A,HIGH);
			digitalWrite(WATERMARK_DIR_B,LOW);
		break;
		case SOCKET_3:
		case SOCKET_C:
			digitalWrite(WATERMARK_DIR_A,LOW);
			digitalWrite(WATERMARK_DIR_B,HIGH);
		break;
	}
	
	#if DEBUG_AGR==2
	PRINT_AGR(F("readWatermark Select:"));
	USB.println(_watermarkSocket);
	#endif
	
	const uint32_t total_timeout = 10000;
	const uint32_t total_counts  = 500;
	uint32_t current_millis;
	uint32_t previous = millis();
	
	// init counter
	counter = 0;
	
	while (counter < total_counts)
	{
		previous_value = value;
		value = digitalRead(ANA5);
		if ((previous_value == 1) && (value == 0))
		{
			counter++;
		}
		
		// get current 'millis' time
		current_millis = millis();
		
		if (current_millis-previous > total_timeout)
		{
			break;
		}
		else if (current_millis < previous)
		{
			previous = millis();
		}
	}

	// switch off
	digitalWrite(WATERMARK_ON,LOW);
	
	if (counter >= total_counts)
	{
		return freq = ((float)total_counts*1000.0) / float((millis() - previous));
	}
	
	// check no counts (bad behaviour)
	if (counter == 0)
	{
		return 0;
	}
	
	return freq = (float)counter*1000.0 / float(total_timeout);
}


/*	
 * Class constructor
 * 
 */
leafWetnessClass::leafWetnessClass()
{
};

/*	getLeafWetness: converts the value read at the analog to digital	converter
 * 				   input corresponding to the leaf wetness sensor into a percentage
 *	Parameters:
 *  Return:		float value : wetness measured by the sensor in %RH
 * 
 */
float leafWetnessClass::getLeafWetness() {
	float aux = 0;
	float value = 0;	
	analogReference(DEFAULT);	
	digitalWrite(ANA6,HIGH);
	delay(100);
	aux = analogRead(ANALOG3);
	delay(100);
	//Convert analog value to %RH
	//This sensor has a range between 1-3.3 V
	//So that the ADC reads values between 310-1023
	//The next formula can be extracted by linearizing with two points
	// (x1 , y1) = (310, 100 %)
	// (x2 , y2) = (1023, 0  %)
	// (y-y1)/(y2-y1) = (x-x1)/(x2-x1)	
	#if DEBUG_AGR > 0
		PRINT_AGR(F("getLeafWetness value Analog Read:"));
		USB.println(aux);		
	#endif

	if(aux > 310.0){
		value = (1023.0*100.0/713.0)-(100.0/713.0)*aux;
	#if DEBUG_AGR==2
		PRINT_AGR(F("getLeafWetness value aux>310:"));
		USB.println(value);		
	#endif		
	}
	else{
		value=100.0;
	#if DEBUG_AGR==2
		PRINT_AGR(F("getLeafWetness value < 310:"));
		USB.println(value);		
	#endif		
	}
	digitalWrite(ANA6,LOW);
	return value;
}


/*	
 * Class constructor
 * 
 */
ds18b20Class::ds18b20Class()
{
}

/*	readDS18b20: reads the analog to digital converter input to which is connected
 * 				the	PT1000 sensor through the I2C and converts its value into
 * 				temperature (ºC)
 *	Parameters: void
 *  Return:	float value : temperature in Celsius (ºC)
 * 
 */
float ds18b20Class::readDS18b20(void)
{	
	float value_ds18b20 = 0;
	digitalWrite(DEN_PT1000_ON,HIGH);
	delay(100);	
	value_ds18b20 = Utils.readTempDS1820(15,true);  
	delay(100);
	digitalWrite(DEN_PT1000_ON,LOW);
	#if DEBUG_AGR > 0
	PRINT_AGR(F("readDS18b20:"));
	USB.println(value_ds18b20);		
	#endif					
	return value_ds18b20;  
}


/*	
 * Class constructor
 * 
 */
pt1000Class::pt1000Class()
{
}


/*	readPT1000: reads the analog to digital converter input to which is connected
 * 				the	PT1000 sensor through the I2C and converts its value into
 * 				temperature (ºC)
 *	Parameters: void
 *  Return:	float value : temperature in Celsius (ºC)
 * 
 */
float pt1000Class::readPT1000(void)
{	
	const byte pt1000_channel = B10100000;
	byte data_pt1000[3] = {0,0,0};
	float value_pt1000 = 0;
	digitalWrite(DEN_PT1000_ON,HIGH);
	delay(100);	
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	delay(100);
	
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
	value_pt1000 = conversion(data_pt1000,1);	
	delay(1000);
	#if DEBUG_AGR > 0
	PRINT_AGR(F("readPT1000 value conversion:"));
	USB.println(value_pt1000);		
	#endif	
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);
	digitalWrite(DEN_PT1000_ON,LOW);		
	return value_pt1000;  
}

/*	
 * Class constructor
 * 
 */
dendrometerClass::dendrometerClass()
{
}

/*	readDendrometer: reads the analog to digital converter input to which is
 * 					 connected the dendrometer through the I2C and converts its
 * 					 value into mm
 *	Parameters: void
 *  Return:	float value : trunk diameter read by the dendrometer in mm
 * 
 */
float dendrometerClass::readDendrometer(void)
{
	const byte dendro_channel = B10100001;
	byte data_dendro[3] = {0,0,0};
	float value_dendro = 0;
	digitalWrite(DEN_PT1000_ON,HIGH);	
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);	
	
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
	/*
	if (Wire.isON && !ACC.isON && RTC.isON!=1)
	{
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
	*/
	digitalWrite(DEN_PT1000_ON,LOW);	
  	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);
	#if DEBUG_AGR==1
	PRINT_AGR(F("readDendrometer value without conversion:"));
	USB.println(value_dendro);		
	#endif
	#if DEBUG_AGR==2
	PRINT_AGR(F("readDendrometer value without conversion:"));
	USB.println(value_dendro);
	PRINT_AGR(F("readDendrometer value conversion:"));
	USB.println(value_dendro = conversion(data_dendro,0));	
	#endif	
	return value_dendro = conversion(data_dendro,0);
}


/*	
 * Class constructor
 * 
 */
radiationClass::radiationClass()
{
}

/*	readRadiation: reads the analog to digital converter to which is connected the
 * 				   solar radiation sensor through the I2C and converts its value
 * 				   into voltage
 *	Parameters: void
 *  Return:	float value : solar radiation in volts
 * 
 */
float radiationClass::readRadiation(void)
{
	byte data_apogee[2] = {0,0};
	long val = 0;
	float val_def = 0;
	digitalWrite(RADIATION_ON,HIGH);
	delay(100);	
	//Switch ON I2C
	pinMode(I2C_PIN_OE, OUTPUT);
	digitalWrite(I2C_PIN_OE, HIGH);
	delay(100);
	
	// Init I2C bus
	if( !Wire.isON ) Wire.begin();
	Wire.requestFrom(I2C_ADDRESS_AGR_RADIATION, 2);
	while (Wire.available())
	{
		Wire.receive();
	}
	delay(50);
	Wire.requestFrom(I2C_ADDRESS_AGR_RADIATION, 2);
	int i = 0;
	while (Wire.available())
	{
		data_apogee[i] = Wire.receive();
		i++;
	}
	val = long(data_apogee[1]) + long(data_apogee[0])*256;
	val_def = (val - 32769)*9;
	digitalWrite(RADIATION_ON,LOW);	
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);
	#if DEBUG_AGR==1
	PRINT_AGR(F("readRadiation without conversion:"));
	USB.println(val_def);		
	#endif
	#if DEBUG_AGR==2
	PRINT_AGR(F("readRadiation without conversion:"));
	USB.println(val_def);
	PRINT_AGR(F("readRadiation with conversion:"));
	USB.println(val_def/65535);	
	#endif			
	return val_def = val_def/65535;
}


/*	
 * Class constructor
 * 
 */
weatherStationClass::weatherStationClass()
{
}

/*	readAnemometer: reads the number of anemometer pulses during three seconds
 * 					and turns the value into speed (km/h)
 *	Parameters: void
 *  Return:	float value : wind speed (km/h)
 * 
 */
float weatherStationClass::readAnemometer(void)
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
	digitalWrite(WEATHER_STATION_ON,HIGH);	
	while( (millis()-start_anemometer) <= MEAS_TIME )
	{
		previous_reading_anemometer = reading_anemometer;
		reading_anemometer = digitalRead(ANEMOMETER_DATA);	
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
	#if DEBUG_AGR > 0
	PRINT_AGR(F("readAnemometer windSpeed:"));
	USB.println(wind_speed);		
	#endif
	#if DEBUG_AGR > 1
	PRINT_AGR(F("readAnemometer windSpeed:"));
	USB.println(wind_speed);		
	#endif	
	// calculate gust of wind 2.4Km/h per second
	gustWind = 2.4 / ((float)pulse_duration/1000);
	#if DEBUG_AGR > 0
	PRINT_AGR(F("readAnemometer windSpeed:"));
	USB.println(gustWind);		
	#endif
	#if DEBUG_AGR > 1
	PRINT_AGR(F("readAnemometer windSpeed:"));
	USB.println(gustWind);		
	#endif		
  	digitalWrite(WEATHER_STATION_ON,LOW);
	return wind_speed;
}


/*	
 * readVaneDirection
 * 
 */
uint8_t weatherStationClass::readVaneDirection()
{	
	float aux2=0;
	float aux=0;
	uint8_t aux3;
	digitalWrite(WEATHER_STATION_ON,HIGH);
	delay(100);	
	aux=analogRead(ANALOG5);	
	aux2 = (aux*3.3)/1023; // Volts,	k
	if( aux2<0.25 ) aux3=SENS_AGR_VANE_ESE;
	else if( aux2>=0.25 && aux2<0.28 ) aux3=SENS_AGR_VANE_ENE;
	else if( aux2>=0.28 && aux2<0.35 ) aux3=SENS_AGR_VANE_E;
	else if( aux2>=0.35 && aux2<0.5 ) aux3=SENS_AGR_VANE_SSE;
	else if( aux2>=0.5 && aux2<0.65 ) aux3=SENS_AGR_VANE_SE;
	else if( aux2>=0.65 && aux2<0.85 ) aux3=SENS_AGR_VANE_SSW;
	else if( aux2>=0.85 && aux2<1.1 ) aux3=SENS_AGR_VANE_S;
	else if( aux2>=1.1 && aux2<1.38 ) aux3=SENS_AGR_VANE_NNE;
	else if( aux2>=1.38 && aux2<1.6 ) aux3=SENS_AGR_VANE_NE;
	else if( aux2>=1.6 && aux2<1.96 ) aux3=SENS_AGR_VANE_WSW;
	else if( aux2>=1.96 && aux2<2.15 ) aux3=SENS_AGR_VANE_SW;
	else if( aux2>=2.15 && aux2<2.35 ) aux3=SENS_AGR_VANE_NNW;
	else if( aux2>=2.35 && aux2<2.6 ) aux3=SENS_AGR_VANE_N;
	else if( aux2>=2.6 && aux2<2.75 ) aux3=SENS_AGR_VANE_WNW;
	else if( aux2>=2.75 && aux2<2.95 ) aux3=SENS_AGR_VANE_NW;
	else if( aux2>=2.95 ) aux3=SENS_AGR_VANE_W;
	digitalWrite(WEATHER_STATION_ON,LOW);	
	#if DEBUG_AGR > 0
	PRINT_AGR(F("readVaneDirection:"));
	USB.println(aux3);		
	#endif
	#if DEBUG_AGR > 1
	PRINT_AGR(F("readVaneDirection:"));
	USB.println(aux3);		
	#endif		
	return aux3;
}

/*	getVaneDirection: stores in the vaneDirection variable the orientation of the
 * 					  vane calculated from the voltage read at its output
 *	Parameters:
 *  Return:		uint8_t value: Returns Direction
 * 
 */
void weatherStationClass::getVaneDirection(float vane)
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
	#if DEBUG_AGR > 0
	PRINT_AGR(F("getVaneDirection:"));
	USB.println(vaneDirection);		
	#endif
	#if DEBUG_AGR > 1
	PRINT_AGR(F("getVaneDirection:"));
	USB.println(vaneDirection);		
	#endif		
}

/*	getVaneFiltred: stores in the vaneDirection variable the orientation of the
 * 					vane calculated from the voltage read at its output. The 
 * 					measurement is performed doing the mean of several values.				
 *	
 *  Return:		void
 *  Remarks: http://en.wikipedia.org/wiki/Mean_of_circular_quantities
 * 
 */
void weatherStationClass::getVaneFiltered()
{
	int NUM_SAMPLES=20;	
	int SAMPLING_TIME=100; // ms
	int aux;
	float sample[NUM_SAMPLES];
	float vanes[NUM_SAMPLES];
	digitalWrite(ANA0,HIGH);		
	for( int i=0 ; i<NUM_SAMPLES; i++ )
	{
		aux = analogRead(ANALOG5); //read bits 0-1023
		sample[i] = (aux*3.3)/1023; // Volts
		getVaneDirection(sample[i]); // in vane direction
		vanes[i] = vaneDirection;
		delay(SAMPLING_TIME);
		#if DEBUG_AGR > 0
		PRINT_AGR(F("getVaneFiltered sample n:"));
		USB.print(i);
		USB.print(F(" "));
		USB.println(sample[i]);		
		#endif
		#if DEBUG_AGR > 1
		PRINT_AGR(F("getVaneFiltered sample n:"));
		USB.print(i);
		USB.print(F(" "));
		USB.println(sample[i]);		
		#endif				
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
	#if DEBUG_AGR > 0
	PRINT_AGR(F("getVaneFiltered conversion:"));
	USB.println(vaneDirection);		
	#endif
	#if DEBUG_AGR > 1
	PRINT_AGR(F("getVaneFiltered conversion:"));
	USB.println(vaneDirection);		
	#endif		
	digitalWrite(WEATHER_STATION_ON,LOW);	
}

/*  attacPluvioInt: It attaches the pluviometer interruptions
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	weatherStationClass::attachPluvioInt(void) 
{
		#if DEBUG_AGR > 1
		PRINT_AGR(F("attachPluvioInt function:\r\n"));	
		#endif
		enableInterrupts(PLV_INT);
}


/*  detachPluvioInt: It detaches the pluviometer interruptions
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	weatherStationClass::detachPluvioInt(void) 
{
	#if DEBUG_AGR > 1
	PRINT_AGR(F("detachPluvioInt function:\r\n"));	
	#endif	
	disableInterrupts(PLV_INT);
}
/*	readPluviometerHour 
 * 
 * It calculates the rain fall during the previous hour before actual slot.
 * 
 * For example: It is 13.30 pm. Then this function calculates the rain fall for 
 * the whole previous slot. It is said to be the rainfall from 12pm to 13pm
 * 
 */
float weatherStationClass::readPluviometerHour()
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
float weatherStationClass::readPluviometerCurrent()
{
	// Introduce one hour time as '1' hour and '0' hour-offset
	return 	readPluviometer(1, 0);
}

/*	readPluviometerDay 
 * 
 * It calculates the rain fall during the last day
 * 
 */
float weatherStationClass::readPluviometerDay()
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
float weatherStationClass::readPluviometer( uint8_t numHours, int offset)
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
	#if DEBUG_AGR>1
	PRINT_AGR(F("readPluviometer (float):"));	
	USB.println(precipitations);		
	#endif	
	return precipitations;	
}


/*	readPluviometer: reads the number of anemometer pulses during three seconds
 * 					 and turns the value into mm of rain
 *	Parameters: void
 *  Return:	float value : precipitations (mm)
 * 
 */
uint16_t weatherStationClass::readPluviometer()
{
	int reading_pluviometer = 0;
	int previous_reading_pluviometer = 0;
	int value_pluviometer = 0;
	unsigned long start_pluviometer=0;

	value_pluviometer = 0;
	start_pluviometer = millis();
	digitalWrite(WEATHER_STATION_ON,HIGH);
	while((millis()-start_pluviometer)<=3000)
	{
		previous_reading_pluviometer = reading_pluviometer;
		reading_pluviometer = digitalRead(PLUVIO_DATA);
    
		if((previous_reading_pluviometer == 1)&&(reading_pluviometer == 0))
		{
			value_pluviometer++;
		}
		//avoid millis overflow problem
		if( millis() < start_pluviometer) start_pluviometer=millis();
	}
	delay(100);
	#if DEBUG_AGR==1
	PRINT_AGR(F("readPluviometer (uint16_t):"));	
	USB.println(value_pluviometer);		
	#endif
	#if DEBUG_AGR==2
	PRINT_AGR(F("readPluviometer (uint16_t):"));		
	USB.println(value_pluviometer);			
	#endif			
  	digitalWrite(WEATHER_STATION_ON,LOW);
	return value_pluviometer;
}


/*	storePulse: 
 * 
 * This function increments the number of pulses inside the pluviometer array 
 * in the corresponding index of 'plv_array' 
 * 
 */
void weatherStationClass::storePulse()
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
