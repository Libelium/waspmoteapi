/*
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
 *  Version:		3.3
 *  Design:			David Gascon
 *  Implementation:	Yuri Carmona
 */
  

#include <Waspmote.h>

//define global variable for Waspmote serial id
volatile uint8_t _serial_id[8];

//define global variable for Waspmote bootloader version
volatile uint8_t _boot_version;

int main(void)
{
	init();

	// switch on main power supply
	pinMode(POWER_3V3, OUTPUT);
	digitalWrite(POWER_3V3,HIGH);	

	//Disable Mux in Xtreme boards
	if (WaspRegisterSensor & REG_XTR)
	{
		//20 is MUX_EN in Xtreme board, HIGH for disabling
		pinMode(20, OUTPUT);
		digitalWrite(20, HIGH);
	}
	
	// get bootloader version
	_boot_version = Utils.getBootVersion();
	
	// proceed depending on the bootloader version
	if (_boot_version >= 'E')
	{
		pinMode(RTC_SLEEP, OUTPUT);
		digitalWrite(RTC_SLEEP, HIGH);
	}
	
	// power on the 3V3 to search BME devices directly connected to SDA and SCL
	PWR.setSensorPower(SENS_3V3, SENS_ON);
	delay(100);
	
	// scan for i2c sensors
	if (I2C.scanSlaves())
	{
		PWR.setSensorPower(SENS_3V3, SENS_ON);
	}
	else
	{
		PWR.setSensorPower(SENS_3V3, SENS_OFF);		
	}
	
	uint8_t rtc_hibernate_triggered = digitalRead(RTC_INT_PIN_MON);
	
	// proceed depending on the bootloader version
	if (_boot_version >= 'G')
	{
		RTC.ON();
		RTC.ON();
		RTC.disableSQW();
		RTC.OFF();
	}
	
	// Check OTA EEPROM flag and mark flag in Waspmote 
	// Control Register if corresponds to
	if (Utils.readEEPROM(0x01) == 0x01)
	{
		// set register flag
		WaspRegister |= REG_OTA;
		
		// clear eeprom flag
		eeprom_write_byte((unsigned char *) 0x01, 0x00);
	}
	
	// validate Hibernate interruption when both RTC interruption 
	// signal and hibernate EEPROM flag are active
	if (rtc_hibernate_triggered && (Utils.readEEPROM(HIB_ADDR)==HIB_VALUE))
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
		if (RTC.minute - RTC.minute_alarm1 > 0)
		{
			total_diff = total_diff + (RTC.minute - RTC.minute_alarm1)*60;
		}
		
		// check minute zero crossing
		if (RTC.minute - RTC.minute_alarm1 < 0)
		{
			total_diff = total_diff + (RTC.minute-RTC.minute_alarm1+60)*60;
		}	
		
		if ((total_diff < 3) && (total_diff >= 0))
		{
			intFlag |= HIB_INT;
		}
	}
	
	// disable both RTC alarms
	RTC.ON();
	RTC.disableAlarm1();
	RTC.disableAlarm2();
	RTC.OFF();
	
	// Improve consumption if there is an XBee in SOCKET0 and 
	// also a SPI sensor board is connected
	pinMode(SOCKET0_SS, INPUT);
	
	delay(3);	
	if (WaspRegister & REG_SX)
	{	
		delay(3);	
		// Powering the module
		PWR.powerSocket(SOCKET0, HIGH);
		delay(3);
		//Configure the MISO, MOSI, CS, SPCR.
		SPI.begin();
		delay(3);
		//Set Most significant bit first
		SPI.setBitOrder(MSBFIRST);
		delay(3);
		//Divide the clock frequency
		SPI.setClockDivider(SPI_CLOCK_DIV2);
		delay(3);
		//Set data mode
		SPI.setDataMode(SPI_MODE0);		
		delay(3);
		//finish
		SPI.end();		
		delay(3);
		// disable all SPI slaves 
		SPI.setSPISlave(ALL_DESELECTED);	
		delay(3);
		// Powering the module
		PWR.powerSocket(SOCKET0, LOW);	
		delay(3);
	}
	delay(3);
	
	// get serial id
	Utils.readSerialID();
	
	// set random seed
	unsigned int seed = 0;
	seed += _serial_id[6] * 0x100;
	seed += _serial_id[7];
	srand(seed);
	
	// check for XBee modules in SOCKET0
	//PWR.checkPeripherals();
	
	// close UART
	closeSerial(0);
		
	// switch off mux on uart0
	if (_boot_version >= 'G')
	{		
		Utils.muxOFF0();
	}
	
	setup();
    
	for (;;) {
		loop();

	}
        
	return 0;
}
