/*! \file TurbiditySensor.cpp
	\brief Library for managing the Smart Water Turbidity Sensor Board

	Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L.
	http://www.libelium.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 2.1 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
	Version:			1.2
	Design:				David Gascón
	Implementation:		Ahmad Saad
*/


/***********************************************************************
 * Includes
 ***********************************************************************/
#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "TurbiditySensor.h"


/***********************************************************************
 * Class contructors
 ***********************************************************************/
turbiditySensorClass::turbiditySensorClass()
{
	// The sensor comes from factory with a default address
	// This direction can be changed using the function configureSensorAddress
	ModbusMaster485 sensor(DEFAULT_ADDRESS);
}

/***********************************************************************
 * Methods of the Class
 ***********************************************************************/
 
//!*************************************************************
//!	Name:	ON()														
//!	Description: Powers and configures the turbidity sensor		
//!	Param : void														
//!	Returns: "0" if no error, "-1" if error						
//!*************************************************************
char turbiditySensorClass::ON()
{
	char result = -1;
	
	// Switch ON the power supply
	PWR.setSensorPower(SENS_5V, SENS_ON);
	// The sensor uses 9600 bps speed communication
	sensor.begin(9600);
	
	// Important: Reset the registers of the sensor
	resetSensor();
	
	// Configure the sensor address
	result = configureSensorAddress(SENSOR_ADDRESS);

#if DEBUG_MODE == 1
	// Check that the address has been well configured
	if (result == -1) {
		// If no response from the slave, print an error message
		USB.println(F("Communication Error. The address hasn't been configured."));
	} 
	else { 
		USB.println(F("Sensor address configured correctly"));
	}
#endif

	delay(10);

	// Clear the Modbus buffers
	clearBuffer();
	
	// Configure the type measurement of the temperature sensor
	typeMeasurementConfiguration(TEMP_TYPE_CON, 0x0003);
	delay(20);
	clearBuffer();

	// Configue the type measurement of the turbidity sensor
	typeMeasurementConfiguration(TURB_TYPE_CON, 0x0003);
	delay(20);
	clearBuffer();
	
	// Configure the average measurement
	average(25);
	
	return result;
}

 
//!*************************************************************
//!	Name:	OFF()														
//!	Description: Powers OFF the turbidity sensor					
//!	Param : void														
//!	Returns: void							
//!*************************************************************
void turbiditySensorClass::OFF()
{
	// Supply the sensor using 5V output
	PWR.setSensorPower(SENS_5V, SENS_OFF);
}


//**********************************************************************
// Frame 80 and 100 in the documentation for Turbidity
//********************************************************************** 
//!*************************************************************
//!	Name:	readTurbidity()											
//!	Description: Reads the turbidity value from the sensor		
//!	Param : void														
//!	Returns: "0" if no error, "-1" if error						
//!*************************************************************
uint8_t turbiditySensorClass::readTurbidity()
{
	////////////////////////////////////////////////////////////////////
	// This declaration is used to generate a float from two integers 
	// integer(16 bits) + integer (16 bits) => float (32bits)
	////////////////////////////////////////////////////////////////////
	union 
	{
		int ints[2];
		float toFloat;
	} 
	foo;
	
	//readTemperature();
	delay(10);
	
	//writeCalibrationValue(0x005D, getTemperature());	
	clearBuffer();
	delay(10);
	startMeasurment(TURB_NEW_MEAS);

	// This variable will store the result of the communication
	// result = 0 : no errors 
	// result = 1 : error occurred
	int result = -1;
	int retries = 0;
	
	while ((result !=0) && (retries < 20)) 
	{
		retries ++;
		sensor.readHoldingRegisters(TURB_MEAS_STATUS, 1);
		delay(1);
		// MASK for getting only the status of the register
		
		result = sensor.getResponseBuffer(0);
		
		#if DEBUG_MODE == 1
			USB.print(F("Turbidity measurement status: "));
			USB.print(result, BIN);
			USB.print(F("\n"));
		#endif
		
		result = sensor.getResponseBuffer(0) & 0x0007;     

		#if DEBUG_MODE == 1
			USB.print(F("Turbidity measurement status after mask: "));
			USB.print(result, BIN);
			USB.print(F("\n"));
		#endif
		delay(10);
	}

	delay(200);
	
	clearBuffer();

	if (result != 0) {
		#if DEBUG_MODE == 1
			USB.println(F("Communication error while reading turbidity measurement status..."));
		#endif

		return -1;
	} 
	else {
		
		result = -1;
		retries = 0;
		
		while ((result !=0) && (retries < 5)) {
		
			result = sensor.readHoldingRegisters(TURB_VALUE_REG, 2);
			retries++;
			delay(10);
		}

		if (result != 0) {
			#if DEBUG_MODE == 1
				// If no response from the slave, print an error message
				USB.println(F("Communication error while reading Turbidity..."));
			#endif
			delay(150);
			
			return -1;
		}
		else {
			// If all OK
			foo.ints[0] = sensor.getResponseBuffer(1);
			foo.ints[1] = sensor.getResponseBuffer(0);
			
			turbidity = foo.toFloat;
			
			return 0;
		}
	}
}

 
//!*************************************************************
//!	Name:	getTurbidity()														
//!	Description: Returns the stored value of the turbidity		
//!	Param : void														
//!	Returns: The turbidity value						
//!*************************************************************
float turbiditySensorClass::getTurbidity()
{
	// Every sensor you use with digitalSmooth needs its own array
	rawData1 = turbidity * 1000;
	smoothData1 = digitalSmooth(rawData1, sensSmoothArray1);  

	float turbidity = smoothData1/1000.0;
	return turbidity;
}
 
 
 
//**********************************************************************
// Private Methods
// *********************************************************************
//!*************************************************************
//!	Name:	getTemperature()											
//!	Description: Returns the value of the temperature			
//!	Param : void														
//!	Returns: The temperature value									
//!*************************************************************
float turbiditySensorClass::getTemperature()
{
	return temperature;
}

//**********************************************************************
// Frame 15 in the documentation
//**********************************************************************
//!*************************************************************
//!	Name:	typeMeasurementConfiguration()							
//!	Description: Configures the type measurement					
//!	Param : address: the address of the configuration			
//! 		 config: The configuration to write					
//!	Returns: void														
//!*************************************************************
void turbiditySensorClass::typeMeasurementConfiguration(uint16_t address, uint16_t config)
{
	delay(100);
	int result = sensor.writeSingleRegister(address, config);
	delay(100);

	#if DEBUG_MODE == 1
		// Chechk that the direction has been well writed
		if (result == -1) {
			// If no response from the slave, print an error message
			USB.println(F("ERROR. Type Measurement Register not configured."));
		} 
		else { 
			USB.println(F("Type Measurement Register well configured"));
		}
	#endif

	clearBuffer();
	delay(150);
}

/*
 * // Not tested functions
void temperatureSensorCalibration()
{
	//Variable to read data from the serial monitor. 
	char serialByte = '0';
	
	/////////////////////////////////////////////////////////////////////////////
	// OFFSET CALIBRATION PROCESS at 0ºC
	/////////////////////////////////////////////////////////////////////////////
	average(1);
	temporaryCoeficients(DISABLE);

	serialFlush(0);
	
	while(serialByte != 'R')
	{		
		readTemperature();
		delay(250);
		serialByte = serialRead(0);
	}

	writeCalibrationValue(TEMP_CAL1_REG, foo.toFloat);
	temporaryCoeficients(OFFSET_0);
	delay(5000);

	/////////////////////////////////////////////////////////////////////////////
	// CALIBRATION PROCESS at 25ºC
	/////////////////////////////////////////////////////////////////////////////
	
	temporaryCoeficients(OFFSET_0);

	serialByte = '0';  
	serialFlush(0);
	
	while(serialByte != 'R')
	{		
		readTemperature();
		delay(250);	
		serialByte = serialRead(0);
	}


	writeCalibrationValue(TEMP_CAL2_REG, foo.toFloat);
	temporaryCoeficients(OFFSET_0 | TEMP_25);
	writeNameDate();
	temporaryCoeficients(DISABLED); 
}*/


//!*************************************************************
//!	Name:	resetSensor()												
//!	Description: Resets the sensor to the default values			
//!	Param : void														
//!	Returns: void														
//!*************************************************************
void turbiditySensorClass::resetSensor()
{
	sensor.writeSingleRegister(RESET_REG, 0x000F);
	delay(100);
}


//**********************************************************************
// Frame 70 in the documentation
//**********************************************************************
//!*************************************************************
//!	Name:	startMeasurment()											
//!	Description: Process to get a new measure						
//!	Param : void														
//!	Returns: void														
//!*************************************************************
void turbiditySensorClass::startMeasurment(uint8_t parameter)
{
	// Result of the communication
	int result = -1;

	result = sensor.writeSingleRegister(NEW_MEAS_REG, parameter);
	delay(100); 
	
	#if DEBUG_MODE == 1
		// Chechk that the direction has been well writed
		if (result == -1) {
			// If no response from the slave, print an error message
			USB.println(F("Communication Error. The sensor can't take a new measure."));
		} 
		else { 
			USB.println(F("Starting a new measure process..."));
		}
	#endif

	delay(10);
}


//**********************************************************************
// Frame 80 and 100 in the documentation for Temperature
//**********************************************************************
//!*************************************************************
//!	Name:	readTemperature()											
//!	Description: Reads the temperature value from the sensor		
//!	Param : void														
//!	Returns: "0" if no error, "-1" if error						
//!*************************************************************
uint8_t turbiditySensorClass::readTemperature() 
{
	union 
	{
		int ints[2];   
		float toFloat;
	}
	foo;
	
	clearBuffer();

	startMeasurment(TEMP_NEW_MEAS);

	// This variable will store the result of the communication
	// result = 0 : no errors 
	// result = 1 : error occurred
	int result = -1;
	int retries = 0;

	delay(100);

	while ((result !=0) & (retries < 20)) 
	{  
		retries ++;
		sensor.readHoldingRegisters(TEMP_MEAS_STATUS, 1);
		// MASK for getting only the status of the register
		
		result = sensor.getResponseBuffer(0);
		
		#if DEBUG_MODE == 1
			USB.print(F("Temperature measurement status: "));
			USB.print(result, BIN);
			USB.print(F("\n"));
		#endif
		
		result = sensor.getResponseBuffer(0) & 0x0007;

		#if DEBUG_MODE == 1
			USB.print(F("Temperature measurement status: "));
			USB.print(result, BIN);
			USB.print(F("\n"));
		#endif
		
		delay(100);    
	}

	delay(100);

	if (result != 0) {    
		#if DEBUG_MODE == 1
			USB.println(F("Communication error while reading temperature measurement status..."));
		#endif

		return -1;
	} 
	else {
		result = sensor.readHoldingRegisters(TEMP_VALUE_REG, 2);

		if (result != 0) {
			#if DEBUG_MODE == 1
				// If no response from the slave, print an error message
				USB.println(F("Communication error while reading temperature..."));
			#endif
			
			return -1;
			delay(100);
		}
		else {
			// If all ok
			foo.ints[0]= sensor.getResponseBuffer(1);
			foo.ints[1]=sensor.getResponseBuffer(0);

			temperature = foo.toFloat;
			return 0;
		}
	}
}



//**********************************************************************
// Frame 110 in the documentation
//**********************************************************************
//!*************************************************************
//!	Name:	average()											
//!	Description: Configure the average value		
//!	Param : void												
//!	Returns: void					
//!*************************************************************
void turbiditySensorClass::average(uint8_t average)
{
	if (average > 50)
		average = 50;
	
	int result = sensor.writeSingleRegister(AVRG_PARA_REG, average);

	#if DEBUG_MODE == 1
	// Chechk that the direction has been well writed
		if (result == -1) {
			// If no response from the slave, print an error message
			USB.println(F("Communication Error. Average not configured."));
		} 
		else { 
			USB.println(F("Average configured..."));
		}
	#endif 
}


//**********************************************************************
// Configuring the sensor address
//**********************************************************************
//!*************************************************************
//!	Name:	configureSensorAddress()						
//!	Description: Configure the address of the sensor		
//!	Param : address: the address to configure				
//!	Returns: void					
//!*************************************************************
int turbiditySensorClass::configureSensorAddress(uint8_t address)
{
	
	int result = -1;
	int retries = 0;
	
	while ((result !=0) & (retries < 10))
	{ 
		retries ++;
		// Asign the address to the sensor
		result = sensor.writeSingleRegister(ADDRESS_REG, address);
		delay(50);
	}

#if DEBUG_MODE == 1
	if (result == -1) {
		// If no response from the slave, print an error message
		USB.println(F("Communication Error. Address not configured."));
	} 
	else { 
		USB.println(F("Address well configured"));
	}
#endif

	// Use the new address of the sensor 
	sensor.setSlaveAddress(SENSOR_ADDRESS);
	// Check that the new address has been configured correctly
	// Read again the address
	// Read one integer from 0x00A3 register
	sensor.readHoldingRegisters(ADDRESS_REG, 1);

	// If the address == 1, no errors
	if (sensor.getResponseBuffer(0) != 0x01) {
		// If no response from the slave return -1
		return -1; 
	}
	else {
		return 0;
	}
}


//!*************************************************************
//!	Name:	clearBuffer()									
//!	Description: Flushes the buffers.		
//!	Param : void				
//!	Returns: void					
//!*************************************************************
void turbiditySensorClass::clearBuffer()
{
	// Clear Response Buffer
	sensor.clearResponseBuffer();
	sensor.clearTransmitBuffer();
	delay(10);
}

//**********************************************************************
// Frame 60 in the documentation for Temperature
// Not tested functions
//**********************************************************************
void turbiditySensorClass::readCompensationTemperature(uint16_t _register)
{
	
		union 
	{
		int ints[2];   
		float toFloat;
	} 
	foo;
  // Result of the communication
  //int result = -1;

 /* foo.toFloat = temperature;
  node.setTransmitBuffer(0 , foo.ints[1]);
  node.setTransmitBuffer(1 , foo.ints[0]); 

#if DEBUG_MODE == 1
  USB.println(F("Writting compensation temperature returned by Master"));
#endif

  node.writeMultipleRegisters(COMP_TEMP_REG, 2);
  delay(100);*/

#if DEBUG_MODE == 1
  sensor.readHoldingRegisters(_register, 4);
  USB.print(F("Temperature writed in register: ")); 
  USB.print(_register, HEX); 
  // Print the read data from the slave 
  USB.print(sensor.getResponseBuffer(0), DEC);
  USB.print(F(" "));
  USB.print(sensor.getResponseBuffer(1), DEC);
  USB.print(F(" "));

  foo.ints[0]= sensor.getResponseBuffer(1);
  foo.ints[1]= sensor.getResponseBuffer(0);

  USB.println(foo.toFloat);
#endif
}

//!*************************************************************
//!	Name:	digitalSmooth()									
//!	Description: Digital smooth filter		
//!	Param : int rawIn: Value to be filtered
//!			int *sensSmoothArray: array of previous values		
//!	Returns: long: filtered value					
//!*************************************************************
long turbiditySensorClass::digitalSmooth(int rawIn, int *sensSmoothArray)
{
	// "int *sensSmoothArray" passes an array to the function - the asterisk indicates the array name is a pointer
	long j, k, temp, top, bottom;
	long total;
	static int i;
	// static int raw[filterSamples];
	static int sorted[filterSamples];
	boolean done;
	
	// Increment counter and roll over if necc. -  % (modulo operator) rolls over variable
	i = (i + 1) % filterSamples;
	// Input new data into the oldest slot
	sensSmoothArray[i] = rawIn;

	// Transfer data array into anther array for sorting and averaging
	for (j=0; j<filterSamples; j++){
		sorted[j] = sensSmoothArray[j];
	}

	// flag to know when we're done sorting
	done = 0;
	// simple swap sort, sorts numbers from lowest to highest
	while(done != 1){
		done = 1;
		for (j = 0; j < (filterSamples - 1); j++){
			// numbers are out of order - swap
			if (sorted[j] > sorted[j + 1]){
				temp = sorted[j + 1];
				sorted [j+1] =  sorted[j] ;
				sorted [j] = temp;
				done = 0;
			}
		}
	}

	// Throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
	bottom = max(((filterSamples * 15)  / 100), 1);
	// the + 1 is to make up for asymmetry caused by integer rounding
	top = min((((filterSamples * 85) / 100) + 1  ), (filterSamples - 1));   
	k = 0;
	total = 0;
	
	for ( j = bottom; j< top; j++){
		total += sorted[j];  // total remaining indices
		k++; 
	}

	// Divide by number of samples
	return total / k;
}



