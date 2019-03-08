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
  
    Version:		3.1
    Design:			David Gascon
    Implementation:	Yuri Carmona, Javier Siscart, Ahmad Saad, Victor Boria
*/
  
extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
  #include "twi/twi_megarf.h"
}

#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif

#include "WaspI2C.h"


/*!
 * 
 * @brief	This function starts the I2C bus	
 * @return	void
 * 
 */
void WaspI2C::begin()
{	
	/* TWI master initialization options. */
	twi_master_options_t opt;
	
	opt.speed = TWI_SPEED_HZ;
	//opt.chip  = devAddr;
	opt.baud_reg = TWI_CLOCK_RATE(F_CPU, opt.speed);
	
	/* Initialize the TWI master driver. */
	twi_master_init(&TWBR,&opt);
}



/*!
 * 
 * @brief	This function shuts down the I2C bus	
 * @return	void
 * 
 */
void WaspI2C::close()
{	
	//~ cli();
	
	//~ // de-activate internal pull-up resistors: SDA and SCL pins set to '0'
	//~ cbi(PORTD, 0); 
	//~ cbi(PORTD, 1);	
	
	//~ // set pre-scaler bits to 64 prescaler value
	//~ sbi(TWSR, TWPS0);
	//~ sbi(TWSR, TWPS1);
	
	//~ // disable twi module, acks, and twi interrupt
	//~ sbi(TWCR,TWINT);
	//~ sbi(TWCR,TWSTO);
	//~ cbi(TWCR,TWEA);
	//~ cbi(TWCR,TWSTA);
	//~ cbi(TWCR,TWWC);
	//~ // switch off TWI depending on wether a sensor board is plugged or not
	//~ if (WaspRegisterSensor & REG_PROTOTYPING)
	//~ {
		//~ cbi(TWCR,TWEN);
	//~ }
	//~ else
	//~ {
		//~ sbi(TWCR,TWEN);
	//~ }
	//~ cbi(TWCR,TWIE);
	//~ sbi(PRR0,PRTWI);
	
	
	//~ sei();	
}



/*!
 * 
 * @brief	This function writes 1 Byte of data to a 1-Byte register
 * @param	uint8_t devAddr: Slave address
 * @param	uint8_t regAddr: Register address
 * @param	uint8_t data: Byte to write
 * @return	enum status_code
 * 
 */
uint8_t WaspI2C::write(uint8_t devAddr, 
						uint8_t regAddr, 
						uint8_t data)
{
	return write(devAddr, regAddr, &data, 1);
}


/*!
 * 
 * @brief	This function writes data to a slave (1-Byte register address is indicated)
 * @param	uint8_t devAddr: Slave address
 * @param	uint8_t regAddr: Register address
 * @param	uint8_t *data: Pointer to buffer of data to write
 * @param	uint16_t length: Number of bytes to write
 * @return	enum status_code
 * 
 */
uint8_t WaspI2C::write(uint8_t devAddr, 
						uint8_t regAddr, 
						uint8_t *data, 
						uint16_t length)
{
	uint8_t error;
	twi_package_t packet;
	
	packet.addr[0]      = regAddr; 			/* TWI slave memory address data */
	packet.addr_length  = TWI_SLAVE_ONE_BYTE_SIZE; 	/* TWI slave memory address data size */
	packet.chip         = (devAddr << 1); 	/* TWI slave bus address */
	packet.buffer       = data; 			/* transfer data source buffer */
	packet.length       = length;			/* transfer data size (bytes) */

	/* Perform a multi-byte write access then check the result. */
	I2C.secureBegin();

	error = twi_master_write(&TWBR, &packet);

	return error;	
}
	
	
/*!
 * 
 * @brief	This function writes data to a slave (2-Byte register address is indicated)
 * @param	uint8_t devAddr: Slave address
 * @param	uint16_t regAddr: Register address
 * @param	uint8_t *data: Pointer to buffer of data to write
 * @param	uint16_t length: Number of bytes to write
 * @return	enum status_code
 * 
 */
uint8_t WaspI2C::write(uint8_t devAddr, 
						uint16_t regAddr, 
						uint8_t *data, 
						uint16_t length)
{
	uint8_t error;
	twi_package_t packet;
	
	packet.addr[0]      = (regAddr >> 8) & 0xFF; 	/* TWI slave memory address data */
	packet.addr[1]      = regAddr & 0xFF; 			/* TWI slave memory address data */
	packet.addr_length  = TWI_SLAVE_TWO_BYTE_SIZE; 	/* TWI slave memory address data size */
	packet.chip         = (devAddr << 1); 	/* TWI slave bus address */
	packet.buffer       = data; 			/* transfer data source buffer */
	packet.length       = length;			/* transfer data size (bytes) */

	/* Perform a multi-byte write access then check the result. */
	I2C.secureBegin();

	error = twi_master_write(&TWBR, &packet);

	return error;
}
	
	
	
/*!
 * 
 * @brief	This function writes data to a slave (No register address is indicated)
 * @param	uint8_t devAddr: Slave address
 * @param	uint8_t *data: Pointer to buffer of data to write
 * @param	uint16_t length: Number of bytes to write
 * @return	enum status_code
 * 
 */
uint8_t WaspI2C::write(uint8_t devAddr, 
						uint8_t *data, 
						uint16_t length)
{
	uint8_t error;
	twi_package_t packet;
	
	packet.addr[0]      = 0x00; 	/* TWI slave memory address data */
	packet.addr_length  = TWI_SLAVE_NO_INTERNAL_ADDRESS; 	/* TWI slave memory address data size */
	packet.chip         = (devAddr << 1); 	/* TWI slave bus address */
	packet.buffer       = data; 			/* transfer data source buffer */
	packet.length       = length;			/* transfer data size (bytes) */

	/* Perform a multi-byte write access then check the result. */
	I2C.secureBegin();
	
	error = twi_master_write(&TWBR, &packet);
		
	return error;
}

	
/*!
 * 
 * @brief	This function reads data from a slave (1-Byte register address is indicated)
 * @param	uint8_t devAddr: Slave address
 * @param	uint8_t regAddr: Register address
 * @param	uint8_t *data_received: Pointer to buffer where data is stored
 * @param	uint16_t size: Number of bytes to read
 * @return	enum status_code
 * 
 */
uint8_t WaspI2C::read(uint8_t devAddr, 
						uint8_t regAddr, 
						uint8_t *data_received, 
						uint16_t size)
{	
	uint8_t error;
	twi_package_t packet_received;
	
	packet_received.addr[0]      = regAddr; 			/* TWI slave memory address data */
	packet_received.addr_length  = TWI_SLAVE_ONE_BYTE_SIZE; 	/* TWI slave memory address data size */
	packet_received.chip         = (devAddr << 1); 		/* TWI slave bus address */
	packet_received.buffer       = data_received; 	/* transfer data destination buffer */
	packet_received.length       = size; 			/* transfer data size (bytes) */

	/* Perform a multi-byte read access then check the result. */
	I2C.secureBegin();
	error = twi_master_read(&TWBR,&packet_received);
	
	return error;
	
}



/*!
 * 
 * @brief	This function reads data from a slave (2-Byte register address is indicated)
 * @param	uint8_t devAddr: Slave address
 * @param	uint16_t regAddr: Register address
 * @param	uint8_t *data_received: Pointer to buffer where data is stored
 * @param	uint16_t size: Number of bytes to read
 * @return	enum status_code
 * 
 */
uint8_t WaspI2C::read(uint8_t devAddr, 
						uint16_t regAddr, 
						uint8_t *data_received, 
						uint16_t size)
{	
	uint8_t error;
	twi_package_t packet_received;
	
	packet_received.addr[0]      = (regAddr >> 8) & 0xFF; 	/* TWI slave memory address data */
	packet_received.addr[1]      = regAddr & 0xFF; 			/* TWI slave memory address data */
	packet_received.addr_length  = TWI_SLAVE_TWO_BYTE_SIZE; 	/* TWI slave memory address data size */
	packet_received.chip         = (devAddr << 1); 		/* TWI slave bus address */
	packet_received.buffer       = data_received; 	/* transfer data destination buffer */
	packet_received.length       = size; 			/* transfer data size (bytes) */

	/* Perform a multi-byte read access then check the result. */
	I2C.secureBegin();
	error = twi_master_read(&TWBR,&packet_received);
	
	return error;
	
}


/*!
 * 
 * @brief	This function reads data from a slave (no register address is needed)
 * @param	uint8_t devAddr: Slave address 
 * @param	uint8_t *data_received: Pointer to buffer where data is stored
 * @param	uint16_t size: Number of bytes to read
 * @return	enum status_code
 * 
 */
uint8_t WaspI2C::read(uint8_t devAddr, 
						uint8_t *data_received, 
						uint16_t size)
{	
	uint8_t error;
	twi_package_t packet_received;
	
	packet_received.addr[0]      = 0x00; 	/* TWI slave memory address data */
	packet_received.addr_length  = TWI_SLAVE_NO_INTERNAL_ADDRESS; 	/* TWI slave memory address data size */
	packet_received.chip         = (devAddr << 1); 		/* TWI slave bus address */
	packet_received.buffer       = data_received; 	/* transfer data destination buffer */
	packet_received.length       = size; 			/* transfer data size (bytes) */

	/* Perform a multi-byte read access then check the result. */
	I2C.secureBegin();
	error = twi_master_read(&TWBR,&packet_received);
	
	return error;
	
}



/*!
 * 
 * @brief	This function scans for a specific slave address presence in the bus
 * @param	uint8_t devAddr: Slave address
 * @return 	enum status_code
 * 
 */
uint8_t WaspI2C::scan(uint8_t devAddr)
{	
	uint8_t error;
	twi_package_t packet_received;
	uint8_t buffer[10];
	
	packet_received.addr[0]      = 0x00; 		/* TWI slave memory address data */
	packet_received.addr_length  = TWI_SLAVE_NO_INTERNAL_ADDRESS; 	/* TWI slave memory address data size */
	packet_received.chip         = (devAddr << 1); 		/* TWI slave bus address */
	packet_received.buffer       = buffer; 	/* transfer data destination buffer */
	packet_received.length       = 1; 		/* transfer data size (bytes) */

	/* Perform a multi-byte read access then check the result. */
	I2C.secureBegin();
	error = twi_master_read(&TWBR,&packet_received);
	
	return error;
	
}



/*!
 * 
 * @brief	This function write a specific bit in a register	
 * @param	uint8_t devAddr: Slave address
 * @param	uint8_t regAddr: Register address
 * @param	uint8_t data: Bit value to write: '1' or '0'
 * @param	uint8_t pos: Bit position in register
 * @return enum status_code
 * 
 */
uint8_t WaspI2C::writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t data, uint8_t pos)
{
	uint8_t buffer;
	uint8_t mask;
	uint8_t status;

	// Read the register
	status = read(devAddr, regAddr, &buffer, 1);

	// Mask to the read data and stores the value
	mask = ~(1 << pos);
	data = (data << pos);
	buffer &= mask;
	buffer |= data;

	// Write the register
	status = write(devAddr, regAddr, &buffer, 1);

	return status;
}


/*!
 * 
 * @brief		
 * @param	
 * @return 	enum status_code
 * 
 */
uint8_t WaspI2C::writeBits(uint8_t devAddr, 
							uint8_t regAddr, 
							uint8_t data,
							uint8_t pos, 
							uint16_t length)
{
	uint8_t buffer;
	uint8_t mask;
	uint8_t error;
	
	// Not needed 
	//I2C.secureBegin();
	
	// Read the register
	error = read(devAddr, regAddr, &buffer, 1);
	if (error != 0)
	{
		return error;
	}	
		
	// Mask to the read data and stores the value
	mask = (((1 << length) - 1) << pos);
	data = (data << pos) & mask;
	buffer &= ~mask;	
	buffer |= data;
		        
	// Write the register
	error = write(devAddr, regAddr, &buffer, 1);
	
	if (error != 0)
	{
		return error;
	}	
		
	return error;	
}


/*!
 * 
 * @brief		
 * @param	
 * @return enum status_code
 * 
 */
uint8_t WaspI2C::readBits(uint8_t devAddr, 
							uint8_t regAddr, 
							uint8_t *data,
							uint8_t pos,
							uint8_t length)
{
	uint8_t buffer;
	uint8_t mask;
	uint8_t error;
	
	// Not needed 
	//I2C.secureBegin();
	
	// Read the register
	error = read(devAddr, regAddr, &buffer, 1);
	
	if (error != 0)
	{
		return error;
	}	
		
	// Mask to the read data and stores the value
	buffer = buffer >> pos;
	mask = ((1 << length) - 1);
	buffer &= mask;
	data[0] = buffer;	
		
	return error;	
}


/*!
 * 
 * @brief	This function read
 * @param	uint8_t devAddr: 
 * @param	uint8_t regAddr: 
 * @param	uint8_t *data: 
 * @param	uint8_t pos: 
 * @return	enum status_code
 * 
 */
uint8_t WaspI2C::readBit(uint8_t devAddr, 
							uint8_t regAddr, 
							uint8_t *data,
							uint8_t pos)
{
	uint8_t buffer;
	uint8_t mask;
	uint8_t error;
	
	// Not needed 
	//I2C.secureBegin();
	
	// Read the register
	error = read(devAddr, regAddr, &buffer, 1);
	if (error != 0)
	{
		return error;
	}	
		
	// Mask to the read data and stores the value
	mask = (1 << pos);
	
	if ((mask & buffer) != 0)
	{
		data[0] = 1;
	}
	else
	{
		data[0] = 0;
		
	}
	
	// Write the register
	error = write(devAddr, regAddr, &buffer, 1);
	
	if (error != 0)
	{
		return error;
	}	
		
	return error;	
}


 /*!
 * 
 * @brief	It makes sure all I2C slaves are switched on when they have been
 * 			plugged to Waspmote. This avoids I2C collisions.
 * @return	void
 * 
 */
void WaspI2C::secureBegin()
{		
	// Get the 3V3 power supply state
	_power_3v3_on = WaspRegister & REG_3V3;	
	
	// this codeblock belongs to the performance of the I2C bus
	// check if any Sensor Board (with I2C components) is ON before using I2C
	if (_slavePresent == true)
	{	
		#if DEBUG_I2C > 0
			PRINT_I2C(F("Sensor Board power ON\n"));
		#endif		
		// It is necessary to switch on the power supply if the Sensor Board is 
		// connected to Waspmote so as not to cause intereferences in the I2C bus
		if (!_power_3v3_on)
		{
			PWR.setSensorPower(SENS_3V3, SENS_ON);
			delay(50);
		}		
	}		
}


/*!
 * 
 * @brief	This function scans for BME and Luxes sensors mainly in Ambient 
 * 			Control devices where the sensors arec directly connected to main 
 * 			SDA/SCL pins and 3V3 power supply
 * @return	'true' if salves are present; 'false' otherwise
 * 
 */
uint8_t WaspI2C::scanSlaves()
{		
	if (!scan(I2C_ADDRESS_GASPRO_BME280) || !scan(I2C_ADDRESS_TSL2561))
	{
		_slavePresent = true;
		return _slavePresent;
	}
	else 
	{
		_slavePresent = false;
		return _slavePresent;
	}
}

/*!
 * 
 * @brief	This function switches off and on the I2C again
 * @return	void
 * 
 */
void WaspI2C::recover()
{
	I2C.close();
	delay(1000);
	I2C.begin();
}
// Preinstantiate Objects //////////////////////////////////////////////////////

WaspI2C I2C = WaspI2C();



