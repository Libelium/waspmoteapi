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

#ifndef I2C_EEPROM_H
#define I2C_EEPROM_H


#include <inttypes.h>
#include <Wire.h>
#include <eeprom_utilities/aes132_comm.h>


// I2C_EEPROM_PAGESIZE must be multiple of 2 e.g. 16, 32 or 64
// 24LC256 -> 64 bytes
#define I2C_EEPROM_PAGESIZE 64

// TWI buffer needs max 2 bytes for address
#define I2C_TWIBUFFERSIZE  30

// to break blocking read/write
#define I2C_EEPROM_TIMEOUT  1000

// comment next line to keep lib small
#define I2C_EEPROM_EXTENDED

// define registers
#define EEPROM_STATUS_REGISTER	0xFFF0


class WaspEEPROM
{
public:
    WaspEEPROM();
    
    uint8_t _buffer[32];
	uint8_t _response[32];
	uint8_t _length;

	uint8_t ON();
    int writeByte(uint16_t address, uint8_t value);
    int writeBlock(uint16_t address, uint8_t* buffer, uint16_t length);
    int setBlock(uint16_t address, uint8_t value, uint16_t length);

    uint8_t readByte(uint16_t address);
    uint16_t readBlock(uint16_t address, uint8_t* buffer, uint16_t length);

#ifdef I2C_EEPROM_EXTENDED
    uint8_t determineSize();
#endif
    uint8_t readRegister(uint16_t address, uint8_t* buffer, uint8_t length);
	uint8_t sendCommand(uint8_t* command);
	uint8_t sleepCommand();
	uint8_t readSerialNumber();
	uint8_t blockRead(uint16_t address, uint8_t length);
	uint8_t readJEDEC();
	uint8_t reset();

private:
    uint8_t _deviceAddress;
    uint32_t _lastWrite;  // for waitReady
   
    int _pageBlock(uint16_t address, uint8_t* buffer, uint16_t length, bool incrBuffer);
    int _WriteBlock(uint16_t address, uint8_t* buffer, uint8_t length);
    uint8_t _ReadBlock(uint16_t address, uint8_t* buffer, uint8_t length);

    uint8_t waitReady();
};

extern WaspEEPROM eeprom;


#endif
// END OF FILE
