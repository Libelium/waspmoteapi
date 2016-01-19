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
 *  Version:		1.14
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
	
	switch( type )
	{
		case SENS_3V3: 	
						if( mode == SENS_ON ) 
						{
							digitalWrite(SENS_PW_3V3,HIGH);
							WaspRegister |= REG_3V3;
						}
						else if( mode == SENS_OFF ) 
						{
							digitalWrite(SENS_PW_3V3,LOW);
							WaspRegister &= ~REG_3V3;
							
						}						
						break;
						
		case SENS_5V:	
						if( mode == SENS_ON ) 
						{
							digitalWrite(SENS_PW_5V,HIGH);
							WaspRegister |= REG_5V;
						}
						else if( mode == SENS_OFF ) 
						{
							digitalWrite(SENS_PW_5V,LOW);
							WaspRegister &= ~REG_5V;
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
	// set this pin LOW to decrease consumption
	// if hibernate is not used
	pinMode(RTC_SLEEP, OUTPUT);
	digitalWrite(RTC_SLEEP, LOW);
		
	// unset I2C bus        
    pinMode(I2C_SDA,OUTPUT);
	digitalWrite(I2C_SDA,LOW);
	pinMode(I2C_SCL,OUTPUT);
	digitalWrite(I2C_SCL,LOW);   
	
	// switch Analog to Digital Converter OFF
	cbi(ADCSRA,ADEN);		
	
	//pinMode(SERID_PW,OUTPUT);
	//digitalWrite(SERID_PW,LOW);
	
	// Disable MEM_PW and SS_PIN not to waste 
	// battery from SD when Waspmote is asleep
  	pinMode(SD_SS, OUTPUT);
	digitalWrite(SD_SS, LOW);	
	pinMode(MEM_PW,OUTPUT);
	digitalWrite(MEM_PW,LOW);
	
	// Set down SOCKET0 SPI SS pin
	pinMode(SOCKET0_SS,OUTPUT);
	digitalWrite(SOCKET0_SS,LOW);
	
	if( option & SENS_OFF )
	{	
		// switch OFF sensor boards
		PWR.setSensorPower(SENS_3V3, SENS_OFF);
		PWR.setSensorPower(SENS_5V, SENS_OFF);
		Wire.isBoard = false;
	}
	
	// close UART0
	closeSerial(SOCKET0);
	
	if( option & SOCKET0_OFF )
	{	
		// set SOCKET0 power supply off
		pinMode(XBEE_PW,OUTPUT);
		digitalWrite(XBEE_PW,LOW);
		
		// update Waspmote Register
		WaspRegister &= ~(REG_SOCKET0);
	}
	
	// close UART1
	closeSerial(SOCKET1);	
	
	// set Expansion board power supply off	unless a 
	// Smart Cities board remains powered on 
	if( ( option & SENS_OFF ) 
		&&  !(WaspRegister & REG_CITIES_V14) 
		&&  !(WaspRegister & REG_CITIES_V15)  )
	{
		pinMode(DIGITAL6, OUTPUT);
		digitalWrite(DIGITAL6, LOW);
	}
	
	// switch off the RTC power supply
	RTC.close();
	pinMode(RTC_PW,OUTPUT);
	digitalWrite(RTC_PW,LOW);
	closeI2C();	
	
	// switch off the battery monitor power supply
	pinMode(BAT_MONITOR_PW,OUTPUT);
	digitalWrite(BAT_MONITOR_PW,LOW);
	
	// check if a Smart Metering board has been switched and proceed to disable 
	// the digital pins so as not to waste energy
	if( WaspRegister & REG_METERING )
	{
		setSensorPower(SENS_3V3,SENS_ON);
		pinMode(DIGITAL3, OUTPUT);
		pinMode(DIGITAL4, OUTPUT);
		digitalWrite(DIGITAL3, HIGH);
		digitalWrite(DIGITAL4, HIGH);
	}
	
	// check if a Gases Sensor Board is used. In this case, switch off the 
	// digital pins so as not to waste energy
	if( WaspRegister & REG_GASES )
	{
		digitalWrite(DIGITAL4,LOW);
	}
	
	// check if an Agriculture Sensor Board is used. In this case, 
	// switch off the digital pins so as not to waste energy
	if( WaspRegister & REG_AGRICULTURE )
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
}


/* switchesON() - switches on all Waspmote switches
 *
 * It switches on all Waspmote switches
 */
void	WaspPWR::switchesON(uint8_t option)
{
	// switch Analog to Digital Converter ON
	sbi(ADCSRA,ADEN);        		
	
	if( option & SENS_OFF )
	{
		pinMode(SENS_PW_3V3,OUTPUT);
		digitalWrite(SENS_PW_3V3,HIGH);	
		pinMode(SENS_PW_5V,OUTPUT);
		digitalWrite(SENS_PW_5V,HIGH);
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
	uint8_t retries=0;
	
	// Switch off both multiplexers in UART_0 and UART_1
	Utils.muxOFF();
	
	// set the XBee monitorization pin to zero
	pinMode(XBEE_MON,OUTPUT);
	digitalWrite(XBEE_MON,LOW);
    
    // switch on and off the RTC so as to unset RTC interruption signal
	RTC.ON();
    RTC.OFF();
    
    // switches off depending on the option selected
	switchesOFF(option);
	
	// mandatory delay to wait for MUX_RX stabilization 
	// after switching off the sensor boards 
	delay(100);	
	
	// make sure interruption pin is LOW before entering a low power state
	// if not the interruption will never come
	while(digitalRead(MUX_RX)==HIGH)
	{
		// clear all detected interruption signals
		delay(1);
		PWR.clearInterruptionPin();
		retries++;
		if(retries>10)
		{
			return (void)0;
		}
	}
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_mode();
	sleep_disable();
	
	if( intFlag & RTC_INT )
	{
		RTC.ON();
		RTC.clearAlarmFlag();
		RTC.OFF();
	}
	
	//~ switchesON(option);
}


/* sleep(timer) - sets the microcontroller to the lowest consumption sleep mode
 *
 * It sets the microcontroller to the lowest consumption sleep mode. It enables watchdog interruption to be able to
 * wake up the microcontroller after 'timer' time.
 *
 * 'timer' --> it specifies the time before the watchdog activates the interruption. Possible values are:
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
	uint8_t retries=0;
		
	// Switch off both multiplexers in UART_0 and UART_1
	Utils.muxOFF();
	
	// set the XBee monitorization pin to zero
	pinMode(XBEE_MON,OUTPUT);
	digitalWrite(XBEE_MON,LOW);
	
    // switch on and off the RTC so as to unset RTC interruption signal
	RTC.ON();
    RTC.OFF(); 
     
	// switches off depending on the option selected       
	switchesOFF(option);
	
	// mandatory delay to wait for MUX_RX stabilization 
	// after switching off the sensor boards 
	delay(100);	
	
	// make sure interruption pin is LOW before entering a low power state
	// if not the interruption will never come
	while(digitalRead(MUX_RX)==HIGH)
	{
		// clear all detected interruption signals
		delay(1);
		PWR.clearInterruptionPin();
		retries++;
		if(retries>10)
		{
			return (void)0;
		}
	}
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	
	// set watchdog timer to cause interruption for selected time
	setWatchdog(WTD_ON,timer);
	sleep_mode();
	sleep_disable();
		
	if( intFlag & RTC_INT )
	{
		RTC.ON();
		RTC.clearAlarmFlag();
		RTC.OFF();
	}
	//~ switchesON(option);
	
}


/* deepSleep(time2wake, offset, mode) - sets the microcontroller to the lowest consumption sleep mode
 *
 * It sets the microcontroller to the lowest consumption sleep mode. It enables RTC interruption to be able to
 * wake up the microcontroller when the RTC alarm is launched.
 *
 * 'time2wake' --> it specifies the time at which the RTC alarm will activate. It must follow the next format:
 *	"DD:HH:MM:SS"
 * 'offset' --> it specifies if 'time2wake' is added to the actual time or if this time is set as the alarm
 * 'mode' --> it specifies the mode for RTC alarm
 *
 * It uses Alarm1 on the RTC due to this Alarm has more precision than Alarm2
 * 
 * It switches off all the switches on the Waspmote board.
 *
 * It returns nothing.
 */
void WaspPWR::deepSleep(	const char* time2wake, 
							uint8_t offset, 
							uint8_t mode, 
							uint8_t option	)
{	
	uint8_t retries=0;
	
	// Switch off both multiplexers in UART_0 and UART_1
	Utils.muxOFF();
	
	// set the XBee monitorization pin to zero
	pinMode(XBEE_MON,OUTPUT);
	digitalWrite(XBEE_MON,LOW);
	
	// switches off depending on the option selected  
	switchesOFF(option);
	
	// mandatory delay to wait for MUX_RX stabilization 
	// after switching off the sensor boards 
	delay(100);	
	
	// make sure interruption pin is LOW before entering a low power state
	// if not the interruption will never come
	while(digitalRead(MUX_RX)==HIGH)
	{	
		// clear all detected interruption signals
		delay(1);
		PWR.clearInterruptionPin();
		retries++;
		if(retries>10)
		{
			return (void)0;
		}
	}
	
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
		RTC.OFF();
		return (void)0;
	}
    RTC.OFF();	
	
	// set sleep mode
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_mode();
	sleep_disable();
		
	// in the case SENS_OFF was an option is mandatory to turn on the
	// sensor boards before setting up the I2C bus
	switchesON(option);
	
	// Switch on the RTC and clear the alarm signals	
	// Disable RTC interruption after waking up 
	RTC.ON();
	RTC.disableAlarm1();
	RTC.clearAlarmFlag();
	RTC.OFF();
	
	// Keep sensor supply powered down if selected
	if( option & SENS_OFF )
	{
		pinMode(SENS_PW_3V3,OUTPUT);
		digitalWrite(SENS_PW_3V3,LOW);	
		pinMode(SENS_PW_5V,OUTPUT);
		digitalWrite(SENS_PW_5V,LOW);
	}
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
   
	pinMode(XBEE_PW,OUTPUT);
	digitalWrite(XBEE_PW, LOW);
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
   float aux=0;
   uint8_t resul=0;
   pinMode(BAT_MONITOR_PW,OUTPUT);
   digitalWrite(BAT_MONITOR_PW,HIGH);
   
   // delay in order to stabilize the measurement
   delay(1);
   
   // read value      
   aux=analogRead(0);
   
	if (aux < 512)
	{
		aux = 0;
		resul=(uint8_t) aux;
		digitalWrite(BAT_MONITOR_PW,LOW);
		return resul;
	}
	if (aux > 651)
	{
		aux = 100;
		resul=(uint8_t) aux;
		digitalWrite(BAT_MONITOR_PW,LOW);
		return resul;
	}
	if ((aux <= 651)&&(aux > 543))
	{
		aux = (aux * (90.0/108.0)) - 442.0;
		resul=(uint8_t) aux;
		digitalWrite(BAT_MONITOR_PW,LOW);
		return resul;
	}
	else
	{
		aux = ((10.0/(543.0-511.0)) * aux) - 160.0;
		resul=(uint8_t) aux;
		digitalWrite(BAT_MONITOR_PW,LOW);
		return resul;
	}   
} 





/* getBatteryVolts() - gets Volts of remaining battery
 *
 * This function gets the Volts of remaining battery.
 *
 * Returns the voltage of battery. 
 */
float WaspPWR::getBatteryVolts()
{
   float aux_volts=0;
   pinMode(BAT_MONITOR_PW,OUTPUT);
   digitalWrite(BAT_MONITOR_PW,HIGH);
   aux_volts=analogRead(0);
   aux_volts=analogRead(0);
   digitalWrite(BAT_MONITOR_PW,LOW);
   return aux_volts*3.3*2.0/1023.0;
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
	Wire.close();
}



/*
 * ifHibernate - Check if Hibernate has generated the reset
 * 
 * This function checks if Waspmote has been reset from an hibernate mode by 
 * reading the RTC interrupt pin and reading the EEPROM's hibernate flag
 * In the case it does not come from hibernate, this function prepares 
 * 
 */
void	WaspPWR::ifHibernate()
{
	// declare counter
	uint8_t counter=0;
	
	// set EEPROM Hibernate flag to 0
	eeprom_write_byte((unsigned char *) HIB_ADDR, 0);
	
	RTC.ON();
	RTC.OFF();
	if( !(intFlag & HIB_INT) )
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
		while( digitalRead(HIB_PIN) == 0 )
		{
			// Force a high pulse in digital switch control 	
			digitalWrite(RST_RTC, LOW);
			delay(10);
			digitalWrite(RST_RTC, HIGH);
					
			// increment counter
			counter++;
			if( counter >= 3)
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
	if( Utils.getBootVersion() < 'E')
	{	
		if(digitalRead(RTC_SLEEP)||digitalRead(RST_RTC))
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



/* printIntFlag() - print 'intFlag' global variable
 *
 */
void WaspPWR::printIntFlag()
{
	USB.println(F(" __________________________________________________________"));
	USB.println(F("|        |      |     |     |     |      |     |     |     |"));
	USB.println(F("| PIR_3G | XBEE | RAD | HIB | PLV | SENS | WTD | RTC | ACC |"));
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



// Private Methods /////////////////////////////////////////////////////////////

// Preinstantiate Objects //////////////////////////////////////////////////////

WaspPWR PWR = WaspPWR();
