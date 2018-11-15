/*! \file ADC.cpp
 *  \brief Library for managing the ADC of Smart Agriculture Extreme sensor board
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
 *  Version:		3.0
 *  Design:			Ahmad Saad, Javier Siscart
 */

//!*************************************************************************************
//! Includes
//!*************************************************************************************
#include "ADC.h"

#ifndef __WPROGRAM_H__
  #include <WaspClasses.h>
#endif

/*	Class constructor
 */
LTC::LTC() 
{}

/*	begin: Configures the SPI to be used with the ADC
 *	Parameters: void
 *  Return: void
 */
void LTC::begin(void)
{
	// Enable the correspondig flag
	SPI.isSmartAgrXtr = true;

	SPI.begin();

	// ADC chip select- HIGH by default
	pinMode(XTR_ADC_CS, OUTPUT);
	digitalWrite(XTR_ADC_CS, HIGH);

    // Initialization of the SPI bus
	SPI.setBitOrder(MSBFIRST);
	//Divide the clock frequency
	SPI.setClockDivider(SPI_CLOCK_DIV4);
	//Set data mode
	SPI.setDataMode(SPI_MODE0);
}

/*	readADC: Take a measure from the ADC
 *	Parameters:  uint8_t channel: the channel of the ADC to read from
 *  Return: -1000 if wrong channel, -2000 if negative or out of range. value otherwise
 */
float LTC::readADC(uint8_t channel)
{
	float value;
	uint8_t en_byte = B00001000;
	uint8_t val[4];

	// If the channel selected is wrong, return -1, else fulfill the channel selection
	// register en_byte
	if (channel > 7)
	{
		return -1000;
	}
	else
	{
		en_byte = en_byte | channel;
	}

    // Disable all pheripherals on SPI bus
	SPI.setSPISlave(ALL_DESELECTED);

	// selection of the ADC channel
	SPI.transfer(en_byte);
	delay(1);

	// A new conversion is started through a pulse in the chip selection pin and initiating
	// a transfer

	SPI.setSPISlave(SMART_XTR_SELECT);
	delay(2);
	SPI.transfer(0x00);

	SPI.setSPISlave(ALL_DESELECTED);

	// Waiting for the conversion time (max 163.36ms)
	delay(175);

	// Once the new data is ready, initiate a new transfer and put the ADC back to
	// idle state

	// This ADC has a 32 bits serial output
	// The first 4 bits represent status information
	// The next 24 bits are the conversion result, MSB first
	// The remaining 4 bits are sub LSBs beyond the 24-bit level (eliminated dividing by 16)

	SPI.setSPISlave(SMART_XTR_SELECT);
	delay(1);
	// Read 4 times to get 4*8 = 32 bits
	val[0] = SPI.transfer(0x00);
	val[1] = SPI.transfer(0x00);
	val[2] = SPI.transfer(0x00);
	val[3] = SPI.transfer(0x00);
	delay(1);

	SPI.setSPISlave(ALL_DESELECTED);

// 			ADC bits sequency
//   __________________________________________________________
//  |              |               |             |             |
//  |    val[0]    |    val[1]|    |   val[3]    |   val[4]    |
//  |______________|_______________|_____________|_____________|
//  32------------24--------------16-------------8-------------0
//			|				|				|			|
//			|				|				|		4 MSB and  shift >> 4 bits
//			|				|				|
//			|				|		8 bits and shift << 4
//			|				|
//			|		8 bits and shift << 12
//			|
//		4 LSB and shift << 20

	// Convert the read value into volts
	value = float( val[3]) / 16 + float(val[2]) * 16 + float(val[1]) * 4096 + float(val[0] & B00001111) * 1048576;
	//						|						|					|									|
	//		This operation eliminates				|					|									|
	//		the 4  bits sub LSBs 			* 16 = shift 4 bits			|									|
	//																*4096 = shift 12						|
	//																									*1048576 = shift 20
	//																								B00001111 = take the LSB 4 bits
	// Conversion to voltage
	value = value / 16777216 * 3;
	//					|		|
	//					|		3 = Voltage reference of the ADC
	//					|
	//	16777216 = 2 ^ 24 bits of the conversor

  // check bit 28 to see if negative or out of range.
  // return -2 if true, value otherwise.
  uint8_t val_aux = (val[0] & B00010000) >> 4;
  if (val_aux == 1)
  {
    #if DEBUG_XTR
    USB.print(F("(-) or out of range: "));
    USB.printFloat(value, 5);
    USB.println(F(" V"));
    #endif
    return -2000;
  }
  else 
  {
    return value;
  }
}

