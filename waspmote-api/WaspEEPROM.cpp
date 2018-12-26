/*
 *  Based on library by Rob Tillaart
 *  URL: http://arduino.cc/playground/Main/LibraryForI2CEEPROM
 *  VERSION: 1.0.05
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
 *  Version:		3.2
 *  Design:			David Gascon
 *  Implementation:	Yuri Carmona
 */


#ifndef __WPROGRAM_H__
  #include "WaspClasses.h"
#endif

#include <WaspEEPROM.h>


WaspEEPROM::WaspEEPROM()
{
    _deviceAddress = I2C_ADDRESS_EEPROM;
    _lastWrite = 0;
    TWBR = 12;          // 12=400Khz  32=200  72=100 152=50    F_CPU/16+(2*TWBR)
}

uint8_t WaspEEPROM::ON()
{
	uint8_t error;
	
	// init I2C bus
	I2C.begin();
	
	error = waitReady();
	
	// check correct comm
	error = readJEDEC();
	
	if (error == 0)
	{		
		if ((_response[0] == 0x00) && (_response[1] == 0x1F))
		{
			return 0;
		}
		
		return 1;		
	}
	else
	{		
		// set default I2C address
		_deviceAddress = I2C_ADDRESS_EEPROM_DEFAULT;
		
		// generate new register value
		uint8_t new_reg_value = 0;
		new_reg_value = I2C_ADDRESS_EEPROM << 1;
		new_reg_value++;
		
		// set new I2C address
		eeprom.writeByte(0xF040, new_reg_value);
		
		// reset eeprom chip
		reset();
		
		// go back to current I2C address
		_deviceAddress = I2C_ADDRESS_EEPROM;
		return error;
	}	
	
	return error;
}

int WaspEEPROM::writeByte(uint16_t address, uint8_t data)
{
    int rv = _WriteBlock(address, &data, 1);
    return rv;
}

int WaspEEPROM::setBlock(uint16_t address, uint8_t data, uint16_t length)
{
    uint8_t buffer[I2C_TWIBUFFERSIZE];
    for (uint8_t i =0; i< I2C_TWIBUFFERSIZE; i++) buffer[i] = data;

    int rv = _pageBlock(address, buffer, length, false); // todo check return value..
    return rv;
}

int WaspEEPROM::writeBlock(uint16_t address, uint8_t* buffer, uint16_t length)
{
    int rv = _pageBlock(address, buffer, length, true); // todo check return value..
    return rv;
}

uint8_t WaspEEPROM::readByte(uint16_t address)
{
    uint8_t rdata;
    _ReadBlock(address, &rdata, 1);
    return rdata;
}

uint16_t WaspEEPROM::readBlock(uint16_t address, uint8_t* buffer, uint16_t length)
{
    uint16_t rv = 0;
    while (length > 0)
    {
        uint8_t cnt = min(length, I2C_TWIBUFFERSIZE);
        rv += _ReadBlock(address, buffer, cnt);
        address += cnt;
        buffer += cnt;
        length -= cnt;
    }
    return rv;
}

#ifdef I2C_EEPROM_EXTENDED
// returns 64, 32, 16, 8, 4, 2, 1, 0
// 0 is smaller than 1K
uint8_t WaspEEPROM::determineSize()
{
    uint8_t rv = 0;  // unknown
    uint8_t orgValues[8];
    uint16_t addr;

    // remember old values, non destructive
    for (uint8_t i=0; i<8; i++)
    {
        addr = (512 << i) + 1;
        orgValues[i] = readByte(addr);
    }

    // scan page folding
    for (uint8_t i=0; i<8; i++)
    {
        rv = i;
        uint16_t addr1 = (512 << i) + 1;
        uint16_t addr2 = (512 << (i+1)) + 1;
        writeByte(addr1, 0xAA);
        writeByte(addr2, 0x55);
        if (readByte(addr1) == 0x55) // folded!
        {
            break;
        }
    }

    // restore original values
    for (uint8_t i=0; i<8; i++)
    {
        uint16_t addr = (512 << i) + 1;
        writeByte(addr, orgValues[i]);
    }
    return 0x01 << (rv-1);
}
#endif

////////////////////////////////////////////////////////////////////
//
// PRIVATE
//

// _pageBlock aligns buffer to page boundaries for writing.
// and to TWI buffer size
// returns 0 = OK otherwise error
int WaspEEPROM::_pageBlock(uint16_t address, uint8_t* buffer, uint16_t length, bool incrBuffer)
{
    int rv = 0;
    while (length > 0)
    {
        uint8_t bytesUntilPageBoundary = I2C_EEPROM_PAGESIZE - address%I2C_EEPROM_PAGESIZE;
        uint8_t cnt = min(length, bytesUntilPageBoundary);
        cnt = min(cnt, I2C_TWIBUFFERSIZE);

        int rv = _WriteBlock(address, buffer, cnt); // todo check return value..
        if (rv != 0) return rv;

        address += cnt;
        if (incrBuffer) buffer += cnt;
        length -= cnt;
    }
    return rv;
}

// pre: length <= I2C_EEPROM_PAGESIZE  && length <= I2C_TWIBUFFERSIZE;
// returns 0 = OK otherwise error
int WaspEEPROM::_WriteBlock(uint16_t address, uint8_t* buffer, uint8_t length)
{
    waitReady();

    int rv = I2C.write(_deviceAddress,address,buffer,length);
    
    _lastWrite = millis();
    return rv;
}

// pre: buffer is large enough to hold length bytes
// returns bytes written
uint8_t WaspEEPROM::_ReadBlock(uint16_t address, uint8_t* buffer, uint8_t length)
{
    waitReady();
    
    int rv = I2C.read(_deviceAddress,address,buffer,length);
    
    return rv;
}



// pre: buffer is large enough to hold length bytes
// returns bytes written
uint8_t WaspEEPROM::readRegister(uint16_t address, uint8_t* buffer, uint8_t length)
{	
	// wait until chip is ready
    waitReady();    
    
    int rv = I2C.read(_deviceAddress,address,buffer,length);
    
    if (rv != 0) return 1;  // error

    return 0;
}





/*************************************************************
 *
 *
 *
 *
 *
 *
 *************************************************************/
uint8_t WaspEEPROM::sendCommand(uint8_t* command)
{
	int retries = 3;
	int x;
	uint8_t crc_tx[2];
	uint8_t crc_rx[2];
	uint8_t crc_aux[2];
	uint8_t length = command[0]-2;
	uint8_t rx_length = 16;
	uint16_t address = 0xFE00; // CMD REGISTER ADDRESS
	
	do
	{
		// calculate CRC
		aes132c_calculate_crc(length, command, crc_tx);

		// wait until chip is ready
		//~ waitReady();
		
		memset(_buffer,0x00,sizeof(_buffer));
		memset(_response,0x00,sizeof(_response));
		memcpy(_buffer,command,sizeof(_buffer));
		
		_buffer[length] = crc_tx[0];
		_buffer[length+1] = crc_tx[1];
		
		#if DEBUG_EEPROM > 0
			PRINT_EEPROM("Command: ");
			USB.printHexln(_buffer, length+2);
		#endif
		
		x = I2C.write(_deviceAddress,address,_buffer,length+2);
		
		
		if (x != 0)
		{
			#if DEBUG_EEPROM > 1
				PRINT_EEPROM(F("Error endTransmission\r\n"));	
			#endif
		}
		delay(100);
		retries--;
		if (retries == 0) return 1;
	}
	while(x != 0);

	// read response	
	x = I2C.read(_deviceAddress,_buffer,90);
	
	if (x != 0)
	{		
		return 1;
	}
	
	// Parse response
	uint8_t count = _buffer[0];
	uint8_t status = _buffer[1];
	
	#if DEBUG_EEPROM > 0
		PRINT_EEPROM("[EEPROM] Response count: ");
		USB.println(count, DEC);
		
		PRINT_EEPROM("[EEPROM] Response status: 0x");
		USB.printHex(status);
		USB.print(F(" => "));	
		
		switch (status)
		{
			case 0x00:
				USB.println(F("Success"));
				break;
			case 0x02:
				USB.println(F("BoundaryError"));
				break;
			case 0x04:
				USB.println(F("RWConfig"));
				break;
			case 0x08:
				USB.println(F("BadAddr"));
				break;
			case 0x10:
				USB.println(F("CountErr"));
				break;
			case 0x20:
				USB.println(F("NonceError"));
				break;
			case 0x40:
				USB.println(F("MacError"));
				break;
			case 0x50:
				USB.println(F("ParseError"));
				break;
			case 0x60:
				USB.println(F("DataMatch"));
				break;
			default:
				USB.println(F("Unknown"));			
		}
		USB.println();
	#endif
	
	_length = 0;	
	for (int i = 2; i < (count-2); i++)
	{
		_response[i-2] = _buffer[i];
		_length++;
	}
	crc_rx[0] = _buffer[count-2];
	crc_rx[1] = _buffer[count-1];
	
	// check crc
	aes132c_calculate_crc(count-2, _buffer, crc_aux);
		
	delay(10);
	
	if (memcmp( crc_rx, crc_aux, 2) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}






/*************************************************************
 *
 *
 *
 *
 *
 *
 *************************************************************/
uint8_t WaspEEPROM::sleepCommand()
{
	uint8_t crc[2];
	int x;
	uint8_t command[] = { 0x09, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8_t length = command[0]-2;
	uint16_t address = 0xFE00; // CMD REGISTER ADDRESS
	
	// calculate CRC
	aes132c_calculate_crc(length, command, crc);
	/*USB.printHex(crc[0]);
	USB.printHex(crc[1]);
	USB.println();*/
	
	memset(_buffer,0x00,sizeof(_buffer));
	memcpy(_buffer,command,sizeof(_buffer));
	
	_buffer[length] = crc[0];
	_buffer[length+1] = crc[1];
	
	x = I2C.write(_deviceAddress,address,_buffer,length+2);

	if (x != 0)
	{
		//USB.println("Error endTransmission_sleep");
		return 1;
	}
	delay(10);
	
	return 0;
}




/*
 * 
 * 
 * 
 * 
 */
uint8_t WaspEEPROM::waitReady()
{
	uint32_t I2C_WRITEDELAY = 5000;

    // Wait until EEPROM gives ACK again.
    // this is a bit faster than the hardcoded 5 milli
    while ((millis() - _lastWrite) <= I2C_WRITEDELAY)
    {
        int x = I2C.scan(_deviceAddress);
        if (x == 0) 
        {
			return 0;
		}
    }
    
    return 1;
}



/* readSerialNumber() - reads the Waspmote unique serial identifier from eeprom
 *
 * It reads the Waspmote unique serial identifier
 */
uint8_t WaspEEPROM::readSerialNumber()
{
	uint8_t error = 0;
	
	// define command
	uint8_t I2C_EEPROM_READ_SERIAL[] = {0x09, 0x10, 0x00, 0xF0, 0x00, 0x00, 0x08};
	
	error = eeprom.sendCommand(I2C_EEPROM_READ_SERIAL);

	return error;
}


/* 
 * 
 */
uint8_t WaspEEPROM::readJEDEC()
{
	uint8_t error = 0;
	
	// define command
	uint8_t I2C_EEPROM_READ_JEDEC[] = { 0x09, 0x10, 0x00, 0xF0, 0x10, 0x00, 0x02};
	
	error = eeprom.sendCommand(I2C_EEPROM_READ_JEDEC);

	return error;
}

/* 
 * 
 */
uint8_t WaspEEPROM::reset()
{
	uint8_t error = 0;
	
	// define command
	uint8_t I2C_EEPROM_RESET[] = { 0x09, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00};
	
	error = eeprom.sendCommand(I2C_EEPROM_RESET);

	return error;
}


/* 
 * 
 */
uint8_t WaspEEPROM::blockRead(uint16_t address, uint8_t length)
{
	uint8_t error = 0;
	
	// define command
	uint8_t I2C_EEPROM_BLOCK_READ[] = {0x09, 0x10, 0x00, 0xFF, 0xFF, 0x00, 0xFF};
	
	I2C_EEPROM_BLOCK_READ[3] = (address>>8) & 0xFF;
	I2C_EEPROM_BLOCK_READ[4] = address & 0xFF;
	I2C_EEPROM_BLOCK_READ[6] = length;	
	
	error = eeprom.sendCommand(I2C_EEPROM_BLOCK_READ);

	return error;
}


/* 
 * @brief Encrypt a 16-byte block of data using AES ECB legacy mode
 * @param uint8_t index: Index of the key memory map (from 0x00 to 0x0F)
 * @param uint8_t *data: Pointer to the plain text data to encrypt
 * @param uint8_t len: Length of the plain text data (max: 16 bytes)
 * @return
 * 	@arg '0' OK
 * 	@arg '1' error
 * 
 */
uint8_t WaspEEPROM::encryptBlock16(uint8_t index, uint8_t *data, uint8_t len)
{
  uint8_t error = 0;
  uint8_t i = 0;

  uint8_t command[1 + 1 + 1 + 2 + 2 + 16];
  memset(command, 0x00, sizeof(command));

  // define command
  command[i++] = 1 + 1 + 1 + 2 + 2 + 16 + 2; // Count
  command[i++] = 0x0F; // Opcode
  command[i++] = 0x00; // Mode
  command[i++] = 0x00; // Param1 Upper byte (LKeyID)
  command[i++] = index; // Param1 Lower byte (LKeyID)
  command[i++] = 0x00; // Param2 Upper byte (Zero)
  command[i++] = 0x00; // Param2 Upper byte (Zero)

  
  uint8_t length = len;
  if (length > 16) length = 16;

  for (uint8_t j = 0; j < length; j++)
  {
    command[i++] = data[j]; // Data
  }
  
  error = eeprom.sendCommand(command);

  return error;
}




/* 
 * @brief Encrypt a
 * @param uint8_t index: Index of the key memory map (from 0x00 to 0x0F)
 * @param uint8_t *data: Pointer to the plain text data to encrypt
 * @param uint8_t len: Length of the plain text data (max: 16 bytes)
 * @return
 * 	@arg '0' OK
 * 	@arg '1' error
 * 
 */
uint8_t WaspEEPROM::encrypt(uint8_t index, uint8_t *data, uint16_t length, uint8_t *encryptedData, uint16_t *encryptedLength)
{
	uint8_t error = 0;
		
	uint16_t aux = (length-1) / 16;
	uint16_t n_iterations;
	
	if (aux == 0)
	{
		n_iterations = 1;
	}
	else 
	{
		n_iterations = (aux*16+16)/16;
	}		

	// iterate through all 16-byte blocks of the original message
	// Examples: 
	// 	16-byte length requires 1 iteration
	// 	17-byte length requires 2 iterations 
	for (uint8_t i = 0; i < n_iterations; i++)
	{
		error = encryptBlock16(index, &data[i*16], 16);		

		if (error == 0)
		{
			// copy encrypted block to final buffer
			memcpy(&encryptedData[i*16], _response, 16);
			
			// update length
			*encryptedLength = i*16+16;
		}		
	}
	

	return error;
}




/* 
 * @brief Store the 16-byte encryption key in Key Memory map (from F200h to F2FFh)
 * @param uint8_t index: Index of the key memory map (from 0x00 to 0x0F)
 * @param uint8_t *key: Pointer to the key to save
 * @param uint8_t len: Length of the key (MUST BE 16)
 * @return
 * 	@arg '0' OK
 * 	@arg '1' bad key length
 * 	@arg '2' bad key index
 * 	@arg '3' error executing the command
 * 
 */
uint8_t WaspEEPROM::saveKey(uint8_t index, uint8_t *key, uint8_t len)
{
	uint8_t error;
	uint8_t length = len;
	
	// check key length
	if (length != 16) 
	{
		return 1;
	}
	
	// check key index (from 0 to 15)
	if (index > 15)
	{
		return 2;
	}
	
	// calculate key address
	uint16_t address = 0xF200 + index*0x10;
	
	error = eeprom.writeBlock(address, (uint8_t*)key, 16);
  
	if (error != 0)
	{
		return 3;
	}
	return 0;
}



/* 
 * @brief Set the KeyConfig register value
 * @param uint8_t index: Index of the key memory map (from 0x00 to 0x0F)
 * @param uint8_t *reg: Pointer to the 4 bytes which define the KeyConfig
 * @return 
 * 	@arg '0' OK
 * 	@arg 'x' error
 * 
 */
uint8_t WaspEEPROM::setKeyConfig(uint8_t index, uint8_t *reg)
{
  return eeprom.writeBlock(0xF080 + index*0x04, reg, 4);
}


/* 
 * @brief Show Configuration Memory Map (from F000h)
 * @return * 
 * 	@arg '0' OK
 * 	@arg 'x' error
 * 
 */
uint8_t WaspEEPROM::showConfigurationMemoryMap()
{
  uint8_t error = 0;

  // define command
  uint8_t command[] = {0x09, 0x10, 0x00, 0xF0, 0x00, 0x00, 0x08};
  
  USB.println(F("----------------------------------"));
  for (uint8_t i = 0; i < 26; i++)
  {
	command[4] = i*0x08;
  
    error = eeprom.sendCommand(command);    
    
    if (error == 0)
    {
	  USB.print(F("F0"));
	  USB.printHex(command[4]);
	  USB.print(F("h-F0"));
	  USB.printHex(command[4]+7);
	  USB.print(F("h ==> "));
	  USB.printHexln(&eeprom._response[0], 8);
    }  
  }
  
  USB.println(F("----------------------------------"));  
  
  return error;
}


WaspEEPROM eeprom = WaspEEPROM();


//
// END OF FILE
//
