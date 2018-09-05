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
 *  Design:			Ahmad Saad
 */

//!*************************************************************************************
//! Includes
//!*************************************************************************************
#include "smartWaterIons.h"


#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

//**************************************************************************************************
//  Smart Water Board Class 
//**************************************************************************************************
//!*************************************************************************************
//!	Name:	WaspSensorSWIons()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
WaspSensorSWIons::WaspSensorSWIons()
{
	// Update Waspmote Control Register
	WaspRegisterSensor |= REG_WATER_IONS;
	
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
}


//!*************************************************************************************
//!	Name:	ON()										
//!	Description: Switch ON the board and configure the ADC and the multiplexer		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
void WaspSensorSWIons::ON(void)
{
	// Turn on the power switches in Waspmote
	PWR.setSensorPower(SENS_5V, SENS_ON);
	PWR.setSensorPower(SENS_3V3, SENS_ON);
	delay(1000);
	
	// These pins manage the analog multiplexor
	// Digital pin 2 is for selecting
	pinMode(DIGITAL2, OUTPUT);
	pinMode(DIGITAL5, OUTPUT);
	pinMode(DIGITAL4, OUTPUT);
	pinMode(DIGITAL3, OUTPUT);
	pinMode(DRDY, INPUT);
	delay(100);
	
	// Configure the ADC
	myADC.begin();
}

//!*************************************************************************************
//!	Name:	OFF()										
//!	Description: Switch OFF the board
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
void WaspSensorSWIons::OFF(void)
{
	// Turn on the power switches in Waspmote
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	delay(100);
	pinMode(DIGITAL2, INPUT);
	pinMode(DIGITAL5, INPUT);
	pinMode(DIGITAL4, INPUT);
	pinMode(DIGITAL3, INPUT);
	pinMode(DIGITAL1, INPUT); 
	
	// Disable SPI flag
	SPI.isSmartWaterIons = false;
	SPI.end();
}


//!*************************************************************************************
//! Smart Water Ions Object
//!*************************************************************************************
WaspSensorSWIons SWIonsBoard= WaspSensorSWIons();

//**************************************************************************************************
//  Ion Sensor Class 
//**************************************************************************************************
//!*************************************************************************************
//!	Name:	ionSensorClass()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
ionSensorClass::ionSensorClass() {}

//!*************************************************************************************
//!	Name:	ionSensorClass()										
//!	Description: Class contructor		
//!	Param : uint8_t socket: socket where the sensor is connected	
//!	Returns: void							
//!*************************************************************************************
ionSensorClass::ionSensorClass(uint8_t socket)
{
	_mySocket = socket;
}


//!*************************************************************************************
//!	Name:	ionSensorClass()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: float: the voltage value read from the ADC						
//!*************************************************************************************
float ionSensorClass::read(void)
{
	// These pins are used to configure the analog multiplexor
	digitalWrite(DIGITAL2, HIGH);
	digitalWrite(DIGITAL3, LOW); 

	// Select the channel to be read from the multiplexer
	if (_mySocket == SOCKET_A) {
		
		digitalWrite(DIGITAL5, LOW);
		digitalWrite(DIGITAL4, LOW);
		
	} else if (_mySocket == SOCKET_B){
		
		digitalWrite(DIGITAL5, HIGH);
		digitalWrite(DIGITAL4, LOW);
		
	} else if (_mySocket == SOCKET_C) {
		
		digitalWrite(DIGITAL5, LOW);
		digitalWrite(DIGITAL4, HIGH);
	
	} else if (_mySocket == SOCKET_D) {
		
		digitalWrite(DIGITAL5, HIGH);
		digitalWrite(DIGITAL4, HIGH);
		
	} else {
		return -1.0;
	}
	
	// Ence the multiplexer is configured, configure and red the ADC
	// Ion Sensors are connected in AIN1, and temperature in AIN2
	myADC.configure(AIN1);
	delay(2500);
	
	return myADC.readADC(AIN1);
	
}

//!*************************************************************************************
//!	Name:	setCalibrationPoints()										
//!	Description: Calculate the slope and the intersection of the logarithmic function
//!	Param : calVoltages[]: an array with the voltages obtained in the calibration
//!			calConcentrations[]: an array with the calibration concentrations used
//!	Returns: void							
//!*************************************************************************************
void ionSensorClass::setCalibrationPoints(const float calVoltages[],const float calConcentrations[],  uint8_t numPoints)
{
	// Summation of the voltages (y values)
	float SUMy = 0.0;

	for (int i = 0; i < numPoints; i++) 
		SUMy = SUMy + calVoltages[i];
	
	// y values average
	float SUMy_avg = SUMy / numPoints; 
	
	// Summation of the logarithm of the x values
	float SUMLogx = 0.0;

	for (int i = 0; i < numPoints; i++) 
		SUMLogx	= SUMLogx + log10(calConcentrations[i]);

	// Sum of the square of the logarithm of the x values
	float SUMLogx_2 = 0.0;

	for (int i = 0; i < numPoints; i++) 
		SUMLogx_2 = SUMLogx_2 + log10(calConcentrations[i])*log10(calConcentrations[i]);

	// Sumation of the logx * y
	float SUMLogx_y = 0.0;

	for (int i = 0; i < numPoints; i++)
		SUMLogx_y = SUMLogx_y + log10(calConcentrations[i])* calVoltages[i];

	// Average of the log x values
	float SUMLogx_avg = SUMLogx / numPoints;

	// Slope of the logarithmic function 
	slope = (SUMLogx_y - SUMy_avg * SUMLogx) / (SUMLogx_2 - SUMLogx_avg * SUMLogx);
	// Intersection of the logarithmic function
	intersection = SUMy_avg - (slope * SUMLogx_avg);
}



//!*************************************************************************************
//!	Name:	setCalibrationPoints()										
//!	Description: Calculate the slope and the intersection of the logarithmic function
//!	Param :		void
//!	Returns:	void
//!*************************************************************************************
void ionSensorClass::setCalibrationPoints()
{
	setCalibrationPoints(voltages, concentrations, numPoints);
}


//!*************************************************************************************
//!	Name:	pointToPointCalibration()
//!	Description: Calibration using point to point method
//!	Param : calVoltages[]: Calibration Voltages measured
//!			calConcentrations[]: The correspondig concentrations
//!	Returns: int: 0, If all success
//!				 -1, If error
//!*************************************************************************************
int ionSensorClass::pointToPointCalibration(float calVoltages[], 
											float calConcentrations[],
											uint8_t numPoints_)
{
	if (numPoints_ <= MAX_POINTS)
		numPoints = numPoints_;
	else 
		return -1;
	
	// Store the calibration values
	for (int i = 0; i < numPoints; i++)
	{
		voltages[i] = calVoltages[i]; 
		concentrations[i] = calConcentrations[i];
	}
	
	return 0;
}

//!*************************************************************************************
//!	Name:	calculateConcentration()										
//!	Description: calculates the concentration in ppm's from the voltage value measured		
//!	Param : input: the voltage measured														
//!	Returns: float: the value of the concentration in ppm's						
//!*************************************************************************************
float ionSensorClass::calculateConcentration(float input)
{
	// The ions sensors have a logarithmic response (Nernst Equation)
	// The calibration process in a non-linear regression
	// y = a * log10(x) + b => x = 10 ^ ((y - b) / a)
	
	float concentration = pow(10, ((input - intersection) / slope));
	
	if (concentration > 999999.9) 
	{
		return -1; 
	}
	else 
	{
		return concentration;
	}
}

//!*************************************************************************************
//!	Name:	calculateConcentrationP2P()									
//!	Description: calculates the concentration in ppm's from the voltage value measured.
//!				 This function uses point to point method for calibrating.
//!	Param : input: the voltage measured									
//!	Returns: float: the value of the concentration in ppm's				
//!*************************************************************************************
float ionSensorClass::calculateConcentrationP2P(float input)
{
	bool inRange = false; 
	int i = 0;
	
	// This loop is to find the range where the input is located
	while ((!inRange) && (i < (numPoints-1))) 
	{
		if ((input > voltages[i]) && (input <= voltages[i + 1]))
			inRange = true;
		else if ((input <= voltages[i]) && (input > voltages[i+1]))
			inRange = true;
		else
			i++;
	}
	
	float temp_slope = 0.0;
	float temp_intersection = 0.0;
	
	// If the voltage input is in a range, we calculate in the slope 
	// and the intersection of the logaritmic function
	if (inRange ) 
	{
		// Slope of the logarithmic function 
		temp_slope = (voltages[i] - voltages[i+1]) / (log10(concentrations[i]) - log10(concentrations[i+1]));
		// Intersection of the logarithmic function
		temp_intersection = voltages[i] - temp_slope * log10(concentrations[i]);		
	
	// Else, we calculate the logarithmic function with the nearest point
	} 
	else
	{
		if (fabs(input - voltages[0]) < fabs(input - voltages[numPoints-1])) 
		{
			// Slope of the logarithmic function
			temp_slope = (voltages[1] - voltages[0]) / (log10(concentrations[1]) - log10(concentrations[0]));
			// Intersection of the logarithmic function
			temp_intersection = voltages[0] - temp_slope * log10(concentrations[0]);
			
		} 
		else
		{
			// Slope of the logarithmic function
			temp_slope = (voltages[numPoints-1] - voltages[numPoints-2]) / (log10(concentrations[numPoints-1]) - log10(concentrations[numPoints-2]));
			// Intersection of the logarithmic function
			temp_intersection = voltages[numPoints-1] - temp_slope * log10(concentrations[numPoints-1]);
		}
	}
	
	float concentration = pow(10, ((input - temp_intersection) / temp_slope));
	
	// Return the value of the concetration
	if (concentration > 999999.9) 
	{
		return -1; 
	}
	else 
	{
		return concentration;
	} 
}

//!*************************************************************************************
//!	Name:	pHConversion()
//!	Description: Returns the pH value
//!	Param: 	float input: voltage measured at the sensor output
//!				float temp: temperature of the test solution
//!	Returns: 	float value : the pH of the solution
//! 			-1 : wrong temperature introduced
//!				-2 : wrong calibration temperature introduced						
//!*************************************************************************************
float ionSensorClass::pHConversion(float input, float temp)
{
	float sensitivity;
	
	// The temperature of the water must be between 0 and 100 ºC
	if( (temp < 0.0)||(temp > 100.0))
		return -1.0;
	
	// The calibration temperature must be between 0 and 100 ºC
	if((calibration_temperature < 0)||(calibration_temperature > 100))
		return -2.0;


	// Two ranges calibration
	if (input > calibration_point_7 )
	{
		// The sensitivity is calculated using the other two calibration values
		// Asumme that the pH sensor is lineal in the range.
		// sensitivity = pHVariation / volts
		// Divide by 3 = (pH) 7 -  (pH) 4
		sensitivity = (calibration_point_4-calibration_point_7)/3;
		// Add the change in the pH owed to the change in temperature
		sensitivity = sensitivity + (temp - calibration_temperature)*0.0001984;

		// The value at pH 7.0 is taken as reference		
		// => Units balance => 7 (pH) + (volts) / ((pH) / (volts)) 
		return 7.0 + (calibration_point_7-input) / sensitivity;
		//				|					|
		//			(pH 7 voltage	-	Measured volts) = Variation from the reference 
	}
	else
	{
		// The sensitivity is calculated using the other two calibration values
		sensitivity = (calibration_point_7-calibration_point_10) / 3;
		// Add the change in the pH owed to the change in temperature
		sensitivity = sensitivity + (temp - calibration_temperature)*0.0001984;

		return 7.0 + (calibration_point_7-input)/sensitivity;
	}
}


//!*************************************************************************************
//!	Name:	pHConversion()
//!	Description: Returns the pH value
//!	Param: 	float input: voltage measured at the sensor output
//!				float temp: temperature of the test solution
//!	Returns: 	float value : the pH of the solution
//! 			-1 : wrong temperature introduced
//!				-2 : wrong calibration temperature introduced						
//!*************************************************************************************
float ionSensorClass::pHConversion(float input)
{
	return pHConversion(input, 25.0);
}

//!*************************************************************************************
//!	Name:	setCalibrationPoints()										
//!	Description: Configures the calibration points of the pH sensor
//!	Param: 	float _calibration_point_10: voltage measured with the 10.0pH solution
//!			float _calibration_point_7: voltage measured with the 7.0pH  solution
//!			float _calibration_point_4: voltage measured with the 4.0pH  solution
//!			float _calibration_temperature: temperature of the solutions
//!	Returns: 	void							
//!*************************************************************************************
void ionSensorClass::setpHCalibrationPoints(	float	_calibration_point_10,
									float	_calibration_point_7,
									float	_calibration_point_4,
									float	_calibration_temperature)
{
	calibration_point_10 = _calibration_point_10;
	calibration_point_7 = _calibration_point_7;
	calibration_point_4 = _calibration_point_4;
	calibration_temperature = _calibration_temperature;
}



//**************************************************************************************************
// Temperature sensor class 
//**************************************************************************************************

//!*************************************************************************************
//!	Name:	pt1000Class()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
pt1000Class::pt1000Class(){}

//!*************************************************************************************
//!	Name:	read()										
//!	Description: read the temperature sensor		
//!	Param : void														
//!	Returns: float: the temperature value read in celsius degrees							
//!*************************************************************************************
float pt1000Class::read(void)
{
	// Temperature sensor is connected in AIN2 of the ADC
	myADC.configure(AIN2);
	delay(2000);

	float value = myADC.readADC(AIN2);  

	value = (value + 2.048) / (2.048 - value) * 1000.0;

	// This formula can be extracted (aproximately) by linearizing with two points
	// (x1 , y1) = (0ºC,  1000 Ohm)
	// (x2 , y2) = (79ºC, 1300 Ohm)
	float temp = 0.26048 * value - 260.83;
	delay(100);

	if ((temp > 100.0) || (temp < 0.0))
	{
		return -1.0;
	}
	else 
	{
		return temp;
	}

}


//**************************************************************************************************
// SOCKET1 Class 
//**************************************************************************************************
//!*************************************************************************************
//!	Name:	socket1Class()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
socket1Class::socket1Class(){}

//!*************************************************************************************
//!	Name:	socket1Class()										
//!	Description: read from the SOCKET1		
//!	Param : void														
//!	Returns: float: voltage read from the socket1							
//!*************************************************************************************
float socket1Class::read()
{
	// Multiplexer configuration for the SOCKET1
	// DIGITAL2 CHIP SELECT PIN
	digitalWrite(DIGITAL2, HIGH);
	
	// S0,S1,S1 PINS of the Multiplexer 
	digitalWrite(DIGITAL5, LOW);
	digitalWrite(DIGITAL4, LOW);
	digitalWrite(DIGITAL3, LOW); 
	delay(100);
	
	//Configure and read from the ADC 
	myADC.configure(AIN1);
	delay(2500);
	
	return myADC.readADC(AIN1);
}


//**************************************************************************************************
// SOCKET2 Class 
//**************************************************************************************************
//!*************************************************************************************
//!	Name:	socket2Class()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
socket2Class::socket2Class(){}

//!*************************************************************************************
//!	Name:	socket2Class()										
//!	Description: read from the SOCKET2		
//!	Param : void														
//!	Returns: float: voltage read from the socket2							
//!*************************************************************************************
float socket2Class::read()
{
	// Multiplexer configuration for the SOCKET2
	// DIGITAL2 CHIP SELECT PIN
	digitalWrite(DIGITAL2, HIGH);
	
	// S0,S1,S1 PINS of the Multiplexer 
	digitalWrite(DIGITAL5, HIGH);
	digitalWrite(DIGITAL4, LOW);
	digitalWrite(DIGITAL3, LOW);
	delay(100);
	
	//Configure and read from the ADC
	myADC.configure(AIN1);
	delay(2500);

	return myADC.readADC(AIN1);
}



//**************************************************************************************************
// SOCKET3 Class 
//**************************************************************************************************
//!*************************************************************************************
//!	Name:	socket3Class()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
socket3Class::socket3Class(){}

//!*************************************************************************************
//!	Name:	socket3Class()										
//!	Description: read from the SOCKET3		
//!	Param : void														
//!	Returns: float: voltage read from the socket3							
//!*************************************************************************************
float socket3Class::read()
{
	// Multiplexer configuration for the SOCKET1
	// DIGITAL2 CHIP SELECT PIN
	digitalWrite(DIGITAL2, HIGH);
	
	// S0,S1,S1 PINS of the Multiplexer 
	digitalWrite(DIGITAL5, LOW);
	digitalWrite(DIGITAL4, HIGH);
	digitalWrite(DIGITAL3, LOW);	
	delay(100);
	
	//Configure and read from the ADC
	myADC. configure(AIN1);
	delay(2500);
	return myADC.readADC(AIN1);
}



//**************************************************************************************************
// SOCKET4 Class 
//**************************************************************************************************
//!*************************************************************************************
//!	Name:	socket4Class()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
socket4Class::socket4Class(){}

//!*************************************************************************************
//!	Name:	socket4Class()										
//!	Description: read from the SOCKET4		
//!	Param : void														
//!	Returns: float: voltage read from the socket4							
//!*************************************************************************************
float socket4Class::read()
{
	// Multiplexer configuration for the SOCKET1
	// DIGITAL2 CHIP SELECT PIN
	digitalWrite(DIGITAL2, HIGH);
	
	// S0,S1,S1 PINS of the Multiplexer
	digitalWrite(DIGITAL5, HIGH);
	digitalWrite(DIGITAL4, HIGH);
	digitalWrite(DIGITAL3, LOW);
	delay(100);
	
	//Configure and read from the ADC
	myADC.configure(AIN1);
	delay(2500);
	return myADC.readADC(AIN1);
}





