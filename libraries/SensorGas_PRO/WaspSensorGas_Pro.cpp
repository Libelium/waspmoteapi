/*
 *  Library for managing the Gas Pro Sensor Board
 * 
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
 *  Version:		1.4
 *  Design:			David Gascón
 *  Implementation:	Alejandro Gállego
 */

#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif

#include <WaspSensorGas_Pro.h>
#include <WaspConstants.h>
#include <BME280.h>
#include <LMP91000.h>
#include <MCP3421.h>


//! Constructors /////////////////////////////////////////////////////////////

/* Function: 	This function owers on the sensor and configures the AFE 
 * Returns: 	1 if OK
 * 				-1 no communication with LMP91000
 */
Gas::Gas(int socket)
{
	
	switch (socket)
	{
		case 1:
			sensor_config.power_pin = DIGITAL3;
			sensor_config.I2C_pin = DIGITAL4;
			sensor_config.socket = 1;
			break;
		case 2:
			sensor_config.power_pin = DIGITAL5;
			sensor_config.I2C_pin = DIGITAL6;
			sensor_config.socket = 2;
			break;
		case 3:
			sensor_config.power_pin = DIGITAL7;
			sensor_config.I2C_pin = DIGITAL8;
			sensor_config.socket = 3;
			break;
		case 4:
			sensor_config.power_pin = ANA6;
			sensor_config.I2C_pin = ANA5;
			sensor_config.socket = 4;
			break;
		case 5:
			sensor_config.power_pin = ANA4;
			sensor_config.I2C_pin = ANA3;
			sensor_config.socket = 5;
			break;
		case 6:
			sensor_config.power_pin = ANA2;
			sensor_config.I2C_pin = ANA1;
			sensor_config.socket = 6;
			break;
		case 0:	// Calibration
			sensor_config.power_pin = GPS_PW;
			sensor_config.I2C_pin = GPS_PW;
			break;
	}
	
	// Default values
	sensor_config.sensor_type = UNDEFINED_SENSOR;
	sensor_config.m_conc = 1;
	sensor_config.baseline = 0;
	sensor_config.val_aux = 1;
	
	for (int x = 0; x < 7; x++)
	{
		sensor_config.calibration[x][0] = 0;
		sensor_config.calibration[x][1] = 1;
	}
	
	pinMode(sensor_config.power_pin, OUTPUT);
	pinMode(sensor_config.I2C_pin, OUTPUT);
	digitalWrite(sensor_config.power_pin, HIGH);
	digitalWrite(sensor_config.I2C_pin, LOW);
	
	/*pinMode(DIGITAL3, OUTPUT);
	pinMode(DIGITAL4, OUTPUT);
	pinMode(DIGITAL5, OUTPUT);
	pinMode(DIGITAL6, OUTPUT);
	pinMode(DIGITAL7, OUTPUT);
	pinMode(DIGITAL8, OUTPUT);
	pinMode(ANA6, OUTPUT);
	pinMode(ANA5, OUTPUT);
	pinMode(ANA4, OUTPUT);
	pinMode(ANA3, OUTPUT);
	pinMode(ANA2, OUTPUT);
	pinMode(ANA1, OUTPUT);
	pinMode(ANA0, OUTPUT);

	digitalWrite(DIGITAL3, HIGH);
	digitalWrite(DIGITAL5, HIGH);
	digitalWrite(DIGITAL7, HIGH);
	digitalWrite(ANA6, HIGH);
	digitalWrite(ANA4, HIGH);
	digitalWrite(ANA2, HIGH);
	digitalWrite(DIGITAL4, LOW);
	digitalWrite(DIGITAL6, LOW);
	digitalWrite(DIGITAL8, LOW);
	digitalWrite(ANA5, LOW);
	digitalWrite(ANA3, LOW);
	digitalWrite(ANA1, LOW);
	digitalWrite(ANA0, LOW);*/
	
	pwrGasPRORegister = 0;
}

Gas::Gas(int socket, uint8_t sensor_type, int power_pin, int I2C_pin, float m_conc, float baseline, float aux_var, float calibration_table[7][2])
{
	
	sensor_config.socket = socket;
	sensor_config.sensor_type = sensor_type;
	sensor_config.power_pin = power_pin;
	sensor_config.I2C_pin = I2C_pin;
	sensor_config.m_conc = m_conc;
	sensor_config.val_aux = aux_var;
	sensor_config.baseline = baseline;
	
	pinMode(DIGITAL3, OUTPUT);
	pinMode(DIGITAL4, OUTPUT);
	pinMode(DIGITAL5, OUTPUT);
	pinMode(DIGITAL6, OUTPUT);
	pinMode(DIGITAL7, OUTPUT);
	pinMode(DIGITAL8, OUTPUT);
	pinMode(ANA6, OUTPUT);
	pinMode(ANA5, OUTPUT);
	pinMode(ANA4, OUTPUT);
	pinMode(ANA3, OUTPUT);
	pinMode(ANA2, OUTPUT);
	pinMode(ANA1, OUTPUT);
	
	digitalWrite(DIGITAL3, HIGH);
	digitalWrite(DIGITAL5, HIGH);
	digitalWrite(DIGITAL7, HIGH);
	digitalWrite(ANA6, HIGH);
	digitalWrite(ANA4, HIGH);
	digitalWrite(ANA2, HIGH);
	digitalWrite(DIGITAL4, LOW);
	digitalWrite(DIGITAL6, LOW);
	digitalWrite(DIGITAL8, LOW);
	digitalWrite(ANA5, LOW);
	digitalWrite(ANA3, LOW);
	digitalWrite(ANA1, LOW);
	
	memcpy(sensor_config.calibration, calibration_table, sizeof(calibration_table));
		
	pwrGasPRORegister = 0;
}

//! PRIVATE FUNCTIONS ////////////////////////////////////////////////////////
//! MEASURING FUNCTIONS
/* Function:	This function generates the baseline compensation for the temperature in ppm
 * Parameters:	temperature: ambient temperature for sensor compensation (-1000 if doesn't needed)
 * Returns:		ppm value for compensation   
*/
float Gas::getBaselineTempComp(float temperature)
{
	float val_high, val_low;
	float comp_ppm = 0;

	
	if(temperature == -1000)
	{
		return 0;
	}
	
	if(temperature < 20)
	{		
		val_low = pgm_read_float(&table_baseline_temp_comp[sensor_config.sensor_type][0]);
		val_high = pgm_read_float(&table_baseline_temp_comp[sensor_config.sensor_type][1]);
		comp_ppm = val_low + (((val_high - val_low) / 40) * (temperature - -20));
		
	}
	else if((temperature >= 20) && (temperature < 40))
	{
		val_low = pgm_read_float(&table_baseline_temp_comp[sensor_config.sensor_type][1]);
		val_high = pgm_read_float(&table_baseline_temp_comp[sensor_config.sensor_type][2]);
		comp_ppm = val_low + (((val_high - val_low) / 20) * (temperature - 20));		
		
	}
	else if((temperature >= 40))
	{
		val_low = pgm_read_float(&table_baseline_temp_comp[sensor_config.sensor_type][2]);
		val_high = pgm_read_float(&table_baseline_temp_comp[sensor_config.sensor_type][3]);
		comp_ppm = val_low + (((val_high - val_low) / 10) * (temperature - 40));
	}
	
	#if GAS_DEBUG==1
		USB.print(F("GP.Baseline compensation: "));
		USB.println(comp_ppm);
	#endif
		
	#if GAS_DEBUG==2
		USB.print(F("GP.Baseline compensation: "));
		USB.print(comp_ppm);
		USB.print(F(" | H_val: "));
		USB.print(val_high);
		USB.print(F(" | L_val: "));
		USB.println(val_low);	
	#endif
	
	return comp_ppm;
}

/* Function: 	This function generates the output current compensation for the temperature
 * Parameters:	temperature: ambient temperature for sensor compensation (-1000 if doesn't needed)
 * Returns:		compensation factor 
*/
float Gas::getSensitivityTempComp(float temperature)
{
	float val_high, val_low;
	float comp_sens = 0;

	
	if(temperature == -1000)
	{
		return 1;
	}
	
	if(temperature < 0)
	{		
		val_low = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][0]);
		val_high = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][1]);
		comp_sens = val_low + (((val_high - val_low) / 40) * (temperature - -20));
	}
	else if((temperature >= 0) && (temperature < 20))
	{
		val_low = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][1]);
		val_high = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][2]);
		comp_sens = val_low + (((val_high - val_low) / 20) * (temperature - 20));		
	}
	else if((temperature >= 20) && (temperature < 40))
	{
		val_low = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][2]);
		val_high = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][3]);
		comp_sens = val_low + (((val_high - val_low) / 20) * (temperature - 20));
	}
	else if((temperature >= 40))
	{
		val_low = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][3]);
		val_high = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][4]);
		comp_sens = val_low + (((val_high - val_low) / 10) * (temperature - 40));
	}
	
	comp_sens = 1 - (1 - comp_sens);
	
	#if GAS_DEBUG==1
		USB.print(F("GP.Sensitivity compensation: "));
		USB.println(comp_sens);
	#endif
		
	#if GAS_DEBUG==2
		USB.print(F("GP.Sensitivity compensation: "));
		USB.print(comp_sens);
		USB.print(F(" | H_val: "));
		USB.print(val_high);
		USB.print(F(" | L_val: "));
		USB.println(val_low);	
	#endif
		
	return comp_sens;
}


//! ONLY FOR 4-ELECTRODE AMPERIOMETRIC BOARD
/* Function:	This function sets the resistance to an specific digipot
 * Parameters:	electrode: electrode asociated to each digipot
 *  			resistor: resistor value to set in Ohms
 * Return: 		void
 */
void Gas::setAmplifier(bool electrode, float resistor)
{
	uint8_t value=0;
	value = 128.0 * (resistor / 100000.0);
	
	#if GAS_DEBUG>0
		USB.print(F("GP.Setting R "));
		USB.print(electrode);
		USB.print(F(" to "));
		USB.print(resistor);
		USB.print(F(" Ohms || wiper: "));
		USB.println(value, HEX);
 	#endif
	
	if (electrode == AUXILIARY_ELECTRODE)
	{
		value = 128 - value;
		Wire.writeBytes( I2C_ADDRESS_GASPRO_MCP4146, VOL_WIPER_0_REG | WRITE_COMMAND, &value, 1);	
	}
	else
	{
		Wire.writeBytes( I2C_ADDRESS_GASPRO_MCP4146, VOL_WIPER_1_REG | WRITE_COMMAND, &value, 1);		
	}	
	
}

/* Function: 	This function gets the resistance from an specific digipot
 * Parameters:	electrode: electrode asociated to each digipot
 * Return: 		resistor value in Ohms
 */
float Gas::getAmplifier(bool electrode)
{
	uint8_t aux[2];
	uint16_t wiper;
	float resistor;
	
	if (electrode == AUXILIARY_ELECTRODE)
	{
		Wire.readBytes(I2C_ADDRESS_GASPRO_MCP4146, VOL_WIPER_0_REG | READ_COMMAND, aux, 2);
	}
	else
	{
		Wire.readBytes(I2C_ADDRESS_GASPRO_MCP4146, VOL_WIPER_1_REG | READ_COMMAND, aux, 2);
	}
	
	wiper = (aux[0] * 256) + aux[1];
	
	if (electrode == AUXILIARY_ELECTRODE)
	{
		wiper = 128 - wiper;
	}
		
	resistor = (float(wiper) / 128.0) * 100000.0;
	
	#if GAS_DEBUG>0
		USB.print(F("GP.Reading wiper "));
		USB.print(electrode);		
		USB.print(F(": "));
		USB.print(wiper, DEC);
		USB.print(F("/128 || Resistor value: "));
		USB.print(resistor);
		USB.println(F(" Ohms"));
	#endif
	
	return resistor;
}


//! MISCELANEUS	
/* Function: 	This function reads the sensor information from EEPROM
 * Return: 		Nothing
 */
void Gas::readSensorInfo()
{
	uint8_t buffer[4];	
	
	// First read the board version and sensor type
	// This parameters are common for all sensors
	Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, VER_BOARD_REG, &sensor_config.sensor_type, 1);	
	Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENSOR_TYPE_REG, &sensor_config.sensor_type, 1);
	
	// Then read the calibration values according the sensor type
	// Each kind of sensor has different calibration patterns
	switch(sensor_config.sensor_type)
	{
		// Pellistors PCB
		case LEL_AS:
		case CALIBRATION_PEL:
		case NDIR_CO2_SS:
		case CALIBRATION_NDIR:			
			
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENSITIVITY_REG, buffer, 4);
			memcpy(&sensor_config.m_conc, buffer, 4);
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, OFFSET_REG, buffer, 4);
			memcpy(&sensor_config.baseline, buffer, 4);
			// Stores calibration value 1
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_1_REG, buffer, 4);
			memcpy(&sensor_config.calibration[0][0], buffer, 4);
			// Stores calibration value 2
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_2_REG, buffer, 4);
			memcpy(&sensor_config.calibration[0][1], buffer, 4);
			
			break;
		
		// 3 electrodes PCB
		case CL2_SS:
		case CO_SS_SEC:
		case ETO_SS:
		case H2_SS_SEC:
		case H2S_SS_SEC:
		case HCL_SS:
		case HCN_SS:
		case NH3_SS:
		case NO_SS:
		case NO2_SS_CLE:
		case O2_SS:
		case PH3_SS:
		case SO2_SS:
		case CALIBRATION_3E:
			
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENSITIVITY_REG, buffer, 4);
			memcpy(&sensor_config.m_conc, buffer, 4);
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, OFFSET_REG, buffer, 4);
			memcpy(&sensor_config.baseline, buffer, 4);
			
			// Reads calibration values
			for (int x = 0; x < 7; x++)
			{
				Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_REG + (x * 8), buffer, 4);
				memcpy(&sensor_config.calibration[x][0], buffer, 4);
				Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_REG + (x * 8) + 4, buffer, 4);
				memcpy(&sensor_config.calibration[x][1], buffer, 4);
			}
			break;
			
		// 4 electrodes PCB
		case O3_AS:
		case CALIBRATION_4E:
			
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENSITIVITY_REG, buffer, 4);
			memcpy(&sensor_config.m_conc, buffer, 4);
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, OFFSET_REG, buffer, 4);
			memcpy(&sensor_config.baseline, buffer, 4);
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENS_AE_REG, buffer, 4);
			memcpy(&sensor_config.val_aux, buffer, 4);
			
			// Reads calibration values for working electrode
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_WE_REG, buffer, 4);
			memcpy(&sensor_config.calibration[0][0], buffer, 4);
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_WE_REG + 4, buffer, 4);
			memcpy(&sensor_config.calibration[0][1], buffer, 4);
			
			// Reads calibration values for working electrode
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_AE_REG, buffer, 4);
			memcpy(&sensor_config.calibration[1][0], buffer, 4);
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_AE_REG + 4, buffer, 4);
			memcpy(&sensor_config.calibration[1][1], buffer, 4);
			
			break;
	}
}


//! PUBLIC FUNCTIONS /////////////////////////////////////////////////////////
//! POWER AND CONFIGURATION FUNCTIONS

/* Function: 	This function powers on the sensor and configures the AFE 
 * Returns: 	1 if OK
 * 				-1 no communication with LMP91000
 */
int8_t Gas::ON()
{
	return ON( -1000);	
}

/* Function: 	This function powers on the sensor, configures the AFE and selects the gain
 * Parameters:	R_gain: resistor value for transimpendance amplifier
 * Returns: 	1 if OK
 * 				-1 no communication with LMP91000
 */
int8_t Gas::ON(float R_gain)
{	
	int answer = 0;
	uint8_t mask;
	
	#ifndef CALIBRATION_MODE
		pinMode(ANA0, OUTPUT);
		digitalWrite(ANA0, HIGH);	
			
		if ((pwrGasPRORegister == 0) || ((WaspRegister & REG_3V3) == 0))
		{
			#if GAS_DEBUG>0
				USB.println(F("GP.3V3 to ON"));
			#endif
			PWR.setSensorPower(SENS_3V3, SENS_ON);
			delay(100);
			BME.ON();
		}
	#endif
	
	pwrGasPRORegister |= (1 << sensor_config.socket);
	
	digitalWrite(sensor_config.power_pin, LOW);
	
	//Enable communication with the AFE
 	digitalWrite(sensor_config.I2C_pin, HIGH);
 	delay(1);
 	readSensorInfo();
	
	#if GAS_DEBUG>1
		showSensorInfo();
		/*USB.println(F("************ Sensor data ************"));
		USB.print(F("Sensor type: "));
		USB.println(sensor_config.sensor_type, DEC);
		USB.print(F("power_pin: "));
		USB.println(sensor_config.power_pin, DEC);
		USB.print(F("I2C_pin: "));
		USB.println(sensor_config.I2C_pin, DEC);
		USB.print(F("m_conc: "));
		USB.println(sensor_config.m_conc);
		USB.print(F("baseline: "));
		USB.println(sensor_config.baseline);
		USB.print(F("val_aux: "));
		USB.println(sensor_config.val_aux);
	
		USB.println(F("Calibration table"));
		for (int x = 0; x < 7; x++)
		{
			USB.print(x, DEC);
			USB.print(F(": "));
			USB.print(sensor_config.calibration[x][0]);
			USB.print(F(" ; "));
			USB.println(sensor_config.calibration[x][1]);
		}*/		
	#endif
 	delay(1000);
	
	answer = configureAFE(R_gain);	
	if (answer == 1)
	{
		// Set bit in pwrGasPRORegister
		pwrGasPRORegister |= (1 << sensor_config.socket);
		sensor_config.tempo = millis();
	}
	else
	{
		// Clear bit in pwrGasPRORegister
		mask = ~(1 << sensor_config.socket);
		pwrGasPRORegister &= mask;
	}
	
	
	return answer;

}

/* Function: 	This function powers off the AFE module and the gases PRO board if necessary without enable the FET transistor of LMP91000
 * Returns: 	pwrGasRegister
 */ 
uint8_t Gas::OFF()
{
	return OFF(0);
}

/* Function: 	This function powers off the AFE module and the gases PRO board if necessary
 * Parameters:	enable_FET: enables FET transistor from LMP91000 chip (only 3 electrode boards)
 * Returns: 	pwrGasRegister
 */ 
uint8_t Gas::OFF(uint8_t enable_FET)
{
	uint8_t mask;
	
	//Enable communication with the AFE
	digitalWrite(sensor_config.I2C_pin, HIGH);
	delay(100);
	
	if (enable_FET == 1)
	{
		LMP.setModeReg(	LMP91000_MODEC_REG_FET_SHORTED, 
						LMP91000_MODEC_REG_PWR_MODE_DEEP_SLEEP);
	}
	else
	{
		LMP.setModeReg(	LMP91000_MODEC_REG_FET_NOT_SHORTED, 
						LMP91000_MODEC_REG_PWR_MODE_DEEP_SLEEP);
	}
	
	// Disable communication
	digitalWrite(sensor_config.I2C_pin, LOW);
	
	// Power off the AFE module
	digitalWrite(sensor_config.power_pin, HIGH);
	
	#ifndef CALIBRATION_MODE
		mask = ~(1 << sensor_config.socket);
		pwrGasPRORegister &= mask;
		
		// If there aren't powered AFE modules, turns off the 3V3 power supply
		if (pwrGasPRORegister == 0x00)
		{					
			#if GAS_DEBUG>0
				USB.println(F("GP.3V3 to OFF"));
			#endif	
			PWR.setSensorPower(SENS_3V3, SENS_OFF);
			pinMode(ANA0, OUTPUT);
			digitalWrite(ANA0, LOW);	
		}
		else if (pwrGasPRORegister == 0x01)
		{
			pinMode(ANA0, OUTPUT);
			digitalWrite(ANA0, LOW);	
		}
	#endif
	
	return pwrGasPRORegister;	
	
}

/* Function: 	This function sets the power mode of LMP91000
 * Parameters:	power_mode: working mode for LMP91000  
 * Returns: 	1 if OK
 */ 
int8_t Gas::setPowerMode(uint8_t power_mode)
{
	return LMP.setModeReg(LMP91000_MODEC_REG_FET_NOT_SHORTED, power_mode);
}

/* Function: 	This function configure the AFE module (LMP91000 and/or MCP4146)
 * Parameters:	R_gain: resistor value for transimpendance stage   
 * Returns: 	1 if OK
 * 				-1 no communication with LMP91000
 */ 
int8_t Gas::configureAFE(float R_gain)
{
	
	uint8_t gain_3E;
	float gain_4E;
	
	// NDIR and pellistor sensors don't need to configure the AFE	
	if ((sensor_config.sensor_type == LEL_AS) || (sensor_config.sensor_type == NDIR_CO2_SS))
	{
		digitalWrite(sensor_config.I2C_pin, LOW);
		return 1;
	}
	
	//Enable communication with the AFE
	digitalWrite(sensor_config.I2C_pin, HIGH);
	
	delay(100);
	

	
	// Check communication with LMP91000
	if (LMP.check() == 0)
	{
		// Communication error
		// Disable communication
		digitalWrite(sensor_config.I2C_pin, LOW);
		#if GAS_DEBUG>0
			USB.println(F("GP.LMP91000 communication error"));
		#endif
		return -1;
	}
	
	// No gain selected
	if (R_gain == -1000)
	{
		if (sensor_config.sensor_type == O3_AS)		// Basic gain for O3 sensor
		{
			gain_4E = MCP_GAIN_2;
		}
		else if (sensor_config.sensor_type == O2_SS)	// Basic gain for O2 sensor
		{
			gain_3E = LMP91000_TIAC_REG_REF_R_GAIN_3K5;
		}
		else											// Basic gain for others
		{
			gain_3E = LMP91000_TIAC_REG_REF_R_GAIN_35K;
		}
	}
	else if ((R_gain > 7) && (sensor_config.sensor_type != O3_AS))	// Incorrect gain for 3 electrode sensors
	{
		gain_3E = LMP91000_TIAC_REG_REF_R_GAIN_35K;
	}
	else
	{
		gain_3E = R_gain;
		gain_4E = R_gain;
	}
	
	// Configure LMP91000 to use an specific sensor
	// Pellistors don't use the LMP91000
	switch(sensor_config.sensor_type)
	{		
		case CL2_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0, 
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case CO_SS_SEC:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0, 
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case ETO_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_14,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case H2_SS_SEC:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case H2S_SS_SEC:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_10,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case HCL_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_10,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case HCN_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case NH3_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case NO_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_14,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case NO2_SS_CLE:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case O2_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_INTERNAL_REF,
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_18,
								LMP91000_REFC_REG_REF_POLARITY_NEGATIVE);
		/*	LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF,
								LMP91000_REFC_REG_REF_INT_Z_67,
								LMP91000_REFC_REG_REF_BIAS_PERC_24,
								LMP91000_REFC_REG_REF_POLARITY_NEGATIVE);*/
			break;
			
		case PH3_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
			
		case SO2_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;
						
		case O3_AS:
			LMP.setTIAConReg(LMP91000_TIAC_REG_REF_R_GAIN_EXT, LMP91000_TIAC_REG_REF_R_LOAD_33R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			setAmplifier(WORKING_ELECTRODE, gain_4E);
			setAmplifier(AUXILIARY_ELECTRODE, gain_4E);
			break;
			
		case CALIBRATION_3E:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_14,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);	
			break;
			
		case CALIBRATION_4E:
			LMP.setTIAConReg(LMP91000_TIAC_REG_REF_R_GAIN_EXT, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF, 
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_14,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);			
			break;
	}

	LMP.setModeReg(	LMP91000_MODEC_REG_FET_NOT_SHORTED, 
					LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPERIOMETRIC);
			
	// Disable communication
	digitalWrite(sensor_config.I2C_pin, LOW);
	
	return 1;
	
}


//! MEASURE FUNCTIONS
/* Function: 	This function reads temperature
 * Parameters:	sensor: '0' for LMP91000, '1' for BME280
 * Returns: 	The temperature, -1000 if error
*/
float Gas::getTemp()
{	
	float temp = -1000;
	
	temp = getTemp(1);
	
	if (temp == -1000)
	{
		// BME 280 error, read from LMP91000
		temp = getTemp(0);
	}
	
    return temp;
}

/* Function: 	This function reads temperature from an specific sensor
 * Parameters:	sensor: '0' for LMP91000, '1' for BME280
 * Returns: 	The temperature, -1000 if error
*/
float Gas::getTemp(bool sensor)
{
	uint8_t last_mode;
    float temp;	
	
	if (sensor == 0)
	{
	   //Enable communication with the AFE
		digitalWrite(sensor_config.I2C_pin, HIGH);
		delay(100);		
		
		#if GAS_DEBUG>0
			USB.println(F("GP.Reading LMP91000 internal "));
		#endif
			
		last_mode = LMP.getModeReg();
		LMP.setModeReg(	LMP91000_MODEC_REG_FET_NOT_SHORTED, 
						LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_ON);
		
		temp = 0;
		for ( int i =0; i < 4; i++)
		{        
			temp += (MCP.readADC(MCP3421_RES_12_BIT, MCP3421_GAIN_1, MCP3421_VOLTS));  
			#if GAS_DEBUG>1
				USB.print(F("GP.Measure "));
				USB.print(i+1, DEC);
				USB.print(F("/4 from ADC: "));
				USB.print(temp);
				USB.println(F("mV"));			
			#endif
		}

		temp/=4;
		
		#if GAS_DEBUG>0
			USB.print(F("GP.V temp: "));
			USB.print(temp);
			USB.print(F(" mV"));	
		#endif
		temp = (temp - 1875)*(-0.1183) - 40; //(80+40)/(861-1875)
		
		#if GAS_DEBUG>0
			USB.print(F(" || Temperature: "));
			USB.print(temp);
			USB.println(F(" ºC"));			
		#endif
			
		
		LMP.setModeReg(LMP91000_MODEC_REG_FET_NOT_SHORTED, last_mode);
		// Disable communication with LMP91000
		digitalWrite(sensor_config.I2C_pin, LOW);
	}
	else
	{
		#if GAS_DEBUG>0
			USB.println(F("GP.Reading BME280"));
		#endif
		temp = BME.getTemperature(BME280_OVERSAMP_1X, 0);	
	}
	
    return temp;

}

/* Function:	This function reads relative humidity from BME280
 * Returns:		The relative humidity, -1000 if error
*/
float Gas::getHumidity()
{	
    return BME.getHumidity(BME280_OVERSAMP_1X);
}

/* Function:	This function reads pressure from BME280
 * Returns:		The pressure, -1000 if error
*/
float Gas::getPressure()
{	
    return BME.getPressure(BME280_OVERSAMP_1X, 0);
}

/* Function: 	This function reads concentration value with default parameters (16bit ADC, BME280 temperature and compensated measure for O3 sensor)
 * Returns: 	The concetration value in ppm / %LEL, -1000 if error.
*/
float Gas::getConc()
{
	float BME280_temp;
	
	BME280_temp = BME.getTemperature(BME280_OVERSAMP_1X, 0);	
	return getConc(MCP3421_HIGH_RES, BME280_temp, COMPENSATED);	
}

/* Function: 	This function reads concentration value with default parameters (BME280 temperature and compensated measure for O3 sensor)
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * Returns: 	The concetration value in ppm / %LEL, -1000 if error.
*/
float Gas::getConc(uint8_t resolution)
{
	float BME280_temp;
	
	BME280_temp = BME.getTemperature(BME280_OVERSAMP_1X, 0);	
	return getConc(resolution, BME280_temp, COMPENSATED);	
}

/* Function: 	This function reads concentration value (used to select an specific eletrode in 4 electrode sensors)
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * 				electrode: electrode to read (WORKING_ELECTRODE or AUXILIARY_ELECTRODE)   
 * Returns: 	The concetration value in ppm / %LEL, -1000 if error.
*/
float Gas::getConc(uint8_t resolution, uint8_t electrode)
{
	float BME280_temp;
	
	BME280_temp = BME.getTemperature(BME280_OVERSAMP_1X, 0);	
	return getConc(resolution, BME280_temp, electrode);	
}

/* Function: 	This function reads concentration value (base function)
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * 				temperature: ambient temperature for sensor compensation (-1000 if doesn't needed)
 * 				electrode: electrode to read (WORKING_ELECTRODE or AUXILIARY_ELECTRODE)   
 * Returns: 	The concetration value in ppm / %LEL
 * 				-1 if the sensors is not initializated
 * 				-1000 if error.
*/
float Gas::getConc(uint8_t resolution, float temperature, uint8_t electrode)
{

    float V_conc = 0;	
	float conc=0, conc_aux=0;
	float aux_val;
	float aux_resistor;
	int r_gain_LMP;
	
	float V_ref=0, R_gain;
	
	// Before to measure, check if the sensor is properly initializated
	if ((pwrGasPRORegister & (1 << sensor_config.socket)) == 0)
	{
		
		#if GAS_DEBUG>0
			USB.println(F("GP.Error,sensor not started"));
		#endif
		// If not return -1		
		return -1;		
	}
	

	
    //Enable communication with the AFE
	digitalWrite(sensor_config.I2C_pin, HIGH);
	delay(100);
	
	switch (sensor_config.sensor_type)
	{
		
		/***************************************
		* 	3-ELECTRODE AMPERIOMETRIC BOARD		*
		***************************************/
		case CL2_SS:
		case CO_SS_SEC:
		case ETO_SS:
		case H2_SS_SEC:
		case H2S_SS_SEC:
		case HCL_SS:
		case HCN_SS:
		case NH3_SS:
		case NO_SS:
		case NO2_SS_CLE:
		case O2_SS:
		case PH3_SS:
		case SO2_SS:
		case CALIBRATION_3E:		
			
			#if GAS_DEBUG>0
				USB.print(F("GP.Reading 3E sensor "));
				USB.print(sensor_config.sensor_type, DEC);
				USB.print(F("; t: "));
				USB.println(millis() - sensor_config.tempo, DEC);
			#endif
			// Selects amperiometric mode
			LMP.setModeReg(	LMP91000_MODEC_REG_FET_NOT_SHORTED, 
							LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPERIOMETRIC);
			delay(100);
			
			V_conc = 0;    
			for ( int i = 0; i < 4; i++)
			{
				// Reads the ADC
				aux_val = (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));   
				
				#if GAS_DEBUG>1
					USB.print(F("GP.Measure "));
					USB.print(i+1, DEC);
					USB.print(F("/4 from ADC: "));
					USB.print(aux_val);
					USB.println(F(" mV"));
				#endif
					
				V_conc += aux_val;     
			}			
	
			V_conc /=4; 
						
			
			// Gets the Vref
			switch (LMP.getRefSource())
			{
				case 0:
					V_ref = 3300;
					break;
				case 1:
					V_ref = 2048;
					break;
			}
			
			switch (LMP.getInternalZero())
			{
				case 0:
					V_ref *= 0.2;
					break;
				case 1:
					V_ref *= 0.5;
					break;
				case 2:
					V_ref *= 0.67;
					break;
				case 3:
					V_ref *= 1;
					break;
			}
			
			// Gets the Rgain used
			r_gain_LMP = LMP.getRgain();
			switch (r_gain_LMP)
			{
				case 1:
					R_gain = 2750;
					break;
				case 2:
					R_gain = 3500;
					break;
				case 3:
					R_gain = 7000;
					break;
				case 4:
					R_gain = 14000;
					break;
				case 5:
					R_gain = 35000;
					break;
				case 6:
					R_gain = 120000;
					break;
				case 7:
					R_gain = 350000;
					break;
				default:
					R_gain = 0;
			}
			
			
			// Disable communication with AFE
			digitalWrite(sensor_config.I2C_pin, LOW);			
			
			#if GAS_DEBUG>0
				USB.print(F("GP.V_conc: "));
				USB.print(V_conc);
				USB.print(F(" mV"));	
				
				USB.print(F(" || V_ref: "));
				USB.print(V_ref);
				USB.print(F(" mV"));	
				
				USB.print(F(" || R_gain: "));
				USB.print(R_gain, DEC);
				USB.println(F(" Ohms"));
			#endif				
				
			#if GAS_DEBUG>1
				USB.print(F("GP.Compensation values: "));
				USB.print(sensor_config.calibration[r_gain_LMP-1][0]);
				USB.print(F("; "));
				USB.println(sensor_config.calibration[r_gain_LMP-1][1]);
				
				USB.print(F("GP.m_conc: "));
				USB.print(sensor_config.m_conc);
				USB.print(F(" nA/ppm || baseline: "));
				USB.print(sensor_config.baseline);
				USB.println(F(" nA"));		
			#endif
			
			conc = (V_conc - V_ref); 						// Vconc(mV) - Vzero(mV)
			
			conc = (conc / R_gain) * 1000;					// V(mV) --> I(uA)			
			
			conc =  ((conc + sensor_config.calibration[r_gain_LMP-1][0]) / (sensor_config.calibration[r_gain_LMP-1][1]));		// Adjust resistor
			
			
			#if GAS_DEBUG>0
				USB.print(F("GP.I: "));
				USB.print(conc);
				USB.println(F(" uA"));
			#endif
			if ((sensor_config.sensor_type == CL2_SS) ||
				(sensor_config.sensor_type == NO2_SS_CLE) ||
				(sensor_config.sensor_type == O2_SS))
			{
				conc *= -1;				
			}
					
			conc -= (sensor_config.baseline / 1000);		// Subtracts baseline current			
			
			conc *= getSensitivityTempComp(temperature);	// Output current temperature compensation			
			
			conc = (conc * 1000) / sensor_config.m_conc;	// I(nA) --> concentración(ppm)	
			
			conc -= getBaselineTempComp(temperature);		// Baseline temperature compensation
			
			if (conc < 0)
			{
				conc = 0;
			}
		
			break;
		

		/***************************************
		* 			PELLISTOR BOARD				*
		***************************************/
		case LEL_AS:
		case CALIBRATION_PEL:
			
			#if GAS_DEBUG>0
				USB.print(F("GP.Reading pellistor sensor; t:"));
				USB.println(millis() - sensor_config.tempo, DEC);
			#endif
				
			V_conc = 0;    
			for ( int i = 0; i < 4; i++)
			{
				// Reads the ADC
				aux_val = (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));   
				
				#if GAS_DEBUG>1
					USB.print(F("GP.Measure "));
					USB.print(i+1, DEC);
					USB.print(F("/4 from ADC: "));
					USB.print(aux_val);
					USB.println(F(" mV"));			
				#endif
					
				V_conc += aux_val;     
			}			
			
			// Disable communication
			digitalWrite(sensor_config.I2C_pin, LOW);
			
			V_conc /= -4; 
			
			#if GAS_DEBUG>0				
				USB.print(F("GP.V_conc: "));
				USB.print(V_conc);
				USB.println(F(" mV"));		
			#endif
			
			#if GAS_DEBUG>1				
				USB.print(F("GP.m_conc: "));
				USB.print(sensor_config.m_conc);
				USB.print(F(" mV/% || baseline: "));
				USB.print(sensor_config.baseline);
				USB.println(F(" mV"));		
			#endif
				
			V_conc = (V_conc - sensor_config.calibration[0][0]) / sensor_config.calibration[0][1];
			
			V_conc -= sensor_config.baseline;		// Vconc(mV) - Voffset(mV) sensor	
			
			conc -= getBaselineTempComp(temperature);	// Baseline temperature compensation	
				
			V_conc *= getSensitivityTempComp(temperature);	// Output current temperature compensation
				
			conc = V_conc / (sensor_config.m_conc);	// conc(mV) --> concentración(% LEL)
			
			if (conc < 0)
			{
				conc = 0;
			}
			break;
			
		case NDIR_CO2_SS:
		case CALIBRATION_NDIR:
			
			#if GAS_DEBUG>0
				USB.print(F("GP.Reading NDIR sensor; t: "));
				USB.println(millis() - sensor_config.tempo, DEC);
			#endif
			
			V_conc = 0;    
			for ( int i = 0; i < 4; i++)
			{
				// Reads the ADC
				aux_val = (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));   
				
				#if GAS_DEBUG>1
					USB.print(F("GP.Measure "));
					USB.print(i+1, DEC);
					USB.print(F("/4 from ADC: "));
					USB.print(aux_val);
					USB.println(F(" mV"));
				#endif
					
				V_conc += aux_val;     
			}			
			
			// Disable communication
			digitalWrite(sensor_config.I2C_pin, LOW);
			
			V_conc /= 4; 
			
			#if GAS_DEBUG>0				
				USB.print(F("GP.V_conc: "));
				USB.print(V_conc);
				USB.println(F(" mV"));		
			#endif
			
			#if GAS_DEBUG>1	
				USB.print(F("GP.m_conc: "));
				USB.print(sensor_config.m_conc);
				USB.print(F(" mV/ppm || baseline: "));
				USB.print(sensor_config.baseline);
				USB.println(F(" mV"));		
			#endif		
				
			// NDIR sensor from Solidsense doesn't need temperature compensation
				
			V_conc = (V_conc - sensor_config.calibration[0][0]) / sensor_config.calibration[0][1];
			
			V_conc -= sensor_config.baseline;		// Vconc(mV) - Voffset(mV) sensor		
			
			conc = V_conc * sensor_config.m_conc;	// conc(mV) --> concentración(% LEL)
			
			if (conc < 0)
			{
				conc = 0;
			}
			break;
			
		
		/***************************************
		* 	4-ELECTRODE AMPERIOMETRIC BOARD		*
		***************************************/		
		case O3_AS:
		case CALIBRATION_4E:
			#if GAS_DEBUG>0
				USB.print(F("GP.Reading 4E sensor; t: "));
				USB.println(millis() - sensor_config.tempo, DEC);
			#endif
			// Selects amperiometric mode
			LMP.setModeReg(	LMP91000_MODEC_REG_FET_NOT_SHORTED, 
							LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPERIOMETRIC);
			
			// Measuring
			conc = 0;
			conc_aux = 0;
			
			if ((electrode == WORKING_ELECTRODE) || (electrode == COMPENSATED))
			{
				#if GAS_DEBUG>0
					USB.println(F("GP.Reading working electrode"));
				#endif
					
				aux_resistor = getAmplifier(AUXILIARY_ELECTRODE);
				setAmplifier(AUXILIARY_ELECTRODE, 0);
					
				V_conc = 0;    
				for ( int i = 0; i < 8; i++)
				{
					// Reads the ADC
					
					delay(100);
					digitalWrite(sensor_config.I2C_pin, HIGH);
					
					aux_val = (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));   
					
					#if GAS_DEBUG>1
						USB.print(F("Measure "));
						USB.print(i+1, DEC);
						USB.print(F("/8 from ADC: "));
						USB.print(aux_val);
						USB.println(F(" mV"));
					#endif
						
					V_conc += aux_val;     
				}			
		
				V_conc /=8;  		
				
				setAmplifier(AUXILIARY_ELECTRODE, aux_resistor);
				
				R_gain = getAmplifier(WORKING_ELECTRODE);
				
				#if GAS_DEBUG>0
					USB.print(F("GP.V_conc: "));
					USB.print(V_conc);					
					USB.print(F(" mV || R_gain: "));
					USB.print(R_gain, DEC);
					USB.println(F(" Ohms"));
				#endif
					
				#if GAS_DEBUG>1
					USB.print(F("GP.Compensation values: "));
					USB.print(sensor_config.calibration[0][0]);
					USB.print(F("; "));
					USB.println(sensor_config.calibration[0][1]);
					
					USB.print(F("GP.m_conc: "));
					USB.print(sensor_config.m_conc);
					USB.print(F(" nA/ppm || baseline: "));
					USB.print(sensor_config.baseline);
					USB.println(F(" nA"));		
				#endif

				
				conc = (V_conc / (R_gain)) * 1000;			// V(mV) --> I(uA)
				
				conc =  ((conc + sensor_config.calibration[0][0]) / (sensor_config.calibration[0][1]));
							
				conc *= -1;

				#if GAS_DEBUG>0
					USB.print(F("GP.Iwe: "));
					USB.print(conc);
					USB.println(F(" uA"));
				#endif	
					
				conc -= (sensor_config.baseline / 1000);	// Subtracts baseline current
						
				conc -= getBaselineTempComp(temperature);		// Baseline temperature compensation
				
				//conc *= getSensitivityTempComp(temperature);	// Output current temperature compensation
				
				conc = (conc * 1000) / sensor_config.m_conc;	// I(uA) --> concentración(ppm)
				
				#if GAS_DEBUG>0
					USB.print(F("GP.conc: "));
					USB.print(conc);
					USB.println(F(" ppm"));
				#endif	
				
				if (conc < 0)
				{
					conc = 0;
				}
				
			}
			
			if ((electrode == AUXILIARY_ELECTRODE) || (electrode == COMPENSATED))	
			{
				#if GAS_DEBUG>0
					USB.println(F("GP.Reading auxiliary electrode"));
				#endif
					
				aux_resistor = getAmplifier(WORKING_ELECTRODE);
				setAmplifier(WORKING_ELECTRODE, 0);
					
				V_conc = 0;    
				for ( int i = 0; i < 8; i++)
				{
					// Reads the ADC
					delay(100);
					digitalWrite(sensor_config.I2C_pin, HIGH);
					
					aux_val = (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));   
					
					#if GAS_DEBUG>1
						USB.print(F("GP.Measure "));
						USB.print(i+1, DEC);
						USB.print(F("/8 from ADC: "));
						USB.print(aux_val);
						USB.println(F(" mV"));
					#endif
						
					V_conc += aux_val;     
				}			
		
				V_conc /=8;  
				
				setAmplifier(WORKING_ELECTRODE, aux_resistor);
				
				R_gain = getAmplifier(AUXILIARY_ELECTRODE);
				
				#if GAS_DEBUG>0
					USB.print(F("GP.V_conc: "));
					USB.print(V_conc);					
					USB.print(F(" mV || R_gain: "));
					USB.print(R_gain, DEC);
					USB.println(F(" Ohms"));
				#endif
					
				#if GAS_DEBUG>1
					USB.print(F("GP.Compensation values: "));
					USB.print(sensor_config.calibration[0][0]);
					USB.print(F("; "));
					USB.println(sensor_config.calibration[0][1]);
					
					USB.print(F("GP.val_aux: "));
					USB.print(sensor_config.val_aux);
					USB.print(F(" nA/ppm || baseline: "));
					USB.print(sensor_config.baseline);
					USB.println(F(" nA"));		
				#endif
				
				conc_aux = (V_conc / (R_gain)) * 1000;				// V(mV) --> I(uA)

				conc_aux =  ((conc_aux + sensor_config.calibration[1][0]) / (sensor_config.calibration[1][1]));
				#if GAS_DEBUG>0
					USB.print(F("GP.Iae: "));
					USB.print(conc_aux);
					USB.println(F(" uA"));
				#endif	
				conc_aux -= (sensor_config.baseline / 1000);	// Subtracts baseline current
									
				//conc_aux -= getBaselineTempComp(temperature);			// Baseline temperature compensation
						
				//conc *= getSensitivityTempComp(temperature);		// Output current temperature compensation
				
				conc_aux = (conc_aux * 1000) / sensor_config.val_aux;	// I(uA) --> concentración(ppm)
				
				#if GAS_DEBUG>0
					USB.print(F("GP.conc_aux: "));
					USB.print(conc_aux);
					USB.println(F(" ppm"));
				#endif	
				if (conc_aux < 0)
				{
					conc_aux = 0;
				}
				
			}
			
			// Compose concentration
			if (electrode == AUXILIARY_ELECTRODE)
			{
				conc = conc_aux;
			}
			else
			{
				conc = conc - conc_aux;
				
			}
			
			if (conc < 0)
			{
				conc = 0;
			}
							
			// Disable communication with AFE
			digitalWrite(sensor_config.I2C_pin, LOW);	
		
			break;
		
		
	}
	
    
    return conc;

}

/* Function: 	This function changes the gain and the Vref of the AFE module
 * 				when the signal is into the limits of the ADC
 * Returns: 	high nibble: steps changed in Vref
 * 				low nibble: steps changed in Rgain
*/
int8_t Gas::autoGain()
{
	float v_ADC = 0;
	float v_ref = 0;
	float upper_range = 0;
	float lower_range = 0;
	int r_gain;
	int vref_reg;
	int8_t r_steps = 0;
	int8_t v_steps = 0;
	bool end;
	uint8_t process_reg = 0;
	uint8_t mask;
	float aux_resistor;

	
	//Enable communication with the AFE
	digitalWrite(sensor_config.I2C_pin, HIGH);
	delay(100);
	
	switch (sensor_config.sensor_type)
	{
		/***************************************
		* 	3-ELECTRODE AMPERIOMETRIC BOARD		*
		***************************************/
		case CL2_SS:
		case CO_SS_SEC:
		case ETO_SS:
		case H2_SS_SEC:
		case H2S_SS_SEC:
		case HCL_SS:
		case HCN_SS:
		case NH3_SS:
		case NO_SS:
		case NO2_SS_CLE:
		case O2_SS:
		case PH3_SS:
		case SO2_SS:
		case CALIBRATION_3E:
			/*
			*	2048mV	|----------------------------------------	
			*			|					UHV						
			*			|----------------------------------------	(2048 - Vref) * MAX_RANGE_FACTOR
			*			|					UMV						
			*			|----------------------------------------	(2048 - Vref) * MIN_RANGE_FACTOR
			*			|					ULV						
			*	Vref	|----------------------------------------	
			*			|					LLV						
			*			|----------------------------------------	(0 - Vref) * MIN_RANGE_FACTOR
			*			|					LMV						
			*			|----------------------------------------	(0 - Vref) * MAX_RANGE_FACTOR
			*			|					LHV						
			*		0mV	|----------------------------------------	
			*/
			
			r_steps = 0;
			v_steps = 0;
			#ifdef GAS_PRO_AUTOGAIN_DEBUG
				USB.println(F("GP.Starting autogain proccess for 3E"));
			#endif

			// Gets the Vref
			switch (LMP.getRefSource())
			{
				case 0:
					v_ref = 3300;
					break;
				case 1:
					v_ref = 2048;
					break;
			}
			
			switch (LMP.getInternalZero())
			{
				case 0:
					v_ref *= 0.2;
					break;
				case 1:
					v_ref *= 0.5;
					break;
				case 2:
					v_ref *= 0.67;
					break;
				case 3:
					v_ref *= 1;
					break;
			}
			
			upper_range = 2048 - v_ref;
			lower_range = 0 - v_ref;
				
			#ifdef GAS_PRO_AUTOGAIN_DEBUG
				USB.print(F("GP.Upper limits: "));
				USB.print(MAX_RANGE_FACTOR * upper_range, DEC);
				USB.print(F("; "));
				USB.println(MIN_RANGE_FACTOR * upper_range, DEC);
				USB.print(F("GP.Lower limits: "));
				USB.print(MAX_RANGE_FACTOR * lower_range, DEC);
				USB.print(F("; "));
				USB.println(MIN_RANGE_FACTOR * lower_range, DEC);
			#endif
					
			do{
				// Reads the ADC
				v_ADC = (MCP.readADC(	MCP3421_MEDIUM_RES,
										MCP3421_GAIN_1,
										MCP3421_VOLTS)); 
				v_ADC += (MCP.readADC(	MCP3421_MEDIUM_RES,
										MCP3421_GAIN_1,
										MCP3421_VOLTS));	
				v_ADC /=2; 	
				
				#ifdef GAS_PRO_AUTOGAIN_DEBUG				
					USB.print(F("GP.Vref:"));
					USB.print(v_ref, DEC);
					USB.print(F(" | ADC value:"));
					USB.print(v_ADC, DEC);
					USB.print(F(" | ADC-vref value:"));
					USB.println(v_ADC - v_ref, DEC);
				#endif
					
				v_ADC = (v_ADC - v_ref); 	// VADC(mV) - Vzero(mV)

	
				if (v_ADC >= MAX_RANGE_FACTOR * upper_range)		// UHV
				{
					process_reg &= 0x03;
					mask = 1 << UHV;
					process_reg |= mask;
				} 
				else if ((v_ADC < (MAX_RANGE_FACTOR * upper_range)) && (v_ADC >= (MIN_RANGE_FACTOR * upper_range)))	//UMV
				{
					process_reg &= 0x03;
					mask = 1 << UMV;
					process_reg |= mask;
				} 
				else if ((v_ADC < (MIN_RANGE_FACTOR * upper_range)) && (v_ADC >= 0))	//ULV
				{
					process_reg &= 0x03;
					mask = 1 << ULV;
					process_reg |= mask;					
				} 
				else if ((v_ADC < 0) && (v_ADC >= (MIN_RANGE_FACTOR * lower_range)))	//LLV
				{	
					process_reg &= 0x03;
					mask = 1 << LLV;
					process_reg |= mask;	
				}
				else if ((v_ADC < (MIN_RANGE_FACTOR * lower_range)) && (v_ADC >= (MAX_RANGE_FACTOR * lower_range)))	//LMV
				{
					process_reg &= 0x03;
					mask = 1 << LMV;
					process_reg |= mask;	
				} 	
				else	// LHV
				{
					process_reg &= 0x03;
					mask = 1 << LHV;
					process_reg |= mask;	
				}
				
				r_gain = LMP.getRgain();
				if (r_gain == 7)
				{	
					process_reg &= 0xFC;
					process_reg |= 0x02;	
				}
				else if (r_gain == 1)
				{					
					process_reg &= 0xFC;
					process_reg |= 0x01;	
				}
				else
				{
					process_reg &= 0xFC;
				}
				
				#ifdef GAS_PRO_AUTOGAIN_DEBUG	
					USB.print(F("GP.process_reg: "));
					USB.println(process_reg, BIN);
				#endif
				
				switch (process_reg)
				{
					case 0x80:	//Decreases gain
					case 0x82:
					case 0x04:
					case 0x06:						
						#ifdef GAS_PRO_AUTOGAIN_DEBUG	
							USB.println(F("GP.Decresaing Rgain"));
						#endif
						r_gain--;
						LMP.setRgain(r_gain);
						r_steps--;
						end = 0;
						break;
						
					case 0x20:	//Increases gain
					case 0x21:
					case 0x10:
					case 0x11:
						#ifdef GAS_PRO_AUTOGAIN_DEBUG	
							USB.println(F("GP.Incresaing Rgain"));
						#endif
						r_gain++;
						LMP.setRgain(r_gain);
						r_steps++;
						end = 0;
						break;
						
					case 0x81:	//Decreases Vref
						vref_reg = LMP.getInternalZero();
						if (vref_reg == 0)
						{
							end = 1;
							#ifdef GAS_PRO_AUTOGAIN_DEBUG	
								USB.println(F("GP.Vref low limit reached"));
							#endif
						}
						else
						{
							#ifdef GAS_PRO_AUTOGAIN_DEBUG	
								USB.println(F("GP.Decresaing Vref"));
							#endif
							LMP.setInternalZero(vref_reg - 1);
							v_steps--;
						}			
									// Gets the Vref
						switch (LMP.getRefSource())
						{
							case 0:
								v_ref = 3300;
								break;
							case 1:
								v_ref = 2048;
								break;
						}
						
						switch (LMP.getInternalZero())
						{
							case 0:
								v_ref *= 0.2;
								break;
							case 1:
								v_ref *= 0.5;
								break;
							case 2:
								v_ref *= 0.67;
								break;
							case 3:
								v_ref *= 1;
								break;
						}
													
						upper_range = 2048 - v_ref;
						lower_range = 0 - v_ref;
						
						#ifdef GAS_PRO_AUTOGAIN_DEBUG	
							USB.print(F("GP.Upper limits: "));
							USB.print(MAX_RANGE_FACTOR * upper_range, DEC);
							USB.print(F("; "));
							USB.println(MIN_RANGE_FACTOR * upper_range, DEC);
							USB.print(F("GP.Lower limits: "));
							USB.print(MAX_RANGE_FACTOR * lower_range, DEC);
							USB.print(F("; "));
							USB.println(MIN_RANGE_FACTOR * lower_range, DEC);
						#endif
						
						break;
						
					case 0x05:	//Increases Vref
						vref_reg = LMP.getInternalZero();
						if (vref_reg == 2)
						{
							end = 1;
							#ifdef GAS_PRO_AUTOGAIN_DEBUG	
								USB.println(F("GP.Vref high limit reached"));
							#endif
						}
						else
						{
							#ifdef GAS_PRO_AUTOGAIN_DEBUG	
								USB.println(F("GP.Incresaing Vref"));
							#endif
							LMP.setInternalZero(vref_reg + 1);
							v_steps++;
						}
						
						switch (LMP.getRefSource())
						{
							case 0:
								v_ref = 3300;
								break;
							case 1:
								v_ref = 2048;
								break;
						}
						
						switch (LMP.getInternalZero())
						{
							case 0:
								v_ref *= 0.2;
								break;
							case 1:
								v_ref *= 0.5;
								break;
							case 2:
								v_ref *= 0.67;
								break;
							case 3:
								v_ref *= 1;
								break;
						}
							
						upper_range = 2048 - v_ref;
						lower_range = 0 - v_ref;
						
						#ifdef GAS_PRO_AUTOGAIN_DEBUG	
							USB.print(F("GP.Upper limits: "));
							USB.print(MAX_RANGE_FACTOR * upper_range, DEC);
							USB.print(F("; "));
							USB.println(MIN_RANGE_FACTOR * upper_range, DEC);
							USB.print(F("GP.Lower limits: "));
							USB.print(MAX_RANGE_FACTOR * lower_range, DEC);
							USB.print(F("; "));
							USB.println(MIN_RANGE_FACTOR * lower_range, DEC);
						#endif
						
						break;
						
					case 0x40:	//End
					case 0x41:
					case 0x42:
					case 0x22:
					case 0x12:
					case 0x08:
					case 0x09:
					case 0x0A:
					default:
						end = 1;
						break;
					
				}
	
			}while(end == 0);	
			
			break;
		

		/***************************************
		* 			PELLISTOR BOARD				*
		***************************************/
		case LEL_AS:
		case CALIBRATION_PEL:
			

			break;
			
		case NDIR_CO2_SS:
		case CALIBRATION_NDIR:

			break;
			
		
		/***************************************
		* 	4-ELECTRODE AMPERIOMETRIC BOARD		*
		***************************************/		
		case O3_AS:
		case CALIBRATION_4E:	
			/*
			*	2048mV	|----------------------------------------	
			*			|					UHV						
			*			|----------------------------------------	2048 * MAX_RANGE_FACTOR
			*			|					UMV						
			*			|----------------------------------------	2048 * MIN_RANGE_FACTOR
			*			|					ULV						
			*	0		|----------------------------------------	
			*			|					LLV						
			*			|----------------------------------------	-2048 * MIN_RANGE_FACTOR
			*			|					LMV						
			*			|----------------------------------------	-2048 * MAX_RANGE_FACTOR
			*			|					LHV						
			*	-2048mV	|----------------------------------------	
			*/		
			r_steps = 0;
			v_steps = 0;
			#ifdef GAS_PRO_AUTOGAIN_DEBUG
				USB.println(F("GP.Starting autogain proccess for 4E"));
			#endif
			
			upper_range = 2048;
			lower_range = -2048;
				
			#ifdef GAS_PRO_AUTOGAIN_DEBUG
				USB.print(F("GP.Upper limits: "));
				USB.print(MAX_RANGE_FACTOR * upper_range, DEC);
				USB.print(F("; "));
				USB.println(MIN_RANGE_FACTOR * upper_range, DEC);
				USB.print(F("GP.Lower limits: "));
				USB.print(MAX_RANGE_FACTOR * lower_range, DEC);
				USB.print(F("; "));
				USB.println(MIN_RANGE_FACTOR * lower_range, DEC);
			#endif
					
			do{
				
				aux_resistor = getAmplifier(AUXILIARY_ELECTRODE);
				setAmplifier(AUXILIARY_ELECTRODE, 0);
				delay(10);
				// Reads the ADC
				v_ADC = (MCP.readADC(	MCP3421_MEDIUM_RES,
										MCP3421_GAIN_1,
										MCP3421_VOLTS)); 
				v_ADC += (MCP.readADC(	MCP3421_MEDIUM_RES,
										MCP3421_GAIN_1,
										MCP3421_VOLTS));	
				v_ADC /=2;
				
				setAmplifier(AUXILIARY_ELECTRODE, aux_resistor);
				
				#ifdef GAS_PRO_AUTOGAIN_DEBUG
					USB.print(F("GP.ADC value:"));
					USB.println(v_ADC , DEC);
				#endif
	
				if (v_ADC >= MAX_RANGE_FACTOR * upper_range)		// UHV
				{
					process_reg &= 0x03;
					mask = 1 << UHV;
					process_reg |= mask;
				} 
				else if ((v_ADC < (MAX_RANGE_FACTOR * upper_range)) && (v_ADC >= (MIN_RANGE_FACTOR * upper_range)))	//UMV
				{
					process_reg &= 0x03;
					mask = 1 << UMV;
					process_reg |= mask;
				} 
				else if ((v_ADC < (MIN_RANGE_FACTOR * upper_range)) && (v_ADC >= 0))	//ULV
				{
					process_reg &= 0x03;
					mask = 1 << ULV;
					process_reg |= mask;					
				} 
				else if ((v_ADC < 0) && (v_ADC >= (MIN_RANGE_FACTOR * lower_range)))	//LLV
				{	
					process_reg &= 0x03;
					mask = 1 << LLV;
					process_reg |= mask;	
				}
				else if ((v_ADC < (MIN_RANGE_FACTOR * lower_range)) && (v_ADC >= (MAX_RANGE_FACTOR * lower_range)))	//LMV
				{
					process_reg &= 0x03;
					mask = 1 << LMV;
					process_reg |= mask;	
				} 	
				else	// LHV
				{
					process_reg &= 0x03;
					mask = 1 << LHV;
					process_reg |= mask;	
				}
				
				aux_resistor = getAmplifier(WORKING_ELECTRODE);
				aux_resistor = round( aux_resistor / 10000) * 10000;
				if (aux_resistor == 100000.0)
				{	
					process_reg &= 0xFC;
					process_reg |= 0x02;	
					aux_resistor = 100000;
				}
				else if (aux_resistor == 80000.0)
				{
					aux_resistor = 80000;
				}
				else if (aux_resistor == 60000.0)
				{
					aux_resistor = 60000;
				}
				else if (aux_resistor == 40000.0)
				{
					aux_resistor = 40000;
				}
				else if (aux_resistor == 20000.0)
				{					
					process_reg &= 0xFC;
					process_reg |= 0x01;	
					aux_resistor = 20000;
				}
				else
				{
					process_reg &= 0xFC;
				}
				
				#ifdef GAS_PRO_AUTOGAIN_DEBUG	
					USB.print(F("process_reg: "));
					USB.println(process_reg, BIN);
				#endif
				
				switch (process_reg)
				{
					case 0x80:	//Decreases gain
					case 0x82:
					case 0x04:
					case 0x06:						
						#ifdef GAS_PRO_AUTOGAIN_DEBUG	
							USB.println(F("GP.Decresaing Rgain"));
						#endif
						aux_resistor -= 20000;
						setAmplifier(WORKING_ELECTRODE, aux_resistor);
						setAmplifier(AUXILIARY_ELECTRODE, aux_resistor);
						r_steps--;
						end = 0;
						break;
						
					case 0x20:	//Increases gain
					case 0x21:
					case 0x10:
					case 0x11:
						#ifdef GAS_PRO_AUTOGAIN_DEBUG	
							USB.println(F("GP.Incresaing Rgain"));
						#endif
						aux_resistor += 20000;
						setAmplifier(WORKING_ELECTRODE, aux_resistor);
						setAmplifier(AUXILIARY_ELECTRODE, aux_resistor);
						r_steps++;
						end = 0;
						break;
						
					case 0x81:	//Decreases Vref
						vref_reg = LMP.getInternalZero();
						if (vref_reg == 0)
						{
							end = 1;
							#ifdef GAS_PRO_AUTOGAIN_DEBUG	
								USB.println(F("GP.Vref low limit reached"));
							#endif
						}
						else
						{
							#ifdef GAS_PRO_AUTOGAIN_DEBUG	
								USB.println(F("GP.Decresaing Vref"));
							#endif
							LMP.setInternalZero(vref_reg - 1);
							v_steps--;
						}
						
						break;
						
					case 0x05:	//Increases Vref
						vref_reg = LMP.getInternalZero();
						if (vref_reg == 2)
						{
							end = 1;
							#ifdef GAS_PRO_AUTOGAIN_DEBUG	
								USB.println(F("GP.Vref high limit reached"));
							#endif
						}
						else
						{
							#ifdef GAS_PRO_AUTOGAIN_DEBUG	
								USB.println(F("GP.Incresaing Vref"));
							#endif
							LMP.setInternalZero(vref_reg + 1);
							v_steps++;
						}
						
						break;
						
					case 0x40:	//End
					case 0x41:
					case 0x42:
					case 0x22:
					case 0x12:
					case 0x08:
					case 0x09:
					case 0x0A:
					default:
						end = 1;
						break;
					
				}
	
			}while(end == 0);	
			
			break;
		
	}
	
	// Disable communication
	digitalWrite(sensor_config.I2C_pin, LOW);
			
	#ifdef GAS_PRO_AUTOGAIN_DEBUG	
		USB.println(F("GP.End of autogain proccess"));
	#endif
	
	return ((v_steps << 4) & 0xF0) + (r_steps & 0x0F);
}

/* Function: 	This function converts concentration in ppm to %
 * Parameters:	ppm_conc: concentration in ppm
 * Returns: 	The concetration value in %
*/
float Gas::ppm2perc(float ppm_conc)
{
	return (ppm_conc / 10000);
	
}

/* Function: 	This function converts temperature in Celsius degrees to Fahrenheit degrees
 * Parameters:	temp: concentration in Celsius degrees
 * Returns: 	The concetration value in Fahrenheit degrees
*/
float Gas::Celsius2Fahrenheit(float temp)
{
	return ((1.8 * temp) + 32);	
}

//! MISCELANEUS	
/* Function:	This function shows the information about the sensor
 * Return:	 	Nothing
 */
void Gas::showSensorInfo()
{
	char sensor_no[17];
	
	//Enable communication with the AFE
	digitalWrite(sensor_config.I2C_pin, HIGH);
	
	memset(sensor_no, '\0', sizeof(sensor_no));
	Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENSOR_NO_REG, (uint8_t*)sensor_no, 16);
			
	//Disable communication with the AFE
	digitalWrite(sensor_config.I2C_pin, LOW);
	
	USB.println(F("************ Sensor data ************"));
	USB.print(F("Serial n.: "));
	USB.println(sensor_no);
	USB.print(F("Sensor type: "));
	switch (sensor_config.sensor_type)
	{
		case CL2_SS:			
			USB.println("Cl2");
			break;
		case CO_SS_SEC:			
			USB.println("CO");
			break;
		case ETO_SS:			
			USB.println("ETO");
			break;
		case H2_SS_SEC:			
			USB.println("H2");
			break;
		case H2S_SS_SEC:			
			USB.println("H2S");
			break;
		case HCL_SS:			
			USB.println("HCl");
			break;
		case HCN_SS:			
			USB.println("HCN");
			break;
		case NH3_SS:			
			USB.println("NH3");
			break;
		case NO_SS:			
			USB.println("NO");
			break;
		case NO2_SS_CLE:			
			USB.println("NO2");
			break;
		case O2_SS:			
			USB.println("O2");
			break;
		case PH3_SS:			
			USB.println("PH3");
			break;
		case SO2_SS:			
			USB.println("SO2");
			break;
		case LEL_AS:			
			USB.println("Combustible gas pellistor");
			break;
		case O3_AS:			
			USB.println("O3");
			break;
		case NDIR_CO2_SS:			
			USB.println("CO2");
			break;
		default:			
			USB.println(sensor_config.sensor_type, DEC);
			break;
	}
	
	USB.print(F("power_pin: "));
	USB.println(sensor_config.power_pin, DEC);
	USB.print(F("I2C_pin: "));
	USB.println(sensor_config.I2C_pin, DEC);
	USB.print(F("m_conc: "));
	USB.print(sensor_config.m_conc);
	
	if ((sensor_config.sensor_type == LEL_AS)
		||	(sensor_config.sensor_type == NDIR_CO2_SS)
		||	(sensor_config.sensor_type == CALIBRATION_NDIR)
		||	(sensor_config.sensor_type == CALIBRATION_PEL))
	{
		USB.println(F(" mV/% LEL"));
	}
	else
	{
		USB.println(F(" nA/ppm"));		
	}
	USB.print(F("baseline: "));
	USB.print(sensor_config.baseline);
	if ((sensor_config.sensor_type == LEL_AS)
		||	(sensor_config.sensor_type == NDIR_CO2_SS)
		||	(sensor_config.sensor_type == CALIBRATION_NDIR)
		||	(sensor_config.sensor_type == CALIBRATION_PEL))
	{
		USB.println(F(" mV"));
	}
	else
	{
		USB.println(F(" nA"));		
	} 
	
	if ((sensor_config.sensor_type == O3_AS) || (sensor_config.sensor_type == CALIBRATION_4E))
	{		
		USB.print(F("aux_conc: "));
		USB.print(sensor_config.val_aux);	
		USB.println(F(" nA/ppm"));		
	}

	if (	(sensor_config.sensor_type == O3_AS) 
		||	(sensor_config.sensor_type == CALIBRATION_4E))
	{
		USB.println(F("Adjust values:"));
		USB.print(sensor_config.calibration[0][0]);
		USB.print(F(" ; "));
		USB.println(sensor_config.calibration[0][1]);
		USB.print(sensor_config.calibration[1][0]);
		USB.print(F(" ; "));
		USB.println(sensor_config.calibration[1][1]);
	}
	else if ((sensor_config.sensor_type == LEL_AS)
		||	(sensor_config.sensor_type == NDIR_CO2_SS)
		||	(sensor_config.sensor_type == CALIBRATION_NDIR)
		||	(sensor_config.sensor_type == CALIBRATION_PEL))
	{
		USB.println(F("Adjust values:"));
		USB.print(sensor_config.calibration[0][0]);
		USB.print(F(" ; "));
		USB.println(sensor_config.calibration[0][1]);
	}
	else
	{	
		USB.println(F("Calibration table"));
		for (int x = 0; x < 7; x++)
		{
			USB.print(x, DEC);
			USB.print(F(": "));
			USB.print(sensor_config.calibration[x][0]);
			USB.print(F(" ; "));
			USB.println(sensor_config.calibration[x][1]);
		}
	}
		
}


