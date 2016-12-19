/*! \file TurbiditySensor.cpp
	\brief Library for managing the Smart Water Turbidity Sensor

	Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L.
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
  
	Version:			3.1
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
turbidityClass::turbidityClass()
{
	// The sensor comes from factory with a default address
	// This direction can be changed using the function configureSensorAddress
}


/***********************************************************************
 * Class contructors
 ***********************************************************************/
turbidityClass::turbidityClass(uint8_t address)
{
	// The sensor comes from factory with a default address
	// This direction can be changed using the function configureSensorAddress
	sensor = ModbusMaster(RS232_COM, address);
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
uint8_t turbidityClass::ON()
{

	uint8_t result;
	
	delay(10);

	if (_boot_version < 'H')
	{
		sensor = ModbusMaster(RS485_COM);		
		
		// The sensor uses 9600 bps speed communication
		sensor. begin(9600);
		
		// Switch ON the power supply
		PWR.setSensorPower(SENS_5V, SENS_ON);	
	
		WaspRegister |= REG_RS485;
	}
	else
	{
		sensor = ModbusMaster(RS232_COM);

		// The sensor uses 9600 bps speed communication
		sensor.begin(9600, 1);
		Utils.setMuxAux1(); // set Auxiliar1 socket
	
		// Switch ON the power supply
		PWR.setSensorPower(SENS_5V, SENS_ON);	
		WaspRegister |= REG_SOCKET1;

		// Turbidity Sensor ON
		pinMode(PWR_TURBIDITY, OUTPUT);
		digitalWrite(PWR_TURBIDITY, HIGH);
		
	}
	
	delay(100);

	result = init();
	
	return result;
}

 
//!*************************************************************
//!	Name:	OFF()														
//!	Description: Powers OFF the turbidity sensor					
//!	Param : void														
//!	Returns: void							
//!*************************************************************
void turbidityClass::OFF()
{	
	if (_boot_version >= 'H')
	{
	
		// Turbidity Sensor ON
		pinMode(PWR_TURBIDITY, OUTPUT);
		digitalWrite(PWR_TURBIDITY, LOW);
		
	}
}


//**********************************************************************
// Frame 80 and 100 in the documentation for Turbidity
//********************************************************************** 
//!*************************************************************
//!	Name:	readTurbidity()											
//!	Description: Read the turbidity value from the sensor		
//!	Param : void														
//!	Returns: "0" if no error, "-1" if error						
//!*************************************************************
uint8_t turbidityClass::readTurbidity()
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
	
	
	if (_boot_version < 'H')
	{
		// The sensor uses 9600 bps speed communication
		sensor.begin(9600);
		
		// Switch ON the power supply
		PWR.setSensorPower(SENS_5V, SENS_ON);	
	
		WaspRegister |= REG_RS485;
	}
	else
	{
		// The sensor uses 9600 bps speed communication
		sensor.begin(9600, 1);
		Utils.setMuxAux1(); // set Auxiliar1 socket
	
		// Switch ON the power supply
		PWR.setSensorPower(SENS_5V, SENS_ON);	
		WaspRegister |= REG_SOCKET1;

		// Turbidity Sensor ON
		pinMode(PWR_TURBIDITY, OUTPUT);
		digitalWrite(PWR_TURBIDITY, HIGH);
	}
	
	delay(10);
	
	//writeCalibrationValue(0x005D, getTemperature());	
	clearBuffer();
	delay(10);
	startMeasurment(TURB_NEW_MEAS);

	// This variable will store the result of the communication
	// result = 0 : no errors 
	// result = 1 : error occurred
	uint8_t result = -1;
	uint8_t retries = 0;
	
	while ((result !=0) && (retries < 20)) 
	{
		retries ++;
		sensor.readHoldingRegisters(TURB_MEAS_STATUS, 1);
		delay(1);
		// MASK for getting only the status of the register
		
		result = sensor.getResponseBuffer(0);
		
		#if DEBUG_TURBIDITY > 1
			PRINT_TURBIDITY(F("Turbidity measurement status: "));
			PRINTLN_TURBIDITY_VAL(result);			
		#endif
		
		result = sensor.getResponseBuffer(0) & 0x0007;     

		#if DEBUG_TURBIDITY > 1
			PRINT_TURBIDITY(F("Turbidity measurement status after mask: "));
			PRINTLN_TURBIDITY_VAL(result);
		#endif
		delay(10);
	}

	delay(200);
	
	clearBuffer();

	if (result != 0) {
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication error while reading turbidity measurement status..."));
		#endif

		return 1;
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
			#if DEBUG_TURBIDITY > 0
				// If no response from the slave, print an error message
				PRINTLN_TURBIDITY(F("Communication error while reading Turbidity"));
			#endif
			delay(150);
			
			return 1;
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
float turbidityClass::getTurbidity()
{
	uint8_t status = -1;
	uint8_t retries = 0;
	
	while ((status !=0) && (retries < 4)) 
	{
		
		delay(20);
		retries++;
		status = readTurbidity();
		
	}
	
	if (status == 1)
	{
		//if readTurbidity function fails return -1000
		return -1000.0;
	}
	
	rawData1 = turbidity * 1000;
	smoothData1 = digitalSmooth(rawData1, sensSmoothArray1);  

	float turbidity = smoothData1/1000.0;
	
	// negative values aren't usefull so return zeros
	// if sensor returns zeros (negative values) is might be badly placed
	if (turbidity<0.0)
	{
		turbidity = 0.0;
	}
	
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
float turbidityClass::getTemperature()
{
	uint8_t status = -1;
	uint8_t retries = 0;
	
	while ((status !=0) && (retries < 4)) 
	{
		
		delay(20);
		retries++;
		status = readTemperature();
		
	}
	if (status==0)
	{	
		return temperature;
	}
	
	// if readTemperature function fails -1000 is returned
	return -1000.0;
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
uint8_t turbidityClass::typeMeasurementConfiguration(uint16_t address, uint16_t config)
{
	delay(100);
	uint8_t result = sensor.writeSingleRegister(address, config);
	delay(100);

	// Chechk that the direction has been well writed
	if (result == 0) 
	{
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Type Measurement Register well configured"));
		#endif
		
		clearBuffer();
		delay(150);
		return 0;
	} 
	else 
	{ 			
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("ERROR. Type Measurement Register not configured."));
		#endif
		
		clearBuffer();
		delay(150);
		return 1;
	}
	
}



//!*************************************************************
//!	Name:	resetSensor()												
//!	Description: Resets the sensor to the default values			
//!	Param : void														
//!	Returns: void														
//!*************************************************************
uint8_t turbidityClass::resetSensor()
{
	// Result of the communication
	uint8_t result;

	// Use the new address of the sensor 
	sensor.setSlaveAddress(DEFAULT_ADDRESS);

	result = sensor.writeSingleRegister(RESET_REG, 0x000F);
	delay(200);
	
	if (result == 0) 
	{	
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Reset well done"));
		#endif	
					
		return 0;
	} 
	else 
	{ 
		// Use the new address of the sensor 
		sensor.setSlaveAddress(SENSOR_ADDRESS);
		
		result = sensor.writeSingleRegister(RESET_REG, 0x000F);
		delay(100);
	
		if (result == 0) 
		{	
			#if DEBUG_TURBIDITY > 0
				PRINTLN_TURBIDITY(F("Reset well done"));	
			#endif	
			
			return 0;		
		} 
		else
		{
			#if DEBUG_TURBIDITY > 0
				PRINTLN_TURBIDITY(F("Reset failure"));	
			#endif
			
			return 1;
		}
	}	
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
uint8_t turbidityClass::startMeasurment(uint8_t parameter)
{
	// Result of the communication
	uint8_t result;
	
	result = sensor.writeSingleRegister(NEW_MEAS_REG, parameter);
	delay(100); 
	
	// Chechk that the direction has been well writed
	if (result == 0) 
	{
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Starting a new measure process..."));
		#endif
		
		return 0;		
	} 
	else 
	{ 
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication Error. The sensor can't take a new measure."));
		#endif
		init();
		return 1;
	}

}


//**********************************************************************
// Frame 80 and 100 in the documentation for Temperature
//**********************************************************************
//!*************************************************************
//!	Name:	readTemperature()											
//!	Description: Read the temperature value from the sensor		
//!	Param : void														
//!	Returns: "0" if no error, "-1" if error						
//!*************************************************************
uint8_t turbidityClass::readTemperature() 
{
	union 
	{
		int ints[2];   
		float toFloat;
	}
	foo;
	
	if (_boot_version < 'H')
	{
		// The sensor uses 9600 bps speed communication
		sensor.begin(9600);
		
		// Switch ON the power supply
		PWR.setSensorPower(SENS_5V, SENS_ON);	
	
		WaspRegister |= REG_RS485;
	}
	else
	{
		// The sensor uses 9600 bps speed communication
		sensor.begin(9600, 1);
		Utils.setMuxAux1(); // set Auxiliar1 socket
	
		// Switch ON the power supply
		PWR.setSensorPower(SENS_5V, SENS_ON);	
		WaspRegister |= REG_SOCKET1;

		// Turbidity Sensor ON
		pinMode(PWR_TURBIDITY, OUTPUT);
		digitalWrite(PWR_TURBIDITY, HIGH);
	}
	
	clearBuffer();
	startMeasurment(TEMP_NEW_MEAS);

	// This variable will store the result of the communication
	// result = 0 : no errors 
	// result = 1 : error occurred
	uint8_t result = -1;
	uint8_t retries = 0;

	delay(100);

	while ((result !=0) & (retries < 20)) 
	{  
		retries ++;
		sensor.readHoldingRegisters(TEMP_MEAS_STATUS, 1);
		// MASK for getting only the status of the register
		
		result = sensor.getResponseBuffer(0);
		
		#if DEBUG_TURBIDITY > 1
			PRINT_TURBIDITY(F("Temperature measurement status: "));
			PRINTLN_TURBIDITY_VAL(result);
		#endif
		
		result = sensor.getResponseBuffer(0) & 0x0007;

		#if DEBUG_TURBIDITY > 1
			PRINT_TURBIDITY(F("Temperature measurement status: "));
			PRINTLN_TURBIDITY_VAL(result);
		#endif
		
		delay(100);    
	}

	delay(100);

	if (result != 0) {    
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication error while reading temperature measurement status..."));
		#endif

		return 1;
	} 
	else {
		result = sensor.readHoldingRegisters(TEMP_VALUE_REG, 2);

		if (result != 0) {
			#if DEBUG_TURBIDITY > 1
				// If no response from the slave, print an error message
				PRINTLN_TURBIDITY(F("Communication error while reading temperature..."));
			#endif
			
			return 1;
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
uint8_t turbidityClass::average(uint8_t average)
{
	if (average > 50)
		average = 50;
	
	uint8_t result = sensor.writeSingleRegister(AVRG_PARA_REG, average);

	// Chechk that the direction has been well writed
	if (result == 0)
	{
		#if DEBUG_TURBIDITY > 0	
			PRINTLN_TURBIDITY(F("Average configured..."));
		#endif 
		return 0;
	} 
	else
	
	{ 
		#if DEBUG_TURBIDITY > 0
			PRINTLN_TURBIDITY(F("Communication Error. Average not configured."));
		#endif 
		return 1;
	}
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
uint8_t turbidityClass::configureSensorAddress(uint8_t address)
{
	
	uint8_t result = -1;
	uint8_t retries = 0;

	while ((result !=0) && (retries < 10))
	{ 	
		retries ++;
		// Asign the address to the sensor
		result = sensor.writeSingleRegister(ADDRESS_REG, address);
		delay(50);
	}

	#if DEBUG_TURBIDITY > 0
		if (result == 0) 
		{
			// If no response from the slave, print an error message
			PRINTLN_TURBIDITY(F("Address well configured"));
		} 
		else 
		{ 
			PRINTLN_TURBIDITY(F("Communication Error. Address not configured."));
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
		// If no response from the slave return 1
		return 1; 
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
void turbidityClass::clearBuffer()
{
	// Clear Response Buffer
	sensor.clearResponseBuffer();
	sensor.clearTransmitBuffer();
	delay(10);
}


//!*************************************************************
//!	Name:	digitalSmooth()									
//!	Description: Digital smooth filter		
//!	Param : int rawIn: Value to be filtered
//!			int *sensSmoothArray: array of previous values		
//!	Returns: long: filtered value					
//!*************************************************************
long turbidityClass::digitalSmooth(int rawIn, int *sensSmoothArray)
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



//!*************************************************************
//!	Name:	init()									
//!	Description: Initialization function	
//!	Returns:	1 reset error	
//!				2 configure address error
//!*************************************************************

uint8_t turbidityClass::init()
{
	uint8_t status = -1;
	uint8_t retries = 0;
	
	while ((status !=0) && (retries < 4)) 
	{
		
		delay(20);
		retries++;
	
		// Important: Reset the registers of the sensor
		status = resetSensor();
		
	}
	
	// Check that the reset has been done
	if (status == 0) 
	{
		#if DEBUG_TURBIDIRY > 0
		PRINTLN_TURBIDITY(F("Sensor reset correctly"));
		#endif
	} 
	else 
	{ 
		#if DEBUG_TURBIDIRY > 0
		PRINTLN_TURBIDITY(F("Communication Error. The reset hasn't been done."));
		#endif
		return 1;
	}
	
	// Configure the sensor address
	status = configureSensorAddress(SENSOR_ADDRESS);

	// Check that the address has been well configured
	if (status == 0) 
	{
		#if DEBUG_TURBIDIRY > 0
		PRINTLN_TURBIDITY(F("Sensor address configured correctly"));
		#endif
	} 
	else 
	{ 
		#if DEBUG_TURBIDIRY > 0
		PRINTLN_TURBIDITY(F("Communication Error. The address hasn't been configured."));
		#endif
		return 2;
	}


	delay(10);

	// Clear the Modbus buffers
	clearBuffer();
	
	status = -1;
	retries = 0;
	
	while ((status !=0) && (retries < 4)) 
	{
		retries++;
		
		// Configure the type measurement of the temperature sensor
		status = typeMeasurementConfiguration(TEMP_TYPE_CON, 0x0003);
		delay(20);
		clearBuffer();

	}
	
	// Check that the address has been well configured
	if (status == 0) 
	{
		#if DEBUG_TURBIDIRY > 0
		PRINTLN_TURBIDITY(F("Sensor meassurement configured correctly"));
		#endif
	} 
	else 
	{ 
		#if DEBUG_TURBIDIRY > 0
		PRINTLN_TURBIDITY(F("Communication Error. The meassurement type hasn't been configured."));
		#endif
		return 3;
	}
	// Configure the average measurement
	average(25);
	
	return 0;
}


