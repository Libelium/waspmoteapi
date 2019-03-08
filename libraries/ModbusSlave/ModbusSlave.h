/* file ModbusSlave.cpp
 * 
 * ModbusSlave library implementing a Modbus RTU Slave for Waspmote
 * Based on the work published by jpmzometa at 
 * http://sites.google.com/site/jpmzometa/arduino-mbrt
 * 
 * These library of functions are designed to enable a program send and
 * receive data from a device that communicates using the Modbus protocol.
 * 
 * Copyright (C) 2000 Philip Costigan  P.C. SCADA LINK PTY. LTD.
 * Modified for Waspmote by Libelium, 2017
 * 
 * This file is part of ModbusSlave.
 * 
 * ModbusSlave is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 * 
 * The functions included here have been derived from the 
 * Modbus Specifications and Implementation Guides
 * 
 * http://www.modbus.org/docs/Modbus_over_serial_line_V1_02.pdf
 * http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b.pdf
 * http://www.modbus.org/docs/PI_MBUS_300.pdf
 * 
 * 
 *  Version:	3.1
 * 
 ****************************************************************************/

#define		RS485_COM	0x01
#define		RS232_COM	0x02


/*******************************************************************************
 * Definitions 
 ******************************************************************************/

/*! 
 * \def DEBUG_MODBUS_SLAVE 
 * \brief Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define DEBUG_MODBUS_SLAVE	0
#define PRINT_MODBUS_SLAVE(str)	USB.print(F("[MB_SLAVE] ")); USB.print(str);
#define PRINTLN_MODBUS_SLAVE(str)	USB.print(F("[MB_SLAVE] ")); USB.println(str);


/****************************************************************************
 * BEGIN MODBUS RTU SLAVE FUNCTIONS
 ****************************************************************************/

#ifndef MODBUS_SLAVE_H
#define MODBUS_SLAVE_H

#include <inttypes.h>
#include "Wasp232.h"
#include "Wasp485.h"


class ModbusSlave 
{
	public:
	
		// Empty constructor
		ModbusSlave();
		ModbusSlave(uint8_t);
		ModbusSlave(uint8_t, uint8_t);

		// Configure the communication parameters
		uint8_t configure(uint8_t, long);
		uint8_t configure(uint8_t, long, uint8_t );
		// Update the registers
		int update(int *regs, unsigned int regs_size); 
		
	protected:
	
		unsigned char slave;
		unsigned long Nowdt;
		unsigned int lastBytesReceived;
		const unsigned long T35 = 5;
		uint8_t _protocol;
		uint8_t _socket;
		

		void modbus_reply(unsigned char *packet, unsigned char string_length);
		int preset_multiple_registers(unsigned int start_addr,unsigned char count,unsigned char *query,int *regs);
		int write_single_register(unsigned int write_addr, unsigned char *query, int *regs);  
		int read_holding_registers(unsigned int start_addr, unsigned char reg_count, int *regs);
		void build_error_packet(unsigned char function,unsigned char exception, unsigned char *packet);
		unsigned int crc(unsigned char *buf, unsigned char start, unsigned char cnt);
		void build_read_packet(unsigned char function, unsigned char count, unsigned char *packet);
		void build_write_packet(unsigned char function, unsigned int start_addr, unsigned char count, unsigned char *packet);
		void build_write_single_packet(unsigned char function, unsigned int write_addr, unsigned int reg_val, unsigned char* packet);
		int send_reply(unsigned char *query, unsigned char string_length);
		int receive_request(unsigned char *received_string);
		int modbus_request(unsigned char *data);
		int validate_request(unsigned char *data, unsigned char length, unsigned int regs_size);
		int write_regs(unsigned int start_addr, unsigned char *query, int *regs);
};

#endif

