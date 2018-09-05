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
 *  Version:		3.1
 *  Design:			Ahmad Saad
 */

//!*************************************************************************************
//! Includes
//!*************************************************************************************
#include "ADC7705.h"

 
#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif


//!*************************************************************************************
//! ADC Object
//!*************************************************************************************
adcClass myADC;


//!*************************************************************************************
//!	Name:	adcClass()										
//!	Description: Class contructor		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
adcClass::adcClass() {}

//!*************************************************************************************
//!	Name:	begin()										
//!	Description: Configures the SPI to be used with the ADC		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
void adcClass::begin(void)
{	
	// Activate the flag
	SPI.isSmartWaterIons = true;
	// Initialization of the SPI bus
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	//Divide the clock frequency
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	//Set data mode
	SPI.setDataMode(SPI_MODE0);
	
	//ADC chips select input
	pinMode(CS_AD7705, OUTPUT);	
	digitalWrite(CS_AD7705, HIGH);  
	delay(10);
	
}

//!*************************************************************************************
//!	Name:	configure()										
//!	Description: Configures the SPI to be used with the ADC		
//!	Param : void														
//!	Returns: void							
//!*************************************************************************************
void adcClass::configure(uint8_t CHANNEL)
{
	// Selet the ADC		
	SPI.setSPISlave(SMART_IONS_SELECT);
	
	SPI.transfer(CHANNEL|WRITE|CLOCK_REG);  // Select channel 1, setup write to clock reg.
	SPI.transfer(CLKDIS|CLKDIV|CLK|FILTER);  // 5MHz Clock, 50MHz output rate
	SPI.transfer(CHANNEL|WRITE|SETUP_REG);  // Select channel 1, setup write to setup reg.
	SPI.transfer(GAIN_1|UNIPOLAR|BUF_OFF|FSYNC_CLR|OP_SELF_CAL);  // gain=1, bipolar mode, buffer off, clear FSYNC and perform a Self Calibration

	// Unselect all
	SPI.setSPISlave(ALL_DESELECTED);
}

//!*************************************************************************************
//!	Name:	readADC()										
//!	Description: Take a measure from the ADC		
//!	Param : uint8_t channel: the channel of the ADC to read from														
//!	Returns: void							
//!*************************************************************************************
float adcClass::readADC(uint8_t channel)
{
	// Data read from the SPI
	unsigned int data=0;
	unsigned int cont = 0;
	unsigned int i = 0;

	// This variable is the Accumulator
	long ACM = 0;

	// Selet the ADC		
	SPI.setSPISlave(SMART_IONS_SELECT);
	
	//Take 200 samples
	for (int i = 0; i< 200; i++) { 		
		
		// Send read command
		SPI.transfer(channel|DATA_REG|READ);
		// Wait until data is ready 
		// The DRDY is a pin of the ADC connected to Waspmote board
		while(!digitalRead(DRDY) && (cont < timeOut))
		{
			cont++;
		}
		
		
		// Get the most significant 8 bits
		data = SPI.transfer(0)<<8;
		// Get the least significant 8 bits
		data |= SPI.transfer(0);
		
		// Accumulate the read values
		ACM += data; 			
		cont = 0;
	}

	SPI.setSPISlave(ALL_DESELECTED);
	
	// The formule to convert to voltage => RETURN volts = (ACM * 4.096) / (200 * 65536)
	// ACM = Accumulator
	// 200 = Number of samples
	// 4.096 = Voltage reference
	// 65536 = 2^16 (resolution of the ADC)	
	return ACM /3200000.0;
}


