/*
 *  Library for managing the Gas Pro Sensor Board
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
 *  Version:		4.1
 *  Design:			David Gascón
 *  Implementation:	Alejandro Gállego & Ahmad Saad
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

/*
 * Constructor: This function powers on the sensor and configures the AFE
 */
Gas::Gas(int socket)
{

	switch (socket)
	{
		case SOCKET_1:
		case SOCKET_C:
			sensor_config.power_pin = DIGITAL3;
			sensor_config.i2c_pin = DIGITAL4;
			sensor_config.cities_3v3_pin = ANA2;
			sensor_config.socket = 1;
			break;
		case SOCKET_2:
		case SOCKET_E:
			sensor_config.power_pin = DIGITAL5;
			sensor_config.i2c_pin = DIGITAL6;
			sensor_config.cities_3v3_pin = 0; //N/A
			sensor_config.socket = 2;
			break;
		case SOCKET_3:
		case SOCKET_F:
			sensor_config.power_pin = DIGITAL7;
			sensor_config.i2c_pin = DIGITAL8;
			sensor_config.cities_3v3_pin = ANA5;
			sensor_config.socket = 3;
			break;
		case SOCKET_4:
		case SOCKET_A:
			sensor_config.power_pin = ANA6;
			sensor_config.i2c_pin = ANA5;
			sensor_config.cities_3v3_pin = 0; //N/A
			sensor_config.socket = 4;
			break;
		case SOCKET_5:
		case SOCKET_B:
			sensor_config.power_pin = ANA4;
			sensor_config.i2c_pin = ANA3;
			sensor_config.cities_3v3_pin = ANA1;
			sensor_config.socket = 5;
			break;
		case SOCKET_6:
			sensor_config.power_pin = ANA2;
			sensor_config.i2c_pin = ANA1;
			sensor_config.cities_3v3_pin = 0; //N/A
			sensor_config.socket = 6;
			break;
		case 0:	// Calibration
			sensor_config.power_pin = GPS_PW;
			sensor_config.i2c_pin = GPS_PW;
			break;
	}

	// Default values
	sensor_config.sensor_type = UNDEFINED_SENSOR;
	sensor_config.m_conc = 1;
	sensor_config.baseline = 0;
	sensor_config.aux_baseline = 1;

	for (int x = 0; x < 7; x++)
	{
		sensor_config.calibration[x][0] = 0;
		sensor_config.calibration[x][1] = 1;
	}

	// Init I2C and power lines
	if (!initDone)
	{
		if ((WaspRegisterSensor & REG_CITIES_PRO) != 0)
		{
			// gases pro board
			// disable all i2c lines
			pinMode(GP_I2C_SOCKET_1_C, OUTPUT);
			pinMode(GP_I2C_SOCKET_2_E, OUTPUT);
			pinMode(GP_I2C_SOCKET_3_F, OUTPUT);
			pinMode(GP_I2C_SOCKET_4_A, OUTPUT);
			pinMode(GP_I2C_SOCKET_5_B, OUTPUT);
			pinMode(GP_I2C_SOCKET_6, OUTPUT);
			digitalWrite(GP_I2C_SOCKET_1_C, LOW);
			digitalWrite(GP_I2C_SOCKET_2_E, LOW);
			digitalWrite(GP_I2C_SOCKET_3_F, LOW);
			digitalWrite(GP_I2C_SOCKET_4_A, LOW);
			digitalWrite(GP_I2C_SOCKET_5_B, LOW);
			digitalWrite(GP_I2C_SOCKET_6, LOW);

			// switch off all socket power lines
			pinMode(GP_PWR_SOCKET_1_C, OUTPUT);
			pinMode(GP_PWR_SOCKET_2_E, OUTPUT);
			pinMode(GP_PWR_SOCKET_3_F, OUTPUT);
			pinMode(GP_PWR_SOCKET_4_A, OUTPUT);
			pinMode(GP_PWR_SOCKET_5_B, OUTPUT);
			pinMode(GP_PWR_SOCKET_6, OUTPUT);
			digitalWrite(GP_PWR_SOCKET_1_C, HIGH);
			digitalWrite(GP_PWR_SOCKET_2_E, HIGH);
			digitalWrite(GP_PWR_SOCKET_3_F, HIGH);
			digitalWrite(GP_PWR_SOCKET_4_A, HIGH);
			digitalWrite(GP_PWR_SOCKET_5_B, HIGH);
			digitalWrite(GP_PWR_SOCKET_6, HIGH);
		}
		else
		{
			// cities pro board
			// this is done in Cities class constructor
		}
	}
	initDone = true;

	// i2c isolator disabled
	// sensor socket power disabled
	pinMode(sensor_config.power_pin, OUTPUT);
	pinMode(sensor_config.i2c_pin, OUTPUT);
	digitalWrite(sensor_config.power_pin, HIGH);
	digitalWrite(sensor_config.i2c_pin, LOW);

	/*
	digitalWrite(I2C_MAIN_EN, LOW);
	*/

	pwrGasPRORegister = 0;
}

Gas::Gas(int socket, uint8_t sensor_type, int power_pin, int I2C_pin, float m_conc, float baseline, float aux_var, float calibration_table[7][2])
{

	sensor_config.socket = socket;
	sensor_config.sensor_type = sensor_type;
	sensor_config.power_pin = power_pin;
	sensor_config.i2c_pin = I2C_pin;
	sensor_config.m_conc = m_conc;
	sensor_config.aux_baseline = aux_var;
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
		comp_ppm = val_low + (((val_high - val_low) / 40) * (temperature - (-20)));

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
	else
	{
		comp_ppm = 0;
	}

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Baseline temperature compensation value (ppm): "));
		USB.printFloat(comp_ppm, 3);
		USB.println();
	#endif

	#if DEBUG_GASES_PRO>2
		PRINT_GASES_PRO(F("Temp: "));
		USB.printFloat(temperature,3);
		USB.print(F(" | H_val: "));
		USB.printFloat(val_high,3);
		USB.print(F(" | L_val: "));
		USB.printFloat(val_low,3);
		USB.println();
	#endif

	#if DEBUG_GASES_PRO>2
		PRINTLN_GASES_PRO(F("***End of baseline temperature compensation***\r\n"));
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

	if (temperature == -1000)
	{
		return 1;
	}

	if (temperature < 0)
	{
		val_low = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][0]);
		val_high = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][1]);
		comp_sens = val_low + (((val_high - val_low) / 40) * (temperature - -20));
	}
	else if ((temperature >= 0) && (temperature < 20))
	{
		val_low = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][1]);
		val_high = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][2]);
		comp_sens = val_low + (((val_high - val_low) / 20) * (temperature - 20));
	}
	else if ((temperature >= 20) && (temperature < 40))
	{
		val_low = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][2]);
		val_high = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][3]);
		comp_sens = val_low + (((val_high - val_low) / 20) * (temperature - 20));
	}
	else if (temperature >= 40)
	{
		val_low = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][3]);
		val_high = pgm_read_float(&table_sensitivity_temp_comp[sensor_config.sensor_type][4]);
		comp_sens = val_low + (((val_high - val_low) / 10) * (temperature - 40));
	}
	else
	{
		comp_sens = 1;
	}

	comp_sens = 1/comp_sens;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Sensitivity temperature compensated (ppm): "));
		USB.printFloat(comp_sens, 3);
		USB.println();
	#endif

	#if DEBUG_GASES_PRO>2
		PRINT_GASES_PRO(F("Temp: "));
		USB.printFloat(temperature,3);
		USB.print(F(" | H_val: "));
		USB.printFloat(val_high,3);
		USB.print(F(" | L_val: "));
		USB.printFloat(val_low,3);
		USB.println();
	#endif

	#if DEBUG_GASES_PRO>2
		PRINTLN_GASES_PRO(F("***End of sensitivity temperature compensation***\r\n"));
	#endif


	return comp_sens;
}


//! ONLY FOR 4-ELECTRODE AMPERIOMETRIC BOARD (V12)
/* Function:	This function sets the resistance to an specific digipot
 * Parameters: electrode: electrode asociated to each digipot
 *  			     resistor: resistor value to set in Ohms
 * Return: 		void
 */
void Gas::setAmplifier(bool electrode, float resistor)
{
	uint8_t value = 0;
	uint8_t aux[2];

	Wire.readBytes(I2C_ADDRESS_GASPRO_MCP4146, VOL_TCON_REG | READ_COMMAND, aux, 2);

	if(resistor <= 100000)
	{
		// Connect the resistor
		value = 128.0 * (resistor / 100000.0);

		if (electrode == AUXILIARY_ELECTRODE)
		{
			aux[0] =  aux[1] | 0x04;
			Wire.writeBytes( I2C_ADDRESS_GASPRO_MCP4146, VOL_TCON_REG | WRITE_COMMAND | 0x01, aux, 1);
			//delay(100);
			value = 128 - value;
			Wire.writeBytes( I2C_ADDRESS_GASPRO_MCP4146, VOL_WIPER_0_REG | WRITE_COMMAND, &value, 1);
		}
		else
		{
			aux[0] =  aux[1] | 0x10;
			Wire.writeBytes( I2C_ADDRESS_GASPRO_MCP4146, VOL_TCON_REG | WRITE_COMMAND | 0x01, aux, 1);
		//	delay(100);
			Wire.writeBytes( I2C_ADDRESS_GASPRO_MCP4146, VOL_WIPER_1_REG | WRITE_COMMAND, &value, 1);
		}
	}
	else
	{

		// Disconnect the resistor
		if (electrode == AUXILIARY_ELECTRODE)
		{
			value = aux[1] & 0xFB;
			Wire.writeBytes( I2C_ADDRESS_GASPRO_MCP4146, VOL_TCON_REG | WRITE_COMMAND | 0x01, &value, 1);
		}
		else
		{
			value = aux[1] & 0xEF;
			Wire.writeBytes( I2C_ADDRESS_GASPRO_MCP4146, VOL_TCON_REG | WRITE_COMMAND | 0x01, &value, 1);

		}

	}

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Setting R "));
		USB.print(electrode);
		USB.print(F(" to "));
		USB.print(resistor);
		USB.print(F(" Ohms || wiper: "));
		USB.println(value, HEX);
 	#endif
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

	Wire.readBytes(I2C_ADDRESS_GASPRO_MCP4146, VOL_TCON_REG | READ_COMMAND, aux, 2);
	if ((aux[1] == 0xEF) || (aux[1] == 0xFB) || (aux[1] == 0xEB))
	{
		#if DEBUG_GASES_PRO>0
			PRINT_GASES_PRO(F("Reading wiper "));
			USB.print(electrode, DEC);
			USB.print(F(": "));
			USB.println(F(" external resistors"));
		#endif
		resistor = 1000000;
		return resistor;
	}

	//delay(10);
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

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Reading wiper "));
		USB.print(electrode);
		USB.print(F(": "));
		USB.print(wiper, DEC);
		USB.print(F("/128 || Resistor value: "));
		USB.print(resistor);
		USB.println(F(" Ohms"));
	#endif

	return resistor;
}

/* Function: 	Specific function to read 3 electrode sensors
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * 				temperature: ambient temperature for sensor compensation (-1000 if doesn't needed)
 * Returns: 	The concetration value in ppm
*/
float Gas::read3ElectrodeSensor(uint8_t resolution, float temperature)
{
	float V_conc = 0;
	float conc = 0;
	float V_ref = 0;
	float R_gain = 0;
	int n_samples = 4;

	// Select amperometric mode
	LMP.setModeReg( LMP91000_MODEC_REG_FET_NOT_SHORTED,
					LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPEROMETRIC);
	delay(100);

	// Read the ADC
	for (int i = 0; i < n_samples; i++)
	{
		V_conc += (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));
	}
	// Get the mean value
	V_conc /= n_samples;


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
	switch (LMP.getRgain())
	{
		case 0:
			R_gain = 1000;
			break;
		case 1:
			R_gain = 2.750;
			break;
		case 2:
			R_gain = 3.500;
			break;
		case 3:
			R_gain = 7;
			break;
		case 4:
			R_gain = 14;
			break;
		case 5:
			R_gain = 35;
			break;
		case 6:
			R_gain = 120;
			break;
		case 7:
			R_gain = 350;
			break;
		default:
			R_gain = 0;
	}


	// Disable communication with AFE
	digitalWrite(sensor_config.i2c_pin, LOW);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("Vo: ", V_conc ," mV");
		PRINT_GASES_PRO_DATA("Vref: ", V_ref," mV");
		PRINT_GASES_PRO_DATA("Rgain: ", R_gain," kOhms");
	#endif

	////////////////////////////////////////////////////////
	// Vo(mV) - Vref(mV)
	////////////////////////////////////////////////////////
	conc = (V_conc - V_ref);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("Vmeas: " , conc, " mV");
	#endif

	// V(mV) ---> Ie(uA)
	conc = (conc / R_gain);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("Ie: ", conc," uA");
	#endif

	// Ie-Ibase  (Subtracts baseline current)
	conc -= (sensor_config.baseline / 1000);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("Ie-Ibase: ", conc," uA");
	#endif

	// Output current temperature compensation
	conc *= getSensitivityTempComp(temperature);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("Compensated conc: ", conc," uA");
	#endif

	// fix sensitivity sign
	if ((sensor_config.sensor_type == CL2_SS) 		||
		(sensor_config.sensor_type == NO2_SS_CLE) 	||
		(sensor_config.sensor_type == O2_SS))
	{
		conc *= -1;
	}

	// Conversion: I(nA) --> concentración(ppm)
	conc = (conc * 1000) / sensor_config.m_conc;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("concentration: ", conc," ppm");
	#endif


	// Baseline temperature compensation
	conc -= getBaselineTempComp(temperature);
	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("after baseline temp compensation: ", conc," ppm");
	#endif

	if (conc < 0)
	{
		conc = 0;
	}

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("CONC: ", conc," ppm");
	#endif

	return conc;
}

/* Function: 	Specific function to read pellistor sensors
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * 				temperature: ambient temperature for sensor compensation (-1000 if doesn't needed)
 * Returns: 	The concetration value in %/LEL
*/
float Gas::readPellistorSensor(uint8_t resolution, float temperature)
{
	float V_conc = 0;
	float concentration = 0;

	for ( int i = 0; i < 4; i++)
	{
		// Reads the ADC
		V_conc += (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));
	}

	// Disable communication
	digitalWrite(sensor_config.i2c_pin, LOW);

	V_conc /= -4;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Average measure: "));
		USB.printFloat(V_conc, 3);
		USB.println(F(" mV"));
	#endif

	// Apply calibration values
	V_conc = (V_conc - sensor_config.calibration[0][0]) / sensor_config.calibration[0][1];

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("AFE compensated: "));
		USB.printFloat(V_conc, 3);
		USB.println(F(" mV"));
	#endif

	// Vconc(mV) - Voffset(mV) sensor
	V_conc -= sensor_config.baseline;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Measure baseline compensated: "));
		USB.printFloat(V_conc, 3);
		USB.println(F(" mV"));
	#endif

	// Baseline temperature compensation
	V_conc -= getBaselineTempComp(temperature);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Measure temperature compensated: "));
		USB.printFloat(V_conc, 3);
		USB.println(F(" mV"));
	#endif

	// Output current temperature compensation
	V_conc *= getSensitivityTempComp(temperature);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Measure sensitivity compensated: "));
		USB.printFloat(V_conc, 3);
		USB.println(F(" mV"));
	#endif

	// V_conc(mV) --> concentration(% LEL)
	concentration = V_conc / (sensor_config.m_conc);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Measure concentration: "));
		USB.printFloat(V_conc, 3);
		USB.println(F(" %"));
	#endif

	if (concentration < 0)
	{
		concentration = 0;
	}

	#if DEBUG_GASES_PRO>1
		PRINTLN_GASES_PRO(F("***End of read pellistor sensor***\r\n"));
	#endif

	return concentration;
}

/* Function: 	Specific function to read NDIR sensors
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * 				temperature: ambient temperature for sensor compensation (-1000 if doesn't needed)
 * Returns: 	The concetration value in ppm
*/
float Gas::readNDIR(uint8_t resolution)
{
	float V_conc = 0;
	float conc = 0;

	for ( int i = 0; i < 4; i++)
	{
		// Reads the ADC
		V_conc += (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));
	}

	// Disable communication
	digitalWrite(sensor_config.i2c_pin, LOW);

	V_conc /= 4;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Average measure: "));
		USB.printFloat(V_conc, 3);
		USB.println(F(" mV"));
	#endif

	// NDIR sensor from Solidsense doesn't need temperature compensation
	V_conc = (V_conc - sensor_config.calibration[0][0]) / sensor_config.calibration[0][1];

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("AFE compensation: "));
		USB.printFloat(conc, 3);
		USB.println(F(" mV"));
	#endif

	// Vconc(mV) - Voffset(mV) sensor
	V_conc -= sensor_config.baseline;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Measure baseline compensated: "));
		USB.printFloat(V_conc, 3);
		USB.println(F(" mV"));
	#endif

	// conc(mV) --> concentración(% LEL)
	conc = V_conc * sensor_config.m_conc;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Compensated measure: "));
		USB.printFloat(conc, 3);
		USB.println(F(" %"));
	#endif

	if (conc < 0)
	{
		conc = 0;
	}

	return conc;
}

// For old O3 sensors
/* Function: 	Specific function to read O3 sensors (v12 sensors)
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * 				temperature: ambient temperature for sensor compensation (-1000 if doesn't needed)
 * Returns: 	The concetration value in ppm
*/
float Gas::read4ElectrodeSensorv100(uint8_t resolution, float temperature)
{

	float V_conc = 0;
	float conc=0, conc_aux=0;
	float aux_val;
	float aux_resistor;

	float R_gain;

	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("****************************"));
		PRINTLN_GASES_PRO(F("Read 4 electrode sensor v100"));
		PRINTLN_GASES_PRO(F("****************************\r\n"));
	#endif

	// Selects amperiometric mode
	LMP.setModeReg(LMP91000_MODEC_REG_FET_NOT_SHORTED,
					LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPEROMETRIC);

	// Measuring
	conc = 0;
	conc_aux = 0;

	/// Read WE
	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("Reading working electrode"));
	#endif

	aux_resistor = getAmplifier(AUXILIARY_ELECTRODE);
	setAmplifier(AUXILIARY_ELECTRODE, 0);

	delay(1000);

	V_conc = 0;
	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("ADC reading"));
	#endif
	for ( int i = 0; i < 8; i++)
	{
		// Reads the ADC
		delay(100);
		aux_val = (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));
		V_conc += aux_val;
	}
	V_conc /=8;

	setAmplifier(AUXILIARY_ELECTRODE, aux_resistor);
	R_gain = getAmplifier(WORKING_ELECTRODE);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("ADC measure: "));
		USB.print(V_conc);
		USB.print(F(" mV || R_gain: "));
		USB.print(R_gain, DEC);
		USB.println(F(" Ohms"));
	#endif

	// V(mV) --> I(uA)
	conc = (V_conc / (R_gain)) * -1000;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Current: "));
		USB.printFloat(conc, 3);
		USB.println(F(" uA"));
	#endif

	// Adjust resistor
	conc =  ((conc + sensor_config.calibration[0][0]) / (sensor_config.calibration[0][1]));

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("AFE compensation: "));
		USB.printFloat(conc, 3);
		USB.println(F(" mV"));
	#endif

	/// Read auxiliary electrode
	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("Reading auxiliary electrode"));
	#endif
	aux_resistor = getAmplifier(WORKING_ELECTRODE);
	setAmplifier(WORKING_ELECTRODE, 0);

	delay(2000);

	V_conc = 0;
	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("ADC"));
	#endif
	for ( int i = 0; i < 8; i++)
	{
		// Reads the ADC
		delay(100);

		aux_val = (MCP.readADC(resolution, MCP3421_GAIN_1, MCP3421_VOLTS));
		V_conc += aux_val;
	}

	V_conc /=8;

	setAmplifier(WORKING_ELECTRODE, aux_resistor);
	R_gain = getAmplifier(AUXILIARY_ELECTRODE);

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Average measure: "));
		USB.print(V_conc);
		USB.print(F(" mV || R_gain: "));
		USB.print(R_gain, DEC);
		USB.println(F(" Ohms"));
	#endif

	conc_aux = (V_conc / (R_gain)) * 1000;// V(mV) --> I(uA)

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Current Aux: "));
		USB.print(conc);
		USB.println(F(" uA"));
	#endif

	conc_aux =  ((conc_aux + sensor_config.calibration[1][0]) / (sensor_config.calibration[1][1]));// Adjust resistor

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("AFE compensation aux: "));
		USB.print(conc_aux);
		USB.println(F(" uA"));
	#endif

	/// Substracts offset currents
	conc -= (sensor_config.baseline / 1000);	// Subtracts baseline current
	conc_aux -= (sensor_config.aux_baseline / 1000);	// Subtracts auxiliary baseline current
	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Iwe without offset: "));
		USB.print(conc);
		USB.println(F(" uA"));
		PRINT_GASES_PRO(F("Iae without offset: "));
		USB.print(conc_aux);
		USB.println(F(" uA"));
	#endif

	/// Compensates WE with AE
	conc -= conc_aux;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Iwe-Iae: "));
		USB.print(conc);
		USB.println(F(" uA"));
	#endif

	conc *= getSensitivityTempComp(temperature);	// Output current temperature compensation

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO(F("Temperature compensation: "));
		USB.print(conc);
		USB.println(F(" uA"));
	#endif

	conc = (conc * 1000) / sensor_config.m_conc;	// I(uA) --> concentración(ppm)

	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("---------------------------------"));
		PRINT_GASES_PRO(F("|Concentration: "));
		USB.print(conc);
		USB.println(F(" ppm|"));
		PRINTLN_GASES_PRO(F("---------------------------------"));
	#endif

	if (conc < 0)
	{
		conc = 0;
	}

	// Disable communication with AFE
	digitalWrite(sensor_config.i2c_pin, LOW);

	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("***End of read 4 electrode sensor v100***\r\n"));
	#endif

	return conc;

}

// For new 4 electrode AFE boards
/* Function: 	Specific function to read 4 electrode sensors
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * 				temperature: ambient temperature for sensor compensation (-1000 if doesn't needed)
 * 				NO2_conc: NO2 concentration in ppm to compensate the cross-sensitivity.
 * 					Only for O3 sensor, for other sensors use 0.0 value
 * Returns: 	The concetration value in ppm
*/
float Gas::read4ElectrodeSensorv301(uint8_t resolution, float temperature, float NO2_conc)
{
	float concentration = 0;
	float conc_aux = 0;

	#if DEBUG_GASES_PRO > 0
		switch (sensor_config.socket)
		{
		  case SOCKET_1:
		  case SOCKET_C:
			PRINTLN_GASES_PRO(F("SOCKET_1_C"));
			break;
		  case SOCKET_2:
		  case SOCKET_E:
			PRINTLN_GASES_PRO(F("SOCKET_2_E"));
			break;
		  case SOCKET_3:
		  case SOCKET_F:
			PRINTLN_GASES_PRO(F("SOCKET_3_F"));
			break;
		  case SOCKET_4:
		  case SOCKET_A:
			PRINTLN_GASES_PRO(F("SOCKET_4_A"));
			break;
		  case SOCKET_5:
		  case SOCKET_B:
			PRINTLN_GASES_PRO(F("SOCKET_5_"));
			break;
		  case SOCKET_6:
		  case SOCKET_D:
			PRINTLN_GASES_PRO(F("SOCKET_6_D"));
			break;
		}
	#endif

	// Selects amperometric mode
	LMP.setModeReg(	LMP91000_MODEC_REG_FET_NOT_SHORTED,
					LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPEROMETRIC);

	/// Read WE ////////////////////////////////
	concentration = readWorkingElectrode4E();
	if (sensor_config.zeroPointOK == 0xAA)
	{
		// Substract OFFSET of the Working Electrode
		concentration = concentration - sensor_config.working_offset;
	}
	else
	{
		// Subtracts baseline current
		//concentration -= (sensor_config.baseline / 1000);
	}

	#if DEBUG_GASES_PRO > 0
		PRINT_GASES_PRO_DATA("Iwe: ", concentration, " uA");
	#endif

	/// Read AE ////////////////////////////////
	conc_aux = readAuxiliaryElectrode4E();

	if (sensor_config.zeroPointOK == 0xAA)
	{
		// Substract OFFSET of the auxiliar Electrode
		conc_aux = conc_aux - sensor_config.auxiliar_offset;
	}
	else
	{
		// Substracts AE baseline current
		//conc_aux -= (sensor_config.aux_baseline / 1000);
	}


 	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("Iae: ", conc_aux, " uA");
	#endif

	// Compensates WE with AE
	concentration -= conc_aux;

	#if DEBUG_GASES_PRO>0
		PRINT_GASES_PRO_DATA("Iwe-Iae: ", concentration, " uA");
	#endif

	// Output current temperature compensation
	concentration *= getSensitivityTempComp(temperature);

	#if DEBUG_GASES_PRO > 0
		PRINT_GASES_PRO_DATA("T-Comp: ", concentration, " uA");
	#endif

	if(sensor_config.sensor_type == O3_AS)
	{
		//concentration = concentration - (sensor_config.OX_NO2_sens * NO2_conc / 1000);
		#if DEBUG_GASES_PRO > 0
			PRINT_GASES_PRO_DATA("O3-NO2: ", concentration, " uA");
		#endif
	}

	// I(uA) --> concentracion (ppm)
	#if DEBUG_GASES_PRO > 0
		PRINT_GASES_PRO_DATA("Sensitivity: ", sensor_config.m_conc, " nA/ppm");
	#endif

	concentration = (concentration * 1000) / sensor_config.m_conc;

	#if DEBUG_GASES_PRO > 0
		PRINT_GASES_PRO_DATA("Concentration: ", concentration, " ppm");
	#endif

	if (concentration < 0)
	{
		concentration = 0;
	}

	// Disable communication with AFE
	digitalWrite(sensor_config.i2c_pin, LOW);

	return concentration;
}


//! MISCELANEUS
/* Function: 	This function reads the sensor information from EEPROM
 * Return: 		'1' if checksum is correct, '0' if not
 */
uint8_t Gas::readSensorInfo()
{
	uint8_t buffer[4];
	uint8_t EEPROM_checksum, generated_checksum;

	// First read the board version and sensor type
	// This parameters are common for all sensors
	Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, VER_BOARD_REG, &sensor_config.AFE_ver, 1);
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

			if (sensor_config.AFE_ver >= 3)
			{
				Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_REG + 56, buffer, 4);
				memcpy(&sensor_config.calibration[7][0], buffer, 4);
				Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, CAL_REG + 60, buffer, 4);
				memcpy(&sensor_config.calibration[7][1], buffer, 4);
			}

			break;

		// 4 electrodes PCB
		case O3_AS:
		case NO2_AS:
		case NO_AS:
		case SO2_AS:
		case CO_AS:
		case CALIBRATION_4E:

			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENSITIVITY_REG, buffer, 4);
			memcpy(&sensor_config.m_conc, buffer, 4);
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, OFFSET_REG, buffer, 4);
			memcpy(&sensor_config.baseline, buffer, 4);
			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENS_AE_REG, buffer, 4);
			memcpy(&sensor_config.OX_NO2_sens, buffer, 4);

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

			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, OFFSET_WRK_ELEC, buffer, 4);
			memcpy(&sensor_config.working_offset, buffer, 4);

			Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, OFFSET_AUX_ELEC, buffer, 4);
			memcpy(&sensor_config.auxiliar_offset, buffer, 4);

			Wire.readByte(I2C_ADDRESS_GASPRO_E2PROM, ZERO_POINT_OK, buffer);
			memcpy(&sensor_config.zeroPointOK, buffer, 1);


			sensor_config.aux_baseline = 0;
			switch (sensor_config.AFE_ver)
			{
				case 3:
					Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, AE_OFFSET_REG, buffer, 4);
					memcpy(&sensor_config.aux_baseline, buffer, 4);
					break;
			}

			break;
	}

	if (sensor_config.AFE_ver >= 3)
	{
		Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENSOR_CHECKSUM, &EEPROM_checksum, 1);
		memcpy(buffer, &sensor_config.m_conc, 4);

		generated_checksum = 	sensor_config.AFE_ver ^
								sensor_config.sensor_type ^
								buffer[0] ^
								buffer[1] ^
								buffer[2] ^
								buffer[3];

		if (EEPROM_checksum != generated_checksum)
		{
			#if DEBUG_GASES_PRO>0
				PRINTLN_GASES_PRO(F("Error with EEPROM parameters"));
			#endif
			return 0;
		}

		#if DEBUG_GASES_PRO>0
			PRINTLN_GASES_PRO(F("Checksum generated OK"));
		#endif
	}

	return 1;
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
 * 				0 if error with EEPROM memory
 * 				-1 no communication with LMP91000
 */
int8_t Gas::ON(float R_gain)
{
	int answer = 0;
	uint8_t mask;

	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("ON function"));
	#endif

	#ifndef CALIBRATION_MODE
		// enable I2C isolator
		pinMode(GP_I2C_MAIN_EN, OUTPUT);
		digitalWrite(GP_I2C_MAIN_EN, HIGH);

		// switch on 3V3 main supply if not initialized
		if ((pwrGasPRORegister == 0) || ((WaspRegister & REG_3V3) == 0))
		{
			#if DEBUG_GASES_PRO>0
				PRINTLN_GASES_PRO(F("Sensor power 3V3 to ON"));
			#endif

			PWR.setSensorPower(SENS_3V3, SENS_ON);
			delay(100);

			// init BME
			BME.ON();
		}
	#endif

	// Update register bitmap with related socket
	pwrGasPRORegister |= (1 << sensor_config.socket);

	// Switch ON the sensor power 3v3 switch if required for Cities Board
	if (WaspRegisterSensor & REG_CITIES_PRO)
	{
		digitalWrite(sensor_config.cities_3v3_pin, HIGH);
		pwrCitiesPRORegister |= (1 << sensor_config.socket);
	}

	// Switch ON the sensor socket
	digitalWrite(sensor_config.power_pin, LOW);

	// Disable All sockets for preventing interferences
	disableCommSockets();

	// Enable communication with the AFE
 	digitalWrite(sensor_config.i2c_pin, HIGH);
 	delay(100);

 	//////////////////////////////////////////////
 	// Read eeprom
 	//////////////////////////////////////////////
	uint8_t retries = 3;
	do
	{
		// read eeprom info
		answer = readSensorInfo();
		retries--;

		if (answer != 1)
		{
			Wire.recover();
		}
	} while ((answer != 1) && (retries > 0));

	// check error
	if (answer == 0)
	{
		// Clear bit in pwrGasPRORegister
		mask = ~(1 << sensor_config.socket);
		pwrGasPRORegister &= mask;

		return 0;
	}

	#if DEBUG_GASES_PRO > 1
		showSensorInfo();
	#endif

 	delay(1000);


 	//////////////////////////////////////////////
 	// Configure AFE
 	//////////////////////////////////////////////

 	retries = 3;
 	do
	{
		// configure AFE
		answer = configureAFE(R_gain);
		retries--;

		if (answer != 1)
		{
			Wire.recover();
		}
	} while ((answer != 1) && (retries > 0));


	if (answer == 1)
	{
		// Set bit in pwrGasPRORegister
		pwrGasPRORegister |= (1 << sensor_config.socket);
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

	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("OFF function"));
	#endif

	// disable the rest of I2C components
	disableCommSockets();

	//Enable communication with the AFE
	digitalWrite(sensor_config.i2c_pin, HIGH);
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
	digitalWrite(sensor_config.i2c_pin, LOW);

	// Power off the AFE module
	digitalWrite(sensor_config.power_pin, HIGH);


	// Switch ON the sensor power 3v3 switch if required for Cities Board
	if (WaspRegisterSensor & REG_CITIES_PRO)
	{
		digitalWrite(sensor_config.cities_3v3_pin, LOW);
		pwrCitiesPRORegister &= ~(1 << sensor_config.socket);
	}


	#ifndef CALIBRATION_MODE
		mask = ~(1 << sensor_config.socket);
		pwrGasPRORegister &= mask;

		// If there aren't powered AFE modules, turns off the 3V3 power supply
		if (pwrGasPRORegister == 0x00)
		{
			#if DEBUG_GASES_PRO>0
				PRINTLN_GASES_PRO(F("Sensor power 3V3 to OFF"));
			#endif
			PWR.setSensorPower(SENS_3V3, SENS_OFF);
			pinMode(GP_I2C_MAIN_EN, OUTPUT);
			digitalWrite(GP_I2C_MAIN_EN, LOW);
		}
		else if (pwrGasPRORegister == 0x01)
		{
			pinMode(GP_I2C_MAIN_EN, OUTPUT);
			digitalWrite(GP_I2C_MAIN_EN, LOW);
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
	#if DEBUG_GASES_PRO>0
		PRINTLN_GASES_PRO(F("Set power mode"));
	#endif
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
	if ((sensor_config.sensor_type == LEL_AS) ||
		(sensor_config.sensor_type == NDIR_CO2_SS) ||
		(sensor_config.sensor_type == CALIBRATION_NDIR) ||
		(sensor_config.sensor_type == CALIBRATION_PEL))
	{
		digitalWrite(sensor_config.i2c_pin, LOW);
		return 1;
	}

	//Enable communication with the AFE
	digitalWrite(sensor_config.i2c_pin, HIGH);

	delay(100);



	// Check communication with LMP91000
	if (LMP.check() == 0)
	{
		// Communication error
		// Disable communication
		digitalWrite(sensor_config.i2c_pin, LOW);
		#if DEBUG_GASES_PRO>0
			PRINTLN_GASES_PRO(F("LMP91000 communication error"));
		#endif
		return -1;
	}

	// No gain selected
	if (R_gain == -1000)
	{
		if ((sensor_config.sensor_type == O3_AS) ||		// Basic gain for O3 sensor
			(sensor_config.sensor_type == NO2_AS) ||
			(sensor_config.sensor_type == NO_AS) ||
			(sensor_config.sensor_type == SO2_AS) ||
			(sensor_config.sensor_type == CO_AS))
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
	else if (	(R_gain > 7) &&
				(sensor_config.sensor_type != O3_AS) &&
				(sensor_config.sensor_type != NO2_AS) &&
				(sensor_config.sensor_type != NO_AS) &&
				(sensor_config.sensor_type != SO2_AS) &&
				(sensor_config.sensor_type != CO_AS))	// Incorrect gain for 3 electrode sensors
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
		case CO_SS_SEC:
		case H2_SS_SEC:
		case HCN_SS:
		case NH3_SS:
		case PH3_SS:
		case SO2_SS:
		case NO2_SS_CLE:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF,
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;

		case ETO_SS:
		case NO_SS:
		case CALIBRATION_3E:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF,
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_14,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;

		case H2S_SS_SEC:
		case HCL_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF,
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_10,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			break;

		case O2_SS:
			LMP.setTIAConReg(gain_3E, LMP91000_TIAC_REG_REF_R_LOAD_50R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_INTERNAL_REF,
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_18,
								LMP91000_REFC_REG_REF_POLARITY_NEGATIVE);
			break;

		case O3_AS:
		case NO2_AS:
		case SO2_AS:
		case CO_AS:

			LMP.setTIAConReg( 	LMP91000_TIAC_REG_REF_R_GAIN_EXT,
								LMP91000_TIAC_REG_REF_R_LOAD_33R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF,
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_0,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);

			if (sensor_config. AFE_ver != 3)
			{
				setAmplifier(WORKING_ELECTRODE, gain_4E);
				setAmplifier(AUXILIARY_ELECTRODE, gain_4E);
			}

			break;

		case NO_AS:
			LMP.setTIAConReg(LMP91000_TIAC_REG_REF_R_GAIN_EXT, LMP91000_TIAC_REG_REF_R_LOAD_33R);
			LMP.setRefConReg(	LMP91000_REFC_REG_REF_SOURCE_EXTERNAL_REF,
								LMP91000_REFC_REG_REF_INT_Z_50,
								LMP91000_REFC_REG_REF_BIAS_PERC_10,
								LMP91000_REFC_REG_REF_POLARITY_POSITIVE);
			if (sensor_config. AFE_ver != 3)
			{
				setAmplifier(WORKING_ELECTRODE, gain_4E);
				setAmplifier(AUXILIARY_ELECTRODE, gain_4E);
			}
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
					LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPEROMETRIC);

	// Disable communication
	digitalWrite(sensor_config.i2c_pin, LOW);

  #if DEBUG_GASES_PRO>0
    PRINTLN_GASES_PRO(F("AFE Configured"));
    USB.println();
  #endif

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
    float temp = -1000;

	if  ((sensor == 0) &&
		(sensor_config.sensor_type != LEL_AS) &&
		(sensor_config.sensor_type != O3_AS) &&
		(sensor_config.sensor_type != NO2_AS) &&
		(sensor_config.sensor_type != NDIR_CO2_SS))
	{
	   //Enable communication with the AFE
		digitalWrite(sensor_config.i2c_pin, HIGH);
		delay(100);


		last_mode = LMP.getModeReg();
		LMP.setModeReg(	LMP91000_MODEC_REG_FET_NOT_SHORTED,
						LMP91000_MODEC_REG_PWR_MODE_TEMP_TIA_ON);

		temp = 0;
		for ( int i =0; i < 4; i++)
		{
			temp += (MCP.readADC(MCP3421_RES_12_BIT, MCP3421_GAIN_1, MCP3421_VOLTS));
		}

		temp/=4;

		// #if DEBUG_GASES_PRO>0
		// 	PRINT_GASES_PRO(F("Measured voltage: "));
		// 	PRINT_GASES_PRO_VAL(temp);
		// 	PRINT_GASES_PRO(F(" mV"));
		// #endif

		temp = (temp - 1875)*(-0.1233) - 40; //(85+40)/(861-1875)

		// #if DEBUG_GASES_PRO>0
		// 	PRINT_GASES_PRO(F(" || Temperature: "));
		// 	PRINT_GASES_PRO_VAL(temp);
		// 	PRINTLN_GASES_PRO(F(" ºC"));
		// #endif


		LMP.setModeReg(LMP91000_MODEC_REG_FET_NOT_SHORTED, last_mode);
		// Disable communication with LMP91000
		digitalWrite(sensor_config.i2c_pin, LOW);
	}
	else
	{
		//~ #if DEBUG_GASES_PRO>0
			//~ USB.println(F("Reading BME280"));
		//~ #endif
		temp = BME.getTemperature(BME280_OVERSAMP_1X, 0);
	}

	//~ #if DEBUG_GASES_PRO>0
		//~ USB.println(F("\r\n***End of get temperature***\r\n"));
	//~ #endif
	//~
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
	return getConc(resolution, BME280_temp, 0);
}


/* Function: 	This function reads concentration value with default parameters (BME280 temperature and compensated measure for O3 sensor)
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * Returns: 	The concetration value in ppm / %LEL, -1000 if error.
*/
float Gas::getConc(float temperature)
{
	return getConc(MCP3421_HIGH_RES, temperature, 0);
}

/* Function: 	This function reads concentration value (used only with O3 sensor)
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * 				NO2_conc: NO2 concentration in ppm to compensate the cross-sensitivity. Only for O3 sensor
 * Returns: 	The concetration value in ppm / %LEL, -1000 if error.
*/
float Gas::getConc(uint8_t resolution, float NO2_conc)
{
	float BME280_temp;

	BME280_temp = BME.getTemperature(BME280_OVERSAMP_1X, 0);
	return getConc(resolution, BME280_temp, NO2_conc);
}

/* Function: 	This function reads concentration value (base function)
 * Parameters:	resolution: resolution value for ADC (RES_12_BIT, RES_14_BIT, RES_16_BIT or RES_18_BIT)
 * 				temperature: ambient temperature for sensor compensation (-1000 if doesn't needed)
 * 				NO2_conc: NO2 concentration in ppm to compensate the cross-sensitivity. Only for O3 sensor
 * Returns: 	The concetration value in ppm / %LEL
 * 				-1 if the sensors is not initializated
 * 				-1000 if error.
*/
float Gas::getConc(uint8_t resolution, float temperature, float NO2_conc)
{

	float conc = 0;

	// Before to measure, check if the sensor is properly initializated
	if ((pwrGasPRORegister & (1 << sensor_config.socket)) == 0)
	{
		#if DEBUG_GASES_PRO>0
			PRINTLN_GASES_PRO(F("Error,sensor not started"));
		#endif
		// If not return -1
		return -1;
	}

	disableCommSockets();
	delay(10);

	// Enable communication with the AFE
	digitalWrite(sensor_config.i2c_pin, HIGH);
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

			conc = read3ElectrodeSensor( resolution, temperature);

			break;


		/***************************************
		* 			PELLISTOR BOARD			*
		***************************************/
		case LEL_AS:
		case CALIBRATION_PEL:

			conc = readPellistorSensor(resolution, temperature);

			break;

		/***************************************
		* 				NDIR BOARD				 *
		***************************************/
		case NDIR_CO2_SS:
		case CALIBRATION_NDIR:

			conc = readNDIR(resolution);

			break;


		/***************************************
		* 	O3 AND OXIDISING BOARD		*
		***************************************/
		case O3_AS:
		case CALIBRATION_4E:

			if(sensor_config.AFE_ver == 3)
			{
				conc = read4ElectrodeSensorv301(resolution, temperature, NO2_conc);
			}
			else
			{
				conc = read4ElectrodeSensorv100(resolution, temperature);
			}

			break;

		/***************************************
		* 	4-ELECTRODE AMPERIOMETRIC BOARD	*
		***************************************/
		case NO2_AS:
		case NO_AS:
		case SO2_AS:
		case CO_AS:

			if (sensor_config.AFE_ver == 3)
			{
				conc = read4ElectrodeSensorv301(resolution, temperature, 0);
			}
			else
			{
				conc = read4ElectrodeSensorv100(resolution, temperature);
			}
			break;
	}
    return conc;
}



/*
 * Function: disable I2C lines in the sensor board to avoid I2C interferences
 * while working with an AFE (eeprom memories have the same i2c address)
 *
 *
 */
uint8_t Gas::disableCommSockets()
{
	if (WaspRegisterSensor & REG_CITIES_PRO)
	{
		// Cities PRO board I2C pins
		pinMode(GP_I2C_SOCKET_1_C, OUTPUT);	// SCP_I2C_SOCKET_1_C
		pinMode(GP_I2C_SOCKET_3_F, OUTPUT); // SCP_I2C_SOCKET_3_F
		pinMode(GP_I2C_SOCKET_5_B, OUTPUT); // SCP_I2C_SOCKET_5_B
		digitalWrite(GP_I2C_SOCKET_1_C, LOW);
		digitalWrite(GP_I2C_SOCKET_3_F, LOW);
		digitalWrite(GP_I2C_SOCKET_5_B, LOW);
		delay(1);

		return 0;
	}

	// Gases PRO board I2C pins
	pinMode(GP_I2C_SOCKET_1_C, OUTPUT);
	pinMode(GP_I2C_SOCKET_2_E, OUTPUT);
	pinMode(GP_I2C_SOCKET_3_F, OUTPUT);
	pinMode(GP_I2C_SOCKET_4_A, OUTPUT);
	pinMode(GP_I2C_SOCKET_5_B, OUTPUT);
	pinMode(GP_I2C_SOCKET_6, OUTPUT);
	digitalWrite(GP_I2C_SOCKET_1_C, LOW);
	digitalWrite(GP_I2C_SOCKET_2_E, LOW);
	digitalWrite(GP_I2C_SOCKET_3_F, LOW);
	digitalWrite(GP_I2C_SOCKET_4_A, LOW);
	digitalWrite(GP_I2C_SOCKET_5_B, LOW);
	digitalWrite(GP_I2C_SOCKET_6, LOW);
	delay(1);

	return 0;
}


void Gas::zeroPointSet()
{

  float auxiliar_offset = 0.0;
  float working_offset = 0.0;
  uint8_t aux_vector[4];

  const uint8_t MEASURES = 8;

  PWR.deepSleep("00:00:01:00", RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON);

  //Enable communication with the AFE
  digitalWrite(sensor_config.i2c_pin, HIGH);
  delay(100);

  for (uint8_t i = 0; i < MEASURES; i++)
  {
    working_offset += readWorkingElectrode4E();
    auxiliar_offset += readAuxiliaryElectrode4E();
  }

  auxiliar_offset = auxiliar_offset/ MEASURES;
  working_offset = working_offset / MEASURES;

  #if DEBUG_GASES_PRO > 0
    PRINT_GASES_PRO_DATA("AUXOFFSET get: ",auxiliar_offset, " uA\n");
    PRINT_GASES_PRO_DATA("WORKING get: ", working_offset, " uA\n");
  #endif

  sensor_config.auxiliar_offset = auxiliar_offset;
  sensor_config.working_offset = working_offset;

  memcpy(aux_vector, &working_offset, sizeof(working_offset));
  Wire.writeBytes(I2C_ADDRESS_GASPRO_E2PROM, OFFSET_WRK_ELEC, aux_vector, 4);
  delay(10);

  memcpy(aux_vector, &auxiliar_offset, sizeof(auxiliar_offset));
  Wire.writeBytes(I2C_ADDRESS_GASPRO_E2PROM, OFFSET_AUX_ELEC, aux_vector, 4);
  delay(10);

  aux_vector[0] = 0xAA;
  Wire.writeBytes(I2C_ADDRESS_GASPRO_E2PROM, ZERO_POINT_OK, aux_vector, 1);

  //Disable communication with the AFE
  digitalWrite(sensor_config.i2c_pin, LOW);
  delay(100);



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

	#if DEBUG_GASES_PRO>0
		USB.println(F("********"));
		USB.println(F("Autogain"));
		USB.println(F("********\r\n"));
	#endif

	//Enable communication with the AFE
	digitalWrite(sensor_config.i2c_pin, HIGH);
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
				USB.println(F("Starting autogain proccess for 3E"));
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
				USB.print(F("Upper limits: "));
				USB.print(MAX_RANGE_FACTOR * upper_range, DEC);
				USB.print(F("; "));
				USB.println(MIN_RANGE_FACTOR * upper_range, DEC);
				USB.print(F("Lower limits: "));
				USB.print(MAX_RANGE_FACTOR * lower_range, DEC);
				USB.print(F("; "));
				USB.println(MIN_RANGE_FACTOR * lower_range, DEC);
			#endif

			do
			{
				// Reads the ADC
				v_ADC = (MCP.readADC(	MCP3421_MEDIUM_RES,
										MCP3421_GAIN_1,
										MCP3421_VOLTS));
				v_ADC += (MCP.readADC(	MCP3421_MEDIUM_RES,
										MCP3421_GAIN_1,
										MCP3421_VOLTS));
				v_ADC /=2;

				#ifdef GAS_PRO_AUTOGAIN_DEBUG
					USB.print(F("Vref:"));
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
					USB.print(F("Process_reg: "));
					USB.println(process_reg, BIN);
				#endif

				switch (process_reg)
				{
					case 0x80:	//Decreases gain
					case 0x82:
					case 0x04:
					case 0x06:
						#ifdef GAS_PRO_AUTOGAIN_DEBUG
							USB.println(F("Decresaing Rgain"));
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
							USB.println(F("Incresaing Rgain"));
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
								USB.println(F("Vref low limit reached"));
							#endif
						}
						else
						{
							#ifdef GAS_PRO_AUTOGAIN_DEBUG
								USB.println(F("Decresaing Vref"));
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
							USB.print(F("Upper limits: "));
							USB.print(MAX_RANGE_FACTOR * upper_range, DEC);
							USB.print(F("; "));
							USB.println(MIN_RANGE_FACTOR * upper_range, DEC);
							USB.print(F("Lower limits: "));
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
								USB.println(F("Vref high limit reached"));
							#endif
						}
						else
						{
							#ifdef GAS_PRO_AUTOGAIN_DEBUG
								USB.println(F("Incresaing Vref"));
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
							USB.print(F("Upper limits: "));
							USB.print(MAX_RANGE_FACTOR * upper_range, DEC);
							USB.print(F("; "));
							USB.println(MIN_RANGE_FACTOR * upper_range, DEC);
							USB.print(F("Lower limits: "));
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
				USB.println(F("Starting autogain proccess for 4E"));
			#endif

			upper_range = 2048;
			lower_range = -2048;

			#ifdef GAS_PRO_AUTOGAIN_DEBUG
				USB.print(F("Upper limits: "));
				USB.print(MAX_RANGE_FACTOR * upper_range, DEC);
				USB.print(F("; "));
				USB.println(MIN_RANGE_FACTOR * upper_range, DEC);
				USB.print(F("Lower limits: "));
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
					USB.print(F("ADC value:"));
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
					USB.print(F("Process_reg: "));
					USB.println(process_reg, BIN);
				#endif

				switch (process_reg)
				{
					case 0x80:	//Decreases gain
					case 0x82:
					case 0x04:
					case 0x06:
						#ifdef GAS_PRO_AUTOGAIN_DEBUG
							USB.println(F("Decresaing Rgain"));
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
							USB.println(F("Incresaing Rgain"));
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
								USB.println(F("Vref low limit reached"));
							#endif
						}
						else
						{
							#ifdef GAS_PRO_AUTOGAIN_DEBUG
								USB.println(F("Decresaing Vref"));
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
								USB.println(F("Vref high limit reached"));
							#endif
						}
						else
						{
							#ifdef GAS_PRO_AUTOGAIN_DEBUG
								USB.println(F("Incresaing Vref"));
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
	digitalWrite(sensor_config.i2c_pin, LOW);

	#ifdef GAS_PRO_AUTOGAIN_DEBUG
		USB.println(F("End of autogain proccess"));
	#endif

	#if DEBUG_GASES_PRO>0
		USB.println(F("\r\n***End of autogain***\r\n"));
	#endif

	return ((v_steps << 4) & 0xF0) + (r_steps & 0x0F);
}

/* Function: 	This function converts concentration in ppm to %
 * Parameters:	ppm_conc: concentration in ppm
 * Returns: 	The concetration value in %
*/
float Gas::ppm2perc(float ppm_conc)
{
	#if DEBUG_GASES_PRO>0
		USB.println(F("********"));
		USB.println(F("ppm2perc"));
		USB.println(F("********\r\n"));
	#endif
	return (ppm_conc / 10000);
}

/* Function: 	This function converts concentration in ppm to ugm3
 * Parameters:	ppm_conc: concentration in ppm
 * Returns: 	The concetration value in %
*/
float Gas::ppm2ugm3(float ppm_conc)
{
	float aux_val;

	#if DEBUG_GASES_PRO>0
		USB.println(F("********"));
		USB.println(F("ppm2ugm3"));
		USB.println(F("********\r\n"));
	#endif

	aux_val = pgm_read_float(&table_ppm2ugm3[sensor_config.sensor_type]);
	return (ppm_conc * aux_val);

}


/* Function: 	This function converts temperature in Celsius degrees to Fahrenheit degrees
 * Parameters:	temp: concentration in Celsius degrees
 * Returns: 	The concetration value in Fahrenheit degrees
*/
float Gas::Celsius2Fahrenheit(float temp)
{
	#if DEBUG_GASES_PRO>0
		USB.println(F("*********************"));
		USB.println(F("Celsius to fahrenheit"));
		USB.println(F("*********************\r\n"));
	#endif
	return ((1.8 * temp) + 32);
}

//! MISCELANEUS
/* Function:	This function shows the information about the sensor
 * Return:	 	Nothing
 */
void Gas::showSensorInfo()
{
	PRINTLN_GASES_PRO(F("******************************************************"));

	char sensor_no[17];

	//Enable communication with the AFE
	digitalWrite(sensor_config.i2c_pin, HIGH);

	memset(sensor_no, '\0', sizeof(sensor_no));
	Wire.readBytes(I2C_ADDRESS_GASPRO_E2PROM, SENSOR_NO_REG, (uint8_t*)sensor_no, 16);

	//Disable communication with the AFE
	digitalWrite(sensor_config.i2c_pin, LOW);

	switch (sensor_config.socket)
	{
		case SOCKET_1:
		case SOCKET_C:
			PRINTLN_GASES_PRO(F("SOCKET -> C"));
			break;
		case SOCKET_2:
		case SOCKET_E:
			PRINTLN_GASES_PRO(F("SOCKET -> E"));
			break;
		case SOCKET_3:
		case SOCKET_F:
			PRINTLN_GASES_PRO(F("SOCKET -> F"));
			break;
		case SOCKET_4:
		case SOCKET_A:
			PRINTLN_GASES_PRO(F("SOCKET -> A"));
			break;
		case SOCKET_5:
		case SOCKET_B:
			PRINTLN_GASES_PRO(F("SOCKET -> B"));
			break;
		case SOCKET_6:
		case SOCKET_D:
			PRINTLN_GASES_PRO(F("SOCKET -> D"));
			break;
		case 0:	// Calibration
			PRINTLN_GASES_PRO(F("CALIBRATION"));
			break;
	}

	PRINT_GASES_PRO(F("SERIAL NUMBER: "));
	USB.println(sensor_no);

	PRINT_GASES_PRO(F("AFE VER: "));
	USB.println(sensor_config.AFE_ver, DEC);

	PRINT_GASES_PRO(F("SENSOR TYPE: "));

	switch (sensor_config.sensor_type)
	{
		case CL2_SS:
			USB.println(F("Cl2-3E"));
			break;
		case CO_SS_SEC:
			USB.println(F("CO-3E"));
			break;
		case ETO_SS:
			USB.println(F("ETO-3E"));
			break;
		case H2_SS_SEC:
			USB.println(F("H2-3E"));
			break;
		case H2S_SS_SEC:
			USB.println(F("H2S-3E"));
			break;
		case HCL_SS:
			USB.println(F("HCl-3E"));
			break;
		case HCN_SS:
			USB.println(F("HCN-3E"));
			break;
		case NH3_SS:
			USB.println(F("NH3-3E"));
			break;
		case NO_SS:
			USB.println(F("NO-3E"));
			break;
		case NO2_SS_CLE:
			USB.println(F("NO2-3E"));
			break;
		case O2_SS:
			USB.println(F("O2-3E"));
			break;
		case PH3_SS:
			PRINTLN_GASES_PRO(F("PH3-3E"));
			break;
		case SO2_SS:
			USB.println(F("SO2-3E"));
			break;
		case LEL_AS:
			USB.println(F("Combustible gas pellistor"));
			break;
		case O3_AS:
			USB.println(F("O3-4E"));
			break;
		case NDIR_CO2_SS:
			USB.println(F("CO2"));
			break;
		case NO2_AS:
			USB.println(F("NO2-4E"));
			break;
		case NO_AS:
			USB.println(F("NO-4E"));
			break;
		case SO2_AS:
			USB.println(F("SO2-4E"));
			break;
		case CO_AS:
			USB.println(F("CO-4E"));
			break;
		default:
			USB.println(sensor_config.sensor_type, DEC);
			break;
	}


	PRINT_GASES_PRO(F("SENSITIVITY: "));
	USB.printFloat(sensor_config.m_conc, 3);

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

	PRINT_GASES_PRO(F("BASELINE: "));
	USB.printFloat(sensor_config.baseline, 3);

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

	if ((sensor_config.sensor_type == O3_AS) ||
		(sensor_config.sensor_type == NO2_AS) ||
		(sensor_config.sensor_type == NO_AS) ||
		(sensor_config.sensor_type == SO2_AS) ||
		(sensor_config.sensor_type == CO_AS) ||
		(sensor_config.sensor_type == CALIBRATION_4E))
	{
		PRINT_GASES_PRO(F("O3-NO2 SENSITIVITY: "));
		USB.printFloat(sensor_config.OX_NO2_sens, 3);
		USB.println(F(" nA/ppm"));

		if(sensor_config.AFE_ver == 3)
		{
			PRINT_GASES_PRO(F("AUX BASELINE: "));
			USB.printFloat(sensor_config.aux_baseline, 3);
			USB.println(F(" nA"));
		}
	}

	if ((sensor_config.sensor_type == O3_AS) ||
		(sensor_config.sensor_type == NO2_AS) ||
		(sensor_config.sensor_type == NO_AS) ||
		(sensor_config.sensor_type == SO2_AS) ||
		(sensor_config.sensor_type == CO_AS) ||
		(sensor_config.sensor_type == CALIBRATION_4E))
	{
		PRINT_GASES_PRO(F("WORK ADJ: "));
		USB.printFloat(sensor_config.calibration[0][0], 3);
		USB.print(F(" | "));
		USB.println(sensor_config.calibration[0][1]);

    PRINT_GASES_PRO(F("AUXL ADJ: "));
		USB.printFloat(sensor_config.calibration[1][0], 3);
		USB.print(F(" | "));
		USB.println(sensor_config.calibration[1][1]);

    PRINT_GASES_PRO(F("WORK OFFSET: "));
    USB.printFloat(sensor_config.working_offset, 3);
    USB.println();

    PRINT_GASES_PRO(F("AUX OFFSET: "));
    USB.printFloat(sensor_config.auxiliar_offset, 3);
    USB.println();

    PRINT_GASES_PRO(F("ZERO STATUS: "));
    USB.printHex(sensor_config.zeroPointOK);
    USB.println();

	}
	else if ((sensor_config.sensor_type == LEL_AS)
		||	(sensor_config.sensor_type == NDIR_CO2_SS)
		||	(sensor_config.sensor_type == CALIBRATION_NDIR)
		||	(sensor_config.sensor_type == CALIBRATION_PEL))
	{
		PRINT_GASES_PRO(F("Adjust values:"));
		USB.printFloat(sensor_config.calibration[0][0], 3);
		USB.print(F(" ; "));
		USB.printFloat(sensor_config.calibration[0][1], 3);
		USB.println();
	}
	else
	{
		PRINTLN_GASES_PRO(F("Calibration table"));
		for (int x = 0; x < 7; x++)
		{
			PRINT_GASES_PRO((int)x);
			USB.print(F(": "));
			USB.print(sensor_config.calibration[x][0]);
			USB.print(F(" ; "));
			USB.println(sensor_config.calibration[x][1]);
		}
		if(sensor_config.AFE_ver >= 3)
		{
			PRINT_GASES_PRO((int)7);
			USB.print(F(": "));
			USB.print(sensor_config.calibration[7][0]);
			USB.print(F(" ; "));
			USB.println(sensor_config.calibration[7][1]);
		}
	}

  PRINTLN_GASES_PRO(F("******************************************************"));
}


//! ONlY FOR MANUFACTURER
/* Function: 	This function reads the value for working electrode
 * Returns: 	Value from working electrode
*/
float Gas::readWorkingElectrode3E()
{
	float V_conc = 0;
	float conc = 0;
	int r_gain_LMP;

	float V_ref=0, R_gain;


	// Selects amperiometric mode
	LMP.setModeReg(	LMP91000_MODEC_REG_FET_NOT_SHORTED,
					LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPEROMETRIC);
	delay(100);


	for ( int i = 0; i < 4; i++)
	{
		// Reads the ADC
		V_conc += (MCP.readADC(MCP3421_ULTRA_HIGH_RES, MCP3421_GAIN_1, MCP3421_VOLTS));
	}

	V_conc /= 4;

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
		case 0:
			R_gain = 1000000;
			break;
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
	digitalWrite(sensor_config.i2c_pin, LOW);

	#if DEBUG_GASES_PRO>0
		USB.print(F("Average measure: "));
		USB.print(V_conc);
		USB.print(F(" mV"));

		USB.print(F(" || V_ref: "));
		USB.print(V_ref);
		USB.print(F(" mV"));

		USB.print(F(" || R_gain: "));
		USB.print(R_gain, DEC);
		USB.println(F(" Ohms"));
	#endif

  // Vconc(mV) - Vzero(mV)
	conc = (V_conc - V_ref);

	#if DEBUG_GASES_PRO>0
		USB.print(F("Reference compensation: "));
		USB.print(conc);
		USB.println(F(" mV"));
	#endif

  // V(mV) --> I(uA)
	conc = (conc / R_gain) * 1000;

	#if DEBUG_GASES_PRO>0
		USB.print(F("Current: "));
		USB.print(conc);
		USB.println(F(" uA"));
	#endif

	if(r_gain_LMP != 0)
	{
		conc =  ((conc + sensor_config.calibration[r_gain_LMP-1][0]) / (sensor_config.calibration[r_gain_LMP-1][1]));		// Adjust resistor
	}
	else
	{
		conc =  ((conc + sensor_config.calibration[7][0]) / (sensor_config.calibration[7][1]));		// Adjust resistor
	}

	#if DEBUG_GASES_PRO>0
		USB.print(F("AFE compensation: "));
		USB.print(conc);
		USB.println(F(" uA"));
	#endif

	conc = (conc * 1000) / sensor_config.m_conc;	// I(nA) --> concentración(ppm)

	#if DEBUG_GASES_PRO>0
		USB.println(F("---------------------------------"));
		USB.print(F("|Concentration: "));
		USB.print(conc);
		USB.println(F(" ppm|"));
		USB.println(F("---------------------------------"));
	#endif

	#if DEBUG_GASES_PRO>0
		USB.println(F("\r\n***End of working electrode 3E***\r\n"));
	#endif

	return conc;

}

/* Function: 	This function reads the value for working electrode
 * Returns: 	Value from working electrode
*/
float Gas::readWorkingElectrode4E()
{

	float V_conc = 0;
	float aux_val;

	// Selects amperiometric mode
	LMP.setModeReg(LMP91000_MODEC_REG_FET_NOT_SHORTED,
					       LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPEROMETRIC);

	// Read WE
	for ( int i = 0; i < 8; i++)
	{
		// Reads the ADC
		aux_val = MCP.readADC(I2C_ADDRESS_GASPRO_MCP3421_A1, MCP3421_ULTRA_HIGH_RES, MCP3421_GAIN_1, MCP3421_VOLTS);
		V_conc += aux_val;
	}

	V_conc /= -8;

 	#if DEBUG_GASES_PRO>1
		PRINT_GASES_PRO_DATA("VOL-WRK: ", V_conc , " mV")
	#endif

	// V(mV) --> I(uA)
	return V_conc / 110;
}

/* Function: 	This function reads the value for auxiliary electrode
 * Returns: 	Value from auxiliary electrode
*/
float Gas::readAuxiliaryElectrode4E()
{
	float V_conc_aux = 0;
	float aux_val;

	// Selects amperiometric mode
	LMP.setModeReg(  LMP91000_MODEC_REG_FET_NOT_SHORTED,
					         LMP91000_MODEC_REG_PWR_MODE_3_LEAD_AMPEROMETRIC);

	// Measuring Auxiliar Electrode
	for ( int i = 0; i < 8; i++)
	{
		//Reads the ADC
		aux_val = MCP.readADC(	I2C_ADDRESS_GASPRO_MCP3421_A2, MCP3421_ULTRA_HIGH_RES, MCP3421_GAIN_1, MCP3421_VOLTS);
		V_conc_aux += aux_val;
	}

	V_conc_aux /= -8;

 	#if DEBUG_GASES_PRO>1
	PRINT_GASES_PRO_DATA("VOL-AUX: ", V_conc_aux , " mV")
	#endif

	return V_conc_aux / 110;
}



//******************************************************************************
// BME Sensor Class functions
//******************************************************************************

/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
bmeGasesSensor::bmeGasesSensor()
{
}



/*!
 * @brief	switch on the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void bmeGasesSensor::ON()
{
  if (pwrGasPRORegister == 0x00)
  {
    #if DEBUG_GASES_PRO>0
      PRINTLN_GASES_PRO(F("3V3 to ON"));
    #endif
    // enable I2C isolator
    pinMode(GP_I2C_MAIN_EN, OUTPUT);
    digitalWrite(GP_I2C_MAIN_EN, HIGH);
    // Power on 3V3
    PWR.setSensorPower(SENS_3V3, SENS_ON);
  }

  // init BME
  BME.ON();

}



/*!
 * @brief	switch off the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void bmeGasesSensor::OFF()
{
  // If there aren't powered AFE modules, turns off the 3V3 power supply
  if (pwrGasPRORegister == 0x00)
  {
    #if DEBUG_GASES_PRO>0
      PRINTLN_GASES_PRO(F("3V3 to OFF"));
    #endif
    // Power off 3V3
    PWR.setSensorPower(SENS_3V3, SENS_OFF);
    // disable I2C isolator
    pinMode(GP_I2C_MAIN_EN, OUTPUT);
    digitalWrite(GP_I2C_MAIN_EN, LOW);
  }
  delay(100);
}


/*!
 *  @brief Read BME temperature value
 *  @return	temperature value
 *
 */
float bmeGasesSensor::getTemperature()
{
  return BME.getTemperature(BME280_OVERSAMP_1X, 0);
}


/*!
 *  @brief Read BME humidity value
 *  @return	humidity value
 *
 */
float bmeGasesSensor::getHumidity()
{
	return BME.getHumidity(BME280_OVERSAMP_1X);
}


/*!
 *  @brief Read BME pressure value
 *  @return	pressure value
 *
 */
float bmeGasesSensor::getPressure()
{
  return BME.getPressure(BME280_OVERSAMP_1X, 0);
}






//******************************************************************************
// Ultrasound Sensor Class functions
//******************************************************************************

/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
ultrasoundGasesSensor::ultrasoundGasesSensor()
{
}



/*!
 * @brief	switch on the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void ultrasoundGasesSensor::ON()
{
  if ((pwrGasPRORegister == 0x00) ||
    ((WaspRegister & REG_3V3) == 0))
  {
    #if DEBUG_GASES_PRO>0
      PRINTLN_GASES_PRO(F("3V3 to ON"));
    #endif
    // enable I2C isolator
    pinMode(GP_I2C_MAIN_EN, OUTPUT);
    digitalWrite(GP_I2C_MAIN_EN, HIGH);
    // Power on 3V3
    PWR.setSensorPower(SENS_3V3, SENS_ON);
  }
}



/*!
 * @brief	switch off the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void ultrasoundGasesSensor::OFF()
{
  // If there aren't powered AFE modules, turns off the 3V3 power supply
  if (pwrGasPRORegister == 0x00)
  {
    #if DEBUG_GASES_PRO>0
      PRINTLN_GASES_PRO(F("3V3 to OFF"));
    #endif
    // Power off 3V3
    PWR.setSensorPower(SENS_3V3, SENS_OFF);
    // disable I2C isolator
    pinMode(GP_I2C_MAIN_EN, OUTPUT);
    digitalWrite(GP_I2C_MAIN_EN, LOW);
  }
	delay(100);
}


/*!
 * @brief 	This function performs a distance measurement
 * @return 	distance in cm.
 * 		  	9000 if error reading the distance
 * 			10000 if error reading the sensor
 */
uint16_t ultrasoundGasesSensor::getDistance()
{
	return Ultrasound.getDistance();
}






//******************************************************************************
// Luxes Sensor Class functions
//******************************************************************************

/*!
 * @brief	Constructor of the class
 * @param 	void
 * @return	void
 */
luxesGasesSensor::luxesGasesSensor()
{
}



/*!
 * @brief	switch on the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void luxesGasesSensor::ON()
{
  if (pwrGasPRORegister == 0x00)
  {
    #if DEBUG_GASES_PRO>0
      PRINTLN_GASES_PRO(F("3V3 to ON"));
    #endif
    // enable I2C isolator
    pinMode(GP_I2C_MAIN_EN, OUTPUT);
    digitalWrite(GP_I2C_MAIN_EN, HIGH);
    // Power on 3V3
    PWR.setSensorPower(SENS_3V3, SENS_ON);
  }

  // init luxes sensor
  TSL.ON();
}



/*!
 * @brief	switch off the corresponding 3v3 switch
 * @param 	void
 * @return	void
 */
void luxesGasesSensor::OFF()
{
  // If there aren't powered AFE modules, turns off the 3V3 power supply
  if (pwrGasPRORegister == 0x00)
  {
    #if DEBUG_GASES_PRO>0
      PRINTLN_GASES_PRO(F("3V3 to OFF"));
    #endif
    // Power off 3V3
    PWR.setSensorPower(SENS_3V3, SENS_OFF);
    // disable I2C isolator
    pinMode(GP_I2C_MAIN_EN, OUTPUT);
    digitalWrite(GP_I2C_MAIN_EN, LOW);
  }
	// switch off delay for better preformance before
	// entering sleep mode after calling this function
	delay(100);
}

/*!
 * @brief 	This function performs a lux measurement
 * @return 	luxes if ok
 * 			-1 if error
 */
uint32_t luxesGasesSensor::getLuminosity()
{
  return getLuminosity(TSL2561_GAIN_1, TSL2561_HIGH_RES);

}

/*!
 * @brief 	This function performs a lux measurement
 * @return 	luxes if ok
 * 			-1 if error
 */
uint32_t luxesGasesSensor::getLuminosity(bool gain)
{
  return getLuminosity(gain, TSL2561_HIGH_RES);
}


/*!
 * @brief 	This function performs a lux measurement
 * @param   Gain: INDOOR, OUTDOOR
 *          Resolution: TSL2561_HIGH_RES, TSL2561_MED_RES, TSL2561_LOW_RES
 * @return 	luxes if ok
 * 			    -1 if error
 */
uint32_t luxesGasesSensor::getLuminosity(bool gain, uint8_t res)
{

  uint8_t error;
	error = TSL.getLuminosity(res, gain);

	if (error == 0)
	{
		return TSL.lux;
	}
  else{
    return (uint32_t)-1;
  }
}
