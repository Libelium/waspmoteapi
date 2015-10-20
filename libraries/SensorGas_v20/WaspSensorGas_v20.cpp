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
 *  Version:		1.2
 *  Design:		David Gascón
 *  Implementation:	Alberto Bielsa, Manuel Calahorra
 */
 

#ifndef __WPROGRAM_H__
	#include <WaspClasses.h>
#endif

#include "WaspSensorGas_v20.h"

// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorGas_v20::WaspSensorGas_v20()
{
	pinMode(DIGITAL7,OUTPUT);
	pinMode(DIGITAL6,OUTPUT);
	pinMode(DIGITAL5,OUTPUT);
	pinMode(DIGITAL2,OUTPUT);
	pinMode(DIGITAL4,OUTPUT);
	pinMode(DIGITAL3,OUTPUT);
	pinMode(DIGITAL1,OUTPUT);	
	
	digitalWrite(DIGITAL7,LOW);
	digitalWrite(DIGITAL6,LOW);
	digitalWrite(DIGITAL5,LOW);
	digitalWrite(DIGITAL2,LOW);
	digitalWrite(DIGITAL4,LOW);
	digitalWrite(DIGITAL3,LOW);
	digitalWrite(DIGITAL1,LOW);	
	
	// init power supply to OFF state
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	
	// update Waspmote Control Register
	WaspRegister |= REG_GASES;
}

// Public Methods //////////////////////////////////////////////////////////////

/*	ON: Calls the setBoardMode function to turn on the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorGas_v20::ON(void)
{
	setBoardMode(SENS_ON);
}

/*	OFF: Calls the setBoardMode function to turn off the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorGas_v20::OFF(void)
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
int8_t	WaspSensorGas_v20::setBoardMode(uint8_t mode)
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

/*	configureSensor: calls the configureSensor function for those sensors that
 * 					 don't have a load resistor
 *	Parameters:	int sensor
 * 						- SENS_CO2 : Carbon Dioxide Sensor
 * 						- O2 : Oxygen Sensor
 *  Return:		int8_t error
 * 						1 : success
 * 						-1 : wrong sensor selected
 * 
 */
int8_t	WaspSensorGas_v20::configureSensor(uint16_t sensor, uint8_t gain)
{
	if( (sensor == SENS_CO2) ||  (sensor == SENS_O2))
	{
		configureSensor(sensor,gain,0);
		return 1;
	} else return -1;
}

/*	configureSensor: It configures the resistor and gain for a given sensor by
 * 					 setting the corresponding digital potentiometers
 *	Parameters:	uint16_t sensor
 * 							- SENS_CO2 : Carbon Dioxide Sensor
 * 							- O2 : Oxygen Sensor
 * 							- SENS_SOCKET2A : Sensor placed on SOCKET2A
 * 							- SENS_SOCKET2B : Sensor placed on SOCKET2B
 * 							- SENS_SOCKET3A : Sensor placed on SOCKET3A
 * 							- SENS_SOCKET3B : Sensor placed on SOCKET3B
 * 							- SENS_SOCKET3CO : Carbon Monoxide Sensor placed on
 * 											   SOCKET3A
 * 							- SENS_SOCKET3NH3 : Ammonia Sensor placed on
 * 												SOCKET3A
 *	 						- SENS_SOCKET4A : Sensor placed on SOCKET4
 * 							- SENS_SOCKET4CO : Carbon Monoxide Sensor placed on
 * 											   SOCKET4
 * 							- SENS_SOCKET4NH3 : Ammonia Sensor placed on SOCKET4
 * 				uint8_t gain : gain of the stage
 * 				float resistor : load resistor of the stage in kiloohms
 *  Return:		int8_t error
 * 						1 : success
 * 						0 : too high load resistor
 * 						-1: wrong sensor selected
 * 						-2: too high gain
 * 
 */
int8_t	WaspSensorGas_v20::configureSensor(uint16_t sensor, uint8_t gain, float resistor)
{
	if(resistor > 100)
	{
		return 0;
	}
	
	if(gain > 101)
	{
		return -2;
	}
		
	switch( sensor )
	{
		case	SENS_CO2		:	configureAmplifier(SENS_AMPLI1,gain);
									break;
		case	SENS_O2			:	configureAmplifier(SENS_AMPLI1,gain);
									break;
		case	SENS_SOCKET2A	:	configureResistor(SENS_R1,resistor);
									configureAmplifier(SENS_AMPLI2,gain);
									break;
		case	SENS_SOCKET2B	:	configureResistor(SENS_R1,resistor);
									configureAmplifier(SENS_AMPLI2,gain);
									break;
		case	SENS_SOCKET3A	:	configureResistor(SENS_R2,resistor);
									configureAmplifier(SENS_AMPLI3,gain);
									break;
		case	SENS_SOCKET3B	:	configureResistor(SENS_R2,resistor);
									configureAmplifier(SENS_AMPLI3,gain);
									break;
		case	SENS_SOCKET3CO	:	configureResistor(SENS_R2,resistor);
									configureAmplifier(SENS_AMPLI3,gain);
									break;
		case	SENS_SOCKET3NH3	:	configureResistor(SENS_R2,resistor);
									configureAmplifier(SENS_AMPLI3,gain);
									break;
		case	SENS_SOCKET4A	:	configureResistor(SENS_R3,resistor);
									configureAmplifier(SENS_AMPLI4,gain);
									break;
		case	SENS_SOCKET4CO	:	configureResistor(SENS_R3,resistor);
									configureAmplifier(SENS_AMPLI4,gain);
									break;
		case	SENS_SOCKET4NH3	:	configureResistor(SENS_R3,resistor);
									configureAmplifier(SENS_AMPLI4,gain);
									break;
		default					:	return -1;
	}
	
	return 1;
}

/*	setSensorMode: It sets ON/OFF the different sensor switches
 *	Parameters:	uint8_t mode 
 * 						- SENS_ON : turn on the sensor
 * 						- SENS_OFF : turn off the sensor
 * 				uint16_t sensor
 * 							- SENS_PRESSURE : Atmospheric Pressure Sensor
 * 							- SENS_CO2 : Carbon Dioxide Sensor
 * 							- SENS_O2 : Oxygen Sensor
 * 							- SENS_SOCKET2A : Sensor placed on SOCKET2A
 * 							- SENS_SOCKET2B : Sensor placed on SOCKET2B
 * 							- SENS_SOCKET3A : Sensor placed on SOCKET3A
 * 							- SENS_SOCKET3B : Sensor placed on SOCKET3B
 *	 						- SENS_SOCKET4A : Sensor placed on SOCKET4
 *  Return:		int8_t error
 * 						1 : success
 * 						0 : wrong mode selected
 * 						-1: wrong sensor selected
 * 
 */
int8_t	WaspSensorGas_v20::setSensorMode(uint8_t mode, uint16_t sensor)
{
	if( mode==SENS_ON )
	{
		switch( sensor )
		{
			case	SENS_PRESSURE	:	digitalWrite(DIGITAL8,HIGH);
										break;
			case	SENS_CO2		:	digitalWrite(DIGITAL2,HIGH);
										break;
			case	SENS_O2			:	digitalWrite(DIGITAL2,LOW);
										break;
			case	SENS_SOCKET2A	:	digitalWrite(DIGITAL4,HIGH);
										break;
			case	SENS_SOCKET2B:		digitalWrite(DIGITAL4,LOW);
										break;
			case	SENS_SOCKET3A	:	digitalWrite(DIGITAL1,HIGH);
										digitalWrite(DIGITAL7,HIGH);
										break;
			case	SENS_SOCKET3B	:	digitalWrite(DIGITAL6,HIGH);
										digitalWrite(DIGITAL1, HIGH);
										NO2_state = NO2_ON;
										break;
			case	SENS_SOCKET4A	:	digitalWrite(DIGITAL3,HIGH);
										digitalWrite(DIGITAL5,HIGH);
										break;
			default					:	return -1;
		}
	} else	if( mode==SENS_OFF )
	{
		switch( sensor )
		{
			case	SENS_PRESSURE	:	digitalWrite(DIGITAL8,LOW);
										break;
			case	SENS_CO2		:	digitalWrite(DIGITAL2,LOW);
										break;
			case	SENS_SOCKET2A	:	digitalWrite(DIGITAL4,LOW);
										break;
			case	SENS_SOCKET2B:		digitalWrite(DIGITAL4,HIGH);
										break;
			case	SENS_SOCKET3A	:	digitalWrite(DIGITAL1,LOW);
										digitalWrite(DIGITAL7,LOW);
										break;
			case	SENS_SOCKET3B	:	digitalWrite(DIGITAL6,LOW);
										digitalWrite(DIGITAL1, LOW);			
										NO2_state = NO2_OFF;
										break;
			case	SENS_SOCKET4A	:	digitalWrite(DIGITAL3,LOW);
										digitalWrite(DIGITAL5,LOW);
										break;
			default					:	return -1;
		}
	} else return 0;
	
	return 1;
}



/*	readValue: reads the analog to digital converter input indicated of the given
 * 			   sensor socket and converts the value into voltage, providing the
 * 			   heater and sensor power pulses in the case of CO and NH3 sensors
 *	Parameters:	uint16_t socket
 * 							- SENS_TEMPERATURE : Temperature Sensor
 * 							- SENS_HUMIDITY : Humidity Sensor
 * 							- SENS_PRESSURE : Pressure Sensor
 * 							- SENS_CO2 : Carbon Dioxide Sensor
 * 							- O2 : Oxygen Sensor
 * 							- SENS_SOCKET2A : Sensor placed on SOCKET2A
 * 							- SENS_SOCKET2B : Sensor placed on SOCKET2B
 * 							- SENS_SOCKET3A : Sensor placed on SOCKET3A
 * 							- SENS_SOCKET3B : Sensor placed on SOCKET3B
 * 							- SENS_SOCKET3CO : Carbon Monoxide Sensor placed on
 * 											   SOCKET3A
 * 							- SENS_SOCKET3NH3 : Ammonia Sensor placed on
 * 												SOCKET3A
 *	 						- SENS_SOCKET4A : Sensor placed on SOCKET4
 * 							- SENS_SOCKET4CO : Carbon Monoxide Sensor placed on
 * 											   SOCKET4
 * 							- SENS_SOCKET4NH3 : Ammonia Sensor placed on SOCKET4
 *  Return:		float value : voltage read at the sensor output or load resistor
 * 							  -1.0 for error in sensor type selection
 * 
 */
float	WaspSensorGas_v20::readValue(uint16_t sensor)
{
	int aux=0;
	float aux2 = 0.0;
	
	switch( sensor )
	{
		case	SENS_TEMPERATURE	:	aux=analogRead(ANALOG1);
										aux2 = mcpConversion(aux);
										break;
		case	SENS_HUMIDITY		:	aux=analogRead(ANALOG4);
										aux2 = senceraConversion(aux);
										break;
		case	SENS_PRESSURE		:	aux=analogRead(ANALOG5);
										aux2 = pressureConversion(aux);
										break;
		case	SENS_CO2			:	aux=analogRead(ANALOG3);
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_O2				:	aux=analogRead(ANALOG3);
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_SOCKET2A		:	aux=analogRead(ANALOG2);
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_SOCKET2B		:	aux=analogRead(ANALOG2);
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_SOCKET3A		:	digitalWrite(DIGITAL6, LOW);
										delay(10);
										aux=analogRead(ANALOG7);
										delay(10);
										if(NO2_state)
										{
											digitalWrite(DIGITAL6, HIGH);
										}
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_SOCKET3B		:	aux=analogRead(ANALOG7);
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_SOCKET3CO		:	aux=pulse(SENS_SOCKET3CO);
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_SOCKET3NH3		:	aux=pulse(SENS_SOCKET3NH3);
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_SOCKET4A		:	aux=analogRead(ANALOG6);
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_SOCKET4CO		:	aux=pulse(SENS_SOCKET4CO);
										aux2 = (aux*3.3)/1023;
										break;
		case	SENS_SOCKET4NH3		:	aux=pulse(SENS_SOCKET4NH3);
										aux2 = (aux*3.3)/1023;
										break;
		default						:	return -1.0;
										
	}
	return	aux2;
}

/*	calculateResistance:	estimates the sensor resistance value in function of
 * 							the voltage read and the configuration parameters
 *	Parameters:	uint16_t sensor
 * 							- SENS_SOCKET2A : Sensor placed on SOCKET2A
 * 							- SENS_SOCKET2B : Sensor placed on SOCKET2B
 * 							- SENS_SOCKET3A : Sensor placed on SOCKET3A
 * 							- SENS_SOCKET3B : Sensor placed on SOCKET3B
 * 							- SENS_SOCKET3CO : Carbon Monoxide Sensor placed on
 * 											   SOCKET3A
 * 							- SENS_SOCKET3NH3 : Ammonia Sensor placed on
 * 												SOCKET3A
 *	 						- SENS_SOCKET4A : Sensor placed on SOCKET4
 * 							- SENS_SOCKET4CO : Carbon Monoxide Sensor placed on
 * 											   SOCKET4
 * 							- SENS_SOCKET4NH3 : Ammonia Sensor placed on SOCKET4
 * 				float value : voltage read using the readValue function
 * 				float load  : load resistor configured with configureSensor
 * 				uint8_t gain: gain configured with function configureSensor
 *  Return:		float value : real resistance of the sensor
 * 							  -1.0 for error owed to a load out of range
 * 							  -2.0 for error owed to a gain out of range
 * 							  -3.0 for error in sensor type selection
 * 
 */
float WaspSensorGas_v20::calculateResistance(uint16_t sensor, float value, uint8_t gain, float load)
{
	float resistor=0.0000000;
	float realGain;
	float realLoad;
	float aux;
	int aux2;
	
	if( (load < 100) || (load > 0) )
	{
		aux = 128*load;
		aux = aux/100;
		aux2 = (uint8_t) 128-aux;
		aux2 = 128 - aux2;
		
		// Calculate the number of steps of the digipot
		// Multiplicate the number of steps by the approximate step resistance and
		// add the approximate wipper resistance
		realLoad = aux2 * 0.781 + 0.12;
	} else
	{
		// Return error if load resistor is out of range
		return -1;
	}
	
	if( (gain < 101) || (gain > 1) )
	{
		// Calculate the number of steps of the digipot
		aux2 = int((gain - 1) * 128 / 100);
		
		// Add the gain according to the number of steps of the resistor and the
		// wipper approximate resistance
		realGain = (1 + 0.12 + 0.781 * aux2);		
	} else
	{
		// Return error if gain is out of range
		return -2;
	}
	
	aux = value / realGain + 0.000001;
	
	switch ( sensor )
	{
		case 	SENS_SOCKET2A	:
		case	SENS_SOCKET3A	:
		case	SENS_SOCKET3CO	:
		case	SENS_SOCKET3NH3	:
		case	SENS_SOCKET4A	:
		case	SENS_SOCKET4CO	:
		case	SENS_SOCKET4NH3	:	resistor = realLoad*(5 - aux)/aux;
									break;
		case	SENS_SOCKET2B	:	resistor = realLoad*(2.5 - aux)/aux;
									break;
		case	SENS_SOCKET3B	:	resistor = realLoad*(1.8 - aux)/aux;
									break;
		default: return -3;
	}
	
	return resistor;
}

/*	calculateConcentration: converts the resistance value read from one sensor into
 * 					   		ppm or ppb using the calibration parameters of the sensor
 *	Parameters:	int calibrationConcentration[3] : array containing the gas concentration
 * 												  values at which the sensor was calibrated
 * 				float calibrationOutput[3]		: sensor's output at the previous
 * 												  concentration values
 * 				float inputValue				: resistance of the sensor measured
 *  Return:		float gasConcentration : concentration of gas measured by the sensor
 * 										 in ppm or ppb
 * 
 */
float WaspSensorGas_v20::calculateConcentration(	int calibrationConcentration[3],
													float calibrationOutput[3],
													float inputValue)
{
	float logx[4];
	float logy[4];
	float sumx;
	float sumy;
	float summul;
	float sumxsqr;
	float alpha;
	float beta;
	float gasConcentration;
	int i;
	float OXYGEN_REF=20.9;
	
	// check if we have a oxygen calibration, then proceed with the linear
	// aproximation of the oxygen value given by the reference value and the
	// calibrated output for the sensor
	if( (calibrationConcentration[0]==0) 
		&&	(calibrationConcentration[1]==0) 
		&&	(calibrationConcentration[2]==0) )
	{
		return  inputValue*OXYGEN_REF/calibrationOutput[0];
	}
		

	for (i=0;i<3;i++)
	{
		logx[i]=log10(calibrationConcentration[i]);
		logy[i]=log10(calibrationOutput[i]);
	}
	  
	sumx = logx[0]+logx[1]+logx[2];
	sumy = logy[0]+logy[1]+logy[2];
	summul = logx[0]*logy[0] + logx[1]*logy[1] + logx[2]*logy[2];
	sumxsqr = logx[0]*logx[0] + logx[1]*logx[1] + logx[2]*logx[2];

	alpha = (3*summul - sumx*sumy) / (3*sumxsqr - sumx*sumx);
	  
	beta = sumy/3 - alpha * sumx/3;
	beta = pow(10,beta);

	gasConcentration=pow((inputValue/beta),(1/alpha));    

	  
	return gasConcentration;

}
// Private Methods //////////////////////////////////////////////////////////////

/*	configureResistor: configures the load resistor corresponding to the indicated
 * 					   stage
 *	Parameters:	uint8_t ampli : select the amplifier to be configured
 *  			int8_t resistor : load resistor selected
 * 	Return: 	void
 * 
 */
void WaspSensorGas_v20::configureResistor(uint8_t ampli, float resistor)
{
	switch( ampli )
	{
		case	SENS_R1	:	setResistor(I2C_ADDRESS_GASES_SOCKET_2A_2B,resistor);
							break;
		case	SENS_R2	:	setResistor(I2C_ADDRESS_GASES_SOCKET_3_3B,resistor);
							break;
		case	SENS_R3	:	setResistor(I2C_ADDRESS_GASES_SOCKET_4,resistor);
							break;
		default			:	;
	}
}

/*	setResistor: calculates the resistor value in function of the entered value
 * 				 and sets the digipot
 *	Parameters:	uint8_t address : I2C address of the digipot
 *  			float value : load resistor value selected
 * 	Return: 	void
 * 
 */
void WaspSensorGas_v20::setResistor(uint8_t address, float value)
{
	float auxiliar = 0;
	uint8_t resist=0;
	
	auxiliar = 128*value;
	auxiliar = auxiliar/100;
	resist = (uint8_t) 128-auxiliar;

	if( !Wire.I2C_ON ) Wire.begin();
	delay(100);
	Wire.beginTransmission(address);
	Wire.send(B00000000);
	Wire.send(resist);
	Wire.endTransmission();
	if( Wire.I2C_ON && !ACC.isON && RTC.isON!=1){
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
}

/*	configureAmplifier: configures the gain corresponding to the indicated
 * 					    stage
 *	Parameters:	uint8_t ampli : select the amplifier to be configured
 *  			int8_t resistor : gain selected
 * 	Return: 	void
 * 
 */
void WaspSensorGas_v20::configureAmplifier(uint8_t ampli, uint8_t gain)
{
	switch( ampli )
	{
		case	SENS_AMPLI1	:	setAmplifier(I2C_ADDRESS_GASES_SOCKET_1A_1B,gain);
								break;
		case	SENS_AMPLI2	:	setAmplifier(I2C_ADDRESS_GASES_SOCKET_2A_2B,gain);
								break;
		case	SENS_AMPLI3	:	setAmplifier(I2C_ADDRESS_GASES_SOCKET_3_3B,gain);
								break;
		case	SENS_AMPLI4	:	setAmplifier(I2C_ADDRESS_GASES_SOCKET_4,gain);
								break;
		default				:	;
	}
}

/*	setAmplifier: calculates the resistor value in function of the gain value
 * 				  and sets the digipot
 *	Parameters:	uint8_t address : I2C address of the digipot
 *  			float value : gain value selected
 * 	Return: 	void
 * 
 */
void WaspSensorGas_v20::setAmplifier(uint8_t address, uint8_t value)
{
	uint8_t ampli=0;

	ampli= uint8_t(128-((128*(value-1))/100));

	if( !Wire.I2C_ON ) Wire.begin();
	delay(100);
	Wire.beginTransmission(address);
	Wire.send(B00010000);
	Wire.send(ampli);
	Wire.endTransmission();
	if( Wire.I2C_ON && !ACC.isON && RTC.isON!=1){
		PWR.closeI2C();
		RTC.setMode(RTC_OFF, RTC_I2C_MODE);
	}
}

/*	readValue: reads the analog to digital converter input indicated of the given
 * 			   sensor socket providing the heater and sensor power pulses in the
 * 			   case of CO and NH3 sensors
 *	Parameters:	uint16_t socket
 * 							- SENS_SOCKET3CO : Carbon Monoxide Sensor placed on
 * 											   SOCKET3A
 * 							- SENS_SOCKET3NH3 : Ammonia Sensor placed on
 * 												SOCKET3A
 * 							- SENS_SOCKET4CO : Carbon Monoxide Sensor placed on
 * 											   SOCKET4
 * 							- SENS_SOCKET4NH3 : Ammonia Sensor placed on SOCKET4
 *  Return:		float value : voltage read at the sensor load resistor in LSB
 * 							  -1 for error in sensor type selection
 * 
 */
uint16_t WaspSensorGas_v20::pulse(uint16_t sensor)
{
	uint16_t aux=0;
	
	switch( sensor )
	{
		case	SENS_SOCKET3CO	:	digitalWrite(DIGITAL7, HIGH); 
									delay(14);
									digitalWrite(DIGITAL7, LOW);
									delay(964);
									digitalWrite(DIGITAL6, LOW);
									delay(10);
									digitalWrite(DIGITAL1, HIGH);
									delay(3); 
									aux = analogRead(ANALOG7);
									delay(2);
									digitalWrite(DIGITAL1, LOW);
									delay(8);
									if(NO2_state)
									{
										digitalWrite(DIGITAL6, HIGH);
									}

									break;
		case	SENS_SOCKET3NH3	:	digitalWrite(DIGITAL6, LOW);
									delay(4);
									digitalWrite(DIGITAL7, HIGH); 
									delay(2);
									digitalWrite(DIGITAL1, HIGH);
									delay(4);
									aux = analogRead(ANALOG7);
									delay(1);
									digitalWrite(DIGITAL1, LOW);
									delay(7); 
									digitalWrite(DIGITAL7, LOW);
									delay(2);
									if(NO2_state)
									{
										digitalWrite(DIGITAL6, HIGH);
									}
									delay(230);
									break;
		case	SENS_SOCKET4CO	:	digitalWrite(DIGITAL5, HIGH); 
									delay(14);
									digitalWrite(DIGITAL5, LOW);
									delay(980);
									digitalWrite(DIGITAL3, HIGH);
									delay(3); 
									aux = analogRead(ANALOG6);
									delay(2);
									digitalWrite(DIGITAL3, LOW);
									break;
		case	SENS_SOCKET4NH3	:	digitalWrite(DIGITAL5, HIGH); 
									delay(2);
									digitalWrite(DIGITAL3, HIGH);
									delay(4);
									aux = analogRead(ANALOG6);
									delay(1);
									digitalWrite(DIGITAL3, LOW);
									delay(7); 
									digitalWrite(DIGITAL5, LOW);
									delay(236);
									break;
		default					:	aux = -1;
	}
	return aux;
}
	
/*	pressureConversion: converts the value read at the analog to digital
 * 						converter corresponding to the atmospheric pressure
 * 						sensor into a pressure value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : temperature measured by the sensor in kilopascals
 * 
 */
float WaspSensorGas_v20::pressureConversion(int readValue)
{
	float pressure = 0;   
	
	pressure = (float(readValue) * 3300.0 / 1023.0)/0.6; //sensor output (mV)  
	 
	pressure = (((pressure + 270) / 5000) + 0.095 ) / 0.0088; // kPa
   
	return(pressure);
}

/*	mcpConversion: converts the value read at the analog to digital
 * 				   converter corresponding to the temperature sensor
 * 				   into a temperature value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : temperature measured by the sensor in ºC
 * 
 */
float WaspSensorGas_v20::mcpConversion(int readValue)
{
	float temperature = 0;
   
	temperature = float(readValue) * 3300 / 1023; //sensor output (mV)
   
	temperature = (temperature - 500) / 10; 
   
	return(temperature);
   
}

/*	senceraConversion: converts the value read at the analog to digital
 * 					   converter corresponding to the humidity sensor
 * 					   into a temperature value
 *	Parameters:	int readValue : value read from the analog-to-digital converter
 *  Return:		float value : temperature measured by the sensor in %RH
 * 
 */
float WaspSensorGas_v20::senceraConversion(int readValue)
{
	float humidity = 0.0;   
	
    humidity = (float(readValue) * 3300.0 / 1023.0)/0.6; //sensor output (mV)
	humidity = (humidity - 800) / 31; // %hum
   
	return(humidity);
   
}
	

WaspSensorGas_v20 SensorGasv20=WaspSensorGas_v20();
