/*! \file WaspCAN.cpp
    \brief  Library for managing CAN Bus modules
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
 *  Version:			3.2
 *  Design:				David Gascon
 *  Implementation:		Luis Antonio Martin Nuez & Ahmad Saad
 */


#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif

#include "WaspCAN.h"


/***********************************************************************
 * Constructors
 ***********************************************************************/

WaspCAN::WaspCAN(void){}


/***********************************************************************
 * PUBLIC METHODS
 ***********************************************************************/

//!*************************************************************
//!	Name:	ON()
//!	Description: 	Initialization MCP2515
//!	Param : void
//!	Returns: "1" if no error, "0" if error
//!*************************************************************
bool WaspCAN::ON(uint16_t speed)
{

	#if (DEBUGMODE ==1 )
		PRINT_CAN(F("-- Constructor Can(uint16_t speed) --\n"));
	#endif

	//Active power Xbee
	PWR.powerSocket(SOCKET0, HIGH);
	SPI.isSocket0 = true;

	//SD CS configure
	pinMode(SD_SS,OUTPUT);
	digitalWrite(SD_SS,HIGH);

	//Initialization SPI
	SPI.begin();
	SPI.detachInterrupt();
	SPI.setBitOrder(MSBFIRST);
	// both mode 0 & 3 should work
	SPI.setDataMode(SPI_MODE0);

	//Set the SPI frequency
	SPI.setClockDivider(SPI_CLOCK_DIV4);

	#if (DEBUGMODE==1)
		PRINT_CAN(F("SPI configured\n"));
	#endif

	//Configure MCP2515 pins
	pinMode(CAN_CS,OUTPUT);
	pinMode(CAN_INT,INPUT);

	//Software resets MCP2515
	reset();
	delay(10);

	//After the reset enters configuration mode

	//Choose the rate of CAN-bus
	switch(speed){

    	case 1000:
		#if (DEBUGMODE==1)
			PRINT_CAN(F("Speed=1Mbps\n"));
		#endif
			digitalWrite(CAN_CS,LOW);
			SPI.transfer(SPI_WRITE);
			SPI.transfer(CNF3);
			SPI.transfer((1<<PHSEG21));
			SPI.transfer((1<<BTLMODE)|(1<<PHSEG11));
			digitalWrite(CAN_CS,HIGH);
      	break;

    	case 500:
		#if (DEBUGMODE==1)
			PRINT_CAN(F("Speed=500kps\n"));
		#endif
			digitalWrite(CAN_CS,LOW);
      		SPI.transfer(SPI_WRITE);
			SPI.transfer(CNF3);
			SPI.transfer((1<<PHSEG21));
			SPI.transfer((1<<BTLMODE)|(1<<PHSEG11));
			SPI.transfer((1<<BRP0));
			digitalWrite(CAN_CS,HIGH);
		break;

    	case 250:
		#if (DEBUGMODE==1)
			PRINT_CAN(F("Speed=250kps\n"));
		#endif
			digitalWrite(CAN_CS,LOW);
			SPI.transfer(SPI_WRITE);
			SPI.transfer(CNF3);
			SPI.transfer((1<<PHSEG20)|(1<<PHSEG22));
			SPI.transfer((1<<BTLMODE)|(1<<PHSEG12)|(1<<PHSEG11)|(1<<PHSEG10));
			SPI.transfer((1<<BRP0));
			digitalWrite(CAN_CS,HIGH);
		break;

		default:
		#if (DEBUGMODE==1)
			PRINT_CAN(F("The rate requested is unavailable, is set to 125 Kbit/s by default\n"));
		#endif
			digitalWrite(CAN_CS,LOW);
			SPI.transfer(SPI_WRITE);
			SPI.transfer(CNF3);
			SPI.transfer((1<<PHSEG21));
			SPI.transfer((1<<BTLMODE)|(1<<PHSEG11));
			SPI.transfer((1<<BRP2)|(1<<BRP1)|(1<<BRP0));
			digitalWrite(CAN_CS,HIGH);
		break;

  	}

	//Enable interrupts the Rx Buffer
	writeRegister(CANINTE,(1<<RX1IE)|(1<<RX0IE));

	//Filters and masks
  	//Bufer 0: All the messages and Rollover
  	writeRegister(RXB0CTRL,(1<<RXM1)|(1<<RXM0)|(1<<BUKT));

  	//Bufer 1: All the messages
	writeRegister(RXB1CTRL,(1<<RXM1)|(1<<RXM0));

	//All bits of the mask reception delete
 	writeRegister( RXM0SIDH, 0 );
 	writeRegister( RXM0SIDL, 0 );
 	writeRegister( RXM0EID8, 0 );
  	writeRegister( RXM0EID0, 0 );
 	writeRegister( RXM1SIDH, 0 );
    writeRegister( RXM1SIDL, 0 );
  	writeRegister( RXM1EID8, 0 );
  	writeRegister( RXM1EID0, 0 );

	//Disable pins RXnBF pins (high impedance state)
	writeRegister( BFPCTRL, 0 );

	//Set normal mode
	setMode(CAN_NORMAL_MODE);

	//Test its correct mode
	/*
	if (read_register(CANSTAT) != 0) {
		USB.println("Failed to initialize the MCP2515, normal mode not activated");
		return false;
	}*/

	#if (DEBUGMODE==1)
		PRINT_CAN(F("-- End Constructor Can(uint16_t speed) --\n"));
		USB.println();
	#endif

	return 1;
}


//!*************************************************************
//!	Name:	OFF()
//!	Description: 	Powers OFF the CAN Bus module
//!	Param : void
//!	Returns: void
//!*************************************************************
void WaspCAN::OFF(void )
{
	PWR.powerSocket(SOCKET0, LOW);
	SPI.isSocket0 = false;
	delay(100);
}


//!*************************************************************
//!	Name:	getMessage()
//!	Description: 	Take the CAN message
//!	Param : messageCAN *rec_msje: pointer to reception buffer
//!	Returns: "1" if no error, "0" if error
//!*************************************************************
char WaspCAN::getMessage(messageCAN *rec_msje)
{
	//Bought that buffer is the message
	char status = readStatus(SPI_RX_STATUS);
	char addr;
	static uint8_t previousBuffer;

	/*
		if (bit_is_set(status,6)) {
			//If the message is in the Buffer 1
			addr = SPI_READ_RX;
		}
		else if (bit_is_set(status,7))
		{
			//If the message is in the Buffer 2
			addr = SPI_READ_RX | 0x04;
		}
		else {
			// Error, the message is not available
			return 0;
	  }*/

	if ( (((status & 0b11000000)>>6)&0b00000011) >2 )
	{
		addr=SPI_READ_RX | (previousBuffer++ & 0x01)<<2;
		#if (DEBUGMODE==1)
			PRINT_CAN(F("Data in buffer available\n"));
		#endif
	}
	else if (bit_is_set(status,6))
	{
		addr = SPI_READ_RX;
		#if (DEBUGMODE==1)
			PRINT_CAN(F("Data in buffer 0\n"));
		#endif
	}
	else if (bit_is_set(status,7))
	{
		addr = SPI_READ_RX | 0x04;
		#if (DEBUGMODE==1)
			PRINT_CAN(F("Data in buffer 1\n"));
		#endif
	}
	else {
		// Error: no message available
		#if (DEBUGMODE==1)
			PRINT_CAN(F("No messages\n"));
		#endif

		return 0;
	}

	digitalWrite(CAN_CS,LOW);
	SPI.transfer(addr);

	//Read id
	rec_msje->id  = (unsigned int) SPI.transfer(0xff) << 3;   //Read the top
	rec_msje->id |=                  SPI.transfer(0xff) >> 5;   //Read the lower

	//Return the Extended ID
	SPI.transfer(0xff);
	SPI.transfer(0xff);

	//Read DLC
	char length = SPI.transfer(0xff) & 0x0f;

	rec_msje->header.length = length;
	rec_msje->header.rtr = (bit_is_set(status, 3)) ? 1 : 0;

	//Read data
	    for (char i=0;i<length;i++) {
			rec_msje->data[i] = SPI.transfer(0xFF);
	    }

	digitalWrite(CAN_CS,HIGH);

	//Delete the interruptions flags
	    if (bit_is_set(status, 6)) {
			bitModify(CANINTF, (1<<RX0IF), 0);
		}
		else {
			bitModify(CANINTF, (1<<RX1IF), 0);
		}

	return status;
}



//!*************************************************************
//!	Name:	sendMessage()
//!	Description: 	Send the CAN message
//!	Param: messageCAN *send_msje: pointer to transmission buffer
//!	Returns: "1" if no error, "0" if error
//!*************************************************************
char WaspCAN::sendMessage(messageCAN *send_msje)
{
	char status = readStatus(SPI_READ_STATUS);

	/* Status char:
	 *
	 * Bit	Funcion
	 *  2	TXB0CNTRL.TXREQ
	 *  4	TXB1CNTRL.TXREQ
	 *  6	TXB2CNTRL.TXREQ
	 */

	char address;

	if (bit_is_clear(status, 2)) {
		address = 0x00;
	} else if (bit_is_clear(status, 4)) {
		address = 0x02;
	} else if (bit_is_clear(status, 6)) {
		address = 0x04;
	} else {
		//All buffers are used can not send messages (returns 0)
		return 0;
	}

	digitalWrite(CAN_CS,LOW);
	SPI.transfer(SPI_WRITE_TX | address);
	//First, send the top ID10....ID3
	SPI.transfer(send_msje->id >> 3);
	//After sending the lower ID2....ID0
	SPI.transfer(send_msje->id << 5);

	//As we will not use the Extended ID you set it to 0
	SPI.transfer(0);
	SPI.transfer(0);

	char length = send_msje->header.length & 0x0F;

		if (send_msje->header.rtr) {
			SPI.transfer((1<<RTR) | length);
		} else {
		//Send the message length
			SPI.transfer(length);
		//Send data
			for (char i=0;i<length;i++) {
				SPI.transfer(send_msje->data[i]);
			}
		}

	digitalWrite(CAN_CS,HIGH);

	//Send message
	digitalWrite(CAN_CS,LOW);
	address = (address == 0) ? 1 : address;
	SPI.transfer(SPI_RTS | address);
	digitalWrite(CAN_CS,HIGH);

	return address;
}


//!*************************************************************
//!	Name:	printMessage()
//!	Description: 	CAN message print out the serial port
//!	Param : messageCAN *msje: pointer to the message
//!	Returns: "1" if no error, "0" if error
//!*************************************************************
void WaspCAN::printMessage(messageCAN *msje)
{
	USB.print(F("  id: "));
	USB.print(CAN.messageRx.id,HEX);
	USB.print(F("  rtr: "));
	USB.print(CAN.messageRx.header.rtr,HEX);
	USB.print(F(" => "));

	if (!msje->header.rtr) {
		//Data
		USB.print(F(" data:  "));
		USB.print(CAN.messageRx.data[0],HEX); USB.print(",");
		USB.print(CAN.messageRx.data[1],HEX); USB.print(",");
		USB.print(CAN.messageRx.data[2],HEX); USB.print(",");
		USB.print(CAN.messageRx.data[3],HEX); USB.print(",");
		USB.print(CAN.messageRx.data[4],HEX); USB.print(",");
		USB.print(CAN.messageRx.data[5],HEX); USB.print(",");
		USB.print(CAN.messageRx.data[6],HEX); USB.print(",");
		USB.println(CAN.messageRx.data[7],HEX);
	}
}


//!*************************************************************
//!	Name:	setMode()
//!	Description: 	Configure the MCP2515
//!	Param : uint8_t mode: The work mode
//!	Returns: void
//!*************************************************************
void WaspCAN::setMode(uint8_t mode)
{
	uint8_t mode_register = 0;

	if (mode == CAN_LISTEN_ONLY_MODE) {
		mode_register = (0<<REQOP2)|(1<<REQOP1)|(1<<REQOP0);
	}
	else if (mode == CAN_LOOPBACK_MODE) {
		mode_register = (0<<REQOP2)|(1<<REQOP1)|(0<<REQOP0);
	}
	else if (mode == CAN_SLEEP_MODE) {
		mode_register = (0<<REQOP2)|(0<<REQOP1)|(1<<REQOP0);
	}
	else if (mode == CAN_NORMAL_MODE) {
		mode_register = (0<<REQOP2)|(0<<REQOP1)|(0<<REQOP0);
	}

	//Set the new mode
	bitModify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), mode_register);

	//Wait until the mode has been changed
	while ((readRegister(CANSTAT) & 0xe0) != mode_register) {

	}
}


//!*************************************************************
//!	Name:	messageAvailable()
//!	Description: 	Check if there is any message
//!	Param : void
//!	Returns: 1 if available, 0 if not.
//!*************************************************************
uint8_t WaspCAN::messageAvailable(void)
{
	char status = readStatus(SPI_RX_STATUS);

	if ( (((status & 0b11000000)>>6)&0b00000011) >2 )
	{
		return 1;
	} else if (bit_is_set(status,6))  {
		return 1;
	} else if (bit_is_set(status,7)) {
		return 1;
	} else  {
		return 0;

		#if (DEBUGMODE==1)
			PRINT_CAN(F("No data available\n"));
		#endif
	}
}

//**********************************************************************
// Standars PIDs
//**********************************************************************


//!*************************************************************
//!	Name:	getEngineLoad()
//!	Description: 	Calculated engine load value
//!	Param : void
//!	Returns: unsigned int: engine load value (0-100)
//!*************************************************************
unsigned int WaspCAN::getEngineLoad()
{
	unsigned int data;

	CiARequest(CALC_ENGINE_LOAD);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  uint16_t(CAN.messageRx.data[3] * 100)  / 255;

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;
}


//!*************************************************************
//!	Name:	getEngineCoolantTemp()
//!	Description: 	Engine coolant temperature
//!	Param : void
//!	Returns: Engine coolant temperature(-40 - 215)
//!*************************************************************
unsigned int WaspCAN::getEngineCoolantTemp()
{
	unsigned int data;

	CiARequest(ENGINE_COOLANT_TEMP);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  uint16_t(CAN.messageRx.data[3] - 40);

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;
}


//!*************************************************************
//!	Name:	getFuelPressure()
//!	Description: 	Fuel pressure
//!	Param : void
//!	Returns: uint16_t: Fuel pressure (0 - 765 Kpa)
//!*************************************************************
uint16_t WaspCAN::getFuelPressure()
{
	uint16_t data;

	CiARequest(FUEL_PRESSURE);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  uint16_t(CAN.messageRx.data[3] * 3) ;

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;
}


//!*************************************************************
//!	Name:	getIntakeMAPressure()
//!	Description: 	Intake manifold absolute pressure
//!	Param : void
//!	Returns: uint16_t: absolute pressure 	(0 - 255 Kpa)
//!*************************************************************
uint16_t WaspCAN::getIntakeMAPressure()
{
	uint16_t data;

	CiARequest(INTAKE_M_A_PRESSURE);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  CAN.messageRx.data[3];

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;


}


//!*************************************************************
//!	Name:	getEngineRPM()
//!	Description: 	Engine RPM
//!	Param : void
//!	Returns: uint16_t: Engine RPM (0 - 16,383 RPM)
//!*************************************************************
uint16_t WaspCAN::getEngineRPM()
{

	uint16_t data;

	CiARequest(ENGINE_RPM);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  (uint16_t(CAN.messageRx.data[3]*256) + CAN.messageRx.data[4])/4;

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;
}


//!*************************************************************
//!	Name:	getVehicleSpeed()
//!	Description: 	Vehicle speed
//!	Param : void
//!	Returns: unsigned int: Vehicle speed (0 - 255)
//!*************************************************************
uint16_t WaspCAN::getVehicleSpeed()
{
	uint16_t data;

	CiARequest(VEHICLE_SPEED);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  uint16_t(CAN.messageRx.data[3]);

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;

}


//!*************************************************************
//!	Name:	getTimingAdvance()
//!	Description: 	Timing advance
//!	Param : void
//!	Returns: unsigned int: Time (-64 - 63.5)
//!*************************************************************
uint16_t WaspCAN::getTimingAdvance()
{
	uint16_t data;

	CiARequest(TIMING_ADVANCE);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  uint16_t(CAN.messageRx.data[3] / 2- 64);

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;
}

//!*************************************************************
//!	Name:	getIntankeAirTemp()
//!	Description: 	Intake air temperature
//!	Param : void
//!	Returns: uint8_t: Intake air temperature(-40 - 215)
//!*************************************************************
uint16_t WaspCAN::getIntankeAirTemp()
{
	uint16_t data;

	CiARequest(INTAKE_AIR_TEMP);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  uint16_t(CAN.messageRx.data[3] - 40);

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;
}


//!*************************************************************
//!	Name:	getMAFairFlowRate()
//!	Description: 	MAF air flow rate
//!	Param : void
//!	Returns: uint8_t: air flow rate	(0 - 655.35 g/s)
//!*************************************************************
uint16_t WaspCAN::getMAFairFlowRate()
{
	uint16_t data;

	CiARequest(MAF_AIR_FLOW_RATE);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  ( uint16_t(CAN.messageRx.data[3] * 256) + CAN.messageRx.data[4]) / 100;

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;
}


//!*************************************************************
//!	Name:	getThrottlePosition()
//!	Description: 	Throttle position
//!	Param : void
//!	Returns: uint8_t: Throttle position	(0 - 100%)
//!*************************************************************
uint8_t WaspCAN::getThrottlePosition()
{
	uint16_t data;

	CiARequest(THROTTLE_POSITION);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  uint16_t(CAN.messageRx.data[3] * 100) / 255;

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return (uint8_t)data;
}


//!*************************************************************
//!	Name:	getFuelLevel()
//!	Description: 	Fuel Level Input
//!	Param : void
//!	Returns: uint8_t: Fuel Level Input (0 - 100%)
//!*************************************************************
uint8_t WaspCAN::getFuelLevel()
{
	uint16_t data;

	CiARequest(FUEL_LEVEL);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  uint16_t(CAN.messageRx.data[3] * 100)  / 255;

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return (uint8_t)data;

}


//!*************************************************************
//!	Name:	getBarometricPressure()
//!	Description: 	Barometric pressure
//!	Param : void
//!	Returns: uint8_t: Barometric pressure (0 - 255 Kpa)
//!*************************************************************
uint8_t WaspCAN::getBarometricPressure()
{
	uint16_t data;

	CiARequest(BAROMETRIC_PRESSURE);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data =  uint16_t(CAN.messageRx.data[3]);

		#if (DEBUGMODE == 1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return (uint8_t)data;
}


//!*************************************************************
//!	Name:	getEngineFuelRate()
//!	Description: 	Engine fuel rate
//!	Param : void
//!	Returns: unsigned int: Engine fuel rate	 (0 - 3212 L/h)
//!*************************************************************
uint16_t WaspCAN::getEngineFuelRate()
{
	uint16_t data;

	CiARequest(ENGINE_FUEL_RATE);

	if (CAN.messageRx.id==ID_RESPONSE) {
		data = uint16_t((CAN.messageRx.data[3] * 256) + CAN.messageRx.data[4]) * 0.05;

		#if (DEBUGMODE==1)
      PRINT_CAN(F(""));
			CAN.printMessage(&CAN.messageRx);
		#endif
	}

	return data;
}


/***********************************************************************
                          CAN in Automation (CiA)
 ***********************************************************************/

//Request information through OBD
void WaspCAN::CiARequest(uint8_t PID)
{
	CAN.messageTx.id = ID_QUERY;
	CAN.messageTx.header.rtr = 0;
	CAN.messageTx.header.length = 8;
	CAN.messageTx.data[0]= 0x02;
	CAN.messageTx.data[1]= 0x01;
	CAN.messageTx.data[2]= PID;


	CAN.sendMessage(&CAN.messageTx);
	delay(5);

	if (CAN.messageAvailable()) {
		//Read the message buffers
		CAN.getMessage(&CAN.messageRx);
	}

}


/***********************************************************************
 * PRIVATE METHODS
 ***********************************************************************/

//Write a MCP2515 register
void WaspCAN::writeRegister( char direction, char data )
{
	//CS low to select the MCP2515
	digitalWrite(CAN_CS,LOW);

	SPI.transfer(SPI_WRITE);
	SPI.transfer(direction);
	SPI.transfer(data);

	//CS line again to release
	digitalWrite(CAN_CS,HIGH);
}


//**********************************************************************

//Read a MCP2515 register
char WaspCAN::readRegister(char direction)
{
	char data;

	//CS low to select the MCP2515
	digitalWrite(CAN_CS,LOW);

	SPI.transfer(SPI_READ);
	SPI.transfer(direction);
	//Read data SPI
	data = SPI.transfer(0xff);

	//CS line again to release
	digitalWrite(CAN_CS,HIGH);

	return data;
}


//***********************************************************************

//Modify a bit of the MCP2515 registers
void WaspCAN::bitModify(char direction, char mask, char data)
{
	//CS low to select the MCP2515
	digitalWrite(CAN_CS,LOW);

	SPI.transfer(SPI_BIT_MODIFY);
	SPI.transfer(direction);
	SPI.transfer(mask);
	SPI.transfer(data);

	//CS line again to release
	digitalWrite(CAN_CS,HIGH);
}


//***********************************************************************

//Check the status of the MCP2515 registers (SPI_RX_STATUS / SPI_READ_STATUS)
char WaspCAN::readStatus(char type)
{
	char data;

	//CS low to select the MCP2515
	digitalWrite(CAN_CS,LOW);

	SPI.transfer(type);
	//Read data SPI
	data = SPI.transfer(0xFF);

	//CS line again to release
	digitalWrite(CAN_CS,HIGH);

	return data;
}


//***********************************************************************

//Check if the buffers are empty
bool WaspCAN::checkFreeBuffer(void)
{
	char status = readStatus(SPI_READ_STATUS);


	if ((status & 0x54) == 0x54)
	{
		//All buffers used
		return false;
	}

	return true;
}


//***********************************************************************

//Reset MCP2515
void WaspCAN::reset(void)
{
	//CS low to select the MCP2515
	digitalWrite(CAN_CS,LOW);
	SPI.transfer(SPI_RESET);
	//CS line again to release
	digitalWrite(CAN_CS,HIGH);

	//Wait a bit to be stabilized after the reset MCP2515
	delay(10);

	#if (DEBUGMODE==1)
		PRINT_CAN(F("The MCP2515 has been successfully reset, configuration mode activated\n"));
	#endif
}


/***********************************************************************
 * Preinstantiate Objects
 ***********************************************************************/

WaspCAN CAN = WaspCAN();
