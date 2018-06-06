/*!	\file WaspSensorGas_v30.cpp
 *  \brief Library for managing the Gas Sensor Board v30
 *
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
 *  Version:			3.2
 *  Design:				David Gascón
 *  Implementation:		Ahmad Saad
 */
 

#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "WaspSensorGas_v30.h"


//************************************************************************************
// GASES SENSOR BOARD CLASS
//************************************************************************************
//======================================================================
// PUBLIC METHODS
//====================================================================== 
 /*!
 * @brief	Class contructor
 * @param 	void
 * @return	void
 */
GasSensorClass::GasSensorClass() 
{
	WaspRegisterSensor |= REG_GASES;
}


/*!
 * @brief	Switch ON the power supply and configure the I/O pins
 * @param 	void
 * @return	void
 */
void GasSensorClass::ON() 
{
	// Configure the MULTIPLEXOR control pins 
	pinMode(A2, OUTPUT);	// <--- ANALOG6  <--- A2
	pinMode(A1, OUTPUT);	// <--- ANALOG4  <--- A1
	pinMode(A0, OUTPUT);	// <--- ANALOG2  <--- A0
	pinMode(EN, OUTPUT);	// <--- DIGITAL1 <--- EN
	
	// I2C ISOLTAOR PIN ENABLE
	pinMode(I2C_PIN_OE, OUTPUT); 
	delay(10);
	
	// Switches configuration
	pinMode(SOCKET2_ON_PIN, OUTPUT);
	pinMode(SOCKET3_ON_PIN, OUTPUT);
	pinMode(SOCKET4_ON_PIN, OUTPUT);
	pinMode(SOCKET5_ON_PIN, OUTPUT);
	pinMode(SOCKET6_ON_PIN, OUTPUT);
	pinMode(SOCKET7_ON_PIN, OUTPUT);   
	// Switch OFF all sockets
	digitalWrite(SOCKET2_ON_PIN, LOW);
	digitalWrite(SOCKET3_ON_PIN, LOW);
	digitalWrite(SOCKET4_ON_PIN, LOW);
	digitalWrite(SOCKET5_ON_PIN, LOW);
	digitalWrite(SOCKET6_ON_PIN, LOW);
	digitalWrite(SOCKET7_ON_PIN, LOW); 
	// Configure the internal reference
	analogReference(INTERNAL2V56);	
	// Switch ON 3V3 and 5V for supplying the board
	PWR.setSensorPower( SENS_5V, SENS_ON);
	PWR.setSensorPower(SENS_3V3, SENS_ON);
	digitalWrite(I2C_PIN_OE, HIGH);	
	// Gases Sensor Borad state ON
	state = ON_STATE;
	
	#if DEBUG_GASES > 1
		PRINTLN_GASES(F("Gases Board v30 switched ON"));
	#endif
	
	// Configure the BME280 Sensor (Temperature, Humidity and Pressure)
	BME.ON();
	delay(100);
	
	if (_boot_version < 'H')
	{
		USB.println(F("\n***************  WARNING *******************"));
		USB.println(F("This example is valid only for Waspmote v15."));
		USB.println(F("Your Waspmote version is v12."));
		USB.println(F("*******************************************"));
	}
}


/*!
 * @brief	Switch OFF the power supply of the sensor board (5v and 3v3)
 * @param 	void
 * @return	void
 */
void GasSensorClass::OFF(void)
{
	// Switch OFF all SOCKETS
	digitalWrite(SOCKET2_ON_PIN, LOW);
	digitalWrite(SOCKET3_ON_PIN, LOW);
	digitalWrite(SOCKET4_ON_PIN, LOW);
	digitalWrite(SOCKET5_ON_PIN, LOW);
	digitalWrite(SOCKET6_ON_PIN, LOW);
	digitalWrite(SOCKET7_ON_PIN, LOW);
	// Isolate I2C bus communication
	digitalWrite(I2C_PIN_OE, LOW);
	// Switch OFF 3V3 and 5V 
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	// Gases Sensor Borad state OFF
	state = OFF_STATE;
	
	#if DEBUG_GASES > 1
		PRINTLN_GASES(F("Gases Board v30 switched OFF"));
	#endif
	
	delay(100);
}


/*!
 * @brief	Gets the temperature from the BME280 sensor
 * @param 	void
 * @return	The temperature value read
 */
float GasSensorClass::getTemperature(void) 
{
	// Read the temperature from the BME280 Sensor
	return BME.getTemperature(BME280_OVERSAMP_1X, 0);
}


/*!
 * @brief	Gets the Humidity from the BME280 sensor
 * @param 	void
 * @return	The humidity value read
 */
float GasSensorClass::getHumidity(void)
{
	// Read the humidity from the BME280 Sensor
	return BME.getHumidity(BME280_OVERSAMP_1X);
}


/*!
 * @brief	Gets the Pressure from the BME280 sensor
 * @param 	void
 * @return	The pressure value read
 */
float GasSensorClass::getPressure()
{
	// Read the pressure from the BME280 Sensor
	return BME.getPressure(BME280_OVERSAMP_1X, 0);
}


/*!
 * @brief	Gets the Luxes value from the TSL sensor
 * @param 	uint8_t gain: INDOOR or OUTDOOR
 * @return	The luxes value read
 */
float GasSensorClass::getLuxes(uint8_t gain)
{
	TSL.ON();
	
	switch (gain)
	{
		case OUTDOOR:
			TSL.getLuminosity(TSL2561_HIGH_RES, TSL2561_GAIN_1);
		break;
		
		case INDOOR:
			TSL.getLuminosity(TSL2561_HIGH_RES, TSL2561_GAIN_16);
		break;
	}

	return TSL.lux;
}


/*!
 * @brief	Gets the distance from the UltraSound sensor
 * @param 	void
 * @return	The distance value read in cm
 */
float GasSensorClass::getDistance()
{
	return Ultrasound.getDistance();
}
//======================================================================
// PRIVATE METHODS
//======================================================================
/*!
 * @brief	Calculates the resistor value in function of the gain
 * @param 	uint8_t address: I2C address of the digipot
 * @param 	float value: gain value selected
 * @return	void
 */
void GasSensorClass::setAmplifier(uint8_t address, float value)
{
	float auxiliar = 0;
	uint8_t ampli=0;
	
	auxiliar = 129*(value-1);
	auxiliar = auxiliar/100;
	ampli = uint8_t (129-auxiliar);

	I2C.begin();
	
	delay(50);
	
	#if DEBUG_GASES > 1
		PRINT_GASES(F("Resitor configured for amplifier stage (KOHMs): "));
		PRINTLN_GASES_VAL((128.0 - ampli) * 0.781 + 1.078)
	#endif

	I2C.write( address, B00010000, ampli);
}

/*!
 * @brief	Configures the resistor of the digital potentiometer
 * @param 	uint8_t address: I2C address of the digipot
 * @param 	float value : resistor value selected 
 * @return	void
 */
void GasSensorClass::setResistor(uint8_t address, float value, int pot)
{
	// Calculates the value to configure
	float auxiliar = 0;
	uint8_t resist=0;
	
	auxiliar = 128*value;
	auxiliar = auxiliar / 100.0;
	resist = (uint8_t) 128-auxiliar;
	
	#if DEBUG_GASES > 1
		PRINT_GASES(F("Load Resistor configured (KOHMs): "));
		PRINTLN_GASES_VAL((128.0 - resist) * 0.781 + 0.078);
	#endif
	
	// Inits the I2C Bus
	I2C.begin();
	
	delay(50);
	
	// Send the corresponding packets to configure the digipot
	I2C.write( address, pot, resist);
}


/*!
 * @brief	Save the calibration points
 * 
 * @param 	float[]: calValues: Y values of the function
 * @param 	float[]: calConcentrations: X values of the function
 * @param	uint8_t: numPoints: the number of points to be used in calibration
 * 
 * @return	
 * 	@arg	'-1' if error 
 * 	@arg	'0' if all OK
 */
int GasSensorClass::saveCalibrationPoints(float calValues[], float calConcentrations[], uint8_t numPoints_) 
{
	if (numPoints_ <= MAX_POINTS)
		numPoints = numPoints_;
	else 
		return -1;
	
	// Store the calibration values
	for (int i = 0; i < numPoints; i++)
	{
		values[i] = calValues[i]; 
		concentrations[i] = calConcentrations[i];
	}
	
	#if DEBUG_GASES > 1
		PRINT_GASES(F("[POINT_1] Concentration: "));
		PRINTLN_GASES_VAL(concentrations[POINT_1]);
		PRINT_GASES(F("[POINT_2] Concentration: "));
		PRINTLN_GASES_VAL(concentrations[POINT_2]);
		PRINT_GASES(F("[POINT_3] Concentration: "));
		PRINTLN_GASES_VAL(concentrations[POINT_3]);
		PRINT_GASES(F("[POINT_1] Values: "));
		PRINTLN_GASES_VAL(calValues[POINT_1]);
		PRINT_GASES(F("[POINT_2] Values: "));
		PRINTLN_GASES_VAL(calValues[POINT_2]);
		PRINT_GASES(F("[POINT_3] Values: "));
		PRINTLN_GASES_VAL(calValues[POINT_3]);
	#endif
	
	return 0;
}


/*!
 * @brief	Prepare the calibration points 
 * @param 	float[]: calValues: Y values of the function
 * @param	float[]: calConcentrations: X values of the function
 * @param	uint8_t: numPoints: the number of points to be used in calibration
 * @return
 * 	@arg	'-1' if error 
 * 	@arg	'0' if all OK
 */
int GasSensorClass::setCalibrationPoints(float calValues[], float calConcentrations[], uint8_t numPoints_)
{ 
	
	if (numPoints_ > MAX_POINTS) 
	{
		#if DEBUG_GASES > 0
			PRINTLN_GASES("ERROR: MAX_POINTS allowed = 10 ");
		#endif
		
		return -1;
	}
	
	Ro = calValues[0];
	// Store the calibration values
	for (int i = 0; i < numPoints_; i++)
	{
		calValues[i] = calValues[i] / Ro;
	}
	
	#if DEBUG_GASES > 1
		PRINTLN_GASES(F("Saving calibration values"));
		PRINT_GASES(F("Ro value: "));
		PRINTLN_GASES_VAL(Ro);
		PRINT_GASES(F("Number of points: "));
		PRINTLN_GASES_VAL(numPoints_);
	#endif
	
	return saveCalibrationPoints(calValues, calConcentrations, numPoints_);
}


/*!
 * @brief	Prepare the calibration points
 * @param	void
 * @return	void
 * 	@arg	'-1' if error 
 * 	@arg	'0' if all OK
 */
int GasSensorClass::setCalibrationPoints()
{
	return setCalibrationPoints(values, concentrations, numPoints);
}


/*!
 * @brief	Description: Point to point calculation function 
 * @param 	float: input: input value for getting concentration 
 * @return	the concentration value
 */
float GasSensorClass::getConcentration(float input)
{
	bool inRange = false; 
	int i = 0;
	
	// This loop is to find the range where the input is located
	while ((!inRange) && (i < (numPoints-1))) {
		
		if ((input > values[i]) && (input <= values[i + 1]))
			inRange = true;
		else if ((input <= values[i]) && (input > values[i+1]))
			inRange = true;
		else
			i++;
	}
	
	float temp_slope = 0.0;
	float temp_intersection = 0.0;
	float concentration = 0.0;
	
	// If the voltage input is in a range, we calculate in the slope 
	// and the intersection of the logaritmic function
	if (inRange) 
	{
		// Slope of the logarithmic function 
		temp_slope = (values[i] - values[i+1]) / (log10(concentrations[i]) - log10(concentrations[i+1]));
		// Intersection of the logarithmic function
		temp_intersection = values[i] - temp_slope * log10(concentrations[i]);	
	}
	// Else, we calculate the logarithmic function with the nearest point
	else
	{
		if (fabs(input - values[0]) < fabs(input - values[numPoints-1])) {
			// Slope of the logarithmic function
			temp_slope = (values[1] - values[0]) / (log10(concentrations[1]) - log10(concentrations[0]));
			// Intersection of the logarithmic function
			temp_intersection = values[0] - temp_slope * log10(concentrations[0]);
		} else {
			// Slope of the logarithmic function
			temp_slope = (values[numPoints-1] - values[numPoints-2]) / (log10(concentrations[numPoints-1]) - log10(concentrations[numPoints-2]));
			// Intersection of the logarithmic function
			temp_intersection = values[numPoints-1] - temp_slope * log10(concentrations[numPoints-1]);
		}
	}
	
	// Return the value of the concetration
	concentration = pow(10, ((input - temp_intersection) / temp_slope));
	
	if (concentration < 99999.9)
	{
		return concentration;
	}
	else 
	{
		#if DEBUG_GASES > 1
			PRINTLN_GASES("Concentration out of range");
		#endif
		
		return -1.0;
	}
}

//************************************************************************************
// O2 SENSOR CLASS
//************************************************************************************
//======================================================================
// PUBLIC METHODS
//======================================================================
/*!
 * @brief	Class contructor
 * @param 	void
 * @return	void
 */
O2SensorClass::O2SensorClass()
{
	gain = 10;
	socket = SOCKET_1;
}


/*!
 * @brief	Class contructor
 * @param 	uint8_t: socket where the sensor is connected
 * @return	void
 */
O2SensorClass::O2SensorClass(uint8_t _socket)
{
	// Store the gain value of the stage
	socket = _socket;
	gain = 50;
}


/*!
 * @brief	Class contructor
 * @param 	uint8_t: socket where the sensor is connected
 * @param 	float: gain of the stage for O2 Sensor
 * @return	void
 */
O2SensorClass::O2SensorClass(uint8_t _socket, float _gain) 
{
	// Store the gain value of the stage
	gain = _gain;
	socket = _socket;
}


/*!
 * @brief	Switch ON the O2 Sensor and configure the multiplexor
 * @param 	void
 * @return	void
 */
void O2SensorClass::ON(void)
{
	#if DEBUG_GASES > 1
		if (socket == SOCKET_E) 
		{	
			PRINTLN_GASES("O2 Sensor configured in the SOCKET_E");
			
		} else if (socket == SOCKET_1)
		{
			PRINTLN_GASES("O2 Sensor configured in the SOCKET_1");
		}
		else 
		{
			PRINTLN_GASES("O2 Sensor wrong configured");
			PRINTLN_GASES("Use SOCKET_1 in OEM platform or SOCKET_E in Plug&Sense! platform");
		}
	#endif
	
	state = ON_STATE;
	
	// Configure the Analog Multiplexor to read from SOCKET1
	setMUX();
	delay(10);
	setAmplifier(GAIN_DIGIPOT_ADDRESS, gain);
}


/*!
 * @brief	Switch OFF the O2 Sensor
 * @param 	void
 * @return	void
 */
void O2SensorClass::OFF(void)
{
	state = OFF_STATE;
}


/*!
 * @brief	Read the ADC of the waspmote and return a voltage
 * @param 	void
 * @return	the voltage read from the Sensor in mV
 */
float O2SensorClass::readVoltage(void)
{
	float analogValue = 0.0;
	
	// Get 100 samples
	for (int i = 0; i < 100; i++) {	
		analogValue = analogValue + analogRead(ANALOG3);
		delay(1);
	}
	
	// Return the correspondig value
	return analogValue = (analogValue / 100.0) * ANALOG_REFERENCE * 1000 / (1024.0 * gain);	
}


/*!
 * @brief	Read the ADC of the waspmote and return concetration
 * @param 	void
 * @return	The concentration value in ppm
 */
float O2SensorClass::readConcentration()
{
	float O2mV = readVoltage();
	float O2Val = (O2mV - values[0]) / slope - concentrations[0];
	
	if ((O2Val > 0.0) && (O2Val < 100.0))
	{
		// Value obtained from the datasheet without a calibration process
		return O2Val;
	}
	else 
	{
		#if DEBUG_GASES > 1
			PRINT_GASES("O2 concentration out of range");
		#endif
		
		// Out of range
		return -1.0;
	}
}


/*!
 * @brief	Prepare the calibration points and store them
 * @param	float[]: calValues: Y values of the function
 * @param	float[]: calConcentrations: X values of the function
 * @return	void
 */
void O2SensorClass::setCalibrationPoints(	float calValues[], 
											float calConcentrations[])
{
	values[0] = calValues[0];
	values[1] = calValues[1];

	concentrations[0] = calConcentrations[0];
	concentrations[1] = calConcentrations[1];
	
	slope = (values[1] - values[0]) / (concentrations[1] - concentrations[0]);
}


//======================================================================
// PRIVATE METHODS
//======================================================================
/*!
 * @brief	Configures the multiplexer to read from the SOCKET_1 or SOCKET_2
 * @param 	void
 * @return	void
 */
void O2SensorClass::setMUX(void)
{
	if (socket == SOCKET_1) {
		// Configurin the ANALOG MULTIPLEXER
		digitalWrite(A2, 0);
		digitalWrite(A1, 0);
		digitalWrite(A0, 0);
		digitalWrite(EN, 1);
	} else {
		// Configure the Analog Multiplexor to read from SOCKET_2
		digitalWrite(A2, 0);
		digitalWrite(A1, 0);
		digitalWrite(A0, 1);
		digitalWrite(EN, 1);
	}
}


//************************************************************************************
// CO2 SENSOR CLASS
//************************************************************************************
//======================================================================
// PUBLIC METHODS
//======================================================================
/*!
 * @brief	Class contructor
 * @param	uint8_t: socket where the sensor is connected
 * @return	void
 */
CO2SensorClass::CO2SensorClass()
{
	// Default gain of the stage
	socket = SOCKET_2;
	gain = 1.08;
}


/*!
 * @brief	Class contructor
 * @param	uint8_t: socket where the sensor is connected
 * @return	void
 */
CO2SensorClass::CO2SensorClass(uint8_t _socket)
{
	// Default gain of the stage
	socket = _socket;
	gain = 1.08;
}


/*!
 * @brief	Class contructor
 * @param	uint8_t: _gain: gain of the stage
 * @param	uint8_t: _socket: socket where the sensor is connected
 * @return	void
 */
CO2SensorClass::CO2SensorClass(uint8_t _socket, uint8_t _gain)
{
	// Store the gain value of the stage
	if (_gain > 5)
	{
		_gain = 5;
	}

	socket = _socket;
	gain = _gain;
}


/*!
 * @brief	Switch ON the CO2 sensor and configures the multiplexer
 * @param 	void
 * @return	void
 */
void CO2SensorClass::ON()
{
	state = ON_STATE;
	digitalWrite(SOCKET2_ON_PIN, HIGH);
	
	#if DEBUG_GASES > 1
		if (socket == SOCKET_E) 
		{	
			PRINTLN_GASES("CO2 Sensor configured in the SOCKET_E");
			
		} else if (socket == SOCKET_2)
		{
			PRINTLN_GASES("CO2 Sensor configured in the SOCKET_2");
		}
		else 
		{
			PRINTLN_GASES("CO2 Sensor wrong configured");
			PRINTLN_GASES("Use SOCKET_2 in OEM platform or SOCKET_E in Plug&Sense! platform");
		}
	#endif
	
	// Configure the Analog Multiplexor to read from SOCKET_2
	setMUX();
	delay(10);
	setAmplifier(GAIN_DIGIPOT_ADDRESS, gain);
}


/*!
 * @brief	Switch OFF the CO2 sensor in SOCKET_2
 * @param 	void
 * @return	void
 */
void CO2SensorClass::OFF()
{
	state = OFF_STATE;
	digitalWrite(SOCKET2_ON_PIN , LOW);
}


/*!
 * @brief	Read the ADC of the waspmote and return a voltage (in V)
 * @param 	void
 * @return	The voltage read from the SOCKET_2
 */
float CO2SensorClass::readVoltage()
{
	float analogValue = 0.0;
	
	for (int i = 0; i < 100; i++) {
		analogValue = analogValue + analogRead(ANALOG3);
		delay(1);
	}
	
	// Return the correspondig value
	return ((analogValue/100.0) * ANALOG_REFERENCE / (1024.0 * gain));
}


/*!
 * @brief	Gets the concentration in PPMs from CO2 sensor
 * @param 	void
 * @return	The value of the concetration read
 */
float CO2SensorClass::readConcentration()
{
	return getConcentration(readVoltage());
}


/*!
 * @brief	Store the calibration points for CO2 sensor
 * 
 * @param	float calValues[]: Y values of the function
 * @param	float calConcentrations[]: X values of the function
 * @param	uint8_t numPoints_: the number of points to be used in calibration
 * 
 * @return	
 * 	@arg	'-1' if error 
 * 	@arg	'0' if all OK
 */
int CO2SensorClass::setCalibrationPoints(	float calValues[], 
											float calConcentrations[], 	
											uint8_t numPoints_)
{
	return saveCalibrationPoints(calValues, calConcentrations, numPoints_);
}


/*!
 * @brief	Store the calibration points for CO2 sensor
 * 
 * @param	void
 * 
 * @return	
 * 	@arg	'-1' if error 
 * 	@arg	'0' if all OK
 */
int CO2SensorClass::setCalibrationPoints()
{
	return saveCalibrationPoints(values, concentrations, numPoints);
}


//======================================================================
// PRIVATE METHODS
//======================================================================
/*!
 * @brief	Configure the Analog Multiplexor to read from SOCKET_2
 * @param 	void
 * @return	void
 */
void CO2SensorClass::setMUX()
{
	// Configure the Analog Multiplexor to read from SOCKET2
	digitalWrite(A2, 0);
	digitalWrite(A1, 0);
	digitalWrite(A0, 1);
	digitalWrite(EN, 1);
}


//************************************************************************************
// SOCKET3 SENSOR CLASS - 1v8 Sensors can be connected in this socket
//************************************************************************************
/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
socket3Class::socket3Class()
{
	gain = 1.08;
	loadResistor = 12.50;
}


/*!
 * @brief	Consturctor of the class
 * 
 * @param 	float _gain: gain of the stage to be configured	
 * @param 	float _loadResistor: Load resistor to be configured
 * 
 * @return	void
 */
socket3Class::socket3Class(float _gain, float _loadResistor)
{
	gain = _gain;
	loadResistor = _loadResistor;
}


/*!
 * @brief	Read the ADC of the waspmote and return a voltage (in V)
 * @param 	void
 * @return	The voltage read from the sensor
 */
float socket3Class::readVoltage()
{
	
	float analogValue = 0.0;
	
	for (int i = 0; i < 100; i++) {
		analogValue += analogRead(ANALOG3);
		delay(1);
	}
	
	// Return the correspondig value
	return ((analogValue / 100.0) * ANALOG_REFERENCE ) / (1024.0 * gain);
}


/*!
 * @brief	Get the resistance from the voltage value read
 * @param 	float: input: voltage value read
 * @return	The resistance value
 */
float socket3Class::readResistance(float input)
{
	return (SOCKET3_SUPPLY * (loadResistor * 1000.0)) / (input)  - (loadResistor * 1000.0);
}


/*!
 * @brief	Get the resistance from the voltage value read
 * @param 	float: input: voltage value read
 * @return	The resistance value
 */
float socket3Class::readResistance()
{
	return (SOCKET3_SUPPLY * (loadResistor * 1000.0)) / (readVoltage())  - (loadResistor * 1000.0);
}


/*!
 * @brief	Get the concentration from teh resistance value read
 * @param 	float: input: the resistance value
 * @return	concentration value claculated
 */
float socket3Class::readConcentration(float input)
{
	return getConcentration((input / Ro ) / 1000.0);
}


/*!
 * @brief	Get the concentration from teh resistance value read
 * @param 	float: input: the resistance value
 * @return	concentration value claculated
 */
float socket3Class::readConcentration()
{
	return getConcentration((readResistance() / Ro ) / 1000.0);
}


/*!
 * @brief	Switch the SOCKET3 ON and configure the multiplexer
 * @param 	void
 * @return	void
 */
void socket3Class::ON(void)
{
	state = ON_STATE;
	digitalWrite(SOCKET3_ON_PIN , HIGH);
	
	#if DEBUG_GASES > 1
		if (socket == SOCKET_D) 
		{	
			PRINTLN_GASES("NO2 Sensor configured in the SOCKET_D");
		} else if (socket == SOCKET_1)
		{
			PRINTLN_GASES("NO2 Sensor configured in the SOCKET_3");
		}
		else 
		{
			PRINTLN_GASES("O2 Sensor wrong configured");
			PRINTLN_GASES("Use SOCKET_3 in OEM platform or SOCKET_D in Plug&Sense! platform");
		}
	#endif
	
	// Configure the Analog Multiplexor to read from SOCKET3
	setMUX();
	delay(10);
	
	setAmplifier(GAIN_DIGIPOT_ADDRESS, gain);
	setResistor(SOCKET3_DIGIPOT_ADDRESS, loadResistor, SOCKET3_POTENTIOMETER);
}


/*!
 * @brief	Switch the SOCKET3 OFF and configure the multiplexe
 * @param 	void
 * @return	void
 */
void socket3Class::OFF()
{
	state = OFF_STATE;
	digitalWrite(SOCKET3_ON_PIN , LOW);	
}


/*!
 * @brief	Configure the Analog Multiplexor to read from SOCKET3
 * @param 	void
 * @return	void
 */
void socket3Class::setMUX(void)
{
	digitalWrite(A2, 0);
	digitalWrite(A1, 1);
	digitalWrite(A0, 0);
	digitalWrite(EN, 1);
}


//************************************************************************************
// NO2 SENSOR CLASS - Derives from SOCKET3 CLASS
//************************************************************************************
/*!
 * @brief	Class constructor
 * @param 	void
 * @return	void
 */
NO2SensorClass::NO2SensorClass()
{
	//~ #if DEBUG_GASES > 1
		//~ PRINTLN_GASES("NO2 Sensor configured in the SOCKET_3 by default");
	//~ #endif
	
	gain = 1.08;
	loadResistor = 12.50;
}


/*!
 * @brief	Class constructor
 * @param 	uint8_t _socket: socket where the sensor is connected
 * @return	void
 */
NO2SensorClass::NO2SensorClass(uint8_t _socket)
{
	gain = 1.08;
	loadResistor = 12.50;
	
	#if DEBUG_GASES > 1
		if (_socket == SOCKET_D) 
		{
				PRINTLN_GASES("NO2 Sensor configured in the SOCKET_D");
		} else if (_socket == SOCKET_3)
		{
			PRINTLN_GASES("NO2 Sensor configured in the SOCKET_3");
		}
		else 
		{	
				PRINTLN_GASES("NO2 Sensor wrong configured");
				PRINTLN_GASES("Use SOCKET_3 in OEM platform or SOCKET_D in Plug&Sense! platform");
		}
	#endif
}

/*!
 * @brief	Class constructor
 * 
 * @param	uint8_t _socket: socket where the sensor is connected
 * @param 	float _gain: Gain of the stage
 * @param 	float _loadResistor: The resistance to be configured
 * 
 * @return	void
 */
NO2SensorClass::NO2SensorClass(uint8_t _socket, float _gain, float _loadResistor)
{
	gain = _gain;
	loadResistor = _loadResistor;
	
	#if DEBUG_GASES > 1
		if (_socket == SOCKET_D) 
		{
				PRINTLN_GASES("NO2 Sensor configured in the SOCKET_D");
		} else if (_socket == SOCKET_3)
		{
			PRINTLN_GASES("NO2 Sensor configured in the SOCKET_3");
		}
		else 
		{	
				PRINTLN_GASES("NO2 Sensor wrong configured");
				PRINTLN_GASES("Use SOCKET_3 in OEM platform or SOCKET_D in Plug&Sense! platform");
		}
	#endif
}


//************************************************************************************
// SOCKET4 SENSOR CLASS - NH3 and CO sensors can be connected
//************************************************************************************
//======================================================================
// PUBLIC METHODS
//======================================================================
/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
socket4Class::socket4Class()
{
	gain = 1.08;
	loadResistor = 12.5;
}


/*!
 * @brief	Constructor of the class
 * 
 * @param 	float _gain: gain of the stage to be configured
 * @param	float _loadResistor: load resistor to be configured
 * 
 * @return	void
 */
socket4Class::socket4Class(float _gain, float _loadResistor)
{
	gain = _gain;
	loadResistor = _loadResistor;
}


/*!
 * @brief	Switch ON the SOCKET4 and configure the multiplexer
 * @param 	void
 * @return	void
 */
void socket4Class::ON()
{
	state = ON_STATE;
	
	#if DEBUG_GASES > 1
		if (socket == SOCKET_A) {
			
				PRINTLN_GASES("CO & NH3 Sensor configured in the SOCKET_A");
		} else if (socket == SOCKET_4)
		{
			PRINTLN_GASES("CO & NH3 Sensor configured in the SOCKET_4");
		}
		else 
		{	
				PRINTLN_GASES("CO & NH3 Sensor wrong configured");
				PRINTLN_GASES("Use SOCKET_4 in OEM platform or SOCKET_A in Plug&Sense! platform");
		}
	#endif
	
	// Configure the Analog Multiplexor to read from SOCKET4
	setMUX();
	delay(10);
	
	setAmplifier(GAIN_DIGIPOT_ADDRESS, gain);
	setResistor(SOCKET4_DIGIPOT_ADDRESS, loadResistor, SOCKET4_POTENTIOMETER);
}


/*!
 * @brief	Switch OFF the SOCKET4
 * @param 	void
 * @return	void
 */
void socket4Class::OFF()
{
	state = OFF_STATE;
}

//======================================================================
// PRIVATE METHODS
//======================================================================
/*!
 * @brief	Configure the Analog Multiplexor to read from SOCKET4
 * @param 	void
 * @return	void
 */
void socket4Class::setMUX()
{
	
	digitalWrite(A2, 0);
	digitalWrite(A1, 1);
	digitalWrite(A0, 1);
	digitalWrite(EN, 1);
}


//======================================================================
// CO Sensor Class
//======================================================================
/*!
 * @brief	Class contructor
 * @param 	void
 * @return	void
 */
COSensorClass::COSensorClass()
{
	gain = 1.08;
	loadResistor = 12.0;
}


/*!
 * @brief	Class contructor
 * @param 	uint8_t _socket: socket where the sensor is connected
 * @return	void
 */
COSensorClass::COSensorClass(uint8_t _socket)
{
	socket = _socket;
}


/*!
 * @brief	Class contructor
 * 
 * @param	uint8_t _socket: socket where the sensor is connected
 * @param 	float _gain: gain of the stage
 * @param	float _loadResistor: load resistor to be configured
 * 
 * @return	void
 */
COSensorClass::COSensorClass(uint8_t _socket, float _gain, float _loadResistor)
{
	// Store the gain value of the stage
	socket = _socket;
	gain = _gain;
	loadResistor = _loadResistor;
}


/*!
 * @brief	Read the ADC of the waspmote and return a voltage  (in mV)
 * @param 	void
 * @return	The value of the volatge read from sensor
 */
float COSensorClass::readVoltage()
{
	float analogValue;
	
	digitalWrite(SOCKET4_ON_PIN, HIGH); 
	delay(14);
	digitalWrite(SOCKET4_ON_PIN, LOW);
	delay(981);
	digitalWrite(SOCKET4_CONTROL_PIN, HIGH);
	delay(3); 
	analogValue = analogRead(ANALOG3);
	delay(2);
	digitalWrite(SOCKET4_CONTROL_PIN, LOW);
	
	// Return the correspondig value
	return ((analogValue * ANALOG_REFERENCE * 1000) / (1024 * gain));
}


/*!
 * @brief	Calculate the resistance from input voltage value
 * @param 	float input: voltage value
 * @return	The resistance value calculated
 */
float COSensorClass::readResistance(float input)
{
	return (SOCKET4_SUPPLY * (loadResistor * 1000.0)) / (input / 1000.0)  - (loadResistor * 1000.0);
}


/*!
 * @brief	Calculate the resistance from a read value
 * @param void
 * @return	The resistance value calculated
 */
float COSensorClass::readResistance()
{
	
	return (SOCKET4_SUPPLY * (loadResistor * 1000.0)) / (readVoltage() / 1000.0)  - (loadResistor * 1000.0);
}


/*!
 * @brief	Calculate the concentration from input resistance value
 * @param 	float input: voltage value
 * @return	The concentration value calculated
 */
float COSensorClass::readConcentration(float input)
{
	return getConcentration((input / Ro ) / 1000.0);
}


/*!
 * @brief	Calculate the concentration from input resistance value
 * @param	void
 * @return	The concentration value calculated
 */
float COSensorClass::readConcentration()
{
	return getConcentration((readResistance() / Ro ) / 1000.0);
}


//======================================================================
// NH3 Sensor Class
//======================================================================
/*!
 * @brief	Class contructor
 * @param 	void
 * @return	void
 */
NH3SensorClass::NH3SensorClass()
{
	gain = 1.08;
	loadResistor = 12.5;
}


/*!
 * @brief	Class contructor
 * @param 	uint8_t socket: socket where the sensor is connected
 * @return	void
 */
NH3SensorClass::NH3SensorClass(uint8_t socket)
{
	gain = 1.08;
	loadResistor = 12.5;
}


/*!
 * @brief	Class contructor
 * @param	uint8_t _socket: socket where the sensor is connected
 * @param	float _gain: gain of the stage
 * @param	float _loadResistor: load resistor to be configured
 * 
 * @return	void
 */
NH3SensorClass::NH3SensorClass(uint8_t _socket, float _gain, float _loadResistor)
{
	// Store the gain value of the stage
	gain = _gain;
	loadResistor = _loadResistor;
}

/*!
 * @brief	Read the ADC of the waspmote and return a voltage (in mV)
 * @param 	void
 * @return	The voltage value read from the ADC
 */
float NH3SensorClass::readVoltage()
{
	
	float analogValue = 0.0;
	
	for (int i = 0; i < 5; i++) {
	
		digitalWrite(SOCKET4_ON_PIN, HIGH); // <-- VCC switch ON 
		delay(2);
		digitalWrite(SOCKET4_CONTROL_PIN, HIGH); // CONTROL switch ON
		delay(4);
		analogValue += analogRead(ANALOG3); // read value 
		delay(1);
		digitalWrite(SOCKET4_CONTROL_PIN, LOW); 
		delay(7); 
		digitalWrite(SOCKET4_ON_PIN, LOW);
		delay(235);
	}
	
	return ( ((analogValue/5.0) * ANALOG_REFERENCE * 1000) / (1024 * gain) );
}

/*!
 * @brief	Get the resistance from the voltage value input
 * @param	float: input: voltage value read
 * @return	The resistance value
 */
float NH3SensorClass::readResistance(float input)
{
	return (SOCKET4_SUPPLY * (loadResistor * 1000.0)) / (input / 1000.0)  - (loadResistor * 1000.0);
}


/*!
 * @brief	Get the resistance from the voltage value read
 * @param 	void
 * @return	The resistance value
 */
float NH3SensorClass::readResistance()
{
	return (SOCKET4_SUPPLY * (loadResistor * 1000.0)) / (readVoltage() / 1000.0) - (loadResistor * 1000.0);
}


/*!
 * @brief	Calculate the concentration from input resistance value
 * @param 	float input: voltage value	
 * @return	the concentration value calculated
 */
float NH3SensorClass::readConcentration(float input)
{
	return getConcentration((input / Ro ) / 1000.0);
}


/*!
 * @brief	Calculate the concentration from input resistance value
 * @param	void
 * @return	The concentration value calculated
 */
float NH3SensorClass::readConcentration()
{
	return getConcentration((readResistance() / Ro ) / 1000.0);
}

//************************************************************************************
// SOCKET5 SENSOR CLASS - NO2 Sensor Class
//************************************************************************************
//======================================================================
// PUBLIC METHODS
//======================================================================
/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
socket5Class::socket5Class()
{
	gain = 1.08;
	loadResistor = 12.5;
}


/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
socket5Class::socket5Class(float _gain, float _loadResistor)
{
	gain = _gain;
	loadResistor = _loadResistor;
}


/*!
 * @brief	Switch ON the SOCKET5 and configure the multiplexer
 * @param 	void
 * @return	void
 */
void socket5Class::ON()
{
	state = ON_STATE;
	digitalWrite(SOCKET5_ON_PIN , HIGH);
	
	#if DEBUG_GASES > 1
		if (socket == SOCKET_B) 
		{
			PRINTLN_GASES("VOC & O3 Sensor configured in the SOCKET_B");
		} 
		else if (socket == SOCKET_5)
		{
			PRINTLN_GASES("VOC & O3 Sensor configured in the SOCKET_5");
		}
		else 
		{
			PRINTLN_GASES("VOC & O3 Sensor wrong configured");
			PRINTLN_GASES("Use SOCKET_5 in OEM platform or SOCKET_B in Plug&Sense! platform");
		}
	#endif
	
	// Configure the Analog Multiplexor to read from SOCKET5
	setMUX();
	delay(10);
	
	setAmplifier(GAIN_DIGIPOT_ADDRESS, gain);
	setResistor(SOCKET5_DIGIPOT_ADDRESS, loadResistor, SOCKET5_POTENTIOMETER);
}


/*!
 * @brief	Switch OFF the SOCKET5
 * @param 	void
 * @return	void
 */
void socket5Class::OFF()
{
	state = OFF_STATE;
	digitalWrite(SOCKET5_ON_PIN , LOW);
}


/*!
 * @brief	Read the ADC of the waspmote and return a voltage (in V)
 * @param 	void
 * @return	The value of the volatge read from sensor
 */
float socket5Class::readVoltage()
{
	float analogValue = 0.0;
	
	for (int i = 0; i < 100; i++) {
		analogValue += analogRead(ANALOG3);
		delay(1);
	}
	
	// Return the correspondig value
	return ((analogValue / 100.0) * ANALOG_REFERENCE ) / (1024.0 * gain);
}


/*!
 * @brief	Calculate the resistance from input voltage value
 * @param 	float input: voltage value
 * @return	The resistance value calculated
 */
float socket5Class::readResistance(float input)
{
	return (SOCKET5_SUPPLY * (loadResistor * 1000.0)) / (input) - (loadResistor * 1000.0);
}


/*!
 * @brief	Calculate the resistance from a read voltage
 * @param 	void
 * @return	The resistance value calculated
 */
float socket5Class::readResistance()
{
	return (SOCKET5_SUPPLY * (loadResistor * 1000.0)) / (readVoltage()) - (loadResistor * 1000.0);
}


/*!
 * @brief	Calculate the concentration from input resistance value
 * @param 	float input: voltage value
 * @return	The concentration value calculated
 */
float socket5Class::readConcentration(float input)
{
	return getConcentration((input / Ro ) / 1000.0);
}


/*!
 * @brief	Calculate the concentration from a read resistance value
 * @param 	void
 * @return	The concentration value calculated
 */
float socket5Class::readConcentration()
{
	return getConcentration((readResistance() / Ro ) / 1000.0);
}

//======================================================================
// PRIVATE METHODS
//======================================================================
/*!
 * @brief	Configure the Analog Multiplexor to read from SOCKET5
 * @param 	void
 * @return	void
 */
void socket5Class::setMUX()
{
	digitalWrite(A2, 1);
	digitalWrite(A1, 0);
	digitalWrite(A0, 0);
	digitalWrite(EN, 1);
}


//======================================================================
// VOC Sensor Class
//======================================================================
/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
VOCSensorClass::VOCSensorClass()
{
	// Default values. Do not change except for expert user.
	socket = SOCKET_5;
	gain = 1.08;
	loadResistor = 12.5;
}


/*!
 * @brief	Constructor of the class
 * @param 	uint8_t socket: socket where the sensor is connected
 * @return	void
 */
VOCSensorClass::VOCSensorClass(uint8_t _socket)
{
	// Default values. Do not change except for expert user.
	gain = 1.08;
	loadResistor = 12.5;
	socket = _socket;
}


/*!
 * @brief	Constructor of the class
 * 
 * @param	uint8_t _socket: socket where the sensor is connected
 * @param 	float _gain: gain of the stage to be configured
 * @param	float _loadResistor: load resistor to be configured
 * 
 * @return	void
 */
VOCSensorClass::VOCSensorClass(uint8_t _socket, float _gain, float _loadResistor)
{
	gain = _gain;
	loadResistor = _loadResistor;
	socket = _socket;
}


//======================================================================
// O3 Sensor Class
//======================================================================
/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
O3SensorClass::O3SensorClass()
{
	// Default values. Do not change except for expert user.
	gain = 1.08;
	loadResistor = 12.5;
	socket = SOCKET_5;
}


/*!
 * @brief	Constructor of the class
 * @param 	uint8_t _socket: socket where the sensor is connected
 * @return	void
 */
O3SensorClass::O3SensorClass(uint8_t _socket)
{
	// Default values. Do not change except for expert user.
	gain = 1.08;
	loadResistor = 12.5;
	socket = _socket;
}


/*!
 * @brief	Constructor of the class
 * 
 * @param 	uint8_t _socket: socket where the sensor is connected
 * @param 	float _gain: gain of the stage to be configured
 * @param	float _loadResistor: load resistor to be configured
 * 
 * @return	void
 */
O3SensorClass::O3SensorClass(uint8_t _socket, float _gain, float _loadResistor)
{
	gain = _gain;
	loadResistor = _loadResistor;
	socket = _socket;
}


//************************************************************************************
// SOCKET6 SENSOR CLASS
//************************************************************************************
//======================================================================
// PUBLIC METHODS
//======================================================================

/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
sockets5VClass::sockets5VClass()
{
	// Default Gain and Load Resistor
	socket = SOCKET_6;
	gain = 1.08;
	loadResistor = 5.45;
}

/*!
 * @brief	Constructor of the class
 * @param 	uint8_t _socket: socket where the sensor is connected
 * @return	void
 */
sockets5VClass::sockets5VClass(uint8_t _socket)
{
	// Default Gain and Load Resistor
	socket = _socket;
	gain = 1.08;
	loadResistor = 5.45;
}
	
/*!
 * @brief	Constructor of the class
 * 
 * @param	uint8_t _socket: socket where the sensor is connected
 * @param 	float _gain: gain of the stage to be configured
 * @param	float _loadResistor: load resistor to be configured
 * 
 * @return	void
 */
sockets5VClass::sockets5VClass(uint8_t _socket, float _gain , float _loadResistor)
{
	socket = _socket;
	gain = _gain;
	loadResistor = _loadResistor;
}


/*!
 * @brief	Switch ON the SOCKET6 and configure the multiplexer
 * @param 	void
 * @return	void
 */
void sockets5VClass::ON()
{
	if ((socket == SOCKET_6) || (socket == SOCKET_F))
	{
		state = ON_STATE;
		digitalWrite(SOCKET6_ON_PIN , HIGH);
	
		#if DEBUG_GASES > 1
			PRINT_GASES("SOCKET_6 and SOCKET_7 (5V Sensors) switched ON. ");
			PRINTLN_GASES("Configuring Amplifier stage and Load Resistor for SOCKET_6 ");
		#endif
	}
	else if (socket == SOCKET_7)
	{
		state = ON_STATE;
		digitalWrite(SOCKET7_ON_PIN , HIGH);
	
		#if DEBUG_GASES > 1
			PRINT_GASES("SOCKET_6 and SOCKET_7 (5V Sensors) switched ON. ");
			PRINTLN_GASES("Configuring Amplifier stage and Load Resistor for SOCKET_7 ");
		#endif
	}
	
	// Configure the Analog Multiplexor to read from SOCKET_6 or SOCKET_7
	setMUX();
	delay(10);
	
	if ((socket == SOCKET_6) || (socket == SOCKET_F))
	{
		setAmplifier(GAIN_DIGIPOT_ADDRESS, gain);
		setResistor(SOCKET6_DIGIPOT_ADDRESS, loadResistor, SOCKET6_POTENTIOMETER);
	} 
	else if (socket == SOCKET_7)
	{
		setAmplifier(GAIN_DIGIPOT_ADDRESS, gain);
		setResistor(SOCKET7_DIGIPOT_ADDRESS, loadResistor, SOCKET7_POTENTIOMETER);
	}
}


/*!
 * @brief	Switch OFF the SOCKET6
 * @param 	void
 * @return	void
 */
void sockets5VClass::OFF()
{
	if ((socket == SOCKET_6) || (socket == SOCKET_F))
	{
		state = OFF_STATE;
		digitalWrite(SOCKET6_ON_PIN , LOW);
	}
	else if (socket == SOCKET_7)
	{
		state = OFF_STATE;
		digitalWrite(SOCKET7_ON_PIN , LOW);
	}
}


/*!
 * @brief	Read the ADC of the waspmote and return a voltage
 * @param 	void
 * @return	The value of the volatge read from sensor
 */
float sockets5VClass::readVoltage()
{ 
	float analogValue = 0.0;
	
	for (int i = 0; i < 100; i++)
	{
		analogValue += analogRead(ANALOG3);
		delay(1);
	}
	
	// Return the correspondig value
	return ((analogValue / 100.0) * ANALOG_REFERENCE / ( 1024 * gain));
}


/*!
 * @brief	Get the resistance from the voltage value read
 * @param 	float: input: voltage value read
 * @return	The resistance value
 */
float sockets5VClass::readResistance(float input)
{
	return (SOCKET6_SUPPLY * (loadResistor * 1000.0)) / (input)  - (loadResistor * 1000.0) ;
}


/*!
 * @brief	Get the resistance from the voltage value read
 * @param 	void
 * @return	The resistance value
 */
float sockets5VClass::readResistance()
{
	return (SOCKET6_SUPPLY * (loadResistor * 1000.0)) / (readVoltage())  - (loadResistor * 1000.0) ;
}


/*!
 * @brief	Calculate the concentration from input resistance value
 * @param 	float input: voltage value
 * @return	The concentration value calculated
 */
float sockets5VClass::readConcentration(float input)
{
	return getConcentration((input / Ro ) / 1000.0);
}


/*!
 * @brief	Calculate the concentration from read resistance value
 * @param 	void
 * @return	The concentration value calculated
 */
float sockets5VClass::readConcentration()
{
	return getConcentration((readResistance() / Ro ) / 1000.0);
}


//======================================================================
// PRIVATE METHODS
//======================================================================
/*!
 * @brief	Configure the Analog Multiplexor to read from SOCKET6
 * @param 	void
 * @return	void
 */
void sockets5VClass::setMUX()
{
	if ((socket == SOCKET_6) || (socket == SOCKET_F)) 
	{ 
		// Configurin the ANALOG MULTIPLEXER
		digitalWrite(A2, 1);
		digitalWrite(A1, 0);
		digitalWrite(A0, 1);
		digitalWrite(EN, 1);
	}
	else if (socket == SOCKET_7)
	{
		// Configurin the ANALOG MULTIPLEXER
		digitalWrite(A2, 1);
		digitalWrite(A1, 1);
		digitalWrite(A0, 0);
		digitalWrite(EN, 1);
	}
}


/*!
 * @brief	Consturctor of the class
 * 
 * @param 	void 
 * @return	void
 */
CH4SensorClass::CH4SensorClass()
{
	// Default Gain and Load Resistor
	socket = SOCKET_6;
	gain = 1.08;
	loadResistor = 5.45;
}


/*!
 * @brief	Consturctor of the class
 * @param	uint8_t _socket: socket where the sensor is connected * 
 * @return	void
 */
CH4SensorClass::CH4SensorClass(uint8_t _socket)
{
	// Default Gain and Load Resistor
	socket = _socket;
	gain = 1.08;
	loadResistor = 5.45;
}


/*!
 * @brief	Consturctor of the class
 * 
 * @param	uint8_t _socket: socket where the sensor is connected
 * @param	float _gain: gain of the stage to be configured	
 * @param	float _loadResistor: Load resistor to be configured
 * 
 * @return	void
 */
CH4SensorClass::CH4SensorClass(uint8_t _socket, float _gain, float _loadResistor)
{
	// Default Gain and Load Resistor
	socket = _socket;
	gain = _gain;
	loadResistor = _loadResistor;
}


/*!
 * @brief	Consturctor of the class 
 * @param	void 
 * @return	void
 */
APSensorClass::APSensorClass()
{
	// Default Gain and Load Resistor
	socket = SOCKET_6;
	gain = 1.08;
	loadResistor = 5.45;
}


/*!
 * @brief	Consturctor of the class 
 * @param	uint8_t _socket: socket where the sensor is connected
 * @return	void
 */
APSensorClass::APSensorClass(uint8_t _socket) 
{
	// Default Gain and Load Resistor
	socket = _socket;
	gain = 1.08;
	loadResistor = 5.45;
}


/*!
 * @brief	Consturctor of the class
 * 
 * @param	uint8_t _socket: socket where the sensor is connected
 * @param	float _gain: gain of the stage to be configured	
 * @param	float _loadResistor: Load resistor to be configured
 * 
 * @return	void
 */
APSensorClass::APSensorClass(uint8_t _socket, float _gain, float _loadResistor)
{
	// Default Gain and Load Resistor
	socket = _socket;
	gain = _gain;
	loadResistor = _loadResistor;
}


/*!
 * @brief	Consturctor of the class
 * 
 * @param	void
 * @return	void
 */
LPGSensorClass::LPGSensorClass()
{
	// Default Gain and Load Resistor
	socket = SOCKET_6;
	gain = 1.08;
	loadResistor = 5.45;
}


/*!
 * @brief	Consturctor of the class
 * @param	uint8_t _socket: socket where the sensor is connected 
 * @return	void
 */
LPGSensorClass::LPGSensorClass(uint8_t _socket)
{
	// Default Gain and Load Resistor
	socket = _socket;
	gain = 1.08;
	loadResistor = 5.45;
}


/*!
 * @brief	Consturctor of the class
 * 
 * @param	uint8_t _socket: socket where the sensor is connected
 * @param	float _gain: gain of the stage to be configured	
 * @param	float _loadResistor: Load resistor to be configured
 * 
 * @return	void
 */
LPGSensorClass::LPGSensorClass(uint8_t _socket, float _gain, float _loadResistor)
{
	// Default Gain and Load Resistor
	socket = _socket;
	gain = _gain;
	loadResistor = _loadResistor;
}


/*!
 * @brief	Consturctor of the class
 * @param	void
 * @return	void
 */
SVSensorClass::SVSensorClass()
{
	// Default Gain and Load Resistor
	socket = SOCKET_6;
	gain = 1.08;
	loadResistor = 5.45;
}


/*!
 * @brief	Consturctor of the class 
 * @param	uint8_t _socket: socket where the sensor is connected 
 * @return	void
 */
SVSensorClass::SVSensorClass(uint8_t _socket)
{
	// Default Gain and Load Resistor
	socket = _socket;
	gain = 1.08;
	loadResistor = 5.45;
}


/*!
 * @brief	Consturctor of the class
 * 
 * @param	uint8_t _socket: socket where the sensor is connected
 * @param	float _gain: gain of the stage to be configured	
 * @param	float _loadResistor: Load resistor to be configured
 * 
 * @return	void
 */
SVSensorClass::SVSensorClass(uint8_t _socket, float _gain, float _loadResistor)
{
	// Default Gain and Load Resistor
	socket = _socket;
	gain = _gain;
	loadResistor = _loadResistor;
}

// Instance of the GasSensorClass 
GasSensorClass Gases = GasSensorClass();

