/*
 *  Copyright (C) 2013 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		1.0
 *  Design:		David Gascón
 *  Implementation:	Alberto Bielsa, David Cuartielles
 */
 

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

#include "WaspSensorSW.h"


// Constructors ////////////////////////////////////////////////////////////////

/*	Constructor: 	Sets the mode of the digital pins and initializes them
 * 
 */
WaspSensorSW::WaspSensorSW()
{
	// Declares as OUTPUT the Vcc and control pins
	pinMode(SENS_SW_PT1000_VCC, OUTPUT);	//ANALOG1
	pinMode(SENS_SW_DO_VCC, OUTPUT);		//ANALOG2
	pinMode(SENS_SW_COND_VCC, OUTPUT);		//ANALOG3
	pinMode(SENS_SW_PH_VCC, OUTPUT);		//ANALOG4
	pinMode(SENS_SW_ORP_VCC, OUTPUT);		//ANALOG5
	pinMode(SENS_SW_DI_VCC, OUTPUT);		//ANALOG6
	
	pinMode(SW_COND_MUX_0, OUTPUT);			//ANALOG7
	pinMode(SW_COND_MUX_1, OUTPUT);			//DIGITAL1
	
	pinMode(DIGITAL4, OUTPUT);				//ADC chips select input

	// Initiates the pins by letting them LOW so everything is OFF at start
	digitalWrite(SENS_SW_PT1000_VCC, LOW);
	digitalWrite(SENS_SW_DO_VCC, LOW);
	digitalWrite(SENS_SW_COND_VCC, LOW);
	digitalWrite(SENS_SW_PH_VCC, LOW);
	digitalWrite(SENS_SW_ORP_VCC, LOW);
	digitalWrite(SENS_SW_DI_VCC, LOW);
	digitalWrite(DIGITAL4, HIGH);

	SW_condFrequency = 0;

}

// Public Methods //////////////////////////////////////////////////////////////

/*	ON: Calls the setBoardMode function to turn on the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorSW::ON(void)
{
	// Turn on the power switches in Waspmote
	PWR.setSensorPower(SENS_5V, SENS_ON);
	PWR.setSensorPower(SENS_3V3, SENS_ON);

	// Initialization of the SPI bus
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	//Divide the clock frequency
	SPI.setClockDivider(SPI_CLOCK_DIV4);
	//Set data mode
	SPI.setDataMode(SPI_MODE0);
}

/*	OFF: Calls the setBoardMode function to turn off the board
 *	Parameters:	void
 *  Return:		void
 * 
 */
void	WaspSensorSW::OFF(void)
{
	// Turn off the power switches in Waspmote
	PWR.setSensorPower(SENS_5V, SENS_OFF);
	PWR.setSensorPower(SENS_3V3, SENS_OFF);
	
	// Disable the SPI bus
	SPI.end();
}

/*	setSensorMode: Turns on or off the specified sensor
 *	Parameters:	uint8_t mode 
 * 						- SENS_ON : turn on the sensor
 * 						- SENS_OFF : turn off the sensor
 *	Parameters:	uint8_t sensor 
 * 						- SENS_SW_PT1000_VCC	: PT1000 sensor
 *						- SENS_SW_DO_VCC		: Dissolved oxygen sensor
 *						- SENS_SW_COND_VCC		: Conductivity sensor
 *						- SENS_SW_PH_VCC		: pH sensor
 *						- SENS_SW_ORP_VCC		: Oxidation Reduction Potential sensor
 *						- SENS_SW_DI_VCC		: Dissolved ions sensor
 * 						- 1 : success / no error detected
 * 						- 0 : wrong mode introduced
 * 						- -1 : wrong sensor introduced
 * 						- -2: wrong frequency for the conductivity sensor introduced
 * 
 */
int8_t	WaspSensorSW::setSensorMode(uint8_t mode, uint8_t sensor)
{
	return setSensorMode(mode, sensor, 0);
}


/*	setSensorMode: Turns on or off the specified sensor
 *	Parameters:	uint8_t mode 
 * 						- SENS_ON : turn on the sensor
 * 						- SENS_OFF : turn off the sensor
 *	Parameters:	uint8_t sensor 
 * 						- SENS_SW_PT1000_VCC	: PT1000 sensor
 *						- SENS_SW_DO_VCC		: Dissolved oxygen sensor
 *						- SENS_SW_COND_VCC		: Conductivity sensor
 *						- SENS_SW_PH_VCC		: pH sensor
 *						- SENS_SW_ORP_VCC		: Oxidation Reduction Potential sensor
 *						- SENS_SW_DI_VCC		: Dissolved ions sensor
 *	Parameters:	uint8_t frequency 
 * 						- SW_COND_FREQ_1		: set conductivity frequency 1
 *						- SW_COND_FREQ_2		: set conductivity frequency 2
 *						- SW_COND_FREQ_3		: set conductivity frequency 3
 *						- SW_COND_FREQ_4		: set conductivity frequency 4
 * 	Return:				- 1 : success / no error detected
 * 						- 0 : wrong mode introduced
 * 						- -1 : wrong sensor introduced
 * 						- -2: wrong frequency for the conductivity sensor introduced
 * 						- -3: don't turn on the PT1000!
 * 
 */
int8_t	WaspSensorSW::setSensorMode(uint8_t mode, uint8_t sensor, uint8_t frequency)
{
	if( mode==SENS_ON )
	{
		
		// Activate the corresponding digital pin to turn on the sensor
		switch( sensor )
		{
			case	SENS_SW_PT1000	:	// The PT1000 sensor must not be turned on
										return -3;
			case	SENS_SW_DO		:	digitalWrite(SENS_SW_DO_VCC,HIGH);
										break;
			case	SENS_SW_COND	:	// Configures the conductivity measurement circuit
										switch ( frequency )
										{
											// Do nothing in case of turning on another sensor
											case 0				:	break;
											// Configure the two pins of the multiplexor
											case SW_COND_FREQ_1 :	digitalWrite(SW_COND_MUX_0,LOW);
																	digitalWrite(SW_COND_MUX_1,LOW);
																	SW_condFrequency = SW_COND_FREQ_1;
																	break;
											case SW_COND_FREQ_2 :	digitalWrite(SW_COND_MUX_0,HIGH);
																	digitalWrite(SW_COND_MUX_1,LOW);
																	SW_condFrequency = SW_COND_FREQ_2;
																	break;
											case SW_COND_FREQ_3 :	digitalWrite(SW_COND_MUX_0,LOW);
																	digitalWrite(SW_COND_MUX_1,HIGH);
																	SW_condFrequency = SW_COND_FREQ_3;
																	break;
											case SW_COND_FREQ_4 :	digitalWrite(SW_COND_MUX_0,HIGH);
																	digitalWrite(SW_COND_MUX_1,HIGH);
																	SW_condFrequency = SW_COND_FREQ_4;
																	break;
											// Return error -2 in case of a wrong frequency selection
											default				:	SW_condFrequency = 0;
																	return -2;
										}
										digitalWrite(SENS_SW_COND_VCC,HIGH);
										break;
			case	SENS_SW_PH		:	digitalWrite(SENS_SW_PH_VCC,HIGH);
										break;
			case	SENS_SW_ORP		:	digitalWrite(SENS_SW_ORP_VCC,HIGH);
										break;
			case	SENS_SW_DI		:	digitalWrite(SENS_SW_DI_VCC,HIGH);
										break;
			default					:	return -1;
		}
	} else if( mode==SENS_OFF )
	{
		// Deactivate the corresponding digital pin to turn off the sensor
		switch( sensor )
		{
			case	SENS_SW_PT1000	:	// The PT1000 sensor must not be turned on
										return -3;
			case	SENS_SW_DO		:	digitalWrite(SENS_SW_DO_VCC,LOW);
										break;
			case	SENS_SW_COND	:	// Also set LOW bothe digital pins
										// of the frequency multiplexor
										digitalWrite(SENS_SW_COND_VCC,LOW);
										digitalWrite(SW_COND_MUX_0,LOW);
										digitalWrite(SW_COND_MUX_1,LOW);
										SW_condFrequency = 0;
										break;
			case	SENS_SW_PH		:	digitalWrite(SENS_SW_PH_VCC,LOW);
										break;
			case	SENS_SW_ORP		:	digitalWrite(SENS_SW_ORP_VCC,LOW);
										break;
			case	SENS_SW_DI		:	digitalWrite(SENS_SW_DI_VCC,LOW);
										break;
			default					:	return -1;
		}
	} else return 0;
	
	return 1;
}


/*	readValue: Reads the specified sensor, including the frequency of operation of
 * 			   the conductivity sensor
 *	Parameters:	uint8_t sensor
 * 						- SENS_SW_PT1000	: PT1000 sensor
 *						- SENS_SW_DO		: Dissolved oxygen sensor
 *						- SENS_SW_COND		: Conductivity sensor
 *						- SENS_SW_PH		: pH sensor
 *						- SENS_SW_ORP		: Oxidation Reduction Potential sensor
 *						- SENS_SW_DI		: Dissolved ions sensor
 *  Return:		float value : value read from the sensor in volts (0~4.096V)
 * 							  In the case of the PT1000 sensor the value is converted
 * 							  into a temperature value in ºC
 * 							  In the case of the conductivity sensor the value is
 * 							  converted into resistance
 * 
 */
float	WaspSensorSW::readValue(uint8_t sensor)
{
	int i = 0;
	float value = 0.0;
	float value_array[16];
	
	switch( sensor )
	{
		case SENS_SW_PT1000	:	value = readPT1000();
								break;
		case SENS_SW_DO		:	for(i=0;i<15;i++)
								{
									value_array[i] = readADC(2);
								}
								value = median(value_array,15);
								break;
		case SENS_SW_COND	:	for(i=0;i<15;i++)
								{
									value_array[i] = readADC(7);
								}
								value = median(value_array,15);
								value = resistanceConversion(value);
								break;
		case SENS_SW_PH		:	for(i=0;i<15;i++)
								{
									value_array[i] = readADC(3);
								}
								value = median(value_array,15);
								break;
		case SENS_SW_ORP	:	for(i=0;i<15;i++)
								{
									value_array[i] = readADC(4);
								}
								value = median(value_array,15)-2.048;
								break;
		case SENS_SW_DI		:	for(i=0;i<15;i++)
								{
									value_array[i] = readADC(5);
								}
								value = median(value_array,15);
								break;
		default				:	return -10.00;
	}

	return value;
}

/*	conductivityConversion: Converts the resistance of the conductivity sensor
 * 							into a conductivity value in mS/cm
 *	Parameters:	float input : resistance of the sensor
 *  Return:		float value : the conductivity of the solution in mS/cm
 * 
 */
float WaspSensorSW::conductivityConversion(float input)
{
	float value;
	
	// Converts the resistance of the sensor into a conductivity value
	value = 1000 / (input);
	
	return value;
}

/*	conductivityConversion: Converts the resistance of the conductivity sensor
 * 							into a conductivity value in mS/cm
 *	Parameters:	float input : resistance of the sensor
 * 				int cond_1  : conductivity of the first calibration solution (higher conductivity)
 * 				float cal_1 : sensor resistance at the first calibration solution
 * 				int cond_2  : conductivity of the second calibration solution (lower conductivity)
 * 				float cal_2 : sensor resistance at the second calibration solution
 *  Return:		float value : the conductivity of the solution in mS/cm
 * 
 */
float WaspSensorSW::conductivityConversion(float input, float cond_1, float cal_1, float cond_2, float cal_2)
{
	float value;
	float SW_condK;
	float SW_condOffset;
	
	// Calculates the cell factor of the conductivity sensor and the offset from the calibration values
	SW_condK = cond_1 * cond_2 * ((cal_1-cal_2)/(cond_2-cond_1));
	SW_condOffset = (cond_1*cal_1-cond_2*cal_2)/(cond_2-cond_1);
	
	// Converts the resistance of the sensor into a conductivity value
	value = SW_condK * 1/ (input+SW_condOffset);

	return value;
}

/*	DOConversion: Converts the voltage of the dissolved oxygen sensor into a 
 * 				  percentage of concentration
 *	Parameters:	float input 	 : voltage measured
 * 				float air_value  : sensor voltage in air
 * 				float zero_value : sensor voltage in zero oxygen solution
 *  Return:		float value : the dissolved oxygen concentration of the solution
 * 
 */
float WaspSensorSW::DOConversion(float input, float air_value, float zero_value)
{
	float value;
	
	// Calculates the concentration of dissolved oxygen
	value = (input - zero_value)/(air_value - zero_value) * 100;
		
	return value;
}

/*	pHConversion: converts the voltage value into a pH value without calibration considerations
 *	Parameters:	float input : voltage measured at the sensor output
 * 				float cal_1 : voltage measured with the 4.0pH calibration solution
 * 				float cal_2 : voltage measured with the 7.0pH calibration solution
 * 				float cal_3 : voltage measured with the 10.0pH calibration solution
 *  Return:		float value : the pH of the solution
 * 
 */
float WaspSensorSW::pHConversion(float input)
{
	return pHConversion(input, 2.227, 2.048, 1.868, 0, 0);
}


/*	pHConversion: converts the voltage value into a pH value without temperature considerations
 *	Parameters:	float input : voltage measured at the sensor output
 * 				float cal_1 : voltage measured with the 4.0pH calibration solution
 * 				float cal_2 : voltage measured with the 7.0pH calibration solution
 * 				float cal_3 : voltage measured with the 10.0pH calibration solution
 *  Return:		float value : the pH of the solution
 * 
 */
float WaspSensorSW::pHConversion(float input, float cal_1, float cal_2, float cal_3)
{
	return pHConversion(input, cal_1, cal_2, cal_3, 0, 0);
}

/*	pHConversion: converts the voltage value into a pH value updating the sensitivity
 * 				  in function of the temperature change
 *	Parameters:	float input    : voltage measured at the sensor output
 * 				float cal_1    : voltage measured with the 10.0pH calibration solution
 * 				float cal_2    : voltage measured with the 7.0pH calibration solution
 * 				float cal_3    : voltage measured with the 4.0pH calibration solution
 * 				float temp     : temperature of the test solution
 * 				float temp_cal : temperature of the calibration solutions
 *  Return:		float value : the pH of the solution
 * 							- -1 : wrong temperature introduced
 * 							- -2 : wrong calibration temperature introduced
 * 
 */
float WaspSensorSW::pHConversion(float input, float cal_1, float cal_2, float cal_3, float temp, float temp_cal)
{
	float value;
	float zero_value;
	float sensitivity;
	
	if( (temp < 0)||(temp > 100) )
	{
		return -1.0;
	}
	if((temp_cal < 0)||(temp_cal > 100))
	{
		return -2.0;
	}
	
	// The value at pH 7.0 is taken as reference
	zero_value = cal_2;
	
	// The sensitivity is calculated using the other two calibration values
	sensitivity = (cal_3-cal_1)/6;

	// Add the change in the conductivity owed to the change in temperature
	sensitivity = sensitivity + (temp - temp_cal)*0.0001984;
	
	// pH value calculated from the calibration values
	value = 7.0 + (zero_value-input)/sensitivity;
	
	return value;
}

// Private Methods //////////////////////////////////////////////////////////////

/*	readADC		: reads the analog-to-digital converter in the Smart Water board
 * 				  through the SPI bus.
 *	Parameters:	int channel : channel of the ADC to be read
 *  Return:		float value : voltage read in the ADC in volts (0~4.096V)
 * 
 */
float WaspSensorSW::readADC(int channel)
{
	float value;
	uint8_t en_byte = B00001000;
	uint8_t val[4];

	// If the channel selected is wrong, return -1, else fulfill the channel selection
	// register en_byte
	if (channel>7)
	{
		return -1;
	}
	else
	{
		en_byte = en_byte | channel;
	}
	 

	// selection of the ADC channel 
	SPI.transfer(en_byte);
	delay(1);

	// A new conversion is started through a pulse in the chip selection pin and initiating
	// a transfer
	digitalWrite(DIGITAL4, LOW);
	delay(1);
	SPI.transfer(0x00);
	digitalWrite(DIGITAL4, HIGH);

	// Waiting for the conversion time (max 163.36ms)
	delay(170);

	// Once the new data is ready, initiate a new transfer and put the ADC back to
	// idle state
	digitalWrite(DIGITAL4, LOW);
	delay(1);
	val[0] = SPI.transfer(0x00);
	val[1] = SPI.transfer(0x00);
	val[2] = SPI.transfer(0x00);
	val[3] = SPI.transfer(0x00);
	delay(1);
	digitalWrite(DIGITAL4, HIGH);

	// Convert the read value into volts
	value = float(val[3]) / 16 + float(val[2]) * 16 + float(val[1]) * 4096 + float(val[0] & B00001111) * 1048576;
	value = value / 16777216 * 4.096;

	return value;
}

/*	readPT1000: reads the PT1000 temperature acquiring 15 values and applying a 
 * 				median filter
 *  Return:		float value : temperature value indicated by the PT1000 in ºC
 * 
 */
 float WaspSensorSW::readPT1000(void)
{
	int i = 0;
	float value;
	float val;
	float vals[16];

	// Take fifteen measurements to filter the signal noise and glitches
	for(i=0;i<15;i++)
	{
		// Briefly turn on the sensor so the PT1000 temperature is not increased
		// by the joule effect
		digitalWrite(SENS_SW_PT1000_VCC,HIGH);
		delay(1);
		// Read the analo-to-digital converter to acquire the output voltage
		value = readADC(0);
		// Turn off the sensor when the measurement is complete
		digitalWrite(SENS_SW_PT1000_VCC,LOW);
		
		// Convert the voltage value into a temperature
		val = value / (5 + 5 * 82 / 68 );
		val = (val + 2.048) / (2.048 - val) * 1000;
		val = 0.26048*val-260.83;
		vals[i] = val;
		
		// Wait for 50 milliseconds for the next reading
		delay(50);
	}

	// Calculate the median value of the fifteen readings
	val = median(vals,15);

	return val;
}


/*	readConductivity: reads the conductivity sensor output returning the resistance
 * 					  of the sensor
 *	Parameters:	uint8_t frequency : frequency selected for the sensor operation
 *  Return:		float value : resistance of the conductivity sensor
 * 
 */
 float WaspSensorSW::readConductivity(void)
{
	int i = 0;
	float vals[16];
	float value;
	float res;

	// Reading of the output value at the ADC fifteen times for signal filtering
	for(i=0;i<15;i++)
	{
		vals[i] = readADC(7);
		delay(10);
	}

	// Calculate the median value of the fifteen readings
	value = median(vals,15);
	
	// Converts the voltage value into a resistance value
	res = resistanceConversion(value);

	return res;
}


/*	resistanceConversion: converts the conductivity sensor output voltage into a
 * 						  resistance value
 *	Parameters:	uint8_t frequency : frequency selected for the sensor operation
 *  Return:		float value : resistance of the conductivity sensor
 * 
 */
 float WaspSensorSW::resistanceConversion(float input)
{  
	float value;

	switch ( SW_condFrequency )
	{
		case SW_COND_FREQ_1 : 	input = input / 2.64;
								break;
		case SW_COND_FREQ_2 : 	input = input / 2.64;
								break;
		case SW_COND_FREQ_3 : 	input = input / 2.59;
								break;
		case SW_COND_FREQ_4 : 	input = input / 2.24;
								break;
		default				:	return -1.0;
			
	}

	if(input<=SW_COND_CAL_01) value = 0;
	else if(input<SW_COND_CAL_02) value = 100*(input-SW_COND_CAL_01)/(SW_COND_CAL_02-SW_COND_CAL_01);
	else if(input<SW_COND_CAL_03) value = 100+120*(input-SW_COND_CAL_02)/(SW_COND_CAL_03-SW_COND_CAL_02);
	else if(input<SW_COND_CAL_04) value = 220+220*(input-SW_COND_CAL_03)/(SW_COND_CAL_04-SW_COND_CAL_03);
	else if(input<SW_COND_CAL_05) value = 440+560*(input-SW_COND_CAL_04)/(SW_COND_CAL_05-SW_COND_CAL_04);
	else if(input<SW_COND_CAL_06) value = 1000+1200*(input-SW_COND_CAL_05)/(SW_COND_CAL_06-SW_COND_CAL_05);
	else if(input<SW_COND_CAL_07) value = 2200+2200*(input-SW_COND_CAL_06)/(SW_COND_CAL_07-SW_COND_CAL_06);
	else if(input<SW_COND_CAL_08) value = 4400+1200*(input-SW_COND_CAL_07)/(SW_COND_CAL_08-SW_COND_CAL_07);
	else if(input<SW_COND_CAL_09) value = 5600+4400*(input-SW_COND_CAL_08)/(SW_COND_CAL_09-SW_COND_CAL_08); 
	else if(input<SW_COND_CAL_10) value = 10000+5000*(input-SW_COND_CAL_09)/(SW_COND_CAL_10-SW_COND_CAL_09); 
	else if(input<SW_COND_CAL_11) value = 15000+7000*(input-SW_COND_CAL_10)/(SW_COND_CAL_11-SW_COND_CAL_10);
	else if(input<SW_COND_CAL_12) value = 22000+11000*(input-SW_COND_CAL_11)/(SW_COND_CAL_12-SW_COND_CAL_11);                
	else if(input<SW_COND_CAL_13) value = 33000+14000*(input-SW_COND_CAL_12)/(SW_COND_CAL_13-SW_COND_CAL_12);
	else if(input<SW_COND_CAL_14) value = 47000+21000*(input-SW_COND_CAL_13)/(SW_COND_CAL_14-SW_COND_CAL_13);
	else if(input<SW_COND_CAL_15) value = 68000+32000*(input-SW_COND_CAL_14)/(SW_COND_CAL_15-SW_COND_CAL_14);
	else value = 100000+900000*(input-SW_COND_CAL_15)/(SW_COND_CAL_16-SW_COND_CAL_15);

	return value;
}
  
/*	median: converts the value read at the analog to digital converter at 
 *	 		the input indicated into a voltage
 *	Parameters:	float* array   : array containing the data to be reordered
 * 				uint8_t length : length of the data array
 *  Return:		float value    : median value of the array
 * 
 */
 float WaspSensorSW::median(float* array, uint8_t length)
{
	int k,l,m,n;
	float aux[length];

	// Initialization of the auxiliar array
	for(k=0;k<length;k++) aux[k]=-100000;
	aux[0] = array[0];

	// Ordering of the sensor from lower to higher value
	for (l=1;l<length;l++)
	{
		for(m=0;m<l+1;m++)
		{
			if(array[l]>aux[m])
			{
				for(n=length-1;n>m;n--) aux[n]=aux[n-1];
				aux[m]=array[l];
				m=l+1;
				continue;
			}
		}
	}
	
	// The value in the central position of the array is returned
	return aux[int(length/2)];
}

WaspSensorSW SensorSW=WaspSensorSW();
