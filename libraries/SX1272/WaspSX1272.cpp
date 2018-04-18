/*! \file WaspSX1272.cpp
 *  \brief Library for managing Semtech modules
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
 *  Version:		3.1
 *  Design:			David Gascón
 *  Implementation:	Covadonga Albiñana, Yuri Carmona
 */


#ifndef __WPROGRAM_H__
#include "WaspClasses.h"
#endif



#include "WaspSX1272.h"
#include "../Frame/WaspFrame.h"

WaspSX1272::WaspSX1272()
{
	// Initialize class variables
	_bandwidth = BW_125;
	_codingRate = CR_5;
	_spreadingFactor = SF_7;
	_channel = CH_12_900;
	_header = HEADER_ON;
	_CRC = CRC_OFF;
	_modem = FSK;
	_power = 15;
	_packetNumber = 0;
	_reception = CORRECT_PACKET;
	_retries = 0;
	_maxRetries = 3;
	packet_sent.retry = _retries;

	WaspRegister |= REG_SX;
};




/*
 Function: Sets the module ON.
 Returns: Nothing
*/
uint8_t WaspSX1272::ON()
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'ON'"));
	#endif

	// Powering the module
    PWR.powerSocket(SOCKET0, HIGH);

    // update SPI flag
	SPI.isSocket0 = true;

	//Configure the MISO, MOSI, CS, SPCR.
	SPI.begin();
	//Set Most significant bit first
	SPI.setBitOrder(MSBFIRST);
	//Divide the clock frequency
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	//Set data mode
	SPI.setDataMode(SPI_MODE0);

	// Set Maximum Over Current Protection
	state = setMaxCurrent(0x1B);

	if( state == 0 )
	{
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## Setting ON with maximum current supply ##"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{
		return 1;
	}

	// set LoRa mode
	state = setLORA();

	return state;
}

/*
 Function: Sets the module OFF.
 Returns: Nothing
*/
void WaspSX1272::OFF()
{
	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'OFF'"));
	#endif

	// disable SPI flag
	SPI.isSocket0 = false;
	// close SPI bus if it is posible
	SPI.close();

	// Powering the module
    PWR.powerSocket(SOCKET0, LOW);

    #if (SX1272_debug_mode > 1)
		PRINTLN_SX1272(F("## Setting OFF ##"));
		PRINTLN_SX1272();
	#endif
}

/*
 Function: Reads the indicated register.
 Returns: The content of the register
 Parameters:
   address: address register to read from
*/
byte WaspSX1272::readRegister(byte address)
{
    byte value = 0x00;

    // Select SX slave
    SPI.setSPISlave(SOCKET0_SELECT);

    // read from module
    delay(1);
    bitClear(address, 7);		// Bit 7 cleared to write in registers
    SPI.transfer(address);
    value = SPI.transfer(0x00);

	// Disable all SPI slaves
    SPI.setSPISlave(ALL_DESELECTED);

    #if (SX1272_debug_mode > 1)
        PRINT_SX1272(F("## Reading:  ##\t"));
		PRINT_SX1272(F("Register "));
		USB.printHex(address);
		USB.print(F(":  "));
		USB.printHex(value);
		USB.println();
	#endif

    return value;
}

/*
 Function: Writes on the indicated register.
 Returns: Nothing
 Parameters:
   address: address register to write in
   data : value to write in the register
*/
void WaspSX1272::writeRegister(byte address, byte data)
{
    // Select SX slave
    SPI.setSPISlave(SOCKET0_SELECT);

    // write to module
    delay(1);
    bitSet(address, 7);			// Bit 7 set to read from registers
    SPI.transfer(address);
    SPI.transfer(data);

    // Disable all SPI slaves
    SPI.setSPISlave(ALL_DESELECTED);

    #if (SX1272_debug_mode > 1)
        PRINT_SX1272(F("## Writing:  ##\t"));
		PRINT_SX1272(F("Register "));
		bitClear(address, 7);
		USB.printHex(address);
		USB.print(F(":  "));
		USB.printHex(data);
		USB.println();
	#endif

}

/*
 * Function: Clears the interruption flags
 *
 * LoRa Configuration registers are accessed through the SPI interface.
 * Registers are readable in all device mode including Sleep. However, they
 * should be written only in Sleep and Stand-by modes.
 *
 * Returns: Nothing
*/
void WaspSX1272::clearFlags()
{
    byte st0;

	// Save the previous status
	st0 = readRegister(REG_OP_MODE);

	if( _modem == LORA )
	{
		/// LoRa mode
		// Stdby mode to write in registers
		writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);
		// LoRa mode flags register
		writeRegister(REG_IRQ_FLAGS, 0xFF);
		// Getting back to previous status
		writeRegister(REG_OP_MODE, st0);

		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## LoRa flags cleared ##"));
		#endif
	}
	else
	{
		/// FSK mode
		// Stdby mode to write in registers
		writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);
		// FSK mode flags1 register
		writeRegister(REG_IRQ_FLAGS1, 0xFF);
		// FSK mode flags2 register
		writeRegister(REG_IRQ_FLAGS2, 0xFF);
		// Getting back to previous status
		writeRegister(REG_OP_MODE, st0);

		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## FSK flags cleared ##"));
		#endif
	}
}

/*
 Function: Sets the module in LoRa mode.
 Returns:  Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::setLORA()
{
    uint8_t state = 2;
    byte st0;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setLORA'"));
	#endif

	writeRegister(REG_OP_MODE, FSK_SLEEP_MODE);    // Sleep mode (mandatory to set LoRa mode)
	writeRegister(REG_OP_MODE, LORA_SLEEP_MODE);    // LoRa sleep mode
	writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);	// LoRa standby mode

	writeRegister(REG_MAX_PAYLOAD_LENGTH,MAX_LENGTH);

	// Set RegModemConfig1 to Default values
	writeRegister(REG_MODEM_CONFIG1, 0x08);
	// Set RegModemConfig2 to Default values
	writeRegister(REG_MODEM_CONFIG2, 0x74);

	//delay(100);

	st0 = readRegister(REG_OP_MODE);	// Reading config mode
	if( st0 == LORA_STANDBY_MODE )
	{ // LoRa mode
		_modem = LORA;
		state = 0;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## LoRa set with success ##"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{ // FSK mode
		_modem = FSK;
		state = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** There has been an error while setting LoRa **"));
			PRINTLN_SX1272();
		#endif
	}
	return state;
}

/*
 Function: Sets the module in FSK mode.
 Returns:   Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::setFSK()
{
	uint8_t state = 2;
    byte st0;
    byte config1;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setFSK'"));
	#endif

	writeRegister(REG_OP_MODE, FSK_SLEEP_MODE);	// Sleep mode (mandatory to change mode)
	writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);	// FSK standby mode
	config1 = readRegister(REG_PACKET_CONFIG1);
	config1 = config1 & B01111101;		// clears bits 8 and 1 from REG_PACKET_CONFIG1
	config1 = config1 | B00000100;		// sets bit 2 from REG_PACKET_CONFIG1
	writeRegister(REG_PACKET_CONFIG1,config1);	// AddressFiltering = NodeAddress + BroadcastAddress
	writeRegister(REG_FIFO_THRESH, 0x80);	// condition to start packet tx
	config1 = readRegister(REG_SYNC_CONFIG);
	config1 = config1 & B00111111;
	writeRegister(REG_SYNC_CONFIG,config1);

	//delay(100);

	st0 = readRegister(REG_OP_MODE);	// Reading config mode
	if( st0 == FSK_STANDBY_MODE )
	{ // FSK mode
		_modem = FSK;
		state = 0;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## FSK set with success ##"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{ // LoRa mode
		_modem = LORA;
		state = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** There has been an error while setting FSK **"));
			PRINTLN_SX1272();
		#endif
	}
	return state;
}

/*
 Function: Gets the bandwidth, coding rate and spreading factor of the LoRa modulation.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getMode()
{
	byte st0;
	int8_t state = 2;
	byte value = 0x00;

	#if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'getMode'"));
	#endif

	// Save the previous status
	st0 = readRegister(REG_OP_MODE);
	// Setting LoRa mode
	if( _modem == FSK )
	{
		setLORA();
	}
	value = readRegister(REG_MODEM_CONFIG1);
	_bandwidth = (value >> 6);   				// Storing 2 MSB from REG_MODEM_CONFIG1 (=_bandwidth)
	_codingRate = (value >> 3) & 0x07;  		// Storing third, forth and fifth bits from
	value = readRegister(REG_MODEM_CONFIG2);	// REG_MODEM_CONFIG1 (=_codingRate)
	_spreadingFactor = (value >> 4) & 0x0F; 	// Storing 4 MSB from REG_MODEM_CONFIG2 (=_spreadingFactor)
	state = 1;

	if( isBW(_bandwidth) )		// Checking available values for:
	{								//		_bandwidth
		if( isCR(_codingRate) )		//		_codingRate
		{							//		_spreadingFactor
			if( isSF(_spreadingFactor) )
			{
				state = 0;
			}
		}
	}

	#if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272(F("## Parameters from configuration mode are:"));
	  PRINT_SX1272(F("Bandwidth: "));
	  USB.printHex(_bandwidth);
	  USB.println();
	  PRINTLN_SX1272(F("\t Coding Rate: "));
	  USB.printHex(_codingRate);
	  USB.println();
	  PRINTLN_SX1272(F("\t Spreading Factor: "));
	  USB.printHex(_spreadingFactor);
	  USB.println(F(" ##"));
	  PRINTLN_SX1272();
	#endif

	writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
	return state;
}

/*
 Function: Sets the bandwidth, coding rate and spreading factor of the LoRa modulation.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
 Parameters:
   mode: mode number to set the required BW, SF and CR of LoRa modem.
*/
int8_t WaspSX1272::setMode(uint8_t mode)
{
	int8_t state = 2;
	byte st0;
	byte config1 = 0x00;
	byte config2 = 0x00;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setMode'"));
	#endif

	st0 = readRegister(REG_OP_MODE);		// Save the previous status

	// 'setMode' function only can be called in LoRa mode
	if( _modem == FSK )
	{
		setLORA();
	}

	// LoRa standby mode
	writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);

	switch (mode)
	{
		// mode 1 (better reach, medium time on air)
		case 1: 	setCR(CR_5);		// CR = 4/5
					setSF(SF_12);		// SF = 12
					setBW(BW_125);		// BW = 125 KHz
					break;

		// mode 2 (medium reach, less time on air)
		case 2: 	setCR(CR_5);		// CR = 4/5
					setSF(SF_12);		// SF = 12
					setBW(BW_250);		// BW = 250 KHz
					break;

		// mode 3 (worst reach, less time on air)
		case 3: 	setCR(CR_5);		// CR = 4/5
					setSF(SF_10);		// SF = 10
					setBW(BW_125);		// BW = 125 KHz
					break;

		// mode 4 (better reach, low time on air)
		case 4: 	setCR(CR_5);		// CR = 4/5
					setSF(SF_12);		// SF = 12
					setBW(BW_500);		// BW = 500 KHz
					break;

		// mode 5 (better reach, medium time on air)
		case 5: 	setCR(CR_5);		// CR = 4/5
					setSF(SF_10);		// SF = 10
					setBW(BW_250);		// BW = 250 KHz
					break;

		// mode 6 (better reach, worst time-on-air)
		case 6: 	setCR(CR_5);		// CR = 4/5
					setSF(SF_11);		// SF = 11
					setBW(BW_500);		// BW = 500 KHz
					break;

		// mode 7 (medium-high reach, medium-low time-on-air)
		case 7: 	setCR(CR_5);		// CR = 4/5
					setSF(SF_9);		// SF = 9
					setBW(BW_250);		// BW = 250 KHz
					break;

		// mode 8 (medium reach, medium time-on-air)
		case 8:		setCR(CR_5);		// CR = 4/5
					setSF(SF_9);		// SF = 9
					setBW(BW_500);		// BW = 500 KHz
					break;

		// mode 9 (medium-low reach, medium-high time-on-air)
		case 9: 	setCR(CR_5);		// CR = 4/5
					setSF(SF_8);		// SF = 8
					setBW(BW_500);		// BW = 500 KHz
					break;

		// mode 10 (worst reach, less time_on_air)
		case 10:	setCR(CR_5);		// CR = 4/5
					setSF(SF_7);		// SF = 7
					setBW(BW_500);		// BW = 500 KHz
					break;

		default:	state = -1; // The indicated mode doesn't exist

	};


	// Check proper register configuration
	if( state == -1 )	// if state = -1, don't change its value
	{
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** The indicated mode doesn't exist, "));
			PRINTLN_SX1272(F("please select from 1 to 10 **"));
		#endif
	}
	else
	{
		state = 1;
		config1 = readRegister(REG_MODEM_CONFIG1);
		switch (mode)
		{	//		Different way to check for each mode:
			// (config1 >> 3) ---> take out bits 7-3 from REG_MODEM_CONFIG1 (=_bandwidth & _codingRate together)
			// (config2 >> 4) ---> take out bits 7-4 from REG_MODEM_CONFIG2 (=_spreadingFactor)

			// mode 1: BW = 125 KHz, CR = 4/5, SF = 12.
			case 1:  if( (config1 >> 3) == 0x01 )
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_12 )
							{
							state = 0;
							}
						}
 					 break;


			// mode 2: BW = 250 KHz, CR = 4/5, SF = 12.
			case 2:  if( (config1 >> 3) == 0x09 )
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_12 )
							{
							state = 0;
							}
						}
 					 break;

			// mode 3: BW = 125 KHz, CR = 4/5, SF = 10.
			case 3:  if( (config1 >> 3) == 0x01 )
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_10 )
							{
							state = 0;
							}
						}
 					 break;

			// mode 4: BW = 500 KHz, CR = 4/5, SF = 12.
			case 4:  if( (config1 >> 3) == 0x11 )
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_12 )
							{
							state = 0;
							}
						}
 					 break;

			// mode 5: BW = 250 KHz, CR = 4/5, SF = 10.
			case 5:  if( (config1 >> 3) == 0x09 )
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_10 )
							{
							state = 0;
							}
						}
 					 break;

			// mode 6: BW = 500 KHz, CR = 4/5, SF = 11.
			case 6:  if( (config1 >> 3) == 0x11 )
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_11 )
							{
							state = 0;
							}
						}
 					 break;

			// mode 7: BW = 250 KHz, CR = 4/5, SF = 9.
			case 7:  if( (config1 >> 3) == 0x09 )
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_9 )
							{
							state = 0;
							}
						}
 					 break;

			// mode 8: BW = 500 KHz, CR = 4/5, SF = 9.
			case 8:  if ((config1 >> 3) == 0x11)
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_9 )
							{
							state = 0;
							}
						}
 					 break;

			// mode 9: BW = 500 KHz, CR = 4/5, SF = 8.
			case 9:  if( (config1 >> 3) == 0x11 )
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_8 )
							{
							state = 0;
							}
						}
 					 break;

			// mode 10: BW = 500 KHz, CR = 4/5, SF = 7.
			case 10: if( (config1 >> 3) == 0x11 )
						{  config2 = readRegister(REG_MODEM_CONFIG2);
						if( (config2 >> 4) == SF_7 )
							{
							state = 0;
							}
						}
		}// end switch
	}

	#if (SX1272_debug_mode > 1)
	if( state == 0 )
	{
		PRINT_SX1272(F("## Mode "));
		USB.print(mode, DEC);
		USB.println(F(" configured with success ##"));
	}
	else
	{
		PRINT_SX1272(F("** There has been an error while configuring mode "));
		USB.print(mode, DEC);
		USB.println(F(". **"));
	}
	#endif

	// Getting back to previous status
	writeRegister(REG_OP_MODE, st0);

	return state;
}

/*
 Function: Indicates if module is configured in implicit or explicit header mode.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t	WaspSX1272::getHeader()
{
	int8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getHeader'"));
	#endif

	// take out bit 2 from REG_MODEM_CONFIG1 indicates ImplicitHeaderModeOn
	if( bitRead(readRegister(REG_MODEM_CONFIG1), 2) == 0 )
	{ // explicit header mode (ON)
		_header = HEADER_ON;
		state = 1;
	}
	else
	{ // implicit header mode (OFF)
		_header = HEADER_OFF;
		state = 1;
	}

	state = 0;

	if( _modem == FSK )
	{ // header is not available in FSK mode
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## Notice that FSK mode packets hasn't header ##"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{ // header in LoRa mode
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("## Header is "));
			if( _header == HEADER_ON )
			{
				USB.println(F("in explicit header mode ##"));
			}
			else
			{
				USB.println(F("in implicit header mode ##"));
			}
			USB.println();
		#endif
	}
	return state;
}

/*
 Function: Sets the module in explicit header mode (header is sent).
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
*/
int8_t	WaspSX1272::setHeaderON()
{
  int8_t state = 2;
  byte config1;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'setHeaderON'"));
  #endif

  if( _modem == FSK )
  {
	  state = -1;		// header is not available in FSK mode
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("## FSK mode packets hasn't header ##"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  {
	config1 = readRegister(REG_MODEM_CONFIG1);	// Save config1 to modify only the header bit
	if( _spreadingFactor == 6 )
	{
		state = -1;		// Mandatory headerOFF with SF = 6
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## Mandatory implicit header mode with spreading factor = 6 ##"));
		#endif
	}
	else
	{
		config1 = config1 & B11111011;			// clears bit 2 from config1 = headerON
		writeRegister(REG_MODEM_CONFIG1,config1);	// Update config1
	}
	if( _spreadingFactor != 6 )
	{ // checking headerON taking out bit 2 from REG_MODEM_CONFIG1
		config1 = readRegister(REG_MODEM_CONFIG1);
		if( bitRead(config1, 2) == HEADER_ON )
		{
			state = 0;
			_header = HEADER_ON;
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("## Header has been activated ##"));
				PRINTLN_SX1272();
			#endif
		}
		else
		{
			state = 1;
		}
	}
  }
  return state;
}

/*
 Function: Sets the module in implicit header mode (header is not sent).
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
*/
int8_t	WaspSX1272::setHeaderOFF()
{
	uint8_t state = 2;
	byte config1;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setHeaderOFF'"));
	#endif

	if( _modem == FSK )
	{
		// header is not available in FSK mode
		state = -1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## Notice that FSK mode packets hasn't header ##"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{
		// Read config1 to modify only the header bit
		config1 = readRegister(REG_MODEM_CONFIG1);

		// sets bit 2 from REG_MODEM_CONFIG1 = headerOFF
		config1 = config1 | B00000100;
		// Update config1
		writeRegister(REG_MODEM_CONFIG1,config1);

		// check register
		config1 = readRegister(REG_MODEM_CONFIG1);
		if( bitRead(config1, 2) == HEADER_OFF )
		{
			// checking headerOFF taking out bit 2 from REG_MODEM_CONFIG1
			state = 0;
			_header = HEADER_OFF;

			#if (SX1272_debug_mode > 1)
			    PRINTLN_SX1272(F("## Header has been desactivated ##"));
			    PRINTLN_SX1272();
			#endif
		}
		else
		{
			state = 1;
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("** Header hasn't been desactivated ##"));
				PRINTLN_SX1272();
			#endif
		}
	}
	return state;
}

/*
 Function: Indicates if module is configured with or without checking CRC.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t	WaspSX1272::getCRC()
{
	int8_t state = 2;
	byte value;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getCRC'"));
	#endif

	if( _modem == LORA )
	{ // LoRa mode

		// take out bit 1 from REG_MODEM_CONFIG1 indicates RxPayloadCrcOn
		value = readRegister(REG_MODEM_CONFIG1);
		if( bitRead(value, 1) == CRC_OFF )
		{ // CRCoff
			_CRC = CRC_OFF;
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("## CRC is desactivated ##"));
				PRINTLN_SX1272();
			#endif
			state = 0;
		}
		else
		{ // CRCon
			_CRC = CRC_ON;
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("## CRC is activated ##"));
				PRINTLN_SX1272();
			#endif
			state = 0;
		}
	}
	else
	{ // FSK mode

		// take out bit 2 from REG_PACKET_CONFIG1 indicates CrcOn
		value = readRegister(REG_PACKET_CONFIG1);
		if( bitRead(value, 4) == CRC_OFF )
		{ // CRCoff
			_CRC = CRC_OFF;
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("## CRC is desactivated ##"));
				PRINTLN_SX1272();
			#endif
			state = 0;
		}
		else
		{ // CRCon
			_CRC = CRC_ON;
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("## CRC is activated ##"));
				PRINTLN_SX1272();
			#endif
			state = 0;
		}
	}
	if( state != 0 )
	{
		state = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** There has been an error while getting configured CRC **"));
			PRINTLN_SX1272();
		#endif
	}
	return state;
}

/*
 Function: Sets the module with CRC on.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t	WaspSX1272::setCRC_ON()
{
  uint8_t state = 2;
  byte config1;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'setCRC_ON'"));
  #endif

  if( _modem == LORA )
  { // LORA mode
	config1 = readRegister(REG_MODEM_CONFIG1);	// Save config1 to modify only the CRC bit
	config1 = config1 | B00000010;				// sets bit 1 from REG_MODEM_CONFIG1 = CRC_ON
	writeRegister(REG_MODEM_CONFIG1,config1);

	state = 1;

	config1 = readRegister(REG_MODEM_CONFIG1);
	if( bitRead(config1, 1) == CRC_ON )
	{ // take out bit 1 from REG_MODEM_CONFIG1 indicates RxPayloadCrcOn
		state = 0;
		_CRC = CRC_ON;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## CRC has been activated ##"));
			PRINTLN_SX1272();
		#endif
	}
  }
  else
  { // FSK mode
	config1 = readRegister(REG_PACKET_CONFIG1);	// Save config1 to modify only the CRC bit
	config1 = config1 | B00010000;				// set bit 4 and 3 from REG_MODEM_CONFIG1 = CRC_ON
	writeRegister(REG_PACKET_CONFIG1,config1);

	state = 1;

	config1 = readRegister(REG_PACKET_CONFIG1);
	if( bitRead(config1, 4) == CRC_ON )
	{ // take out bit 4 from REG_PACKET_CONFIG1 indicates CrcOn
		state = 0;
		_CRC = CRC_ON;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## CRC has been activated ##"));
			PRINTLN_SX1272();
		#endif
	}
  }
  if( state != 0 )
  {
	  state = 1;
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("** There has been an error while setting CRC ON **"));
		  PRINTLN_SX1272();
	  #endif
  }
  return state;
}

/*
 Function: Sets the module with CRC off.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t	WaspSX1272::setCRC_OFF()
{
  int8_t state = 2;
  byte config1;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'setCRC_OFF'"));
  #endif

  if( _modem == LORA )
  { // LORA mode
  	config1 = readRegister(REG_MODEM_CONFIG1);	// Save config1 to modify only the CRC bit
	config1 = config1 & B11111101;				// clears bit 1 from config1 = CRC_OFF
	writeRegister(REG_MODEM_CONFIG1,config1);

	config1 = readRegister(REG_MODEM_CONFIG1);
	if( (bitRead(config1, 1)) == CRC_OFF )
	{ // take out bit 1 from REG_MODEM_CONFIG1 indicates RxPayloadCrcOn
	  state = 0;
	  _CRC = CRC_OFF;
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("## CRC has been desactivated ##"));
		  PRINTLN_SX1272();
	  #endif
	}
  }
  else
  { // FSK mode
	config1 = readRegister(REG_PACKET_CONFIG1);	// Save config1 to modify only the CRC bit
	config1 = config1 & B11101111;				// clears bit 4 from config1 = CRC_OFF
	writeRegister(REG_PACKET_CONFIG1,config1);

	config1 = readRegister(REG_PACKET_CONFIG1);
	if( bitRead(config1, 4) == CRC_OFF )
	{ // take out bit 4 from REG_PACKET_CONFIG1 indicates RxPayloadCrcOn
		state = 0;
		_CRC = CRC_OFF;
		#if (SX1272_debug_mode > 1)
		    PRINTLN_SX1272(F("## CRC has been desactivated ##"));
		    PRINTLN_SX1272();
	    #endif
	}
  }
  if( state != 0 )
  {
	  state = 1;
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("** There has been an error while setting CRC OFF **"));
		  PRINTLN_SX1272();
	  #endif
  }
  return state;
}

/*
 Function: Checks if SF is a valid value.
 Returns: Boolean that's 'true' if the SF value exists and
		  it's 'false' if the SF value does not exist.
 Parameters:
   spr: spreading factor value to check.
*/
boolean	WaspSX1272::isSF(uint8_t spr)
{
  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'isSF'"));
  #endif

  // Checking available values for _spreadingFactor
  switch(spr)
  {
	  case SF_6:
	  case SF_7:
	  case SF_8:
	  case SF_9:
	  case SF_10:
	  case SF_11:
	  case SF_12:	return true;
					break;

	  default:		return false;
  }
  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272(F("## Finished 'isSF' ##"));
	  PRINTLN_SX1272();
  #endif
}

/*
 Function: Gets the SF within the module is configured.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
*/
int8_t	WaspSX1272::getSF()
{
  int8_t state = 2;
  byte config2;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'getSF'"));
  #endif

  if( _modem == FSK )
  {
	  state = -1;		// SF is not available in FSK mode
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("** FSK mode hasn't spreading factor **"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  {
	// take out bits 7-4 from REG_MODEM_CONFIG2 indicates _spreadingFactor
	config2 = (readRegister(REG_MODEM_CONFIG2)) >> 4;
	_spreadingFactor = config2;
	state = 1;

	if( (config2 == _spreadingFactor) && isSF(_spreadingFactor) )
	{
		state = 0;
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("## Spreading factor is "));
			USB.printHex(_spreadingFactor);
			USB.println(F(" ##"));
			PRINTLN_SX1272();
		#endif
	}
  }
  return state;
}

/*
 Function: Sets the indicated SF in the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
 Parameters:
   spr: spreading factor value to set in LoRa modem configuration.
*/
uint8_t	WaspSX1272::setSF(uint8_t spr)
{
	byte st0;
	int8_t state = 2;
	byte config1;
	byte config2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setSF'"));
	#endif

	st0 = readRegister(REG_OP_MODE);	// Save the previous status

	if( _modem == FSK )
	{
		/// FSK mode
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("## Notice that FSK hasn't Spreading Factor parameter, "));
			USB.println(F("so you are configuring it in LoRa mode ##"));
		#endif
		state = setLORA();				// Setting LoRa mode
	}
	else
	{
		/// LoRa mode
		// LoRa standby mode
		writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);

		// Read config1 to modify only the LowDataRateOptimize
		config1 = (readRegister(REG_MODEM_CONFIG1));
		// Read config2 to modify SF value (bits 7-4)
		config2 = (readRegister(REG_MODEM_CONFIG2));

		switch(spr)
		{
			case SF_6:
					config2 = config2 & B01101111;	// clears bits 7 & 4 from REG_MODEM_CONFIG2
					config2 = config2 | B01100000;	// sets bits 6 & 5 from REG_MODEM_CONFIG2
					break;
			case SF_7:
					config2 = config2 & B01111111;	// clears bits 7 from REG_MODEM_CONFIG2
					config2 = config2 | B01110000;	// sets bits 6, 5 & 4
					break;

			case SF_8:
					config2 = config2 & B10001111;	// clears bits 6, 5 & 4 from REG_MODEM_CONFIG2
					config2 = config2 | B10000000;	// sets bit 7 from REG_MODEM_CONFIG2
					break;

			case SF_9:
					config2 = config2 & B10011111;	// clears bits 6, 5 & 4 from REG_MODEM_CONFIG2
					config2 = config2 | B10010000;	// sets bits 7 & 4 from REG_MODEM_CONFIG2
					break;

			case SF_10:	config2 = config2 & B10101111;	// clears bits 6 & 4 from REG_MODEM_CONFIG2
					config2 = config2 | B10100000;	// sets bits 7 & 5 from REG_MODEM_CONFIG2
					break;

			case SF_11:
					config2 = config2 & B10111111;	// clears bit 6 from REG_MODEM_CONFIG2
					config2 = config2 | B10110000;	// sets bits 7, 5 & 4 from REG_MODEM_CONFIG2
					getBW();
					//if( _bandwidth == BW_125 )
					{ // LowDataRateOptimize (Mandatory with SF_11 if BW_125)
						config1 = config1 | B00000001;
					}
					break;

			case SF_12:
					config2 = config2 & B11001111;	// clears bits 5 & 4 from REG_MODEM_CONFIG2
					config2 = config2 | B11000000;	// sets bits 7 & 6 from REG_MODEM_CONFIG2
					//if( _bandwidth == BW_125 )
					{ // LowDataRateOptimize (Mandatory with SF_12 if BW_125)
						config1 = config1 | B00000001;
					}
					break;
	}

	// Check if it is neccesary to set special settings for SF=6
	if( spr == SF_6 )
	{
		// Mandatory headerOFF with SF = 6 (Implicit mode)
		setHeaderOFF();

		// Set the bit field DetectionOptimize of
		// register RegLoRaDetectOptimize to value "0b101".
		writeRegister(REG_DETECT_OPTIMIZE, 0x05);

		// Write 0x0C in the register RegDetectionThreshold.
		writeRegister(REG_DETECTION_THRESHOLD, 0x0C);
	}
	else
	{
		// LoRa detection Optimize: 0x03 --> SF7 to SF12
		writeRegister(REG_DETECT_OPTIMIZE, 0x03);

		// LoRa detection threshold: 0x0A --> SF7 to SF12
		writeRegister(REG_DETECTION_THRESHOLD, 0x0A);
	}

	// sets bit 2-0 (AgcAutoOn and SymbTimout) for any SF value
	config2 = config2 | B00000111;

	// Update 'config1' and 'config2'
	writeRegister(REG_MODEM_CONFIG1, config1);
	writeRegister(REG_MODEM_CONFIG2, config2);

	// Read 'config1' and 'config2' to check update
	config1 = (readRegister(REG_MODEM_CONFIG1));
	config2 = (readRegister(REG_MODEM_CONFIG2));

	// (config2 >> 4) ---> take out bits 7-4 from REG_MODEM_CONFIG2 (=_spreadingFactor)
	// bitRead(config1, 0) ---> take out bits 1 from config1 (=LowDataRateOptimize)
	switch(spr)
	{
		case SF_6:	if(		((config2 >> 4) == spr)
						&& 	(bitRead(config2, 2) == 1)
						&& 	(_header == HEADER_OFF))
					{
						state = 0;
					}
					break;
		case SF_7:	if(		((config2 >> 4) == 0x07)
						 && (bitRead(config2, 2) == 1))
					{
						state = 0;
					}
					break;
		case SF_8:	if(		((config2 >> 4) == 0x08)
						 && (bitRead(config2, 2) == 1))
					{
						state = 0;
					}
					break;
		case SF_9:	if(		((config2 >> 4) == 0x09)
						 && (bitRead(config2, 2) == 1))
					{
						state = 0;
					}
					break;
		case SF_10:	if(		((config2 >> 4) == 0x0A)
						 && (bitRead(config2, 2) == 1))
					{
						state = 0;
					}
					break;
		case SF_11:	if(		((config2 >> 4) == 0x0B)
						 && (bitRead(config2, 2) == 1)
						 && (bitRead(config1, 0) == 1))
					{
						state = 0;
					}
					break;
		case SF_12:	if(		((config2 >> 4) == 0x0C)
						 && (bitRead(config2, 2) == 1)
						 && (bitRead(config1, 0) == 1))
					{
						state = 0;
					}
					break;
		default:	state = 1;
	}
  }

  writeRegister(REG_OP_MODE, st0);	// Getting back to previous status

  if( isSF(spr) )
  { // Checking available value for _spreadingFactor
		state = 0;
		_spreadingFactor = spr;
		#if (SX1272_debug_mode > 1)
		    PRINT_SX1272(F("## Spreading factor "));
		    USB.print(_spreadingFactor, DEC);
		    USB.println(F(" has been successfully set ##"));
		    PRINTLN_SX1272();
		#endif
  }
  else
  {
	  if( state != 0 )
	  {
		  #if (SX1272_debug_mode > 1)
		      PRINTLN_SX1272(F("** There has been an error while setting the spreading factor **"));
		      USB.println();
		  #endif
	  }
  }
  return state;
}

/*
 Function: Checks if BW is a valid value.
 Returns: Boolean that's 'true' if the BW value exists and
		  it's 'false' if the BW value does not exist.
 Parameters:
   band: bandwidth value to check.
*/
boolean	WaspSX1272::isBW(uint16_t band)
{
  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'isBW'"));
  #endif

  // Checking available values for _bandwidth
  switch(band)
  {
	  case BW_125:
	  case BW_250:
	  case BW_500:	return true;
					break;

	  default:		return false;
  }
  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272(F("## Finished 'isBW' ##"));
	  PRINTLN_SX1272();
  #endif
}

/*
 Function: Gets the BW within the module is configured.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
*/
int8_t	WaspSX1272::getBW()
{
  uint8_t state = 2;
  byte config1;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'getBW'"));
  #endif

  if( _modem == FSK )
  {
	  state = -1;		// BW is not available in FSK mode
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("** FSK mode hasn't bandwidth **"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  {
	  // take out bits 7-6 from REG_MODEM_CONFIG1 indicates _bandwidth
	  config1 = (readRegister(REG_MODEM_CONFIG1)) >> 6;
	  _bandwidth = config1;

	  if( (config1 == _bandwidth) && isBW(_bandwidth) )
	  {
		  state = 0;
		  #if (SX1272_debug_mode > 1)
			  PRINT_SX1272(F("## Bandwidth is "));
			  USB.printHex(_bandwidth);
			  USB.println(F(" ##"));
			  PRINTLN_SX1272();
		  #endif
	  }
	  else
	  {
		  state = 1;
		  #if (SX1272_debug_mode > 1)
			  PRINT_SX1272(F("** There has been an error while getting bandwidth **"));
			  USB.println();
		  #endif
	  }
  }
  return state;
}

/*
 Function: Sets the indicated BW in the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
 Parameters:
   band: bandwith value to set in LoRa modem configuration.
*/
int8_t	WaspSX1272::setBW(uint16_t band)
{
  byte st0;
  int8_t state = 2;
  byte config1;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'setBW'"));
  #endif

  st0 = readRegister(REG_OP_MODE);	// Save the previous status

  if( _modem == FSK )
  {
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("## Notice that FSK hasn't Bandwidth parameter, "));
		  USB.println(F("so you are configuring it in LoRa mode ##"));
	  #endif
	  state = setLORA();
  }
  writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);	// LoRa standby mode
  config1 = (readRegister(REG_MODEM_CONFIG1));	// Save config1 to modify only the BW
  switch(band)
  {
	  case BW_125:  config1 = config1 & B00111111;	// clears bits 7 & 6 from REG_MODEM_CONFIG1
					getSF();
					if( _spreadingFactor == 11 )
					{ // LowDataRateOptimize (Mandatory with BW_125 if SF_11)
						config1 = config1 | B00000001;
					}
					if( _spreadingFactor == 12 )
					{ // LowDataRateOptimize (Mandatory with BW_125 if SF_12)
						config1 = config1 | B00000001;
					}
					break;
	  case BW_250:  config1 = config1 & B01111111;	// clears bit 7 from REG_MODEM_CONFIG1
					config1 = config1 | B01000000;	// sets bit 6 from REG_MODEM_CONFIG1
					break;
	  case BW_500:  config1 = config1 & B10111111;	//clears bit 6 from REG_MODEM_CONFIG1
					config1 = config1 | B10000000;	//sets bit 7 from REG_MODEM_CONFIG1
					break;
  }
  writeRegister(REG_MODEM_CONFIG1,config1);		// Update config1

  config1 = (readRegister(REG_MODEM_CONFIG1));
  // (config1 >> 6) ---> take out bits 7-6 from REG_MODEM_CONFIG1 (=_bandwidth)
  switch(band)
  {
	   case BW_125: if( (config1 >> 6) == BW_125 )
					{
						state = 0;
						if( _spreadingFactor == 11 )
						{
							if( bitRead(config1, 0) == 1 )
							{ // LowDataRateOptimize
								state = 0;
							}
							else
							{
								state = 1;
							}
						}
						if( _spreadingFactor == 12 )
						{
							if( bitRead(config1, 0) == 1 )
							{ // LowDataRateOptimize
								state = 0;
							}
							else
							{
								state = 1;
							}
						}
					}
					break;
	   case BW_250: if( (config1 >> 6) == BW_250 )
					{
						state = 0;
					}
					break;
	   case BW_500: if( (config1 >> 6) == BW_500 )
					{
						state = 0;
					}
					break;
  }

  if( not isBW(band) )
  {
	  state = 1;
	  #if (SX1272_debug_mode > 1)
		  PRINT_SX1272(F("** Bandwidth "));
		  USB.printHex(band);
		  USB.println(F(" is not a correct value **"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  {
	  _bandwidth = band;
	  #if (SX1272_debug_mode > 1)
		  PRINT_SX1272(F("## Bandwidth "));
		  USB.printHex(band);
		  USB.println(F(" has been successfully set ##"));
		  PRINTLN_SX1272();
	  #endif
  }
  writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
  return state;
}

/*
 Function: Checks if CR is a valid value.
 Returns: Boolean that's 'true' if the CR value exists and
		  it's 'false' if the CR value does not exist.
 Parameters:
   cod: coding rate value to check.
*/
boolean	WaspSX1272::isCR(uint8_t cod)
{
  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'isCR'"));
  #endif

  // Checking available values for _codingRate
  switch(cod)
  {
	  case CR_5:
	  case CR_6:
	  case CR_7:
	  case CR_8:	return true;
					break;

	  default:		return false;
  }
  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272(F("## Finished 'isCR' ##"));
	  PRINTLN_SX1272();
  #endif
}

/*
 Function: Indicates the CR within the module is configured.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
*/
int8_t	WaspSX1272::getCR()
{
  int8_t state = 2;
  byte config1;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'getCR'"));
  #endif

  if( _modem == FSK )
  {
	  state = -1;		// CR is not available in FSK mode
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("** FSK mode hasn't coding rate **"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  {
	// take out bits 7-3 from REG_MODEM_CONFIG1 indicates _bandwidth & _codingRate
	config1 = (readRegister(REG_MODEM_CONFIG1)) >> 3;
	config1 = config1 & B00000111;	// clears bits 7-5 ---> clears _bandwidth
	_codingRate = config1;
	state = 1;

	if( (config1 == _codingRate) && isCR(_codingRate) )
	{
		state = 0;
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("## Coding rate is "));
			USB.printHex(_codingRate);
			USB.println(F(" ##"));
			PRINTLN_SX1272();
		#endif
	}
  }
  return state;
}

/*
 Function: Sets the indicated CR in the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
 Parameters:
   cod: coding rate value to set in LoRa modem configuration.
*/
int8_t	WaspSX1272::setCR(uint8_t cod)
{
  byte st0;
  int8_t state = 2;
  byte config1;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'setCR'"));
  #endif

  st0 = readRegister(REG_OP_MODE);		// Save the previous status

  if( _modem == FSK )
  {
	  #if (SX1272_debug_mode > 1)
		  PRINT_SX1272(F("## Notice that FSK hasn't Coding Rate parameter, "));
		  USB.println(F("so you are configuring it in LoRa mode ##"));
	  #endif
	  state = setLORA();
  }
  else
  {
	  writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);		// Set Standby mode to write in registers

	  config1 = readRegister(REG_MODEM_CONFIG1);	// Save config1 to modify only the CR
	  switch(cod)
	  {
		 case CR_5: config1 = config1 & B11001111;	// clears bits 5 & 4 from REG_MODEM_CONFIG1
					config1 = config1 | B00001000;	// sets bit 3 from REG_MODEM_CONFIG1
					break;
		 case CR_6: config1 = config1 & B11010111;	// clears bits 5 & 3 from REG_MODEM_CONFIG1
					config1 = config1 | B00010000;	// sets bit 4 from REG_MODEM_CONFIG1
					break;
		 case CR_7: config1 = config1 & B11011111;	// clears bit 5 from REG_MODEM_CONFIG1
					config1 = config1 | B00011000;	// sets bits 4 & 3 from REG_MODEM_CONFIG1
					break;
		 case CR_8: config1 = config1 & B11100111;	// clears bits 4 & 3 from REG_MODEM_CONFIG1
					config1 = config1 | B00100000;	// sets bit 5 from REG_MODEM_CONFIG1
					break;
	  }
	  writeRegister(REG_MODEM_CONFIG1, config1);		// Update config1

	  config1 = readRegister(REG_MODEM_CONFIG1);
	  // ((config1 >> 3) & B0000111) ---> take out bits 5-3 from REG_MODEM_CONFIG1 (=_codingRate)
	  switch(cod)
	  {
		 case CR_5: if( ((config1 >> 3) & B0000111) == 0x01 )
					{
						state = 0;
					}
					break;
		 case CR_6: if( ((config1 >> 3) & B0000111) == 0x02 )
					{
						state = 0;
					}
					break;
		 case CR_7: if( ((config1 >> 3) & B0000111) == 0x03 )
					{
						state = 0;
					}
					break;
		 case CR_8: if( ((config1 >> 3) & B0000111) == 0x04 )
					{
						state = 0;
					}
					break;
	  }
  }

  if( isCR(cod) )
  {
	  _codingRate = cod;
	  #if (SX1272_debug_mode > 1)
		  PRINT_SX1272(F("## Coding Rate "));
		  USB.printHex(cod);
		  USB.println(F(" has been successfully set ##"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  {
	  state = 1;
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("** There has been an error while configuring Coding Rate parameter **"));
		  PRINTLN_SX1272();
	  #endif
  }
  writeRegister(REG_OP_MODE,st0);	// Getting back to previous status
  return state;
}

/*
 Function: Checks if channel is a valid value.
 Returns: Boolean that's 'true' if the CR value exists and
		  it's 'false' if the CR value does not exist.
 Parameters:
   ch: frequency channel value to check.
*/
boolean	WaspSX1272::isChannel(uint32_t ch)
{
  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'isChannel'"));
  #endif

  // Checking available values for _channel
  switch(ch)
  {
	  case CH_10_868:
	  case CH_11_868:
	  case CH_12_868:
	  case CH_13_868:
	  case CH_14_868:
	  case CH_15_868:
	  case CH_16_868:
	  case CH_17_868:
	  case CH_00_900:
	  case CH_01_900:
	  case CH_02_900:
	  case CH_03_900:
	  case CH_04_900:
	  case CH_05_900:
	  case CH_06_900:
	  case CH_07_900:
	  case CH_08_900:
	  case CH_09_900:
	  case CH_10_900:
	  case CH_11_900:
	  case CH_12_900:	return true;
						break;

	  default:			return false;
  }
  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272(F("## Finished 'isChannel' ##"));
	  PRINTLN_SX1272();
  #endif
}

/*
 Function: Indicates the frequency channel within the module is configured.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getChannel()
{
  uint8_t state = 2;
  uint32_t ch;
  uint8_t freq3;
  uint8_t freq2;
  uint8_t freq1;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'getChannel'"));
  #endif

  freq3 = readRegister(REG_FRF_MSB);	// frequency channel MSB
  freq2 = readRegister(REG_FRF_MID);	// frequency channel MID
  freq1 = readRegister(REG_FRF_LSB);	// frequency channel LSB
  ch = ((uint32_t)freq3 << 16) + ((uint32_t)freq2 << 8) + (uint32_t)freq1;
  _channel = ch;						// frequency channel

  if( (_channel == ch) && isChannel(_channel) )
  {
	  state = 0;
	  #if (SX1272_debug_mode > 1)
		  PRINT_SX1272(F("## Frequency channel is "));
		  USB.printHex(_channel);
		  USB.println(F(" ##"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  {
	  state = 1;
  }
  return state;
}

/*
 Function: Sets the indicated channel in the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
 Parameters:
   ch: frequency channel value to set in configuration.
*/
int8_t WaspSX1272::setChannel(uint32_t ch)
{
  byte st0;
  int8_t state = 2;
  unsigned int freq3;
  unsigned int freq2;
  uint8_t freq1;
  uint32_t freq;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'setChannel'"));
  #endif

  st0 = readRegister(REG_OP_MODE);	// Save the previous status
  if( _modem == LORA )
  {
	  // LoRa Stdby mode in order to write in registers
	  writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);
  }
  else
  {
	  // FSK Stdby mode in order to write in registers
	  writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);
  }

  freq3 = ((ch >> 16) & 0x0FF);		// frequency channel MSB
  freq2 = ((ch >> 8) & 0x0FF);		// frequency channel MIB
  freq1 = (ch & 0xFF);				// frequency channel LSB

  writeRegister(REG_FRF_MSB, freq3);
  writeRegister(REG_FRF_MID, freq2);
  writeRegister(REG_FRF_LSB, freq1);

  // storing MSB in freq channel value
  freq3 = (readRegister(REG_FRF_MSB));
  freq = (freq3 << 8) & 0xFFFFFF;

  // storing MID in freq channel value
  freq2 = (readRegister(REG_FRF_MID));
  freq = (freq << 8) + ((freq2 << 8) & 0xFFFFFF);

  // storing LSB in freq channel value
  freq = freq + ((readRegister(REG_FRF_LSB)) & 0xFFFFFF);

  if( freq == ch )
  {
    state = 0;
    _channel = ch;
    #if (SX1272_debug_mode > 1)
		PRINT_SX1272(F("## Frequency channel "));
		USB.printHex(ch);
		USB.println(F(" has been successfully set ##"));
		PRINTLN_SX1272();
	#endif
  }
  else
  {
    state = 1;
  }

  if( not isChannel(ch) )
  {
	 state = -1;
	 #if (SX1272_debug_mode > 1)
		 PRINT_SX1272(F("** Frequency channel "));
		 USB.printHex(ch);
		 USB.println(F("is not a correct value **"));
		 PRINTLN_SX1272();
	 #endif
  }

  writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
  return state;
}

/*
 Function: Gets the signal power within the module is configured.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getPower()
{
  uint8_t state = 2;
  byte value = 0x00;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'getPower'"));
  #endif

  value = readRegister(REG_PA_CONFIG);
  state = 1;

  _power = value;
  if( (value > -1) && (value < 16) )
  {
	    state = 0;
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("## Output power is "));
			USB.printHex(_power);
			USB.println(F(" ##"));
			PRINTLN_SX1272();
		#endif
	}

  return state;
}

/*
 Function: Sets the signal power indicated in the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
 Parameters:
   p: power option to set in configuration.
*/
int8_t WaspSX1272::setPower(char p)
{
  byte st0;
  int8_t state = 2;
  byte value = 0x00;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'setPower'"));
  #endif

  st0 = readRegister(REG_OP_MODE);	  // Save the previous status
  if( _modem == LORA )
  { // LoRa Stdby mode to write in registers
	  writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);
  }
  else
  { // FSK Stdby mode to write in registers
	  writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);
  }

  switch (p)
  {
    // L = low
    // H = high
    // M = max

    case 'M':  _power = 0x0F;
               break;

    case 'L':  _power = 0x00;
               break;

    case 'H':  _power = 0x07;
               break;

    default:   state = -1;
               break;
  }

  writeRegister(REG_PA_CONFIG, _power);	// Setting output power value
  value = readRegister(REG_PA_CONFIG);

  if( value == _power )
  {
	  state = 0;
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("## Output power has been successfully set ##"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  {
	  state = 1;
  }

  writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
  return state;
}

/*
 Function: Sets the signal power indicated as input to the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
 Parameters:
   pow: power option to set in configuration. The input value range is from
   0 to 14 dBm.
*/
int8_t WaspSX1272::setPowerNum(uint8_t pow)
{
  byte st0;
  int8_t state = 2;
  byte value = 0x00;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'setPower'"));
  #endif

  st0 = readRegister(REG_OP_MODE);	  // Save the previous status
  if( _modem == LORA )
  { // LoRa Stdby mode to write in registers
	  writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);
  }
  else
  { // FSK Stdby mode to write in registers
	  writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);
  }

  if ( (pow >= 0) && (pow < 15) )
  {
	  _power = pow;
  }
  else
  {
	  state = -1;
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("## Power value is not valid ##"));
		  PRINTLN_SX1272();
	  #endif
  }

  writeRegister(REG_PA_CONFIG, _power);	// Setting output power value
  value = readRegister(REG_PA_CONFIG);

  if( value == _power )
  {
	  state = 0;
	  #if (SX1272_debug_mode > 1)
		  PRINTLN_SX1272(F("## Output power has been successfully set ##"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  {
	  state = 1;
  }

  writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
  return state;
}


/*
 Function: Gets the preamble length from the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getPreambleLength()
{
	int8_t state = 2;
	uint8_t p_length;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getPreambleLength'"));
	#endif

	state = 1;
	if( _modem == LORA )
  	{ // LORA mode
  		p_length = readRegister(REG_PREAMBLE_MSB_LORA);
  		// Saving MSB preamble length in LoRa mode
		_preamblelength = (p_length << 8) & 0xFFFF;
		p_length = readRegister(REG_PREAMBLE_LSB_LORA);
  		// Saving LSB preamble length in LoRa mode
		_preamblelength = _preamblelength + (p_length & 0xFFFF);
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("## Preamble length configured is "));
			USB.printHex(_preamblelength);
			USB.print(F(" ##"));
			USB.println();
		#endif
	}
	else
	{ // FSK mode
		p_length = readRegister(REG_PREAMBLE_MSB_FSK);
		// Saving MSB preamble length in FSK mode
		_preamblelength = (p_length << 8) & 0xFFFF;
		p_length = readRegister(REG_PREAMBLE_LSB_FSK);
		// Saving LSB preamble length in FSK mode
		_preamblelength = _preamblelength + (p_length & 0xFFFF);
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("## Preamble length configured is "));
			USB.printHex(_preamblelength);
			USB.print(F(" ##"));
			USB.println();
		#endif
	}
	state = 0;
	return state;
}

/*
 Function: Sets the preamble length in the module
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
 Parameters:
   l: length value to set as preamble length.
*/
uint8_t WaspSX1272::setPreambleLength(uint16_t l)
{
	byte st0;
	uint8_t p_length;
	int8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setPreambleLength'"));
	#endif

	st0 = readRegister(REG_OP_MODE);	// Save the previous status
	state = 1;
	if( _modem == LORA )
  	{ // LoRa mode
  		writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);    // Set Standby mode to write in registers
  		p_length = ((l >> 8) & 0x0FF);
  		// Storing MSB preamble length in LoRa mode
		writeRegister(REG_PREAMBLE_MSB_LORA, p_length);
		p_length = (l & 0x0FF);
		// Storing LSB preamble length in LoRa mode
		writeRegister(REG_PREAMBLE_LSB_LORA, p_length);
	}
	else
	{ // FSK mode
		writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);    // Set Standby mode to write in registers
		p_length = ((l >> 8) & 0x0FF);
  		// Storing MSB preamble length in FSK mode
		writeRegister(REG_PREAMBLE_MSB_FSK, p_length);
		p_length = (l & 0x0FF);
  		// Storing LSB preamble length in FSK mode
		writeRegister(REG_PREAMBLE_LSB_FSK, p_length);
	}

	state = 0;
	#if (SX1272_debug_mode > 1)
		PRINT_SX1272(F("## Preamble length "));
		USB.printHex(l);
		USB.println(F(" has been successfully set ##"));
		PRINTLN_SX1272();
	#endif

	writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
	return state;
}

/*
 Function: Gets the payload length from the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getPayloadLength()
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getPayloadLength'"));
	#endif

	if( _modem == LORA )
  	{ // LORA mode
  		// Saving payload length in LoRa mode
		_payloadlength = readRegister(REG_PAYLOAD_LENGTH_LORA);
		state = 1;
	}
	else
	{ // FSK mode
  		// Saving payload length in FSK mode
		_payloadlength = readRegister(REG_PAYLOAD_LENGTH_FSK);
		state = 1;
	}

	#if (SX1272_debug_mode > 1)
		PRINT_SX1272(F("## Payload length configured is "));
		USB.printHex(_payloadlength);
		USB.println(F(" ##"));
		PRINTLN_SX1272();
	#endif

	state = 0;
	return state;
}

/*
 Function: Sets the packet length in the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
*/
int8_t WaspSX1272::setPacketLength()
{
	uint16_t length;

	length = _payloadlength + OFFSET_PAYLOADLENGTH;
	return setPacketLength(length);
}

/*
 Function: Sets the packet length in the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
 Parameters:
   l: length value to set as payload length.
*/
int8_t WaspSX1272::setPacketLength(uint8_t l)
{
	byte st0;
	byte value = 0x00;
	int8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setPacketLength'"));
	#endif

	st0 = readRegister(REG_OP_MODE);	// Save the previous status
	//----
	//	truncPayload(l);
	packet_sent.length = l;
	//
	if( _modem == LORA )
  	{ // LORA mode
  		writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);    // Set LoRa Standby mode to write in registers
		writeRegister(REG_PAYLOAD_LENGTH_LORA, packet_sent.length);
		// Storing payload length in LoRa mode
		value = readRegister(REG_PAYLOAD_LENGTH_LORA);
	}
	else
	{ // FSK mode
		writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);    //  Set FSK Standby mode to write in registers
		writeRegister(REG_PAYLOAD_LENGTH_FSK, packet_sent.length);
		// Storing payload length in FSK mode
		value = readRegister(REG_PAYLOAD_LENGTH_FSK);
	}

	if( packet_sent.length == value )
	{
		state = 0;
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("## Packet length "));
			USB.print(packet_sent.length, DEC);
			USB.println(F(" has been successfully set ##"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{
		state = 1;
	}

	writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
  	//delay(250);
	return state;
}

/*
 Function: Gets the node address in the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getNodeAddress()
{
	byte st0 = 0;
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getNodeAddress'"));
	#endif

	if( _modem == LORA )
	{
		// Nothing to read
		// node address is stored in _nodeAddress attribute
		state = 0;
	}
	else
	{
		// FSK mode
		st0 = readRegister(REG_OP_MODE);	// Save the previous status

		// Allowing access to FSK registers while in LoRa standby mode
		writeRegister(REG_OP_MODE, LORA_STANDBY_FSK_REGS_MODE);

		// Read node address
		_nodeAddress = readRegister(REG_NODE_ADRS);

		// Getting back to previous status
		writeRegister(REG_OP_MODE, st0);

		// update state
		state = 0;
	}

	#if (SX1272_debug_mode > 1)
		PRINT_SX1272(F("## Node address configured is "));
		USB.print(_nodeAddress, DEC);
		USB.println(F(" ##"));
		PRINTLN_SX1272();
	#endif
	return state;
}

/*
 Function: Sets the node address in the module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
 Parameters:
   addr: address value to set as node address.
*/
int8_t WaspSX1272::setNodeAddress(uint8_t addr)
{
	byte st0;
	byte value;
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setNodeAddress'"));
	#endif

	// check address value is within valid range
	if( addr > 255 )
	{
		state = -1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Node address must be less than 255 **"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{
		// Saving node address
		_nodeAddress = addr;
		st0 = readRegister(REG_OP_MODE);	  // Save the previous status

		// in LoRa mode
		state = 0;

		if( _modem == LORA )
		{
			// in LoRa mode, address is SW controlled
			// set status to success
			state = 0;
		}
		else if( _modem == FSK )
		{
			//Set FSK Standby mode to write in registers
			writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);

			// Storing node and broadcast address
			writeRegister(REG_NODE_ADRS, addr);
			writeRegister(REG_BROADCAST_ADRS, BROADCAST_0);

			value = readRegister(REG_NODE_ADRS);
			writeRegister(REG_OP_MODE, st0);		// Getting back to previous status

			if( value == _nodeAddress )
			{
				state = 0;
				#if (SX1272_debug_mode > 1)
					PRINT_SX1272(F("## Node address "));
					USB.print(_nodeAddress, DEC);
					USB.println(F(" has been successfully set ##"));
					PRINTLN_SX1272();
				#endif
			}
			else
			{
				state = 1;
				#if (SX1272_debug_mode > 1)
					PRINTLN_SX1272(F("** There has been an error while setting address ##"));
					PRINTLN_SX1272();
				#endif
			}
		}
	}
	return state;
}

/*
 Function: Gets the SNR value in LoRa mode.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
*/
int8_t WaspSX1272::getSNR()
{	// getSNR exists only in LoRa mode
  int8_t state = 2;
  byte value;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'getSNR'"));
  #endif

  if( _modem == LORA )
  { // LoRa mode
	  state = 1;
	  value = readRegister(REG_PKT_SNR_VALUE);
	  if( value & 0x80 ) // The SNR sign bit is 1
	  {
		  // Invert and divide by 4
		  value = ( ( ~value + 1 ) & 0xFF ) >> 2;
          _SNR = -value;
      }
      else
      {
		  // Divide by 4
		  _SNR = ( value & 0xFF ) >> 2;
	  }
	  state = 0;
	  #if (SX1272_debug_mode > 0)
		  PRINT_SX1272(F("## SNR value is "));
		  USB.print(_SNR, DEC);
		  USB.println(F(" ##"));
		  PRINTLN_SX1272();
	  #endif
  }
  else
  { // forbidden command if FSK mode
	state = -1;
	#if (SX1272_debug_mode > 0)
		PRINTLN_SX1272(F("** SNR does not exist in FSK mode **"));
		PRINTLN_SX1272();
	#endif
  }
  return state;
}

/*
 Function: Gets the current value of RSSI.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getRSSI()
{
	uint8_t state = 2;
	int rssi_mean = 0;
	int total = 5;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getRSSI'"));
	#endif

	if( _modem == LORA )
	{
		/// LoRa mode
		// get mean value of RSSI
		for(int i = 0; i < total; i++)
		{
			_RSSI = -OFFSET_RSSI + readRegister(REG_RSSI_VALUE_LORA);
			rssi_mean += _RSSI;
		}
		rssi_mean = rssi_mean / total;
		_RSSI = rssi_mean;

		state = 0;
		#if (SX1272_debug_mode > 0)
			PRINT_SX1272(F("## RSSI value is "));
			USB.print(_RSSI, DEC);
			USB.println(F(" ##"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{
		/// FSK mode
		// get mean value of RSSI
		for(int i = 0; i < total; i++)
		{
			_RSSI = (readRegister(REG_RSSI_VALUE_FSK) >> 1);
			rssi_mean += _RSSI;
		}
		rssi_mean = rssi_mean / total;
		_RSSI = rssi_mean;

		state = 0;
		#if (SX1272_debug_mode > 0)
			PRINT_SX1272(F("## RSSI value is "));
			USB.print(_RSSI);
			USB.println(F(" ##"));
			PRINTLN_SX1272();
		#endif
	}

	return state;
}

/*
 Function: Gets the RSSI of the last packet received in LoRa mode.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden command for this protocol
*/
int16_t WaspSX1272::getRSSIpacket()
{	// RSSIpacket only exists in LoRa
  int8_t state = 2;

  #if (SX1272_debug_mode > 1)
	  PRINTLN_SX1272();
	  PRINTLN_SX1272(F("Starting 'getRSSIpacket'"));
  #endif

  state = 1;
  if( _modem == LORA )
  { // LoRa mode
	  state = getSNR();
	  if( state == 0 )
	  {
		  if( _SNR < 0 )
		  {
			  _RSSIpacket = -NOISE_ABSOLUTE_ZERO + 10.0 * SignalBwLog[_bandwidth] + NOISE_FIGURE + ( double )_SNR;
			  state = 0;
		  }
		  else
		  {
			  _RSSIpacket = readRegister(REG_PKT_RSSI_VALUE);
			  _RSSIpacket = -OFFSET_RSSI + ( double )_RSSIpacket;
			  state = 0;
		  }
	  #if (SX1272_debug_mode > 0)
		  PRINT_SX1272(F("## RSSI packet value is "));
		  USB.print(_RSSIpacket, DEC);
  		  USB.println(F(" ##"));
		  PRINTLN_SX1272();
	  #endif
	  }
  }
  else
  { // RSSI packet doesn't exist in FSK mode
	state = -1;
	#if (SX1272_debug_mode > 0)
		PRINTLN_SX1272(F("** RSSI packet does not exist in FSK mode **"));
		PRINTLN_SX1272();
	#endif
  }
  return state;
}

/*
 Function: It sets the maximum number of retries.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 -->
*/
uint8_t WaspSX1272::setRetries(uint8_t ret)
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setRetries'"));
	#endif

	state = 1;
	if( ret > MAX_RETRIES )
	{
		state = -1;
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("** Retries value can't be greater than "));
			USB.print(MAX_RETRIES, DEC);
			USB.println(F(" **"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{
		_maxRetries = ret;
		state = 0;
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("## Maximum retries value = "));
			USB.print(_maxRetries, DEC);
			USB.println(F(" ##"));
			PRINTLN_SX1272();
		#endif
	}
	return state;
}

/*
 Function: Gets the current supply limit of the power amplifier, protecting battery chemistries.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
 Parameters:
   rate: value to compute the maximum current supply. Maximum current is 45+5*'rate' [mA]
*/
uint8_t WaspSX1272::getMaxCurrent()
{
	int8_t state = 2;
	byte value;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getMaxCurrent'"));
	#endif

	state = 1;
	_maxCurrent = readRegister(REG_OCP);

	// extract only the OcpTrim value from the OCP register
	_maxCurrent &= B00011111;

	if( _maxCurrent <= 15 )
	{
		value = (45 + (5 * _maxCurrent));
	}
	else if( _maxCurrent <= 27 )
	{
		value = (-30 + (10 * _maxCurrent));
	}
	else
	{
		value = 240;
	}

	_maxCurrent = value;
	#if (SX1272_debug_mode > 1)
		PRINT_SX1272(F("## Maximum current supply configured is "));
		USB.print(value, DEC);
		USB.println(F(" mA ##"));
		PRINTLN_SX1272();
	#endif
	state = 0;
	return state;
}

/*
 Function: Limits the current supply of the power amplifier, protecting battery chemistries.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden parameter value for this function
 Parameters:
   rate: value to compute the maximum current supply. Range: 0x00 to 0x1B. The
   Maximum current is:
	Imax = 45+5*OcpTrim [mA] 	if OcpTrim <= 15 (120 mA) /
	Imax = -30+10*OcpTrim [mA] 	if 15 < OcpTrim <= 27 (130 to 240 mA)
	Imax = 240mA 				for higher settings
*/
int8_t WaspSX1272::setMaxCurrent(uint8_t rate)
{
	int8_t state = 2;
	byte st0;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setMaxCurrent'"));
	#endif

	// Maximum rate value = 0x1B, because maximum current supply = 240 mA
	if (rate > 0x1B)
	{
		state = -1;
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("** Maximum current supply is 240 mA, "));
			USB.println(F("so maximum parameter value must be 27 (DEC) or 0x1B (HEX) **"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{
		// Enable Over Current Protection
		rate |= B00100000;

		state = 1;
		st0 = readRegister(REG_OP_MODE);	// Save the previous status
		if( _modem == LORA )
		{ // LoRa mode
			writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);	// Set LoRa Standby mode to write in registers
		}
		else
		{ // FSK mode
			writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);	// Set FSK Standby mode to write in registers
		}
		writeRegister(REG_OCP, rate);		// Modifying maximum current supply
		writeRegister(REG_OP_MODE, st0);		// Getting back to previous status
		state = 0;
	}
	return state;
}

/*
 Function: Gets the content of different registers.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getRegs()
{
	int8_t state = 2;
	uint8_t state_f = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getRegs'"));
	#endif

	state_f = 1;
	state = getMode();			// Stores the BW, CR and SF.
	if( state == 0 )
	{
		state = getPower();		// Stores the power.
	}
	else
	{
		state_f = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting mode **"));
		#endif
	}
 	if( state == 0 )
	{
		state = getChannel();	// Stores the channel.
	}
	else
	{
		state_f = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting power **"));
		#endif
	}
	if( state == 0 )
	{
		state = getCRC();		// Stores the CRC configuration.
	}
	else
	{
		state_f = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting channel **"));
		#endif
	}
	if( state == 0 )
	{
		state = getHeader();	// Stores the header configuration.
	}
	else
	{
		state_f = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting CRC **"));
		#endif
	}
	if( state == 0 )
	{
		state = getPreambleLength();	// Stores the preamble length.
	}
	else
	{
		state_f = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting header **"));
		#endif
	}
	if( state == 0 )
	{
		state = getPayloadLength();		// Stores the payload length.
	}
	else
	{
		state_f = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting preamble length **"));
		#endif
	}
	if( state == 0 )
	{
		state = getNodeAddress();		// Stores the node address.
	}
	else
	{
		state_f = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting payload length **"));
		#endif
	}
	if( state == 0 )
	{
		state = getMaxCurrent();		// Stores the maximum current supply.
	}
	else
	{
		state_f = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting node address **"));
		#endif
	}
	if( state == 0 )
	{
		state_f = getTemp();		// Stores the module temperature.
	}
	else
	{
		state_f = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting maximum current supply **"));
		#endif
	}
	if( state_f != 0 )
	{
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("** Error getting temperature **"));
			PRINTLN_SX1272();
		#endif
	}
	return state_f;
}

/*
 Function: It truncs the payload length if it is greater than 0xFF.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::truncPayload(uint16_t length16)
{
	uint8_t state = 2;

	state = 1;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'truncPayload'"));
	#endif

	if( length16 > MAX_PAYLOAD )
	{
		_payloadlength = MAX_PAYLOAD;
	}
	else
	{
		_payloadlength = (length16 & 0xFF);
	}
	state = 0;

	return state;
}

/*
 Function: It sets an ACK in FIFO in order to send it.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::setACK()
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setACK'"));
	#endif

	clearFlags();	// Initializing flags

	if( _modem == LORA )
	{ // LoRa mode
		writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);	// Stdby LoRa mode to write in FIFO
	}
	else
	{ // FSK mode
		writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);	// Stdby FSK mode to write in FIFO
	}

	// Setting ACK length in order to send it
	state = setPacketLength(ACK_LENGTH);
	if( state == 0 )
	{
		// Setting ACK
		memset( &ACK, 0x00, sizeof(ACK) );
		ACK.dst = packet_received.src; // ACK destination is packet source
		ACK.src = packet_received.dst; // ACK source is packet destination
		ACK.packnum = packet_received.packnum; // packet number that has been correctly received
		ACK.length = 0;		  // length = 0 to show that's an ACK
		ACK.data[0] = _reception;	// CRC of the received packet

		// Setting address pointer in FIFO data buffer
		writeRegister(REG_FIFO_ADDR_PTR, 0x00);
		writeRegister(REG_FIFO_TX_BASE_ADDR, 0x00);

		state = 1;

		// Writing ACK to send in FIFO
		writeRegister(REG_FIFO, ACK.dst); 		// Writing the destination in FIFO
		writeRegister(REG_FIFO, ACK.src);		// Writing the source in FIFO
		writeRegister(REG_FIFO, ACK.packnum);	// Writing the packet number in FIFO
		writeRegister(REG_FIFO, ACK.length); 	// Writing the packet length in FIFO
		writeRegister(REG_FIFO, ACK.data[0]);	// Writing the ACK in FIFO

		#if (SX1272_debug_mode > 0)
			PRINTLN_SX1272(F("## ACK set and written in FIFO ##"));
			// Print the complete ACK if debug_mode
			PRINT_SX1272(F("## ACK to send:"));
			USB.printHex(ACK.dst);			 	// Printing destination
			USB.print("|");
			USB.printHex(ACK.src);			 	// Printing source
			USB.print("|");
			USB.printHex(ACK.packnum);			// Printing ACK number
			USB.print("|");
			USB.printHex(ACK.length);				// Printing ACK length
			USB.print("|");
			USB.printHex(ACK.data[0]);			// Printing ACK payload
			USB.println(F(" ##"));
			PRINTLN_SX1272();
		#endif

		state = 0;
		_reception = CORRECT_PACKET;		// Updating value to next packet

		delay(500);
	}
	return state;
}

/*
 Function: Configures the module to receive information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::receive()
{
	uint8_t state = 1;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'receive'"));
	#endif

	// Initializing packet_received struct
	memset( &packet_received, 0x00, sizeof(packet_received) );

	// Setting Testmode
	writeRegister(0x31,0x43);
	// Set LowPnTxPllOff
	writeRegister(REG_PA_RAMP, 0x09);
	// Set LNA gain: Highest gain. LnaBoost:Improved sensitivity
	writeRegister(REG_LNA, 0x23);
	// Setting address pointer in FIFO data buffer
	writeRegister(REG_FIFO_ADDR_PTR, 0x00);
	// change RegSymbTimeoutLsb
	writeRegister(REG_SYMB_TIMEOUT_LSB, 0xFF);
	// Setting current value of reception buffer pointer
	writeRegister(REG_FIFO_RX_BYTE_ADDR, 0x00);

	// Proceed depending on the protocol selected
	if( _modem == LORA )
	{
		/// LoRa mode
		// With MAX_LENGTH gets all packets with length < MAX_LENGTH
		state = setPacketLength(MAX_LENGTH);
		// Set LORA mode - Rx
		writeRegister(REG_OP_MODE, LORA_RX_MODE);

		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## Receiving LoRa mode activated with success ##"));
			USB.println(millis(),DEC);
		#endif
	}
	else
	{
		/// FSK mode
		state = setPacketLength();
		// FSK mode - Rx
		writeRegister(REG_OP_MODE, FSK_RX_MODE);
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## Receiving FSK mode activated with success ##"));
			PRINTLN_SX1272();
		#endif
	}

	#if (SX1272_debug_mode > 1)
		//showRxRegisters();
	#endif

	return state;
}

/*
 Function: Configures the module to receive information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::receivePacketMAXTimeout()
{
	return receivePacketTimeout(MAX_TIMEOUT);
}

/*
 Function: Configures the module to receive information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::receivePacketTimeout()
{
	setTimeout();
	return receivePacketTimeout(_sendTime);
}

/*
 Function: Configures the module to receive information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::receivePacketTimeout(uint32_t wait)
{
	uint8_t state = 2;
	uint8_t state_f = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'receivePacketTimeout'"));
	#endif

	// set RX mode
	state = receive();

	// if RX mode is set correctly then wait for data
	if( state == 0 )
	{
		// Wait for a new packet for 'wait' time
		if( availableData(wait) )
		{
			// If packet received, getPacket
			state_f = getPacket();
		}
		else
		{
			state_f = 1;
		}
	}
	else
	{
		state_f = state;
	}
	return state_f;
}

/*
 Function: Configures the module to receive information and send an ACK.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::receivePacketMAXTimeoutACK()
{
	return receivePacketTimeoutACK(MAX_TIMEOUT);
}

/*
 Function: Configures the module to receive information and send an ACK.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::receivePacketTimeoutACK()
{
	setTimeout();
	return receivePacketTimeoutACK(_sendTime);
}

/*
 Function: Configures the module to receive information and send an ACK.
 Returns: Integer that determines if there has been any error
   state = 4  --> The command has been executed but the packet received is incorrect
   state = 3  --> The command has been executed but there is no packet received
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::receivePacketTimeoutACK(uint32_t wait)
{
	uint8_t state = 2;
	uint8_t state_f = 2;


	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'receivePacketTimeoutACK'"));
	#endif

	// set RX mode
	state = receive();

	// if RX mode is set correctly then wait for data
	if( state == 0 )
	{
		// Wait for a new packet for 'wait' time
		if( availableData(wait) )
		{
			// If packet received, getPacket
			state = getPacket();
		}
		else
		{
			state = 1;
			state_f = 3;  // There is no packet received
		}
	}
	else
	{
		state = 1;
		state_f = 1; // There has been an error with the 'receive' function
	}


	if( (state == 0) || (state == 3) )
	{
		if( _reception == INCORRECT_PACKET )
		{
			state_f = 4;  // The packet has been incorrectly received
		}
		else
		{
			state_f = 1;  // The packet has been correctly received
		}
		state = setACK();
		if( state == 0 )
		{
			state = sendWithTimeout();
			if( state == 0 )
			{
			state_f = 0;
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("This last packet was an ACK, so ..."));
				PRINTLN_SX1272(F("ACK successfully sent"));
				PRINTLN_SX1272();
			#endif
			}
			else
			{
				state_f = 1; // There has been an error with the 'sendWithTimeout' function
			}
		}
		else
		{
			state_f = 1; // There has been an error with the 'setACK' function
		}
	}
	else
	{
		state_f = 1;
	}
	return state_f;
}

/*
 Function: Configures the module to receive all the information on air, before MAX_TIMEOUT expires.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t	WaspSX1272::receiveAll()
{
	return receiveAll(MAX_TIMEOUT);
}

/*
 Function: Configures the module to receive all the information on air.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::receiveAll(uint32_t wait)
{
	uint8_t state = 2;
	byte config1;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'receiveAll'"));
	#endif

	if( _modem == FSK )
	{
		/// FSK mode
		writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);		// Setting standby FSK mode
		config1 = readRegister(REG_PACKET_CONFIG1);
		config1 = config1 & B11111001;			// clears bits 2-1 from REG_PACKET_CONFIG1
		writeRegister(REG_PACKET_CONFIG1, config1);		// AddressFiltering = None
	}

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272(F("## Address filtering desactivated ##"));
		PRINTLN_SX1272();
	#endif

	// Setting Rx mode
	state = receive();

	if( state == 0 )
	{
		// Getting all packets received in wait
		state = getPacket(wait);
	}
	return state;
}

/*
 Function: If a packet is received, checks its destination.
 Returns: Boolean that's 'true' if the packet is for the module and
		  it's 'false' if the packet is not for the module.
*/
boolean	WaspSX1272::availableData()
{
	return availableData(MAX_TIMEOUT);
}

/*
 Function: If a packet is received, checks its destination.
 Returns: Boolean that's 'true' if the packet is for the module and
		  it's 'false' if the packet is not for the module.
 Parameters:
   wait: time to wait while there is no a valid header received.
*/
boolean	WaspSX1272::availableData(uint32_t wait)
{
	byte value;
	byte header = 0;
	boolean forme = false;
	unsigned long previous;

	// update attribute
	_hreceived = false;

	#if (SX1272_debug_mode > 0)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'availableData'"));
	#endif

	previous = millis();

	if( _modem == LORA )
	{
		/// LoRa mode
		// read REG_IRQ_FLAGS
		value = readRegister(REG_IRQ_FLAGS);

		// Wait to ValidHeader interrupt in REG_IRQ_FLAGS
		while( (bitRead(value, 4) == 0) && (millis()-previous < (unsigned long)wait) )
		{
			// read REG_IRQ_FLAGS
			value = readRegister(REG_IRQ_FLAGS);

			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous )
			{
				previous = millis();
			}
		}

		// Check if ValidHeader was received
		if( bitRead(value, 4) == 1 )
		{
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("## Valid Header received in LoRa mode ##"));
			#endif
			_hreceived = true;
			while( (header == 0) && (millis()-previous < (unsigned long)wait) )
			{
				// Wait for the increment of the RX buffer pointer
				header = readRegister(REG_FIFO_RX_BYTE_ADDR);

				// Condition to avoid an overflow (DO NOT REMOVE)
				if( millis() < previous )
				{
					previous = millis();
				}
			}

			// If packet received: Read first byte of the received packet
			if( header != 0 )
			{
				_destination = readRegister(REG_FIFO);
			}
		}
		else
		{
			forme = false;
			_hreceived = false;
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("** The timeout has expired **"));
				PRINTLN_SX1272();
			#endif
		}
	}
	else
	{
		/// FSK mode
		// read REG_IRQ_FLAGS2
		value = readRegister(REG_IRQ_FLAGS2);
		// Wait to Payload Ready interrupt
		while( (bitRead(value, 2) == 0) && (millis() - previous < wait) )
		{
			value = readRegister(REG_IRQ_FLAGS2);
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous )
			{
				previous = millis();
			}
		}// end while (millis)
		if( bitRead(value, 2) == 1 )	// something received
		{
			_hreceived = true;
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("## Valid Preamble detected in FSK mode ##"));
			#endif
			// Reading first byte of the received packet
			_destination = readRegister(REG_FIFO);
		}
		else
		{
			forme = false;
			_hreceived = false;
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("** The timeout has expired **"));
				PRINTLN_SX1272();
			#endif
		}
	}


	/* We use '_hreceived' because we need to ensure that '_destination' value
	 * is correctly updated and is not the '_destination' value from the
	 * previously packet
	 */
	if( _hreceived == true )
	{
		#if (SX1272_debug_mode > 0)
			PRINTLN_SX1272(F("## Checking destination ##"));
		#endif

		// Checking destination
		if( (_destination == _nodeAddress) || (_destination == BROADCAST_0) )
		{ // LoRa or FSK mode
			forme = true;
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("## Packet received is for me ##"));
			#endif
		}
		else
		{
			forme = false;
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("## Packet received is not for me ##"));
				PRINT_SX1272(millis());
			#endif

			// If it is not a correct destination address, then change to
			// STANDBY to minimize power consumption
			if( _modem == LORA )
			{
				// Setting standby LoRa mode
				writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);
			}
			else
			{
				// Setting standby FSK mode
				writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);
			}
		}
	}
	else
	{
		// If timeout has expired, then change to
		// STANDBY to minimize power consumption
		if( _modem == LORA )
		{
			// Setting standby LoRa mode
//~ 			writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);
		}
		else
		{
			// Setting standby FSK mode
			writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);
		}
	}
	return forme;
}

/*
 Function: It gets and stores a packet if it is received before MAX_TIMEOUT expires.
 Returns:  Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getPacketMAXTimeout()
{
	return getPacket(MAX_TIMEOUT);
}

/*
 Function: It gets and stores a packet if it is received.
 Returns:  Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
int8_t WaspSX1272::getPacket()
{
	return getPacket(MAX_TIMEOUT);
}

/*
 Function: It gets and stores a packet if it is received before ending 'wait' time.
 Returns:  Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
   state = -1 --> Forbidden parameter value for this function
 Parameters:
   wait: time to wait while there is no a valid header received.
*/
int8_t WaspSX1272::getPacket(uint32_t wait)
{
	uint8_t state = 2;
	uint8_t state_f = 2;
	byte value = 0x00;
	unsigned long previous;
	boolean p_received = false;

	#if (SX1272_debug_mode > 0)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getPacket'"));
	#endif

	previous = millis();

	if( _modem == LORA )
	{
		/// LoRa mode
		// read REG_IRQ_FLAGS
		value = readRegister(REG_IRQ_FLAGS);

		// Wait until the packet is received (RxDone flag) or the timeout expires
		while( (bitRead(value, 6) == 0) && (millis()-previous < (unsigned long)wait) )
		{
			value = readRegister(REG_IRQ_FLAGS);

			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous )
			{
				previous = millis();
			}
		}

		// Check if 'RxDone' is true and 'PayloadCrcError' is correct
		if( (bitRead(value, 6) == 1) && (bitRead(value, 5) == 0) )
		{
			// packet received & CRC correct
			p_received = true;	// packet correctly received
			_reception = CORRECT_PACKET;
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("## Packet correctly received in LoRa mode ##"));
			#endif
		}
		else
		{
			if( bitRead(value, 6) != 1 )
			{
				#if (SX1272_debug_mode > 0)
					PRINTLN_SX1272(F("NOT 'RxDone' flag"));
				#endif
			}

			if( _CRC != CRC_ON )
			{
				#if (SX1272_debug_mode > 0)
					PRINTLN_SX1272(F("NOT 'CRC_ON' enabled"));
				#endif
			}

			if( (bitRead(value, 5) == 0) && (_CRC == CRC_ON) )
			{
				// CRC is correct
				_reception = CORRECT_PACKET;
			}
			else
			{
				// CRC incorrect
				_reception = INCORRECT_PACKET;
				state = 3;
				#if (SX1272_debug_mode > 0)
					PRINTLN_SX1272(F("** The CRC is incorrect **"));
					PRINTLN_SX1272();
				#endif
			}
		}

	}
	else
	{
		/// FSK mode
		value = readRegister(REG_IRQ_FLAGS2);
		while( (bitRead(value, 2) == 0) && (millis() - previous < wait) )
		{
			value = readRegister(REG_IRQ_FLAGS2);
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous )
			{
				previous = millis();
			}
		} // end while (millis)
		if( bitRead(value, 2) == 1 )
		{ // packet received
 			if( (bitRead(value, 1) == 1) && (_CRC == CRC_ON) )
			{ // CRC correct
				_reception = CORRECT_PACKET;
				p_received = true;
				#if (SX1272_debug_mode > 0)
					PRINTLN_SX1272(F("## Packet correctly received in FSK mode ##"));
				#endif
			}
			else
			{ // CRC incorrect
				_reception = INCORRECT_PACKET;
				state = 3;
				p_received = false;
				#if (SX1272_debug_mode > 0)
					PRINTLN_SX1272(F("## Packet incorrectly received in FSK mode ##"));
				#endif
			}
		}
		else
		{
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("** The timeout has expired **"));
				PRINTLN_SX1272();
			#endif
		}
		writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);	// Setting standby FSK mode
	}

	/* If a new packet was received correctly, now the information must be
	 * filled inside the structures of the class
	 */
	if( p_received == true )
	{
		// Store the packet
		if( _modem == LORA )
		{
			/// LoRa
			// Setting address pointer in FIFO data buffer
			writeRegister(REG_FIFO_ADDR_PTR, 0x00);
			// Storing first byte of the received packet
			packet_received.dst = readRegister(REG_FIFO);
		}
		else
		{
			/// FSK
			value = readRegister(REG_PACKET_CONFIG1);
			if( (bitRead(value, 2) == 0) && (bitRead(value, 1) == 0) )
			{
				// Storing first byte of the received packet
				packet_received.dst = readRegister(REG_FIFO);
			}
			else
			{
				// Storing first byte of the received packet
				packet_received.dst = _destination;
			}
		}

		// Reading second byte of the received packet
		// Reading third byte of the received packet
		// Reading fourth byte of the received packet
		packet_received.src = readRegister(REG_FIFO);
		packet_received.packnum = readRegister(REG_FIFO);
		packet_received.length = readRegister(REG_FIFO);

		// calculate the payload length
		if( _modem == LORA )
		{
			_payloadlength = packet_received.length - OFFSET_PAYLOADLENGTH;
		}

		// check if length is incorrect
		if( packet_received.length > (MAX_LENGTH + 1) )
		{
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("Corrupted packet, length must be less than 256"));
			#endif
		}
		else
		{
			// Store payload in 'data'
			for(unsigned int i = 0; i < _payloadlength; i++)
			{
				packet_received.data[i] = readRegister(REG_FIFO);
			}
			// Store 'retry'
			packet_received.retry = readRegister(REG_FIFO);

			// Print the packet if debug_mode
			#if (SX1272_debug_mode > 0)
				PRINT_SX1272(F("## Packet received:"));
				USB.printHex(packet_received.dst);			 	// Printing destination
				USB.print("|");
				USB.printHex(packet_received.src);			 	// Printing source
				USB.print("|");
				USB.printHex(packet_received.packnum);			// Printing packet number
				USB.print("|");
				USB.printHex(packet_received.length);			// Printing packet length
				USB.print("|");
				for(unsigned int i = 0; i < _payloadlength; i++)
				{
					USB.printHex(packet_received.data[i]);		// Printing payload
					USB.print("|");
				}
				USB.printHex(packet_received.retry);			// Printing number retry
				USB.println(F(" ##"));
				PRINTLN_SX1272();
			#endif
			state_f = 0;
		}
	}
	else
	{
		// if packet was NOT received
		state_f = 1;
		if( (_reception == INCORRECT_PACKET) && (_retries < _maxRetries) && (state != 3) )
		{
			_retries++;
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("## Retrying to send the last packet ##"));
				PRINTLN_SX1272();
			#endif
		}
	}

	// Setting address pointer in FIFO data buffer to 0x00 again
	if( _modem == LORA )
	{
		writeRegister(REG_FIFO_ADDR_PTR, 0x00);
	}

	// Initializing flags
	clearFlags();

	if( wait > MAX_WAIT )
	{
		state_f = -1;
		#if (SX1272_debug_mode > 0)
			PRINTLN_SX1272(F("** The timeout must be smaller than 12.5 seconds **"));
			PRINTLN_SX1272();
		#endif
	}

	return state_f;
}

/*
 Function: It sets the packet destination.
 Returns:  Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
 Parameters:
   dest: destination value of the packet sent.
*/
int8_t WaspSX1272::setDestination(uint8_t dest)
{
	int8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setDestination'"));
	#endif

	state = 1;
	_destination = dest; // Storing destination in a global variable
	packet_sent.dst = dest;	 // Setting destination in packet structure
	packet_sent.src = _nodeAddress; // Setting source in packet structure
	packet_sent.packnum = _packetNumber;	// Setting packet number in packet structure
	_packetNumber++;
	state = 0;

	#if (SX1272_debug_mode > 1)
		PRINT_SX1272(F("## Destination "));
		USB.printHex(_destination);
		USB.println(F(" successfully set ##"));
		PRINT_SX1272(F("## Source "));
		USB.print(packet_sent.src, DEC);
		USB.println(F(" successfully set ##"));
		PRINT_SX1272(F("## Packet number "));
		USB.print(packet_sent.packnum, DEC);
		USB.println(F(" successfully set ##"));
		PRINTLN_SX1272();
	#endif
	return state;
}

/*
 Function: It sets the timeout according to the configured mode.
 Link: http://www.semtech.com/images/datasheet/sx1272.pdf
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::setTimeout()
{
	uint8_t state = 2;
	uint16_t delay;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setTimeout'"));
	#endif

	state = 1;
	if( _modem == LORA )
	{
		// calculate 'delay'
		delay = ((0.1*_sendTime) + 1);

		float Tpacket = timeOnAir();

		// calculate final send/receive timeout adding an offset and a random value
		_sendTime = (uint16_t) Tpacket + (rand()%delay) + 1000;

		#if (SX1272_debug_mode > 2)
			PRINT_SX1272(F("Tsym (ms):"));
			USB.println(Tsym);
			PRINT_SX1272(F("Tpreamble (ms):"));
			USB.println(Tpreamble);
			PRINT_SX1272(F("payloadSymbNb:"));
			USB.println(payloadSymbNb);
			PRINT_SX1272(F("Tpacket:"));
			USB.println(Tpacket);
		#endif

		// update state
		state = 0;
	}
	else
	{
		// update state
		_sendTime = MAX_TIMEOUT;

		// update state
		state = 0;
	}

	#if (SX1272_debug_mode > 1)
		PRINT_SX1272(F("Timeout to send/receive is: "));
		USB.println(_sendTime, DEC);
	#endif

	return state;
}


/*
 Function: It gets the theoretical value of the time-on-air of the packet
 Link: http://www.semtech.com/images/datasheet/sx1272.pdf
 Returns: Float that determines the time-on-air
*/
float WaspSX1272::timeOnAir()
{
	return timeOnAir( _payloadlength );
}

/*
 Function: It gets the theoretical value of the time-on-air of the packet
 Link: http://www.semtech.com/images/datasheet/sx1272.pdf
 Returns: Float that determines the time-on-air
*/
float WaspSX1272::timeOnAir( uint16_t payloadlength )
{
	float BW;
	float DE = 0;
	float SF = _spreadingFactor;
	float PL = payloadlength + OFFSET_PAYLOADLENGTH;
	float H = _header;
	float CR = _codingRate;

	// Dara rate optimization enabled if SF is 11 or 12
	if( SF > 10) DE = 1.0;
	else DE = 0.0;

	// payload correction
	if( payloadlength == 0 ) PL = 255;

	// Bandwidth value setting
	if( _bandwidth == BW_125 ) 		BW = 125.0;
	else if( _bandwidth == BW_250 ) BW = 250.0;
	else if( _bandwidth == BW_500 ) BW = 500.0;
	else BW = 125.0;

	// Calculation steps:
	float Tsym = pow(2,SF)/(BW); // ms
	float Tpreamble = (8+4.25)*Tsym;// ms
	float argument1 = ceil( (8.0*PL-4.0*SF+28.0+16.0-20.0*H)/(4.0*(SF-2.0*DE)) )*(CR+4.0);
	float argument2 = 0;
	float payloadSymbNb = 8 + max( argument1, argument2);
	float Tpayload = payloadSymbNb * Tsym;
	float Tpacket = Tpreamble + Tpayload;

	return Tpacket;
}




/*
 Function: It sets a char array payload packet in a packet struct.
 Returns:  Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::setPayload(char *payload)
{
	uint8_t state = 2;
	uint8_t state_f = 2;
	uint16_t length16;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setPayload'"));
	#endif

	state = 1;
	length16 = (uint16_t)strlen(payload);
	state = truncPayload(length16);
	if( state == 0 )
	{
		// fill data field until the end of the string
		for(unsigned int i = 0; i < _payloadlength; i++)
		{
			packet_sent.data[i] = payload[i];
		}
	}
	else
	{
		state_f = state;
	}

	// In the case of FSK mode, the max payload is more restrictive
	if( ( _modem == FSK ) && ( _payloadlength > MAX_PAYLOAD_FSK ) )
	{
		_payloadlength = MAX_PAYLOAD_FSK;
		state = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("In FSK, payload length must be less than 60 bytes."));
			PRINTLN_SX1272();
		#endif
	}

	// Set length with the actual counter value
	// Setting packet length in packet structure
	state_f = setPacketLength();
	return state_f;
}

/*
 Function: It sets an uint8_t array payload packet in a packet struct.
 Returns:  Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::setPayload(uint8_t *payload)
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setPayload'"));
	#endif

	state = 1;
	if( ( _modem == FSK ) && ( _payloadlength > MAX_PAYLOAD_FSK ) )
	{
		_payloadlength = MAX_PAYLOAD_FSK;
		state = 1;
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("In FSK, payload length must be less than 60 bytes."));
			PRINTLN_SX1272();
		#endif
	}
	for(unsigned int i = 0; i < _payloadlength; i++)
	{
		packet_sent.data[i] = payload[i];	// Storing payload in packet structure
	}
	// set length with the actual counter value
    state = setPacketLength();	// Setting packet length in packet structure
	return state;
}

/*
 Function: It sets a packet struct in FIFO in order to send it.
 Returns:  Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::setPacket(uint8_t dest, char *payload)
{
	int8_t state = 2;
	byte st0;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setPacket'"));
	#endif

	// Save the previous status
	st0 = readRegister(REG_OP_MODE);
	// Initializing flags
	clearFlags();

	// Updating incorrect value
	_reception = CORRECT_PACKET;


	if (_retries == 0)
	{
		// Updating these values only if it is the first try
		// Setting destination in packet structure
		state = setDestination(dest);
		if( state == 0 )
		{
			state = setPayload(payload);
		}
	}
	else
	{
		state = setPacketLength();
		packet_sent.retry = _retries;
		#if (SX1272_debug_mode > 0)
			PRINT_SX1272(F("** Retrying to send last packet "));
			USB.print(_retries, DEC);
			USB.println(F(" time **"));
		#endif
	}

	// Setting address pointer in FIFO data buffer
	writeRegister(REG_FIFO_TX_BASE_ADDR, 0x00);
	writeRegister(REG_FIFO_ADDR_PTR, 0x00);
	if( state == 0 )
	{
		state = 1;
		// Writing packet to send in FIFO
		writeRegister(REG_FIFO, packet_sent.dst); 		// Writing the destination in FIFO
		writeRegister(REG_FIFO, packet_sent.src);		// Writing the source in FIFO
		writeRegister(REG_FIFO, packet_sent.packnum);	// Writing the packet number in FIFO
		writeRegister(REG_FIFO, packet_sent.length); 	// Writing the packet length in FIFO
		for( uint16_t i = 0; i < _payloadlength; i++)
		{
			writeRegister(REG_FIFO, packet_sent.data[i]);  // Writing the payload in FIFO
		}
		writeRegister(REG_FIFO, packet_sent.retry);		// Writing the number retry in FIFO
		state = 0;
		#if (SX1272_debug_mode > 0)
			PRINTLN_SX1272(F("## Packet set and written in FIFO ##"));
			// Print the complete packet if debug_mode
			PRINT_SX1272(F("## Packet to send: "));
			USB.printHex(packet_sent.dst);			 	// Printing destination
			USB.print("|");
			USB.printHex(packet_sent.src);			 	// Printing source
			USB.print("|");
			USB.printHex(packet_sent.packnum);			// Printing packet number
			USB.print("|");
			USB.printHex(packet_sent.length);			// Printing packet length
			USB.print("|");
			for( uint16_t i = 0; i < _payloadlength; i++)
			{
				USB.printHex(packet_sent.data[i]);		// Printing payload
				USB.print("|");
			}
			USB.printHex(packet_sent.retry);			// Printing retry number
			USB.println(F(" ##"));
		#endif
	}
	writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
	return state;
}

/*
 Function: It sets a packet struct in FIFO in order to sent it.
 Returns:  Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::setPacket(uint8_t dest, uint8_t *payload)
{
	int8_t state = 2;
	byte st0;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'setPacket'"));
	#endif

	st0 = readRegister(REG_OP_MODE);	// Save the previous status
	clearFlags();	// Initializing flags

	if( _modem == LORA )
	{ // LoRa mode
		writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);	// Stdby LoRa mode to write in FIFO
	}
	else
	{ // FSK mode
		writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);	// Stdby FSK mode to write in FIFO
	}

	_reception = CORRECT_PACKET;	// Updating incorrect value to send a packet (old or new)
	if(_retries == 0)
	{ // Sending new packet
		state = setDestination(dest);	// Setting destination in packet structure
		if( state == 0 )
		{
			state = setPayload(payload);
		}
	}
	else
	{
		state = setPacketLength();
		packet_sent.retry = _retries;
		#if (SX1272_debug_mode > 0)
			PRINT_SX1272(F("** Retrying to send last packet "));
			USB.print(_retries, DEC);
			USB.println(F(" time **"));
		#endif
	}
	writeRegister(REG_FIFO_TX_BASE_ADDR, 0x00);
	writeRegister(REG_FIFO_ADDR_PTR, 0x00);  // Setting address pointer in FIFO data buffer
	if( state == 0 )
	{
		state = 1;
		// Writing packet to send in FIFO
		writeRegister(REG_FIFO, packet_sent.dst); 		// Writing the destination in FIFO
		writeRegister(REG_FIFO, packet_sent.src);		// Writing the source in FIFO
		writeRegister(REG_FIFO, packet_sent.packnum);	// Writing the packet number in FIFO
		writeRegister(REG_FIFO, packet_sent.length); 	// Writing the packet length in FIFO
		for(unsigned int i = 0; i < _payloadlength; i++)
		{
			writeRegister(REG_FIFO, packet_sent.data[i]);  // Writing the payload in FIFO
		}
		writeRegister(REG_FIFO, packet_sent.retry);		// Writing the number retry in FIFO
		state = 0;
		#if (SX1272_debug_mode > 0)
			PRINTLN_SX1272(F("## Packet set and written in FIFO ##"));
			// Print the complete packet if debug_mode
			PRINT_SX1272(F("## Packet to send: "));
			USB.printHex(packet_sent.dst);			 	// Printing destination
			USB.print("|");
			USB.printHex(packet_sent.src);			 	// Printing source
			USB.print("|");
			USB.printHex(packet_sent.packnum);			// Printing packet number
			USB.print("|");
			USB.printHex(packet_sent.length);			// Printing packet length
			USB.print("|");
			for(unsigned int i = 0; i < _payloadlength; i++)
			{
				USB.printHex(packet_sent.data[i]);		// Printing payload
				USB.print("|");
			}
			USB.printHex(packet_sent.retry);			// Printing retry number
			USB.println(F(" ##"));
		#endif
	}
	writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
	return state;
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendWithMAXTimeout()
{
	return sendWithTimeout(MAX_TIMEOUT);
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendWithTimeout()
{
	setTimeout();
	return sendWithTimeout(_sendTime);
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendWithTimeout(uint32_t wait)
{
	uint8_t state = 2;
	byte value = 0x00;
	unsigned long previous;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendWithTimeout'"));
	#endif

	// wait to TxDone flag
	previous = millis();
	if( _modem == LORA )
	{
		/// LoRa mode
		// Initializing flags
		clearFlags();
		// LORA mode - Tx
		writeRegister(REG_OP_MODE, LORA_TX_MODE);

		value = readRegister(REG_IRQ_FLAGS);

		// Wait until the packet is sent (TX Done flag) or the timeout expires
		while ((bitRead(value, 3) == 0) && (millis() - previous < wait))
		{
			value = readRegister(REG_IRQ_FLAGS);
			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous )
			{
				previous = millis();
			}
		}
		state = 1;
	}
	else
	{
		/// FSK mode
		writeRegister(REG_OP_MODE, FSK_TX_MODE);  // FSK mode - Tx

		value = readRegister(REG_IRQ_FLAGS2);
		// Wait until the packet is sent (Packet Sent flag) or the timeout expires
		while ((bitRead(value, 3) == 0) && (millis() - previous < wait))
		{
			value = readRegister(REG_IRQ_FLAGS2);

			// Condition to avoid an overflow (DO NOT REMOVE)
			if( millis() < previous )
			{
				previous = millis();
			}
		}
		state = 1;
	}
	if( bitRead(value, 3) == 1 )
	{
		state = 0;	// Packet successfully sent
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("## Packet successfully sent ##"));
			PRINTLN_SX1272();
		#endif
	}
	else
	{
		if( state == 1 )
		{
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("** Timeout has expired **"));
				PRINTLN_SX1272();
			#endif
		}
		else
		{
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("** There has been an error and packet has not been sent **"));
				PRINTLN_SX1272();
			#endif
		}
	}

	// Initializing flags
	clearFlags();
	return state;
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketMAXTimeout(uint8_t dest, char *payload)
{
	return sendPacketTimeout(dest, payload, MAX_TIMEOUT);
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketMAXTimeout(	uint8_t dest,
											uint8_t *payload,
											uint16_t length16)
{
	return sendPacketTimeout(dest, payload, length16, MAX_TIMEOUT);
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeout(uint8_t dest, char *payload)
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeout'"));
	#endif

	// Setting a packet with 'dest' destination address, 'payload' data field
	// and writing it in FIFO.
	state = setPacket(dest, payload);
	if (state == 0)
	{
		state = sendWithTimeout();	// Sending the packet
	}
	return state;
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeout(	uint8_t dest,
										uint8_t *payload,
										uint16_t length16)
{
	uint8_t state = 2;
	uint8_t state_f = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeout'"));
	#endif

	state = truncPayload(length16);
	if( state == 0 )
	{
		state_f = setPacket(dest, payload);	// Setting a packet with 'dest' destination
	}												// and writing it in FIFO.
	else
	{
		state_f = state;
	}
	if( state_f == 0 )
	{
		state_f = sendWithTimeout();	// Sending the packet
	}
	return state_f;
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeout(uint8_t dest, char *payload, uint32_t wait)
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeout'"));
	#endif

	state = setPacket(dest, payload);	// Setting a packet with 'dest' destination
	if (state == 0)								// and writing it in FIFO.
	{
		state = sendWithTimeout(wait);	// Sending the packet
	}
	return state;
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeout(	uint8_t dest,
										uint8_t *payload,
										uint16_t length16,
										uint32_t wait)
{
	uint8_t state = 2;
	uint8_t state_f = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeout'"));
	#endif

	state = truncPayload(length16);
	if( state == 0 )
	{
		state_f = setPacket(dest, payload);	// Setting a packet with 'dest' destination
	}
	else
	{
		state_f = state;
	}
	if( state_f == 0 )								// and writing it in FIFO.
	{
		state_f = sendWithTimeout(wait);	// Sending the packet
	}
	return state_f;
}

/*
 Function: Configures the module to transmit information.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketMAXTimeoutACK(uint8_t dest, char *payload)
{
	return sendPacketTimeoutACK(dest, payload, MAX_TIMEOUT);
}

/*
 Function: Configures the module to transmit information and receive an ACK.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketMAXTimeoutACK(uint8_t dest,
											uint8_t *payload,
											uint16_t length16)
{
	return sendPacketTimeoutACK(dest, payload, length16, MAX_TIMEOUT);
}

/*
 Function: Configures the module to transmit information and receive an ACK.
 Returns: Integer that determines if there has been any error
   state = 9  --> The ACK lost (no data available)
   state = 8  --> The ACK lost
   state = 7  --> The ACK destination incorrectly received
   state = 6  --> The ACK source incorrectly received
   state = 5  --> The ACK number incorrectly received
   state = 4  --> The ACK length incorrectly received
   state = 3  --> N-ACK received
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeoutACK(uint8_t dest, char *payload)
{
	uint8_t state = 2;
	uint8_t state_f = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeoutACK'"));
	#endif

	state = sendPacketTimeout(dest, payload);	// Sending packet to 'dest' destination
	if( state == 0 )
	{
		state = receive();	// Setting Rx mode to wait an ACK
	}
	else
	{
		state_f = state;
	}
	if( state == 0 )
	{
		if( availableData() )
		{
			state_f = getACK();	// Getting ACK
		}
		else
		{
			state_f = 9;
		}
	}
	else
	{
		state_f = state;
	}

	return state_f;
}

/*
 Function: Configures the module to transmit information and receive an ACK.
 Returns: Integer that determines if there has been any error
   state = 9  --> The ACK lost (no data available)
   state = 8  --> The ACK lost
   state = 7  --> The ACK destination incorrectly received
   state = 6  --> The ACK source incorrectly received
   state = 5  --> The ACK number incorrectly received
   state = 4  --> The ACK length incorrectly received
   state = 3  --> N-ACK received
   state = 2  --> The ACK has not been received
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeoutACK(	uint8_t dest,
											uint8_t *payload,
											uint16_t length16)
{
	uint8_t state = 2;
	uint8_t state_f = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeoutACK'"));
	#endif

	// Sending packet to 'dest' destination
	state = sendPacketTimeout(dest, payload, length16);

	// Trying to receive the ACK
	if( state == 0 )
	{
		state = receive();	// Setting Rx mode to wait an ACK
	}
	else
	{
		state_f = state;
	}
	if( state == 0 )
	{
		if( availableData() )
		{
			state_f = getACK();	// Getting ACK
		}
		else
		{
			state_f = 9;
		}
	}
	else
	{
		state_f = state;
	}

	return state_f;
}

/*
 Function: Configures the module to transmit information and receive an ACK.
 Returns: Integer that determines if there has been any error
   state = 9  --> The ACK lost (no data available)
   state = 8  --> The ACK lost
   state = 7  --> The ACK destination incorrectly received
   state = 6  --> The ACK source incorrectly received
   state = 5  --> The ACK number incorrectly received
   state = 4  --> The ACK length incorrectly received
   state = 3  --> N-ACK received
   state = 2  --> The ACK has not been received
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeoutACK(	uint8_t dest,
											char *payload,
											uint32_t wait)
{
	uint8_t state = 2;
	uint8_t state_f = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeoutACK'"));
	#endif

	state = sendPacketTimeout(dest, payload, wait);	// Sending packet to 'dest' destination
	if( state == 0 )
	{
		state = receive();	// Setting Rx mode to wait an ACK
	}
	else
	{
		state_f = 1;
	}
	if( state == 0 )
	{
		if( availableData() )
		{
			state_f = getACK();	// Getting ACK
		}
		else
		{
			state_f = 9;
		}
	}
	else
	{
		state_f = 1;
	}

	return state_f;
}

/*
 Function: Configures the module to transmit information and receive an ACK.
 Returns: Integer that determines if there has been any error
   state = 9  --> The ACK lost (no data available)
   state = 8  --> The ACK lost
   state = 7  --> The ACK destination incorrectly received
   state = 6  --> The ACK source incorrectly received
   state = 5  --> The ACK number incorrectly received
   state = 4  --> The ACK length incorrectly received
   state = 3  --> N-ACK received
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeoutACK(	uint8_t dest,
											uint8_t *payload,
											uint16_t length16,
											uint32_t wait)
{
	uint8_t state = 2;
	uint8_t state_f = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeoutACK'"));
	#endif

	state = sendPacketTimeout(dest, payload, length16, wait);	// Sending packet to 'dest' destination
	if( state == 0 )
	{
		state = receive();	// Setting Rx mode to wait an ACK
	}
	else
	{
		state_f = 1;
	}
	if( state == 0 )
	{
		if( availableData() )
		{
			state_f = getACK();	// Getting ACK
		}
		else
		{
			state_f = 9;
		}
	}
	else
	{
		state_f = 1;
	}

	return state_f;
}

/*
 Function: It gets and stores an ACK if it is received.
 Returns:
*/
uint8_t WaspSX1272::getACK()
{
	return getACK(MAX_TIMEOUT);
}

/*
 Function: It gets and stores an ACK if it is received, before ending 'wait' time.
 Returns: Integer that determines if there has been any error
   state = 8  --> The ACK lost
   state = 7  --> The ACK destination incorrectly received
   state = 6  --> The ACK source incorrectly received
   state = 5  --> The ACK number incorrectly received
   state = 4  --> The ACK length incorrectly received
   state = 3  --> N-ACK received
   state = 2  --> The ACK has not been received
   state = 1  --> not used (reserved)
   state = 0  --> The ACK has been received with no errors
 Parameters:
   wait: time to wait while there is no a valid header received.
*/
uint8_t WaspSX1272::getACK(uint32_t wait)
{
	uint8_t state = 2;
	byte value = 0x00;
	unsigned long previous;
	boolean a_received = false;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getACK'"));
	#endif

    previous = millis();

	if( _modem == LORA )
	{ // LoRa mode
	    value = readRegister(REG_IRQ_FLAGS);
		// Wait until the ACK is received (RxDone flag) or the timeout expires
		while ((bitRead(value, 6) == 0) && (millis() - previous < wait))
		{
			value = readRegister(REG_IRQ_FLAGS);
			if( millis() < previous )
			{
				previous = millis();
			}
		}
		if( bitRead(value, 6) == 1 )
		{ // ACK received
			a_received = true;
		}
		// Standby para minimizar el consumo
		writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);	// Setting standby LoRa mode
	}
	else
	{ // FSK mode
		value = readRegister(REG_IRQ_FLAGS2);
		// Wait until the packet is received (RxDone flag) or the timeout expires
		while ((bitRead(value, 2) == 0) && (millis() - previous < wait))
		{
			value = readRegister(REG_IRQ_FLAGS2);
			if( millis() < previous )
			{
				previous = millis();
			}
		}
		if( bitRead(value, 2) == 1 )
		{ // ACK received
			a_received = true;
		}
		// Standby para minimizar el consumo
		writeRegister(REG_OP_MODE, FSK_STANDBY_MODE);	// Setting standby FSK mode
	}

	if( a_received )
	{
//----	writeRegister(REG_FIFO_ADDR_PTR, 0x00);  // Setting address pointer in FIFO data buffer
		// Storing the received ACK
		ACK.dst = _destination;
		ACK.src = readRegister(REG_FIFO);
		ACK.packnum = readRegister(REG_FIFO);
		ACK.length = readRegister(REG_FIFO);
		ACK.data[0] = readRegister(REG_FIFO);

		// Checking the received ACK
		if( ACK.dst == packet_sent.src )
		{
			if( ACK.src == packet_sent.dst )
			{
				if( ACK.packnum == packet_sent.packnum )
				{
					if( ACK.length == 0 )
					{
						if( ACK.data[0] == CORRECT_PACKET )
						{
							state = 0;
							#if (SX1272_debug_mode > 0)
							// Printing the received ACK
							PRINT_SX1272(F("## ACK received:"));
							USB.printHex(ACK.dst);
							USB.print("|");
							USB.printHex(ACK.src);
							USB.print("|");
							USB.printHex(ACK.packnum);
							USB.print("|");
							USB.printHex(ACK.length);
							USB.print("|");
							USB.printHex(ACK.data[0]);
							USB.println(F(" ##"));
							PRINTLN_SX1272();
							#endif
						}
						else
						{
							state = 3;
							#if (SX1272_debug_mode > 0)
								PRINTLN_SX1272(F("** N-ACK received **"));
								PRINTLN_SX1272();
							#endif
						}
					}
					else
					{
						state = 4;
						#if (SX1272_debug_mode > 0)
							PRINTLN_SX1272(F("** ACK length incorrectly received **"));
							PRINTLN_SX1272();
						#endif
					}
				}
				else
				{
					state = 5;
					#if (SX1272_debug_mode > 0)
						PRINTLN_SX1272(F("** ACK number incorrectly received **"));
						PRINTLN_SX1272();
					#endif
				}
			}
			else
			{
				state = 6;
				#if (SX1272_debug_mode > 0)
					PRINTLN_SX1272(F("** ACK source incorrectly received **"));
					PRINTLN_SX1272();
				#endif
			}
		}
		else
		{
			state = 7;
			#if (SX1272_debug_mode > 0)
				PRINTLN_SX1272(F("** ACK destination incorrectly received **"));
				PRINTLN_SX1272();
			#endif
		}
	}
	else
	{
		state = 8;
		#if (SX1272_debug_mode > 0)
			PRINTLN_SX1272(F("** ACK lost **"));
			PRINTLN_SX1272();
		#endif
	}
	clearFlags();	// Initializing flags
	return state;
}

/*
 Function: Configures the module to transmit information with retries in case of error.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketMAXTimeoutACKRetries(	uint8_t dest,
													char  *payload)
{
	return sendPacketTimeoutACKRetries(dest, payload, MAX_TIMEOUT);
}

/*
 Function: Configures the module to transmit information with retries in case of error.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketMAXTimeoutACKRetries(	uint8_t dest,
													uint8_t *payload,
													uint16_t length16)
{
	return sendPacketTimeoutACKRetries(dest, payload, length16, MAX_TIMEOUT);
}

/*
 Function: Configures the module to transmit information with retries in case of error.
 Returns: Integer that determines if there has been any error
   state = 9  --> The ACK lost (no data available)
   state = 8  --> The ACK lost
   state = 7  --> The ACK destination incorrectly received
   state = 6  --> The ACK source incorrectly received
   state = 5  --> The ACK number incorrectly received
   state = 4  --> The ACK length incorrectly received
   state = 3  --> N-ACK received
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeoutACKRetries(uint8_t dest, char *payload)
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeoutACKRetries'"));
	#endif

	// Sending packet to 'dest' destination and waiting an ACK response.
	state = 1;
	while( (state != 0) && (_retries <= _maxRetries) )
	{
		state = sendPacketTimeoutACK(dest, payload);
		_retries++;
	}
	_retries = 0;

	return state;
}

/*
 Function: Configures the module to transmit information with retries in case of error.
 Returns: Integer that determines if there has been any error
   state = 9  --> The ACK lost (no data available)
   state = 8  --> The ACK lost
   state = 7  --> The ACK destination incorrectly received
   state = 6  --> The ACK source incorrectly received
   state = 5  --> The ACK number incorrectly received
   state = 4  --> The ACK length incorrectly received
   state = 3  --> N-ACK received
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeoutACKRetries(uint8_t dest,
												uint8_t *payload,
												uint16_t length16)
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeoutACKRetries'"));
	#endif

	// Sending packet to 'dest' destination and waiting an ACK response.
	state = 1;
	while( (state != 0) && (_retries <= _maxRetries) )
	{
		state = sendPacketTimeoutACK(dest, payload, length16);
		_retries++;
	}
	_retries = 0;

	return state;
}

/*
 Function: Configures the module to transmit information with retries in case of error.
 Returns: Integer that determines if there has been any error
   state = 9  --> The ACK lost (no data available)
   state = 8  --> The ACK lost
   state = 7  --> The ACK destination incorrectly received
   state = 6  --> The ACK source incorrectly received
   state = 5  --> The ACK number incorrectly received
   state = 4  --> The ACK length incorrectly received
   state = 3  --> N-ACK received
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeoutACKRetries(uint8_t dest,
												char *payload,
												uint32_t wait)
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeoutACKRetries'"));
	#endif

	// Sending packet to 'dest' destination and waiting an ACK response.
	state = 1;
	while( (state != 0) && (_retries <= _maxRetries) )
	{
		state = sendPacketTimeoutACK(dest, payload, wait);
		_retries++;
	}
	_retries = 0;

	return state;
}

/*
 Function: Configures the module to transmit information with retries in case of error.
 Returns: Integer that determines if there has been any error
   state = 9  --> The ACK lost (no data available)
   state = 8  --> The ACK lost
   state = 7  --> The ACK destination incorrectly received
   state = 6  --> The ACK source incorrectly received
   state = 5  --> The ACK number incorrectly received
   state = 4  --> The ACK length incorrectly received
   state = 3  --> N-ACK received
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::sendPacketTimeoutACKRetries(uint8_t dest,
												uint8_t *payload,
												uint16_t length16,
												uint32_t wait)
{
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'sendPacketTimeoutACKRetries'"));
	#endif

	// Sending packet to 'dest' destination and waiting an ACK response.
	state = 1;
	while( (state != 0) && (_retries <= _maxRetries) )
	{
		state = sendPacketTimeoutACK(dest, payload, length16, wait);
		_retries++;
	}
	_retries = 0;

	return state;
}

/*
 Function: It gets the temperature from the measurement block module.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::getTemp()
{
	byte st0;
	uint8_t state = 2;

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272();
		PRINTLN_SX1272(F("Starting 'getTemp'"));
	#endif

	st0 = readRegister(REG_OP_MODE);	// Save the previous status

	if( _modem == LORA )
	{ // Allowing access to FSK registers while in LoRa standby mode
		writeRegister(REG_OP_MODE, LORA_STANDBY_FSK_REGS_MODE);
	}

	state = 1;
	// Saving temperature value
	_temp = readRegister(REG_TEMP);
	if( _temp & 0x80 ) // The SNR sign bit is 1
	{
		// Invert and divide by 4
		_temp = ( ( ~_temp + 1 ) & 0xFF );
    }
    else
    {
		// Divide by 4
		_temp = ( _temp & 0xFF );
	}


	#if (SX1272_debug_mode > 1)
		PRINT_SX1272(F("## Temperature is: "));
		USB.print(_temp);
		USB.println(F(" ##"));
		PRINTLN_SX1272();
	#endif

	if( _modem == LORA )
	{
		writeRegister(REG_OP_MODE, st0);	// Getting back to previous status
	}

	state = 0;
	return state;
}
/*
 Function: It prints a frame received in a packet.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
void WaspSX1272::showFramefromPacket()
{
	uint8_t length = 0;

	// begin UART0
	USB.secureBegin();

	for(int i = 0; i < 30; i++)
	{
		printByte('=',  0);
	}

	printByte('\r',  0);
	printByte('\n',  0);
	printString("Current ", 0);
	if (packet_received.data[3] == 0)
	{
		printString("BINARY", 0);
	}
	else
	{
		printString("ASCII", 0);
	}
	printString(" Frame:", 0);

	length = packet_received.length - OFFSET_PAYLOADLENGTH;
	printString("\r\nLength: ", 0);
	printIntegerInBase(length, 10, 0);

	printString("\r\nFrame Type (decimal): ", 0);
	printIntegerInBase(packet_received.data[3], 10, 0);


	printString("\r\nHEX: ", 0);
	for( int i = 0; i < length ; i++ )
	{
		puthex(packet_received.data[i], 0);
	}

	printString("\r\nString: ", 0);
	for( int i = 0; i < length ; i++ )
	{
		printByte(packet_received.data[i], 0);
	}
	printByte('\r',  0);
	printByte('\n',  0);

	for(int i = 0; i < 30; i++)
	{
		printByte('=',  0);
	}

	printByte('\r',  0);
	printByte('\n',  0);

	USB.secureEnd();

}
/*
 Function: It prints a frame received in a packet.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
void WaspSX1272::showReceivedPacket()
{
	uint8_t length = 0;

	// get payload length
	length = packet_received.length - OFFSET_PAYLOADLENGTH;

	// begin UART0
	USB.secureBegin();

	for(int i = 0; i < 30; i++)
	{
		printByte('=',  0);
	}

	printString("\r\ndest: ", 0);
	printIntegerInBase(packet_received.dst, 10, 0);
	printString("\r\nsrc: ", 0);
	printIntegerInBase(packet_received.src, 10, 0);
	printString("\r\npacknum: ", 0);
	printIntegerInBase(packet_received.packnum, 10, 0);
	printString("\r\nlength: ", 0);
	printIntegerInBase(packet_received.length, 10, 0);

	printString("\r\nretry: ", 0);
	printIntegerInBase(packet_received.retry, 10, 0);

	printString("\r\npayload (HEX): ", 0);
	for( int i = 0; i < length ; i++ )
	{
		puthex(packet_received.data[i], 0);
	}

	printString("\r\npayload (string): ", 0);
	for( int i = 0; i < length ; i++ )
	{
		printByte(packet_received.data[i], 0);
	}
	printByte('\r',  0);
	printByte('\n',  0);

	for(int i = 0; i < 30; i++)
	{
		printByte('=',  0);
	}
	printByte('\r',  0);
	printByte('\n',  0);

	USB.secureEnd();
}
/*
 Function: It prints the registers related to RX
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
void WaspSX1272::showRxRegisters()
{
	PRINTLN_SX1272(F("\n--- Show RX register ---"));

	// variable
	byte reg;

	for(int i = 0x00; i < 0x80; i++)
	{
		reg = readRegister(i);
		PRINT_SX1272(F("Reg 0x"));
		USB.printHex(i);
		USB.print(F(":"));
		USB.printHex(reg);
		USB.println();
		delay(100);
	}

	PRINTLN_SX1272(F("------------------------"));

}


#ifdef WASPMOTE_GATEWAY_FOR_MESHLIUM
/*
 Function: It prints a frame received in a packet to Meshlium.
 Returns: Integer that determines if there has been any error
   state = 2  --> The command has not been executed
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
 WARNING: This function mustn't be used with Waspmote.
*/
uint8_t WaspSX1272::showFramefromPacketMeshlium()
{
	uint8_t state = 2;
	uint8_t length = 0;
    length = packet_received.length - OFFSET_PAYLOADLENGTH;
	for( int i = 0; i < length ; i++ )
	{
		printByte(packet_received.data[i],0);
	}
	printString("\r\n",0);

	state = 0;
	return state;
}
#endif



/*
 Function: It sets the RTC settings with Meshlium timestamp configuration
 This function sends a special Frame to Meshlium (Meshlium's address must be
 '1'), and then Meshlium returns an answer with the timestamp. This function
 parses the info and sets the RTC Time and Date.
 Returns: Integer that determines if there has been any error
   state = 1  --> There has been an error while executing the command
   state = 0  --> The command has been executed with no errors
*/
uint8_t WaspSX1272::setRTCfromMeshlium()
{
	uint8_t length = 0;
	byte status;
	char buffer[100];
	char timestamp[30];
	int year, yearH;
	int month;
	int date;
	int hour;
	int minute;
	int second;
	uint8_t meshlium_address = 1;

	// clear buffer
	memset( buffer, 0x00, sizeof(buffer) );
	memset( timestamp, 0x00, sizeof(timestamp) );

	// Creating frame to send
	frame.createFrame(ASCII);
	frame.decrementSequence();
	frame.setFrameType(155);

	// Printing frame
	#if (SX1272_debug_mode > 1)
		frame.showFrame();
	#endif

	// Sending packet before ending a timeout
	status = sx1272.sendPacketTimeoutACK( meshlium_address, frame.buffer, frame.length );

	// check tx status
	if( status == 0 )
	{
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("packet sent OK"));
		#endif
	}
	else
	{
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("packet sent ERROR"));
		#endif
		return 1;
	}

	// wait to receive packet with Timestamp for several seconds
	status = receivePacketTimeoutACK(10000);

	// check rx status
	if( status == 0 )
	{
		#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272(F("Show packet received: "));
		showReceivedPacket();
		#endif

		// get payload length
		length = packet_received.length - OFFSET_PAYLOADLENGTH;

		// check if valid length then copy buffer
		if( length < sizeof(buffer) )
		{
			// copy payload
			memcpy( buffer, packet_received.data, length);

			#if (SX1272_debug_mode > 1)
				PRINT_SX1272(F("\nbuffer:"));
				USB.println(buffer);
			#endif
		}
		else
		{
			#if (SX1272_debug_mode > 1)
				PRINTLN_SX1272(F("ERROR: buffer not enough for length"));
				USB.print(F("length:"));
				USB.println(length, DEC);
			#endif
			return 1;
		}

		// get all data fields: "YYYYMMDDHHMMSS"
		sscanf( buffer,
				"%2u%2u%2u%2u%2u%2u%2u",
				&yearH,
				&year,
				&month,
				&date,
				&hour,
				&minute,
				&second );


		unsigned long offsetTime = (unsigned long)(timeOnAir(25) + timeOnAir(frame.length))/1000;
		unsigned long actualTime =  RTC.getEpochTime(year,
													month,
													date,
													hour,
													minute,
													second);

		unsigned long timeToSet = actualTime + offsetTime + 3; // add offset

		timestamp_t tm;

		// get time elements from epoch time
		RTC.breakTimeAbsolute( timeToSet, &tm );

		// create sentence to set Time
		snprintf( 	timestamp,
					sizeof(timestamp),
					"%02u:%02u:%02u:%02u:%02u:%02u:%02u",
					tm.year,
					tm.month,
					tm.date,
					RTC.dow(tm.year, tm.month, tm.date),
					tm.hour,
					tm.minute,
					tm.second	);

		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("\ntimestamp:"));
			USB.println(timestamp);
		#endif

		RTC.ON();
		RTC.setTime(timestamp);

		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("RTC time:"));
			USB.println(RTC.getTime());
		#endif
	}
	else
	{
		#if (SX1272_debug_mode > 1)
			PRINT_SX1272(F("Receiving packet TIMEOUT, state "));
			USB.println(status, DEC);
		#endif
		return 1;
	}

	return 0;
}


/*
 Function: It sets the CAD mode to search Channel Activity Detection
 Returns: Integer that determines if there has been any error
   state = true   --> Channel Activity Detected
   state = false  --> Channel Activity NOT Detected
*/
bool WaspSX1272::cadDetected()
{
	byte val = 0;

	// get actual time
	unsigned long time = millis();

	// set LNA
	sx1272.writeRegister(REG_LNA,0x23);
	sx1272.clearFlags();

    sx1272.getRSSI();

	#if (SX1272_debug_mode > 1)
		PRINT_SX1272(F("Inside CAD DETECTION -> RSSI: "));
		USB.println(sx1272._RSSI);
	#endif

	if( _modem == LORA )
	{
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("Set CAD mode"));
		#endif

		// Setting LoRa CAD mode
		sx1272.writeRegister(REG_OP_MODE,0x87);
	}

	// Wait for IRQ CadDone
    val = sx1272.readRegister(REG_IRQ_FLAGS);
    while((bitRead(val,2) == 0) && (millis()-time)<10000 )
    {
      val = sx1272.readRegister(REG_IRQ_FLAGS);
    }

	// After waiting or detecting CadDone
	// check 'CadDetected' bit in 'RegIrqFlags' register
    if(bitRead(val,0) == 1)
    {
		#if (SX1272_debug_mode > 1)
			PRINTLN_SX1272(F("CAD true"));
		#endif
		return true;
	}

	#if (SX1272_debug_mode > 1)
		PRINTLN_SX1272(F("CAD false"));
	#endif
	return false;

}



WaspSX1272	sx1272 = WaspSX1272();
