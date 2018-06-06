/*! 
    Copyright (C) 2018 Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.
   
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
  
    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
    Version:		3.0
    Design:			David Gascon
    Implementation:	Yuri Carmona, Javier Siscart, Ahmad Saad, Victor Boria
*/
 
  
#ifndef WaspI2C_h
#define WaspI2C_h

#include "twi/twi_megarf.h"

/******************************************************************************
 * Definitions & Declarations
 ******************************************************************************/

//! DEBUG MODE
/*! 0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages 
 * \Remarks do not enable mode 2 unless SOCKET1 is used
 */
#define DEBUG_I2C 0

// define print MACRO
#define PRINT_I2C(str)		USB.print(F("[I2C] ")); USB.print(str);


#define I2C_ADDRESS_WASP_ACC			0x19
#define I2C_ADDRESS_WASP_RTC			0x68
#define I2C_ADDRESS_EVENTS_DIGIPOT1		0x28
#define I2C_ADDRESS_EVENTS_DIGIPOT2		0x2C
#define I2C_ADDRESS_EVENTS_DIGIPOT3		0x2A
#define I2C_ADDRESS_AGR_DENDROMETER		0x16
#define I2C_ADDRESS_AGR_PT1000			0x16
#define I2C_ADDRESS_AGR_RADIATION		0x14
#define I2C_ADDRESS_GASES_DIGIPOT1		0x2C
#define I2C_ADDRESS_GASES_DIGIPOT2		0x28
#define I2C_ADDRESS_GASES_DIGIPOT3		0x2E
#define I2C_ADDRESS_SENS_CITIES_DUST	0X2A
#define I2C_ADDRESS_CITIES_LD			0X28
#define I2C_ADDRESS_CITIES_AUDIO		0X2A
#define I2C_ADDRESS_CITIES_AUDIO_GAIN	0X2E
#define I2C_ADDRESS_CITIES_HUMIDITY		0X2F
#define I2C_ADDRESS_CITIES_TEMPERATURE	0X2C
#define I2C_ADDRESS_CITIES_ULTRA_5V		0X2F
#define I2C_ADDRESS_CITIES_ULTRA_3V3	0X2C
#define I2C_ADDRESS_CITIES_LDR			0X2C
#define I2C_ADDRESS_CITIES_CD			0X2C
#define I2C_ADDRESS_CITIES_CP			0X2C
#define I2C_ADDRESS_GASPRO_BME280		0x77
#define I2C_ADDRESS_GASPRO_LMP91000 	0x48
#define I2C_ADDRESS_GASPRO_MCP3421_A1	0x69
#define I2C_ADDRESS_GASPRO_MCP3421_A2	0x6A
#define I2C_ADDRESS_GASPRO_E2PROM		0x50
#define I2C_ADDRESS_GASPRO_MCP4146		0x2A
#define I2C_ADDRESS_EEPROM				0x55
#define I2C_ADDRESS_EEPROM_DEFAULT 		0x50
#define I2C_ADDRESS_TSL2561	 			0x39
#define I2C_ADDRESS_MB7040_MB1202		0x70
#define I2C_ADDRESS_GASES_SOCKET_1A_1B	0x28
#define I2C_ADDRESS_GASES_SOCKET_4		0x2A
#define I2C_ADDRESS_GASES_SOCKET_2A_2B	0x2C
#define I2C_ADDRESS_GASES_SOCKET_3_3B	0x2E



/******************************************************************************
 * Class
 ******************************************************************************/
 
class WaspI2C
{
private:

	bool _power_3v3_on;
	bool _slavePresent;
	
public:

	WaspI2C()
	{		
		
	};	

	void begin();
	void close();
	void secureBegin();
	void recover();
	
	uint8_t write(uint8_t devAddr, uint8_t regAddr, uint8_t data);
	uint8_t write(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t length);
	uint8_t write(uint8_t devAddr, uint16_t regAddr, uint8_t *data, uint16_t length);
	uint8_t writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t pos);
	uint8_t writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t pos, uint16_t length);
	uint8_t write(uint8_t devAddr, uint8_t *data, uint16_t length);
						
	uint8_t read(uint8_t devAddr, uint8_t regAddr, uint8_t *data_received, uint16_t size);
	uint8_t read(uint8_t devAddr, uint16_t regAddr, uint8_t *data_received, uint16_t size);
	uint8_t read(uint8_t devAddr, uint8_t *data_received, uint16_t size);
	uint8_t readBits(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t pos, uint8_t length);
	uint8_t readBit(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t pos);	

	uint8_t scan(uint8_t devAddr);
	uint8_t scanSlaves();
	
};

extern WaspI2C I2C;

#endif
