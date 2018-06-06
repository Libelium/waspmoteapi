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
 *  Implementation:	Carlos Bello
 */

 

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

// BME280 library for reading temperature, humidity and pressure values
#include "BME280.h"
#include "WaspSensorEvent_v30.h"
#include <TSL2561.h>

//**********************************************************************
// EVENTOS SENSOR BOARD CLASS
//**********************************************************************

//======================================================================
// PUBLIC METHODS
//======================================================================
 
//!*********************************************************************
//!	Name:	EventsSensorClass()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*********************************************************************
WaspSensorEvent_v30::WaspSensorEvent_v30() 
{
	//PWR.setSensorPower( SENS_5V, SENS_OFF);	
	//PWR.setSensorPower(SENS_3V3, SENS_OFF);	
	// init interruption attribute flag 
	_intEnabled = true;
}

//!*********************************************************************
//!	Name:	getTemperature()										
//!	Description: Gets the temperature from the BME280 sensor
//!	Param : void														
//!	Returns: float: temperature value read		
//!*********************************************************************
float WaspSensorEvent_v30::getTemperature() {
	float value = 0;
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	//Configure the BME280 Sensor (Temperature, Humidity and Pressure)
	BME.ON();
	delay(100);	
	value = BME.getTemperature(BME280_OVERSAMP_1X, 0);
	#if DEBUG_EVN==1
		PRINT_EVENT(F("getTemperature:"));
		USB.println(value);
	#endif
		
	#if DEBUG_EVN==2
		PRINT_EVENT(F("getTemperature:"));
		USB.println(value);	
		PRINT_EVENT(F("BME280_OVERSAMP_1X"));
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
float WaspSensorEvent_v30::getHumidity() {
	float value = 0;
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	//Configure the BME280 Sensor (Temperature, Humidity and Pressure)
	BME.ON();
	delay(100);	
	// Read the humidity from the BME280 Sensor
	value = BME.getHumidity(BME280_OVERSAMP_1X);
	#if DEBUG_EVN==1
		PRINT_EVENT(F("getHumidity:"));
		USB.println(value);		
	#endif
		
	#if DEBUG_EVN==2
		PRINT_EVENT(F("getHumidity:"));
		USB.println(value);	
		PRINT_EVENT(F("BME280_OVERSAMP_1X"));
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
float WaspSensorEvent_v30::getPressure() {
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
	#if DEBUG_EVN==1
		PRINT_EVENT(F("getPressure:"));
		USB.println(value);		
	#endif
		
	#if DEBUG_EVN==2
		PRINT_EVENT(F("getPressure:"));
		USB.println(value);	
		PRINT_EVENT(F("BME280_OVERSAMP_1X"));
		USB.println(BME280_OVERSAMP_1X);	
	#endif  	
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);
	// Read the temperature from the BME280 Sensor	
	return value;	
}
//======================================================================
// PUBLIC METHODS
//======================================================================
//!*********************************************************************
//!	Name:	ON()										
//!	Description: Switch ON the power supply and configure the I/O pins		
//!	Param : void														
//!	Returns: void							
//!*********************************************************************
void WaspSensorEvent_v30::ON() {
	// Configure the internal reference
	//analogReference(INTERNAL2V56);
	//pinMode(DIGITAL5,INPUT);  //PULS FLOW CHANNEL A
	// Configure pins
	pinMode(ANA0,INPUT);		//REL_EXT_INT EVENTS
	pinMode(ANA1,OUTPUT);		//K1 OUT
	pinMode(ANA2,INPUT);		//PULS E
	pinMode(ANA3,INPUT);		//PULS D
	pinMode(ANA4,INPUT);		//PULS C
	pinMode(ANA5,OUTPUT);		//I2C MAIN PIN
	pinMode(DIGITAL5,INPUT);    //PULS FLOW CHANNEL A		
	pinMode(DIGITAL1,INPUT);    //PULS FLOW CHANNEL A	
	pinMode(SENS_INT_CLK_INH,OUTPUT);    //PULS FLOW CHANNEL A	
	pinMode(SENS_INT_CLK_REG,OUTPUT);    //PULS FLOW CHANNEL A	    
	pinMode(SENS_INT_ENABLE,OUTPUT);    //PULS FLOW CHANNEL A	
	pinMode(SENS_INT_ENABLE,OUTPUT);   //PULS FLOW CHANNEL A		
	delay(10);
	//Set Firts Time Values
	digitalWrite(DIGITAL0,LOW);	
	digitalWrite(ANA0,LOW);
	digitalWrite(ANA1,LOW);
	digitalWrite(ANA2,LOW);
	digitalWrite(ANA3,LOW);
	digitalWrite(ANA4,LOW);
	digitalWrite(ANA5,LOW);	
	//I2C ISOLATOR PIN ENABLE
	pinMode(I2C_PIN_OE, OUTPUT);
	digitalWrite(I2C_PIN_OE, LOW);
	// Switch ON 3V3 and 5V for supplying the board
	PWR.setSensorPower(SENS_5V, SENS_ON);
	PWR.setSensorPower(SENS_3V3, SENS_ON);
    delay(500);
	_intEnabled = true;	
	
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
void WaspSensorEvent_v30::OFF(){ 
	// Switch OFF I2C
	digitalWrite(I2C_PIN_OE, LOW);

	// Switch OFF 3V3 and 5V 
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	delay(100);
}
//!*********************************************************************
//!	Name:	attachInt()										
//!	Description: enable Interrupts
//!	Param : void																						
//!*********************************************************************
void	WaspSensorEvent_v30::attachInt() 
{
	#if DEBUG_EVN > 0
	PRINT_EVENT(F("attachInt function\r\n\r\n"));	
	#endif	
	//digitalWrite(SENS_INT_ENABLE,HIGH); 	
	digitalWrite(SENS_INT_ENABLE,HIGH); 
	enableInterrupts(SENS_INT);
	_intEnabled = true;
}
//!*********************************************************************
//!	Name:	detachInt()										
//!	Description: disable Interrupts
//!	Param : void																						
//!*********************************************************************
void WaspSensorEvent_v30::detachInt() 
{
	#if DEBUG_EVN > 0
	PRINT_EVENT(F("detachInt function\r\n"));	
	#endif	
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
void	WaspSensorEvent_v30::loadInt() 
{
	input1Flag = false;
	input2Flag = false;
	input3Flag = false;
	input4Flag = false;
	input6Flag = false;
	flowFlag = false;
	
	#if DEBUG_EVN > 0
	PRINT_EVENT(F("loadInt function\r\n"));
	#endif
	
	digitalWrite(SENS_INT_ENABLE,LOW);
	delay(10);
	digitalWrite(SENS_INT_CLK_INH, LOW);
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	if(digitalRead(DIGITAL1) == 1){ 
		flowFlag = true;
	}
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	if(digitalRead(DIGITAL1) == 1){ 
		input6Flag = true;  
	}
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	if(digitalRead(DIGITAL1) == 1){ 
        input3Flag = true;      
	}
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	if(digitalRead(DIGITAL1) == 1){ 
        input2Flag = true;
	}
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	if(digitalRead(DIGITAL1) == 1){ 
          input1Flag = true;
	}
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	if(digitalRead(DIGITAL1) == 1){ 
      input4Flag = true;        
	}
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	if(digitalRead(DIGITAL1) == 1){ 
      flowFlag = true;        
	}
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, LOW);
	delay(2);
	digitalWrite(SENS_INT_CLK_REG, HIGH);
	if(digitalRead(DIGITAL1) == 1){ 
       flowFlag = true;      
	}		
	delay(200);
	digitalWrite(SENS_INT_ENABLE, HIGH);
	digitalWrite(SENS_INT_ENABLE,HIGH); 
	digitalWrite(SENS_INT_CLK_INH, HIGH);
}


//!*********************************************************************
//!	Name:	readInput()										
//!	Description: Read digital information about objets inputs
//!	Param : void	
//!	Returns: int: 0 or 1									
//!*********************************************************************
uint8_t WaspSensorEvent_v30::readInput(uint8_t _socket){
	uint8_t aux = 0;
	// get actual interruption state flag
	bool isEnabled = _intEnabled;// disable interruption
	Events.detachInt();
	switch (_socket){
		case SOCKET_1:
		case SOCKET_C:
			aux = digitalRead(PULS_C);
			#if DEBUG_EVN > 1
			PRINT_EVENT(F("Read SOCKET_1 or SOCKET_C\r\n"));	
			#endif	
		break;
		case SOCKET_2:
		case SOCKET_D:
			aux = digitalRead(PULS_D);
			#if DEBUG_EVN > 1
			PRINT_EVENT(F("Read SOCKET_2 or SOCKET_D\r\n"));	
			#endif				
		break;
		case SOCKET_3:
		case SOCKET_E:
			aux = digitalRead(PULS_E);
			#if DEBUG_EVN > 1
			PRINT_EVENT(F("Read SOCKET_3 or SOCKET_E\r\n"));	
			#endif				
		break;
		case SOCKET_4:
		case SOCKET_A:
			aux = digitalRead(PULS_A);
			#if DEBUG_EVN > 1
			PRINT_EVENT(F("Read SOCKET_4 or SOCKET_A\r\n"));	
			#endif				
		break;	
		case SOCKET_6:
			aux = digitalRead(PULS_F);
			#if DEBUG_EVN > 1
			PRINT_EVENT(F("Read SOCKET_6\r\n"));	
			#endif				
		break;	
		
		default:
			#if DEBUG_EVN > 0
			PRINT_EVENT(F("Incorrect input\r\n"));	
			#endif		
		break;
	}
	// re-enable interruption if needed
	if( isEnabled == true )
	{	
		delay(50);
		Events.attachInt();
	}	
	return aux;
}

//!*********************************************************************
//!	Name:	getDistance()										
//!	Description: Gets distance from Ultrasound Sensor
//!	Param : void														
//!	Returns:  float: distance value read								
//!*********************************************************************
uint16_t WaspSensorEvent_v30::getDistance(){
	uint16_t value;
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	delay(100);	
	value = Ultrasound.getDistance();
	delay(100);
	// Switch OFF I2C
	#if DEBUG_EVN > 0
	PRINT_EVENT(F("getDistance function: "));
	USB.println(value);
	#endif			
	digitalWrite(I2C_PIN_OE, LOW);	
	return value;
}

/*!
 * @brief 	This function performs a lux measurement
 * @return 	luxes if ok
 * 			-1 if error
 */
uint32_t WaspSensorEvent_v30::getLuxes()
{
  return getLuxes(TSL2561_GAIN_1, TSL2561_HIGH_RES);
}

/*!
 * @brief 	This function performs a lux measurement
 * @return 	luxes if ok
 * 			-1 if error
 */
uint32_t WaspSensorEvent_v30::getLuxes(bool gain)
{
  return getLuxes(gain, TSL2561_HIGH_RES);
}

//!*********************************************************************
//!	Name:	getLuxes()
//!	Description: Gets luxes from TSL2561
//!	Param : gain ( OUTDOOR OR INDOOR)
//!         res (TSL2561_HIGH_RES, TSL2561_MED_RES, TSL2561_LOW_RES)										
//!	Returns:  float: luxes value read
//!*********************************************************************
uint32_t WaspSensorEvent_v30::getLuxes(bool gain, uint8_t res){
	uint8_t error;
	TSL.ON();
	//Switch ON I2C
	digitalWrite(I2C_PIN_OE, HIGH);
	delay(100);

	error = TSL.getLuminosity(res, gain);

  delay(100);
  // Switch OFF I2C
  digitalWrite(I2C_PIN_OE, LOW);
  if (error == 0)
  {
    return TSL.lux;
  }
  else{
    return (uint32_t)-1;
  }
}

// Preinstantiate Objects //////////////////////////////////////////////////////
WaspSensorEvent_v30 Events = WaspSensorEvent_v30();
//**************************************************************************************************
// Hall Effect Class
//**************************************************************************************************
hallSensorClass::hallSensorClass(uint8_t socket){
	hallEffectSocket = socket;	
}


//!*********************************************************************
//!	Name:	read()										
//!	Description: Read digital information about hallSensor
//!	Call readInput() function from WaspSensorEvents
//!	Param : void	
//!	Returns: int: 0 or 1																			
//!*********************************************************************
uint8_t hallSensorClass::read(){
	return readInput(hallEffectSocket);
}

//!*********************************************************************
//!	Name:	readHallSensor()										
//!	Description: Read digital information about hallSensor
//!	Call readInput() function from WaspSensorEvents
//!	Param : void	
//!	Returns: int: 0 or 1																			
//!*********************************************************************
uint8_t hallSensorClass::readHallSensor(){
	return readInput(hallEffectSocket);
}

//!*********************************************************************
//!	Name:	getInt()										
//!	Description: Get interruption from object
//!	Param : void													
//!	Returns:  bool: True or False								
//!*********************************************************************
bool hallSensorClass::getInt(){
	bool aux = false;
	#if DEBUG_EVN > 0
	PRINT_EVENT(F("getInt function: \r\n"));
	#endif
	
	switch (hallEffectSocket){
		case SOCKET_1:
		case SOCKET_C:
			aux = Events.input1Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: \r\n"));
				USB.println(aux);
			#endif			
		break;
		case SOCKET_2:
		case SOCKET_D:
			aux = Events.input2Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: \r\n"));
				USB.println(aux);
			#endif				
		break;
		case SOCKET_3:
		case SOCKET_E:
			aux = Events.input3Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: \r\n"));
				USB.println(aux);
			#endif				
		break;
		case SOCKET_4:
		case SOCKET_A:
			aux = Events.input4Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif				
		break;
		case SOCKET_6:
			aux = Events.input6Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif
		break;
		default:
		break;
	}
	return aux;
}
//**************************************************************************************************
// PIR Sensor Class
//**************************************************************************************************
pirSensorClass::pirSensorClass(uint8_t socket){
	pirSensorSocket = socket;
}


//!*********************************************************************
//!	Name:	read()										
//!	Description: Read digital information about pir sensor
//!	Call readInput() function from WaspSensorEvents
//!	Param : void	
//!	Returns: int: 0 or 1								
//!*********************************************************************
uint8_t pirSensorClass::read(){
	return readInput(pirSensorSocket);
}
//!*********************************************************************
//!	Name:	readPirSensor()										
//!	Description: Read digital information about pir sensor
//!	Call readInput() function from WaspSensorEvents
//!	Param : void	
//!	Returns: int: 0 or 1																			
//!*********************************************************************
uint8_t pirSensorClass::readPirSensor(){
	return readInput(pirSensorSocket);
}

//!*********************************************************************
//!	Name:	getInt()										
//!	Description: Get interruption from object
//!	Param : void													
//!	Returns:  bool: True or False								
//!*********************************************************************

bool pirSensorClass::getInt(){
	bool aux = false;
	
	switch (pirSensorSocket){
		case SOCKET_1:
		case SOCKET_C:
			aux = Events.input1Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif			
		break;
		case SOCKET_2:
		case SOCKET_D:
			aux = Events.input2Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif				
		break;
		case SOCKET_3:
		case SOCKET_E:
			aux = Events.input3Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif				
		break;
		case SOCKET_4:
		case SOCKET_A:
			aux = Events.input4Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif				
		break;
		case SOCKET_6:
			aux = Events.input6Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif
		break;
		default:
		break;
	}
	return aux;
}

//**************************************************************************************************
// Liquid Level Class
//**************************************************************************************************
liquidLevelClass::liquidLevelClass(uint8_t socket){
	liquidLevelSocket = socket;
}

//!*********************************************************************
//!	Name:	read()										
//!	Description: Read digital information about liquid level
//!	Call readInput() function from WaspSensorEvents
//!	Param : void	
//!	Returns: int: 0 or 1																			
//!*********************************************************************
uint8_t liquidLevelClass::read(){
	
	
	return readInput(liquidLevelSocket);
}
//!*********************************************************************
//!	Name:	readliquidLevel()										
//!	Description: Read digital information about liquid level
//!	Call readInput() function from WaspSensorEvents
//!	Param : void	
//!	Returns: int: 0 or 1																			
//!*********************************************************************
uint8_t liquidLevelClass::readliquidLevel(){
	return readInput(liquidLevelSocket);
}

//!*********************************************************************
//!	Name:	getInt()										
//!	Description: Get interruption from object
//!	Param : void													
//!	Returns:  bool: True or False								
//!*********************************************************************
bool liquidLevelClass::getInt(){
	bool aux = false;
	
	switch (liquidLevelSocket){
		case SOCKET_1:
		case SOCKET_C:
			aux = Events.input1Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif			
		break;
		case SOCKET_2:
		case SOCKET_D:
			aux = Events.input2Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif				
		break;
		case SOCKET_3:
		case SOCKET_E:
			aux = Events.input3Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif				
		break;
		case SOCKET_4:
		case SOCKET_A:
			aux = Events.input4Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif				
		break;
		case SOCKET_6:
			aux = Events.input6Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif
		break;
		default:
		break;
	}
	return aux;
}
//**************************************************************************************************
// Liquid Presence Sensor Class
//**************************************************************************************************
liquidPresenceClass::liquidPresenceClass(uint8_t socket){
	liquidPresenceSocket = socket;
}


//!*********************************************************************
//!	Name:	readliquidPresence()										
//!	Description: Read digital information about liquid presence
//!	Call readInput() function from WaspSensorEvents
//!	Param : void	
//!	Returns: int: 0 or 1																			
//!*********************************************************************
uint8_t liquidPresenceClass::read(){
	return readInput(liquidPresenceSocket);
}

//!*********************************************************************
//!	Name:	readliquidPresence()										
//!	Description: Read digital information about liquid presence
//!	Call readInput() function from WaspSensorEvents
//!	Param : void	
//!	Returns: int: 0 or 1																			
//!*********************************************************************
uint8_t liquidPresenceClass::readliquidPresence(){
	return readInput(liquidPresenceSocket);
}

//!*********************************************************************
//!	Name:	readVoltage()										
//!	Description: Read analog information about liquid presence
//!	Param : void	
//!	Returns: float: volts value read																			
//!*********************************************************************
float liquidPresenceClass::readVoltage(){
	
	int aux = 0;
	// get actual interruption state flag
	bool isEnabled = _intEnabled;// disable interruption
	Events.detachInt();
	switch (liquidPresenceSocket){
		case SOCKET_1:
		case SOCKET_C:
			aux = analogRead(ANALOG5);
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("Read SOCKET_1 or SOCKET_C\r\n"));	
			#endif	
		break;
		case SOCKET_2:
		case SOCKET_D:
			aux = analogRead(ANALOG4);
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("Read SOCKET_2 or SOCKET_D\r\n"));	
			#endif				
		break;
		case SOCKET_3:
		case SOCKET_E:
			aux = analogRead(ANALOG3);
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("Read SOCKET_3 or SOCKET_E\r\n"));	
			#endif				
		break;
		case SOCKET_4:
		case SOCKET_A:
			aux = analogRead(ANALOG7);
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("Read SOCKET_4 or SOCKET_A\r\n"));	
			#endif				
		break;	
		case SOCKET_6:
			aux = analogRead(ANALOG1);
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("Read SOCKET_6\r\n"));	
			#endif				
		break;	
		
		default:
			#if DEBUG_EVN > 0
				PRINT_EVENT(F("Incorrect input\r\n"));	
			#endif		
		break;
	}
	// re-enable interruption if needed
	if( isEnabled == true )
	{	
		delay(50);
		Events.attachInt();
	}	
	float volts = ((float)aux * 3.3) / 1023.0;
	return volts;
}

//!*********************************************************************
//!	Name:	readResistance()									
//!	Description: Read the resistance of the sensor
//!	Param : void													
//!	Returns:  float: Resistance value read in KOhms
//!*********************************************************************
float liquidPresenceClass::readResistance(float volts){
	
	if ( volts == 0.0 )
	{
		// Max value of resistance can be detected is 10.5 MOhm
		return 10500.0;
	}
	else
	{
		float resistance = (( 3.3 / volts ) - 1.0) * 10.0;
		return resistance;
	}
}


//!*********************************************************************
//!	Name:	getInt()										
//!	Description: Get interruption from object
//!	Param : void													
//!	Returns:  bool: True or False								
//!*********************************************************************
bool liquidPresenceClass::getInt(){
	bool aux = false;
	
	switch (liquidPresenceSocket){
		case SOCKET_1:
		case SOCKET_C:
			aux = Events.input1Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif
		break;
		case SOCKET_2:
		case SOCKET_D:
			aux = Events.input2Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif
		break;
		case SOCKET_3:
		case SOCKET_E:
			aux = Events.input3Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif
		break;
		case SOCKET_4:
		case SOCKET_A:
			aux = Events.input4Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif
		break;
		case SOCKET_6:
			aux = Events.input6Flag;
			#if DEBUG_EVN > 1
				PRINT_EVENT(F("getInt function: "));
				USB.println(aux);
			#endif
		break;
		default:
		break;
	}
	return aux;
}
//**************************************************************************************************
// Relay Class
//**************************************************************************************************
//!*************************************************************************************
//!	Name:	relayClass()										
//!	Description: Class contructor		
//!	Param : void												
//!	Returns: void							
//!*************************************************************************************
relayClass::relayClass()
{
}

//!*********************************************************************
//!	Name:	read()										
//!	Description: Read digital information about In Rel
//!	Param : void	
//!	Returns: int: 0 or 1									
//!*********************************************************************
uint8_t relayClass::read(){ 
	return readInRel();
}

//!*********************************************************************
//!	Name:	readInRel()										
//!	Description: Read digital information about In Rel
//!	Param : void	
//!	Returns: int: 0 or 1									
//!*********************************************************************
uint8_t relayClass::readInRel(){ 
	uint8_t aux = 0;
	// get actual interruption state flag
	bool isEnabled = _intEnabled;// disable interruption
	detachInt();
	aux = digitalRead(PULS_F);
	// re-enable interruption if needed
	if( isEnabled == true )
	{	
		delay(50);
		attachInt();
	}
	return aux;
}

//!*********************************************************************
//!	Name:	getInt()										
//!	Description: Get interruption from object
//!	Param : void													
//!	Returns:  bool: True or False								
//!*********************************************************************
bool relayClass::getInt(){
	bool aux = false;
	aux = Events.input6Flag;
	return aux;
}
//!*********************************************************************
//!	Name:	relayON()										
//!	Description: Switch ON Relay Output
//!	Param : void																						
//!*********************************************************************
void relayClass::relayON() 
{
	#if DEBUG_EVN > 0
	PRINT_EVENT(F("Relay On\r\n"));
	#endif		
	digitalWrite(ANA1,HIGH); 
} 
//!*********************************************************************
//!	Name:	relayOFF()										
//!	Description: Switch ON Relay Output
//!	Param : void																						
//!*********************************************************************
void relayClass::relayOFF() 
{
	#if DEBUG_EVN > 0
	PRINT_EVENT(F("Relay Off\r\n"));
	#endif		
	digitalWrite(ANA1,LOW); 
} 
//**************************************************************************************************
// flowClass Class
//**************************************************************************************************
//!*************************************************************************************
//!	Name:	flowClass()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
flowClass::flowClass(uint8_t model)
{
	_model = model;	
	disableFlowInt();
}
/*	flowReading: reads the analog to digital converter input indicated
 * 						   in socket and converts the value into distance in
 * 						   function of the sensor selected in mode
 *	Parameters:	uint8_t socket : digital input to be read (FLOW_B)
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
//!*********************************************************************
//!	Name:	read()										
//!	Description: Count pulses from input flow
//!	Param : void													
//!	Returns:  float:  flow value read							
//!*********************************************************************
float flowClass::read()
{
	return flowReading();
}


//!*********************************************************************
//!	Name:	flowReading()										
//!	Description: Count pulses from input flow
//!	Param : void													
//!	Returns:  float:  flow value read							
//!*********************************************************************
float flowClass::flowReading()
{
	float flow = 0.0;
	int value = 0;
	long start = 0;
	int previous_reading = 0;
	int reading = 0;
	bool isEnabled = _intEnabled;// disable interruption
	detachInt();	
	start = millis();		
	while((millis()-start)<=1000)
	{
	  previous_reading = reading;
	  reading = digitalRead(DIGITAL5);  
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
	#if DEBUG_EVN > 0
	PRINT_EVENT(F("Flow control\r\n"));
	#endif		
	switch(_model)
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
	if( isEnabled == true )
	{	
		delay(50);
		attachInt();
	}
	return flow;
}

//!*********************************************************************
//!	Name:	getInt()										
//!	Description: Get interruption from object
//!	Param : void													
//!	Returns:  bool: True or False								
//!*********************************************************************
bool flowClass::getInt(){
	bool aux = false;
	aux = Events.flowFlag;
	return aux;
}



//!*********************************************************************
//!	Name:	enableFlowInt()										
//!	Description: enable Interrupts from the flow sensor
//!	Param : void												
//!*********************************************************************
void flowClass::enableFlowInt() 
{
	// get current 'intFlag' and sensor output
	uint8_t flag   = intFlag & SENS_INT;
	uint8_t output = digitalRead(DIGITAL5);
	
	// enable flow ints
	pinMode(SENS_INT_FLOW_EN, OUTPUT);
	digitalWrite(SENS_INT_FLOW_EN, HIGH);
	
	// clear 'intFlag' if enabling triggered the event
	if ((output == HIGH) && (flag == 0))
	{
		intFlag &= ~(SENS_INT);
	}
}

//!*********************************************************************
//!	Name:	disableFlowInt()										
//!	Description: disable Interrupts from the flow sensor
//!	Param : void																						
//!*********************************************************************
void flowClass::disableFlowInt() 
{
	// disable flow ints
	pinMode(SENS_INT_FLOW_EN, OUTPUT);
	digitalWrite(SENS_INT_FLOW_EN, LOW);
	
}

