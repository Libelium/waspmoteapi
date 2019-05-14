/*
 *  Copyright (C) 2019 Libelium Comunicaciones Distribuidas S.L.
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
 *  Version:		3.6
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, David Cuartielles, Yuri Carmona
 */
 
#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif


#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// Variables ////////////////////////////////////////////////////////////////

// these two variables have been moved to the general system
uint8_t intIPRA = 0;
uint8_t intIPRB = 0;

// Constructors ////////////////////////////////////////////////////////////////

WaspPWR::WaspPWR()
{
  // nothing to do when constructing
}

// Private Methods /////////////////////////////////////////////////////////////

/* setIPF ( peripheral )
 * - sets a certain internal peripheral on 
 * - to control the pwr on the different internal peripherals it is
 *   convenient to read MCU's manual on pgs. 56/57
 * FIXME: missing all the Timers and UART to reduce consumption
 */
void WaspPWR::setIPF(uint8_t peripheral) 
{
	setIPF_(peripheral);
	intIPRA = IPRA;
}

/* resetIPR ( peripheral )
 * - resets a certain internal peripheral to off 
 * - to control the pwr on the different internal peripherals it is
 *   convenient to read MCU's manual on pgs. 56/57
 * FIXME: missing all the Timers and UART to reduce consumption
 */
void WaspPWR::resetIPF(uint8_t peripheral) 
{
	resetIPF_(peripheral);
	intIPRA = IPRA;
}

/* uint8_t getIPR ( )
 * - answers with the whole IPR 
 */
uint8_t WaspPWR::getIPF() 
{
	return intIPRA;
}


// Public Methods //////////////////////////////////////////////////////////////



/* setSensorPower( type, mode) - set ON/OFF 3V3 or 5V switches
 *
 * It sets ON/OFF 3V3 or 5V switches
 * type: SENS_3V3 or SENS_5V
 * mode: SENS_ON or SENS_OFF
 */
void WaspPWR::setSensorPower(uint8_t type, uint8_t mode)
{
	pinMode(SENS_PW_3V3,OUTPUT);
	pinMode(SENS_PW_5V,OUTPUT);
	
	switch (type)
	{
		case SENS_3V3: 	
						if (mode == SENS_ON) 
						{
							WaspRegister |= REG_3V3;
							digitalWrite(SENS_PW_3V3,HIGH);
						}
						else if (mode == SENS_OFF) 
						{
							WaspRegister &= ~REG_3V3;
							digitalWrite(SENS_PW_3V3,LOW);
							
						}						
						break;
						
		case SENS_5V:	
						if (mode == SENS_ON) 
						{
							WaspRegister |= REG_5V;
							digitalWrite(SENS_PW_5V,HIGH);
							delay(1);
						}
						else if (mode == SENS_OFF) 
						{
							WaspRegister &= ~REG_5V;
							digitalWrite(SENS_PW_5V,LOW);
						}
						break;
						
		default:		break;
	}
}


/* setWatchdog( mode, timer) - enables or disables watchdog interruption
 *
 * It enables or disables watchdog interruption.
 *
 * 'mode' --> if mode=WTD_ON, it enables watchdog interruption. If mode=WTD_OFF, 
 * it disables watchdog interruption.
 * 'timer' --> it specifies the time before the watchdog activates the 
 * interruption. Possible values are:
 * 	WTD_16MS	0
 *	WTD_32MS	1
 *	WTD_64MS	2
 *	WTD_128MS	3
 *	WTD_250MS	4
 *	WTD_500MS	5
 *	WTD_1S		6
 *	WTD_2S		7
 *	WTD_4S		8
 *	WTD_8S		9
 * 
 * It returns nothing
 */
void WaspPWR::setWatchdog(uint8_t mode, uint8_t timer)
{
	if(mode==WTD_ON)
	{
		enableInterrupts(WTD_INT);
		setup_watchdog(timer); // set watchdog interrupt to wake up from Sleep Power Down Mode
	}
	
	if(mode==WTD_OFF)
	{
		disableInterrupts(WTD_INT);
		off_watchdog();
	}
}


/* switchesOFF() - switches off the Waspmote switches specified
 *
 * It switches off all Waspmote switches
 */
void WaspPWR::switchesOFF(uint8_t option)
{	
	// check if main 3V3 will be kept
	// in that case sleep the eeprom memory
	if (!((ACC.accInt == NO_INT) && (option == ALL_OFF)))
	{
		if (_boot_version >= 'G')
		{
			uint8_t error = 0;
			uint8_t I2C_EEPROM_INFO[] = { 0x09, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00};
			eeprom.ON();
			error += eeprom.sendCommand(I2C_EEPROM_INFO);
			error += eeprom.sleepCommand();

			if (error == 0) 
			{
				Utils.setLED(LED0, LED_OFF);		
			}
			else
			{
				Utils.setLED(LED0, LED_ON);
			}
		}
	}
	
	// power down the accelerometer when ACC_INT is not used
	if (ACC.accInt == NO_INT)
	{
		// switch on if neccesary
		if (!ACC.isON)
		{
			ACC.ON();
		}
		
		// set power-down mode
		ACC.setMode(ACC_POWER_DOWN);
	}	
	
	// Switch off both multiplexers in UART_0 and UART_1
	Utils.muxOFF();	

	// set the XBee monitorization pin to zero
	pinMode(XBEE_MON, OUTPUT);
	digitalWrite(XBEE_MON, LOW);	

	// set this pin LOW to decrease consumption
	// if hibernate is not used
	pinMode(RTC_SLEEP, OUTPUT);
	digitalWrite(RTC_SLEEP, LOW);
		
	// unset I2C bus        
    //~ pinMode(I2C_SDA,OUTPUT);
	//~ digitalWrite(I2C_SDA,LOW);
	//~ pinMode(I2C_SCL,OUTPUT);
	//~ digitalWrite(I2C_SCL,LOW);
	
	// switch Analog to Digital Converter OFF
	cbi(ADCSRA,ADEN);
	
	// Disable MEM_PW and SS_PIN not to waste 
	// battery from SD when Waspmote is asleep
  	pinMode(SD_SS, OUTPUT);
	digitalWrite(SD_SS, LOW);
	pinMode(MEM_PW,OUTPUT);
	digitalWrite(MEM_PW,LOW);
	SPI.isSD = false;
	
	// Set down SOCKET0 SPI SS pin
	pinMode(SOCKET0_SS,OUTPUT);
	digitalWrite(SOCKET0_SS,LOW);
	
	// Switch off sensor board power supply
	if ((option == ALL_OFF) || (option == SENS_OFF) || (option == SOCKET0_ON))
	{	
		// switch OFF sensor boards
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		PWR.setSensorPower(SENS_5V, SENS_OFF);		
	}
	
	// close UART0
	closeSerial(SOCKET0);
	
	// switch off SOCKET0 if needed
	if ((option == ALL_OFF) || (option == SOCKET0_OFF) || (option == SENSOR_ON))
	{	
		// set SOCKET0 power supply off
		PWR.powerSocket(SOCKET0, LOW);
		
		// update Waspmote Register
		WaspRegister &= ~(REG_SOCKET0);
	}	
	
	// close UART1
	closeSerial(SOCKET1);
	// set SOCKET1 power supply off
	PWR.powerSocket(SOCKET1, LOW);	
	
	// set Expansion board power supply off	unless a 
	// Smart Cities board remains powered on 
	if (((option == ALL_OFF) || (option == SENS_OFF) || (option == SOCKET0_ON))
		&&  !(WaspRegisterSensor & REG_CITIES_V14) 
		&&  !(WaspRegisterSensor & REG_CITIES_V15))
	{
		pinMode(DIGITAL6, OUTPUT);
		digitalWrite(DIGITAL6, LOW);
	}
	
	// switch off the battery monitor power supply
	pinMode(BAT_MONITOR_PW,OUTPUT);
	digitalWrite(BAT_MONITOR_PW,LOW);
	
	// switch off monitoring pin
	pinMode(BAT_MONITOR,OUTPUT);
	digitalWrite(BAT_MONITOR,LOW);
		
	// check if an Cities PRO Sensor Board is used. 
	if (WaspRegisterSensor & REG_CITIES_PRO)
	{
		// disable I2C isolator
		digitalWrite(ANA0, LOW);
	}
	
	// check if a Smart Metering board has been switched and proceed to disable 
	// the digital pins so as not to waste energy
	if (WaspRegisterSensor & REG_METERING)
	{
		setSensorPower(SENS_3V3,SENS_ON);
		pinMode(DIGITAL3, OUTPUT);
		pinMode(DIGITAL4, OUTPUT);
		digitalWrite(DIGITAL3, HIGH);
		digitalWrite(DIGITAL4, HIGH);
	}
	
	// check if a Gases Sensor Board is used. In this case, switch off the 
	// digital pins so as not to waste energy
	if (WaspRegisterSensor & REG_GASES)
	{
		digitalWrite(DIGITAL4,LOW);
	}
	
	// check if an Agriculture Sensor Board is used. In this case, 
	// switch off the digital pins so as not to waste energy
	if (WaspRegisterSensor & REG_AGRICULTURE)
	{
		// switch off sensors power supply
		digitalWrite(DIGITAL7, LOW);
		digitalWrite(DIGITAL1, LOW);
		digitalWrite(DIGITAL5, LOW);
		digitalWrite(DIGITAL3, LOW);
		digitalWrite(DIGITAL6, LOW);
		digitalWrite(ANA0, LOW);
	}
	
	// set the interruption line down
	pinMode(MUX_RX, INPUT);
	digitalWrite(MUX_RX, LOW);
		
	// set the interruption line high
//~ 	pinMode(MUX_TX, INPUT);
//~ 	digitalWrite(MUX_TX, HIGH);	

}


/* switchesON() - switches on all Waspmote switches
 *
 * It switches on all Waspmote switches
 */
void WaspPWR::switchesON(uint8_t option)
{
	// switch Analog to Digital Converter ON
	sbi(ADCSRA, ADEN);        		

	// check if an Cities PRO Sensor Board is used. 
	if ((WaspRegisterSensor & REG_CITIES_PRO) && ((option == SENSOR_ON) || (option == ALL_ON)))
	{
		// enable I2C isolator
		digitalWrite(ANA0, HIGH);
	}
}


/* sleep() - sets the microcontroller to the lowest consumption sleep mode
 *
 * It sets the microcontroller to the lowest consumption sleep mode. Before setting this state, some interruption
 * should be enabled to be able to wake up the microcontroller from this state.
 *
 * It switches off all the switches on the Waspmote board.
 *
 * It returns nothing.
 */
void WaspPWR::sleep(uint8_t option)
{
	sleep(0xFF, option);
}


/* sleep(timer) - sets the microcontroller to the lowest consumption sleep mode
 *
 * It sets the microcontroller to the lowest consumption sleep mode. It enables
 * watchdog interruption to be able to wake up the microcontroller after 'timer' 
 * time
 *
 * 'timer' --> it specifies the time before the watchdog activates the 
 * interruption. Possible values are:
 * 	WTD_16MS	0
 *	WTD_32MS	1
 *	WTD_64MS	2
 *	WTD_128MS	3
 *	WTD_250MS	4
 *	WTD_500MS	5
 *	WTD_1S		6
 *	WTD_2S		7
 *	WTD_4S		8
 *	WTD_8S		9
 * 
 * It switches off all the switches on the Waspmote board.
 *
 * It returns nothing.
 */
void WaspPWR::sleep(uint8_t	timer, uint8_t option)
{	
	// enable the microcontroller sleep mode
	sleep_enable(); 
    
    // Switch off RTC (Waspv12)
	RTC.ON();
	RTC.OFF();
    
	// switches off depending on the option selected       
	switchesOFF(option);
	
	// mandatory delay to wait for MUX_RX stabilization 
	// after switching off the sensor boards 
	delay(100);	
	
	// switch off main power supply when needed:
	// -> ACC interruption is disabled
	// -> Sensor interruption is disabled
	// -> XBee interruption is disabled
	if ((ACC.accInt == NO_INT) && (option == ALL_OFF))
	{
		digitalWrite(POWER_3V3, LOW);
	}

	// *** set sleep mode ***
	// check interruption pins and register are ok
	if (!digitalRead(MUX_RX))
	{
		// set sleep mode
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		
		if (timer != 0xFF)
		{
			// set watchdog timer to cause interruption for selected time
			setWatchdog(WTD_ON, timer);		
		}
		sleep_mode();
	}
	// wake up here
	sleep_disable();
		
	// switch on main power supply
	digitalWrite(POWER_3V3,HIGH);
	
	if (intFlag & RTC_INT)
	{
		RTC.ON();
		RTC.clearAlarmFlag();
	}
	
	// re-activate what is needed
	switchesON(option);
}



/* 
 * deepSleep()
 *
 * It sets the microcontroller to the sleep mode. It enables RTC interruption to 
 * be able to wake up the microcontroller when the RTC alarm is generated. It 
 * uses Alarm1 on the RTC due to this Alarm. It switches off all the switches on 
 * the Waspmote board.
 * 
 * Parameters:	
 * 	time2wake: 	it specifies the time at which the RTC alarm will activate. It 
 * 				must follow the next format:"DD:HH:MM:SS"
 * 	offset:		it specifies if 'time2wake' is added to the actual time or if 
 * 				this time is set as the alarm
 * 	mode: 		it specifies the mode for RTC alarm
 *
 * 
 * Return: void
 */
void WaspPWR::deepSleep(const char* time2wake, 
						uint8_t offset, 
						uint8_t mode)
{
	return deepSleep(time2wake, offset, mode, ALL_OFF);
}


/* 
 * deepSleep()
 *
 * It sets the microcontroller to the sleep mode. It enables RTC interruption to 
 * be able to wake up the microcontroller when the RTC alarm is generated. It 
 * uses Alarm1 on the RTC due to this Alarm. 
 * 
 * Parameters:	
 * 	time2wake: 	it specifies the time at which the RTC alarm will activate. It 
 * 				must follow the next format:"DD:HH:MM:SS"
 * 	offset:		it specifies if 'time2wake' is added to the actual time or if 
 * 				this time is set as the alarm
 * 	mode: 		it specifies the mode for RTC alarm
 * 	option: 	Option to switch off when entering deep sleep
 *
 * 
 * Return: void
 */
void WaspPWR::deepSleep(const char* time2wake, 
						uint8_t offset, 
						uint8_t mode, 
						uint8_t option)
{	
	// enable the microcontroller sleep mode
	sleep_enable();
	
	// switches off depending on the option selected  
	switchesOFF(option);
	
	// mandatory delay to wait for MUX_RX stabilization 
	// after switching off the sensor boards 
	delay(100);
	
	// RTC ON
	RTC.ON();
	// set Alarm
	RTC.setAlarm1(time2wake,offset,mode); 
	// get backup of selected Alarm	
	uint8_t day_aux = RTC.day_alarm1; 
	uint8_t hour_aux = RTC.hour_alarm1; 
	uint8_t minute_aux = RTC.minute_alarm1; 
	uint8_t second_aux = RTC.second_alarm1; 
	// get Alarm
	RTC.getAlarm1();
	// check Alarm was correctly set	
	if(	( day_aux != RTC.day_alarm1 ) 
	||	( hour_aux != RTC.hour_alarm1 )
	||	( minute_aux != RTC.minute_alarm1 )
	||	( second_aux != RTC.second_alarm1 ) )
	{
		RTC.disableAlarm1();
		sleep_disable();
		RTC.OFF();
		I2C.recover();
		USB.println(F("[PWR] deepSleep RTC error"));
		return (void)0;
	}
    RTC.OFF();
	
	// switch off main power supply when needed:
	// -> ACC interruption is disabled
	// -> Sensor interruption is disabled
	// -> XBee interruption is disabled
	if ((ACC.accInt == NO_INT) && (option == ALL_OFF))
	{
		digitalWrite(POWER_3V3, LOW);
	}
    
	// *** set sleep mode ***
	// check interruption pins and register are ok
	if (!digitalRead(MUX_RX))
	{		
		// set sleep mode
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_mode();
	}
	else
	{
		USB.ON();
		USB.println(F("[PWR] Noise in Interruption line"));
	}
	// wake up here
	sleep_disable();
	
	// switch on main power supply
	digitalWrite(POWER_3V3,HIGH);
	
	// Switch on the RTC and clear the alarm signals	
	// Disable RTC interruption after waking up 
	RTC.ON();
	RTC.disableAlarm1();
	RTC.clearAlarmFlag();
	
	// re-activate what is needed
	switchesON(option);
	
	//SPI.setSPISlave(ALL_DESELECTED);
}



/*
 * hibernate(time2wake, offset, mode) - enter a hibernate state
 * 
 * Waspmote enters hibernate. The device is off and no variable will be stored
 * in RAM memory
 * 
 */
void WaspPWR::hibernate(const char* time2wake, uint8_t offset, uint8_t mode)
{
	int retries = 3;
	
	// set EEPROM Hibernate flag
	eeprom_write_byte((unsigned char *) HIB_ADDR, HIB_VALUE);
   
	// switch off socket power
	PWR.powerSocket(SOCKET0, LOW);
	
	//~ closeSerial(0);
	//~ while(digitalRead(GPS_PW))
	//~ {              
		//~ digitalWrite(GPS_PW,LOW);
	//~ }
   
	// switch multiplexers power supply 
	Utils.muxOFF();
      
	RTC.ON();
	// Set RTC alarme to wake up from Sleep Power Down Mode
	RTC.setAlarm1(time2wake,offset,mode);
	// get backup of selected Alarm	
	uint8_t day_aux = RTC.day_alarm1; 
	uint8_t hour_aux = RTC.hour_alarm1; 
	uint8_t minute_aux = RTC.minute_alarm1; 
	uint8_t second_aux = RTC.second_alarm1; 
	// get Alarm
	RTC.getAlarm1();
	// check Alarm was correctly set	
	if(	( day_aux != RTC.day_alarm1 ) 
	||	( hour_aux != RTC.hour_alarm1 )
	||	( minute_aux != RTC.minute_alarm1 )
	||	( second_aux != RTC.second_alarm1 ) )
	{
		return (void)0;
	}
	RTC.OFF();
   
	pinMode(RTC_SLEEP,OUTPUT);
	digitalWrite(RTC_SLEEP,HIGH);
	delay(50);
	digitalWrite(RTC_SLEEP,LOW);
   
	// To avoid executing any other function after calling hibernate
	while( retries > 0 ) 
	{
	   retries--;
       pinMode(RTC_SLEEP,OUTPUT);
       digitalWrite(RTC_SLEEP,HIGH);
       delay(50);
       digitalWrite(RTC_SLEEP,LOW);
       delay(50);
	}
}



/* getBatteryLevel() - gets % of remaining battery
 *
 * It gets the % of remaining battery.
 *
 * It gives a value of 1024 for +3V3
 * A resistor bridge is put to down max +4V2 battery level around +2V07 on 100% battery charge
 * Minimum value for good battery is +1V5, so with resistor bridge is set to +0V75
 * Values (in this case) are from 204 to 567
 */
uint8_t WaspPWR::getBatteryLevel()
{
	float volts = 0;
	int bits;
	float aux;
	uint8_t percentage = 0;

	// read battery volts
	volts = getBatteryVolts();
		
	// convert from volts to bits
	bits = volts*1023/3.3;
	aux = (float)bits/2.0; // voltage divider	
	
	// make conversion from bits to '%' units
	if (aux < 512)
	{
		percentage = 0;
	}
	else if (aux > 651)
	{
		percentage = 100;
	}
	else if (aux > 543)
	{
		aux = (aux * (90.0/108.0)) - 442.0;
		percentage = (uint8_t) aux;
	}
	else
	{
		aux = ((10.0/(543.0-511.0)) * aux) - 160.0;
		percentage = (uint8_t) aux;
	}
	
	return percentage;	
} 





/* getBatteryVolts() - gets Volts of remaining battery
 *
 * This function gets the Volts of remaining battery.
 *
 * Returns the voltage of battery. 
 */
float WaspPWR::getBatteryVolts()
{
	if (_boot_version < 'G')
	{		
		float aux_volts=0;	 
		pinMode(BAT_MONITOR, INPUT);
		pinMode(BAT_MONITOR_PW, OUTPUT);
		digitalWrite(BAT_MONITOR_PW, HIGH);
		aux_volts = analogRead(0);
		aux_volts = analogRead(0);
		digitalWrite(BAT_MONITOR_PW, LOW);
		return aux_volts*3.3*2.0/1023.0;
	}
	else
	{
		float result = 0;
		int nSamples = 10;
		int values[nSamples];		
		
		// change to REF 2.56V
		analogReference(INTERNAL2V56);
		
		// enables the ADC
		sbi(ADCSRA, ADEN);	

		// check if it is necessary to turn on the 5v power supply
		bool flag = WaspRegister & REG_5V;
  
		if (!flag)
		{
			PWR.setSensorPower(SENS_5V, SENS_ON);
		}

		// power on the components
		pinMode(BAT_MONITOR, INPUT);
		pinMode(BAT_MONITOR_PW, OUTPUT);
		digitalWrite(BAT_MONITOR_PW, HIGH);
		delay(1);		
		
		// dummy readings
		for(int i = 0; i<nSamples; i++)
		{
			analogRead(0);
		}
		
		// get several readings and get the max repeated element in readings
		uint8_t count = 0;
		int	m;
		for(int i = 0; i<nSamples; i++)
		{
			values[i] = analogRead(0);		

			if (count == 0)
			{
				m = values[i];
			}
			if (i == 0)
			{
				m = values[0];
			}
			if (values[i] == m)
			{
				count++;
			}
			else
			{
				count--;
			}
		}		
		//get result
		result = m;
		
		// check if it is necessary to turn off the 5v power supply
		if (!flag)
		{
			PWR.setSensorPower(SENS_5V, SENS_OFF);
		}
		
		//turn off
		digitalWrite(BAT_MONITOR_PW, LOW);
		
		// change to DEFAULT
		analogReference(DEFAULT);
		
		// convert to volts
		//~ result *= 3.3;
		result *= 2.56;
		result *= 2.0;
		result /= 1023.0;
		
		// trunc to three decimals
		result *= 1000;
		result = round(result);
		result /= 1000;
		
		return result;
	}
}

/* getBatteryCurrent() - gets current charging the battery from solar pannel
 *
 * This function gets the current charging the battery from solar pannel
 *
 * Returns the current charging the battery by solar pannel. 
 */
uint16_t WaspPWR::getBatteryCurrent()
{		
	if (_boot_version < 'H')
	{
		USB.println(F("\n***************  WARNING *******************"));
		USB.println(F("This example is valid only for Waspmote v15."));
		USB.println(F("Your Waspmote version is v12."));
		USB.println(F("*******************************************"));
		return 0;
	}
	
	float current = 0;
	pinMode(BAT_MONITOR, INPUT);
	pinMode(BAT_MONITOR_PW, OUTPUT);
	digitalWrite(BAT_MONITOR_PW, LOW);
	current = analogRead(0);
	current = analogRead(0);
	digitalWrite(BAT_MONITOR_PW, HIGH);
	return (uint16_t)(current*(3.3/1023.0)*1000/3.3);
} 

/* getChargingState() - gets the state of the battery charger
 *
 * This function gets the state of the battery charger
 *
 * Returns the he state of the battery charger
 * (1 Battery is being charged, 0 battery is not being charged)
 */
bool WaspPWR::getChargingState()
{
	uint8_t state = 0;
	
	if (_boot_version < 'H')
	{
		USB.println(F("\n***************  WARNING *******************"));
		USB.println(F("This example is valid only for Waspmote v15."));
		USB.println(F("Your Waspmote version is v12."));
		USB.println(F("*******************************************"));
		return 0;
	}	
	
	// mandatory delay to avoid USB print interferences in reading process
	delay(100);
	
	// get reading from digital pin
	pinMode(CHG_IND, INPUT);
	state = digitalRead(CHG_IND);
	
	return state;
} 

/* closeI2C() - closes I2C, setting SDA and SCL to '0'
 *
 * This function closes I2C, setting SDA and SCL to '0'
 *
 * Returns nothing
 */
void	WaspPWR::closeI2C()
{
	pinMode(I2C_SDA,OUTPUT);
	pinMode(I2C_SCL,OUTPUT);
	//digitalWrite(I2C_SDA,LOW);
	//digitalWrite(I2C_SCL,LOW);
	I2C.close();
}



/*
 * ifHibernate - Check if Hibernate has generated the reset
 * 
 * This function checks if Waspmote has been reset from an hibernate mode by 
 * reading the RTC interrupt pin and reading the EEPROM's hibernate flag
 * In the case it does not come from hibernate, this function prepares 
 * 
 */
void WaspPWR::ifHibernate()
{
	// declare counter
	uint8_t counter=0;
	
	// set EEPROM Hibernate flag to 0
	eeprom_write_byte((unsigned char *) HIB_ADDR, 0);
	
	RTC.ON();
	RTC.OFF();
	if (!(intFlag & HIB_INT))
	{
		// Force a high pulse in digital switch control 
		// in order to set up Waspmote for hibernating
		pinMode(RST_RTC, OUTPUT);
		digitalWrite(RST_RTC, LOW);
		delay(10);
		digitalWrite(RST_RTC, HIGH);
			
		// check the hibernate switch has been set correctly. If not, then 
		// insert a new pulse so as to establish the correct level in the pin
		// (must be '1')
		while (digitalRead(HIB_PIN) == 0)
		{
			// Force a high pulse in digital switch control 	
			digitalWrite(RST_RTC, LOW);
			delay(10);
			digitalWrite(RST_RTC, HIGH);
					
			// increment counter
			counter++;
			if (counter >= 3)
			{
				break;
			}
		}

		// switch on the red led
		// the Hibernate switch MUST be turned off before the red led lights off
		Utils.setLED(LED0,LED_ON);
		delay(3000);
		Utils.setLED(LED0,LED_OFF);
		
		// blink the green to indicate "the program is running ok"
		Utils.setLED(LED1,LED_ON);
		delay(500);
		Utils.setLED(LED1,LED_OFF);
	}	
	
	// make sure both digital pins are off depending on the boot version
	if (Utils.getBootVersion() < 'E')
	{	
		if (digitalRead(RTC_SLEEP) || digitalRead(RST_RTC))
		{
			digitalWrite(RTC_SLEEP,LOW);
			digitalWrite(RST_RTC, LOW);
		}
	}
	else
	{
		digitalWrite(RST_RTC, LOW);		
	}
}


// reboots waspmote
void    WaspPWR::reboot()
{
	if( Utils.getBootVersion() < 'C')
	{	
		__asm__("jmp 0x1E000");
	}
	else
	{
		// enable watchdog to reset MCU
		wdt_enable(WDTO_15MS);   
		for(;;)
		{}
	}
}


// clear all kind of Interruption signal in Waspmote
void WaspPWR::clearInterruptionPin()
{
	// check if there is a non-captured interruption and clear it 
	if (!intFlag && digitalRead(MUX_RX)) 
	{	
		// unset XBee interruption line
		pinMode(XBEE_MON,OUTPUT);
		digitalWrite(XBEE_MON,LOW);
		
		// RTC module
		if( digitalRead(RTC_INT_PIN_MON) )
		{
			// clear RTC interrupt
			RTC.ON();
			RTC.clearAlarmFlag();
		}
		
		// check ACC interruption
		if( digitalRead(ACC_INT_PIN_MON)==HIGH )
		{
			// clear ACC interrupt
			ACC.ON();
			
			switch(ACC.accInt)
			{
				case FF_INT:	ACC.setFF();				
								break;	
											
				case IWU_INT:	ACC.setIWU();				
								break;	
											
				case _6DMOV_INT:ACC.set6DMovement();				
								break;
					
				case _6DPOS_INT:ACC.set6DPosition();				
								break;	
															
				case NO_INT:	break;
				
				default: 		// do nothing
								break;				
			}										
		}
		
		// set the interruption line down
		pinMode(MUX_RX, INPUT);
		digitalWrite(MUX_RX, LOW);
	}
}



/* printIntFlag() - print 'intFlag' global variable
 *
 */
void WaspPWR::printIntFlag()
{
	USB.println(F(" __________________________________________________________"));
	USB.println(F("|        |      |     |     |     |      |     |     |     |"));
	USB.println(F("| PIR_3G |  --  | RAD | HIB | PLV | SENS | WTD | RTC | ACC |"));
	USB.println(F("|________|______|_____|_____|_____|______|_____|_____|_____|"));
	USB.print(F("     "));
	USB.print(bool(intFlag & PIR_3G_INT));
	USB.print(F("       "));
	USB.print(bool(intFlag & XBEE_INT));
	USB.print(F("     "));
	USB.print(bool(intFlag & RAD_INT));
	USB.print(F("     "));
	USB.print(bool(intFlag & HIB_INT));
	USB.print(F("     "));
	USB.print(bool(intFlag & PLV_INT));
	USB.print(F("     "));
	USB.print(bool(intFlag & SENS_INT));
	USB.print(F("      "));
	USB.print(bool(intFlag & WTD_INT));
	USB.print(F("     "));
	USB.print(bool(intFlag & RTC_INT));
	USB.print(F("     "));
	USB.print(bool(intFlag & ACC_INT));
	USB.println();
	USB.println();
}




/* 
 * powerSocket() - powers on/off the socket selected as input
 */
void WaspPWR::powerSocket(uint8_t socket, uint8_t state)
{
	switch (socket)
	{
		case SOCKET0:
			pinMode(SOCKET0_PW, OUTPUT);
			digitalWrite(SOCKET0_PW, state);
			break;
			
		case SOCKET1:
			pinMode(DIGITAL6, OUTPUT);
			digitalWrite(DIGITAL6, state);	
			break;
			
		default:
			break;
	}
}




/*
 * 
 * 
 */
void WaspPWR::checkPeripherals()
{
	uint8_t answer;
	
	// define object for UART0
	WaspUART uart0 = WaspUART();
	
	// init object in SOCKET0
	uart0.setUART(SOCKET0);
	
    // select multiplexer
    Utils.setMuxSocket0();
    
    // begin serial communication
    uart0.beginUART();
    
    // power on the socket
    PWR.powerSocket(SOCKET0, HIGH);
    delay(500);    
    serialFlush(SOCKET0);
	
    // check for XBees in SOCKET0
	uint8_t cmd_xbee[] = {0x7E, 0x00 , 0x04 , 0x08 , 0x01 , 0x56 , 0x52 , 0x4E};
	
	// send command & receive answer
	uart0.sendCommand(cmd_xbee, sizeof(cmd_xbee));
	uart0.readBuffer(100);
	
	// check response: 7E00078801565200xxxx??
	if (uart0._length > 0)
	{
		if ((uart0._buffer[0] == 0x7E)
		&&	(uart0._buffer[1] == 0x00)
		&&	(uart0._buffer[3] == 0x88)
		&&	(uart0._buffer[4] == 0x01)
		&&	(uart0._buffer[5] == 0x56)
		&&	(uart0._buffer[6] == 0x52)
		&&	(uart0._buffer[7] == 0x00))
		{			
			/*
			USB.print(F("XBee module in SOCKET0. Firmware: "));
			USB.printHex(uart0._buffer[8]);
			USB.printHex(uart0._buffer[9]);
			USB.println();
			*/
			
			// mark corresponding flag in WaspRegister
			WaspRegister |= REG_XBEE_SOCKET0;
		}		
	}
	
}


// Private Methods /////////////////////////////////////////////////////////////

// Preinstantiate Objects //////////////////////////////////////////////////////

WaspPWR PWR = WaspPWR();
