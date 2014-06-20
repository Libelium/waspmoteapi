/*! \file TurbiditySensor.cpp
	\brief Library for managing the Smart Water Turbidity Sensor Board

	Copyright (C) 2014 Libelium Comunicaciones Distribuidas S.L.
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
  
	Version:			1.0
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
	ModbusMaster485 sensor(0);
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
	cont = 0;
	
	// Switch ON the power supply
	PWR.setSensorPower(SENS_5V, SENS_ON);
	// El sensor se comunica a 9600 bps
	sensor.begin(9600);
	resetSensor();
	 // Configure the sensor address
  result = configureSensorAddress(sensorAddress);

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

	// Clear the Modbus buffers
	clearBuffer();

	typeMeasurementConfiguration(TEMP_TYPE_CON, 0x0003);
	delay(20);
	clearBuffer();

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
	startMeasurment(TURB_NEW_MEAS);

	// This variable will store the result of the communication
	// result = 0 : no errors 
	// result = 1 : error occurred
	int result = -1;
	int retries = 0;
	
	while ((result !=0) & (retries < 20)) 
	{
		retries ++;
		sensor.readHoldingRegisters(TURB_MEAS_STATUS, 1);
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

	delay(100);	
	
	clearBuffer();

	if (result != 0) {
		#if DEBUG_MODE == 1
			USB.println(F("Communication error while reading turbidity measurement status..."));
		#endif
	} 
	else {
		result = sensor.readHoldingRegisters(TURB_VALUE_REG, 2);

		if (result != 0) {
			#if DEBUG_MODE == 1
				// If no response from the slave, print an error message
				USB.println(F("Communication error while reading Turbidity..."));
			#endif
			delay(100);
			return -1;
		}
		else {
			// If all ok
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
	rawData1 = turbidity* 1000;
	smoothData1 = digitalSmooth(rawData1, sensSmoothArray1);  // every sensor you use with digitalSmooth needs its own array

	float turbidity = smoothData1/1000.0;
	float correction = 0.0;  

	correction = -0.12 * (turbidity - 0.4) + 0.2;
	float value = turbidity - correction;
	
	if (value < 0.0) 
		value = 0.0;    
	
	return value;
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
	delay(100);
}

/*
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
	delay(10);
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
		delay(10);    
	}

	delay(100);

	if (result != 0) {    
		#if DEBUG_MODE == 1
			USB.println(F("Communication error while reading temperature measurement status..."));
		#endif
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

			temperature = foo.toFloat + 1.3;
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
	sensor.setSlaveAddress(sensorAddress);
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
  int result = -1;

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




long turbiditySensorClass::digitalSmooth(int rawIn, int *sensSmoothArray)
{
	 // "int *sensSmoothArray" passes an array to the function - the asterisk indicates the array name is a pointer
  long j, k, temp, top, bottom;
  long total;
  static int i;
  // static int raw[filterSamples];
  static int sorted[filterSamples];
  boolean done;

  i = (i + 1) % filterSamples;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
  sensSmoothArray[i] = rawIn;                 // input new data into the oldest slot

  // Serial.print("raw = ");

  for (j=0; j<filterSamples; j++){     // transfer data array into anther array for sorting and averaging
    sorted[j] = sensSmoothArray[j];
  }

  done = 0;                // flag to know when we're done sorting              
  while(done != 1){        // simple swap sort, sorts numbers from lowest to highest
    done = 1;
    for (j = 0; j < (filterSamples - 1); j++){
      if (sorted[j] > sorted[j + 1]){     // numbers are out of order - swap
        temp = sorted[j + 1];
        sorted [j+1] =  sorted[j] ;
        sorted [j] = temp;
        done = 0;
      }
    }
  }


  // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
  bottom = max(((filterSamples * 15)  / 100), 1); 
  top = min((((filterSamples * 85) / 100) + 1  ), (filterSamples - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
  k = 0;
  total = 0;
  for ( j = bottom; j< top; j++){
    total += sorted[j];  // total remaining indices
    k++; 
    // Serial.print(sorted[j]); 
    // Serial.print("   "); 
  }

  //  Serial.println();
  //  Serial.print("average = ");
  //  Serial.println(total/k);
  return total / k;    // divide by number of samples
}



