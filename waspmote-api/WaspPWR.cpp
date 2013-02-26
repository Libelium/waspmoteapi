/*
 *  Copyright (C) 2009 Libelium Comunicaciones Distribuidas S.L.
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
 */
void WaspPWR::setSensorPower(uint8_t type, uint8_t mode)
{
	pinMode(SENS_PW_3V3,OUTPUT);
	pinMode(SENS_PW_5V,OUTPUT);
	
	switch( type )
	{
		case SENS_3V3: 	if(mode==SENS_ON) digitalWrite(SENS_PW_3V3,HIGH);
		else if(mode==SENS_OFF) digitalWrite(SENS_PW_3V3,LOW);
		break;
		case SENS_5V:	if(mode==SENS_ON) digitalWrite(SENS_PW_5V,HIGH);
		else if(mode==SENS_OFF) digitalWrite(SENS_PW_5V,LOW);
		break;
	}
}


/* setWatchdog( mode, timer) - enables or disables watchdog interruption
 *
 * It enables or disables watchdog interruption.
 *
 * 'mode' --> if mode=WTD_ON, it enables watchdog interruption. If mode=WTD_OFF, it disables watchdog interruption.
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
	cbi(ADCSRA,ADEN);		// switch Analog to Digital Converter OFF
	//pinMode(SERID_PW,OUTPUT);
	//digitalWrite(SERID_PW,LOW);
	pinMode(MEM_PW,OUTPUT);
	digitalWrite(MEM_PW,LOW);
		
	if( option & SENS_OFF )
	{
		pinMode(SENS_PW_3V3,OUTPUT);
		digitalWrite(SENS_PW_3V3,LOW);	
		pinMode(SENS_PW_5V,OUTPUT);
		digitalWrite(SENS_PW_5V,LOW);
	}
	
	if( option & UART0_OFF )
	{
		// close UART0
		closeSerial(SOCKET0);
		// set XBee module off
		pinMode(XBEE_PW,OUTPUT);
		digitalWrite(XBEE_PW,LOW);		
	}
	
	if( option & UART1_OFF )
	{
		// close UART1
		closeSerial(SOCKET1);
		
		pinMode(MUX_PW, OUTPUT);
		digitalWrite(MUX_PW, LOW);
		pinMode(GPS_PW, OUTPUT);
		digitalWrite(GPS_PW, LOW);
	}
	
	if( option & RTC_OFF )
	{
		RTC.close();
		pinMode(RTC_PW,OUTPUT);
		digitalWrite(RTC_PW,LOW);
		closeI2C();	
	}
	
	if( option & BAT_OFF )
	{
		pinMode(BAT_MONITOR_PW,OUTPUT);
		digitalWrite(BAT_MONITOR_PW,LOW);
	}	
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
	// Switch off both multiplexers in UART_0 and UART_1 when 
	// no interruption is expected through the UART1
   	if( !(option & UART1_OFF) )
	{	
		// keep multiplexer on
	}
	else
	{
		Utils.muxOFF();
	}
    
	RTC.ON();
	RTC.close();
    RTC.OFF();
        
    pinMode(I2C_SDA,OUTPUT);
	digitalWrite(I2C_SDA,LOW);
	pinMode(I2C_SCL,OUTPUT);
	digitalWrite(I2C_SCL,LOW);    
	
	pinMode(XBEE_MON,INPUT);
	digitalWrite(XBEE_MON,LOW);
    
	switchesOFF(option);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_mode();
	sleep_disable();
	switchesON(option);
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
	// Switch off both multiplexers in UART_0 and UART_1 when 
	// no interruption is expected through the UART1
   	if( !(option & UART1_OFF) )
	{	
		// keep multiplexer on
	}
	else
	{
		Utils.muxOFF();
	}
	
	RTC.ON();
   
    pinMode(XBEE_MON,INPUT);
	digitalWrite(XBEE_MON,LOW);
           
	switchesOFF(option);
	pinMode(I2C_SDA,OUTPUT);
	digitalWrite(I2C_SDA,LOW);
	pinMode(I2C_SCL,OUTPUT);
	digitalWrite(I2C_SCL,LOW); 
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	
	setWatchdog(WTD_ON,timer);
	sleep_mode();
	sleep_disable();
	switchesON(option);
	
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
	// set the monitorization pin to zero
	pinMode(XBEE_MON,INPUT);
	digitalWrite(XBEE_MON,LOW);
	
	// Switch off both multiplexers in UART_0 and UART_1 when 
	// no interruption is expected through the UART1
   	if( !(option & UART1_OFF) )
	{	
		// keep multiplexer on
	}
	else
	{
		Utils.muxOFF();
	}
	delay(100);
	
	// Set RTC alarm to wake up from Sleep Power Down Mode
	RTC.ON();
	RTC.setAlarm1(time2wake,offset,mode);
	RTC.close();  
    RTC.OFF();

    pinMode(I2C_SDA,OUTPUT);
	digitalWrite(I2C_SDA,LOW);
	pinMode(I2C_SCL,OUTPUT);
	digitalWrite(I2C_SCL,LOW);    
	
    pinMode(SD_SS,OUTPUT);
    digitalWrite(SD_SS,HIGH);    
 
	switchesOFF(option);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_mode();
	sleep_disable();
	delay(500);
	switchesON(option);
	RTC.ON();
	RTC.clearAlarmFlag();
	if( option & RTC_OFF ) RTC.OFF();
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
   //RTC.close();
   RTC.setMode(RTC_OFF, RTC_NORMAL_MODE);
   
   pinMode(RTC_SLEEP,OUTPUT);
   digitalWrite(RTC_SLEEP,HIGH);
   delay(50);
   digitalWrite(RTC_SLEEP,LOW);
   // To avoid executing any other function after calling hibernate
   while(1);
   {
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
uint8_t    WaspPWR::getBatteryLevel()
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

// inits the value of the digipot used in the battery detector
void    WaspPWR::setLowBatteryThreshold(float threshold)
{
	if ( threshold > 3.4 )
	{
		threshold = 3.4;
	}
	if ( threshold < 3.1 )
	{
		threshold = 3.1;
	}
	uint8_t dig=0;
	uint8_t rpot=200;
	dig = uint8_t (rpot-(((threshold-1.15)*470/1.15)-806))*255/rpot;
	if( !Wire.I2C_ON ) Wire.begin();
	delay(200);
	Wire.beginTransmission(0x56);    // Address
	Wire.send(0x11);                 // Write command
	Wire.send(dig);                  // Data
	Wire.endTransmission();
	if( Wire.I2C_ON ) closeI2C();
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
	
	// validate Hibernate interruption when both RTC interruption 
	// signal and hibernate EEPROM flag are active
	if( digitalRead(RTC_INT_PIN_MON) && (Utils.readEEPROM(HIB_ADDR)==HIB_VALUE) )
	{
		// get RTC time and last almarm setting
		RTC.ON();
		RTC.getAlarm1();
		RTC.getTime();	
		
		// when the interruption and startup has been produced within 3 seconds
		// then we validate the Hibernate interruption. If not, maybe the 
		// Waspmote startup conditions may show the hibernate startup conditions 
		// when it is not true	
		int total_diff = RTC.second - RTC.second_alarm1;	
				
		// check seconds zero crossing
		if( RTC.minute - RTC.minute_alarm1 > 0 )
		{
			total_diff = total_diff + (RTC.minute - RTC.minute_alarm1)*60;
		}
		
		// check minute zero crossing
		if( RTC.minute - RTC.minute_alarm1 < 0 )	
		{
			total_diff = total_diff + (RTC.minute-RTC.minute_alarm1+60)*60;
		}	
		
		if( (total_diff < 3) && (total_diff >= 0) )	
		{
			intFlag |= HIB_INT;
		}
	}	
	
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
	
	// make sure both digital pins are off
	while(digitalRead(RTC_SLEEP)||digitalRead(RST_RTC))
	{
		digitalWrite(RTC_SLEEP,LOW);
		digitalWrite(RST_RTC, LOW);
	}
}


// reboots waspmote
void    WaspPWR::reboot()
{
    __asm__("jmp 0x1E000");
}

// Private Methods /////////////////////////////////////////////////////////////

// Preinstantiate Objects //////////////////////////////////////////////////////

WaspPWR PWR = WaspPWR();
