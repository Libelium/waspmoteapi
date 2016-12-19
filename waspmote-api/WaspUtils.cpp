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
 *  Design:			David Gascon
 *  Implementation:	Alberto Bielsa, David Cuartielles, Yuri Carmona
 */
  

#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif

#include <inttypes.h>

/*
 * Constructor
 */
WaspUtils::WaspUtils (void)
{
}


/* setLED(led, state) - set the specified LED to the specified state(ON or OFF)
 *
 * It sets the specified LED to the specified state(ON or OFF)
 */
void WaspUtils::setLED(uint8_t led, uint8_t state)
{
	pinMode(led,OUTPUT);
	if(state==LED_ON)
	{
		digitalWrite(led,HIGH);
	}
	if(state==LED_OFF)
	{
		digitalWrite(led,LOW);
	}
}


/* setExternalLED(led, state) - set external LED to the specified state(ON or OFF)
 *
 * It sets external LED to the specified state(ON or OFF)
 */
void	WaspUtils::setExternalLED(uint8_t state)
{
	pinMode(LED1,OUTPUT);
	if(state==LED_ON)
	{
		digitalWrite(LED1,HIGH);
	}
	if(state==LED_OFF)
	{
		digitalWrite(LED1,LOW);
	}
}

/* getLED(led) - gets the state of the specified LED
 *
 * It gets the state of the specified LED
 */
uint8_t	WaspUtils::getLED(uint8_t led)
{
	return digitalRead(led);
}

/* getExternalLED(led) - gets the state of the specified LED
 *
 * It gets the state of external LED
 */
uint8_t	WaspUtils::getExternalLED()
{
	return digitalRead(LED1);
}


/* blinkLEDs(time) - blinks LED, with the specified time of blinking
 *
 * It bliks LED0 and LED1, with the specified time of blinking
 */
void WaspUtils::blinkLEDs(uint16_t time) 
{
	setLED(LED0,LED_ON);
	setLED(LED1,LED_ON);
	delay(time);
	setLED(LED0,LED_OFF);
	setLED(LED1,LED_OFF);  
	delay(time);
}


/* blinkRedLED(time, num) - blinks the red LED once during 200ms
 */
void WaspUtils::blinkRedLED() 
{
	blinkRedLED( 200, 1 );
}

/* blinkRedLED(time, num) - blinks the red LED once during 'time' milliseconds
 */
void WaspUtils::blinkRedLED( uint16_t time ) 
{
	blinkRedLED( time, 1 );
}

/* blinkRedLED(time, num) - blinks the red LED for 'num' times, and during 
 * 'time' milliseconds
 */
void WaspUtils::blinkRedLED( uint16_t time, uint8_t num ) 
{
	for( int i = 0; i < num ; i++ )
	{
		setLED(LED0,LED_ON);
		delay(time);
		setLED(LED0,LED_OFF);
		delay(time);	
	}
}

/* blinkGreenLED(time, num) - blinks the green LED once during 200ms
 */
void WaspUtils::blinkGreenLED() 
{
	blinkGreenLED( 200, 1 );
}

/* blinkGreenLED(time, num) - blinks the green LED once during 'time' milliseconds
 */
void WaspUtils::blinkGreenLED( uint16_t time ) 
{
	blinkGreenLED( time, 1);
}

/* blinkGreenLED(time, num) - blinks the green LED for 'num' times, and during 
 * 'time' milliseconds
 */
void WaspUtils::blinkGreenLED( uint16_t time, uint8_t num ) 
{
	for( int i = 0; i < num ; i++ )
	{
		setLED(LED1,LED_ON);
		delay(time);
		setLED(LED1,LED_OFF);
		delay(time);	
	}
}



/* externalLedBlink(time) - blinks external LED, with the specified time of blinking
 *
 * It bliks LED1, with the specified time of blinking
 */
void WaspUtils::externalLEDBlink(uint16_t time) 
{
	
	setLED(LED1,LED_ON);
	delay(time);
	
	setLED(LED1,LED_OFF);  
	delay(time);
}

/* map(x,in_min,in_max,out_min,out_max) - maps 'x' from the read range to the specified range
 *
 * It maps 'x' from the read range to the specified range
 *
 * 'in_min' and 'in_max' are the entry range read from the sensor
 * 'out_min' and 'out_max' are the desired output range
 */
long WaspUtils::map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


/* setMux( MUX_LOW, MUX_HIGH) - sets multiplexer on UART_1 to the desired combination
 *
 * It sets MUX to the desired combination.
 *
 * --------------
 * MUX1_0 = 0 & MUX1_1 = 1 ---> GPS MODULE
 * MUX1_0 = 1 & MUX1_1 = 1 ---> GPRS MODULE
 * MUX1_0 = 1 & MUX1_1 = 0 ---> AUX1 MODULE
 * MUX1_0 = 0 & MUX1_1 = 0 ---> AUX2 MODULE
 */
void WaspUtils::setMux(uint8_t MUX_LOW, uint8_t MUX_HIGH)
{
	pinMode(MUX1_PW, OUTPUT);
	pinMode(MUX1_0, OUTPUT);      
	pinMode(MUX1_1, OUTPUT);   
	digitalWrite(MUX1_PW, HIGH);   
	digitalWrite(MUX1_0, MUX_LOW);
	digitalWrite(MUX1_1, MUX_HIGH);
}


/* setMuxGPS() - sets multiplexer on UART_1 to the desired combination (0,1)
 *
 * It sets multiplexer on UART_1 to the desired combination (0,1) to enable GPS module
 *
 * --------------
 * MUX1_0 = 0 & MUX1_1 = 1 ---> GPS MODULE
 * MUX1_0 = 1 & MUX1_1 = 1 ---> GPRS MODULE
 * MUX1_0 = 1 & MUX1_1 = 0 ---> AUX1 MODULE
 * MUX1_0 = 0 & MUX1_1 = 0 ---> AUX2 MODULE
 */
void WaspUtils::setMuxGPS()
{
	pinMode(MUX1_PW, OUTPUT);
	pinMode(MUX1_0, OUTPUT);      
	pinMode(MUX1_1, OUTPUT);   
	digitalWrite(MUX1_PW, HIGH);   
	digitalWrite(MUX1_0, LOW);
	digitalWrite(MUX1_1, HIGH);
}


/* setMuxSocket1() - sets multiplexer on UART_1 to the desired combination (1,1)
 *
 * It sets multiplexer on UART_1 to the desired combination (1,1) to enable SOCKET1
 *
 * --------------
 * MUX1_0 = 0 & MUX1_1 = 1 ---> GPS MODULE
 * MUX1_0 = 1 & MUX1_1 = 1 ---> GPRS MODULE
 * MUX1_0 = 1 & MUX1_1 = 0 ---> AUX1 MODULE
 * MUX1_0 = 0 & MUX1_1 = 0 ---> AUX2 MODULE
 */
void WaspUtils::setMuxSocket1()
{
	// check RTC int pin to disable line in order to communicate
	if (digitalRead(RTC_INT_PIN_MON) == HIGH)
	{
		if (RTC.isON == 0)
		{
			RTC.ON();
			RTC.clearAlarmFlag();
			RTC.OFF();
		}
		else
		{
			RTC.clearAlarmFlag();
		}
	}
	
	// disable interruptions when using UART1
	detachInterrupt(RXD1_PIN);
	detachInterrupt(TXD1_PIN);
	
	pinMode(MUX1_PW, OUTPUT);
	pinMode(MUX1_0, OUTPUT);      
	pinMode(MUX1_1, OUTPUT);   
	digitalWrite(MUX1_PW, HIGH);   
	digitalWrite(MUX1_0, HIGH);
	digitalWrite(MUX1_1, HIGH);
}


/* setMuxAux1() - sets multiplexer on UART_1 to the desired combination (1,1)
 *
 * It sets multiplexer on UART_1 to the desired combination (1,1) to enable Aux1 module
 *
 * --------------
 * MUX1_0 = 0 & MUX1_1 = 1 ---> GPS MODULE
 * MUX1_0 = 1 & MUX1_1 = 1 ---> GPRS MODULE
 * MUX1_0 = 1 & MUX1_1 = 0 ---> AUX1 MODULE
 * MUX1_0 = 0 & MUX1_1 = 0 ---> AUX2 MODULE
 */
void WaspUtils::setMuxAux1()
{
	pinMode(MUX1_PW, OUTPUT);
	pinMode(MUX1_0, OUTPUT);      
	pinMode(MUX1_1, OUTPUT);   
	digitalWrite(MUX1_PW, HIGH);   
	digitalWrite(MUX1_0, HIGH);
	digitalWrite(MUX1_1, LOW);
}


/* setMuxAux2() - sets multiplexer on UART_1 to the desired combination (1,1)
 *
 * It sets multiplexer on UART_1 to the desired combination (1,1) to enable Aux2 module
 *
 * --------------
 * MUX1_0 = 0 & MUX1_1 = 1 ---> GPS MODULE
 * MUX1_0 = 1 & MUX1_1 = 1 ---> GPRS MODULE
 * MUX1_0 = 1 & MUX1_1 = 0 ---> AUX1 MODULE
 * MUX1_0 = 0 & MUX1_1 = 0 ---> AUX2 MODULE
 */
void WaspUtils::setMuxAux2()
{
	pinMode(MUX1_PW, OUTPUT);
	pinMode(MUX1_0, OUTPUT);      
	pinMode(MUX1_1, OUTPUT);   
	digitalWrite(MUX1_PW, HIGH);   
	digitalWrite(MUX1_0, LOW);
	digitalWrite(MUX1_1, LOW);
}


/* setMuxUSB() - set multiplexer on UART_0 to USB
 *
*/
void WaspUtils::setMuxUSB()
{
	if (_boot_version >= 'G')
	{
		pinMode(MUX0_PW,OUTPUT);
		digitalWrite(MUX0_PW,HIGH);
		
		pinMode(MUX_USB_XBEE,OUTPUT);
		digitalWrite(MUX_USB_XBEE,LOW);
	}
	else
	{
		pinMode(MUX_PW,OUTPUT);
		digitalWrite(MUX_PW,HIGH);
		
		pinMode(MUX_USB_XBEE,OUTPUT);
		digitalWrite(MUX_USB_XBEE,LOW);
	}
}

/* muxOFF() - switch off the multiplexer on UART_0 and UART_1
 *
*/
void WaspUtils::muxOFF()
{
	if (_boot_version >= 'G')
	{
		pinMode(MUX1_PW,OUTPUT);
		pinMode(MUX0_PW,OUTPUT);
		pinMode(MUX_USB_XBEE,OUTPUT);
		pinMode(MUX1_0,OUTPUT);
		pinMode(MUX1_1,OUTPUT);
		digitalWrite(MUX1_PW,LOW);
		digitalWrite(MUX0_PW,LOW);
		digitalWrite(MUX_USB_XBEE,LOW);  
		digitalWrite(MUX1_0, LOW);
		digitalWrite(MUX1_1, LOW);
	}
	else
	{
		pinMode(MUX_PW,OUTPUT);	
		pinMode(MUX_USB_XBEE,OUTPUT);
		pinMode(MUX1_0,OUTPUT);
		pinMode(MUX1_1,OUTPUT);
		digitalWrite(MUX_PW,LOW);	
		digitalWrite(MUX_USB_XBEE,LOW);  
		digitalWrite(MUX1_0, LOW);
		digitalWrite(MUX1_1, LOW);
	}
}



/* muxOFF1() - switch off the multiplexer on UART_1
 *
*/
void WaspUtils::muxOFF1()
{
	if (_boot_version >= 'G')
	{
		pinMode(MUX1_PW,OUTPUT);
		pinMode(MUX1_0,OUTPUT);
		pinMode(MUX1_1,OUTPUT);
		digitalWrite(MUX1_PW,LOW);
		digitalWrite(MUX1_0, LOW);
		digitalWrite(MUX1_1, LOW);		
	}
	else
	{
		// previous generation -> switch mux to Aux2
		Utils.setMuxAux2();
	}
}

/* muxOFF0() - switch off the multiplexer on UART_0
 *
*/
void WaspUtils::muxOFF0()
{
	if (_boot_version >= 'G')
	{
		pinMode(MUX0_PW,OUTPUT);
		pinMode(MUX_USB_XBEE,OUTPUT);
		digitalWrite(MUX0_PW,LOW);
		digitalWrite(MUX_USB_XBEE,LOW);
	}
	else
	{
		pinMode(MUX_PW,OUTPUT);	
		pinMode(MUX_USB_XBEE,OUTPUT);
		pinMode(MUX1_0,OUTPUT);
		pinMode(MUX1_1,OUTPUT);
		digitalWrite(MUX_PW,LOW);
		digitalWrite(MUX_USB_XBEE,LOW);  
		digitalWrite(MUX1_0, LOW);
		digitalWrite(MUX1_1, LOW);
	}
}


/* setMuxSocket0() - set multiplexer on UART_0 to SOCKET0
 *
*/
void WaspUtils::setMuxSocket0()
{
	if (_boot_version >= 'G')
	{
		pinMode(MUX0_PW,OUTPUT);
		digitalWrite(MUX0_PW,HIGH);
		
		pinMode(MUX_USB_XBEE,OUTPUT);
		digitalWrite(MUX_USB_XBEE,HIGH);
	}
	else
	{
		pinMode(MUX_PW,OUTPUT);
		digitalWrite(MUX_PW,HIGH);
		
		pinMode(MUX_USB_XBEE,OUTPUT);
		digitalWrite(MUX_USB_XBEE,HIGH);
	}
}

/* readEEPROM(address) - reads from the EEPROM specified address
 *
 * It reads from the EEPROM specified address
 * 
 * EEPROM has 4096 Bytes of memory
 */
uint8_t WaspUtils::readEEPROM(int address)
{
	return eeprom_read_byte((unsigned char *) address);
}


/* writeEEPROM(address,value) - writes the specified value into the specified address
 *
 * It writes the specified value into the specified address
 * 
 * EEPROM has 4096 Bytes of memory
 */
void WaspUtils::writeEEPROM(int address, uint8_t value)
{
	if( address >= EEPROM_START )
	{	
		eeprom_write_byte((uint8_t*) address, value);
	}
}

/*
 * setID (moteID) - store mote ID to EEPROM
 *
 * This function stores the mote Identifier in EEPROM[147-162] addresses
 */
void WaspUtils::setID(char* moteID)
{
	
	// set zeros in EEPROM addresses
	for( int i=0 ; i<16 ; i++ )
	{
		eeprom_write_byte( (uint8_t*)(i+EEPROM_FRAME_MOTEID), 0x00);
	}
	
	// set the mote ID to EEPROM memory
	for( int i=0 ; i<16 ; i++ )
	{		
		eeprom_write_byte( (uint8_t*)(i+EEPROM_FRAME_MOTEID), moteID[i] );
		// break if end of string
		if( moteID[i] == '\0') 
		{
			break;
		}
	}

}


/*
 * setAuthKey (moteID) - store the authentication key to EEPROM
 *
 * This function stores the authentication key in EEPROM[107-114] addresses
 */
void WaspUtils::setAuthKey(char* authkey)
{
	
	// set zeros in EEPROM addresses
	for(int i=0;i<8;i++)
	{
		eeprom_write_byte((unsigned char *) i+EEPROM_OTA_AUTHKEY, 0x00);
	}
	
	// set the authentication key to EEPROM memory
	for(int i=0;i<8;i++)
	{		
		eeprom_write_byte((unsigned char *) i+EEPROM_OTA_AUTHKEY, authkey[i]);
		// break if end of string
		if( authkey[i] == '\0') 
		{
			break;
		}
	}
}



/* readSerialChip() - reads the Waspmote unique serial identifier chip several 
 * times and compare if always is equal
 *  
 */
unsigned long WaspUtils::readSerialChip()
{	
	int data[64];
	int aux_48[48];
	unsigned long id = 0;
	int attempts = 2;
	unsigned long id_array[attempts];	
	unsigned long ID_ERROR = 0xFFFFFFFF;
	unsigned long seed = 1;
		
	for(int index = 0; index < attempts; index++)
	{
		// init seed
		seed = 1;
		
		WaspOneWire OneWire(LED1);
	
		Utils.setLED(LED0,LED_OFF);
		Utils.setLED(LED1,LED_OFF);
		
		// init variable
		id_array[index] = 0;	
		
		// Powering the serial ID chip
		pinMode(LED0, OUTPUT);
		digitalWrite(LED0,HIGH);
	
		// reset DS2411 chip
		OneWire.resetSerialID();	
		
		Utils.setLED(LED1,LED_ON);
		delay(10);
	  
		// ask the ID number
		OneWire.write(0x33,0);
		delay(50);
		
		// read the ID number
		for (int i = 63; i >= 0;i--)
		{
			data[i] = OneWire.read_bit();
			delay(1);
		}

		for (int i = 8;i < 56;i++)
		{
			aux_48[i-8]=data[i];
		}
		
		// convert from the array to integer
		for(int i=(48-1);i>=0;i--)
		{
			if(aux_48[i] == 1)
			{
				id_array[index] += seed;
			}
			seed = seed * 2;
		}			
		
		if (id_array[index] == ID_ERROR) 
		{
			id_array[index] = 0;
		}
		
		// Powering off the serial ID chip
		digitalWrite(LED0,LOW);
		Utils.setLED(LED0,LED_OFF);
		Utils.setLED(LED1,LED_OFF);
	}		
	
	for(int index = 0; index < attempts-1; index++)
	{
		if( id_array[index] != id_array[index+1] )
		{
			return 0;
		}
	}
	
	// give value
	id = id_array[0];
	
	return id;
}




/* readSerialID() - reads the Waspmote unique serial identifier
 *
 * It reads the Waspmote unique serial identifier
 */
unsigned long WaspUtils::readSerialID()
{
	uint8_t error;
	unsigned long eeprom_id;
	unsigned long id;
	
	if (_boot_version >= 'G')
	{
		eeprom.ON();
		error = eeprom.readSerialNumber();
		if (error == 0)
		{		
			_serial_id[0] = eeprom._response[0];
			_serial_id[1] = eeprom._response[1];
			_serial_id[2] = eeprom._response[2];
			_serial_id[3] = eeprom._response[3];
			_serial_id[4] = eeprom._response[4];
			_serial_id[5] = eeprom._response[5];
			_serial_id[6] = eeprom._response[6];
			_serial_id[7] = eeprom._response[7];
			return 0;
		}
		else
		{
			memset( (uint8_t*)_serial_id, 0x00, sizeof(_serial_id));
			return 1;
		}
	}
	else
	{
		id = readSerialChip();
		if( id == 0 )
		{
			// get eeprom serial id (latest Waspmote batches)
			eeprom_id = Utils.getSerialEEPROM();
			
			// check correct value of serial id
			// -> 0x0A0A0A0A is a wrong value for default Waspmote EEPROM 
			// -> 0xFFFFFFFF is a wrong value
			if( (eeprom_id != 0x0A0A0A0A) && (eeprom_id !=0xFFFFFFFF) )
			{
				id = eeprom_id;
			}
			else
			{
				id = 0;
			}
		}
		
		_serial_id[0] = 0x00;
		_serial_id[1] = 0x00;
		_serial_id[2] = 0x00;
		_serial_id[3] = 0x00;
		_serial_id[4] = (id>>24) & 0xFF;
		_serial_id[5] = (id>>16) & 0xFF;
		_serial_id[6] = (id>>8)  & 0xFF;
		_serial_id[7] = (id>>0)  & 0xFF;
		
		return id;
	}
}


/* setSerialEEPROM() - sets the Waspmote unique serial identifier to EEPROM
 *
 * The serial id to be stored is specified as input
 */
bool WaspUtils::setSerialEEPROM( unsigned long serial )
{		
	// Store to EEPROM
	eeprom_write_dword( (uint32_t*)EEPROM_SERIALID_START, serial );
	
	// check EEPROM
	if( serial == getSerialEEPROM() )
	{		
		return true;
	}
	
	return false;
}


/* getSerialEEPROM() - gets the Waspmote unique serial identifier from EEPROM
 *
 */
unsigned long WaspUtils::getSerialEEPROM()
{		
	return eeprom_read_dword( (uint32_t*)EEPROM_SERIALID_START );	
}


/* readTempDS1820() - reads the DS1820 temperature sensor
 *
 * It reads the DS1820 temperature sensor
 */
float WaspUtils::readTempDS1820(uint8_t pin)
{    
	return readTempDS1820( pin, true);
}

/* readTempDS1820() - reads the DS1820 temperature sensor
 *
 * It reads the DS1820 temperature sensor
 */
float WaspUtils::readTempDS1820(uint8_t pin, bool is3v3 )
{
	// check if it is necessary to turn on 
	// the generic 3v3 power supply
	if( is3v3 == true )
	{
		PWR.setSensorPower(SENS_3V3,SENS_ON);
		delay(10);
	}
	
	WaspOneWire OneWireTemp(pin);
	
	byte data[12];
	byte addr[8];
	delay(25);
	if ( !OneWireTemp.search(addr))
	{
		//no more sensors on chain, reset search
		OneWireTemp.reset_search();
		return -1000;
	}
	
	if ( WaspOneWire::crc8( addr, 7) != addr[7]) 
	{
		return -1000;	
	}

	if ( addr[0] != 0x10 && addr[0] != 0x28)
	{
		return -1000;
	}
	
	OneWireTemp.reset();
	OneWireTemp.select(addr);
	OneWireTemp.write(0x44,1); // start conversion, with parasite power on at the end
    delay(1000);
    
	OneWireTemp.reset();
	OneWireTemp.select(addr);    
	OneWireTemp.write(0xBE); // Read Scratchpad

  	for (int i = 0; i < 9; i++)  // we need 9 bytes
	{
		data[i] = OneWireTemp.read();
	}
  
	OneWireTemp.reset_search();
  
	byte MSB = data[1];
	byte LSB = data[0];

	float tempRead = ((MSB << 8) | LSB); //using two's compliment
	float TemperatureSum = tempRead / 16;
        
    // check if it is necessary to turn off 
	// the generic 3v3 power supply
	if( is3v3 == true )
	{
		PWR.setSensorPower(SENS_3V3,SENS_OFF);
	}
    
	return TemperatureSum;
}




/*
 * It converts a hexadecimal number stored in an array to a string (8 Byte 
 * numbers). This function is used by the XBee module library in order to 
 * convert mac addresses
 * 
 */
void WaspUtils::hex2str(uint8_t* number, char* macDest)
{
	hex2str(number,macDest,8);
}

/*
 * It converts a hexadecimal number stored in an array to a string (length is an 
 * input parameter). This function is used by the XBee module library in order to 
 * convert mac addresses
 * 
 */
void WaspUtils::hex2str(uint8_t* number, char* macDest, uint8_t length)
{
	uint8_t aux_1=0;
	uint8_t aux_2=0;

	for(int i=0;i<length;i++)
	{
		aux_1=number[i]/16;
		aux_2=number[i]%16;
		if (aux_1<10)
		{
			macDest[2*i]=aux_1+'0';
		}
		else{
			macDest[2*i]=aux_1+('A'-10);
		}
		if (aux_2<10){
			macDest[2*i+1]=aux_2+'0';
		}
		else{
			macDest[2*i+1]=aux_2+('A'-10);
		}
	} 
	macDest[length*2]='\0';
}

/* readTemperature() - reads the temperature sensor
 *
 * It reads the temperature sensor
 */
float WaspUtils::readTemperature()
{
	// variables
	int sensor_value = 0;
	float sensor_volts = 0;
	float temperature = 0.0;

	// Powering the sensor
	PWR.setSensorPower(SENS_3V3,SENS_ON);
	delay(1000);
  
	// Reading the analog value
	sensor_value = analogRead(ANALOG6);
	delay(100);
	sensor_value = analogRead(ANALOG6);
  	delay(100);

	PWR.setSensorPower(SENS_3V3,SENS_OFF);	
		
	// Calculating the volts
	sensor_volts = float(sensor_value) * 3.300 / 1023;
  
	// Calculating the temperature value
	temperature = (sensor_volts * 100) - 50;
    
    return temperature;
}
	
/* readHumidity() - reads the humidity sensor
 *
 * It reads the humidity sensor
 */
uint8_t WaspUtils::readHumidity()
{
	// variables
	int sensor_value = 0;
	float sensor_volts = 0;
	int humidity = 0;
	
	// Powering the sensor
	PWR.setSensorPower(SENS_3V3,SENS_ON);
	
	delay(15000);
  
	// Reading the analog value
	sensor_value = analogRead(ANALOG7);
	delay(100);
	sensor_value = analogRead(ANALOG7);
	delay(100);  
	PWR.setSensorPower(SENS_3V3,SENS_OFF);
	
	// Calculating the volts
	sensor_volts = float(sensor_value) * 3.300 / 1023;
	  
	// Calculating the light value
	humidity = int((sensor_volts * 100) / 3);
	  
	return humidity;
}

/* readLight() - reads the light sensor
 *
 * It reads the light sensor
 */
uint8_t WaspUtils::readLight()
{
	// variables
	int sensor_value = 0;
	float sensor_volts = 0;
	int light = 0;
	
	// Powering the sensor
	PWR.setSensorPower(SENS_3V3,SENS_ON);
  
	// Reading the analog value
	sensor_value = analogRead(ANALOG5);
	delay(100);
	sensor_value = analogRead(ANALOG5);
  
	PWR.setSensorPower(SENS_3V3,SENS_OFF);
  
	// Calculating the volts
	sensor_volts = float(sensor_value) * 3.300 / 1023;
  
	// Calculating the light value
	light = int((sensor_volts * 100) / 3.3);
  
    return light;
}


/*
 Function: Coverts a long to a number stored in an array
*/
uint8_t WaspUtils::long2array(long num, char* numb)
{
	long aux=num;
	uint8_t i=0;
	
	if( num<0 )
	{
		num = ~(num);
		num+=1;
		numb[i]='-';
		i++;
	}
	aux=num;
	while(aux>=10)
	{
		aux=aux/10;
		i++;
	}
	numb[i+1]='\0';
	aux=num;
	while(aux>=10)
	{
		numb[i]=aux%10 + '0';
		aux=aux/10;
		i--;
	}
	numb[i]=aux + '0';
	return i;
}

/*
 * Function: Converts a string to an hex number
 * 
 */
uint8_t WaspUtils::str2hex(char* str)
{
    int aux=0, aux2=0;

    if( (*str>='0') && (*str<='9') )
    {
        aux=*str++-'0';
    }
    else if( (*str>='A') && (*str<='F') )
    {
        aux=*str++-'A'+10;
    }
    else if( (*str>='a') && (*str<='f') )
    {
        aux=*str++-'a'+10;
    }
    if( (*str>='0') && (*str<='9') )
    {
        aux2=*str-'0';
    }
    else if( (*str>='A') && (*str<='F') )
    {
        aux2=*str-'A'+10;
    }
    else if( (*str>='a') && (*str<='f') )
    {
        aux2=*str-'a'+10;
    }
    return aux*16+aux2;
}



/*
 * Function: Converts a string to an array of bytes
 * For example: If the input string is defined as: 
 * 		char input[] = "";
 * The output string is array -> 23576173706D6F74655F50726F23
 */
uint16_t WaspUtils::str2hex(char* str, uint8_t* array)
{		
    // get length in bytes (half of ASCII characters)
	uint16_t length=strlen(str)/2;
	
    // Conversion from ASCII to HEX    
    for(uint16_t j=0; j<length; j++)
    {    
		array[j] = Utils.str2hex(&str[j*2]);      
    }
	
	return length;
}





/*
 * Function: Converts a string to an array of bytes
 */
uint16_t WaspUtils::str2hex(char* str, uint8_t* array, uint16_t size)
{		
    // get length in bytes (half of ASCII characters)
	uint16_t length = strlen(str)/2;	
	
    // Conversion from ASCII to HEX    
    for(uint16_t j=0; j<length; j++)
    {    
		// check size of array
		if (j >= size)
		{
			length = j;
			break;
		}
		
		// store conversion in array
		array[j] = Utils.str2hex(&str[j*2]);		     
    }
	
	return length;
}


/*
 * Function: Converts a string to an hex number
 * 
 */
uint8_t WaspUtils::str2hex(uint8_t* str)
{
	int aux=0, aux2=0;
	
	
	if( (*str>='0') && (*str<='9') )
	{
		aux=*str++-'0';
	}
	else if( (*str>='A') && (*str<='F') )
	{
		aux=*str++-'A'+10;
	}
	if( (*str>='0') && (*str<='9') )
	{
		aux2=*str-'0';
	}
	else if( (*str>='A') && (*str<='F') )
	{
		aux2=*str-'A'+10;
	}
	return aux*16+aux2;
}

/*
 * Function: Generates a decimal number from two ASCII characters which were numbers
 * Returns: The generated number
 * 
 */
uint8_t WaspUtils::converter(uint8_t conv1, uint8_t conv2)
{
	uint8_t aux=0;
	uint8_t aux2=0;
	uint8_t resul=0;

	switch(conv1)
	{
		case 48: aux=0;
		break;
		case 49: aux=1;
		break;
		case 50: aux=2;
		break;
		case 51: aux=3;
		break;
		case 52: aux=4;
		break;
		case 53: aux=5;
		break;
		case 54: aux=6;
		break;
		case 55: aux=7;
		break;
		case 56: aux=8;
		break;
		case 57: aux=9;
		break;
		case 65: aux=10;
		break;
		case 66: aux=11;
		break;
		case 67: aux=12;
		break;
		case 68: aux=13;
		break;
		case 69: aux=14;
		break;
		case 70: aux=15;
		break;
	}
	switch(conv2)
	{
		case 48: aux2=0;
		break;
		case 49: aux2=1;
		break;
		case 50: aux2=2;
		break;
		case 51: aux2=3;
		break;
		case 52: aux2=4;
		break;
		case 53: aux2=5;
		break;
		case 54: aux2=6;
		break;
		case 55: aux2=7;
		break;
		case 56: aux2=8;
		break;
		case 57: aux2=9;
		break;
		case 65: aux2=10;
		break;
		case 66: aux2=11;
		break;
		case 67: aux2=12;
		break;
		case 68: aux2=13;
		break;
		case 69: aux2=14;
		break;
		case 70: aux2=15;
		break;
		default: aux2=100;
		break;
	}
	if(aux2==100) // Only one character but we have treated two, so We have to fix it
	{
		resul=aux;
	}
	else
	{
		resul=(aux*16)+aux2;
	}
	return resul;
}

/*
 * Function: Converts a float variable to a string
 * Returns: void
 * 
 * Remarks: It is recommended to use the AVR std library function
 * http://www.nongnu.org/avr-libc/user-manual/group__avr__stdlib.html
 * 
 * 		char* dtostrf( 	double  	__val,
 *						signed char  	__width,
 *						unsigned char  	__prec,
 *						char *  	__s ) 	
 * 
 */
void WaspUtils::float2String (float fl, char str[], int N) 
{

	boolean neg = false;
 
	if( fl<0 ){
		neg = true;
		fl*=-1;
	}
 
	float numeroFloat=fl; 
	int parteEntera[10];
	int cifra; 
	long numero=(long)numeroFloat;  
	int size=0;
  
	while(1){
		size=size+1;
		cifra=numero%10;
		numero=numero/10;
		parteEntera[size-1]=cifra; 
		if (numero==0){
			break;
		}
	}

	int indice=0;
	if( neg ){
		indice++;
		str[0]='-';
	}
	for (int i=size-1; i>=0; i--)
	{
		str[indice]=parteEntera[i]+'0'; 
		indice++;
	}

	str[indice]='.';
	indice++;

	numeroFloat=(numeroFloat-(int)numeroFloat);
	for (int i=1; i<=N ; i++)
	{
		numeroFloat=numeroFloat*10;
		cifra= (long)numeroFloat;          
		numeroFloat=numeroFloat-cifra;
		str[indice]=char(cifra)+48;
		indice++;
	}
	str[indice]='\0';
}



/*
 * loadOTA() - It writes into the EEPROM the name of the OTA file
 * 
 * This function writes into the EEPROM the name of the OTA file
 * 
 */
void WaspUtils::loadOTA(const char* filename, uint8_t version)
{ 
	uint8_t program_version;
	
	// save the name in EEPROM
	for (int aux=0; aux<32; aux++)
	{
		if (aux < 7)
		{
			// filename
			eeprom_write_byte((uint8_t *) (aux+2), uint8_t(filename[aux]));
		}
		else
		{
			// asterisks
			eeprom_write_byte((uint8_t *) (aux+2), 0x2A);
		}
	}

	// set OTA flag in EEPROM to '1'
	eeprom_write_byte((uint8_t *) EEPROM_OTA_FLAG, 0x01);
  
	// set OTA retries to 3 attempts
	eeprom_write_byte((uint8_t *) EEPROM_OTA_RETRIES, 0x03);
	
	// sets the new program version into EEPROM
	program_version = eeprom_read_byte((unsigned char *) EEPROM_PROG_VERSION );
	eeprom_write_byte((unsigned char *) EEPROM_PROG_VERSION_BACKUP, program_version);
	
	// sets the new program version into EEPROM
	setProgramVersion(version);
  
	SD.ON();
	delay(100);
	
	// reboot
	PWR.reboot();

	// A little delay
	delay(2000);
}

/*
 * readEEPROM() - It reads the EEPROM from position 2 to 34 and shows it by USB
 * 
 * This function prints by USB the map of positions 2 to 34
 * 
 */
void WaspUtils::readEEPROM()
{
	uint8_t aux;

	USB.println(F("---------------------------------"));
	USB.println(F("EEPROM MAP"));
	USB.println(F("---------------------------------"));

	USB.print(F("OTA: "));
	USB.printHex(Utils.readEEPROM(0x01));
	USB.println();

	USB.println(F("\n\t\t\t\tPID\t\tCID\t\tLast Stable ID"));
	// Reading the EEPROM
	for(int address=2; address<34; address++)
	{
		USB.print(F("Address:  "));
		USB.print(address,DEC);
		USB.print(F(" -- Value: \t\t"));

		//PID
		aux = Utils.readEEPROM(address);
		USB.printHex(aux);
		USB.print(F("   "));
		USB.print(char(aux));

		//CID    
		aux = Utils.readEEPROM(address+32);
		USB.print(F("\t\t"));
		USB.printHex(aux);
		USB.print(F("   "));
		USB.print(char(aux));

		//Last Stable ID    
		aux = Utils.readEEPROM(address+64);
		USB.print(F("\t\t"));
		USB.printHex(aux);
		USB.print(F("   "));
		USB.println(char(aux));
	}
}

/*
 * checkNewProgram() - It checks the new firmware upgrade
 * 
 * This function checks if there is any OTA process has been performed. This 
 * function should be called at the beginning of any OTA-supporting code, just
 * after switching the XBee module ON 
 * 
 * Returns '0' if reprogramming error, '1' if reprogramming OK and '2' for normal restart
 */
int8_t WaspUtils::checkNewProgram()
{
	uint8_t buffer_OTA[32];
	uint8_t current_ID[32];
	uint8_t program_version;
	uint8_t program_version_backup;
	bool reprogrammingOK = true;

	// copy current ID (CID) to Last Stable ID 
	for (int i = 0; i < 32; i++)
	{
		current_ID[i] = Utils.readEEPROM(i + 34);
		eeprom_write_byte((uint8_t *)(i + 66), current_ID[i]);
	}

	// check OTA flag
	if (WaspRegister & REG_OTA)
	{
		// Checking if programID and currentID are the same 
		// If so, the program has been changed properly
		for (int i = 0; i < 32; i++)
		{
			// get PID
			buffer_OTA[i] = eeprom_read_byte((uint8_t*)(i+2));
		}

		for (int i = 0; i < 32; i++)
		{
			// compare PID vs CID
			if (buffer_OTA[i] != eeprom_read_byte((uint8_t*)(i+34)))
			{
				reprogrammingOK = false;
			}
		}

		// unset OTA Flag in Waspmote Control Register
		WaspRegister &= ~(REG_OTA);

		// If both IDs are equal a confirmation message is sent to the trasmitter
		if (reprogrammingOK)
		{
			program_version = eeprom_read_byte((unsigned char *) EEPROM_PROG_VERSION );
			eeprom_write_byte((unsigned char *) EEPROM_PROG_VERSION_BACKUP, program_version);
			
			return 1;
		}
		// If the IDs are different an error message is sent to the transmitter
		else
		{     		
			program_version = eeprom_read_byte((unsigned char *) EEPROM_PROG_VERSION_BACKUP);
			eeprom_write_byte((unsigned char *) EEPROM_PROG_VERSION, program_version);
			return 0; 
		}
	}   
	else
	{   
		program_version = eeprom_read_byte((unsigned char *) EEPROM_PROG_VERSION );
		program_version_backup = eeprom_read_byte((unsigned char *) EEPROM_PROG_VERSION_BACKUP );
		
		if (program_version_backup != program_version)
		{
			eeprom_write_byte((unsigned char *) EEPROM_PROG_VERSION, program_version_backup);
			return 0;
		}
		return 2;  
	}

} 

/*
 * getProgramID (program_ID) - read program ID (PID) from EEPROM
 *
 * This function read the program Identifier (PID) from EEPROM
 */
void WaspUtils::getProgramID(char* program_ID)
{
	for(int address = 2; address < 9; address++)
	{
		//PID
		program_ID[address-2] = Utils.readEEPROM(address);
	}
	
	program_ID[7] = '\0';
}

/*
 * getID (moteID) - read mote ID from EEPROM
 *
 * This function read the mote Identifier from EEPROM[147-162] addresses
 */
void WaspUtils::getID(char* moteID)
{
	// set the mote ID to EEPROM memory
	for( int i = 0 ; i<16 ; i++ )
	{		
		moteID[i] = Utils.readEEPROM(i+147);
		// break if end of string
		if( moteID[i] == '\0') 
		{
			break;
		}
	}
}

/*
 * setProgramVersion (version) - store the version of the program to EEPROM
 *
 * This function stores the version of the program to EEPROM
 */
void WaspUtils::setProgramVersion(uint8_t version)
{
	eeprom_write_byte((unsigned char *) EEPROM_PROG_VERSION, version);
}

/*
 * getProgramVersion () - read the version of the program from EEPROM
 *
 * This function reads the version of the program from EEPROM
 */
uint8_t WaspUtils::getProgramVersion()
{
	return (eeprom_read_byte((unsigned char *) EEPROM_PROG_VERSION));
}


/*
 * getBootVersion () - read the version of the Bootloader from EEPROM
 *
 * 
 */
uint8_t WaspUtils::getBootVersion()
{
	uint8_t boot_version;
	boot_version = eeprom_read_byte((unsigned char *) 223);
	
	if(boot_version != 0xFF)
	{
		return boot_version;
	}
	else
	{
		return 0x00;
	}
}

/*
 * showVersion () - display Waspmote version number: v12 or v15
 *
 * 
 */
void WaspUtils::showVersion()
{
	if (getBootVersion() >= 'H')
	{
		USB.println(F("v15"));
	}
	else
	{
		USB.println(F("v12"));
	}
	
}


WaspUtils Utils = WaspUtils();

