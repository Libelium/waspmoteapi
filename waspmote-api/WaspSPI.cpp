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
 *  Version:		1.4
 *  Design:			David Gascón
 *  Implementation:	Alberto Bielsa, David Cuartielles
 */
  

#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif



/******************************************************************************* 
 * begin
 *
 ******************************************************************************/
void WaspSPI::begin() 
{
  // Set direction register for SCK and MOSI pin.
  // MISO pin automatically overrides to INPUT.
  // When the SS pin is set as OUTPUT, it can be used as
  // a general purpose output port (it doesn't influence
  // SPI operations).

  pinMode(SD_SCK, OUTPUT);
  pinMode(SD_MOSI, OUTPUT);
  pinMode(SD_SS, OUTPUT);

  digitalWrite(SD_SCK, LOW);
  digitalWrite(SD_MOSI, LOW);
  digitalWrite(SD_SS, HIGH);

  // Warning: if the SS pin ever becomes a LOW INPUT then SPI 
  // automatically switches to Slave, so the data direction of 
  // the SS pin MUST be kept as OUTPUT.
  SPCR |= _BV(MSTR);
  SPCR |= _BV(SPE);
}



/******************************************************************************* 
 * close
 *
 ******************************************************************************/
void WaspSPI::close() 
{  
	// Close SPI COM only when all modules are off
	// if one of them is still on, then do not proceed with
	// the closing process
	if( (SPI.isSD == false) 
		&& (SPI.isSX == false) 
		&& (SPI.isDustSensor == false) 
		&& (SPI.isSmartWater == false) 
		&& (SPI.isSmartWaterIons == false)
		&& (SPI.isRS485 == false) )
	{
		// define SPI pins as INPUTs (high impedance)
		pinMode(SD_SCK, INPUT);
		pinMode(SD_MOSI, INPUT);
		pinMode(SD_MISO, INPUT);
		pinMode(SD_SS, INPUT);
		
		// end SPI com
		SPI.end();
	}
}



/******************************************************************************* 
 * end
 *
 ******************************************************************************/
void WaspSPI::end() 
{
  SPCR &= ~_BV(SPE);
}



/******************************************************************************* 
 * setBitOrder
 *
 ******************************************************************************/
void WaspSPI::setBitOrder(uint8_t bitOrder)
{
  if(bitOrder == LSBFIRST) 
  {
    SPCR |= _BV(DORD);
  } else {
    SPCR &= ~(_BV(DORD));
  }
}


/******************************************************************************* 
 * setDataMode
 *
 ******************************************************************************/
void WaspSPI::setDataMode(uint8_t mode)
{
  SPCR = (SPCR & ~SPI_MODE_MASK) | mode;
}


/******************************************************************************* 
 * setClockDivider
 *
 ******************************************************************************/
void WaspSPI::setClockDivider(uint8_t rate)
{
  SPCR = (SPCR & ~SPI_CLOCK_MASK) | (rate & SPI_CLOCK_MASK);
  SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | (rate & SPI_2XCLOCK_MASK);
}


/******************************************************************************* 
 * receive
 *
 ******************************************************************************/
uint8_t WaspSPI::receive() 
{
	// perform secure SPI power management
	SPI.secureBegin();
	
	SPDR = 0XFF;
	while (!(SPSR & (1 << SPIF)));
	
	// perform secure SPI power management
	SPI.secureEnd();
	
	
	return SPDR;
}


/******************************************************************************* 
 * receive
 *
 ******************************************************************************/
uint8_t WaspSPI::receive(uint8_t* buf, size_t n) 
{	
	if (n-- == 0) 
	{
		return 0;
	}
	
	// perform secure SPI power management
	SPI.secureBegin();
	
	SPDR = 0XFF;
	for (size_t i = 0; i < n; i++) 
	{
		while (!(SPSR & (1 << SPIF)));
		uint8_t b = SPDR;
		SPDR = 0XFF;
		buf[i] = b;
	}
	while (!(SPSR & (1 << SPIF)));
	buf[n] = SPDR;
	
	// perform secure SPI power management
	SPI.secureEnd();
		
	return 0;
}



/******************************************************************************* 
 * transfer
 *
 ******************************************************************************/
byte WaspSPI::transfer(uint8_t _data) 
{	
	// perform secure SPI power management
	SPI.secureBegin();
	
	SPDR = _data;
	while (!(SPSR & _BV(SPIF)))
    ;
    
	// perform secure SPI power management
	SPI.secureEnd();
    
	return SPDR;
}



/******************************************************************************* 
 * transfer
 *
 ******************************************************************************/
void WaspSPI::transfer(const uint8_t* buf , size_t n) 
{
  for (size_t i = 0; i < n; i++) {
    transfer(buf[i]);
  }
}





/******************************************************************************* 
 * setSPISlave() - It selects the slave on SPI bus to use
 *
 * It selects the slave on SPI bus to use
 *
 ******************************************************************************/
void WaspSPI::setSPISlave(uint8_t SELECTION)
{
	pinMode(SD_SS,OUTPUT);	
	pinMode(SOCKET0_SS,OUTPUT);
	
	digitalWrite(SD_SS,HIGH);
	digitalWrite(SOCKET0_SS,HIGH);
	
	if( WaspRegister & REG_DUST_GASES_PRO )
	{
		pinMode(DUST_SENSOR_CS,OUTPUT);
		digitalWrite(DUST_SENSOR_CS,HIGH);
	}	
	
	if( WaspRegister & REG_WATER )
	{
		// Chip Select of the Smart Water ADC 
		pinMode(DIGITAL4,OUTPUT);
		digitalWrite(DIGITAL4,HIGH);
	}
	
	if( WaspRegister & REG_WATER_IONS )
	{
		// Chip Select of the Smart Water Ions ADC 
		pinMode(DIGITAL1,OUTPUT);
		digitalWrite(DIGITAL1,HIGH);
	}
	
	if( WaspRegister & REG_RS485 )
	{
		// Chip Select of the RS-485 Board 
		pinMode(SOCKET0_SS,OUTPUT);
		digitalWrite(SOCKET0_SS,HIGH);
	}
	
	switch(SELECTION)
	{
		case SD_SELECT:		 		digitalWrite(SD_SS,LOW);
									break;
		case SOCKET0_SELECT:		digitalWrite(SOCKET0_SS,LOW);
									break;
		case SOCKET1_SELECT:		Utils.setMuxSocket1();
									digitalWrite(MUX_TX,LOW);
									break;
		case DUST_SENSOR_SELECT:	if( WaspRegister & REG_DUST_GASES_PRO )
									{
										digitalWrite(DUST_SENSOR_CS,LOW);
									}
									break;
		case SMART_WATER_SELECT:	if( WaspRegister & REG_WATER )
									{
										digitalWrite(DIGITAL4,LOW);
									}
									break;
									
		case SMART_IONS_SELECT:		if( WaspRegister & REG_WATER_IONS )
									{
										digitalWrite(DIGITAL1,LOW);
									}
									break;							
									
		case ALL_DESELECTED:		digitalWrite(SD_SS,HIGH);							 
									digitalWrite(SOCKET0_SS,HIGH);
									
									if( WaspRegister & REG_DUST_GASES_PRO )
									{
										digitalWrite(DUST_SENSOR_CS,HIGH);
									}	
									
									if( WaspRegister & REG_WATER )
									{
										digitalWrite(DIGITAL4,HIGH);
									}
									
									if( WaspRegister & REG_WATER_IONS )
									{
										digitalWrite(DIGITAL1,HIGH);
									}
																		
									break;
		default:					break;		
	}
}




/******************************************************************************* 
 * secureBegin() - It makes sure all SPI slaves are swichted on when they
 * have been plugged to Waspmote. Thus, when they are powered on, the MISO,
 * MOSI, SCK lines are set to High Impedance
 *
 ******************************************************************************/
void WaspSPI::secureBegin()
{	
	// this codeblock belongs to the performance of the SD card
	// check if Dust sensor was not powered on before using the SD card
	if( WaspRegister & REG_DUST_GASES_PRO )
	{
		if( (WaspRegister & REG_3V3) && (SPI.isDustSensor == false) )		
		{
			digitalWrite(DUST_SENSOR_POWER,HIGH);		
		}
	}	
	
	// this codeblock belongs to the performance of the SD card
	// check if Semtech module was not powered on before using the SD card
	if( WaspRegister & REG_SX )
	{
		if( SPI.isSX == false )
		{
			pinMode(XBEE_PW,OUTPUT);
			digitalWrite(XBEE_PW,HIGH);			
		}
	}	
	
	// SD card
	if( SPI.isSD == false )
	{			
		pinMode(MEM_PW,OUTPUT);
		digitalWrite(MEM_PW, HIGH);				
	}
	
	// check if Semtech module was not powered on before using the SD card
	if( WaspRegister & REG_RS485 )
	{
		if( SPI.isRS485 == false )
		{
			pinMode(XBEE_PW,OUTPUT);
			digitalWrite(XBEE_PW,HIGH);			
		}
	}	
	
}



/******************************************************************************* 
 * secureEnd() - It makes sure all SPI slaves are swichted off when they
 * have been plugged to Waspmote and they were switched off prior to the SPI 
 * operation. 
 *
 ******************************************************************************/
void WaspSPI::secureEnd()
{		
	// this codeblock belongs to the performance of the SD card
	// check if Dust sensor was not powered on before using the SD card
	if( WaspRegister & REG_DUST_GASES_PRO )
	{
		if( (WaspRegister & REG_3V3) && (SPI.isDustSensor == false) )		
		{
			digitalWrite(DUST_SENSOR_POWER,LOW);		
		}
	}	
	
	// this codeblock belongs to the performance of the SD card
	// switch off the SX module if it was not powered on 
	if( WaspRegister & REG_SX )
	{
		if( SPI.isSX == false )
		{			
			pinMode(XBEE_PW,OUTPUT);
			digitalWrite(XBEE_PW,LOW);			
		}
	}
	
	// SD card
	if( SPI.isSD == false )
	{			
		pinMode(MEM_PW,OUTPUT);
		digitalWrite(MEM_PW, LOW);				
	}
	
	if( WaspRegister & REG_RS485 )
	{
		if( SPI.isRS485 == false )
		{			
			pinMode(XBEE_PW,OUTPUT);
			digitalWrite(XBEE_PW,LOW);			
		}
	}
	
	
}




/// Preinstantiate object

WaspSPI SPI = WaspSPI();
