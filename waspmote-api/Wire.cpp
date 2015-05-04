/*
 *  Modified for Waspmote by Libelium, 2009-2015
 *
 *  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
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
 */
 
extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "twi.h"
}

//#include "Wire.h"

#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif

// Initialize Class Variables //////////////////////////////////////////////////

uint8_t TwoWire::rxBuffer[BUFFER_LENGTH] = {0};
uint8_t TwoWire::rxBufferIndex = 0;
uint8_t TwoWire::rxBufferLength = 0;

uint8_t TwoWire::txAddress = 0;
uint8_t TwoWire::txBuffer[BUFFER_LENGTH] = {0};
uint8_t TwoWire::txBufferIndex = 0;
uint8_t TwoWire::txBufferLength = 0;

uint8_t TwoWire::transmitting = 0;
void (*TwoWire::user_onRequest)(void);
void (*TwoWire::user_onReceive)(int);

// Constructors ////////////////////////////////////////////////////////////////

TwoWire::TwoWire()
{
	// init flags
	isBoard = false;
	_5V_ON  = false;
	_3V3_ON = false;
	
	readTimeout = I2C_TIMEOUT;
}

// Public Methods //////////////////////////////////////////////////////////////

void TwoWire::begin(void)
{
	// init buffer for reads
	memset( rxBuffer, 0x00, BUFFER_LENGTH);
	rxBufferIndex = 0;
	rxBufferLength = 0;

	// init buffer for writes
	memset( txBuffer, 0x00, BUFFER_LENGTH); 
	txBufferIndex = 0;
	txBufferLength = 0;

	twi_init();
  
	// update flag
	I2C_ON = 1;
	
	delayMicroseconds(4);	
}

void TwoWire::begin(uint8_t address)
{
	twi_setAddress(address);
	twi_attachSlaveTxEvent(onRequestService);
	twi_attachSlaveRxEvent(onReceiveService);
	begin();
}

void TwoWire::begin(int address)
{
  begin((uint8_t)address);
}


/* 
 * name: requestFrom
 * It attempts to become twi bus master and read a series of bytes from a device 
 * on the bus
 * @param address: 7bit i2c device address
 * @param quantity: number of bytes to read into array
 * @return '0' ok, '1' length too long for buffer
 * 
 */
uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
	// Secure I2C power management
	Wire.secureBegin();
	
	// clamp to buffer length
	if(quantity > BUFFER_LENGTH)
	{
		quantity = BUFFER_LENGTH;
	}
	
	// perform blocking read into buffer
	uint8_t ret = twi_readFrom(address, rxBuffer, quantity);
	
	// set rx buffer iterator vars
	rxBufferIndex = 0;
	rxBufferLength = quantity;
	
	// Secure I2C power management
	Wire.secureEnd();
	
	return ret;
}

// Same as above but with types conversion
uint8_t TwoWire::requestFrom(int address, int quantity)
{
	return requestFrom((uint8_t)address, (uint8_t)quantity);
}



void TwoWire::beginTransmission(uint8_t address)
{
  // indicate that we are transmitting
  transmitting = 1;
  // set address of targeted slave
  txAddress = address;
  // reset tx buffer iterator vars
  txBufferIndex = 0;
  txBufferLength = 0;
}

void TwoWire::beginTransmission(int address)
{
  beginTransmission((uint8_t)address);
}

uint8_t TwoWire::endTransmission(void)
{
	// Secure I2C power management
	Wire.secureBegin();
	
	// transmit buffer (blocking)
	uint8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, 1);
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
	// indicate that we are done transmitting
	transmitting = 0;
	
	// Secure I2C power management
	Wire.secureEnd();
	
	return ret;
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(uint8_t data)
{
	if(transmitting)
	{
		// in master transmitter mode
		// don't bother if buffer is full
		if(txBufferLength >= BUFFER_LENGTH)
		{
			return;
		}
		// put byte in tx buffer
		txBuffer[txBufferIndex] = data;
		++txBufferIndex;
		// update amount in buffer   
		txBufferLength = txBufferIndex;
	}
	else
	{	
		// Secure I2C power management
		Wire.secureBegin();
		
		// in slave send mode
		// reply to master
		twi_transmit(&data, 1);
		
		// Secure I2C power management
		Wire.secureEnd();
	}
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(uint8_t* data, uint8_t quantity)
{
	if(transmitting)
	{
		// in master transmitter mode
		for(uint8_t i = 0; i < quantity; ++i)
		{
			send(data[i]);
		}
	}
	else
	{
		// Secure I2C power management
		Wire.secureBegin();
	
		// in slave send mode
		// reply to master
		twi_transmit(data, quantity);
			
		// Secure I2C power management
		Wire.secureEnd();
	}
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(char* data)
{
  send((uint8_t*)data, strlen(data));
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(int data)
{
  send((uint8_t)data);
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
uint8_t TwoWire::available(void)
{
  return rxBufferLength - rxBufferIndex;
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
uint8_t TwoWire::receive(void)
{
  // default to returning null char
  // for people using with char strings
  uint8_t value = '\0';
  
  // get each successive byte on each call
  if(rxBufferIndex < rxBufferLength){
    value = rxBuffer[rxBufferIndex];
    ++rxBufferIndex;
  }

  return value;
}

// behind the scenes function that is called when data is received
void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes)
{
  // don't bother if user hasn't registered a callback
  if(!user_onReceive){
    return;
  }
  // don't bother if rx buffer is in use by a master requestFrom() op
  // i know this drops data, but it allows for slight stupidity
  // meaning, they may not have read all the master requestFrom() data yet
  if(rxBufferIndex < rxBufferLength){
    return;
  }
  // copy twi rx buffer into local read buffer
  // this enables new reads to happen in parallel
  for(uint8_t i = 0; i < numBytes; ++i){
    rxBuffer[i] = inBytes[i];    
  }
  // set rx iterator vars
  rxBufferIndex = 0;
  rxBufferLength = numBytes;
  // alert user program
  user_onReceive(numBytes);
}

// behind the scenes function that is called when data is requested
void TwoWire::onRequestService(void)
{
  // don't bother if user hasn't registered a callback
  if(!user_onRequest){
    return;
  }
  // reset tx buffer iterator vars
  // !!! this will kill any pending pre-master sendTo() activity
  txBufferIndex = 0;
  txBufferLength = 0;
  // alert user program
  user_onRequest();
}

// sets function called on slave write
void TwoWire::onReceive( void (*function)(int) )
{
  user_onReceive = function;
}

// sets function called on slave read
void TwoWire::onRequest( void (*function)(void) )
{
  user_onRequest = function;
}

void TwoWire::close()
{
	twi_close();
	I2C_ON = 0;
}




/******************************************************************************* 
 * secureBegin() - It makes sure all I2C slaves are switched on when they
 * have been plugged to Waspmote. 
 *
 ******************************************************************************/
void TwoWire::secureBegin()
{		
	// Get the 5V and 3V3 power supply state to be set again if necessary
	_5V_ON  = WaspRegister & REG_5V;
	_3V3_ON = WaspRegister & REG_3V3;	
	
	// this codeblock belongs to the performance of the I2C bus
	// check if any Sensor Board (with I2C components) is ON before using I2C
	if( (WaspRegister & REG_METERING) 		||
		(WaspRegister & REG_AGRICULTURE)	||
		(WaspRegister & REG_GASES) 			||
		(WaspRegister & REG_EVENTS) 		||
		(WaspRegister & REG_CITIES_V14) 	||
		(WaspRegister & REG_CITIES_V15) 	||
		(WaspRegister & REG_PROTOTYPING) )
	{
		if( Wire.isBoard == false )
		{			
			// It is necessary to switch on the power supply if the Sensor Board is 
			// connected to Waspmote so as not to cause intereferences in the I2C bus
			PWR.setSensorPower(SENS_3V3, SENS_ON);
			PWR.setSensorPower(SENS_5V, SENS_ON);
		}
	}		
}



/******************************************************************************* 
 * secureEnd() - It makes sure all I2C slaves are swichted off when they
 * have been plugged to Waspmote and they were off prior to the I2C 
 * operation. 
 *
 ******************************************************************************/
void TwoWire::secureEnd()
{		
	// this codeblock belongs to the performance of the I2C bus
	// check if any Sensor Board (with I2C components) is ON before using I2C
	if( (WaspRegister & REG_METERING) 		||
		(WaspRegister & REG_AGRICULTURE)	||
		(WaspRegister & REG_GASES) 			||
		(WaspRegister & REG_EVENTS) 		||
		(WaspRegister & REG_CITIES_V14) 	||
		(WaspRegister & REG_CITIES_V15) 	||
		(WaspRegister & REG_PROTOTYPING) )
	{
		// this codeblock belongs to the performance of the SD card
		// switch off the SX module if it was not powered on 
		if( (Wire.isBoard == false) )
		{
			// switch OFF sensor boards to previous state before 'secureBegin'
			PWR.setSensorPower(SENS_3V3, SENS_OFF);
			PWR.setSensorPower(SENS_5V, SENS_OFF);
		}
		else
		{
			// if sensor board were switched off without doing OFF from their 
			// class function, then it is necessary to do it manually:
			// set power supply lines to previous state before 'secureBegin'
			if( _3V3_ON == false )
			{
				PWR.setSensorPower(SENS_3V3, SENS_OFF);
			}
			
			if( _5V_ON == false )
			{
				PWR.setSensorPower(SENS_5V, SENS_OFF);
			}
		}
		
		
	}	
}

/* Function: 	This function writes a bit via I2C
 * Parameters:	devAddr: I2C address of the device
 *				regAddr: I2C register
 *				data: data to send
 *				pos: position of the bit to write [7|6|5|4|3|2|1|0]
 * Return: 		1 if OK, -1 if error
 * 				
 */
int8_t TwoWire::writeBit(uint8_t devAddr, uint8_t regAddr, bool data, uint8_t pos)
{
	uint8_t buffer;
	uint8_t mask;
	uint8_t error;
	

	// Read the register
	error = readBytes(devAddr, regAddr, &buffer, 1);
	if (error != 1)
	{
		return error;
	}
	

	#ifdef I2C_DEBUG_FULL		
		USB.print(F("Bit pos: "));
		USB.println(pos, DEC);	
		USB.print("Old value: ");
		USB.println(buffer, BIN);
	#endif
	// Mask to the read data and stores the value
	mask = ~(1 << pos);
	data = (data << pos) & mask;
	buffer &= mask;	
	buffer |= data;
	
	#ifdef I2C_DEBUG_FULL
		USB.print("mask: ");
		USB.println(mask, BIN);
		USB.print("data: ");
		USB.println(data, BIN);
		USB.print("New value: ");
		USB.println(buffer, BIN);
	#endif
	
	// Write the register
	writeBytes(devAddr, regAddr, &buffer, 1);
	if (error != 1)
	{
		return error;
	}	
	
	return 1;
}

/* Function: 	This function writes some bits via I2C
 * Parameters:	devAddr: I2C address of the device
 *				regAddr: I2C register
 *				data: data to send
 *				pos: first position of the bits to write starting by the LSb [7|6|5|4|3|2|1|0]
 *				length: number of bits to write
 * Return: 		1 if OK, -1 if error
 */
int8_t TwoWire::writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t pos, uint8_t length)
{
	uint8_t buffer;
	uint8_t mask;
	uint8_t error;
	
	// Read the register
	error = readBytes(devAddr, regAddr, &buffer, 1);
	if (error != 1)
	{
		return error;
	}	
	
	#ifdef I2C_DEBUG_FULL		
		USB.print(F("Bit pos: "));
		USB.println(pos, DEC);		
		USB.print(F("Bit length: "));
		USB.println(length, DEC);	
		USB.print("Old value: ");
		USB.println(buffer, BIN);
	#endif
	
	// Mask to the read data and stores the value
	mask = (((1 << length) - 1) << pos);
	data = (data << pos) & mask;
	buffer &= ~mask;	
	buffer |= data;
	
	#ifdef I2C_DEBUG_FULL
		USB.print("mask: ");
		USB.println(mask, BIN);
		USB.print("data: ");
		USB.println(data, BIN);
		USB.print("New value: ");
		USB.println(buffer, BIN);
	#endif
	        
	// Write the register
	writeBytes(devAddr, regAddr, &buffer, 1);
	if (error != 1)
	{
		return error;
	}	
	
	return 1;
}

/* Function: 	This function writes bytes via I2C
 * Parameters:	devAddr: I2C address of the device
 *				regAddr: I2C register
 *				data: data to send
 *				length: number of bytes to send
 * Return: 		Nothing
 */
void TwoWire::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t length)
{	
    
	#ifdef I2C_DEBUG
        USB.print(F("I2C (0x"));
        USB.printHex(devAddr);
        USB.print(F(") writing "));
        USB.print(length, DEC);
        USB.print(F(" bytes to 0x"));
        USB.printHex(regAddr);
        USB.print(F("..."));
    #endif
	
	// Inits I2C bus
	if( !Wire.I2C_ON ) Wire.begin();
    
    for (uint8_t k = 0; k < length; k += min(length, BUFFER_LENGTH))
    {
        Wire.beginTransmission(devAddr);
        Wire.send(regAddr + k);   
		
        for (uint8_t i = 0; i < length; i++) {
            Wire.send( data[i]);
			#ifdef I2C_DEBUG
                USB.printHex(data[i]);
                if (i + 1 < length)
                {
					USB.print(F(" "));
				}
			#endif
        }        
		Wire.endTransmission();
    }	

	#ifdef I2C_DEBUG
        USB.println(F(". Done"));
    #endif
}

/* Function: 	This function reads a bit via I2C
 * Parameters:	devAddr: I2C address of the device
 *				regAddr: I2C register
 *				data: buffer to store the data
 *				pos: position of the bit to read [7|6|5|4|3|2|1|0]
 * Return: 		Bytes read, -1 if error
 */
int8_t TwoWire::readBit(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t pos)
{
	uint8_t buffer, mask;
	int8_t answer;
	
	answer = readBytes( devAddr, regAddr, &buffer, 1);
	
	#ifdef I2C_DEBUG_FULL		
		USB.print(F("Bit pos: "));
		USB.println(pos, DEC);
		USB.print("Old value: ");
		USB.println(buffer, BIN);
	#endif
	
	mask = 1 << pos;	
	if ((mask & buffer) != 0)
	{
		data[0] = 1;
	}
	else
	{
		data[0] = 0;
		
	}
	
	#ifdef I2C_DEBUG_FULL
		USB.print("mask: ");
		USB.println(mask, BIN);
		USB.print("New value: ");
		USB.println(data[0], BIN);
	#endif
	
	return answer;	
}

/* Function: 	This function reads a bit via I2C
 * Parameters:	devAddr: I2C address of the device
 *				regAddr: I2C register
 *				data: buffer to store the data
 *				pos: position of the bit to read starting by the LSb  [7|6|5|4|3|2|1|0]
 * Return: 		Bytes read, -1 if error
 */
int8_t TwoWire::readBits(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t pos, uint8_t length)
{
	uint8_t buffer, mask;
	int8_t answer;
	

	answer = readBytes( devAddr, regAddr, &buffer, 1);	
	
	#ifdef I2C_DEBUG_FULL		
		USB.print(F("Bit pos: "));
		USB.println(pos, DEC);		
		USB.print(F("Bit length: "));
		USB.println(length, DEC);	
		USB.print("Old value: ");
		USB.println(buffer, BIN);
	#endif
	
	// Mask to the read data and stores the value
	buffer = buffer >> pos;
	mask = ((1 << length) - 1);
	buffer &= mask;
	data[0] = buffer;	
	
	#ifdef I2C_DEBUG_FULL
		USB.print("mask: ");
		USB.println(mask, BIN);
		USB.print("New value: ");
		USB.println(buffer, BIN);
	#endif
	
	return answer;	
}

/* Function: 	This function reads bytes via I2C
 * Parameters:	devAddr: I2C address of the device
 *				regAddr: I2C register
 *				data: buffer to store the data
 *				length: number of bytes to read
 * Return: 		Bytes read, -1 if error
 */
int8_t TwoWire::readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t length)
{
    
	#ifdef I2C_DEBUG
        USB.print(F("I2C (0x"));
        USB.printHex(devAddr);
        USB.print(F(") reading "));
        USB.print(length, DEC);
        USB.print(F(" bytes from 0x"));
        USB.printHex(regAddr);
        USB.print(F("..."));
    #endif

    int8_t count = 0;
    uint32_t t1;

    // Inits I2C bus
	if( !Wire.I2C_ON ) Wire.begin();
    
    for (uint8_t k = 0; k < length; k += min(length, BUFFER_LENGTH))
    {
        Wire.beginTransmission(devAddr);
        Wire.send(regAddr + k);
        Wire.endTransmission();
		t1 = millis();
        Wire.requestFrom(devAddr, (uint8_t)min(length - k, BUFFER_LENGTH));
        
		
        for (; Wire.available() && ((readTimeout == 0) || (millis() - t1) < readTimeout); count++)
        {
            data[count] = Wire.receive();
            #ifdef I2C_DEBUG
                USB.printHex(data[count]);
                if (count + 1 < length)
                {
					USB.print(F(" "));
				}
			#endif
        }        
		Wire.endTransmission();
    }


    // check for timeout
    if ((readTimeout > 0) && ((millis() - t1) >= readTimeout) && (count < length))
    {
		count = -1; // timeout
	}

	#ifdef I2C_DEBUG
        USB.print(F(". Done ("));
        USB.print(count, DEC);
        USB.println(F(" read)."));
    #endif

    return count;
}



// Preinstantiate Objects //////////////////////////////////////////////////////

TwoWire Wire = TwoWire();

