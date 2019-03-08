/*
 file ModbusSlave.cpp
 
 Modbus over serial line - RTU Slave Waspmote Sketch 
 
 This library of functions are designed to enable a program send and
 receive data from a device that communicates using the Modbus protocol.
 
 Copyright (C) 2000 Philip Costigan  P.C. SCADA LINK PTY. LTD.
 Modified for Waspmote by Libelium, 2017
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 
 The functions included here have been derived from the 
 Modicon Modbus Protocol Reference Guide
 which can be obtained from Schneider at www.schneiderautomation.com.
 
 This code has its origins with 
 paul@pmcrae.freeserve.co.uk (http://www.pmcrae.freeserve.co.uk)
 who wrote a small program to read 100 registers from a modbus slave. 

 Version:	3.2
  
*/

#ifndef __WPROGRAM_H__
	#include "WaspClasses.h"
#endif

#include "ModbusSlave.h"


/****************************************************************************
 * BEGIN MODBUS RTU SLAVE FUNCTIONS
 ****************************************************************************/
/* constants */
enum
{ 
	MAX_READ_REGS = 0x7D, 
	MAX_WRITE_REGS = 0x7B, 
	MAX_MESSAGE_LENGTH = 256 
};


enum
{ 
	RESPONSE_SIZE = 6, 
	EXCEPTION_SIZE = 3, 
	CHECKSUM_SIZE = 2 
};

/* exceptions code */
enum
{ 
	NO_REPLY = -1, 
	EXC_FUNC_CODE = 1, 
	EXC_ADDR_RANGE = 2, 
	EXC_REGS_QUANT = 3, 
	EXC_EXECUTE = 4 
};

/* positions inside the query/response array */
enum
{ 
	SLAVE = 0, 
	FUNC, 
	START_H, 
	START_L, 
	REGS_H, 
	REGS_L, 
	BYTE_CNT 
};


/* enum of supported modbus function codes. If you implement a new one, put its function code here ! */
enum { 
		FC_READ_REGS  = 0x03,   //Read contiguous block of holding register
		FC_WRITE_REG  = 0x06,   //Write single holding register
		FC_WRITE_REGS = 0x10    //Write block of contiguous registers
};

/* supported functions. If you implement a new one, put its function code into this array! */
const unsigned char fsupported[] = { FC_READ_REGS, FC_WRITE_REG, FC_WRITE_REGS };


 /*!
 * @brief	Class contructor
 * @param 	void
 * @return	void
 */
ModbusSlave::ModbusSlave()
{
	Nowdt = 0;
	_protocol = RS485_COM;
	_socket = 0;
}


 /*!
 * @brief	Class contructor
 * @param 	uint8_t protocol: RS232 or RS485
 * @return	void
 */
ModbusSlave::ModbusSlave(uint8_t protocol)
{
	Nowdt = 0;
	_protocol = protocol;
	_socket = 0;
}


 /*!
 * @brief	Class contructor
 * @param 	uint8_t protocol: RS-232 or RS-485
 * @param	uint8_t socket: SOCKET_1 or SOCKET_0 (for RS-232)
 * @return	void
 */
ModbusSlave::ModbusSlave(uint8_t protocol, uint8_t socket)
{
	Nowdt = 0;
	_protocol = protocol;
	_socket = socket;
}


 /*!
 * @brief	Class contructor
 * @param 	unsigned char * buf: Array containing message to be sent to controller
 * @param	unsigned char start: Start of loop in crc counter, usually 0
 * @param	unsigned char cnt: Amount of bytes in message being sent to controller
 * @return	unsigned int temp: Returns crc byte for message
 */
unsigned int ModbusSlave::crc(unsigned char *buf, unsigned char start, unsigned char cnt) 
{
	unsigned char i, j;
	unsigned temp, temp2, flag;

	temp = 0xFFFF;

	for (i = start; i < cnt; i++)
	{
		temp = temp ^ buf[i];

		for (j = 1; j <= 8; j++) 
		{
			flag = temp & 0x0001;
			temp = temp >> 1;
			
			if (flag) 
			{
				temp = temp ^ 0xA001;
			}
		}
	}

	// Reverse byte order
	temp2 = temp >> 8;
	temp = (temp << 8) | temp2;
	temp &= 0xFFFF;

	return (temp);
}



 /*!
 * @brief	Start of the packet of a read_holding_register response
 * @param 	unsigned char function: the modbus function
 * @param	unsigned char count: specifies the quantity of complete bytes of data
 * @param	unsigned char *packet: pointer to the packet buffer
 * @return	void
 */
void ModbusSlave::build_read_packet(unsigned char function, unsigned char count, unsigned char *packet) 
{
	packet[SLAVE] = slave;
	packet[FUNC] = function;
	packet[2] = count * 2;
} 


 /*!
 * @brief	Start of the packet of a preset_multiple_register response
 * @param 	unsigned char function: the modbus function
 * @param	unsigned int start_addr: start address where reading
 * @param	unsigned char count: specifies the quantity of complete bytes of data
 * @param	unsigned char *packet: pointer to the packet buffer
 * @return	void
 */
void ModbusSlave::build_write_packet(unsigned char function, unsigned int start_addr, unsigned char count, unsigned char *packet) 
{
	packet[SLAVE] = slave;
	packet[FUNC] = function;
	packet[START_H] = start_addr >> 8;
	packet[START_L] = start_addr & 0x00FF;
	packet[REGS_H] = 0x00;
	packet[REGS_L] = count;
}


 /*!
 * @brief	Start of the packet of a write_single_register response
 * @param 	unsigned char function: the modbus function
 * @param	unsigned int write_addr: start address where write
 * @param	unsigned int reg_val: value to write
 * @param	unsigned char *packet: pointer to the packet buffer
 * @return	void
 */
void ModbusSlave::build_write_single_packet(unsigned char function, unsigned int write_addr, unsigned int reg_val, unsigned char* packet) 
{
	packet[SLAVE] = slave;
	packet[FUNC] = function;
	packet[START_H] = write_addr >> 8;
	packet[START_L] = write_addr & 0x00FF;
	packet[REGS_H] = reg_val >> 8;
	packet[REGS_L] = reg_val & 0x00FF;
} 


 /*!
 * @brief	Start of the packet of an exception response 
 * @param 	unsigned char function: the modbus function
 * @param	unsigned char exception: exception code
 * @param	unsigned char *packet: pointer to the packet buffer
 * @return	void
 */
void ModbusSlave::build_error_packet( unsigned char function, unsigned char exception, unsigned char *packet) 
{
	packet[SLAVE] = slave;
	packet[FUNC] = function + 0x80;
	packet[2] = exception;
} 


 /*!
 * @brief	Function to add a checksum to the end of a packet. 
 * 			Please note that the packet array must be at least 2 fields longer than
 * 			string_length.
 * 
 * @param	unsigned char *packet: pointer to the packet
 * @param	unsigned char string_length: length of the packet
 * @return	void
 */
void ModbusSlave::modbus_reply(unsigned char *packet, unsigned char string_length) 
{
	int temp_crc;

	temp_crc = crc(packet, 0, string_length);
	packet[string_length] = temp_crc >> 8;
	string_length++;
	packet[string_length] = temp_crc & 0x00FF;
} 


 /*!
 * @brief	Function to send a reply to a modbus master
 * @param 	unsigned char *query: packet to be sent
 * @param	unsigned char string_length: length of the packet
 * @return	int: number of bytes sent
 */
int ModbusSlave::send_reply(unsigned char *query, unsigned char string_length) 
{
	unsigned char i;

	modbus_reply(query, string_length);
	string_length += 2;
	
	if (_protocol == RS232_COM)
	{
		for (i = 0; i < string_length; i++)
		{
			W232.send(query[i], BYTE);
		}
	}
	else 
	{
		for (i = 0; i < string_length; i++) 
		{
			W485.send(query[i], BYTE);
		}
	}
	
	#if DEBUG_MODBUS_SLAVE > 1
		PRINT_MODBUS_SLAVE("Slave send:");
		USB.printHexln(query, string_length);
	#endif


	// It does not mean that the write was successful
	return i;
}


 /*!
 * @brief	Function to monitor for a request from the modbus master
 * @param 	unsigned char *received_string: received string
 * @return	int: bytes received
 */
int ModbusSlave::receive_request(unsigned char *received_string) 
{
	int bytes_received = 0;

	if (_protocol == RS232_COM) 
	{
		// FIXME: does Serial.available wait 1.5T or 3.5T before exiting the loop?
		while (W232.available()) 
		{
			received_string[bytes_received] = W232.read();
			bytes_received++;
			delay(1);
			if (bytes_received >= MAX_MESSAGE_LENGTH)
			{
				// Port error
				return NO_REPLY;
			}
		}
	}
	else 
	{
		// FIXME: does Serial.available wait 1.5T or 3.5T before exiting the loop?
		while (W485.available()) 
		{
			received_string[bytes_received] = W485.read();
			bytes_received++;
			
			if (bytes_received >= MAX_MESSAGE_LENGTH)
			{
				// Port error
				return NO_REPLY;
			}
		}
	}
	#if DEBUG_MODBUS_SLAVE > 1
		PRINT_MODBUS_SLAVE("Slave receive:");
		USB.printHexln(received_string, bytes_received);
	#endif

	return (bytes_received);
}


 /*!
 * @brief	Function to the correct request is returned and that the checksum is correct.
 * @param 	unsigned char *data: data to be sent
 * @return	int: response length. 0 if failed
 */
int ModbusSlave::modbus_request(unsigned char *data) 
{
	int response_length;
	unsigned int crc_calc = 0;
	unsigned int crc_received = 0;
	unsigned char recv_crc_hi;
	unsigned char recv_crc_lo;

	response_length = receive_request(data);

	if (response_length > 0)
	{
		crc_calc = crc(data, 0, response_length - 2);
		recv_crc_hi = (unsigned) data[response_length - 2];
		recv_crc_lo = (unsigned) data[response_length - 1];
		crc_received = data[response_length - 2];
		crc_received = (unsigned) crc_received << 8;
		crc_received = crc_received | (unsigned) data[response_length - 1];

		/*********** check CRC of response ************/
		if (crc_calc != crc_received) 
		{
				return NO_REPLY;
		}

		// check for slave id
		if (slave != data[SLAVE]) 
		{
			return NO_REPLY;
		}
	}

	return (response_length);
}


 /*!
 * @brief	Function to check that the request can be processed by the slave
 * @param 	unsigned char *data: data to validate
 * @param	unsigned char length: length of the request
 * @param	unsigned int regs_size: size of register
 * @return	int: 0 if OK. 
 */
int ModbusSlave::validate_request(unsigned char *data, unsigned char length, unsigned int regs_size) 
{
	int i, fcnt = 0;
	unsigned int regs_num = 0;
	unsigned int start_addr = 0;
	unsigned char max_regs_num;

	// check function code
	for (i = 0; i < sizeof(fsupported); i++) 
	{
		if (fsupported[i] == data[FUNC]) 
		{
			fcnt = 1;
			break;
		}
	}
	
	if (0 == fcnt)
		return EXC_FUNC_CODE;
			
	if (FC_WRITE_REG == data[FUNC]) 
	{
		/* For function write single reg, this is the target reg.*/
		regs_num = ((int) data[START_H] << 8) + (int) data[START_L];
		if (regs_num >= regs_size)
			return EXC_ADDR_RANGE;
		
		return 0;
	}                

	// For functions read/write regs, this is the range
	regs_num = ((int) data[REGS_H] << 8) + (int) data[REGS_L];

	// Check quantity of registers
	if (FC_READ_REGS == data[FUNC])
	{
		max_regs_num = MAX_READ_REGS;
	}
	else if (FC_WRITE_REGS == data[FUNC])
	{
		max_regs_num = MAX_WRITE_REGS;
	}

	if ((regs_num < 1) || (regs_num > max_regs_num))
	{
		return EXC_REGS_QUANT;
	}

	// Check registers range, start address is 0
	start_addr = ((int) data[START_H] << 8) + (int) data[START_L];
	
	if ((start_addr + regs_num) > regs_size)
	{
		return EXC_ADDR_RANGE;
	}

	// OK, no exception
	return 0;
}


 /*!
 * @brief	Writes into the slave's holding registers the data in query
 * @param 	unsigned int start_addr: start address
 * @param	unsigned char *query: query to write
 * @param	int *regs: registers to be writed
 * @return	int: bytes sent
 */
int ModbusSlave::write_regs(unsigned int start_addr, unsigned char *query, int *regs) 
{
	int temp;
	unsigned int i;

	for (i = 0; i < query[REGS_L]; i++) {
		// Shift reg hi_byte to temp
		temp = (int) query[(BYTE_CNT + 1) + i * 2] << 8;
		
		// OR with lo_byte          
		temp = temp | (int) query[(BYTE_CNT + 2) + i * 2];
		regs[start_addr + i] = temp;
	}

	return i;
}


 /*!
 * @brief	Write the data from an array into the holding registers of the slave
 * @param	unsigned int start_addr: start address
 * @param	unsigned char count: number of bytes
 * @param	unsigned char *query: query to be writed
 * @param	int *regs: registers to be writed
 * @return	int: status
 */
int ModbusSlave::preset_multiple_registers(unsigned int start_addr, unsigned char count, unsigned char *query, int *regs) 
{
	unsigned char function = FC_WRITE_REGS;	/* Preset Multiple Registers */
	int status = 0;
	unsigned char packet[RESPONSE_SIZE + CHECKSUM_SIZE];

	build_write_packet(function, start_addr, count, packet);

	if (write_regs(start_addr, query, regs))
	{
		status = send_reply(packet, RESPONSE_SIZE);
	}

		return (status);
}


  /*!
 * @brief	Write a single int val into a single holding register of the slave
 * @param	unsigned int write_addr: write address
 * @param	unsigned char *query: query to be writed
 * @param	int *regs: registers to write
 * @return	int: status
 */
int ModbusSlave::write_single_register(unsigned int write_addr, unsigned char *query, int *regs) 
{
	// Function: Write Single Register
	unsigned char function = FC_WRITE_REG;
	int status = 0;
	unsigned int reg_val;
	unsigned char packet[RESPONSE_SIZE + CHECKSUM_SIZE];

	reg_val = query[REGS_H] << 8 | query[REGS_L];
	build_write_single_packet(function, write_addr, reg_val, packet);
	regs[write_addr] = (int) reg_val;
	
	/*
	written.start_addr=write_addr;
	written.num_regs=1;
	*/
	
	status = send_reply(packet, RESPONSE_SIZE);    

	return (status);
}

 /*!
 * @brief	Read the slave's holdings registers and sends them to the Modbus master
 * @param 	unsigned int start_addr: start address
 * @param	unsigned char reg_count: number of bytes
 * @param	int *regs: registers to be read
 * @return	int: status
 */
int ModbusSlave::read_holding_registers(unsigned int start_addr, unsigned char reg_count, int *regs) 
{
	/* Read Holding Registers */
	unsigned char function = FC_READ_REGS; 
	int packet_size = 3;
	int status;
	unsigned int i;
	unsigned char packet[MAX_MESSAGE_LENGTH];

	build_read_packet(function, reg_count, packet);

	for (i = start_addr; i < (start_addr + (unsigned int) reg_count); i++)
	{
		packet[packet_size] = regs[i] >> 8;
		packet_size++;
		packet[packet_size] = regs[i] & 0x00FF;
		packet_size++;
	} 

	status = send_reply(packet, packet_size);

	return (status);
}


 /*!
 * @brief	Sets the communication parameters for of the serial line.
 * @param	uint8_t _slave: identification number of the slave in the Modbus network (1 to 127)
 * @param	long baud: baudrate in bps (typical values 9600, 19200... 115200)
 * @param	uint8_t socket: SOCKET_0 or SOCKET_1  for RS-232 protocol
 * @return	void
 */
uint8_t ModbusSlave::configure(uint8_t _slave, long baud, uint8_t socket)
{
	slave = _slave;
	uint8_t answer;

	if (_protocol == RS232_COM)
	{
		//~ W232.ON(socket);
		//~ delay(10);
		//~ beginSerial(baud, socket);
		_socket = socket;
		W232.ON(_socket);
		// Configure the baud rate of the module
		W232.baudRateConfig(baud);
		// Configure the parity bit as disabled 
		W232.parityBit(DISABLE);
		// Use one stop bit configuration 
		W232.stopBitConfig(1); 
	}
	else 
	{
		// init module
		answer = W485.ON();
		delay(100);		
		if (answer != 0) 
		{
			return 1;
		}

		// Configure the baud rate of the module
		W485.baudRateConfig(baud);
		// Configure the parity bit as disabled 
		W485.parityBit(DISABLE);
		// Use one stop bit configuration 
		W485.stopBitConfig(1); 
	}
	
	return 0;
}


 /*!
 * @brief	Sets the communication parameters for of the serial line SOCKET_0 by default
 * @param	uint8_t _slave: identification number of the slave in the Modbus network (1 to 127)
 * @param	long baud: baudrate in bps (typical values 9600, 19200... 115200)
 * @return	void
 */
uint8_t ModbusSlave::configure(uint8_t _slave, long baud)
{
	return configure(_slave, baud, 0);
}


 /*!
 * @brief	checks if there is any valid request from the modbus master. If there is performs the requested action.
 * @param	int *regs: an array with the holding registers. They start at address 1 (master point of view)
 * @param	unsigned int regs_size: total number of holding registers.
 * @return	int: returns: 
 * 			- 0 if no request from master
 * 			- (-1) if no reply is sent to the master
 */
int ModbusSlave::update(int *regs, unsigned int regs_size) 
{
	unsigned char query[MAX_MESSAGE_LENGTH];
	unsigned char errpacket[EXCEPTION_SIZE + CHECKSUM_SIZE];
	unsigned int start_addr;
	int exception;
	int length;
	unsigned long now = millis();

	if (_protocol == RS232_COM) 
	{
		length = W232.available();
	} 
	else 
	{
		length = W485.available();
	}

	if (length == 0) 
	{
		lastBytesReceived = 0;
		
		#if DEBUG_MODBUS_SLAVE > 2
			PRINTLN_MODBUS_SLAVE("No request from Master1");
		#endif
		return 0;
	}

	if (lastBytesReceived != length)
	{
		lastBytesReceived = length;
		Nowdt = now + T35;		
		#if DEBUG_MODBUS_SLAVE > 2
			PRINTLN_MODBUS_SLAVE("No request from Master2");
		#endif
		return 0;
	}
	
	if (now < Nowdt) 
	{		
		#if DEBUG_MODBUS_SLAVE > 2
			PRINTLN_MODBUS_SLAVE("No request from Master3");
		#endif
		return 0;
	}

	lastBytesReceived = 0;

	length = modbus_request(query);

	if (length < 1) 
	{
		return length;
	}
		 
		exception = validate_request(query, length, regs_size);

	if (exception)
	{
		build_error_packet( query[FUNC], exception, errpacket);
		send_reply(errpacket, EXCEPTION_SIZE);
		return (exception);
	} 

	start_addr = ((int) query[START_H] << 8) + (int) query[START_L];

	switch (query[FUNC])
	{
		case FC_READ_REGS:
			return read_holding_registers(start_addr, query[REGS_L], regs);
		break;
		
		case FC_WRITE_REGS:
			return preset_multiple_registers(start_addr, query[REGS_L], query, regs);
		break;
		
		case FC_WRITE_REG: 
			write_single_register(start_addr, query, regs);
		break;
	}		
}


