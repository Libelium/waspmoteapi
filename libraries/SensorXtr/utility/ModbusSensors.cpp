/*! \file ModbusSensors.cpp
	\brief Library for managing the modbus sensors in Smart Water Xtreme.
	This library is not compatible con Smart water version.

	Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
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

	Version:			3.0
	Design:				David Gascón
	Implementation:		Victor Boria
*/


/***********************************************************************
 * Includes
 ***********************************************************************/
#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "ModbusSensors.h"


uint8_t sensorAddress; //!< Sensor address
uint16_t waitingTime;

/***********************************************************************
 * Class contructors
 ***********************************************************************/
modbusSensorsClass::modbusSensorsClass()
{
	waitingTime = DEFAULT_WAITING_TIME;
	temporaryCoefficientListBuffer = 0;
}


/***********************************************************************
 * Class contructors
 ***********************************************************************/
modbusSensorsClass::modbusSensorsClass(uint8_t address)
{
	waitingTime = DEFAULT_WAITING_TIME;
	temporaryCoefficientListBuffer = 0;
}

/***********************************************************************
 * Methods of the Class
 ***********************************************************************/

//!*************************************************************
//!	Name:	initCommunication()
//!	Description: Initializes the communication channel
//!	Param : void
//!	Returns: void
//!*************************************************************
void modbusSensorsClass::initCommunication()
{
	sensor = ModbusMaster(RS232_COM, sensorAddress);

	// The sensor uses 9600 bps speed communication
	sensor.begin(9600, 1);

	// Two stop bits configuration
	//sbi(UCSR1C, USBS1);		//FIX: this is not needed and also there is a dedicated function for this.
	
	// set Auxiliar2 socket
	Utils.setMuxAux2();
	
	clearBuffer();
}


//!*************************************************************
//!	Name:	initSensor()
//!	Description: Setups the sensor configuration paramenters 
//!	Param : void
//!	Returns: void
//!*************************************************************
uint8_t modbusSensorsClass::initSensor()
{
	initCommunication();
	
	//Get the necessary waiting time to get measures after asking for them
	if(readWaitingTime() != 0)
	{
		return 1;
	}
	
	//Our avg by default must be 1
	uint8_t avg = 1;
	
	//Configure average
	if(writeAverage(avg) == 0)
	{
		if(readAverage() != avg)
		{
			#if DEBUG_XTR_MODBUS > 0
				PRINTLN_XTR_MODBUS(F("Error configuring average"));
			#endif
			return 1;
		}
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication error writing average"));
		#endif
		//if fails return 1
		return 1;
	}
	
	return 0;
}


//!*************************************************************
//!	Name:	initSensor()
//!	Description: Setups the sensor configuration paramenters 
//!	Param : void
//!	Returns: void
//!*************************************************************
uint8_t modbusSensorsClass::initSensor(uint8_t range)
{
	initCommunication();
	
	//Get the necessary waiting time to get measures after asking for them
	if(readWaitingTime() != 0)
	{
		return 1;
	}
	
	//Configure Parameter 1: 
	//In NTU sensor is Nephelometric Turbidity
	//In C4E sensor is Conductivity
	if(writeParamConfig(1, range) == 0)
	{
		if(readParamConfig(1)/256 != range)
		{
			#if DEBUG_XTR_MODBUS > 0
				PRINTLN_XTR_MODBUS(F("Error configuring param"));
			#endif
			return 1;
		}
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication error writing param config"));
		#endif
		//if fails return 1
		return 1;
	}
	
	//Our avg by default must be 1
	uint8_t avg = 1;
	
	//Configure average
	if(writeAverage(avg) == 0)
	{
		if(readAverage() != avg)
		{
			#if DEBUG_XTR_MODBUS > 0
				PRINTLN_XTR_MODBUS(F("Error configuring average"));
			#endif
			return 1;
		}
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication error writing average"));
		#endif
		//if fails return 1
		return 1;
	}
	
	return 0;
}


//!*************************************************************
//!	Name:	initSensor()
//!	Description: Setups the sensor configuration paramenters 
//!	Param : void
//!	Returns: void
//!*************************************************************
uint8_t modbusSensorsClass::initSensor(uint8_t range, uint8_t avg)
{
	initCommunication();
	
	//Get the necessary waiting time to get measures after asking for them
	if(readWaitingTime() != 0)
	{
		return 1;
	}
	
	//Configure Parameter 1: Nephelo turbidity in NTU
	//Configure Parameter 1: Conductivity in C4E
	if(writeParamConfig(1, range) == 0)
	{
		if(readParamConfig(1)/256 != range)
		{
			#if DEBUG_XTR_MODBUS > 0
				PRINTLN_XTR_MODBUS(F("Error configuring param"));
			#endif
			return 1;
		}
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication error writing param config"));
		#endif
		//if fails return 1
		return 1;
	}
	
	//Configure average
	if(writeAverage(avg) == 0)
	{
		if(readAverage() != avg)
		{
			#if DEBUG_XTR_MODBUS > 0
				PRINTLN_XTR_MODBUS(F("Error configuring average"));
			#endif
			return 1;
		}
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication error writing average"));
		#endif
		//if fails return 1
		return 1;
	}
	
	return 0;
}


//!*************************************************************
//!	Name:	readParamConfig(uint8_t paramNumber)
//!	Description: Returns all the measures of the sensor
//!	Param : paramNumber
//!	Returns: 0 is OK, 1 if error
//!*************************************************************
uint8_t modbusSensorsClass::writeParamConfig(uint8_t paramNumber, uint8_t range)
{
	initCommunication();
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	uint16_t address;
	
	switch(paramNumber)
	{
		case 1:
			address = 0x00A6;
			break;
		
		case 2:
			address = 0x00A7;
			break;
			
		case 3:
			address = 0x00A8;
			break;
		
		case 4:
			address = 0x00A9;
			break;
			
		default:
			address = 0x00A6;
			break;
	}
	
	//Range is set in byte 1 of the parameter, byte 0 is 0
	uint16_t configRegister = range*256;
	
	status = -1;
	retries = 0;
	
	while ((status !=0) && (retries < 5))
	{
		//Write 1 register (set previouly in TX buffer) in param address
		status =  sensor.writeSingleRegister(address, configRegister);
		
		retries++;
		delay(10);
	}
	
	if (status == 0)
	{
		#if DEBUG_XTR_MODBUS > 1
		PRINT_XTR_MODBUS(F("Param "));
		USB.print(paramNumber, DEC);
		USB.print(F(" configured to range:"));
		USB.println(range, DEC);
		#endif
	}
	else
	{
		// If no response from the slave, print an error message.
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication error (Writing Multiple Registers)"));
		#endif

		return 1;
	}
	
	return 0;

}


//!*************************************************************
//!	Name:	readParamConfig(uint8_t paramNumber)
//!	Description: Returns all the measures of the sensor
//!	Param : paramNumber
//!	Returns: paramConfig if OK, 0 if error
//!*************************************************************
uint16_t modbusSensorsClass::readParamConfig(uint8_t paramNumber)
{
	uint16_t address;
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	initCommunication();
	
	switch(paramNumber)
	{
		case 1:
			address = 0x00A6;
			break;
		
		case 2:
			address = 0x00A7;
			break;
			
		case 3:
			address = 0x00A8;
			break;
		
		case 4:
			address = 0x00A9;
			break;
			
		default:
			address = 0x00A6;
			break;
	}
	
	while ((status !=0) && (retries < 10))
	{
		//Read 1 register
		status = sensor.readHoldingRegisters(address, 1);
		delay(10);
		retries++;
	}
	
	uint16_t configRegister = 0;

	if (status == 0)
	{
		configRegister = sensor.getResponseBuffer(0);
		#if DEBUG_XTR_MODBUS > 1
			PRINT_XTR_MODBUS(F("Param "));
			USB.print(paramNumber, DEC);
			USB.print(F(" read with range:"));
			USB.println(configRegister/256, DEC);
		#endif
		
		return configRegister;
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Error reading ParamConfig"));
		#endif
		
		return 0;
	}
}

//!*************************************************************
//!	Name:	writeCalibrationStandard()
//!	Description: Configure the acalibration standart
//!	Param : address and value
//!	Returns: uint8_t "0" if no error, "1" if error
//!*************************************************************
uint8_t modbusSensorsClass::writeCalibrationStandard(uint16_t address, float value)
{
	initCommunication();
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	foo.toFloat = value;
	sensor.setTransmitBuffer(0, foo.ints[1]);
	sensor.setTransmitBuffer(1, foo.ints[0]);
	
	while ((status !=0) && (retries < 5))
	{
		status = sensor.writeMultipleRegisters(address, 2);
		delay(10);
		retries++;
	}

	// Check that the direction has been well written
	if (status == 0)
	{
		#if DEBUG_XTR_MODBUS > 1
			PRINT_XTR_MODBUS(F("Calibration standard with address 0x0"));
			USB.print(address, HEX);
			USB.print(F(" written with value:"));
			USB.println(value);
		#endif
		return 0;
	}
	else

	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Error writing calibration standard"));
		#endif
		return 1;
	}
}

//!*************************************************************
//!	Name:	readCalibrationStandard(uint8_t address)
//!	Description: Returns the calibration standard in a particular address
//!	Param : address
//!	Returns: calibrationStandard if OK, -1 if error
//!*************************************************************
float modbusSensorsClass::readCalibrationStandard(uint16_t address)
{
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	initCommunication();
	
	while ((status !=0) && (retries < 10))
	{
		//Read 2 register -> 1 float (4 bytes)
		status = sensor.readHoldingRegisters(address, 2);
		delay(10);
		retries++;
	}
	
	float calibrationStandard = 0;

	if (status == 0)
	{
		foo.ints[0] = sensor.getResponseBuffer(1);
		foo.ints[1] = sensor.getResponseBuffer(0);
		calibrationStandard = foo.toFloat;
			
			
		#if DEBUG_XTR_MODBUS > 1
			PRINT_XTR_MODBUS(F("Calibration standard with address 0x0"));
			USB.print(address, HEX);
			USB.print(F(" read with value:"));
			USB.println(calibrationStandard);
		#endif
		
		return calibrationStandard;
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Error reading calibration standard"));
		#endif
		
		return -1;
	}
}



//!*************************************************************
//!	Name:	restoreToFactoryCalibration()
//!	Description: restores to factory calibration
//!	Param : the use of value depends on the step
//!	Returns: "0" if no error, "1" if error
//!*************************************************************
uint8_t modbusSensorsClass::restoreToFactoryCalibration(uint8_t parameter)
{
	initCommunication();
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	uint16_t transmit_buffer = 0;
	switch (parameter)
	{
		case TEMPERATURE:
			transmit_buffer = 0x0001;
		break;
		
		case PARAMETER_1:
			transmit_buffer = 0x0002;
		break;
		
		case PARAMETER_2:
			transmit_buffer = 0x0004;
		break;
			
		case PARAMETER_3:
			transmit_buffer = 0x0008;
		break;
		
		case PARAMETER_4:
			transmit_buffer = 0x0010;
		break;
	}
	
	while ((status !=0) && (retries < 5))
	{
		status = sensor.writeSingleRegister(RESTORE_CALIB_REG, transmit_buffer);
		delay(10);
		retries++;
	}

	// Check that the direction has been well written
	if (status == 0)
	{
		#if DEBUG_XTR_MODBUS > 1
			PRINTLN_XTR_MODBUS(F("Restore to factory calibration successfully"));
		#endif
		return 0;
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Error restoring to factory calibration"));
		#endif
		return 1;
	}
}

//!*************************************************************
//!	Name:	calibrate()
//!	Description: Calibrates several parameters
//!	Param : the use of value depends on the step
//!	Returns: "0" if no error, "1" if error
//!*************************************************************
uint8_t modbusSensorsClass::calibrate(uint8_t sensor, uint8_t parameter, uint8_t step, float value)
{
	// General calibration process for several parameters
	switch (step)
	{
		//In step 1 we reset temporary calibration data and indicate the range if it exist
		//Additionaly we change the averagin to 25 only during calibration process
		case STEP_1:
			switch (sensor)
			{
				case OPTOD:
					switch (parameter)
					{
						case TEMPERATURE:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_TEMP_1;
							modbusSensorsXtr.address_slope = CALIB_STANDARD_TEMP_2;
						break;
						
						case PARAMETER_1:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_1;
							modbusSensorsXtr.address_slope = CALIB_STANDARD_4;
						break;
					}
				break;
				
				case PHEHT:
					switch (parameter)
					{
						case TEMPERATURE:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_TEMP_1;
							modbusSensorsXtr.address_slope = CALIB_STANDARD_TEMP_2;
						break;
						
						case PARAMETER_1:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_1;
							modbusSensorsXtr.address_slope = CALIB_STANDARD_2;
						break;
						
						case PARAMETER_2:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_3;
							modbusSensorsXtr.address_slope = CALIB_STANDARD_4;
						break;
					}
				break;
				
				case C4E:
					
					switch (parameter)
					{
						case TEMPERATURE:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_TEMP_1;
							modbusSensorsXtr.address_slope = CALIB_STANDARD_TEMP_2;
						break;
						
						case PARAMETER_1:
							switch ((uint8_t)value)
							{
								case RANGE_1:
									modbusSensorsXtr.address_offset = CALIB_STANDARD_1;
									modbusSensorsXtr.address_slope = CALIB_STANDARD_2;
									break;
								
								case RANGE_2:
									modbusSensorsXtr.address_offset = CALIB_STANDARD_3; 
									modbusSensorsXtr.address_slope	 = CALIB_STANDARD_4;
									break;
								
								case RANGE_3:
									modbusSensorsXtr.address_offset = CALIB_STANDARD_5; 
									modbusSensorsXtr.address_slope	 = CALIB_STANDARD_6;
									break;
								
								case RANGE_4:
									modbusSensorsXtr.address_offset = CALIB_STANDARD_7; 
									modbusSensorsXtr.address_slope	 = CALIB_STANDARD_8;
									break;
							}
						break;
					}
				break;
				
				case NTU:
					
					switch (parameter)
					{
						case TEMPERATURE:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_TEMP_1;
							modbusSensorsXtr.address_slope	 = CALIB_STANDARD_TEMP_2;
						break;
						
						case PARAMETER_1:
							switch ((uint8_t)value)
							{
								case RANGE_1:
									modbusSensorsXtr.address_offset = CALIB_STANDARD_1;
									modbusSensorsXtr.address_slope	 = CALIB_STANDARD_2;
									break;
								
								case RANGE_2:
									modbusSensorsXtr.address_offset = CALIB_STANDARD_3; 
									modbusSensorsXtr.address_slope	 = CALIB_STANDARD_4;
									break;
								
								case RANGE_3:
									modbusSensorsXtr.address_offset = CALIB_STANDARD_5; 
									modbusSensorsXtr.address_slope	 = CALIB_STANDARD_6;
									break;
								
								case RANGE_4:
									modbusSensorsXtr.address_offset = CALIB_STANDARD_7; 
									modbusSensorsXtr.address_slope	 = CALIB_STANDARD_8;
									break;
							}
						break;
					}
				break;
				
				
				case CTZN:
					switch (parameter)
					{
						case TEMPERATURE:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_TEMP_1;
							modbusSensorsXtr.address_slope	 = CALIB_STANDARD_TEMP_2;
						break;
						
						case PARAMETER_1:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_1;
							modbusSensorsXtr.address_slope	 = CALIB_STANDARD_2;
						break;
					}
				break;
				
				case MES5:
					switch (parameter)
					{
						case TEMPERATURE:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_TEMP_1;
							modbusSensorsXtr.address_slope	 = CALIB_STANDARD_TEMP_2;
						break;
						
						case PARAMETER_1:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_3;
							//address_slope = CALIB_STANDARD_2;
						break;
						
						case PARAMETER_3:
							modbusSensorsXtr.address_offset = CALIB_STANDARD_1;
							modbusSensorsXtr.address_slope	 = CALIB_STANDARD_2;
						break;
					}
				break;
			}

			
			//[231] Reset all temporary calibration data
			resetTemporaryCalibrationData(DONT_RETURN_AVG_TO_1);
			
			//Read all calibration standard registers
			//must be set to 0 after the reset
			if((readCalibrationStandard(modbusSensorsXtr.address_offset) != 0)
			|| (readCalibrationStandard(modbusSensorsXtr.address_slope) != 0))
			{
				#if DEBUG_XTR_MODBUS > 0
					PRINTLN_XTR_MODBUS(F("Error reseting temporary calibration data"));
				#endif
				
				return 1;
			}
			else
			{
				//Configure average -> change to 25 like Calsens
				if(writeAverage(25) == 0)
				{
					if(readAverage() != 25)
					{
						#if DEBUG_XTR_MODBUS > 0
							PRINTLN_XTR_MODBUS(F("Error configuring average to 25"));
						#endif
						return 1;
					}
				}
				else
				{
					#if DEBUG_XTR_MODBUS > 0
						PRINTLN_XTR_MODBUS(F("Communication error configuring average to 25"));
					#endif
					//if fails return 1
					return 1;
				}
				
				//PHEHT sensor in REDOX parameter requiere activate ELECTRONIC ZERO
				if((sensor == PHEHT) && (parameter == REDOX))
				{
					//Write float 1.0 in 0x0208 address
					if(writeCalibrationStandard(modbusSensorsXtr.address_offset, (float)1.0) == 1)
					{
						#if DEBUG_XTR_MODBUS > 0
							PRINTLN_XTR_MODBUS(F("Error writing calibration standart for offset for 1st time (electronic zero)"));
						#endif
						return 1;
					}
				}
				
			}
		break;
			
		//In step 2 user select calibration standard 1 (offset) 
		//This step must be done after stabilizing and measuring in water with 
		//the selected value using readMeasures function previosly
		case STEP_2:
			
			if((sensor == PHEHT) && (parameter == REDOX))
			{
				//Write float 2.0 in 0x0208 address
				if(writeCalibrationStandard(modbusSensorsXtr.address_offset, (float)2.0) == 1)
				{
					#if DEBUG_XTR_MODBUS > 0
						PRINTLN_XTR_MODBUS(F("Error writing calibration standart for offset for 2nd time (electronic zero)"));
					#endif
					return 1;
				}
				
				//[230] Then we update the list "temporary coefficient to be used for next measurement"
				//First we read the state of the list
				if(readTemporaryCoefficientList() == 1)
				{
					#if DEBUG_XTR_MODBUS > 0
						PRINTLN_XTR_MODBUS(F("Error reading Temporary Coefficient List"));
					#endif
					return 1;
				}
				//Then we update with the right bit in the list
				if(writeTemporaryCoefficientList(modbusSensorsXtr.address_offset) == 1)
				{
					#if DEBUG_XTR_MODBUS > 0
						PRINTLN_XTR_MODBUS(F("Error updating temporary coef list for offset"));
					#endif
					return 1;
				}
				
				//Write float 0.0 in 0x0208 address
				if(writeCalibrationStandard(modbusSensorsXtr.address_offset, (float)0.0) == 1)
				{
					#if DEBUG_XTR_MODBUS > 0
						PRINTLN_XTR_MODBUS(F("Error writing calibration standart for offset for 3rd time (electronic zero)"));
					#endif
					return 1;
				}
				
			}
			else
			{
				//[170] It stores the calibration standart, calculates automatically the coefficient
				//using the last measurement
				if(writeCalibrationStandard(modbusSensorsXtr.address_offset, value) == 1)
				{
					#if DEBUG_XTR_MODBUS > 0
						PRINTLN_XTR_MODBUS(F("Error writing calibration standart for offset"));
					#endif
					return 1;
				}
				//[230] Then we update the list "temporary coefficient to be used for next measurement"
				//First we read the state of the list
				if(readTemporaryCoefficientList() == 1)
				{
					#if DEBUG_XTR_MODBUS > 0
						PRINTLN_XTR_MODBUS(F("Error reading Temporary Coefficient List"));
					#endif
					return 1;
				}
				//Then we update with the right bit in the list
				if(writeTemporaryCoefficientList(modbusSensorsXtr.address_offset) == 1)
				{
					#if DEBUG_XTR_MODBUS > 0
						PRINTLN_XTR_MODBUS(F("Error updating temporary coef list for offset"));
					#endif
					return 1;
				}
			}
		break;
		
		//In step 3 user select calibration standard 2 (slope) 
		//This step must be done after stabilizing and measuring in water with 
		//the selected value
		case STEP_3:
			//[170] It stores the calibration standart, calculates automatically the coefficient
			//using the last measurement
			if(writeCalibrationStandard(modbusSensorsXtr.address_slope, value) == 1)
			{
				#if DEBUG_XTR_MODBUS > 0
					PRINTLN_XTR_MODBUS(F("Error writing calibration standart for slope"));
				#endif
				return 1;
			}
			//[230] Then we update the list "temporary coefficient to be used for next measurement"
			//First we read the state of the list
			if(readTemporaryCoefficientList() == 1)
			{
				#if DEBUG_XTR_MODBUS > 0
					PRINTLN_XTR_MODBUS(F("Error reading Temporary Coefficient List"));
				#endif
				return 1;
			}
			//Then we update with the right bit in the list
			if(writeTemporaryCoefficientList(modbusSensorsXtr.address_slope) == 1)
			{
				#if DEBUG_XTR_MODBUS > 0
					PRINTLN_XTR_MODBUS(F("Error updating temporary coef list for slope"));
				#endif
				return 1;
			}
		break;
		
		//Special case for pH calibration with 2 slopes (three point calibration)
		//In step 3 user select calibration standard 2 (slope) 
		//This step must be done after stabilizing and measuring in water with 
		//the selected value
		case STEP_3B:
		
		
			modbusSensorsXtr.address_slope = CALIB_STANDARD_5;
			
			//[170] It stores the calibration standart, calculates automatically the coefficient
			//using the last measurement
			if(writeCalibrationStandard(modbusSensorsXtr.address_slope, value) == 1)
			{
				#if DEBUG_XTR_MODBUS > 0
					PRINTLN_XTR_MODBUS(F("Error writing calibration standart for slope"));
				#endif
				return 1;
			}
			//[230] Then we update the list "temporary coefficient to be used for next measurement"
			//First we read the state of the list
			if(readTemporaryCoefficientList() == 1)
			{
				#if DEBUG_XTR_MODBUS > 0
					PRINTLN_XTR_MODBUS(F("Error reading Temporary Coefficient List"));
				#endif
				return 1;
			}
			//Then we update with the right bit in the list
			if(writeTemporaryCoefficientList(modbusSensorsXtr.address_slope) == 1)
			{
				#if DEBUG_XTR_MODBUS > 0
					PRINTLN_XTR_MODBUS(F("Error updating temporary coef list for slope"));
				#endif
				return 1;
			}
		break;
		//In step 4 user validates the entire calibration entering operator's name and date
		case STEP_4:
			//[210]
			uint8_t response_1 = writeCalibrationValidation((uint8_t)parameter);
			
			//[231] Reset all temporary calibration data for finishing the validation and return averaging to 1
			uint8_t response_2 = resetTemporaryCalibrationData(RETURN_AVG_TO_1);
				
			//if error, return 1
			if((response_1 == 1) || (response_2 == 1))
			{
				return 1;
			}
			
		break;
	}
	
	return 0;
}


//!*************************************************************
//!	Name:	validateCalibration()
//!	Description: Validates the calibration entering name and date
//!	Param : void
//!	Returns: 0 if OK, 1 if error
//!*************************************************************
uint8_t modbusSensorsClass::writeCalibrationValidation(uint8_t value)
{
	initCommunication();
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	uint16_t nameAddress;
	uint16_t dateAddress;
	
	switch (value)
	{
		case TEMPERATURE:
			nameAddress = 0x027E;
			dateAddress = 0x0286;
			break;
		
		case PARAMETER_1:
			nameAddress = 0x028E;
			dateAddress = 0x0296;
			break;
			
		case PARAMETER_2:
			nameAddress = 0x029E;
			dateAddress = 0x02A6;
			break;
			
		case PARAMETER_3:
			nameAddress = 0x02AE;
			dateAddress = 0x02B6;
			break;
	}

	//Prepare operator name in buffer
	for(uint8_t i = 0; i<8; i++)
	{
		foo2.uint8t[0] = calibrationOperatorsName[(i*2)+1];
		foo2.uint8t[1] = calibrationOperatorsName[(i*2)];
		sensor.setTransmitBuffer(i, foo2.uint16t);
	}
	
	while ((status !=0) && (retries < 5))
	{
		status = sensor.writeMultipleRegisters(nameAddress, 8);
		delay(10);
		retries++;
	}

	// Check that the direction has been well written
	if (status == 0)
	{
		#if DEBUG_XTR_MODBUS > 1
			PRINTLN_XTR_MODBUS(F("Operator name written"));
		#endif
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Error writing operator name"));
		#endif
		return 1;
	}
	
	
	//Now prepare calibration date in buffer
	for(uint8_t i = 0; i<8; i++)
	{
		foo2.uint8t[0] = calibrationDate[(i*2)+1];
		foo2.uint8t[1] = calibrationDate[(i*2)];
		sensor.setTransmitBuffer(i, foo2.uint16t);
	}
	
	//Now write date of calibration
	status = -1;
	retries = 0;
	
	while ((status !=0) && (retries < 5))
	{
		status = sensor.writeMultipleRegisters(dateAddress, 8);
		delay(10);
		retries++;
	}

	// Check that the direction has been well written
	if (status == 0)
	{
		#if DEBUG_XTR_MODBUS > 1
			PRINTLN_XTR_MODBUS(F("Calibration date written"));
		#endif
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Error writing calibration date"));
		#endif
		return 1;
	}
	
	return 0;
}

//!*************************************************************
//!	Name:	readTemporaryCoefficientList()
//!	Description: read Temporary Coefficient List
//!	Param : void
//!	Returns: 0 if OK, 1 if error
//!*************************************************************
uint8_t modbusSensorsClass::readTemporaryCoefficientList()
{
	initCommunication();
	
	uint16_t average = 0;
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	while ((status !=0) && (retries < 10))
	{
		//Read 1 register
		status = sensor.readHoldingRegisters(TEMP_COEF_LIST_REG, 2);
		delay(10);
		retries++;
	}

	if (status == 0)
	{
		//sensor.getResponseBuffer(0); must be always 0x00
		temporaryCoefficientListBuffer = sensor.getResponseBuffer(1);
		
		#if DEBUG_XTR_MODBUS > 1
			PRINT_XTR_MODBUS(F("Temporary Coefficient List read: Ox"));
			foo2.uint16t = temporaryCoefficientListBuffer;
			USB.printHex(foo2.uint8t[1]);
			USB.printHex(foo2.uint8t[0]);
			USB.println();
		#endif
		
		return 0;
	}
	else
	{
		// If no response from the slave, print an error message.
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication error Temporary Coefficient List"));
		#endif
		
		//if fails return 1
		return 1;
	}
}




//!*************************************************************
//!	Name:	writeTemporaryCoefficientList()
//!	Description: write temporary coefficient list
//!	Param : coefficient
//!	Returns: "0" if no error, "1" if error
//!*************************************************************
uint8_t modbusSensorsClass::writeTemporaryCoefficientList(uint16_t coefficient)
{
	initCommunication();
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	switch (coefficient)
	{
		case CALIB_STANDARD_TEMP_1:
			bitSet(temporaryCoefficientListBuffer, 0); 
			break;
			
		case CALIB_STANDARD_TEMP_2:
			bitSet(temporaryCoefficientListBuffer, 1); 
			break;
			
		case CALIB_STANDARD_1:
			bitSet(temporaryCoefficientListBuffer, 2); 
			break;
			
		case CALIB_STANDARD_2:
			bitSet(temporaryCoefficientListBuffer, 3); 
			break;
			
		case CALIB_STANDARD_3:
			bitSet(temporaryCoefficientListBuffer, 4); 
			break;
			
		case CALIB_STANDARD_4:
			bitSet(temporaryCoefficientListBuffer, 5); 
			break;
			
		case CALIB_STANDARD_5:
			bitSet(temporaryCoefficientListBuffer, 6); 
			break;
			
		case CALIB_STANDARD_6:
			bitSet(temporaryCoefficientListBuffer, 7); 
			break;
			
		case CALIB_STANDARD_7:
			bitSet(temporaryCoefficientListBuffer, 8); 
			break;
			
		case CALIB_STANDARD_8:
			bitSet(temporaryCoefficientListBuffer, 9); 
			break;
			
		case CALIB_STANDARD_9:
			bitSet(temporaryCoefficientListBuffer, 10); 
			break;
			
		case CALIB_STANDARD_10:
			bitSet(temporaryCoefficientListBuffer, 11); 
			break;
	}
	
	sensor.setTransmitBuffer(0, 0x0000);
	sensor.setTransmitBuffer(1, temporaryCoefficientListBuffer);
	
	while ((status !=0) && (retries < 5))
	{
		status = sensor.writeMultipleRegisters(TEMP_COEF_LIST_REG, 2);
		delay(10);
		retries++;
	}

	// Check that the direction has been well written
	if (status == 0)
	{
		#if DEBUG_XTR_MODBUS > 1
			PRINT_XTR_MODBUS(F("Temporary Coefficient List written with value 0x0"));
			foo2.uint16t = temporaryCoefficientListBuffer;
			USB.printHexln(foo2.uint8t, 2);
		#endif
		return 0;
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Error writing Temporary Coefficient List"));
		#endif
		return 1;
	}
}



//!*************************************************************
//!	Name:	resetTemporaryCalibrationData()
//!	Description: Reset all temporary calibration data and return average to 1
//!	Param : void
//!	Returns: "0" if no error, "1" if error
//!*************************************************************
uint8_t modbusSensorsClass::resetTemporaryCalibrationData(uint8_t returnAvgTo1_stopElectronicZero)
{
	//Write '0x00000000 ' at 0x014C address 
	//List of temporary coefficients to be used in measurement calculation
	initCommunication();
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;

	sensor.setTransmitBuffer(0, 0x0000);
	sensor.setTransmitBuffer(1, 0x0000);

	while ((status !=0) && (retries < 5))
	{
		status = sensor.writeMultipleRegisters(0x014C, 2);
		delay(10);
		retries++;
	}

	// Check that the direction has been well written
	if (status != 0)
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("0x014C writing failed"));
		#endif
		return 1;
	}
	
	//Write '0x0001' at 0x004C address
	//Reset standard + Operator + Date of temporary calibration
	//active with value 0x01
	status = -1;
	retries = 0;

	sensor.setTransmitBuffer(0, 0x0001);

	while ((status !=0) && (retries < 5))
	{
		//List of temporary coefficients to be used in measurement calculation 
		status = sensor.writeMultipleRegisters(0x004C, 1);
		delay(10);
		retries++;
	}

	// Check that the direction has been well written
	if (status != 0)
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("0x014C writing failed"));
		#endif
		return 1;
	}
	
	if(returnAvgTo1_stopElectronicZero > 0)
	{
		//Configure average -> return to 1
		if(writeAverage(1) == 0)
		{
			if(readAverage() != 1)
			{
				#if DEBUG_XTR_MODBUS > 0
					PRINTLN_XTR_MODBUS(F("Error configuring average to 1"));
				#endif
				return 1;
			}
		}
		else
		{
			#if DEBUG_XTR_MODBUS > 0
				PRINTLN_XTR_MODBUS(F("Communication error configuring average to 1"));
			#endif
			//if fails return 1
			return 1;
		}
	}
	
	if(returnAvgTo1_stopElectronicZero == RETURN_AVG_TO_1_AND_STOP_ELECTRONIC_ZERO)
	{
		//Write float 3.0 in 0x0208 address
		if(writeCalibrationStandard(0x0208, (float)3.0) == 1)
		{
			#if DEBUG_XTR_MODBUS > 0
				PRINTLN_XTR_MODBUS(F("Error writing calibration standart for stopping electronic zero"));
			#endif
			return 1;
		}
	}
	return 0;
}



//!*************************************************************
//!	Name:	writeAverage()
//!	Description: Configure the average value (1-50)
//!	Param : avg
//!	Returns: uint8_t "0" if no error, "1" if error
//!*************************************************************
uint8_t modbusSensorsClass::writeAverage(uint8_t avg)
{
	initCommunication();
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;

	if (avg > 50) avg = 50;


	while ((status !=0) && (retries < 5))
	{

		status = sensor.writeSingleRegister(AVRG_PARA_REG, avg);

		delay(10);
		retries++;
	}

	// Check that the direction has been well written
	if (status == 0)
	{
		#if DEBUG_XTR_MODBUS > 1
			PRINT_XTR_MODBUS(F("Average configured with value:"));
			USB.println(avg, DEC);
		#endif
		return 0;
	}
	else

	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication Error. Average not configured."));
		#endif
		return 1;
	}
}

//!*************************************************************
//!	Name:	readWaitingTime()
//!	Description: Get the necessary waiting time to get measures after asking for them
//!	Param : void
//!	Returns: 0 if OK, 1 if error
//!*************************************************************
uint8_t modbusSensorsClass::readWaitingTime()
{
	initCommunication();
	
	uint16_t average = 0;
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	while ((status !=0) && (retries < 10))
	{
		//Read 1 register
		status = sensor.readHoldingRegisters(WAITING_TIME_REG, 1);
		delay(10);
		retries++;
	}

	if (status == 0)
	{
		waitingTime = sensor.getResponseBuffer(0);
		
		#if DEBUG_XTR_MODBUS > 1
			PRINT_XTR_MODBUS(F("waitingTime:"));
			USB.print(waitingTime);
			USB.println(F("ms"));
		#endif
		
		return 0;
	}
	else
	{
		// If no response from the slave, print an error message.
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication error reading waiting time"));
		#endif
		
		//if fails return 1
		return 1;
	}
}

//!*************************************************************
//!	Name:	readAverage()
//!	Description: Read the average value (1-50)
//!	Param : void
//!	Returns: average value (1-50) if OK, 0 if error
//!*************************************************************
uint16_t modbusSensorsClass::readAverage()
{
	initCommunication();
	
	uint16_t average = 0;
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	while ((status !=0) && (retries < 10))
	{
		//Read 1 register
		status = sensor.readHoldingRegisters(AVRG_PARA_REG, 1);
		delay(10);
		retries++;
	}

	if (status == 0)
	{
		average = sensor.getResponseBuffer(0);
		
		#if DEBUG_XTR_MODBUS > 1
			PRINT_XTR_MODBUS(F("Average read with value:"));
			USB.println(average, DEC);
		#endif
		
		return average;
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Error reading average"));
		#endif
		
		return 0;
	}
}



//!*************************************************************
//!	Name:	clearBuffer()
//!	Description: Flushes the buffers.
//!	Param : void
//!	Returns: void
//!*************************************************************
void modbusSensorsClass::clearBuffer()
{
	// Clear Response Buffer
	sensor.clearResponseBuffer();
	sensor.clearTransmitBuffer();
	delay(10);
}



//!*************************************************************
//!	Name:	readSerialNumber()
//!	Description: Gets the serial number of the sensor
//!	Param : void
//!	Returns: "0" if no error, "1" if error
//!*************************************************************
uint8_t modbusSensorsClass::readSerialNumber(char *sensorSerialNumber)
{

	initCommunication();
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	while ((status !=0) && (retries < 5))
	{
		retries++;
		
		status =  sensor.readHoldingRegisters(SERIAL_NUMBER_REG, 16);
		delay(10);
	}
	
	uint8_t j = 0;
	
	if (status == 0)
	{

		for (int i=0; i<7; i++)
		{
			sensorSerialNumber[j++] = sensor.getResponseBuffer(i) >>8 & 0xFF;
			sensorSerialNumber[j++] = sensor.getResponseBuffer(i) & 0xFF;
		}
	}
	else
	{
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Error reading serial number"));
		#endif
		
		return 1;
	}

	return status;
}


void modbusSensorsClass::setParametersBySensor(uint8_t sensorType)
{
	switch (sensorType)
	{
		case OPTOD:
			sensorAddress = 10;
			waitingTime = 500;
			break;
		
		case PHEHT:
			sensorAddress = 20;
			waitingTime = 400;
			break;
		
		case C4E:
			sensorAddress = 30;
			waitingTime = 500;
			break;
		
		case NTU:
			sensorAddress = 40;
			waitingTime = 300;
			break;
		
		case CTZN:
			sensorAddress = 50;
			waitingTime = 500;
			break;
		
		case MES5:
			sensorAddress = 60;
			waitingTime = 500;
			break;
		
		default:
			sensorAddress = 40;
			waitingTime = 400;
			break;
	}
}


//!*************************************************************
//!	Name:	readMeasures()
//!	Description: Returns all the measures of the sensor
//!	Param : void
//!	Returns: 1 if OK, 0 if error
//!*************************************************************
uint8_t modbusSensorsClass::readMeasures(float &parameter1, float &parameter2, float &parameter3, float &parameter4)
{
	initCommunication();
	
	uint8_t status = 0xFF;
	uint8_t retries = 0;
	
	
	//Set Modbus TX buffer with "0x000F" in order to get the 4 measures of the sensor
	//			TX buffer
	//	0	0	0	0	1	1	1	1
	//					P3	P2	P1	T
	sensor.setTransmitBuffer(0, 0x000F);
	
	while ((status !=0) && (retries < 5))
	{
		retries++;
		
		//Write 1 register (set previouly in TX buffer) in address "NEW_MEAS_REG"
		status =  sensor.writeMultipleRegisters(NEW_MEAS_REG, 1);
		delay(10);
	}

	// Important delay
	delay(waitingTime + 10);
	
	if (status == 0)
	{
		status = -1;
		retries = 0;

		while ((status !=0) && (retries < 10))
		{
			//Read 8 registers with the 4 measures (each register is 2 bytes)
			status = sensor.readHoldingRegisters(MEASUREMENTS_REG, 0x08);
			retries++;
			delay(10);
		}

		if (status == 0)
		{
			foo.ints[0] = sensor.getResponseBuffer(1);
			foo.ints[1] = sensor.getResponseBuffer(0);
			parameter1 = foo.toFloat;

			foo.ints[0] = sensor.getResponseBuffer(3);
			foo.ints[1] = sensor.getResponseBuffer(2);
			parameter2 = foo.toFloat;
			
			foo.ints[0] = sensor.getResponseBuffer(5);
			foo.ints[1] = sensor.getResponseBuffer(4);
			parameter3 = foo.toFloat;

			foo.ints[0] = sensor.getResponseBuffer(7);
			foo.ints[1] = sensor.getResponseBuffer(6);
			parameter4 = foo.toFloat;
		}
		else
		{
			// If no response from the slave, print an error message.
			#if DEBUG_XTR_MODBUS > 0
				PRINTLN_XTR_MODBUS(F("Communication error reading parameters"));
			#endif
			
			//if fails return 0
			return 0;
		}
	}
	else
	{
		// If no response from the slave, print an error message.
		#if DEBUG_XTR_MODBUS > 0
			PRINTLN_XTR_MODBUS(F("Communication error (Writing Multiple Registers)"));
		#endif

		return 0;
	}

	return 1;
}



modbusSensorsClass	modbusSensorsXtr = modbusSensorsClass();

