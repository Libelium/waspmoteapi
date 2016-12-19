/*
 *  Based on library by Rob Tillaart
 *  URL: http://arduino.cc/playground/Main/LibraryForI2CEEPROM
 *  VERSION: 1.0.05
 * 
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
	if (!Wire.isON)
	{
		Wire.begin();
	}
	
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

    Wire.beginTransmission(_deviceAddress);
    Wire.send((int)(address >> 8));
    Wire.send((int)(address & 0xFF));
    for (uint8_t cnt = 0; cnt < length; cnt++)
    Wire.send(buffer[cnt]);
    int rv = Wire.endTransmission();
    _lastWrite = millis();
    return rv;
}

// pre: buffer is large enough to hold length bytes
// returns bytes written
uint8_t WaspEEPROM::_ReadBlock(uint16_t address, uint8_t* buffer, uint8_t length)
{
    waitReady();

    Wire.beginTransmission(_deviceAddress);
    Wire.send((int)(address >> 8));
    Wire.send((int)(address & 0xFF));

    int rv = Wire.endTransmission();
    if (rv != 0) return 0;  // error

    Wire.requestFrom(_deviceAddress, length);
    uint8_t cnt = 0;
    uint32_t before = millis();
    while ((cnt < length) && ((millis() - before) < I2C_EEPROM_TIMEOUT))
    {
        if (Wire.available()) buffer[cnt++] = Wire.receive();
    }
    return cnt;
}



// pre: buffer is large enough to hold length bytes
// returns bytes written
uint8_t WaspEEPROM::readRegister(uint16_t address, uint8_t* buffer, uint8_t length)
{	
	// wait until chip is ready
    waitReady();    

    Wire.beginTransmission(_deviceAddress);
    Wire.send((int)(address >> 8));
    Wire.send((int)(address & 0xFF));

    Wire.requestFrom(_deviceAddress, length);
    uint8_t cnt = 0;
    uint32_t before = millis();
    while ((cnt < length) && ((millis() - before) < I2C_EEPROM_TIMEOUT))
    {
        if (Wire.available()) buffer[cnt++] = Wire.receive();
    }

    uint8_t rv = Wire.endTransmission();
    delay(10);
    
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

	do
	{
		// calculate CRC
		aes132c_calculate_crc(length, command, crc_tx);

		// wait until chip is ready
		waitReady();

		Wire.beginTransmission(_deviceAddress);
		Wire.send(0xFE); // CMD REGISTER ADDRESS
		Wire.send(0x00);

		for (uint8_t i = 0; i<length; i++)
		{
			Wire.send(command[i]);  //COUNT  
		}
		Wire.send(crc_tx[0]);  //CRC 1
		Wire.send(crc_tx[1]);  //CRC 2
		x = Wire.endTransmission();
		if (x != 0)
		{
			//USB.println(F("Error endTransmission"));	
		}
		delay(100);
		retries--;
		if (retries == 0) return 1;
	}
	while(x != 0);

	// read response
	x = Wire.requestFrom(_deviceAddress, rx_length);
	if (x != 0)
	{		
		return 1;
	}
	
	// Store response
	uint16_t index = 0;
	while (Wire.available() && (index < sizeof(_buffer)))
	{
		_buffer[index] = Wire.receive();	
		index++; 
	}  

	// Stop transmission
	x = Wire.endTransmission();
	if (x != 0)
	{		
		return 1;
	}
	
	// Parse response
	uint8_t count = _buffer[0];
//~ 	uint8_t success = _buffer[1];	
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

	// calculate CRC
	aes132c_calculate_crc(length, command, crc);
	/*USB.printHex(crc[0]);
	USB.printHex(crc[1]);
	USB.println();*/
	Wire.beginTransmission(_deviceAddress);

	Wire.send(0xFE); // CMD REGISTER ADDRESS
	Wire.send(0x00);

	for (int x = 0; x<length; x++)
	{
		Wire.send(command[x]);
	}
	Wire.send(crc[0]);  //CRC 1
	Wire.send(crc[1]);  //CRC 2

	x = Wire.endTransmission();
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
        Wire.beginTransmission(_deviceAddress);
        int x = Wire.endTransmission();
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





WaspEEPROM eeprom = WaspEEPROM();


//
// END OF FILE
//
